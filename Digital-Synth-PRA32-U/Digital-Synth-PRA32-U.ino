/*
 * Digital Synth PRA32-U
 */

//#define DEBUG_PRINT


#define USE_USB_MIDI      // Select USB Stack: "Adafruit TinyUSB" in the Arduino IDE "Tools" menu
//#define USE_SERIAL1_MIDI

#define SERIAL1_MIDI_SPEED              (31250)
//#define SERIAL1_MIDI_SPEED              (38400)


#define MIDI_CH                         (0)  // 0-based


// for Pimoroni Pico Audio Pack [PIM544]
#define I2S_DAC_MUTE_OFF_PIN            (22)
#define I2S_DATA_PIN                    (9)
//#define I2S_MCLK_PIN                    (0)
//#define I2S_MCLK_MULT                   (0)
#define I2S_BCLK_PIN                    (10)  // I2S_LRCLK_PIN is I2S_BCLK_PIN + 1
#define I2S_SWAP_BCLK_AND_LRCLK_PINS    (false)

#define I2S_BUFFERS                     (4)
#define I2S_BUFFER_WORDS                (64)


//#define USE_PWM_AUDIO

#define PWM_AUDIO_L_PIN                 (28)
#define PWM_AUDIO_R_PIN                 (27)

#define PWM_AUDIO_BUFFERS               (4)
#define PWM_AUDIO_BUFFER_WORDS          (64)

////////////////////////////////////////////////////////////////

#include "pra32-u-common.h"
#include "pra32-u-synth.h"

PRA32_U_Synth g_synth;


#include <MIDI.h>
#if defined(USE_USB_MIDI)
#include <Adafruit_TinyUSB.h>
Adafruit_USBD_MIDI usbd_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usbd_midi, MIDI);
#elif defined(USE_SERIAL1_MIDI)
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
#endif // defined(USE_USB_MIDI)


#if defined(USE_PWM_AUDIO)
#include <PWMAudio.h>
PWMAudio g_pwm_l(PWM_AUDIO_L_PIN);
PWMAudio g_pwm_r(PWM_AUDIO_R_PIN);
#else // defined(USE_PWM_AUDIO)
#include <I2S.h>
I2S g_i2s_output(OUTPUT);
#endif // defined(USE_PWM_AUDIO)


void handleNoteOn(byte channel, byte pitch, byte velocity);
void handleNoteOff(byte channel, byte pitch, byte velocity);
void handleControlChange(byte channel, byte number, byte value);
void handleHandleProgramChange(byte channel, byte number);
void handleHandlePitchBend(byte channel, int bend);


void __not_in_flash_func(setup)() {
}

void __not_in_flash_func(loop)() {
}


void __not_in_flash_func(setup1)() {
#if defined(USE_PWM_AUDIO)
  g_pwm_l.setBuffers(PWM_AUDIO_BUFFERS, PWM_AUDIO_BUFFER_WORDS / 2);
  g_pwm_r.setBuffers(PWM_AUDIO_BUFFERS, PWM_AUDIO_BUFFER_WORDS / 2);
  g_pwm_l.setFrequency(SAMPLING_RATE);
  g_pwm_r.setFrequency(SAMPLING_RATE);
  g_pwm_l.begin();
  g_pwm_r.begin();
#else // defined(USE_PWM_AUDIO)
  g_i2s_output.setSysClk(SAMPLING_RATE);
  g_i2s_output.setFrequency(SAMPLING_RATE);
  g_i2s_output.setDATA(I2S_DATA_PIN);
#if defined(I2S_MCLK_PIN)
  g_i2s_output.setMCLK(I2S_MCLK_PIN);
  g_i2s_output.setMCLKmult(I2S_MCLK_MULT);
#endif // defined(I2S_MCLK_PIN)
  g_i2s_output.setBCLK(I2S_BCLK_PIN);
  if (I2S_SWAP_BCLK_AND_LRCLK_PINS) {
    g_i2s_output.swapClocks();
  }
  g_i2s_output.setBitsPerSample(16);
  g_i2s_output.setBuffers(I2S_BUFFERS, I2S_BUFFER_WORDS);
  g_i2s_output.begin();
#endif // defined(USE_PWM_AUDIO)


#if defined(USE_USB_MIDI)
  TinyUSB_Device_Init(0);
  USBDevice.setManufacturerDescriptor("ISGK Instruments");
  USBDevice.setProductDescriptor("Digital Synth PRA32-U");
#endif // defined(USE_USB_MIDI)
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleProgramChange(handleHandleProgramChange);
  MIDI.setHandlePitchBend(handleHandlePitchBend);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
#if defined(USE_SERIAL1_MIDI)
  Serial1.begin(SERIAL1_MIDI_SPEED);
#endif // defined(USE_SERIAL1_MIDI)


#if defined(DEBUG_PRINT)
#if defined(USE_SERIAL1_MIDI)
  Serial.begin(0);  // Select USB Stack: "Pico SDK" in the Arduino IDE "Tools" menu
#else // defined(USE_SERIAL1_MIDI)
  Serial1.begin(115200);
#endif // defined(USE_SERIAL1_MIDI)
#endif // defined(DEBUG_PRINT)


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);


#if defined(USE_PWM_AUDIO)
#else // defined(USE_PWM_AUDIO)
#if defined(I2S_DAC_MUTE_OFF_PIN)
  pinMode(I2S_DAC_MUTE_OFF_PIN, OUTPUT);
  digitalWrite(I2S_DAC_MUTE_OFF_PIN, HIGH);
#endif // defined(I2S_DAC_MUTE_OFF_PIN)
#endif // defined(USE_PWM_AUDIO)
}

void __not_in_flash_func(loop1)() {

#if defined(DEBUG_PRINT)
  uint32_t debug_measurement_start0_us = micros();
#endif // defined(DEBUG_PRINT)


#if defined(USE_PWM_AUDIO)

  for (uint32_t i = 0; i < (PWM_AUDIO_BUFFER_WORDS + 15) / 16; i++) {
    MIDI.read();
  }

#if defined(DEBUG_PRINT)
  uint32_t debug_measurement_start1_us = micros();
#endif // defined(DEBUG_PRINT)

  int16_t left_buffer[PWM_AUDIO_BUFFER_WORDS];
  int16_t right_buffer[PWM_AUDIO_BUFFER_WORDS];
  for (uint32_t i = 0; i < PWM_AUDIO_BUFFER_WORDS; i++) {
    left_buffer[i] = g_synth.process(right_buffer[i]);
  }

#if defined(DEBUG_PRINT)
  uint32_t debug_measurement_end_us = micros();
#endif // defined(DEBUG_PRINT)

  for (uint32_t i = 0; i < I2S_BUFFER_WORDS; i++) {
    g_pwm_l.write(left_buffer[i]);
    g_pwm_r.write(right_buffer[i]);
  }

#else // defined(USE_PWM_AUDIO)

  for (uint32_t i = 0; i < (I2S_BUFFER_WORDS + 15) / 16; i++) {
    MIDI.read();
  }

#if defined(DEBUG_PRINT)
  uint32_t debug_measurement_start1_us = micros();
#endif // defined(DEBUG_PRINT)

  int16_t left_buffer[I2S_BUFFER_WORDS];
  int16_t right_buffer[I2S_BUFFER_WORDS];
  for (uint32_t i = 0; i < I2S_BUFFER_WORDS; i++) {
    left_buffer[i] = g_synth.process(right_buffer[i]);
  }

#if defined(DEBUG_PRINT)
  uint32_t debug_measurement_end_us = micros();
#endif // defined(DEBUG_PRINT)

  for (uint32_t i = 0; i < I2S_BUFFER_WORDS; i++) {
    g_i2s_output.write16(left_buffer[i], right_buffer[i]);
  }

#endif // defined(USE_PWM_AUDIO)


#if defined(DEBUG_PRINT)
  static uint32_t s_debug_measurement_max0_us = 0;
  uint32_t debug_measurement_elapsed0_us = debug_measurement_end_us - debug_measurement_start0_us;
  s_debug_measurement_max0_us += (debug_measurement_elapsed0_us > s_debug_measurement_max0_us) *
                                 (debug_measurement_elapsed0_us - s_debug_measurement_max0_us);

  static uint32_t s_debug_measurement_max1_us = 0;
  uint32_t debug_measurement_elapsed1_us = debug_measurement_end_us - debug_measurement_start1_us;
  s_debug_measurement_max1_us += (debug_measurement_elapsed1_us > s_debug_measurement_max1_us) *
                                 (debug_measurement_elapsed1_us - s_debug_measurement_max1_us);

  static uint32_t s_debug_loop_counter = 0;
  if (++s_debug_loop_counter == 4000) {
    s_debug_loop_counter = 0;
#if defined(USE_SERIAL1_MIDI)
    Serial.println(debug_measurement_elapsed1_us);
    Serial.println(s_debug_measurement_max1_us);
    Serial.println(debug_measurement_elapsed0_us);
    Serial.println(s_debug_measurement_max0_us);
    Serial.println();
#else // defined(USE_SERIAL1_MIDI)
    Serial1.println(debug_measurement_elapsed1_us);
    Serial1.println(s_debug_measurement_max1_us);
    Serial1.println(debug_measurement_elapsed0_us);
    Serial1.println(s_debug_measurement_max0_us);
    Serial1.println();
#endif // defined(USE_SERIAL1_MIDI)
  }
#endif // defined(DEBUG_PRINT)
}

void __not_in_flash_func(handleNoteOn)(byte channel, byte pitch, byte velocity)
{
  if ((channel - 1) == MIDI_CH) {
    if (velocity > 0) {
      g_synth.note_on(pitch, velocity);
    } else {
      g_synth.note_off(pitch);
    }
  }
}

void __not_in_flash_func(handleNoteOff)(byte channel, byte pitch, byte velocity)
{
  if ((channel - 1) == MIDI_CH) {
    (void) velocity;
    g_synth.note_off(pitch);
  }
}

void __not_in_flash_func(handleControlChange)(byte channel, byte number, byte value)
{
  if ((channel - 1) == MIDI_CH) {
    g_synth.control_change(number, value);
  }
}

void __not_in_flash_func(handleHandleProgramChange)(byte channel, byte number)
{
  if ((channel - 1) == MIDI_CH) {
    g_synth.program_change(number);
  }
}

void __not_in_flash_func(handleHandlePitchBend)(byte channel, int bend)
{
  if ((channel - 1) == MIDI_CH) {
    g_synth.pitch_bend((bend + 8192) & 0x7F, (bend + 8192) >> 7);
  }
}

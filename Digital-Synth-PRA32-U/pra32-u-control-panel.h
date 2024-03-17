#pragma once

#include "pra32-u-common.h"

static uint32_t s_adc_average_value_0 = 0;
static uint32_t s_adc_average_value_1 = 0;
static uint32_t s_adc_average_value_2 = 0;

static char s_display_buffer[8][21 + 1] = {
  "                    1",
  "Filter     Filter    ",
  "Cutoff     Resonance ",
  "A 127[127] B   0[  0]",
  "                     ",
  "           Filter    ",
  "           EG Amt    ",
  "           C  64[ +0]",
};

INLINE void PRA32_U_ControlPanel_setup() {
#if defined(PRA32_U_USE_CONTROL_PANEL)
#if defined(PRA32_U_USE_CONTROL_PANEL_ANALOG_INPUT)
  adc_init();
  adc_gpio_init(26);
  adc_gpio_init(27);
  adc_gpio_init(28);
#endif  // defined(PRA32_U_USE_CONTROL_PANEL_ANALOG_INPUT)
#endif  // defined(PRA32_U_USE_CONTROL_PANEL)
}

INLINE void PRA32_U_ControlPanel_update(uint32_t loop_counter) {
#if defined(PRA32_U_USE_CONTROL_PANEL)
#if defined(PRA32_U_USE_CONTROL_PANEL_ANALOG_INPUT)
  switch (loop_counter & 0x3F) {
  case 0x10:
    adc_select_input(0);
    s_adc_average_value_0 =
      (adc_read() + adc_read() + adc_read() + adc_read() +
       adc_read() + adc_read() + adc_read() + adc_read()) >> 7;
    break;
  case 0x20:
    adc_select_input(1);
    s_adc_average_value_1 =
      (adc_read() + adc_read() + adc_read() + adc_read() +
       adc_read() + adc_read() + adc_read() + adc_read()) >> 7;
    break;
  case 0x30:
    adc_select_input(2);
    s_adc_average_value_2 =
      (adc_read() + adc_read() + adc_read() + adc_read() +
       adc_read() + adc_read() + adc_read() + adc_read()) >> 7;
    break;
  }
#endif  // defined(PRA32_U_USE_CONTROL_PANEL_ANALOG_INPUT)
#endif  // defined(PRA32_U_USE_CONTROL_PANEL)
}

INLINE void PRA32_U_ControlPanel_debug_print(uint32_t loop_counter) {
#if defined(PRA32_U_USE_DEBUG_PRINT)
#if defined(PRA32_U_USE_CONTROL_PANEL)
  switch (loop_counter) {
  case  5 * 750:
    Serial1.print("\e[7;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[0]));
    break;
  case  6 * 750:
    Serial1.print("\e[8;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[1]));
    break;
  case  7 * 750:
    Serial1.print("\e[9;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[2]));
    break;
  case  8 * 750:
    Serial1.print("\e[10;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[3]));
    break;
  case  9 * 750:
    Serial1.print("\e[11;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[4]));
    break;
  case 10 * 750:
    Serial1.print("\e[12;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[5]));
    break;
  case 11 * 750:
    Serial1.print("\e[13;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[6]));
    break;
  case 12 * 750:
    Serial1.print("\e[14;1H\e[K");
    Serial1.print(static_cast<char*>(s_display_buffer[7]));
    break;
#if defined(PRA32_U_USE_CONTROL_PANEL_ANALOG_INPUT)
  case 13 * 750:
    Serial1.print("\e[16;1H\e[K");
    Serial1.print(s_adc_average_value_0);
    break;
  case 14 * 750:
    Serial1.print("\e[17;1H\e[K");
    Serial1.print(s_adc_average_value_1);
    break;
  case 15 * 750:
    Serial1.print("\e[18;1H\e[K");
    Serial1.print(s_adc_average_value_2);
    break;
#endif  // defined(PRA32_U_USE_CONTROL_PANEL_ANALOG_INPUT)
  }
#endif  // defined(PRA32_U_USE_CONTROL_PANEL)
#endif  // defined(PRA32_U_USE_DEBUG_PRINT)
}

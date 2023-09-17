

A4_FREQ = 440.0

SAMPLING_RATE       = 48000
FREQUENCY_MAX       = 23000
BIT_DEPTH           = 8
NOTE_NUMBER_MIN     = 0
NOTE_NUMBER_MAX     = 127
NOTE_NUMBER_INVALID = 255

PROGRAM_NUMBER_MAX           = 15

OSC_CONTROL_INTERVAL_BITS    = 1
OSC_CONTROL_INTERVAL         = 0x01 << OSC_CONTROL_INTERVAL_BITS
OSC_PHASE_RESOLUTION_BITS    = 24
OSC_TUNE_TABLE_STEPS_BITS    = 8
OSC_TUNE_DENOMINATOR_BITS    = 15
OSC_WAVE_TABLE_AMP_BITS      = 13
OSC_WAVE_TABLE_AMP           = 1 << OSC_WAVE_TABLE_AMP_BITS
OSC_WAVE_TABLE_SAMPLES_BITS  = 9
OSC_DETUNE_MUL_NUM_BITS      = 4
OSC_DETUNE_FREQ_MAX          = (20 * 2) * (1 << 24) / SAMPLING_RATE
FILTER_CONTROL_INTERVAL_BITS = 3
FILTER_CONTROL_INTERVAL      = 0x01 << FILTER_CONTROL_INTERVAL_BITS
FILTER_TABLE_FRACTION_BITS   = 30
EG_CONTROL_INTERVAL          = 0x10
EG_LEVEL_MAX                 = 0x40000000
EG_LEVEL_MAX_2               = 0x7FFFFFFF

DATA_BYTE_MAX         = 0x7F
STATUS_BYTE_INVALID   = 0x7F
DATA_BYTE_INVALID     = 0x80
STATUS_BYTE_MIN       = 0x80
NOTE_OFF              = 0x80
NOTE_ON               = 0x90
CONTROL_CHANGE        = 0xB0
PROGRAM_CHANGE        = 0xC0
PITCH_BEND            = 0xE0
SYSTEM_MESSAGE_MIN    = 0xF0
SYSTEM_EXCLUSIVE      = 0xF0
TIME_CODE             = 0xF1
SONG_POSITION         = 0xF2
SONG_SELECT           = 0xF3
TUNE_REQUEST          = 0xF6
EOX                   = 0xF7
REAL_TIME_MESSAGE_MIN = 0xF8
ACTIVE_SENSING        = 0xFE

MODULATION      = 1
SUSTAIN_PEDAL   = 64


OSC_1_WAVE      = 24
OSC_1_SHAPE     = 102
OSC_1_MORPH     = 103
MIXER_SUB_OSC   = 26

OSC_2_WAVE      = 55
OSC_2_COARSE    = 20
OSC_2_PITCH     = 21
MIXER_OSC_MIX   = 25

FILTER_CUTOFF   = 16
FILTER_RESO     = 17
FILTER_EG_AMT   = 18
FILTER_KEY_TRK  = 86

EG_ATTACK       = 23
EG_DECAY        = 19
EG_SUSTAIN      = 27
EG_RELEASE      = 28

EG_OSC_AMT      = 104
EG_OSC_DST      = 105
VOICE_MODE      = 87
PORTAMENTO      = 22

LFO_WAVE        = 14
LFO_RATE        = 80
LFO_DEPTH       = 81
LFO_FADE_TIME   = 15

LFO_OSC_AMT     = 82
LFO_OSC_DST     = 9
LFO_FILTER_AMT  = 83
AMP_GAIN        = 110

AMP_ATTACK      = 56
AMP_DECAY       = 57
AMP_SUSTAIN     = 58
AMP_RELEASE     = 59

FILTER_MODE     = 109
EG_AMP_MOD      = 31
REL_EQ_DECAY    = 89
P_BEND_RANGE    = 85

CHORUS_MODE     = 63
CHORUS_RATE     = 61
CHORUS_DEPTH    = 60


PC_BY_CC_8      = 112
PC_BY_CC_9      = 113
PC_BY_CC_10     = 114
PC_BY_CC_11     = 115
PC_BY_CC_12     = 116
PC_BY_CC_13     = 117
PC_BY_CC_14     = 118
PC_BY_CC_15     = 119


ALL_SOUND_OFF   = 120
RESET_ALL_CTRLS = 121
ALL_NOTES_OFF   = 123
OMNI_MODE_OFF   = 124
OMNI_MODE_ON    = 125
MONO_MODE_ON    = 126
POLY_MODE_ON    = 127

OSC_WAVE_SAW       = 0
OSC_WAVE_SINE      = 25
OSC_WAVE_TRIANGLE  = 75
OSC_WAVE_1_PULSE   = 100
OSC_WAVE_2_NOISE   = 100
OSC_WAVE_SQUARE    = 127

OSC_DST_PITCH      = 0
OSC_DST_PITCH_2    = 64
OSC_DST_SHAPE_1    = 127

LFO_WAVE_TRIANGLE  = 0
LFO_WAVE_SINE      = 25
LFO_WAVE_SAW_DOWN  = 75
LFO_WAVE_S_AND_H   = 100
LFO_WAVE_SQUARE    = 127

CHORUS_OFF         = 0
CHORUS_MONO        = 25
CHORUS_P_STEREO    = 75
CHORUS_STEREO      = 100
CHORUS_STEREO_2    = 127

VOICE_PARAPHONIC   = 0
VOICE_POLYPHONIC   = 25
VOICE_MONOPHONIC   = 75
VOICE_LEGATO       = 100
VOICE_LEGATO_PORTA = 127

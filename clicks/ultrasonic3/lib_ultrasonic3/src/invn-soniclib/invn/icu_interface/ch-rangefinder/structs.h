#ifndef _ICU_ALGO_RANGEFINDER_INTERFACE_H_
#define _ICU_ALGO_RANGEFINDER_INTERFACE_H_

#include <invn/icu_interface/shasta_iq_format.h>

#define EVENT_TYPE_RANGEFINDER_DETECTED_MASK (1<<0)
#define RINGDOWN_CANCEL_SAMPLES_MAX 60

#define GPT_IQ_SAMPLES_MAX 340

typedef struct target {
    volatile uint16_t range; //the range to the target, in ticks. The tick frequency is the frequency of the PMUT3M clock * (2^ODR-4)
    volatile uint16_t amplitude; //the amplitude in lsbs (CORDIC calculated, with a gain of 0.82 re: sqrt(I^2+Q^2)
    volatile uint16_t reserved[2]; //future use, e.g. velocity or stationary status or some modulated data associated with the pulse
}target_t;

#define MAXTARG (5U)
typedef struct target_list{
    volatile uint8_t num_valid_targets; //number of valid targets
    volatile uint8_t reserved; //bitmask: last bit used for target_in_ringdown detection
    volatile target_t targets[MAXTARG];
}target_list_t;

typedef struct{
    volatile target_list_t tL; //a list of targets
    volatile uint8_t event;                   /*!< Event detection. Binary value: 0-> no interrup, 1->interrupt.*/
    volatile uint8_t mask;                    /*!< Event type */
}InvnAlgoRangeFinderOutput;

#define LEN_THRESH 8
typedef struct thresholds{
    uint16_t stop_index[LEN_THRESH]; //for a threshold[i], when stop_index[i] sample is reached, switch to the next threshold[i+1]
    uint16_t threshold[LEN_THRESH]; //the threshold for detection. Cordic_mag(I,Q) must exceed this level for the 1st target to be detected.
    // Thereafter, subsequent targets must be above the threshold and 1/4 of the previous target amplitude.
}thresholds_t;

typedef struct{
    volatile uint16_t ringdown_cancel_samples; //cancel up to this many ringdown samples
    volatile uint16_t static_target_samples; //apply the static target rejection algorithm for this many samples
    volatile thresholds_t thresholds; //0x84 the thresholds for detection
    volatile uint8_t num_ranges; // 0x83 ask the rangefinder to calculate up to this many ranges
    volatile uint8_t iq_output_format; //0=normal (Q,I) pairs; 1=mag,threshold pairs, 2=mag,phase pairs
    volatile uint8_t filter_update_modulo; //update the ringdown and STR filters every N+1 samples (0 = every time, 1=every other time, etc)
    volatile uint8_t reserved; //padding
}InvnAlgoRangeFinderMeasConfig;

typedef struct
{
    InvnAlgoRangeFinderMeasConfig meas_cfg[MEAS_QUEUE_MAX_MEAS];
}InvnAlgoRangeFinderConfig;

#endif

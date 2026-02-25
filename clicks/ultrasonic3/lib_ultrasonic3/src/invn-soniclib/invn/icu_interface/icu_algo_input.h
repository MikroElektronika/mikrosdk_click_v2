//
// Created by rprzybyla on 9/21/2021.
//

#ifndef SHASTA_GPT_ICU_ALGO_INPUT_H
#define SHASTA_GPT_ICU_ALGO_INPUT_H
#include "shasta_iq_format.h"

typedef struct icu_algo_input{
    qi_t *QI;
    volatile uint16_t *num_iq_bytes;
    volatile uint16_t *start;
    volatile uint16_t *stop;
    volatile uint8_t *iq_output_format;
    volatile uint8_t *cur_meas;
}ICU_ALGO_SHASTA_INPUT;

#endif //SHASTA_GPT_ICU_ALGO_INPUT_H

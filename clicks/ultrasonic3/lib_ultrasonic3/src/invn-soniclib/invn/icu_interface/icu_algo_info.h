//
// Created by rprzybyla on 9/20/2021.
//

#ifndef SHASTA_GPT_ICU_ALGO_INFO_H
#define SHASTA_GPT_ICU_ALGO_INFO_H

#include <stdint.h>

typedef struct icu_algo_info{
    uint8_t algo_id;
    uint8_t algo_major_version;
    uint8_t algo_minor_version;
    uint8_t algo_patch_version;
    volatile uint16_t algo_cfg_ptr;
    uint16_t algo_cfg_len;
    volatile uint16_t algo_out_ptr;
    uint16_t algo_out_len;
    volatile uint16_t algo_state;
    uint16_t algo_state_len;
}ICU_ALGO_SHASTA_INFO;

#endif //SHASTA_GPT_ICU_ALGO_INFO_H

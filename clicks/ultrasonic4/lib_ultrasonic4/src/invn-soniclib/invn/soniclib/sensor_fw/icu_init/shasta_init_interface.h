//
// Created by rprzybyla on 9/8/2021.
//

#ifndef SHASTA_NONE_SHASTA_INIT_INTERFACE_H
#define SHASTA_NONE_SHASTA_INIT_INTERFACE_H

#include <invn/soniclib/sensor_fw/icu_init/icu_shasta_algo_structs.h>
#include "icu_algo_info.h"

typedef struct shasta_init{
    ICU_ALGO_SHASTA_OUTPUT algo_out;
    ICU_ALGO_SHASTA_CONFIG algo_cfg;
    ICU_ALGO_SHASTA_INFO algo_info;
} shasta_init_t;


#endif //SHASTA_NONE_SHASTA_INIT_INTERFACE_H

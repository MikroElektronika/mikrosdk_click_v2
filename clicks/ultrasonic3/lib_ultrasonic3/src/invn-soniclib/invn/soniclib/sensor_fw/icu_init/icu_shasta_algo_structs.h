//
// Created by rprzybyla on 8/25/2021.
//

#ifndef SHASTA_NONE_ICU_SHASTA_ALGO_STRUCTS_H
#define SHASTA_NONE_ICU_SHASTA_ALGO_STRUCTS_H

#include <stdint.h>
#define ICU_SHASTA_ALGO_VERSION_X 1 //this should be updated whenever ICU_ALGO_SHASTA_CONFIG or ICU_ALGO_SHASTA_OUTPUT change format
#define ICU_SHASTA_ALGO_VERSION_Y 0
#define ICU_SHASTA_ALGO_VERSION_Z 0
#define ICU_SHASTA_ALGO_VERSION_W 0
#define ICU_SHASTA_ALGO_ID 0

typedef struct shasta_init_out{
    uint8_t event;                   /*!< Event detection. Binary value: 0-> no interrup, 1->interrupt.*/
    uint8_t mask;                    /*!< Event type */
}shasta_init_out_t;

typedef uint16_t ICU_ALGO_SHASTA_STATE;
typedef uint16_t ICU_ALGO_SHASTA_CONFIG;
typedef shasta_init_out_t ICU_ALGO_SHASTA_OUTPUT;

#endif //SHASTA_NONE_ICU_SHASTA_ALGO_STRUCTS_H

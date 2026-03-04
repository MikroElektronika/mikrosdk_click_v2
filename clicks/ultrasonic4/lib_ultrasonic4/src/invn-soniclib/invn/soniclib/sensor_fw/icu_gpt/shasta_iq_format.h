//
// Created by rprzybyla on 8/24/2021.
//

#ifndef SHASTA_GPT_SHASTA_MEMORY_H
#define SHASTA_GPT_SHASTA_MEMORY_H
#include <stdint.h>

typedef struct qi_data {  // as in Whitney, data is packed with q first. Unlike Whitney, IQ data cannot overflow.
	                      // Theoretical abs maximum is about 25klsbs
	int16_t q;
	int16_t i;
} qi_t;

#define IQ_SAMPLES_MAX       356  // 5.1m at 95kHz and ODR=4
#define MEAS_QUEUE_MAX_MEAS  (2)
#define IQ_OUTPUT_NORMAL     (0)  // normal qi_t (Q,I) pairs
#define IQ_OUTPUT_MAG_THRESH (1)  // magnitude,threshold pairs
#define IQ_OUTPUT_MAG        (2)  // uint16_t magnitude, half length of normal trace

#endif  // SHASTA_GPT_SHASTA_MEMORY_H

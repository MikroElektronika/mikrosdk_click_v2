//
// Created by rprzybyla on 1/12/2021.
//

#ifndef SHASTA_TEST_SHASTA_PMUT_INSTRUCTION_H
#define SHASTA_TEST_SHASTA_PMUT_INSTRUCTION_H

typedef struct pmut_instruction {
   volatile uint16_t cmd_config;
   volatile uint16_t length;
} pmut_transceiver_inst_t;

#endif //SHASTA_TEST_SHASTA_PMUT_INSTRUCTION_H

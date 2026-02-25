//
// Created by rprzybyla on 5/7/2020.
//
#include "stdint.h"
#include "shasta_pmut_instruction.h"

#ifndef PROJECT_SHASTA_PMUT_CMDS_H
#define PROJECT_SHASTA_PMUT_CMDS_H

#define PMUT_CMD_BITSHIFT       (0)
#define PMUT_CMD_BITS           (0x0003)
#define PMUT_CMD_COUNT          (0)
#define PMUT_CMD_TX             (1)
#define PMUT_CMD_RX             (2)
#define PMUT_CMD_EOF            (3)
#define PMUT_RDY_IEN_BITS       (0x0004)
#define PMUT_DONE_IEN_BITS      (0x0008)
#define PMUT_RX_RESET_BITS      (0x0010)
#define PMUT_RX_BIAS_EN_BITS    (0x0020)
//Transmit specific
#define PMUT_TX_PHASE_BITSHIFT  (12)
#define PMUT_TX_PHASE_BM        (0x0f)
#define PMUT_TX_PW_BM           (0x07)
#define PMUT_TX_PW_BITSHIFT     (8)
//Receive specific
#define PMUT_RXGAIN_RED_BITSHIFT    (8)
#define PMUT_RXGAIN_BM              (0x1f)
#define PMUT_RXATTEN_BITSHIFT       (13)
#define PMUT_RXATTEN_BM             (0x03)
#define PMUT_BE_FLOAT_BM            (0x01)
#define PMUT_BE_FLOAT_BITSHIFT      (6)
#define PMUT_TEST_SIGNAL_EN_BITSHIFT         (7)


#define MAKE_PMUT_RX_CMD(RXGAIN, RXATTEN, CFG_BITS) \
    (PMUT_CMD_RX | CFG_BITS \
     | (RXGAIN << PMUT_RXGAIN_RED_BITSHIFT) \
     | (RXATTEN << PMUT_RXATTEN_BITSHIFT))

void construct_tx_cmd(pmut_transceiver_inst_t * inst, uint8_t pulsewidth, uint8_t txphase, uint16_t length);
void construct_rx_cmd(pmut_transceiver_inst_t * inst, uint8_t gain_reduction, uint8_t atten, uint8_t befloat, uint16_t length);
void construct_delay_cmd(pmut_transceiver_inst_t * inst, uint16_t length);
void construct_eof_cmd(pmut_transceiver_inst_t * inst);
void enable_done_interrupt_cmd(pmut_transceiver_inst_t * inst);
void enable_ready_interrupt_cmd(pmut_transceiver_inst_t * inst);

#endif //PROJECT_SHASTA_PMUT_CMDS_H

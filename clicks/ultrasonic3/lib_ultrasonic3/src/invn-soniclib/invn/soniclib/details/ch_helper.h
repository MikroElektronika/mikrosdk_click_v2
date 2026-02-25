/*! \file ch_helper.h
 *
 * \brief Internal helper functions for operation with the Chirp ultrasonic sensor.
 *
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#ifndef CH_HELPER_H_
#define CH_HELPER_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef INCLUDE_SHASTA_SUPPORT
#include "invn/icu_interface/shasta_pmut_cmds.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef INCLUDE_SHASTA_SUPPORT

#define GET_INSTRUCTION_CMD_TYPE(inst) ((inst.cmd_config) & PMUT_CMD_BITS)
#define IS_INSTRUCTION_CMD_RX(cmd)     (((cmd)&PMUT_CMD_BITS) == PMUT_CMD_RX)
#define IS_INSTRUCTION_CMD_TX(cmd)     (((cmd)&PMUT_CMD_BITS) == PMUT_CMD_TX)
#define IS_INSTRUCTION_CMD_EOF(cmd)    (((cmd)&PMUT_CMD_BITS) == PMUT_CMD_EOF)

#endif

#ifdef __cplusplus
}
#endif

#endif /* CH_HELPER_H_ */

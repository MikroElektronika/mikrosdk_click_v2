/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/
/*!
 * @file  spi_specifics.h
 * @brief This file contains SPI specific macros, functions, etc.
 */

#ifndef _SPI_SPECIFICS_
#define _SPI_SPECIFICS_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_definitions.h"

// mikroE toolchain specific
#if defined(__MIKROC_AI_FOR_PIC__) || defined(__MIKROC_AI_FOR_DSPIC__) || \
    defined(__MIKROC_AI_FOR_PIC32__)

#ifdef __MIKROC_AI_FOR_PIC__
    #define BIT_INDEX 7
#elif defined(__MIKROC_AI_FOR_PIC32__)
    #define BIT_INDEX 9
#elif defined(__MIKROC_AI_FOR_DSPIC__)
    #ifdef HAL_LL_SPI1_CONTROL_REG_ADDRESS
    #define BIT_INDEX 9
    #else
    #define BIT_INDEX 7
    #endif
#endif

#ifdef SAMPLE_REG_CASE_1
    #ifdef __MIKROC_AI_FOR_PIC32__
        #define SAMPLE_REG_ADDRESS(index) HAL_LL_SPI ## index ## CON_ADDRESS
    #elif defined (__MIKROC_AI_FOR_PIC__)
        #define SAMPLE_REG_ADDRESS(index) HAL_LL_SPI ## index ## CON1_ADDRESS
    #else
        #define SAMPLE_REG_ADDRESS(index) HAL_LL_SPI ## index ## _CONTROL_REG_ADDRESS
    #endif
#else
    #define SAMPLE_REG_ADDRESS(index) HAL_LL_SSP ## index ## STAT_ADDRESS
#endif

#if defined(SPI_MODULE) || defined(SPI_MODULE_1)
    #define SET_SPI_DATA_SAMPLE_MIDDLE1 clear_reg_bit(SAMPLE_REG_ADDRESS(1), BIT_INDEX);
    #define SET_SPI_DATA_SAMPLE_EDGE1   set_reg_bit(SAMPLE_REG_ADDRESS(1), BIT_INDEX);
#else
    #define SET_SPI_DATA_SAMPLE_MIDDLE1
    #define SET_SPI_DATA_SAMPLE_EDGE1
#endif

#ifdef SPI_MODULE_2
    #define SET_SPI_DATA_SAMPLE_MIDDLE2 clear_reg_bit(SAMPLE_REG_ADDRESS(2), BIT_INDEX);
    #define SET_SPI_DATA_SAMPLE_EDGE2   set_reg_bit(SAMPLE_REG_ADDRESS(2), BIT_INDEX);
#else
    #define SET_SPI_DATA_SAMPLE_MIDDLE2
    #define SET_SPI_DATA_SAMPLE_EDGE2
#endif

#ifdef SPI_MODULE_3
    #define SET_SPI_DATA_SAMPLE_MIDDLE3 clear_reg_bit(SAMPLE_REG_ADDRESS(3), BIT_INDEX);
    #define SET_SPI_DATA_SAMPLE_EDGE3   set_reg_bit(SAMPLE_REG_ADDRESS(3), BIT_INDEX);
#else
    #define SET_SPI_DATA_SAMPLE_MIDDLE3
    #define SET_SPI_DATA_SAMPLE_EDGE3
#endif

#ifdef SPI_MODULE_4
    #define SET_SPI_DATA_SAMPLE_MIDDLE4 clear_reg_bit(SAMPLE_REG_ADDRESS(4), BIT_INDEX);
    #define SET_SPI_DATA_SAMPLE_EDGE4   set_reg_bit(SAMPLE_REG_ADDRESS(4), BIT_INDEX);
#else
    #define SET_SPI_DATA_SAMPLE_MIDDLE4
    #define SET_SPI_DATA_SAMPLE_EDGE4
#endif

#ifdef SPI_MODULE_5
    #define SET_SPI_DATA_SAMPLE_MIDDLE5 clear_reg_bit(SAMPLE_REG_ADDRESS(5), BIT_INDEX);
    #define SET_SPI_DATA_SAMPLE_EDGE5   set_reg_bit(SAMPLE_REG_ADDRESS(5), BIT_INDEX);
#else
    #define SET_SPI_DATA_SAMPLE_MIDDLE5
    #define SET_SPI_DATA_SAMPLE_EDGE5
#endif

#ifdef SPI_MODULE_6
    #define SET_SPI_DATA_SAMPLE_MIDDLE6 clear_reg_bit(SAMPLE_REG_ADDRESS(6), BIT_INDEX);
    #define SET_SPI_DATA_SAMPLE_EDGE6   set_reg_bit(SAMPLE_REG_ADDRESS(6), BIT_INDEX);
#else
    #define SET_SPI_DATA_SAMPLE_MIDDLE6
    #define SET_SPI_DATA_SAMPLE_EDGE6
#endif


#define SET_SPI_DATA_SAMPLE_MIDDLE SET_SPI_DATA_SAMPLE_MIDDLE1 SET_SPI_DATA_SAMPLE_MIDDLE2 \
                                   SET_SPI_DATA_SAMPLE_MIDDLE3 SET_SPI_DATA_SAMPLE_MIDDLE4 \
                                   SET_SPI_DATA_SAMPLE_MIDDLE5 SET_SPI_DATA_SAMPLE_MIDDLE6
#define SET_SPI_DATA_SAMPLE_EDGE   SET_SPI_DATA_SAMPLE_EDGE1 SET_SPI_DATA_SAMPLE_EDGE2 \
                                   SET_SPI_DATA_SAMPLE_EDGE3 SET_SPI_DATA_SAMPLE_EDGE4 \
                                   SET_SPI_DATA_SAMPLE_EDGE5 SET_SPI_DATA_SAMPLE_EDGE6
#else
    #define SET_SPI_DATA_SAMPLE_MIDDLE
    #define SET_SPI_DATA_SAMPLE_EDGE
#endif

#ifdef __cplusplus
}
#endif
#endif // _SPI_SPECIFICS_

// ------------------------------------------------------------------------ END

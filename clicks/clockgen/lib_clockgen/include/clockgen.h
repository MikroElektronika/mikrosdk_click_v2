/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Clock Gen Click driver.
 *
 * \addtogroup clockgen Clock Gen Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CLOCKGEN_H
#define CLOCKGEN_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CLOCKGEN_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CLOCKGEN_RETVAL  uint8_t

#define CLOCKGEN_OK           0x00
#define CLOCKGEN_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define CLOCKGEN_SLAVE_ADDRESS                                     0x60
/** \} */

/**
 * \defgroup ctrl_regs CTRL Registers
 * \{
 */
#define CLOCKGEN_REG_DEV_STATUS                                    0
#define CLOCKGEN_REG_INT_STATUS_STICKY                             1
#define CLOCKGEN_REG_INT_STATUS_MASK                               2
#define CLOCKGEN_REG_OUTPUT_ENABLE_CTRL                            3
#define CLOCKGEN_REG_OEB_EN_CTRL_MASK                              9
#define CLOCKGEN_REG_PLL_IN_SRC                                    15
#define CLOCKGEN_REG_CLK0_CTRL                                     16
#define CLOCKGEN_REG_CLK1_CTRL                                     17
#define CLOCKGEN_REG_CLK2_CTRL                                     18
#define CLOCKGEN_REG_CLK3_CTRL                                     19
#define CLOCKGEN_REG_CLK4_CTRL                                     20
#define CLOCKGEN_REG_CLK5_CTRL                                     21
#define CLOCKGEN_REG_CLK6_CTRL                                     22
#define CLOCKGEN_REG_CLK7_CTRL                                     23
#define CLOCKGEN_REG_CLK3_0_DIS_STATE                              24
#define CLOCKGEN_REG_CLK7_4_DIS_STATE                              25
/** \} */

/**
 * \defgroup multyisynth_na MULTYISYNTH NA
 * \{
 */
#define CLOCKGEN_REG_MULTI_NA_PARAM3_B15_8                         26
#define CLOCKGEN_REG_MULTI_NA_PARAM3_B7_0                          27
#define CLOCKGEN_REG_MULTI_NA_PARAM1_B17_16                        28
#define CLOCKGEN_REG_MULTI_NA_PARAM1_B15_8                         29
#define CLOCKGEN_REG_MULTI_NA_PARAM1_B7_0                          30
#define CLOCKGEN_REG_MULTI_NA_PARAM3_2_B19_16                      31
#define CLOCKGEN_REG_MULTI_NA_PARAM2_B15_8                         32
#define CLOCKGEN_REG_MULTI_NA_PARAM2_B7_0                          33
/** \} */

/**
 * \defgroup multyisynth_nb MULTYISYNTH NB
 * \{
 */
#define CLOCKGEN_REG_MULTI_NB_PARAM3_B15_8                         34
#define CLOCKGEN_REG_MULTI_NB_PARAM3_B7_0                          35
#define CLOCKGEN_REG_MULTI_NB_PARAM1_B17_16                        36
#define CLOCKGEN_REG_MULTI_NB_PARAM1_B15_8                         37
#define CLOCKGEN_REG_MULTI_NB_PARAM1_B7_0                          38
#define CLOCKGEN_REG_MULTI_NB_PARAM3_2_B19_16                      39
#define CLOCKGEN_REG_MULTI_NB_PARAM2_B15_8                         40
#define CLOCKGEN_REG_MULTI_NB_PARAM2_B7_0                          41
/** \} */

/**
 * \defgroup multyisynth_0 MULTYISYNTH 0
 * \{
 */
#define CLOCKGEN_REG_MULTI_0_PARAM3_B15_8                          42
#define CLOCKGEN_REG_MULTI_0_PARAM3_B7_0                           43
#define CLOCKGEN_REG_MULTI_0_PARAM1_B17_16_DIVS                    44
#define CLOCKGEN_REG_MULTI_0_PARAM1_B15_8                          45
#define CLOCKGEN_REG_MULTI_0_PARAM1_B7_0                           46
#define CLOCKGEN_REG_MULTI_0_PARAM3_2_B19_16                       47
#define CLOCKGEN_REG_MULTI_0_PARAM2_B15_8                          48
#define CLOCKGEN_REG_MULTI_0_PARAM2_B7_0                           49
/** \} */

/**
 * \defgroup multyisynth_1 MULTYISYNTH 1
 * \{
 */
#define CLOCKGEN_REG_MULTI_1_PARAM3_B15_8                          50
#define CLOCKGEN_REG_MULTI_1_PARAM3_B7_0                           51
#define CLOCKGEN_REG_MULTI_1_PARAM1_B17_16_DIVS                    52
#define CLOCKGEN_REG_MULTI_1_PARAM1_B15_8                          53
#define CLOCKGEN_REG_MULTI_1_PARAM1_B7_0                           54
#define CLOCKGEN_REG_MULTI_1_PARAM3_2_B19_16                       55
#define CLOCKGEN_REG_MULTI_1_PARAM2_B15_8                          56
#define CLOCKGEN_REG_MULTI_1_PARAM2_B7_0                           57
/** \} */

/**
 * \defgroup multyisynth_2 MULTYISYNTH 2
 * \{
 */
#define CLOCKGEN_REG_MULTI_2_PARAM3_B15_8                          58
#define CLOCKGEN_REG_MULTI_2_PARAM3_B7_0                           59
#define CLOCKGEN_REG_MULTI_2_PARAM1_B17_16_DIVS                    60
#define CLOCKGEN_REG_MULTI_2_PARAM1_B15_8                          61
#define CLOCKGEN_REG_MULTI_2_PARAM1_B7_0                           62
#define CLOCKGEN_REG_MULTI_2_PARAM3_2_B19_16                       63
#define CLOCKGEN_REG_MULTI_2_PARAM2_B15_8                          64
#define CLOCKGEN_REG_MULTI_2_PARAM2_B7_0                           65
/** \} */

/**
 * \defgroup multyisynth_3 MULTYISYNTH 3
 * \{
 */
#define CLOCKGEN_REG_MULTI_3_PARAM3_B15_8                          66
#define CLOCKGEN_REG_MULTI_3_PARAM3_B7_0                           67
#define CLOCKGEN_REG_MULTI_3_PARAM1_B17_16_DIVS                    68
#define CLOCKGEN_REG_MULTI_3_PARAM1_B15_8                          69
#define CLOCKGEN_REG_MULTI_3_PARAM1_B7_0                           70
#define CLOCKGEN_REG_MULTI_3_PARAM3_2_B19_16                       71
#define CLOCKGEN_REG_MULTI_3_PARAM2_B15_8                          72
#define CLOCKGEN_REG_MULTI_3_PARAM2_B7_0                           73
/** \} */

/**
 * \defgroup multyisynth_4 MULTYISYNTH 4
 * \{
 */
#define CLOCKGEN_REG_MULTI_4_PARAM3_B15_8                          74
#define CLOCKGEN_REG_MULTI_4_PARAM3_B7_0                           75
#define CLOCKGEN_REG_MULTI_4_PARAM1_B17_16_DIVS                    76
#define CLOCKGEN_REG_MULTI_4_PARAM1_B15_8                          77
#define CLOCKGEN_REG_MULTI_4_PARAM1_B7_0                           78
#define CLOCKGEN_REG_MULTI_4_PARAM3_2_B19_16                       79
#define CLOCKGEN_REG_MULTI_4_PARAM2_B15_8                          80
#define CLOCKGEN_REG_MULTI_4_PARAM2_B7_0                           81
/** \} */

/**
 * \defgroup multyisynth_5 MULTYISYNTH 5
 * \{
 */
#define CLOCKGEN_REG_MULTI_5_PARAM3_B15_8                          82
#define CLOCKGEN_REG_MULTI_5_PARAM3_B7_0                           83
#define CLOCKGEN_REG_MULTI_5_PARAM1_B17_16_DIVS                    84
#define CLOCKGEN_REG_MULTI_5_PARAM1_B15_8                          85
#define CLOCKGEN_REG_MULTI_5_PARAM1_B7_0                           86
#define CLOCKGEN_REG_MULTI_5_PARAM3_2_B19_16                       87
#define CLOCKGEN_REG_MULTI_5_PARAM2_B15_8                          88
#define CLOCKGEN_REG_MULTI_5_PARAM2_B7_0                           89
/** \} */

/**
 * \defgroup multyisynth_6 MULTYISYNTH 6
 * \{
 */
#define CLOCKGEN_REG_MULTI_6_PARAM3_B15_8                          90
#define CLOCKGEN_REG_MULTI_6_PARAM3_B7_0                           91
#define CLOCKGEN_REG_MULTI_6_PARAM1_B17_16_DIVS                    92
#define CLOCKGEN_REG_MULTI_6_PARAM1_B15_8                          93
#define CLOCKGEN_REG_MULTI_6_PARAM1_B7_0                           94
#define CLOCKGEN_REG_MULTI_6_PARAM3_2_B19_16                       95
#define CLOCKGEN_REG_MULTI_6_PARAM2_B15_8                          96
#define CLOCKGEN_REG_MULTI_6_PARAM2_B7_0                           97
/** \} */

/**
 * \defgroup multyisynth_7 MULTYISYNTH 7
 * \{
 */
#define CLOCKGEN_REG_MULTI_7_PARAM3_B15_8                          98
#define CLOCKGEN_REG_MULTI_7_PARAM3_B7_0                           99
#define CLOCKGEN_REG_MULTI_7_PARAM1_B17_16_DIVS                    100
#define CLOCKGEN_REG_MULTI_7_PARAM1_B15_8                          101
#define CLOCKGEN_REG_MULTI_7_PARAM1_B7_0                           102
#define CLOCKGEN_REG_MULTI_7_PARAM3_2_B19_16                       103
#define CLOCKGEN_REG_MULTI_7_PARAM2_B15_8                          104
#define CLOCKGEN_REG_MULTI_7_PARAM2_B7_0                           105
/** \} */

/**
 * \defgroup spread_spectrum SPREAD SPECTRUM
 * \{
 */
#define CLOCKGEN_REG_SPREAD_SPECTRUM_DOWN_PARAM2_EN_B14_8          149
#define CLOCKGEN_REG_SPREAD_SPECTRUM_DOWN_PARAM2_B7_0              150
#define CLOCKGEN_REG_SPREAD_SPECTRUM_DOWN_PARAM3_MODE_B14_8        151
#define CLOCKGEN_REG_SPREAD_SPECTRUM_DOWN_PARAM3_B7_0              152
#define CLOCKGEN_REG_SPREAD_SPECTRUM_DOWN_PARAM1_B7_0              153
#define CLOCKGEN_REG_SPREAD_SPECTRUM_DOWN_PARAM3_B11_8_UP_DWN      154
#define CLOCKGEN_REG_SPREAD_SPECTRUM_UP_DOWN_PLL_A                 155
#define CLOCKGEN_REG_SPREAD_SPECTRUM_UP_PARAM2_B14_8               156
#define CLOCKGEN_REG_SPREAD_SPECTRUM_UP_PARAM2_B7_0                157
#define CLOCKGEN_REG_SPREAD_SPECTRUM_UP_PARAM3_B14_8               158
#define CLOCKGEN_REG_SPREAD_SPECTRUM_UP_PARAM3_B7_0                159
#define CLOCKGEN_REG_SPREAD_SPECTRUM_UP_PARAM1_B7_0                160
#define CLOCKGEN_REG_SPREAD_SPECTRUM_UP_PARAM1_B11_8               161
/** \} */

/**
 * \defgroup vcxo_param VCXO PARAM
 * \{
 */
#define CLOCKGEN_REG_VCXO_PARAM_B7_0                               162
#define CLOCKGEN_REG_VCXO_PARAM_B15_8                              163
#define CLOCKGEN_REG_VCXO_PARAM_B21_16                             164
/** \} */

/**
 * \defgroup init_offset INIT OFFSET
 * \{
 */
#define CLOCKGEN_REG_CLK0_INIT_OFFSET                              165
#define CLOCKGEN_REG_CLK1_INIT_OFFSET                              166
#define CLOCKGEN_REG_CLK2_INIT_OFFSET                              167
/** \} */

/**
 * \defgroup pll PLL
 * \{
 */
#define CLOCKGEN_REG_PLL_RST                                       177
#define CLOCKGEN_REG_CRYSTAL_INTERNAL_CL                           183
#define CLOCKGEN_REG_FANOUT_EN                                     187
/** \} */

/**
 * \defgroup clock_enum Clock Enumeration
 * \{
 */
#define CLOCKGEN_CLOCK_0                                           0
#define CLOCKGEN_CLOCK_1                                           1
#define CLOCKGEN_CLOCK_2                                           2
#define CLOCKGEN_CLOCK_3                                           3
#define CLOCKGEN_CLOCK_4                                           4
#define CLOCKGEN_CLOCK_5                                           5
#define CLOCKGEN_CLOCK_6                                           6
#define CLOCKGEN_CLOCK_7                                           7
#define CLOCKGEN_DISABLE_ALL_CLK                                   8
/** \} */

/**
 * \defgroup pll_params PLL Params
 * \{
 */
#define CLOCKGEN_CLK_CTRL                                          16

#define CLOCKGEN_PLLA                                              0xFF
#define CLOCKGEN_PLLB                                              0xDF

#define CLOCKGEN_RESET_PLLA                                        0x20
#define CLOCKGEN_RESET_PLLB                                        0x80

#define CLOCKGEN_PLL_PARAMS                                        0xFA
#define CLOCKGEN_CLK_PARAMS                                        0xFB

#define CLOCKGEN_PARAM_DIV_4_EN                                    0x3
#define CLOCKGEN_PARAM_DIV_OTHER                                   0x0
/** \} */

/**
 * \defgroup param_div Param Divider
 * \{
 */
#define CLOCKGEN_PARAM_DIV_1                                       0x0
#define CLOCKGEN_PARAM_DIV_2                                       0x1
#define CLOCKGEN_PARAM_DIV_4                                       0x2
#define CLOCKGEN_PARAM_DIV_8                                       0x3
#define CLOCKGEN_PARAM_DIV_16                                      0x4
#define CLOCKGEN_PARAM_DIV_32                                      0x5
#define CLOCKGEN_PARAM_DIV_64                                      0x6
#define CLOCKGEN_PARAM_DIV_128                                     0x7
/** \} */

/**
 * \defgroup pll_input PLL Input
 * \{
 */
#define CLOCKGEN_PLL_INPUT_XO                                      0
#define CLOCKGEN_PLL_INPUT_CLKIN                                   1

#define CLOCKGEN_FREQ_MULTY                                        100
/** \} */

/**
 * \defgroup dis_state DIS State
 * \{
 */
#define CLOCKGEN_DIS_STATE_LOW                                     0
#define CLOCKGEN_DIS_STATE_HIGH                                    1
#define CLOCKGEN_DIS_STATE_HIGH_IMP                                2
#define CLOCKGEN_DIS_STATE_NEVER_DIS                               3
/** \} */

/**
 * \defgroup other_macros Other Macros
 * \{
 */
#define CLOCKGEN_PARAMS_MACRO                                      8
#define CLOCKGEN                                                   0
#define CLOCKGEN_DISIABLE_STATE_SHIFT                              2

#define CLOCKGEN_XTAL                                              25000000
#define CLOCKGEN_MAX_FREQ                                          CLOCKGEN_XTAL * 32
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    // Aditional variable 

    uint32_t denom;
    uint8_t factor;

} clockgen_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} clockgen_cfg_t;

/**
 * @brief Structure for setting clock parameters
 */
typedef struct 
{
   uint32_t p1;
   uint32_t p2;
   uint32_t p3;
   uint8_t div4;
   uint8_t div_val;

} clockgen_params_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void clockgen_cfg_setup ( clockgen_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CLOCKGEN_RETVAL clockgen_init ( clockgen_t *ctx, clockgen_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for ClockGen click.
 */
void clockgen_default_cfg ( clockgen_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void clockgen_generic_write ( clockgen_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void clockgen_generic_read ( clockgen_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function enabling specific clock 
 * 
 * @param ctx               Click object. 
 * @param clk_num           Clock number.
 *
 * @description This function enable specific clock.
 */
void clockgen_enable_clk ( clockgen_t *ctx, uint8_t clk_num );

/**
 * @brief Function enabling specific clock 
 * 
 * @param ctx               Click object.  
 * @param clk_num           Clock number.
 * @param ctrl_data         Data to set on clk_num.
 *
 * @description This function enable clock with specific clock number.
 */
void clockgen_ctrl_clk ( clockgen_t *ctx, uint8_t clk_num, uint8_t ctrl_data );

/**
 * @brief Function for setting clock disabling state
 * 
 * @param ctx               Click object.  
 * @param clk_num           Clock number.
 * @param disable_state     Disable state of the clock.
 *
 * @description This function disable clock state.
 */
void clockgen_set_disable_state ( clockgen_t *ctx, uint8_t clk_num, uint8_t disable_state );

/**
 * @brief Function for setting clock pll-s 
 * 
 * @param ctx               Click object.  
 * @param clk_num           Clock number.
 * @param pll_sel           Pll.
 *
 * @description This function sets clock pll.
 */
void clockgen_set_clk_pll ( clockgen_t *ctx, uint8_t clk_num, uint8_t pll_sel );

/**
 * @brief Function for setting clock pll-s 
 * 
 * @param ctx               Click object.  
 * @param clk_pll_num       Clock or pll.
 * @param param_group       Structure for setting parameters.
 *
 * @description This function sets clock pll with parameter structure.
 */
void clockgen_set_params ( clockgen_t *ctx, uint8_t clk_pll_num, clockgen_params_t *param_group );

/**
 * @brief Function for getting clock pll-s 
 * 
 * @param ctx               Click object.  
 * @param clk_pll_num       Clock or pll.
 * @param param_group       Structure for getting parameters.
 *
 * @description This function gets clock pll.
 */
void clockgen_get_params ( clockgen_t *ctx, uint8_t clk_pll_num, clockgen_params_t *param_group );

/**
 * @brief Function for setting clock frequency on specific clock
 * 
 * @param ctx               Click object.  
 * @param clk_num           Clock number.
 * @param pll_num           Pll number.
 * @param freq              Frequency to be set in MHz.
 *
 * @description This function sets clock frequency on specific clock.
 */
void clockgen_set_frequency ( clockgen_t *ctx, uint8_t clk_num, uint8_t pll_num, uint32_t freq );

/**
 * @brief Function for setting pll
 *
 * @param ctx               Click object.  
 * @param clk_num           Clock number.
 * @param mult              Multiplier value.
 * @param num               Nominator value.
 *
 * @description This function sets pll.
 * @note @param denom             Denominator value.
 */
void clockgen_setup_pll ( clockgen_t *ctx, uint8_t pll, uint8_t mult, uint32_t num );

/**
 * @brief Function for setting clock divider
 *
 * @param ctx               Click object.  
 * @param clk_num           Clock number.
 * @param divider           Divider value.
 * @param num               Nominator value.
 *
 * @description This function sets clock divider
 * @note
 * @param denom             Denominator value.
 * @param factor            R divider.
 */
void clockgen_setup_multisyinth ( clockgen_t *ctx, uint8_t clk_num, uint32_t divider, uint32_t num );

#ifdef __cplusplus
}
#endif
#endif  // _CLOCKGEN_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

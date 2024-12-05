/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file hwmonitor3.h
 * @brief This file contains API for HW Monitor 3 Click Driver.
 */

#ifndef HWMONITOR3_H
#define HWMONITOR3_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup hwmonitor3 HW Monitor 3 Click Driver
 * @brief API for configuring and manipulating HW Monitor 3 Click driver.
 * @{
 */

/**
 * @defgroup hwmonitor3_reg HW Monitor 3 Registers List
 * @brief List of registers of HW Monitor 3 Click driver.
 */

/**
 * @addtogroup hwmonitor3_reg
 * @{
 */

/**
 * @brief HW Monitor 3 registers list bank 0 register.
 * @details Specified register for registers list bank 0 of HW Monitor 3 Click driver.
 */
#define HWMONITOR3_REG_INT_SRC                  0x10
#define HWMONITOR3_REG_INT_MONITOR              0x11
#define HWMONITOR3_REG_INT_UVHF                 0x12
#define HWMONITOR3_REG_INT_UVLF                 0x14
#define HWMONITOR3_REG_INT_OVHF                 0x16
#define HWMONITOR3_REG_INT_OVLF                 0x18
#define HWMONITOR3_REG_INT_SEQ_ON               0x1A
#define HWMONITOR3_REG_INT_SEQ_OFF              0x1C
#define HWMONITOR3_REG_INT_SEQ_EXS              0x1E
#define HWMONITOR3_REG_INT_SEQ_ENS              0x20
#define HWMONITOR3_REG_INT_CONTROL              0x22
#define HWMONITOR3_REG_INT_TEST                 0x23
#define HWMONITOR3_REG_INT_VENDOR               0x24
#define HWMONITOR3_REG_VMON_STAT                0x30
#define HWMONITOR3_REG_TEST_INFO                0x31
#define HWMONITOR3_REG_OFF_STAT                 0x32
#define HWMONITOR3_REG_SEQ_REC_STAT             0x34
#define HWMONITOR3_REG_SEQ_OW_STAT              0x35
#define HWMONITOR3_REG_SEQ_ORD_STAT             0x36
#define HWMONITOR3_REG_MON_LVL_1                0x40
#define HWMONITOR3_REG_MON_LVL_2                0x41
#define HWMONITOR3_REG_MON_LVL_3                0x42
#define HWMONITOR3_REG_MON_LVL_4                0x43
#define HWMONITOR3_REG_MON_LVL_5                0x44
#define HWMONITOR3_REG_MON_LVL_6                0x45
#define HWMONITOR3_REG_SEQ_ON_LOG_1             0x50
#define HWMONITOR3_REG_SEQ_ON_LOG_2             0x51
#define HWMONITOR3_REG_SEQ_ON_LOG_3             0x52
#define HWMONITOR3_REG_SEQ_ON_LOG_4             0x53
#define HWMONITOR3_REG_SEQ_ON_LOG_5             0x54
#define HWMONITOR3_REG_SEQ_ON_LOG_6             0x55
#define HWMONITOR3_REG_SEQ_OFF_LOG_1            0x60
#define HWMONITOR3_REG_SEQ_OFF_LOG_2            0x61
#define HWMONITOR3_REG_SEQ_OFF_LOG_3            0x62
#define HWMONITOR3_REG_SEQ_OFF_LOG_4            0x63
#define HWMONITOR3_REG_SEQ_OFF_LOG_5            0x64
#define HWMONITOR3_REG_SEQ_OFF_LOG_6            0x65
#define HWMONITOR3_REG_SEQ_EXS_LOG_1            0x70
#define HWMONITOR3_REG_SEQ_EXS_LOG_2            0x71
#define HWMONITOR3_REG_SEQ_EXS_LOG_3            0x72
#define HWMONITOR3_REG_SEQ_EXS_LOG_4            0x73
#define HWMONITOR3_REG_SEQ_EXS_LOG_5            0x74
#define HWMONITOR3_REG_SEQ_EXS_LOG_6            0x75
#define HWMONITOR3_REG_SEQ_ENS_LOG_1            0x80
#define HWMONITOR3_REG_SEQ_ENS_LOG_2            0x81
#define HWMONITOR3_REG_SEQ_ENS_LOG_3            0x82
#define HWMONITOR3_REG_SEQ_ENS_LOG_4            0x83
#define HWMONITOR3_REG_SEQ_ENS_LOG_5            0x84
#define HWMONITOR3_REG_SEQ_ENS_LOG_6            0x85
#define HWMONITOR3_REG_SEQ_TIME_MSB_1           0x90
#define HWMONITOR3_REG_SEQ_TIME_LSB_1           0x91
#define HWMONITOR3_REG_SEQ_TIME_MSB_2           0x92
#define HWMONITOR3_REG_SEQ_TIME_LSB_2           0x93
#define HWMONITOR3_REG_SEQ_TIME_MSB_3           0x94
#define HWMONITOR3_REG_SEQ_TIME_LSB_3           0x95
#define HWMONITOR3_REG_SEQ_TIME_MSB_4           0x96
#define HWMONITOR3_REG_SEQ_TIME_LSB_4           0x97
#define HWMONITOR3_REG_SEQ_TIME_MSB_5           0x98
#define HWMONITOR3_REG_SEQ_TIME_LSB_5           0x99
#define HWMONITOR3_REG_SEQ_TIME_MSB_6           0x9A
#define HWMONITOR3_REG_SEQ_TIME_LSB_6           0x9B
#define HWMONITOR3_REG_BANK_SEL                 0xF0
#define HWMONITOR3_REG_PROT1                    0xF1
#define HWMONITOR3_REG_PROT2                    0xF2
#define HWMONITOR3_REG_PROT_MON2                0xF3
#define HWMONITOR3_REG_I2CADDR                  0xF9
#define HWMONITOR3_REG_DEV_CFG                  0xFA

/**
 * @brief HW Monitor 3 registers list bank 1 register.
 * @details Specified register for registers list bank 1 of HW Monitor 3 Click driver.
 */
#define HWMONITOR3_REG_VMON_CTL                 0x10
#define HWMONITOR3_REG_VMON_MISC                0x11
#define HWMONITOR3_REG_TEST_CFG                 0x12
#define HWMONITOR3_REG_IEN_UVHF                 0x13
#define HWMONITOR3_REG_IEN_UVLF                 0x14
#define HWMONITOR3_REG_IEN_OVHF                 0x15
#define HWMONITOR3_REG_IEN_OVLF                 0x16
#define HWMONITOR3_REG_IEN_SEQ_ON               0x17
#define HWMONITOR3_REG_IEN_SEQ_OFF              0x18
#define HWMONITOR3_REG_IEN_SEQ_EXS              0x19
#define HWMONITOR3_REG_IEN_SEQ_ENS              0x1A
#define HWMONITOR3_REG_IEN_CONTROL              0x1B
#define HWMONITOR3_REG_IEN_TEST                 0x1C
#define HWMONITOR3_REG_MON_CH_EN                0x1E
#define HWMONITOR3_REG_VRANGE_MULT              0x1F
#define HWMONITOR3_REG_UV_HF_1                  0x20
#define HWMONITOR3_REG_OV_HF_1                  0x21
#define HWMONITOR3_REG_UV_LF_1                  0x22
#define HWMONITOR3_REG_OV_LF_1                  0x23
#define HWMONITOR3_REG_FLT_HF_1                 0x24
#define HWMONITOR3_REG_FC_LF_1                  0x25
#define HWMONITOR3_REG_UV_HF_2                  0x30
#define HWMONITOR3_REG_OV_HF_2                  0x31
#define HWMONITOR3_REG_UV_LF_2                  0x32
#define HWMONITOR3_REG_OV_LF_2                  0x33
#define HWMONITOR3_REG_FLT_HF_2                 0x34
#define HWMONITOR3_REG_FC_LF_2                  0x35
#define HWMONITOR3_REG_UV_HF_3                  0x40
#define HWMONITOR3_REG_OV_HF_3                  0x41
#define HWMONITOR3_REG_UV_LF_3                  0x42
#define HWMONITOR3_REG_OV_LF_3                  0x43
#define HWMONITOR3_REG_FLT_HF_3                 0x44
#define HWMONITOR3_REG_FC_LF_3                  0x45
#define HWMONITOR3_REG_UV_HF_4                  0x50
#define HWMONITOR3_REG_OV_HF_4                  0x51
#define HWMONITOR3_REG_UV_LF_4                  0x52
#define HWMONITOR3_REG_OV_LF_4                  0x53
#define HWMONITOR3_REG_FLT_HF_4                 0x54
#define HWMONITOR3_REG_FC_LF_4                  0x55
#define HWMONITOR3_REG_UV_HF_5                  0x60
#define HWMONITOR3_REG_OV_HF_5                  0x61
#define HWMONITOR3_REG_UV_LF_5                  0x62
#define HWMONITOR3_REG_OV_LF_5                  0x63
#define HWMONITOR3_REG_FLT_HF_5                 0x64
#define HWMONITOR3_REG_FC_LF_5                  0x65
#define HWMONITOR3_REG_UV_HF_6                  0x70
#define HWMONITOR3_REG_OV_HF_6                  0x71
#define HWMONITOR3_REG_UV_LF_6                  0x72
#define HWMONITOR3_REG_OV_LF_6                  0x73
#define HWMONITOR3_REG_FLT_HF_6                 0x74
#define HWMONITOR3_REG_FC_LF_6                  0x75
#define HWMONITOR3_REG_TI_CONTROL               0x9F
#define HWMONITOR3_REG_SEQ_REC_CTL              0xA0
#define HWMONITOR3_REG_AMSK_ON                  0xA1
#define HWMONITOR3_REG_AMSK_OFF                 0xA2
#define HWMONITOR3_REG_AMSK_EXS                 0xA3
#define HWMONITOR3_REG_AMSK_ENS                 0xA4
#define HWMONITOR3_REG_SEQ_TOUT_MSB             0xA5
#define HWMONITOR3_REG_SEQ_TOUT_LSB             0xA6
#define HWMONITOR3_REG_SEQ_SYNC                 0xA7
#define HWMONITOR3_REG_SEQ_UP_THLD              0xA8
#define HWMONITOR3_REG_SEQ_DN_THLD              0xA9
#define HWMONITOR3_REG_SEQ_DN_THLD              0xA9
#define HWMONITOR3_REG_SEQ_ON_EXP_1             0xB0
#define HWMONITOR3_REG_SEQ_ON_EXP_2             0xB1
#define HWMONITOR3_REG_SEQ_ON_EXP_3             0xB2
#define HWMONITOR3_REG_SEQ_ON_EXP_4             0xB3
#define HWMONITOR3_REG_SEQ_ON_EXP_5             0xB4
#define HWMONITOR3_REG_SEQ_ON_EXP_6             0xB5
#define HWMONITOR3_REG_SEQ_OFF_EXP_1            0xC0
#define HWMONITOR3_REG_SEQ_OFF_EXP_2            0xC1
#define HWMONITOR3_REG_SEQ_OFF_EXP_3            0xC2
#define HWMONITOR3_REG_SEQ_OFF_EXP_4            0xC3
#define HWMONITOR3_REG_SEQ_OFF_EXP_5            0xC4
#define HWMONITOR3_REG_SEQ_OFF_EXP_6            0xC5
#define HWMONITOR3_REG_SEQ_EXS_EXP_1            0xD0
#define HWMONITOR3_REG_SEQ_EXS_EXP_2            0xD1
#define HWMONITOR3_REG_SEQ_EXS_EXP_3            0xD2
#define HWMONITOR3_REG_SEQ_EXS_EXP_4            0xD3
#define HWMONITOR3_REG_SEQ_EXS_EXP_5            0xD4
#define HWMONITOR3_REG_SEQ_EXS_EXP_6            0xD5
#define HWMONITOR3_REG_SEQ_ENS_EXP_1            0xE0
#define HWMONITOR3_REG_SEQ_ENS_EXP_2            0xE1
#define HWMONITOR3_REG_SEQ_ENS_EXP_3            0xE2
#define HWMONITOR3_REG_SEQ_ENS_EXP_4            0xE3
#define HWMONITOR3_REG_SEQ_ENS_EXP_5            0xE4
#define HWMONITOR3_REG_SEQ_ENS_EXP_6            0xE5

/*! @} */ // hwmonitor3_reg

/**
 * @defgroup hwmonitor3_set HW Monitor 3 Registers Settings
 * @brief Settings for registers of HW Monitor 3 Click driver.
 */

/**
 * @addtogroup hwmonitor3_set
 * @{
 */

/**
 * @brief HW Monitor 3 channel scaling setting.
 * @details Specified setting for channel scaling of HW Monitor 3 Click driver.
 */
#define HWMONITOR3_SCALING_1X                   0
#define HWMONITOR3_SCALING_4X                   1

/**
 * @brief HW Monitor 3 channel selection setting.
 * @details Specified setting for channel selection of HW Monitor 3 Click driver.
 */
#define HWMONITOR3_CHANNEL_NONE                 0x00
#define HWMONITOR3_CHANNEL_1                    0x01
#define HWMONITOR3_CHANNEL_2                    0x02
#define HWMONITOR3_CHANNEL_3                    0x04
#define HWMONITOR3_CHANNEL_4                    0x08
#define HWMONITOR3_CHANNEL_5                    0x10
#define HWMONITOR3_CHANNEL_6                    0x20
#define HWMONITOR3_CHANNEL_ALL                  0x3F

/**
 * @brief HW Monitor 3 voltage calculation setting.
 * @details Specified setting for voltage calculation of HW Monitor 3 Click driver.
 */
#define HWMONITOR3_DATA_RES                     0.005
#define HWMONITOR3_DATA_OFFSET                  0.2
#define HWMONITOR3_DATA_SCALE_4X                4.0

/**
 * @brief HW Monitor 3 device address setting.
 * @details Specified setting for device slave address selection of
 * HW Monitor 3 Click driver.
 */
#define HWMONITOR3_DEVICE_ADDRESS_0             0x33
#define HWMONITOR3_DEVICE_ADDRESS_1             0x37

/*! @} */ // hwmonitor3_set

/**
 * @defgroup hwmonitor3_map HW Monitor 3 MikroBUS Map
 * @brief MikroBUS pin mapping of HW Monitor 3 Click driver.
 */

/**
 * @addtogroup hwmonitor3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HW Monitor 3 Click to the selected MikroBUS.
 */
#define HWMONITOR3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sync = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hwmonitor3_map
/*! @} */ // hwmonitor3

/**
 * @brief HW Monitor 3 Click channel voltage monitor object.
 * @details Channel voltage monitor object definition of HW Monitor 3 Click driver.
 */
typedef struct
{
    float ch1_v;                /**< Channel 1 voltage monitor. */
    float ch2_v;                /**< Channel 2 voltage monitor. */
    float ch3_v;                /**< Channel 3 voltage monitor. */
    float ch4_v;                /**< Channel 4 voltage monitor. */
    float ch5_v;                /**< Channel 5 voltage monitor. */
    float ch6_v;                /**< Channel 6 voltage monitor. */

} hwmonitor3_ch_mon_t;

/**
 * @brief HW Monitor 3 Click context object.
 * @details Context object definition of HW Monitor 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Device enable pin (active high). */
    digital_out_t sleep;        /**< Sleep enable pin (active low). */

    // Input pins
    digital_in_t sync;          /**< Sequence logging synchronization pin. */
    digital_in_t irq;           /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t scaling;            /**< Channel scaling [5:0]: 0 -> 1x, 1 -> 4x. */

} hwmonitor3_t;

/**
 * @brief HW Monitor 3 Click configuration object.
 * @details Configuration object definition of HW Monitor 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t sync;            /**< Sequence logging synchronization pin. */
    pin_name_t en;              /**< Device enable pin (active high). */
    pin_name_t sleep;           /**< Sleep enable pin (active low). */
    pin_name_t irq;             /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} hwmonitor3_cfg_t;

/**
 * @brief HW Monitor 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HWMONITOR3_OK = 0,
    HWMONITOR3_ERROR = -1

} hwmonitor3_return_value_t;

/*!
 * @addtogroup hwmonitor3 HW Monitor 3 Click Driver
 * @brief API for configuring and manipulating HW Monitor 3 Click driver.
 * @{
 */

/**
 * @brief HW Monitor 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hwmonitor3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hwmonitor3_cfg_setup ( hwmonitor3_cfg_t *cfg );

/**
 * @brief HW Monitor 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hwmonitor3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_init ( hwmonitor3_t *ctx, hwmonitor3_cfg_t *cfg );

/**
 * @brief HW Monitor 3 default configuration function.
 * @details This function executes a default configuration of HW Monitor 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hwmonitor3_default_cfg ( hwmonitor3_t *ctx );

/**
 * @brief HW Monitor 3 write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_write_reg ( hwmonitor3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief HW Monitor 3 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_write_regs ( hwmonitor3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief HW Monitor 3 read reg function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_read_reg ( hwmonitor3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief HW Monitor 3 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_read_regs ( hwmonitor3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief HW Monitor 3 set en pin function.
 * @details This function sets the enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] state : 0 - enable, 1 - disable.
 * @return None.
 * @note None.
 */
void hwmonitor3_set_en_pin ( hwmonitor3_t *ctx, uint8_t state );

/**
 * @brief HW Monitor 3 set sleep pin function.
 * @details This function sets the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] state : 0 - sleep enable, 1 - sleep disable.
 * @return None.
 * @note None.
 */
void hwmonitor3_set_sleep_pin ( hwmonitor3_t *ctx, uint8_t state );

/**
 * @brief HW Monitor 3 get sync pin function.
 * @details This function returns the sequence logging synchronization pin logic state.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hwmonitor3_get_sync_pin ( hwmonitor3_t *ctx );

/**
 * @brief HW Monitor 3 get irq pin function.
 * @details This function returns the interrupt pin logic state.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hwmonitor3_get_irq_pin ( hwmonitor3_t *ctx );

/**
 * @brief HW Monitor 3 select bank0 function.
 * @details This function selects bank 0 register map active.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_select_bank0 ( hwmonitor3_t *ctx );

/**
 * @brief HW Monitor 3 select bank1 function.
 * @details This function selects bank 1 register map active.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_select_bank1 ( hwmonitor3_t *ctx );

/**
 * @brief HW Monitor 3 check communication function.
 * @details This function checks the communication by reading and verifying
 * the I2C address register.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor3_check_communication ( hwmonitor3_t *ctx );

/**
 * @brief HW Monitor 3 enable channel function.
 * @details This function enables the selected monitoring channels.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] ch_mask : Bit mask of channels to enable [5:0].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Before this function call the register bank 1 needs to be selected using
 * the hwmonitor3_select_bank1 function.
 */
err_t hwmonitor3_enable_channel ( hwmonitor3_t *ctx, uint8_t ch_mask );

/**
 * @brief HW Monitor 3 disable channel function.
 * @details This function disables the selected monitoring channels.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] ch_mask : Bit mask of channels to disable [5:0].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Before this function call the register bank 1 needs to be selected using
 * the hwmonitor3_select_bank1 function.
 */
err_t hwmonitor3_disable_channel ( hwmonitor3_t *ctx, uint8_t ch_mask );

/**
 * @brief HW Monitor 3 set scaling function.
 * @details This function sets the scaling level for the selected monitoring channels.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[in] scaling : 0 - 1x scaling, 1 - 4x scaling.
 * @param[in] ch_mask : Bit mask of channels to set scaling [5:0].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Before this function call the register bank 1 needs to be selected using
 * the hwmonitor3_select_bank1 function.
 */
err_t hwmonitor3_set_scaling ( hwmonitor3_t *ctx, uint8_t scaling, uint8_t ch_mask );

/**
 * @brief HW Monitor 3 read voltage function.
 * @details This function reads the voltage level from all 6 monitoring analog input channels.
 * @param[in] ctx : Click context object.
 * See #hwmonitor3_t object definition for detailed explanation.
 * @param[out] ch_mon : Monitoring channels object.
 * See #hwmonitor3_ch_mon_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Before this function call the register bank 0 needs to be selected using
 * the hwmonitor3_select_bank0 function.
 */
err_t hwmonitor3_read_voltage ( hwmonitor3_t *ctx, hwmonitor3_ch_mon_t *ch_mon );

#ifdef __cplusplus
}
#endif
#endif // HWMONITOR3_H

/*! @} */ // hwmonitor3

// ------------------------------------------------------------------------ END

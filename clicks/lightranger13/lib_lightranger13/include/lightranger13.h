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
 * @file lightranger13.h
 * @brief This file contains API for LightRanger 13 Click Driver.
 */

#ifndef LIGHTRANGER13_H
#define LIGHTRANGER13_H

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
 * @addtogroup lightranger13 LightRanger 13 Click Driver
 * @brief API for configuring and manipulating LightRanger 13 Click driver.
 * @{
 */

/**
 * @defgroup lightranger13_reg LightRanger 13 Registers List
 * @brief List of registers of LightRanger 13 Click driver.
 */

/**
 * @addtogroup lightranger13_reg
 * @{
 */

/**
 * @brief LightRanger 13 always available registers list.
 * @details Specified always available registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_APPID                     0x00
#define LIGHTRANGER13_REG_APPREV_MAJOR              0x01
#define LIGHTRANGER13_REG_APPREQID                  0x02
#define LIGHTRANGER13_REG_ENABLE                    0xE0
#define LIGHTRANGER13_REG_INT_STATUS                0xE1
#define LIGHTRANGER13_REG_INT_ENAB                  0xE2
#define LIGHTRANGER13_REG_ID                        0xE3
#define LIGHTRANGER13_REG_REVID                     0xE4

/**
 * @brief LightRanger 13 App0 registers list.
 * @details Specified App0 registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_APP0_CMD_DATA_9           0x06
#define LIGHTRANGER13_REG_APP0_CMD_DATA_8           0x07
#define LIGHTRANGER13_REG_APP0_CMD_DATA_7           0x08
#define LIGHTRANGER13_REG_APP0_CMD_DATA_6           0x09
#define LIGHTRANGER13_REG_APP0_CMD_DATA_5           0x0A
#define LIGHTRANGER13_REG_APP0_CMD_DATA_4           0x0B
#define LIGHTRANGER13_REG_APP0_CMD_DATA_3           0x0C
#define LIGHTRANGER13_REG_APP0_CMD_DATA_2           0x0D
#define LIGHTRANGER13_REG_APP0_CMD_DATA_1           0x0E
#define LIGHTRANGER13_REG_APP0_CMD_DATA_0           0x0F
#define LIGHTRANGER13_REG_APP0_CMD                  0x10
#define LIGHTRANGER13_REG_APP0_PREVIOUS             0x11
#define LIGHTRANGER13_REG_APP0_APPREV_MINOR         0x12
#define LIGHTRANGER13_REG_APP0_APPREV_PATCH         0x13
#define LIGHTRANGER13_REG_APP0_STATE                0x1C
#define LIGHTRANGER13_REG_APP0_STATUS               0x1D
#define LIGHTRANGER13_REG_APP0_REGISTER_CONTENTS    0x1E
#define LIGHTRANGER13_REG_APP0_TID                  0x1F

/**
 * @brief LightRanger 13 object detection results registers list.
 * @details Specified object detection results registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_APP0_ODR_RESULT_NUMBER    0x20
#define LIGHTRANGER13_REG_APP0_ODR_RESULT_INFO      0x21
#define LIGHTRANGER13_REG_APP0_ODR_DISTANCE_PEAK_0  0x22
#define LIGHTRANGER13_REG_APP0_ODR_DISTANCE_PEAK_1  0x23
#define LIGHTRANGER13_REG_APP0_ODR_SYS_CLOCK_0      0x24
#define LIGHTRANGER13_REG_APP0_ODR_SYS_CLOCK_1      0x25
#define LIGHTRANGER13_REG_APP0_ODR_SYS_CLOCK_2      0x26
#define LIGHTRANGER13_REG_APP0_ODR_SYS_CLOCK_3      0x27
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_0     0x28
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_1     0x29
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_2     0x2A
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_3     0x2B
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_4     0x2C
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_5     0x2D
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_6     0x2E
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_7     0x2F
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_8     0x30
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_9     0x31
#define LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_10    0x32
#define LIGHTRANGER13_REG_APP0_ODR_TEMPERATURE      0x33
#define LIGHTRANGER13_REG_APP0_ODR_REFERENCE_HITS_0 0x34
#define LIGHTRANGER13_REG_APP0_ODR_REFERENCE_HITS_1 0x35
#define LIGHTRANGER13_REG_APP0_ODR_REFERENCE_HITS_2 0x36
#define LIGHTRANGER13_REG_APP0_ODR_REFERENCE_HITS_3 0x37
#define LIGHTRANGER13_REG_APP0_ODR_OBJECT_HITS_0    0x38
#define LIGHTRANGER13_REG_APP0_ODR_OBJECT_HITS_1    0x39
#define LIGHTRANGER13_REG_APP0_ODR_OBJECT_HITS_2    0x3A
#define LIGHTRANGER13_REG_APP0_ODR_OBJECT_HITS_3    0x3B
#define LIGHTRANGER13_REG_APP0_ODR_XTALK_MSB        0x3C
#define LIGHTRANGER13_REG_APP0_ODR_XTALK_LSB        0x3D

/**
 * @brief LightRanger 13 calibration and algorithm state data exchange registers list.
 * @details Specified calibration and algorithm state data exchange registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_0  0x20
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_1  0x21
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_2  0x22
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_3  0x23
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_4  0x24
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_5  0x25
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_6  0x26
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_7  0x27
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_8  0x28
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_9  0x29
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_10 0x2A
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_11 0x2B
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_12 0x2C
#define LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_13 0x2D
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_0  0x2E
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_1  0x2F
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_2  0x30
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_3  0x31
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_4  0x32
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_5  0x33
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_6  0x34
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_7  0x35
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_8  0x36
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_9  0x37
#define LIGHTRANGER13_REG_APP0_CAD_STATE_DATA_WR_10 0x38

/**
 * @brief LightRanger 13 RAW histogram registers list.
 * @details Specified RAW histogram registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_APP0_RH_HIST_START        0x20
#define LIGHTRANGER13_REG_APP0_RH_HIST_END          0x9F

/**
 * @brief LightRanger 13 serial number registers list.
 * @details Specified serial number registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_APP0_SN_SERIAL_NUMBER_0   0x28
#define LIGHTRANGER13_REG_APP0_SN_SERIAL_NUMBER_1   0x29
#define LIGHTRANGER13_REG_APP0_SN_IDENTI_NUMBER_0   0x2A
#define LIGHTRANGER13_REG_APP0_SN_IDENTI_NUMBER_1   0x2B

/**
 * @brief LightRanger 13 interrupt suppression registers list.
 * @details Specified interrupt suppression registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_APP0_IS_PERSISTENCE       0x20
#define LIGHTRANGER13_REG_APP0_IS_LOW_THOLD_LSB     0x21
#define LIGHTRANGER13_REG_APP0_IS_LOW_THOLD_MSB     0x22
#define LIGHTRANGER13_REG_APP0_IS_HIGH_THOLD_LSB    0x23
#define LIGHTRANGER13_REG_APP0_IS_HIGH_THOLD_MSB    0x24

/**
 * @brief LightRanger 13 App0 commands list.
 * @details Specified App0 commands list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_CMD_NOP                       0x00
#define LIGHTRANGER13_CMD_START_MEASUREMENT         0x02
#define LIGHTRANGER13_CMD_WRITE_ADD_CFG             0x08
#define LIGHTRANGER13_CMD_READ_ADD_CFG              0x09
#define LIGHTRANGER13_CMD_CUSTOMER_FACTORY_CALIB    0x0A
#define LIGHTRANGER13_CMD_GPIO_CONTROL              0x0F
#define LIGHTRANGER13_CMD_ENABLE_HISTOGRAM_ROUT     0x30
#define LIGHTRANGER13_CMD_CONTINUE_HISTOGRAM_ROUT   0x32
#define LIGHTRANGER13_CMD_READ_SERIAL_NUMBER        0x47
#define LIGHTRANGER13_CMD_CHANGE_I2C_ADDRESS        0x49
#define LIGHTRANGER13_CMD_READ_HISTOGRAM            0x80
#define LIGHTRANGER13_CMD_STOP_COMMAND              0xFF

/**
 * @brief LightRanger 13 bootloader registers list.
 * @details Specified bootloader registers list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REG_BL_CMD_STAT               0x08
#define LIGHTRANGER13_REG_BL_SIZE                   0x09
#define LIGHTRANGER13_REG_BL_DATA                   0x0A

/**
 * @brief LightRanger 13 bootloader commands list.
 * @details Specified bootloader commands list of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_BL_CMD_RAMREMAP_RESET         0x11
#define LIGHTRANGER13_BL_CMD_DOWNLOAD_INIT          0x14
#define LIGHTRANGER13_BL_CMD_W_RAM                  0x41
#define LIGHTRANGER13_BL_CMD_ADDR_RAM               0x43

/*! @} */ // lightranger13_reg

/**
 * @defgroup lightranger13_set LightRanger 13 Registers Settings
 * @brief Settings for registers of LightRanger 13 Click driver.
 */

/**
 * @addtogroup lightranger13_set
 * @{
 */

/**
 * @brief LightRanger 13 wait register state setting.
 * @details Specified setting for wait register state of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_MASK_ALL                      0xFF

/**
 * @brief LightRanger 13 STATUS register setting.
 * @details Specified setting for STATUS register of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_STATUS_IDLE                   0x00
#define LIGHTRANGER13_STATUS_DIAGNOSTIC             0x01
#define LIGHTRANGER13_STATUS_START                  0x02
#define LIGHTRANGER13_STATUS_CALIBRATION            0x03
#define LIGHTRANGER13_STATUS_LIGHT_COL              0x04
#define LIGHTRANGER13_STATUS_ALGORITHM              0x05
#define LIGHTRANGER13_STATUS_STARTUP                0x06
#define LIGHTRANGER13_STATUS_VCSEL_PWR_FAIL         0x10
#define LIGHTRANGER13_STATUS_VCSEL_LED_A_FAIL       0x11
#define LIGHTRANGER13_STATUS_VCSEL_LED_K_FAIL       0x12
#define LIGHTRANGER13_STATUS_CALIB_ERROR            0x1B
#define LIGHTRANGER13_STATUS_INVAL_CMD              0x1C
#define LIGHTRANGER13_STATUS_ERR_MISSING_FACT_CAL   0x27
#define LIGHTRANGER13_STATUS_ERR_INVALID_FACT_CAL   0x28
#define LIGHTRANGER13_STATUS_ERR_INVALID_ALG_STATE  0x29

/**
 * @brief LightRanger 13 ENABLE register setting.
 * @details Specified setting for ENABLE register of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_ENABLE_CPU_RESET              0x80
#define LIGHTRANGER13_ENABLE_CPU_READY              0x40
#define LIGHTRANGER13_ENABLE_PON                    0x01
#define LIGHTRANGER13_ENABLE_STANDBY                0x00

/**
 * @brief LightRanger 13 APPID register setting.
 * @details Specified setting for APPID register of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_APPID_BOOTLOADER              0x80
#define LIGHTRANGER13_APPID_APP0                    0xC0

/**
 * @brief LightRanger 13 REGISTER_CONTENTS data setting.
 * @details Specified setting for register data of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_REGISTER_CONTENTS_CALIBRATION 0x0A
#define LIGHTRANGER13_REGISTER_CONTENTS_SN          0x47
#define LIGHTRANGER13_REGISTER_CONTENTS_MEASUREMENT 0x55
#define LIGHTRANGER13_REGISTER_CONTENTS_HISTOGRAM   0x80

/**
 * @brief LightRanger 13 interrupt setting.
 * @details Specified setting for interrupt of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_INTERRUPT_RESULT              0x01
#define LIGHTRANGER13_INTERRUPT_DIAGNOSTIC          0x02

/**
 * @brief LightRanger 13 measurement config setting.
 * @details Specified setting for measurement config of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_MEAS_CFG_9_AMPLITUDE_MASK     0x0F
#define LIGHTRANGER13_MEAS_CFG_9_CONFIG_MASK        0x30
#define LIGHTRANGER13_MEAS_CFG_8_AMPLITUDE_MASK     0x0F
#define LIGHTRANGER13_MEAS_CFG_8_CONFIG_MASK        0x30
#define LIGHTRANGER13_MEAS_CFG_7_FACTORY_CAL_MASK   0x01
#define LIGHTRANGER13_MEAS_CFG_7_ALG_STATE_MASK     0x02
#define LIGHTRANGER13_MEAS_CFG_7_SPAD_DEAD_T_MASK   0x38
#define LIGHTRANGER13_MEAS_CFG_7_SPAD_SELECT_MASK   0xC0
#define LIGHTRANGER13_MEAS_CFG_6_DISTANCE_EN_MASK   0x02
#define LIGHTRANGER13_MEAS_CFG_6_VCSEL_CLKDIV2_MASK 0x04
#define LIGHTRANGER13_MEAS_CFG_6_DISTANCE_MODE_MASK 0x08
#define LIGHTRANGER13_MEAS_CFG_6_IMMEDIATE_INT_MASK 0x10
#define LIGHTRANGER13_MEAS_CFG_6_ALG_KEEP_RDY_MASK  0x80
#define LIGHTRANGER13_MEAS_CFG_5_GPIO_0_MASK        0x0F
#define LIGHTRANGER13_MEAS_CFG_5_GPIO_1_MASK        0xF0
#define LIGHTRANGER13_MEAS_CFG_4_ALS_DELAY_MASK     0x03
#define LIGHTRANGER13_MEAS_CFG_3_THRESHOLD_MASK     0x3F
#define LIGHTRANGER13_MEAS_CFG_3_VCSEL_SS_AMP_MASK  0xC0
#define LIGHTRANGER13_MEAS_CFG_2_REP_PERIOD_MS_MASK 0xFF
#define LIGHTRANGER13_MEAS_CFG_1_K_ITERS_LSB_MASK   0xFF
#define LIGHTRANGER13_MEAS_CFG_0_K_ITERS_MSB_MASK   0xFF

/**
 * @brief LightRanger 13 factory calibration setting.
 * @details Specified setting for factory calibration of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_FACTORY_CALIB_STATE           0x00
#define LIGHTRANGER13_FACTORY_CALIB_K_ITERS         0xA000

/**
 * @brief LightRanger 13 default factory calib, state data, and measurement config setting.
 * @details Specified setting for default factory calib, state data, and measurement config of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_FACTORY_CALIB_0               0x02
#define LIGHTRANGER13_FACTORY_CALIB_1               0x00
#define LIGHTRANGER13_FACTORY_CALIB_2               0x00
#define LIGHTRANGER13_FACTORY_CALIB_3               0x00
#define LIGHTRANGER13_FACTORY_CALIB_4               0x00
#define LIGHTRANGER13_FACTORY_CALIB_5               0x00
#define LIGHTRANGER13_FACTORY_CALIB_6               0x00
#define LIGHTRANGER13_FACTORY_CALIB_7               0x00
#define LIGHTRANGER13_FACTORY_CALIB_8               0x00
#define LIGHTRANGER13_FACTORY_CALIB_9               0x00
#define LIGHTRANGER13_FACTORY_CALIB_10              0x00
#define LIGHTRANGER13_FACTORY_CALIB_11              0x00
#define LIGHTRANGER13_FACTORY_CALIB_12              0x00
#define LIGHTRANGER13_FACTORY_CALIB_13              0x00
#define LIGHTRANGER13_STATE_DATA_0                  0x02
#define LIGHTRANGER13_STATE_DATA_1                  0x3C
#define LIGHTRANGER13_STATE_DATA_2                  0x00
#define LIGHTRANGER13_STATE_DATA_3                  0x00
#define LIGHTRANGER13_STATE_DATA_4                  0x7C
#define LIGHTRANGER13_STATE_DATA_5                  0x7C
#define LIGHTRANGER13_STATE_DATA_6                  0x00
#define LIGHTRANGER13_STATE_DATA_7                  0x00
#define LIGHTRANGER13_STATE_DATA_8                  0x00
#define LIGHTRANGER13_STATE_DATA_9                  0x00
#define LIGHTRANGER13_STATE_DATA_10                 0x00
#define LIGHTRANGER13_MEAS_CFG_SS_SPAD_CHG_PUMP     0x00
#define LIGHTRANGER13_MEAS_CFG_SS_VCSEL_CHG_PUMP    0x00
#define LIGHTRANGER13_MEAS_CFG_CALIB_STATE          ( LIGHTRANGER13_MEAS_CFG_7_FACTORY_CAL_MASK | \
                                                      LIGHTRANGER13_MEAS_CFG_7_ALG_STATE_MASK )
#define LIGHTRANGER13_MEAS_CFG_ALGO                 LIGHTRANGER13_MEAS_CFG_6_DISTANCE_EN_MASK
#define LIGHTRANGER13_MEAS_CFG_GPIO_CTRL            0x00
#define LIGHTRANGER13_MEAS_CFG_DAX_DELAY_100US      0x00
#define LIGHTRANGER13_MEAS_CFG_SNR                  0x06
#define LIGHTRANGER13_MEAS_CFG_REP_PERIOD_MS        33
#define LIGHTRANGER13_MEAS_CFG_K_ITERS              400

/**
 * @brief LightRanger 13 timeout setting.
 * @details Specified setting for timeout of LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_TIMEOUT_INFINITE              0
#define LIGHTRANGER13_TIMEOUT_1MS                   1
#define LIGHTRANGER13_TIMEOUT_2MS                   2
#define LIGHTRANGER13_TIMEOUT_3MS                   3
#define LIGHTRANGER13_TIMEOUT_5MS                   5
#define LIGHTRANGER13_TIMEOUT_10MS                  10
#define LIGHTRANGER13_TIMEOUT_150MS                 150
#define LIGHTRANGER13_TIMEOUT_5S                    5000

/**
 * @brief LightRanger 13 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 13 Click driver.
 */
#define LIGHTRANGER13_DEVICE_ADDRESS                0x41

/*! @} */ // lightranger13_set

/**
 * @defgroup lightranger13_map LightRanger 13 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 13 Click driver.
 */

/**
 * @addtogroup lightranger13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 13 Click to the selected MikroBUS.
 */
#define LIGHTRANGER13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger13_map
/*! @} */ // lightranger13

/**
 * @brief LightRanger 13 Click device information object.
 * @details Device information object definition of LightRanger 13 Click driver.
 */
typedef struct
{
    uint32_t serial_num;        /**< Serial number of device, if 0 after read -> device is in bootloader mode. */
    uint8_t app_ver[ 4 ];       /**< Application version number (app id, major, minor, patch). */
    uint8_t chip_ver[ 2 ];      /**< Chip version (id, rev id). */

} lightranger13_info_t;

/**
 * @brief LightRanger 13 Click device measurement config object.
 * @details Device measurement config object definition of LightRanger 13 Click driver.
 */
typedef struct
{
    uint8_t ss_spad_chg_pump;   /**< Spread spectrum (jitter) of the High Voltage (SPAD) charge pump clock. */
    uint8_t ss_vcsel_chg_pump;  /**< Spread spectrum (jitter) of the VCSEL charge pump clock. */
    uint8_t calib_state;        /**< Calibration/state data bit mask. */
    uint8_t algo;               /**< Algorithm bit mask. */
    uint8_t gpio_ctrl;          /**< GPIO control bits. */
    uint8_t dax_delay_100us;    /**< DAX delay, 0 for no delay/signal, otherwise in units of 100uS. */
    uint8_t snr;                /**< Object detection threshold and spread spectrum mode. */
    uint8_t rep_period_ms;      /**< Measurement period in ms, use 0 for single shot. */
    uint16_t k_iters;           /**< Integration iteration *1000. Valid values are from 10 to 4000. */

} lightranger13_meas_cfg_t;

/**
 * @brief LightRanger 13 Click device measurement results object.
 * @details Device measurement results object definition of LightRanger 13 Click driver.
 */
typedef struct
{
    uint8_t result_num;         /**< Result number, incremented every time there is a unique answer. */
    uint8_t result_info;        /**< Reliability and status of object measurement. */
    uint16_t dist_peak;         /**< Distance to the peak of the object */
    uint32_t sys_clock;         /**< System clock/time stamp in units of 0.2us. */
    uint8_t state_data[ 11 ];   /**< Packed state data. Host can store this during a sleep, and re-upload it for the next measurement. */
    int8_t temperature;         /**< The measurement temperature in degree celsius. */
    uint32_t ref_hits;          /**< Sum of the reference SPADs during the distance measurement. */
    uint32_t object_hits;       /**< Sum of the object SPADs during the distance measurement. */
    uint16_t xtalk;             /**< The crosstalk peak value. */

} lightranger13_meas_result_t;

/**
 * @brief LightRanger 13 Click context object.
 * @details Context object definition of LightRanger 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    lightranger13_info_t info;  /**< Device information. */

    lightranger13_meas_cfg_t meas_cfg;  /**< Measurement config. */
    uint8_t factory_calib[ 14 ];        /**< Factory calibration data. */
    uint8_t state_data[ 11 ];           /**< Packed state data used for next measurement. */

} lightranger13_t;

/**
 * @brief LightRanger 13 Click configuration object.
 * @details Configuration object definition of LightRanger 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} lightranger13_cfg_t;

/**
 * @brief LightRanger 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTRANGER13_OK = 0,
    LIGHTRANGER13_ERROR = -1

} lightranger13_return_value_t;

/*!
 * @addtogroup lightranger13 LightRanger 13 Click Driver
 * @brief API for configuring and manipulating LightRanger 13 Click driver.
 * @{
 */

/**
 * @brief LightRanger 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger13_cfg_setup ( lightranger13_cfg_t *cfg );

/**
 * @brief LightRanger 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_init ( lightranger13_t *ctx, lightranger13_cfg_t *cfg );

/**
 * @brief LightRanger 13 default configuration function.
 * @details This function executes a default configuration of LightRanger 13
 * Click board.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lightranger13_default_cfg ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_write_regs ( lightranger13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 13 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_read_regs ( lightranger13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LightRanger 13 write reg function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_write_reg ( lightranger13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LightRanger 13 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_read_reg ( lightranger13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LightRanger 13 send cmd function.
 * @details This function sends a desired App0 command with or without payload,
 * and waits a desired period for a command execution.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] cmd : App0 command list.
 * @param[in] payload : Command payload buffer.
 * @param[in] payload_len : Command payload len.
 * @param[in] timeout_ms : Response timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_send_cmd ( lightranger13_t *ctx, uint8_t cmd, uint8_t *payload, 
                               uint8_t payload_len, uint16_t timeout_ms );

/**
 * @brief LightRanger 13 wait reg state function.
 * @details This function waits a desired period for selected register bit mask state.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Register bit mask.
 * @param[in] state : Register bit state.
 * @param[in] timeout_ms : Response timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_wait_reg_state ( lightranger13_t *ctx, uint8_t reg, uint8_t mask, 
                                     uint8_t state, uint16_t timeout_ms );

/**
 * @brief LightRanger 13 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger13_enable_device ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger13_disable_device ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lightranger13_get_int_pin ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 power up function.
 * @details This function enables the device and switches it to ROM application state.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_power_up ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 read info function.
 * @details This function reads the device information and stores it in ctx->info structure.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_read_info ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 clear interrupts function.
 * @details This function reads and clears the interrupt status register.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_clear_interrupts ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 factory calib function.
 * @details This function performs a factory calibration.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Calibration environment:
 * Device has to be in the final (correct) optical stack.
 * Cover glass (no smudge on the glass) in front of the device.
 * No target in front of the device within 40cm.
 * Dark room or low ambient light.
 */
err_t lightranger13_factory_calib ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 set threshold function.
 * @details This function sets a threshold level and interrupt persistance.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] t_low : Threshold low in millimeters.
 * @param[in] t_high : Threshold high in millimeters.
 * @param[in] persistance : 0 - ignore threshold, >=1 - number of consecutive results in threshold range.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_set_threshold ( lightranger13_t *ctx, uint16_t t_low, uint16_t t_high, uint8_t persistance );

/**
 * @brief LightRanger 13 start measurement function.
 * @details This function starts a measurement (the configuration, factory calibration and state data are
 * used from context object).
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_start_measurement ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 stop measurement function.
 * @details This function stops a measurement.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_stop_measurement ( lightranger13_t *ctx );

/**
 * @brief LightRanger 13 read result function.
 * @details This function reads the measurement results.
 * @param[in] ctx : Click context object.
 * See #lightranger13_t object definition for detailed explanation.
 * @param[in] result : Click context object.
 * See #lightranger13_meas_result_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger13_read_result ( lightranger13_t *ctx, lightranger13_meas_result_t *result );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER13_H

/*! @} */ // lightranger13

// ------------------------------------------------------------------------ END

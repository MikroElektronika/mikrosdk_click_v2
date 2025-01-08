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
 * @file smartdof4.h
 * @brief This file contains API for Smart DOF 4 Click Driver.
 */

#ifndef SMARTDOF4_H
#define SMARTDOF4_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup smartdof4 Smart DOF 4 Click Driver
 * @brief API for configuring and manipulating Smart DOF 4 Click driver.
 * @{
 */

/**
 * @defgroup smartdof4_reg Smart DOF 4 Registers List
 * @brief List of registers of Smart DOF 4 Click driver.
 */

/**
 * @addtogroup smartdof4_reg
 * @{
 */

/**
 * @brief Smart DOF 4 channel list.
 * @details Specified channel list of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_CH_CMD                                0
#define SMARTDOF4_CH_EXE                                1
#define SMARTDOF4_CH_CTRL                               2
#define SMARTDOF4_CH_INPUT_REP                          3
#define SMARTDOF4_CH_WAKE_REP                           4
#define SMARTDOF4_CH_GYRO_VECTOR                        5

/**
 * @brief Smart DOF 4 commands list.
 * @details Specified commands list of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_CMD_ERR                               0x01
#define SMARTDOF4_CMD_COUNT                             0x02
#define SMARTDOF4_CMD_TARE                              0x03
#define SMARTDOF4_CMD_INIT                              0x04
#define SMARTDOF4_CMD_UNS_INIT                          0x84
#define SMARTDOF4_CMD_SAVE_DCD                          0x06
#define SMARTDOF4_CMD_ME_CALIB                          0x07
#define SMARTDOF4_CMD_DCD_PERIOD_SAVE                   0x09
#define SMARTDOF4_CMD_OSCIL                             0x0A
#define SMARTDOF4_CMD_CLEAR_DCD                         0x0B
#define SMARTDOF4_CMD_CALIB                             0x0C
#define SMARTDOF4_CMD_BOOT                              0x0D
#define SMARTDOF4_CMD_INTER_CALIB                       0x0E

/**
 * @brief Smart DOF 4 commands settings.
 * @details Specified commands settings of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_CMD_INIT_SUB_REINIT                   0x01
#define SMARTDOF4_CMD_INIT_STATUS_OK                    0x00

/**
 * @brief Smart DOF 4 report ID list.
 * @details Specified report ID list of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_REP_ID_GET_FEAT_REQ                   0xFE
#define SMARTDOF4_REP_ID_SET_FEAT_CMD                   0xFD
#define SMARTDOF4_REP_ID_GET_FEAT_RESP                  0xFC
#define SMARTDOF4_REP_ID_BASE_TIMESTAMP                 0xFB
#define SMARTDOF4_REP_ID_TIMESTAMP_REBASE               0xFA
#define SMARTDOF4_REP_ID_PROD_ID_REQ                    0xF9
#define SMARTDOF4_REP_ID_PROD_ID_RESP                   0xF8
#define SMARTDOF4_REP_ID_FRS_WR_REQ                     0xF7
#define SMARTDOF4_REP_ID_FRS_WR_DATA                    0xF6
#define SMARTDOF4_REP_ID_FRS_WR_RESP                    0xF5
#define SMARTDOF4_REP_ID_FRS_RD_REQ                     0xF4
#define SMARTDOF4_REP_ID_FRS_RD_RESP                    0xF3
#define SMARTDOF4_REP_ID_CMD_REQ                        0xF2
#define SMARTDOF4_REP_ID_CMD_RESP                       0xF1
#define SMARTDOF4_REP_ID_ACCEL                          0x01
#define SMARTDOF4_REP_ID_GYRO                           0x02
#define SMARTDOF4_REP_ID_MAGNET                         0x03
#define SMARTDOF4_REP_ID_LINEAR_ACCEL                   0x04
#define SMARTDOF4_REP_ID_ROT_VECTOR                     0x05
#define SMARTDOF4_REP_ID_GRAVITY                        0x06
#define SMARTDOF4_REP_ID_UNCALIB_GYRO                   0x07
#define SMARTDOF4_REP_ID_GAME_ROT_VECTOR                0x08
#define SMARTDOF4_REP_ID_GEOMAG_ROT_VECTOR              0x09
#define SMARTDOF4_REP_ID_PRESSURE                       0x0A
#define SMARTDOF4_REP_ID_AMB_LIGHT                      0x0B
#define SMARTDOF4_REP_ID_HUMIDITY                       0x0C
#define SMARTDOF4_REP_ID_PROXIMITY                      0x0D
#define SMARTDOF4_REP_ID_TEMPERATURE                    0x0E
#define SMARTDOF4_REP_ID_UNCALIB_MAG_FIELD              0x0F
#define SMARTDOF4_REP_ID_TAP_DETECT                     0x10
#define SMARTDOF4_REP_ID_STEP_COUNT                     0x11
#define SMARTDOF4_REP_ID_SIG_MOTION                     0x12
#define SMARTDOF4_REP_ID_STABIL_CLASS                   0x13
#define SMARTDOF4_REP_ID_RAW_ACCEL                      0x14
#define SMARTDOF4_REP_ID_RAW_GYRO                       0x15
#define SMARTDOF4_REP_ID_RAW_MAGNETO                    0x16
#define SMARTDOF4_REP_ID_SAR                            0x17
#define SMARTDOF4_REP_ID_STEP_DETECT                    0x18
#define SMARTDOF4_REP_ID_SHAKE_DETECT                   0x19
#define SMARTDOF4_REP_ID_FLIP_DETECT                    0x1A
#define SMARTDOF4_REP_ID_PICKUP_DETECT                  0x1B
#define SMARTDOF4_REP_ID_STABIL_DETECT                  0x1C
#define SMARTDOF4_REP_ID_PERS_ACT_CLASS                 0x1E
#define SMARTDOF4_REP_ID_SLEEP_DETECT                   0x1F
#define SMARTDOF4_REP_ID_TILT_DETECT                    0x20
#define SMARTDOF4_REP_ID_POCKET_DETECT                  0x21
#define SMARTDOF4_REP_ID_CIRCLE_DETECT                  0x22
#define SMARTDOF4_REP_ID_HEART_RATE_MONITOR             0x23
#define SMARTDOF4_REP_ID_ARVR_ROT_VECT                  0x28
#define SMARTDOF4_REP_ID_ARVR_GAME_ROT_VECT             0x29

/**
 * @brief Smart DOF 4 FRS record ID list.
 * @details Specified FRS record ID list of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_REC_ID_STATIC_CALIB_AGM               0x7979
#define SMARTDOF4_REC_ID_NOMINAL_CALIB_AGM              0x4D4D
#define SMARTDOF4_REC_ID_STATIC_CALIB_SRA               0x8A8A
#define SMARTDOF4_REC_ID_NOMINAL_CALIB_SRA              0x4E4E
#define SMARTDOF4_REC_ID_DYNAMIC_CALIB                  0x1F1F
#define SMARTDOF4_REC_ID_MOTION_ENG_POW_MGMT            0xD3E2
#define SMARTDOF4_REC_ID_SYS_ORIENT                     0x2D3E
#define SMARTDOF4_REC_ID_PRIM_ACCEL_ORIENT              0x2D41
#define SMARTDOF4_REC_ID_SCREEN_ROT_ACCEL_ORIENT        0x2D43
#define SMARTDOF4_REC_ID_GYRO_ORIENT                    0x2D46
#define SMARTDOF4_REC_ID_MAGNETO_ORIENT                 0x2D4C
#define SMARTDOF4_REC_ID_ARVR_ROT_VEC                   0x3E2D
#define SMARTDOF4_REC_ID_ARVR_GAME_ROT_VEC              0x3E2E
#define SMARTDOF4_REC_ID_SIG_MOTION_DETECT_CFG          0xC274
#define SMARTDOF4_REC_ID_SHAKE_DETECT_CFG               0x7D7D
#define SMARTDOF4_REC_ID_MAX_FUSION_PERIOD              0xD7D7
#define SMARTDOF4_REC_ID_SERIAL_NUM                     0x4B4B
#define SMARTDOF4_REC_ID_ENVIRO_SENS_PRESS              0x39AF
#define SMARTDOF4_REC_ID_ENVIRO_SENS_TEMP               0x4D20
#define SMARTDOF4_REC_ID_ENVIRO_SENS_HUMI               0x1AC9
#define SMARTDOF4_REC_ID_ENVIRO_SENS_AMBI               0x39B1
#define SMARTDOF4_REC_ID_ENVIRO_SENS_PROXI              0x4DA2
#define SMARTDOF4_REC_ID_ALS_CALIB                      0xD401
#define SMARTDOF4_REC_ID_PROXI_SENS_CALIB               0xD402
#define SMARTDOF4_REC_ID_PICKUP_DETECT_CFG              0x1B2A
#define SMARTDOF4_REC_ID_FLIP_DETECT_CFG                0xFC94
#define SMARTDOF4_REC_ID_STAB_DETECT_CFG                0xED85
#define SMARTDOF4_REC_ID_ACT_TRACK_CFG                  0xED88
#define SMARTDOF4_REC_ID_SLEEP_DETECT_CFG               0xED87
#define SMARTDOF4_REC_ID_TILT_DETECT_CFG                0xED89
#define SMARTDOF4_REC_ID_POCK_DETECT_CFG                0xEF27
#define SMARTDOF4_REC_ID_CIRC_DETECT_CFG                0xEE51
#define SMARTDOF4_REC_ID_USER_REC                       0x74B4
#define SMARTDOF4_REC_ID_MOTION_ENG_TIME_SRC_SEL        0xD403
#define SMARTDOF4_REC_ID_UART_OUT_FORMAT_SEL            0xA1A1
#define SMARTDOF4_REC_ID_GYROINT_ROT_VEC_CFG            0xA1A2
#define SMARTDOF4_REC_ID_FUSION_CTRL_FLAGS              0xA1A3
#define SMARTDOF4_REC_ID_SIMPLE_CALIB_CONF              0xA1A4
#define SMARTDOF4_REC_ID_NOMIN_CALIB_CONF               0xA1A5
#define SMARTDOF4_REC_ID_RAW_ACCEL                      0xE301
#define SMARTDOF4_REC_ID_ACCEL                          0xE302
#define SMARTDOF4_REC_ID_LINEAR_ACCEL                   0xE303
#define SMARTDOF4_REC_ID_GRAVITY                        0xE304
#define SMARTDOF4_REC_ID_RAW_GYRO                       0xE305
#define SMARTDOF4_REC_ID_GYRO_CALIB                     0xE306
#define SMARTDOF4_REC_ID_GYRO_UNCALIB                   0xE307
#define SMARTDOF4_REC_ID_RAW_MAGNETO                    0xE308
#define SMARTDOF4_REC_ID_MAGNETO_CALIB                  0xE309
#define SMARTDOF4_REC_ID_MAGNETO_UNCALIB                0xE30A
#define SMARTDOF4_REC_ID_ROT_VECTOR                     0xE30B
#define SMARTDOF4_REC_ID_GAME_ROT_VECTOR                0xE30C
#define SMARTDOF4_REC_ID_GEO_ROT_VECTOR                 0xE30D
#define SMARTDOF4_REC_ID_PRESSURE                       0xE30E
#define SMARTDOF4_REC_ID_AMBIENT_LIGHT                  0xE30F
#define SMARTDOF4_REC_ID_HUMIDITY                       0xE310
#define SMARTDOF4_REC_ID_PROXI                          0xE311
#define SMARTDOF4_REC_ID_TEMPERATURE                    0xE312
#define SMARTDOF4_REC_ID_TAP_DETECT                     0xE313
#define SMARTDOF4_REC_ID_STEP_DETECT                    0xE314
#define SMARTDOF4_REC_ID_STEP_COUNT                     0xE315
#define SMARTDOF4_REC_ID_SIG_MOTION                     0xE316
#define SMARTDOF4_REC_ID_STABIL_CLASS                   0xE317
#define SMARTDOF4_REC_ID_SHAKE_DETECT                   0xE318
#define SMARTDOF4_REC_ID_FLIP_DETECT                    0xE319
#define SMARTDOF4_REC_ID_PICK_DETECT                    0xE31A
#define SMARTDOF4_REC_ID_STABIL_DETECT                  0xE31B
#define SMARTDOF4_REC_ID_PERS_ACT_CLASS                 0xE31C
#define SMARTDOF4_REC_ID_SLEEP_DETECT                   0xE31D
#define SMARTDOF4_REC_ID_TILT_DETECT                    0xE31E
#define SMARTDOF4_REC_ID_POCKET_DETECT                  0xE31F
#define SMARTDOF4_REC_ID_CIRCLE_DETECT                  0xE320
#define SMARTDOF4_REC_ID_HEART_RATE_MON                 0xE321
#define SMARTDOF4_REC_ID_ARVR_ROT_VECTOR                0xE322
#define SMARTDOF4_REC_ID_ARVR_GAME_ROT_VECTOR           0xE323
#define SMARTDOF4_REC_ID_GYRO_INTEG_ROT_VEC             0xE324
#define SMARTDOF4_REC_ID_MOTION_REQ                     0xE325

/*! @} */ // smartdof4_reg

/**
 * @defgroup smartdof4_set Smart DOF 4 Registers Settings
 * @brief Settings for registers of Smart DOF 4 Click driver.
 */

/**
 * @addtogroup smartdof4_set
 * @{
 */

/**
 * @brief Smart DOF 4 timeout setting.
 * @details Specified setting for timeout of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_TIMEOUT_MS                            2000

/**
 * @brief Smart DOF 4 Sensor data Q points setting.
 * @details Specified setting for sensor data Q points of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_QPOINT_RAW_ACCEL                      0
#define SMARTDOF4_QPOINT_ACCEL                          8
#define SMARTDOF4_QPOINT_LINEAR_ACCEL                   8
#define SMARTDOF4_QPOINT_GRAVITY                        8
#define SMARTDOF4_QPOINT_RAW_GYRO                       0
#define SMARTDOF4_QPOINT_GYRO_CALIB                     9
#define SMARTDOF4_QPOINT_GYRO_UNCALIB                   9
#define SMARTDOF4_QPOINT_RAW_MAGNETO                    0
#define SMARTDOF4_QPOINT_MAGNET_CALIB                   4
#define SMARTDOF4_QPOINT_MAGNET_UNCALIB                 4
#define SMARTDOF4_QPOINT_ROT_VECT                       14
#define SMARTDOF4_QPOINT_GAME_ROT_VECT                  14
#define SMARTDOF4_QPOINT_GEOMAG_ROT_VECT                14
#define SMARTDOF4_QPOINT_TAP_DETECT                     0
#define SMARTDOF4_QPOINT_STEP_DETECT                    0
#define SMARTDOF4_QPOINT_STEP_COUNT                     0
#define SMARTDOF4_QPOINT_SIG_MOTION                     0
#define SMARTDOF4_QPOINT_STABIL_CLASS                   0
#define SMARTDOF4_QPOINT_SHAKE_DETECT                   0
#define SMARTDOF4_QPOINT_STABIL_DETECT                  0
#define SMARTDOF4_QPOINT_PERS_ACT_CLASS                 0
#define SMARTDOF4_QPOINT_ARVR_STABIL_ROT_VECT           14
#define SMARTDOF4_QPOINT_ARVR_STABIL_GAME_ROT_VECT      14
#define SMARTDOF4_QPOINT_GYRO_INT_ROT_VECT              14

/**
 * @brief Smart DOF 4 data calculation setting.
 * @details Specified setting for data calculation of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_SCALEQ( x )                           ( 1.0f / ( 1u << x ) )
#define SMARTDOF4_GRAVITY                               9.80665f
#define SMARTDOF4_RAD_TO_DEG                            57.2957795f

/**
 * @brief Smart DOF 4 sensor feature setting.
 * @details Specified setting for sensor feature of Smart DOF 4 Click driver.
 */
#define SMARTDOF4_FEATURE_FLAGS                         0x00
#define SMARTDOF4_FEATURE_CHANCE_SENS                   0x0000
#define SMARTDOF4_FEATURE_REP_INTERVAL_US               100000ul
#define SMARTDOF4_FEATURE_BATCH_INTERVAL_US             0ul
#define SMARTDOF4_FEATURE_SENSOR_SPEC                   0x00000000ul

/**
 * @brief Smart DOF 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart DOF 4 Click driver.
 */
#define SMARTDOF4_DEVICE_ADDRESS_0                      0x4A
#define SMARTDOF4_DEVICE_ADDRESS_1                      0x4B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smartdof4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMARTDOF4_SET_DATA_SAMPLE_EDGE                  SET_SPI_DATA_SAMPLE_EDGE
#define SMARTDOF4_SET_DATA_SAMPLE_MIDDLE                SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // smartdof4_set

/**
 * @defgroup smartdof4_map Smart DOF 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart DOF 4 Click driver.
 */

/**
 * @addtogroup smartdof4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart DOF 4 Click to the selected MikroBUS.
 */
#define SMARTDOF4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartdof4_map
/*! @} */ // smartdof4

/**
 * @brief Smart DOF 4 Click driver selector.
 * @details Selects target driver interface of Smart DOF 4 Click driver.
 */
typedef enum
{
    SMARTDOF4_DRV_SEL_SPI,          /**< SPI driver descriptor. */
    SMARTDOF4_DRV_SEL_I2C           /**< I2C driver descriptor. */

} smartdof4_drv_t;

/**
 * @brief Smart DOF 4 SHTP packet buffer object.
 * @details SHTP packet buffer object definition of Smart DOF 4 Click driver.
 */
typedef struct
{
    uint8_t channel;                /**< Channel number. */
    uint8_t ch_seq_num;             /**< Channel sequence number. */
    uint8_t payload[ 1020 ];        /**< SHTP packet payload. */
    uint16_t payload_len;           /**< SHTP packet payload len (without header bytes). */

} smartdof4_shtp_t;

/**
 * @brief Smart DOF 4 Click context object.
 * @details Context object definition of Smart DOF 4 Click driver.
 */
typedef struct smartdof4_s
{
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t wup;              /**< Protocol select pin 0 or wake up pin. */

    digital_in_t int_pin;           /**< Interrupt pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    smartdof4_drv_t drv_sel;        /**< Master driver interface selector. */

    uint8_t cmd_seq_num;            /**< Command sequence number. */
    uint8_t ch_seq_num[ 6 ];        /**< Write channel sequence number. */
    smartdof4_shtp_t shtp;          /**< SHTP read packet object. */

} smartdof4_t;

/**
 * @brief Smart DOF 4 Click configuration object.
 * @details Configuration object definition of Smart DOF 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t wup;                 /**< Protocol select pin 0 or wake up pin. */
    pin_name_t int_pin;             /**< Interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    smartdof4_drv_t drv_sel;        /**< Master driver interface selector. */

} smartdof4_cfg_t;

/**
 * @brief Smart DOF 4 Click sensor feature object.
 * @details Sensor feature object definition of Smart DOF 4 Click driver.
 */
typedef struct
{
    uint8_t rep_id;                 /**< Feature Report ID. */
    uint8_t flags;                  /**< Feature flags. */
    uint16_t change_sens;           /**< Change sensitivity. */
    uint32_t rep_interval_us;       /**< Report interval in microseconds. */
    uint32_t batch_interval_us;     /**< Batch interval in microseconds. */
    uint32_t sensor_spec;           /**< Sensor-Specific configuration word. */

} smartdof4_feature_t;

/**
 * @brief Smart DOF 4 Click data axis object.
 * @details Data axis object definition of Smart DOF 4 Click driver.
 */
typedef struct
{
    float x;                        /**< X-axis data. */
    float y;                        /**< Y-axis data. */
    float z;                        /**< Z-axis data. */

} smartdof4_axis_t;

/**
 * @brief Smart DOF 4 Click product ID object.
 * @details Product ID object definition of Smart DOF 4 Click driver.
 */
typedef struct
{
    uint8_t reset_cause;            /**< The last cause of the processor reset. */
    uint8_t sw_ver_major;           /**< Software version major (8 bits). */
    uint8_t sw_ver_minor;           /**< Software version minor (8 bits). */
    uint32_t sw_part_num;           /**< 32-bit value representing the software part number. */
    uint32_t sw_build_num;          /**< 32-bit software build number. */
    uint16_t sw_ver_patch;          /**< Software version patch (16 bits). */

} smartdof4_pid_t;

/**
 * @brief Smart DOF 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTDOF4_OK = 0,
    SMARTDOF4_ERROR = -1

} smartdof4_return_value_t;

/*!
 * @addtogroup smartdof4 Smart DOF 4 Click Driver
 * @brief API for configuring and manipulating Smart DOF 4 Click driver.
 * @{
 */

/**
 * @brief Smart DOF 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartdof4_cfg_setup ( smartdof4_cfg_t *cfg );

/**
 * @brief Smart DOF 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #smartdof4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void smartdof4_drv_interface_sel ( smartdof4_cfg_t *cfg, smartdof4_drv_t drv_sel );

/**
 * @brief Smart DOF 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartdof4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_init ( smartdof4_t *ctx, smartdof4_cfg_t *cfg );

/**
 * @brief Smart DOF 4 default configuration function.
 * @details This function executes a default configuration of Smart DOF 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartdof4_default_cfg ( smartdof4_t *ctx );

/**
 * @brief Smart DOF 4 send packet function.
 * @details This function forms a SHTP packet and sends it over the serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] ch_num : Channel number [0-5].
 * @param[in] payload : Data payload buffer.
 * @param[in] len : Number of payload bytes to be written (up to 128).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_send_packet ( smartdof4_t *ctx, uint8_t ch_num, uint8_t *payload, uint16_t len );

/**
 * @brief Smart DOF 4 read packet function.
 * @details This function waits for a data ready indication from INT pin, then reads 
 * the received SHTP packet and stores it in the ctx->shtp.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_read_packet ( smartdof4_t *ctx );

/**
 * @brief Smart DOF 4 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void smartdof4_set_rst_pin ( smartdof4_t *ctx, uint8_t state );

/**
 * @brief Smart DOF 4 set wup pin function.
 * @details This function sets the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void smartdof4_set_wup_pin ( smartdof4_t *ctx, uint8_t state );

/**
 * @brief Smart DOF 4 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t smartdof4_get_int_pin ( smartdof4_t *ctx );

/**
 * @brief Smart DOF 4 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartdof4_reset_device ( smartdof4_t *ctx );

/**
 * @brief Smart DOF 4 wait ready function.
 * @details This function waits a desired period for a data ready indication from INT pin.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] timeout_ms : Wait timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_wait_ready ( smartdof4_t *ctx, uint16_t timeout_ms );

/**
 * @brief Smart DOF 4 read pid function.
 * @details This function reads the product ID information.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[out] pid : Product ID information read.
 * See #smartdof4_pid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_read_pid ( smartdof4_t *ctx, smartdof4_pid_t *pid );

/**
 * @brief Smart DOF 4 frs wr req function.
 * @details This function sends a FRS write request for the selected FRS record ID and length.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] rec_id : FRS record ID.
 * @param[in] len : Length in 32-bit words of the record to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_frs_wr_req ( smartdof4_t *ctx, uint16_t rec_id, uint16_t len );

/**
 * @brief Smart DOF 4 frs wr data req function.
 * @details This function writes FRS data to the record indicated by a previous write request.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] offset : Offset, in 32-bit words, from the beginning of the record.
 * @param[in] data0_in : 32-bit data 0 word to be written to the FRS record.
 * @param[in] data1_in : 32-bit data 1 word to be written to the FRS record.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_frs_wr_data_req ( smartdof4_t *ctx, uint16_t offset, uint32_t data0_in, uint32_t data1_in );

/**
 * @brief Smart DOF 4 frs wr resp function.
 * @details This function reads the status of a FRS write operation.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[out] offset : Offset, in 32-bit words, from the beginning of the record.
 * @param[out] status : Status/Error byte read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_frs_wr_resp ( smartdof4_t *ctx, uint16_t *offset, uint8_t *status );

/**
 * @brief Smart DOF 4 frs rd req function.
 * @details This function sends a FRS read request for the selected FRS record ID.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] rec_id : FRS record ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_frs_rd_req ( smartdof4_t *ctx, uint16_t rec_id );

/**
 * @brief Smart DOF 4 frs rd resp function.
 * @details This function reads the contents of an FRS record.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[out] offset : Offset, in 32-bit words, from the beginning of the record.
 * @param[out] status : Data Len / Status byte read.
 * @param[out] data0_out : 32-bit data 0 word read from the FRS record.
 * @param[out] data1_out : 32-bit data 1 word read from the FRS record.
 * @param[out] rec_id : FRS record ID read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_frs_rd_resp ( smartdof4_t *ctx, uint16_t *offset, uint8_t *status, 
                              uint32_t *data0_out, uint32_t *data1_out, uint16_t *rec_id );

/**
 * @brief Smart DOF 4 cmd req function.
 * @details This function sends a CMD request with specified command parameters.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] params : 9 bytes command parameters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_cmd_req ( smartdof4_t *ctx, uint8_t cmd, uint8_t *params );

/**
 * @brief Smart DOF 4 cmd resp function.
 * @details This function reads the command response with parameters.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[out] cmd : Command byte.
 * @param[out] params : 11 bytes command parameters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_cmd_resp ( smartdof4_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Smart DOF 4 feature req function.
 * @details This function sends a get feature request for the selected report ID.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] rep_id : Repord ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_feature_req ( smartdof4_t *ctx, uint8_t rep_id );

/**
 * @brief Smart DOF 4 feature set function.
 * @details This function sets a full feature report.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[in] feat : Feature report object.
 * See #smartdof4_feature_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_feature_set ( smartdof4_t *ctx, smartdof4_feature_t *feat );

/**
 * @brief Smart DOF 4 feature resp function.
 * @details This function retrieves a full feature report that was requested.
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[out] feat : Feature report object.
 * See #smartdof4_feature_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_feature_resp ( smartdof4_t *ctx, smartdof4_feature_t *feat );

/**
 * @brief Smart DOF 4 read data function.
 * @details This function reads the accelerometer (g), gyroscope (dps), and magnetometer (uT) 
 * 3-axis data from input report. 
 * @param[in] ctx : Click context object.
 * See #smartdof4_t object definition for detailed explanation.
 * @param[out] accel : Accelerometer data [g].
 * See #smartdof4_axis_t object definition for detailed explanation.
 * @param[out] gyro : Gyroscope data [dps].
 * See #smartdof4_axis_t object definition for detailed explanation.
 * @param[out] mag : Magnetometer data [uT].
 * See #smartdof4_axis_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof4_read_data ( smartdof4_t *ctx, smartdof4_axis_t *accel, 
                            smartdof4_axis_t *gyro, smartdof4_axis_t *mag );

#ifdef __cplusplus
}
#endif
#endif // SMARTDOF4_H

/*! @} */ // smartdof4

// ------------------------------------------------------------------------ END

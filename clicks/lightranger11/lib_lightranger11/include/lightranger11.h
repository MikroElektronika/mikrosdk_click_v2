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
 * @file lightranger11.h
 * @brief This file contains API for LightRanger 11 Click Driver.
 */

#ifndef LIGHTRANGER11_H
#define LIGHTRANGER11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup lightranger11 LightRanger 11 Click Driver
 * @brief API for configuring and manipulating LightRanger 11 Click driver.
 * @{
 */

/**
 * @defgroup lightranger11_reg LightRanger 11 Registers List
 * @brief List of registers of LightRanger 11 Click driver.
 */

/**
 * @addtogroup lightranger11_reg
 * @{
 */

/**
 * @brief LightRanger 11 description register.
 * @details Specified register for description of LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_DCI_ZONE_CONFIG             0x5450
#define LIGHTRANGER11_DCI_FREQ_HZ                 0x5458
#define LIGHTRANGER11_DCI_INT_TIME                0x545C
#define LIGHTRANGER11_DCI_FW_NB_TARGET            0x5478
#define LIGHTRANGER11_DCI_RANGING_MODE            0xAD30
#define LIGHTRANGER11_DCI_DSS_CONFIG              0xAD38
#define LIGHTRANGER11_DCI_TARGET_ORDER            0xAE64
#define LIGHTRANGER11_DCI_SHARPENER               0xAED8
#define LIGHTRANGER11_DCI_INTERNAL_CP             0xB39C
#define LIGHTRANGER11_DCI_MOTION_DETECTOR_CFG     0xBFAC
#define LIGHTRANGER11_DCI_SINGLE_RANGE            0xCD5C
#define LIGHTRANGER11_DCI_OUTPUT_CONFIG           0xCD60
#define LIGHTRANGER11_DCI_OUTPUT_ENABLES          0xCD68
#define LIGHTRANGER11_DCI_OUTPUT_LIST             0xCD78
#define LIGHTRANGER11_DCI_PIPE_CONTROL            0xCF78

/**
 * @brief LightRanger 11 UI commands list.
 * @details Specified UI commands list of LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_UI_CMD_STATUS               0x2C00
#define LIGHTRANGER11_UI_CMD_START                0x2C04
#define LIGHTRANGER11_UI_CMD_END                  0x2FFF

/*! @} */ // lightranger11_reg

/**
 * @defgroup lightranger11_set LightRanger 11 Registers Settings
 * @brief Settings for registers of LightRanger 11 Click driver.
 */

/**
 * @addtogroup lightranger11_set
 * @{
 */

/**
 * @brief LightRanger 11 buffers size setting.
 * @details Specified buffers size setting of LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_TEMP_BUFFER_SIZE            1024
#define LIGHTRANGER11_NVM_DATA_SIZE               492
#define LIGHTRANGER11_OFFSET_BUFFER_SIZE          488
#define LIGHTRANGER11_XTALK_BUFFER_SIZE           776

/**
 * @brief LightRanger 11 resolution setting.
 * @details Specified resolution setting of LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_RESOLUTION_4X4              16
#define LIGHTRANGER11_RESOLUTION_8X8              64

/**
 * @brief LightRanger 11 ranging mode setting.
 * @details Specified resolution setting of LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_RANGING_MODE_CONTINUOUS     1
#define LIGHTRANGER11_RANGING_MODE_AUTONOMOUS     3

/**
 * @brief LightRanger 11 range results block headers setting.
 * @details Specified range results block headers setting of LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_START_BH                    0x0000000Dul
#define LIGHTRANGER11_METADATA_BH                 0x54B400C0ul
#define LIGHTRANGER11_COMMONDATA_BH               0x54C00040ul
#define LIGHTRANGER11_AMBIENT_RATE_BH             0x54D00104ul
#define LIGHTRANGER11_SPAD_COUNT_BH               0x55D00404ul
#define LIGHTRANGER11_NB_TARGET_DETECTED_BH       0xCF7C0401ul
#define LIGHTRANGER11_SIGNAL_RATE_BH              0xCFBC0404ul
#define LIGHTRANGER11_RANGE_SIGMA_MM_BH           0xD2BC0402ul
#define LIGHTRANGER11_DISTANCE_BH                 0xD33C0402ul
#define LIGHTRANGER11_REFLECTANCE_BH              0xD43C0401ul
#define LIGHTRANGER11_TARGET_STATUS_BH            0xD47C0401ul
#define LIGHTRANGER11_MOTION_DETECT_BH            0xCC5008C0ul
#define LIGHTRANGER11_METADATA_IDX                0x54B4
#define LIGHTRANGER11_SPAD_COUNT_IDX              0x55D0
#define LIGHTRANGER11_AMBIENT_RATE_IDX            0x54D0
#define LIGHTRANGER11_NB_TARGET_DETECTED_IDX      0xCF7C
#define LIGHTRANGER11_SIGNAL_RATE_IDX             0xCFBC
#define LIGHTRANGER11_RANGE_SIGMA_MM_IDX          0xD2BC
#define LIGHTRANGER11_DISTANCE_IDX                0xD33C
#define LIGHTRANGER11_REFLECTANCE_EST_PC_IDX      0xD43C
#define LIGHTRANGER11_TARGET_STATUS_IDX           0xD47C
#define LIGHTRANGER11_MOTION_DETEC_IDX            0xCC50

/**
 * @brief LightRanger 11 default settings.
 * @details Specified default settings of LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_DEF_RESOLUTION              LIGHTRANGER11_RESOLUTION_8X8
#define LIGHTRANGER11_DEF_RANGING_FREQ_HZ         2
#define LIGHTRANGER11_DEF_RANGING_MODE            LIGHTRANGER11_RANGING_MODE_AUTONOMOUS
#define LIGHTRANGER11_DEF_INTEGRATION_TIME_MS     20

/**
 * @brief LightRanger 11 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 11 Click driver.
 */
#define LIGHTRANGER11_DEVICE_ADDRESS              0x29

/*! @} */ // lightranger11_set

/**
 * @defgroup lightranger11_map LightRanger 11 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 11 Click driver.
 */

/**
 * @addtogroup lightranger11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 11 Click to the selected MikroBUS.
 */
#define LIGHTRANGER11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.rsc = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.lp = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger11_map
/*! @} */ // lightranger11

/**
 * @brief LightRanger 11 Click context object.
 * @details Context object definition of LightRanger 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rsc;        /**< I2C interface reset pin. */
    digital_out_t lp;         /**< Comms enable pin. */

    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    
    /**< Results stream count, value auto-incremented at each range. */
    uint8_t stream_count;
    /**< Size of data read though I2C. */
    uint32_t data_read_size;
    /**< Offset buffer. */
    uint8_t offset_data[ LIGHTRANGER11_OFFSET_BUFFER_SIZE ];
    /**< Temporary buffer used for internal driver processing. */
    uint8_t temp_buf[ LIGHTRANGER11_TEMP_BUFFER_SIZE ];

} lightranger11_t;

/**
 * @brief LightRanger 11 Click configuration object.
 * @details Configuration object definition of LightRanger 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rsc;             /**< I2C interface reset pin. */
    pin_name_t lp;              /**< Comms enable pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} lightranger11_cfg_t;

/**
 * @brief LightRanger 11 Click block header union data definition.
 * @details Block header union data definition of LightRanger 11 Click driver.
 */
typedef struct
{
    /**< Internal sensor silicon temperature. */
    int8_t silicon_temp_degc;

    /**< Number of valid target detected for 1 zone. */
    uint8_t nb_target_detected[ 64 ];

    /**< Measured distance in mm. */
    int16_t distance_mm[ 64 ];

    /**< Status indicating the measurement validity (5 & 9 means ranging OK). */
    uint8_t target_status[ 64 ];

} lightranger11_results_data_t;

/**
 * @brief LightRanger 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTRANGER11_OK = 0,
    LIGHTRANGER11_ERROR = -1

} lightranger11_return_value_t;

/**
 * @brief LightRanger 11 Click block header union data definition.
 * @details Block header union data definition of LightRanger 11 Click driver.
 */
typedef union 
{
    uint32_t bytes;
    struct 
    {
        uint32_t type : 4;
        uint32_t size : 12;
        uint32_t idx : 16;
    };
} lightranger11_block_header_t;

/*!
 * @addtogroup lightranger11 LightRanger 11 Click Driver
 * @brief API for configuring and manipulating LightRanger 11 Click driver.
 * @{
 */

/**
 * @brief LightRanger 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger11_cfg_setup ( lightranger11_cfg_t *cfg );

/**
 * @brief LightRanger 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_init ( lightranger11_t *ctx, lightranger11_cfg_t *cfg );

/**
 * @brief LightRanger 11 default configuration function.
 * @details This function executes a default configuration of LightRanger 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lightranger11_default_cfg ( lightranger11_t *ctx );

/**
 * @brief LightRanger 11  write multi function.
 * @details This function writes a desired number of data bytes to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 16 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_write_multi ( lightranger11_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 11 read multi function.
 * @details This function reads a desired number of data bytes from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_read_multi ( lightranger11_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief LightRanger 11 write byte function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_write_byte ( lightranger11_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief LightRanger 11 read byte function.
 * @details This function reads data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_read_byte ( lightranger11_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief LightRanger 11 write data function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_write_data ( lightranger11_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LightRanger 11 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_check_comm ( lightranger11_t *ctx );

/**
 * @brief LightRanger 11 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lightranger11_get_int_pin ( lightranger11_t *ctx );

/**
 * @brief LightRanger 11 set i2c rst function.
 * @details This function sets the I2C RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lightranger11_set_i2c_rst_pin ( lightranger11_t *ctx, uint8_t state );

/**
 * @brief LightRanger 11 set lpn function.
 * @details This function sets the LPn pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lightranger11_set_lpn_pin ( lightranger11_t *ctx, uint8_t state );

/**
 * @brief LightRanger 11 reset i2c function.
 * @details This function resets the I2C communication by toggling the I2C RST pin.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger11_reset_i2c ( lightranger11_t *ctx );

/**
 * @brief LightRanger 11 sensor init function.
 * @details This function initializes the sensor. It must be called after a power on, 
 * to load the firmware into the sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_sensor_init ( lightranger11_t *ctx );

/**
 * @brief LightRanger 11 dci write data function.
 * @details This function writes 'extra data' to DCI. The data can be simple data, or casted structure.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] index : DCI register address. 
 * @param[in] data_in : This field can be a casted structure, or a simple array. Please note that the FW only
 * accept data of 32 bits. So field data can only have a size of 32, 64, 96, 128, bits..
 * @param[in] data_size : This field must be the structure or array size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_dci_write_data ( lightranger11_t *ctx, uint16_t index, 
                                                           uint8_t *data_in, 
                                                           uint16_t data_size );

/**
 * @brief LightRanger 11 dci read data function.
 * @details This function reads 'extra data' from DCI. Using a known index, the function fills the
 * casted structure passed in argument.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] index : DCI register address. 
 * @param[out] data_out : This field can be a casted structure,
 * or a simple array. Please note that the FW only
 * accept data of 32 bits. So field data can only have a size of 32, 64, 96, 128, bits..
 * @param[in] data_size : This field must be the structure or array size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_dci_read_data ( lightranger11_t *ctx, uint16_t index, 
                                                          uint8_t *data_out, 
                                                          uint16_t data_size );

/**
 * @brief LightRanger 11 dci replace data function.
 * @details This function replaces 'extra data' in DCI. The data can be simple data, or casted structure.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] index : DCI register address. 
 * @param[in] data_in : This field can be a casted structure, or a simple array. Please note that the FW only
 * accept data of 32 bits. So field data can only have a size of 32, 64, 96, 128, bits..
 * @param[in] data_size : This field must be the structure or array size.
 * @param[in] new_data : Contains the new fields.
 * @param[in] new_data_size : New data size.
 * @param[in] new_data_pos : New data position into the buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_dci_replace_data ( lightranger11_t *ctx, uint16_t index, uint8_t *data_in, 
                                                             uint16_t data_size, uint8_t *new_data, 
                                                             uint16_t new_data_size, uint16_t new_data_pos );

/**
 * @brief LightRanger 11 set resolution function.
 * @details This function sets a new data resolution (4x4 or 8x8).
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] resolution : Use macro LIGHTRANGER11_RESOLUTION_4X4 
 * or LIGHTRANGER11_RESOLUTION_8X8 to set the resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_set_resolution ( lightranger11_t *ctx, uint8_t resolution );

/**
 * @brief LightRanger 11 get resolution function.
 * @details This function gets the current resolution (4x4 or 8x8).
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[out] resolution : Value of this pointer will be equal to 16 for 4x4 mode, and 64 for 8x8 mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_get_resolution ( lightranger11_t *ctx, uint8_t *resolution );

/**
 * @brief LightRanger 11 set ranging frequency hz function.
 * @details This function sets a new ranging frequency in Hz. 
 * Ranging frequency corresponds to the measurements 
 * frequency. This setting depends of the resolution, 
 * so please select your resolution before using this function.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] frequency_hz : Contains the ranging frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For 4x4, min and max allowed values are : [1;60] - For 8x8, min and max allowed values are : [1;15].
 */
err_t lightranger11_set_rang_freq_hz ( lightranger11_t *ctx, uint8_t frequency_hz );

/**
 * @brief LightRanger 11 get ranging frequency hz function.
 * @details This function gets the current ranging frequency in Hz. Ranging frequency corresponds to 
 * the time between each measurement.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[out] frequency_hz : Contains the ranging frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_get_rang_freq_hz ( lightranger11_t *ctx, uint8_t *frequency_hz );

/**
 * @brief LightRanger 11 set integration time ms function.
 * @details This function sets a new integration time in ms. 
 * Integration time must be computed to be lower than 
 * the ranging period, for a selected resolution.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] integration_time_ms : Contains the integration time in ms. For all resolutions and frequency, 
 * the minimum value is 2ms, and the maximum is 1000ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function has no impact on ranging mode continous.
 */
err_t lightranger11_set_integ_time_ms ( lightranger11_t *ctx, uint32_t integration_time_ms );

/**
 * @brief LightRanger 11 get integration time ms function.
 * @details This function gets the current integration time in ms.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[out] integration_time_ms : Contains integration time in ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_get_integ_time_ms ( lightranger11_t *ctx, uint32_t *integration_time_ms );

/**
 * @brief LightRanger 11 set ranging mode function.
 * @details This function sets the ranging mode. Two modes are available using ULD : 
 * Continuous and autonomous. 
 * The default mode is Autonomous.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[in] ranging_mode : Use macros 
 * LIGHTRANGER11_RANGING_MODE_CONTINUOUS, LIGHTRANGER11_RANGING_MODE_CONTINUOUS.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_set_ranging_mode ( lightranger11_t *ctx, uint8_t ranging_mode );

/**
 * @brief LightRanger 11 get ranging mode function.
 * @details This function gets the ranging mode. Two modes are available using ULD : 
 * Continuous and autonomous. 
 * The default mode is Autonomous.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[out] ranging_mode : Current ranging mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_get_ranging_mode ( lightranger11_t *ctx, uint8_t *ranging_mode );

/**
 * @brief LightRanger 11 start ranging function.
 * @details This function starts a ranging session. 
 * When the sensor streams, host cannot change settings 'on-the-fly'.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_start_ranging ( lightranger11_t *ctx );

/**
 * @brief LightRanger 11 stop ranging function.
 * @details This function stops the ranging session. It must be used when the sensor streams, 
 * after calling lightranger11_start_ranging( ).
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_stop_ranging ( lightranger11_t *ctx );

/**
 * @brief LightRanger 11 get ranging data function.
 * @details This function gets the ranging data, using the selected output and the resolution.
 * @param[in] ctx : Click context object.
 * See #lightranger11_t object definition for detailed explanation.
 * @param[out] results : LightRanger 11 results structure.
 * See #lightranger11_results_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger11_get_ranging_data ( lightranger11_t *ctx, lightranger11_results_data_t *results );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER11_H

/*! @} */ // lightranger11

// ------------------------------------------------------------------------ END

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
 * @file proximity16.h
 * @brief This file contains API for Proximity 16 Click Driver.
 */

#ifndef PROXIMITY16_H
#define PROXIMITY16_H

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
 * @addtogroup proximity16 Proximity 16 Click Driver
 * @brief API for configuring and manipulating Proximity 16 Click driver.
 * @{
 */

/**
 * @defgroup proximity16_reg Proximity 16 Registers List
 * @brief List of registers of Proximity 16 Click driver.
 */

/**
 * @addtogroup proximity16_reg
 * @{
 */

/**
 * @brief Proximity 16 DCI registers list.
 * @details Specified DCI registers list of Proximity 16 Click driver.
 */
#define PROXIMITY16_DCI_ZONE_CONFIG             0x5450
#define PROXIMITY16_DCI_FREQ_HZ                 0x5458
#define PROXIMITY16_DCI_INT_TIME                0x545C
#define PROXIMITY16_DCI_FW_NB_TARGET            0x5478
#define PROXIMITY16_DCI_RANGING_MODE            0xAD30
#define PROXIMITY16_DCI_DSS_CONFIG              0xAD38
#define PROXIMITY16_DCI_TARGET_ORDER            0xAE64
#define PROXIMITY16_DCI_SHARPENER               0xAED8
#define PROXIMITY16_DCI_INTERNAL_CP             0xB39C
#define PROXIMITY16_DCI_MOTION_DETECTOR_CFG     0xBFAC
#define PROXIMITY16_DCI_SINGLE_RANGE            0xCD5C
#define PROXIMITY16_DCI_OUTPUT_CONFIG           0xCD60
#define PROXIMITY16_DCI_OUTPUT_ENABLES          0xCD68
#define PROXIMITY16_DCI_OUTPUT_LIST             0xCD78
#define PROXIMITY16_DCI_PIPE_CONTROL            0xCF78

/**
 * @brief Proximity 16 UI commands list.
 * @details Specified UI commands list of Proximity 16 Click driver.
 */
#define PROXIMITY16_UI_CMD_STATUS               0x2C00
#define PROXIMITY16_UI_CMD_START                0x2C04
#define PROXIMITY16_UI_CMD_END                  0x2FFF

/*! @} */ // proximity16_reg

/**
 * @defgroup proximity16_set Proximity 16 Registers Settings
 * @brief Settings for registers of Proximity 16 Click driver.
 */

/**
 * @addtogroup proximity16_set
 * @{
 */

/**
 * @brief Proximity 16 buffers size setting.
 * @details Specified buffers size setting of Proximity 16 Click driver.
 */
#define PROXIMITY16_TEMP_BUFFER_SIZE            1024
#define PROXIMITY16_NVM_DATA_SIZE               492
#define PROXIMITY16_OFFSET_BUFFER_SIZE          488
#define PROXIMITY16_XTALK_BUFFER_SIZE           776

/**
 * @brief Proximity 16 resolution setting.
 * @details Specified resolution setting of Proximity 16 Click driver.
 */
#define PROXIMITY16_RESOLUTION_4X4              16
#define PROXIMITY16_RESOLUTION_8X8              64

/**
 * @brief Proximity 16 ranging mode setting.
 * @details Specified resolution setting of Proximity 16 Click driver.
 */
#define PROXIMITY16_RANGING_MODE_CONTINUOUS     1
#define PROXIMITY16_RANGING_MODE_AUTONOMOUS     3

/**
 * @brief Proximity 16 range results block headers setting.
 * @details Specified range results block headers setting of Proximity 16 Click driver.
 */
#define PROXIMITY16_START_BH                    0x0000000Dul
#define PROXIMITY16_METADATA_BH                 0x54B400C0ul
#define PROXIMITY16_COMMONDATA_BH               0x54C00040ul
#define PROXIMITY16_AMBIENT_RATE_BH             0x54D00104ul
#define PROXIMITY16_SPAD_COUNT_BH               0x55D00404ul
#define PROXIMITY16_NB_TARGET_DETECTED_BH       0xCF7C0401ul
#define PROXIMITY16_SIGNAL_RATE_BH              0xCFBC0404ul
#define PROXIMITY16_RANGE_SIGMA_MM_BH           0xD2BC0402ul
#define PROXIMITY16_DISTANCE_BH                 0xD33C0402ul
#define PROXIMITY16_REFLECTANCE_BH              0xD43C0401ul
#define PROXIMITY16_TARGET_STATUS_BH            0xD47C0401ul
#define PROXIMITY16_MOTION_DETECT_BH            0xCC5008C0ul
#define PROXIMITY16_METADATA_IDX                0x54B4
#define PROXIMITY16_SPAD_COUNT_IDX              0x55D0
#define PROXIMITY16_AMBIENT_RATE_IDX            0x54D0
#define PROXIMITY16_NB_TARGET_DETECTED_IDX      0xCF7C
#define PROXIMITY16_SIGNAL_RATE_IDX             0xCFBC
#define PROXIMITY16_RANGE_SIGMA_MM_IDX          0xD2BC
#define PROXIMITY16_DISTANCE_IDX                0xD33C
#define PROXIMITY16_REFLECTANCE_EST_PC_IDX      0xD43C
#define PROXIMITY16_TARGET_STATUS_IDX           0xD47C
#define PROXIMITY16_MOTION_DETEC_IDX            0xCC50

/**
 * @brief Proximity 16 default settings.
 * @details Specified default settings of Proximity 16 Click driver.
 */
#define PROXIMITY16_DEF_RESOLUTION              PROXIMITY16_RESOLUTION_8X8
#define PROXIMITY16_DEF_RANGING_FREQ_HZ         2
#define PROXIMITY16_DEF_RANGING_MODE            PROXIMITY16_RANGING_MODE_AUTONOMOUS
#define PROXIMITY16_DEF_INTEGRATION_TIME_MS     20

/**
 * @brief Proximity 16 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 16 Click driver.
 */
#define PROXIMITY16_DEVICE_ADDRESS              0x29

/*! @} */ // proximity16_set

/**
 * @defgroup proximity16_map Proximity 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 16 Click driver.
 */

/**
 * @addtogroup proximity16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 16 Click to the selected MikroBUS.
 */
#define PROXIMITY16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.i2c_rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.lpn = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity16_map
/*! @} */ // proximity16

/**
 * @brief Proximity 16 Click context object.
 * @details Context object definition of Proximity 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t i2c_rst;      /**< I2C interface reset pin, active high. */
    digital_out_t lpn;          /**< LP mode communication enable pin, active high. */

    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    /**< Results stream count, value auto-incremented at each range. */
    uint8_t stream_count;
    /**< Size of data read though I2C. */
    uint32_t data_read_size;
    /**< Offset buffer. */
    uint8_t offset_data[ PROXIMITY16_OFFSET_BUFFER_SIZE ];
    /**< Temporary buffer used for internal driver processing. */
    uint8_t temp_buf[ PROXIMITY16_TEMP_BUFFER_SIZE ];

} proximity16_t;

/**
 * @brief Proximity 16 Click configuration object.
 * @details Configuration object definition of Proximity 16 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t i2c_rst;         /**< I2C interface reset pin, active high. */
    pin_name_t lpn;             /**< LP mode communication enable pin, active high. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} proximity16_cfg_t;

/**
 * @brief Proximity 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY16_OK = 0,
    PROXIMITY16_ERROR = -1

} proximity16_return_value_t;

/**
 * @brief Proximity 16 Click results data structure.
 * @details Results data structure object definition of Proximity 16 Click driver.
 */
typedef struct
{
    /**< Internal sensor silicon temperature. */
    int8_t silicon_temp_degc;

    /**< Number of valid target detected for 1 zone. */
    uint8_t nb_target_detected[ PROXIMITY16_RESOLUTION_8X8 ];

    /**< Measured distance in mm. */
    int16_t distance_mm[ PROXIMITY16_RESOLUTION_8X8 ];

    /**< Status indicating the measurement validity (5 & 9 means ranging OK). */
    uint8_t target_status[ PROXIMITY16_RESOLUTION_8X8 ];

} proximity16_results_data_t;

/**
 * @brief Proximity 16 Click block header union data definition.
 * @details Block header union data definition of Proximity 16 Click driver.
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
} proximity16_block_header_t;

/*!
 * @addtogroup proximity16 Proximity 16 Click Driver
 * @brief API for configuring and manipulating Proximity 16 Click driver.
 * @{
 */

/**
 * @brief Proximity 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity16_cfg_setup ( proximity16_cfg_t *cfg );

/**
 * @brief Proximity 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_init ( proximity16_t *ctx, proximity16_cfg_t *cfg );

/**
 * @brief Proximity 16 default configuration function.
 * @details This function executes a default configuration of Proximity 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity16_default_cfg ( proximity16_t *ctx );

/**
 * @brief Proximity 16 write multi function.
 * @details This function writes a desired number of data bytes to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 16 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_write_multi ( proximity16_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Proximity 16 read multi function.
 * @details This function reads a desired number of data bytes from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_read_multi ( proximity16_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief Proximity 16 write byte function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_write_byte ( proximity16_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief Proximity 16 read byte function.
 * @details This function reads data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_read_byte ( proximity16_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief Proximity 16 write data function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_write_data ( proximity16_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Proximity 16 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_check_communication ( proximity16_t *ctx );

/**
 * @brief Proximity 16 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity16_get_int_pin ( proximity16_t *ctx );

/**
 * @brief Proximity 16 set i2c rst function.
 * @details This function sets the I2C RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proximity16_set_i2c_rst_pin ( proximity16_t *ctx, uint8_t state );

/**
 * @brief Proximity 16 set lpn function.
 * @details This function sets the LPn pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proximity16_set_lpn_pin ( proximity16_t *ctx, uint8_t state );

/**
 * @brief Proximity 16 reset i2c function.
 * @details This function resets the I2C communication by toggling the I2C RST pin.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity16_reset_i2c ( proximity16_t *ctx );

/**
 * @brief Proximity 16 sensor init function.
 * @details This function initializes the sensor. It must be called after a power on, 
 * to load the firmware into the sensor.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_sensor_init ( proximity16_t *ctx );

/**
 * @brief Proximity 16 dci write data function.
 * @details This function writes 'extra data' to DCI. The data can be simple data, or casted structure.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] index : DCI register address. 
 * @param[in] data_in : This field can be a casted structure, or a simple array. Please note that the FW only
 * accept data of 32 bits. So field data can only have a size of 32, 64, 96, 128, bits..
 * @param[in] data_size : This field must be the structure or array size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_dci_write_data ( proximity16_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size );

/**
 * @brief Proximity 16 dci read data function.
 * @details This function reads 'extra data' from DCI. Using a known index, the function fills the
 * casted structure passed in argument.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] index : DCI register address. 
 * @param[out] data_out : This field can be a casted structure, or a simple array. Please note that the FW only
 * accept data of 32 bits. So field data can only have a size of 32, 64, 96, 128, bits..
 * @param[in] data_size : This field must be the structure or array size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_dci_read_data ( proximity16_t *ctx, uint16_t index, uint8_t *data_out, uint16_t data_size );

/**
 * @brief Proximity 16 dci replace data function.
 * @details This function replaces 'extra data' in DCI. The data can be simple data, or casted structure.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
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
err_t proximity16_dci_replace_data ( proximity16_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size, 
                                     uint8_t *new_data, uint16_t new_data_size, uint16_t new_data_pos );

/**
 * @brief Proximity 16 set resolution function.
 * @details This function sets a new data resolution (4x4 or 8x8).
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] resolution : Use macro PROXIMITY16_RESOLUTION_4X4 or PROXIMITY16_RESOLUTION_8X8 to set the resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_set_resolution ( proximity16_t *ctx, uint8_t resolution );

/**
 * @brief Proximity 16 get resolution function.
 * @details This function gets the current resolution (4x4 or 8x8).
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[out] resolution : Value of this pointer will be equal to 16 for 4x4 mode, and 64 for 8x8 mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_get_resolution ( proximity16_t *ctx, uint8_t *resolution );

/**
 * @brief Proximity 16 set ranging frequency hz function.
 * @details This function sets a new ranging frequency in Hz. Ranging frequency corresponds to the measurements 
 * frequency. This setting depends of the resolution, so please select your resolution before using this function.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] frequency_hz : Contains the ranging frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For 4x4, min and max allowed values are : [1;60] - For 8x8, min and max allowed values are : [1;15].
 */
err_t proximity16_set_ranging_frequency_hz ( proximity16_t *ctx, uint8_t frequency_hz );

/**
 * @brief Proximity 16 get ranging frequency hz function.
 * @details This function gets the current ranging frequency in Hz. Ranging frequency corresponds to 
 * the time between each measurement.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[out] frequency_hz : Contains the ranging frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_get_ranging_frequency_hz ( proximity16_t *ctx, uint8_t *frequency_hz );

/**
 * @brief Proximity 16 set integration time ms function.
 * @details This function sets a new integration time in ms. Integration time must be computed to be lower than 
 * the ranging period, for a selected resolution.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] integration_time_ms : Contains the integration time in ms. For all resolutions and frequency, 
 * the minimum value is 2ms, and the maximum is 1000ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function has no impact on ranging mode continous.
 */
err_t proximity16_set_integration_time_ms ( proximity16_t *ctx, uint32_t integration_time_ms );

/**
 * @brief Proximity 16 get integration time ms function.
 * @details This function gets the current integration time in ms.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[out] integration_time_ms : Contains integration time in ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_get_integration_time_ms ( proximity16_t *ctx, uint32_t *integration_time_ms );

/**
 * @brief Proximity 16 set ranging mode function.
 * @details This function sets the ranging mode. Two modes are available using ULD : Continuous and autonomous. 
 * The default mode is Autonomous.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] ranging_mode : Use macros PROXIMITY16_RANGING_MODE_CONTINUOUS, PROXIMITY16_RANGING_MODE_CONTINUOUS.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_set_ranging_mode ( proximity16_t *ctx, uint8_t ranging_mode );

/**
 * @brief Proximity 16 get ranging mode function.
 * @details This function gets the ranging mode. Two modes are available using ULD : Continuous and autonomous. 
 * The default mode is Autonomous.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[out] ranging_mode : Current ranging mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_get_ranging_mode ( proximity16_t *ctx, uint8_t *ranging_mode );

/**
 * @brief Proximity 16 start ranging function.
 * @details This function starts a ranging session. When the sensor streams, host cannot change settings 'on-the-fly'.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_start_ranging ( proximity16_t *ctx );

/**
 * @brief Proximity 16 stop ranging function.
 * @details This function stops the ranging session. It must be used when the sensor streams, 
 * after calling proximity16_start_ranging( ).
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_stop_ranging ( proximity16_t *ctx );

/**
 * @brief Proximity 16 get ranging data function.
 * @details This function gets the ranging data, using the selected output and the resolution.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[out] results : Proximity 16 results structure.
 * See #proximity16_results_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity16_get_ranging_data ( proximity16_t *ctx, proximity16_results_data_t *results );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY16_H

/*! @} */ // proximity16

// ------------------------------------------------------------------------ END

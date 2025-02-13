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
 * @file lightranger12.h
 * @brief This file contains API for LightRanger 12 Click Driver.
 */

#ifndef LIGHTRANGER12_H
#define LIGHTRANGER12_H

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
 * @addtogroup lightranger12 LightRanger 12 Click Driver
 * @brief API for configuring and manipulating LightRanger 12 Click driver.
 * @{
 */

/**
 * @defgroup lightranger12_reg LightRanger 12 Registers List
 * @brief List of registers of LightRanger 12 Click driver.
 */

/**
 * @addtogroup lightranger12_reg
 * @{
 */

/**
 * @brief LightRanger 12 DCI registers list.
 * @details Specified DCI registers list of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_DCI_ZONE_CONFIG               0x5450
#define LIGHTRANGER12_DCI_FREQ_HZ                   0x5458
#define LIGHTRANGER12_DCI_INT_TIME                  0x545C
#define LIGHTRANGER12_DCI_FW_NB_TARGET              0x5478
#define LIGHTRANGER12_DCI_RANGING_MODE              0xAD30
#define LIGHTRANGER12_DCI_DSS_CONFIG                0xAD38
#define LIGHTRANGER12_DCI_TARGET_ORDER              0xAE64
#define LIGHTRANGER12_DCI_SHARPENER                 0xAED8
#define LIGHTRANGER12_DCI_INTERNAL_CP               0xB39C
#define LIGHTRANGER12_DCI_SYNC_PIN			        0xB5F0
#define LIGHTRANGER12_DCI_MOTION_DETECTOR_CFG       0xBFAC
#define LIGHTRANGER12_DCI_SINGLE_RANGE              0xD964
#define LIGHTRANGER12_DCI_OUTPUT_CONFIG             0xD968
#define LIGHTRANGER12_DCI_OUTPUT_ENABLES            0xD970
#define LIGHTRANGER12_DCI_OUTPUT_LIST               0xD980
#define LIGHTRANGER12_DCI_PIPE_CONTROL              0xDB80
#define LIGHTRANGER12_DCI_GLARE_FILTER_CFG	        0xE108

/**
 * @brief LightRanger 12 UI commands list.
 * @details Specified UI commands list of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_UI_CMD_STATUS                 0x2C00
#define LIGHTRANGER12_UI_CMD_START                  0x2C04
#define LIGHTRANGER12_UI_CMD_END                    0x2FFF

/*! @} */ // lightranger12_reg

/**
 * @defgroup lightranger12_set LightRanger 12 Registers Settings
 * @brief Settings for registers of LightRanger 12 Click driver.
 */

/**
 * @addtogroup lightranger12_set
 * @{
 */

/**
 * @brief LightRanger 12 buffers size setting.
 * @details Specified buffers size setting of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_TEMP_BUFFER_SIZE              1024
#define LIGHTRANGER12_NVM_DATA_SIZE                 492
#define LIGHTRANGER12_OFFSET_BUFFER_SIZE            488
#define LIGHTRANGER12_XTALK_BUFFER_SIZE             776

/**
 * @brief LightRanger 12 resolution setting.
 * @details Specified resolution setting of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_RESOLUTION_4X4                16
#define LIGHTRANGER12_RESOLUTION_8X8                64

/**
 * @brief LightRanger 12 ranging mode setting.
 * @details Specified resolution setting of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_RANGING_MODE_CONTINUOUS       1
#define LIGHTRANGER12_RANGING_MODE_AUTONOMOUS       3

/**
 * @brief LightRanger 12 range results block headers setting.
 * @details Specified range results block headers setting of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_START_BH                      0x0000000Dul
#define LIGHTRANGER12_METADATA_BH                   0x54B400C0ul
#define LIGHTRANGER12_COMMONDATA_BH                 0x54C00040ul
#define LIGHTRANGER12_AMBIENT_RATE_BH               0x54D00404ul
#define LIGHTRANGER12_SPAD_COUNT_BH                 0x55D00404ul
#define LIGHTRANGER12_MOTION_DETECT_BH              0xD85808C0ul
#define LIGHTRANGER12_NB_TARGET_DETECTED_BH         0xDB840401ul
#define LIGHTRANGER12_SIGNAL_RATE_BH                0xDBC40404ul
#define LIGHTRANGER12_RANGE_SIGMA_MM_BH             0xDEC40402ul
#define LIGHTRANGER12_DISTANCE_BH                   0xDF440402ul
#define LIGHTRANGER12_REFLECTANCE_BH                0xE0440401ul
#define LIGHTRANGER12_TARGET_STATUS_BH              0xE0840401ul
#define LIGHTRANGER12_METADATA_IDX                  0x54B4
#define LIGHTRANGER12_COMMONDATA_IDX                0x54C0
#define LIGHTRANGER12_AMBIENT_RATE_IDX              0x54D0
#define LIGHTRANGER12_SPAD_COUNT_IDX                0x55D0
#define LIGHTRANGER12_MOTION_DETEC_IDX              0xD858
#define LIGHTRANGER12_NB_TARGET_DETECTED_IDX        0xDB84
#define LIGHTRANGER12_SIGNAL_RATE_IDX               0xDBC4
#define LIGHTRANGER12_RANGE_SIGMA_MM_IDX            0xDEC4
#define LIGHTRANGER12_DISTANCE_IDX                  0xDF44
#define LIGHTRANGER12_REFLECTANCE_EST_PC_IDX        0xE044
#define LIGHTRANGER12_TARGET_STATUS_IDX             0xE084

/**
 * @brief LightRanger 12 device ID settings.
 * @details Specified device ID settings of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_DEVICE_ID                     0xF0
#define LIGHTRANGER12_REVISION_ID_L8                0x0C

/**
 * @brief LightRanger 12 default settings.
 * @details Specified default settings of LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_DEF_RESOLUTION                LIGHTRANGER12_RESOLUTION_8X8
#define LIGHTRANGER12_DEF_RANGING_FREQ_HZ           5
#define LIGHTRANGER12_DEF_RANGING_MODE              LIGHTRANGER12_RANGING_MODE_AUTONOMOUS
#define LIGHTRANGER12_DEF_INTEGRATION_TIME_MS       40

/**
 * @brief LightRanger 12 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 12 Click driver.
 */
#define LIGHTRANGER12_DEVICE_ADDRESS                0x29

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b lightranger12_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LIGHTRANGER12_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define LIGHTRANGER12_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // lightranger12_set

/**
 * @defgroup lightranger12_map LightRanger 12 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 12 Click driver.
 */

/**
 * @addtogroup lightranger12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 12 Click to the selected MikroBUS.
 */
#define LIGHTRANGER12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sync = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.lpn  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger12_map
/*! @} */ // lightranger12

/**
 * @brief LightRanger 12 Click driver selector.
 * @details Selects target driver interface of LightRanger 12 Click driver.
 */
typedef enum
{
    LIGHTRANGER12_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    LIGHTRANGER12_DRV_SEL_I2C       /**< I2C driver descriptor. */

} lightranger12_drv_t;

/**
 * @brief LightRanger 12 Click driver interface.
 * @details Definition of driver interface of LightRanger 12 Click driver.
 */
struct lightranger12_s;
typedef err_t ( *lightranger12_master_io_t )( struct lightranger12_s*, uint16_t, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief LightRanger 12 Click context object.
 * @details Context object definition of LightRanger 12 Click driver.
 */
typedef struct lightranger12_s
{
    digital_out_t sync;             /**< External synchronization pin. */
    digital_out_t lpn;              /**< I2C communication enable pin (active high). */

    digital_in_t int_pin;           /**< Interrupt pin (active low). */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    lightranger12_drv_t drv_sel;    /**< Master driver interface selector. */

    lightranger12_master_io_t write_f;  /**< Master write function. */
    lightranger12_master_io_t read_f;   /**< Master read function. */

    uint8_t stream_count;           /**< Results stream count, value auto-incremented at each range. */
    uint32_t data_read_size;        /**< Size of data read though I2C or SPI. */
    uint8_t offset_data[ LIGHTRANGER12_OFFSET_BUFFER_SIZE ];    /**< Offset buffer. */
    uint8_t temp_buf[ LIGHTRANGER12_TEMP_BUFFER_SIZE ]; /**< Temporary buffer used for internal driver processing. */

} lightranger12_t;

/**
 * @brief LightRanger 12 Click configuration object.
 * @details Configuration object definition of LightRanger 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t sync;                /**< External synchronization pin. */
    pin_name_t lpn;                 /**< I2C communication enable pin (active high). */
    pin_name_t int_pin;             /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    lightranger12_drv_t drv_sel;    /**< Master driver interface selector. */

} lightranger12_cfg_t;

/**
 * @brief LightRanger 12 Click results data structure.
 * @details Results data structure object definition of LightRanger 12 Click driver.
 */
typedef struct
{
    /**< Internal sensor silicon temperature. */
    int8_t silicon_temp_degc;

    /**< Number of valid target detected for 1 zone. */
    uint8_t nb_target_detected[ LIGHTRANGER12_RESOLUTION_8X8 ];

    /**< Measured distance in mm. */
    int16_t distance_mm[ LIGHTRANGER12_RESOLUTION_8X8 ];

    /**< Status indicating the measurement validity (5 & 9 means ranging OK). */
    uint8_t target_status[ LIGHTRANGER12_RESOLUTION_8X8 ];

} lightranger12_results_data_t;

/**
 * @brief LightRanger 12 Click block header union data definition.
 * @details Block header union data definition of LightRanger 12 Click driver.
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

} lightranger12_block_header_t;

/**
 * @brief LightRanger 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTRANGER12_OK = 0,
    LIGHTRANGER12_ERROR = -1

} lightranger12_return_value_t;

/*!
 * @addtogroup lightranger12 LightRanger 12 Click Driver
 * @brief API for configuring and manipulating LightRanger 12 Click driver.
 * @{
 */

/**
 * @brief LightRanger 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger12_cfg_setup ( lightranger12_cfg_t *cfg );

/**
 * @brief LightRanger 12 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger12_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #lightranger12_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void lightranger12_drv_interface_sel ( lightranger12_cfg_t *cfg, lightranger12_drv_t drv_sel );

/**
 * @brief LightRanger 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_init ( lightranger12_t *ctx, lightranger12_cfg_t *cfg );

/**
 * @brief LightRanger 12 default configuration function.
 * @details This function executes a default configuration of LightRanger 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lightranger12_default_cfg ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 write multi function.
 * @details This function writes a desired number of data bytes to the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 16 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_write_multi ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief LightRanger 12 read multi function.
 * @details This function reads a desired number of data bytes from the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_read_multi ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief LightRanger 12 write byte function.
 * @details This function writes a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_write_byte ( lightranger12_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief LightRanger 12 read byte function.
 * @details This function reads data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_read_byte ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief LightRanger 12 write data function.
 * @details This function writes a desired number of data bytes.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_write_data ( lightranger12_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LightRanger 12 disable I2C function.
 * @details This function disables I2C by setting the LPn pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger12_disable_i2c ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 enable I2C function.
 * @details This function enables I2C by setting the LPn pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger12_enable_i2c ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 set sync pin function.
 * @details This function sets the SYNC pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lightranger12_set_sync_pin ( lightranger12_t *ctx, uint8_t state );

/**
 * @brief LightRanger 12 get INT pin function.
 * @details This function returns the INT (interrupt) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lightranger12_get_int_pin ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 check comm function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_check_comm ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 set I2C address function.
 * @details This function changes the I2C address of the sensor. If multiple LightRanger 12 Click boards
 * are connected to the same I2C line, I2C on all other Click boards must be disabled using
 * the lightranger12_disable_i2c function.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] i2c_address : 7-bit I2C address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_set_i2c_address ( lightranger12_t *ctx, uint8_t i2c_address );

/**
 * @brief LightRanger 12 sensor init function.
 * @details This function initializes the sensor. It must be called after a power on, 
 * to load the firmware into the sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_sensor_init ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 dci write data function.
 * @details This function writes 'extra data' to DCI. The data can be simple data, or casted structure.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] index : DCI register address. 
 * @param[in] data_in : This field can be a casted structure, or a simple array. Please note that the FW only
 * accept data of 32 bits. So field data can only have a size of 32, 64, 96, 128, bits..
 * @param[in] data_size : This field must be the structure or array size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_dci_write_data ( lightranger12_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size );

/**
 * @brief LightRanger 12 dci read data function.
 * @details This function reads 'extra data' from DCI. Using a known index, the function fills the
 * casted structure passed in argument.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] index : DCI register address. 
 * @param[out] data_out : This field can be a casted structure, or a simple array. Please note that the FW only
 * accept data of 32 bits. So field data can only have a size of 32, 64, 96, 128, bits..
 * @param[in] data_size : This field must be the structure or array size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_dci_read_data ( lightranger12_t *ctx, uint16_t index, uint8_t *data_out, uint16_t data_size );

/**
 * @brief LightRanger 12 dci replace data function.
 * @details This function replaces 'extra data' in DCI. The data can be simple data, or casted structure.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
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
err_t lightranger12_dci_replace_data ( lightranger12_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size, 
                                       uint8_t *new_data, uint16_t new_data_size, uint16_t new_data_pos );

/**
 * @brief LightRanger 12 set resolution function.
 * @details This function sets a new data resolution (4x4 or 8x8).
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] resolution : Use macro LIGHTRANGER12_RESOLUTION_4X4 or LIGHTRANGER12_RESOLUTION_8X8 to set the resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_set_resolution ( lightranger12_t *ctx, uint8_t resolution );

/**
 * @brief LightRanger 12 get resolution function.
 * @details This function gets the current resolution (4x4 or 8x8).
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[out] resolution : Value of this pointer will be equal to 16 for 4x4 mode, and 64 for 8x8 mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_get_resolution ( lightranger12_t *ctx, uint8_t *resolution );

/**
 * @brief LightRanger 12 set ranging frequency hz function.
 * @details This function sets a new ranging frequency in Hz. Ranging frequency corresponds to the measurements 
 * frequency. This setting depends of the resolution, so please select your resolution before using this function.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] frequency_hz : Contains the ranging frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For 4x4, min and max allowed values are : [1;60] - For 8x8, min and max allowed values are : [1;15].
 */
err_t lightranger12_set_ranging_freq ( lightranger12_t *ctx, uint8_t frequency_hz );

/**
 * @brief LightRanger 12 get ranging frequency hz function.
 * @details This function gets the current ranging frequency in Hz. Ranging frequency corresponds to 
 * the time between each measurement.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[out] frequency_hz : Contains the ranging frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_get_ranging_freq ( lightranger12_t *ctx, uint8_t *frequency_hz );

/**
 * @brief LightRanger 12 set integration time ms function.
 * @details This function sets a new integration time in ms. Integration time must be computed to be lower than 
 * the ranging period, for a selected resolution.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] int_time_ms : Contains the integration time in ms. For all resolutions and frequency, 
 * the minimum value is 2ms, and the maximum is 1000ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function has no impact on ranging mode continous.
 */
err_t lightranger12_set_int_time ( lightranger12_t *ctx, uint32_t int_time_ms );

/**
 * @brief LightRanger 12 get integration time ms function.
 * @details This function gets the current integration time in ms.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[out] integration_time_ms : Contains integration time in ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_get_int_time ( lightranger12_t *ctx, uint32_t *int_time_ms );

/**
 * @brief LightRanger 12 set ranging mode function.
 * @details This function sets the ranging mode. Two modes are available using ULD : Continuous and autonomous. 
 * The default mode is Autonomous.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] ranging_mode : Use macros LIGHTRANGER12_RANGING_MODE_CONTINUOUS, LIGHTRANGER12_RANGING_MODE_CONTINUOUS.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_set_ranging_mode ( lightranger12_t *ctx, uint8_t ranging_mode );

/**
 * @brief LightRanger 12 get ranging mode function.
 * @details This function gets the ranging mode. Two modes are available using ULD : Continuous and autonomous. 
 * The default mode is Autonomous.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[out] ranging_mode : Current ranging mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_get_ranging_mode ( lightranger12_t *ctx, uint8_t *ranging_mode );

/**
 * @brief LightRanger 12 start ranging function.
 * @details This function starts a ranging session. When the sensor streams, host cannot change settings 'on-the-fly'.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_start_ranging ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 stop ranging function.
 * @details This function stops the ranging session. It must be used when the sensor streams, 
 * after calling lightranger12_start_ranging( ).
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_stop_ranging ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 get ranging data function.
 * @details This function gets the ranging data, using the selected output and the resolution.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[out] results : LightRanger 12 results structure.
 * See #lightranger12_results_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger12_get_ranging_data ( lightranger12_t *ctx, lightranger12_results_data_t *results );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER12_H

/*! @} */ // lightranger12

// ------------------------------------------------------------------------ END

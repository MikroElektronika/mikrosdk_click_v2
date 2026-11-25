/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file pressure28.h
 * @brief This file contains API for Pressure 28 Click Driver.
 */

#ifndef PRESSURE28_H
#define PRESSURE28_H

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
 * @addtogroup pressure28 Pressure 28 Click Driver
 * @brief API for configuring and manipulating Pressure 28 Click driver.
 * @{
 */

/**
 * @defgroup pressure28_cmd Pressure 28 Command List
 * @brief List of commands of Pressure 28 Click driver.
 */

/**
 * @addtogroup pressure28_cmd
 * @{
 */

/**
 * @brief Pressure 28 command list.
 * @details Specified command list of Pressure 28 Click driver.
 */
#define PRESSURE28_CMD_RESET                    0x72
#define PRESSURE28_CMD_IDLE                     0x94
#define PRESSURE28_CMD_ACTIVE_MODE_1            0xA0
#define PRESSURE28_CMD_ACTIVE_MODE_2            0xA2
#define PRESSURE28_CMD_ACTIVE_MODE_3            0xA4
#define PRESSURE28_CMD_ACTIVE_MODE_4            0xA6
#define PRESSURE28_CMD_READ_STATUS              0x80
#define PRESSURE28_CMD_READ_PRESSURE            0xC0
#define PRESSURE28_CMD_READ_TEMPERATURE         0xC2
#define PRESSURE28_CMD_READ_NVM                 0xD6

/*! @} */ // pressure28_cmd

/**
 * @defgroup pressure28_set Pressure 28 Registers Settings
 * @brief Settings for registers of Pressure 28 Click driver.
 */

/**
 * @addtogroup pressure28_set
 * @{
 */

/**
 * @brief Pressure 28 device state setting.
 * @details Specified setting for device state of Pressure 28 Click driver.
 */
#define PRESSURE28_STATE_SHUTDOWN               0x00
#define PRESSURE28_STATE_IDLE                   0xE5
#define PRESSURE28_STATE_ACTIVE                 0xED

/**
 * @brief Pressure 28 NVM setting.
 * @details Specified setting for NVM of Pressure 28 Click driver.
 */
#define PRESSURE28_NVM_ADDR_MODEL_RANK          0x75
#define PRESSURE28_NVM_ADDR_CORR_VOLTAGE        0x76
#define PRESSURE28_NVM_MODEL_RANK_MMR902_A      0x2A
#define PRESSURE28_NVM_CORR_VOLTAGE_3V4         0x34
#define PRESSURE28_NVM_SPI_READY_MARKER         0x01

/**
 * @brief Pressure 28 timing setting.
 * @details Specified setting for timing of Pressure 28 Click driver.
 */
#define PRESSURE28_FIRST_CONV_MODE_1_MS         34
#define PRESSURE28_FIRST_CONV_MODE_2_MS         21
#define PRESSURE28_FIRST_CONV_MODE_3_MS         14
#define PRESSURE28_FIRST_CONV_MODE_4_MS         439
#define PRESSURE28_CONV_MODE_1_MS               16
#define PRESSURE28_CONV_MODE_2_MS               8
#define PRESSURE28_CONV_MODE_3_MS               4
#define PRESSURE28_CONV_MODE_4_MS               256
#define PRESSURE28_NVM_SPI_TIMEOUT              32

/**
 * @brief Pressure 28 measurement result setting.
 * @details Specified setting for measurement result of Pressure 28 Click driver.
 */
#define PRESSURE28_RESULT_LEN                   3
#define PRESSURE28_CMD_BUF_LEN                  2
#define PRESSURE28_SIGN_BIT_MASK                0x00800000ul
#define PRESSURE28_SIGN_EXTENSION_MASK          0xFF000000ul
#define PRESSURE28_PRESSURE_RES_MMHG            1000.0f
#define PRESSURE28_TEMPERATURE_RES_C            65536.0f

/**
 * @brief Pressure 28 default measurement mode setting.
 * @details Specified setting for default measurement mode of Pressure 28 Click driver.
 */
#define PRESSURE28_DEFAULT_MODE                 PRESSURE28_CMD_ACTIVE_MODE_1

/**
 * @brief Pressure 28 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 28 Click driver.
 */
#define PRESSURE28_DEVICE_ADDRESS               0x65

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b pressure28_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PRESSURE28_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define PRESSURE28_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // pressure28_set

/**
 * @defgroup pressure28_map Pressure 28 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 28 Click driver.
 */

/**
 * @addtogroup pressure28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 28 Click to the selected MikroBUS.
 */
#define PRESSURE28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dry  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure28_map
/*! @} */ // pressure28

/**
 * @brief Pressure 28 Click driver selector.
 * @details Selects target driver interface of Pressure 28 Click driver.
 */
typedef enum
{
    PRESSURE28_DRV_SEL_SPI,                  /**< SPI driver descriptor. */
    PRESSURE28_DRV_SEL_I2C                   /**< I2C driver descriptor. */

} pressure28_drv_t;

/**
 * @brief Pressure 28 Click driver interface.
 * @details Definition of driver interface of Pressure 28 Click driver.
 */
struct pressure28_s;
typedef err_t ( *pressure28_master_write_t )( struct pressure28_s*, uint8_t ); /**< Driver serial write interface. */
typedef err_t ( *pressure28_master_read_t )( struct pressure28_s*, uint8_t, uint8_t, uint8_t* ); /**< Driver serial read interface. */

/**
 * @brief Pressure 28 Click context object.
 * @details Context object definition of Pressure 28 Click driver.
 */
typedef struct pressure28_s
{
    digital_in_t dry;                               /**< Data ready pin (active low). */

    i2c_master_t i2c;                               /**< I2C driver object. */
    spi_master_t spi;                               /**< SPI driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */
    pressure28_drv_t drv_sel;                       /**< Master driver interface selector. */

    pressure28_master_write_t write_f;              /**< Master write function. */
    pressure28_master_read_t  read_f;               /**< Master read function. */

    uint8_t      mode;                              /**< Active measurement mode command. */

} pressure28_t;

/**
 * @brief Pressure 28 Click configuration object.
 * @details Configuration object definition of Pressure 28 Click driver.
 */
typedef struct
{
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t dry;                                 /**< Data ready pin descriptor. */

    uint32_t   i2c_speed;                           /**< I2C serial speed. */
    uint8_t    i2c_address;                         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    pressure28_drv_t drv_sel;                       /**< Master driver interface selector. */

} pressure28_cfg_t;

/**
 * @brief Pressure 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE28_OK = 0,
    PRESSURE28_ERROR = -1

} pressure28_return_value_t;

/*!
 * @addtogroup pressure28 Pressure 28 Click Driver
 * @brief API for configuring and manipulating Pressure 28 Click driver.
 * @{
 */

/**
 * @brief Pressure 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure28_cfg_setup ( pressure28_cfg_t *cfg );

/**
 * @brief Pressure 28 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pressure28_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pressure28_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pressure28_drv_interface_sel ( pressure28_cfg_t *cfg, pressure28_drv_t drv_sel );

/**
 * @brief Pressure 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure28_init ( pressure28_t *ctx, pressure28_cfg_t *cfg );

/**
 * @brief Pressure 28 default configuration function.
 * @details This function executes a default configuration of Pressure 28
 * Click board.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure28_default_cfg ( pressure28_t *ctx );

/**
 * @brief Pressure 28 generic write function.
 * @details This function sends a single command byte to the device by using
 * the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure28_generic_write ( pressure28_t *ctx, uint8_t cmd );

/**
 * @brief Pressure 28 generic read function.
 * @details This function sends a result command byte and reads a desired number
 * of response bytes by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @param[out] data_out : Pointer to the output data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure28_generic_read ( pressure28_t *ctx, uint8_t cmd, uint8_t *data_out );

/**
 * @brief Pressure 28 read NVM function.
 * @details This function reads a single byte from the selected non-volatile
 * memory address by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] addr : Non-volatile memory address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must be called while the device is in the idle state.
 */
err_t pressure28_read_nvm ( pressure28_t *ctx, uint8_t addr, uint8_t *data_out );

/**
 * @brief Pressure 28 reset device function.
 * @details This function resets the device and returns it to the shutdown state.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure28_reset_device ( pressure28_t *ctx );

/**
 * @brief Pressure 28 set idle function.
 * @details This function puts the device into the idle state.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure28_set_idle ( pressure28_t *ctx );

/**
 * @brief Pressure 28 check communication function.
 * @details This function checks the communication by reading the factory
 * programmed product code and verifying it against the expected values.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must be called while the device is in the idle state.
 */
err_t pressure28_check_communication ( pressure28_t *ctx );

/**
 * @brief Pressure 28 read status function.
 * @details This function reads the device status code.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[out] status : Pointer to the device status code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure28_read_status ( pressure28_t *ctx, uint8_t *status );

/**
 * @brief Pressure 28 start measurement function.
 * @details This function starts a measurement session in the selected mode and
 * waits for the first conversion cycle to complete.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] mode : Active command that selects the measurement mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device converts temperature only once per measurement session,
 * therefore a new session is required to refresh the temperature result.
 */
err_t pressure28_start_measurement ( pressure28_t *ctx, uint8_t mode );

/**
 * @brief Pressure 28 read temperature function.
 * @details This function reads the compensated temperature result and converts
 * it to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device converts temperature only once per measurement session,
 * therefore a new session is required to refresh the temperature result.
 */
err_t pressure28_read_temperature ( pressure28_t *ctx, float *temp );

/**
 * @brief Pressure 28 read pressure function.
 * @details This function reads the compensated pressure result
 * and converts it to millimeters of mercury.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[out] press : Pressure in millimeters of mercury.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure28_read_pressure ( pressure28_t *ctx, float *press );

/**
 * @brief Pressure 28 get DRY pin function.
 * @details This function reads the logic state of the DRY pin.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @return DRY pin logic state.
 * @note None.
 */
uint8_t pressure28_get_dry_pin ( pressure28_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE28_H

/*! @} */ // pressure28

// ------------------------------------------------------------------------ END

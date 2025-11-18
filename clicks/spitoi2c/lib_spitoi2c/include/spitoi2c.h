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
 * @file spitoi2c.h
 * @brief This file contains API for SPI to I2C Click Driver.
 */

#ifndef SPITOI2C_H
#define SPITOI2C_H

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

/*!
 * @addtogroup spitoi2c SPI to I2C Click Driver
 * @brief API for configuring and manipulating SPI to I2C Click driver.
 * @{
 */

/**
 * @defgroup spitoi2c_reg SPI to I2C Registers List
 * @brief List of registers of SPI to I2C Click driver.
 */

/**
 * @addtogroup spitoi2c_reg
 * @{
 */

/**
 * @brief SPI to I2C control commands.
 * @details Specified control commands of SPI to I2C Click driver.
 */
#define SPITOI2C_CMD_WRITE                  0x00
#define SPITOI2C_CMD_READ                   0x01
#define SPITOI2C_CMD_READ_AFTER_WRITE       0x02
#define SPITOI2C_CMD_WRITE_AFTER_WRITE      0x03
#define SPITOI2C_CMD_READ_BUFFER            0x06
#define SPITOI2C_CMD_SPI_CONFIG             0x18
#define SPITOI2C_CMD_WRITE_REG              0x20
#define SPITOI2C_CMD_READ_REG               0x21
#define SPITOI2C_CMD_DEEP_POWER_DOWN        0x30
#define SPITOI2C_CMD_READ_VERSION           0xFE

/**
 * @brief SPI to I2C registers list.
 * @details Specified registers list of SPI to I2C Click driver.
 */
#define SPITOI2C_REG_IO_CONFIG              0x00
#define SPITOI2C_REG_IO_STATE               0x01
#define SPITOI2C_REG_I2C_CLOCK              0x02
#define SPITOI2C_REG_I2C_TO                 0x03
#define SPITOI2C_REG_I2C_STAT               0x04
#define SPITOI2C_REG_I2C_ADR                0x05

/*! @} */ // spitoi2c_reg

/**
 * @defgroup spitoi2c_set SPI to I2C Registers Settings
 * @brief Settings for registers of SPI to I2C Click driver.
 */

/**
 * @addtogroup spitoi2c_set
 * @{
 */

/**
 * @brief SPI to I2C I2C settings.
 * @details Specified I2C settings of SPI to I2C Click driver.
 */
#define SPITOI2C_I2C_CLOCK_375_KHZ          5
#define SPITOI2C_I2C_CLOCK_99_KHZ           19
#define SPITOI2C_I2C_CLOCK_7p4_KHZ          255
#define SPITOI2C_I2C_ADDR_127               0xFE
#define SPITOI2C_I2C_TO_DISABLE             0x00

/**
 * @brief SPI to I2C I2C status.
 * @details Specified I2C status of SPI to I2C Click driver.
 */
#define SPITOI2C_I2C_STATUS_SUCCESS         0xF0
#define SPITOI2C_I2C_STATUS_TARGET_NACK     0xF1
#define SPITOI2C_I2C_STATUS_WRITE_NACK      0xF2
#define SPITOI2C_I2C_STATUS_BUSY            0xF3
#define SPITOI2C_I2C_STATUS_TIMEOUT         0xF8
#define SPITOI2C_I2C_STATUS_DATA_COUNT      0xF9

/**
 * @brief SPI to I2C read timeout settings.
 * @details Specified read timeout settings of SPI to I2C Click driver.
 */
#define SPITOI2C_TIMEOUT_MS                 3000

/**
 * @brief SPI to I2C pin mask values.
 * @details Specified pin mask values of SPI to I2C Click driver.
 */
#define SPITOI2C_NO_PIN_MASK                0x00
#define SPITOI2C_PIN_0_MASK                 0x01
#define SPITOI2C_PIN_1_MASK                 0x02
#define SPITOI2C_PIN_2_MASK                 0x04
#define SPITOI2C_PIN_3_MASK                 0x08
#define SPITOI2C_PIN_4_MASK                 0x10
#define SPITOI2C_ALL_PINS_MASK              0x1F
#define SPITOI2C_ALL_OUT_PINS_MASK          0x0F

/**
 * @brief SPI to I2C pin direction settings.
 * @details Specified pin direction settings of SPI to I2C Click driver.
 */
#define SPITOI2C_PIN_DIR_INPUT              0x00
#define SPITOI2C_PIN_DIR_OUTPUT_PP          0x02
#define SPITOI2C_PIN_DIR_OUTPUT_OD          0x03
#define SPITOI2C_PIN_DIR_MASK               0x03

/**
 * @brief SPI to I2C I2C read bit.
 * @details Specified setting for I2C read bit of SPI to I2C Click driver.
 */
#define SPITOI2C_I2C_READ_BIT               0x01

/**
 * @brief SPI to I2C SPI config bytes.
 * @details Specified setting for SPI config of SPI to I2C Click driver.
 */
#define SPITOI2C_SPI_CONFIG_LSB_FIRST       0x81
#define SPITOI2C_SPI_CONFIG_MSB_FIRST       0x42

/**
 * @brief SPI to I2C deep power down bytes.
 * @details Specified setting for deep power down of SPI to I2C Click driver.
 */
#define SPITOI2C_DEEP_PDOWN_BYTE_0          0x5A
#define SPITOI2C_DEEP_PDOWN_BYTE_1          0xA5

/*! @} */ // spitoi2c_set

/**
 * @defgroup spitoi2c_map SPI to I2C MikroBUS Map
 * @brief MikroBUS pin mapping of SPI to I2C Click driver.
 */

/**
 * @addtogroup spitoi2c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI to I2C Click to the selected MikroBUS.
 */
#define SPITOI2C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // spitoi2c_map
/*! @} */ // spitoi2c

/**
 * @brief SPI to I2C Click context object.
 * @details Context object definition of SPI to I2C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mosi;             /**< Master output - slave input pin descriptor for SPI driver. */
    digital_out_t sck;              /**< Clock pin descriptor for SPI driver. */
    digital_out_t cs;               /**< Chip select pin descriptor for SPI driver. */
    digital_out_t rst;              /**< Reset pin (Active low). */

    // Input pins
    digital_in_t miso;              /**< Master input - slave output pin descriptor for SPI driver. */
    digital_in_t int_pin;           /**< Interrupt pin (Active low). */

} spitoi2c_t;

/**
 * @brief SPI to I2C Click configuration object.
 * @details Configuration object definition of SPI to I2C Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (Active low). */
    pin_name_t int_pin;             /**< Interrupt pin (Active low). */

} spitoi2c_cfg_t;

/**
 * @brief SPI to I2C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPITOI2C_OK = 0,
    SPITOI2C_ERROR = -1

} spitoi2c_return_value_t;

/*!
 * @addtogroup spitoi2c SPI to I2C Click Driver
 * @brief API for configuring and manipulating SPI to I2C Click driver.
 * @{
 */

/**
 * @brief SPI to I2C configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spitoi2c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spitoi2c_cfg_setup ( spitoi2c_cfg_t *cfg );

/**
 * @brief SPI to I2C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spitoi2c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_init ( spitoi2c_t *ctx, spitoi2c_cfg_t *cfg );

/**
 * @brief SPI to I2C default configuration function.
 * @details This function executes a default configuration of SPI to I2C
 * Click board.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t spitoi2c_default_cfg ( spitoi2c_t *ctx );

/**
 * @brief SPI to I2C gpio write function.
 * @details This function writes a desired data to the gpio port.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] gpio_data : GPIO data to be written (only GPIO0-GPIO3 are writable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The pins should be configured as output in order for this to take effect.
 */
err_t spitoi2c_gpio_write ( spitoi2c_t *ctx, uint8_t gpio_data );

/**
 * @brief SPI to I2C gpio read function.
 * @details This function reads data from the gpio port.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[out] gpio_data : GPIO data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_gpio_read ( spitoi2c_t *ctx, uint8_t *gpio_data );

/**
 * @brief SPI to I2C gpio gpio config function.
 * @details This function sets the gpio direction config for the selected pins.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] direction : GPIO direction: @li @c 0 - Input,
 *                                        @li @c 2 - Output push-pull,
 *                                        @li @c 3 - Output open-drain.
 * @param[in] pin_mask : Mask for pins to configure (only GPIO0-GPIO3 are configurable, GPIO4 is input only).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_gpio_config ( spitoi2c_t *ctx, uint8_t direction, uint8_t pin_mask );

/**
 * @brief SPI to I2C read i2c status function.
 * @details This function reads the I2C status register.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[out] i2c_stat : I2C status register data. Refer to I2C Status macro definitions for more details.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_read_i2c_status ( spitoi2c_t *ctx, uint8_t *i2c_stat );

/**
 * @brief SPI to I2C i2c write function.
 * @details This function writes a desired number of data bytes to the I2C target device.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit target device slave address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c >0 - I2C status error,
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_i2c_write ( spitoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief SPI to I2C i2c read function.
 * @details This function reads a desired number of data bytes from the I2C target device.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit target device slave address.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c >0 - I2C status error,
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_i2c_read ( spitoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief SPI to I2C i2c read after write function.
 * @details This function performs a write then read with a repeated start to the I2C target device.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit target device slave address.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @param[out] data_out : Output data read.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c >0 - I2C status error,
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_i2c_read_after_write ( spitoi2c_t *ctx, uint8_t slave_addr, 
                                      uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );

/**
 * @brief SPI to I2C i2c write after write function.
 * @details This function performs a write then write with a repeated start to the I2C target device.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit target device slave address.
 * @param[in] data_in1 : Data 1 to be written.
 * @param[in] in1_len : Number of bytes of data 1 to be written.
 * @param[in] data_in2 : Data 2 to be written.
 * @param[in] in2_len : Number of bytes of data 2 to be written.
 * @return @li @c >0 - I2C status error,
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_i2c_write_after_write ( spitoi2c_t *ctx, uint8_t slave_addr, 
                                       uint8_t *data_in1, uint8_t in1_len, uint8_t *data_in2, uint8_t in2_len );

/**
 * @brief SPI to I2C read buffer function.
 * @details This function reads a desired number of data bytes performing a read buffer command.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of bytes to be read.
 * @return None.
 * @note None.
 */
void spitoi2c_read_buffer ( spitoi2c_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief SPI to I2C set spi config function.
 * @details This function sets the spi configuration to MSB or LSB first.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] spi_cfg : 0x81 - LSB first, 0x42 - MSB first.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_set_spi_config ( spitoi2c_t *ctx, uint8_t spi_cfg );

/**
 * @brief SPI to I2C write register function.
 * @details This function writes a desired data to the specified chip internal register.
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] reg : Chip internal register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_write_register ( spitoi2c_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief SPI to I2C read register function.
 * @details This function reads data from the specified chip internal register.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] reg : Chip internal register address.
 * @param[out] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_read_register ( spitoi2c_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief SPI to I2C deep power down function.
 * @details This function performs a deep power down command.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void spitoi2c_deep_power_down ( spitoi2c_t *ctx );

/**
 * @brief SPI to I2C wake up function.
 * @details This function wakes up from deep power down mode by toggling the chip select pin.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void spitoi2c_wake_up ( spitoi2c_t *ctx );

/**
 * @brief SPI to I2C read version function.
 * @details This function reads the firmware version (16-bytes string ending with a null terminator).
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[out] version : Firmware version (16-bytes string ending with a null terminator).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spitoi2c_read_version ( spitoi2c_t *ctx, uint8_t *version );

/**
 * @brief SPI to I2C enable device function.
 * @details This function enables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void spitoi2c_enable_device ( spitoi2c_t *ctx );

/**
 * @brief SPI to I2C disable device function.
 * @details This function disables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void spitoi2c_disable_device ( spitoi2c_t *ctx );

/**
 * @brief SPI to I2C get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t spitoi2c_get_int_pin ( spitoi2c_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SPITOI2C_H

/*! @} */ // spitoi2c

// ------------------------------------------------------------------------ END

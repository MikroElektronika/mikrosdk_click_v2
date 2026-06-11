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
 * @file digipot15.h
 * @brief This file contains API for DIGI POT 15 Click Driver.
 */

#ifndef DIGIPOT15_H
#define DIGIPOT15_H

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
 * @addtogroup digipot15 DIGI POT 15 Click Driver
 * @brief API for configuring and manipulating DIGI POT 15 Click driver.
 * @{
 */

/**
 * @defgroup digipot15_reg DIGI POT 15 Registers List
 * @brief List of registers of DIGI POT 15 Click driver.
 */

/**
 * @addtogroup digipot15_reg
 * @{
 */

/**
 * @brief DIGI POT 15 memory map.
 * @details Specified memory map of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_REG_VOLATILE_WIPER_0          0x01
#define DIGIPOT15_REG_NV_WIPER_0                0x03
#define DIGIPOT15_REG_GP_DATA_0                 0x05
#define DIGIPOT15_REG_GP_DATA_1                 0x06
#define DIGIPOT15_REG_GP_DATA_2                 0x07
#define DIGIPOT15_REG_STATUS                    0x08
#define DIGIPOT15_REG_LOCK                      0x09
#define DIGIPOT15_REG_TERMINAL_CONTROL          0x0A
#define DIGIPOT15_REG_SYNC                      0x0B
#define DIGIPOT15_REG_CRC                       0x0C
#define DIGIPOT15_REG_RESET                     0x0D
#define DIGIPOT15_REG_NV_W_0_COUNT              0x15
#define DIGIPOT15_REG_DATA_0_COUNT              0x19
#define DIGIPOT15_REG_DATA_1_COUNT              0x1B
#define DIGIPOT15_REG_DATA_2_COUNT              0x1D

/**
 * @brief DIGI POT 15 command and data settings.
 * @details Specified command and data settings of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_CMD_REG_MASK                  0xF8
#define DIGIPOT15_CMD_OP_WRITE_DATA             0x00
#define DIGIPOT15_CMD_OP_READ_DATA              0x07
#define DIGIPOT15_CMD_OP_INCREMENT_WIPER        0x02
#define DIGIPOT15_CMD_OP_DECREMENT_WIPER        0x04
#define DIGIPOT15_CMD_OP_MASK                   0x07
#define DIGIPOT15_DATA_MASK                     0x03FF

/*! @} */ // digipot15_reg

/**
 * @defgroup digipot15_set DIGI POT 15 Registers Settings
 * @brief Settings for registers of DIGI POT 15 Click driver.
 */

/**
 * @addtogroup digipot15_set
 * @{
 */

/**
 * @brief DIGI POT 15 STATUS register setting.
 * @details Specified setting for STATUS register of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_STATUS_ECED                   0x0040
#define DIGIPOT15_STATUS_SPIWDT                 0x0020
#define DIGIPOT15_STATUS_CMDERR                 0x0010
#define DIGIPOT15_STATUS_CRCERR                 0x0008
#define DIGIPOT15_STATUS_SRST                   0x0004
#define DIGIPOT15_STATUS_POR                    0x0002
#define DIGIPOT15_STATUS_MTPMA                  0x0001

/**
 * @brief DIGI POT 15 LOCK register setting.
 * @details Specified setting for LOCK register of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_LOCK_LOCKNV                   0x0002
#define DIGIPOT15_LOCK_LOCKV                    0x0001

/**
 * @brief DIGI POT 15 TCON0 register setting.
 * @details Specified setting for TCON0 register of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_TCON0_R0A                     0x0004
#define DIGIPOT15_TCON0_R0W                     0x0002
#define DIGIPOT15_TCON0_R0B                     0x0001

/**
 * @brief DIGI POT 15 SYNC register setting.
 * @details Specified setting for SYNC register of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_SYNC_WLAT                     0x0004

/**
 * @brief DIGI POT 15 CRC register setting.
 * @details Specified setting for CRC register of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_CRC_CRCEN                     0x0001

/**
 * @brief DIGI POT 15 RESET register setting.
 * @details Specified setting for RESET register of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_RESET_SWRSTVAL                0x00A5

/**
 * @brief DIGI POT 15 wiper setting.
 * @details Specified setting for wiper of DIGI POT 15 Click driver.
 */
#define DIGIPOT15_WIPER_FULL_SCALE              0x03FF
#define DIGIPOT15_WIPER_MID_SCALE               0x0200
#define DIGIPOT15_WIPER_ZERO_SCALE              0x0000

/**
 * @brief DIGI POT 15 device address setting.
 * @details Specified setting for device slave address selection of
 * DIGI POT 15 Click driver.
 */
#define DIGIPOT15_DEVICE_ADDRESS_A1A0_00        0x2C
#define DIGIPOT15_DEVICE_ADDRESS_A1A0_01        0x2D
#define DIGIPOT15_DEVICE_ADDRESS_A1A0_10        0x2E
#define DIGIPOT15_DEVICE_ADDRESS_A1A0_11        0x2F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b digipot15_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DIGIPOT15_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define DIGIPOT15_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // digipot15_set

/**
 * @defgroup digipot15_map DIGI POT 15 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 15 Click driver.
 */

/**
 * @addtogroup digipot15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 15 Click to the selected MikroBUS.
 */
#define DIGIPOT15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.com  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // digipot15_map
/*! @} */ // digipot15

/**
 * @brief DIGI POT 15 Click driver selector.
 * @details Selects target driver interface of DIGI POT 15 Click driver.
 */
typedef enum
{
    DIGIPOT15_DRV_SEL_SPI,          /**< SPI driver descriptor. */
    DIGIPOT15_DRV_SEL_I2C           /**< I2C driver descriptor. */

} digipot15_drv_t;

/**
 * @brief DIGI POT 15 Click driver interface.
 * @details Definition of driver interface of DIGI POT 15 Click driver.
 */
struct digipot15_s;
typedef err_t ( *digipot15_master_io_t )( struct digipot15_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief DIGI POT 15 Click context object.
 * @details Context object definition of DIGI POT 15 Click driver.
 */
typedef struct digipot15_s
{
    digital_out_t com;              /**< Communication selection pin (high-I2C, low-SPI), must be aligned with COMM SEL jumper settings. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    digipot15_drv_t drv_sel;        /**< Master driver interface selector. */

    digipot15_master_io_t write_f;  /**< Master write function. */
    digipot15_master_io_t read_f;   /**< Master read function. */

} digipot15_t;

/**
 * @brief DIGI POT 15 Click configuration object.
 * @details Configuration object definition of DIGI POT 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t com;                 /**< Description. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    digipot15_drv_t drv_sel;        /**< Master driver interface selector. */

} digipot15_cfg_t;

/**
 * @brief DIGI POT 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT15_OK = 0,
    DIGIPOT15_ERROR = -1

} digipot15_return_value_t;

/*!
 * @addtogroup digipot15 DIGI POT 15 Click Driver
 * @brief API for configuring and manipulating DIGI POT 15 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot15_cfg_setup ( digipot15_cfg_t *cfg );

/**
 * @brief DIGI POT 15 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #digipot15_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #digipot15_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void digipot15_drv_interface_sel ( digipot15_cfg_t *cfg, digipot15_drv_t drv_sel );

/**
 * @brief DIGI POT 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot15_init ( digipot15_t *ctx, digipot15_cfg_t *cfg );

/**
 * @brief DIGI POT 15 default configuration function.
 * @details This function executes a default configuration of DIGI POT 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digipot15_default_cfg ( digipot15_t *ctx );

/**
 * @brief DIGI POT 15 write register function.
 * @details This function writes a 16-bit data word to the selected register address.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot15_write_reg ( digipot15_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DIGI POT 15 read register function.
 * @details This function reads a 16-bit data word from the selected register address.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot15_read_reg ( digipot15_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DIGI POT 15 increment wiper function.
 * @details This function increments the selected wiper register value by one step.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] reg : Wiper register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot15_increment_wiper ( digipot15_t *ctx, uint8_t reg );

/**
 * @brief DIGI POT 15 decrement wiper function.
 * @details This function decrements the selected wiper register value by one step.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] reg : Wiper register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot15_decrement_wiper ( digipot15_t *ctx, uint8_t reg );

/**
 * @brief DIGI POT 15 software reset function.
 * @details This function performs a software reset of the device.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot15_soft_reset ( digipot15_t *ctx );

/**
 * @brief DIGI POT 15 set wiper function.
 * @details This function sets the value of wiper volatile register.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] wiper : Wiper value [0-1023].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot15_set_wiper ( digipot15_t *ctx, uint16_t wiper );

/**
 * @brief DIGI POT 15 set COM pin function.
 * @details This function sets the COM pin logic state which must be aligned with COMM SEL jumper settings.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] state : COM pin logic state.
 * @return None.
 * @note None.
 */
void digipot15_set_com_pin ( digipot15_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT15_H

/*! @} */ // digipot15

// ------------------------------------------------------------------------ END

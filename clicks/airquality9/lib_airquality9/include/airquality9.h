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
 * @file airquality9.h
 * @brief This file contains API for Air Quality 9 Click Driver.
 */

#ifndef AIRQUALITY9_H
#define AIRQUALITY9_H

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
 * @addtogroup airquality9 Air Quality 9 Click Driver
 * @brief API for configuring and manipulating Air Quality 9 Click driver.
 * @{
 */

/**
 * @defgroup airquality9_reg Air Quality 9 Registers List
 * @brief List of registers of Air Quality 9 Click driver.
 */

/**
 * @addtogroup airquality9_reg
 * @{
 */

/**
 * @brief Air Quality 9 Register Map.
 * @details Specified Register Map of Air Quality 9 Click driver.
 */
#define AIRQUALITY9_REG_PART_ID                 0x00
#define AIRQUALITY9_REG_OPMODE                  0x10
#define AIRQUALITY9_REG_CONFIG                  0x11
#define AIRQUALITY9_REG_COMMAND                 0x12
#define AIRQUALITY9_REG_TEMP_IN                 0x13
#define AIRQUALITY9_REG_RH_IN                   0x15
#define AIRQUALITY9_REG_DATA_STATUS             0x20
#define AIRQUALITY9_REG_DATA_AQI                0x21
#define AIRQUALITY9_REG_DATA_TVOC               0x22
#define AIRQUALITY9_REG_DATA_ECO2               0x24
#define AIRQUALITY9_REG_DATA_T                  0x30
#define AIRQUALITY9_REG_DATA_RH                 0x32
#define AIRQUALITY9_REG_DATA_MISR               0x38
#define AIRQUALITY9_REG_GPR_WRITE               0x40
#define AIRQUALITY9_REG_GPR_READ                0x48

/*! @} */ // airquality9_reg

/**
 * @defgroup airquality9_set Air Quality 9 Registers Settings
 * @brief Settings for registers of Air Quality 9 Click driver.
 */

/**
 * @addtogroup airquality9_set
 * @{
 */

/**
 * @brief Air Quality 9 operating mode settings.
 * @details Specified operating mode settings of Air Quality 9 Click driver.
 */
#define AIRQUALITY9_OPMODE_DEEP_SLEEP           0x00
#define AIRQUALITY9_OPMODE_IDLE                 0x01
#define AIRQUALITY9_OPMODE_STANDARD             0x02
#define AIRQUALITY9_OPMODE_RESET                0xF0

/**
 * @brief Air Quality 9 interrupt config register settings.
 * @details Specified interrupt config register settings of Air Quality 9 Click driver.
 */
#define AIRQUALITY_CONFIG_INTPOL_LOW            0x00
#define AIRQUALITY_CONFIG_INTPOL_HIGH           0x40
#define AIRQUALITY_CONFIG_INTCFG_OPEN_DRAIN     0x00
#define AIRQUALITY_CONFIG_INTCFG_PUSH_PULL      0x20
#define AIRQUALITY_CONFIG_INTGPR_BIT            0x08
#define AIRQUALITY_CONFIG_INTDAT_BIT            0x02
#define AIRQUALITY_CONFIG_INTEN_BIT             0x01

/**
 * @brief Air Quality 9 data status register values.
 * @details Specified data status register values of Air Quality 9 Click driver.
 */
#define AIRQUALITY_STATUS_OPMODE_RUNNING        0x80
#define AIRQUALITY_STATUS_ERROR_DETECTED        0x40
#define AIRQUALITY_STATUS_VALID_NORMAL_OP       0x00
#define AIRQUALITY_STATUS_VALID_WARM_UP         0x04
#define AIRQUALITY_STATUS_VALID_INIT_START_UP   0x08
#define AIRQUALITY_STATUS_VALID_INVALID         0x0C
#define AIRQUALITY_STATUS_VALID_FLAG_BITS       0x0C
#define AIRQUALITY_STATUS_NEW_DATA              0x02
#define AIRQUALITY_STATUS_NEW_GPR               0x01

/**
 * @brief Air Quality 9 part ID value.
 * @details Specified part ID value of Air Quality 9 Click driver.
 */
#define AIRQUALITY9_PART_ID_LSB                 0x60
#define AIRQUALITY9_PART_ID_MSB                 0x01

/**
 * @brief Air Quality 9 AQI-UBA rating values.
 * @details Specified AQI-UBA rating values of Air Quality 9 Click driver.
 */
#define AIRQUALITY9_AQI_UBA_EXELLENT            1
#define AIRQUALITY9_AQI_UBA_GOOD                2
#define AIRQUALITY9_AQI_UBA_MODERATE            3
#define AIRQUALITY9_AQI_UBA_POOR                4
#define AIRQUALITY9_AQI_UBA_UNHEALTHY           5

/**
 * @brief Air Quality 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Air Quality 9 Click driver.
 */
#define AIRQUALITY9_DEVICE_ADDRESS_0            0x52
#define AIRQUALITY9_DEVICE_ADDRESS_1            0x53

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b airquality9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define AIRQUALITY9_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define AIRQUALITY9_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // airquality9_set

/**
 * @defgroup airquality9_map Air Quality 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Air Quality 9 Click driver.
 */

/**
 * @addtogroup airquality9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Air Quality 9 Click to the selected MikroBUS.
 */
#define AIRQUALITY9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // airquality9_map
/*! @} */ // airquality9

/**
 * @brief Air Quality 9 Click driver selector.
 * @details Selects target driver interface of Air Quality 9 Click driver.
 */
typedef enum
{
    AIRQUALITY9_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    AIRQUALITY9_DRV_SEL_I2C       /**< I2C driver descriptor. */

} airquality9_drv_t;

/**
 * @brief Air Quality 9 Click driver interface.
 * @details Definition of driver interface of Air Quality 9 Click driver.
 */
typedef err_t ( *airquality9_master_io_t )( struct airquality9_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Air Quality 9 Click context object.
 * @details Context object definition of Air Quality 9 Click driver.
 */
typedef struct airquality9_s
{
    digital_out_t en;                   /**< Enable device pin. */

    digital_in_t  int_pin;              /**< Interrupt pin. */

    i2c_master_t  i2c;                  /**< I2C driver object. */
    spi_master_t  spi;                  /**< SPI driver object. */

    uint8_t     slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    airquality9_drv_t  drv_sel;         /**< Master driver interface selector. */

    airquality9_master_io_t  write_f;   /**< Master write function. */
    airquality9_master_io_t  read_f;    /**< Master read function. */

} airquality9_t;

/**
 * @brief Air Quality 9 Click configuration object.
 * @details Configuration object definition of Air Quality 9 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                     /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  en;                     /**< Description. */
    pin_name_t  int_pin;                /**< Description. */

    uint32_t  i2c_speed;                /**< I2C serial speed. */
    uint8_t   i2c_address;              /**< I2C slave address. */

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

    airquality9_drv_t  drv_sel;         /**< Master driver interface selector. */

} airquality9_cfg_t;

/**
 * @brief Air Quality 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AIRQUALITY9_OK = 0,
    AIRQUALITY9_ERROR = -1

} airquality9_return_value_t;

/*!
 * @addtogroup airquality9 Air Quality 9 Click Driver
 * @brief API for configuring and manipulating Air Quality 9 Click driver.
 * @{
 */

/**
 * @brief Air Quality 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #airquality9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void airquality9_cfg_setup ( airquality9_cfg_t *cfg );

/**
 * @brief Air Quality 9 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #airquality9_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #airquality9_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void airquality9_drv_interface_selection ( airquality9_cfg_t *cfg, airquality9_drv_t drv_sel );

/**
 * @brief Air Quality 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #airquality9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_init ( airquality9_t *ctx, airquality9_cfg_t *cfg );

/**
 * @brief Air Quality 9 default configuration function.
 * @details This function executes a default configuration of Air Quality 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t airquality9_default_cfg ( airquality9_t *ctx );

/**
 * @brief Air Quality 9 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_generic_write ( airquality9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Quality 9 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_generic_read ( airquality9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Air Quality 9 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void airquality9_enable_device ( airquality9_t *ctx );

/**
 * @brief Air Quality 9 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void airquality9_disable_device ( airquality9_t *ctx );

/**
 * @brief Air Quality 9 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t airquality9_get_int_pin ( airquality9_t *ctx );

/**
 * @brief Air Quality 9 check communication function.
 * @details This function checks the communication by reading and verifying the chip part ID.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_check_communication ( airquality9_t *ctx );

/**
 * @brief Air Quality 9 set operating mode function.
 * @details This function sets the device operating mode.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] opmode : @li @c 0x00 - Deep sleep,
 *                     @li @c 0x01 - IDLE,
 *                     @li @c 0x02 - Standard,
 *                     @li @c 0xF0 - Reset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_set_operating_mode ( airquality9_t *ctx, uint8_t opmode );

/**
 * @brief Air Quality 9 set interrupt config function.
 * @details This function sets the interrupt config register.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] int_cfg : Interrupt config register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_set_interrupt_config ( airquality9_t *ctx, uint8_t int_cfg );

/**
 * @brief Air Quality 9 read status function.
 * @details This function reads the data status register.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[out] status : Data status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_read_status ( airquality9_t *ctx, uint8_t *status );

/**
 * @brief Air Quality 9 read aqi uba function.
 * @details This function reads the Air Quality Index per UBA (AQI-UBA).
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[out] aqi_uba : AQI-UBA value [1-5].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_read_aqi_uba ( airquality9_t *ctx, uint8_t *aqi_uba );

/**
 * @brief Air Quality 9 read tvoc function.
 * @details This function reads the calculated Total Volatile Organic Compounds (TVOC) 
 * concentration per ppb.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[out] tvoc : TVOC per ppb [0-65000].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_read_tvoc ( airquality9_t *ctx, uint16_t *tvoc );

/**
 * @brief Air Quality 9 read eco2 function.
 * @details This function reads the calculated Equivalent CO2 (eCO2) concentration per ppm.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[out] eco2 : eCO2 per ppm [400-65000].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality9_read_eco2 ( airquality9_t *ctx, uint16_t *eco2 );

#ifdef __cplusplus
}
#endif
#endif // AIRQUALITY9_H

/*! @} */ // airquality9

// ------------------------------------------------------------------------ END

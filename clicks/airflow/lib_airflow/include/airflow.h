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
 * @file airflow.h
 * @brief This file contains API for Air Flow Click Driver.
 */

#ifndef AIRFLOW_H
#define AIRFLOW_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup airflow Air Flow Click Driver
 * @brief API for configuring and manipulating Air Flow Click driver.
 * @{
 */

/**
 * @defgroup airflow_reg Air Flow Registers List
 * @brief List of registers of Air Flow Click driver.
 */

/**
 * @addtogroup airflow_reg
 * @{
 */

/**
 * @brief Air Flow I2C control registers.
 * @details Specified registers for communication of Air Flow Click driver via I2C.
 */
#define AIRFLOW_I2C_CMD_RESET                   0x11
#define AIRFLOW_I2C_CMD_GET_SIG                 0x23
#define AIRFLOW_I2C_CMD_GET_DATA                0x26
#define AIRFLOW_I2C_CMD_CONV                    0x27
#define AIRFLOW_I2C_CMD_GET_NON_BAR             0x50
#define AIRFLOW_I2C_CMD_GET_NON_BLOCK_BAR       0x51
/**
 * @brief Air Flow SPI control registers.
 * @details Specified registers for communication of Air Flow Click driver via SPI.
 */
#define AIRFLOW_SPI_CMD_NONE                    0x00
#define AIRFLOW_SPI_CMD_RESET                   0x01
#define AIRFLOW_SPI_CMD_CONV                    0x04
#define AIRFLOW_SPI_CMD_STOP                    0x05
#define AIRFLOW_SPI_CMD_GET_DATA                0x06
#define AIRFLOW_SPI_CMD_GET_BAR                 0x07
#define AIRFLOW_SPI_CMD_GET_SIG                 0x0C

/*! @} */ // airflow_reg

/**
 * @defgroup airflow_set Air Flow Registers Settings
 * @brief Settings for registers of Air Flow Click driver.
 */

/**
 * @addtogroup airflow_set
 * @{
 */

/**
 * @brief Air Flow description setting.
 * @details Specified setting for description of Air Flow Click driver.
 */
#define AIRFLOW_NO_BAROMETRIC_CORRECTION    0x01
#define AIRFLOW_BAROMETRIC_CORRECTION       0x03

/**
 * @brief Air Flow device address setting.
 * @details Specified setting for device slave address selection of
 * Air Flow Click driver.
 */
#define AIRFLOW_SET_DEV_ADDR                    0x5B

/*! @} */ // airflow_set

/**
 * @defgroup airflow_map Air Flow MikroBUS Map
 * @brief MikroBUS pin mapping of Air Flow Click driver.
 */

/**
 * @addtogroup airflow_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Air Flow Click to the selected MikroBUS.
 */
#define AIRFLOW_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // airflow_map
/*! @} */ // airflow

/**
 * @brief Air Flow Click driver selector.
 * @details Selects target driver interface of Air Flow Click driver.
 */
typedef enum
{
   AIRFLOW_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   AIRFLOW_DRV_SEL_I2C       /**< I2C driver descriptor. */

} airflow_drv_t;

/**
 * @brief Air Flow Click driver interface.
 * @details Definition of driver interface of Air Flow Click driver.
 */
typedef err_t ( *airflow_master_io_t )( struct airflow_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Air Flow Click context object.
 * @details Context object definition of Air Flow Click driver.
 */
typedef struct airflow_s
{
    digital_in_t  rdy;             /**< Data ready pin. */

    i2c_master_t  i2c;             /**< I2C driver object. */
    spi_master_t  spi;             /**< SPI driver object. */

    uint8_t     slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
   airflow_drv_t  drv_sel;         /**< Master driver interface selector. */

   airflow_master_io_t  write_f;   /**< Master write function. */
   airflow_master_io_t  read_f;    /**< Master read function. */
   
   uint8_t major_fw_ver;
   uint8_t minor_fw_ver;
   char part_number[ 12 ];
   char lot_number[ 8 ];
   uint16_t pressure_range;
   char output_type;
   uint16_t scale_factor;
   char calibration_id[ 3 ];
   uint8_t week;
   uint8_t year;
   uint16_t sequence_number;

} airflow_t;

/**
 * @brief Air Flow Click configuration object.
 * @details Configuration object definition of Air Flow Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  rdy;        /**< Data ready pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

   airflow_drv_t  drv_sel;  /**< Master driver interface selector. */

} airflow_cfg_t;

/**
 * @brief Air Flow Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   AIRFLOW_OK = 0,
   AIRFLOW_ERROR = -1

} airflow_return_value_t;

/*!
 * @addtogroup airflow Air Flow Click Driver
 * @brief API for configuring and manipulating Air Flow Click driver.
 * @{
 */

/**
 * @brief Air Flow configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #airflow_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void airflow_cfg_setup ( airflow_cfg_t *cfg );

/**
 * @brief Air Flow driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #airflow_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #airflow_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void airflow_drv_interface_selection ( airflow_cfg_t *cfg, airflow_drv_t drv_sel );

/**
 * @brief Air Flow initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #airflow_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airflow_init ( airflow_t *ctx, airflow_cfg_t *cfg );

/**
 * @brief Air Flow default configuration function.
 * @details This function executes a default configuration of Air Flow
 * click board.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t airflow_default_cfg ( airflow_t *ctx );

/**
 * @brief Air Flow data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t airflow_generic_write ( airflow_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Flow data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t airflow_generic_read ( airflow_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Reset device.
 * @details This function sends command to reset device.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @return Nothing.
 * @note After command function will hold MCU for 100ms.
 */
void airflow_reset_device ( airflow_t *ctx );

/**
 * @brief Reads ready pin state.
 * @details This function reads logic level of @b rdy pin.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note Pin state is high when device has data ready to read.
 */
uint8_t airflow_check_ready ( airflow_t *ctx );

/**
 * @brief Reads differential pressure.
 * @details This function reads differential pressure data from sensor.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[out] pressure : Differential pressure data in Pascals.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t airflow_get_differential_pressure ( airflow_t *ctx, float *pressure );

/**
 * @brief Reads atmospheric pressure and temperature.
 * @details This function reads pressure and temperature data from sensor.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data in mBar.
 * @param[out] temperature : Temperature data in C.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t airflow_get_atmospheric_pressure ( airflow_t *ctx, float *pressure, float *temperature );

/**
 * @brief Reads status data.
 * @details This function reads status data from sensor.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[out] status : Device status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function will work only in SPI example.
 */
err_t airflow_get_status ( airflow_t *ctx, uint8_t *status );

#ifdef __cplusplus
}
#endif
#endif // AIRFLOW_H

/*! @} */ // airflow

// ------------------------------------------------------------------------ END

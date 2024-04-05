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
 * @file temphum16.h
 * @brief This file contains API for Temp&Hum 16 Click Driver.
 */

#ifndef TEMPHUM16_H
#define TEMPHUM16_H

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

/*!
 * @addtogroup temphum16 Temp&Hum 16 Click Driver
 * @brief API for configuring and manipulating Temp&Hum 16 Click driver.
 * @{
 */

/**
 * @defgroup temphum16_reg Temp&Hum 16 Registers List
 * @brief List of registers of Temp&Hum 16 Click driver.
 */

/**
 * @addtogroup temphum16_reg
 * @{
 */

/**
 * @brief Temp&Hum 16 description register.
 * @details Specified register for description of Temp&Hum 16 Click driver.
 */
#define TEMPHUM16_REG_DEVICE_ID              0x0F 
#define TEMPHUM16_REG_AVERAGE                0x10   
#define TEMPHUM16_REG_CTRL_1                 0x20    
#define TEMPHUM16_REG_CTRL_2                 0x21    
#define TEMPHUM16_REG_CTRL_3                 0x22    
#define TEMPHUM16_REG_STATUS                 0x27    
#define TEMPHUM16_REG_H_OUT_L                0x28   
#define TEMPHUM16_REG_H_OUT_H                0x29   
#define TEMPHUM16_REG_T_OUT_L                0x2A   
#define TEMPHUM16_REG_T_OUT_H                0x2B   
#define TEMPHUM16_REG_H0_RH_X2               0x30      
#define TEMPHUM16_REG_H1_RH_X2               0x31      
#define TEMPHUM16_REG_T0_DEGC_X8             0x32    
#define TEMPHUM16_REG_T1_DEGC_X8             0x33    
#define TEMPHUM16_REG_T0_T1_DEGC_H2          0x35 
#define TEMPHUM16_REG_H0_T0_OUT_L            0x36   
#define TEMPHUM16_REG_H0_T0_OUT_H            0x37   
#define TEMPHUM16_REG_H1_T0_OUT_L            0x3A   
#define TEMPHUM16_REG_H1_T0_OUT_H            0x3B   
#define TEMPHUM16_REG_T0_OUT_L               0x3C      
#define TEMPHUM16_REG_T0_OUT_H               0x3D      
#define TEMPHUM16_REG_T1_OUT_L               0x3E      
#define TEMPHUM16_REG_T1_OUT_H               0x3F

/*! @} */ // temphum16_reg

/**
 * @defgroup temphum16_set Temp&Hum 16 Registers Settings
 * @brief Settings for registers of Temp&Hum 16 Click driver.
 */

/**
 * @addtogroup temphum16_set
 * @{
 */

/**
 * @brief Temp&Hum 16 description setting.
 * @details Specified setting for description of Temp&Hum 16 Click driver.
 */
#define TEMPHUM16_PWR_MODE_POWER_DOWN        0x00
#define TEMPHUM16_PWR_MODE_CONTINUOUS        0x01
    
#define TEMPHUM16_BDU_CONTINUOUS_UPDATE      0x00
#define TEMPHUM16_BDU_NOT_UPDAT_UNTIL_READ   0x01
    
#define TEMPHUM16_ODR_ONE_SHOT_MODE          0x00
#define TEMPHUM16_ODR_1_Hz                   0x01
#define TEMPHUM16_ODR_7_Hz                   0x02
#define TEMPHUM16_ODR_12_5_Hz                0x03
    
#define TEMPHUM16_HEATER_DISABLE             0x00
#define TEMPHUM16_HEATER_ENABLE              0x01

/**
 * @brief Temp&Hum 16 device ID value.
 * @details Specified device ID value of Temp&Hum 16 Click driver.
 */
#define TEMPHUM16_DEVICE_ID                  0xBC

/**
 * @brief Temp&Hum 16 data ready.
 * @details Specified new data ready of Temp&Hum 16 Click driver.
 */
#define TEMPHUM16_DRDY                       0x01

/**
 * @brief Temp&Hum 16 device address setting.
 * @details Specified setting for device slave address selection of
 * Temp&Hum 16 Click driver.
 */
#define TEMPHUM16_SET_DEV_ADDR               0x5F

/*! @} */ // temphum16_set

/**
 * @defgroup temphum16_map Temp&Hum 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Temp&Hum 16 Click driver.
 */

/**
 * @addtogroup temphum16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Temp&Hum 16 Click to the selected MikroBUS.
 */
#define TEMPHUM16_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // temphum16_map
/*! @} */ // temphum16

/**
 * @brief Temp&Hum 16 Click driver selector.
 * @details Selects target driver interface of Temp&Hum 16 Click driver.
 */
typedef enum
{
   TEMPHUM16_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   TEMPHUM16_DRV_SEL_I2C       /**< I2C driver descriptor. */

} temphum16_drv_t;

/**
 * @brief Temp&Hum 16 Click driver interface.
 * @details Definition of driver interface of Temp&Hum 16 Click driver.
 */
typedef err_t ( *temphum16_master_io_t )( struct temphum16_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Temp&Hum 16 Click context object.
 * @details Context object definition of Temp&Hum 16 Click driver.
 */
typedef struct temphum16_s
{
    digital_in_t  rdy;       /**< Description. */

    i2c_master_t  i2c;                              /**< I2C driver object. */
    spi_master_t  spi;                              /**< SPI driver object. */

    uint8_t     slave_address;                      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                        /**< Chip select pin descriptor (used for SPI driver). */
    temphum16_drv_t  drv_sel;               /**< Master driver interface selector. */

    temphum16_master_io_t  write_f;         /**< Master write function. */
    temphum16_master_io_t  read_f;          /**< Master read function. */

} temphum16_t;

/**
 * @brief Temp&Hum 16 Click configuration object.
 * @details Configuration object definition of Temp&Hum 16 Click driver.
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

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

   temphum16_drv_t  drv_sel;                            /**< Master driver interface selector. */

} temphum16_cfg_t;

/**
 * @brief Temp&Hum 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   TEMPHUM16_OK = 0,
   TEMPHUM16_ERROR = -1

} temphum16_return_value_t;

/*!
 * @addtogroup temphum16 Temp&Hum 16 Click Driver
 * @brief API for configuring and manipulating Temp&Hum 16 Click driver.
 * @{
 */

/**
 * @brief Temp&Hum 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum16_cfg_setup ( temphum16_cfg_t *cfg );

/**
 * @brief Temp&Hum 16 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #temphum16_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #temphum16_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void temphum16_drv_interface_selection ( temphum16_cfg_t *cfg, temphum16_drv_t drv_sel );

/**
 * @brief Temp&Hum 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_init ( temphum16_t *ctx, temphum16_cfg_t *cfg );

/**
 * @brief Temp&Hum 16 default configuration function.
 * @details This function executes a default configuration of Temp&Hum 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t temphum16_default_cfg ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Write multiple bytes available only by using I2C serial interface.
 */
err_t temphum16_generic_write ( temphum16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Temp&Hum 16 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Read multiple bytes available only by using I2C serial interface. 
 */
err_t temphum16_generic_read ( temphum16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Temp&Hum 16 get device ID function.
 * @details This function reads a device ID value 
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[out] device_id : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_get_device_id ( temphum16_t *ctx, uint8_t *device_id );

/**
 * @brief Temp&Hum 16 set power mode function.
 * @details This function performs power mode
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] pwr_mode :
 *         @li @c 0x00 ( TEMPHUM16_PWR_MODE_POWER_DOWN ) - Power down mode.
 *         @li @c 0x01 ( TEMPHUM16_PWR_MODE_CONTINUOUS ) - Continuous mode for active measurement.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_power_mode ( temphum16_t *ctx, uint8_t pwr_mode );

/**
 * @brief Temp&Hum 16 set block data update mode function.
 * @details This function set block data update mode
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] bdu_mode : 
 *         @li @c 0x00 ( TEMPHUM16_BDU_CONTINUOUS_UPDATE )    -  Continuous update.
 *         @li @c 0x01 ( TEMPHUM16_BDU_NOT_UPDAT_UNTIL_READ ) - Output registers are not updated until MSB and LSB is read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_bdu_mode ( temphum16_t *ctx, uint8_t bdu_mode );

/**
 * @brief Temp&Hum 16 set output data rate function.
 * @details This function set output data rate of the humidity and temperature 
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[out]in odr : 
 *         @li @c 0x00 ( TEMPHUM16_ODR_ONE_SHOT_MODE ) -  One shot mode.
 *         @li @c 0x01 ( TEMPHUM16_ODR_1_Hz )          - Output data rate  1 Hz.
 *         @li @c 0x02 ( TEMPHUM16_ODR_7_Hz )          - Output data rate  7 Hz.
 *         @li @c 0x03 ( TEMPHUM16_ODR_12_5_Hz )       - Output data rate 12.5 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_set_odr ( temphum16_t *ctx, uint8_t odr );

/**
 * @brief Temp&Hum 16 heater function.
 * @details This function performs enable or disable heater
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] pwr_mode :
 *         @li @c 0x00 ( TEMPHUM16_HEATER_DISABLE ) - Disable.
 *         @li @c 0x01 ( TEMPHUM16_HEATER_ENABLE )  - Enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_heater ( temphum16_t *ctx, uint8_t heater_mode );

/**
 * @brief Temp&Hum 16 enable data ready interrupt function.
 * @details This function performs enable or disable heater
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_enable_data_ready_interrupt ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 get status function.
 * @details This function get status output data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[out] status : Status output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_get_status ( temphum16_t *ctx, uint8_t *status );

/**
 * @brief Temp&Hum 16 check ready function.
 * @details This function check output data ready
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return @li @c 0x00 - Data not ready.
 *         @li @c 0x01 - Data is ready.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t temphum16_check_ready ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 get humidity function.
 * @details This function read the Humidity data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[out] humidity : Humidity [ % ].
 *         @li @c 0x00 ( TEMPHUM16_HEATER_DISABLE ) - Disable.
 *         @li @c 0x01 ( TEMPHUM16_HEATER_ENABLE )  - Enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_get_humidity ( temphum16_t *ctx, float *humidity );

/**
 * @brief Temp&Hum 16 get temperature function.
 * @details This function read the Temperature data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[out] humidity : Temperature [ degree Celsius ].
 *         @li @c 0x00 ( TEMPHUM16_HEATER_DISABLE ) - Disable.
 *         @li @c 0x01 ( TEMPHUM16_HEATER_ENABLE )  - Enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum16_get_temperature ( temphum16_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM16_H

/*! @} */ // temphum16

// ------------------------------------------------------------------------ END

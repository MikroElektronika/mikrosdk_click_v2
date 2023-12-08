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
 * @file barometer6.h
 * @brief This file contains API for Barometer 6 Click Driver.
 */

#ifndef BAROMETER6_H
#define BAROMETER6_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup barometer6 Barometer 6 Click Driver
 * @brief API for configuring and manipulating Barometer 6 Click driver.
 * @{
 */

/**
 * @defgroup barometer6_reg Barometer 6 Registers List
 * @brief List of registers of Barometer 6 Click driver.
 */

/**
 * @addtogroup barometer6_reg
 * @{
 */

/**
 * @brief Barometer 6 description register.
 * @details Specified register for description of Barometer 6 Click driver.
 */
#define BAROMETER6_TEMP_TXD0            0xFC
#define BAROMETER6_TEMP_TXD1            0xFB
#define BAROMETER6_TEMP_TXD2            0xFA
#define BAROMETER6_PRESS_TXD0           0xF9
#define BAROMETER6_PRESS_TXD1           0xF8
#define BAROMETER6_PRESS_TXD2           0xF7
#define BAROMETER6_IO_SETUP             0xF5
#define BAROMETER6_CTRL_MESS            0xF4
#define BAROMETER6_DEVICE_STAT          0xF3
#define BAROMETER6_I2C_SET              0xF2
#define BAROMETER6_IIR_CNT              0XF1
#define BAROMETER6_RESET                0XE0
#define BAROMETER6_CHIP_ID              0XD1
#define BAROMETER6_COE_B00_A0_EX        0XB8
#define BAROMETER6_COE_A2_0             0XB7
#define BAROMETER6_COE_A2_1             0XB6
#define BAROMETER6_COE_A1_0             0XB5
#define BAROMETER6_COE_A1_1             0XB4
#define BAROMETER6_COE_A0_0             0XB3
#define BAROMETER6_COE_A0_1             0XB2
#define BAROMETER6_COE_BP3_0            0XB1
#define BAROMETER6_COE_BP3_1            0XB0
#define BAROMETER6_COE_B21_0            0XAF
#define BAROMETER6_COE_B21_1            0XAE
#define BAROMETER6_COE_B12_0            0XAD
#define BAROMETER6_COE_B12_1            0XAC
#define BAROMETER6_COE_BP2_0            0XAB
#define BAROMETER6_COE_BP2_1            0XAA
#define BAROMETER6_COE_B11_0            0XA9
#define BAROMETER6_COE_B11_1            0XA8
#define BAROMETER6_COE_BP1_0            0XA7
#define BAROMETER6_COE_BP1_1            0XA6
#define BAROMETER6_COE_BT2_0            0XA5
#define BAROMETER6_COE_BT2_1            0XA4
#define BAROMETER6_COE_BT1_0            0XA3
#define BAROMETER6_COE_BT1_1            0XA2
#define BAROMETER6_COE_B00_0            0XA1
#define BAROMETER6_COE_B00_1            0XA0

/*! @} */ // barometer6_reg

/**
 * @defgroup barometer6_set Barometer 6 Registers Settings
 * @brief Settings for registers of Barometer 6 Click driver.
 */

/**
 * @addtogroup barometer6_set
 * @{
 */

/**
 * @brief Barometer 6 description setting.
 * @details Specified setting for description of Barometer 6 Click driver.
 */

/**
 * @brief Barometer 6 software reset command.
 * @details Specified software reset command of Barometer 6 Click driver.
 */
#define BAROMETER6_CMD_RESET                0xE6

/**
 * @brief Barometer 6 average time for measurments.
 * @details Specified setting for average time for measurments of Barometer 6 Click driver.
 */
#define BAROMETER6_AVG_SKIP                 0x00
#define BAROMETER6_AVG_1                    0x01
#define BAROMETER6_AVG_2                    0x02
#define BAROMETER6_AVG_4                    0x03
#define BAROMETER6_AVG_8                    0x04
#define BAROMETER6_AVG_16                   0x05
#define BAROMETER6_AVG_32                   0x06
#define BAROMETER6_AVG_64                   0x07

/**
 * @brief Barometer 6 operating mode.
 * @details Specified setting for operating mode of Barometer 6 Click driver.
 */
#define BAROMETER6_SLEEP_MODE               0x00
#define BAROMETER6_FORCED_MODE_1            0x01
#define BAROMETER6_FORCED_MODE_2            0x02
#define BAROMETER6_NORMAL_MODE              0x03

/**
 * @brief Barometer 6 data ready oprions.
 * @details Specified options of data ready flag of Barometer 6 Click driver.
 */
#define BAROMETER6_DATA_NOT_READY           0x00
#define BAROMETER6_DATA_READY               0x01

/**
 * @brief Barometer 6 standby time.
 * @details Specified standby time of Barometer 6 Click driver.
 */
#define BAROMETER6_STANDBY_1ms              0x00
#define BAROMETER6_STANDBY_5ms              0x01
#define BAROMETER6_STANDBY_50ms             0x02
#define BAROMETER6_STANDBY_250ms            0x03
#define BAROMETER6_STANDBY_500ms            0x04
#define BAROMETER6_STANDBY_1s               0x05
#define BAROMETER6_STANDBY_2s               0x06
#define BAROMETER6_STANDBY_4s               0x07

/**
 * @brief Barometer 6 ID register value.
 * @details Specified chip ID of Barometer 6 Click driver.
 */
#define BAROMETER6_ID_VALUE                 0x5C

/**
 * @brief Barometer 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 6 Click driver.
 */
#define BAROMETER6_SET_DEV_ADDR_LOW     0x70
#define BAROMETER6_SET_DEV_ADDR_HIGH    0x56

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b barometer6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BAROMETER6_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define BAROMETER6_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // barometer6_set

/**
 * @defgroup barometer6_map Barometer 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 6 Click driver.
 */

/**
 * @addtogroup barometer6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 6 Click to the selected MikroBUS.
 */
#define BAROMETER6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST )
/*! @} */ // barometer6_map
/*! @} */ // barometer6

/**
 * @brief Barometer 6 Click driver selector.
 * @details Selects target driver interface of Barometer 6 Click driver.
 */
typedef enum
{
    BAROMETER6_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    BAROMETER6_DRV_SEL_I2C       /**< I2C driver descriptor. */

} barometer6_drv_t;

/**
 * @brief Barometer 6 Click driver interface.
 * @details Definition of driver interface of Barometer 6 Click driver.
 */
typedef err_t ( *barometer6_master_io_t )( struct barometer6_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Barometer 6 Click context object.
 * @details Context object definition of Barometer 6 Click driver.
 */
typedef struct barometer6_s
{
    digital_out_t  rst;                      /**< Reset. */

    i2c_master_t  i2c;                       /**< I2C driver object. */
    spi_master_t  spi;                       /**< SPI driver object. */

    uint8_t     slave_address;               /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                 /**< Chip select pin descriptor (used for SPI driver). */
    barometer6_drv_t  drv_sel;               /**< Master driver interface selector. */

    barometer6_master_io_t  write_f;         /**< Master write function. */
    barometer6_master_io_t  read_f;          /**< Master read function. */
    
    float coef_a0;
    float coef_a1;
    float coef_a2;
    
    float coef_b00;
    float coef_bt1;
    float coef_bp1;
    float coef_b11;
    float coef_bt2;
    float coef_bp2;
    float coef_b12;
    float coef_b21;
    float coef_bp3;
    
} barometer6_t;

/**
 * @brief Barometer 6 Click configuration object.
 * @details Configuration object definition of Barometer 6 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  rst;        /**< Reset. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    barometer6_drv_t  drv_sel;                   /**< Master driver interface selector. */

} barometer6_cfg_t;

/**
 * @brief Barometer 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER6_OK = 0,
    BAROMETER6_ERROR = -1

} barometer6_return_value_t;

/*!
 * @addtogroup barometer6 Barometer 6 Click Driver
 * @brief API for configuring and manipulating Barometer 6 Click driver.
 * @{
 */

/**
 * @brief Barometer 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer6_cfg_setup ( barometer6_cfg_t *cfg );

/**
 * @brief Barometer 6 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #barometer6_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #barometer6_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void barometer6_drv_interface_selection ( barometer6_cfg_t *cfg, barometer6_drv_t drv_sel );

/**
 * @brief Barometer 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t barometer6_init ( barometer6_t *ctx, barometer6_cfg_t *cfg );

/**
 * @brief Barometer 6 default configuration function.
 * @details This function executes a default configuration of Barometer 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void barometer6_default_cfg ( barometer6_t *ctx );

/**
 * @brief Barometer 6 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t barometer6_generic_write ( barometer6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 6 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t barometer6_generic_read ( barometer6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 6 data writing function.
 * @details This function writes a byte data into the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 */
void barometer6_write_register ( barometer6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Barometer 6 data reading function.
 * @details This function reads a 16 bits of data starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return Nothing.
 */
void barometer6_read_register ( barometer6_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Barometer 6 Id reading function.
 * @details This function reads a chip id from the CHIP_ID register.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return Nothing.
 */
void barometer6_read_id ( barometer6_t *ctx, uint8_t *data_out );

/**
 * @brief Barometer 6 software reset function.
 * @details This function is used for performing software reset of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @return Nothing.
 */
void barometer6_software_reset ( barometer6_t *ctx );

/**
 * @brief Barometer 6 hardware reset function.
 * @details This function is used for performing hardware reset of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @return Nothing.
 */
void barometer6_hardware_reset ( barometer6_t *ctx );

/**
 * @brief Barometer 6 set average data function.
 * @details This function is used for setting average data of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] temp_avg : Average data for the temperaature.
 * @param[in] pressure_avg : Average data for the preassure.
 * @return Nothing.
 * 
 * @note If you set up an average below BAROMETER6_AVG_4, data read for temperature and pressure 
 *       becomes 23bit for BAROMETER6_AVG_2, and 22bit for BAROMETER6_AVG_1.  
 */
void barometer6_set_avrege ( barometer6_t *ctx, uint8_t temp_avg, uint8_t pressure_avg );

/**
 * @brief Barometer 6 set operation mode function.
 * @details This function is used for setting operating mode of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] mode : Selected operation mode.
 * @return Nothing.
 */
void barometer6_set_mode ( barometer6_t *ctx, uint8_t mode );

/**
 * @brief Barometer 6 set standby time function.
 * @details This function is used for setting standby time of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] t_standby : Selected standby time.
 * @return Nothing.
 */
void barometer6_set_standby_time ( barometer6_t *ctx, uint8_t t_standby );

/**
 * @brief Barometer 6 check if data is ready function.
 * @details This function is used for checking if data is ready to be read.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @return @li @c 0 - Data not ready,
 *         @li @c 1 - Data is ready.
 */
uint8_t barometer6_check_ready ( barometer6_t *ctx );

/**
 * @brief Barometer 6 read raw temperature function.
 * @details This function is used for reading raw temperature walue of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] data_out : Raw temperature data.
 * @return Nothing.
 */
void barometer6_read_raw_temp ( barometer6_t *ctx, int32_t *data_out );

/**
 * @brief Barometer 6 read raw pressure function.
 * @details This function is used for reading raw pressure walue of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] data_out : Raw pressure data.
 * @return Nothing.
 */
void barometer6_read_raw_pressure ( barometer6_t *ctx, float *data_out );

/**
 * @brief Barometer 6 read conpensation coefficients data function.
 * @details This function is used for reading conpensation coefficient's data of 
 * the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return Nothing.
 */
void barometer6_read_conp_coef ( barometer6_t *ctx, uint8_t reg, int16_t *data_out );

/**
 * @brief Barometer 6 calculate conpensation coefficients data function.
 * @details This function is used for calculate conpensation coefficient's data of 
 * the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] a_coef : Conversion factor A.
 * @param[in] s_coef : Conversion factor S.
 * @param[out] data_out : Output read data.
 * @return Nothing.
 */
void barometer6_get_conp_coef ( barometer6_t *ctx, uint8_t reg, float a_coef, float s_coef, 
                                float *data_out );

/**
 * @brief Barometer 6 calculate a0 and b00 conpensation coefficients data function.
 * @details This function is used for calculate a0 and b00 conpensation coefficient's
 * data of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] coef_a0 : Conversion factor a0.
 * @param[out] coef_b00 : Conversion factor b00.
 * @return Nothing.
 */
void barometer6_get_a0_b00_coef ( barometer6_t *ctx, float *coef_a0, float *coef_b00 );

/**
 * @brief Barometer 6 get all conpensation coefficients data function.
 * @details This function is used for getting all conpensation coefficients
 * data of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @return Nothing.
 */
void barometer6_get_conpesation_coe ( barometer6_t *ctx );

/**
 * @brief Barometer 6 get temperature data function.
 * @details This function is used for temperature data of the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] temp_out : Output read data.
 * @return Nothing.
 */
void barometer6_get_temperature_data ( barometer6_t *ctx, float *temp_out );

/**
 * @brief Barometer 6 get temperature value function.
 * @details This function is used for temperature value in degrees celsius of 
 * the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] temp_out : Output read data in degrees celsius.
 * @return Nothing.
 */
void barometer6_read_temperature_value ( barometer6_t *ctx, float *temp_out );

/**
 * @brief Barometer 6 get preassure data function.
 * @details This function is used for preassure data in degrees celsius of 
 * the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] press_out : Output read data.
 * @return Nothing.
 */
void barometer6_read_preassure_data ( barometer6_t *ctx, float *press_out );

/**
 * @brief Barometer 6 get preassure mBar function.
 * @details This function is used for preassure mBar in degrees celsius of 
 * the Barometer 6 Clock Board.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[out] press_out : Output read data in mBar.
 * @return Nothing.
 */
void barometer6_read_preassure_value ( barometer6_t *ctx, float *press_out );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER6_H

/*! @} */ // barometer6

// ------------------------------------------------------------------------ END

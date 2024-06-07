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
 * @file inclinometer3.h
 * @brief This file contains API for Inclinometer 3 Click Driver.
 */

#ifndef INCLINOMETER3_H
#define INCLINOMETER3_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup inclinometer3 Inclinometer 3 Click Driver
 * @brief API for configuring and manipulating Inclinometer 3 Click driver.
 * @{
 */

/**
 * @defgroup inclinometer3_reg Inclinometer 3 Registers List
 * @brief List of registers of Inclinometer 3 Click driver.
 */

/**
 * @addtogroup inclinometer3_reg
 * @{
 */

/**
 * @brief Inclinometer 3 description register.
 * @details Specified register for description of Inclinometer 3 Click driver.
 */
#define INCLINOMETER3_REG_ACC_X                0x01
#define INCLINOMETER3_REG_ACC_Y                0x02
#define INCLINOMETER3_REG_TEMP                 0x05
#define INCLINOMETER3_REG_STATUS               0x06
#define INCLINOMETER3_REG_ERR_FLAG1            0x07
#define INCLINOMETER3_REG_ERR_FLAG2            0x08
#define INCLINOMETER3_REG_MODE                 0x0D
#define INCLINOMETER3_REG_WHOAMI               0x10
#define INCLINOMETER3_REG_SERIAL1              0x19
#define INCLINOMETER3_REG_SERIAL2              0x1A
#define INCLINOMETER3_REG_SELBANK              0x1F

/**
 * @brief Inclinometer 3 description operation commands.
 * @details Specified operation commands for description of Inclinometer 3 Click driver.
 */
#define INCLINOMETER3_CMD_READ_ACC_X           0x040000F7ul
#define INCLINOMETER3_CMD_READ_ACC_Y           0x080000FDul
#define INCLINOMETER3_CMD_READ_TEMP            0x140000EFul
#define INCLINOMETER3_CMD_READ_STATUS          0x180000E5ul
#define INCLINOMETER3_CMD_READ_ERR_FLAG1       0x1C0000E3ul
#define INCLINOMETER3_CMD_READ_ERR_FLAG2       0x200000C1ul
#define INCLINOMETER3_CMD_READ_CMD             0x340000DFul
#define INCLINOMETER3_CMD_CHANGE_TO_MODE_A     0xB400001Ful
#define INCLINOMETER3_CMD_CHANGE_TO_MODE_B     0xB4000338ul
#define INCLINOMETER3_CMD_POWER_DOWN           0xB400046Bul
#define INCLINOMETER3_CMD_WAKE_UP              0xB400001Ful
#define INCLINOMETER3_CMD_SW_RESET             0xB4002098ul
#define INCLINOMETER3_CMD_READ_WHOAMI          0x40000091ul
#define INCLINOMETER3_CMD_READ_SERIAL1         0x640000A7ul
#define INCLINOMETER3_CMD_READ_SERIAL2         0x680000ADul
#define INCLINOMETER3_CMD_READ_CURRENT_BANK    0x7C0000B3ul
#define INCLINOMETER3_CMD_SWITCH_TO_BANK_0     0xFC000073ul
#define INCLINOMETER3_CMD_SWITCH_TO_BANK_1     0xFC00016Eul


/*! @} */ // inclinometer3_reg

/**
 * @defgroup inclinometer3_set Inclinometer 3 Registers Settings
 * @brief Settings for registers of Inclinometer 3 Click driver.
 */

/**
 * @addtogroup inclinometer3_set
 * @{
 */

/**
 * @brief Inclinometer 3 device ID data value.
 * @details Device ID data value of Inclinometer 3 Click driver.
 */
#define INCLINOMETER3_WHOAMI                   0xE0

/**
 * @brief Inclinometer 3 memory banks and modes selection.
 * @details Memory banks and modes selection of Inclinometer 3 Click driver.
 */
#define INCLINOMETER3_SEL_BANK_0               0
#define INCLINOMETER3_SEL_BANK_1               1
#define INCLINOMETER3_SEL_MODE_A               0
#define INCLINOMETER3_SEL_MODE_B               1

/**
 * @brief Inclinometer 3 acceel and temperature sensitivity data values.
 * @details Acceel sensitivity data values of Inclinometer 3 Click driver.
 */
#define INCLINOMETER3_ACC_SENS_MODE_A          32.768f
#define INCLINOMETER3_ACC_SENS_MODE_B          16.384f
#define INCLINOMETER3_TEMP_SENS                18.9f
#define INCLINOMETER3_TEMP_CONVERT             273.0f

/**
 * @brief Inclinometer 3 return status bits.
 * @details return status bits of Inclinometer 3 Click driver.
 */
#define INCLINOMETER3_RTN_STS_PROGRESS         0x00
#define INCLINOMETER3_RTN_STS_NORMAL           0x01
#define INCLINOMETER3_RTN_STS_ERROR            0x03
#define INCLINOMETER3_RTN_STS_BITMASK          0x03

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b inclinometer3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define INCLINOMETER3_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define INCLINOMETER3_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // inclinometer3_set

/**
 * @defgroup inclinometer3_map Inclinometer 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Inclinometer 3 Click driver.
 */

/**
 * @addtogroup inclinometer3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Inclinometer 3 Click to the selected MikroBUS.
 */
#define INCLINOMETER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // inclinometer3_map
/*! @} */ // inclinometer3

/**
 * @brief Inclinometer 3 Click context object.
 * @details Context object definition of Inclinometer 3 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t rtn_sts;             /**< Return status bits. */
    float sensitivity;           /**< Accel sensitivity. */

} inclinometer3_t;

/**
 * @brief Inclinometer 3 Click configuration object.
 * @details Configuration object definition of Inclinometer 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} inclinometer3_cfg_t;

/**
 * @brief Inclinometer 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    INCLINOMETER3_OK = 0,
    INCLINOMETER3_ERROR = -1

} inclinometer3_return_value_t;

/*!
 * @addtogroup inclinometer3 Inclinometer 3 Click Driver
 * @brief API for configuring and manipulating Inclinometer 3 Click driver.
 * @{
 */

/**
 * @brief Inclinometer 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #inclinometer3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void inclinometer3_cfg_setup ( inclinometer3_cfg_t *cfg );

/**
 * @brief Inclinometer 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #inclinometer3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_init ( inclinometer3_t *ctx, inclinometer3_cfg_t *cfg );

/**
 * @brief Inclinometer 3 default configuration function.
 * @details This function executes a default configuration of Inclinometer 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t inclinometer3_default_cfg ( inclinometer3_t *ctx );

/**
 * @brief Inclinometer 3 data writing function.
 * @details This function writes a 16-bit data to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_reg_write ( inclinometer3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Inclinometer 3 data reading function.
 * @details This function reads 16-bit data from the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_reg_read ( inclinometer3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Inclinometer 3 command writing function.
 * @details This function writes a desired command - SPI frame 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[in] op_cmd : Operation command - SPI frame.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_cmd_write ( inclinometer3_t *ctx, uint32_t op_cmd );

/**
 * @brief Inclinometer 3 command reading function.
 * @details This function reads 32-bit data by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[in] op_cmd : Operation command - SPI frame.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_cmd_read ( inclinometer3_t *ctx, uint32_t op_cmd, uint32_t *data_out );

/**
 * @brief Inclinometer 3 set bank function.
 * @details This function is used to select the desired memory bank
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[in] bank : Memory bank selection [0-1].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_set_bank ( inclinometer3_t *ctx, uint8_t bank );

/**
 * @brief Inclinometer 3 software reset function.
 * @details This function performs sensor software reset
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_sw_reset ( inclinometer3_t *ctx );

/**
 * @brief Inclinometer 3 get sensor ID function.
 * @details This function reads the sensor ID data value
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[out] device_id : Sensor component identification.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_get_sensor_id ( inclinometer3_t *ctx, uint8_t *device_id );

/**
 * @brief Inclinometer 3 get status function.
 * @details This function reads the status data value
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[out] status : Status data frame.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_get_status ( inclinometer3_t *ctx, uint32_t *status );

/**
 * @brief Inclinometer 3 set mode function.
 * @details This function is used to select the desired operation mode
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[in] mode : Operation mode [0-1].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_set_mode ( inclinometer3_t *ctx, uint8_t mode );

/**
 * @brief Inclinometer 3 get the accel data function.
 * @details This function reads the accelerometer raw data 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[out] x_data : X-axis raw data.
 * @param[out] y_data : Y-axis raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_get_axes_data ( inclinometer3_t *ctx, int16_t *x_data, int16_t *y_data );

/**
 * @brief Inclinometer 3 get the accel sensor axes function.
 * @details This function reads the accelerometer sensor axes data 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[out] x_data : Linear acceleration X-axis output data object [mg].
 * @param[out] y_data : Linear acceleration Y-axis output data object [mg].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_get_axes ( inclinometer3_t *ctx, float *x_axes, float *y_axes );

/**
 * @brief Inclinometer 3 get the temperature data function.
 * @details This function reads the temperature raw data 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[out] x_dattemp_dataa : Temperature raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_get_temp_data ( inclinometer3_t *ctx, int16_t *temp_data );

/**
 * @brief Inclinometer 3 get the temperature function.
 * @details This function reads the temperature measurement data
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer3_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data [degree Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer3_get_temperature ( inclinometer3_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // INCLINOMETER3_H

/*! @} */ // inclinometer3

// ------------------------------------------------------------------------ END

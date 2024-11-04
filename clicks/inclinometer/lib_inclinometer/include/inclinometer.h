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
 * @file inclinometer.h
 * @brief This file contains API for Inclinometer Click Driver.
 */

#ifndef INCLINOMETER_H
#define INCLINOMETER_H

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

/*!
 * @addtogroup inclinometer Inclinometer Click Driver
 * @brief API for configuring and manipulating Inclinometer Click driver.
 * @{
 */

/**
 * @defgroup inclinometer_reg Inclinometer Registers List
 * @brief List of registers of Inclinometer Click driver.
 */

/**
 * @addtogroup inclinometer_reg
 * @{
 */

/**
 * @brief Inclinometer control register.
 * @details Specified register for control of Inclinometer Click driver.
 */
#define INCLINOMETER_REG_ACC_X              0x01
#define INCLINOMETER_REG_ACC_Y              0x02
#define INCLINOMETER_REG_ACC_Z              0x03
#define INCLINOMETER_REG_STO                0x04
#define INCLINOMETER_REG_TEMP               0x05
#define INCLINOMETER_REG_STATUS             0x06
#define INCLINOMETER_REG_ERR_FLAG1          0x07
#define INCLINOMETER_REG_ERR_FLAG2          0x08
#define INCLINOMETER_REG_ANG_X              0x09
#define INCLINOMETER_REG_ANG_Y              0x0A
#define INCLINOMETER_REG_ANG_Z              0x0B
#define INCLINOMETER_REG_ANG_CTRL           0x0C
#define INCLINOMETER_REG_MODE               0x0D
#define INCLINOMETER_REG_WHOAMI             0x10
#define INCLINOMETER_REG_SERIAL1            0x19
#define INCLINOMETER_REG_SERIAL2            0x1A
#define INCLINOMETER_REG_SELBANK            0x1F

/*! @} */ // inclinometer_reg

/**
 * @defgroup inclinometer_cmd Inclinometer Commands
 * @brief Commands of Inclinometer Click driver.
 */

/**
 * @addtogroup inclinometer_cmd
 * @{
 */

/**
 * @brief Inclinometer control commands.
 * @details Specified commands for control of Inclinometer Click driver.
 */
#define INCLINOMETER_CMD_READ_ACC_X         0x040000F7
#define INCLINOMETER_CMD_READ_ACC_Y         0x080000FD
#define INCLINOMETER_CMD_READ_ACC_Z         0x0C0000FB
#define INCLINOMETER_CMD_READ_STO           0x100000E9
#define INCLINOMETER_CMD_EN_ANGLE_OUT       0xB0001F6F
#define INCLINOMETER_CMD_READ_ANG_X         0x240000C7
#define INCLINOMETER_CMD_READ_ANG_Y         0x280000CD
#define INCLINOMETER_CMD_READ_ANG_Z         0x2C0000CB
#define INCLINOMETER_CMD_READ_TEMP          0x140000EF
#define INCLINOMETER_CMD_READ_STATUS        0x180000E5
#define INCLINOMETER_CMD_READ_ERR_FLAG1     0x1C0000E3
#define INCLINOMETER_CMD_READ_ERR_FLAG2     0x200000C1
#define INCLINOMETER_CMD_READ_MODE          0x340000DF
#define INCLINOMETER_CMD_CHANGE_TO_MODE1    0xB400001F
#define INCLINOMETER_CMD_CHANGE_TO_MODE2    0xB4000102
#define INCLINOMETER_CMD_CHANGE_TO_MODE3    0xB4000225
#define INCLINOMETER_CMD_CHANGE_TO_MODE4    0xB4000338
#define INCLINOMETER_CMD_POWER_DOWN         0xB400046B
#define INCLINOMETER_CMD_WAKE_UP            0xB400001F
#define INCLINOMETER_CMD_SW_RESET           0xB4002098
#define INCLINOMETER_CMD_READ_WHOAMI        0x40000091
#define INCLINOMETER_CMD_READ_SERIAL1       0x640000A7
#define INCLINOMETER_CMD_READ_SERIAL2       0x680000AD
#define INCLINOMETER_CMD_READ_CURRENT_BANK  0x7C0000B3
#define INCLINOMETER_CMD_SWITCH_TO_BANK0    0xFC000073
#define INCLINOMETER_CMD_SWITCH_TO_BANK1    0xFC00016E

/*! @} */ // inclinometer_cmd

/**
 * @defgroup inclinometer_map Inclinometer MikroBUS Map
 * @brief MikroBUS pin mapping of Inclinometer Click driver.
 */

/**
 * @addtogroup inclinometer_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Inclinometer Click to the selected MikroBUS.
 */
#define INCLINOMETER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); 

/*! @} */ // inclinometer_map
/*! @} */ // inclinometer

/**
 * @brief Inclinometer Click context object.
 * @details Context object definition of Inclinometer Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t rs;                 /**< Return status. */
    float resolution;           /**< Resolution. */

} inclinometer_t;

/**
 * @brief Inclinometer Click configuration object.
 * @details Configuration object definition of Inclinometer Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} inclinometer_cfg_t;

/**
 * @brief Inclinometer Click axis/angle data object.
 * @details Axis/Angle data object of Inclinometer Click driver.
 */
typedef struct
{
    float x;    /**< X Axis/Angle data. */
    float y;    /**< Y Axis/Angle data. */
    float z;    /**< Z Axis/Angle data. */

} inclinometer_accel_t;

/**
 * @brief Inclinometer Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   INCLINOMETER_OK = 0,
   INCLINOMETER_ERROR = -1,
   INCLINOMETER_CRC_ERROR = -2

} inclinometer_return_value_t;

/*!
 * @addtogroup inclinometer Inclinometer Click Driver
 * @brief API for configuring and manipulating Inclinometer Click driver.
 * @{
 */

/**
 * @brief Inclinometer configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #inclinometer_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void inclinometer_cfg_setup ( inclinometer_cfg_t *cfg );

/**
 * @brief Inclinometer initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #inclinometer_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer_init ( inclinometer_t *ctx, inclinometer_cfg_t *cfg );

/**
 * @brief Inclinometer default configuration function.
 * @details This function executes a default configuration of Inclinometer
 * Click board.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t inclinometer_default_cfg ( inclinometer_t *ctx );

/**
 * @brief Data writing function.
 * @details This function writes a data to register.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t inclinometer_generic_write ( inclinometer_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Data reading function.
 * @details This function reads a data from register.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[in] reg :Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t inclinometer_generic_read ( inclinometer_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief CMD writing function.
 * @details This function writes predefined command.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[in] cmd : Predefined command.
 * See #inclinometer_cmd def group for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t inclinometer_cmd_write ( inclinometer_t *ctx, uint32_t cmd );

/**
 * @brief CMD reading function.
 * @details This function reads a data from predefined command.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[in] cmd : Predefined command.
 * See #inclinometer_cmd def group for detailed explanation.
 * @param[out] cmd_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t inclinometer_cmd_read ( inclinometer_t *ctx, uint32_t cmd, uint16_t *cmd_data );

/**
 * @brief Temperature reading.
 * @details This function reads a temperature data from device.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[out] temperature : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t inclinometer_get_temperature ( inclinometer_t *ctx, float *temperature );

/**
 * @brief Axes reading.
 * @details This function reads a axes data from device.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[out] axes_data : Output read data.
 * See #inclinometer_accel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t inclinometer_get_axes ( inclinometer_t *ctx, inclinometer_accel_t *axes_data );

/**
 * @brief Angle reading.
 * @details This function reads a angle data from device.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[out] angle_data : Output read data.
 * See #inclinometer_accel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t inclinometer_get_angle ( inclinometer_t *ctx, inclinometer_accel_t *angle_data );

#ifdef __cplusplus
}
#endif
#endif // INCLINOMETER_H

/*! @} */ // inclinometer

// ------------------------------------------------------------------------ END

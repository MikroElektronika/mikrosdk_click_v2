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
 * @file amrangle.h
 * @brief This file contains API for AMR Angle Click Driver.
 */

#ifndef AMRANGLE_H
#define AMRANGLE_H

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
#include "drv_analog_in.h"
#include "math.h"
    
/*!
 * @addtogroup amrangle AMR Angle Click Driver
 * @brief API for configuring and manipulating AMR Angle Click driver.
 * @{
 */

/**
 * @defgroup sel_toolchain AMR Angle toolchain select
 * @brief List of working boards for AMR Angle gain control.
 */

/**
 * @addtogroup sel_toolchain
 * @{
 */

/**
 * @brief AMR Angle arm toolchain.
 * @details Select this if using Fusion for ARM v8 board.
 */
#define AMRANGLE_ARM_TOOLCHAIN                                  0x00

/**
 * @brief AMR Angle pic toolchain.
 * @details Select this if using EasyPIC PRO v8 board.
 */
#define AMRANGLE_PIC_TOOLCHAIN                                  0x01

/*! @} */ // sel_toolchain

/**
 * @defgroup gain_control AMR Angle gain control mode list
 * @brief List of possible modes of AMR Angle gain control.
 */

/**
 * @addtogroup gain_control
 * @{
 */

/**
 * @brief AMR Angle gain control enable.
 * @details Enables the gain control mode of AMR Angle click.
 */
#define AMRANGLE_GAIN_CONTROL_EN                                0x01

/**
 * @brief AMR Angle gain control disable.
 * @details Disables the gain control mode of AMR Angle click.
 */
#define AMRANGLE_GAIN_CONTROL_DIS                               0x00

/*! @} */ // gain_control

/**
 * @defgroup pd_state AMR Angle power down state mode list
 * @brief List of possible modes for AMR Angle power down.
 */

/**
 * @addtogroup pd_state
 * @{
 */

/**
 * @brief AMR Angle power down enable.
 * @details Shuts down the device of AMR Angle click.
 */
#define AMRANGLE_POWER_DOWN_EN                                  0x01

/**
 * @brief AMR Angle power down disable.
 * @details Powers up the device of AMR Angle click.
 */
#define AMRANGLE_POWER_DOWN_DIS                                 0x00

/*! @} */ // pd_state

/**
 * @defgroup amrangle_map AMR Angle MikroBUS Map
 * @brief MikroBUS pin mapping of AMR Angle Click driver.
 */

/**
 * @addtogroup amrangle_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AMR Angle Click to the selected MikroBUS.
 */
#define AMRANGLE_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.gc   = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.pd   = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // amrangle_map
/*! @} */ // amrangle

/**
 * @brief AMR Angle Click context object.
 * @details Context object definition of AMR Angle Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  gc;                  /**< Digital output pin for gain control mode. */
    digital_out_t  pd;                  /**< Digital output pin for power down function. */

    // Modules
    
    analog_in_t   adc;                  /**< ADC driver object. */

    spi_master_t  spi;                  /**< SPI driver object. */

    pin_name_t    chip_select;          /**< Chip select pin descriptor (used for SPI driver). */

} amrangle_t;

/**
 * @brief AMR Angle Click configuration object.
 * @details Configuration object definition of AMR Angle Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

     pin_name_t  an;                    /**< Vtemp analog pin. */
     pin_name_t  gc;                    /**< Digital output pin for gain control mode. */
     pin_name_t  pd;                    /**< Digital output pin for power down function. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */
    
    analog_in_resolution_t             resolution;       /**< ADC resolution. */
    float                              vref;             /**< ADC reference voltage. */

} amrangle_cfg_t;

/**
 * @brief AMR Angle Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMRANGLE_OK = 0,
    AMRANGLE_ERROR = -1

} amrangle_return_value_t;

/*!
 * @addtogroup amrangle AMR Angle Click Driver
 * @brief API for configuring and manipulating AMR Angle Click driver.
 * @{
 */

/**
 * @brief AMR Angle configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #amrangle_cfg_t object definition for detailed explanation.
 * @param[in] sel_toolchain : Selected toolchain.
 *         @li @c 0x00 ( AMRANGLE_ARM_TOOLCHAIN ) - Insert for ARM board,
 *         @li @c 0x01 ( AMRANGLE_PIC_TOOLCHAIN ) - Insert for PIC board.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void amrangle_cfg_setup ( amrangle_cfg_t *cfg, uint8_t sel_toolchain );

/**
 * @brief AMR Angle initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #amrangle_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #amrangle_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle_init ( amrangle_t *ctx, amrangle_cfg_t *cfg );

/**
 * @brief AMR Angle default configuration function.
 * @details This function executes a default configuration of AMR Angle
 * click board.
 * @param[in] ctx : Click context object.
 * See #amrangle_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void amrangle_default_cfg ( amrangle_t *ctx );

/**
 * @brief AMR Angle read angle function.
 * @details This function reads an angle in degrees.
 * @param[in] ctx : Click context object.
 * See #amrangle_t object definition for detailed explanation.
 * @return Angle in degrees.
 *
 * @note None.
 */
float amrangle_angle_read ( amrangle_t *ctx );

/**
 * @brief AMR Angle read vtp voltage function.
 * @details This function reads analog voltage from vtp pin.
 * @param[in] ctx : Click context object.
 * See #amrangle_t object definition for detailed explanation.
 * @param[out] vtp_volts : Analog pin voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle_read_vtp_voltage ( amrangle_t *ctx, float *vtp_volts );

/**
 * @brief AMR Angle read temperature function.
 * @details This function returns calculated temperature using
 * vtp pin voltage. The calculation is performed by extracting
 * constants from linear function using VTEMP Output Voltage vs 
 * Temperature graph ( ADA4571 datasheet - Figure 21. ).
 * @param[in] ctx : Click context object.
 * See #amrangle_t object definition for detailed explanation.
 * @return Temperature in degrees celsius.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
float amrangle_read_vtp_temp ( amrangle_t *ctx );

/**
 * @brief AMR Angle gain control mode function.
 * @details This function sets the gain control mode pin which
 * is used to compensate the sensor amplitude output for reduction
 * of temperature variation.
 * @param[in] ctx : Click context object.
 * See #amrangle_t object definition for detailed explanation.
 * @param[in] state : Gain control state.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void amrangle_gain_control_mode ( amrangle_t *ctx, uint8_t gain_control );

/**
 * @brief AMR Angle power down function.
 * @details This function controls the power down pin which can
 * be used to shut down the device.
 * @param[in] ctx : Click context object.
 * See #amrangle_t object definition for detailed explanation.
 * @param[in] state : Power down state.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void amrangle_power_down_pin ( amrangle_t *ctx, uint8_t pd_state );

#ifdef __cplusplus
}
#endif
#endif // AMRANGLE_H

/*! @} */ // amrangle

// ------------------------------------------------------------------------ END

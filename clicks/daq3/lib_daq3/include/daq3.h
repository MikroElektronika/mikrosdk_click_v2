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
 * @file daq3.h
 * @brief This file contains API for DAQ 3 Click Driver.
 */

#ifndef DAQ3_H
#define DAQ3_H

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
 * @addtogroup daq3 DAQ 3 Click Driver
 * @brief API for configuring and manipulating DAQ 3 Click driver.
 * @{
 */

/**
 * @defgroup daq3_reg DAQ 3 Registers List
 * @brief List of registers of DAQ 3 Click driver.
 */

/**
 * @addtogroup daq3_reg
 * @{
 */

/**
 * @brief DAQ 3 description register.
 * @details Specified register for description of DAQ 3 Click driver.
 */
#define DAQ3_REG_0      0x00
#define DAQ3_REG_1      0x01
#define DAQ3_REG_2      0x02
#define DAQ3_REG_3      0x03
#define DAQ3_REG_CMD    0x14

/*! @} */ // daq3_reg

/**
 * @defgroup daq3_set DAQ 3 Registers Settings
 * @brief Settings for registers of DAQ 3 Click driver.
 */

/**
 * @addtogroup daq3_set
 * @{
 */

/**
 * @brief DAQ 3 description setting.
 * @details Specified setting for description of DAQ 3 Click driver.
 */
#define DAQ3_CMD_WEN          0x00
#define DAQ3_CMD_REG_READ     0x40
#define DAQ3_CMD_REG_WRITE    0x00

/*! @} */ // daq3_set

/**
 * @addtogroup reg_cmd_default
 * @{
 */

/**
 * @brief DAQ 3 command register default setting.
 * @details Specified default setting for command register of DAQ 3 Click driver.
 */
#define DAQ3_CMD_REG_DEFAULT     0xE1

/*! @} */ // daq3_set

/**
 * @addtogroup mode
 * @{
 */

/**
 * @brief DAQ 3 power mode setting.
 * @details Specified setting for power mode 
 * for the Fully Differential ADC Driver of DAQ 3 Click driver.
 */
#define DAQ3_LOW_POWER_MODE           0x00
#define DAQ3_FULL_PERFORMANCE_MODE    0x01

/*! @} */ // mode

/**
 * @addtogroup pd_ref
 * @{
 */

/**
 * @brief DAQ 3 power-down reference buffer setting.
 * @details Specified setting for power-down reference buffer
 * of DAQ 3 Click driver.
 */
#define DAQ3_PD_REF_POWER_DOWN    0x00
#define DAQ3_PD_REF_POWER_UP      0x01

/*! @} */ // pd_ref

/**
 * @addtogroup pd_amp
 * @{
 */

/**
 * @brief DAQ 3 power-down amplifier setting.
 * @details Specified setting for power-down amplifier
 * of DAQ 3 Click driver.
 */
#define DAQ3_PD_AMP_POWER_DOWN        0x00
#define DAQ3_PD_AMP_POWER_UP          0x01

/*! @} */ // pd_amp

/**
 * @defgroup daq3_map DAQ 3 MikroBUS Map
 * @brief MikroBUS pin mapping of DAQ 3 Click driver.
 */

/**
 * @addtogroup daq3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAQ 3 Click to the selected MikroBUS.
 */
#define DAQ3_MAP_MIKROBUS( cfg, mikrobus )          \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.dam = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.dre = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.mod = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // daq3_map
/*! @} */ // daq3

/**
 * @brief DAQ 3 Click context object.
 * @details Context object definition of DAQ 3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  dam;      /**< Power-Down Amplifier.                             */
    digital_out_t  dre;      /**< Power-Down Reference Buffer.                      */
    digital_out_t  mod;      /**< Power Mode for the Fully Differential ADC Driver. */

    // Input pins

    digital_in_t  int_pin;   /**< State of SDO on Power-Up.                         */

    // Modules

    spi_master_t  spi;       /**< SPI driver object.                                */

    pin_name_t  chip_select; /**< Chip select pin descriptor (used for SPI driver). */

} daq3_t;

/**
 * @brief DAQ 3 Click configuration object.
 * @details Configuration object definition of DAQ 3 Click driver.
 */
typedef struct
{
    uint8_t    en_six_st_bits; /**< Enable six status bits.   */
    uint8_t    span_comp;      /**< Span compression.         */
    uint8_t    high_z_mode;    /**< High-Z mode.              */
    uint8_t    turbo_mode;     /**< Turbo mode.               */
    uint8_t    ov_clamp_flag;  /**< OV clamp flag - read only */

} daq3_reg_cfg_t;

/**
 * @brief DAQ 3 Click configuration object.
 * @details Configuration object definition of DAQ 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;     /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;     /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;      /**< Clock pin descriptor for SPI driver.                       */
    pin_name_t  cs;       /**< Chip select pin descriptor for SPI driver.                 */

    // Additional gpio pins

    pin_name_t  dam;      /**< Power-Down Amplifier.                                      */
    pin_name_t  dre;      /**< Power-Down Reference Buffer.                               */
    pin_name_t  mod;      /**< Power Mode for the Fully Differential ADC Driver.          */
    pin_name_t  int_pin;  /**< State of SDO on Power-Up.                                  */

    // static variable

    uint32_t                           spi_speed;   /**< SPI serial speed.                */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode.                 */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity.        */

} daq3_cfg_t;

/*!
 * @addtogroup daq3 DAQ 3 Click Driver
 * @brief API for configuring and manipulating DAQ 3 Click driver.
 * @{
 */

/**
 * @brief DAQ 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #daq3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void daq3_cfg_setup ( daq3_cfg_t *cfg );

/**
 * @brief DAQ 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #daq3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t daq3_init ( daq3_t *ctx, daq3_cfg_t *cfg );

/**
 * @brief DAQ 3 default configuration function.
 * @details This function executes a default configuration of DAQ 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void daq3_default_cfg ( daq3_t *ctx );

/**
 * @brief DAQ 3 set power mode function.
 * @details This function set power mode for the fully differential ADC Driver
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board.
 * @param[out] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] mode   
 * Power mode:
 *  @li @c 0x00 ( DAQ3_LOW_POWER_MODE )        - Low Power Mode,
 *  @li @c 0x01 ( DAQ3_FULL_PERFORMANCE_MODE ) - Full Performance Mode.
 * 
 * @note None.
 */
void daq3_set_pwr_mode ( daq3_t *ctx, uint8_t mode );

/**
 * @brief DAQ 3 set power reference buffer function.
 * @details This function set power reference buffer
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board.
 * @param[out] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] pd_ref   
 * Reference buffer:
 *  @li @c 0x00 ( DAQ3_PD_REF_POWER_DOWN ) - Power-Down,
 *  @li @c 0x01 ( DAQ3_PD_REF_POWER_UP )   - Power-Up.
 * 
 * @note None.
 */
void daq3_set_pwr_down_ref_buf ( daq3_t *ctx, uint8_t pd_ref );

/**
 * @brief DAQ 3 set power Amplifier function.
 * @details This function set power Amplifier
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board.
 * @param[out] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] pd_amp   
 * Amplifier:
 *  @li @c 0x00 ( DAQ3_PD_AMP_POWER_DOWN ) - Power-Down,
 *  @li @c 0x01 ( DAQ3_PD_AMP_POWER_UP )   - Power-Up.
 * 
 * @note None.
 */
void daq3_set_pwr_down_amp ( daq3_t *ctx, uint8_t pd_amp );


/**
 * @brief DAQ 3 get state of SDO function.
 * @details This function get State of SDO on Power-Up
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board.
 * @param[out] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @return 
 *  @li @c 0x00 - Low,
 *  @li @c 0x01 - High.
 * 
 * @note None.
 */
uint8_t daq3_get_sdo ( daq3_t *ctx );

/**
 * @brief DAQ 3 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t daq3_generic_write ( daq3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DAQ 3 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t daq3_generic_read ( daq3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DAQ 3 set command register function.
 * @details This function set command register status 
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board. 
 * @param[in] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] cfg_data : Structure where gesture data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t daq3_set_reg_cfg ( daq3_t *ctx, daq3_reg_cfg_t cfg_data );

/**
 * @brief DAQ 3 get command register function.
 * @details This function get command register status 
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board. 
 * @param[in] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] cfg_data : Pointer to the memory location where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t daq3_get_reg_cfg ( daq3_t *ctx, daq3_reg_cfg_t *cfg_data );

/**
 * @brief DAQ 3 get conversion result function.
 * @details This function reads a conversion result data
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board. 
 * @param[in] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @param[in] cfg_data : Structure where gesture data be stored.
 * @return 18-bit, two complement, ADC conversion data. 
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
int32_t daq3_get_conversion_result ( daq3_t *ctx, daq3_reg_cfg_t cfg_data );

/**
 * @brief DAQ 3 get voltage function.
 * @details This function reads a conversion result data and 
 * calculate voltage [ mV ]
 * of ADAQ4003 18-Bit, 2 MSPS, µModule Data Acquisition Solution 
 * on DAQ 3 click board. 
 * @param[in] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @return Volatge [ mV ]. 
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
float daq3_get_voltage ( daq3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DAQ3_H

/*! @} */ // daq3

// ------------------------------------------------------------------------ END

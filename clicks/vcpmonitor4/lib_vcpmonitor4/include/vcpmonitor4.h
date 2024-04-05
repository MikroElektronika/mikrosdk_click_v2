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
 * @file vcpmonitor4.h
 * @brief This file contains API for VCP Monitor 4 Click Driver.
 */

#ifndef vcpmonitor4_H
#define vcpmonitor4_H

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
 * @addtogroup vcpmonitor4 VCP Monitor 4 Click Driver
 * @brief API for configuring and manipulating VCP Monitor 4 Click driver.
 * @{
 */

/**
 * @defgroup vcpmonitor4_reg VCP Monitor 4 Registers List
 * @brief List of registers of VCP Monitor 4 Click driver.
 */

/**
 * @addtogroup vcpmonitor4_reg
 * @{
 */

/**
 * @brief VCP Monitor 4 description register.
 * @details Specified register for description of VCP Monitor 4 Click driver.
 */
#define VCPMONITOR4_REG_CONFIG          0x00
#define VCPMONITOR4_REG_ADC_CONFIG      0x01
#define VCPMONITOR4_REG_SHUNT_CAL       0x02
#define VCPMONITOR4_REG_VSHUNT          0x04
#define VCPMONITOR4_REG_VBUS            0x05
#define VCPMONITOR4_REG_DIETEMP         0x06
#define VCPMONITOR4_REG_CURRENT         0x07
#define VCPMONITOR4_REG_POWER           0x08
#define VCPMONITOR4_REG_DIAG_ALERT      0x0B
#define VCPMONITOR4_REG_SOVL            0x0C
#define VCPMONITOR4_REG_SUVL            0x0D
#define VCPMONITOR4_REG_BOVL            0x0E
#define VCPMONITOR4_REG_BUVL            0x0F
#define VCPMONITOR4_REG_TEMP_LIMIT      0x10
#define VCPMONITOR4_REG_PWR_LIMIT       0x11
#define VCPMONITOR4_REG_MANUFACTURER_ID 0x3E
#define VCPMONITOR4_REG_DEVICE_ID       0x3F

/*! @} */ // vcpmonitor4_reg

/**
 * @defgroup vcpmonitor4_set VCP Monitor 4 Registers Settings
 * @brief Settings for registers of VCP Monitor 4 Click driver.
 */

/**
 * @addtogroup vcpmonitor4_set
 * @{
 */

/**
 * @brief VCP Monitor 4 description setting.
 * @details Specified setting for description of VCP Monitor 4 Click driver.
 */
#define VCPMONITOR4_CURRENT_LSB         0.000305

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b vcpmonitor4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define VCPMONITOR4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define VCPMONITOR4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // vcpmonitor4_set

/**
 * @defgroup vcpmonitor4_map VCP Monitor 4 MikroBUS Map
 * @brief MikroBUS pin mapping of VCP Monitor 4 Click driver.
 */

/**
 * @addtogroup vcpmonitor4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VCP Monitor 4 Click to the selected MikroBUS.
 */
#define VCPMONITOR4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // vcpmonitor4_map
/*! @} */ // vcpmonitor4

/**
 * @brief VCP Monitor 4 Click context object.
 * @details Context object definition of VCP Monitor 4 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  alr;          /**< Description. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} vcpmonitor4_t;

/**
 * @brief VCP Monitor 4 Click configuration object.
 * @details Configuration object definition of VCP Monitor 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  alr;        /**< Description. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} vcpmonitor4_cfg_t;

/**
 * @brief VCP Monitor 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   vcpmonitor4_OK = 0,
   vcpmonitor4_ERROR = -1

} vcpmonitor4_return_value_t;

/*!
 * @addtogroup vcpmonitor4 VCP Monitor 4 Click Driver
 * @brief API for configuring and manipulating VCP Monitor 4 Click driver.
 * @{
 */

/**
 * @brief VCP Monitor 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vcpmonitor4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vcpmonitor4_cfg_setup ( vcpmonitor4_cfg_t *cfg );

/**
 * @brief VCP Monitor 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vcpmonitor4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor4_init ( vcpmonitor4_t *ctx, vcpmonitor4_cfg_t *cfg );

/**
 * @brief VCP Monitor 4 default configuration function.
 * @details This function executes a default configuration of VCP Monitor 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t vcpmonitor4_default_cfg ( vcpmonitor4_t *ctx );

/**
 * @brief VCP Monitor 4 data writing function.
 * @details This function writes a data to the selected register.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor4_generic_write ( vcpmonitor4_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief VCP Monitor 4 data reading function.
 * @details This function reads a data from the selected register.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Output data will be @b uint16_t data exept for the @b VCPMONITOR4_REG_POWER.
 */
err_t vcpmonitor4_generic_read ( vcpmonitor4_t *ctx, uint8_t reg, uint32_t *data_out ) ;

/**
 * @brief Get alert pin state.
 * @details 
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t vcpmonitor4_get_alert ( vcpmonitor4_t *ctx );

/**
 * @brief Get device temperature.
 * @details This function reads a ADC data for temperature and calculates 
 * real value in degrees C.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[out] temperature : Output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vcpmonitor4_get_temperature ( vcpmonitor4_t *ctx, float *temperature );

/**
 * @brief Get BUS voltage.
 * @details This function reads a ADC data for vbus voltage and calculates 
 * real value in V.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[out] vbus : Output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vcpmonitor4_get_vbus ( vcpmonitor4_t *ctx, float *vbus );

/**
 * @brief Get Shunt voltage.
 * @details This function reads a ADC data for shunt voltage and calculates 
 * real value in mV.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[out] vshunt : Output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vcpmonitor4_get_vshunt ( vcpmonitor4_t *ctx, float *vshunt );

/**
 * @brief Get Current.
 * @details This function reads a ADC data for device current and calculates 
 * real value in A.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[out] current : Output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vcpmonitor4_get_current ( vcpmonitor4_t *ctx, float *current );

/**
 * @brief Get Shunt voltage.
 * @details This function reads a ADC data for device power and calculates 
 * real value in W.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor4_t object definition for detailed explanation.
 * @param[out] power : Output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vcpmonitor4_get_power ( vcpmonitor4_t *ctx, float *power );

#ifdef __cplusplus
}
#endif
#endif // vcpmonitor4_H

/*! @} */ // vcpmonitor4

// ------------------------------------------------------------------------ END

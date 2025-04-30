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
 * @file irsense6.h
 * @brief This file contains API for IR Sense 6 Click Driver.
 */

#ifndef IRSENSE6_H
#define IRSENSE6_H

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

/*!
 * @addtogroup irsense6 IR Sense 6 Click Driver
 * @brief API for configuring and manipulating IR Sense 6 Click driver.
 * @{
 */

/**
 * @defgroup irsense6_cmd IR Sense 6 Commands List
 * @brief List of commands of IR Sense 6 Click driver.
 */

/**
 * @addtogroup irsense6_cmd
 * @{
 */

/**
 * @brief IR Sense 6 commands list.
 * @details Specified commands list of IR Sense 6 Click driver.
 */
#define IRSENSE6_CMD_FULL_MEASUREMENT       0xAA

/*! @} */ // irsense6_cmd

/**
 * @defgroup irsense6_set IR Sense 6 Settings
 * @brief Settings of IR Sense 6 Click driver.
 */

/**
 * @addtogroup irsense6_set
 * @{
 */

/**
 * @brief IR Sense 6 temperature calculation setting.
 * @details Specified setting for temperature calculation of IR Sense 6 Click driver.
 */
#define IRSENSE6_RAW_DATA_RESOLUTION        0xFFFFFFul
#define IRSENSE6_OBJ_TEMP_RES               130
#define IRSENSE6_OBJ_TEMP_OFFSET            20
#define IRSENSE6_AMB_TEMP_RES               105
#define IRSENSE6_AMB_TEMP_OFFSET            20

/**
 * @brief IR Sense 6 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Sense 6 Click driver.
 */
#define IRSENSE6_DEVICE_ADDRESS             0x38

/*! @} */ // irsense6_set

/**
 * @defgroup irsense6_map IR Sense 6 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Sense 6 Click driver.
 */

/**
 * @addtogroup irsense6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Sense 6 Click to the selected MikroBUS.
 */
#define IRSENSE6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // irsense6_map
/*! @} */ // irsense6

/**
 * @brief IR Sense 6 Click context object.
 * @details Context object definition of IR Sense 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t status;             /**< Device status byte. */

} irsense6_t;

/**
 * @brief IR Sense 6 Click configuration object.
 * @details Configuration object definition of IR Sense 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} irsense6_cfg_t;

/**
 * @brief IR Sense 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRSENSE6_OK = 0,
    IRSENSE6_ERROR = -1

} irsense6_return_value_t;

/*!
 * @addtogroup irsense6 IR Sense 6 Click Driver
 * @brief API for configuring and manipulating IR Sense 6 Click driver.
 * @{
 */

/**
 * @brief IR Sense 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irsense6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irsense6_cfg_setup ( irsense6_cfg_t *cfg );

/**
 * @brief IR Sense 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #irsense6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irsense6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense6_init ( irsense6_t *ctx, irsense6_cfg_t *cfg );

/**
 * @brief IR Sense 6 I2C write function.
 * @details This function writes data via I2C to the IR Sense 6 device.
 * @param[in] ctx : Click context object.
 * See #irsense6_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irsense6_i2c_write ( irsense6_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief IR Sense 6 I2C read function.
 * @details This function reads data via I2C from the IR Sense 6 device.
 * @param[in] ctx : Click context object.
 * See #irsense6_t object definition for detailed explanation.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irsense6_i2c_read ( irsense6_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief IR Sense 6 enable device function.
 * @details This function enables the IR Sense 6 device by setting the EN pin high.
 * @param[in] ctx : Click context object.
 * See #irsense6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irsense6_enable_device ( irsense6_t *ctx );

/**
 * @brief IR Sense 6 disable device function.
 * @details This function disables the IR Sense 6 device by setting the EN pin low.
 * @param[in] ctx : Click context object.
 * See #irsense6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irsense6_disable_device ( irsense6_t *ctx );

/**
 * @brief IR Sense 6 read temperature data function.
 * @details This function reads the object and ambient temperature data from the IR Sense 6 sensor.
 * @param[in] ctx : Click context object.
 * See #irsense6_t object definition for detailed explanation.
 * @param[out] obj_temp : Pointer to store the object temperature in degrees Celsius.
 * @param[out] amb_temp : Pointer to store the ambient temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irsense6_read_data ( irsense6_t *ctx, float *obj_temp, float *amb_temp );

#ifdef __cplusplus
}
#endif
#endif // IRSENSE6_H

/*! @} */ // irsense6

// ------------------------------------------------------------------------ END

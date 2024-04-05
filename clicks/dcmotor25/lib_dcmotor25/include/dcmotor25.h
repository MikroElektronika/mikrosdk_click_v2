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
 * @file dcmotor25.h
 * @brief This file contains API for DC Motor 25 Click Driver.
 */

#ifndef DCMOTOR25_H
#define DCMOTOR25_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup dcmotor25 DC Motor 25 Click Driver
 * @brief API for configuring and manipulating DC Motor 25 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor25_inst DC Motor 25 Registers List
 * @brief List of registers of DC Motor 25 Click driver.
 */

/**
 * @addtogroup dcmotor25_inst
 * @{
 */

/**
 * @brief DC Motor 25 description register.
 * @details Specified register for description of DC Motor 25 Click driver.
 */
#define DCMOTOR25_WRITE_TO_RDAC                 0x00
#define DCMOTOR25_ONE_TIME_PROG                 0x80

/*! @} */ // dcmotor25_inst

/**
 * @defgroup dcmotor25_set DC Motor 25 Registers Settings
 * @brief Settings for registers of DC Motor 25 Click driver.
 */

/**
 * @addtogroup dcmotor25_set
 * @{
 */

/**
 * @brief DC Motor 25 description setting.
 * @details Specified setting for description of DC Motor 25 Click driver.
 */
#define DCMOTOR25_OTP_V_READY                   0x00
#define DCMOTOR25_OTP_V_TEST_OK                 0x40
#define DCMOTOR25_OTP_V_ERROR                   0x80
#define DCMOTOR25_OTP_V_PROG_SUCCESS            0xC0

/**
 * @brief DC Motor 25 description digital potentiometer wiper data.
 * @details Specified digital potentiometer wiper data 
 * for description of DC Motor 25 Click driver.
 */
#define DCMOTOR25_RESISTANCE_MIN                17000
#define DCMOTOR25_RES_DEFAULT_20_kOhm           20000
#define DCMOTOR25_FULL_SCALE_RES_50_kOhm        50000
#define DCMOTOR25_WIPER_POS_MAX                 0x3F


/**
 * @brief DC Motor 25 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 25 Click driver.
 */
#define DCMOTOR25_DEVICE_ADDRESS                0x2C

/*! @} */ // dcmotor25_set

/**
 * @defgroup dcmotor25_map DC Motor 25 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 25 Click driver.
 */

/**
 * @addtogroup dcmotor25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 25 Click to the selected MikroBUS.
 */
#define DCMOTOR25_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // dcmotor25_map
/*! @} */ // dcmotor25

/**
 * @brief DC Motor 25 Click context object.
 * @details Context object definition of DC Motor 25 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t in1;        /**< Control logic input 1 pin. */
    digital_out_t in2;        /**< Control logic input 2 pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} dcmotor25_t;

/**
 * @brief DC Motor 25 Click configuration object.
 * @details Configuration object definition of DC Motor 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t in1;            /**< Control logic input 1 pin. */
    pin_name_t in2;            /**< Control logic input 2 pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} dcmotor25_cfg_t;

/**
 * @brief DC Motor 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR25_OK = 0,
    DCMOTOR25_ERROR = -1

} dcmotor25_return_value_t;

/*!
 * @addtogroup dcmotor25 DC Motor 25 Click Driver
 * @brief API for configuring and manipulating DC Motor 25 Click driver.
 * @{
 */

/**
 * @brief DC Motor 25 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor25_cfg_setup ( dcmotor25_cfg_t *cfg );

/**
 * @brief DC Motor 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor25_init ( dcmotor25_t *ctx, dcmotor25_cfg_t *cfg );

/**
 * @brief DC Motor 25 default configuration function.
 * @details This function executes a default configuration of DC Motor 25
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor25_default_cfg ( dcmotor25_t *ctx );

/**
 * @brief DC Motor 25 I2C writing function.
 * @details This function writes data bytes with desired instructions 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @param[in] inst : Instruction Byte.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor25_write_byte ( dcmotor25_t *ctx, uint8_t inst, uint8_t data_in );

/**
 * @brief DC Motor 25 I2C reading function.
 * @details This function reads data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor25_read_byte ( dcmotor25_t *ctx, uint8_t *data_out );

/**
 * @brief DC Motor 25 write RDAC function.
 * @details This function writes 6-bit RDAC values
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @param[in] rdac_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor25_write_rdac ( dcmotor25_t *ctx, uint8_t rdac_data );

/**
 * @brief DC Motor 25 read RDAC function.
 * @details This function function reads 6-bit RDAC values
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @param[out] rdac_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor25_read_rdac ( dcmotor25_t *ctx, uint8_t *rdac_data );

/**
 * @brief DC Motor 25 set the digital potentiometer function.
 * @details This function set the digital potentiometer wiper position 
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position (from 0 to 63).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor25_set_digi_pot ( dcmotor25_t *ctx, uint8_t wiper_pos );

/**
 * @brief DC Motor 25 set the resistance function.
 * @details This function set the resistance value 
 * of the digital potentiometer wiper position
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance (from 17000 to 50000 Ohm).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor25_set_resistance ( dcmotor25_t *ctx, uint16_t res_ohm );

/**
 * @brief DC Motor 25 set standby mode function.
 * @details This function set standby operating mode
 * of the A3908, Low Voltage DC Motor Driver
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dcmotor25_standby ( dcmotor25_t *ctx );

/**
 * @brief DC Motor 25 set reverse mode function.
 * @details This function set reverse operating mode
 * of the A3908, Low Voltage DC Motor Driver
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dcmotor25_reverse ( dcmotor25_t *ctx );

/**
 * @brief DC Motor 25 set forward mode function
 * @details This function set forward operating mode
 * of the A3908, Low Voltage DC Motor Driver
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dcmotor25_forward ( dcmotor25_t *ctx );

/**
 * @brief DC Motor 25 set brake mode function.
 * @details This function set brake operating mode
 * of the A3908, Low Voltage DC Motor Driver
 * on the DC Motor 25 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor25_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dcmotor25_brake ( dcmotor25_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR25_H

/*! @} */ // dcmotor25

// ------------------------------------------------------------------------ END

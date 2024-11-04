/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file i2cextend2.h
 * @brief This file contains API for I2C Extend 2 Click Driver.
 */

#ifndef I2CEXTEND2_H
#define I2CEXTEND2_H

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
 * @addtogroup i2cextend2 I2C Extend 2 Click Driver
 * @brief API for configuring and manipulating I2C Extend 2 Click driver.
 * @{
 */

/**
 * @defgroup i2cextend2_reg I2C Extend 2 Registers List
 * @brief List of registers of I2C Extend 2 Click driver.
 */

/**
 * @addtogroup i2cextend2_reg
 * @{
 */

/**
 * @brief I2C Extend 2 description register.
 * @details Specified register for description of I2C Extend 2 Click driver.
 */

/**
 * @brief 6DOF IMU 11 description register.
 * @details Specified register for description of I2C 6DOF IMU 11 Click.
 */
#define C6DOFIMU11_REG_WHO_AM_I                                     0x00
#define C6DOFIMU11_REG_CNTL2                                        0x3A
#define C6DOFIMU11_REG_INC3                                         0x2C
#define C6DOFIMU11_REG_ACCEL_XOUT_L                                 0x0A
#define C6DOFIMU11_REG_ACCEL_YOUT_L                                 0x0C
#define C6DOFIMU11_REG_ACCEL_ZOUT_L                                 0x0E
#define C6DOFIMU11_REG_MAG_XOUT_L                                   0x10
#define C6DOFIMU11_REG_MAG_YOUT_L                                   0x12
#define C6DOFIMU11_REG_MAG_ZOUT_L                                   0x14

/*! @} */ // i2cextend2_reg

/**
 * @defgroup i2cextend2_set I2C Extend 2 Registers Settings
 * @brief Settings for registers of I2C Extend 2 Click driver.
 */

/**
 * @addtogroup i2cextend2_set
 * @{
 */

/**
 * @brief I2C Extend 2 Disable/Enable.
 * @details Disable/Enable states of I2C Extend 2 Click driver.
 */
#define I2CEXTEND2_EXTEND_DISABLE                                   0x00
#define I2CEXTEND2_EXTEND_ENABLE                                    0x01

/**
 * @brief I2C Extend 2 pin state.
 * @details Pin state of I2C Extend 2 Click driver.
 */
#define I2CEXTEND_PIN_STATE_LOW                                    0x00
#define I2CEXTEND_PIN_STATE_HIGH                                   0x01

/**
 * @brief 6DOF IMU 11 bit mask.
 * @details Bit mask of 6DOF IMU 11 Click driver.
 */
#define C6DOFIMU11_CNTL2_TEMP_EN_STANDBY_MODE                       0x00
#define C6DOFIMU11_CNTL2_MAG_EN_STANDBY_MODE                        0x00
#define C6DOFIMU11_CNTL2_ACCEL_EN_STANDBY_MODE                      0x00
#define C6DOFIMU11_INC3_IEL2_FIFO_TRIG                              0x20
#define C6DOFIMU11_INC3_IEL1_FIFO_TRIG                              0x02
#define C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE                    0x01
#define C6DOFIMU11_CNTL2_GSEL_8G                                    0x00
#define C6DOFIMU11_CNTL2_RES_MAX2                                   0x0C
#define C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE                      0x02
#define C6DOFIMU11_WHO_AM_I_WIA_ID                                  0x2D

/**
 * @brief 6DOF IMU 11 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 11 Click driver.
 */
#define C6DOFIMU11_I2C_SLAVE_ADDRESS_GND                            0x0E
#define C6DOFIMU11_I2C_SLAVE_ADDRESS_VCC                            0x0F

/*! @} */ // i2cextend2_set

/**
 * @defgroup i2cextend2_map I2C Extend 2 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Extend 2 Click driver.
 */

/**
 * @addtogroup i2cextend2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Extend 2 Click to the selected MikroBUS.
 */
#define I2CEXTEND2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // i2cextend2_map
/*! @} */ // i2cextend2

/**
 * @brief I2C Extend 2 Click context object.
 * @details Context object definition of I2C Extend 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable. */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} i2cextend2_t;

/**
 * @brief I2C Extend 2 Click configuration object.
 * @details Configuration object definition of I2C Extend 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} i2cextend2_cfg_t;

/**
 * @brief I2C Extend 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   I2CEXTEND2_OK = 0,
   I2CEXTEND2_ERROR = -1

} i2cextend2_return_value_t;

/*!
 * @addtogroup i2cextend2 I2C Extend 2 Click Driver
 * @brief API for configuring and manipulating I2C Extend 2 Click driver.
 * @{
 */

/**
 * @brief I2C Extend 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cextend2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cextend2_cfg_setup ( i2cextend2_cfg_t *cfg );

/**
 * @brief I2C Extend 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2cextend2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cextend2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cextend2_init ( i2cextend2_t *ctx, i2cextend2_cfg_t *cfg );

/**
 * @brief Generic write data in Remote Mode function.
 * @details Function writes a the byte of data to the targeted 8-bit
 * register address of the Click board connected 
 * to the I2c Extend 2 Click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : Data to be written.
 * @return Nothing.
 */
void i2cextend2_rmt_write ( i2cextend2_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Generic read data in Remote Mode function.
 * @details Function read a the byte of data from the targeted 8-bit
 * register address of the Click board connected
 * to the I2c Extend 2 Click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit read data.
 */
uint8_t i2cextend2_rmt_read ( i2cextend2_t *ctx, uint8_t reg );

/**
 * @brief Generic multi write data in Remote Mode function.
 * @details Function writes a sequential data starting 
 * to the targeted register address of the Click board connected
 * to the I2c Extend 2 Click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] p_tx_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return Nothing.
 */
void i2cextend2_rmt_multi_write ( i2cextend2_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Generic multi read data in Remote Mode function.
 * @details Function read a sequential data starting
 * from the targeted register address of the Click board connected
 * to the I2c Extend 2 Click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : Number of bytes to be read.
 * @return Nothing.
 */
void i2cextend2_rmt_multi_read ( i2cextend2_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Enable extend function.
 * @details The function enables extend 
 * by the set state of the CS ( logic '1' ) 
 * and disable by the clear state of the CS ( logic '0' ) 
 * of PCA9615 2-channel multipoint Fast-mode Plus differential I2C-bus
 * buffer with hot-swap logic on the I2C Extend 2 Click.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] en_extend : CS pin state.
 * @return Nothing.
 */
void i2cextend2_enable ( i2cextend2_t *ctx, uint8_t en_extend );

#ifdef __cplusplus
}
#endif
#endif // I2CEXTEND2_H

/*! @} */ // i2cextend2

// ------------------------------------------------------------------------ END

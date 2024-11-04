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
 * @file i2cisolator3.h
 * @brief This file contains API for I2C Isolator 3 Click Driver.
 */

#ifndef I2CISOLATOR3_H
#define I2CISOLATOR3_H

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
 * @addtogroup i2cisolator3 I2C Isolator 3 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 3 Click driver.
 * @{
 */

/**
 * @defgroup i2cisolator3_set I2C Isolator 3 Registers Settings
 * @brief Settings for registers of I2C Isolator 3 Click driver.
 */

/**
 * @addtogroup i2cisolator3_set
 * @{
 */

/**
 * @brief I2C Isolator 3 description setting.
 * @details Specified setting for description of I2C Isolator 3 Click driver.
 */
#define I2CISOLATOR3_THERMO20_CMD_RESET                            0x1E
#define I2CISOLATOR3_THERMO20_CMD_CONVERSION                       0x46
#define I2CISOLATOR3_THERMO20_CMD_READ_ADC                         0x00

#define I2CISOLATOR3_READ_WRITE_LEN_ERROR                          0x00
#define I2CISOLATOR3_READ_WRITE_LEN_MIN                            0x01
/**
 * @brief I2C Isolator 3 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C Isolator 3 Click driver.
 */
#define I2CISOLATOR3_SET_DEV_ADDR                                  0x40

/*! @} */ // i2cisolator3_set

/**
 * @defgroup i2cisolator3_map I2C Isolator 3 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Isolator 3 Click driver.
 */

/**
 * @addtogroup i2cisolator3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Isolator 3 Click to the selected MikroBUS.
 */
#define I2CISOLATOR3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    
/*! @} */ // i2cisolator3_map
/*! @} */ // i2cisolator3

/**
 * @brief I2C Isolator 3 Click context object.
 * @details Context object definition of I2C Isolator 3 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                 /**< I2C driver object. */
                                                     
    // I2C slave address                             
    uint8_t slave_address;                            /**< Device slave address (used for I2C driver). */

} i2cisolator3_t;

/**
 * @brief I2C Isolator 3 Click configuration object.
 * @details Configuration object definition of I2C Isolator 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                  /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                  /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                              /**< I2C serial speed. */
    uint8_t   i2c_address;                            /**< I2C slave address. */

} i2cisolator3_cfg_t;

/**
 * @brief I2C Isolator 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   I2CISOLATOR3_OK = 0,
   I2CISOLATOR3_ERROR = -1

} i2cisolator3_return_value_t;

/*!
 * @addtogroup i2cisolator3 I2C Isolator 3 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 3 Click driver.
 * @{
 */

/**
 * @brief I2C Isolator 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cisolator3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cisolator3_cfg_setup ( i2cisolator3_cfg_t *cfg );

/**
 * @brief I2C Isolator 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cisolator3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator3_init ( i2cisolator3_t *ctx, i2cisolator3_cfg_t *cfg );

/**
 * @brief I2C Isolator 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator3_generic_write ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief I2C Isolator 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator3_generic_read ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief I2C Isolator 3 send command function.
 * @details The function sends the desired command to a remote device wired with CPC5902, 
 * Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] command : 8-bit commands instruction.
 * @return Nothing.
 * @note None.
 */
void i2cisolator3_send_cmd ( i2cisolator3_t *ctx, uint8_t command );

/**
 * @brief I2C Isolator 3 write the byte of data function.
 * @details The function writes the byte of data to the targeted 8-bit register address of the remote device
 * wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : 8-bit data to be written.
 * @return Nothing.
 * @note None.
 */
void i2cisolator3_write_byte ( i2cisolator3_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief I2C Isolator 3 read the byte of data function.
 * @details The function read a the byte of data from the targeted 8-bit register address of the remote device
 * wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit read data..
 * @note None.
 */
uint8_t i2cisolator3_read_byte ( i2cisolator3_t *ctx, uint8_t reg );

/**
 * @brief I2C Isolator 3 burst write function.
 * @details The function writes sequential data starting to the targeted 8-bit register address
 * of the remote device wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] p_tx_data : pointer to the data to be written.
 * @param[in] n_bytes : number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cisolator3_burst_write ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief I2C Isolator 3 burst read function.
 * @details The function read sequential data starting from the targeted 8-bit register address
 * of the remote device wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] reg : 8-bit memory address.
 * @param[in] p_rx_data : pointer to the memory location where data be stored.
 * @param[in] n_bytes : number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cisolator3_burst_read ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief I2C Isolator 3 advanced write function.
 * @details The function advanced write, writes sequential data starting of the targeted ( selectable ) register address
 * of the remote device wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] p_reg : pointer to the memory address.
 * @param[in] n_reg_bytes : the number of bytes of the registry address.
 * @param[in] p_tx_data : pointer to the data to be written.
 * @param[in] n_tx_data_bytes : number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cisolator3_adv_write ( i2cisolator3_t *ctx, uint8_t *p_reg, uint8_t n_reg_bytes, uint8_t *p_tx_data, uint8_t n_tx_data_bytes );

/**
 * @brief I2C Isolator 3 advanced read function.
 * @details The function advanced read, read sequential data starting from the targeted ( selectable ) register address
 * of the remote device wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator3_t object definition for detailed explanation.
 * @param[in] p_reg : pointer to the memory address.
 * @param[in] n_reg_bytes : the number of bytes of the registry address.
 * @param[in] p_rx_data : pointer to the memory location where data be stored.
 * @param[in] n_rx_data_bytes : number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cisolator3_adv_read ( i2cisolator3_t *ctx, uint8_t *p_reg, uint8_t n_reg_bytes, uint8_t *p_rx_data, uint8_t n_rx_data_bytes );

#ifdef __cplusplus
}
#endif
#endif // I2CISOLATOR3_H

/*! @} */ // i2cisolator3

// ------------------------------------------------------------------------ END

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
 * @file i2cextend.h
 * @brief This file contains API for I2C Extend Click Driver.
 */

#ifndef I2CEXTEND_H
#define I2CEXTEND_H

#ifdef __cplusplus
extern "C"{
#endif
    
#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup i2cextend I2C Extend Click Driver
 * @brief API for configuring and manipulating I2C Extend Click driver.
 * @{
 */

/**
 * @defgroup i2cextend_reg I2C Extend Registers List
 * @brief List of registers of I2C Extend Click driver.
 */

/**
 * @addtogroup i2cextend_reg
 * @{
 */

/**
 * @brief I2C Extend description register.
 * @details Specified register for description of I2C Extend Click driver.
 */
#define I2CEXTEND_REG_CONFIG                                       0x00
#define I2CEXTEND_REG_STATUS                                       0x01
#define I2CEXTEND_REG_EVENT                                        0x02
#define I2CEXTEND_REG_ALERT_EN                                     0x03
#define I2CEXTEND_REG_FAULT                                        0x04
#define I2CEXTEND_REG_SCRATCH                                      0x05
#define I2CEXTEND_REG_ADDR_TRANS                                   0x06
#define I2CEXTEND_REG_CTRL                                         0x07

/**
 * @brief 6DOF IMU 11 description register.
 * @details Specified register for description of I2C 6DOF IMU 11 click.
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

/*! @} */ // i2cextend_reg

/**
 * @defgroup i2cextend_set I2C Extend Registers Settings
 * @brief Settings for registers of I2C Extend Click driver.
 */

/**
 * @addtogroup i2cextend_set
 * @{
 */

/**
 * @brief I2C Extend description setting.
 * @details Specified setting for description of I2C Extend Click driver.
 */
#define I2CEXTEND_CONFIG_INTR_MODE_BIT_MASK                        0x01
#define I2CEXTEND_CONFIG_INTR_MODE_SET_ALERT_PIN                   0x00
#define I2CEXTEND_CONFIG_INTR_MODE_IGNORE_ARA                      0x01
#define I2CEXTEND_CONFIG_CTRL_SEL_BIT_MASK                         0x02
#define I2CEXTEND_CONFIG_CTRL_SEL_MIRRORED_RMT_OUT                 0x00
#define I2CEXTEND_CONFIG_CTRL_SEL_USE_REG_CTRL_VAL                 0x02

/**
 * @brief I2C Extend alert enable.
 * @details Alert enable settings of I2C Extend Click driver.
 */
#define I2CEXTEND_ALERT_EN_LINK_GOOD_DISABLE                       0x00
#define I2CEXTEND_ALERT_EN_LINK_GOOD                               0x01
#define I2CEXTEND_ALERT_EN_LINK_LOST_DISABLE                       0x00
#define I2CEXTEND_ALERT_EN_LINK_LOST                               0x02
#define I2CEXTEND_ALERT_EN_FAULT_DISABLE                           0x00
#define I2CEXTEND_ALERT_EN_FAULT                                   0x04

/**
 * @brief I2C Extend control.
 * @details Control settings of I2C Extend Click driver.
 */
#define I2CEXTEND_CTRL_SEL_L                                       0x00
#define I2CEXTEND_CTRL_SEL_H                                       0x01

/**
 * @brief I2C Extend pin state.
 * @details Pin state of I2C Extend Click driver.
 */
#define I2CEXTEND_PIN_STATE_LOW                                    0x00
#define I2CEXTEND_PIN_STATE_HIGH                                   0x01

/**
 * @brief 6DOF IMU 11 bit mask.
 * @details Bit mask of 6DOF IMU 11 click driver.
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
 * @brief I2C Extend device address setting.
 * @details Specified setting for device slave address selection of
 * I2C Extend Click driver.
 */
#define I2CEXTEND_I2C_SLAVE_ADDR_0                                 0x3E
#define I2CEXTEND_I2C_SLAVE_ADDR_1                                 0x3F
#define I2CEXTEND_I2C_SLAVE_ADDR_2                                 0x76
#define I2CEXTEND_I2C_SLAVE_ADDR_3                                 0x77

/**
 * @brief 6DOF IMU 11 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 11 click driver.
 */
#define C6DOFIMU11_I2C_SLAVE_ADDRESS_GND                            0x0E
#define C6DOFIMU11_I2C_SLAVE_ADDRESS_VCC                            0x0F

/*! @} */ // i2cextend_set

/**
 * @defgroup i2cextend_map I2C Extend MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Extend Click driver.
 */

/**
 * @addtogroup i2cextend_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Extend Click to the selected MikroBUS.
 */
#define I2CEXTEND_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // i2cextend_map
/*! @} */ // i2cextend

/**
 * @brief I2C Extend Click context object.
 * @details Context object definition of I2C Extend Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  cs;                                  /**< Reset pin. */
    digital_out_t  rst;                                 /**< Chip Select. */
    
    // Input pins
    digital_in_t  int_pin;                              /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;                                   /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                              /**< Device slave address (used for I2C driver). */

} i2cextend_t;

/**
 * @brief I2C Extend Click configuration object.
 * @details Configuration object definition of I2C Extend Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  cs;                                     /**< Reset pin. */
    pin_name_t  rst;                                    /**< Chip Select. */
    pin_name_t  int_pin;                                /**< Interrupt pin. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} i2cextend_cfg_t;

/**
 * @brief I2C Extend Click status data.
 * @details Status data definition of I2C Extend Click driver.
 */
typedef struct
{
    uint8_t nlink;
    uint8_t nalert;
    uint8_t ext_nalert;
    uint8_t speed_idx;
} i2cextend_status_data_t;

/**
 * @brief I2C Extend Click fault data.
 * @details Fault data definition of I2C Extend Click driver.
 */
typedef struct
{
    uint8_t i2c_write_fault;
    uint8_t link_fault;
    uint8_t ext_i2c_fault;
    uint8_t tx_buf_overflow;
} i2cextend_fault_data_t;

/**
 * @brief I2C Extend Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   I2CEXTEND_OK = 0,
   I2CEXTEND_ERROR = -1

} i2cextend_return_value_t;

/*!
 * @addtogroup i2cextend I2C Extend Click Driver
 * @brief API for configuring and manipulating I2C Extend Click driver.
 * @{
 */

/**
 * @brief I2C Extend configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cextend_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cextend_cfg_setup ( i2cextend_cfg_t *cfg );

/**
 * @brief I2C Extend initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cextend_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cextend_init ( i2cextend_t *ctx, i2cextend_cfg_t *cfg );

/**
 * @brief Generic write data function.
 * @details Function writes a byte of data to the targeted 8-bit
 * register address of the LTC4331 I2C Slave Device Extender
 * Over Rugged Differential Link on the I2c Extend click board.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : Data to be written.
 * @return Nothing.
 */
void i2cextend_generic_write ( i2cextend_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Generic read data function.
 * @details Function read a byte of data from the targeted 8-bit
 * register address of the LTC4331 I2C Slave Device Extender
 * Over Rugged Differential Link on the I2c Extend click board.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit read data.
 */
uint8_t i2cextend_generic_read ( i2cextend_t *ctx, uint8_t reg );

/**
 * @brief Generic write data in Remote Mode function.
 * @details Function writes a byte of data to the targeted 8-bit
 * register address of the click board connected 
 * to the I2c Extend click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] rmt_slave_addr : 7-bit slave address.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : Data to be written.
 * @return Nothing.
 */
void i2cextend_rmt_write ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg, uint8_t tx_data );

/**
 * @brief Generic read data in Remote Mode function.
 * @details Function read a byte of data from the targeted 8-bit
 * register address of the click board connected
 * to the I2c Extend click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] rmt_slave_addr : 7-bit slave address.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit read data.
 */
uint8_t i2cextend_rmt_read ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg );

/**
 * @brief Generic multi write data in Remote Mode function.
 * @details Function writes a sequential data starting 
 * to the targeted register address of the click board connected
 * to the I2c Extend click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] rmt_slave_addr : 7-bit slave address.
 * @param[in] reg : 8-bit register address.
 * @param[in] p_tx_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return Nothing.
 */
void i2cextend_rmt_multi_write ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Generic multi read data in Remote Mode function.
 * @details Function read a sequential data starting
 * from the targeted register address of the click board connected
 * to the I2c Extend click in Remote Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] rmt_slave_addr : 7-bit slave address.
 * @param[in] reg : 8-bit register address.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : Number of bytes to be read.
 * @return Nothing.
 */
void i2cextend_rmt_multi_read ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Set the configuration function.
 * @details Function set configuration
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] intr_mode : Internal slave interrupt behavior.
 * @param[in] ctrl_sel : CTRL settings:
 * @return Nothing.
 */
void i2cextend_set_config ( i2cextend_t *ctx, uint8_t intr_mode, uint8_t ctrl_sel );

/**
 * @brief Check the status function.
 * @details Function read status register and update status data structe
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] status_data : Pointer to the memory location where data be stored.
 * @return Nothing.
 */
void i2cextend_status ( i2cextend_t *ctx, i2cextend_status_data_t *status_data );

/**
 * @brief Set enable alerts function.
 * @details Function enable alerts
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] link_good : The local and remote I2C networks alert.
 * @param[in] link_lost : The local and remote I2C networks have lost link communication:
 * @param[in] fault : Check fault state:
 * @return Nothing.
 */
void i2cextend_enable_alerts ( i2cextend_t *ctx, uint8_t link_good, uint8_t link_lost, uint8_t fault );

/**
 * @brief Check the fault state function.
 * @details Function read fault register and update fault state data structe
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[out] fault_data : Pointer to the memory location where data be stored.
 * @return Nothing.
 */
void i2cextend_fault ( i2cextend_t *ctx, i2cextend_fault_data_t *fault_data );

/**
 * @brief Get scratch function.
 * @details Function read scratch register and return scratch data
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @return 8-bit scratch data ( default 0x08 );
 */
uint8_t i2cextend_get_scratch ( i2cextend_t *ctx );

/**
 * @brief Set out slave address function.
 * @details Function output slave address,
 * incoming 7-bit I2C addresses are translated to the remote network by: 
 * out_slave_address = i2c_trans XOR in_slave_address
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] out_slave_address : 7-bit out slave address.
 * @return Nothing.
 */
void i2cextend_set_out_slave_address ( i2cextend_t *ctx, uint8_t out_slave_address );

/**
 * @brief Set out CTRL function.
 * @details Function set output value of the remote CTRL pin
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] out_ctrl : Output value of the remote CTRL.
 * @return Nothing.
 */
void i2cextend_set_out_ctrl ( i2cextend_t *ctx, uint8_t out_ctrl );

/**
 * @brief Set RTS pin state function.
 * @details Function set RTS pin state
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] en_rst : RST pin state.
 * @return Nothing.
 */
void i2cextend_set_rst ( i2cextend_t *ctx, uint8_t en_rst );

/**
 * @brief Set CS pin state function.
 * @details Function set CS pin state
 * of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @param[in] en_cs : CS pin state.
 * @return Nothing.
 */
void i2cextend_set_cs ( i2cextend_t *ctx, uint8_t en_cs );

/**
 * @brief Check interrupt ststus function.
 * @details Function check interrupt state by return state
 * of the INT pin of I2c Extend click in Local Mode.
 * @param[in] ctx : Click context object.
 * See #i2cextend_t object definition for detailed explanation.
 * @return Interrupt state.
 */
uint8_t i2cextend_check_int ( i2cextend_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // I2CEXTEND_H

/*! @} */ // i2cextend

// ------------------------------------------------------------------------ END

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
 * @file usbcsink.h
 * @brief This file contains API for USB-C Sink Click Driver.
 */

#ifndef USBCSINK_H
#define USBCSINK_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
    
/*!
 * @addtogroup usbcsink USB-C Sink Click Driver
 * @brief API for configuring and manipulating USB-C Sink Click driver.
 * @{
 */

/**
 * @defgroup usbcsink_reg USB-C Sink Registers List
 * @brief List of registers of USB-C Sink Click driver.
 */

/**
 * @addtogroup usbcsink_reg
 * @{
 */

/**
 * @brief USB-C Sink description register.
 * @details Specified register for description of USB-C Sink Click driver.
 */
#define USBCSINK_REG_BCD_TYPEC_REV_LOW                              0x06
#define USBCSINK_REG_BCD_TYPEC_REV_HIGH                             0x07
#define USBCSINK_REG_BCD_USBPD_REV_LOW                              0x08
#define USBCSINK_REG_BCD_USBPD_REV_HIGH                             0x09
#define USBCSINK_REG_DEVICE_CAPAB_HIGH                              0x0A
#define USBCSINK_REG_ALERT_STAT_1                                   0x0B
#define USBCSINK_REG_ALERT_STAT_1_MASK                              0x0C
#define USBCSINK_REG_PORT_STAT_0                                    0x0D
#define USBCSINK_REG_PORT_STAT_1                                    0x0E
#define USBCSINK_REG_TYPEC_MON_STAT_0                               0x0F
#define USBCSINK_REG_TYPEC_MON_STAT_1                               0x10
#define USBCSINK_REG_CC_STAT                                        0x11
#define USBCSINK_REG_CC_HW_FAULT_STAT_0                             0x12
#define USBCSINK_REG_CC_HW_FAULT_STAT_1                             0x13
#define USBCSINK_REG_PD_TYPEC_STAT                                  0x14
#define USBCSINK_REG_TYPEC_STAT                                     0x15
#define USBCSINK_REG_PRT_STAT                                       0x16
#define USBCSINK_REG_PD_CMD_CTL                                     0x1A
#define USBCSINK_REG_MON_CTL_0                                      0x20
#define USBCSINK_REG_MON_CTL_2                                      0x22
#define USBCSINK_REG_RESET_CTL                                      0x23
#define USBCSINK_REG_VBUS_DISCH_TIME_CTL                            0x25
#define USBCSINK_REG_VBUS_DISCH_CTL                                 0x26
#define USBCSINK_REG_VBUS_CTL                                       0x27
#define USBCSINK_REG_GPIO3_SW_GPIO                                  0x2D
#define USBCSINK_REG_DEV_ID                                         0x2F
#define USBCSINK_REG_RX_HEADER_LOW                                  0x31
#define USBCSINK_REG_RX_HEADER_HIGH                                 0x32
#define USBCSINK_REG_RX_DATA_OBJ1_0                                 0x33
#define USBCSINK_REG_RX_DATA_OBJ1_1                                 0x34
#define USBCSINK_REG_RX_DATA_OBJ1_2                                 0x35
#define USBCSINK_REG_RX_DATA_OBJ1_3                                 0x36
#define USBCSINK_REG_RX_DATA_OBJ2_0                                 0x37
#define USBCSINK_REG_RX_DATA_OBJ2_1                                 0x38
#define USBCSINK_REG_RX_DATA_OBJ2_2                                 0x39
#define USBCSINK_REG_RX_DATA_OBJ2_3                                 0x3A
#define USBCSINK_REG_RX_DATA_OBJ3_0                                 0x3B
#define USBCSINK_REG_RX_DATA_OBJ3_1                                 0x3C
#define USBCSINK_REG_RX_DATA_OBJ3_2                                 0x3D
#define USBCSINK_REG_RX_DATA_OBJ3_3                                 0x3E
#define USBCSINK_REG_RX_DATA_OBJ4_0                                 0x3F
#define USBCSINK_REG_RX_DATA_OBJ4_1                                 0x40
#define USBCSINK_REG_RX_DATA_OBJ4_2                                 0x41
#define USBCSINK_REG_RX_DATA_OBJ4_3                                 0x42
#define USBCSINK_REG_RX_DATA_OBJ5_0                                 0x43
#define USBCSINK_REG_RX_DATA_OBJ5_1                                 0x44
#define USBCSINK_REG_RX_DATA_OBJ5_2                                 0x45
#define USBCSINK_REG_RX_DATA_OBJ5_3                                 0x46
#define USBCSINK_REG_RX_DATA_OBJ6_0                                 0x47
#define USBCSINK_REG_RX_DATA_OBJ6_1                                 0x48
#define USBCSINK_REG_RX_DATA_OBJ6_2                                 0x49
#define USBCSINK_REG_RX_DATA_OBJ6_3                                 0x4A
#define USBCSINK_REG_RX_DATA_OBJ7_0                                 0x4B
#define USBCSINK_REG_RX_DATA_OBJ7_1                                 0x4C
#define USBCSINK_REG_RX_DATA_OBJ7_2                                 0x4D
#define USBCSINK_REG_RX_DATA_OBJ7_3                                 0x4E
#define USBCSINK_REG_TX_HEADER_LOW                                  0x51
#define USBCSINK_REG_TX_HEADER_HIGH                                 0x52
#define USBCSINK_REG_DPM_PDO_NUMB                                   0x70
#define USBCSINK_REG_DPM_SNK_PDO1_0                                 0x85
#define USBCSINK_REG_DPM_SNK_PDO1_1                                 0x86
#define USBCSINK_REG_DPM_SNK_PDO1_2                                 0x87
#define USBCSINK_REG_DPM_SNK_PDO1_3                                 0x88
#define USBCSINK_REG_DPM_SNK_PDO2_0                                 0x89
#define USBCSINK_REG_DPM_SNK_PDO2_1                                 0x8A
#define USBCSINK_REG_DPM_SNK_PDO2_2                                 0x8B
#define USBCSINK_REG_DPM_SNK_PDO2_3                                 0x8C
#define USBCSINK_REG_DPM_SNK_PDO3_0                                 0x8D
#define USBCSINK_REG_DPM_SNK_PDO3_1                                 0x8E
#define USBCSINK_REG_DPM_SNK_PDO3_2                                 0x8F
#define USBCSINK_REG_DPM_SNK_PDO3_3                                 0x90
#define USBCSINK_REG_DPM_REQ_RDO3_0                                 0x91
#define USBCSINK_REG_DPM_REQ_RDO3_1                                 0x92
#define USBCSINK_REG_DPM_REQ_RDO3_2                                 0x93
#define USBCSINK_REG_DPM_REQ_RDO3_3                                 0x94
#define USBCSINK_REG_DEF                                            0xFF
#define USBCSINK_REG_FTP_CUST_PWD_REG                               0x95
#define USBCSINK_REG_FTP_CTL_0                                      0x96
#define USBCSINK_REG_FTP_CTL_1                                      0x97
#define USBCSINK_REG_RW_BUF                                         0x53

#define USBCSINK_FTP_CUST_PWR                                       0x80
#define USBCSINK_FTP_CUST_RST_N                                     0x40
#define USBCSINK_FTP_CUST_REQ                                       0x10
#define USBCSINK_FTP_CUST_SECT                                      0x07

#define USBCSINK_FTP_CUST_SER                                       0xF8
#define USBCSINK_FTP_CUST_OPCODE                                    0x07

#define USBCSINK_SEC_0                                              0x01
#define USBCSINK_SEC_1                                              0x02
#define USBCSINK_SEC_2                                              0x04
#define USBCSINK_SEC_3                                              0x08
#define USBCSINK_SEC_4                                              0x10

/*! @} */ // usbcsink_reg

/**
 * @defgroup usbcsink_set USB-C Sink Registers Settings
 * @brief Settings for registers of USB-C Sink Click driver.
 */

/**
 * @addtogroup usbcsink_set
 * @{
 */

/**
 * @brief USB-C Sink description setting.
 * @details Specified setting for description of USB-C Sink Click driver.
 */

/**
 * @brief USB-C Sink customer password.
 * @details Specified customer password of USB-C Sink Click driver.
 */
#define USBCSINK_FTP_CUST_PWD                                       0x47

/**
 * @brief USB-C Sink software reset.
 * @details Specified software reset setting of USB-C Sink Click driver.
 */
#define USBCSINK_SW_RESET_ON                                        0x01
#define USBCSINK_SW_RESET_OFF                                       0x00

/**
 * @brief USB-C Sink sector commands.
 * @details Specified sector commands of USB-C Sink Click driver.
 */
#define USBCSINK_READ                                               0x00
#define USBCSINK_WRITE_PL                                           0x01
#define USBCSINK_WRITE_SER                                          0x02
#define USBCSINK_ERASE_SEC                                          0x05
#define USBCSINK_PROG_SEC                                           0x06
#define USBCSINK_SOFT_PROG_SEC                                      0x07

/**
 * @brief USB-C Sink PDO select.
 * @details Specified PDO select settings of USB-C Sink Click driver.
 */
#define USBCSINK_SET_PDO_1                                          0x01
#define USBCSINK_SET_PDO_2                                          0x02
#define USBCSINK_SET_PDO_3                                          0x03

#define USBCSINK_UPLOAD_NEW_DATA_VAL                                0x00
#define USBCSINK_UPLOAD_DEFAULT                                     0x01

/**
 * @brief USB-C Sink device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Sink Click driver.
 */
#define USBCSINK_SLAVE_ADR_0                                         0x28
#define USBCSINK_SLAVE_ADR_1                                         0x29
#define USBCSINK_SLAVE_ADR_2                                         0x2A
#define USBCSINK_SLAVE_ADR_3                                         0x2B

/*! @} */ // usbcsink_set

/**
 * @defgroup usbcsink_map USB-C Sink MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Sink Click driver.
 */

/**
 * @addtogroup usbcsink_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Sink Click to the selected MikroBUS.
 */
#define USBCSINK_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.po3 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.po2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcsink_map
/*! @} */ // usbcsink

/**
 * @brief USB-C Sink Click context object.
 * @details Context object definition of USB-C Sink Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset. */

    // Input pins
    digital_in_t  po3;         /**< Power Contract Flag. */
    digital_in_t  po2;         /**< Power Contract Flag. */
    digital_in_t  int_pin;     /**< Interrupt. */

    // Modules
    i2c_master_t i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;     /**< Device slave address (used for I2C driver). */

} usbcsink_t;

/**
 * @brief USB-C Sink Click configuration object.
 * @details Configuration object definition of USB-C Sink Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  po3;            /**< Power Contract Flag. */
    pin_name_t  po2;            /**< Power Contract Flag. */
    pin_name_t  rst;            /**< Reset. */
    pin_name_t  int_pin;        /**< Interrupt. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} usbcsink_cfg_t;

/**
 * @brief USB-C Sink Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   USBCSINK_OK = 0,
   USBCSINK_ERROR = -1

} usbcsink_return_value_t;

/*!
 * @addtogroup usbcsink USB-C Sink Click Driver
 * @brief API for configuring and manipulating USB-C Sink Click driver.
 * @{
 */

/**
 * @brief USB-C Sink configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcsink_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcsink_cfg_setup ( usbcsink_cfg_t *cfg );

/**
 * @brief USB-C Sink initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcsink_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink_init ( usbcsink_t *ctx, usbcsink_cfg_t *cfg );

/**
 * @brief USB-C Sink I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink_generic_write ( usbcsink_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief USB-C Sink I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink_generic_read ( usbcsink_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief HW reset function.
 * @details The function hw reset, 
 * reset the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[out] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @return Nothing.
**/
void usbcsink_hw_reset ( usbcsink_t *ctx );

/**
 * @brief Get PO2 pin state function.
 * @details The function get PO2 ( AN ) pin state
 * reset the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @return State of the PO2 ( AN ) pin.
**/
uint8_t usbcsink_get_pdo2 ( usbcsink_t *ctx );

/**
 * @brief Get PO3 pin state function.
 * @details The function get PO3 ( CS ) pin state
 * reset the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @return State of the PO3 ( CS ) pin.
**/
uint8_t usbcsink_get_pdo3 ( usbcsink_t *ctx );

/**
 * @brief Get INT pin state function.
 * @details The function get INT pin state
 * reset the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @return State of the INT pin.
**/
uint8_t usbcsink_get_interrupt ( usbcsink_t *ctx );


/**
 * @brief Write byte function.
 * @details The function write byte the byte of data 
 * to the targeted 8-bit register address
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : Data to be written.
 * @return Nothing.
**/
void usbcsink_write_byte ( usbcsink_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Read byte function.
 * @details The function read a the byte of data from the targeted 8-bit
 * register address of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit read data.
**/
uint8_t usbcsink_read_byte ( usbcsink_t *ctx, uint8_t reg );

/**
 * @brief Check device communication function.
 * @details The function check device communication
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @return It will return 0x01 on success or 0x00 on failure.
**/
uint8_t usbcsink_dev_chk ( usbcsink_t *ctx );

/**
 * @brief Write sector function.
 * @details The function write sector is used to write multiple data bytes
 * to a group of sector registers
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * @param[in] sec_num : Sector number.
 * @param[in] sec_data : Sector data to be written.
 * See #usbcsink_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
**/
err_t usbcsink_cust_wr_sec ( usbcsink_t *ctx, uint8_t sec_num,  uint8_t *sec_data );

/**
 * @brief Enter the write mode function.
 * @details The function enter the write mode
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @param[in] er_sec : Sector number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
**/
err_t usbcsink_cust_ent_wr_mode ( usbcsink_t *ctx, uint8_t er_sec );

/**
 * @brief Exit write mode function.
 * @details The function the exit of writing mode
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
**/
err_t usbcsink_cust_ext_test_mode ( usbcsink_t *ctx );

/**
 * @brief Load data function.
 * @details The function load data is used to read the non-volatile memory
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink_t object definition for detailed explanation.
 * @return Nothing.
**/
void usbcsink_load_data ( usbcsink_t *ctx );

/**
 * @brief Upload data function.
 * @details The function upload data is used to write new data
 * to the non-volatile memory
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] ctx : Click context object.
 * @param[in] def_vals : Default values.
 * See #usbcsink_t object definition for detailed explanation.
 * @return Nothing.
**/
void usbcsink_upload_new_data ( usbcsink_t *ctx, uint8_t def_vals );

/**
 * @brief Set the voltage function.
 * @details The function sets the voltage to be requested for each 
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @param[in] volt : Float voltage value.
 * @return Nothing.
**/
void usbcsink_set_voltage ( uint8_t pdo_numb, float volt );

/**
 * @brief Get the voltage function.
 * @details The function get the voltage to be requested for each
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @return Float voltage value.
**/
float usbcsink_get_voltage ( uint8_t pdo_numb );

/**
 * @brief Set the current function.
 * @details The function set the current to be requested for each
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @param[in] curr : Float current value.
 * @return Nothing.
**/
void usbcsink_set_current ( uint8_t pdo_numb,  float curr );

/**
 * @brief Get the current function.
 * @details The function get the current to be requested for each
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @return Float voltage value.
 *
 * @note Valid current values are:
 * 0.00, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00,
 * 2.25, 2.50, 2.75, 3.00, 3.50, 4.00, 4.50, 5.00.
**/
float usbcsink_get_current ( uint8_t pdo_numb );

/**
 * @brief Set the lower voltage limit function.
 * @details The function set the under votlage lock out parameter for each
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @param[in] value : 8-bit under votlage lock out parameter.
 * @return Nothing.
 *
 * @note Valid high voltage limits are 5-20% in 1% increments.
 * PDO1 has a fixed lower limit to 3.3V.
**/
void usbcsink_set_lo_volt_limit ( uint8_t pdo_numb, uint8_t value );

/**
 * @brief Get the lower voltage limit function.
 * @details The function get the under votlage lock out parameter for each
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @return 8-bit voltage value.
**/
uint8_t usbcsink_get_lo_volt_limit ( uint8_t pdo_numb );

/**
 * @brief Set the upper voltage limit function.
 * @details The function set the over votlage lock out parameter for each
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @param[in] value : 8-bit over votlage lock out parameter.
 * @return Nothing.
 * 
 * @note Valid high voltage limits are 5-20% in 1% increments.
**/
void usbcsink_set_up_volt_limit ( uint8_t pdo_numb,  uint8_t value );

/**
 * @brief Get the over voltage limit function.
 * @details The function get the over votlage lock out parameter for each
 * of the three power data objects ( PDO )
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @return 8-bit over votlage lock out parameter.
**/
uint8_t usbcsink_get_up_volt_limit ( uint8_t pdo_numb );

/**
 * @brief Set the flexible current function.
 * @details The function set the flexible current value common to all PDOs
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : Float flexible current data.
 * @return Nothing.
**/
void usbcsink_set_flx_curr ( float value );

/**
 * @brief Get the flexible current function.
 * @details The function set the flexible current value common to all PDOs
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @return Float flexible current value.
**/
float usbcsink_get_flx_curr ( void );

/**
 * @brief Set the number of sink function.
 * @details The function set the the number of sink PDOs
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] pdo_numb : Number of the sink PDOs[ 1 - 3 ] ( profile ).
 * @return Nothing.
**/
void usbcsink_set_pdo_num ( uint8_t pdo_numb );

/**
 * @brief Get the number of sink function.
 * @details The function set the number of sink PDOs
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @return Number of the sink PDOs[ 1 - 3 ] ( profile ).
**/
uint8_t usbcsink_get_pdo_num ( void );

/**
 * @brief Set the external source of power function.
 * @details The function set the external source of power
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : @li @c 0 - No external source of power.
 *                    @li @c 1 - An external power source is available and is sufficient to
 *                               adequately power the system while charging external devices.
 * @return Nothing.
**/
void usbcsink_set_ext_pow ( uint8_t value );

/**
 * @brief Get the external source of power function.
 * @details The function get the external source of power
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @return @li @c 0 - No external source of power.
 *         @li @c 1 - An external power source is available and is sufficient to
 *                    adequately power the system while charging external devices.
**/
uint8_t usbcsink_get_ext_pow ( void );

/**
 * @brief Set the USB capable function.
 * @details The function set the USB capable parameter value
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : @li @c 0 - Sink does not support data communication.
 *                    @li @c 1 - Sink does support data communication.
 * @return Nothing.
**/
void usbcsink_set_usb_com_capa ( uint8_t value );

/**
 * @brief Get the USB capable function.
 * @details The function get the USB capable parameter value
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @return @li @c 0 - Sink does not support data communication.
 *         @li @c 1 - Sink does support data communication.
**/
uint8_t usbcsink_get_usb_com_cap ( void );

/**
 * @brief Set the config OK GPIO function.
 * @details The function set the config OK GPIO
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : @li @c 0 - Source attached.
 *                    @li @c 1 - No source attached
 * @return Nothing.
**/
void usbcsink_set_cfg_ok_gpio ( uint8_t value );

/**
 * @brief Get the config OK GPIO function.
 * @details The function get the config OK GPIO
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @return @li @c 0 - Source attached.
 *         @li @c 1 - No source attached.
**/
uint8_t usbcsink_get_cfg_ok_gpio ( void );

/**
 * @brief Set the config CTRL GPIO function.
 * @details The function set the config CTRL GPIO
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : @li @c 0 - Source attached.
 *                    @li @c 1 - No source attached
 * @return Nothing.
**/
void usbcsink_set_gpio_ctl ( uint8_t value );

/**
 * @brief Get the config CTRL GPIO function.
 * @details The function get the config CTRL GPIO
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @return @li @c 0 - Source attached.
 *         @li @c 1 - No source attached.
**/
uint8_t usbcsink_get_gpio_ctl ( void );

/**
 * @brief Set the power only above 5V function.
 * @details The function set the power only above 5V parameter configuration
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : @li @c 0 - Source attached.
 *                    @li @c 1 - No source attached
 * @return Nothing.
**/
void usbcsink_set_pow_above_5v_only ( uint8_t value );

/**
 * @brief Get the power only above 5V function.
 * @details The function get the power only above 5V parameter configuration
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : @li @c 0 - Enabled when source is attached.
 *                    @li @c 1 - Enabled only when source attached.
**/
uint8_t usbcsink_get_pow_above_5v_only ( void );

/**
 * @brief Set the request operating current function.
 * @details The function set the request operating current
 * selects which operation current from the sink or the source 
 * is to be requested in the RDO message
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @param[in] value : @li @c 0 - Request I SNK sink as operating current in RDO message.
 *                    @li @c 1 - Request I SRC sink as operating current in RDO message.
 * @return Nothing.
**/
void usbcsink_set_req_src_current ( uint8_t value );

/**
 * @brief Get the request operating current function.
 * @details The function get the request operating current
 * selects which operation current from the sink or the source
 * is to be requested in the RDO message
 * of the STUSB4500 Standalone USB PD sink controller
 * on USB-C Sink Click board.
 * @return @li @c 0 - Request I SNK sink as operating current in RDO message.
 *         @li @c 1 - Request I SRC sink as operating current in RDO message.
**/
uint8_t usbcsink_get_req_src_curr ( void );

#ifdef __cplusplus
}
#endif
#endif // USBCSINK_H

/*! @} */ // usbcsink

// ------------------------------------------------------------------------ END

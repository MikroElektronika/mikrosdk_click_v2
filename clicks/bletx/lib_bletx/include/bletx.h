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
 * @file bletx.h
 * @brief This file contains API for BLE TX Click Driver.
 */

#ifndef BLETX_H
#define BLETX_H

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
 * @addtogroup bletx BLE TX Click Driver
 * @brief API for configuring and manipulating BLE TX Click driver.
 * @{
 */

/**
 * @defgroup bletx_sel BLE TX selection.
 * @brief Selection of BLE TX Click driver.
 */

/**
 * @addtogroup bletx_sel
 * @{
 */

/**
 * @brief BLE TX interface selection description register.
 * @details Specified interface selection for description of BLE TX Click driver.
 */
#define BLETX_SEL_INTERFACE_I2C                                 0
#define BLETX_SEL_INTERFACE_UART                                1

/**
 * @brief BLE TX UART baud rate description register.
 * @details Specified UART baud rate for description of BLE TX Click driver.
 */
#define BLETX_SEL_BAUD_RATE_9600                             9600
#define BLETX_SEL_BAUD_RATE_115200                         115200 

/*! @} */ // bletx_sel

/**
 * @defgroup bletx_reg BLE TX Registers List
 * @brief List of registers of BLE TX Click driver.
 */

/**
 * @addtogroup bletx_reg
 * @{
 */

/**
 * @brief BLE TX description register.
 * @details Specified register for description of BLE TX Click driver.
 */
#define BLETX_REG_SETTING_1                                0x01
#define BLETX_REG_SETTING_2                                0x02
#define BLETX_REG_SETTING_3                                0x03
#define BLETX_REG_SETTING_4                                0x04
#define BLETX_REG_SETTING_5                                0x05
#define BLETX_REG_SETTING_6                                0x06
#define BLETX_REG_PREAMBLE                                 0x07
#define BLETX_REG_ACCESS_ADDRESS_0                         0x08
#define BLETX_REG_ACCESS_ADDRESS_1                         0x09
#define BLETX_REG_ACCESS_ADDRESS_2                         0x0A
#define BLETX_REG_ACCESS_ADDRESS_3                         0x0B
#define BLETX_REG_PDU_HEADER_0                             0x0C
#define BLETX_REG_PDU_HEADER_1                             0x0D
#define BLETX_REG_PDU_ADV_ADDR_0                           0x0E
#define BLETX_REG_PDU_ADV_ADDR_1                           0x0F
#define BLETX_REG_PDU_ADV_ADDR_2                           0x10
#define BLETX_REG_PDU_ADV_ADDR_3                           0x11
#define BLETX_REG_PDU_ADV_ADDR_4                           0x12
#define BLETX_REG_PDU_ADV_ADDR_5                           0x13
#define BLETX_REG_PDU_ADV_DATA_START                       0x14
#define BLETX_REG_PDU_ADV_EDDYSTONE_DATA                   0x17
#define BLETX_REG_PDU_ADV_EDDYSTONE_UID                    0x2F
#define BLETX_REG_CRC_0                                    0x33
#define BLETX_REG_CRC_1                                    0x34
#define BLETX_REG_CRC_2                                    0x35
#define BLETX_REG_MODE                                     0x36
#define BLETX_REG_SOFT_RESET                               0x3F

/*! @} */ // bletx_reg

/**
 * @defgroup bletx_set BLE TX Registers Settings
 * @brief Settings for registers of BLE TX Click driver.
 */

/**
 * @addtogroup bletx_set
 * @{
 */

/**
 * @brief BLE TX AD type name description setting.
 * @details Specified AD type name setting for description of BLE TX Click driver.
 */
#define BLETX_AD_TYPE_FLAGS                                0x01
#define BLETX_AD_TYPE_FLAGS_CLASS_UUID_16                  0x02
#define BLETX_AD_TYPE_FLAGS_COMPLETE_UUID_16               0x03
#define BLETX_AD_TYPE_FLAGS_SHORT_LOCAL_NAME               0x08
#define BLETX_AD_TYPE_FLAGS_COMPLETE_LOCAL_NAME            0x09
#define BLETX_AD_TYPE_FLAGS_TX_POWER_LEVEL                 0x0A
#define BLETX_AD_TYPE_FLAGS_CLASS_OF_DEVICE                0x0D
#define BLETX_AD_TYPE_FLAGS_SIMPLE_PAIR_HASH_C             0x0E
#define BLETX_AD_TYPE_FLAGS_DEVICE_ID                      0x10
#define BLETX_AD_TYPE_FLAGS_SERVICE_DATA_UUID_16           0x16
#define BLETX_AD_TYPE_FLAGS_PUBLIC_TARGET_ADDR             0x17
#define BLETX_AD_TYPE_FLAGS_RANDOM_TARGET_ADDR             0x18 
#define BLETX_AD_TYPE_FLAGS_APPEARANCE                     0x19
#define BLETX_AD_TYPE_FLAGS_ADVERTISING_INTERVAL           0x1A
#define BLETX_AD_TYPE_FLAGS_BLE_DEVICE_ADDR                0x1B
#define BLETX_AD_TYPE_FLAGS_RANDOM_LE_ROLE                 0x1C
#define BLETX_AD_TYPE_FLAGS_URI                            0x24
#define BLETX_AD_TYPE_FLAGS_INDOOR_POSITIONING             0x25
#define BLETX_AD_TYPE_FLAGS_TRANSPORT_DISCOVERY            0x26
#define BLETX_AD_TYPE_FLAGS_BROADCAST_CODE                 0x2D
#define BLETX_AD_TYPE_FLAGS_MANUFACTURER_SPEC_DATA         0xFF

/**
 * @brief BLE TX software reset description setting.
 * @details Specified software reset setting for description of BLE TX Click driver.
 */
#define BLETX_SOFT_RESET_CMD                               0xAA

/**
 * @brief BLE TX preamble description setting.
 * @details Specified preamble setting for description of BLE TX Click driver.
 */
#define BLETX_PREAMBLE                                     0xAA
   
/**
 * @brief BLE TX PDU type name description setting.
 * @details Specified PDU type name setting for description of BLE TX Click driver.
 */
#define BLETX_HEADER_PDU_TYPE_ADV_IND                      0x00
#define BLETX_HEADER_PDU_TYPE_ADV_NONCONN_IND              0x02
#define BLETX_HEADER_PDU_TYPE_ADV_SCAN_IND                 0x06
    
/**
 * @brief BLE TX TX power level description setting.
 * @details Specified setting for TX power level description of BLE TX Click driver.
 */
#define BLETX_TX_POWER_LVL_MODE_LOWEST                     0x00
#define BLETX_TX_POWER_LVL_MODE_LOW                        0x01
#define BLETX_TX_POWER_LVL_MODE_MEDIUM                     0x02
#define BLETX_TX_POWER_LVL_MODE_HIGH                       0x03

/**
 * @brief BLE TX advertising delay description setting.
 * @details Specified setting for advertising delay description of BLE TX Click driver.
 */
#define BLETX_ADV_DELAY_ENABLE                             0x80
#define BLETX_ADV_DELAY_DISABLE                            0x00

/**
 * @brief BLE TX CRC description setting.
 * @details Specified setting for CRC description of BLE TX Click driver.
 */
#define BLETX_CRC_ENABLE                                   0x80
#define BLETX_CRC_DISABLE                                  0x00

/**
 * @brief BLE TX white description setting.
 * @details Specified setting for white description of BLE TX Click driver.
 */
#define BLETX_WHITE_ENABLE                                 0x40
#define BLETX_WHITE_DISABLE                                0x00
    
/**
 * @brief BLE TX character codes description setting.
 * @details Specified setting for character codes description of BLE TX Click driver.
 */
#define BLETX_CHARACTER_CODES_DOT_COM                      0x07
#define BLETX_CHARACTER_CODES_DOT_ORG                      0x08
#define BLETX_CHARACTER_CODES_DOT_EDU                      0x09
#define BLETX_CHARACTER_CODES_DOT_NET                      0x0A
#define BLETX_CHARACTER_CODES_DOT_INFO                     0x0B
#define BLETX_CHARACTER_CODES_DOT_BIZ                      0x0C
#define BLETX_CHARACTER_CODES_DOT_GOV                      0x0D
    
/**
 * @brief BLE TX Eddystone spec data description setting.
 * @details Specified setting for Eddystone spec data description of BLE TX Click driver.
 */
#define BLETX_EDDYSTONE_SPEC_DATA_HTTP_WWW                 0x00
#define BLETX_EDDYSTONE_SPEC_DATA_HTTPS_WWW                0x01
#define BLETX_EDDYSTONE_SPEC_DATA_HTTP                     0x02
#define BLETX_EDDYSTONE_SPEC_DATA_HTTPS                    0x03
#define BLETX_EDDYSTONE_SPEC_DATA_UDI                      0x63
#define BLETX_EDDYSTONE_SPEC_DATA_TLM                      0x63
    
/**
 * @brief BLE TX Eddystone service UUID description setting.
 * @details Specified setting for Eddystone service UUID description of BLE TX Click driver.
 */
#define BLETX_EDDYSTONE_SERVICE_UUID                       0xAAFE
#define BLETX_EDDYSTONE_SERVICE_DATA_TYPE_VALUE            0x16
  
/**
 * @brief BLE TX Eddystone frame type description setting.
 * @details Specified setting for Eddystone frame type description of BLE TX Click driver.
 */
#define BLETX_EDDYSTONE_FRAME_TYPE_UID                     0x00
#define BLETX_EDDYSTONE_FRAME_TYPE_URL                     0x10
#define BLETX_EDDYSTONE_FRAME_TYPE_TLM                     0x20
#define BLETX_EDDYSTONE_FRAME_TYPE_EID                     0x30

/**
 * @brief BLE TX device address setting.
 * @details Specified setting for device slave address selection of
 * BLE TX Click driver.
 */
#define BLETX_SET_DEV_ADDR                                 0x28

/**
 * @brief BLE TX access address setting.
 * @details Specified setting for device access address selection of
 * BLE TX Click driver.
 */
#define BLETX_ACCESS_ADDRESS                               0xD6BE898Eul

/*! @} */ // bletx_set

/**
 * @defgroup bletx_map BLE TX MikroBUS Map
 * @brief MikroBUS pin mapping of BLE TX Click driver.
 */

/**
 * @addtogroup bletx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE TX Click to the selected MikroBUS.
 */
#define BLETX_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ui = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.s0 = MIKROBUS( mikrobus, MIKROBUS_PWM ) 

/*! @} */ // bletx_map
/*! @} */ // bletx

/**
 * @brief BLE TX Click context object.
 * @details Context object definition of BLE TX Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  ui;     /**< Interface selection pin. */
    digital_out_t  s0;     /**< Interface setting pin. */
    digital_out_t  s1;     /**< Interface setting pin. */
    digital_out_t  rst;    /**< Reset pin. */

    // Modules
    i2c_master_t i2c;      /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address; /**< Device slave address (used for I2C driver). */

} bletx_t;

/**
 * @brief BLE TX Click configuration object.
 * @details Configuration object definition of BLE TX Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  ui;         /**< Interface selection pin. */
    pin_name_t  s0;         /**< Interface setting pin. */
    pin_name_t  s1;         /**< Interface setting pin. */
    pin_name_t  rst;        /**< Reset pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} bletx_cfg_t;

/**
 * @brief BLE TX Click advertising settings object. 
 * @details Settings object definition of BLE TX Click driver. 
 */
typedef struct
{                              
    uint8_t   adv_ch_1_frequency;
    uint8_t   adv_ch_2_frequency; 
    uint8_t   adv_ch_3_frequency; 
    uint8_t   tx_output_power; 
    uint8_t   txdata_loop;
    uint8_t   txdata_cw;
    uint8_t   eventnum;
    uint8_t   advdelay_enb;
    uint16_t  avdintvl_interval_ms;
    uint8_t   crc_enb;
    uint8_t   white_enb;
    uint8_t   pdu_len;
    uint8_t   uuid[ 6 ];

} bletx_adv_cfg_t;

/**
 * @brief BLE TX Click advertising data packet.
 * @details Configuration the advertising packet data of Bluetooth® Low Energy Advertising channel. 
 */
typedef struct
{                              
    uint8_t   preamble;
    uint32_t  access_address; 
    uint16_t  pdu_header; 
    uint8_t   adv_addr[ 6 ]; 
    uint8_t   adv_data[ 32 ]; 
    uint32_t  crc; 

} bletx_create_adv_data_packet_t;

/**
 * @brief BLE TX Click Eddystone™ data packet.
 * @details Configuration the Eddystone™ packet data of Bluetooth® Low Energy Advertising channel. 
 */
typedef struct
{                              
    uint8_t   length_of_service_list;
    uint8_t   param_service_list; 
    uint16_t  eddystone_id; 
    uint8_t   length_of_service_data; 
    uint8_t   service_data; 
    uint8_t   frame_type_url; 
    uint8_t   power; 
    uint8_t   spec_data;
    uint8_t   advdata_url[ 32 ];
    uint8_t   domain;
    uint8_t   name_space_id[ 10 ];
    uint8_t   instance_id[ 6 ];
    uint8_t   tlm_version;
    uint16_t  battery_voltage;
    float     beacon_temperature;
    uint32_t  pdu_count;
    uint32_t  time_since_reboot;

} bletx_eddystone_data_t;

/**
 * @brief BLE TX Click Advertising channel setting.
 * @details Predefined enum values for advertising 1st, 2nd and 3rd channel setting.
 */
typedef enum
{
    ADVCH1_37_Ch_2402_MHz = 0x00,
    ADVCH1_37_Ch_2480_MHz = 0x30,
    ADVCH1_38_Ch_2426_MHz = 0x10,
    ADVCH1_39_Ch_2480_MHz = 0x20,
    ADVCH2_37_Ch_2402_MHz = 0x00,
    ADVCH2_38_Ch_2426_MHz = 0x04,
    ADVCH2_39_Ch_2480_MHz = 0x08,
    ADVCH2_NO_TX_OUTPUT   = 0x0C,
    ADVCH3_37_Ch_2402_MHz = 0x00,
    ADVCH3_38_Ch_2426_MHz = 0x01,
    ADVCH3_39_Ch_2480_MHz = 0x02,
    ADVCH3_NO_TX_OUTPUT   = 0x03

} bletx_advch_value_t;

/**
 * @brief BLE TX Click TX output power setting.
 * @details Predefined enum values for TX output power [ dBm ] setting.
 */
typedef enum
{
    TX_POWER_0_dBm = 0x00,
    TX_POWER_MINUS_3_dBm,
    TX_POWER_MINUS_6_dBm,
    TX_POWER_MINUS_9_dBm,
    TX_POWER_MINUS_12_dBm,
    TX_POWER_MINUS_15_dBm,
    TX_POWER_MINUS_20_dBm,
    TX_POWER_MINUS_32_dBm

} bletx_tx_output_power_value_t;

/**
 * @brief BLE TX Click TX data loop.
 * @details Predefined enum values for TX data loop, burst transmission or continuous transmission setting.
 */
typedef enum
{
    BURST_TRANSMISSION = 0x00,
    CONTINUOUS_TRANSMISSION = 0x10,
    GFSK = 0x00,
    CONTINUOUS_WAVE = 0x08

} bletx_txdata_value_t;

/**
 * @brief BLE TX Click advertising event setting.
 * @details Predefined enum values for the number of advertising event setting.
 */
typedef enum
{
    ADVERTISING_EVENT_REPEAT = 0x00,
    ADVERTISING_EVENT_1_TIME,
    ADVERTISING_EVENT_2_TIME,
    ADVERTISING_EVENT_3_TIME,
    ADVERTISING_EVENT_4_TIME,
    ADVERTISING_EVENT_5_TIME,
    ADVERTISING_EVENT_6_TIME,
    ADVERTISING_EVENT_7_TIME

} bletx_eventnum_value_t;

/**
 * @brief BLE TX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLETX_OK = 0,
    BLETX_ERROR = -1

} bletx_return_value_t;

/*!
 * @addtogroup bletx BLE TX Click Driver
 * @brief API for configuring and manipulating BLE TX Click driver.
 * @{
 */

/**
 * @brief BLE TX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bletx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bletx_cfg_setup ( bletx_cfg_t *cfg );

/**
 * @brief BLE TX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board™.
 * @param[out] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bletx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_init ( bletx_t *ctx, bletx_cfg_t *cfg );

/**
 * @brief BLE TX default configuration function.
 * @details This function executes a default configuration of BLE TX
 * click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t bletx_default_cfg ( bletx_t *ctx );

/**
 * @brief BLE TX full power down function.
 * @details This function full power-down blocks communication of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_power_down ( bletx_t *ctx );

/**
 * @brief BLE TX full power up function.
 * @details This function full power-up initialization of all registers of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_power_up ( bletx_t *ctx );

/**
 * @brief BLE TX hardware reset function.
 * @details This function executes a hardware reset reconfigures all registers of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_hw_reset ( bletx_t *ctx );

/**
 * @brief BLE TX software reset function.
 * @details This function executes a software reset reconfigures all registers of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_soft_reset ( bletx_t *ctx );

/**
 * @brief BLE TX interface selection function.
 * @details This function select interface of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] sel_interface : 
 *         @li @c  0 ( BLETX_SEL_INTERFACE_I2C ) - I2C serial interface,
 *         @li @c  1 ( BLETX_SEL_INTERFACE_UART )- UART serial interface.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_interface_selection ( bletx_t *ctx, uint8_t sel_interface );

/**
 * @brief BLE TX slave address selection function.
 * @details This function select slave address of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] sel_slave_address : Slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_slave_address_selection ( bletx_t *ctx, uint8_t sel_slave_address ) ;

/**
 * @brief BLE TX baud rate selection function.
 * @details This function select baud rate of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] sel_baud_rate :
 *         @li @c    9600 ( BLETX_SEL_BAUD_RATE_9600 )  -   9600 bps,
 *         @li @c  115200 ( BLETX_SEL_BAUD_RATE_115200 )- 115200 bps. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_baud_rate_selection ( bletx_t *ctx, uint32_t sel_baud_rate );

/**
 * @brief BLE TX I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_generic_write ( bletx_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief BLE TX I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_generic_read ( bletx_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief BLE TX start advertising function.
 * @details This function start advertising of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_start_advertising ( bletx_t *ctx );

/**
 * @brief BLE TX stop advertising function.
 * @details This function stop advertising of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_stop_advertising ( bletx_t *ctx );

/**
 * @brief BLE TX advertising channel setting function.
 * @details This function advertising channel setting of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] advch_data : Enum values for advertising channel setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_set_cfg_adv_channel ( bletx_t *ctx, bletx_advch_value_t advch_data );

/**
 * @brief BLE TX output power setting function.
 * @details This function output power setting of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] power_data : Enum values for TX output power [ dBm ] setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_set_output_power ( bletx_t *ctx, bletx_tx_output_power_value_t power_data );

/**
 * @brief BLE TX TX data setting function.
 * @details This function TX data setting of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] txdata_data : Enum values for TX data loop, burst transmission or continuous transmission setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_set_tx_data ( bletx_t *ctx, bletx_txdata_value_t txdata_data );

/**
 * @brief BLE TX eventnum setting function.
 * @details This function eventnum setting of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] eventnum_data : Enum values for the number of advertising event setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_set_eventnum ( bletx_t *ctx, bletx_eventnum_value_t eventnum_data );

/**
 * @brief BLE TX advertising delay setting function.
 * @details This function advertising delay setting of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] adv_delay_ms : Advertising delay in milliseconds from 20 ms to 10240 ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_set_adv_delay ( bletx_t *ctx, float adv_delay_ms );

/**
 * @brief BLE TX configuration setting function.
 * @details This function configuration setting of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] adv_cfg : Advertising settings structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_set_configuration ( bletx_t *ctx, bletx_adv_cfg_t adv_cfg );

/**
 * @brief BLE TX create advertising data packet function.
 * @details This function create advertising data packet of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] adv_data_packet : Advertising data packet structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_create_adv_data_packet ( bletx_t *ctx, bletx_create_adv_data_packet_t adv_data_packet );

/**
 * @brief BLE TX create Eddystone™ URI data packet function.
 * @details This function create advertising Eddystone™ URI data packet of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] adv_data : Advertising data packet structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_create_eddystone_uri ( bletx_t *ctx, bletx_eddystone_data_t adv_data );

/**
 * @brief BLE TX create Eddystone™ UID data packet function.
 * @details This function create advertising Eddystone™ UID data packet of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] adv_data : Advertising data packet structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_create_eddystone_uid ( bletx_t *ctx, bletx_eddystone_data_t adv_data );

/**
 * @brief BLE TX create Eddystone™ TLM data packet function.
 * @details This function create advertising Eddystone™ TLM data packet of the 
 * AK1595 Bluetooth® Low Energy transmitter on the BLE TX click board™. 
 * @param[in] ctx : Click context object.
 * See #bletx_t object definition for detailed explanation.
 * @param[in] adv_data : Advertising data packet structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletx_create_eddystone_tlm ( bletx_t *ctx, bletx_eddystone_data_t adv_data );

#ifdef __cplusplus
}
#endif
#endif // BLETX_H

/*! @} */ // bletx

// ------------------------------------------------------------------------ END

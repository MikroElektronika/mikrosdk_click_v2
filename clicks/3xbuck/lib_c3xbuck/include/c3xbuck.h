/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for 3xBuck  Click driver.
 *
 * \addtogroup c3xbuck 3xBuck  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C3XBUCK_H
#define C3XBUCK_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define C3XBUCK_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en1  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en2  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.en3  = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C3XBUCK_RETVAL  uint8_t

#define C3XBUCK_OK           0x00
#define C3XBUCK_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup enable_buck_registers Enable Buck registers
 * \{
 */
#define C3XBUCK_SELECT_BUCK_1   0x00 
#define C3XBUCK_SELECT_BUCK_2   0x01 
#define C3XBUCK_SELECT_BUCK_3   0x02 
/** \} */

/**
 * \defgroup voltage_reg Voltage registers
 * \{
 */
#define C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE  0x80
#define C3XBUCK_REG_VOUT1_SEL                0x00 
#define C3XBUCK_REG_VOUT2_SEL                0x01 
#define C3XBUCK_REG_VOUT3_SEL                0x02 
#define C3XBUCK_REG_VOUT1_COM                0x03 
#define C3XBUCK_REG_VOUT2_COM                0x04 
#define C3XBUCK_REG_VOUT3_COM                0x05 
#define C3XBUCK_REG_SYS_STATUS               0x06 
/** \} */

/**
 * \defgroup configure_buck Buck configuration
 * \{
 */
#define C3XBUCK_CFG_RATE_10mV_0cycles     0x00 
#define C3XBUCK_CFG_RATE_10mV_2cycles     0x10 
#define C3XBUCK_CFG_RATE_10mV_4cycles     0x20 
#define C3XBUCK_CFG_RATE_10mV_8cycles     0x30 
#define C3XBUCK_CFG_RATE_10mV_16cycles    0x40 
#define C3XBUCK_CFG_RATE_10mV_32cycles    0x50 
#define C3XBUCK_CFG_RATE_10mV_64cycles    0x60 
#define C3XBUCK_CFG_RATE_10mV_128cycles   0x70 
#define C3XBUCK_CFG_MODE_PSM_OPERATION    0x00 
#define C3XBUCK_CFG_MODE_PWM_OPERATION    0x02 
#define C3XBUCK_CFG_SW_ENABLE_BUCK        0x00 
#define C3XBUCK_CFG_SW_DISABLE_BUCK       0x01 
/** \} */


/**
 * \defgroup variable_voltage Variable voltage output
 * \{
 */
#define C3XBUCK_OUTPUT_VOLTAGE_680mV    0x00 
#define C3XBUCK_OUTPUT_VOLTAGE_690mV    0x01 
#define C3XBUCK_OUTPUT_VOLTAGE_700mV    0x02 
#define C3XBUCK_OUTPUT_VOLTAGE_710mV    0x03 
#define C3XBUCK_OUTPUT_VOLTAGE_720mV    0x04 
#define C3XBUCK_OUTPUT_VOLTAGE_730mV    0x05 
#define C3XBUCK_OUTPUT_VOLTAGE_740mV    0x06 
#define C3XBUCK_OUTPUT_VOLTAGE_750mV    0x07 
#define C3XBUCK_OUTPUT_VOLTAGE_760mV    0x08 
#define C3XBUCK_OUTPUT_VOLTAGE_770mV    0x09 
#define C3XBUCK_OUTPUT_VOLTAGE_780mV    0x0A 
#define C3XBUCK_OUTPUT_VOLTAGE_790mV    0x0B 
#define C3XBUCK_OUTPUT_VOLTAGE_800mV    0x0C 
#define C3XBUCK_OUTPUT_VOLTAGE_810mV    0x0D 
#define C3XBUCK_OUTPUT_VOLTAGE_820mV    0x0E 
#define C3XBUCK_OUTPUT_VOLTAGE_830mV    0x0F 
#define C3XBUCK_OUTPUT_VOLTAGE_840mV    0x10 
#define C3XBUCK_OUTPUT_VOLTAGE_850mV    0x11 
#define C3XBUCK_OUTPUT_VOLTAGE_860mV    0x12 
#define C3XBUCK_OUTPUT_VOLTAGE_870mV    0x13 
#define C3XBUCK_OUTPUT_VOLTAGE_880mV    0x14 
#define C3XBUCK_OUTPUT_VOLTAGE_890mV    0x15 
#define C3XBUCK_OUTPUT_VOLTAGE_900mV    0x16 
#define C3XBUCK_OUTPUT_VOLTAGE_910mV    0x17 
#define C3XBUCK_OUTPUT_VOLTAGE_920mV    0x18 
#define C3XBUCK_OUTPUT_VOLTAGE_930mV    0x19 
#define C3XBUCK_OUTPUT_VOLTAGE_940mV    0x1A 
#define C3XBUCK_OUTPUT_VOLTAGE_950mV    0x1B 
#define C3XBUCK_OUTPUT_VOLTAGE_960mV    0x1C 
#define C3XBUCK_OUTPUT_VOLTAGE_970mV    0x1D 
#define C3XBUCK_OUTPUT_VOLTAGE_980mV    0x1E 
#define C3XBUCK_OUTPUT_VOLTAGE_990mV    0x1F 
#define C3XBUCK_OUTPUT_VOLTAGE_1000mV   0x20 
#define C3XBUCK_OUTPUT_VOLTAGE_1010mV   0x21 
#define C3XBUCK_OUTPUT_VOLTAGE_1020mV   0x22 
#define C3XBUCK_OUTPUT_VOLTAGE_1030mV   0x23 
#define C3XBUCK_OUTPUT_VOLTAGE_1040mV   0x24 
#define C3XBUCK_OUTPUT_VOLTAGE_1050mV   0x25 
#define C3XBUCK_OUTPUT_VOLTAGE_1060mV   0x26 
#define C3XBUCK_OUTPUT_VOLTAGE_1070mV   0x27 
#define C3XBUCK_OUTPUT_VOLTAGE_1080mV   0x28 
#define C3XBUCK_OUTPUT_VOLTAGE_1090mV   0x29 
#define C3XBUCK_OUTPUT_VOLTAGE_1100mV   0x2A 
#define C3XBUCK_OUTPUT_VOLTAGE_1110mV   0x2B 
#define C3XBUCK_OUTPUT_VOLTAGE_1120mV   0x2C 
#define C3XBUCK_OUTPUT_VOLTAGE_1130mV   0x2D 
#define C3XBUCK_OUTPUT_VOLTAGE_1140mV   0x2E 
#define C3XBUCK_OUTPUT_VOLTAGE_1150mV   0x2F 
#define C3XBUCK_OUTPUT_VOLTAGE_1160mV   0x30 
#define C3XBUCK_OUTPUT_VOLTAGE_1170mV   0x31 
#define C3XBUCK_OUTPUT_VOLTAGE_1180mV   0x32 
#define C3XBUCK_OUTPUT_VOLTAGE_1190mV   0x33 
#define C3XBUCK_OUTPUT_VOLTAGE_1200mV   0x34 
#define C3XBUCK_OUTPUT_VOLTAGE_1210mV   0x35 
#define C3XBUCK_OUTPUT_VOLTAGE_1220mV   0x36 
#define C3XBUCK_OUTPUT_VOLTAGE_1230mV   0x37 
#define C3XBUCK_OUTPUT_VOLTAGE_1240mV   0x38 
#define C3XBUCK_OUTPUT_VOLTAGE_1250mV   0x39 
#define C3XBUCK_OUTPUT_VOLTAGE_1260mV   0x3A 
#define C3XBUCK_OUTPUT_VOLTAGE_1270mV   0x3B 
#define C3XBUCK_OUTPUT_VOLTAGE_1280mV   0x3C 
#define C3XBUCK_OUTPUT_VOLTAGE_1290mV   0x3D 
#define C3XBUCK_OUTPUT_VOLTAGE_1300mV   0x3E 
#define C3XBUCK_OUTPUT_VOLTAGE_1310mV   0x3F 
#define C3XBUCK_OUTPUT_VOLTAGE_1320mV   0x40 
#define C3XBUCK_OUTPUT_VOLTAGE_1330mV   0x41 
#define C3XBUCK_OUTPUT_VOLTAGE_1340mV   0x42 
#define C3XBUCK_OUTPUT_VOLTAGE_1350mV   0x43 
#define C3XBUCK_OUTPUT_VOLTAGE_1360mV   0x44 
#define C3XBUCK_OUTPUT_VOLTAGE_1370mV   0x45 
#define C3XBUCK_OUTPUT_VOLTAGE_1380mV   0x46 
#define C3XBUCK_OUTPUT_VOLTAGE_1390mV   0x47 
#define C3XBUCK_OUTPUT_VOLTAGE_1400mV   0x48 
#define C3XBUCK_OUTPUT_VOLTAGE_1410mV   0x49 
#define C3XBUCK_OUTPUT_VOLTAGE_1420mV   0x4A 
#define C3XBUCK_OUTPUT_VOLTAGE_1430mV   0x4B 
#define C3XBUCK_OUTPUT_VOLTAGE_1440mV   0x4C 
#define C3XBUCK_OUTPUT_VOLTAGE_1450mV   0x4D 
#define C3XBUCK_OUTPUT_VOLTAGE_1460mV   0x4E 
#define C3XBUCK_OUTPUT_VOLTAGE_1470mV   0x4F 
#define C3XBUCK_OUTPUT_VOLTAGE_1480mV   0x50 
#define C3XBUCK_OUTPUT_VOLTAGE_1490mV   0x51 
#define C3XBUCK_OUTPUT_VOLTAGE_1500mV   0x52 
#define C3XBUCK_OUTPUT_VOLTAGE_1510mV   0x53 
#define C3XBUCK_OUTPUT_VOLTAGE_1520mV   0x54 
#define C3XBUCK_OUTPUT_VOLTAGE_1530mV   0x55 
#define C3XBUCK_OUTPUT_VOLTAGE_1540mV   0x56 
#define C3XBUCK_OUTPUT_VOLTAGE_1550mV   0x57 
#define C3XBUCK_OUTPUT_VOLTAGE_1560mV   0x58 
#define C3XBUCK_OUTPUT_VOLTAGE_1570mV   0x59 
#define C3XBUCK_OUTPUT_VOLTAGE_1580mV   0x5A 
#define C3XBUCK_OUTPUT_VOLTAGE_1590mV   0x5B 
#define C3XBUCK_OUTPUT_VOLTAGE_1600mV   0x5C 
#define C3XBUCK_OUTPUT_VOLTAGE_1610mV   0x5D 
#define C3XBUCK_OUTPUT_VOLTAGE_1620mV   0x5E 
#define C3XBUCK_OUTPUT_VOLTAGE_1630mV   0x5F 
#define C3XBUCK_OUTPUT_VOLTAGE_1640mV   0x60 
#define C3XBUCK_OUTPUT_VOLTAGE_1650mV   0x61 
#define C3XBUCK_OUTPUT_VOLTAGE_1660mV   0x62 
#define C3XBUCK_OUTPUT_VOLTAGE_1670mV   0x63 
#define C3XBUCK_OUTPUT_VOLTAGE_1680mV   0x64 
#define C3XBUCK_OUTPUT_VOLTAGE_1690mV   0x65 
#define C3XBUCK_OUTPUT_VOLTAGE_1700mV   0x66 
#define C3XBUCK_OUTPUT_VOLTAGE_1710mV   0x67 
#define C3XBUCK_OUTPUT_VOLTAGE_1720mV   0x68 
#define C3XBUCK_OUTPUT_VOLTAGE_1730mV   0x69 
#define C3XBUCK_OUTPUT_VOLTAGE_1740mV   0x6A 
#define C3XBUCK_OUTPUT_VOLTAGE_1750mV   0x6B 
#define C3XBUCK_OUTPUT_VOLTAGE_1760mV   0x6C 
#define C3XBUCK_OUTPUT_VOLTAGE_1770mV   0x6D 
#define C3XBUCK_OUTPUT_VOLTAGE_1780mV   0x6E 
#define C3XBUCK_OUTPUT_VOLTAGE_1790mV   0x6F 
#define C3XBUCK_OUTPUT_VOLTAGE_1800mV   0x70 
#define C3XBUCK_OUTPUT_VOLTAGE_1810mV   0x71 
#define C3XBUCK_OUTPUT_VOLTAGE_1820mV   0x72 
#define C3XBUCK_OUTPUT_VOLTAGE_1830mV   0x73 
#define C3XBUCK_OUTPUT_VOLTAGE_1840mV   0x74 
#define C3XBUCK_OUTPUT_VOLTAGE_1850mV   0x75 
#define C3XBUCK_OUTPUT_VOLTAGE_1860mV   0x76 
#define C3XBUCK_OUTPUT_VOLTAGE_1870mV   0x77 
#define C3XBUCK_OUTPUT_VOLTAGE_1880mV   0x78 
#define C3XBUCK_OUTPUT_VOLTAGE_1890mV   0x79 
#define C3XBUCK_OUTPUT_VOLTAGE_1900mV   0x7A 
#define C3XBUCK_OUTPUT_VOLTAGE_1910mV   0x7B 
#define C3XBUCK_OUTPUT_VOLTAGE_1920mV   0x7C 
#define C3XBUCK_OUTPUT_VOLTAGE_1930mV   0x7D 
#define C3XBUCK_OUTPUT_VOLTAGE_1940mV   0x7E 
#define C3XBUCK_OUTPUT_VOLTAGE_1950mV   0x7F 
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en1;
    digital_out_t en2;
    digital_out_t en3;
   
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} c3xbuck_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en1;
    pin_name_t en2;
    pin_name_t en3;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} c3xbuck_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void c3xbuck_cfg_setup ( c3xbuck_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c3xbuck Click object.
 * @param cfg     Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 * @returns       Initialization response. 
 */
C3XBUCK_RETVAL c3xbuck_init ( c3xbuck_t *ctx, c3xbuck_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 3xBuck click.
 */
void c3xbuck_default_cfg ( c3xbuck_t *ctx );

/**
 * @brief Write byte function
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function writes data from the desired register.
 */
void c3xbuck_write_byte ( c3xbuck_t *ctx, uint8_t reg, uint8_t data_value );


/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @returns            Read data;
 * @description This function reads data from the desired register.
 */
uint8_t c3xbuck_read_byte( c3xbuck_t *ctx, uint8_t reg);


/**
 * @brief Enable Buck function
 *
 * @param ctx  Click object.
 *
 * @description This function enables desired Buck on the click.
 */
void c3xbuck_enable_buck ( c3xbuck_t *ctx, uint8_t buck );

/**
 * @brief Disable Buck function
 *
 * @param ctx  Click object.
 *
 * @description This function disables 3xBuck click.
 */
void c3xbuck_disable_buck ( c3xbuck_t *ctx, uint8_t buck );

/**
 * @brief Set voltage function.
 *
 * @param ctx      Click object.
 * @param buck     Buck 1 - 3
 * @param voltage  Voltage value
 *
 * @description This function sets voltage on desired Buck.
 */
void c3xbuck_set_voltage ( c3xbuck_t *ctx, uint8_t buck, uint8_t voltage );

/**
 * @brief Get status function
 *
 * @param ctx  Click object.
 * @returns    Status register value.
 * 
 * @description This function returns status register.
 */
uint8_t c3xbuck_get_status( c3xbuck_t *ctx );

/**
 * @brief  Configuration function.
 *
 * @param ctx  Click object.
 * @param buck Buck 1 - 3.
 * 
 * @description This function executes default configuration for 3xBuck click.
 */
void c3xbuck_configuration_buck( c3xbuck_t *ctx, uint8_t buck, uint8_t config);

#ifdef __cplusplus
}
#endif
#endif  // _C3XBUCK_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

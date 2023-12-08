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
 * \brief This file contains API for Heart rate 3 Click driver.
 *
 * \addtogroup heartrate3 Heart rate 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HEARTRATE3_H
#define HEARTRATE3_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define HEARTRATE3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );  \
  cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
  cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HEARTRATE3_OK                       0
#define HEARTRATE3_ERROR                   -1
/** \} */

/**
 * \defgroup dev_slave_adr Device slave address
 * \{
 */
#define HEARTRATE3_SLAVE_ADDR               0x58
/** \} */

/**
 * \defgroup register_map Register map
 * \{
 */
#define HEARTRATE3_REG_CONTROL0             0x00
#define HEARTRATE3_REG_LED2STC              0x01
#define HEARTRATE3_REG_LED2ENDC             0x02
#define HEARTRATE3_REG_LED1LEDSTC           0x03
#define HEARTRATE3_REG_LED1LEDENDC          0x04
#define HEARTRATE3_REG_ALED2STC             0x05
#define HEARTRATE3_REG_ALED2ENDC            0x06
#define HEARTRATE3_REG_LED1STC              0x07
#define HEARTRATE3_REG_LED1ENDC             0x08
#define HEARTRATE3_REG_LED2LEDSTC           0x09
#define HEARTRATE3_REG_LED2LEDENDC          0x0A
#define HEARTRATE3_REG_ALED1STC             0x0B
#define HEARTRATE3_REG_ALED1ENDC            0x0C
#define HEARTRATE3_REG_LED2CONVST           0x0D
#define HEARTRATE3_REG_LED2CONVEND          0x0E
#define HEARTRATE3_REG_ALED2CONVST          0x0F
#define HEARTRATE3_REG_ALED2CONVEND         0x10
#define HEARTRATE3_REG_LED1CONVST           0x11
#define HEARTRATE3_REG_LED1CONVEND          0x12
#define HEARTRATE3_REG_ALED1CONVST          0x13
#define HEARTRATE3_REG_ALED1CONVEND         0x14
#define HEARTRATE3_REG_ADCRSTSTCT0          0x15
#define HEARTRATE3_REG_ADCRSTENDCT0         0x16
#define HEARTRATE3_REG_ADCRSTSTCT1          0x17
#define HEARTRATE3_REG_ADCRSTENDCT1         0x18
#define HEARTRATE3_REG_ADCRSTSTCT2          0x19
#define HEARTRATE3_REG_ADCRSTENDCT2         0x1A
#define HEARTRATE3_REG_ADCRSTSTCT3          0x1B
#define HEARTRATE3_REG_ADCRSTENDCT3         0x1C
#define HEARTRATE3_REG_PRPCOUNT             0x1D
#define HEARTRATE3_REG_CONTROL1             0x1E
#define HEARTRATE3_REG_TIA_GAIN_SEP         0x20
#define HEARTRATE3_REG_TIA_GAIN             0x21
#define HEARTRATE3_REG_LEDCNTRL             0x22
#define HEARTRATE3_REG_CONTROL2             0x23
#define HEARTRATE3_REG_ALARM                0x29
#define HEARTRATE3_REG_LED2VAL              0x2A
#define HEARTRATE3_REG_ALED2VAL             0x2B
#define HEARTRATE3_REG_LED1VAL              0x2C
#define HEARTRATE3_REG_ALED1VAL             0x2D
#define HEARTRATE3_REG_LED2_ALED2VAL        0x2E
#define HEARTRATE3_REG_LED1_ALED1VAL        0x2F
#define HEARTRATE3_REG_CONTROL3             0x31
#define HEARTRATE3_REG_PDNCYCLESTC          0x32
#define HEARTRATE3_REG_PDNCYCLEENDC         0x33
#define HEARTRATE3_REG_PROG_TG_STC          0x34
#define HEARTRATE3_REG_PROG_TG_ENDC         0x35
#define HEARTRATE3_REG_LED3LEDSTC           0x36
#define HEARTRATE3_REG_LED3LEDENDC          0x37
#define HEARTRATE3_REG_CLKDIV_PRF           0x39
#define HEARTRATE3_REG_OFFDAC               0x3A
#define HEARTRATE3_REG_DEC                  0x3D
#define HEARTRATE3_REG_AVG_LED2_ALED2VAL    0x3F
#define HEARTRATE3_REG_AVG_LED1_ALED1VAL    0x40
/** \} */

/**
 * \defgroup cmd_list Configuration commands list
 * \{
 */
#define HEARTRATE3_CONTROL0_CMD             0x000000ul
#define HEARTRATE3_LED2STC_CMD              0x000050ul
#define HEARTRATE3_LED2ENDC_CMD             0x00018Ful
#define HEARTRATE3_LED1LEDSTC_CMD           0x000320ul
#define HEARTRATE3_LED1LEDENDC_CMD          0x0004AFul
#define HEARTRATE3_ALED2STC_CMD             0x0001E0ul
#define HEARTRATE3_ALED2ENDC_CMD            0x00031Ful
#define HEARTRATE3_LED1STC_CMD              0x000370ul
#define HEARTRATE3_LED1ENDC_CMD             0x0004AFul
#define HEARTRATE3_LED2LEDSTC_CMD           0x000000ul
#define HEARTRATE3_LED2LEDENDC_CMD          0x00018Ful
#define HEARTRATE3_ALED1STC_CMD             0x0004FFul
#define HEARTRATE3_ALED1ENDC_CMD            0x00063Eul
#define HEARTRATE3_LED2CONVST_CMD           0x000198ul
#define HEARTRATE3_LED2CONVEND_CMD          0x0005BBul
#define HEARTRATE3_ALED2CONVST_CMD          0x0005C4ul
#define HEARTRATE3_ALED2CONVEND_CMD         0x0009E7ul
#define HEARTRATE3_LED1CONVST_CMD           0x0009F0ul
#define HEARTRATE3_LED1CONVEND_CMD          0x000E13ul
#define HEARTRATE3_ALED1CONVST_CMD          0x000E1Cul
#define HEARTRATE3_ALED1CONVEND_CMD         0x00123Ful
#define HEARTRATE3_ADCRSTSTCT0_CMD          0x000191ul
#define HEARTRATE3_ADCRSTENDCT0_CMD         0x000197ul
#define HEARTRATE3_ADCRSTSTCT1_CMD          0x0005BDul
#define HEARTRATE3_ADCRSTENDCT1_CMD         0x0005C3ul
#define HEARTRATE3_ADCRSTSTCT2_CMD          0x0009E9ul
#define HEARTRATE3_ADCRSTENDCT2_CMD         0x0009EFul
#define HEARTRATE3_ADCRSTSTCT3_CMD          0x000E15ul
#define HEARTRATE3_ADCRSTENDCT3_CMD         0x000E1Bul
#define HEARTRATE3_PRPCOUNT_CMD             0x009C3Eul
#define HEARTRATE3_CONTROL1_CMD             0x000103ul
#define HEARTRATE3_TIA_GAIN_SEP_CMD         0x008003ul
#define HEARTRATE3_TIA_GAIN_CMD             0x000003ul
#define HEARTRATE3_LEDCNTRL_CMD             0x01B6D9ul
#define HEARTRATE3_CONTROL2_CMD             0x104218ul
#define HEARTRATE3_ALARM_CMD                0x000000ul
#define HEARTRATE3_CONTROL3_CMD             0x000000ul
#define HEARTRATE3_PDNCYCLESTC_CMD          0x00155Ful
#define HEARTRATE3_PDNCYCLEENDC_CMD         0x00991Eul
#define HEARTRATE3_PROG_TG_STC_CMD          0x000000ul
#define HEARTRATE3_PROG_TG_ENDC_CMD         0x000000ul
#define HEARTRATE3_LED3LEDSTC_CMD           0x000190ul
#define HEARTRATE3_LED3LEDENDC_CMD          0x00031Ful
#define HEARTRATE3_CLKDIV_PRF_CMD           0x000000ul
#define HEARTRATE3_OFFDAC_CMD               0x000000ul
/** \} */

/**
 * \defgroup pin_state Pin state
 * \{
 */
#define HEARTRATE3_PIN_STATE_LOW            0x00
#define HEARTRATE3_PIN_STATE_HIGH           0x01
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
    digital_out_t rst;
    digital_out_t clk;

    // Input pins 
    digital_in_t rdy;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} heartrate3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t rst;
    pin_name_t clk;
    pin_name_t rdy;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} heartrate3_cfg_t;

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
 * @details This function initializes click configuration structure to 
 * init state.
 * @note All used pins will be set to unconnected state.
 */
void heartrate3_cfg_setup ( heartrate3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals 
 * used for this click.
 */
err_t heartrate3_init ( heartrate3_t *ctx, heartrate3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for 
 * HeartRate3 click.
 */
err_t heartrate3_default_cfg ( heartrate3_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @details This function writes data to the desired register.
 */
err_t heartrate3_generic_write ( heartrate3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_out     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @details This function reads data from the desired register.
 */
err_t heartrate3_generic_read ( heartrate3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Write data function
 *
 * @param ctx      Click object.
 * @param reg_adr  8-bit data that defines register's address
 * @param wr_data  32-bit used defined data to be written into register
 *
 * @details Function is used to write 32-bit data into register.
**/
err_t heartrate3_write_data ( heartrate3_t *ctx, uint8_t reg_adr, uint32_t wr_data );

/**
 * @brief Read 24-bit data function
 *
 * @param ctx      Click object. 
 * @param reg_adr  8-bit data that defines register's address
 * @param data_out 24-bit value read from chosen register
 *
 * @details Function is used to read 24-bit value from register.
**/
err_t heartrate3_read_24bit ( heartrate3_t *ctx, uint8_t reg_adr, uint32_t *data_out );

/**
 * @brief Read 16-bit data function
 *
 * @param ctx      Click object.
 * @param reg_adr  8-bit data that defines register's address
 * @param data_out 16-bit value read from chosen register
 *
 * @details Function is used to read 16-bit value from register.
**/
err_t heartrate3_read_16bit ( heartrate3_t *ctx, uint8_t reg_adr, uint16_t *data_out );

/**
 * @brief Set Reset pin state
 *
 * @param ctx          Click object.
 * @param state  0 - rst pin cleared / 1 - rst pin set
 *
 * @details Function is used to set or clear rst pin.
 */
void heartrate3_rst_state ( heartrate3_t *ctx, uint8_t state );

/**
 * @brief Set Clock pin state
 *
 * @param ctx          Click object.
 * @param state  0 - clk pin cleared / 1 - clk pin set
 *
 * @details Function is used to set or clear clk pin.
 */
void heartrate3_clk_state ( heartrate3_t *ctx, uint8_t state );

/**
 * @brief Check data ready function
 *
 * @param ctx          Click object.
 *
 * @return 1 : data ready / 0 : data not ready
 *
 * @details Function is used to check data ready flag.
**/
uint8_t heartrate3_check_data_ready ( heartrate3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HEARTRATE3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

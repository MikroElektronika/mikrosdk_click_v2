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
 * \brief This file contains API for DAC 8 Click driver.
 *
 * \addtogroup dac8 DAC 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC8_H
#define DAC8_H

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
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define DAC8_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define DAC8_MASTER_I2C                                           0
#define DAC8_MASTER_SPI                                           1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DAC8_RETVAL  uint8_t

#define DAC8_OK                                                   0x00
#define DAC8_INIT_ERROR                                           0xFF
/** \} */

/**
 * \defgroup dac_60501 DAC 60501
 * \{
 */
#define DAC8_I2C_SLAVE_ADDR                                       0x48
/** \} */

/**
 * \defgroup register_map Register Map
 * \{
 */
#define DAC8_REG_NOOP                                             0x00
#define DAC8_REG_DEVID                                            0x01
#define DAC8_REG_SYNC                                             0x02
#define DAC8_REG_CONFIG                                           0x03
#define DAC8_REG_GAIN                                             0x04
#define DAC8_REG_TRIGGER                                          0x05
#define DAC8_REG_STATUS                                           0x07
#define DAC8_REG_DAC                                              0x08
/** \} */

/**
 * \defgroup sync_register SYNC Register
 * \{
 */
#define DAC8_SYNC_DISABLE                                         0x0000
#define DAC8_SYNC_ENABLE                                          0x0001
/** \} */

/**
 * \defgroup config_register CONFIG Register
 * \{
 */
#define DAC8_CONFIG_REF_PWDWN_ENABLE                              0x0000
#define DAC8_CONFIG_REF_PWDWN_DISABLE                             0x0001
#define DAC8_CONFIG_REF_PWDWN_BIT_MASK                            0x0001
#define DAC8_CONFIG_DAC_PWDWN_DISABLE                             0x0000
#define DAC8_CONFIG_DAC_PWDWN_ENABLE                              0x0001
#define DAC8_CONFIG_DAC_PWDWN_BIT_MASK                            0x0001
/** \} */

/**
 * \defgroup gain_register GAIN Register
 * \{
 */
#define DAC8_GAIN_REF_DIV_DISABLE                                 0x0000
#define DAC8_GAIN_REF_DIV_2                                       0x0001
#define DAC8_GAIN_REF_DIV_BIT_MASK                                0x0001
#define DAC8_GAIN_BUFF_GAIN_1                                     0x0000
#define DAC8_GAIN_BUFF_GAIN_2                                     0x0001
#define DAC8_GAIN_BUFF_GAIN_BIT_MASK                              0x0001
/** \} */

/**
 * \defgroup trigger_register TRIGGER Register
 * \{
 */
#define DAC8_TRIGGER_LDAC                                         0x0010
#define DAC8_TRIGGER_SOFT_RESET                                   0x000A
/** \} */

/**
 * \defgroup status_register STATUS Register
 * \{
 */
#define DAC8_STATUS_REF_ALARM_BIT_MASK                            0x0001

#define DAC8_ERROR                                                0x00
#define DAC8_SUCCESS                                              0x01
/** \} */

/**
 * \defgroup dac_8554 DAC 8554
 * \{
 */
#define DAC8_ADDR_DEFAULT                                         0x00
#define DAC8_ADDR_BIT_MASK                                        0x03

#define DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE                      0x00
#define DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_UPDATE                     0x01
#define DAC8_CTRL_UPD_AN_OUT_SIMULTANEOUS_UPDATE                  0x02
#define DAC8_CTRL_UPD_AN_OUT_BROADCAST_UPDATE                     0x03
#define DAC8_CTRL_UPD_AN_OUT_BIT_MASK                             0x03

#define DAC8_DAC_SEL_CH_A                                         0x00
#define DAC8_DAC_SEL_CH_B                                         0x01
#define DAC8_DAC_SEL_CH_C                                         0x02
#define DAC8_DAC_SEL_CH_D                                         0x03
#define DAC8_DAC_SEL_ALL_CH_BROADCAST                             0x30
#define DAC8_DAC_SEL_CH_BIT_MASK                                  0x03

#define DAC8_PWR_MODE_POWER_UP                                    0x00
#define DAC8_PWR_MODE_POWER_DOWN_OUT_HIGH_IMPEDANCE               0x09
#define DAC8_PWR_MODE_POWER_DOWN_OUT_TYP_1K_TO_GND                0x0B
#define DAC8_PWR_MODE_POWER_DOWN_OUT_TYP_100K_TO_GND              0x0D
#define DAC8_PWR_MODE_POWER_DOWN_OUT_HIGH_IMPEDANCES              0x0F
#define DAC8_PWR_UP_MODE_BIT_MASK                                 0x01
#define DAC8_PWR_DOWN_MODE_BIT_MASK                               0x0E

#define DAC8_24_BIT_BIT_MASK                                      0x00FFFFFF

#define DAC8_DAC_OUT_DATA_MIN                                     0x0000
#define DAC8_DAC_OUT_DATA_MAX                                     0x0FFF

#define DAC8_LDAC_LOW                                             0x00
#define DAC8_LDAC_HIGH                                            0x01

#define DAC8_DAC8554_ENABLE                                       0x00
#define DAC8_DAC8554_DISABLE                                      0x01
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  dac8_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *dac8_master_io_t )( struct dac8_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct dac8_s
{   
    // Modules 

   i2c_master_t i2c;
   spi_master_t spi;

   // Output pins 
   
   digital_out_t cs;
   digital_out_t pwm;
   digital_out_t rst;

   // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   dac8_master_io_t write_f;
   dac8_master_io_t read_f;
   dac8_select_t master_sel;

} dac8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
   // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

   // Additional gpio pins 

   pin_name_t pwm;
   pin_name_t rst;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   dac8_select_t sel;

} dac8_cfg_t;

typedef struct
{
    uint8_t addr;
    uint8_t ctrl_upd_an_out;
    uint8_t dac_sel;
    uint8_t pwr_mode;
    uint16_t dac_val;
}
dac8_cfg_data_t;

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
 *
 * @note All used pins will be set to unconnected state.
 */
void dac8_cfg_setup ( dac8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DAC8_RETVAL dac8_init ( dac8_t *ctx, dac8_cfg_t *cfg, uint8_t master_mode );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void dac8_generic_write ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx       Click object.
 * @param reg       Register address.
 * @param data_buf  Data buf to be written.
 * @param len       Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void dac8_generic_read ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Enable synchronous function.
 *
 * @param ctx      Click object. 
 * @param en_sync
 * <pre>
 * - 0x0000 ( DAC8_SYNC_DISABLE ) : Asynchronous mode.
 * - 0x0001 ( DAC8_SYNC_ENABLE )  : Synchronous mode.
 * </pre> 
 *
 * @retval status
 * <pre> 
 * - 0x00 ( DAC8_ERROR )   : Error.
 * - 0x01 ( DAC8_SUCCESS ) : Success.
 * </pre>
 *
 * @description The function set synchronous or asynchronous mode
 * of the DAC60501, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
 * With Precision Internal Reference on DAC 8 Click board.
**/
DAC8_RETVAL dac8_enable_sync ( dac8_t *ctx, uint8_t en_sync );

/**
 * @brief Set config function.
 *
 * @param ctx       Click object. 
 * @param en_ref_pwdwn
 * <pre> 
 * - 0x0000 ( DAC8_CONFIG_REF_PWDWN_ENABLE )  : Enable the internal reference.
 * - 0x0001 ( DAC8_CONFIG_REF_PWDWN_DISABLE ) : Disables the internal reference.
 * </pre>
 * @param en_dac_pwdwn
 * <pre> 
 * - 0x0000 ( DAC8_CONFIG_DAC_PWDWN_DISABLE ) : DAC in power-up mode.
 * - 0x0001 ( DAC8_CONFIG_DAC_PWDWN_ENABLE )  : DAC in power-down mode.
 * </pre> 
 *
 * @retval status
 * <pre> 
 * - 0x00 ( DAC8_ERROR )   : Error.
 * - 0x01 ( DAC8_SUCCESS ) : Success.
 * </pre>  
 *
 * @description The function set configuration
 * of the DAC60501, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
 * With Precision Internal Reference on DAC 8 Click board.
**/
DAC8_RETVAL dac8_set_config ( dac8_t *ctx, uint16_t en_ref_pwdwn, uint16_t en_dac_pwdwn );

/**
 * @brief Set gain function.
 *
 * @param ctx       Click object. 
 * @param en_ref_div
 * <pre> 
 * - 0x0000 ( DAC8_GAIN_REF_DIV_DISABLE ) : Reference voltage is unaffected.
 * - 0x0001 ( DAC8_GAIN_REF_DIV_2 )       : Reference voltage is internally 
 * divided by a factor of 2.
 * </pre> 
 * @param en_buff_gain
 * <pre> 
 * - 0x0000 ( DAC8_GAIN_BUFF_GAIN_1 ) : DAC has a gain of 1.
 * - 0x0001 ( DAC8_GAIN_BUFF_GAIN_2 )  : DAC has a gain of 2.
 * </pre> 
 *
 * @retval status
 * <pre> 
 * - 0x00 ( DAC8_ERROR )   : Error.
 * - 0x01 ( DAC8_SUCCESS ) : Success.
 * </pre>  
 *
 * @description The function set gain
 * of the DAC60501, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
 * With Precision Internal Reference on DAC 8 Click board.
**/
DAC8_RETVAL dac8_set_gain ( dac8_t *ctx, uint16_t en_ref_div, uint16_t en_buff_gain );

/**
 * @brief Set synchronously load function.
 *
 * @param ctx       Click object. 
 * 
 * @description The function set synchronously load the DAC in synchronous mode
 * of the DAC60501, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
 * With Precision Internal Reference on DAC 8 Click board.
**/
void dac8_set_synchronously_load ( dac8_t *ctx );

/**
 * @brief Set reset function.
 *
 * @param ctx       Click object. 
 * 
 * @description The function set reset
 * of the DAC60501, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
 * With Precision Internal Reference on DAC 8 Click board.
**/
void dac8_soft_reset ( dac8_t *ctx );

/**
 * @brief Get ref alarm function.
 *
 * @param ctx       Click object. 
 * 
 * @retval return
 * <pre> 
 * - 0x00 : Ok.
 * - 0x01 : Difference between the reference and supply pins 
 * is below a minimum analog threshold.
 * </pre>   
 *
 * @description The function get reference alarm
 * of the DAC60501, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
 * With Precision Internal Reference on DAC 8 Click board.
**/
uint8_t dac8_get_ref_alarm ( dac8_t *ctx );

/**
 * @brief Set vref function.
 *
 * @param ctx       Click object.  
 * @param vref_mv   Vref in mV.
 *
 * @retval status
 * <pre>  
 * - 0x00 ( DAC8_ERROR )   : Error.
 * - 0x01 ( DAC8_SUCCESS ) : Success.
 * </pre>   
 *
 * @description The function set Vref ( mV ) by write 12-bit 
 * to the DAC data register
 * of the DAC60501, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
 * With Precision Internal Reference on DAC 8 Click board.
**/
DAC8_RETVAL dac8_set_vref ( dac8_t *ctx, uint16_t vref_mv );

/**
 * @brief Device enable function.
 *
 * @param ctx       Click object.  
 * @param en_sel
 * <pre>   
 * - 0x00 ( DAC8_DAC8554_DISABLE ) : Disable.
 * - 0x01 ( DAC8_DAC8554_ENABLE )  : Enable.
 * </pre>   
 *
 * @description The function device enable - EN ( RST ) pin tied to a logic high
 * or disable - tied to a logic low 
 * of the DAC8554, 16-bit, quad-channel, ultra-low glitch, voltage output
 * digital-to-analog converter on DAC 8 Click board.
**/
void dac8_device_enable ( dac8_t *ctx, uint8_t en_sel );

/**
 * @brief Set LDAC function.
 *
 * @param ctx       Click object.  
 * @param en_sel
 * <pre>   
 * - 0x00 ( DAC8_LDAC_LOW )  : Low state.
 * - 0x01 ( DAC8_LDAC_HIGH ) : High state.
 * </pre>   
 *
 * @description The function states of the LD ( PWM ) pin
 * of the DAC8554, 16-bit, quad-channel, ultra-low glitch, voltage output
 * digital-to-analog converter on DAC 8 Click board.
**/
void dac8_set_ldac ( dac8_t *ctx, uint8_t ldac_sel );

/**
 * @brief Load DAC function.
 *
 * @param ctx       Click object.  
 * 
 * @description The function load DAC s are simultaneously updated with the contents of the 
 * corresponding data buffers. Used as a positive edge triggered timing signal for asynchronous 
 * DAC updates. Data buffers of all channels must be loaded with desired data before
 * call Load DAC function.
**/
void dac8_load_dac ( dac8_t *ctx );

/**
 * @brief Generic SPI write function.
 *
 * @param ctx       Click object.   
 * @param tx_data   24-bit data to write.
 *
 * @description The function write the 24-bit data
 * to the shift registe of the DAC8554, 
 * 16-bit, quad-channel, ultra-low glitch, voltage output
 * digital-to-analog converter on DAC 8 Click board.
**/
void dac8_generic_spi_write ( dac8_t *ctx, uint32_t tx_data );

/**
 * @brief Set device config function.
 *
 * @param ctx           Click object.   
 * @param dac8_cfg_t    Structure where data be stored.
 *
 * @description The function set configuration of the DAC8554,
 * 16-bit, quad-channel, ultra-low glitch, voltage output
 * digital-to-analog converter on DAC 8 Click board.
**/
void dac8_device_config ( dac8_t *ctx, dac8_cfg_data_t cfg_data );

#ifdef __cplusplus
}
#endif
#endif  // _DAC8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

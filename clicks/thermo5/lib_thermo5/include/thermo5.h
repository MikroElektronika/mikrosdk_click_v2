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
 * \brief This file contains API for THERMO 5 Click driver.
 *
 * \addtogroup thermo5 THERMO 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO5_H
#define THERMO5_H

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
#define THERMO5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO5_RETVAL  uint8_t

#define THERMO5_OK           0x00
#define THERMO5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_slave_address I2C Slave Address
 * \{
 */
#define THERMO5_I2C_ADDRESS                                             0x4C
/** \} */

/**
 * \defgroup temperature_data_registers Temperature Data Registers
 * \{
 */
#define THERMO5_INTER_DIO_DATA_HI_BYTE                                  0x00
#define THERMO5_INTER_DIO_DATA_LO_BYTE                                  0x29
#define THERMO5_EXTER_DIO_1_DATA_HI_BYTE                                0x01
#define THERMO5_EXTER_DIO_1_DATA_LO_BYTE                                0x10
#define THERMO5_EXTER_DIO_2_DATA_HI_BYTE                                0x23
#define THERMO5_EXTER_DIO_2_DATA_LO_BYTE                                0x24
#define THERMO5_EXTER_DIO_3_HI_BYTE                                     0x2A
#define THERMO5_EXTER_DIO_3_LO_BYTE                                     0x2B

#define THERMO5_INTER_DIODE                                             0x0029
#define THERMO5_EXTER_DIODE1                                            0x0110
#define THERMO5_EXTER_DIODE2                                            0x2324
#define THERMO5_EXTER_DIODE3                                            0x2A2B
/** \} */

/**
 * \defgroup status_register Status Register
 * \{
 */
#define THERMO5_STAT                                                    0x02
/** \} */

/**
 * \defgroup configuration_register Configuration Register
 * \{
 */
#define THERMO5_CONFIG                                                  0x03
/** \} */

/**
 * \defgroup conversion_rate_register Conversion Rate Register
 * \{
 */
#define THERMO5_CONVERS_RATE                                            0x04
/** \} */

/**
 * \defgroup temperature_limit_registers Temperature Limit Registers
 * \{
 */
#define THERMO5_INTER_DIO_HI_LIM                                        0x05
#define THERMO5_INTER_DIO_LO_LIM                                        0x06
#define THERMO5_EXTER_DIO_1_HI_LIM_HI_BYTE                              0x07
#define THERMO5_EXTER_DIO_1_HI_LIM_LO_BYTE                              0x13
#define THERMO5_EXTER_DIO_1_LO_LIM_HI_BYTE                              0x08
#define THERMO5_EXTER_DIO_1_LO_LIM_LO_BYTE                              0x14
#define THERMO5_EXTER_DIO_2_HI_LIM_HI_BYTE                              0x15
#define THERMO5_EXTER_DIO_2_LO_LIM_HI_BYTE                              0x16
#define THERMO5_EXTER_DIO_2_HI_LIM_LO_BYTE                              0x17
#define THERMO5_EXTER_DIO_2_LO_LIM_LO_BYTE                              0x18
#define THERMO5_EXTER_DIO_3_HI_LIM_HI_BYTE                              0x2C
#define THERMO5_EXTER_DIO_3_LO_LIM_HI_BYTE                              0x2D
#define THERMO5_EXTER_DIO_3_HI_LIM_LO_BYTE                              0x2E
#define THERMO5_EXTER_DIO_3_LO_LIM_LO_BYTE                              0x2F
/** \} */

/**
 * \defgroup scratchpad_register Scratchpad Register
 * \{
 */
#define THERMO5_SCRATCHPAD_1                                            0x11
#define THERMO5_SCRATCHPAD_2                                            0x12
/** \} */

/**
 * \defgroup one_shot_register One Shot Register
 * \{
 */
#define THERMO5_ONE_SHOT                                                0x0F
/** \} */

/**
 * \defgroup therm_limit_register Therm Limit Register
 * \{
 */
#define THERMO5_EXTER_DIO_1_THERM_LIM                                   0x19
#define THERMO5_EXTER_DIO_2_THERM_LIM                                   0x1A
#define THERMO5_INTER_DIO_THERM_LIM                                     0x20
#define THERMO5_THERM_HYSTERESIS                                        0x21
#define THERMO5_EXTER_DIO_3_THERM_LIM                                   0x30
/** \} */

/**
 * \defgroup external_diode_fault_register External Diode Fault Register
 * \{
 */
#define THERMO5_EXTER_DIO_FAULT                                         0x1B
/** \} */

/**
 * \defgroup channel_mask_register Channel Mask Register
 * \{
 */
#define THERMO5_CHANNEL_MASK_REGISTER                                   0x1F
/** \} */

/**
 * \defgroup consecutive_alert_register Consecutive ALERT Register
 * \{
 */
#define THERMO5_CONSECUTIVE_ALERT                                       0x22
/** \} */

/**
 * \defgroup beta_configuration_register Beta Configuration Register
 * \{
 */
#define THERMO5_EXTER_DIO_1_BETA_CONFIG                                 0x25
#define THERMO5_EXTER_DIO_2_BETA_CONFIG                                 0x26
/** \} */

/**
 * \defgroup ideality_configuration_register Ideality Configuration Register
 * \{
 */
#define THERMO5_EXTER_DIO_1_IDE_FAC                                     0x27
#define THERMO5_EXTER_DIO_2_IDE_FAC                                     0x28
#define THERMO5_EXTER_DIO_3_IDE_FAC                                     0x31
/** \} */

/**
 * \defgroup high_limit_status_register High Limit Status Register
 * \{
 */
#define THERMO5_HI_LIM_STAT                                             0x35
/** \} */

/**
 * \defgroup low_limit_status_register Low Limit Status Register
 * \{
 */
#define THERMO5_LO_LIM_STAT                                             0x36
/** \} */

/**
 * \defgroup therm_limit_status_register Therm Limit Status Register
 * \{
 */
#define THERMO5_THERM_LIM_STAT                                          0x37
/** \} */

/**
 * \defgroup filter_configuration_register Filter Configuration Register
 * \{
 */
#define THERMO5_FILTER_CONTROL                                          0x40
/** \} */

/**
 * \defgroup product_id_register Product ID Register
 * \{
 */
#define THERMO5_PRODUCT_ID                                              0xFD
/** \} */

/**
 * \defgroup manufacturer_id_register Manufacturer ID Register
 * \{
 */
#define THERMO5_MANUFACTURER_ID                                         0xFE
/** \} */

/**
 * \defgroup revision_register Revision Register
 * \{
 */
#define THERMO5_REVISION                                                0xFF
/** \} */

/**
 * \defgroup conversion_rates conversion Rates
 * \{
 */
#define THERMO5_CONVER_RATE_0_0625                                      0x00
#define THERMO5_CONVER_RATE_0_125                                       0x01
#define THERMO5_CONVER_RATE_0_25                                        0x02
#define THERMO5_CONVER_RATE_0_5                                         0x03
#define THERMO5_CONVER_RATE_1                                           0x04
#define THERMO5_CONVER_RATE_2                                           0x05
#define THERMO5_CONVER_RATE_4                                           0x06
#define THERMO5_CONVER_RATE_8                                           0x07
#define THERMO5_CONVER_RATE_16                                          0x08
#define THERMO5_CONVER_RATE_32                                          0x09
#define THERMO5_CONVER_RATE_64                                          0x0A
/** \} */

/**
 * \defgroup filter_decode Filter Decode
 * \{
 */
#define THERMO5_FILTER_DECODE_DISABLE                                   0x00
#define THERMO5_FILTER_DECODE_LEVEL_1                                   0x01
#define THERMO5_FILTER_DECODE_AVERAGE                                   0x02
#define THERMO5_FILTER_DECODE_LEVEL_2                                   0x03
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
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} thermo5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermo5_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void thermo5_cfg_setup ( thermo5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
THERMO5_RETVAL thermo5_init ( thermo5_t *ctx, thermo5_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void thermo5_generic_write ( thermo5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void thermo5_generic_read ( thermo5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write byte function.
 *
 * @param ctx          Click object.
 * @param wr_addr      8-bit register address.
 * @param wr_data      8-bit data to be written into register.
 *
 * @description This function writes single byte of data into specified register.
 */
void thermo5_write_byte ( thermo5_t *ctx, uint8_t wr_addr, uint8_t wr_data );

/**
 * @brief Read byte function.
 *
 * @param ctx          Click object.
 * @param rd_addr      8-bit register address.
 *
 * @description This function reads single byte of data from specified register.
 */
uint8_t thermo5_read_byte ( thermo5_t *ctx, uint8_t rd_addr );

/**
 * @brief Read data function.
 *
 * @param ctx          Click object.
 * @param reg_addr     16-bit register address.
 *
 * @description This function reads 2 bytes of data from specified, raad only register.
 */
uint16_t thermo5_read_data ( thermo5_t *ctx, uint16_t reg_addr );

/**
 * @brief Read internal diode temperature function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads measurements made by internal diode.
 */
float thermo5_read_inter_temp ( thermo5_t *ctx );

/**
 * @brief Read external diode 1 temperature function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads measurements made by external 1 diode.
 */
float thermo5_read_extern_1_temp ( thermo5_t *ctx );

/**
 * @brief Read external diode 2 temperature function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads measurements made by external 2 diode.
 */
float thermo5_read_extern_2_temp ( thermo5_t *ctx );

/**
 * @brief Read external diode 3 temperature function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads measurements made by external 3 diode.
 */
float thermo5_read_extern_3_temp ( thermo5_t *ctx );

/**
 * @brief Read product ID function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads device specific ID number.
 */
uint8_t thermo5_read_product_id ( thermo5_t *ctx );

/**
 * @brief Read manufacturer ID function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads manufacturer's ID number.
 */
uint8_t thermo5_read_manufacturer_id ( thermo5_t *ctx );

/**
 * @brief Read revision register function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads register that contains an 8-bit word that identifies the die revision.
 */
uint8_t thermo5_read_revision_register ( thermo5_t *ctx );

/**
 * @brief Get interrupt state function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads state of INT pin.
 */
uint8_t thermo5_get_interrupt_state ( thermo5_t *ctx );

/**
 * @brief Read status register function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads current state od the device from status registers.
 */
uint8_t thermo5_read_stat_reg ( thermo5_t *ctx );

/**
 * @brief Read therm limit status function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the Therm Limit Status register which utilises its
 *  lower nibble to represents which diodes have exceeded the therm limit.
 */
uint8_t thermo5_read_therm_limit_stat ( thermo5_t *ctx );

/**
 * @brief Read external diode fault function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the External Diode Fault Status register which utilises
 *  3 of its bits [B3 - B1] to represents which of the external diodes caused the fault bit.
 */
uint8_t thermo5_read_exter_diode_fault ( thermo5_t *ctx );

/**
 * @brief Read low limit status function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the Low Limit Status register which utilises its lower
 *  nibble to represents which diodes have droped below their programmed low limit.
 */
uint8_t thermo5_read_low_limit_stat ( thermo5_t *ctx );

/**
 * @brief Read high limit status function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the High Limit Status register which utilises its lower
 *  nibble to represents which diodes have exceed their programmed high limit.
 */
uint8_t thermo5_read_high_limit_stat ( thermo5_t *ctx );

/**
 * @brief Write configuration function.
 *
 * @param ctx          Click object.
 * @param wr_data      8-bit data that defines wandted configuration.
 *
 * @description This function writes 8-bit data into Configuration register.
 */
void thermo5_write_config ( thermo5_t *ctx, uint8_t wr_data );

/**
 * @brief Read configuration function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads 8-bit data from Configuration register.
 */
uint8_t thermo5_read_config ( thermo5_t *ctx );

/**
 * @brief Set conversion rate function.
 *
 * @param ctx             Click object.
 * @param convers_rate    4-bit value that defines rate of conversion.
 *
 * @description This function sets the conversion rate.
 */
void thermo5_set_convers_rate ( thermo5_t *ctx, uint8_t convers_rate );

/**
 * @brief Read conversion rate function.
 *
 * @param ctx   Click object.
 *
 * @description This function reads data from conversion rate register.
 */
uint8_t thermo5_read_convers_rate ( thermo5_t *ctx );

/**
 * @brief Filter configuration function.
 *
 * @param ctx                   Click object.
 * @param filter_decode_rate    Data that defines the level of digital filtering.
 *
 * @description This function controls the digital filter on the external diode 1 channel.
 */
void thermo5_set_filter_rate ( thermo5_t *ctx, uint8_t filter_decode_rate );

/**
 * @brief Read filter configuration function.
 *
 * @param ctx   Click object.
 *
 * @description This function reads data from filter configuration register.
 */
uint8_t thermo5_read_filter_rate ( thermo5_t *ctx );

/**
 * @brief Set External Diode 1 Beta Configuration function.
 *
 * @param ctx       Click object.
 * @param enable    Data that defines the level of digital filtering.
 *
 * @description This function allows user to enable or disable beta compensation factor for external diode 1.
 */
void thermo5_set_diode_1_beta_config ( thermo5_t *ctx, uint8_t enable );

/**
 * @brief Read External Diode 1 Beta Configuration function.
 *
 * @param ctx   Click object.
 *
 * @description This function reads current beta configuration settings for external diode 1.
 */
uint8_t thermo5_read_diode_1_beta_config ( thermo5_t *ctx );

/**
 * @brief Set External Diode 2 Beta Configuration function.
 *
 * @param ctx       Click object.
 * @param enable    Data that defines the level of digital filtering.
 *
 * @description This function allows user to enable or disable beta compensation factor for external diode 2.
 */
void thermo5_set_diode_2_beta_config ( thermo5_t *ctx, uint8_t enable );

/**
 * @brief Read External Diode 2 Beta Configuration function.
 *
 * @param ctx   Click object.
 *
 * @description This function reads current beta configuration settings for external diode 2.
 */
uint8_t thermo5_read_diode_2_beta_config ( thermo5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO5_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

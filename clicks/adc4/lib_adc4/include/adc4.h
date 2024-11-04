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
 * \brief This file contains API for ADC 4 Click driver.
 *
 * \addtogroup adc4 ADC 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADC4_H
#define ADC4_H

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

#define ADC4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.err   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADC4_RETVAL  uint8_t

#define ADC4_OK           0x00
#define ADC4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reselution Resolution
 * \{
 */
#define ADC4_RESOLUTION            8388607
/** \} */

/**
 * \defgroup vref  Vref
 * \{
 */
#define ADC4_VREF_4000MV            4.096
#define ADC4_VREF_2500MV              2.5
/** \} */

/**
 * \defgroup register  Register
 * \{
 */
#define ADC4_STATUS_REG               0x00
#define ADC4_MODE_REG                 0x01
#define ADC4_IFACE_MODE_REG           0x02
#define ADC4_CHECK_REG                0x03
#define ADC4_DATA_REG                 0x04
#define ADC4_GPIO_CONFIG_REG          0x06
#define ADC4_ID_REG                   0x07
#define ADC4_SETUP_CONFIGURATION_REG  0x20
/** \} */

/**
 * \defgroup reg_base  Reg base
 * \{
 */
#define ADC4_CH_REG_BASE            0x10
#define ADC4_CON_REG_BASE           0x20
#define ADC4_FILCON_REG_BASE        0x28
#define ADC4_OFFSET_REG_BASE        0x30
#define ADC4_GAIN_REG_BASE          0x38
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define ADC4_STATUS_RDY             0x80
#define ADC4_STATUS_ERR             0x40
#define ADC4_STATUS_CRC_ERR         0x20
#define ADC4_STATUS_REG_ERR         0x10
#define ADC4_STATUS_CH_ACTIVE       0x0F
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define ADC4_MODE_INT_REF_AND_SING_CYC_EN      0xA000
#define ADC4_MODE_INT_REF_EN                   0x8000
#define ADC4_MODE_HIDE_RELAY_DIS               0x4000
#define ADC4_MODE_SING_CYC_EN                  0x2000
#define ADC4_MODE_DELAY_0                      0x0000
#define ADC4_MODE_DELAY_4                      0x0100
#define ADC4_MODE_DELAY_16                     0x0200
#define ADC4_MODE_DELAY_40                     0x0300
#define ADC4_MODE_DELAY_100                    0x0400
#define ADC4_MODE_DELAY_200                    0x0500
#define ADC4_MODE_DELAY_500                    0x0600
#define ADC4_MODE_DELAY_1000                   0x0700
#define ADC4_MODE_CONTINUOUS                   0x0000
#define ADC4_MODE_SINGLE                       0x0010
#define ADC4_MODE_STBY                         0x0020
#define ADC4_MODE_POWER_DOWN                   0x0030
#define ADC4_MODE_INTERNAL_OFFSET              0x0040
#define ADC4_MODE_SYSTEM_OFFSET                0x0060
#define ADC4_MODE_GAIN_OFFSET                  0x0070
#define ADC4_MODE_CLK_INTOSC                   0x0000
#define ADC4_MODE_CLK_INTOSC_XT2               0x0002
#define ADC4_MODE_CLK_EXTOSC_XT2               0x0004
#define ADC4_MODE_CLK_EXTOSC                   0x0006
/** \} */

/**
 * \defgroup iface_mode  Iface mode
 * \{
 */
#define ADC4_IFACE_MODE_ALTSYNC_EN  0x1000
#define ADC4_IFACE_MODE_IOSTREN_EN  0x0800
#define ADC4_IFACE_MODE_DOUTRES_EN  0x0100
#define ADC4_IFACE_MODE_CONTRD_EN   0x0080
#define ADC4_IFACE_MODE_DATASTA_EN  0x0040
#define ADC4_IFACE_MODE_REGCHK_EN   0x0020
#define ADC4_IFACE_MODE_CRC_DIS     0x0000
#define ADC4_IFACE_MODE_CRC_RD_EN   0x0002
#define ADC4_IFACE_MODE_CRC_RW_EN   0x0004
/** \} */
 
/**
 * \defgroup config  Config
 * \{
 */
#define ADC4_CFG_PDSW               0x4000
#define ADC4_CFG_OP_EN2_3           0x2000
#define ADC4_CFG_MUX_IO             0x1000
#define ADC4_CFG_SYNC_EN            0x0800
#define ADC4_CFG_ERR_DISABLE        0x0000
#define ADC4_CFG_ERR_INPUT          0x0400
#define ADC4_CFG_ERR_OPENDRAIN      0x0200
#define ADC4_CFG_ERR_OUTPUT         0x0600
#define ADC4_CFG_ERR_DAT            0x0010
/** \} */
 
/**
 * \defgroup ch_reg  Ch reg
 * \{
 */
#define ADC4_CH_EN                   0x8000
#define ADC4_CH_SETUP_0              0x0001 << 12
#define ADC4_CH_SETUP_1              0x0002 << 12
#define ADC4_CH_SETUP_2              0x0003 << 12
#define ADC4_CH_SETUP_3              0x0004 << 12
#define ADC4_CH_SETUP_4              0x0005 << 12
#define ADC4_CH_SETUP_5              0x0006 << 12
#define ADC4_CH_SETUP_6              0x0007 << 12
#define ADC4_CH_SETUP_7              0x0008 << 12
#define ADC4_CH_AINPOS_0             0x0000 << 5      
#define ADC4_CH_AINPOS_1             0x0001 << 5      
#define ADC4_CH_AINPOS_2             0x0002 << 5      
#define ADC4_CH_AINPOS_3             0x0003 << 5      
#define ADC4_CH_AINPOS_4             0x0004 << 5      
#define ADC4_CH_AINPOS_5             0x0005 << 5      
#define ADC4_CH_AINPOS_6             0x0006 << 5      
#define ADC4_CH_AINPOS_7             0x0007 << 5
#define ADC4_CH_AINPOS_8             0x0008 << 5   
#define ADC4_CH_AINPOS_9             0x0009 << 5   
#define ADC4_CH_AINPOS_10            0x000A << 5    
#define ADC4_CH_AINPOS_11            0x000B << 5    
#define ADC4_CH_AINPOS_12            0x000C << 5    
#define ADC4_CH_AINPOS_13            0x000D << 5    
#define ADC4_CH_AINPOS_14            0x000E << 5    
#define ADC4_CH_AINPOS_15            0x000F << 5    
#define ADC4_CH_AINPOS_16            0x0010 << 5
#define ADC4_CH_AINPOS_TEMP_P        0x0011 << 5
#define ADC4_CH_AINPOS_TEMP_N        0x0012 << 5
#define ADC4_CH_AINPOS_AV_P          0x0013 << 5
#define ADC4_CH_AINPOS_AV_N          0x0014 << 5
#define ADC4_CH_AINPOS_REF_P         0x0015 << 5
#define ADC4_CH_AINPOS_REF_N         0x0016 << 5
#define ADC4_CH_AINNEG_0             0x0000
#define ADC4_CH_AINNEG_1             0x0001
#define ADC4_CH_AINNEG_2             0x0002
#define ADC4_CH_AINNEG_3             0x0003
#define ADC4_CH_AINNEG_4             0x0004
#define ADC4_CH_AINNEG_5             0x0005
#define ADC4_CH_AINNEG_6             0x0006
#define ADC4_CH_AINNEG_7             0x0007
#define ADC4_CH_AINNEG_8             0x0008
#define ADC4_CH_AINNEG_9             0x0009
#define ADC4_CH_AINNEG_10            0x000A
#define ADC4_CH_AINNEG_11            0x000B
#define ADC4_CH_AINNEG_12            0x000C
#define ADC4_CH_AINNEG_13            0x000D
#define ADC4_CH_AINNEG_14            0x000E
#define ADC4_CH_AINNEG_15            0x000F
#define ADC4_CH_AINNEG_16            0x0010
#define ADC4_CH_AINNEG_TEMP_P        0x0011
#define ADC4_CH_AINNEG_TEMP_N        0x0012
#define ADC4_CH_AINNEG_AV_P          0x0013
#define ADC4_CH_AINNEG_AV_N          0x0014
#define ADC4_CH_AINNEG_REF_P         0x0015
#define ADC4_CH_AINNEG_REF_N         0x0016
/** \} */
 
/**
 * \defgroup con  Con
 * \{
 */
#define ADC4_CON_UNIPOL              0x0000
#define ADC4_CON_BIPOL               0x0001 << 12
#define ADC4_CON_REFBUF_P_EN         0x0001 << 11
#define ADC4_CON_REFBUF_N_EN         0x0001 << 10
#define ADC4_CON_AINBUF_P_EN         0x0001 << 9
#define ADC4_CON_AINBUF_N_EN         0x0001 << 8
#define ADC4_CON_BURNOUT_EN          0x0001 << 7
#define ADC4_CON_EXTREF              0x0000
#define ADC4_CON_EXTREF_SUPP         0x0001 << 4
#define ADC4_CON_EXTREF_INT          0x0002 << 4
#define ADC4_CON_EXTREF_AV           0x0003 << 4
/** \} */
 
/**
 * \defgroup filter  Filter
 * \{
 */
#define ADC4_FILCON_SINC_MAP0         0x8000 
#define ADC4_FILCON_ENHFILEN          0x0001 << 11
#define ADC4_FILCON_ENHFIL_SET1       0x0002 << 8
#define ADC4_FILCON_EHFFIL_SET2       0x0003 << 8
#define ADC4_FILCON_ENHFIL_SET3       0x0005 << 8
#define ADC4_FILCON_ENHFIL_SET4       0x0006 << 8
#define ADC4_FILCON_ORD_SINC5         0x0000
#define ADC4_FILCON_ORD_SINC3         0x0003 << 5
#define ADC4_FILCON_ODR_250000        0x0000 
#define ADC4_FILCON_ODR_125000        0x0001 
#define ADC4_FILCON_ODR_62500         0x0002 
#define ADC4_FILCON_ODR_50000         0x0003 
#define ADC4_FILCON_ODR_31250         0x0004 
#define ADC4_FILCON_ODR_25000         0x0005 
#define ADC4_FILCON_ODR_15625         0x0006 
#define ADC4_FILCON_ODR_10000         0x0007 
#define ADC4_FILCON_ODR_5000          0x0008 
#define ADC4_FILCON_ODR_2500          0x0009 
#define ADC4_FILCON_ODR_1000          0x000A 
#define ADC4_FILCON_ODR_500           0x000B 
#define ADC4_FILCON_ODR_397_5         0x000C 
#define ADC4_FILCON_ODR_200           0x000D 
#define ADC4_FILCON_ODR_100           0x000E 
#define ADC4_FILCON_ODR_59_92         0x000F 
#define ADC4_FILCON_ODR_49_96         0x0010 
#define ADC4_FILCON_ODR_20            0x0011 
#define ADC4_FILCON_ODR_16_66         0x0012 
#define ADC4_FILCON_ODR_10            0x0013 
#define ADC4_FILCON_ODR_5             0x0014
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
    digital_out_t cs;

    // Input pins 

    digital_in_t err;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    uint16_t w_dog;
    uint8_t sing_bit;

} adc4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t err;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} adc4_cfg_t;

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
void adc4_cfg_setup ( adc4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx        Click object.
 * @param cfg        Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
ADC4_RETVAL adc4_init ( adc4_t *ctx, adc4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for ADC 4 Click.
 */
void adc4_default_cfg ( adc4_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @note
 * <pre>
 *      Set: ADC4_CH_REG_BASE
 *              - ADC4_CH_EN
 *      Set: ADC4_MODE_REG
 *              - ADC4_MODE_INT_REF_AND_SING_CYC_EN
 *      Set: ADC4_IFACE_MODE_REG
 *              - ADC4_IFACE_MODE_CRC_DIS
 *      Set: ADC4_GPIO_CONFIG_REG
 *              - ADC4_CFG_SYNC_EN
 *      Set: ADC4_SETUP_CONFIGURATION_REG
 *              - 0x1320
 * </pre>
 * @description Generic SPI transfer, for sending and receiving packages
 */
void adc4_generic_transfer ( adc4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic Write Function
 *
 * @param ctx               Click object.
 * @param reg_sddress       register address
 * @param value             pointer to input data
 *
 * @return n_bytes - number of bytes to be written
 *
 * @description Function writes data in register determined by register address parametar of function.
 */
uint8_t adc4_write_reg ( adc4_t *ctx, const uint8_t reg_address, uint8_t *value );

/**
 * @brief Generic Write Function
 *
 * @param ctx              Click object.
 * @param reg_address      register address
 * @param value            pointer when output data will be storaged
 *
 * @return n_bytes - number of bytes to be read
 *
 * @description Function reads data from register determined by register address parametar of function.
 */
uint8_t adc4_read_reg ( adc4_t *ctx, const uint8_t reg_address, uint8_t *value );

/**
 * @brief Reset function
 *
 * @param ctx          Click object.
 * 
 * @description This function reset ADC 4 Click.
 */
void adc4_reset ( adc4_t *ctx );

/**
 * @brief Error check function
 *
 * @param ctx          Click object.
 * 
 * @return state of INT pin
 *
 * @description This function returns value of INT (ERROR) pin witch is controlled by ERR_DAT bit in the GPIOCON register.
 */
uint8_t adc4_get_err_pin ( adc4_t *ctx );

/**
 * @brief Get configuration function
 *
 * @param ctx                Click object.
 * @param reg_address        register address
 * @param value              pointer when output data will be storaged
 *
 * @description This function writes value of configuration registers in storage determined by pointer value.
 */
void adc4_get_config ( adc4_t *ctx, uint8_t reg_address, uint16_t *value );

/**
 * @brief Set configuration function
 *
 * @param ctx               Click object.
 * @param reg_address       register address
 * @param value             16-bit value to be written
 *
 * @description This function writes 16-bit value in configuration registers determined by register address parametar.
 */
void adc4_set_config ( adc4_t *ctx, const uint8_t reg_address, uint16_t value );

/**
 * @brief Get data function
 *
 * @param ctx          Click object.
 * 
 * @return 24-bit data from register
 *
 * @description This function checks ready bit, is data ready or not, and returns 24-bit value from data register.
 */
uint32_t adc4_get_data ( adc4_t *ctx );

/**
 * @brief Get voltage function
 *
 * @param ctx              Click object.
 * @param ref_voltage      Referent voltage for ADC conversion
 *
 * @return calculated 16-bit ADC voltage value
 *
 * @description This function returns 16-bit calculated and AD converted voltage value.
 */
uint16_t adc4_get_voltage ( adc4_t *ctx, const float ref_voltage );

#ifdef __cplusplus
}
#endif
#endif  // _ADC4_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

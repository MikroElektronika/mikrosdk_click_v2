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
 * \brief This file contains API for LPS22HB Click driver.
 *
 * \addtogroup lps22hb LPS22HB Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LPS22HB_H
#define LPS22HB_H

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

#define LPS22HB_MAP_MIKROBUS( cfg, mikrobus )          \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup communication Select Communication
 * \{
 */
#define LPS22HB_MASTER_I2C                          0
#define LPS22HB_MASTER_SPI                          1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LPS22HB_RETVAL  uint8_t

#define LPS22HB_OK                                  0x00
#define LPS22HB_INIT_ERROR                          0xFF
/** \} */

/**
 * \defgroup dev_res Device Resolution
 * \{
 */
#define LPS22HB_DEV_RES_PRES                        4096.0
#define LPS22HB_DEV_RES_TEMP                        100.0
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define LPS22HB_I2C_ADDRESS_0                       0x5C
#define LPS22HB_I2C_ADDRESS_1                       0x5D
/** \} */

/**
 * \defgroup reg Register Address
 * \{
 */
#define LPS22HB_REG_INTERRUPT_CFG                   0x0B
#define LPS22HB_REG_THS_P_L                         0x0C
#define LPS22HB_REG_THS_P_H                         0x0D
#define LPS22HB_REG_WHO_AM_I                        0x0F

#define LPS22HB_REG_REF_P_XL                        0x15
#define LPS22HB_REG_REF_P_L                         0x16
#define LPS22HB_REG_REF_P_H                         0x17
#define LPS22HB_REG_RPDS_L                          0x18
#define LPS22HB_REG_RPDS_H                          0x19
#define LPS22HB_REG_RES_CONF                        0x1A
#define LPS22HB_REG_INT_SOURCE                      0x25
#define LPS22HB_REG_FIFO_STATUS                     0x26
#define LPS22HB_REG_STATUS                          0x27
#define LPS22HB_REG_PRESS_OUT_XL                    0x28
#define LPS22HB_REG_PRESS_OUT_L                     0x29
#define LPS22HB_REG_PRESS_OUT_H                     0x2A
#define LPS22HB_REG_TEMP_OUT_L                      0x2B
#define LPS22HB_REG_TEMP_OUT_H                      0x2C
#define LPS22HB_REG_CLOCK_TREE_CONFIGURATION        0x43
/** \} */

/**
 * \defgroup res_conf Low-power Mode Configuration
 * \{
 */
#define LPS22HB_RES_CONF_NORMAL_MODE                0x00
#define LPS22HB_RES_CONF_LOW_CURRENT_MODE           0x01
/** \} */

/**
 * \defgroup ctrl_reg Control Registers
 * \{
 */
#define LPS22HB_CTRL_REG_R1                         0x10
#define LPS22HB_CTRL_REG_R2                         0x11
#define LPS22HB_CTRL_REG_R3                         0x12
#define LPS22HB_CTRL_REG_FIFO                       0x14

#define LPS22HB_CTRL_I2C                            0x10
#define LPS22HB_CTRL_SPI                            0x18
/** \} */

/**
 * \defgroup mask Mask Bit
 * \{
 */
#define LPS22HB_MASK_DATA                           0x80
#define LPS22HB_MASK_DATA_RESET                     0x02
#define LPS22HB_MASK_DATA_ODR                       0x30

#define LPS22HB_MASK_REG1_ODR                       0x70
#define LPS22HB_MASK_REG1_LPFP                      0x08
#define LPS22HB_MASK_REG1_LPFP_CUTOFF               0x04
#define LPS22HB_MASK_REG1_BDU                       0x02
#define LPS22HB_MASK_REG1_SIM                       0x01
                                                    
#define LPS22HB_MASK_REG2_FIFO_EN                   0x40
#define LPS22HB_MASK_REG2_WTM_EN                    0x20
#define LPS22HB_MASK_REG2_ADD_INC                   0x10
#define LPS22HB_MASK_REG2_I2C                       0x08
#define LPS22HB_MASK_REG2_ONE_SHOT                  0x01
                                                    
#define LPS22HB_MASK_REG3_INT_H_L                   0x80
#define LPS22HB_MASK_REG3_PP_OD                     0x40
#define LPS22HB_MASK_REG3_FIFO_FULL                 0x20
#define LPS22HB_MASK_REG3_FIFO_FTH                  0x10
#define LPS22HB_MASK_REG3_FIFO_OVR                  0x08
#define LPS22HB_MASK_REG3_DRDY                      0x04
#define LPS22HB_MASK_REG3_INT_S12                   0x03
/** \} */

/**
 * \defgroup int_mask Mask Bit
 * \{
 */
#define LPS22HB_INT_MASK_CFG_AUTORIFP               0x80
#define LPS22HB_INT_MASK_CFG_RESET_ARP              0x40
#define LPS22HB_INT_MASK_CFG_AUTOZERO               0x20
#define LPS22HB_INT_MASK_CFG_RESET_AZ               0x10
#define LPS22HB_INT_MASK_CFG_DIFF_EN                0x08
#define LPS22HB_INT_MASK_CFG_LIR                    0x04
#define LPS22HB_INT_MASK_CFG_PLE                    0x02
#define LPS22HB_INT_MASK_CFG_PHE                    0x01
         
#define LPS22HB_INT_MASK_SOURCE_BOOT_STATUS         0x80
#define LPS22HB_INT_MASK_SOURCE_IA                  0x04
#define LPS22HB_INT_MASK_SOURCE_PL                  0x02
#define LPS22HB_INT_MASK_SOURCE_PH                  0x01
                  
#define LPS22HB_INT_MASK_SOURCE_TOR                 0x20
#define LPS22HB_INT_MASK_SOURCE_POR                 0x10
#define LPS22HB_INT_MASK_SOURCE_TDA                 0x02
#define LPS22HB_INT_MASK_SOURCE_PDA                 0x01
/** \} */

/**
 * \defgroup fifo_mask Mask Bit
 * \{
 */
#define LPS22HB_FIFO_MASK_CTRL_MODE                 0xE0
#define LPS22HB_FIFO_MASK_CTRL_WTM_POINT            0x1F
                    
#define LPS22HB_FIFO_MASK_STATUS_FTH                0x80
#define LPS22HB_FIFO_MASK_STATUS_OVR                0x40
#define LPS22HB_FIFO_MASK_STATUS_LEVEL              0x3F
#define LPS22HB_FIFO_STATUS_EMPTY                   0x00
#define LPS22HB_FIFO_STATUS_FULL                    0x20
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
typedef uint8_t  lps22hb_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *lps22hb_master_io_t )( struct lps22hb_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct lps22hb_s
{
    // Output pins 
   
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    lps22hb_master_io_t  write_f;
    lps22hb_master_io_t  read_f;
    lps22hb_select_t master_sel;

} lps22hb_t;

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

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   lps22hb_select_t sel;

} lps22hb_cfg_t;

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
 * @param cfg           Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void lps22hb_cfg_setup ( lps22hb_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx       Click object.
 * @param cfg           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LPS22HB_RETVAL lps22hb_init ( lps22hb_t *ctx, lps22hb_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function executes default configuration for LPS22HB click.
 */
void lps22hb_default_cfg ( lps22hb_t *ctx, lps22hb_cfg_t *cfg  );

/**
 * @brief Generic write function.
 *
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf      Output data buf
 * @param len           Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void lps22hb_generic_write ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf      Data buf to be written.
 * @param len           Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void lps22hb_generic_read ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Soft reset function.
 *
 * @param ctx           Click object.
 *
 * @description This function soft reset by write ( 0x02 )to the
 * target 8-bit register address ( 0x11 ) of the LPS22HB Click.
 */
void lps22hb_soft_reset ( lps22hb_t *ctx );

/**
 * @brief Set start configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function sets start configuration to the
 * target 8-bit register address of the LPS22HB Click.
 */
void lps22hb_start_configuration ( lps22hb_t *ctx );

/**
 * @brief Update register function
 *
 * @param ctx           Click object.
 * @param reg_adr       8-bit register address
 * @param reg_val       8-bit data to be written into register
 *
 * @description Function is used to apply new values.
**/
void lps22hb_update_reg ( lps22hb_t *ctx, uint8_t reg_adr, uint8_t reg_val );

/**
 * @brief Get pressure value function
 *
 * @param ctx           Click object.
 * 
 * @return 
 * ------------------------------------------
 * <pre>
 *     float pressure value [ mbar ]
 * </pre>
 * ------------------------------------------
 *
 * @description Function gets pressure data, calculates and returns pressure.
 */
float lps22hb_get_pressure ( lps22hb_t *ctx );

/**
 * @brief Get temperature value function
 *
 * @param ctx           Click object.
 * 
 * @return 
 * ------------------------------------------
 * <pre>
 *     float temperature value [ ºC ]
 * </pre>
 * ------------------------------------------
 *
 * @description Function gets temperature returns value in degrees Celsius.
 */
float lps22hb_get_temp ( lps22hb_t *ctx );

/**
 * @brief Set FIFO control mode function
 *
 * @param ctx           Click object.
 * @param mode_sel      8-bit FIFO mode selection
 * @param wm_lvl        8-bit FIFO watermark level
 *
 * @description Function set FIFO control mode.
 */
void lps22hb_set_fifo_mode ( lps22hb_t *ctx, uint8_t mode_sel, uint8_t wm_lvl );

/**
 * @brief Check Interrupt state function
 *
 * @param ctx           Click object.
 * 
 * @return 
 * ------------------------------------------
 * <pre>
 *     1 : Interrupt occured / 0 : Interrupt not occured
 * </pre>
 * ------------------------------------------
 *
 * @description Function is used to check if interrupt occured.
**/
uint8_t lps22hb_check_int ( lps22hb_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LPS22HB_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

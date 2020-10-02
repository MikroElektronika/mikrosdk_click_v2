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
 * \brief This file contains API for Pixi Click driver.
 *
 * \addtogroup pixi Pixi Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PIXI_H
#define PIXI_H

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

#define PIXI_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.cnv   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PIXI_RETVAL  uint8_t

#define PIXI_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup op_code Op Code
 * \{
 */
#define READ_OP  0
#define WRITE_OP 1

#define PIXI_ERR 1
#define PIXI_OK  0
/** \} */

/**
 * \defgroup ro_regs RO Regs
 * \{
 */
#define PIXI_REG_DEVICE_ID             0x00
#define PIXI_REG_INTERRUPT             0x01
#define PIXI_REG_ADC_DATA_STATUS       0x02
#define PIXI_REG_OVERCURRENT_STATUS    0x04
#define PIXI_REG_GPI_STATUS            0x06
#define PIXI_REG_INT_TEMP              0x08
#define PIXI_REG_EXT_TEMP_1            0x09
#define PIXI_REG_EXT_TEMP_2            0x0A
#define PIXI_REG_GPI_DATA              0x0B
#define PIXI_REG_ADC_DATA_BASE         0x40
/** \} */

/**
 * \defgroup rw_regs RW Regs
 * \{
 */
#define PIXI_REG_GPO_DATA                 0x0D
#define PIXI_REG_DEVICE_CONTROL           0x10
#define PIXI_REG_INTERRUPT_MASK           0x11
#define PIXI_REG_GPI_IRQMODE              0x12
#define PIXI_REG_DAC_PRESET_1             0x16
#define PIXI_REG_DAC_PRESET_2             0x17
#define PIXI_REG_TEMP_MONITOR_CONFIG      0x18
#define PIXI_REG_TEMP_IN_THRES_HIGH       0x19
#define PIXI_REG_TEMP_IN_THRES_LOW        0x1A
#define PIXI_REG_TEMP_EXT_1_THRES_HIGH    0x1B
#define PIXI_REG_TEMP_EXT_1_THRES_LOW     0x1C
#define PIXI_REG_TEMP_EXT_2_THRES_HIGH    0x1D
#define PIXI_REG_TEMP_EXT_2_THRES_LOW     0x1E
#define PIXI_REG_PORT_CONFIG_BASE         0x20
#define PIXI_REG_DAC_DATA_BASE            0x60
/** \} */

/**
 * \defgroup device_control_reg Device Control Reg
 * \{
 */
#define PIXI_CTL_ADCCTL_IDLE           0x0000
#define PIXI_CTL_ADCCTL_SINGLESWEEP    0x0001
#define PIXI_CTL_ADCCTL_SINGLECONV     0x0002
#define PIXI_CTL_ADCCTL_CONTSWEEP      0x0003
#define PIXI_CTL_DACCTL_SEQUPDATE      0x0000
#define PIXI_CTL_DACCTL_IMMUPDATE      0x0001 << 2
#define PIXI_CTL_DACCTL_USEPRST_1      0x0002 << 2
#define PIXI_CTL_DACCTL_USEPRST_2      0x0003 << 2
#define PIXI_CTL_ADCCONV_200KSPS       0x0000
#define PIXI_CTL_ADCCONV_250KSPS       0x0001 << 4
#define PIXI_CTL_ADCCONV_333KSPS       0x0002 << 4
#define PIXI_CTL_ADCCONV_400KSPS       0x0003 << 4
#define PIXI_CTL_DACREF_INTREF         0x0001 << 6
#define PIXI_CTL_THSHDN_ENABLE         0x0001 << 7
#define PIXI_CTL_TMPCTL_INT            0x0001 << 8
#define PIXI_CTL_TMPCTL_EXT_1          0x0002 << 8
#define PIXI_CTL_TMPCTL_EXT_2          0x0004 << 8
#define PIXI_CTL_TMPPER_EXTENDED       0x0001 << 11
#define PIXI_CTL_RS_CANCEL_ENABLE      0x0001 << 12
#define PIXI_CTL_LPEN_LOWPOWER         0x0001 << 13
#define PIXI_CTL_BRST_CONTEX_INC       0x0001 << 14
#define PIXI_CTL_RESET                 0x0001 << 15
/** \} */

/**
 * \defgroup interrupt_mask_reg Interrupt Mask Reg
 * \{
 */
#define PIXI_IMASK_ADCFLAG    0x0001
#define PIXI_IMASK_ADCDR      0x0002
#define PIXI_IMASK_ADCDM      0x0004
#define PIXI_IMASK_GPIDR      0x0008
#define PIXI_IMASK_GPIDM      0x0010
#define PIXI_IMASK_DACOI      0x0020
#define PIXI_IMASK_TMPINT     6
#define PIXI_IMASK_TMPEXT1    9
#define PIXI_IMASK_TMPEXT2    12
#define PIXI_IMASK_VMON       0x8000
/** \} */

/**
 * \defgroup temp_monitor_config Temp Monitor Config
 * \{
 */
#define PIXI_TMPMON_INT_4_SMP            0x0000
#define PIXI_TMPMOD_INT_8_SMP            0x0001
#define PIXI_TMPMON_INT_16_SMP           0x0002
#define PIXI_TMPMON_INT_32_SMP           0x0003
#define PIXI_TMPMON_EXT1_4_SMP           0x0000
#define PIXI_TMPMOD_EXT1_8_SMP           0x0001 << 2
#define PIXI_TMPMON_EXT1_16_SMP          0x0002 << 2
#define PIXI_TMPMON_EXT1_32_SMP          0x0003 << 2
#define PIXI_TMPMON_EXT2_4_SMP           0x0000
#define PIXI_TMPMOD_EXT2_8_SMP           0x0001 << 4
#define PIXI_TMPMON_EXT2_16_SMP          0x0002 << 4
#define PIXI_TMPMON_EXT2_32_SMP          0x0003 << 4
#define PIXI_PORT_CFG_CFG_ASSOCIATED     0
#define PIXI_PORT_CFG_CFG_SAMPLES_1      0x0000 << 5
#define PIXI_PORT_CFG_CFG_SAMPLES_2      0x0001 << 5
#define PIXI_PORT_CFG_CFG_SAMPLES_4      0x0002 << 5
#define PIXI_PORT_CFG_CFG_SAMPLES_8      0x0003 << 5
#define PIXI_PORT_CFG_CFG_SAMPLES_16     0x0004 << 5
#define PIXI_PORT_CFG_CFG_SAMPLES_32     0x0005 << 5
#define PIXI_PORT_CFG_CFG_SAMPLES_64     0x0006 << 5
#define PIXI_PORT_CFG_CFG_SAMPLES_128    0x0007 << 5
#define PIXI_PORT_CFG_CFG_RANGE_N        0x0000 << 8
#define PIXI_PORT_CFG_CFG_RANGE_1        0x0001 << 8
#define PIXI_PORT_CFG_CFG_RANGE_2        0x0002 << 8
#define PIXI_PORT_CFG_CFG_RANGE_3        0x0003 << 8
#define PIXI_PORT_CFG_CFG_RANGE_4        0x0004 << 8
#define PIXI_PORT_CFG_CFG_RANGE_5        0x0005 << 8
#define PIXI_PORT_CFG_CFG_RANGE_6        0x0006 << 8
#define PIXI_PORT_CFG_CFG_RANGE_7        0x0007 << 8
#define PIXI_PORT_CFG_MODE_0             0x0000 << 12
#define PIXI_PORT_CFG_MODE_1             0x0001 << 12
#define PIXI_PORT_CFG_MODE_2             0x0002 << 12
#define PIXI_PORT_CFG_MODE_3             0x0003 << 12
#define PIXI_PORT_CFG_MODE_4             0x0004 << 12
#define PIXI_PORT_CFG_MODE_5             0x0005 << 12
#define PIXI_PORT_CFG_MODE_6             0x0006 << 12
#define PIXI_PORT_CFG_MODE_7             0x0007 << 12
#define PIXI_PORT_CFG_MODE_8             0x0008 << 12
#define PIXI_PORT_CFG_MODE_9             0x0009 << 12
#define PIXI_PORT_CFG_MODE_10            0x000A << 12
#define PIXI_PORT_CFG_MODE_11            0x000B << 12
#define PIXI_PORT_CFG_MODE_12            0x000C << 12
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

    digital_out_t cnv;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} pixi_t;

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

    pin_name_t cnv;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} pixi_cfg_t;

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
void pixi_cfg_setup ( pixi_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pixi Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PIXI_RETVAL pixi_init ( pixi_t *ctx, pixi_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pixi click.
 */
void pixi_default_cfg ( pixi_t *ctx );

/**
 * @brief Write register function.
 *
 * @param ctx        Click object.
 * @param reg_addr   Register address.
 * @param reg_data   Write data.
 *
 * @description This function writes data to the click module.
 */
uint8_t pixi_write_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t reg_data );

/**
 * @brief Read register function.
 *
 * @param ctx        Click object.
 * @param reg_addr   Register address.
 * @param reg_data   Read buffer.
 *
 * @description This function reads data from the click module.
 */
uint8_t pixi_read_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t *reg_data );

#ifdef __cplusplus
}
#endif
#endif  // _PIXI_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for Balancer 5 Click driver.
 *
 * \addtogroup balancer5 Balancer 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BALANCER5_H
#define BALANCER5_H

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
#define BALANCER5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pg = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.pss = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cd = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BALANCER5_RETVAL  uint8_t

#define BALANCER5_OK           0x00
#define BALANCER5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define BALANCER5_REG_CELL_V_LIMIT                         0x00
#define BALANCER5_REG_CHARGE_CURR_LIMIT                    0x01
#define BALANCER5_REG_INPUT_V_LIMIT                        0x02
#define BALANCER5_REG_INPUT_CURR_LIMIT                     0x03
#define BALANCER5_REG_PRECHARGE_N_TERMINATION_CTRL         0x04
#define BALANCER5_REG_CHARGER_CTRL_1                       0x05
#define BALANCER5_REG_CHARGER_CTRL_2                       0x06
#define BALANCER5_REG_CHARGER_CTRL_3                       0x07
#define BALANCER5_REG_CHARGER_CTRL_4                       0x08
#define BALANCER5_REG_ICO_CURR_LIMIT                       0x0A
#define BALANCER5_REG_CHARGER_STATUS_1                     0x0B
#define BALANCER5_REG_CHARGER_STATUS_2                     0x0C
#define BALANCER5_REG_NTC_STATUS                           0x0D
#define BALANCER5_REG_FAULT_STATUS                         0x0E
#define BALANCER5_REG_CHARGER_FLAG_1                       0x0F
#define BALANCER5_REG_CHARGER_FLAG_2                       0x10
#define BALANCER5_REG_FAULT_FLAG                           0x11
#define BALANCER5_REG_CHARGER_MASK_1                       0x12
#define BALANCER5_REG_CHARGER_MASK_2                       0x13
#define BALANCER5_REG_FAULT_MASK                           0x14
#define BALANCER5_REG_ADC_CTRL                             0x15
#define BALANCER5_REG_ADC_FUNCTION_DISABLE                 0x16
#define BALANCER5_REG_IBUS_ADC1                            0x17
#define BALANCER5_REG_IBUS_ADC0                            0x18
#define BALANCER5_REG_ICHG_ADC1                            0x19
#define BALANCER5_REG_ICHG_ADC0                            0x1A
#define BALANCER5_REG_VBUS_ADC1                            0x1B
#define BALANCER5_REG_VBUS_ADC0                            0x1C
#define BALANCER5_REG_VBAT_ADC1                            0x1D
#define BALANCER5_REG_VBAT_ADC0                            0x1E
#define BALANCER5_REG_VCELLTOP_ADC1                        0x1F
#define BALANCER5_REG_VCELLTOP_ADC0                        0x20
#define BALANCER5_REG_TS_ADC1                              0x21
#define BALANCER5_REG_TS_ADC0                              0x22
#define BALANCER5_REG_TDIE_ADC1                            0x23
#define BALANCER5_REG_TDIE_ADC0                            0x24
#define BALANCER5_REG_PART_INFO                            0x25
#define BALANCER5_REG_VCELLBOT_ADC1                        0x26
#define BALANCER5_REG_VCELLBOT_ADC0                        0x27
#define BALANCER5_REG_CELL_BALANCING_CTRL1                 0x28
#define BALANCER5_REG_CELL_BALANCING_CTRL2                 0x29
#define BALANCER5_REG_CELL_BALANCING_STATUS_N_CNTRL        0x2A
#define BALANCER5_REG_CELL_BALANCING_FLAG                  0x2B
#define BALANCER5_REG_CELL_BALANCING_MASK                  0x2C
/** \} */

/**
 * \defgroup id_statuses Id Statuses
 * \{
 */
#define BALANCER5_ERROR_ID                                 0xAA
#define BALANCER5_SUCCESSFUL                               0xFF
 /** \} */

/**
 * \defgroup device_id Device Id
 * \{
 */
#define  BALANCER5_DEVICE_ID                                0x29
  /** \} */

/**
 * \defgroup pin_state Pin State
 */
#define  BALANCER5_PIN_STATUS_HIGH                          1  
#define  BALANCER5_PIN_STATUS_LOW                           0  
 /** \} */

 /**
 * \defgroup charge_status Charge Status
 */
#define  BALANCER5_CHARGE_OFF                               1   
#define  BALANCER5_CHARGE_ON                                0   
 /** \} */

 /**
 * \defgroup adc_control ADC Controls
 */
#define  BALANCER5_ADC_CTRL_ENABLE                          0x80
#define  BALANCER5_ADC_CTRL_DISABLE                         0x00
#define  BALANCER5_ADC_CTRL_CONT_CONV                       0x00
#define  BALANCER5_ADC_CTRL_ONE_SHOT_CONV                   0x40
#define  BALANCER5_ADC_CTRL_15BIT_RES                       0x00
#define  BALANCER5_ADC_CTRL_14BIT_RES                       0x10
#define  BALANCER5_ADC_CTRL_13BIT_RES                       0x20
#define  BALANCER5_ADC_CTRL_12BIT_RES                       0x30
 /** \} */

 /**
 * \defgroup charge_status_1 Charge Status 1
 */
#define  BALANCER5_CS1_IINDPM_NORMAL                        0x00
#define  BALANCER5_CS1_IINDPM_IN_REGULATION                 0x40
#define  BALANCER5_CS1_VINDPM_NORMAL                        0x00
#define  BALANCER5_CS1_VINDPM_IN_REGULATION                 0x20
#define  BALANCER5_CS1_IC_NORMAL                            0x00
#define  BALANCER5_CS1_IC_IN_THERMAL_REGULATION             0x10
#define  BALANCER5_CS1_WD_NORMAL                            0x00
#define  BALANCER5_CS1_WD_TIMER_EXPIRED                     0x08
#define  BALANCER5_CS1_NOT_CHARGING                         0x00
#define  BALANCER5_CS1_TRICKLE_CHARGE                       0x01
#define  BALANCER5_CS1_PRE_CHARGE                           0x02
#define  BALANCER5_CS1_FAST_CHARGE                          0x03
#define  BALANCER5_CS1_TAPER_CHARGE                         0x04
#define  BALANCER5_CS1_TOP_OFF_TIMER_CHARGE                 0x05
#define  BALANCER5_CS1_CHARGE_TERMINATION                   0x06
 /** \} */

 /**
 * \defgroup charge_status_2 Charge Status 2
 */
#define  BALANCER5_CS2_POWER_GOOD                           0x80
#define  BALANCER5_CS2_POWER_NOT_GOOD                       0x00
#define  BALANCER5_CS2_NO_INPUT                             0x00
#define  BALANCER5_CS2_USB_HOST_SDP                         0x10
#define  BALANCER5_CS2_USB_CDP                              0x20
#define  BALANCER5_CS2_ADAPTER                              0x30
#define  BALANCER5_CS2_POORSRC                              0x40
#define  BALANCER5_CS2_UNKNOWN_ADAPTER                      0x50
#define  BALANCER5_CS2_NON_STANDARD_ADAPTER                 0x60
#define  BALANCER5_CS2_ICO_DISABLED                         0x00
#define  BALANCER5_CS2_ICO_OPTIMIZATION_IN_PROGRESS         0x02
#define  BALANCER5_CS2_MAX_INPUT                            0x04
 /** \} */

 /**
 * \defgroup slave_addr Slave Address
 */
#define BALANCER5_SLAVE_ADDRESS                             0x6A
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

    digital_out_t cd;
   

    // Input pins 

    digital_in_t pg;
    digital_in_t pss;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} balancer5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t pg;
    pin_name_t pss;
    pin_name_t cd;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} balancer5_cfg_t;

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
void balancer5_cfg_setup ( balancer5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param balancer5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
BALANCER5_RETVAL balancer5_init ( balancer5_t *ctx, balancer5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Balancer5 Click.
 *
 * @note 
 * <pre> Default config in this implementation means "write BALANCER5_ADC_CTRL_ENABLE |
 * BALANCER5_ADC_CTRL_CONT_CONV | BALANCER5_ADC_CTRL_15BIT_RES value to BALANCER5_REG_ADC_CTRL
 * register address". </pre>
 */
void balancer5_default_cfg ( balancer5_t *ctx );

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
void balancer5_generic_write ( balancer5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void balancer5_generic_read ( balancer5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic function for reading one Byte data from registar
 * 
 * @param        ctx           Click object.
 * @param        reg_addr      Command Registar.
 * 
 * @returns  data read from reg_addr
 *
 * @description This function reads one byte from address reg_addr
 */
uint8_t balancer5_read_data( balancer5_t *ctx, uint8_t reg_addr );


/**
 * @brief Generic function for writing one Byte data to registar
 * 
 * @param        ctx             Click object.
 * @param        reg_addr        Command Registar.
 * @param        write_data      data to be written to reg_addr.
 *
 * @description This function writes one byte to address reg_addr.
 */
void balancer5_write_data ( balancer5_t *ctx, uint8_t reg_addr, uint8_t write_data );

/**
 * @brief Function for setting charging status
 * 
 * @param        ctx             Click object.
 * @param        state           State of charge status to be set.
 *
 * @description This function sets charging status.
 */
void balancer5_charge ( balancer5_t *ctx, uint8_t state );

/**
 * @brief Gets state of the int pin
 * 
 * @param   ctx       Click object.
 *
 * @returns           State of the pin.
 *
 * @description This function gets int pin status.
 */
uint8_t balancer5_get_int_status ( balancer5_t *ctx );

/**
 * @brief Gets state of the pg pin on an
 * 
 * @param   ctx       Click object.
 *
 * @returns           State of the pin.
 *
 * @description This function gets state of an pin i.e pg pin status.
 */
uint8_t balancer5_get_power_good_status ( balancer5_t *ctx );

/**
 * @brief Gets state of the psel pin on rst
 * 
 * @param   ctx        Click object.
 *
 * @returns State of the rst i.e pss pin.
 *
 * @description This function gets pss i.e rst pin status.
 */
uint8_t balancer5_get_power_source_status ( balancer5_t *ctx );

/**
 * @brief Checks if device ID is good
 * 
 * @param   ctx         Click object.
 *
 * @returns BALANCER5_ERROR_ID or BALANCER5_SUCCESSFUL.
 *
 * @description This function checks if device ID is good.
 */
uint8_t balancer5_check_id ( balancer5_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _BALANCER5_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

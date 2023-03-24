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
 * \brief This file contains API for Temp&Hum 12 Click driver.
 *
 * \addtogroup temphum12 Temp&Hum 12 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM12_H
#define TEMPHUM12_H

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
#define TEMPHUM12_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM12_RETVAL  uint8_t

#define TEMPHUM12_OK           0x00
#define TEMPHUM12_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define TEMPHUM12_REG_TEMPERATURE_LSB      0x00
#define TEMPHUM12_REG_TEMPERATURE_MSB      0x01
#define TEMPHUM12_REG_HUMIDITY_LSB         0x02
#define TEMPHUM12_REG_HUMIDITY_MSB         0x03
#define TEMPHUM12_REG_DRDY_INTERRUPT       0x04
#define TEMPHUM12_REG_TEMP_MAX             0x05
#define TEMPHUM12_REG_HUM_MAX              0x06
#define TEMPHUM12_REG_INT_ENABLE           0x07
#define TEMPHUM12_REG_TEMP_OFFSET          0x08
#define TEMPHUM12_REG_HUM_OFFSET           0x09
#define TEMPHUM12_REG_TEMP_THR_LSB         0x0A
#define TEMPHUM12_REG_TEMP_THR_MSB         0x0B
#define TEMPHUM12_REG_HUM_THR_LSB          0x0C
#define TEMPHUM12_REG_HUM_THR_MSB          0x0D
#define TEMPHUM12_REG_DRDY_INT_CONFIG      0x0E
#define TEMPHUM12_REG_CONFIGURATION        0x0F
#define TEMPHUM12_REG_MANUFACTURER_ID_LSB  0xFC
#define TEMPHUM12_REG_MANUFACTURER_ID_MSB  0xFD
#define TEMPHUM12_REG_DEVICE_ID_LSB        0xFE
#define TEMPHUM12_REG_DEVICE_ID_MSB        0xFF
/** \} */

/**
 * \defgroup register_for_read_data Register for read data
 * \{
 */
#define TEMPHUM12_REG_DATA_TEMPERATURE       0x00
#define TEMPHUM12_REG_DATA_HUMIDITY          0x02
#define TEMPHUM12_REG_DATA_TEMP_THR          0x0A
#define TEMPHUM12_REG_DATA_HUM_THR           0x0C
#define TEMPHUM12_REG_DATA_MANUFACTURER_ID   0xFC
#define TEMPHUM12_REG_DATA_DEVICE_ID         0xFE
/** \} */

/**
 * \defgroup interrupt_drdy_register  Interrupt DRDY register
 * \{
 */
#define TEMPHUM12_INT_STATUS_DRDY            0x80
#define TEMPHUM12_INT_STATUS_TEMP_THR_HIGH   0x40
#define TEMPHUM12_INT_STATUS_TEMP_THR_LOW    0x20
#define TEMPHUM12_INT_STATUS_HUM_THR_HIGH    0x10
#define TEMPHUM12_INT_STATUS_HUM_THR_LOW     0x08
/** \} */

/**
 * \defgroup interrupt_enable_register  Interrupt enable register
 * \{
 */
#define TEMPHUM12_INTE_DRDY_ENABLE        0x80
#define TEMPHUM12_INTE_DRDY_DISABLE       0x00
#define TEMPHUM12_INTE_TEMP_TH_ENABLE     0x40
#define TEMPHUM12_INTE_TEMP_TH_DISABLE    0x00
#define TEMPHUM12_INTE_TEMP_TL_ENABLE     0x20
#define TEMPHUM12_INTE_TEMP_TL_DISABLE    0x00
#define TEMPHUM12_INTE_HUM_TH_ENABLE      0x10
#define TEMPHUM12_INTE_HUM_TH_DISABLE     0x00
#define TEMPHUM12_INTE_HUM_TL_ENABLE      0x08
#define TEMPHUM12_INTE_HUM_TL_DISABLE     0x00
/** \} */

/**
 * \defgroup temperature_offset  Temperature offset
 * \{
 */
#define TEMPHUM12_TO_PLUS_0_16C     0x01
#define TEMPHUM12_TO_PLUS_0_32C     0x02
#define TEMPHUM12_TO_PLUS_0_64C     0x04
#define TEMPHUM12_TO_PLUS_1_28C     0x08
#define TEMPHUM12_TO_PLUS_2_58C     0x10
#define TEMPHUM12_TO_PLUS_5_16C     0x20
#define TEMPHUM12_TO_PLUS_10_32C    0x40
#define TEMPHUM12_TO_MINUS_20_62C   0x80
/** \} */

/**
 * \defgroup humidity_offset  Humidity offset
 * \{
 */
#define TEMPHUM12_RHO_PLUS_0_2RH    0x01
#define TEMPHUM12_RHO_PLUS_0_4RH    0x02
#define TEMPHUM12_RHO_PLUS_0_8RH    0x04
#define TEMPHUM12_RHO_PLUS_1_6RH    0x08
#define TEMPHUM12_RHO_PLUS_3_1RH    0x10
#define TEMPHUM12_RHO_PLUS_6_3RH    0x20
#define TEMPHUM12_RHO_PLUS_12_5RH   0x40
#define TEMPHUM12_RHO_MINUS_25RH    0x80
/** \} */

/**
 * \defgroup configuration_register COnfiguration register
 * \{
 */
#define TEMPHUM12_ICFG_NORAML_OPERATION  0x00
#define TEMPHUM12_ICFG_SOFTWARE_RESET    0x80
#define TEMPHUM12_ICFG_AMM_1_120Hz       0x10
#define TEMPHUM12_ICFG_AMM_1_60Hz        0x20
#define TEMPHUM12_ICFG_AMM_0p1Hz         0x30
#define TEMPHUM12_ICFG_AMM_0p2Hz         0x40
#define TEMPHUM12_ICFG_AMM_1Hz           0x50
#define TEMPHUM12_ICFG_AMM_2Hz           0x60
#define TEMPHUM12_ICFG_AMM_5Hz           0x70
#define TEMPHUM12_ICFG_HEATER_DISABLE    0x00
#define TEMPHUM12_ICFG_HEATER_ENABLE     0x08
#define TEMPHUM12_ICFG_DRDY_ENABLE       0x04
#define TEMPHUM12_ICFG_INT_ACTIVE_LOW    0x00
#define TEMPHUM12_ICFG_INT_ACTIVE_HIGH   0x02
#define TEMPHUM12_ICFG_LEVEL_SENSITIVE   0x00
#define TEMPHUM12_ICFG_COMPARATOR_MODE   0x01
/** \} */

/**
 * \defgroup measurement_configuration_register  Measurement configuration register
 * \{
 */
#define TEMPHUM12_MCFG_TEMP_RES_14bit           0x00
#define TEMPHUM12_MCFG_TEMP_RES_11bit           0x40
#define TEMPHUM12_MCFG_TEMP_RES_8bit            0x80
#define TEMPHUM12_MCFG_HUM_RES_14bit            0x00
#define TEMPHUM12_MCFG_HUM_RES_11bit            0x10
#define TEMPHUM12_MCFG_HUM_RES_8bit             0x20
#define TEMPHUM12_MCFG_TEMP_HUM_READ            0x00
#define TEMPHUM12_MCFG_TEMP_ONLY                0x02
#define TEMPHUM12_MCFG_HUM_ONLY                 0x04
#define TEMPHUM12_MCFG_TRIG_NO_ACTION           0x00
#define TEMPHUM12_MCFG_TRIG_START_MEASUREMENT   0x01
/** \} */

/**
 * \defgroup id  Id
 * \{
 */
#define TEMPHUM12_MANUFACTURER_ID        0x4954
#define TEMPHUM12_DEVICE_ID              0x07D0
#define TEMPHUM12_DEVICE_SLAVE_ADDRESS   0x40
/** \} */

/**
 * \defgroup temperature_data  Temperature data 
 * \{
 */
#define TEMPHUM12_TEMP_IN_CELSIUS     0x00
#define TEMPHUM12_TEMP_IN_KELVIN      0x01
#define TEMPHUM12_TEMP_IN_FAHRENHEIT  0x02
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

} temphum12_t;

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

} temphum12_cfg_t;

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
void temphum12_cfg_setup ( temphum12_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param temphum12 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM12_RETVAL temphum12_init ( temphum12_t *ctx, temphum12_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note
 * <pre>
    Configuration device
        TEMPHUM12_REG_INT_ENABLE:
          - TEMPHUM12_INTE_DRDY_ENABLE
        TEMPHUM12_REG_DRDY_INT_CONFIG:
          - TEMPHUM12_ICFG_NORAML_OPERATION 
          - TEMPHUM12_ICFG_AMM_5Hz 
          - TEMPHUM12_ICFG_HEATER_DISABLE 
          - TEMPHUM12_ICFG_DRDY_ENABLE  
          - TEMPHUM12_ICFG_INT_ACTIVE_HIGH 
          - TEMPHUM12_ICFG_COMPARATOR_MODE
        TEMPHUM12_REG_CONFIGURATION:
          - TEMPHUM12_MCFG_TEMP_RES_14bit  
          - TEMPHUM12_MCFG_HUM_RES_14bit  
          - TEMPHUM12_MCFG_TEMP_HUM_READ  
          - TEMPHUM12_MCFG_TRIG_START_MEASUREMEN
 * </pre> 
 *
 * @description This function executes default configuration for Temphum 12 click.
 */
void temphum12_default_cfg ( temphum12_t *ctx );

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
void temphum12_generic_write ( temphum12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum12_generic_read ( temphum12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Temperature data
 *
 * @param ctx          Click object.
 * @param temp_in      Temperature in ... (FAHRENHEIT, KELVIN or CELSIUS)
 *
 * @return Temperature data
 */
float temphum12_get_temperature ( temphum12_t *ctx, uint8_t temp_in );

/**
 * @brief Relative Huminidy data
 *
 * @param ctx          Click object.
 *
 * @return Relative Huminidy data in [%RH]
 */
float temphum12_get_humidity ( temphum12_t *ctx );

/**
 * @brief Interrupt state
 *
 * @param ctx          Click object.
 *
 * @return Interrupt state on the INT pin
 */
uint8_t temphum12_get_intrrupt_state ( temphum12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM12_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

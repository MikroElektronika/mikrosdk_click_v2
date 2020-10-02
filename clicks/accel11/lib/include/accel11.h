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
 * \brief This file contains API for Accel 11 Click driver.
 *
 * \addtogroup accel11 Accel 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL11_H
#define ACCEL11_H

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

#define ACCEL11_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.it1   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.it2   = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ACCEL11_MASTER_I2C 0
#define ACCEL11_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL11_RETVAL  uint8_t

#define ACCEL11_OK                               0x00
#define ACCEL11_INIT_ERROR                       0xFF
/** \} */

/**
 * \defgroup chip_id Chip Id
 * \{
 */
#define ACCEL11_CHIP_ID                          0x16 
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define ACCEL11_REG_CHIP_ID                      0x00
#define ACCEL11_REG_ERROR                        0x02
#define ACCEL11_REG_STATUS                       0x03
#define ACCEL11_REG_AUX_X_LSB                    0x0A
#define ACCEL11_REG_AUX_X_MSB                    0x0B
#define ACCEL11_REG_AUX_Y_LSB                    0x0C
#define ACCEL11_REG_AUX_Y_MSB                    0x0D
#define ACCEL11_REG_AUX_Z_LSB                    0x0E
#define ACCEL11_REG_AUX_Z_MSB                    0x0F
#define ACCEL11_REG_AUX_R_LSB                    0x10
#define ACCEL11_REG_AUX_R_MSB                    0x11
#define ACCEL11_REG_ACCEL_X_LSB                  0x12
#define ACCEL11_REG_ACCEL_X_MSB                  0x13
#define ACCEL11_REG_ACCEL_Y_LSB                  0x14
#define ACCEL11_REG_ACCEL_Y_MSB                  0x15
#define ACCEL11_REG_ACCEL_Z_LSB                  0x16
#define ACCEL11_REG_ACCEL_Z_MSB                  0x17
#define ACCEL11_REG_SENSOR_TIME_0                0x18
#define ACCEL11_REG_SENSOR_TIME_1                0x19
#define ACCEL11_REG_SENSOR_TIME_2                0x1A
#define ACCEL11_REG_EVENT                        0x1B
#define ACCEL11_REG_STATUS_INT_0                 0x1C
#define ACCEL11_REG_STATUS_INT_1                 0x1D
#define ACCEL11_REG_STEP_COUNTER_0               0x1E
#define ACCEL11_REG_STEP_COUNTER_1               0x1F
#define ACCEL11_REG_STEP_COUNTER_2               0x20
#define ACCEL11_REG_STEP_COUNTER_3               0x21
#define ACCEL11_REG_TEMPERATURE                  0x22
#define ACCEL11_REG_FIFO_LENGTH_LSB              0x24
#define ACCEL11_REG_FIFO_LENGTH_MSB              0x25
#define ACCEL11_REG_FIFO_DATA                    0x26
#define ACCEL11_REG_ACTIVITY_TYPE                0x27
#define ACCEL11_REG_INTERNAL_STATUS              0x2A
#define ACCEL11_REG_ACCEL_CONFIG                 0x40
#define ACCEL11_REG_ACCEL_RANGE                  0x41
#define ACCEL11_REG_AUX_CONFIG                   0x44
#define ACCEL11_REG_FIFO_DOWNS                   0x45
#define ACCEL11_REG_FIFO_WTM_LSB                 0x46
#define ACCEL11_REG_FIFO_WTM_MSB                 0x47
#define ACCEL11_REG_FIFO_CONFIG_0                0x48
#define ACCEL11_REG_FIFO_CONFIG_1                0x49
#define ACCEL11_AUX_DEV_ID                       0x4B
#define ACCEL11_REG_AUX_IF_CONFIG                0x4C
#define ACCEL11_REG_AUX_RD_ADDRESS               0x4D
#define ACCEL11_REG_AUX_WR_ADDRESS               0x4E
#define ACCEL11_REG_AUX_WR_DATA                  0x4F
#define ACCEL11_REG_INT1_IO_CTRL                 0x53
#define ACCEL11_REG_INT2_IO_CTRL                 0x54
#define ACCEL11_REG_INT_LATCH                    0x55
#define ACCEL11_REG_INT1_MAP                     0x56
#define ACCEL11_REG_INT2_MAP                     0x57
#define ACCEL11_REG_INT_MAP_DATA                 0x58
#define ACCEL11_REG_INT_CTRL                     0x59
#define ACCEL11_REG_FEATURES_IN                  0x5E
#define ACCEL11_REG_INTERNAL_ERROR               0x5F
#define ACCEL11_REG_NVM_CONF                     0x6A
#define ACCEL11_REG_SPI_IF_CONF                  0x6B
#define ACCEL11_REG_ACCEL_SELF_TEST              0x6D
#define ACCEL11_REG_NV_CONF                      0x70
#define ACCEL11_REG_OFFSET_X_AXIS                0x71
#define ACCEL11_REG_OFFSET_Y_AXIS                0x72
#define ACCEL11_REG_OFFSET_Z_AXIS                0x73
#define ACCEL11_REG_POWER_CONFIG                 0x7C
#define ACCEL11_REG_POWER_CTRL                   0x7D
#define ACCEL11_REG_COMMAND                      0x7E
/** \} */    

/**
 * \defgroup error Error
 * \{
 */
#define ACCEL11_ERR_AUX                          0x80
#define ACCEL11_ERR_FIFO                         0x80
#define ACCEL11_ERR_ACCEL                        0x04
#define ACCEL11_ERR_CMD                          0x02
#define ACCEL11_ERR_FATAL                        0x01
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define ACCEL11_STATUS_DRDY_ACCEL                0x80
#define ACCEL11_STATUS_DRDY_AUX                  0x20
#define ACCEL11_STATUS_RDY_CMD                   0x10
#define ACCEL11_STATUS_AUX_MAN_OP                0x04
/** \} */

/**
 * \defgroup event Event
 * \{
 */
#define ACCEL11_EVENT_POWER_UP                   0x00
#define ACCEL11_EVENT_SOFTWARE_RESET             0x01
/** \} */

/**
 * \defgroup interrupt_status_0 Interrupt Status 0
 * \{
 */
#define ACCEL11_INTS0_ERR_INT_OUT                0x80
#define ACCEL11_INTS0_NO_MOTION_OUT              0x40
#define ACCEL11_INTS0_WAKEUP_OUT                 0x20
#define ACCEL11_INTS0_WRIST_TILT_OUT             0x08
#define ACCEL11_INTS0_ACTIVITY_TYPE_OUT          0x04
#define ACCEL11_INTS0_STEP_COUNTER_OUT           0x02
/** \} */

/**
 * \defgroup interrupt_status_1 Interrupt Status 1
 * \{
 */
#define ACCEL11_INTS1_ACCEL_DRDY_INT             0x80
#define ACCEL11_INTS1_AUX_DRDY_INT               0x20
#define ACCEL11_INTS1_FWM_INT                    0x02
#define ACCEL11_INTS1_FFULL_INT                  0x01
/** \} */

/**
 * \defgroup activity_type Activity Type
 * \{
 */
#define ACCEL11_ATYPE_USER_NOT_MOVING            0x00
#define ACCEL11_ATYPE_USER_WALKING               0x01
#define ACCEL11_ATYPE_USER_RUNNING               0x02
/** \} */

/**
 * \defgroup internal_status Internal Status
 * \{
 */
#define ACCEL11_INTERS_ODR_HIGH_ERR              0x80
#define ACCEL11_INTERS_ODR_50HZ_ERR              0x40
#define ACCEL11_INTERS_AXES_REMAP_ERR            0x20
#define ACCEL11_INTERS_NOT_INIT                  0x00
#define ACCEL11_INTERS_INIT_OK                   0x01
#define ACCEL11_INTERS_INIT_ERROR                0x02
#define ACCEL11_INTERS_INVALID_DRIVER            0x03
#define ACCEL11_INTERS_SENSOR_STOPPED            0x04
/** \} */

/**
 * \defgroup accel_configuration Accel Configuration
 * \{
 */
#define ACCEL11_ACFG_AVERAGING_MODE              0x00
#define ACCEL11_ACFG_CONTINUOUS_MODE             0x80
#define ACCEL11_ACFG_BWP_NO_AVERAGING            0x00
#define ACCEL11_ACFG_BWP_AVERAGING_2_SAMPLES     0x10
#define ACCEL11_ACFG_BWP_AVERAGING_4_SAMPLES     0x20
#define ACCEL11_ACFG_BWP_AVERAGING_8_SAMPLES     0x30
#define ACCEL11_ACFG_BWP_AVERAGING_16_SAMPLES    0x40
#define ACCEL11_ACFG_BWP_AVERAGING_32_SAMPLES    0x50
#define ACCEL11_ACFG_BWP_AVERAGING_64_SAMPLES    0x60
#define ACCEL11_ACFG_BWP_AVERAGING_128_SAMPLES   0x70
/** \} */

/**
 * \defgroup accel_range Accel Range
 * \{
 */
#define ACCEL11_RANGE_2g                         0x00
#define ACCEL11_RANGE_4g                         0x01
#define ACCEL11_RANGE_8g                         0x02
#define ACCEL11_RANGE_16g                        0x03
/** \} */

/**
 * \defgroup cfg_odr Cfg Odr 
 * \{
 */
#define ACCEL11_CFG_ODR_0p78Hz                   0x01
#define ACCEL11_CFG_ODR_1p5Hz                    0x02
#define ACCEL11_CFG_ODR_3p1Hz                    0x03
#define ACCEL11_CFG_ODR_6p25Hz                   0x04
#define ACCEL11_CFG_ODR_12p5Hz                   0x05
#define ACCEL11_CFG_ODR_25Hz                     0x06
#define ACCEL11_CFG_ODR_50Hz                     0x07
#define ACCEL11_CFG_ODR_100Hz                    0x08
#define ACCEL11_CFG_ODR_200Hz                    0x09
#define ACCEL11_CFG_ODR_400Hz                    0x0A
#define ACCEL11_CFG_ODR_800Hz                    0x0B
#define ACCEL11_CFG_ODR_1k6Hz                    0x0C
#define ACCEL11_CFG_ODR_3k2Hz                    0x0D
#define ACCEL11_CFG_ODR_6k4Hz                    0x0E
#define ACCEL11_CFG_ODR_12k8Hz                   0x0F
/** \} */

/**
 * \defgroup fifo_config_0 FIFO config 0
 * \{
 */
#define ACCEL11_FCFG0_FIFO_TIME_ENABLE           0x02
#define ACCEL11_FCFG0_FIFO_TIME_DISABLE          0x00
#define ACCEL11_FCFG0_FIFO_STOP_ON_FULL_ENABLE   0x01
#define ACCEL11_FCFG0_FIFO_STOP_ON_FULL_DISABLE  0x00
/** \} */

/**
 * \defgroup fifo_config_1 FIFO config 1
 * \{
 */
#define ACCEL11_FCGF1_FIFO_ACCEL_ENABLE          0x40
#define ACCEL11_FCGF1_FIFO_ACCEL_DISABLE         0x00
#define ACCEL11_FCGF1_FIFO_AUX_ENABLE            0x20
#define ACCEL11_FCGF1_FIFO_AUX_DISABLE           0x00
#define ACCEL11_FCGF1_FIFO_HEADER_ENABLE         0x10
#define ACCEL11_FCGF1_FIFO_HEADER_DISABLE        0x00
#define ACCEL11_FCGF1_FIFO_TAG_INT1_ENABLE       0x08
#define ACCEL11_FCGF1_FIFO_TAG_INT1_DISABLE      0x00
#define ACCEL11_FCGF1_FIFO_TAG_INT2_ENABLE       0x04
#define ACCEL11_FCGF1_FIFO_TAG_INT2_DISABLE      0x00
/** \} */

/**
 * \defgroup aux_if_config AUX IF Config
 * \{
 */
#define ACCEL11_IFCFG_DATA_MODE                  0x00
#define ACCEL11_IFCFG_SETUP_MODE                 0x80
#define ACCEL11_IFCFG_BURST_LENGTH_1             0x00
#define ACCEL11_IFCFG_BURST_LENGTH_2             0x01
#define ACCEL11_IFCFG_BURST_LENGTH_6             0x02
#define ACCEL11_IFCFG_BURST_LENGTH_8             0x03
/** \} */

/**
 * \defgroup interrupt_control Interrupt Control
 * \{
 */
#define ACCEL11_INTIO_INPUT_ENABLE               0x10
#define ACCEL11_INTIO_INPUT_DISABLE              0x00
#define ACCEL11_INTIO_OUTPUT_ENABLE              0x08
#define ACCEL11_INTIO_OUTPUT_DISABLE             0x00
#define ACCEL11_INTIO_PUSH_PULL                  0x00
#define ACCEL11_INTIO_OPEN_DRAIN                 0x04
#define ACCEL11_INTIO_LVL_ACTIVE_LOW             0x00
#define ACCEL11_INTIO_LVL_ACTIVE_HIGH            0x02
#define ACCEL11_INTIO_TRIGGER_LEVEL              0x00
#define ACCEL11_INTIO_TRIGGER_EDGE               0x01
/** \} */

/**
 * \defgroup interrupt_modes Interrupt Modes
 * \{
 */
#define ACCEL11_INTLAT_NON_LATCHED               0x00
#define ACCEL11_INTLAT_LATCHED                   0x01
/** \} */

/**
 * \defgroup interrupt_map_data Interrupt Map Data
 * \{
 */
#define ACCEL11_IMAPD_INT1_FFULL                 0x01
#define ACCEL11_IMAPD_INT1_FWM                   0x03
#define ACCEL11_IMAPD_INT1_DRDY                  0x04
#define ACCEL11_IMAPD_INT2_FFULL                 0x10
#define ACCEL11_IMAPD_INT2_FWM                   0x20
#define ACCEL11_IMAPD_INT2_DRDY                  0x40
/** \} */

/**
 * \defgroup serial_interface_settings Serial Interface Settings
 * \{
 */
#define ACCEL11_SPI_4_WIRE                       0x00
#define ACCEL11_SPI_3_WIRE                       0x01
#define ACCEL11_AUX_INTERFACE_OFF                0x00
#define ACCEL11_AUX_INTERFACE_MAG                0x10
/** \} */

/**
 * \defgroup nvm_backed_configuration_bits NVM Backed Configuration Bits
 * \{
 */
#define ACCEL_NV_ACCEL_OFFSET_ENABLE             0x08
#define ACCEL_NV_ACCEL_OFFSET_DISABLE            0x00
#define ACCEL_NV_I2C_WATCHDOG_ENABLE             0x04
#define ACCEL_NV_I2C_WATCHDOG_DISABLE            0x00
#define ACCEL_NV_I2C_WDT_TIMEOUT_SHORT           0x00
#define ACCEL_NV_I2C_WDT_TIMEOUT_LONG            0x02
#define ACCEL_NV_I2C_INTERFACE_ENABLE            0x00
#define ACCEL_NV_I2C_INTERFACE_DISABLE           0x01
/** \} */

/**
 * \defgroup power_config Power Config
 * \{
 */
#define ACCEL11_PWRCFG_APS_ON                    0x01
#define ACCEL11_PWRCFG_APS_OFF                   0x00
#define ACCEL11_PWRCFG_FSW_ON                    0x02
#define ACCEL11_PWRCFG_FSW_OFF                   0x00
/** \} */

/**
 * \defgroup power_control Power Control
 * \{
 */
#define ACCEL11_PWRCTRL_ACCEL_ENABLE             0x04
#define ACCEL11_PWRCTRL_ACCEL_DISABLE            0x00
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define ACCEL11_CMD_NVM_PROG                     0xA0
#define ACCEL11_CMD_FIFO_FLUSH                   0xB0
#define ACCEL11_CMD_SW_RESET                     0xB6
/** \} */

/**
 * \defgroup axis Axis
 * \{
 */
#define ACCEL11_ACCEL_X_AXIS                     0x12
#define ACCEL11_ACCEL_Y_AXIS                     0x14
#define ACCEL11_ACCEL_Z_AXIS                     0x16
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define ACCEL11_SLAVE_ADDRESS_GND                0x18
#define ACCEL11_SLAVE_ADDRESS_VCC                0x19
/** \} */

/**
 * \defgroup test_comunication Test Comunication
 * \{
 */
#define ACCEL11_TEST_COMUNICATION_ERROR          0x01
#define ACCEL11_TEST_COMUNICATION_OK             0x00
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
typedef uint8_t  accel11_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *accel11_master_io_t )( struct accel11_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct accel11_s
{
   // Output pins 
   digital_out_t cs;

    // Input pins 

    digital_in_t it1;
    digital_in_t it2;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   accel11_master_io_t  write_f;
   accel11_master_io_t  read_f;
   accel11_select_t master_sel;

} accel11_t;

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

    pin_name_t it1;
    pin_name_t it2;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   accel11_select_t sel;

} accel11_cfg_t;

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
void accel11_cfg_setup ( accel11_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param accel11 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL11_RETVAL accel11_init ( accel11_t *ctx, accel11_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Accel 11 click.
 */
void accel11_default_cfg ( accel11_t *ctx );

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
void accel11_generic_write ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void accel11_generic_read ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for write one byte in register.
 *
 * @param ctx       Click object.
 * @param addr      Register in which the data will be written.
 * @param data_in   Data which be written in the register.
 *
 * @description This function writes one byte in register.
 */
void accel11_write_byte ( accel11_t *ctx, uint8_t addr, uint8_t data_in );

/**
 * @brief Functions for read byte from register.
 *
 * @param ctx       Click object.
 * @param addr      Register which will be read.
 *
 * @description This function reads byte from register.
 */
uint8_t accel11_read_byte ( accel11_t *ctx, uint8_t addr );

/**
 * @brief Test comunication function.
 *
 * @param ctx       Click object.
 *
 * @description This function test comunication.
 */
uint8_t accel11_test_comunication ( accel11_t *ctx );

/**
 * @brief Software reset function.
 *
 * @param ctx       Click object.
 *
 * @description This function reset software.
 */
void accel11_software_reset ( accel11_t *ctx );

/**
 * @brief Accel Axis data function.
 *
 * @param ctx       Click object.
 * @param axis      Accel axis that will be read.
 *
 * @description This function reads accel axis.
 */
int16_t accel11_get_axis_data ( accel11_t *ctx, uint8_t axis );

/**
 * @brief Function for power on chip.
 *
 * @param ctx       Click object.
 *
 * @description This function for power on chip.
 */
void accel11_power_on_procedure ( accel11_t *ctx );

/**
 * @brief Function get temperature.
 *
 * @param ctx       Click object.
 *
 * @description This function gets temperature in celsius [C].
 */
int8_t accel11_get_temperature ( accel11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

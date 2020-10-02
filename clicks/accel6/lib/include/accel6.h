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
 * \brief This file contains API for Accel 6 Click driver.
 *
 * \addtogroup accel6 Accel 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL6_H
#define ACCEL6_H

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

#define ACCEL6_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ACCEL6_MASTER_I2C 0
#define ACCEL6_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL6_RETVAL  uint8_t

#define ACCEL6_OK           0x00
#define ACCEL6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup мask Mask
 * \{
 */
#define ACCEL6_CHIP_ID        0xFB
#define ACCEL6_SOFT_RESET     0xB6 
/** \} */
 
/**
 * \defgroup аxis Axis
 * \{
 */
#define ACCEL6_AXIS_X        0x02 
#define ACCEL6_AXIS_Y        0x04 
#define ACCEL6_AXIS_Z        0x06 
/** \} */
 
/**
 * \defgroup register Register
 * \{
 */ 
#define ACCEL6_REG_CHIP_ID              0x00 
#define ACCEL6_REG_AXIS_X_LSB           0x02 
#define ACCEL6_REG_AXIS_X_MSB           0x03 
#define ACCEL6_REG_AXIS_Y_LSB           0x04 
#define ACCEL6_REG_AXIS_Y_MSB           0x05 
#define ACCEL6_REG_AXIS_Z_LSB           0x06 
#define ACCEL6_REG_AXIS_Z_MSB           0x07 
#define ACCEL6_REG_TEMPERATURE          0x08 
#define ACCEL6_REG_INT_STATUS_0         0x09 
#define ACCEL6_REG_INT_STATUS_1         0x0A 
#define ACCEL6_REG_INT_STATUS_2         0x0B 
#define ACCEL6_REG_INT_STATUS_3         0x0C 
#define ACCEL6_REG_FIFO_STATUS          0x0E 
#define ACCEL6_REG_PMU_RANGE            0x0F 
#define ACCEL6_REG_PMU_BW               0x10 
#define ACCEL6_REG_PMU_LPW              0x11 
#define ACCEL6_REG_PMU_LOW_POWER        0x12 
#define ACCEL6_REG_ACCD_HBW             0x13 
#define ACCEL6_REG_BGW_SOFTRESET        0x14 
#define ACCEL6_REG_INT_EN_0             0x16 
#define ACCEL6_REG_INT_EN_1             0x17 
#define ACCEL6_REG_INT_EN_2             0x18 
#define ACCEL6_REG_INT_MAP_0            0x19 
#define ACCEL6_REG_INT_MAP_1            0x1A 
#define ACCEL6_REG_INT_MAP_2            0x1B 
#define ACCEL6_REG_INT_SRC              0x1E 
#define ACCEL6_REG_INT_OUT_CTRL         0x20 
#define ACCEL6_REG_INT_RST_LATCH        0x21 
#define ACCEL6_REG_INT1                 0x23 
#define ACCEL6_REG_INT2                 0x24 
#define ACCEL6_REG_INT3                 0x25 
#define ACCEL6_REG_INT4                 0x26 
#define ACCEL6_REG_INT5                 0x27 
#define ACCEL6_REG_INT6                 0x28 
#define ACCEL6_REG_INT7                 0x29 
#define ACCEL6_REG_INT8                 0x2A 
#define ACCEL6_REG_INT9                 0x2B 
#define ACCEL6_REG_INT_A                0x2C 
#define ACCEL6_REG_INT_B                0x2D 
#define ACCEL6_REG_INT_C                0x2E 
#define ACCEL6_REG_INT_D                0x2F 
#define ACCEL6_REG_FIFO_CONFIG_0        0x30 
#define ACCEL6_REG_PMU_SELF_TEST        0x32 
#define ACCEL6_REG_TRIM_NVM_CTRL        0x33 
#define ACCEL6_REG_BGW_SPI3_WDT         0x34 
#define ACCEL6_REG_OFC_CTRL             0x36 
#define ACCEL6_REG_OFC_SETTINGS         0x37 
#define ACCEL6_REG_OFC_OFFSET_X         0x38 
#define ACCEL6_REG_OFC_OFFSET_Y         0x39 
#define ACCEL6_REG_OFC_OFFSET_Z         0x3A 
#define ACCEL6_REG_TRIM_GP_0            0x3B 
#define ACCEL6_REG_TRIM_GP_1            0x3C 
#define ACCEL6_REG_FIFO_CONFIG_1        0x3E 
#define ACCEL6_REG_FIFO_DATA            0x3F 
/** \} */
 
/**
 * \defgroup interrupt_status_register 0Interrupt status register 0
 * \{
 */
#define ACCEL6_STATUS_0_FLAT_INT              0x80 
#define ACCEL6_STATUS_0_ORIENT_INT            0x40 
#define ACCEL6_STATUS_0_SINGLE_TAP_INT        0x20 
#define ACCEL6_STATUS_0_DOUBLE_TAP_INT        0x10 
#define ACCEL6_STATUS_0_MOTION_INT            0x08 
#define ACCEL6_STATUS_0_SLOPE_INT             0x04 
#define ACCEL6_STATUS_0_HIGH_INT              0x02 
#define ACCEL6_STATUS_0_LOW_INT               0x01 
/** \} */
 
/**
 * \defgroup interrupt_status_register_1 Interrupt status register 1
 * \{
 */
#define ACCEL6_STATUS_1_DATA_INT             0x80 
#define ACCEL6_STATUS_1_FIFO_WM_INT          0x40 
#define ACCEL6_STATUS_1_FIFO_FULL_INT        0x20 
/** \} */
 
/**
 * \defgroup interrupt_status_register_2 Interrupt status register 2
 * \{
 */
#define ACCEL6_STATUS_2_TAP_SING              0x80 
#define ACCEL6_STATUS_2_TAP_FIRST_Z           0x40 
#define ACCEL6_STATUS_2_TAP_FIRST_Y           0x20 
#define ACCEL6_STATUS_2_TAP_FIRST_X           0x10 
#define ACCEL6_STATUS_2_SLOPE_SING            0x08 
#define ACCEL6_STATUS_2_SLOPE_FIRST_Z         0x04 
#define ACCEL6_STATUS_2_SLOPE_FIRST_Y         0x02 
#define ACCEL6_STATUS_2_SLOPE_FIRST_X         0x01 
/** \} */
 
/**
 * \defgroup interrupt_status_register_3  Interrupt status register 3
 * \{
 */
#define ACCEL6_STATUS_3_FLAT_POSITION                    0x80 
#define ACCEL6_STATUS_3_ORIENT_Z_UPWARD                  0x00 
#define ACCEL6_STATUS_3_ORIENT_Z_DOWNWARD                0x40 
#define ACCEL6_STATUS_3_ORIENT_XY_UPRIGHT                0x00 
#define ACCEL6_STATUS_3_ORIENT_XY_UPSIDE                 0x10 
#define ACCEL6_STATUS_3_ORIENT_XY_LANDSCAPE_LEFT         0x20 
#define ACCEL6_STATUS_3_ORIENT_XY_LANDSCAPE_RIGHT        0x30 
#define ACCEL6_STATUS_3_HIGH_SING_POSITIVE               0x00 
#define ACCEL6_STATUS_3_HIGH_SING_NEGATIVE               0x08 
#define ACCEL6_STATUS_3_HIGH_FIRST_Z                     0x04 
#define ACCEL6_STATUS_3_HIGH_FIRST_Y                     0x02 
#define ACCEL6_STATUS_3_HIGH_FIRST_X                     0x01  
/** \} */
 
/**
 * \defgroup accelerometer_g_range  Accelerometer g-range
 * \{
 */
#define ACCEL6_PMU_RANGE_2g         0x03 
#define ACCEL6_PMU_RANGE_4g         0x05 
#define ACCEL6_PMU_RANGE_8g         0x08 
#define ACCEL6_PMU_RANGE_16g        0x0C 
/** \} */
 
/**
 * \defgroup acceleration_data_filter_bandwidth   Acceleration data filter bandwidth
 * \{
 */
#define ACCEL6_PMU_BW_7_81Hz         0x08 
#define ACCEL6_PMU_BW_15_63Hz        0x09 
#define ACCEL6_PMU_BW_31_25Hz        0x0A 
#define ACCEL6_PMU_BW_62_5Hz         0x0B 
#define ACCEL6_PMU_BW_125Hz          0x0C 
#define ACCEL6_PMU_BW_250Hz          0x0D 
#define ACCEL6_PMU_BW_500Hz          0x0E 
/** \} */
 
/**
 * \defgroup power_sleep_period  power sleep period
 * \{
 */
#define ACCEL6_PMU_LPW_NORMAL_MODE              0x00 
#define ACCEL6_PMU_LPW_DEEP_SUSPEND_MODE        0x20 
#define ACCEL6_PMU_LPW_LOW_POWER_MODE           0x40 
#define ACCEL6_PMU_LPW_SUSPEND_MODE             0x80 
#define ACCEL6_PMU_LPW_SLEEP_0_5ms              0x05 
#define ACCEL6_PMU_LPW_SLEEP_1ms                0x06 
#define ACCEL6_PMU_LPW_SLEEP_2ms                0x07 
#define ACCEL6_PMU_LPW_SLEEP_4ms                0x08 
#define ACCEL6_PMU_LPW_SLEEP_6ms                0x09 
#define ACCEL6_PMU_LPW_SLEEP_10ms               0x0A 
#define ACCEL6_PMU_LPW_SLEEP_25ms               0x0B 
#define ACCEL6_PMU_LPW_SLEEP_50ms               0x0C 
#define ACCEL6_PMU_LPW_SLEEP_100ms              0x0D 
#define ACCEL6_PMU_LPW_SLEEP_500ms              0x0E 
/** \} */
 
/**
 * \defgroup interrupt_enable_group_0  Interrupt enable group 0
 * \{
 */
#define ACCEL6_INT_EN_0_FLAT_ENABLE               0x80 
#define ACCEL6_INT_EN_0_ORIENT_ENABLE             0x40 
#define ACCEL6_INT_EN_0_SINGLE_TAP_ENABLE         0x20 
#define ACCEL6_INT_EN_0_DOUBLE_TAP_ENABLE         0x10 
#define ACCEL6_INT_EN_0_SLOPE_Z_ENABLE            0x04 
#define ACCEL6_INT_EN_0_SLOPE_Y_ENABLE            0x02 
#define ACCEL6_INT_EN_0_SLOPE_X_ENABLE            0x01 
/** \} */
 
/**
 * \defgroup interrupt_enable_group_1  Interrupt enable group 1
 * \{
 */
#define ACCEL6_INT_EN_1_FIFO_WM_ENABLE           0x40 
#define ACCEL6_INT_EN_1_FIFO_FULL_ENABLE         0x20 
#define ACCEL6_INT_EN_1_DATA_ENABLE              0x10 
#define ACCEL6_INT_EN_1_LOW_ENABLE               0x08 
#define ACCEL6_INT_EN_1_HIGH_Z_ENABLE            0x04 
#define ACCEL6_INT_EN_1_HIGH_Y_ENABLE            0x02 
#define ACCEL6_INT_EN_1_HIGH_X_ENABLE            0x01 
/** \} */
 
/**
 * \defgroup interrupt_enable_group_2  Interrupt enable group 2
 * \{
 */
#define ACCEL6_INT_EN_2_MOTION_ENABLE          0x08 
#define ACCEL6_INT_EN_2_MOTION_Z_ENABLE        0x04 
#define ACCEL6_INT_EN_2_MOTION_Y_ENABLE        0x02 
#define ACCEL6_INT_EN_2_MOTION_X_ENABLE        0x01 
/** \} */
 
/**
 * \defgroup interrupt_map_group_0  Interrupt map group 0
 * \{
 */
#define ACCEL6_INT1_MAP_FLAT_ENABLE               0x80 
#define ACCEL6_INT1_MAP_ORIENT_ENABLE             0x40 
#define ACCEL6_INT1_MAP_SINGLE_TAP_ENABLE         0x20 
#define ACCEL6_INT1_MAP_DOUBLE_TAP_ENABLE         0x10 
#define ACCEL6_INT1_MAP_MOTION_ENABLE             0x08 
#define ACCEL6_INT1_MAP_SLOPE_ENABLE              0x04 
#define ACCEL6_INT1_MAP_HIGH_ENABLE               0x02 
#define ACCEL6_INT1_MAP_LOW_ENABLE                0x01 
/** \} */
 
/**
 * \defgroup interrupt_map_group_1  Interrupt map group 1
 * \{
 */
#define ACCEL6_INT2_MAP_DATA_ENABLE               0x80 
#define ACCEL6_INT2_MAP_FIFO_WM_ENABLE            0x40 
#define ACCEL6_INT2_MAP_FIFO_FULL_ENABLE          0x20 
#define ACCEL6_INT1_MAP_DATA_ENABLE               0x01 
#define ACCEL6_INT1_MAP_FIFO_WM_ENABLE            0x02 
#define ACCEL6_INT1_MAP_FIFO_FULL_ENABLE          0x04 
/** \} */
 
/**
 * \defgroup interrupt_map_group_2  Interrupt map group 2
 * \{
 */
#define ACCEL6_INT2_MAP_FLAT_ENABLE               0x80 
#define ACCEL6_INT2_MAP_ORIENT_ENABLE             0x40 
#define ACCEL6_INT2_MAP_SINGLE_TAP_ENABLE         0x20 
#define ACCEL6_INT2_MAP_DOUBLE_TAP_ENABLE         0x10 
#define ACCEL6_INT2_MAP_MOTION_ENABLE             0x08 
#define ACCEL6_INT2_MAP_SLOPE_ENABLE              0x04 
#define ACCEL6_INT2_MAP_HIGH_ENABLE               0x02 
#define ACCEL6_INT2_MAP_LOW_ENABLE                0x01 
/** \} */
 
/**
 * \defgroup interrup_with_selectable_data_source  Interrupt with selectable data source
 * \{
 */
#define ACCEL6_INT_SRC_DATA          0x20 
#define ACCEL6_INT_SRC_TAP           0x10 
#define ACCEL6_INT_SRC_MOTION        0x08 
#define ACCEL6_INT_SRC_SLOPE         0x04 
#define ACCEL6_INT_SRC_HIGH          0x02 
#define ACCEL6_INT_SRC_LOW           0x01 
/** \} */
 
/**
 * \defgroup configuration_of_the_interrupt_pin  Configuration of the interrupt pin 
 * \{
 */
#define ACCEL6_INT2_CTRL_OPEN_DRAIN               0x08 
#define ACCEL6_INT1_CTRL_OPEN_DRAIN               0x02 
#define ACCEL6_INT2_CTRL_ACTIVE_HIGH_LEVEL        0x04 
#define ACCEL6_INT1_CTRL_ACTIVE_HIGH_LEVEL        0x01 
/** \} */
 
/**
 * \defgroup interrupt_reset_and_interrupt_selection_mode  Interrupt reset and interrupt selection mode
 * \{
 */
#define ACCEL6_LATCH_RESET_INT         0x80 
#define ACCEL6_LATCH_INT_250ms         0x01 
#define ACCEL6_LATCH_INT_500ms         0x02 
#define ACCEL6_LATCH_INT_1sec          0x03 
#define ACCEL6_LATCH_INT_2sec          0x04 
#define ACCEL6_LATCH_INT_4sec          0x05 
#define ACCEL6_LATCH_INT_8sec          0x06 
#define ACCEL6_LATCH_INT_250us         0x09 
#define ACCEL6_LATCH_INT_500us         0x0A 
#define ACCEL6_LATCH_INT_1ms           0x0B 
#define ACCEL6_LATCH_INT_12_5ms        0x0C 
#define ACCEL6_LATCH_INT_25ms          0x0D 
#define ACCEL6_LATCH_INT_50ms          0x0E 
/** \} */
 
/**
 * \defgroup single_tap_and_double_tap_interrupts  Single tap and double tap interrupts
 * \{
 */
#define ACCEL6_TAP_QUIET_30ms        0x00 
#define ACCEL6_TAP_QUIET_20ms        0x80 
#define ACCEL6_TAP_SHOCK_50ms        0x00 
#define ACCEL6_TAP_SHOCK_75ms        0x40 
#define ACCEL6_TAP_DUR_50ms          0x00 
#define ACCEL6_TAP_DUR_100ms         0x01 
#define ACCEL6_TAP_DUR_150ms         0x02 
#define ACCEL6_TAP_DUR_200ms         0x03 
#define ACCEL6_TAP_DUR_250ms         0x04 
#define ACCEL6_TAP_DUR_375ms         0x05 
#define ACCEL6_TAP_DUR_500ms         0x06 
#define ACCEL6_TAP_DUR_700ms         0x07 
/** \} */
 
/**
 * \defgroup tap_samples  Tap samples
 * \{
 */
#define ACCEL6_TAP_2_SAMPLES         0x00 
#define ACCEL6_TAP_4_SAMPLES         0x40 
#define ACCEL6_TAP_8_SAMPLES         0x80 
#define ACCEL6_TAP_16_SAMPLES        0xC0 
/** \} */
 
/**
 * \defgroup self_test  Self test
 * \{
 */
#define ACCEL6_SELF_TEST_SING_POSITIVE        0x40 
#define ACCEL6_SELF_TEST_SING_NEGATIVE        0x00 
#define ACCEL6_SELF_TEST_DISABLE              0x00 
#define ACCEL6_SELF_TEST_X_AXIS               0x01 
#define ACCEL6_SELF_TEST_Y_AXIS               0x02 
#define ACCEL6_SELF_TEST_Z_AXIS               0x03 
/** \} */
 
/**
 * \defgroup settings_for_the_digital_interfaces  Settings for the digital interfaces
 * \{
 */
#define ACCEL6_I2C_ENABLE          0x04 
#define ACCEL6_I2C_DISABLE         0x00 
#define ACCEL6_I2C_WTD_1ms         0x00 
#define ACCEL6_I2C_WTD_50ms        0x02 
#define ACCEL6_SPI_4_WIRE          0x00 
#define ACCEL6_SPI_3_WIRE          0x01 
/** \} */
 
/**
 * \defgroup offset_control_register  Offset control register
 * \{
 */
#define ACCEL6_OFFSET_RESET                 0x80 
#define ACCEL6_OFFSET_TRIGGER_X_AXIS        0x20 
#define ACCEL6_OFFSET_TRIGGER_Y_AXIS        0x40 
#define ACCEL6_OFFSET_TRIGGER_Z_AXIS        0x60 
#define ACCEL6_OFFSET_NOT_TRIGGER           0x00 
#define ACCEL6_OFC_HP_X_ENABLE              0x04 
#define ACCEL6_OFC_HP_Y_ENABLE              0x02 
#define ACCEL6_OFC_HP_Z_ENABLE              0x01 
/** \} */
 
/**
 * \defgroup offset_settings  Offset settings
 * \{
 */
#define ACCEL6_OFFSET_TARGET_Z_0g              0x00 
#define ACCEL6_OFFSET_TARGET_Z_PLUS_1g         0x20 
#define ACCEL6_OFFSET_TARGET_Z_MINUS_1g        0x40 
#define ACCEL6_OFFSET_TARGET_Y_PLUS_1g         0x08 
#define ACCEL6_OFFSET_TARGET_Y_MINUS_1g        0x10 
#define ACCEL6_OFFSET_TARGET_X_PLUS_1g         0x02 
#define ACCEL6_OFFSET_TARGET_X_MINUS_1g        0x04 
#define ACCEL6_OFFSET_CUT_OFF_1Hz              0x00 
#define ACCEL6_OFFSET_CUT_OFF_10Hz             0x01 
/** \} */
 
/**
 * \defgroup fifo_mode_and_fifo_data_selsect  FIFO mode and FIFO data selsect
 * \{
 */
#define ACCEL6_FIFO_MODE_BYPASS            0x00 
#define ACCEL6_FIFO_MODE_FIFO              0x40 
#define ACCEL6_FIFO_MODE_STREAM            0x80 
#define ACCEL6_FIFO_SELECT_XYZ_AXIS        0x00 
#define ACCEL6_FIFO_SELECT_X_AXIS          0x01 
#define ACCEL6_FIFO_SELECT_Y_AXIS          0x02 
#define ACCEL6_FIFO_SELECT_Z_AXIS          0x03 
/** \} */
 
/**
 * \defgroup error  Error
 * \{
 */
/*  */
#define DEVICE_ERROR        0x04 
#define DEVICE_OK           0x00 
/** \} */
 
/**
 * \defgroup tap_detect  Tap detect
 * \{
 */
#define TAP_X_NEGATIVE          0x01 
#define TAP_Y_NEGATIVE          0x02 
#define TAP_Z_NEGATIVE          0x03 
#define TAP_X_POSITIVE          0x04 
#define TAP_Y_POSITIVE          0x05 
#define TAP_Z_POSITIVE          0x06 
#define NON_TAP                 0x00 
/** \} */
 
/**
 * \defgroup slope_detect  Slope detect
 * \{
 */
#define SLOPE_X_NEGATIVE          0x01 
#define SLOPE_Y_NEGATIVE          0x02 
#define SLOPE_Z_NEGATIVE          0x03 
#define SLOPE_X_POSITIVE          0x04 
#define SLOPE_Y_POSITIVE          0x05 
#define SLOPE_Z_POSITIVE          0x06 
#define NON_SLOPE                 0x00 
/** \} */
 
/**
 * \defgroup orient_detect  Orient detect
 * \{
 */
#define Z_ORIENT_UPWARD_LOOKING          0x01 
#define Z_ORIENT_DOWNWARD_LOOKING        0x02 
#define XY_ORIENT_UPSIDE_DOWN            0x01 
#define XY_ORIENT_LANDSCAPE_LEFT         0x02 
#define XY_ORIENT_LANDSCAPE_RIGHT        0x03 
#define XY_ORIENT_UPRIGHT                0x04 
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
typedef uint8_t  accel6_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *accel6_master_io_t )( struct accel6_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct accel6_s
{
   digital_out_t cs;
   
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   accel6_master_io_t  write_f;
   accel6_master_io_t  read_f;
   accel6_select_t master_sel;

   float device_gaus;
   float device_freq;

} accel6_t;

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

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;
    uint32_t spi_speed;
    uint8_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   accel6_select_t sel;

   float dev_gaus;
   float dev_freq;

} accel6_cfg_t;

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
void accel6_cfg_setup ( accel6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param accel6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL6_RETVAL accel6_init ( accel6_t *ctx, accel6_cfg_t *cfg );

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
void accel6_generic_write ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void accel6_generic_read ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for software reset
 *
 * @param ctx      Click object.
 *
 */
void accel6_soft_reset ( accel6_t *ctx );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx         Click object.
 * @param range_data  Accelerometer g-range        
 * @param bw_data     Acceleration data filter bandwidth
 * @param lpw_data    Power mode and the low power sleep period.      
 *
 * @description This function executes default configuration for Accel 6 click.
 * @note Default configuration of the chip contains the settings:
 *<pre> 
 *      Set ACCEL6_REG_PMU_RANGE reg:
 *        - range_data
 *      Set ACCEL6_REG_PMU_BW reg:
 *        - bw_data
 *      Set ACCEL6_REG_PMU_LPW reg:
 *        - lpw_data
 *      Set ACCEL6_REG_BGW_SPI3_WDT reg:
 *        - ACCEL6_I2C_ENABLE | ACCEL6_I2C_WTD_50ms
 *      Set ACCEL6_REG_INT_EN_1 reg:
 *        - ACCEL6_INT_EN_1_DATA_ENABLE
 *      Set ACCEL6_REG_INT_MAP_1 reg:
 *        - ACCEL6_INT1_MAP_DATA_ENABLE
 *      Set ACCEL6_REG_INT_EN_0 reg:
 *        - ACCEL6_INT1_MAP_ORIENT_ENABLE |
 *          ACCEL6_INT1_MAP_SINGLE_TAP_ENABLE | 
 *          ACCEL6_INT1_MAP_DOUBLE_TAP_ENABLE |
 *          ACCEL6_INT1_MAP_SLOPE_ENABLE;
 *      Set ACCEL6_REG_INT9 reg:
 *        - 0x0A
 *      Set ACCEL6_REG_INT_OUT_CTRL reg:
 *        - ACCEL6_INT2_CTRL_ACTIVE_HIGH_LEVEL | ACCEL6_INT1_CTRL_ACTIVE_HIGH_LEVEL
 *
 * -storage accel range
 * -storage bandwidth data
 *</pre>
 */
void accel6_default_cfg ( accel6_t *ctx, uint8_t range_data, uint8_t bw_data, uint8_t lpw_data );

/**
 * @brief Functions for set offset
 *
 * @param ctx           Click object.
 * @param set_offset    Data which will be written in offset settings register
 * @param offset_data   Buffer in which the XYZ offset will be written.
 *                             - offset_data[ 0 ] = x_offset
 *                             - offset_data[ 1 ] = y_offset
 *                             - offset_data[ 2 ] = z_offset
 *
 */
void accel6_data_offset ( accel6_t *ctx, uint8_t set_offset, float *offset_data );

/**
 * @brief Functions for detect tap on the x/y/z axis
 *
 * @param ctx      Click object.
 *
 * @retval Information of the Tap
 *
 * @note 
 * <pre>
 * Tap detection :
 *    - X negative  (0x01)
 *    - Y negative  (0x02)
 *    - Z negative  (0x03)
 *    - X positive  (0x04)
 *    - Y positive  (0x05)
 *    - Z positive  (0x06) 
 *</pre>
 */
uint8_t accel6_get_tap_status ( accel6_t *ctx );

/**
 * @brief Functions for detect slope on the x/y/z axis
 *
 * @param ctx      Click object.
 *
 * @retval Information of the slope
 *
 * @note 
 * <pre>
 * Tap detection :
 *    - X negative  (0x01)
 *    - Y negative  (0x02)
 *    - Z negative  (0x03)
 *    - X positive  (0x04)
 *    - Y positive  (0x05)
 *    - Z positive  (0x06) 
 *</pre>
 */
uint8_t accel6_get_slope_status ( accel6_t *ctx );

/**
 * @brief Functions for read orient
 *
 * @param ctx       Click object.
 * @param z_orient  Buffer in which the Z-axis chip orientation will be written.
 * @param xy_orient Buffer in which the XY-axis chip orientation will be written.
 *
 *@note
 *<pre>
 *  Z orientation :
 *      - UPWARD LOOKING
 *      - DOWNWARD LOOKING
 *   XY orientation :
 *      - UPRIGHT
 *      - UPSIDE DOWN
 *      - LANDSCAPE LEFT
 *      - LANDSCAPE RIGHT
 *</pre>
 */
void accel6_get_orient ( accel6_t *ctx, uint8_t *z_orient, uint8_t *xy_orient );

/**
 * @brief Functions for read axis data
 *
 * @param ctx      Click object.
 * @param axis     Axis data which will be read
 *
 * @retval Axis data in mg
 *
 * @description This function reads data from the desired register.
 */
float accel6_get_axis ( accel6_t *ctx, uint8_t axis );

/**
 * @brief Functions for read temperature
 *
 * @param ctx      Click object.
 *
 * @retval Temperature data in C
 *
 * @note
 * <pre>
 * Formula:
 *   Temperature = 0.5 * Temp_data + 23.0
 *   - Temp_data  data read from ACCEL6_REG_TEMPERATURE register
 *   The formula for calculating the temperature is from dataheet.
 * </pre>
 */
float accel6_get_temperature ( accel6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

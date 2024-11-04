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
 * \brief This file contains API for Shake2Wake Click driver.
 *
 * \addtogroup shake2wake Shake2Wake Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SHAKE2WAKE_H
#define SHAKE2WAKE_H

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

#define SHAKE2WAKE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SHAKE2WAKE_OK                                   0x00
#define SHAKE2WAKE_ERROR                                0xFF
/** \} */

/**
 * \defgroup communication_commands Communication Commands
 * \{
 */
#define SHAKE2WAKE_WRITE_REG                            0x0A
#define SHAKE2WAKE_READ_REG                             0x0B
#define SHAKE2WAKE_READ_FIFO                            0x0D
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define SHAKE2WAKE_REG_DEVID_AD                         0x00
#define SHAKE2WAKE_REG_DEVID_MST                        0x01
#define SHAKE2WAKE_REG_PARTID                           0x02
#define SHAKE2WAKE_REG_REVID                            0x03
#define SHAKE2WAKE_REG_XDATA                            0x08
#define SHAKE2WAKE_REG_YDATA                            0x09
#define SHAKE2WAKE_REG_ZDATA                            0x0A
#define SHAKE2WAKE_REG_STATUS                           0x0B
#define SHAKE2WAKE_REG_FIFO_L                           0x0C
#define SHAKE2WAKE_REG_FIFO_H                           0x0D
#define SHAKE2WAKE_REG_XDATA_L                          0x0E
#define SHAKE2WAKE_REG_XDATA_H                          0x0F
#define SHAKE2WAKE_REG_YDATA_L                          0x10
#define SHAKE2WAKE_REG_YDATA_H                          0x11
#define SHAKE2WAKE_REG_ZDATA_L                          0x12
#define SHAKE2WAKE_REG_ZDATA_H                          0x13
#define SHAKE2WAKE_REG_TEMP_L                           0x14
#define SHAKE2WAKE_REG_TEMP_H                           0x15
#define SHAKE2WAKE_REG_SOFT_RESET                       0x1F
#define SHAKE2WAKE_REG_THRESH_ACT_L                     0x20
#define SHAKE2WAKE_REG_THRESH_ACT_H                     0x21
#define SHAKE2WAKE_REG_TIME_ACT                         0x22
#define SHAKE2WAKE_REG_THRESH_INACT_L                   0x23
#define SHAKE2WAKE_REG_THRESH_INACT_H                   0x24
#define SHAKE2WAKE_REG_TIME_INACT_L                     0x25
#define SHAKE2WAKE_REG_TIME_INACT_H                     0x26
#define SHAKE2WAKE_REG_ACT_INACT_CTL                    0x27
#define SHAKE2WAKE_REG_FIFO_CTL                         0x28
#define SHAKE2WAKE_REG_FIFO_SAMPLES                     0x29
#define SHAKE2WAKE_REG_INTMAP1                          0x2A
#define SHAKE2WAKE_REG_INTMAP2                          0x2B
#define SHAKE2WAKE_REG_FILTER_CTL                       0x2C
#define SHAKE2WAKE_REG_POWER_CTL                        0x2D
#define SHAKE2WAKE_REG_SELF_TEST                        0x2E
/** \} */

/**
 * \defgroup reg_status Register Status
 * \{
 */
#define SHAKE2WAKE_STATUS_ERR_USER_REGS               ( 1 << 7 )
#define SHAKE2WAKE_STATUS_AWAKE                       ( 1 << 6 )
#define SHAKE2WAKE_STATUS_INACT                       ( 1 << 5 )
#define SHAKE2WAKE_STATUS_ACT                         ( 1 << 4 )
#define SHAKE2WAKE_STATUS_FIFO_OVERRUN                ( 1 << 3 )
#define SHAKE2WAKE_STATUS_FIFO_WATERMARK              ( 1 << 2 )
#define SHAKE2WAKE_STATUS_FIFO_RDY                    ( 1 << 1 )
#define SHAKE2WAKE_STATUS_DATA_RDY                      1
/** \} */

/**
 * \defgroup reg_act_inact_ctl Reg Act Inact Ctl
 * \{
 */
#define SHAKE2WAKE_CTL_LINKLOOP_MODE_DEFAULT        ( ( 0 & 0x03 ) << 4 )
#define SHAKE2WAKE_CTL_LINKLOOP_MODE_LINK           ( ( 1 & 0x03 ) << 4 )
#define SHAKE2WAKE_CTL_LINKLOOP_MODE_LOOP           ( ( 3 & 0x03 ) << 4 )
#define SHAKE2WAKE_ACT_INACT_CTL_INACT_REF          ( 1 << 3 )
#define SHAKE2WAKE_ACT_INACT_CTL_INACT_EN           ( 1 << 2 )
#define SHAKE2WAKE_ACT_INACT_CTL_ACT_REF            ( 1 << 1 )
#define SHAKE2WAKE_ACT_INACT_CTL_ACT_EN               1
/** \} */

/**
 * \defgroup reg_fifo_ctl Reg Fifo Ctl
 * \{
 */
#define SHAKE2WAKE_FIFO_CTL_AH                      ( 1 << 3 )
#define SHAKE2WAKE_FIFO_CTL_FIFO_TEMP               ( 1 << 2 )
#define SHAKE2WAKE_FIFO_CTL_FIFO_MODE_DIS           ( 0 & 0x03 )
#define SHAKE2WAKE_FIFO_CTL_FIFO_MODE_OSM           ( 1 & 0x03 )
#define SHAKE2WAKE_FIFO_CTL_FIFO_MODE_STREAM        ( 2 & 0x03 )
#define SHAKE2WAKE_FIFO_CTL_FIFO_MODE_TRIG          ( 3 & 0x03 )
/** \} */

/**
 * \defgroup reg_int_map_1 Reg Int Map 1
 * \{
 */
#define SHAKE2WAKE_INTMAP1_INT_LOW                  ( 1 << 7 )
#define SHAKE2WAKE_INTMAP1_AWAKE                    ( 1 << 6 )
#define SHAKE2WAKE_INTMAP1_INACT                    ( 1 << 5 )
#define SHAKE2WAKE_INTMAP1_ACT                      ( 1 << 4 )
#define SHAKE2WAKE_INTMAP1_FIFO_OVERRUN             ( 1 << 3 )
#define SHAKE2WAKE_INTMAP1_FIFO_WATERMARK           ( 1 << 2 )
#define SHAKE2WAKE_INTMAP1_FIFO_READY               ( 1 << 1 )
#define SHAKE2WAKE_INTMAP1_DATA_READY                 1
/** \} */

/**
 * \defgroup reg_int_map_2 Reg Int Map 2
 * \{
 */
#define SHAKE2WAKE_INTMAP2_INT_LOW                  ( 1 << 7 )
#define SHAKE2WAKE_INTMAP2_AWAKE                    ( 1 << 6 )
#define SHAKE2WAKE_INTMAP2_INACT                    ( 1 << 5 )
#define SHAKE2WAKE_INTMAP2_ACT                      ( 1 << 4 )
#define SHAKE2WAKE_INTMAP2_FIFO_OVERRUN             ( 1 << 3 )
#define SHAKE2WAKE_INTMAP2_FIFO_WATERMARK           ( 1 << 2 )
#define SHAKE2WAKE_INTMAP2_FIFO_READY               ( 1 << 1 )
#define SHAKE2WAKE_INTMAP2_DATA_READY                 1
/** \} */

/**
 * \defgroup reg_filter_ctl Reg Filter Ctl
 * \{
 */
#define SHAKE2WAKE_FILTER_CTL_RANGE_2_G           ( ( 0 & 0x3 ) << 6 )
#define SHAKE2WAKE_FILTER_CTL_RANGE_4_G           ( ( 1 & 0x3 ) << 6 )
#define SHAKE2WAKE_FILTER_CTL_RANGE_8_G           ( ( 2 & 0x3 ) << 6 )
#define SHAKE2WAKE_FILTER_CTL_RES                   ( 1 << 5 )
#define SHAKE2WAKE_FILTER_CTL_HALF_BW               ( 1 << 4 )
#define SHAKE2WAKE_FILTER_CTL_EXT_SAMPLE            ( 1 << 3 )
#define SHAKE2WAKE_FILTER_CTL_ODR_12_5              ( 0 & 0x07 )
#define SHAKE2WAKE_FILTER_CTL_ODR_25                ( 1 & 0x07 )
#define SHAKE2WAKE_FILTER_CTL_ODR_50                ( 2 & 0x07 )
#define SHAKE2WAKE_FILTER_CTL_ODR_100               ( 3 & 0x07 )
#define SHAKE2WAKE_FILTER_CTL_ODR_200               ( 4 & 0x07 )
#define SHAKE2WAKE_FILTER_CTL_ODR_400               ( 7 & 0x07 )
/** \} */

/**
 * \defgroup reg_power_ctl Reg Power Ctl
 * \{
 */
#define SHAKE2WAKE_POWER_CTL_RES                     ( 1 << 7 )
#define SHAKE2WAKE_POWER_CTL_EXT_CLK                 ( 1 << 6 )
#define SHAKE2WAKE_POWER_CTL_LOW_NOISE_MODE_NORMAL   ( ( 0 & 0x03 ) << 4 )
#define SHAKE2WAKE_POWER_CTL_LOW_NOISE_MODE_LOW      ( ( 1 & 0x03 ) << 4 )
#define SHAKE2WAKE_POWER_CTL_LOW_NOISE_MODE_ULTRALOW ( ( 2 & 0x03 ) << 4 )
#define SHAKE2WAKE_POWER_CTL_WAKEUP                  ( 1 << 3 )
#define SHAKE2WAKE_POWER_CTL_AUTOSLEEP               ( 1 << 2 )
#define SHAKE2WAKE_POWER_CTL_MEASURE_STD_BY          ( 0x00 )
#define SHAKE2WAKE_POWER_CTL_MEASURE_MODE            ( 0x02 )
/** \} */

/**
 * \defgroup reg_self_test Reg Self Test
 * \{
 */
#define SHAKE2WAKE_SELF_TEST_ST                        1
/** \} */

/**
 * \defgroup device_information Device Information
 * \{
 */
#define SHAKE2WAKE_DEVICE_AD                           0xAD
#define SHAKE2WAKE_DEVICE_MST                          0x1D
#define SHAKE2WAKE_PART_ID                             0xF2
/** \} */

/**
 * \defgroup reset_settings Reset Settings
 * \{
 */
#define SHAKE2WAKE_RESET_KEY                           0x52
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
    spi_master_t spi;
    pin_name_t chip_select;

} shake2wake_t;

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
    pin_name_t int_pin;

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} shake2wake_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void shake2wake_cfg_setup ( shake2wake_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param shake2wake Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t shake2wake_init ( shake2wake_t *ctx, shake2wake_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for Shake2Wake Click.
 */
void shake2wake_default_cfg ( shake2wake_t *ctx );

/**
 * @brief Read one byte function.
 *
 * @param ctx          Click object.
 * @param rd_addr      8-bit data that represents an address of a register.
 *
 * @details This function is used to read single byte from an address specified register.
 */
uint8_t shake2wake_read_byte ( shake2wake_t *ctx, uint8_t rd_addr );

/**
 * @brief Write one byte function.
 *
 * @param ctx          Click object.
 * @param wr_addr      8-bit data that represents an address of a register.
 * @param wr_val       8-bit data that that will be written into a register.
 *
 * @details This function is used to write single byte to an address specified register.
 */
void shake2wake_write_byte ( shake2wake_t *ctx, uint8_t wr_addr, uint8_t wr_val );

/**
 * @brief Write two bytes function.
 *
 * @param ctx           Click object.
 * @param reg_addr      8-bit data that represents an address of a register.
 * @param reg_val       16-bit data that that will be written into registers.
 * @param cnt           Number of bytes to be written.
 *
 * @details This function is used to write up to two bytes of data to an address specified register.
 */
void shake2wake_write_two_byte ( shake2wake_t *ctx, uint8_t reg_addr, uint16_t reg_val, uint8_t cnt );

/**
 * @brief Read miltiple bytes function.
 *
 * @param ctx           Click object.
 * @param reg_addr      8-bit data that represents an address of a register.
 * @param prd_data      8-bit data that that will be read from registers.
 * @param cnt           16-bit value that represents number of bytes to be written.
 *
 * @details This function is used to read multiple registers.
 */
void shake2wake_read_multiple_byte ( shake2wake_t *ctx, uint8_t reg_addr, uint8_t *prd_data, uint8_t cnt );

/**
 * @brief FIFO read function.
 *
 * @param ctx         Click object.
 * @param p_buff      8-bit data that that will be read from registers.
 * @param cnt         16-bit value that represents number of bytes to be read from FIFO register.
 *
 * @details This function is used to burst read data from FIFO register.
 */
void shake2wake_fifo_read ( shake2wake_t *ctx, uint8_t *p_buff, uint16_t cnt );

/**
 * @brief Read DEVID_AD register function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to read device's DEVID_AD register.
 */
uint8_t shake2wake_read_dev_id_ad ( shake2wake_t *ctx );

/**
 * @brief Read DEVID_MST register function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to read device's DEVID_MST register.
 */
uint8_t shake2wake_read_dev_id_mst ( shake2wake_t *ctx );

/**
 * @brief Read part ID register function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to read device's part ID register.
 */
uint8_t shake2wake_read_part_id ( shake2wake_t *ctx );

/**
 * @brief Read silicon revision register function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to read device's silicon revision register.
 */
uint8_t shake2wake_read_revision ( shake2wake_t *ctx );

/**
 * @brief Software reset function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to perform software reset.
 */
void shake2wake_soft_reset ( shake2wake_t *ctx );

/**
 * @brief Read status register function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to read status register.
 */
uint8_t shake2wake_read_status ( shake2wake_t *ctx );

/**
 * @brief Read fifo entries registers function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to read the number of valid data samples present in the FIFO buffer.
 */
uint16_t shake2wake_read_fifo_ent ( shake2wake_t *ctx );

/**
 * @brief Get low resolution raw accelerometer data function.
 *
 * @param ctx           Click object.
 * @param x_val         12-bit value that represents the x-axis acceleration data.
 * @param y_val         12-bit value that represents the y-axis acceleration data.
 * @param z_val         12-bit value that represents the z-axis acceleration data.
 *
 * @details This function is used to read 8-bit acceleration data per axis.
 */
void shake2wake_get_lo_res_raw_data ( shake2wake_t *ctx, int8_t *x_val, int8_t *y_val, int8_t *z_val );

/**
 * @brief Get raw accelerometer data function.
 *
 * @param ctx           Click object.
 * @param x_val         12-bit value that represents the x-axis acceleration data.
 * @param y_val         12-bit value that represents the y-axis acceleration data.
 * @param z_val         12-bit value that represents the z-axis acceleration data.
 *
 * @details This function is used to read the 3-axis raw data from the accelerometer.
 */
void shake2wake_get_raw_data ( shake2wake_t *ctx, int16_t *x_val, int16_t *y_val, int16_t *z_val );

/**
 * @brief Read temperature function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to read temperature from an internal sensor.
 */
float shake2wake_read_temperature ( shake2wake_t *ctx );

/**
 * @brief Stand by function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to put the device into stand by mode.
 */
void shake2wake_stand_by_mode ( shake2wake_t *ctx );

/**
 * @brief Measure mode function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to put the device into Measure mode.
 */
void shake2wake_measure_mode ( shake2wake_t *ctx );

/**
 * @brief Auto-sleep mode function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to enable the Auto-sleep functionality.
 */
void shake2wake_auto_sleep_mode ( shake2wake_t *ctx );

/**
 * @brief Wake up function.
 *
 * @param ctx         Click object.
 *
 * @details This function is used to wake up the device.
 */
void shake2wake_wake_up ( shake2wake_t *ctx );

/**
 * @brief Set Low Noise Mode function.
 *
 * @param ctx          Click object.
 * @param low_noise    8-bit data representing the low noise settings.
 *
 * @details This function is used to set power vs noise tradeoff.
 */
void shake2wake_set_low_noise_mode ( shake2wake_t *ctx, uint8_t low_noise );

/**
 * @brief Enable external clock function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to enable an external clock.
 */
void shake2wake_extern_clk ( shake2wake_t *ctx );

/**
 * @brief Select measurement range function.
 *
 * @param ctx          Click object.
 * @param range        8-bit data representing the range.
 *
 * @details This function is used to set the range.
 */
void shake2wake_set_range ( shake2wake_t *ctx, uint8_t range );

/**
 * @brief Select halved bandwidth function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to select halved bandwidth.
 */
void shake2wake_sel_hal_bandw ( shake2wake_t *ctx );

/**
 * @brief External sampling trigger function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to enable an external sampling trigger.
 */
void shake2wake_set_ext_samp_trg ( shake2wake_t *ctx );

/**
 * @brief Select output data rate function.
 *
 * @param ctx          Click object.
 * @param odr          8-bit data representing the output data rate.
 *
 * @details This function is used to select output data rate.
 */
void shake2wake_set_out_data_rate ( shake2wake_t *ctx, uint8_t odr );

/**
 * @brief Get accelerometer data in "g" function.
 *
 * @param ctx           Click object.
 * @param x_val         Float value that represents the x-axis acceleration data converted it to g
 * @param y_val         Float value that represents the y-axis acceleration data converted it to g
 * @param z_val         Float value that represents the z-axis acceleration data converted it to g
 *
 * @details This function is used to read the 3-axis raw data from the accelerometer and converts it to g.
 */
void shake2wake_get_data_g ( shake2wake_t *ctx, float *x_val, float *y_val, float *z_val );

/**
 * @brief Set FIFO Above Half function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to set the above half functionality.
 */
void shake2wake_set_fifo_above_half ( shake2wake_t *ctx );

/**
 * @brief Store Temperature Data to FIFO function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to store the temperature data into FIFO.
 */
void shake2wake_store_temp ( shake2wake_t *ctx );

/**
 * @brief Enable FIFO and Mode Selection function.
 *
 * @param ctx          Click object.
 * @param mode         8-bit data representing the FIFO mode.
 *
 * @details This function is used to enable FIFO and mode selection.
 */
void shake2wake_set_fifo_mode ( shake2wake_t *ctx, uint8_t mode );

/**
 * @brief Read filter control register function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read contents of the filter control register.
 */
uint8_t shake2wake_read_filter_ctl ( shake2wake_t *ctx );

/**
 * @brief Read power control register function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read contents of the power control register.
 */
uint8_t shake2wake_read_power_ctl ( shake2wake_t *ctx );

/**
 * @brief Read FIFO control register function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read contents of the FIFO control register.
 */
uint8_t shake2wake_read_fifo_ctl ( shake2wake_t *ctx );

/**
 * @brief Read activity/inactivity control register function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read contents of the activity/inactivity control register.
 */
uint8_t shake2wake_read_act_inact_ctl ( shake2wake_t *ctx );

/**
 * @brief Set Activity Enable function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to enables the activity (overthreshold) functionality.
 */
void shake2wake_set_act_enable ( shake2wake_t *ctx );

/**
 * @brief Set Referenced Activity function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to enable the activity detection in referenced mode.
 */
void shake2wake_set_ref_act ( shake2wake_t *ctx );

/**
 * @brief Set Inactivity Enable function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to enables the inactivity (underthreshold) functionality.
 */
void shake2wake_set_inact_enable ( shake2wake_t *ctx );

/**
 * @brief Set Referenced Inactivity function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to enable the inactivity detection in referenced mode.
 */
void shake2wake_set_ref_inact ( shake2wake_t *ctx );

/**
 * @brief Select LINK/LOOP mode function.
 *
 * @param ctx          Click object.
 * @param mode         8-bit data representing the operational mode.
 *
 * @details This function is used to select Default Mode, Linked Mode or Loop Mode.
 */
void shake2wake_sel_link_loop_mode ( shake2wake_t *ctx, uint8_t mode );

/**
 * @brief Set activity threshold function.
 *
 * @param ctx          Click object.
 * @param act_trsh     16-bit data representing the activity threshold.
 *
 * @details This function is used to set the activity threshold.
 */
void shake2wake_set_act_trsh ( shake2wake_t *ctx, uint16_t act_trsh );

/**
 * @brief Read activity threshold function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read the activity threshold.
 */
int16_t shake2wake_read_act_trsh ( shake2wake_t *ctx );

/**
 * @brief Set activity time function.
 *
 * @param ctx          Click object.
 * @param ac_time      8-bit data representing the activity time.
 *
 * @details This function is used to set activity time.
 */
void shake2wake_set_act_time ( shake2wake_t *ctx, uint8_t ac_time );

/**
 * @brief Read activity time function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read the activity time register.
 */
uint8_t shake2wake_read_act_time ( shake2wake_t *ctx );

/**
 * @brief Set inactivity threshold function.
 *
 * @param ctx             Click object.
 * @param inact_trsh      16-bit data representing the inactivity threshold.
 *
 * @details This function is used to set the inactivity threshold.
 */
void shake2wake_set_inact_trsh ( shake2wake_t *ctx, uint16_t inact_trsh );

/**
 * @brief Read inactivity threshold function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read the inactivity threshold.
 */
int16_t shake2wake_read_inact_trsh ( shake2wake_t *ctx );

/**
 * @brief Set inactivity time function.
 *
 * @param ctx             Click object.
 * @param inac_time       8-bit data representing the inactivity time.
 *
 * @details This function is used to set inactivity time.
 */
void shake2wake_set_inact_time ( shake2wake_t *ctx, uint16_t inac_time );

/**
 * @brief Read inactivity time function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read the inactivity time register.
 */
uint16_t shake2wake_read_inact_time ( shake2wake_t *ctx );

/**
 * @brief Write INT1 function map function.
 *
 * @param ctx             Click object.
 * @param wr_data         8-bit user defined data to be written into a register.
 *
 * @details This function is used to configure the INT1 interrupt pin.
 */
void shake2wake_write_int_1_map ( shake2wake_t *ctx, uint8_t wr_data );

/**
 * @brief Read INT1 function map function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read configuration of the INT1 interrupt pin.
 */
uint8_t shake2wake_read_int_1_map ( shake2wake_t *ctx );

/**
 * @brief Write INT2 function map function.
 *
 * @param ctx             Click object.
 * @param wr_data         8-bit user defined data to be written into a register.
 *
 * @details This function is used to configure the INT2 interrupt pin.
 */
void shake2wake_write_int_2_map ( shake2wake_t *ctx, uint8_t wr_data );

/**
 * @brief Read INT2 function map function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read configuration of the INT2 interrupt pin.
 */
uint8_t shake2wake_read_int_2_map ( shake2wake_t *ctx );

/**
 * @brief Write FIFO samples function.
 *
 * @param ctx          Click object.
 * @param samp         8-bit value specifies the number of samples to store in the FIFO.
 *
 * @details This function is used to specifie the number of samples to store in the FIFO.
 */
void shake2wake_write_fifo_samp ( shake2wake_t *ctx, uint8_t samp );

/**
 * @brief Read FIFO samples function.
 *
 * @param ctx          Click object.
 *
 * @details This function is used to read the specified number of samples stored in the FIFO.
 */
uint8_t shake2wake_read_fifo_samp ( shake2wake_t *ctx );

/**
 * @brief Get Interrupt state function.
 *
 * @param ctx          Click object.
 *
 * @details This function checks the state of the interrupt pin.
 */
uint8_t shake2wake_check_int ( shake2wake_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SHAKE2WAKE_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file stepper15.h
 * @brief This file contains API for Stepper 15 Click Driver.
 */

#ifndef STEPPER15_H
#define STEPPER15_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
    

/*!
 * @addtogroup stepper15 Stepper 15 Click Driver
 * @brief API for configuring and manipulating Stepper 15 Click driver.
 * @{
 */

/**
 * @defgroup stepper15_reg Stepper 15 Registers List
 * @brief List of registers of Stepper 15 Click driver.
 */

/**
 * @addtogroup stepper15_reg
 * @{
 */

/**
 * @brief Stepper 15 description PCA9538A register.
 * @details Specified PCA9538A register for description of Stepper 15 Click driver.
 */
#define STEPPER15_REG_INPUT_PORT                               0x00
#define STEPPER15_REG_OUTPUT_PORT                              0x01
#define STEPPER15_REG_POLARITY_INVERSION                       0x02
#define STEPPER15_REG_CONFIGURATION                            0x03

/**
 * @brief Stepper 15 description DRV8889A-Q1 register.
 * @details Specified DRV8889A-Q1 register for description of Stepper 15 Click driver.
 */
#define STEPPER15_REG_FAULT_STATUS                             0x00
#define STEPPER15_REG_DIAG_STATUS_1                            0x01
#define STEPPER15_REG_DIAG_STATUS_2                            0x02
#define STEPPER15_REG_CTRL_1                                   0x03
#define STEPPER15_REG_CTRL_2                                   0x04
#define STEPPER15_REG_CTRL_3                                   0x05
#define STEPPER15_REG_CTRL_4                                   0x06
#define STEPPER15_REG_CTRL_5                                   0x07
#define STEPPER15_REG_CTRL_6                                   0x08
#define STEPPER15_REG_CTRL_7                                   0x09
#define STEPPER15_REG_CTRL_8                                   0x0A

/*! @} */ // stepper15_reg

/**
 * @defgroup stepper15_set Stepper 15 Registers Settings
 * @brief Settings for registers of Stepper 15 Click driver.
 */

/**
 * @addtogroup stepper15_set
 * @{
 */

/**
 * @brief Stepper 15 direction description setting.
 * @details Specified the direction setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_SET_DIRECTION_BIT_MASK                       0xFB
#define STEPPER15_SET_DIRECTION_CCW                            0x00
#define STEPPER15_SET_DIRECTION_CW                             0x04

/**
 * @brief Stepper 15 work mode description setting.
 * @details Specified the work mode setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_SET_WORK_MODE_BIT_MASK                       0xFE
#define STEPPER15_SET_WORK_MODE_SLEEP                          0x00
#define STEPPER15_SET_WORK_MODE_ENABLE_DEVICE                  0x01

/**
 * @brief Stepper 15 work mode description setting.
 * @details Specified the work mode setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_SET_OUT_MODE_BIT_MASK                        0xFD
#define STEPPER15_SET_OUT_MODE_DEVICE_OUTPUTS_ENABLE           0x00
#define STEPPER15_SET_OUT_MODE_DEVICE_OUTPUTS_DISABLE          0x02

/**
 * @brief Stepper 15 configuration description setting.
 * @details Specified the configuration setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_SET_CONFIG_DEFAULT                           0xF8

/**
 * @brief Stepper 15 IC fault status register description setting.
 * @details Specified the IC fault status register setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_FAULT_ST_OL_MASK                             0x01        
#define STEPPER15_FAULT_ST_OT_MASK                             0x02        
#define STEPPER15_FAULT_ST_STL_SLIP_MASK                       0x04        
#define STEPPER15_FAULT_ST_OCP_MASK                            0x08        
#define STEPPER15_FAULT_ST_CPUV_MASK                           0x10        
#define STEPPER15_FAULT_ST_UVLO_MASK                           0x20        
#define STEPPER15_FAULT_ST_SPI_ERROR_MASK                      0x40        
#define STEPPER15_FAULT_ST_FAULT_MASK                          0x80 

/**
 * @brief Stepper 15 Diagnostic register 1 description setting.
 * @details Specified the diagnostic register 1 setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_DIAG_1_OCP_HS1_A_MASK                        0x01       
#define STEPPER15_DIAG_1_OCP_LS1_A_MASK                        0x02       
#define STEPPER15_DIAG_1_OCP_HS2_A_MASK                        0x04       
#define STEPPER15_DIAG_1_OCP_LS2_A_MASK                        0x08       
#define STEPPER15_DIAG_1_OCP_HS1_B_MASK                        0x10       
#define STEPPER15_DIAG_1_OCP_LS1_B_MASK                        0x20       
#define STEPPER15_DIAG_1_OCP_HS2_B_MASK                        0x40       
#define STEPPER15_DIAG_1_OCP_LS2_B_MASK                        0x80

/**
 * @brief Stepper 15 Diagnostic register 2 description setting.
 * @details Specified the diagnostic register 1 setting 
 * for other faults and warnings setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_DIAG_2_OL_A_MASK                             0x01       
#define STEPPER15_DIAG_2_OL_B_MASK                             0x02       
#define STEPPER15_DIAG_2_SLIP_MASK                             0x04       
#define STEPPER15_DIAG_2_STALL_MASK                            0x08       
#define STEPPER15_DIAG_2_STL_LRN_OK_MASK                       0x10       
#define STEPPER15_DIAG_2_OTS_MASK                              0x20       
#define STEPPER15_DIAG_2_OTW_MASK                              0x40       
#define STEPPER15_DIAG_2_UTW_MASK                              0x80 

/**
 * @brief Stepper 15 CTRL1 register description setting.
 * @details Specified the CTRL1 register, Torque DAC, synchronous rectification, 
 * slew rate setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_CTRL1_SLEW_RATE_MASK                         0x03       
#define STEPPER15_CTRL1_EN_NSR_MASK                            0x04       
#define STEPPER15_CTRL1_RSVD1_MASK                             0x08       
#define STEPPER15_CTRL1_TRQ_DAC_MASK                           0xF0
#define STEPPER15_SET_CTRL1_TRQ_100                            0x00
#define STEPPER15_SET_CTRL1_TRQ_93_75                          0x10
#define STEPPER15_SET_CTRL1_TRQ_87_5                           0x20
#define STEPPER15_SET_CTRL1_TRQ_81_25                          0x30
#define STEPPER15_SET_CTRL1_TRQ_75                             0x40
#define STEPPER15_SET_CTRL1_TRQ_68_75                          0x50
#define STEPPER15_SET_CTRL1_TRQ_62_5                           0x60
#define STEPPER15_SET_CTRL1_TRQ_56_25                          0x70
#define STEPPER15_SET_CTRL1_TRQ_50                             0x80
#define STEPPER15_SET_CTRL1_TRQ_43_75                          0x90
#define STEPPER15_SET_CTRL1_TRQ_37_5                           0xA0
#define STEPPER15_SET_CTRL1_TRQ_31_25                          0xB0
#define STEPPER15_SET_CTRL1_TRQ_25                             0xC0
#define STEPPER15_SET_CTRL1_TRQ_18_75                          0xD0
#define STEPPER15_SET_CTRL1_TRQ_12_5                           0xE0
#define STEPPER15_SET_CTRL1_TRQ_6_25                           0xF0


/**
 * @brief Stepper 15 CTRL2 register description setting.
 * @details Specified the CTRL3 register,  
 * Disable, TOFF, DECAY setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_CTRL2_DECAY_MASK                             0x07       
#define STEPPER15_CTRL2_TOFF_MASK                              0x18       
#define STEPPER15_CTRL2_RSVD2_MASK                             0x60       
#define STEPPER15_CTRL2_DIS_OUT_MASK                           0x80
#define STEPPER15_SET_CTRL2_OUTPUT_ENABLE                      0x00
#define STEPPER15_SET_CTRL2_OUTPUT_DISABLE                     0x80
#define STEPPER15_SET_CTRL2_TOFF_7_us                          0x00
#define STEPPER15_SET_CTRL2_TOFF_16_us                         0x08
#define STEPPER15_SET_CTRL2_TOFF_24_us                         0x10
#define STEPPER15_SET_CTRL2_TOFF_32_us                         0x18
#define STEPPER15_SET_CTRL2_SMART_TUNE_RIPPLE_CTRL             0x07

/**
 * @brief Stepper 15 CTRL3 register description setting.
 * @details Specified the CTRL3 register, 
 * Step, dir, microstep setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_CTRL3_MICROSTEP_MODE_MASK                    0x0F       
#define STEPPER15_CTRL3_SPI_STEP_MASK                          0x10       
#define STEPPER15_CTRL3_SPI_DIR_MASK                           0x20       
#define STEPPER15_CTRL3_STEP_MASK                              0x40       
#define STEPPER15_CTRL3_DIR_MASK                               0x80
#define STEPPER15_SET_SPI_DIR_INPUT_PIN                        0x00
#define STEPPER15_SET_SPI_DIR_SPI                              0x80
#define STEPPER15_SET_SPI_STEP_INPUT_PIN                       0x00
#define STEPPER15_SET_SPI_STEP_SPI                             0x40
#define STEPPER15_SET_CTRL3_SET_MICROSTEP_MODE_FULL_STEP       0x00

/**
 * @brief Stepper 15 CTRL4 register description setting.
 * @details Specified the CTRL4 register, Clear fault, lock, OL, OCP, OTSD, OTW 
 * setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_CTRL4_TW_REP_MASK                            0x01         
#define STEPPER15_CTRL4_OTSD_MODE_MASK                         0x02         
#define STEPPER15_CTRL4_OCP_MODE_MASK                          0x04         
#define STEPPER15_CTRL4_EN_OL_MASK                             0x08         
#define STEPPER15_CTRL4_LOCK_MASK                              0x70         
#define STEPPER15_CTRL4_CLR_FLT_MASK                           0x80
#define STEPPER15_SET_CTRL4_CLR_FLT                            0x80
#define STEPPER15_SET_CTRL4_UNLOCK_ALL_REG                     0x30

/**
 * @brief Stepper 15 CTRL5 register description setting.
 * @details Specified the CTRL5 register, Stall detection configuration setting 
 * for description of Stepper 15 Click driver.
 */
#define STEPPER15_CTRL5_SLIP_REP_MASK                          0x01      
#define STEPPER15_CTRL5_EN_SLIP_MASK                           0x02      
#define STEPPER15_CTRL5_EN_STLFCHG_MASK                        0x04      
#define STEPPER15_CTRL5_STL_REP_MASK                           0x08
#define STEPPER15_SET_CTRL5_REPORTED_ON_FAULT                  0x08
                                                              
/**                                                           
 * @brief Stepper 15 CTRL6 register description setting.      
 * @details Specified the CTRL6 register, Stall threshold     
 * for description of Stepper 15 Click driver.                
 */                                                           
#define STEPPER15_CTRL6_STALL_TH_MASK                          0xFF
                                                              
/**                                                           
 * @brief Stepper 15 CTRL7 register description setting.      
 * @details Specified the CTRL7 register, Torque count        
 * for description of Stepper 15 Click driver.                
 */                                                           
#define STEPPER15_CTRL7_STALL_TH_MASK                          0xFF

/**
 * @brief Stepper 15 CTRL8 register description setting.
 * @details Specified the CTRL8 register, UTW and Rev ID
 * for description of Stepper 15 Click driver.
 */
#define STEPPER15_CTRL8_REV_ID_MASK                            0x0F         
#define STEPPER15_CTRL8_STL_UPDATE_MODE_MASK                   0x10         
#define STEPPER15_CTRL8_UTW_REP_MASK                           0x20         
#define STEPPER15_CTRL8_RSVD3_MASK                             0xC0 

/**
 * @brief Stepper 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 15 Click driver.
 */
#define STEPPER15_SET_DEV_ADDR                                 0x70

/*! @} */ // stepper15_set

/**
 * @addtogroup direction
 * @{
 */

/**
 * @brief Stepper 15 direction description setting.
 * @details Specified the direction setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_DIRECTION_COUNTERCLOCKWISE                      0
#define STEPPER15_DIRECTION_CLOCKWISE                             1

/*! @} */ // direction

/**
 * @addtogroup work_mode
 * @{
 */

/**
 * @brief Stepper 15 work mode description setting.
 * @details Specified the work mode setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_WORK_MODE_SLEEP                                 0
#define STEPPER15_WORK_MODE_ENABLE_DEVICE                         1

/*! @} */ // work_mode

/**
 * @addtogroup output_mode
 * @{
 */

/**
 * @brief Stepper 15 outpu mode description setting.
 * @details Specified the output mode setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_OUTPUT_MODE_OUTPUTS_DISABLE                     0
#define STEPPER15_OUTPUT_MODE_OUTPUTS_ENABLE                      1

/*! @} */ // output_mode

/**
 * @addtogroup fault_condition
 * @{
 */

/**
 * @brief Stepper 15 fault condition state description setting.
 * @details Specified the fault condition state setting for description of Stepper 15 Click driver.
 */
#define STEPPER15_FAULT_CONDITION                                 0
#define STEPPER15_CORRECT_CONDITION                               1

/*! @} */ // fault_condition

/**
 * @defgroup stepper15_map Stepper 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 15 Click driver.
 */

/**
 * @addtogroup stepper15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 15 Click to the selected MikroBUS.
 */
#define STEPPER15_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper15_map
/*! @} */ // stepper15

/**
 * @brief Stepper 15 Click driver selector.
 * @details Selects target driver interface of Stepper 15 Click driver.
 */
typedef enum
{
    STEPPER15_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    STEPPER15_DRV_SEL_I2C       /**< I2C driver descriptor. */

} stepper15_drv_t;

/**
 * @brief Stepper 15 Click driver interface.
 * @details Definition of driver interface of Stepper 15 Click driver.
 */
typedef err_t ( *stepper15_master_io_t )( struct stepper15_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Stepper 15 Click context object.
 * @details Context object definition of Stepper 15 Click driver.
 */
typedef struct stepper15_s
{
    digital_out_t  rst;              /**< Reset pin.      */
    digital_out_t  pwm;              /**< Step pin.       */
                                     
    digital_in_t  int_pin;           /**< Interrupt pin. */

    i2c_master_t  i2c;               /**< I2C driver object. */
    spi_master_t  spi;               /**< SPI driver object. */

    uint8_t     slave_address;       /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;         /**< Chip select pin descriptor (used for SPI driver). */
    stepper15_drv_t  drv_sel;        /**< Master driver interface selector. */

    stepper15_master_io_t  write_f;  /**< Master write function. */
    stepper15_master_io_t  read_f;   /**< Master read function. */

} stepper15_t;

/**
 * @brief Stepper 15 Click configuration object.
 * @details Configuration object definition of Stepper 15 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    pin_name_t  rst;        /**< Reset pin. */
    pin_name_t  pwm;        /**< Step pin. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    stepper15_drv_t  drv_sel;                          /**< Master driver interface selector. */

} stepper15_cfg_t;

/**
 * @brief Stepper 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER15_OK = 0,
    STEPPER15_ERROR = -1

} stepper15_return_value_t;

/*!
 * @addtogroup stepper15 Stepper 15 Click Driver
 * @brief API for configuring and manipulating Stepper 15 Click driver.
 * @{
 */

/**
 * @brief Stepper 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper15_cfg_setup ( stepper15_cfg_t *cfg );

/**
 * @brief Stepper 15 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #stepper15_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #stepper15_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void stepper15_drv_interface_selection ( stepper15_cfg_t *cfg, stepper15_drv_t drv_sel );

/**
 * @brief Stepper 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_init ( stepper15_t *ctx, stepper15_cfg_t *cfg );

/**
 * @brief Stepper 15 default configuration function.
 * @details This function executes a default configuration of Stepper 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper15_default_cfg ( stepper15_t *ctx );

/**
 * @brief Stepper 15 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_generic_write ( stepper15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Stepper 15 reset function.
 * @details This function performs hardware reset of the
 * PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void stepper15_reset ( stepper15_t *ctx );

/**
 * @brief Stepper 15 motor stop function.
 * @details This function performs stop the stepper motor of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void stepper15_motor_stop ( stepper15_t *ctx );

/**
 * @brief Stepper 15 get interrupt function.
 * @details This function get interrupt flag state of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 * 
 * @note None.
 */
uint8_t stepper15_get_interrupt ( stepper15_t *ctx );

/**
 * @brief Stepper 15 make one step function.
 * @details This function performs make one step of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] step_speed : Step speed ( percent from 1 to 100 ( max speed ) ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_make_one_step ( stepper15_t *ctx, uint8_t step_speed );

/**
 * @brief Stepper 15 set direction function.
 * @details This function selects the direction of movement of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] direction : 
 *         @li @c 0 ( STEPPER15_DIRECTION_COUNTERCLOCKWISE ) - Clockwise motion,
 *         @li @c 1 ( STEPPER15_DIRECTION_CLOCKWISE )        - Counterclockwise motion.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_set_direction ( stepper15_t *ctx, uint8_t direction );

/**
 * @brief Stepper 15 set work mode function.
 * @details This function set the work mode of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] work_mode : 
 *         @li @c 0 ( STEPPER15_WORK_MODE_SLEEP )         - Sleep mode,
 *         @li @c 1 ( STEPPER15_WORK_MODE_ENABLE_DEVICE ) - Enable device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_set_work_mode ( stepper15_t *ctx, uint8_t work_mode );

/**
 * @brief Stepper 15 set output mode function.
 * @details This function set the output mode of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] output_mode : 
 *         @li @c 0 ( STEPPER15_OUTPUT_MODE_OUTPUTS_DISABLE ) - Disable device outputs,
 *         @li @c 1 ( STEPPER15_OUTPUT_MODE_OUTPUTS_ENABLE )  - Enable device outputs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_set_output_mode ( stepper15_t *ctx, uint8_t output_mode );

/**
 * @brief Stepper 15 set torque DAC function.
 * @details This function set torque DAC to allows for the controller 
 * to scale the output current through SPI without needing to scale the Vref of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] trq_data :  
 *         @li @c 0x00 ( STEPPER15_SET_CTRL1_TRQ_100 )   - Current scalar ( TRQ ) of 100%,
 *         @li @c 0x10 ( STEPPER15_SET_CTRL1_TRQ_93_75 ) - Current scalar ( TRQ ) of 93.75%,
 *         @li @c 0x20 ( STEPPER15_SET_CTRL1_TRQ_87_5 )  - Current scalar ( TRQ ) of 87.5%,
 *         @li @c 0x30 ( STEPPER15_SET_CTRL1_TRQ_81_25 ) - Current scalar ( TRQ ) of 81.25%,
 *         @li @c 0x40 ( STEPPER15_SET_CTRL1_TRQ_75 )    - Current scalar ( TRQ ) of 75%,
 *         @li @c 0x50 ( STEPPER15_SET_CTRL1_TRQ_68_75 ) - Current scalar ( TRQ ) of 68.75%,
 *         @li @c 0x60 ( STEPPER15_SET_CTRL1_TRQ_62_5 )  - Current scalar ( TRQ ) of 62.5%,
 *         @li @c 0x70 ( STEPPER15_SET_CTRL1_TRQ_56_25 ) - Current scalar ( TRQ ) of 56.25%,
 *         @li @c 0x80 ( STEPPER15_SET_CTRL1_TRQ_50 )    - Current scalar ( TRQ ) of 50%,
 *         @li @c 0x90 ( STEPPER15_SET_CTRL1_TRQ_43_75 ) - Current scalar ( TRQ ) of 43.75%,
 *         @li @c 0xA0 ( STEPPER15_SET_CTRL1_TRQ_37_5 )  - Current scalar ( TRQ ) of 37.5%,
 *         @li @c 0xB0 ( STEPPER15_SET_CTRL1_TRQ_31_25 ) - Current scalar ( TRQ ) of 31.25%,
 *         @li @c 0xC0 ( STEPPER15_SET_CTRL1_TRQ_25 )    - Current scalar ( TRQ ) of 25%,
 *         @li @c 0xD0 ( STEPPER15_SET_CTRL1_TRQ_18_75 ) - Current scalar ( TRQ ) of 18.75%,
 *         @li @c 0xE0 ( STEPPER15_SET_CTRL1_TRQ_12_5 )  - Current scalar ( TRQ ) of 12.5%,
 *         @li @c 0xF0 ( STEPPER15_SET_CTRL1_TRQ_6_25 )  - Current scalar ( TRQ ) of 6.25%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_set_torque_dac ( stepper15_t *ctx, uint8_t trq_data );

/**
 * @brief Stepper 15 set counts function.
 * @details This function set the counts of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] counts : Counts 0 - 255.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_set_counts ( stepper15_t *ctx, uint8_t counts );

/**
 * @brief Stepper 15 get fault condition function.
 * @details This function get fault condition of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @return @li @c 0 - Fault condition,
 *         @li @c 1 - Correct condition.
 * 
 * @note None.
 */
uint8_t stepper15_get_fault_condition ( stepper15_t *ctx );

/**
 * @brief Stepper 15 step by angle function.
 * @details This function turn the stepper motor to the desired angle of the
 * DRV8889A-Q1 Automotive Stepper Driver with Integrated Current
 * Sense, 1/256 Micro-Stepping, and Stall Detection
 * on the Stepper 15 click board™.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] step_speed : Step speed ( percent from 1 to 100 ( max speed ) ).
 * @param[in] angle : Angle of rotation.
 * @param[in] step_360 : Number of steps per full circle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper15_step_by_angle ( stepper15_t *ctx, uint8_t step_speed, float angle, uint16_t step_360 );



#ifdef __cplusplus
}
#endif
#endif // STEPPER15_H

/*! @} */ // stepper15

// ------------------------------------------------------------------------ END

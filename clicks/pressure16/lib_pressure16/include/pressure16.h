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
 * @file pressure16.h
 * @brief This file contains API for Pressure 16 Click Driver.
 */

#ifndef PRESSURE16_H
#define PRESSURE16_H

#ifdef __cplusplus
extern "C"{
#endif

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
       

/*!
 * @addtogroup pressure16 Pressure 16 Click Driver
 * @brief API for configuring and manipulating Pressure 16 Click driver.
 * @{
 */

/**
 * @defgroup pressure16_reg Pressure 16 Registers List
 * @brief List of registers of Pressure 16 Click driver.
 */

/**
 * @addtogroup pressure16_reg
 * @{
 */

/**
 * @brief Pressure 16 description register.
 * @details Specified register for description of Pressure 16 Click driver.
 */
#define PRESSURE16_REG_INT_CFG                           0x0B
#define PRESSURE16_REG_THR_P_L                           0x0C
#define PRESSURE16_REG_THR_P_H                           0x0D
#define PRESSURE16_REG_INTERFACE_CTRL                    0x0E
#define PRESSURE16_REG_DEVICE_ID                         0x0F
#define PRESSURE16_REG_CTRL_1                            0x10
#define PRESSURE16_REG_CTRL_2                            0x11
#define PRESSURE16_REG_CTRL_3                            0x12
#define PRESSURE16_REG_FIFO_CTRL                         0x13
#define PRESSURE16_REG_FIFO_WTM                          0x14
#define PRESSURE16_REG_REF_P_L                           0x15
#define PRESSURE16_REG_REF_P_H                           0x16
#define PRESSURE16_REG_OPC_P_L                           0x18
#define PRESSURE16_REG_OPC_P_H                           0x19
#define PRESSURE16_REG_INT_SOURCE                        0x24
#define PRESSURE16_REG_FIFO_STATUS_1                     0x25
#define PRESSURE16_REG_FIFO_STATUS_2                     0x26
#define PRESSURE16_REG_STATUS                            0x27
#define PRESSURE16_REG_DATA_P_XL                         0x28
#define PRESSURE16_REG_DATA_P_L                          0x29
#define PRESSURE16_REG_DATA_P_H                          0x2A
#define PRESSURE16_REG_DATA_T_L                          0x2B
#define PRESSURE16_REG_DATA_T_H                          0x2C
#define PRESSURE16_REG_FIFO_DATA_P_XL                    0x78
#define PRESSURE16_REG_FIFO_DATA_P_L                     0x79
#define PRESSURE16_REG_FIFO_DATA_P_H                     0x7A
#define PRESSURE16_REG_FIFO_DATA_T_L                     0x7B
#define PRESSURE16_REG_FIFO_DATA_T_H                     0x7C

/*! @} */ // pressure16_reg

/**
 * @defgroup pressure16_set Pressure 16 Registers Settings
 * @brief Settings for registers of Pressure 16 Click driver.
 */

/**
 * @addtogroup pressure16_set
 * @{
 */

/**
 * @brief Pressure 16 description setting.
 * @details Specified setting for description of Pressure 16 Click driver.
 */
#define PRESSURE16_SET_CTRL_ODR_POWER_DOWN_MODE          0x00
#define PRESSURE16_SET_CTRL_ODR_1                        0x01  
#define PRESSURE16_SET_CTRL_ODR_10                       0x02  
#define PRESSURE16_SET_CTRL_ODR_25                       0x03  
#define PRESSURE16_SET_CTRL_ODR_50                       0x04
#define PRESSURE16_SET_CTRL_ODR_75                       0x05  
#define PRESSURE16_SET_CTRL_ODR_100                      0x06  
#define PRESSURE16_SET_CTRL_ODR_200                      0x07

#define PRESSURE16_SET_CTRL_LPFP_DISABLE                 0x00
#define PRESSURE16_SET_CTRL_LPFP_ENABLE                  0x01

#define PRESSURE16_SET_CTRL_LPFP_DISABLE                 0x00
#define PRESSURE16_SET_CTRL_LPFP_ENABLE                  0x01
    
#define PRESSURE16_SET_BDU_DATA_UPDATES_CONTINUOUS       0x00
#define PRESSURE16_SET_BDU_DATA_NOT_UPDATES_UNTIL_READ   0x01
    
#define PRESSURE16_SET_SIM_SPI_4_WIRE_INTERFACE          0x00
#define PRESSURE16_SET_SIM_SPI_3_WIRE_INTERFACE          0x01
    
#define PRESSURE16_SET_BOOT_NORMAL_OPERATION             0x00
#define PRESSURE16_SET_BOOT_REBOOT_MEMORY_CONTENT        0x01
    
#define PRESSURE16_SET_INT_H_L_INTERRUPT_ACTIVE_HIGH     0x00
#define PRESSURE16_SET_INT_H_L_INTERRUPT_ACTIVE_LOW      0x01
    
#define PRESSURE16_SET_PP_OD_PUSH_PULL                   0x00
#define PRESSURE16_SET_PP_OD_OPEN_DRAIN                  0x01
    
#define PRESSURE16_SET_IF_ADD_INC_DISABLED               0x00
#define PRESSURE16_SET_IF_ADD_INC_ENABLED                0x01
    
#define PRESSURE16_SET_LOW_NOISE_ENABLE_LOW_POWER_MODE   0x00
#define PRESSURE16_SET_LOW_NOISE_ENABLE_LOW_NOISE_MODE   0x01
    
#define PRESSURE16_SET_ONE_SHOT_NORMAL_OPERATION         0x00
#define PRESSURE16_SET_ONE_SHOT_NEW_DATA_SET_IS_ACQUIRED 0x01
    
#define PRESSURE16_SET_INT_F_FULL_DISABLED               0x00
#define PRESSURE16_SET_INT_F_FULL_ENABLED                0x01
    
#define PRESSURE16_SET_INT_F_WTM_DISABLED                0x00
#define PRESSURE16_SET_INT_F_WTM_ENABLED                 0x01
    
#define PRESSURE16_SET_INT_F_OVR_DISABLED                0x00
#define PRESSURE16_SET_INT_F_OVR_ENABLED                 0x01
    
#define PRESSURE16_SET_DRDY_DISABLED                     0x00
#define PRESSURE16_SET_DRDY_ENABLED                      0x01
    
#define PRESSURE16_SET_INT_S_DATA_SIGNAL                 0x00
#define PRESSURE16_SET_INT_S_PRESSURE_HIGH_EVENT         0x01
#define PRESSURE16_SET_INT_S_PRESSURE_LOW_EVENT          0x02
#define PRESSURE16_SET_INT_S_PRESSURE_LOW_HIGH_EVENT     0x03

#define PRESSURE16_SET_INT_CFG_AUTOREFP_DISABLED         0x00
#define PRESSURE16_SET_INT_CFG_AUTOREFP_ENABLED          0x01

#define PRESSURE16_SET_INT_CFG_RESET_ARP_NORMAL_MODE     0x00
#define PRESSURE16_SET_INT_CFG_RESET_ARP_RST_AUTOREFP    0x01

#define PRESSURE16_SET_INT_CFG_AUTOZERO_DISABLED         0x00
#define PRESSURE16_SET_INT_CFG_AUTOZERO_ENABLED          0x01

#define PRESSURE16_SET_INT_CFG_AUTOZERO_NORMAL_MODE      0x00
#define PRESSURE16_SET_INT_CFG_RST_AUTOZERO              0x01

#define PRESSURE16_SET_INT_CFG_DIFF_EN_DISABLED          0x00
#define PRESSURE16_SET_INT_CFG_DIFF_EN_ENABLED           0x01

#define PRESSURE16_SET_INT_CFG_LIR_INT_IS_NOT_LATCHED    0x00
#define PRESSURE16_SET_INT_CFG_LIR_INT_IS_LATCHED        0x01

#define PRESSURE16_SET_INT_CFG_PLE_INT_IS_INACTIVE       0x00
#define PRESSURE16_SET_INT_CFG_PLE_INT_IS_ACTIVE         0x01

#define PRESSURE16_SET_INT_CFG_PHE_INT_IS_INACTIVE       0x00
#define PRESSURE16_SET_INT_CFG_PHE_INT_IS_ACTIVE         0x01

#define PRESSURE16_SET_SW_RESET_BIT_MASK                 0x04

/**
 * @brief Pressure 16 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 16 Click driver.
 */
#define PRESSURE16_SET_DEV_ADDR_GND                      0x5C
#define PRESSURE16_SET_DEV_ADDR_VCC                      0x5D

/**
 * @brief Pressure 16 device ID value.
 * @details Specified setting for device device ID value of
 * Pressure 16 Click driver.
 */
#define PRESSURE16_DEVICE_ID                             0xB3

/*! @} */ // pressure16_set

/**
 * @defgroup pressure16_map Pressure 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 16 Click driver.
 */

/**
 * @addtogroup pressure16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 16 Click to the selected MikroBUS.
 */
#define PRESSURE16_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure16_map
/*! @} */ // pressure16

/**
 * @brief Pressure 16 Click driver selector.
 * @details Selects target driver interface of Pressure 16 Click driver.
 */
typedef enum
{
    PRESSURE16_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    PRESSURE16_DRV_SEL_I2C       /**< I2C driver descriptor. */

} pressure16_drv_t;

/**
 * @brief Pressure 16 Click driver interface.
 * @details Definition of driver interface of Pressure 16 Click driver.
 */
typedef err_t ( *pressure16_master_io_t )( struct pressure16_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Pressure 16 Click context object.
 * @details Context object definition of Pressure 16 Click driver.
 */
typedef struct pressure16_s
{
    digital_in_t  int_pin;             /**< Interrupt pin. */

    i2c_master_t  i2c;                 /**< I2C driver object. */
    spi_master_t  spi;                 /**< SPI driver object. */

    uint8_t     slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    pressure16_drv_t  drv_sel;         /**< Master driver interface selector. */

    pressure16_master_io_t  write_f;   /**< Master write function. */
    pressure16_master_io_t  read_f;    /**< Master read function. */

} pressure16_t;

/**
 * @brief Pressure 16 Click configuration object.
 * @details Configuration object definition of Pressure 16 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    pressure16_drv_t  drv_sel;                   /**< Master driver interface selector. */

} pressure16_cfg_t;

/**
 * @brief Pressure 16 Click Interrupt configuration object.
 * @details Interrupt configuration object definition of Pressure 16 Click driver.
 */
typedef struct
{
   
    uint8_t auto_refp;                              
    uint8_t reset_arp;
    uint8_t auto_zero;
    uint8_t reset_az;
    uint8_t diff_en;
    uint8_t lir;
    uint8_t ple;
    uint8_t phe;

} pressure16_int_cfg_t;

/**
 * @brief Pressure 16 Click Control configuration object.
 * @details Control configuration object definition of Pressure 16 Click driver.
 */
typedef struct
{
   
    uint8_t odr;                              
    uint8_t en_lpfp;
    uint8_t lpfp_cfg;
    uint8_t bdu;
    uint8_t sim;
    uint8_t boot;
    uint8_t int_h_l;
    uint8_t pp_od;
    uint8_t if_add_inc;
    uint8_t low_noise_en;
    uint8_t one_shot;
    uint8_t int_f_full;
    uint8_t int_f_wtm;
    uint8_t int_f_ovr;
    uint8_t drdy;
    uint8_t int_s;

} pressure16_ctrl_cfg_t;

/**
 * @brief Pressure 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PRESSURE16_OK = 0,
   PRESSURE16_ERROR = -1

} pressure16_return_value_t;

/*!
 * @addtogroup pressure16 Pressure 16 Click Driver
 * @brief API for configuring and manipulating Pressure 16 Click driver.
 * @{
 */

/**
 * @brief Pressure 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure16_cfg_setup ( pressure16_cfg_t *cfg );

/**
 * @brief Pressure 16 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pressure16_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pressure16_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pressure16_drv_interface_selection ( pressure16_cfg_t *cfg, pressure16_drv_t drv_sel );

/**
 * @brief Pressure 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_init ( pressure16_t *ctx, pressure16_cfg_t *cfg );

/**
 * @brief Pressure 16 default configuration function.
 * @details This function executes a default configuration of Pressure 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure16_default_cfg ( pressure16_t *ctx );

/**
 * @brief Pressure 16 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_generic_write ( pressure16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 16 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_generic_read ( pressure16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 16 get device ID function.
 * @details This function reads a device ID from PRESSURE16_REG_DEVICE_ID register address 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[out] dev_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_get_device_id ( pressure16_t *ctx, uint8_t *dev_id );

/**
 * @brief Pressure 16 software reset function.
 * @details This function performs a software reset 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_sw_reset ( pressure16_t *ctx );

/**
 * @brief Pressure 16 set interrupt configuration function.
 * @details This function set interrupt configuration 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] int_cfg_data : Interrupt configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_set_interrupt_config( pressure16_t *ctx, pressure16_int_cfg_t int_cfg_data );

/**
 * @brief Pressure 16 get interrupt configuration function.
 * @details This function get interrupt configuration 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[out] int_cfg_data : Interrupt configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_get_interrupt_config( pressure16_t *ctx, pressure16_int_cfg_t *int_cfg_data );

/**
 * @brief Pressure 16 set control configuration function.
 * @details This function set control configuration 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] ctrl_cfg_data : Control configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_set_ctrl_config( pressure16_t *ctx, pressure16_ctrl_cfg_t ctrl_cfg_data );

/**
 * @brief Pressure 16 get control configuration function.
 * @details This function get control configuration 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[out] ctrl_cfg_data : Control configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_get_ctrl_config( pressure16_t *ctx, pressure16_ctrl_cfg_t *ctrl_cfg_data );

/**
 * @brief Pressure 16 get pressure function.
 * @details This function get pressure data 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data [ mbar ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_get_pressure ( pressure16_t *ctx, float *pressure );

/**
 * @brief Pressure 16 get temperature function.
 * @details This function get temperature data 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data [ degree Celsius ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_get_temperature ( pressure16_t *ctx, float *temperature );

/**
 * @brief Pressure 16 get pressure and temperature function.
 * @details This function get pressure and temperature data 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data [ mbar ].
 * @param[out] temperature : Temperature data [ degree Celsius ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure16_get_press_temp ( pressure16_t *ctx, float *pressure, float *temperature );

/**
 * @brief Pressure 16 get interrupt function.
 * @details This function get interrupt state 
 * of the WSEN-PADS Absolute Pressure Sensor
 * on the Pressure 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @return Interrupt state.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t pressure16_get_interrupt ( pressure16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE16_H

/*! @} */ // pressure16

// ------------------------------------------------------------------------ END

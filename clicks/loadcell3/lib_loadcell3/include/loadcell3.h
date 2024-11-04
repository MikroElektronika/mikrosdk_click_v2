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
 * @file loadcell3.h
 * @brief This file contains API for Load Cell 3 Click Driver.
 */

#ifndef LOADCELL3_H
#define LOADCELL3_H

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

    
/*!
 * @addtogroup loadcell3 Load Cell 3 Click Driver
 * @brief API for configuring and manipulating Load Cell 3 Click driver.
 * @{
 */

/**
 * @defgroup loadcell3_reg Load Cell 3 Registers List
 * @brief List of registers of Load Cell 3 Click driver.
 */

/**
 * @addtogroup loadcell3_reg
 * @{
 */

/**
 * @brief Load Cell 3 description register.
 * @details Specified register for description of Load Cell 3 Click driver.
 */
#define LOADCELL3_REG_TEST_MICRO_INTERFACE_CONTROL        0x0C
#define LOADCELL3_REG_TEST_PADC_DATA_1                    0x10
#define LOADCELL3_REG_TEST_PADC_DATA_2                    0x11
#define LOADCELL3_REG_TEST_TADC_DATA_1                    0x14
#define LOADCELL3_REG_TEST_TADC_DATA_2                    0x15

#define LOADCELL3_REG_CTRL_STATUS_PSMON_1                 0x58
#define LOADCELL3_REG_CTRL_STATUS_AFEDIAG                 0x5A 
#define LOADCELL3_REG_CTRL_STATUS_P_GAIN_SELECT           0x47
#define LOADCELL3_REG_CTRL_STATUS_T_GAIN_SELECT           0x48 
#define LOADCELL3_REG_CTRL_STATUS_TEMP_CTRL               0x4C 
#define LOADCELL3_REG_CTRL_STATUS_OFFSET_CANCEL           0x4E 
#define LOADCELL3_REG_CTRL_STATUS_DAC_REG0_1              0x30 
#define LOADCELL3_REG_CTRL_STATUS_DAC_REG0_2              0x31 
#define LOADCELL3_REG_CTRL_STATUS_OP_STAGE_CTRL           0x3B
    
#define LOADCELL3_REG_EEPROM_ARRAY_START                  0x00
#define LOADCELL3_REG_EEPROM_ARRAY_END                    0x7F
#define LOADCELL3_REG_EEPROM_CACHE_BYTE_0                 0x80
#define LOADCELL3_REG_EEPROM_CACHE_BYTE_1                 0x81
#define LOADCELL3_REG_EEPROM_PAGE_ADDRESS                 0x82
#define LOADCELL3_REG_EEPROM_CTRL                         0x83
#define LOADCELL3_REG_EEPROM_CRC                          0x84
#define LOADCELL3_REG_EEPROM_STATUS                       0x85
#define LOADCELL3_REG_EEPROM_CRC_STATUS                   0x86
#define LOADCELL3_REG_EEPROM_CRC_VALUE                    0x87

/*! @} */ // loadcell3_reg

/**
 * @defgroup loadcell3_set Load Cell 3 Registers Settings
 * @brief Settings for registers of Load Cell 3 Click driver.
 */

/**
 * @addtogroup loadcell3_set
 * @{
 */

/**
 * @brief Load Cell 3 description setting.
 * @details Specified setting for description of Load Cell 3 Click driver.
 */
#define LOADCELL3_SET_IF_SEL_ACCESSES_CONTROLLER          0x00
#define LOADCELL3_SET_IF_SEL_ACCESSES_DIGITAL_INTERFACE   0x01
    
#define LOADCELL3_SET_TSEM_MODE_SINGLE_ENDED              0x00
#define LOADCELL3_SET_TSEM_MODE_DIFFERENTIAL              0x01
      
#define LOADCELL3_SET_T_MUX_CTRL_EXT_TEMPE                0x00
#define LOADCELL3_SET_T_MUX_CTRL_TEST                     0x01
#define LOADCELL3_SET_T_MUX_CTRL_INT_TEMPE                0x02
#define LOADCELL3_SET_T_MUX_CTRL_BRIDGE_CURRENT           0x03
#define LOADCELL3_SET_T_MUX_CTRL_ITEMP                    0x04
    
#define LOADCELL3_SET_GAIN_1_33                           0x00
#define LOADCELL3_SET_GAIN_2                              0x01
#define LOADCELL3_SET_GAIN_4                              0x02
#define LOADCELL3_SET_GAIN_10                             0x03
#define LOADCELL3_SET_GAIN_20                             0x04
#define LOADCELL3_SET_GAIN_40                             0x05
#define LOADCELL3_SET_GAIN_100                            0x06
#define LOADCELL3_SET_GAIN_200                            0x07
    
#define LOADCELL3_SET_ITEMP_CTRL_50_mA                    0x00
#define LOADCELL3_SET_ITEMP_CTRL_100_mA                   0x01
#define LOADCELL3_SET_ITEMP_CTRL_200_mA                   0x02
#define LOADCELL3_SET_ITEMP_CTRL_1000_mA                  0x03
#define LOADCELL3_SET_ITEMP_CTRL_OFF                      0x04
    
#define LOADCELL3_SET_OFFSET_CANCEL_0_mV                  0x00
#define LOADCELL3_SET_OFFSET_CANCEL_3_65_mV               0x01
#define LOADCELL3_SET_OFFSET_CANCEL_7_3_mV                0x02
#define LOADCELL3_SET_OFFSET_CANCEL_10_95_mV              0x03
#define LOADCELL3_SET_OFFSET_CANCEL_14_6_mV               0x04
#define LOADCELL3_SET_OFFSET_CANCEL_18_28_mV              0x05
#define LOADCELL3_SET_OFFSET_CANCEL_21_9_mV               0x06
#define LOADCELL3_SET_OFFSET_CANCEL_25_55_mV              0x07
#define LOADCELL3_SET_OFFSET_CANCEL_29_2_mV               0x08
#define LOADCELL3_SET_OFFSET_CANCEL_32_85_mV              0x09
#define LOADCELL3_SET_OFFSET_CANCEL_36_5_mV               0x0A
#define LOADCELL3_SET_OFFSET_CANCEL_40_15_mV              0x0B
#define LOADCELL3_SET_OFFSET_CANCEL_43_8_mV               0x0C
#define LOADCELL3_SET_OFFSET_CANCEL_47_45_mV              0x0D
#define LOADCELL3_SET_OFFSET_CANCEL_51_1_mV               0x0E
#define LOADCELL3_SET_OFFSET_CANCEL_54_75_mV              0x0F
    
#define LOADCELL3_SET_OFFSET_CURRENT_VINPN                0x00
#define LOADCELL3_SET_OFFSET_CURRENT_VINPP                0x01

/**
 * @brief Load Cell 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Load Cell 3 Click driver.
 */
#define LOADCELL3_SET_DEV_ADDR                            0x42
#define LOADCELL3_SET_MEMORY_PAGE_TEST_REG                0x40
#define LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG  0x42
#define LOADCELL3_SET_MEMORY_PAGE_EEPROM_CACHE_CELLS      0x45
#define LOADCELL3_SET_MEMORY_PAGE_CTRL_AND_STATUS_REG     0x47

/*! @} */ // loadcell3_set

/**
 * @addtogroup weight
 * @{
 */

/**
 * @brief Load Cell 3 weight data.
 * @details Specified weight data.
 */
#define LOADCELL3_WEIGHT_ZERO                               0
#define LOADCELL3_WEIGHT_100G                             100
#define LOADCELL3_WEIGHT_500G                             500
#define LOADCELL3_WEIGHT_1000G                           1000
#define LOADCELL3_WEIGHT_5000G                           5000
#define LOADCELL3_WEIGHT_10000G                         10000

/*! @} */ // weight

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief Load Cell 3 data status.
 * @details Specified check data status of Load Cell 3 Click driver.
 */
#define LOADCELL3_DATA_NO_DATA                              0
#define LOADCELL3_DATA_OK                                   1   

/*! @} */ // status

/**
 * @defgroup loadcell3_map Load Cell 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Load Cell 3 Click driver.
 */

/**
 * @addtogroup loadcell3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Load Cell 3 Click to the selected MikroBUS.
 */
#define LOADCELL3_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // loadcell3_map
/*! @} */ // loadcell3

/**
 * @brief Load Cell 3 Click context object.
 * @details Context object definition of Load Cell 3 Click driver.
 */
typedef struct
{
    // Input pins

    digital_in_t  an;         /**< Analog input pin. */

    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} loadcell3_t;

/**
 * @brief Load Cell 3 Click configuration object.
 * @details Configuration object definition of Load Cell 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  an;         /**< Analog input pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} loadcell3_cfg_t;

/**
 * @brief Load Cell 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LOADCELL3_OK = 0,
   LOADCELL3_ERROR = -1

} loadcell3_return_value_t;

/**
 * @brief Load Cell 3 Click data structure definition.
 * @details Data object definition of Load Cell 3 Click driver.
 */
typedef struct
{
    float tare;
    uint8_t tare_ok;
    float weight_coeff_100g;
    uint8_t weight_data_100g_ok;
    float weight_coeff_500g;
    uint8_t weight_data_500g_ok;
    float weight_coeff_1000g;
    uint8_t weight_data_1000g_ok;
    float weight_coeff_5000g;
    uint8_t weight_data_5000g_ok;
    float weight_coeff_10000g;
    uint8_t weight_data_10000g_ok;
}
loadcell3_data_t;

/*!
 * @addtogroup loadcell3 Load Cell 3 Click Driver
 * @brief API for configuring and manipulating Load Cell 3 Click driver.
 * @{
 */

/**
 * @brief Load Cell 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #loadcell3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void loadcell3_cfg_setup ( loadcell3_cfg_t *cfg );

/**
 * @brief Load Cell 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #loadcell3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_init ( loadcell3_t *ctx, loadcell3_cfg_t *cfg );

/**
 * @brief Load Cell 3 default configuration function.
 * @details This function executes a default configuration of Load Cell 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t loadcell3_default_cfg ( loadcell3_t *ctx );

/**
 * @brief Load Cell 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_generic_write ( loadcell3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Load Cell 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_generic_read ( loadcell3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Load Cell 3 EEPROM I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected EEPROM memory page register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_generic_eeprom_write ( loadcell3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Load Cell 3 I2C EEPROM reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected EEPROM memory page register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_generic_eeprom_read ( loadcell3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Load Cell 3 test I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected test memory page register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_generic_test_page_write ( loadcell3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Load Cell 3 Control and Status I2C EEPROM reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected control and status memory page register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_generic_test_page_read ( loadcell3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Load Cell 3 set memory page function.
 * @details This function set memory page slave address to control communication of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] memory_page : Desired memory page slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_set_memory_page_slave_addr ( loadcell3_t *ctx, uint8_t memory_page );

/**
 * @brief Load Cell 3 accesses controller function.
 * @details This function set ccontroller accesses the memory of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_accesses_controller ( loadcell3_t *ctx );

/**
 * @brief Load Cell 3 accesses digital interface control function.
 * @details This function set digital interface accesses the memory of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_accesses_digital_interface_control ( loadcell3_t *ctx );

/**
 * @brief Load Cell 3 soft reset function.
 * @details This function executes a software reset of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_soft_reset ( loadcell3_t *ctx );

/**
 * @brief Load Cell 3 set pressure gain function.
 * @details This function set desired pressure gain of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] p_gain : Desired pressure gain steps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_set_p_gain ( loadcell3_t *ctx, uint8_t p_gain );

/**
 * @brief Load Cell 3 set temperature gain function.
 * @details This function set desired temperature gain of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] t_gain : Desired temperature gain steps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_set_t_gain ( loadcell3_t *ctx, uint8_t t_gain );

/**
 * @brief Load Cell 3 set temperature mode function.
 * @details This function set desired temperature mode of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] t_mode : Desired temperature mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_set_temp_mode ( loadcell3_t *ctx, uint8_t t_mode );

/**
 * @brief Load Cell 3 set mux control function.
 * @details This function set desired pressure channel input MUX of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] t_mux_ctrl : Desired P channel input MUX.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_set_t_mux_ctrl ( loadcell3_t *ctx, uint8_t t_mux_ctrl );

/**
 * @brief Load Cell 3 set ITEMP control function.
 * @details This function set desired ITEMP control of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] itemp_ctrl : Desired ITEMP control.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_itemp_ctrl ( loadcell3_t *ctx, uint8_t itemp_ctrl );

/**
 * @brief Load Cell 3 set offset function.
 * @details This function set desired offset of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] offset_cancel_val : Desired offset cancel value.
 * @param[in] offset_cancel_sel : Desired offset selection value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t loadcell3_set_offset ( loadcell3_t *ctx, uint8_t offset_cancel_val, uint8_t offset_cancel_sel );

/**
 * @brief Load Cell 3 get pressure ADC data function.
 * @details This function set desired offset of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @return 16-bit pressure ADC data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
int16_t loadcell3_get_p_adc_data ( loadcell3_t *ctx );

/**
 * @brief Load Cell 3 get temperature ADC data function.
 * @details This function set desired offset of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @return 16-bit temperature ADC data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
int16_t loadcell3_get_t_adc_data ( loadcell3_t *ctx );

/**
 * @brief Load Cell 3 tare the scales function.
 * @details This function for the tare scales sets the tara value into the cell data structure of the 
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return Nothing.
 * 
 * @note Function delay is approximately 500 ms.
 *
 * @endcode
 */
void loadcell3_tare ( loadcell3_t *ctx, loadcell3_data_t *cell_data );

/**
 * @brief Load Cell 3 calibration function.
 * @details This function for the calibration sets the calibration value into the cell data structure of the
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[in] cal_val : Etalon weight value
 *         @li @c   100 ( LOADCELL3_WEIGHT_100G )   :   100g etalon,
 *         @li @c   500 ( LOADCELL3_WEIGHT_500G )   :   500g etalon,
 *         @li @c  1000 ( LOADCELL3_WEIGHT_1000G )  :  1000g etalon,
 *         @li @c  5000 ( LOADCELL3_WEIGHT_5000G )  :  5000g etalon,
 *         @li @c 10000 ( LOADCELL3_WEIGHT_10000G ) : 10000g etalon.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Function delay is approximately 500 ms.
 *
 * @endcode
 */
err_t loadcell3_calibration ( loadcell3_t *ctx, uint16_t cal_val, loadcell3_data_t *cell_data );

/**
 * @brief Load Cell 3 get weight function.
 * @details This function gets float value of the scales measurements [ g ] of the
 * PGA302 Sensor Signal Conditioner With 0-5V Ratiometric Output on the Load Cell 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell3_t object definition for detailed explanation.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return Float value of the scales measurements [ g ].
 *
 * @note Function delay is approximately 500 ms.
 *
 * @endcode
 */
float loadcell3_get_weight ( loadcell3_t *ctx, loadcell3_data_t *cell_data );

#ifdef __cplusplus
}
#endif
#endif // LOADCELL3_H

/*! @} */ // loadcell3

// ------------------------------------------------------------------------ END

/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file irsense7.h
 * @brief This file contains API for IR Sense 7 Click Driver.
 */

#ifndef IRSENSE7_H
#define IRSENSE7_H

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
 * @addtogroup irsense7 IR Sense 7 Click Driver
 * @brief API for configuring and manipulating IR Sense 7 Click driver.
 * @{
 */

/**
 * @defgroup irsense7_reg IR Sense 7 Registers List
 * @brief List of registers of IR Sense 7 Click driver.
 */

/**
 * @addtogroup irsense7_reg
 * @{
 */

/**
 * @brief IR Sense 7 memory map.
 * @details Specified memory map of IR Sense 7 Click driver.
 */
#define IRSENSE7_EEPROM_PROTECTED_START     0x2400
#define IRSENSE7_EEPROM_PROTECTED_END       0x247F
#define IRSENSE7_EEPROM_UNPROTECTED_START   0x2480
#define IRSENSE7_EEPROM_UNPROTECTED_END     0x24FF
#define IRSENSE7_REG_I2C_ADDRESS            0x3000
#define IRSENSE7_REG_CONTROL                0x3001
#define IRSENSE7_REG_EE_CONTROL             0x3005
#define IRSENSE7_REG_STATUS                 0x3FFF
#define IRSENSE7_RAM_START                  0x4000
#define IRSENSE7_RAM_END                    0x403B

/**
 * @brief IR Sense 7 EEPROM address index setting.
 * @details Specified EEPROM address index setting of IR Sense 7 Click driver.
 */
#define IRSENSE7_IDX_START                  0x00
#define IRSENSE7_IDX_ID0                    0x05
#define IRSENSE7_IDX_ID1                    0x06
#define IRSENSE7_IDX_ID2                    0x07
#define IRSENSE7_IDX_ID_CRC16               0x08
#define IRSENSE7_IDX_EE_PRODUCT_CODE        0x09
#define IRSENSE7_IDX_EE_VERSION             0x0B
#define IRSENSE7_IDX_EE_P_R_L               0x0C
#define IRSENSE7_IDX_EE_P_R_H               0x0D
#define IRSENSE7_IDX_EE_P_G_L               0x0E
#define IRSENSE7_IDX_EE_P_G_H               0x0F
#define IRSENSE7_IDX_EE_P_T_L               0x10
#define IRSENSE7_IDX_EE_P_T_H               0x11
#define IRSENSE7_IDX_EE_P_O_L               0x12
#define IRSENSE7_IDX_EE_P_O_H               0x13
#define IRSENSE7_IDX_EE_EA_L                0x14
#define IRSENSE7_IDX_EE_EA_H                0x15
#define IRSENSE7_IDX_EE_EB_L                0x16
#define IRSENSE7_IDX_EE_EB_H                0x17
#define IRSENSE7_IDX_EE_FA_L                0x18
#define IRSENSE7_IDX_EE_FA_H                0x19
#define IRSENSE7_IDX_EE_FB_L                0x1A
#define IRSENSE7_IDX_EE_FB_H                0x1B
#define IRSENSE7_IDX_EE_GA_L                0x1C
#define IRSENSE7_IDX_EE_GA_H                0x1D
#define IRSENSE7_IDX_EE_GB                  0x1E
#define IRSENSE7_IDX_EE_KA                  0x1F
#define IRSENSE7_IDX_MLX_CRC                0x7F
#define IRSENSE7_IDX_CUST_CRC               0x80
#define IRSENSE7_IDX_EE_HA                  0x81
#define IRSENSE7_IDX_EE_HB                  0x82
#define IRSENSE7_IDX_CUSTOMER_DATA_START    0xC0
#define IRSENSE7_IDX_CUSTOMER_DATA_END      0xCF
#define IRSENSE7_IDX_EE_CONTROL             0xD4
#define IRSENSE7_IDX_EE_I2C_ADDRESS         0xD5
#define IRSENSE7_IDX_EE_TCC1                0xDE
#define IRSENSE7_IDX_EE_TCC2                0xDB
#define IRSENSE7_IDX_EE_MEAS_2              0xE2
#define IRSENSE7_IDX_EE_MEAS_3              0xE3
#define IRSENSE7_IDX_END                    0xFF

/*! @} */ // irsense7_reg

/**
 * @defgroup irsense7_set IR Sense 7 Registers Settings
 * @brief Settings for registers of IR Sense 7 Click driver.
 */

/**
 * @addtogroup irsense7_set
 * @{
 */

/**
 * @brief IR Sense 7 EE_CONTROL register setting.
 * @details Specified setting for EE_CONTROL register of IR Sense 7 Click driver.
 */
#define IRSENSE7_EE_CONTROL_DEVICE_RESET    0x0006
#define IRSENSE7_EE_CONTROL_EEPROM_UNLOCK   0x554C

/**
 * @brief IR Sense 7 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Sense 7 Click driver.
 */
#define IRSENSE7_DEVICE_ADDRESS_0           0x3A
#define IRSENSE7_DEVICE_ADDRESS_1           0x3B

/*! @} */ // irsense7_set

/**
 * @defgroup irsense7_map IR Sense 7 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Sense 7 Click driver.
 */

/**
 * @addtogroup irsense7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Sense 7 Click to the selected MikroBUS.
 */
#define IRSENSE7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // irsense7_map
/*! @} */ // irsense7

/**
 * @brief IR Sense 7 Click calibration constants object.
 * @details EEPROM calibration constants object definition of IR Sense 7 Click driver.
 */
typedef struct
{
    uint8_t cp_val;
    uint8_t cv_val;
    uint8_t ch_val;
    uint8_t cl_val;
    uint8_t ci_val;
    float p_r_val;
    float p_g_val;
    float p_t_val;
    float p_o_val;
    float ea_val;
    float eb_val;
    float fa_val;
    float fb_val;
    float ga_val;
    float gb_val;
    float ka_val;
    float ha_val;
    float hb_val;

} irsense7_ee_cal_t;

/**
 * @brief IR Sense 7 Click context object.
 * @details Context object definition of IR Sense 7 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint16_t ee_data[ IRSENSE7_IDX_END - IRSENSE7_IDX_START + 1 ];  /**< EEPROM data. */
    int16_t ram_data[ IRSENSE7_RAM_END - IRSENSE7_RAM_START + 1 ];  /**< RAM data. */

    irsense7_ee_cal_t ee_cal;   /**< EEPROM calibration constants. */

} irsense7_t;

/**
 * @brief IR Sense 7 Click configuration object.
 * @details Configuration object definition of IR Sense 7 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t i2c_speed;         /**< I2C serial speed. */
    uint8_t i2c_address;        /**< I2C slave address. */

} irsense7_cfg_t;

/**
 * @brief IR Sense 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRSENSE7_OK = 0,
    IRSENSE7_ERROR = -1

} irsense7_return_value_t;

/*!
 * @addtogroup irsense7 IR Sense 7 Click Driver
 * @brief API for configuring and manipulating IR Sense 7 Click driver.
 * @{
 */

/**
 * @brief IR Sense 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irsense7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irsense7_cfg_setup ( irsense7_cfg_t *cfg );

/**
 * @brief IR Sense 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irsense7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense7_init ( irsense7_t *ctx, irsense7_cfg_t *cfg );

/**
 * @brief IR Sense 7 default configuration function.
 * @details This function executes a default configuration of IR Sense 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t irsense7_default_cfg ( irsense7_t *ctx );

/**
 * @brief IR Sense 7 write data function.
 * @details This function writes a 16-bit data value to the selected memory address over I2C.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @param[in] addr : Memory address.
 * @param[in] data_in : 16-bit data to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense7_write_data ( irsense7_t *ctx, uint16_t addr, uint16_t data_in );

/**
 * @brief IR Sense 7 read data function.
 * @details This function reads multiple 16-bit values starting from the selected memory address.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @param[in] addr : Memory address.
 * @param[out] data_out : Pointer to the memory where the read data will be stored.
 * @param[in] len : Number of 16-bit values to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns error if parameters are invalid.
 */
err_t irsense7_read_data ( irsense7_t *ctx, uint16_t addr, uint16_t *data_out, uint16_t len );

/**
 * @brief IR Sense 7 reset device function.
 * @details This function performs a device reset by writing to the control register.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense7_reset_device ( irsense7_t *ctx );

/**
 * @brief IR Sense 7 EEPROM write unlock function.
 * @details This function unlocks EEPROM write access.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense7_eeprom_write_unlock ( irsense7_t *ctx );

/**
 * @brief IR Sense 7 communication check function.
 * @details This function verifies device communication by checking ID CRC.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense7_check_com ( irsense7_t *ctx );

/**
 * @brief IR Sense 7 read EEPROM function.
 * @details This function reads EEPROM data, verifies CRC values, and calculates calibration constants.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns error if CRC validation fails.
 */
err_t irsense7_read_eeprom ( irsense7_t *ctx );

/**
 * @brief IR Sense 7 read RAM function.
 * @details This function reads measurement data from RAM.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense7_read_ram ( irsense7_t *ctx );

/**
 * @brief IR Sense 7 calculate ambient temperature function.
 * @details This function calculates the ambient temperature using RAM data and calibration constants.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return Calculated ambient temperature in degrees Celsius.
 * @note None.
 */
float irsense7_calculate_amb_temp ( irsense7_t *ctx );

/**
 * @brief IR Sense 7 calculate object temperature function.
 * @details This function calculates the object temperature using RAM data, calibration constants, and iterative correction.
 * @param[in] ctx : Click context object.
 * See #irsense7_t object definition for detailed explanation.
 * @return Calculated object temperature in degrees Celsius.
 * @note Uses previous temperature value for iterative calculation.
 */
float irsense7_calculate_obj_temp ( irsense7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IRSENSE7_H

/*! @} */ // irsense7

// ------------------------------------------------------------------------ END

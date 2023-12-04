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
 * @file smartbuck2.h
 * @brief This file contains API for Smart Buck 2 Click Driver.
 */

#ifndef SMARTBUCK2_H
#define SMARTBUCK2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup smartbuck2 Smart Buck 2 Click Driver
 * @brief API for configuring and manipulating Smart Buck 2 Click driver.
 * @{
 */

/**
 * @defgroup smartbuck2_reg Smart Buck 2 Registers List
 * @brief List of registers of Smart Buck 2 Click driver.
 */

/**
 * @addtogroup smartbuck2_reg
 * @{
 */

/**
 * @brief Smart Buck 2 description register.
 * @details Specified register for description of Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_REG_SET0               0x00
#define SMARTBUCK2_REG_SET1               0x01
#define SMARTBUCK2_REG_SET2               0x02
#define SMARTBUCK2_REG_SET3               0x03
#define SMARTBUCK2_REG_CTRL               0x04
#define SMARTBUCK2_REG_TEMP               0x05
#define SMARTBUCK2_REG_RMPCTRL            0x06
#define SMARTBUCK2_REG_CHIP_ID_0          0x08
#define SMARTBUCK2_REG_CHIP_ID_1          0x09

/*! @} */ // smartbuck2_reg

/**
 * @defgroup smartbuck2_set Smart Buck 2 Registers Settings
 * @brief Settings for registers of Smart Buck 2 Click driver.
 */

/**
 * @addtogroup smartbuck2_set
 * @{
 */

/**
 * @brief Smart Buck 2 description of operation mode values.
 * @details Specified operation mode values of Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_OP_MOD_BIT_MASK        0x80
#define SMARTBUCK2_OP_MODE_FORCED_PWM     0x80
#define SMARTBUCK2_OP_MODE_PFM            0x00

/**
 * @brief Smart Buck 2 description of control register values.
 * @details Specified control register values of Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_CTRL_BIT_MASK          0xE0
#define SMARTBUCK2_CTRL_PD_EN             0x80
#define SMARTBUCK2_CTRL_PD_DIS            0x00
#define SMARTBUCK2_CTRL_PD_VSEL0_EN       0x40
#define SMARTBUCK2_CTRL_PD_VSEL0_DIS      0x00
#define SMARTBUCK2_CTRL_PD_VSEL1_EN       0x20
#define SMARTBUCK2_CTRL_PD_VSEL1_DIS      0x00
#define SMARTBUCK2_CTRL_PD_VSEL           0x40

/**
 * @brief Smart Buck 2 description of temp register values.
 * @details Specified temp register values of Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_TEMP_DIS_BIT_MASK      0xFB
#define SMARTBUCK2_TEMP_TS_ENABLE         0x00
#define SMARTBUCK2_TEMP_TS_DISABLE        0x04
#define SMARTBUCK2_TEMP_TJEW              0x02
#define SMARTBUCK2_TEMP_TJEW_BIT_MASK     0xFD
#define SMARTBUCK2_TEMP_LT_120_C          0x00
#define SMARTBUCK2_TEMP_GT_120_C          0x01
#define SMARTBUCK2_TEMP_ERROR             0x02
#define SMARTBUCK2_TEMP_TJTS              0x01

/**
 * @brief Smart Buck 2 description of ramp temp register values.
 * @details Specified ramp temp register values of Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_RMP_VTG_T_BIT_MASK     0xE0
#define SMARTBUCK2_RMP_SET                0xE0
#define SMARTBUCK2_RMP_EN_DISC            0x04
#define SMARTBUCK2_RMP_PFM                0x02
#define SMARTBUCK2_RMP_VTG_T_32MVNS       0x00
#define SMARTBUCK2_RMP_VTG_T_16MVNS       0x01
#define SMARTBUCK2_RMP_VTG_T_8MVNS        0x02
#define SMARTBUCK2_RMP_VTG_T_4MVNS        0x03
#define SMARTBUCK2_RMP_VTG_T_2MVNS        0x04
#define SMARTBUCK2_RMP_VTG_T_1MVNS        0x05
#define SMARTBUCK2_RMP_VTG_T_0_5MVNS      0x06
#define SMARTBUCK2_RMP_VTG_T_0_25MVNS     0x07

/**
 * @brief Smart Buck 2 description of device ID values.
 * @details Specified device ID values of Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_VENDOR_ID_BIT_MASK     0xF0
#define SMARTBUCK2_ID_VENDOR              0x80
#define SMARTBUCK2_PART_NUM_ID_BIT_MASK   0x0C
#define SMARTBUCK2_ID_PART_NUM            0x03
#define SMARTBUCK2_CHIP_REV_ID_BIT_MASK   0x03

/**
 * @brief Smart Buck 2 description of Vout calculation values.
 * @details Specified Vout calculation values of Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_VOUT_MIN                500u
#define SMARTBUCK2_VOUT_MAX               1770u
#define SMARTBUCK2_VOUT_STEP_10MV           10u
#define SMARTBUCK2_VOUT_START_500MV        500u

/**
 * @brief Smart Buck 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Buck 2 Click driver.
 */
#define SMARTBUCK2_DEVICE_ADDRESS        0x60

/*! @} */ // smartbuck2_set

/**
 * @defgroup smartbuck2_map Smart Buck 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Buck 2 Click driver.
 */

/**
 * @addtogroup smartbuck2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Buck 2 Click to the selected MikroBUS.
 */
#define SMARTBUCK2_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // smartbuck2_map
/*! @} */ // smartbuck2

/**
 * @brief Smart Buck 2 Click context object.
 * @details Context object definition of Smart Buck 2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} smartbuck2_t;

/**
 * @brief Smart Buck 2 Click configuration object.
 * @details Configuration object definition of Smart Buck 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} smartbuck2_cfg_t;

/**
 * @brief Smart Buck 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTBUCK2_OK = 0,
    SMARTBUCK2_ERROR = -1

} smartbuck2_return_value_t;

/*!
 * @addtogroup smartbuck2 Smart Buck 2 Click Driver
 * @brief API for configuring and manipulating Smart Buck 2 Click driver.
 * @{
 */

/**
 * @brief Smart Buck 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartbuck2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartbuck2_cfg_setup ( smartbuck2_cfg_t *cfg );

/**
 * @brief Smart Buck 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartbuck2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_init ( smartbuck2_t *ctx, smartbuck2_cfg_t *cfg );

/**
 * @brief Smart Buck 2 default configuration function.
 * @details This function executes a default configuration of Smart Buck 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartbuck2_default_cfg ( smartbuck2_t *ctx );

/**
 * @brief Smart Buck 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_generic_write ( smartbuck2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart Buck 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_generic_read ( smartbuck2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart Buck 2 set voltage function.
 * @details This function sets the output voltage
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] vout_mv : Voltage output in millivolts [500-1770mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_set_voltage ( smartbuck2_t *ctx, uint16_t vout_mv );

/**
 * @brief Smart Buck 2 get voltage function.
 * @details This function reads the output voltage
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[out] vout_mv : Voltage output in millivolts [500-1770mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_get_voltage ( smartbuck2_t *ctx, uint16_t *vout_mv );

/**
 * @brief Smart Buck 2 set operation mode function.
 * @details This function sets the desired operation mode
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] op_mode : 
 *         @li @c SMARTBUCK2_OP_MODE_PFM - PFM/PWM mode operation,
 *         @li @c SMARTBUCK2_OP_MODE_FORCED_PWM - Forced PWM mode operation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_set_op_mode ( smartbuck2_t *ctx, uint8_t op_mode );

/**
 * @brief Smart Buck 2 get operation mode function.
 * @details This function reads the desired operation mode
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[out] op_mode : Operation mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_get_op_mode ( smartbuck2_t *ctx, uint8_t *op_mode );

/**
 * @brief Smart Buck 2 set control function.
 * @details This function sets desired configuration of the control register
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] ctrl : Control register configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_set_ctrl ( smartbuck2_t *ctx, uint8_t ctrl );

/**
 * @brief Smart Buck 2 set temperature shutdown function.
 * @details This function sets temperature shutdown feature
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] temp_enable : 
 *         @li @c SMARTBUCK2_TEMP_TS_ENABLE  - Temperature shutdown enabled,
 *         @li @c SMARTBUCK2_TEMP_TS_DISABLE - Temperature shutdown disabled (not recommended).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_set_temp_shd ( smartbuck2_t *ctx, uint8_t temp_enable );

/**
 * @brief Smart Buck 2 check temperature warning function.
 * @details This function checks temperature warnings
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @return @li @c SMARTBUCK2_TEMP_LT_120_C - The temperature is less than 120 degrees Celsius,
 *         @li @c SMARTBUCK2_TEMP_GT_120_C - The temperature is greater than 120 degrees Celsius.
 * @note None.
 */
uint8_t smartbuck2_check_temp_warning ( smartbuck2_t *ctx );

/**
 * @brief Smart Buck 2 set voltage ramp timing function.
 * @details This function sets output voltage ramp timing
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[in] slope : 
 *         @li @c SMARTBUCK2_RMP_VTG_T_32MVNS   - 32 mV/µs,
 *         @li @c SMARTBUCK2_RMP_VTG_T_16MVNS   - 16 mV/µs,
 *         @li @c SMARTBUCK2_RMP_VTG_T_8MVNS    -  8 mV/µs,
 *         @li @c SMARTBUCK2_RMP_VTG_T_4MVNS    -  4 mV/µs,
 *         @li @c SMARTBUCK2_RMP_VTG_T_2MVNS    -  2 mV/µs,
 *         @li @c SMARTBUCK2_RMP_VTG_T_1MVNS    -  1 mV/µs,
 *         @li @c SMARTBUCK2_RMP_VTG_T_0_5MVNS  -  0.5 mV/µs,
 *         @li @c SMARTBUCK2_RMP_VTG_T_0_25MVNS -  0.25 mV/µs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_set_vtg_ramp_timing ( smartbuck2_t *ctx, uint8_t slope ); 

/**
 * @brief Smart Buck 2 get device ID function.
 * @details This function reads Chip ID register (vendor ID, part number ID and chip revision ID)
 * of the TPS62363YZHT, 3A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck2_t object definition for detailed explanation.
 * @param[out] ven_id : Vendor ID.
 * @param[out] part_num_id : Part number ID.
 * @param[out] chip_id : Chip revision ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck2_get_device_id ( smartbuck2_t *ctx, uint8_t *ven_id, uint8_t *part_num_id, uint8_t *chip_id );

#ifdef __cplusplus
}
#endif
#endif // SMARTBUCK2_H

/*! @} */ // smartbuck2

// ------------------------------------------------------------------------ END

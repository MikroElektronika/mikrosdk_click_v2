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
 * @file battmon3.h
 * @brief This file contains API for BATT-MON 3 Click Driver.
 */

#ifndef BATTMON3_H
#define BATTMON3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup battmon3 BATT-MON 3 Click Driver
 * @brief API for configuring and manipulating BATT-MON 3 Click driver.
 * @{
 */

/**
 * @defgroup battmon3_reg BATT-MON 3 Registers List
 * @brief List of registers of BATT-MON 3 Click driver.
 */

/**
 * @addtogroup battmon3_reg
 * @{
 */

/**
 * @brief BATT-MON 3 Register Map.
 * @details Specified register map of BATT-MON 3 Click driver.
 */
#define BATTMON3_REG_CONTROL                    0x00
#define BATTMON3_REG_ACCUMULATED_CAPACITY       0x02
#define BATTMON3_REG_TEMPERATURE                0x06
#define BATTMON3_REG_VOLTAGE                    0x08
#define BATTMON3_REG_BATTERY_STATUS             0x0A
#define BATTMON3_REG_BATTERY_ALERT              0x0B
#define BATTMON3_REG_CURRENT                    0x0C
#define BATTMON3_REG_SCALED_R                   0x16
#define BATTMON3_REG_MEASURED_Z                 0x22
#define BATTMON3_REG_INTERNAL_TEMPERATURE       0x28
#define BATTMON3_REG_STATE_OF_HEALTH            0x2E
#define BATTMON3_REG_DESIGN_CAPACITY            0x3C
#define BATTMON3_REG_MAC                        0x3E
#define BATTMON3_REG_MAC_DATA                   0x40
#define BATTMON3_REG_MAC_DATA_SUM               0x60
#define BATTMON3_REG_MAC_DATA_LEN               0x61
#define BATTMON3_REG_MAC_DATA_CONTROL           0x62
#define BATTMON3_REG_CAL_COUNT                  0x79
#define BATTMON3_REG_CAL_CURRENT                0x7A
#define BATTMON3_REG_CAL_VOLTAGE                0x7C
#define BATTMON3_REG_CAL_TEMPERATURE            0x7E

/**
 * @brief BATT-MON 3 Control register functions.
 * @details Specified Control register functions of BATT-MON 3 Click driver.
 */
#define BATTMON3_CONTROL_STATUS                 0x0000
#define BATTMON3_CONTROL_DEVICE_TYPE            0x0001
#define BATTMON3_CONTROL_FW_VERSION             0x0002
#define BATTMON3_CONTROL_HW_VERSION             0x0003
#define BATTMON3_CONTROL_STATIC_CHEM_CHKSUM     0x0005
#define BATTMON3_CONTROL_CHEM_ID                0x0006
#define BATTMON3_CONTROL_PREV_MACWRITE          0x0007
#define BATTMON3_CONTROL_BOARD_OFFSET           0x0009
#define BATTMON3_CONTROL_CC_OFFSET              0x000A
#define BATTMON3_CONTROL_CC_OFFSET_SAVE         0x000B
#define BATTMON3_CONTROL_DF_VERSION             0x000C
#define BATTMON3_CONTROL_GAUGE_START            0x0011
#define BATTMON3_CONTROL_GAUGE_STOP             0x0012
#define BATTMON3_CONTROL_SEALED                 0x0020
#define BATTMON3_CONTROL_CAL_ENABLE             0x002D
#define BATTMON3_CONTROL_LT_ENABLE              0x002E
#define BATTMON3_CONTROL_RESET                  0x0041
#define BATTMON3_CONTROL_EXIT_CAL               0x0080
#define BATTMON3_CONTROL_ENTER_CAL              0x0081
#define BATTMON3_CONTROL_NEW_BATTERY            0xA613

/**
 * @brief BATT-MON 3 Data Flash Table.
 * @details Specified Data Flash Table of BATT-MON 3 Click driver.
 * @note For the full list of addresses refer to the TI BQ35100 technical reference manual.
 */
#define BATTMON3_DF_CC_GAIN                     0x4000
#define BATTMON3_DF_CC_DELTA                    0x4004
#define BATTMON3_DF_CC_OFFSET                   0x4008
#define BATTMON3_DF_BOARD_OFFSET                0x400C
#define BATTMON3_DF_INT_TEMP_OFFSET             0x400D
#define BATTMON3_DF_EXT_TEMP_OFFSET             0x400E
#define BATTMON3_DF_PACK_V_OFFSET               0x400F
#define BATTMON3_DF_OPERATION_CONFIG_A          0x41B1
#define BATTMON3_DF_FULL_UNSEAL_STEP_1          0x41D0
#define BATTMON3_DF_CELL_DESIGN_CAPACITY        0x41FE

/*! @} */ // battmon3_reg

/**
 * @defgroup battmon3_set BATT-MON 3 Registers Settings
 * @brief Settings for registers of BATT-MON 3 Click driver.
 */

/**
 * @addtogroup battmon3_set
 * @{
 */

/**
 * @brief BATT-MON 3 default CHEM ID value.
 * @details Specified default CHEM ID value of BATT-MON 3 Click driver.
 */
#define BATTMON3_CHEM_ID                        0x0606

/**
 * @brief BATT-MON 3 seal codes.
 * @details Specified seal codes of BATT-MON 3 Click driver.
 */
#define BATTMON3_SEAL_CODES_DEFAULT             0x04143672ul

/**
 * @brief BATT-MON 3 status bit masks.
 * @details Specified status bit masks of BATT-MON 3 Click driver.
 */
#define BATTMON3_STATUS_GA_BIT_MASK             0x0001
#define BATTMON3_STATUS_G_DONE_BIT_MASK         0x0040
#define BATTMON3_STATUS_INIT_COMP_BIT_MASK      0x0080
#define BATTMON3_STATUS_CCA_BIT_MASK            0x0400
#define BATTMON3_STATUS_BCA_BIT_MASK            0x0800
#define BATTMON3_STATUS_CAL_MODE_BIT_MASK       0x1000
#define BATTMON3_STATUS_FLASHF_BIT_MASK         0x8000

/**
 * @brief BATT-MON 3 operation config A bit masks.
 * @details Specified operation config A bit masks of BATT-MON 3 Click driver.
 */
#define BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK     0x80
#define BATTMON3_OP_CONFIG_A_EXTVCELL_BIT_MASK  0x40
#define BATTMON3_OP_CONFIG_A_WRTEMP_BIT_MASK    0x20
#define BATTMON3_OP_CONFIG_A_LF_EN_BIT_MASK     0x10
#define BATTMON3_OP_CONFIG_A_GNDSEL_BIT_MASK    0x04
#define BATTMON3_OP_CONFIG_A_GMSEL_BIT_MASK     0x03

/**
 * @brief BATT-MON 3 device address setting.
 * @details Specified setting for device slave address selection of
 * BATT-MON 3 Click driver.
 */
#define BATTMON3_DEVICE_ADDRESS                 0x55

/*! @} */ // battmon3_set

/**
 * @defgroup battmon3_map BATT-MON 3 MikroBUS Map
 * @brief MikroBUS pin mapping of BATT-MON 3 Click driver.
 */

/**
 * @addtogroup battmon3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT-MON 3 Click to the selected MikroBUS.
 */
#define BATTMON3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // battmon3_map
/*! @} */ // battmon3

/**
 * @brief BATT-MON 3 Click context object.
 * @details Context object definition of BATT-MON 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;               /**< Gauge enable (Active High). */

    // Input pins
    digital_in_t  alr;              /**< Alert pin (Active Low). */

    // Modules
    i2c_master_t  i2c;              /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    
    uint8_t security_mode;          /**< Security Mode setting. */
    
    bool    enabled;                /**< Gauge enable flag. */

} battmon3_t;

/**
 * @brief BATT-MON 3 Click configuration object.
 * @details Configuration object definition of BATT-MON 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;                 /**< Gauge enable (Active High). */
    pin_name_t  alr;                /**< Alert pin (Active Low). */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} battmon3_cfg_t;

/**
 * @brief BATT-MON 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTMON3_OK = 0,
    BATTMON3_ERROR = -1

} battmon3_return_value_t;

/**
 * @brief BATT-MON 3 the security mode of the BQ35100 chip.
 * @details Predefined enum values the security mode of the BQ35100 chip.
 */
typedef enum 
{
    BATTMON3_SECURITY_MODE_UNKNOWN = 0x00,
    BATTMON3_SECURITY_MODE_FULL_ACCESS = 0x01, //!< Allows writes to all of memory.
    BATTMON3_SECURITY_MODE_UNSEALED = 0x02, //!< Allows writes to all of memory apart from the security codes area.
    BATTMON3_SECURITY_MODE_SEALED = 0x03 //!< Normal operating mode, prevents accidental writes.
    
} battmon3_security_mode_t;

/**
 * @brief BATT-MON 3 the gauge mode of the BQ35100 chip.
 * @details Predefined enum values the gauge mode of the BQ35100 chip.
 */
typedef enum 
{
    BATTMON3_GAUGE_MODE_ACCUMULATOR = 0x00,
    BATTMON3_GAUGE_MODE_SOH = 0x01, // for LiMnO2
    BATTMON3_GAUGE_MODE_EOS = 0x02, // for LiSOCl2
    BATTMON3_GAUGE_MODE_UNKNOWN = 0x03
    
} battmon3_gauge_mode_t;

/*!
 * @addtogroup battmon3 BATT-MON 3 Click Driver
 * @brief API for configuring and manipulating BATT-MON 3 Click driver.
 * @{
 */

/**
 * @brief BATT-MON 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battmon3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battmon3_cfg_setup ( battmon3_cfg_t *cfg );

/**
 * @brief BATT-MON 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battmon3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_init ( battmon3_t *ctx, battmon3_cfg_t *cfg );

/**
 * @brief BATT-MON 3 default configuration function.
 * @details This function executes a default configuration of BATT-MON 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t battmon3_default_cfg ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_generic_write ( battmon3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief BATT-MON 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_generic_read ( battmon3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief BATT-MON 3 write two bytes function.
 * @details This function writes two bytes of data to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written [16-bit].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_write_two_bytes ( battmon3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief BATT-MON 3 read two bytes function.
 * @details This function reads two bytes of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Data output read [16-bit].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_two_bytes ( battmon3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief BATT-MON 3 write control function.
 * @details This function writes the selected control subcommand.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] control : Control subcommand.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_write_control ( battmon3_t *ctx, uint16_t control );

/**
 * @brief BATT-MON 3 read control function.
 * @details This function reads data from the selected control subcommand.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] control : Control subcommand.
 * @param[out] data_out : Data output read [16-bit].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_control ( battmon3_t *ctx, uint16_t control, uint16_t *data_out );

/**
 * @brief BATT-MON 3 write data flash function.
 * @details This function writes a desired number of data bytes starting from
 * the selected data flash address.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] address : Data flash address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_write_data_flash ( battmon3_t *ctx, uint16_t address, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief BATT-MON 3 read data flash function.
 * @details This function reads a desired number of data bytes starting from
 * the selected data flash address.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] address : Data flash address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_data_flash ( battmon3_t *ctx, uint16_t address, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief BATT-MON 3 check communication function.
 * @details This function checks the communication by reading and verifying the CHEM ID value.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_check_communication ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 read status function.
 * @details This function reads the control status register.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] status : Control status [16-bit].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_status ( battmon3_t *ctx, uint16_t *status );

/**
 * @brief BATT-MON 3 wait for status function.
 * @details This function waits for the specific status to occur (up to 10 seconds).
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] mask : Bit mask to be matched.
 * @param[in] status : Status of bit mask to be matched.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_wait_for_status ( battmon3_t *ctx, uint16_t mask, uint16_t status );

/**
 * @brief BATT-MON 3 set en pin high function.
 * @details This function sets the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void battmon3_set_en_pin_high ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 set en pin low function.
 * @details This function sets the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void battmon3_set_en_pin_low ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 get alert pin function.
 * @details This function returns the Alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t battmon3_get_alert_pin ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 start gauge function.
 * @details This function starts the battery gauge. Battery gauging must be switched on
 * for the battery capacity and percentage readings to be valid. The chip will consume 
 * more when battery gauging is switched on.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_start_gauge ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 stop gauge function.
 * @details This function stops the battery gauging. It doesn't handle EN pin!
 * If BATTMON3_GAUGE_MODE_ACCUMULATOR is activated, the accumulated capacity values
 * will be stored in non-volatile memory. Please see the warning in section 5.1.1 
 * of the TI BQ35100 technical reference manual concerning how frequently this should be done.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_stop_gauge ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 disable gauge function.
 * @details This function disables gauge by stopping it and waiting for G_DONE bit to be set.
 * And after that it clears the EN pin.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_disable_gauge ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 set gauge mode function.
 * @details This function sets the gauging mode.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] gauge_mode : @li @c 0 - Accumulated,
 *                         @li @c 1 - SOH (for LiMnO2),
 *                         @li @c 2 - EOS (for LiSOCl2).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_set_gauge_mode ( battmon3_t *ctx, uint8_t gauge_mode );

/**
 * @brief BATT-MON 3 reset function.
 * @details This function performs a hard reset of the chip, reinitialising RAM data to defaults from ROM.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The security mode of the chip is unaffected.
 */
err_t battmon3_reset ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 read security mode function.
 * @details This function reads the security mode and stores the value in @b ctx->security_mode.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_security_mode ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 set security mode function.
 * @details This function sets the security mode of the chip.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] security_mode : @li @c 1 - FULL ACCESS - Allows writes to all of memory,
 *                            @li @c 2 - UNSEALED - Allows writes to all of memory apart from the security codes area,
 *                            @li @c 3 - SEALED - Normal operating mode, prevents accidental writes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_set_security_mode ( battmon3_t *ctx, uint8_t security_mode );

/**
 * @brief BATT-MON 3 new battery function.
 * @details This function indicates to the chip that a new battery has been inserted.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] des_capacity : The capacity of the battery (mAh), if zero use the previous set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_new_battery ( battmon3_t *ctx, uint16_t des_capacity );

/**
 * @brief BATT-MON 3 set design capacity function.
 * @details This function sets the design capacity of the cell.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] des_capacity : The capacity of the battery (mAh).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_set_design_capacity ( battmon3_t *ctx, uint16_t des_capacity );

/**
 * @brief BATT-MON 3 read design capacity function.
 * @details This function reads the design capacity of the cell.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] des_capacity : The capacity of the battery (mAh).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_design_capacity ( battmon3_t *ctx, uint16_t *des_capacity );

/**
 * @brief BATT-MON 3 read used capacity function.
 * @details This function reads the used battery capacity in mAh.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] used_capacity : The used capacity of the battery (mAh).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_used_capacity ( battmon3_t *ctx, float *used_capacity );

/**
 * @brief BATT-MON 3 read remaining capacity function.
 * @details This function reads the remaining battery capacity in mAh.
 * This relies on the Design Capacity of the battery having been set correctly.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] rem_capacity : The remaining capacity of the battery (mAh).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_remaining_capacity ( battmon3_t *ctx, float *rem_capacity );

/**
 * @brief BATT-MON 3 read remaining percentage function.
 * @details This function reads the remaining battery capacity in percent.
 * This relies on the Design Capacity of the battery having been set correctly.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] rem_percentage : The remaining capacity of the battery (%).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_remaining_percentage ( battmon3_t *ctx, float *rem_percentage );

/**
 * @brief BATT-MON 3 use internal temperature function.
 * @details This function selects the internal temperature sensor to be used for temperature measurements.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_use_internal_temperature ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 use external temperature function.
 * @details This function selects the external temperature sensor (NTC) to be used for temperature measurements.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_use_external_temperature ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 read temperature function.
 * @details This function reads the internal or external temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_temperature ( battmon3_t *ctx, float *temperature );

/**
 * @brief BATT-MON 3 read internal temperature function.
 * @details This function reads the internal temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_internal_temperature ( battmon3_t *ctx, float *temperature );

/**
 * @brief BATT-MON 3 read voltage function.
 * @details This function reads the battery voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] voltage : Battery voltage in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_voltage ( battmon3_t *ctx, uint16_t *voltage );

/**
 * @brief BATT-MON 3 read current function.
 * @details This function reads the battery current load from BATT+ to GND in milliampers.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] current : Battery current in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_current ( battmon3_t *ctx, int16_t *current );

/**
 * @brief BATT-MON 3 read scaled R function.
 * @details This function reads the scaled resistance of the cell. It is updated upon a new 
 * resistance update in EOS mode only with a resolution of 1 mOhm per bit.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] scaled_r : Scaled resistance of the cell.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_scaled_r ( battmon3_t *ctx, uint16_t *scaled_r );

/**
 * @brief BATT-MON 3 read measured Z function.
 * @details This function reads the measured impedance of the cell. It is updated upon a new 
 * resistance update in EOS mode only with a resolution of 1 mOhm per bit.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] measured_z : Measured impedance of the cell.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_measured_z ( battmon3_t *ctx, uint16_t *measured_z );

/**
 * @brief BATT-MON 3 read state of health function.
 * @details This function reads the state-of-health (SOH) value.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] state_of_health : State-of-health (SOH) value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_state_of_health ( battmon3_t *ctx, uint8_t *state_of_health );

/**
 * @brief BATT-MON 3 read battery status function.
 * @details This function reads the battery status register.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] batt_status : Battery status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_battery_status ( battmon3_t *ctx, uint8_t *batt_status );

/**
 * @brief BATT-MON 3 read battery alert function.
 * @details This function reads the battery alert register.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[out] batt_alert : Battery alert register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_battery_alert ( battmon3_t *ctx, uint8_t *batt_alert );

/**
 * @brief BATT-MON 3 enter calibration mode function.
 * @details This function enters to the calibration mode.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_enter_calibration_mode ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 exit calibration mode function.
 * @details This function exits from the calibration mode.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_exit_calibration_mode ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 read raw calibration data function.
 * @details This function reads the RAW calibration voltage, current or temperature data.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] reg : Calibration voltage, current or temperature register address.
 * @param[out] cal_data : Output read calibration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon3_read_raw_calibration_data ( battmon3_t *ctx, uint8_t reg, uint16_t *cal_data );

/**
 * @brief BATT-MON 3 perform CC offset function.
 * @details This function performs the CC offset (no current should be flowing).
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note UNSEAL the chip before calibration.
 */
err_t battmon3_perform_cc_offset ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 perform board offset function.
 * @details This function performs the board offset (no current should be flowing).
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note UNSEAL the chip before calibration.
 */
err_t battmon3_perform_board_offset ( battmon3_t *ctx );

/**
 * @brief BATT-MON 3 calibrate voltage function.
 * @details This function calibrates the chip with known voltage.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] voltage : Known voltage in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note UNSEAL the chip before calibration.
 */
err_t battmon3_calibrate_voltage ( battmon3_t *ctx, uint16_t voltage );

/**
 * @brief BATT-MON 3 calibrate current function.
 * @details This function calibrates the chip with known current flowing.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] current : Known constant current in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note UNSEAL the chip before calibration.
 */
err_t battmon3_calibrate_current ( battmon3_t *ctx, int16_t current );

/**
 * @brief BATT-MON 3 calibrate temperature function.
 * @details This function calibrates the internal or external temperature.
 * To determine which temperature source is selected calling @b battmon3_use_internal_temperature or 
 * @b battmon3_use_external_temperature functions is recommended prior to this.
 * @param[in] ctx : Click context object.
 * See #battmon3_t object definition for detailed explanation.
 * @param[in] temperature : Known temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note UNSEAL the chip before calibration.
 */
err_t battmon3_calibrate_temperature ( battmon3_t *ctx, float temperature );

#ifdef __cplusplus
}
#endif
#endif // BATTMON3_H

/*! @} */ // battmon3

// ------------------------------------------------------------------------ END

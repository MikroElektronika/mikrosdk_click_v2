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
 * @file heartrate13.h
 * @brief This file contains API for Heart Rate 13 Click Driver.
 */

#ifndef HEARTRATE13_H
#define HEARTRATE13_H

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
 * @addtogroup heartrate13 Heart Rate 13 Click Driver
 * @brief API for configuring and manipulating Heart Rate 13 Click driver.
 * @{
 */

/**
 * @defgroup heartrate13_reg Heart Rate 13 Registers List
 * @brief List of registers of Heart Rate 13 Click driver.
 */

/**
 * @addtogroup heartrate13_reg
 * @{
 */

/**
 * @brief Heart Rate 13 register list.
 * @details Specified register list of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_REG_STATUS                              0x00
#define HEARTRATE13_REG_INT_MASK                            0x01
#define HEARTRATE13_REG_GPIO_DRV                            0x02
#define HEARTRATE13_REG_BG_STATUS                           0x04
#define HEARTRATE13_REG_FIFO_THRESH                         0x06
#define HEARTRATE13_REG_DEVID                               0x08
#define HEARTRATE13_REG_I2CS_ID                             0x09
#define HEARTRATE13_REG_CLK_RATIO                           0x0A
#define HEARTRATE13_REG_GPIO_CTRL                           0x0B
#define HEARTRATE13_REG_SLAVE_ADDRESS_KEY                   0x0D
#define HEARTRATE13_REG_SW_RESET                            0x0F
#define HEARTRATE13_REG_MODE                                0x10
#define HEARTRATE13_REG_SLOT_EN                             0x11
#define HEARTRATE13_REG_FSAMPLE                             0x12
#define HEARTRATE13_REG_PD_LED_SELECT                       0x14
#define HEARTRATE13_REG_NUM_AVG                             0x15
#define HEARTRATE13_REG_BG_MEAS_A                           0x16
#define HEARTRATE13_REG_INT_SEQ_A                           0x17
#define HEARTRATE13_REG_SLOTA_CH1_OFFSET                    0x18
#define HEARTRATE13_REG_SLOTA_CH2_OFFSET                    0x19
#define HEARTRATE13_REG_SLOTA_CH3_OFFSET                    0x1A
#define HEARTRATE13_REG_SLOTA_CH4_OFFSET                    0x1B
#define HEARTRATE13_REG_BG_MEAS_B                           0x1C
#define HEARTRATE13_REG_INT_SEQ_B                           0x1D
#define HEARTRATE13_REG_SLOTB_CH1_OFFSET                    0x1E
#define HEARTRATE13_REG_SLOTB_CH2_OFFSET                    0x1F
#define HEARTRATE13_REG_SLOTB_CH3_OFFSET                    0x20
#define HEARTRATE13_REG_SLOTB_CH4_OFFSET                    0x21
#define HEARTRATE13_REG_ILED3_COARSE                        0x22
#define HEARTRATE13_REG_ILED1_COARSE                        0x23
#define HEARTRATE13_REG_ILED2_COARSE                        0x24
#define HEARTRATE13_REG_ILED_FINE                           0x25
#define HEARTRATE13_REG_SLOTA_LED_PULSE                     0x30
#define HEARTRATE13_REG_SLOTA_NUMPULSES                     0x31
#define HEARTRATE13_REG_LED_DISABLE                         0x34
#define HEARTRATE13_REG_SLOTB_LED_PULSE                     0x35
#define HEARTRATE13_REG_SLOTB_NUMPULSES                     0x36
#define HEARTRATE13_REG_ALT_PWR_DN                          0x37
#define HEARTRATE13_REG_EXT_SYNC_STARTUP                    0x38
#define HEARTRATE13_REG_SLOTA_AFE_WINDOW                    0x39
#define HEARTRATE13_REG_SLOTB_AFE_WINDOW                    0x3B
#define HEARTRATE13_REG_AFE_PWR_CFG1                        0x3C
#define HEARTRATE13_REG_SLOTA_FLOAT_LED                     0x3E
#define HEARTRATE13_REG_SLOTB_FLOAT_LED                     0x3F
#define HEARTRATE13_REG_SLOTA_TIA_CFG                       0x42
#define HEARTRATE13_REG_SLOTA_AFE_CFG                       0x43
#define HEARTRATE13_REG_SLOTB_TIA_CFG                       0x44
#define HEARTRATE13_REG_SLOTB_AFE_CFG                       0x45
#define HEARTRATE13_REG_SAMPLE_CLK                          0x4B
#define HEARTRATE13_REG_CLK32M_ADJUST                       0x4D
#define HEARTRATE13_REG_EXT_SYNC_SEL                        0x4F
#define HEARTRATE13_REG_CLK32M_CAL_EN                       0x50
#define HEARTRATE13_REG_AFE_PWR_CFG2                        0x54
#define HEARTRATE13_REG_TIA_INDEP_GAIN                      0x55
#define HEARTRATE13_REG_MATH                                0x58
#define HEARTRATE13_REG_FLT_CONFIG_B                        0x59
#define HEARTRATE13_REG_FLT_LED_FIRE                        0x5A
#define HEARTRATE13_REG_FLT_CONFIG_A                        0x5E
#define HEARTRATE13_REG_DATA_ACCESS_CTL                     0x5F
#define HEARTRATE13_REG_FIFO_ACCESS                         0x60
#define HEARTRATE13_REG_SLOTA_PD1_16BIT                     0x64
#define HEARTRATE13_REG_SLOTA_PD2_16BIT                     0x65
#define HEARTRATE13_REG_SLOTA_PD3_16BIT                     0x66
#define HEARTRATE13_REG_SLOTA_PD4_16BIT                     0x67
#define HEARTRATE13_REG_SLOTB_PD1_16BIT                     0x68
#define HEARTRATE13_REG_SLOTB_PD2_16BIT                     0x69
#define HEARTRATE13_REG_SLOTB_PD3_16BIT                     0x6A
#define HEARTRATE13_REG_SLOTB_PD4_16BIT                     0x6B
#define HEARTRATE13_REG_A_PD1_LOW                           0x70
#define HEARTRATE13_REG_A_PD2_LOW                           0x71
#define HEARTRATE13_REG_A_PD3_LOW                           0x72
#define HEARTRATE13_REG_A_PD4_LOW                           0x73
#define HEARTRATE13_REG_A_PD1_HIGH                          0x74
#define HEARTRATE13_REG_A_PD2_HIGH                          0x75
#define HEARTRATE13_REG_A_PD3_HIGH                          0x76
#define HEARTRATE13_REG_A_PD4_HIGH                          0x77
#define HEARTRATE13_REG_B_PD1_LOW                           0x78
#define HEARTRATE13_REG_B_PD2_LOW                           0x79
#define HEARTRATE13_REG_B_PD3_LOW                           0x7A
#define HEARTRATE13_REG_B_PD4_LOW                           0x7B
#define HEARTRATE13_REG_B_PD1_HIGH                          0x7C
#define HEARTRATE13_REG_B_PD2_HIGH                          0x7D
#define HEARTRATE13_REG_B_PD3_HIGH                          0x7E
#define HEARTRATE13_REG_B_PD4_HIGH                          0x7F

/*! @} */ // heartrate13_reg

/**
 * @defgroup heartrate13_set Heart Rate 13 Registers Settings
 * @brief Settings for registers of Heart Rate 13 Click driver.
 */

/**
 * @addtogroup heartrate13_set
 * @{
 */

/**
 * @brief Heart Rate 13 SAMPLE_CLK register settings.
 * @details Specified settings for SAMPLE_CLK register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_SAMPLE_CLK_RESERVED                     0x2600u
#define HEARTRATE13_SAMPLE_CLK_CLK32K_BYP_MASK              0x0100u
#define HEARTRATE13_SAMPLE_CLK_CLK32K_EN_MASK               0x0080u
#define HEARTRATE13_SAMPLE_CLK_CLK32K_ADJUST_MASK           0x003Fu

/**
 * @brief Heart Rate 13 INT_MASK register settings.
 * @details Specified settings for INT_MASK register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_INT_MASK_RESERVED                       0x009Fu
#define HEARTRATE13_INT_MASK_FIFO_INT_MASK                  0x0100u
#define HEARTRATE13_INT_MASK_SLOTB_INT_MASK                 0x0040u
#define HEARTRATE13_INT_MASK_SLOTA_INT_MASK                 0x0020u

/**
 * @brief Heart Rate 13 GPIO_DRV register settings.
 * @details Specified settings for GPIO_DRV register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_GPIO_DRV_GPIO1_DRV_MASK                 0x0200u
#define HEARTRATE13_GPIO_DRV_GPIO1_POL_MASK                 0x0100u
#define HEARTRATE13_GPIO_DRV_GPIO0_ENA_MASK                 0x0004u
#define HEARTRATE13_GPIO_DRV_GPIO0_DRV_MASK                 0x0002u
#define HEARTRATE13_GPIO_DRV_GPIO0_POL_MASK                 0x0001u

/**
 * @brief Heart Rate 13 SLOT_EN register settings.
 * @details Specified settings for SLOT_EN register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_SLOT_EN_RDOUT_MODE_MASK                 0x2000u
#define HEARTRATE13_SLOT_EN_FIFO_OVRN_PREVENT_MASK          0x1000u
#define HEARTRATE13_SLOT_EN_SLOTB_FIFO_MODE_MASK            0x01C0u
#define HEARTRATE13_SLOT_EN_SLOTB_EN_MASK                   0x0020u
#define HEARTRATE13_SLOT_EN_SLOTA_FIFO_MODE_MASK            0x001Cu
#define HEARTRATE13_SLOT_EN_SLOTA_EN_MASK                   0x0001u

/**
 * @brief Heart Rate 13 PD_LED_SELECT register settings.
 * @details Specified settings for PD_LED_SELECT register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_NC_NC_NC_NC      0x0000u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_34_12_NC_NC      0x0100u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_78_56_NC_NC      0x0200u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_1234_NC_NC_NC    0x0300u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_5_6_7_8          0x0400u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_1_2_3_4          0x0500u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_34_56_NC_NC      0x0600u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_5678_NC_NC_NC    0x0700u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_PD_SEL_MASK         0x0F00u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_NC_NC_NC_NC      0x0000u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_34_12_NC_NC      0x0010u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_78_56_NC_NC      0x0020u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_1234_NC_NC_NC    0x0030u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_5_6_7_8          0x0040u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_1_2_3_4          0x0050u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_34_56_NC_NC      0x0060u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_5678_NC_NC_NC    0x0070u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_PD_SEL_MASK         0x00F0u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_LED_FLOAT           0x0000u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_LED_1               0x0004u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_LED_2               0x0008u
#define HEARTRATE13_PD_LED_SELECT_SLOTB_LED_3               0x000Cu
#define HEARTRATE13_PD_LED_SELECT_SLOTB_LED_SEL_MASK        0x000Cu
#define HEARTRATE13_PD_LED_SELECT_SLOTA_LED_FLOAT           0x0000u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_LED_1               0x0001u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_LED_2               0x0002u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_LED_3               0x0003u
#define HEARTRATE13_PD_LED_SELECT_SLOTA_LED_SEL_MASK        0x0003u

/**
 * @brief Heart Rate 13 photodiode LED selector.
 * @details Specified photodiode LED selector of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_LED_GREEN                               1
#define HEARTRATE13_LED_IR                                  2
#define HEARTRATE13_LED_RED                                 3
#define HEARTRATE13_DEFAULT_LED                             HEARTRATE13_LED_GREEN

/**
 * @brief Heart Rate 13 NUM_AVG register settings.
 * @details Specified settings for NUM_AVG register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_NUM_AVG_SLOTB_1                         0x0000u
#define HEARTRATE13_NUM_AVG_SLOTB_2                         0x0100u
#define HEARTRATE13_NUM_AVG_SLOTB_4                         0x0200u
#define HEARTRATE13_NUM_AVG_SLOTB_8                         0x0300u
#define HEARTRATE13_NUM_AVG_SLOTB_16                        0x0400u
#define HEARTRATE13_NUM_AVG_SLOTB_32                        0x0500u
#define HEARTRATE13_NUM_AVG_SLOTB_64                        0x0600u
#define HEARTRATE13_NUM_AVG_SLOTB_128                       0x0700u
#define HEARTRATE13_NUM_AVG_SLOTB_MASK                      0x0700u
#define HEARTRATE13_NUM_AVG_SLOTA_1                         0x0000u
#define HEARTRATE13_NUM_AVG_SLOTA_2                         0x0010u
#define HEARTRATE13_NUM_AVG_SLOTA_4                         0x0020u
#define HEARTRATE13_NUM_AVG_SLOTA_8                         0x0030u
#define HEARTRATE13_NUM_AVG_SLOTA_16                        0x0040u
#define HEARTRATE13_NUM_AVG_SLOTA_32                        0x0050u
#define HEARTRATE13_NUM_AVG_SLOTA_64                        0x0060u
#define HEARTRATE13_NUM_AVG_SLOTA_128                       0x0070u
#define HEARTRATE13_NUM_AVG_SLOTA_MASK                      0x0070u

/**
 * @brief Heart Rate 13 ILEDx_COARSE register settings.
 * @details Specified settings for ILEDx_COARSE register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_ILEDX_COARSE_RESERVED                   0x1000u
#define HEARTRATE13_ILEDX_COARSE_SCALE_10_PCT               0x0000u
#define HEARTRATE13_ILEDX_COARSE_SCALE_100_PCT              0x2000u
#define HEARTRATE13_ILEDX_COARSE_SCALE_MASK                 0x2000u
#define HEARTRATE13_ILEDX_COARSE_SLEW_MIN                   0x0000u
#define HEARTRATE13_ILEDX_COARSE_SLEW_MAX                   0x0070u
#define HEARTRATE13_ILEDX_COARSE_SLEW_MASK                  0x0070u
#define HEARTRATE13_ILEDX_COARSE_COARSE_MIN                 0x0000u
#define HEARTRATE13_ILEDX_COARSE_COARSE_MAX                 0x000Fu
#define HEARTRATE13_ILEDX_COARSE_COARSE_MASK                0x000Fu

/**
 * @brief Heart Rate 13 SLOTA_NUMPULSES register settings.
 * @details Specified settings for SLOTA_NUMPULSES register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_SLOTA_NUMPULSES_PULSES_8                0x0800u
#define HEARTRATE13_SLOTA_NUMPULSES_PULSES_MASK             0xFF00u
#define HEARTRATE13_SLOTA_NUMPULSES_PERIOD_15_US            0x000Eu
#define HEARTRATE13_SLOTA_NUMPULSES_PERIOD_MASK             0x00FFu

/**
 * @brief Heart Rate 13 SLOTA_AFE_WINDOW register settings.
 * @details Specified settings for SLOTA_AFE_WINDOW register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_SLOTA_AFE_WINDOW_WIDTH_4_US             0x2000u
#define HEARTRATE13_SLOTA_AFE_WINDOW_WIDTH_MASK             0xF800u
#define HEARTRATE13_SLOTA_AFE_WINDOW_OFFSET_23_5_US         0x02F0u
#define HEARTRATE13_SLOTA_AFE_WINDOW_OFFSET_MASK            0x07FFu

/**
 * @brief Heart Rate 13 FSAMPLE register settings.
 * @details Specified settings for FSAMPLE register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_INT_OSC                                 32000u
#define HEARTRATE13_FSAMPLE_1000_HZ                         1000u
#define HEARTRATE13_FSAMPLE_MAX                             2000u

/**
 * @brief Heart Rate 13 SW_RESET register settings.
 * @details Specified settings for SW_RESET register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_SW_RESET                                0x0001u

/**
 * @brief Heart Rate 13 MODE register settings.
 * @details Specified settings for MODE register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_MODE_STANDBY                            0x0000u
#define HEARTRATE13_MODE_PROGRAM                            0x0001u
#define HEARTRATE13_MODE_NORMAL                             0x0002u

/**
 * @brief Heart Rate 13 STATUS register settings.
 * @details Specified settings for STATUS register of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_STATUS_FIFO_SAMPLES_MASK                0xFF00u
#define HEARTRATE13_STATUS_SLOTB_INT_MASK                   0x0040u
#define HEARTRATE13_STATUS_SLOTA_INT_MASK                   0x0020u
#define HEARTRATE13_STATUS_CLEAR                            0xFFFFu

/**
 * @brief Heart Rate 13 timeout value for data ready.
 * @details Specified timeout value for data ready of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_TIMEOUT_MS                              5000u

/**
 * @brief Heart Rate 13 device ID value.
 * @details Specified device ID value of Heart Rate 13 Click driver.
 */
#define HEARTRATE13_DEVICE_ID                               0x16
#define HEARTRATE13_DEVICE_ID_MASK                          0xFF

/**
 * @brief Heart Rate 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Heart Rate 13 Click driver.
 */
#define HEARTRATE13_DEVICE_ADDRESS                          0x64

/*! @} */ // heartrate13_set

/**
 * @defgroup heartrate13_map Heart Rate 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Heart Rate 13 Click driver.
 */

/**
 * @addtogroup heartrate13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Heart Rate 13 Click to the selected MikroBUS.
 */
#define HEARTRATE13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.io0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.io1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // heartrate13_map
/*! @} */ // heartrate13

/**
 * @brief Heart Rate 13 Click photodiodes data object.
 * @details Photodiodes data object definition of Heart Rate 13 Click driver.
 */
typedef struct
{
    uint16_t pd1;
    uint16_t pd2;
    uint16_t pd3;

} heartrate13_pd_data_t;

/**
 * @brief Heart Rate 13 Click context object.
 * @details Context object definition of Heart Rate 13 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t io0;           /**< GPIO0 pin. */
    digital_in_t io1;           /**< GPIO1 pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} heartrate13_t;

/**
 * @brief Heart Rate 13 Click configuration object.
 * @details Configuration object definition of Heart Rate 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t io0;             /**< GPIO0 pin. */
    pin_name_t io1;             /**< GPIO1 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} heartrate13_cfg_t;

/**
 * @brief Heart Rate 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HEARTRATE13_OK = 0,
    HEARTRATE13_ERROR = -1

} heartrate13_return_value_t;

/*!
 * @addtogroup heartrate13 Heart Rate 13 Click Driver
 * @brief API for configuring and manipulating Heart Rate 13 Click driver.
 * @{
 */

/**
 * @brief Heart Rate 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #heartrate13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void heartrate13_cfg_setup ( heartrate13_cfg_t *cfg );

/**
 * @brief Heart Rate 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #heartrate13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_init ( heartrate13_t *ctx, heartrate13_cfg_t *cfg );

/**
 * @brief Heart Rate 13 default configuration function.
 * @details This function executes a default configuration of Heart Rate 13
 * Click board.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t heartrate13_default_cfg ( heartrate13_t *ctx );

/**
 * @brief Heart Rate 13 write register function.
 * @details This function writes data word to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_write_register ( heartrate13_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Heart Rate 13 read register function.
 * @details This function reads data word from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_read_register ( heartrate13_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Heart Rate 13 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_check_communication ( heartrate13_t *ctx );

/**
 * @brief Heart Rate 13 get io0 function.
 * @details This function returns the GPIO0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t heartrate13_get_io0_pin ( heartrate13_t *ctx );

/**
 * @brief Heart Rate 13 get io1 function.
 * @details This function returns the GPIO1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t heartrate13_get_io1_pin ( heartrate13_t *ctx );

/**
 * @brief Heart Rate 13 sw reset function.
 * @details This function executes software reset of the device.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_sw_reset ( heartrate13_t *ctx );

/**
 * @brief Heart Rate 13 set mode function.
 * @details This function sets the device operating mode.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Standby,
 *                   @li @c 1 - Program,
 *                   @li @c 2 - Normal.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_set_mode ( heartrate13_t *ctx, uint8_t mode );

/**
 * @brief Heart Rate 13 set adc fsample function.
 * @details This function sets the sample frequency of the device.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @param[in] freq_hz : Sample frequency in Hz (up to 2000 Hz).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_set_adc_fsample ( heartrate13_t *ctx, uint16_t freq_hz );

/**
 * @brief Heart Rate 13 clear status function.
 * @details This function clears the STATUS register.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_clear_status ( heartrate13_t *ctx );

/**
 * @brief Heart Rate 13 wait data ready function.
 * @details This function waits for the data ready interrupt up to @b HEARTRATE13_TIMEOUT_MS 
 * milliseconds and then clears the STATUS registers.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_wait_data_ready ( heartrate13_t *ctx );

/**
 * @brief Heart Rate 13 get pd data function.
 * @details This function waits for the data ready interrupt and then reads data from 
 * photodiodes PD1, PD2, and PD3.
 * @param[in] ctx : Click context object.
 * See #heartrate13_t object definition for detailed explanation.
 * @param[out] pd_data : Photodiodes data.
 * See #heartrate13_pd_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate13_get_pd_data ( heartrate13_t *ctx, heartrate13_pd_data_t *pd_data );

#ifdef __cplusplus
}
#endif
#endif // HEARTRATE13_H

/*! @} */ // heartrate13

// ------------------------------------------------------------------------ END

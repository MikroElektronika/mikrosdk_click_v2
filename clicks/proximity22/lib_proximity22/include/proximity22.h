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
 * @file proximity22.h
 * @brief This file contains API for Proximity 22 Click Driver.
 */

#ifndef PROXIMITY22_H
#define PROXIMITY22_H

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
 * @addtogroup proximity22 Proximity 22 Click Driver
 * @brief API for configuring and manipulating Proximity 22 Click driver.
 * @{
 */

/**
 * @defgroup proximity22_reg Proximity 22 Registers List
 * @brief List of registers of Proximity 22 Click driver.
 */

/**
 * @addtogroup proximity22_reg
 * @{
 */

/**
 * @brief Proximity 22 registers map.
 * @details Specified register map of Proximity 22 Click driver.
 */
#define PROXIMITY22_REG_LOTL                        0x07
#define PROXIMITY22_REG_LOTH                        0x08
#define PROXIMITY22_REG_SNL                         0x09
#define PROXIMITY22_REG_SNH                         0x0A
#define PROXIMITY22_REG_IPTAT                       0x1A
#define PROXIMITY22_REG_ENABLE                      0x80
#define PROXIMITY22_REG_PTIME                       0x82
#define PROXIMITY22_REG_AILTL                       0x84
#define PROXIMITY22_REG_AILTH                       0x85
#define PROXIMITY22_REG_AIHTL                       0x86
#define PROXIMITY22_REG_AIHTH                       0x87
#define PROXIMITY22_REG_PILTL                       0x88
#define PROXIMITY22_REG_PILTH                       0x89
#define PROXIMITY22_REG_PIHTL                       0x8A
#define PROXIMITY22_REG_PIHTH                       0x8B
#define PROXIMITY22_REG_PERS                        0x8C
#define PROXIMITY22_REG_CFG0                        0x8D
#define PROXIMITY22_REG_PCFG0                       0x8E
#define PROXIMITY22_REG_PCFG1                       0x8F
#define PROXIMITY22_REG_PCFG2                       0x90
#define PROXIMITY22_REG_REVID                       0x91
#define PROXIMITY22_REG_ID                          0x92
#define PROXIMITY22_REG_REVID2                      0x93
#define PROXIMITY22_REG_CFG1                        0x94
#define PROXIMITY22_REG_AGAIN_1_0                   0x95
#define PROXIMITY22_REG_AGAIN_3_2                   0x96
#define PROXIMITY22_REG_LDR0_CFG                    0x9A
#define PROXIMITY22_REG_LDR1_CFG                    0x9B
#define PROXIMITY22_REG_EYE_SAFETY_CFG              0x9E
#define PROXIMITY22_REG_EYE_SAFETY_STATUS           0x9F
#define PROXIMITY22_REG_STATUS                      0xA0
#define PROXIMITY22_REG_STATUS_2                    0xA1
#define PROXIMITY22_REG_STATUS_3                    0xA2
#define PROXIMITY22_REG_PID_L                       0xA5
#define PROXIMITY22_REG_PID_H                       0xA6
#define PROXIMITY22_REG_CFG2                        0xA7
#define PROXIMITY22_REG_RESET                       0xA8
#define PROXIMITY22_REG_CFG3                        0xAB
#define PROXIMITY22_REG_CFG6                        0xAE
#define PROXIMITY22_REG_PWM_CFG                     0xB0
#define PROXIMITY22_REG_VSYNC_CFG                   0xB1
#define PROXIMITY22_REG_VSYNC_PRD_L                 0xB2
#define PROXIMITY22_REG_VSYNC_PRD_H                 0xB3
#define PROXIMITY22_REG_PWM_PRD_L                   0xB5
#define PROXIMITY22_REG_PWM_PRD_H                   0xB6
#define PROXIMITY22_REG_PWM_HIP_L                   0xB7
#define PROXIMITY22_REG_PWM_HIP_H                   0xB8
#define PROXIMITY22_REG_POFFSET                     0xC0
#define PROXIMITY22_REG_POFFSET_SIGN                0xC1
#define PROXIMITY22_REG_AZ_CONFIG                   0xD6
#define PROXIMITY22_REG_CALIB                       0xD7
#define PROXIMITY22_REG_CALIB_OFFSET                0xD8
#define PROXIMITY22_REG_CALIBCFG                    0xD9
#define PROXIMITY22_REG_PCFG4                       0xDA
#define PROXIMITY22_REG_CALIBSTAT                   0xDC
#define PROXIMITY22_REG_INTENAB                     0xDD
#define PROXIMITY22_REG_INTENAB_2                   0xDE
#define PROXIMITY22_REG_ASD_L                       0xE0
#define PROXIMITY22_REG_ASD_H                       0xE1
#define PROXIMITY22_REG_ASP1_L                      0xE2
#define PROXIMITY22_REG_ASP1_H                      0xE3
#define PROXIMITY22_REG_ASP2_L                      0xE4
#define PROXIMITY22_REG_ASP2_H                      0xE5
#define PROXIMITY22_REG_ATIME                       0xE6
#define PROXIMITY22_REG_AWTIME                      0xE7
#define PROXIMITY22_REG_ACFG                        0xE8
#define PROXIMITY22_REG_PSD_L                       0xEA
#define PROXIMITY22_REG_PSD_H                       0xEB
#define PROXIMITY22_REG_PWTIME                      0xEC
#define PROXIMITY22_REG_FIFO_STATUS_1               0xF0
#define PROXIMITY22_REG_FIFO_CONTROL                0xF1
#define PROXIMITY22_REG_PDATA_L                     0xF4
#define PROXIMITY22_REG_PDATA_H                     0xF5
#define PROXIMITY22_REG_TDATA_L                     0xF6
#define PROXIMITY22_REG_TDATA_H                     0xF7
#define PROXIMITY22_REG_FIFO_ADATA_7                0xF8
#define PROXIMITY22_REG_FIFO_ADATA_6                0xF9
#define PROXIMITY22_REG_FIFO_ADATA_5                0xFA
#define PROXIMITY22_REG_FIFO_ADATA_4                0xFB
#define PROXIMITY22_REG_FIFO_ADATA_3                0xFC
#define PROXIMITY22_REG_FIFO_ADATA_2                0xFD
#define PROXIMITY22_REG_FIFO_ADATA_1                0xFE
#define PROXIMITY22_REG_FIFO_ADATA_0                0xFF

/*! @} */ // proximity22_reg

/**
 * @defgroup proximity22_set Proximity 22 Registers Settings
 * @brief Settings for registers of Proximity 22 Click driver.
 */

/**
 * @addtogroup proximity22_set
 * @{
 */

/**
 * @brief Proximity 22 IPTAT register setting.
 * @details Specified setting for IPTAT register of Proximity 22 Click driver.
 */
#define PROXIMITY22_IPTAT_INIT                      0x03

/**
 * @brief Proximity 22 ENABLE register setting.
 * @details Specified setting for ENABLE register of Proximity 22 Click driver.
 */
#define PROXIMITY22_ENABLE_PVSYNC_EN                0x80
#define PROXIMITY22_ENABLE_AVSYNC_EN                0x40
#define PROXIMITY22_ENABLE_TEN                      0x20
#define PROXIMITY22_ENABLE_PWEN                     0x10
#define PROXIMITY22_ENABLE_AWEN                     0x08
#define PROXIMITY22_ENABLE_PEN                      0x04
#define PROXIMITY22_ENABLE_AEN                      0x02
#define PROXIMITY22_ENABLE_PON                      0x01

/**
 * @brief Proximity 22 PTIME register setting.
 * @details Specified setting for PTIME register of Proximity 22 Click driver.
 */
#define PROXIMITY22_PTIME_88_US                     0x00
#define PROXIMITY22_PTIME_2_816_MS                  0x1F
#define PROXIMITY22_PTIME_22_528_US                 0xFF

/**
 * @brief Proximity 22 PCFG0 register setting.
 * @details Specified setting for PCFG0 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_PCFG0_PGAIN_1X                  0x00
#define PROXIMITY22_PCFG0_PGAIN_2X                  0x20
#define PROXIMITY22_PCFG0_PGAIN_4X                  0x40
#define PROXIMITY22_PCFG0_PGAIN_8X                  0x60
#define PROXIMITY22_PCFG0_PGAIN_16X                 0x80
#define PROXIMITY22_PCFG0_PGAIN_MASK                0xE0
#define PROXIMITY22_PCFG0_PGAIN2_2_5X               0x00
#define PROXIMITY22_PCFG0_PGAIN2_5X                 0x01
#define PROXIMITY22_PCFG0_PGAIN2_10X                0x03
#define PROXIMITY22_PCFG0_PGAIN2_MASK               0x03

/**
 * @brief Proximity 22 PCFG1 register setting.
 * @details Specified setting for PCFG1 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_PCFG1_PPULSE_LENH_MASK          0xC0
#define PROXIMITY22_PCFG1_PPULSE_1                  0x00
#define PROXIMITY22_PCFG1_PPULSE_32                 0x1F
#define PROXIMITY22_PCFG1_PPULSE_64                 0x3F
#define PROXIMITY22_PCFG1_PPULSE_MASK               0x3F

/**
 * @brief Proximity 22 PCFG2 register setting.
 * @details Specified setting for PCFG2 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_PCFG2_PPULSE_LENL_2_US          0x00
#define PROXIMITY22_PCFG2_PPULSE_LENL_34_US         0x20
#define PROXIMITY22_PCFG2_PPULSE_LENL_257_US        0xFF

/**
 * @brief Proximity 22 ID register setting.
 * @details Specified setting for ID register of Proximity 22 Click driver.
 */
#define PROXIMITY22_DEVICE_ID                       0x82

/**
 * @brief Proximity 22 CFG1 register setting.
 * @details Specified setting for CFG1 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_CFG1_PD_MUX_SEL_TWO_CHANN_MODE  0x00
#define PROXIMITY22_CFG1_PD_MUX_SEL_COLOR_MODE      0x06
#define PROXIMITY22_CFG1_PD_MUX_SEL_MASK            0x0E
#define PROXIMITY22_CFG1_ENAB_TEMP_SENSOR           0x01

/**
 * @brief Proximity 22 AGAIN_1_0/AGAIN_3_2 register setting.
 * @details Specified setting for AGAIN_1_0/AGAIN_3_2 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_AGAIN_1X                        0x00
#define PROXIMITY22_AGAIN_2X                        0x01
#define PROXIMITY22_AGAIN_4X                        0x02
#define PROXIMITY22_AGAIN_8X                        0x03
#define PROXIMITY22_AGAIN_16X                       0x04
#define PROXIMITY22_AGAIN_32X                       0x05
#define PROXIMITY22_AGAIN_64X                       0x06
#define PROXIMITY22_AGAIN_128X                      0x07
#define PROXIMITY22_AGAIN_256X                      0x08
#define PROXIMITY22_AGAIN_512X                      0x09
#define PROXIMITY22_AGAIN_1024X                     0x0A
#define PROXIMITY22_AGAIN_2048X                     0x0B
#define PROXIMITY22_AGAIN_4096X                     0x0C

/**
 * @brief Proximity 22 LDR0_CFG register setting.
 * @details Specified setting for LDR0_CFG register of Proximity 22 Click driver.
 */
#define PROXIMITY22_LDR0_CFG_EN_LDR_0               0x40
#define PROXIMITY22_LDR0_CFG_ISINK_LSB_0_5_MA       0x00
#define PROXIMITY22_LDR0_CFG_ISINK_LSB_1_0_MA       0x10
#define PROXIMITY22_LDR0_CFG_ISINK_LSB_1_5_MA       0x20
#define PROXIMITY22_LDR0_CFG_ISINK_LSB_2_0_MA       0x30
#define PROXIMITY22_LDR0_CFG_ISINK_LSB_MASK         0x30
#define PROXIMITY22_LDR0_CFG_PLDRIVE0_0             0x00
#define PROXIMITY22_LDR0_CFG_PLDRIVE0_4             0x04
#define PROXIMITY22_LDR0_CFG_PLDRIVE0_15            0x0F
#define PROXIMITY22_LDR0_CFG_PLDRIVE0_MASK          0x0F

/**
 * @brief Proximity 22 LDR1_CFG register setting.
 * @details Specified setting for LDR1_CFG register of Proximity 22 Click driver.
 */
#define PROXIMITY22_LDR1_CFG_EN_LDR_1               0x40
#define PROXIMITY22_LDR1_CFG_PLDRIVE1_0             0x00
#define PROXIMITY22_LDR1_CFG_PLDRIVE1_4             0x04
#define PROXIMITY22_LDR1_CFG_PLDRIVE1_15            0x0F
#define PROXIMITY22_LDR1_CFG_PLDRIVE1_MASK          0x0F

/**
 * @brief Proximity 22 STATUS_3 register setting.
 * @details Specified setting for STATUS_3 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_STATUS_3_PWM_PRD_CHG_INT        0x80
#define PROXIMITY22_STATUS_3_ATINT                  0x10
#define PROXIMITY22_STATUS_3_FTINT                  0x08
#define PROXIMITY22_STATUS_3_AWINT                  0x04
#define PROXIMITY22_STATUS_3_ASAT                   0x02
#define PROXIMITY22_STATUS_3_AINT                   0x01

/**
 * @brief Proximity 22 RESET register setting.
 * @details Specified setting for RESET register of Proximity 22 Click driver.
 */
#define PROXIMITY22_RESET_INV_XRES                  0x08
#define PROXIMITY22_RESET_ENAB_XRES                 0x04
#define PROXIMITY22_RESET_HARD_RESET                0x02
#define PROXIMITY22_RESET_SOFT_RESET                0x01

/**
 * @brief Proximity 22 CFG3 register setting.
 * @details Specified setting for CFG3 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_CFG3_INT_READ_CLEAR             0x80
#define PROXIMITY22_CFG3_MODE_CFG_SEQUENTIAL        0x00
#define PROXIMITY22_CFG3_MODE_CFG_CONCURRENT        0x20
#define PROXIMITY22_CFG3_MODE_CFG_FULL_PARALLEL     0x40
#define PROXIMITY22_CFG3_MODE_CFG_MASK              0x60
#define PROXIMITY22_CFG3_SAI                        0x10
#define PROXIMITY22_CFG3_PID_EN                     0x08
#define PROXIMITY22_CFG3_RESERVED                   0x01

/**
 * @brief Proximity 22 CFG6 register setting.
 * @details Specified setting for CFG6 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_CFG6_DISABLE_APC                0x40
#define PROXIMITY22_CFG6_RESERVED                   0x3F

/**
 * @brief Proximity 22 CALIB register setting.
 * @details Specified setting for CALIB register of Proximity 22 Click driver.
 */
#define PROXIMITY22_CALIB_OFFCAL_ENAB_AVG           0x80
#define PROXIMITY22_CALIB_ELECTRICAL_CALIBRATION    0x20
#define PROXIMITY22_CALIB_PTIME_IN_CALIB            0x10
#define PROXIMITY22_CALIB_START_OFFSET_CAL          0x01

/**
 * @brief Proximity 22 CALIBCFG register setting.
 * @details Specified setting for CALIBCFG register of Proximity 22 Click driver.
 */
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_3       0x00
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_7       0x20
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_15      0x40
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_31      0x60
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_63      0x80
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_127     0xA0
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_255     0xC0
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_511     0xE0
#define PROXIMITY22_CALIBCFG_BINSRCH_TARGET_MASK    0xE0
#define PROXIMITY22_CALIBCFG_RESERVED               0x10
#define PROXIMITY22_CALIBCFG_PROX_AUTO_OFFSET_ADJ   0x08
#define PROXIMITY22_CALIBCFG_PROX_DATA_AVG_DIS      0x00
#define PROXIMITY22_CALIBCFG_PROX_DATA_AVG_2        0x01
#define PROXIMITY22_CALIBCFG_PROX_DATA_AVG_4        0x02
#define PROXIMITY22_CALIBCFG_PROX_DATA_AVG_8        0x03
#define PROXIMITY22_CALIBCFG_PROX_DATA_AVG_16       0x04
#define PROXIMITY22_CALIBCFG_PROX_DATA_AVG_MASK     0x07

/**
 * @brief Proximity 22 CALIBSTAT register setting.
 * @details Specified setting for CALIBSTAT register of Proximity 22 Click driver.
 */
#define PROXIMITY22_CALIBSTAT_OFFSET_ADJUSTED       0x04
#define PROXIMITY22_CALIBSTAT_CALIB_FINISHED        0x01

/**
 * @brief Proximity 22 INTENAB_2 register setting.
 * @details Specified setting for INTENAB_2 register of Proximity 22 Click driver.
 */
#define PROXIMITY22_INTENAB_2_PWMIEN                0x80
#define PROXIMITY22_INTENAB_2_ESIEN                 0x10
#define PROXIMITY22_INTENAB_2_ATIEN                 0x08
#define PROXIMITY22_INTENAB_2_FTIEN                 0x04
#define PROXIMITY22_INTENAB_2_PWIEN                 0x02
#define PROXIMITY22_INTENAB_2_AWIEN                 0x01

/**
 * @brief Proximity 22 ATIME register setting.
 * @details Specified setting for ATIME register of Proximity 22 Click driver.
 */
#define PROXIMITY22_ATIME_2_779_MS                  0x00
#define PROXIMITY22_ATIME_88_923_MS                 0x1F
#define PROXIMITY22_ATIME_711_381_MS                0xFF

/**
 * @brief Proximity 22 AWTIME register setting.
 * @details Specified setting for AWTIME register of Proximity 22 Click driver.
 */
#define PROXIMITY22_AWTIME_2_779_MS                 0x00
#define PROXIMITY22_AWTIME_200_088_MS               0x47
#define PROXIMITY22_AWTIME_711_381_MS               0xFF

/**
 * @brief Proximity 22 FIFO_CONTROL register setting.
 * @details Specified setting for FIFO_CONTROL register of Proximity 22 Click driver.
 */
#define PROXIMITY22_FIFO_CONTROL_FIFO_LVL_LSB       0x40
#define PROXIMITY22_FIFO_CONTROL_FIFO_THR_LVL_MASK  0x38
#define PROXIMITY22_FIFO_CONTROL_FIFO_CLR           0x04
#define PROXIMITY22_FIFO_CONTROL_FIFO_EMPTY         0x02
#define PROXIMITY22_FIFO_CONTROL_FIFO_OVF           0x01

/**
 * @brief Proximity 22 temperature calculation setting.
 * @details Specified setting for temperature calculation of Proximity 22 Click driver.
 */
#define PROXIMITY22_TEMP_OFFSET                     399.0
#define PROXIMITY22_TEMP_RES                        1.48

/**
 * @brief Proximity 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 22 Click driver.
 */
#define PROXIMITY22_DEVICE_ADDRESS                  0x39

/*! @} */ // proximity22_set

/**
 * @defgroup proximity22_map Proximity 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 22 Click driver.
 */

/**
 * @addtogroup proximity22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 22 Click to the selected MikroBUS.
 */
#define PROXIMITY22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity22_map
/*! @} */ // proximity22

/**
 * @brief Proximity 22 Click context object.
 * @details Context object definition of Proximity 22 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} proximity22_t;

/**
 * @brief Proximity 22 Click configuration object.
 * @details Configuration object definition of Proximity 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} proximity22_cfg_t;

/**
 * @brief Proximity 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY22_OK = 0,
    PROXIMITY22_ERROR = -1

} proximity22_return_value_t;

/**
 * @brief Proximity 22 Click als data object.
 * @details ALS data object definition of Proximity 22 Click driver.
 */
typedef struct
{
    uint16_t clear;             /**< Clear data counts. */
    uint16_t red;               /**< Red data counts. */
    uint16_t green;             /**< Green data counts. */
    uint16_t blue;              /**< Blue data counts. */
    
} proximity22_als_t;

/**
 * @brief Proximity 22 Click data object.
 * @details Data object definition of Proximity 22 Click driver.
 */
typedef struct
{
    uint16_t proximity;         /**< Proximity data. */
    float temperature;          /**< Temperature data in degC. */
    proximity22_als_t als;      /**< ALS data. */
    
} proximity22_data_t;

/*!
 * @addtogroup proximity22 Proximity 22 Click Driver
 * @brief API for configuring and manipulating Proximity 22 Click driver.
 * @{
 */

/**
 * @brief Proximity 22 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity22_cfg_setup ( proximity22_cfg_t *cfg );

/**
 * @brief Proximity 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity22_init ( proximity22_t *ctx, proximity22_cfg_t *cfg );

/**
 * @brief Proximity 22 default configuration function.
 * @details This function executes a default configuration of Proximity 22
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity22_default_cfg ( proximity22_t *ctx );

/**
 * @brief Proximity 22 write registers function.
 * @details This function writes a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_write_regs ( proximity22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Proximity 22 read registers function.
 * @details This function reads a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory where read data will be stored.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_read_regs ( proximity22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Proximity 22 write register function.
 * @details This function writes a single byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_write_reg ( proximity22_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Proximity 22 read register function.
 * @details This function reads a single byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_read_reg ( proximity22_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Proximity 22 set RST pin function.
 * @details This function sets the logic state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[in] state : Logic state (0 or 1).
 * @note None.
 */
void proximity22_set_rst_pin ( proximity22_t *ctx, uint8_t state );

/**
 * @brief Proximity 22 get INT pin function.
 * @details This function returns the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @return Logic state of INT pin.
 * @note None.
 */
uint8_t proximity22_get_int_pin ( proximity22_t *ctx );

/**
 * @brief Proximity 22 reset device function.
 * @details This function performs a hardware reset by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @note None.
 */
void proximity22_reset_device ( proximity22_t *ctx );

/**
 * @brief Proximity 22 check communication function.
 * @details This function checks device ID to verify communication.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @return @li @c  0 - Success (correct device ID),
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_check_comm ( proximity22_t *ctx );

/**
 * @brief Proximity 22 software reset function.
 * @details This function performs a software reset by writing to the RESET register.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_soft_reset ( proximity22_t *ctx );

/**
 * @brief Proximity 22 clear FIFO function.
 * @details This function clears the FIFO buffer.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_clear_fifo ( proximity22_t *ctx );

/**
 * @brief Proximity 22 read proximity function.
 * @details This function reads proximity measurement data.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[out] prox : Pointer to memory where proximity data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_read_prox ( proximity22_t *ctx, uint16_t *prox );

/**
 * @brief Proximity 22 read temperature function.
 * @details This function reads and converts internal temperature data.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[out] temp : Pointer to memory where temperature value (degC) will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_read_temp ( proximity22_t *ctx, float *temp );

/**
 * @brief Proximity 22 read ALS data function.
 * @details This function reads ambient light sensor (ALS) data from FIFO.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[out] als : Pointer to #proximity22_als_t structure for storing ALS data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_read_als ( proximity22_t *ctx, proximity22_als_t *als );

/**
 * @brief Proximity 22 read sensor data function.
 * @details This function reads proximity, temperature, and ALS data if available.
 * @param[in] ctx : Click context object.
 * See #proximity22_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to #proximity22_data_t structure to store sensor data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proximity22_read_data ( proximity22_t *ctx, proximity22_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY22_H

/*! @} */ // proximity22

// ------------------------------------------------------------------------ END

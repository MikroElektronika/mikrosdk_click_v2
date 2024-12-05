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
 * @file mlvibrosens.h
 * @brief This file contains API for ML Vibro Sens Click Driver.
 */

#ifndef MLVIBROSENS_H
#define MLVIBROSENS_H

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
 * @addtogroup mlvibrosens ML Vibro Sens Click Driver
 * @brief API for configuring and manipulating ML Vibro Sens Click driver.
 * @{
 */

/**
 * @defgroup mlvibrosens_reg ML Vibro Sens Registers List
 * @brief List of registers of ML Vibro Sens Click driver.
 */

/**
 * @addtogroup mlvibrosens_reg
 * @{
 */

/**
 * @brief ML Vibro Sens register list.
 * @details Specified register list of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_REG_INT_STATUS                  0x00
#define MLVIBROSENS_REG_TEMP_OUT                    0x01
#define MLVIBROSENS_REG_VECM_LSB                    0x02
#define MLVIBROSENS_REG_VECM_MSB                    0x03
#define MLVIBROSENS_REG_OUT_X_LSB                   0x04
#define MLVIBROSENS_REG_OUT_X_MSB                   0x05
#define MLVIBROSENS_REG_OUT_Y_LSB                   0x06
#define MLVIBROSENS_REG_OUT_Y_MSB                   0x07
#define MLVIBROSENS_REG_OUT_Z_LSB                   0x08
#define MLVIBROSENS_REG_OUT_Z_MSB                   0x09
#define MLVIBROSENS_REG_BUF_STATUS                  0x0B
#define MLVIBROSENS_REG_BUF_X_LSB                   0x0C
#define MLVIBROSENS_REG_BUF_X_MSB                   0x0D
#define MLVIBROSENS_REG_BUF_Y_LSB                   0x0E
#define MLVIBROSENS_REG_BUF_Y_MSB                   0x0F
#define MLVIBROSENS_REG_BUF_Z_LSB                   0x10
#define MLVIBROSENS_REG_BUF_Z_MSB                   0x11
#define MLVIBROSENS_REG_PROD_REV                    0x12
#define MLVIBROSENS_REG_WHO_AM_I                    0x13
#define MLVIBROSENS_REG_SYS_MODE                    0x14
#define MLVIBROSENS_REG_SENS_CONFIG1                0x15
#define MLVIBROSENS_REG_SENS_CONFIG2                0x16
#define MLVIBROSENS_REG_SENS_CONFIG3                0x17
#define MLVIBROSENS_REG_SENS_CONFIG4                0x18
#define MLVIBROSENS_REG_SENS_CONFIG5                0x19
#define MLVIBROSENS_REG_WAKE_IDLE_LSB               0x1A
#define MLVIBROSENS_REG_WAKE_IDLE_MSB               0x1B
#define MLVIBROSENS_REG_SLEEP_IDLE_LSB              0x1C
#define MLVIBROSENS_REG_SLEEP_IDLE_MSB              0x1D
#define MLVIBROSENS_REG_ASLP_COUNT_LSB              0x1E
#define MLVIBROSENS_REG_ASLP_COUNT_MSB              0x1F
#define MLVIBROSENS_REG_INT_EN                      0x20
#define MLVIBROSENS_REG_INT_PIN_SEL                 0x21
#define MLVIBROSENS_REG_OFF_X                       0x22
#define MLVIBROSENS_REG_OFF_Y                       0x23
#define MLVIBROSENS_REG_OFF_Z                       0x24
#define MLVIBROSENS_REG_BUF_CONFIG1                 0x26
#define MLVIBROSENS_REG_BUF_CONFIG2                 0x27
#define MLVIBROSENS_REG_ORIENT_STATUS               0x28
#define MLVIBROSENS_REG_ORIENT_CONFIG               0x29
#define MLVIBROSENS_REG_ORIENT_DBCOUNT              0x2A
#define MLVIBROSENS_REG_ORIENT_BF_ZCOMP             0x2B
#define MLVIBROSENS_REG_ORIENT_THS_REG              0x2C
#define MLVIBROSENS_REG_SDCD_INT_SRC1               0x2D
#define MLVIBROSENS_REG_SDCD_INT_SRC2               0x2E
#define MLVIBROSENS_REG_SDCD_CONFIG1                0x2F
#define MLVIBROSENS_REG_SDCD_CONFIG2                0x30
#define MLVIBROSENS_REG_SDCD_OT_DBCNT               0x31
#define MLVIBROSENS_REG_SDCD_WT_DBCNT               0x32
#define MLVIBROSENS_REG_SDCD_LTHS_LSB               0x33
#define MLVIBROSENS_REG_SDCD_LTHS_MSB               0x34
#define MLVIBROSENS_REG_SDCD_UTHS_LSB               0x35
#define MLVIBROSENS_REG_SDCD_UTHS_MSB               0x36
#define MLVIBROSENS_REG_SELF_TEST_CONFIG1           0x37
#define MLVIBROSENS_REG_SELF_TEST_CONFIG2           0x38

/*! @} */ // mlvibrosens_reg

/**
 * @defgroup mlvibrosens_set ML Vibro Sens Registers Settings
 * @brief Settings for registers of ML Vibro Sens Click driver.
 */

/**
 * @addtogroup mlvibrosens_set
 * @{
 */

/**
 * @brief ML Vibro Sens INT_STATUS register setting.
 * @details Specified setting for INT_STATUS register of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_INT_STATUS_SRC_DRDY             0x80
#define MLVIBROSENS_INT_STATUS_SRC_OVF              0x40
#define MLVIBROSENS_INT_STATUS_SRC_BUF              0x20
#define MLVIBROSENS_INT_STATUS_SRC_SDCD_OT          0x10
#define MLVIBROSENS_INT_STATUS_SRC_SDCD_WT          0x08
#define MLVIBROSENS_INT_STATUS_SRC_ORIENT           0x04
#define MLVIBROSENS_INT_STATUS_SRC_ASLP             0x02
#define MLVIBROSENS_INT_STATUS_SRC_BOOT             0x01

/**
 * @brief ML Vibro Sens WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_WHO_AM_I                        0x86

/**
 * @brief ML Vibro Sens SENS_CONFIG1 register setting.
 * @details Specified setting for SENS_CONFIG1 register of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_SENS_CONFIG1_RST                0x80
#define MLVIBROSENS_SENS_CONFIG1_ST_AXIS_SEL_DIS    0x00
#define MLVIBROSENS_SENS_CONFIG1_ST_AXIS_SEL_X      0x20
#define MLVIBROSENS_SENS_CONFIG1_ST_AXIS_SEL_Y      0x40
#define MLVIBROSENS_SENS_CONFIG1_ST_AXIS_SEL_Z      0x60
#define MLVIBROSENS_SENS_CONFIG1_ST_AXIS_SEL_MASK   0x60
#define MLVIBROSENS_SENS_CONFIG1_ST_POL             0x10
#define MLVIBROSENS_SENS_CONFIG1_SPI_M_4_WIRE       0x00
#define MLVIBROSENS_SENS_CONFIG1_SPI_M_3_WIRE       0x08
#define MLVIBROSENS_SENS_CONFIG1_SPI_M_MASK         0x08
#define MLVIBROSENS_SENS_CONFIG1_FSR_2G             0x00
#define MLVIBROSENS_SENS_CONFIG1_FSR_4G             0x02
#define MLVIBROSENS_SENS_CONFIG1_FSR_8G             0x04
#define MLVIBROSENS_SENS_CONFIG1_FSR_16G            0x06
#define MLVIBROSENS_SENS_CONFIG1_FSR_MASK           0x06
#define MLVIBROSENS_SENS_CONFIG1_MODE_STANDBY       0x00
#define MLVIBROSENS_SENS_CONFIG1_MODE_ACTIVE        0x01
#define MLVIBROSENS_SENS_CONFIG1_MODE_MASK          0x01

/**
 * @brief ML Vibro Sens SENS_CONFIG3 register setting.
 * @details Specified setting for SENS_CONFIG3 register of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_SENS_CONFIG3_WAKE_ODR_MASK      0xF0
#define MLVIBROSENS_SENS_CONFIG3_SLEEP_ODR_MASK     0x0F

/**
 * @brief ML Vibro Sens SENS_CONFIG4 register setting.
 * @details Specified setting for SENS_CONFIG4 register of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_SENS_CONFIG4_EXT_TRIG_M         0x80
#define MLVIBROSENS_SENS_CONFIG4_WAKE_SDCD_WT       0x40
#define MLVIBROSENS_SENS_CONFIG4_WAKE_SDCD_OT       0x20
#define MLVIBROSENS_SENS_CONFIG4_WAKE_ORIENT        0x10
#define MLVIBROSENS_SENS_CONFIG4_DRDY_PUL           0x08
#define MLVIBROSENS_SENS_CONFIG4_INT2_FUNC          0x04
#define MLVIBROSENS_SENS_CONFIG4_INT_PP_OD          0x02
#define MLVIBROSENS_SENS_CONFIG4_INT_POL            0x01
#define MLVIBROSENS_SENS_CONFIG4_INT_PP_LOW         0x00

/**
 * @brief ML Vibro Sens INT_EN register setting.
 * @details Specified setting for INT_EN register of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_INT_EN_DRDY                     0x80
#define MLVIBROSENS_INT_EN_BUF                      0x40
#define MLVIBROSENS_INT_EN_SDCD_OT                  0x20
#define MLVIBROSENS_INT_EN_SDCD_WT                  0x10
#define MLVIBROSENS_INT_EN_ORIENT                   0x08
#define MLVIBROSENS_INT_EN_ASLP                     0x04
#define MLVIBROSENS_INT_EN_BOOT_DIS                 0x02
#define MLVIBROSENS_INT_EN_WAKE_OUT                 0x01

/**
 * @brief ML Vibro Sens INT_PIN_SEL register setting.
 * @details Specified setting for INT_PIN_SEL register of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_INT_PIN_SEL_DRDY_INT2           0x80
#define MLVIBROSENS_INT_PIN_SEL_BUF_INT2            0x40
#define MLVIBROSENS_INT_PIN_SEL_SDCD_OT_INT2        0x20
#define MLVIBROSENS_INT_PIN_SEL_SDCD_WT_INT2        0x10
#define MLVIBROSENS_INT_PIN_SEL_ORIENT_INT2         0x08
#define MLVIBROSENS_INT_PIN_SEL_ASLP_INT2           0x04
#define MLVIBROSENS_INT_PIN_SEL_BOOT_INT2           0x02
#define MLVIBROSENS_INT_PIN_SEL_WAKE_OUT_INT2       0x01
#define MLVIBROSENS_INT_PIN_SEL_ALL_INT1            0x00

/**
 * @brief ML Vibro Sens operating mode setting.
 * @details Specified setting for operating mode of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_MODE_STANDBY                    0
#define MLVIBROSENS_MODE_ACTIVE                     1

/**
 * @brief ML Vibro Sens FSR setting.
 * @details Specified setting for FSR of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_FSR_2G                          0
#define MLVIBROSENS_FSR_4G                          1
#define MLVIBROSENS_FSR_8G                          2
#define MLVIBROSENS_FSR_16G                         3

/**
 * @brief ML Vibro Sens ODR setting.
 * @details Specified setting for ODR of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_ODR_3200_HZ                     0
#define MLVIBROSENS_ODR_1600_HZ                     1
#define MLVIBROSENS_ODR_800_HZ                      2
#define MLVIBROSENS_ODR_400_HZ                      3
#define MLVIBROSENS_ODR_200_HZ                      4
#define MLVIBROSENS_ODR_100_HZ                      5
#define MLVIBROSENS_ODR_50_HZ                       6
#define MLVIBROSENS_ODR_25_HZ                       7
#define MLVIBROSENS_ODR_12_5_HZ                     8
#define MLVIBROSENS_ODR_6_25_HZ                     9
#define MLVIBROSENS_ODR_3_125_HZ                    10
#define MLVIBROSENS_ODR_1_563_HZ                    11
#define MLVIBROSENS_ODR_0_781_HZ                    12

/**
 * @brief ML Vibro Sens LSB/g setting.
 * @details Specified setting for LSB/g of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_LSB_PER_G_FSR_2G                1024
#define MLVIBROSENS_LSB_PER_G_FSR_4G                512
#define MLVIBROSENS_LSB_PER_G_FSR_8G                256
#define MLVIBROSENS_LSB_PER_G_FSR_16G               128

/**
 * @brief ML Vibro Sens temperature offset setting.
 * @details Specified setting for temperature offset of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_TEMP_OFFSET                     25

/**
 * @brief ML Vibro Sens vibro motor state setting.
 * @details Specified setting for vibro motor state of ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_VIBRO_STATE_IDLE                0
#define MLVIBROSENS_VIBRO_STATE_BALANCED            1
#define MLVIBROSENS_VIBRO_STATE_UNBALANCED          2
#define MLVIBROSENS_VIBRO_STATE_BOTH                3

/**
 * @brief ML Vibro Sens device address setting.
 * @details Specified setting for device slave address selection of
 * ML Vibro Sens Click driver.
 */
#define MLVIBROSENS_DEVICE_ADDRESS_0                0x18
#define MLVIBROSENS_DEVICE_ADDRESS_1                0x19

/*! @} */ // mlvibrosens_set

/**
 * @defgroup mlvibrosens_map ML Vibro Sens MikroBUS Map
 * @brief MikroBUS pin mapping of ML Vibro Sens Click driver.
 */

/**
 * @addtogroup mlvibrosens_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ML Vibro Sens Click to the selected MikroBUS.
 */
#define MLVIBROSENS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.bal = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.unb = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // mlvibrosens_map
/*! @} */ // mlvibrosens

/**
 * @brief ML Vibro Sens Click context object.
 * @details Context object definition of ML Vibro Sens Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t bal;          /**< Balanced control pin (active high). */
    digital_out_t unb;          /**< Unbalanced control pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint16_t lsb_per_g;         /**< LSB/g nominal sensitivity for FSR. */

} mlvibrosens_t;

/**
 * @brief ML Vibro Sens Click configuration object.
 * @details Configuration object definition of ML Vibro Sens Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t bal;             /**< Balanced control pin (active high). */
    pin_name_t unb;             /**< Unbalanced control pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} mlvibrosens_cfg_t;

/**
 * @brief ML Vibro Sens Click Axes data structure.
 * @details Axes data object definition of ML Vibro Sens Click driver.
 */
typedef struct
{
    float x;                    /**< X axis [g]. */
    float y;                    /**< Y axis [g]. */
    float z;                    /**< Z axis [g]. */
    int8_t temperature;         /**< Temperature [degrees Celsius]. */

} mlvibrosens_data_t;

/**
 * @brief ML Vibro Sens Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MLVIBROSENS_OK = 0,
    MLVIBROSENS_ERROR = -1

} mlvibrosens_return_value_t;

/*!
 * @addtogroup mlvibrosens ML Vibro Sens Click Driver
 * @brief API for configuring and manipulating ML Vibro Sens Click driver.
 * @{
 */

/**
 * @brief ML Vibro Sens configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mlvibrosens_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mlvibrosens_cfg_setup ( mlvibrosens_cfg_t *cfg );

/**
 * @brief ML Vibro Sens initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mlvibrosens_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_init ( mlvibrosens_t *ctx, mlvibrosens_cfg_t *cfg );

/**
 * @brief ML Vibro Sens default configuration function.
 * @details This function executes a default configuration of ML Vibro Sens
 * Click board.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mlvibrosens_default_cfg ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_write_regs ( mlvibrosens_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ML Vibro Sens read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_read_regs ( mlvibrosens_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ML Vibro Sens write reg function.
 * @details This function write a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_write_reg ( mlvibrosens_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ML Vibro Sens read reg function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_read_reg ( mlvibrosens_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ML Vibro Sens balanced enable function.
 * @details This function enables balanced vibro motor by setting the BAL pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mlvibrosens_balanced_enable ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens balanced disable function.
 * @details This function disables balanced vibro motor by setting the BAL pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mlvibrosens_balanced_disable ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens unbalanced enable function.
 * @details This function enables unbalanced vibro motor by setting the UNB pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mlvibrosens_unbalanced_enable ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens unbalanced disable function.
 * @details This function disables unbalanced vibro motor by setting the UNB pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mlvibrosens_unbalanced_disable ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens get int1 pin function.
 * @details This function returns the interrupt pin logic state.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mlvibrosens_get_int_pin ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens set vibro state function.
 * @details This function sets the vibro motors state.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - IDLE (both motors disabled),
 *                    @li @c 1 - BALANCED (balanced motor enabled),
 *                    @li @c 2 - UNBALANCED (unbalanced motor enabled),
 *                    @li @c 3 - BOTH (both motors enabled),
 * @return None.
 * @note None.
 */
void mlvibrosens_set_vibro_state ( mlvibrosens_t *ctx, uint8_t state );

/**
 * @brief ML Vibro Sens check comm function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_check_comm ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens get status function.
 * @details This function reads the interrupt status register.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[out] status : Interrupt status read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_get_status ( mlvibrosens_t *ctx, uint8_t *status );

/**
 * @brief ML Vibro Sens sw reset function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_sw_reset ( mlvibrosens_t *ctx );

/**
 * @brief ML Vibro Sens set mode function.
 * @details This function sets the device operating mode to standby or active.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] mode : Operating mode: @li @c 0 - Standby,
 *                                   @li @c 1 - Active.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_set_mode ( mlvibrosens_t *ctx, uint8_t mode );

/**
 * @brief ML Vibro Sens set fsr function.
 * @details This function sets the accel measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 2G,
 *                  @li @c 1 - 4G,
 *                  @li @c 2 - 8G,
 *                  @li @c 3 - 16G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_set_fsr ( mlvibrosens_t *ctx, uint8_t fsr );

/**
 * @brief ML Vibro Sens set odr function.
 * @details This function sets the measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - 3200Hz,
 *                  @li @c 1 - 1600Hz,
 *                  @li @c 2 - 800Hz,
 *                  @li @c 3 - 400Hz,
 *                  @li @c 4 - 200Hz,
 *                  @li @c 5 - 100Hz,
 *                  @li @c 6 - 50Hz,
 *                  @li @c 7 - 25Hz,
 *                  @li @c 8 - 12.5Hz,
 *                  @li @c 9 - 6.25Hz,
 *                  @li @c 10 - 3.125Hz,
 *                  @li @c 11 - 1.563Hz,
 *                  @li @c 12 - 0.781Hz,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_set_odr ( mlvibrosens_t *ctx, uint8_t odr );

/**
 * @brief ML Vibro Sens get data function.
 * @details This function reads accel X, Y, and Z axis data in g and temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #mlvibrosens_t object definition for detailed explanation.
 * @param[out] data_out : X, Y, and Z axis data in g, and temperature in degrees Celsius.
 * See #mlvibrosens_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mlvibrosens_get_data ( mlvibrosens_t *ctx, mlvibrosens_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // MLVIBROSENS_H

/*! @} */ // mlvibrosens

// ------------------------------------------------------------------------ END

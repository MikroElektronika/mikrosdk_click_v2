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
 * @file brushless28.h
 * @brief This file contains API for Brushless 28 Click Driver.
 */

#ifndef BRUSHLESS28_H
#define BRUSHLESS28_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_pwm.h"

/*!
 * @addtogroup brushless28 Brushless 28 Click Driver
 * @brief API for configuring and manipulating Brushless 28 Click driver.
 * @{
 */

/**
 * @defgroup brushless28_reg Brushless 28 Registers List
 * @brief List of registers of Brushless 28 Click driver.
 */

/**
 * @addtogroup brushless28_reg
 * @{
 */

/**
 * @brief Brushless 28 register list.
 * @details Specified register list of Brushless 28 Click driver.
 */
#define BRUSHLESS28_REG_IC_STAT1                    0x00
#define BRUSHLESS28_REG_IC_STAT2                    0x01
#define BRUSHLESS28_REG_IC_STAT3                    0x02
#define BRUSHLESS28_REG_IC_STAT4                    0x03
#define BRUSHLESS28_REG_IC_STAT5                    0x04
#define BRUSHLESS28_REG_IC_STAT6                    0x05
#define BRUSHLESS28_REG_IC_CTRL1                    0x1A
#define BRUSHLESS28_REG_IC_CTRL2                    0x1B
#define BRUSHLESS28_REG_IC_CTRL3                    0x1C
#define BRUSHLESS28_REG_GD_CTRL1                    0x1E
#define BRUSHLESS28_REG_GD_CTRL2                    0x1F
#define BRUSHLESS28_REG_GD_CTRL3                    0x21
#define BRUSHLESS28_REG_GD_CTRL3B                   0x22
#define BRUSHLESS28_REG_GD_CTRL4                    0x23
#define BRUSHLESS28_REG_GD_CTRL5                    0x24
#define BRUSHLESS28_REG_GD_CTRL6                    0x25
#define BRUSHLESS28_REG_GD_CTRL7                    0x26
#define BRUSHLESS28_REG_CSA_CTRL                    0x29
#define BRUSHLESS28_REG_MON_CTRL1                   0x2B
#define BRUSHLESS28_REG_MON_CTRL2                   0x2C
#define BRUSHLESS28_REG_MON_CTRL3                   0x2D
#define BRUSHLESS28_REG_MON_CTRL4                   0x2E
#define BRUSHLESS28_REG_SPI_TEST                    0x36
#define BRUSHLESS28_REG_OTP_USR                     0x48

/*! @} */ // brushless28_reg

/**
 * @defgroup brushless28_set Brushless 28 Registers Settings
 * @brief Settings for registers of Brushless 28 Click driver.
 */

/**
 * @addtogroup brushless28_set
 * @{
 */

/**
 * @brief Brushless 28 IC_CTRL2 register setting.
 * @details Specified setting for IC_CTRL2 register of Brushless 28 Click driver.
 */
#define BRUSHLESS28_IC_CTRL2_ENABLE_DRV             0x8000
#define BRUSHLESS28_IC_CTRL2_MODE_NSLEEP            0x4000
#define BRUSHLESS28_IC_CTRL2_CFG_CRC_EN             0x2000
#define BRUSHLESS28_IC_CTRL2_CLKMON_EN              0x1000
#define BRUSHLESS28_IC_CTRL2_CSA_EN                 0x0800
#define BRUSHLESS28_IC_CTRL2_CSA_AZ_DIS             0x0400
#define BRUSHLESS28_IC_CTRL2_GVDD_MODE_LDO          0x0100
#define BRUSHLESS28_IC_CTRL2_VCP_MODE_NORMAL        0x0000
#define BRUSHLESS28_IC_CTRL2_VCP_MODE_SW_DIS        0x0040
#define BRUSHLESS28_IC_CTRL2_VCP_MODE_SHUTDOWN      0x0080
#define BRUSHLESS28_IC_CTRL2_VCP_MODE_TCP_DIS       0x00C0
#define BRUSHLESS28_IC_CTRL2_VCP_MODE_MASK          0x00C0
#define BRUSHLESS28_IC_CTRL2_LOCK_UNLOCK            0x0006
#define BRUSHLESS28_IC_CTRL2_LOCK_LOCK              0x000C
#define BRUSHLESS28_IC_CTRL2_LOCK_MASK              0x000E
#define BRUSHLESS28_IC_CTRL2_CLR_FLT                0x0001

/**
 * @brief Brushless 28 GD_CTRL1 register setting.
 * @details Specified setting for GD_CTRL1 register of Brushless 28 Click driver.
 */
#define BRUSHLESS28_GD_CTRL1_PWM_MODE_6X_PWM        0x0000
#define BRUSHLESS28_GD_CTRL1_PWM_MODE_3X_PWM_INLX   0x1000
#define BRUSHLESS28_GD_CTRL1_PWM_MODE_3X_PWM_SPI    0x2000
#define BRUSHLESS28_GD_CTRL1_PWM_MODE_1X_PWM        0x3000
#define BRUSHLESS28_GD_CTRL1_PWM_MODE_SPI_GATE      0x5000
#define BRUSHLESS28_GD_CTRL1_PWM_MODE_MASK          0x7000
#define BRUSHLESS28_GD_CTRL1_SGD_MODE_FIXED         0x0000
#define BRUSHLESS28_GD_CTRL1_SGD_MODE_DYNAMIC       0x0200
#define BRUSHLESS28_GD_CTRL1_SGD_MODE_MASK          0x0600
#define BRUSHLESS28_GD_CTRL1_SGD_TMP_EN             0x0100
#define BRUSHLESS28_GD_CTRL1_STP_MODE_0             0x0000
#define BRUSHLESS28_GD_CTRL1_STP_MODE_1             0x0080
#define BRUSHLESS28_GD_CTRL1_STP_MODE_MASK          0x0080
#define BRUSHLESS28_GD_CTRL1_DEADT_70NS             0x0000
#define BRUSHLESS28_GD_CTRL1_DEADT_200NS            0x0008
#define BRUSHLESS28_GD_CTRL1_DEADT_300NS            0x0010
#define BRUSHLESS28_GD_CTRL1_DEADT_500NS            0x0018
#define BRUSHLESS28_GD_CTRL1_DEADT_750NS            0x0020
#define BRUSHLESS28_GD_CTRL1_DEADT_1000NS           0x0028
#define BRUSHLESS28_GD_CTRL1_DEADT_1500NS           0x0030
#define BRUSHLESS28_GD_CTRL1_DEADT_2000NS           0x0038
#define BRUSHLESS28_GD_CTRL1_DEADT_MASK             0x0038
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_0           0x0000
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_1           0x0004
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_MASK        0x0004
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_6X_0        0x0000
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_6X_1        0x0001
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_6X_2        0x0002
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_6X_3        0x0003
#define BRUSHLESS28_GD_CTRL1_DEADT_MODE_6X_MASK     0x0003

/**
 * @brief Brushless 28 SPI test word setting.
 * @details Specified setting for SPI test word of Brushless 28 Click driver.
 */
#define BRUSHLESS28_SPI_TEST_WORD                   0x5AA5

/**
 * @brief Brushless 28 SPI frame setting.
 * @details Specified setting for SPI frame of Brushless 28 Click driver.
 */
#define BRUSHLESS28_SPI_FRAME_READ_BIT              0x01
#define BRUSHLESS28_SPI_FRAME_CRC_DISABLE           0x00
#define BRUSHLESS28_SPI_FRAME_CRC_ENABLE            0x01
#define BRUSHLESS28_SPI_FRAME_CRC_MASK              0x01

/**
 * @brief Brushless 28 direction settings.
 * @details Specified setting for direction of Brushless 28 Click driver.
 */
#define BRUSHLESS28_DIR_CW                          0
#define BRUSHLESS28_DIR_CCW                         1

/**
 * @brief Brushless 28 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 28 Click driver.
 */
#define BRUSHLESS28_DEF_DUTY                        0.0
#define BRUSHLESS28_DEF_FREQ                        5000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b brushless28_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BRUSHLESS28_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define BRUSHLESS28_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // brushless28_set

/**
 * @defgroup brushless28_map Brushless 28 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 28 Click driver.
 */

/**
 * @addtogroup brushless28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 28 Click to the selected MikroBUS.
 */
#define BRUSHLESS28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.brake = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless28_map
/*! @} */ // brushless28

/**
 * @brief Brushless 28 Click context object.
 * @details Context object definition of Brushless 28 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;              /**< Direction control pin (CW-LOW, CCW-HIGH). */
    digital_out_t brake;            /**< Brake pin (active low). */

    // Input pins
    digital_in_t fault;             /**< Fault indication pin (active low). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */
    pwm_t pwm;                      /**< PWM driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */
    uint32_t pwm_freq;              /**< PWM frequency value. */

    uint8_t crc_en;                 /**< CRC enable flag. */

} brushless28_t;

/**
 * @brief Brushless 28 Click configuration object.
 * @details Configuration object definition of Brushless 28 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t pwm;                 /**< PWM pin. */

    // Additional gpio pins
    pin_name_t dir;                 /**< Direction control pin (CW-LOW, CCW-HIGH). */
    pin_name_t brake;               /**< Brake pin (active low). */
    pin_name_t fault;               /**< Fault indication pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t dev_pwm_freq;          /**< PWM frequency value. */

} brushless28_cfg_t;

/**
 * @brief Brushless 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS28_OK = 0,
    BRUSHLESS28_ERROR = -1

} brushless28_return_value_t;

/*!
 * @addtogroup brushless28 Brushless 28 Click Driver
 * @brief API for configuring and manipulating Brushless 28 Click driver.
 * @{
 */

/**
 * @brief Brushless 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless28_cfg_setup ( brushless28_cfg_t *cfg );

/**
 * @brief Brushless 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless28_init ( brushless28_t *ctx, brushless28_cfg_t *cfg );

/**
 * @brief Brushless 28 default configuration function.
 * @details This function executes a default configuration of Brushless 28
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless28_default_cfg ( brushless28_t *ctx );

/**
 * @brief Brushless 28 data writing function.
 * @details This function writes a data word to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless28_write_reg ( brushless28_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Brushless 28 data reading function.
 * @details This function reads a data bytes word from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless28_read_reg ( brushless28_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Brushless 28 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless28_set_duty_cycle ( brushless28_t *ctx, float duty_cycle );

/**
 * @brief Brushless 28 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless28_pwm_stop ( brushless28_t *ctx );

/**
 * @brief Brushless 28 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless28_pwm_start ( brushless28_t *ctx );

/**
 * @brief Brushless 28 set direction function.
 * @details This function sets the direction of motor rotation by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - CW,
 *                  @li @c 1 - CCW.
 * @return None.
 * @note None.
 */
void brushless28_set_direction ( brushless28_t *ctx, uint8_t dir );

/**
 * @brief Brushless 28 switch direction function.
 * @details This function switches the direction of motor rotation by toggling the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless28_switch_direction ( brushless28_t *ctx );

/**
 * @brief Brushless 28 pull brake function.
 * @details This function pulls brake by setting the BRAKE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless28_pull_brake ( brushless28_t *ctx );

/**
 * @brief Brushless 28 release brake function.
 * @details This function releases brake by setting the BRAKE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless28_release_brake ( brushless28_t *ctx );

/**
 * @brief Brushless 28 get fault pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless28_get_fault_pin ( brushless28_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS28_H

/*! @} */ // brushless28

// ------------------------------------------------------------------------ END

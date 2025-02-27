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
 * @file hbridge18.h
 * @brief This file contains API for H-Bridge 18 Click Driver.
 */

#ifndef HBRIDGE18_H
#define HBRIDGE18_H

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

/*!
 * @addtogroup hbridge18 H-Bridge 18 Click Driver
 * @brief API for configuring and manipulating H-Bridge 18 Click driver.
 * @{
 */

/**
 * @defgroup hbridge18_reg H-Bridge 18 Registers List
 * @brief List of registers of H-Bridge 18 Click driver.
 */

/**
 * @addtogroup hbridge18_reg
 * @{
 */

/**
 * @brief H-Bridge 18 register list.
 * @details Specified register list of H-Bridge 18 Click driver.
 */
#define HBRIDGE18_REG_IC_STAT                   0x00
#define HBRIDGE18_REG_OCP_STAT_1                0x01
#define HBRIDGE18_REG_OLD_STAT_1                0x04
#define HBRIDGE18_REG_CONFIG_CTRL               0x07
#define HBRIDGE18_REG_OP_CTRL_1                 0x08
#define HBRIDGE18_REG_PWM_CTRL_1                0x0B
#define HBRIDGE18_REG_PWM_CTRL_2                0x0C
#define HBRIDGE18_REG_FW_CTRL_1                 0x0D
#define HBRIDGE18_REG_PWM_MAP_CTRL_1            0x0F
#define HBRIDGE18_REG_PWM_MAP_CTRL_2            0x10
#define HBRIDGE18_REG_PWM_FREQ_CTRL_1           0x13
#define HBRIDGE18_REG_PWM_DUTY_CTRL_1           0x15
#define HBRIDGE18_REG_PWM_DUTY_CTRL_2           0x16
#define HBRIDGE18_REG_PWM_DUTY_CTRL_3           0x17
#define HBRIDGE18_REG_PWM_DUTY_CTRL_4           0x18
#define HBRIDGE18_REG_SR_CTRL_1                 0x1D
#define HBRIDGE18_REG_OLD_CTRL_1                0x1F
#define HBRIDGE18_REG_OLD_CTRL_2                0x20
#define HBRIDGE18_REG_OLD_CTRL_3                0x21
#define HBRIDGE18_REG_OLD_CTRL_4                0x22
#define HBRIDGE18_REG_OLD_CTRL_5                0x23
#define HBRIDGE18_REG_OLD_CTRL_6                0x24

/*! @} */ // hbridge18_reg

/**
 * @defgroup hbridge18_set H-Bridge 18 Registers Settings
 * @brief Settings for registers of H-Bridge 18 Click driver.
 */

/**
 * @addtogroup hbridge18_set
 * @{
 */

/**
 * @brief H-Bridge 18 IC_STAT register setting.
 * @details Specified setting for IC_STAT register of H-Bridge 18 Click driver.
 */
#define HBRIDGE18_IC_STAT_OTSD                  0x40
#define HBRIDGE18_IC_STAT_OTW                   0x20
#define HBRIDGE18_IC_STAT_OLD                   0x10
#define HBRIDGE18_IC_STAT_OCP                   0x08
#define HBRIDGE18_IC_STAT_UVLO                  0x04
#define HBRIDGE18_IC_STAT_OVP                   0x02
#define HBRIDGE18_IC_STAT_NPOR                  0x01

/**
 * @brief H-Bridge 18 CONFIG_CTRL register setting.
 * @details Specified setting for CONFIG_CTRL register of H-Bridge 18 Click driver.
 */
#define HBRIDGE18_CONFIG_CTRL_POLD_EN           0x80
#define HBRIDGE18_CONFIG_CTRL_IC_ID_DRV8904     0x40
#define HBRIDGE18_CONFIG_CTRL_IC_ID_MASK        0x70
#define HBRIDGE18_CONFIG_CTRL_OCP_REP           0x08
#define HBRIDGE18_CONFIG_CTRL_OTW_REP           0x04
#define HBRIDGE18_CONFIG_CTRL_EXT_OVP           0x02
#define HBRIDGE18_CONFIG_CTRL_CLR_FLT           0x01

/**
 * @brief H-Bridge 18 OP_CTRL_1 register setting.
 * @details Specified setting for OP_CTRL_1 register of H-Bridge 18 Click driver.
 */
#define HBRIDGE18_OP_CTRL_1_HB4_HS_EN           0x80
#define HBRIDGE18_OP_CTRL_1_HB4_LS_EN           0x40
#define HBRIDGE18_OP_CTRL_1_HB3_HS_EN           0x20
#define HBRIDGE18_OP_CTRL_1_HB3_LS_EN           0x10
#define HBRIDGE18_OP_CTRL_1_HB2_HS_EN           0x08
#define HBRIDGE18_OP_CTRL_1_HB2_LS_EN           0x04
#define HBRIDGE18_OP_CTRL_1_HB1_HS_EN           0x02
#define HBRIDGE18_OP_CTRL_1_HB1_LS_EN           0x01
#define HBRIDGE18_OP_CTRL_1_HB34_MASK           0xF0
#define HBRIDGE18_OP_CTRL_1_HB12_MASK           0x0F

/**
 * @brief H-Bridge 18 OLD_CTRL_1 register setting.
 * @details Specified setting for OLD_CTRL_1 register of H-Bridge 18 Click driver.
 */
#define HBRIDGE18_OLD_CTRL_1_HB4_OLD_DIS        0x08
#define HBRIDGE18_OLD_CTRL_1_HB3_OLD_DIS        0x04
#define HBRIDGE18_OLD_CTRL_1_HB2_OLD_DIS        0x02
#define HBRIDGE18_OLD_CTRL_1_HB1_OLD_DIS        0x01

/**
 * @brief H-Bridge 18 motor selection setting.
 * @details Specified setting for motor selection of H-Bridge 18 Click driver.
 */
#define HBRIDGE18_MOTOR_0                       0
#define HBRIDGE18_MOTOR_1                       1

/**
 * @brief H-Bridge 18 motor state setting.
 * @details Specified setting for motor state of H-Bridge 18 Click driver.
 */
#define HBRIDGE18_MOTOR_STATE_COAST             0
#define HBRIDGE18_MOTOR_STATE_FORWARD           1
#define HBRIDGE18_MOTOR_STATE_REVERSE           2
#define HBRIDGE18_MOTOR_STATE_BRAKE_LS          3
#define HBRIDGE18_MOTOR_STATE_BRAKE_HS          4

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hbridge18_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HBRIDGE18_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define HBRIDGE18_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hbridge18_set

/**
 * @defgroup hbridge18_map H-Bridge 18 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 18 Click driver.
 */

/**
 * @addtogroup hbridge18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 18 Click to the selected MikroBUS.
 */
#define HBRIDGE18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge18_map
/*! @} */ // hbridge18

/**
 * @brief H-Bridge 18 Click context object.
 * @details Context object definition of H-Bridge 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sleep;        /**< Sleep pin (active low). */

    // Input pins
    digital_in_t fault;         /**< Fault indicator pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t ic_status;          /**< IC status byte. */

} hbridge18_t;

/**
 * @brief H-Bridge 18 Click configuration object.
 * @details Configuration object definition of H-Bridge 18 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t sleep;           /**< Sleep pin (active low). */
    pin_name_t fault;           /**< Fault indicator pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hbridge18_cfg_t;

/**
 * @brief H-Bridge 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE18_OK = 0,
    HBRIDGE18_ERROR = -1

} hbridge18_return_value_t;

/*!
 * @addtogroup hbridge18 H-Bridge 18 Click Driver
 * @brief API for configuring and manipulating H-Bridge 18 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge18_cfg_setup ( hbridge18_cfg_t *cfg );

/**
 * @brief H-Bridge 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge18_init ( hbridge18_t *ctx, hbridge18_cfg_t *cfg );

/**
 * @brief H-Bridge 18 default configuration function.
 * @details This function executes a default configuration of H-Bridge 18
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge18_default_cfg ( hbridge18_t *ctx );

/**
 * @brief H-Bridge 18 write register function.
 * @details This function writes a byte of data to the specified register using the SPI interface.
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written to the register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t hbridge18_write_reg ( hbridge18_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief H-Bridge 18 read register function.
 * @details This function reads a byte of data from the specified register using the SPI interface.
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to store the read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t hbridge18_read_reg ( hbridge18_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 18 enable device function.
 * @details This function enables the H-Bridge 18 device by setting the sleep pin high.
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge18_enable_device ( hbridge18_t *ctx );

/**
 * @brief H-Bridge 18 disable device function.
 * @details This function disables the H-Bridge 18 device by setting the sleep pin low.
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge18_disable_device ( hbridge18_t *ctx );

/**
 * @brief H-Bridge 18 get fault pin function.
 * @details This function reads the fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hbridge18_get_fault_pin ( hbridge18_t *ctx );

/**
 * @brief H-Bridge 18 check communication function.
 * @details This function checks communication with the device by reading and verifying the configuration register.
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @return @li @c  0 - Success (Device ID matches),
 *         @li @c -1 - Error (Device ID mismatch or communication failure).
 * @note None.
 */
err_t hbridge18_check_communication ( hbridge18_t *ctx );

/**
 * @brief H-Bridge 18 set motor state function.
 * @details This function sets the motor state for the selected motor (coast, forward, reverse, brake low-side, or brake high-side).
 * @param[in] ctx : Click context object.
 * See #hbridge18_t object definition for detailed explanation.
 * @param[in] motor : Motor selection.
 *                    - 0: Motor 0 (connected between O1-O2),
 *                    - 1: Motor 1 (connected between O3-O4).
 * @param[in] state : Motor state selection.
 *                    - 0: Coast,
 *                    - 1: Forward,
 *                    - 2: Reverse,
 *                    - 3: Brake low-side,
 *                    - 4: Brake high-side.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t hbridge18_set_motor_state ( hbridge18_t *ctx, uint8_t motor, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE18_H

/*! @} */ // hbridge18

// ------------------------------------------------------------------------ END

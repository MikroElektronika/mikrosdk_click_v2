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
 * @file solidswitch2.h
 * @brief This file contains API for SolidSwitch 2 Click Driver.
 */

#ifndef SOLIDSWITCH2_H
#define SOLIDSWITCH2_H

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
 * @addtogroup solidswitch2 SolidSwitch 2 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 2 Click driver.
 * @{
 */

/**
 * @defgroup solidswitch2_reg SolidSwitch 2 Registers List
 * @brief List of registers of SolidSwitch 2 Click driver.
 */

/**
 * @addtogroup solidswitch2_reg
 * @{
 */

/**
 * @brief SolidSwitch 2 register map.
 * @details Specified register map of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_REG_CHIP_ID                0x00
#define SOLIDSWITCH2_REG_CFG_0                  0x01
#define SOLIDSWITCH2_REG_CFG_1                  0x02
#define SOLIDSWITCH2_REG_CFG_2                  0x03
#define SOLIDSWITCH2_REG_BIM                    0x04
#define SOLIDSWITCH2_REG_RESERVED_1             0x05
#define SOLIDSWITCH2_REG_PWM_SPI                0x06
#define SOLIDSWITCH2_REG_MAP_IN0                0x07
#define SOLIDSWITCH2_REG_MAP_IN1                0x08
#define SOLIDSWITCH2_REG_MAP_PWM                0x09
#define SOLIDSWITCH2_REG_PWM_SEL                0x0A
#define SOLIDSWITCH2_REG_PWM_GEN_DC             0x0B
#define SOLIDSWITCH2_REG_PWM_LED_DC             0x0C
#define SOLIDSWITCH2_REG_DIAG_OFF_EN            0x0D
#define SOLIDSWITCH2_REG_DIAG_OPL_ON_EN         0x0E
#define SOLIDSWITCH2_REG_DIAG_OVC_OVT_RLW       0x0F
#define SOLIDSWITCH2_REG_STA_0                  0x10
#define SOLIDSWITCH2_REG_STA_1                  0x11
#define SOLIDSWITCH2_REG_DIAG_OVC_OVT           0x12
#define SOLIDSWITCH2_REG_DIAG_OPL_OFF           0x13
#define SOLIDSWITCH2_REG_DIAG_OPL_ON            0x14
#define SOLIDSWITCH2_REG_DIAG_SHD               0x15

/*! @} */ // solidswitch2_reg

/**
 * @defgroup solidswitch2_set SolidSwitch 2 Registers Settings
 * @brief Settings for registers of SolidSwitch 2 Click driver.
 */

/**
 * @addtogroup solidswitch2_set
 * @{
 */

/**
 * @brief SolidSwitch 2 chip ID setting.
 * @details Specified setting for chip ID of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_CHIP_ID                    0x56

/**
 * @brief SolidSwitch 2 CFG_0 register setting.
 * @details Specified setting for CFG_0 register of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_CFG_0_OUT7                 0x80
#define SOLIDSWITCH2_CFG_0_OUT6                 0x40
#define SOLIDSWITCH2_CFG_0_OUT5                 0x20
#define SOLIDSWITCH2_CFG_0_OUT4                 0x10
#define SOLIDSWITCH2_CFG_0_OUT3                 0x08
#define SOLIDSWITCH2_CFG_0_OUT2                 0x04
#define SOLIDSWITCH2_CFG_0_DIS_EN               0x02
#define SOLIDSWITCH2_CFG_0_NRES_EN              0x01

/**
 * @brief SolidSwitch 2 CFG_1 register setting.
 * @details Specified setting for CFG_1 register of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_CFG_1_RST                  0x80
#define SOLIDSWITCH2_CFG_1_ACT                  0x40
#define SOLIDSWITCH2_CFG_1_PWM_DIV_LED_122p5Hz  0x00
#define SOLIDSWITCH2_CFG_1_PWM_DIV_LED_245p1Hz  0x01
#define SOLIDSWITCH2_CFG_1_PWM_DIV_LED_490p2Hz  0x02
#define SOLIDSWITCH2_CFG_1_PWM_DIV_LED_980p4Hz  0x03

/**
 * @brief SolidSwitch 2 CFG_2 register setting.
 * @details Specified setting for CFG_2 register of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_CFG_2_FR_ADJ_NO_FREQ_ADJ   0x00
#define SOLIDSWITCH2_CFG_2_FR_ADJ_MINUS_15_PCT  0x04
#define SOLIDSWITCH2_CFG_2_FR_ADJ_PLUS_15_PCT   0x08
#define SOLIDSWITCH2_CFG_2_PWM_DIV_GEN_122p5Hz  0x00
#define SOLIDSWITCH2_CFG_2_PWM_DIV_GEN_245p1Hz  0x01
#define SOLIDSWITCH2_CFG_2_PWM_DIV_GEN_490p2Hz  0x02
#define SOLIDSWITCH2_CFG_2_PWM_DIV_GEN_980p4Hz  0x03

/**
 * @brief SolidSwitch 2 OUT mask setting.
 * @details Specified setting for OUT mask of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_OUT7                       0x80
#define SOLIDSWITCH2_OUT6                       0x40
#define SOLIDSWITCH2_OUT5                       0x20
#define SOLIDSWITCH2_OUT4                       0x10
#define SOLIDSWITCH2_OUT3                       0x08
#define SOLIDSWITCH2_OUT2                       0x04
#define SOLIDSWITCH2_OUT1                       0x02
#define SOLIDSWITCH2_OUT0                       0x01
#define SOLIDSWITCH2_OUT_NONE                   0x00

/**
 * @brief SolidSwitch 2 duty cycle setting.
 * @details Specified setting for duty cycle of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_MAX_DUTY_CYCLE             0xFF
#define SOLIDSWITCH2_MIN_DUTY_CYCLE             0x00

/**
 * @brief SolidSwitch 2 SPI frame bits setting.
 * @details Specified SPI frame bits setting of SolidSwitch 2 Click driver.
 */
#define SOLIDSWITCH2_SPI_RW_BIT                 0x80
#define SOLIDSWITCH2_SPI_ERROR_BIT              0x80
#define SOLIDSWITCH2_ADDRESS_BIT_MASK           0x1F
#define SOLIDSWITCH2_ODD_PARITY                 0x01
#define SOLIDSWITCH2_SPI_ERROR_BIT              0x80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b solidswitch2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SOLIDSWITCH2_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define SOLIDSWITCH2_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // solidswitch2_set

/**
 * @defgroup solidswitch2_map SolidSwitch 2 MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch 2 Click driver.
 */

/**
 * @addtogroup solidswitch2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch 2 Click to the selected MikroBUS.
 */
#define SOLIDSWITCH2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.idle = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch2_map
/*! @} */ // solidswitch2

/**
 * @brief SolidSwitch 2 Click context object.
 * @details Context object definition of SolidSwitch 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t idle;         /**< Idle function pin. */
    digital_out_t in0;          /**< Parallel command input 0 pin. */
    digital_out_t in1;          /**< Parallel command input 1 pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} solidswitch2_t;

/**
 * @brief SolidSwitch 2 Click configuration object.
 * @details Configuration object definition of SolidSwitch 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t idle;            /**< Idle function pin. */
    pin_name_t in0;             /**< Parallel command input 0 pin. */
    pin_name_t in1;             /**< Parallel command input 1 pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} solidswitch2_cfg_t;

/**
 * @brief SolidSwitch 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH2_OK = 0,
    SOLIDSWITCH2_ERROR = -1

} solidswitch2_return_value_t;

/*!
 * @addtogroup solidswitch2 SolidSwitch 2 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 2 Click driver.
 * @{
 */

/**
 * @brief SolidSwitch 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solidswitch2_cfg_setup ( solidswitch2_cfg_t *cfg );

/**
 * @brief SolidSwitch 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch2_init ( solidswitch2_t *ctx, solidswitch2_cfg_t *cfg );

/**
 * @brief SolidSwitch 2 default configuration function.
 * @details This function executes a default configuration of SolidSwitch 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t solidswitch2_default_cfg ( solidswitch2_t *ctx );

/**
 * @brief SolidSwitch 2 data writing function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch2_write_register ( solidswitch2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief SolidSwitch 2 data reading function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch2_read_register ( solidswitch2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief SolidSwitch 2 check communication function.
 * @details This function checks the communication by reading and verifying the chip ID value.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch2_check_communication ( solidswitch2_t *ctx );

/**
 * @brief SolidSwitch 2 set idle pin function.
 * @details This function sets the IDLE pin logic state.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solidswitch2_set_idle_pin ( solidswitch2_t *ctx, uint8_t state );

/**
 * @brief SolidSwitch 2 set in0 pin function.
 * @details This function sets the IN0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solidswitch2_set_in0_pin ( solidswitch2_t *ctx, uint8_t state );

/**
 * @brief SolidSwitch 2 set in1 pin function.
 * @details This function sets the IN1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solidswitch2_set_in1_pin ( solidswitch2_t *ctx, uint8_t state );

/**
 * @brief SolidSwitch 2 toggle in0 pin function.
 * @details This function toggles the IN0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch2_toggle_in0_pin ( solidswitch2_t *ctx );

/**
 * @brief SolidSwitch 2 toggle in1 pin function.
 * @details This function toggles the IN1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch2_toggle_in1_pin ( solidswitch2_t *ctx );

/**
 * @brief SolidSwitch 2 soft reset function.
 * @details This function performs the software reset by setting a desired bit in the CFG_1 register.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch2_soft_reset ( solidswitch2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH2_H

/*! @} */ // solidswitch2

// ------------------------------------------------------------------------ END

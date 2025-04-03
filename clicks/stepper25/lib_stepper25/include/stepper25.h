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
 * @file stepper25.h
 * @brief This file contains API for Stepper 25 Click Driver.
 */

#ifndef STEPPER25_H
#define STEPPER25_H

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
 * @addtogroup stepper25 Stepper 25 Click Driver
 * @brief API for configuring and manipulating Stepper 25 Click driver.
 * @{
 */

/**
 * @defgroup stepper25_reg Stepper 25 Registers List
 * @brief List of registers of Stepper 25 Click driver.
 */

/**
 * @addtogroup stepper25_reg
 * @{
 */

/**
 * @brief Stepper 25 register list.
 * @details Specified register list of Stepper 25 Click driver.
 */
#define STEPPER25_REG_FAULT                         0x00
#define STEPPER25_REG_DIAG1                         0x01
#define STEPPER25_REG_DIAG2                         0x02
#define STEPPER25_REG_DIAG3                         0x03
#define STEPPER25_REG_CTRL1                         0x04
#define STEPPER25_REG_CTRL2                         0x05
#define STEPPER25_REG_CTRL3                         0x06
#define STEPPER25_REG_CTRL4                         0x07
#define STEPPER25_REG_CTRL5                         0x08
#define STEPPER25_REG_CTRL6                         0x09
#define STEPPER25_REG_CTRL7                         0x0A
#define STEPPER25_REG_CTRL8                         0x0B
#define STEPPER25_REG_CTRL9                         0x0C
#define STEPPER25_REG_CTRL10                        0x0D
#define STEPPER25_REG_CTRL11                        0x0E
#define STEPPER25_REG_CTRL12                        0x0F
#define STEPPER25_REG_CTRL13                        0x10
#define STEPPER25_REG_INDEX1                        0x11
#define STEPPER25_REG_INDEX2                        0x12
#define STEPPER25_REG_INDEX3                        0x13
#define STEPPER25_REG_INDEX4                        0x14
#define STEPPER25_REG_INDEX5                        0x15
#define STEPPER25_REG_CUSTOM_CTRL1                  0x16
#define STEPPER25_REG_CUSTOM_CTRL2                  0x17
#define STEPPER25_REG_CUSTOM_CTRL3                  0x18
#define STEPPER25_REG_CUSTOM_CTRL4                  0x19
#define STEPPER25_REG_CUSTOM_CTRL5                  0x1A
#define STEPPER25_REG_CUSTOM_CTRL6                  0x1B
#define STEPPER25_REG_CUSTOM_CTRL7                  0x1C
#define STEPPER25_REG_CUSTOM_CTRL8                  0x1D
#define STEPPER25_REG_CUSTOM_CTRL9                  0x1E
#define STEPPER25_REG_ATQ_CTRL1                     0x1F
#define STEPPER25_REG_ATQ_CTRL2                     0x20
#define STEPPER25_REG_ATQ_CTRL3                     0x21
#define STEPPER25_REG_ATQ_CTRL4                     0x22
#define STEPPER25_REG_ATQ_CTRL5                     0x23
#define STEPPER25_REG_ATQ_CTRL6                     0x24
#define STEPPER25_REG_ATQ_CTRL7                     0x25
#define STEPPER25_REG_ATQ_CTRL8                     0x26
#define STEPPER25_REG_ATQ_CTRL9                     0x27
#define STEPPER25_REG_ATQ_CTRL10                    0x28
#define STEPPER25_REG_ATQ_CTRL11                    0x29
#define STEPPER25_REG_ATQ_CTRL12                    0x2A
#define STEPPER25_REG_ATQ_CTRL13                    0x2B
#define STEPPER25_REG_ATQ_CTRL14                    0x2C
#define STEPPER25_REG_ATQ_CTRL15                    0x2D
#define STEPPER25_REG_ATQ_CTRL16                    0x2E
#define STEPPER25_REG_ATQ_CTRL17                    0x2F
#define STEPPER25_REG_ATQ_CTRL18                    0x30
#define STEPPER25_REG_SS_CTRL1                      0x31
#define STEPPER25_REG_SS_CTRL2                      0x32
#define STEPPER25_REG_SS_CTRL3                      0x33
#define STEPPER25_REG_SS_CTRL4                      0x34
#define STEPPER25_REG_SS_CTRL5                      0x35
#define STEPPER25_REG_CTRL14                        0x3C

/*! @} */ // stepper25_reg

/**
 * @defgroup stepper25_set Stepper 25 Registers Settings
 * @brief Settings for registers of Stepper 25 Click driver.
 */

/**
 * @addtogroup stepper25_set
 * @{
 */

/**
 * @brief Stepper 25 FAULT register setting.
 * @details Specified setting for FAULT register of Stepper 25 Click driver.
 */
#define STEPPER25_FAULT_FAULT                       0x80
#define STEPPER25_FAULT_SPI_ERROR                   0x40
#define STEPPER25_FAULT_UVLO                        0x20
#define STEPPER25_FAULT_CPUV                        0x10
#define STEPPER25_FAULT_OCP                         0x08
#define STEPPER25_FAULT_STL                         0x04
#define STEPPER25_FAULT_TF                          0x02
#define STEPPER25_FAULT_OL                          0x01

/**
 * @brief Stepper 25 CTRL1 register setting.
 * @details Specified setting for CTRL1 register of Stepper 25 Click driver.
 */
#define STEPPER25_CTRL1_EN_OUT_DISABLED             0x00
#define STEPPER25_CTRL1_EN_OUT_ENABLED              0x80
#define STEPPER25_CTRL1_EN_OUT_MASK                 0x80
#define STEPPER25_CTRL1_SR_140_NS                   0x00
#define STEPPER25_CTRL1_SR_70_NS                    0x40
#define STEPPER25_CTRL1_SR_MASK                     0x40
#define STEPPER25_CTRL1_IDX_RST_LOW                 0x00
#define STEPPER25_CTRL1_IDX_RST_HIGH                0x20
#define STEPPER25_CTRL1_IDX_RST_MASK                0x20
#define STEPPER25_CTRL1_TOFF_9_5_US                 0x00
#define STEPPER25_CTRL1_TOFF_19_US                  0x08
#define STEPPER25_CTRL1_TOFF_27_US                  0x10
#define STEPPER25_CTRL1_TOFF_35_US                  0x18
#define STEPPER25_CTRL1_TOFF_MASK                   0x18
#define STEPPER25_CTRL1_DECAY_SLOW                  0x00
#define STEPPER25_CTRL1_DECAY_MIXED_30_PCT          0x04
#define STEPPER25_CTRL1_DECAY_MIXED_60_PCT          0x05
#define STEPPER25_CTRL1_DECAY_SMART_DYNAMIC         0x06
#define STEPPER25_CTRL1_DECAY_SMART_RIPPLE          0x07
#define STEPPER25_CTRL1_DECAY_MASK                  0x07

/**
 * @brief Stepper 25 CTRL2 register setting.
 * @details Specified setting for CTRL2 register of Stepper 25 Click driver.
 */
#define STEPPER25_CTRL2_DIR_LOW                     0x00
#define STEPPER25_CTRL2_DIR_HIGH                    0x80
#define STEPPER25_CTRL2_DIR_MASK                    0x80
#define STEPPER25_CTRL2_STEP_LOW                    0x00
#define STEPPER25_CTRL2_STEP_HIGH                   0x40
#define STEPPER25_CTRL2_STEP_MASK                   0x40
#define STEPPER25_CTRL2_SPI_DIR_PIN                 0x00
#define STEPPER25_CTRL2_SPI_DIR_BIT                 0x20
#define STEPPER25_CTRL2_SPI_DIR_MASK                0x20
#define STEPPER25_CTRL2_SPI_STEP_PIN                0x00
#define STEPPER25_CTRL2_SPI_STEP_BIT                0x10
#define STEPPER25_CTRL2_SPI_STEP_MASK               0x10
#define STEPPER25_CTRL2_MICROSTEP_MODE_FULL_100     0x00
#define STEPPER25_CTRL2_MICROSTEP_MODE_FULL_71      0x01
#define STEPPER25_CTRL2_MICROSTEP_MODE_HALF_NO_CIRC 0x02
#define STEPPER25_CTRL2_MICROSTEP_MODE_HALF         0x03
#define STEPPER25_CTRL2_MICROSTEP_MODE_QUARTER      0x04
#define STEPPER25_CTRL2_MICROSTEP_MODE_1_OVER_8     0x05
#define STEPPER25_CTRL2_MICROSTEP_MODE_1_OVER_16    0x06
#define STEPPER25_CTRL2_MICROSTEP_MODE_1_OVER_32    0x07
#define STEPPER25_CTRL2_MICROSTEP_MODE_1_OVER_64    0x08
#define STEPPER25_CTRL2_MICROSTEP_MODE_1_OVER_128   0x09
#define STEPPER25_CTRL2_MICROSTEP_MODE_1_OVER_256   0x0A
#define STEPPER25_CTRL2_MICROSTEP_MODE_MASK         0x0F

/**
 * @brief Stepper 25 CTRL3 register setting.
 * @details Specified setting for CTRL3 register of Stepper 25 Click driver.
 */
#define STEPPER25_CTRL3_CLR_FLT_LOW                 0x00
#define STEPPER25_CTRL3_CLR_FLT_HIGH                0x80
#define STEPPER25_CTRL3_CLR_FLT_MASK                0x80
#define STEPPER25_CTRL3_LOCK_UNLOCK                 0x30
#define STEPPER25_CTRL3_LOCK_LOCK                   0x60
#define STEPPER25_CTRL3_LOCK_MASK                   0x70
#define STEPPER25_CTRL3_TOCP_1_2_US                 0x00
#define STEPPER25_CTRL3_TOCP_2_2_US                 0x08
#define STEPPER25_CTRL3_TOCP_MASK                   0x08
#define STEPPER25_CTRL3_OCP_MODE_LATCHED            0x00
#define STEPPER25_CTRL3_OCP_MODE_AUTO_RETRY         0x04
#define STEPPER25_CTRL3_OCP_MODE_MASK               0x04
#define STEPPER25_CTRL3_OTSD_MODE_LATCHED           0x00
#define STEPPER25_CTRL3_OTSD_MODE_AUTO_RETRY        0x02
#define STEPPER25_CTRL3_OTSD_MODE_MASK              0x02
#define STEPPER25_CTRL3_TW_REP_DISABLED             0x00
#define STEPPER25_CTRL3_TW_REP_ENABLED              0x01
#define STEPPER25_CTRL3_TW_REP_MASK                 0x01

/**
 * @brief Stepper 25 CTRL4 register setting.
 * @details Specified setting for CTRL4 register of Stepper 25 Click driver.
 */
#define STEPPER25_CTRL4_TBLANK_TIME_1_US            0x00
#define STEPPER25_CTRL4_TBLANK_TIME_1_5_US          0x40
#define STEPPER25_CTRL4_TBLANK_TIME_2_US            0x80
#define STEPPER25_CTRL4_TBLANK_TIME_2_5_US          0xC0
#define STEPPER25_CTRL4_TBLANK_TIME_MASK            0xC0
#define STEPPER25_CTRL4_STL_LRN_DIS                 0x00
#define STEPPER25_CTRL4_STL_LRN_EN                  0x20
#define STEPPER25_CTRL4_STL_LRN_MASK                0x20
#define STEPPER25_CTRL4_EN_STL_DIS                  0x00
#define STEPPER25_CTRL4_EN_STL_EN                   0x10
#define STEPPER25_CTRL4_EN_STL_MASK                 0x10
#define STEPPER25_CTRL4_STL_REP_DIS                 0x00
#define STEPPER25_CTRL4_STL_REP_EN                  0x08
#define STEPPER25_CTRL4_STL_REP_MASK                0x08
#define STEPPER25_CTRL4_FRQ_CHG_FILTERED            0x00
#define STEPPER25_CTRL4_FRQ_CHG_NOT_FILTERED        0x04
#define STEPPER25_CTRL4_FRQ_CHG_MASK                0x04
#define STEPPER25_CTRL4_STEP_FRQ_TOL_1_PCT          0x00
#define STEPPER25_CTRL4_STEP_FRQ_TOL_2_PCT          0x01
#define STEPPER25_CTRL4_STEP_FRQ_TOL_4_PCT          0x02
#define STEPPER25_CTRL4_STEP_FRQ_TOL_6_PCT          0x03
#define STEPPER25_CTRL4_STEP_FRQ_TOL_MASK           0x03

/**
 * @brief Stepper 25 CTRL11 register setting.
 * @details Specified setting for CTRL11 register of Stepper 25 Click driver.
 */
#define STEPPER25_CTRL11_TRQ_DAC_100_PCT            0xFF
#define STEPPER25_CTRL11_TRQ_DAC_87_5_PCT           0xDF
#define STEPPER25_CTRL11_TRQ_DAC_75_PCT             0xBF
#define STEPPER25_CTRL11_TRQ_DAC_62_5_PCT           0x9F
#define STEPPER25_CTRL11_TRQ_DAC_50_PCT             0x7F
#define STEPPER25_CTRL11_TRQ_DAC_37_5_PCT           0x5F
#define STEPPER25_CTRL11_TRQ_DAC_25_PCT             0x3F
#define STEPPER25_CTRL11_TRQ_DAC_12_5_PCT           0x1F

/**
 * @brief Stepper 25 step mode setting.
 * @details Specified setting for step mode of Stepper 25 Click driver.
 */
#define STEPPER25_STEP_MODE_FULL_100                0
#define STEPPER25_STEP_MODE_FULL_71                 1
#define STEPPER25_STEP_MODE_HALF_NO_CIRC            2
#define STEPPER25_STEP_MODE_HALF                    3
#define STEPPER25_STEP_MODE_QUARTER                 4
#define STEPPER25_STEP_MODE_1_OVER_8                5
#define STEPPER25_STEP_MODE_1_OVER_16               6
#define STEPPER25_STEP_MODE_1_OVER_32               7
#define STEPPER25_STEP_MODE_1_OVER_64               8
#define STEPPER25_STEP_MODE_1_OVER_128              9
#define STEPPER25_STEP_MODE_1_OVER_256              10

/**
 * @brief Stepper 25 direction setting.
 * @details Specified setting for direction of Stepper 25 Click driver.
 */
#define STEPPER25_DIR_CCW                           0
#define STEPPER25_DIR_CW                            1

/**
 * @brief Stepper 25 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 25 Click driver.
 */
#define STEPPER25_PIN_LOW_LEVEL                     0
#define STEPPER25_PIN_HIGH_LEVEL                    1

/**
 * @brief Stepper 25 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER25_SPEED_VERY_SLOW                   0
#define STEPPER25_SPEED_SLOW                        1
#define STEPPER25_SPEED_MEDIUM                      2
#define STEPPER25_SPEED_FAST                        3
#define STEPPER25_SPEED_VERY_FAST                   4

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepper25_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPPER25_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define STEPPER25_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepper25_set

/**
 * @defgroup stepper25_map Stepper 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 25 Click driver.
 */

/**
 * @addtogroup stepper25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 25 Click to the selected MikroBUS.
 */
#define STEPPER25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper25_map
/*! @} */ // stepper25

/**
 * @brief Stepper 25 Click context object.
 * @details Context object definition of Stepper 25 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;              /**< Direction control pin. */
    digital_out_t sleep;            /**< Sleep mode pin (active low). */
    digital_out_t step;             /**< Step signal pin. */

    // Input pins
    digital_in_t fault;             /**< Fault indication pin. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t step_mode;              /**< Step mode resolution. */
    uint8_t status;                 /**< Fault register status byte. */

} stepper25_t;

/**
 * @brief Stepper 25 Click configuration object.
 * @details Configuration object definition of Stepper 25 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t dir;                 /**< Direction control pin. */
    pin_name_t sleep;               /**< Sleep mode pin (active low). */
    pin_name_t step;                /**< Step signal pin. */
    pin_name_t fault;               /**< Fault indication pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} stepper25_cfg_t;

/**
 * @brief Stepper 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER25_OK = 0,
    STEPPER25_ERROR = -1

} stepper25_return_value_t;

/*!
 * @addtogroup stepper25 Stepper 25 Click Driver
 * @brief API for configuring and manipulating Stepper 25 Click driver.
 * @{
 */

/**
 * @brief Stepper 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper25_cfg_setup ( stepper25_cfg_t *cfg );

/**
 * @brief Stepper 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper25_init ( stepper25_t *ctx, stepper25_cfg_t *cfg );

/**
 * @brief Stepper 25 default configuration function.
 * @details This function executes a default configuration of Stepper 25
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper25_default_cfg ( stepper25_t *ctx );

/**
 * @brief Stepper 25 write register function.
 * @details This function writes a byte of data to the specified register using the SPI interface.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written to the register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t stepper25_write_reg ( stepper25_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 25 read register function.
 * @details This function reads a byte of data from the specified register using the SPI interface.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to store the read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t stepper25_read_reg ( stepper25_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 25 enable device function.
 * @details This function enables the device by setting the SLEEP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper25_enable_device ( stepper25_t *ctx );

/**
 * @brief Stepper 25 disable device function.
 * @details This function disables the device by setting the SLEEP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper25_disable_device ( stepper25_t *ctx );

/**
 * @brief Stepper 25 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper25_set_direction ( stepper25_t *ctx, uint8_t dir );

/**
 * @brief Stepper 25 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper25_switch_direction ( stepper25_t *ctx );

/**
 * @brief Stepper 25 get FAULT pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper25_get_fault_pin ( stepper25_t *ctx );

/**
 * @brief Stepper 25 set STEP pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper25_set_step_pin ( stepper25_t *ctx, uint8_t state );

/**
 * @brief Stepper 25 clear fault function.
 * @details This function clears the fault register by setting the CLR_FLT bit.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t stepper25_clear_fault ( stepper25_t *ctx );

/**
 * @brief Stepper 25 enable output function.
 * @details This function enables all outputs by setting the EN_OUT bit.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t stepper25_enable_output ( stepper25_t *ctx );

/**
 * @brief Stepper 25 disable output function.
 * @details This function disables all outputs by clearing the EN_OUT bit.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t stepper25_disable_output ( stepper25_t *ctx );

/**
 * @brief Stepper 25 set step mode function.
 * @details This function sets the step mode (microstepping level) of the Stepper 25 device.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @param[in] step_mode : Step mode value (e.g., full-step, half-step, 1/4-step, etc.), 
                          refer to STEPPER25_STEP_MODE_x macros definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t stepper25_set_step_mode ( stepper25_t *ctx, uint8_t step_mode );

/**
 * @brief Stepper 25 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper25_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t stepper25_drive_motor ( stepper25_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER25_H

/*! @} */ // stepper25

// ------------------------------------------------------------------------ END

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
 * @file hbridge11.h
 * @brief This file contains API for H-Bridge 11 Click Driver.
 */

#ifndef HBRIDGE11_H
#define HBRIDGE11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup hbridge11 H-Bridge 11 Click Driver
 * @brief API for configuring and manipulating H-Bridge 11 Click driver.
 * @{
 */

/**
 * @defgroup hbridge11_reg H-Bridge 11 Registers List
 * @brief List of registers of H-Bridge 11 Click driver.
 */

/**
 * @addtogroup hbridge11_reg
 * @{
 */

/**
 * @brief H-Bridge 11 register list.
 * @details Specified register list of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_REG_STATUS                0x00
#define HBRIDGE11_REG_CFG_CH0               0x01
#define HBRIDGE11_REG_CFG_CH1               0x02
#define HBRIDGE11_REG_CFG_CH2               0x03
#define HBRIDGE11_REG_CFG_CH3               0x04
#define HBRIDGE11_REG_CFG_CH4               0x05
#define HBRIDGE11_REG_CFG_CH5               0x06
#define HBRIDGE11_REG_CFG_CH6               0x07
#define HBRIDGE11_REG_CFG_CH7               0x08
#define HBRIDGE11_REG_FAULT                 0x09
#define HBRIDGE11_REG_CFG_DPM               0x0A

/*! @} */ // hbridge11_reg

/**
 * @defgroup hbridge11_set H-Bridge 11 Registers Settings
 * @brief Settings for registers of H-Bridge 11 Click driver.
 */

/**
 * @addtogroup hbridge11_set
 * @{
 */

/**
 * @brief H-Bridge 11 command register setting.
 * @details Specified setting for command register of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_CMD_WRITE                 0x80
#define HBRIDGE11_CMD_ADDRESS_MASK          0x1E
#define HBRIDGE11_CMD_8BIT_REG              0x01

/**
 * @brief H-Bridge 11 status register setting.
 * @details Specified setting for status register of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_STATUS_ONCH_ALL_OFF       0x00000000ul
#define HBRIDGE11_STATUS_ONCH_ALL_ON        0xFF000000ul
#define HBRIDGE11_STATUS_ONCH_MASK          0xFF000000ul
#define HBRIDGE11_STATUS_M_OVT              0x00800000ul
#define HBRIDGE11_STATUS_M_OCP              0x00400000ul
#define HBRIDGE11_STATUS_M_OLF              0x00200000ul
#define HBRIDGE11_STATUS_M_HHF              0x00100000ul
#define HBRIDGE11_STATUS_M_DPM              0x00080000ul
#define HBRIDGE11_STATUS_M_COMF             0x00040000ul
#define HBRIDGE11_STATUS_M_UVM              0x00020000ul
#define HBRIDGE11_STATUS_FREQM_100KHZ       0x00000000ul
#define HBRIDGE11_STATUS_FREQM_80KHZ        0x00010000ul
#define HBRIDGE11_STATUS_FREQM_MASK         0x00010000ul
#define HBRIDGE11_STATUS_CM76_INDEPEND      0x00000000ul
#define HBRIDGE11_STATUS_CM76_PARALLEL      0x00004000ul
#define HBRIDGE11_STATUS_CM76_HBRIDGE       0x00008000ul
#define HBRIDGE11_STATUS_CM76_MASK          0x0000C000ul
#define HBRIDGE11_STATUS_CM54_INDEPEND      0x00000000ul
#define HBRIDGE11_STATUS_CM54_PARALLEL      0x00001000ul
#define HBRIDGE11_STATUS_CM54_HBRIDGE       0x00002000ul
#define HBRIDGE11_STATUS_CM54_MASK          0x00003000ul
#define HBRIDGE11_STATUS_CM32_INDEPEND      0x00000000ul
#define HBRIDGE11_STATUS_CM32_PARALLEL      0x00000400ul
#define HBRIDGE11_STATUS_CM32_HBRIDGE       0x00000800ul
#define HBRIDGE11_STATUS_CM32_MASK          0x00000C00ul
#define HBRIDGE11_STATUS_CM10_INDEPEND      0x00000000ul
#define HBRIDGE11_STATUS_CM10_PARALLEL      0x00000100ul
#define HBRIDGE11_STATUS_CM10_HBRIDGE       0x00000200ul
#define HBRIDGE11_STATUS_CM10_MASK          0x00000300ul
#define HBRIDGE11_STATUS_OVT                0x00000080ul
#define HBRIDGE11_STATUS_OCP                0x00000040ul
#define HBRIDGE11_STATUS_OLF                0x00000020ul
#define HBRIDGE11_STATUS_HHF                0x00000010ul
#define HBRIDGE11_STATUS_DPM                0x00000008ul
#define HBRIDGE11_STATUS_COMF               0x00000004ul
#define HBRIDGE11_STATUS_UVM                0x00000002ul
#define HBRIDGE11_STATUS_ACTIVE             0x00000001ul

/**
 * @brief H-Bridge 11 cfg_ch setting.
 * @details Specified setting for cfg_ch register of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_CFG_CH_HFS_FULL_SCALE     0x00000000ul
#define HBRIDGE11_CFG_CH_HFS_HALF_SCALE     0x80000000ul
#define HBRIDGE11_CFG_CH_HFS_MASK           0x80000000ul
#define HBRIDGE11_CFG_CH_HOLD_HS_OFF_LS_ON  0x00000000ul
#define HBRIDGE11_CFG_CH_HOLD_DUTY_MIN      0x01000000ul
#define HBRIDGE11_CFG_CH_HOLD_DUTY_MAX      0x7E000000ul
#define HBRIDGE11_CFG_CH_HOLD_HS_ON_LS_OFF  0x7F000000ul
#define HBRIDGE11_CFG_CH_HOLD_MASK          0x7F000000ul
#define HBRIDGE11_CFG_CH_TRGNSPI_ONCH       0x00000000ul
#define HBRIDGE11_CFG_CH_TRGNSPI_TRIG       0x00800000ul
#define HBRIDGE11_CFG_CH_TRGNSPI_MASK       0x00800000ul
#define HBRIDGE11_CFG_CH_HIT_HS_OFF_LS_ON   0x00000000ul
#define HBRIDGE11_CFG_CH_HIT_DUTY_MIN       0x00010000ul
#define HBRIDGE11_CFG_CH_HIT_DUTY_MAX       0x007E0000ul
#define HBRIDGE11_CFG_CH_HIT_HS_ON_LS_OFF   0x007F0000ul
#define HBRIDGE11_CFG_CH_HIT_MASK           0x007F0000ul
#define HBRIDGE11_CFG_CH_HIT_T_MASK         0x0000FF00ul
#define HBRIDGE11_CFG_CH_VDRNCDR_CDR        0x00000000ul
#define HBRIDGE11_CFG_CH_VDRNCDR_VDR        0x00000080ul
#define HBRIDGE11_CFG_CH_VDRNCDR_MASK       0x00000080ul
#define HBRIDGE11_CFG_CH_HSNLS_LS           0x00000000ul
#define HBRIDGE11_CFG_CH_HSNLS_HS           0x00000040ul
#define HBRIDGE11_CFG_CH_HSNLS_MASK         0x00000040ul
#define HBRIDGE11_CFG_CH_FREQ_CFG_MAIN_4    0x00000000ul
#define HBRIDGE11_CFG_CH_FREQ_CFG_MAIN_3    0x00000010ul
#define HBRIDGE11_CFG_CH_FREQ_CFG_MAIN_2    0x00000020ul
#define HBRIDGE11_CFG_CH_FREQ_CFG_MAIN      0x00000030ul
#define HBRIDGE11_CFG_CH_FREQ_CFG_MASK      0x00000030ul
#define HBRIDGE11_CFG_CH_SRC_MASK           0x00000008ul
#define HBRIDGE11_CFG_CH_OL_EN_MASK         0x00000004ul
#define HBRIDGE11_CFG_CH_DPM_EN_MASK        0x00000002ul
#define HBRIDGE11_CFG_CH_HHF_EN_MASK        0x00000001ul

/**
 * @brief H-Bridge 11 fault setting.
 * @details Specified setting for fault register of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_FAULT_OCP_MASK            0xFF000000ul
#define HBRIDGE11_FAULT_HHF_MASK            0x00FF0000ul
#define HBRIDGE11_FAULT_OLF_MASK            0x0000FF00ul
#define HBRIDGE11_FAULT_DPM_MASK            0x000000FFul

/**
 * @brief H-Bridge 11 cfg_dpm setting.
 * @details Specified setting for cfg_dpm register of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_CFG_DPM_ISTART_MASK       0x00007F00ul
#define HBRIDGE11_CFG_DPM_TDEB_MASK         0x000000F0ul
#define HBRIDGE11_CFG_DPM_IPTH_MASK         0x0000000Ful

/**
 * @brief H-Bridge 11 motor selection setting.
 * @details Specified setting for motor selection of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_MOTOR_SEL_0               0
#define HBRIDGE11_MOTOR_SEL_1               1
#define HBRIDGE11_MOTOR_SEL_2               2
#define HBRIDGE11_MOTOR_SEL_3               3

/**
 * @brief H-Bridge 11 motor state setting.
 * @details Specified setting for motor state of H-Bridge 11 Click driver.
 */
#define HBRIDGE11_MOTOR_STATE_HI_Z          0
#define HBRIDGE11_MOTOR_STATE_FORWARD       1
#define HBRIDGE11_MOTOR_STATE_REVERSE       2
#define HBRIDGE11_MOTOR_STATE_BRAKE         3    

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hbridge11_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HBRIDGE11_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HBRIDGE11_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hbridge11_set

/**
 * @defgroup hbridge11_map H-Bridge 11 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 11 Click driver.
 */

/**
 * @addtogroup hbridge11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 11 Click to the selected MikroBUS.
 */
#define HBRIDGE11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cmd  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.flt  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge11_map
/*! @} */ // hbridge11

/**
 * @brief H-Bridge 11 Click context object.
 * @details Context object definition of H-Bridge 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cmd;          /**< Command pin (High-CMD, Low-Data). */
    digital_out_t en;           /**< Enable pin (Active high). */

    // Input pins
    digital_in_t flt;           /**< Fault pin (Active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} hbridge11_t;

/**
 * @brief H-Bridge 11 Click configuration object.
 * @details Configuration object definition of H-Bridge 11 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t cmd;             /**< Command pin (High-CMD, Low-Data). */
    pin_name_t en;              /**< Enable pin (Active high). */
    pin_name_t flt;             /**< Fault pin (Active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hbridge11_cfg_t;

/**
 * @brief H-Bridge 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE11_OK = 0,
    HBRIDGE11_ERROR = -1

} hbridge11_return_value_t;

/*!
 * @addtogroup hbridge11 H-Bridge 11 Click Driver
 * @brief API for configuring and manipulating H-Bridge 11 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge11_cfg_setup ( hbridge11_cfg_t *cfg );

/**
 * @brief H-Bridge 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge11_init ( hbridge11_t *ctx, hbridge11_cfg_t *cfg );

/**
 * @brief H-Bridge 11 default configuration function.
 * @details This function executes a default configuration of H-Bridge 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge11_default_cfg ( hbridge11_t *ctx );

/**
 * @brief H-Bridge 11 write 8bit register function.
 * @details This function writes a data byte to the selected register MSB by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge11_write_8bit_register ( hbridge11_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief H-Bridge 11 read 8bit register function.
 * @details This function reads a MSB data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge11_read_8bit_register ( hbridge11_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 11 write 32bit register function.
 * @details This function writes 32-bit data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge11_write_32bit_register ( hbridge11_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief H-Bridge 11 read 32bit register function.
 * @details This function reads 32-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge11_read_32bit_register ( hbridge11_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief H-Bridge 11 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge11_enable_device ( hbridge11_t *ctx );

/**
 * @brief H-Bridge 11 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge11_disable_device ( hbridge11_t *ctx );

/**
 * @brief H-Bridge 11 get fault pin function.
 * @details This function returns the fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hbridge11_get_fault_pin ( hbridge11_t *ctx );

/**
 * @brief H-Bridge 11 read flags function.
 * @details This function reads and clears the fault flags from the status register.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @param[out] fault_flags : Fault flags from the status register [bits 7-0].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge11_read_flags ( hbridge11_t *ctx, uint8_t *fault_flags );

/**
 * @brief H-Bridge 11 set motor state function.
 * @details This function sets the operating state for the selected motor from
 * the half-bridge pairs 0–1, 2–3, 4–5, or 6–7.
 * @param[in] ctx : Click context object.
 * See #hbridge11_t object definition for detailed explanation.
 * @param[in] motor : Motor selection [0-3] related to the half-bridge pairs 0–1, 2–3, 4–5, and 6–7.
 * @param[in] state : @li @c 0 - High-Z,
 *                    @li @c 1 - Forward,
 *                    @li @c 2 - Reverse,
 *                    @li @c 3 - Brake.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge11_set_motor_state ( hbridge11_t *ctx, uint8_t motor, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE11_H

/*! @} */ // hbridge11

// ------------------------------------------------------------------------ END

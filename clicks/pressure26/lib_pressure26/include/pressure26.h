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
 * @file pressure26.h
 * @brief This file contains API for Pressure 26 Click Driver.
 */

#ifndef PRESSURE26_H
#define PRESSURE26_H

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
 * @addtogroup pressure26 Pressure 26 Click Driver
 * @brief API for configuring and manipulating Pressure 26 Click driver.
 * @{
 */

/**
 * @defgroup pressure26_cmd Pressure 26 Commands List
 * @brief List of commands of Pressure 26 Click driver.
 */

/**
 * @addtogroup pressure26_cmd
 * @{
 */

/**
 * @brief Pressure 26 command list.
 * @details Specified command list of Pressure 26 Click driver.
 */
#define PRESSURE26_CMD_ACQUIRE_PRESSURE_10BIT             0x30
#define PRESSURE26_CMD_ACQUIRE_PRESSURE_12BIT             0x34
#define PRESSURE26_CMD_ACQUIRE_PRESSURE_14BIT             0x38
#define PRESSURE26_CMD_ACQUIRE_TEMPERATURE_10BIT          0x50
#define PRESSURE26_CMD_ACQUIRE_TEMPERATURE_12BIT          0x54
#define PRESSURE26_CMD_ACQUIRE_TEMPERATURE_14BIT          0x58
#define PRESSURE26_CMD_TRIGGER_DIAG_10BIT                 0x90
#define PRESSURE26_CMD_TRIGGER_DIAG_12BIT                 0x94
#define PRESSURE26_CMD_TRIGGER_DIAG_14BIT                 0x98
#define PRESSURE26_CMD_TRIGGER_POWER_DOWN                 0xA0
#define PRESSURE26_CMD_TRIGGER_LPM                        0xA8
#define PRESSURE26_CMD_ACQUIRE_LPM_STATUS                 0xA9
#define PRESSURE26_CMD_ACQUIRE_ABS_PRESS_ITER_N           0xAA
#define PRESSURE26_CMD_ACQUIRE_ABS_PRESS_ITER_N1          0xAB
#define PRESSURE26_CMD_ACQUIRE_ABS_PRESS_ITER_N2          0xAC
#define PRESSURE26_CMD_ACQUIRE_LPM_ITER_COUNT             0xAD
#define PRESSURE26_CMD_ACQUIRE_LPM_EDC_CHECK              0xAE
#define PRESSURE26_CMD_ACQUIRE_IDENTIFIER                 0xF0
#define PRESSURE26_CMD_RESET_DIAG                         0x00

/*! @} */ // pressure26_cmd

/**
 * @defgroup pressure26_set Pressure 26 Commands Settings
 * @brief Settings for commands of Pressure 26 Click driver.
 */

/**
 * @addtogroup pressure26_set
 * @{
 */

/**
 * @brief Pressure 26 diagnosis bits for 14-bit response.
 * @details Specified diagnosis bits for 14-bit response of Pressure 26 Click driver.
 */
#define PRESSURE26_DIAG_14BIT_INTERNAL_ERROR              0x8000

/**
 * @brief Pressure 26 diagnosis bits for 12-bit response.
 * @details Specified diagnosis bits for 12-bit response of Pressure 26 Click driver.
 */
#define PRESSURE26_DIAG_12BIT_ECC_ERROR                   0x8000
#define PRESSURE26_DIAG_12BIT_INTERNAL_ERROR              0xE000
#define PRESSURE26_DIAG_12BIT_ACQ_CHAIN_FAIL              0x4000
#define PRESSURE26_DIAG_12BIT_SENSOR_CELL_FAIL            0x2000
#define PRESSURE26_DIAG_12BIT_OK                          0x6000

/**
 * @brief Pressure 26 diagnosis bits for 10-bit response.
 * @details Specified diagnosis bits for 10-bit response of Pressure 26 Click driver.
 */
#define PRESSURE26_DIAG_10BIT_ECC_ERROR                   0x8000  
#define PRESSURE26_DIAG_10BIT_ACQ_CHAIN_FAIL              0x4000
#define PRESSURE26_DIAG_10BIT_SENSOR_CELL_FAIL            0x2000
#define PRESSURE26_DIAG_10BIT_PRESS_HIGH                  0x1000
#define PRESSURE26_DIAG_10BIT_PRESS_LOW                   0x0800
#define PRESSURE26_DIAG_10BIT_OK                          0x5000

 /**
 * @brief Pressure 26 LPM status register bits.
 * @details Specified LPM status register bits of Pressure 26 Click driver.
 */
#define PRESSURE26_LPM_THRESH1_EXCEEDED                   0x8000
#define PRESSURE26_LPM_THRESH2_EXCEEDED                   0x4000
#define PRESSURE26_LPM_STORAGE_ERR                        0x2000
#define PRESSURE26_LPM_EEPROM_UNPROGRAMMED                0x1000
#define PRESSURE26_LPM_EEPROM_ECC_ERR                     0x0800
#define PRESSURE26_LPM_EEPROM_CTRL_ERR                    0x0400
#define PRESSURE26_LPM_OVERVOLTAGE                        0x0200
#define PRESSURE26_LPM_PRESS_HIGH                         0x0100
#define PRESSURE26_LPM_PRESS_LOW                          0x0080
#define PRESSURE26_LPM_DIAG1_ERR                          0x0040
#define PRESSURE26_LPM_DIAG2_ERR                          0x0020
#define PRESSURE26_LPM_TJ_ERR                             0x0010
#define PRESSURE26_LPM_FULL_POR                           0x0008
#define PRESSURE26_LPM_WAKEUP_NCS_CLK                     0x0004
#define PRESSURE26_LPM_COUNTER_ERR                        0x0002

/**
 * @brief Pressure 26 ODD parity flag.
 * @details Specified flag for ODD parity of Pressure 26 Click driver.
 */
#define PRESSURE26_ODD_PARITY                             0x01

/**
 * @brief Pressure 26 identifier response fields.
 * @details Specified identifier response fields of Pressure 26 Click driver.
 */
#define PRESSURE26_IDENTIFIER_SPI_ID                      0x6C
#define PRESSURE26_IDENTIFIER_SPI_ID_MASK                 0xFF
#define PRESSURE26_IDENTIFIER_SUPPLIER_MASK               0x03
#define PRESSURE26_IDENTIFIER_SILICON_VERSION_MASK        0x07
#define PRESSURE26_IDENTIFIER_METAL_VERSION_MASK          0x07

/**
 * @brief Pressure 26 pressure and temperature calculation.
 * @details Specified pressure and temperature calculation of Pressure 26 Click driver.
 */
#define PRESSURE26_SP_14BIT                               18.203f
#define PRESSURE26_OFFSP_14BIT                         ( -9102.0f )
#define PRESSURE26_ST_14BIT                               99.29f
#define PRESSURE26_OFFST_14BIT_5V                         3971.64f
#define PRESSURE26_OFFST_14BIT_3V3                        3822.7f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b pressure26_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PRESSURE26_SET_DATA_SAMPLE_EDGE                   SET_SPI_DATA_SAMPLE_EDGE
#define PRESSURE26_SET_DATA_SAMPLE_MIDDLE                 SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // pressure26_set

/**
 * @defgroup pressure26_map Pressure 26 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 26 Click driver.
 */

/**
 * @addtogroup pressure26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 26 Click to the selected MikroBUS.
 */
#define PRESSURE26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure26_map
/*! @} */ // pressure26

/**
 * @brief Pressure 26 Click context object.
 * @details Context object definition of Pressure 26 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t wkp;                           /**< Wake-up output pin. */

    // Modules
    spi_master_t spi;                           /**< SPI driver object. */

    pin_name_t   chip_select;                   /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t      prev_cmd;                      /**< Previous command. */

} pressure26_t;

/**
 * @brief Pressure 26 Click configuration object.
 * @details Configuration object definition of Pressure 26 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wkp;             /**< Wake-up output pin descriptor. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} pressure26_cfg_t;

/**
 * @brief Pressure 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE26_OK = 0,
    PRESSURE26_ERROR = -1

} pressure26_return_value_t;

/*!
 * @addtogroup pressure26 Pressure 26 Click Driver
 * @brief API for configuring and manipulating Pressure 26 Click driver.
 * @{
 */

/**
 * @brief Pressure 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure26_cfg_setup ( pressure26_cfg_t *cfg );

/**
 * @brief Pressure 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_init ( pressure26_t *ctx, pressure26_cfg_t *cfg );

/**
 * @brief Pressure 26 send command function.
 * @details This function sends a command over the SPI interface, reads the previous
 * response word and validates the odd parity bit.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @param[out] prev_rsp : Pointer to the previous response word (can be NULL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_send_cmd ( pressure26_t *ctx, uint8_t cmd, uint16_t *prev_rsp );

/**
 * @brief Pressure 26 get pressure function.
 * @details This function triggers a 14-bit pressure acquisition and calculates the result in millibars.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @param[out] press : Pressure value in millibars.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_get_pressure ( pressure26_t *ctx, float *press );

/**
 * @brief Pressure 26 get temperature function.
 * @details This function triggers a 14-bit temperature acquisition and calculates the result in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_get_temperature ( pressure26_t *ctx, float *temp );

/**
 * @brief Pressure 26 get identifier function.
 * @details This function triggers an identifier acquisition and reads the identifier response word.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @param[out] identifier : Pointer to the raw identifier value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_get_identifier ( pressure26_t *ctx, uint16_t *identifier );

/**
 * @brief Pressure 26 power down function.
 * @details This function sends the command that triggers the device power-down mode.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_power_down ( pressure26_t *ctx );

/**
 * @brief Pressure 26 trigger low power monitoring mode function.
 * @details This function sends the command that triggers the device
 * low power monitoring (LPM) mode.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_trigger_lpm ( pressure26_t *ctx );

/**
 * @brief Pressure 26 get LPM status register function.
 * @details This function requests the LPM status register and reads
 * the 16-bit response.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @param[in] lpm_status : Pointer to the 16-bit LPM status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure26_get_lpm_status ( pressure26_t *ctx, uint16_t *lpm_status );

/**
 * @brief Pressure 26 WKP pin state function.
 * @details This function reads the state of the WKP digital output pin.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @return Pin state (0/1).
 * @note None.
 */
uint8_t pressure26_get_wkp_pin ( pressure26_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE26_H

/*! @} */ // pressure26

// ------------------------------------------------------------------------ END

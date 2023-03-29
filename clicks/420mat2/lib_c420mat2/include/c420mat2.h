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
 * @file c420mat2.h
 * @brief This file contains API for 4-20mA T 2 Click Driver.
 */

#ifndef C420MAT2_H
#define C420MAT2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup c420mat2 4-20mA T 2 Click Driver
 * @brief API for configuring and manipulating 4-20mA T 2 Click driver.
 * @{
 */

/**
 * @defgroup c420mat2_reg 4-20mA T 2 Registers List
 * @brief List of registers of 4-20mA T 2 Click driver.
 */

/**
 * @addtogroup c420mat2_reg
 * @{
 */

/**
 * @brief 4-20mA T 2 description register.
 * @details Specified register for description of 4-20mA T 2 Click driver.
 */
#define C420MAT2_REG_XFER                            0x01
#define C420MAT2_REG_NOP                             0x02
#define C420MAT2_REG_WR_MODE                         0x03
#define C420MAT2_REG_DACCODE                         0x04
#define C420MAT2_REG_ERR_CONFIG                      0x05
#define C420MAT2_REG_ERR_LOW                         0x06
#define C420MAT2_REG_ERR_HIGH                        0x07
#define C420MAT2_REG_RESET                           0x08
#define C420MAT2_REG_STATUS                          0x09

/*! @} */ // c420mat2_reg

/**
 * @defgroup c420mat2_set 4-20mA T 2 Registers Settings
 * @brief Settings for registers of 4-20mA T 2 Click driver.
 */

/**
 * @addtogroup c420mat2_set
 * @{
 */

/**
 * @brief 4-20mA T 2 description setting.
 * @details Specified setting for description of 4-20mA T 2 Click driver.
 */
#define C420MAT2_CMD_XFER                            0x00FF
#define C420MAT2_CMD_NOP                             0x0000
#define C420MAT2_CMD_WR_MODE_DISABLE                 0x0000
#define C420MAT2_CMD_WR_MODE_ENABLE                  0x0001
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_50ms     0x0000
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_100ms    0x0100
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_150ms    0x0200
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_200ms    0x0300
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_250ms    0x0400
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_300ms    0x0500
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_350ms    0x0600
#define C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_400ms    0x0700
#define C420MAT2_CMD_DIS_RETRY_LOOP_DISABLE          0x0000
#define C420MAT2_CMD_DIS_RETRY_LOOP_ENABLE           0x0080
#define C420MAT2_CMD_MASK_LOOP_ERR_DISABLE           0x0000
#define C420MAT2_CMD_MASK_LOOP_ERR_ENABLE            0x0040
#define C420MAT2_CMD_DIS_LOOP_ERR_ERRB_DISABLE       0x0000
#define C420MAT2_CMD_DIS_LOOP_ERR_ERRB_ENABLE        0x0020  
#define C420MAT2_CMD_MASK_SPI_ERR_DISABLE            0x0000
#define C420MAT2_CMD_MASK_SPI_ERR_ENABLE             0x0010
#define C420MAT2_CMD_SPI_TIMEOUT_50ms                0x0000
#define C420MAT2_CMD_SPI_TIMEOUT_100ms               0x0002
#define C420MAT2_CMD_SPI_TIMEOUT_150ms               0x0004
#define C420MAT2_CMD_SPI_TIMEOUT_200ms               0x0006
#define C420MAT2_CMD_SPI_TIMEOUT_250ms               0x0008
#define C420MAT2_CMD_SPI_TIMEOUT_300ms               0x000A
#define C420MAT2_CMD_SPI_TIMEOUT_350ms               0x000C
#define C420MAT2_CMD_SPI_TIMEOUT_400ms               0x000E
#define C420MAT2_CMD_MASK_SPI_TOUT_DISABLE           0x0000
#define C420MAT2_CMD_MASK_SPI_TOUT_ENABLE            0x0001
#define C420MAT2_CMD_RESET                           0xC33C

/**
 * @brief 4-20mA T 2 status bitmask.
 * @details Specified setting for status bitmask of 4-20mA T 2 Click driver.
 */
#define C420MAT2_STATUS_DAC_RES_BIT_MASK             0x00E0
#define C420MAT2_STATUS_ERRLVL_PIN_BIT_MASK          0x0010
#define C420MAT2_STATUS_FERR_STS_BIT_MASK            0x0008
#define C420MAT2_STATUSSPI_TIMEOUT_ERR_BIT_MASK      0x0004
#define C420MAT2_STATUS_LOOP_STS_BIT_MASK            0x0002
#define C420MAT2_STATUS_CURR_LOOP_STS_BIT_MASK       0x0001


/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c420mat2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C420MAT2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define C420MAT2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c420mat2_set

/**
 * @defgroup c420mat2_map 4-20mA T 2 MikroBUS Map
 * @brief MikroBUS pin mapping of 4-20mA T 2 Click driver.
 */

/**
 * @addtogroup c420mat2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 4-20mA T 2 Click to the selected MikroBUS.
 */
#define C420MAT2_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.err = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c420mat2_map
/*! @} */ // c420mat2

/**
 * @brief 4-20mA T 2 Click context object.
 * @details Context object definition of 4-20mA T 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;           /**< Reset pin. */

    // Input pins
    digital_in_t err;            /**< Error flag pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} c420mat2_t;

/**
 * @brief 4-20mA T 2 Click configuration object.
 * @details Configuration object definition of 4-20mA T 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t err;    /**< Error flag pin. */

    // static variable
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

} c420mat2_cfg_t;

/**
 * @brief 4-20mA T 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C420MAT2_OK = 0,
    C420MAT2_ERROR = -1

} c420mat2_return_value_t;

/**
 * @brief 4-20mA T 2 Click status object.
 * @details Status object definition of 4-20mA T 2 Click driver.
 */
typedef struct
{
    uint8_t    errlvl_pin;
    uint8_t    ferr_sts;
    uint8_t    spi_timeout_err;
    uint8_t    loop_sts;
    uint8_t    curr_loop_sts;

} c420mat2_status_t;

/**
 * @brief 4-20mA T 2 Click error status value data.
 * @details Predefined enum values for error status values.
 */
typedef enum
{
    C420MAT2_STATUS_OK = 0,
    C420MAT2_STATUS_ERROR = 1

} c420mat2_status_value_t;

/*!
 * @addtogroup c420mat2 4-20mA T 2 Click Driver
 * @brief API for configuring and manipulating 4-20mA T 2 Click driver.
 * @{
 */

/**
 * @brief 4-20mA T 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c420mat2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c420mat2_cfg_setup ( c420mat2_cfg_t *cfg );

/**
 * @brief 4-20mA T 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c420mat2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_init ( c420mat2_t *ctx, c420mat2_cfg_t *cfg );

/**
 * @brief 4-20mA T 2 default configuration function.
 * @details This function executes a default configuration of 4-20mA T 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c420mat2_default_cfg ( c420mat2_t *ctx );

/**
 * @brief 4-20mA T 2 data writing function.
 * @details This function writes a desired byte of data to
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_write_data ( c420mat2_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief 4-20mA T 2 data reading function.
 * @details This function reads a desired byte of data from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_read_data ( c420mat2_t *ctx, uint8_t cmd, uint16_t *data_out );

/**
 * @brief 4-20mA T 2 protected data writing function.
 * @details This function protected writes a desired byte of data to
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Protected data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_protected_write ( c420mat2_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief 4-20mA T 2 soft reset function.
 * @details This function performs software reset of 
 * the DAC161S997 16-Bit SPI-Programmable DAC for 4-20 mA Loops on 
 * the 4-20mA T 2 Click board™.  
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_sw_reset ( c420mat2_t *ctx );

/**
 * @brief 4-20mA T 2 set DAC data function.
 * @details This function writes a DAC data to
 * the C420MAT2_REG_DACCODE register of 
 * the DAC161S997 16-Bit SPI-Programmable DAC for 4-20 mA Loops on 
 * the 4-20mA T 2 Click board™.  
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] dac_output_code : DAC data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_set_dac_data ( c420mat2_t *ctx, uint16_t dac_output_code );

/**
 * @brief 4-20mA T 2 set lower limit function.
 * @details This functionset lower error conditions the output current of 
 * the DAC161S997 16-Bit SPI-Programmable DAC for 4-20 mA Loops on 
 * the 4-20mA T 2 Click board™.  
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] lower_limit_ma : Error conditions the output current (range from 0mA to 12mA).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t  c420mat2_set_lower_limit ( c420mat2_t *ctx, float lower_limit_ma );

/**
 * @brief 4-20mA T 2 set upper limit function.
 * @details This functionset upper error conditions the output current of 
 * the DAC161S997 16-Bit SPI-Programmable DAC for 4-20 mA Loops on 
 * the 4-20mA T 2 Click board™.  
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] upper_limit_ma : Error conditions the output current (range from 12mA to 20mA).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_set_upper_limit ( c420mat2_t *ctx, float upper_limit_ma );

/**
 * @brief 4-20mA T 2 set output current function.
 * @details This functionset set analog output current transfer 
 * over an industry standard 4-20mA current loop of 
 * the DAC161S997 16-Bit SPI-Programmable DAC for 4-20 mA Loops on 
 * the 4-20mA T 2 Click board™.  
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[in] current_ma : Output loop current value 
 * (range from 4mA to 20mA).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_set_output_current ( c420mat2_t *ctx, float current_ma );

/**
 * @brief 4-20mA T 2 set status function.
 * @details This functionset set status data object of 
 * the DAC161S997 16-Bit SPI-Programmable DAC for 4-20 mA Loops on 
 * the 4-20mA T 2 Click board™.  
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @param[out] status : Status data object.
 * (range from 4mA to 20mA).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat2_get_status ( c420mat2_t *ctx, c420mat2_status_t *status );

/**
 * @brief 4-20mA T 2 get error flag pin state function.
 * @details This function get states of the ERR ( INT pin ) of
 * the DAC161S997 16-Bit SPI-Programmable DAC for 4-20 mA Loops on 
 * the 4-20mA T 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #c420mat2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t c420mat2_get_err_pin ( c420mat2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C420MAT2_H

/*! @} */ // c420mat2

// ------------------------------------------------------------------------ END

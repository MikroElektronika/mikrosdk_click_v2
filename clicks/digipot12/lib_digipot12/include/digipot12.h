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
 * @file digipot12.h
 * @brief This file contains API for DIGI POT 12 Click Driver.
 */

#ifndef DIGIPOT12_H
#define DIGIPOT12_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup digipot12 DIGI POT 12 Click Driver
 * @brief API for configuring and manipulating DIGI POT 12 Click driver.
 * @{
 */

/**
 * @defgroup digipot12_cmd DIGI POT 12 Registers List
 * @brief List of registers of DIGI POT 12 Click driver.
 */

/**
 * @addtogroup digipot12_ctrl
 * @{
 */

/**
 * @brief DIGI POT 12 description control bits.
 * @details Specified control bits for description of DIGI POT 12 Click driver.
 */
#define DIGIPOT12_CTRL_BIT_NOP                       0x00
#define DIGIPOT12_CTRL_BIT_WRITE_RDAC                0x10
#define DIGIPOT12_CTRL_BIT_WRITE_SHIFT_REG           0x20
#define DIGIPOT12_CTRL_BIT_READ                      0x30
#define DIGIPOT12_CTRL_BIT_LIN_RDAC                  0x40
#define DIGIPOT12_CTRL_BIT_6_DB_RDAC                 0x50
#define DIGIPOT12_CTRL_BIT_COPY_LRDAC                0x60
#define DIGIPOT12_CTRL_BIT_COPY_RDAC_EEPROM          0x70
#define DIGIPOT12_CTRL_BIT_WRITE_EEPROM              0x80
#define DIGIPOT12_CTRL_BIT_SCALE                     0x90
#define DIGIPOT12_CTRL_BIT_SW_RST                    0xB0
#define DIGIPOT12_CTRL_BIT_SW_SHDN                   0xC0
#define DIGIPOT12_CTRL_BIT_REG_CTRL                  0xD0
#define DIGIPOT12_CTRL_BIT_MASK                      0xF0

/*! @} */ // digipot12_ctrl

/**
 * @addtogroup digipot12_addr
 * @{
 */

/**
 * @brief DIGI POT 12 description address bits.
 * @details Specified address bits for description of DIGI POT 12 Click driver.
 */
#define DIGIPOT12_ADDR_BIT_RDAC1                     0x00
#define DIGIPOT12_ADDR_BIT_RDAC2                     0x01
#define DIGIPOT12_ADDR_BIT_ALL_CHANNELS              0x08

/*! @} */ // digipot12_addr

/**
 * @addtogroup digipot12_wiper_sel
 * @{
 */

/**
 * @brief DIGI POT 12 description of the wiper selection.
 * @details Specified setting for wiper selection of DIGI POT 12 Click driver.
 */
#define DIGIPOT12_WIPER_SEL_1                        0x00
#define DIGIPOT12_WIPER_SEL_2                        0x01
#define DIGIPOT12_WIPER_SEL_BOTH                     0x08

/*! @} */ // digipot12_wiper_sel

/**
 * @addtogroup digipot12_mask
 * @{
 */

/**
 * @brief DIGI POT 12 description mask data bits.
 * @details Specified mask data bits for description of DIGI POT 12 Click driver.
 */
#define DIGIPOT12_ADDR_BIT_READ_INPUT_REG            0x00
#define DIGIPOT12_ADDR_BIT_READ_EEPROM               0x01
#define DIGIPOT12_ADDR_BIT_READ_CTRL_REG             0x02
#define DIGIPOT12_ADDR_BIT_READ_RDAC                 0x03
#define DIGIPOT12_ADDR_BIT_RDAC_DECR                 0x00
#define DIGIPOT12_ADDR_BIT_RDAC_INCR                 0x01
#define DIGIPOT12_ADDR_BIT_COPY_TO_RDAC              0x00
#define DIGIPOT12_ADDR_BIT_COPY_TO_EEPROM            0x01
#define DIGIPOT12_ADDR_BIT_SCALE_MODE_NORMAL         0x80
#define DIGIPOT12_ADDR_BIT_SCALE_MODE_SHDN           0x81
#define DIGIPOT12_ADDR_BIT_SCALE_EXIT                0x00
#define DIGIPOT12_ADDR_BIT_SCALE_ENTER               0x01
#define DIGIPOT12_ADDR_BIT_SW_SHDN_MODE_NORMAL       0x00
#define DIGIPOT12_ADDR_BIT_SW_SHDN_MODE_SHDN         0x01


/*! @} */ // digipot12_mask

/**
 * @defgroup digipot12_set DIGI POT 12 Registers Settings
 * @brief Settings for registers of DIGI POT 12 Click driver.
 */

/**
 * @addtogroup digipot12_set
 * @{
 */

/**
 * @brief DIGI POT 12 control register bit descriptions.
 * @details Specified control register bit descriptions of DIGI POT 12 Click driver.
 */
#define DIGIPOT12_CTRL_REG_WIPER_POS_FROZEN          0x00
#define DIGIPOT12_CTRL_REG_UPDATE_WIPER_POS          0x01
#define DIGIPOT12_CTRL_REG_EEPROM_PROGRAM_DISABLE    0x00
#define DIGIPOT12_CTRL_REG_EEPROM_PROGRAM_ENABLE     0x02
#define DIGIPOT12_CTRL_REG_MODE_POTENTIOMETER        0x00
#define DIGIPOT12_CTRL_REG_MODE_LINEAR_GAIN          0x04
#define DIGIPOT12_CTRL_REG_MODE_BURST_DISABLE        0x00
#define DIGIPOT12_CTRL_REG_MODE_BURST_ENABLE         0x08

/**
 * @brief DIGI POT 12 wiper and resistance data values.
 * @details Specified wiper and resistance data values of DIGI POT 12 Click driver.
 */
#define DIGIPOT12_WIPER_POS_MAX                      255
#define DIGIPOT12_WIPER_POS_MIN                        0
#define DIGIPOT12_WIPER_POS_MIDDLE                   127
#define DIGIPOT12_RES_10_KOHM                         10
#define DIGIPOT12_RES_0_KOHM                           0

/**
 * @brief DIGI POT 12 device address setting.
 * @details Specified setting for device slave address selection of
 * DIGI POT 12 Click driver.
 */
#define DIGIPOT12_DEVICE_ADDRESS_0                   0x2F
#define DIGIPOT12_DEVICE_ADDRESS_1                   0x2C
#define DIGIPOT12_DEVICE_ADDRESS_2                   0x23
#define DIGIPOT12_DEVICE_ADDRESS_3                   0x20

/*! @} */ // digipot12_set

/**
 * @defgroup digipot12_map DIGI POT 12 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 12 Click driver.
 */

/**
 * @addtogroup digipot12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 12 Click to the selected MikroBUS.
 */
#define DIGIPOT12_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // digipot12_map
/*! @} */ // digipot12

/**
 * @brief DIGI POT 12 Click context object.
 * @details Context object definition of DIGI POT 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;        /**< Reset pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} digipot12_t;

/**
 * @brief DIGI POT 12 Click configuration object.
 * @details Configuration object definition of DIGI POT 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;    /**< Reset pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} digipot12_cfg_t;

/**
 * @brief DIGI POT 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT12_OK = 0,
    DIGIPOT12_ERROR = -1

} digipot12_return_value_t;

/*!
 * @addtogroup digipot12 DIGI POT 12 Click Driver
 * @brief API for configuring and manipulating DIGI POT 12 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot12_cfg_setup ( digipot12_cfg_t *cfg );

/**
 * @brief DIGI POT 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_init ( digipot12_t *ctx, digipot12_cfg_t *cfg );

/**
 * @brief DIGI POT 12 default configuration function.
 * @details This function executes a default configuration of DIGI POT 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digipot12_default_cfg ( digipot12_t *ctx );

/**
 * @brief DIGI POT 12 enable the device function.
 * @details This function performs the enable the device
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void digipot12_device_enable ( digipot12_t *ctx );

/**
 * @brief DIGI POT 12 hardware reset function.
 * @details This function perform the hardware reset 
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void digipot12_hw_reset ( digipot12_t *ctx );

/**
 * @brief DIGI POT 12 I2C writing function.
 * @details This function writes a byte of data for 
 * the selected command and address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] ctrl : Control bits - commands operation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_write_data ( digipot12_t *ctx, uint8_t ctrl, uint8_t addr, uint8_t data_in );

/**
 * @brief DIGI POT 12 I2C reading function.
 * @details This function reads a byte of data from
 * the selected address and data bits mask by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[in] mask : Data bits mask.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_read_data ( digipot12_t *ctx, uint8_t addr, uint8_t mask, uint8_t *data_out );

/**
 * @brief DIGI POT 12 write the RDAC function.
 * @details This function writes RDAC data value
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_write_rdac ( digipot12_t *ctx, uint8_t addr, uint8_t data_in );

/**
 * @brief DIGI POT 12 read the RDAC function.
 * @details This function reads the RDAC data value
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_read_rdac ( digipot12_t *ctx, uint8_t addr, uint8_t *data_out );

/**
 * @brief DIGI POT 12 set wiper 1 function.
 * @details This function sets the position of the wiper 1
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper 1 position [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_set_wiper_1 ( digipot12_t *ctx, uint8_t wiper_pos );

/**
 * @brief DIGI POT 12 set wiper 2 function.
 * @details This function sets the position of the wiper 2
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper 2 position [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_set_wiper_2 ( digipot12_t *ctx, uint8_t wiper_pos );

/**
 * @brief DIGI POT 12 set the resistance function.
 * @details This function sets the resistance of the selected wiper 
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] wiper_sel : Wiper selection.
 * @param[in] res_kohm : Rwb1/2 (wiper-to-B) resistance from 0.0 to 10.0 [kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_set_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float res_kohm );

/**
 * @brief DIGI POT 12 get the resistance function.
 * @details This function gets the resistance of the selected wiper 
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the DIGI POT 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot12_t object definition for detailed explanation.
 * @param[in] wiper_sel : Wiper selection.
 * @param[out] res_kohm : Rwb1/2 (wiper-to-B) resistance from 0.0 to 10.0 [kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot12_get_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float *res_kohm );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT12_H

/*! @} */ // digipot12

// ------------------------------------------------------------------------ END

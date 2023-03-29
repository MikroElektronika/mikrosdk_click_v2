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
 * @file nvsram.h
 * @brief This file contains API for nvSRAM Click Driver.
 */

#ifndef NVSRAM_H
#define NVSRAM_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup nvsram nvSRAM Click Driver
 * @brief API for configuring and manipulating nvSRAM Click driver.
 * @{
 */

/**
 * @defgroup nvsram_reg nvSRAM Registers List
 * @brief List of registers of nvSRAM Click driver.
 */

/**
 * @addtogroup nvsram_reg
 * @{
 */

/**
 * @brief nvSRAM description of control registers.
 * @details Specified control registers of nvSRAM Click driver.
 */
#define NVSRAM_MEM_CTL_REG             0x00
#define NVSRAM_SERIAL_NUM_REG_1        0x01
#define NVSRAM_SERIAL_NUM_REG_2        0x02
#define NVSRAM_SERIAL_NUM_REG_3        0x03
#define NVSRAM_SERIAL_NUM_REG_4        0x04
#define NVSRAM_SERIAL_NUM_REG_5        0x05
#define NVSRAM_SERIAL_NUM_REG_6        0x06
#define NVSRAM_SERIAL_NUM_REG_7        0x07
#define NVSRAM_SERIAL_NUM_REG_8        0x08
#define NVSRAM_DEV_ID_REG_1            0x09
#define NVSRAM_DEV_ID_REG_2            0x0A
#define NVSRAM_DEV_ID_REG_3            0x0B
#define NVSRAM_DEV_ID_REG_4            0x0C
#define NVSRAM_CMD_REG                 0xAA

/*! @} */ // nvsram_reg

/**
 * @defgroup nvsram_set nvSRAM Registers Settings
 * @brief Settings for registers of nvSRAM Click driver.
 */

/**
 * @addtogroup nvsram_set
 * @{
 */

/**
 * @brief nvSRAM description setting.
 * @details Specified setting for description of nvSRAM Click driver.
 */
#define NVSRAM_I2C_MEM_SEL             0x50

/**
 * @brief nvSRAM description of commands.
 * @details Specified commands of nvSRAM Click driver.
 */
#define NVSRAM_CMD_STORE               0x3C
#define NVSRAM_CMD_RECALL              0x60
#define NVSRAM_CMD_ASENB               0x59
#define NVSRAM_CMD_ASDISB              0x19
#define NVSRAM_CMD_SLEEP               0xB9

/**
 * @brief nvSRAM description of block protection.
 * @details Specified commands for block protection of nvSRAM Click driver.
 */
#define NVSRAM_BP_NONE                 0x00
#define NVSRAM_BP_QUARTER              0x04
#define NVSRAM_BP_HALF                 0x08
#define NVSRAM_BP_ALL                  0x0C
#define NVSRAM_NO_SNL                  0x00
#define NVSRAM_SNL                     0x40

/**
 * @brief nvSRAM description of memory enable and disable.
 * @details Specified description of memory enable and disable nvSRAM Click driver.
 */
#define NVSRAM_WRITE_MEMORY_DISABLE    0x00
#define NVSRAM_WRITE_MEMORY_ENABLE     0x01

/**
 * @brief nvSRAM control registers slave.
 * @details Specified setting for slave address of nvSRAM Click driver.
 */
#define NVSRAM_I2C_SLAVE_ADDR_0        0x18
#define NVSRAM_I2C_SLAVE_ADDR_1        0x1A
#define NVSRAM_I2C_SLAVE_ADDR_2        0x1C
#define NVSRAM_I2C_SLAVE_ADDR_3        0x1E

/*! @} */ // nvsram_set

/**
 * @defgroup nvsram_map nvSRAM MikroBUS Map
 * @brief MikroBUS pin mapping of nvSRAM Click driver.
 */

/**
 * @addtogroup nvsram_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of nvSRAM Click to the selected MikroBUS.
 */
#define NVSRAM_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // nvsram_map
/*! @} */ // nvsram

/**
 * @brief nvSRAM Click context object.
 * @details Context object definition of nvSRAM Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;                               /**< Write protection. */

    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} nvsram_t;

/**
 * @brief nvSRAM Click configuration object.
 * @details Configuration object definition of nvSRAM Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  wp;         /**< Write protection. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} nvsram_cfg_t;

/**
 * @brief nvSRAM Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   NVSRAM_OK = 0,
   NVSRAM_ERROR = -1

} nvsram_return_value_t;

/*!
 * @addtogroup nvsram nvSRAM Click Driver
 * @brief API for configuring and manipulating nvSRAM Click driver.
 * @{
 */

/**
 * @brief nvSRAM configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nvsram_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nvsram_cfg_setup ( nvsram_cfg_t *cfg );

/**
 * @brief nvSRAM initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nvsram_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram_init ( nvsram_t *ctx, nvsram_cfg_t *cfg );

/**
 * @brief nvSRAM I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram_generic_write ( nvsram_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief nvSRAM I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram_generic_read ( nvsram_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Generic write the byte of data function.
 * @details The function writes the byte of data to the targeted 8-bit
 * register address of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_data : Data to be written.
 * @return Nothing.
 * 
 * @note None.
 */
void nvsram_reg_write ( nvsram_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Generic read the byte of data function.
 * @details The function read a the byte of data from the targeted 8-bit
 * register address of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @return 8-bit read data.
 * 
 * @note None.
 */
uint8_t nvsram_reg_read ( nvsram_t *ctx, uint8_t reg );

/**
 * @brief Burst register write function.
 * @details The function writes a sequential data starting
 * of the targeted 8-bit register address
 * of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] p_tx_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return Nothing.
 * 
 * @note None.
 */
void nvsram_burst_reg_write ( nvsram_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Burst register read function.
 * @details The function read a sequential data starting
 * from the targeted 8-bit register address
 * of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : number of bytes to be read.
 * @return Nothing.
 * 
 * @note None.
 */
void nvsram_burst_reg_read ( nvsram_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Send command function.
 * @details The function sends the desired command
 * to the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] cmd : Command that is being sent.
 * @return Nothing.
 * 
 * @note None.
 */
void nvsram_send_cmd ( nvsram_t *ctx, uint8_t cmd );

/**
 * @brief Read device ID function.
 * @details The function read a device ID
 * of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @return 32-bit read device ID.
 * 
 * @note None.
 */
uint32_t nvsram_read_dev_id ( nvsram_t *ctx );

/**
 * @brief Write memory function.
 * @details The function writes a sequential data starting
 * of the targeted 17-bit memory address
 * of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] mem_adr : 17-bit start memory address.
 * @param[in] p_tx_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return Nothing.
 * 
 * @note None.
 */
void nvsram_memory_write ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_tx_data, uint16_t n_bytes );

/**
 * @brief Read memory function.
 * @details The function read a sequential data starting
 * from the targeted 17-bit memory address
 * of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] mem_adr : 17-bit start memory address.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : Number of bytes to be read.
 * @return Nothing.
 * 
 * @note None.
 */
void nvsram_memory_read ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_rx_data, uint16_t n_bytes );

/**
 * @brief Enable memory write function.
 * @details The function enable write depending on the function argument
 * of the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM
 * on nvSRAM click board.
 * @param[in] ctx : Click context object.
 * See #nvsram_t object definition for detailed explanation.
 * @param[in] en_wr_mem : Write enable or disable.
 * @return Nothing.
 * 
 * @note None.
 */
void nvsram_enable_memory_write ( nvsram_t *ctx, uint8_t en_wr_mem );

#ifdef __cplusplus
}
#endif
#endif // NVSRAM_H

/*! @} */ // nvsram

// ------------------------------------------------------------------------ END

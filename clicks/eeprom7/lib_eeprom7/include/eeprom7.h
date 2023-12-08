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
 * @file eeprom7.h
 * @brief This file contains API for EEPROM 7 Click Driver.
 */

#ifndef EEPROM7_H
#define EEPROM7_H

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

/*!
 * @addtogroup eeprom7 EEPROM 7 Click Driver
 * @brief API for configuring and manipulating EEPROM 7 Click driver.
 * @{
 */

/**
 * @defgroup eeprom7_reg EEPROM 7 Registers List
 * @brief List of registers of EEPROM 7 Click driver.
 */

/**
 * @addtogroup eeprom7_reg
 * @{
 */

/**
 * @brief EEPROM 7 description register.
 * @details Specified register for description of EEPROM 7 Click driver.
 */
#define EEPROM7_OPCODE_STATUS_RDSR                  0x05
#define EEPROM7_OPCODE_STATUS_WRBP                  0x08
#define EEPROM7_OPCODE_STATUS_WREN                  0x06
#define EEPROM7_OPCODE_STATUS_WRDI                  0x04
#define EEPROM7_OPCODE_STATUS_WRSR                  0x01

/**
 * @brief EEPROM 7 Security register instructions.
 * @details Security register instructions of EEPROM 7 Click driver.
 */
#define EEPROM7_OPCODE_EEPROM_SECURITY_READ         0x03
#define EEPROM7_OPCODE_EEPROM_SECURITY_WRITE        0x02
#define EEPROM7_OPCODE_EEPROM_SECURITY_RDEX         0x83
#define EEPROM7_OPCODE_EEPROM_SECURITY_WREX         0x82
#define EEPROM7_OPCODE_EEPROM_SECURITY_LOCK         0x82
#define EEPROM7_OPCODE_EEPROM_SECURITY_CHLK         0x83

/**
 * @brief EEPROM 7 Memory partition register instructions.
 * @details Memory partition register instructions of EEPROM 7 Click driver.
 */
#define EEPROM7_OPCODE_MP_REG_RMPR                  0x31
#define EEPROM7_OPCODE_MP_REG_PRWE                  0x07
#define EEPROM7_OPCODE_MP_REG_PRWD                  0x0A
#define EEPROM7_OPCODE_MP_REG_WMPR                  0x32
#define EEPROM7_OPCODE_MP_REG_PPAB                  0x34
#define EEPROM7_OPCODE_MP_REG_FRZR                  0x37

/**
 * @brief EEPROM 7 Identification register instructions.
 * @details Identification register instructions of EEPROM 7 Click driver.
 */
#define EEPROM7_OPCODE_MP_REG_SPID                  0x9F

/**
 * @brief EEPROM 7 Device reset instruction.
 * @details Device reset instruction of EEPROM 7 Click driver.
 */
#define EEPROM7_OPCODE_SW_RESET_SRST                0x7C

/**
 * @brief EEPROM 7 Write enable/disable.
 * @details Write enable/disable of EEPROM 7 Click driver.
 */
#define EEPROM7_SEC_WRITE_DISABLE                   0x00
#define EEPROM7_SEC_WRITE_ENABLE                    0x01

/**
 * @brief EEPROM 7 Pin state.
 * @details Pin state of EEPROM 7 Click driver.
 */
#define EEPROM7_PIN_WRITE_PROTECT_DISABLE           0x00
#define EEPROM7_PIN_WRITE_PROTECT_ENABLE            0x01
#define EEPROM7_PIN_HOLD_PROTECT_DISABLE            0x00
#define EEPROM7_PIN_HOLD_PROTECT_ENABLE             0x01

/**
 * @brief EEPROM 7 Status.
 * @details Status of EEPROM 7 Click driver.
 */
#define EEPROM7_STATUS_ERROR                        0x00
#define EEPROM7_STATUS_SUCCESS                      0x01
#define EEPROM7_DUMMY                               0x00
#define EEPROM7_ENABLE_WRITE_DISABLE                0x00
#define EEPROM7_ENABLE_WRITE_ENABLE                 0x01
#define EEPROM7_DEVICE_NOT_READY                    0x00
#define EEPROM7_DEVICE_IS_READY                     0x01

/*! @} */ // eeprom7_reg

/**
 * @defgroup eeprom7_map EEPROM 7 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 7 Click driver.
 */

/**
 * @addtogroup eeprom7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 7 Click to the selected MikroBUS.
 */
#define EEPROM7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // eeprom7_map
/*! @} */ // eeprom7

/**
 * @brief EEPROM 7 Click context object.
 * @details Context object definition of EEPROM 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;     /**< Write Protect. */
    digital_out_t  hld;     /**< Hold. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} eeprom7_t;

/**
 * @brief EEPROM 7 Click configuration object.
 * @details Configuration object definition of EEPROM 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  wp;        /**< Write Protect. */
    pin_name_t  hld;        /**< Hold. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} eeprom7_cfg_t;

/**
 * @brief EEPROM 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EEPROM7_OK = 0,
   EEPROM7_ERROR = -1

} eeprom7_return_value_t;

/*!
 * @addtogroup eeprom7 EEPROM 7 Click Driver
 * @brief API for configuring and manipulating EEPROM 7 Click driver.
 * @{
 */

/**
 * @brief EEPROM 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom7_cfg_setup ( eeprom7_cfg_t *cfg );

/**
 * @brief EEPROM 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom7_init ( eeprom7_t *ctx, eeprom7_cfg_t *cfg );

/**
 * @brief EEPROM 7 default configuration function.
 * @details This function executes a default configuration of EEPROM 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t eeprom7_default_cfg ( eeprom7_t *ctx );

/**
 * @brief EEPROM 7 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom7_generic_write ( eeprom7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 7 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom7_generic_read ( eeprom7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 7 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len_in : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len_out : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t eeprom7_generic_write_then_read ( eeprom7_t *ctx, uint8_t *data_in, uint8_t len_in, uint8_t *data_out, uint8_t len_out );

/**
 * @brief Enable write protect function.
 * @details The function enable write protect,
 * the EEPROM protection is determined by the contents of the Memory
 * Partition Registers (MPR) by sets the states of the HLD ( PWM ) pin
 * depending on the function argument.
 * @param[out] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] en_write_protect : Write protection enable/disable.
 * @return Nothing.
 */
void eeprom7_enable_write_protect ( eeprom7_t *ctx, uint8_t en_write_protect );

/**
 * @brief Enable hold operation function.
 * @details The function enable hold operation
 * by sets the states of the HLD ( PWM ) pin
 * depending on the function argument.
 * @param[out] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] en_hold : Enable/disable hold.
 * @return Nothing.
 */
void eeprom7_enable_hold_operation ( eeprom7_t *ctx, uint8_t en_hold );

/**
 * @brief Enable write function.
 * @details The function enable write depending on the function argument
 * of the 25CSM04 4-Mbit SPI Serial EEPROM with 128-Bit Serial Number
 * and Enhanced Write Protection on EEPROM 7 click board.
 * @param[out] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] en_write : Write enable/disable
 * @return Nothing.
 */
void eeprom7_enable_write ( eeprom7_t *ctx, uint8_t en_write );

/**
 * @brief Read status function.
 * @details The function read 16-bit status register
 * of the 25CSM04 4-Mbit SPI Serial EEPROM with 128-Bit Serial Number
 * and Enhanced Write Protection on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @return 16-bit status data.
 */
uint16_t eeprom7_read_status ( eeprom7_t *ctx );

/**
 * @brief Check the device is ready function.
 * @details The function checks the device is ready 
 * by check bit 0 of the status register 
 * of the 25CSM04 4-Mbit SPI Serial EEPROM 
 * with 128-Bit Serial Number and Enhanced Write Protection 
 * on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @return EEPROM 7 status.
 */
uint8_t eeprom7_is_device_ready ( eeprom7_t *ctx );

/**
 * @brief Send command function.
 * @details The function sends the desired command
 * to the 25CSM04 4-Mbit SPI Serial EEPROM
 * with 128-Bit Serial Number and Enhanced Write Protection
 * on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] cmd : 8-bit Commands Opcode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t eeprom7_send_cmd ( eeprom7_t *ctx, uint8_t cmd );

/**
 * @brief Software device reset function.
 * @details The function software reset,
 * reset the 25CSM04 4-Mbit SPI Serial EEPROM
 * with 128-Bit Serial Number and Enhanced Write Protection
 * on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @return Nothing.
 */
void eeprom7_sw_reset ( eeprom7_t *ctx );

/**
 * @brief Set status function.
 * @details The function set status register
 * of the 25CSM04 4-Mbit SPI Serial EEPROM
 * with 128-Bit Serial Number and Enhanced Write Protection
 * on EEPROM 7 click board.
 * @param[out] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] status : 8-bit status data.
 * @return Nothing.
 */
void eeprom7_set_status ( eeprom7_t *ctx, uint8_t status );

/**
 * @brief Get status function.
 * @details The function get status register
 * of the 25CSM04 4-Mbit SPI Serial EEPROM
 * with 128-Bit Serial Number and Enhanced Write Protection
 * on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @return 8-bit status data.
 */
uint8_t eeprom7_get_status ( eeprom7_t *ctx );

/**
 * @brief Write EEPROM memory function.
 * @details The function writes a sequential data starting
 * of the targeted register address of the 25CSM04 4-Mbit SPI Serial EEPROM
 * with 128-Bit Serial Number and Enhanced Write Protection
 * on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] addr : 24-bit memory address.
 * @param[in] p_tx_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return Nothing.
 */
void eeprom7_write_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Read EEPROM memory function.
 * @details The function read a sequential data starting
 * from the targeted register address of t25CSM04 4-Mbit SPI Serial EEPROM
 * with 128-Bit Serial Number and Enhanced Write Protection
 * on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] addr : 24-bit memory address.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : Number of bytes to be read.
 * @return Nothing.
 */
void eeprom7_read_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_rx_data, uint8_t n_bytes);
/**
 * @brief Status register bits check function.
 * @details The function checks value of status register bit determined 
 * by check_bit parametar from the targeted register address
 * of t25CSM04 4-Mbit SPI Serial EEPROM
 * with 128-Bit Serial Number and Enhanced Write Protection
 * on EEPROM 7 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom7_t object definition for detailed explanation.
 * @param[in] check_bit : Determined witch bit in status register be checked
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t eeprom7_check_status ( eeprom7_t *ctx, uint8_t check_bit );

#ifdef __cplusplus
}
#endif
#endif // EEPROM7_H

/*! @} */ // eeprom7

// ------------------------------------------------------------------------ END

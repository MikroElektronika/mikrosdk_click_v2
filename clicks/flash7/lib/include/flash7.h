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
 * @file flash7.h
 * @brief This file contains API for Flash 7 Click Driver.
 */

#ifndef FLASH7_H
#define FLASH7_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup flash7 Flash 7 Click Driver
 * @brief API for configuring and manipulating Flash 7 Click driver.
 * @{
 */

/**
 * @defgroup flash7_reg Flash 7 Registers List
 * @brief List of registers of Flash 7 Click driver.
 */

/**
 * @addtogroup flash7_reg
 * @{
 */

/**
 * @brief Flash 7 description register.
 * @details Specified register for description of Flash 7 Click driver.
 */

/**
 * @brief Flash 7 LSB status registers.
 * @details Definition of LSB status registers of Flash 7 Cluck driver.
 */
#define FLASH7_STAT_REG_LSB_SRP0                                  0x80
#define FLASH7_STAT_REG_LSB_BP4                                   0x40
#define FLASH7_STAT_REG_LSB_BP3                                   0x20
#define FLASH7_STAT_REG_LSB_BP2                                   0x10
#define FLASH7_STAT_REG_LSB_BP1                                   0x08
#define FLASH7_STAT_REG_LSB_BP0                                   0x04
#define FLASH7_STAT_REG_LSB_WEL                                   0x02
#define FLASH7_STAT_REG_LSB_WIP                                   0x01

/**
 * @brief Flash 7 MSB status registers.
 * @details Definition of MSB status registers of Flash 7 Cluck driver.
 */
#define FLASH7_STAT_REG_MSB_SUS1                                  0x80
#define FLASH7_STAT_REG_MSB_CMP                                   0x40
#define FLASH7_STAT_REG_MSB_LB3                                   0x20
#define FLASH7_STAT_REG_MSB_LB2                                   0x10
#define FLASH7_STAT_REG_MSB_LB1                                   0x08
#define FLASH7_STAT_REG_MSB_SUS2                                  0x04
#define FLASH7_STAT_REG_MSB_QE                                    0x02
#define FLASH7_STAT_REG_MSB_SRP1                                  0x01

/**
 * @brief Flash 7 Memory address boundary.
 * @details Definition of memory address boundaries of Flash 7 Cluck driver.
 */
#define FLASH7_MEMORY_ADDR_START                            0x00000000
#define FLASH7_MEMORY_ADDR_END                              0x00FFFFFF
#define FLASH7_MEM_SECTOR_LEN                               0x00001000
#define FLASH7_MEMORY_BLOCK_SIZE                            0x00008000

/*! @} */ // flash7_reg

/**
 * @defgroup flash7_set Flash 7 Registers Settings
 * @brief Settings for registers of Flash 7 Click driver.
 */

/**
 * @addtogroup flash7_set
 * @{
 */

/**
 * @brief Flash 7 description setting.
 * @details Specified setting for description of Flash 7 Click driver.
 */

/**
 * @brief Flash 7 commands.
 * @details Definition of commands of Flash 7 Cluck driver.
 */
#define FLASH7_CMD_WRSR                                           0x01
#define FLASH7_CMD_WRITE                                          0x02
#define FLASH7_CMD_READ                                           0x03
#define FLASH7_CMD_WRDI                                           0x04
#define FLASH7_CMD_RDSR_LSB                                       0x05
#define FLASH7_CMD_RDSR_MSB                                       0x35
#define FLASH7_CMD_WREN                                           0x06
#define FLASH7_CMD_FREAD                                          0x0B
#define FLASH7_CMD_WEVSR                                          0x50
#define FLASH7_CMD_SE                                             0x20
#define FLASH7_CMD_BE_32KB                                        0x52
#define FLASH7_CMD_BE_64KB                                        0xD8
#define FLASH7_CMD_CE                                             0x60
#define FLASH7_CMD_SLEEP                                          0xB9
#define FLASH7_CMD_WAKE                                           0xAB
#define FLASH7_CMD_REMS                                           0x90
#define FLASH7_CMD_RDID                                           0x9F
#define FLASH7_CMD_ID                                             0x4B
#define FLASH7_CMD_ENRES                                          0x66
#define FLASH7_CMD_RES                                            0x99

/**
 * @brief Flash 7 write protect.
 * @details Definition of write protection of Flash 7 Cluck driver.
 */
#define FLASH7_WRITE_PROTECT_DISABLE                              0x00
#define FLASH7_WRITE_PROTECT_ENABLE                               0x01

/**
 * @brief Flash 7 hold.
 * @details Definition of hold of Flash 7 Cluck driver.
 */
#define FLASH7_HOLD_DISABLE                                       0x00
#define FLASH7_HOLD_ENABLE                                        0x01

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define FLASH7_DUMMY                                              0x00

/*! @} */ // flash7_set

/**
 * @defgroup flash7_map Flash 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 7 Click driver.
 */

/**
 * @addtogroup flash7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 7 Click to the selected MikroBUS.
 */
#define FLASH7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.io2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.io3 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // flash7_map
/*! @} */ // flash7

/**
 * @brief Flash 7 Click context object.
 * @details Context object definition of Flash 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  io2;     /**< Write Protect. */
    digital_out_t  io3;     /**< HOLD. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} flash7_t;

/**
 * @brief Flash 7 Click configuration object.
 * @details Configuration object definition of Flash 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  io2;        /**< Write Protect. */
    pin_name_t  io3;        /**< HOLD. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} flash7_cfg_t;

/**
 * @brief Flash 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   FLASH7_OK = 0,
   FLASH7_ERROR = -1

} flash7_return_value_t;

/*!
 * @addtogroup flash7 Flash 7 Click Driver
 * @brief API for configuring and manipulating Flash 7 Click driver.
 * @{
 */

/**
 * @brief Flash 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash7_cfg_setup ( flash7_cfg_t *cfg );

/**
 * @brief Flash 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #flash7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash7_init ( flash7_t *ctx, flash7_cfg_t *cfg );

/**
 * @brief Flash 7 default configuration function.
 * @details This function executes a default configuration of Flash 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #flash7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t flash7_default_cfg ( flash7_t *ctx );

/**
 * @brief Flash 7 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash7_generic_write ( flash7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 7 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t flash7_generic_read ( flash7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Enable write protect function.
 * @details The function enables write protect,
 * by sets the states of the IO2 ( PWM ) pin
 * depending on the function argument.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] en_write_protect : Write protection on or off.
 * @return Nothing.
 * 
*/
void flash7_write_protect ( flash7_t *ctx, uint8_t en_write_protect );

/**
 * @brief Enable hold operation function.
 * @details The function enable hold operation
 * by sets the states of the IO3 ( INT ) pin
 * depending on the function argument.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] en_hold : Resume or pause any serial communications with the device.
 * @return Nothing.
 */
void flash7_hold ( flash7_t *ctx, uint8_t en_hold );

/**
 * @brief Send command function.
 * @details The function sends the desired command
 * to the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] cmd : 8-bit commands instruction.
 * @return Nothing.
 */
void flash7_send_command ( flash7_t *ctx, uint8_t cmd );

/**
 * @brief Write enable function.
 * @details The function sends enable write command
 * to the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void flash7_write_enable ( flash7_t *ctx );

/**
 * @brief Write disable function.
 * @details The function sends disable write command
 * to the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void flash7_write_disable ( flash7_t *ctx );

/**
 * @brief Chip erase function.
 * @details The function sends chip erase command
 * to the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void flash7_chip_erase ( flash7_t *ctx );

/**
 * @brief Read status register function.
 * @details The function reads status byte
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] status_byte : Read LSB or MSB status register.
 * @return 8-bit status.
 */
uint8_t flash7_read_status_register ( flash7_t *ctx, uint8_t status_byte );

/**
 * @brief Write status register function.
 * @details The function writes status data
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] status_data : 16-bit write status data.
 * @return Nothing.
 */
void flash7_write_status_register ( flash7_t *ctx, uint16_t status_data );

/**
 * @brief Page program function.
 * @details The function writes a sequential data starting
 * from the targeted 24-bit register address
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] mem_addr : 24-bit start memory address.
 * @param[out] p_tx_data : Pointer to the data to be written.
 * @param[in] n_bytes : 16-bit number of bytes to be written.
 * @return 8-bit status.
 */
uint8_t flash7_page_program ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_tx_data, uint16_t n_bytes );

/**
 * @brief Read memory function.
 * @details The function reads a sequential data starting
 * from the targeted 24-bit register address
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] mem_addr : 24-bit start memory address.
 * @param[out] p_rx_data : Pointer to the memory location where data is stored.
 * @param[in] n_bytes : 16-bit number of bytes to be read.
 * @return Nothing.
 */
void flash7_read_memory ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint16_t n_bytes );

/**
 * @brief Fast read memory function.
 * @details The function reads a sequential data starting
 * from the targeted 24-bit register address
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] mem_addr : 24-bit start memory address.
 * @param[out] p_rx_data : Pointer to the memory location where data is stored.
 * @param[in] n_bytes : 16-bit number of bytes to be read.
 * @return Nothing.
 */
void flash7_fast_read_memory ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint16_t n_bytes );

/**
 * @brief Sector erase function.
 * @details This function performs
 * erase of all data in the chosen sector
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param mem_sector
 * number of sector in memory ( from 1 to 512 )
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
uint8_t flash7_sector_erase ( flash7_t *ctx, uint16_t mem_sector );

/**
 * @brief Block erase function.
 * @details This function performs erase of all data
 * with the range depending on block length in the chosen block
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[in] mem_block : Number of block in memory for complete erase
 * ( from 1 to 32 or 64 , depending on mem_block_len ).
 * @param mem_block_len : Sets the block erase length ( 32kb or 64kb ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
uint8_t flash7_block_erase ( flash7_t *ctx, uint8_t mem_block, uint8_t mem_block_len );

/**
 * @brief Go to sleep mode function.
 * @details The function go to sleep
 * is the only way to put the device in the lowest consumption mode,
 * executing the Deep Power-Down
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void flash7_go_to_sleep ( flash7_t *ctx );

/**
 * @brief Wake up function.
 * @details The function performs wake up,
 * release from power-down and read device ID
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return 8-bit device ID.
 */
uint8_t flash7_wake_up ( flash7_t *ctx );

/**
 * @brief Read ID function.
 * @details The function acquries manufacturer and device ID
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[out] manufacturer_id : Pointer to the memory location where the manufacturer ID is stored.
 * @param[out] device_id : Pointer to the memory location where device ID is stored.
 * @return Nothing.
 */
void flash7_read_id ( flash7_t *ctx, uint8_t *manufacturer_id, uint8_t *device_id );

/**
 * @brief Get identification function.
 * @details The function acquries identification data
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @param[out] manufacturer_id : Pointer to the memory location where the manufacturer ID is stored.
 * @param[out] memory_type_id : Pointer to the memory location where the memory type ID is stored.
 * @param[out] capacity_id : Pointer to the memory location where device ID is stored.
 * @return Nothing.
 */
void flash7_get_identification ( flash7_t *ctx, uint8_t *manufacturer_id, uint8_t *memory_type_id, uint8_t *capacity_id );

/**
 * @brief Soft reset function.
 * @details The function performs a software reset
 * of the GD25LQ16C 1.8V Uniform Sector Dual and Quad Serial Flash
 * on Flash 7 click board.
 * @param[in] ctx : Click context object.
 * See #flash7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void flash7_sw_reset ( flash7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // FLASH7_H

/*! @} */ // flash7

// ------------------------------------------------------------------------ END

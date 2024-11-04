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
 * @file mram4.h
 * @brief This file contains API for MRAM 4 Click Driver.
 */

#ifndef MRAM4_H
#define MRAM4_H

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
 * @addtogroup mram4 MRAM 4 Click Driver
 * @brief API for configuring and manipulating MRAM 4 Click driver.
 * @{
 */

/**
 * @defgroup mram4_cmd MRAM 4 instruction command set
 * @brief Instruction command set of MRAM 4 Click driver.
 */

/**
 * @addtogroup mram4_cmd
 * @{
 */

/**
 * @brief MRAM 4 description register.
 * @details Specified register for description of MRAM 4 Click driver.
 */
#define MRAM4_CMD_RESET_ENABLE                        0x66
#define MRAM4_CMD_RESET_MEMORY                        0x99
#define MRAM4_CMD_READ_ID                             0x9E
#define MRAM4_CMD_READ_ID_MIO                         0xAF
#define MRAM4_CMD_READ                                0x03
#define MRAM4_CMD_READ_FAST_XIP                       0x0B
#define MRAM4_CMD_READ_FAST_DUAL_OUTPUT               0x3B
#define MRAM4_CMD_READ_FAST_DUAL_IO                   0xBB
#define MRAM4_CMD_READ_FAST_QUAD_OUTPUT               0x6B
#define MRAM4_CMD_READ_FAST_QUAD_IO                   0xEB
#define MRAM4_CMD_READ_FAST_DTR                       0x0D
#define MRAM4_CMD_READ_FAST_DUAL_OUTPUT_DTR           0x3D
#define MRAM4_CMD_READ_FAST_DUAL_IO_DTR               0xBD
#define MRAM4_CMD_READ_FAST_QUAD_OUTPUT_DTR           0x6D
#define MRAM4_CMD_READ_FAST_QUAD_IO_DTR               0xED
#define MRAM4_CMD_READ_WORD_QUAD_IO                   0xE7
#define MRAM4_CMD_READ_FAST_OCTAL_OUTPUT              0x8B
#define MRAM4_CMD_READ_FAST_OCTAL_IO                  0xCB
#define MRAM4_CMD_READ_FAST_OCTAL_OUTPUT_DTR          0x9D
#define MRAM4_CMD_READ_FAST_OCTAL_IO_DTR              0xFD
#define MRAM4_CMD_READ_4BYTE_ADDR                     0x13 
#define MRAM4_CMD_READ_FAST_4BYTE_ADDR                0x0C
#define MRAM4_CMD_READ_FAST_DUAL_OUTPUT_4BYTE_ADDR    0x3C
#define MRAM4_CMD_READ_FAST_DUAL_IO_4BYTE_ADDR        0xBC
#define MRAM4_CMD_READ_FAST_QUAD_OUTPUT_4BYTE_ADDR    0x6C
#define MRAM4_CMD_READ_FAST_QUAD_IO_4BYTE_ADDR        0xEC
#define MRAM4_CMD_READ_FAST_DTR_4BYTE_ADDR            0x0E
#define MRAM4_CMD_READ_FAST_DUAL_IO_DTR_4BYTE_ADDR    0xBE
#define MRAM4_CMD_READ_FAST_QUAD_IO_DTR_4BYTE_ADDR    0xEE
#define MRAM4_CMD_READ_FAST_OCTAL_OUTPUT_4BYTE_ADDR   0x7C
#define MRAM4_CMD_READ_FAST_OCTAL_IO_4BYTE_ADDR       0xCC
#define MRAM4_CMD_WRITE_ENABLE                        0x06
#define MRAM4_CMD_WRITE_DISABLE                       0x04
#define MRAM4_CMD_READ_STATUS_REG                     0x05
#define MRAM4_CMD_READ_FLAG_STATUS_REG                0x70
#define MRAM4_CMD_READ_NVOL_CFG_REG                   0xB5
#define MRAM4_CMD_READ_VOL_CFG_REG                    0x85
#define MRAM4_CMD_READ_GENERAL_PURPOSE_READ_REG       0x96
#define MRAM4_CMD_WRITE_STATUS_REG                    0x01
#define MRAM4_CMD_WRITE_NVOL_CFG_REG                  0xB1
#define MRAM4_CMD_WRITE_VOL_CFG_REG                   0x81
#define MRAM4_CMD_CLEAR_FLAG_STATUS_REG               0x50
#define MRAM4_CMD_WRITE_PR_PAGE                       0x02
#define MRAM4_CMD_WRITE_PR_FAST_DUAL_INPUT            0xA2
#define MRAM4_CMD_WRITE_PR_FAST_DUAL_INPUT_EXT        0xD2
#define MRAM4_CMD_WRITE_PR_FAST_QUAD_INPUT            0x32
#define MRAM4_CMD_WRITE_PR_FAST_QUAD_INPUT_EXT        0x38
#define MRAM4_CMD_WRITE_PR_FAST_OCTAL_INPUT           0x82
#define MRAM4_CMD_WRITE_PR_FAST_OCTAL_INPUT_EXT       0xC2
#define MRAM4_CMD_WRITE_PR_4BYTE_ADDRESS              0x12
#define MRAM4_CMD_WRITE_PR_FAST_QUAD_INPUT_4BYTE      0x34
#define MRAM4_CMD_WRITE_PR_FAST_QUAD_INPUT_EXT_4BYTE  0x3E
#define MRAM4_CMD_WRITE_PR_FAST_OCTAL_INPUT_4BYTE     0x84
#define MRAM4_CMD_WRITE_FAST_OCTAL_INPUT_EXT_4BYTE    0x8E
#define MRAM4_CMD_ERASE_32KB                          0x52
#define MRAM4_CMD_ERASE_4KB                           0x20
#define MRAM4_CMD_ERASE_SECTOR                        0xD8
#define MRAM4_CMD_ERASE_BULK_CHIP                     0xC7
#define MRAM4_CMD_ERASE_CHIP                          0x60
#define MRAM4_CMD_ERASE_SECTOR_4BYTE_ADDRESS          0xDC
#define MRAM4_CMD_ERASE_4KB_4_BYTE_ADDRESS            0x21
#define MRAM4_CMD_ERASE_32KB_4BYTE_ADDRESS            0x5C 
#define MRAM4_CMD_OTP_READ                            0x4B
#define MRAM4_CMD_OTP_WRITE                           0x42
#define MRAM4_CMD_4BYTE_ADDRESS_MODE_ENTER            0xB7
#define MRAM4_CMD_4BYTE_ADDRESS_MODE_EXIT             0xE9
#define MRAM4_CMD_DEEP_POWER_DOWN_ENTER               0xB9
#define MRAM4_CMD_DEEP_POWER_DOWN_EXIT                0xAB
#define MRAM4_CMD_INTERFACE_ACTIVATION_CRC            0x9B
#define MRAM4_CMD_TDP_WRITE                           0xF0
#define MRAM4_CMD_TDP_READ                            0xF1
#define MRAM4_CMD_TDP_READ_DTR                        0xF2

/*! @} */ // mram4_cmd

/**
 * @defgroup mram4_set MRAM 4 Registers Settings
 * @brief Settings for registers of MRAM 4 Click driver.
 */

/**
 * @addtogroup mram4_set
 * @{
 */

/**
 * @brief MRAM 4 description of the persistent memory and page size values.
 * @details Specified persistent memory and page size values of MRAM 4 Click driver.
 */
#define MRAM4_MEMORY_ADDRESS_MIN                      0x000000ul
#define MRAM4_MEMORY_ADDRESS_MAX                      0x3FFFFFul
#define MRAM4_PAGE_SIZE                               256

/**
 * @brief MRAM 4 description of the write-protection and hold pin logic state.
 * @details Specified write-protection and hold pin logic state of MRAM 4 Click driver.
 */
#define MRAM4_WRITE_PROTECT_ENABLE                    0
#define MRAM4_WRITE_PROTECT_DISABLE                   1
#define MRAM4_HOLD_ENABLE                             0
#define MRAM4_HOLD_DISABLE                            1

/**
 * @brief MRAM 4 description of status register bit assignments.
 * @details Specified status register bit assignments of MRAM 4 Click driver.
 */
#define MRAM4_STATUS_WP_BIT_MASK                      0x80
#define MRAM4_STATUS_BP3_BIT_MASK                     0x40
#define MRAM4_STATUS_TOP_BOTTOM_BIT_MASK              0x20
#define MRAM4_STATUS_BP2_BIT_MASK                     0x10
#define MRAM4_STATUS_BP1_BIT_MASK                     0x08
#define MRAM4_STATUS_BP0_BIT_MASK                     0x04
#define MRAM4_STATUS_WEL_BIT_MASK                     0x02
#define MRAM4_STATUS_WIP_BIT_MASK                     0x01
#define MRAM4_STATUS_WEL_SET                          0x02
#define MRAM4_STATUS_WEL_CLR                          0x00

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b mram4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MRAM4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define MRAM4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // mram4_set

/**
 * @defgroup mram4_map MRAM 4 MikroBUS Map
 * @brief MikroBUS pin mapping of MRAM 4 Click driver.
 */

/**
 * @addtogroup mram4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MRAM 4 Click to the selected MikroBUS.
 */
#define MRAM4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // mram4_map
/*! @} */ // mram4

/**
 * @brief MRAM 4 Click context object.
 * @details Context object definition of MRAM 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;     /**< Write-protection pin. */
    digital_out_t hld;    /**< Hold pin. */
    
    // Modules
    spi_master_t spi;     /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} mram4_t;

/**
 * @brief MRAM 4 Click configuration object.
 * @details Configuration object definition of MRAM 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wp;      /**< Write-protection pin. */
    pin_name_t hld;     /**< Hold pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} mram4_cfg_t;

/**
 * @brief MRAM 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MRAM4_OK = 0,
    MRAM4_ERROR = -1

} mram4_return_value_t;

/*!
 * @addtogroup mram4 MRAM 4 Click Driver
 * @brief API for configuring and manipulating MRAM 4 Click driver.
 * @{
 */

/**
 * @brief MRAM 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mram4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mram4_cfg_setup ( mram4_cfg_t *cfg );

/**
 * @brief MRAM 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mram4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_init ( mram4_t *ctx, mram4_cfg_t *cfg );

/**
 * @brief MRAM 4 default configuration function.
 * @details This function executes a default configuration of MRAM 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mram4_default_cfg ( mram4_t *ctx );

/**
 * @brief MRAM 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_generic_write ( mram4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief MRAM 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_generic_read ( mram4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief MRAM 4 write command adress data function.
 * @details This function writes a desired number of data bytes 
 * starting from a desired address of the selected command
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command.
 * @param[in] addr : Memory address (0x000000-0x3FFFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_write_cmd_addr_data ( mram4_t *ctx, uint8_t cmd, uint32_t addr, uint8_t *data_in, uint32_t len );

/**
 * @brief MRAM 4 read command adress data function.
 * @details This function reads a desired number of data bytes 
 * starting from a desired address of the selected command
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command.
 * @param[in] addr : Memory address (0x000000-0x3FFFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_read_cmd_addr_data ( mram4_t *ctx, uint8_t cmd, uint32_t addr, uint8_t *data_out, uint32_t len );

/**
 * @brief MRAM 4 memory write function.
 * @details This function writes a desired number of data bytes 
 * starting from the selected memory address
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] mem_addr : Memory address (0x000000-0x3FFFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_memory_write ( mram4_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief MRAM 4 memory read function.
 * @details This function reads a desired number of data bytes 
 * starting from the selected memory address
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] mem_addr : Memory address (0x000000-0x3FFFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_memory_read ( mram4_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief MRAM 4 memory reset function.
 * @details This function performs the software reset of the memory
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_memory_reset ( mram4_t *ctx );

/**
 * @brief MRAM 4 set the command function.
 * @details This function writes the desired instruction command
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_set_command ( mram4_t *ctx, uint8_t cmd );

/**
 * @brief MRAM 4 write enable function.
 * @details This function disable hardware write protection of the entire memory 
 * and sets the write enable command
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_write_enable ( mram4_t *ctx );

/**
 * @brief MRAM 4 write disable function.
 * @details This function enable hardware write protection of the entire memory 
 * and sets the write disable command
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_write_disable ( mram4_t *ctx );

/**
 * @brief MRAM 4 block erase function.
 * @details This function erases the desired amount of memory starting from the selected memory address
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] cmd_block_erase : Block erase command 
 * [MRAM4_CMD_ERASE_4KB, MRAM4_CMD_ERASE_32KB, MRAM4_CMD_ERASE_SECTOR].
 * @param[in] mem_addr : Memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_block_erase ( mram4_t *ctx, uint8_t cmd_block_erase, uint32_t mem_addr );

/**
 * @brief MRAM 4 chip erase function.
 * @details This function erases the entire memory array
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_chip_erase ( mram4_t *ctx );

/**
 * @brief MRAM 4 set status function.
 * @details This function writes data byte to the desired status register
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] st_reg : Write status register command.
 * @param[in] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_set_status ( mram4_t *ctx, uint8_t st_reg, uint8_t status );

/**
 * @brief MRAM 4 get the status function.
 * @details This function reads status data from the desired status register
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram4_get_status ( mram4_t *ctx, uint8_t *status );

/**
 * @brief MRAM 4 hardware write protect function.
 * @details This function is used for write-protection
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] en_wp Write-protection [MRAM4_WRITE_PROTECT_ENABLE, MRAM4_WRITE_PROTECT_DISABLE].
 * @return Nothing.
 * @note None.
 */
void mram4_hw_write_protect ( mram4_t *ctx, uint8_t en_wp );

/**
 * @brief MRAM 4 set hold function.
 * @details This function is used for pausing SPI communication
 * of the EM064LXQADG13IS1R, Industrial STT-MRAM Persistent Memory
 * on the MRAM 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #mram4_t object definition for detailed explanation.
 * @param[in] en_hld Write-protection [MRAM4_HOLD_ENABLE, MRAM4_HOLD_DISABLE].
 * @return Nothing.
 * @note None.
 */
void mram4_set_hold ( mram4_t *ctx, uint8_t en_hld );

#ifdef __cplusplus
}
#endif
#endif // MRAM4_H

/*! @} */ // mram4

// ------------------------------------------------------------------------ END

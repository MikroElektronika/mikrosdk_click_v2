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
 * @file mram3.h
 * @brief This file contains API for MRAM 3 Click Driver.
 */

#ifndef MRAM3_H
#define MRAM3_H

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
 * @addtogroup mram3 MRAM 3 Click Driver
 * @brief API for configuring and manipulating MRAM 3 Click driver.
 * @{
 */

/**
 * @defgroup mram3_reg MRAM 3 Registers List
 * @brief List of registers of MRAM 3 Click driver.
 */

/**
 * @addtogroup mram3_reg
 * @{
 */

/**
 * @brief MRAM 3 control instruction set.
 * @details Specified control instruction set of MRAM 3 Click driver.
 */
#define MRAM3_CMD_NOP                       0x00
#define MRAM3_CMD_WRITE_ENABLE              0x06
#define MRAM3_CMD_WRITE_DISABLE             0x04
#define MRAM3_CMD_ENABLE_DPI                0x37
#define MRAM3_CMD_ENABLE_QPI                0x38
#define MRAM3_CMD_ENABLE_SPI                0xFF
#define MRAM3_CMD_ENTER_DEEP_POWER_DOWN     0xB9
#define MRAM3_CMD_ENTER_HIBERNATE           0xBA
#define MRAM3_CMD_SOFT_RESET_ENABLE         0x66
#define MRAM3_CMD_SOFT_RESET                0x99
#define MRAM3_CMD_EXIT_DEEP_POWER_DOWN      0xAB

/**
 * @brief MRAM 3 read register instruction set.
 * @details Specified read register instruction set of MRAM 3 Click driver.
 */
#define MRAM3_CMD_READ_STATUS               0x05
#define MRAM3_CMD_READ_CONFIG_1             0x35
#define MRAM3_CMD_READ_CONFIG_2             0x3F
#define MRAM3_CMD_READ_CONFIG_3             0x44
#define MRAM3_CMD_READ_CONFIG_4             0x45
#define MRAM3_CMD_READ_CONFIG_ALL           0x46
#define MRAM3_CMD_READ_DEVICE_ID            0x9F
#define MRAM3_CMD_READ_UNIQUE_ID            0x4C
#define MRAM3_CMD_READ_SERIAL_NUMBER        0xC3
#define MRAM3_CMD_READ_AUG_ARRAY_PROTECT    0x14
#define MRAM3_CMD_READ_ADDRESS_BASED        0x65

/**
 * @brief MRAM 3 write register instruction set.
 * @details Specified write register instruction set of MRAM 3 Click driver.
 */
#define MRAM3_CMD_WRITE_STATUS              0x01
#define MRAM3_CMD_WRITE_CONFIG_ALL          0x87
#define MRAM3_CMD_WRITE_SERIAL_NUMBER       0xC2
#define MRAM3_CMD_WRITE_AUG_ARRAY_PROTECT   0x1A
#define MRAM3_CMD_WRITE_ADDRESS_BASED       0x71

/**
 * @brief MRAM 3 read memory array instruction set.
 * @details Specified read memory array instruction set of MRAM 3 Click driver.
 */
#define MRAM3_CMD_READ_MEMORY_SDR           0x03
#define MRAM3_CMD_FAST_READ_MEMORY_SDR      0x0B
#define MRAM3_CMD_FAST_READ_MEMORY_DDR      0x0D
#define MRAM3_CMD_READ_DUAL_OUT_MEMORY_SDR  0x3B
#define MRAM3_CMD_READ_QUAD_OUT_MEMORY_SDR  0x6B
#define MRAM3_CMD_READ_DUAL_IO_MEMORY_SDR   0xBB
#define MRAM3_CMD_READ_DUAL_IO_MEMORY_DDR   0xBD
#define MRAM3_CMD_READ_QUAD_IO_MEMORY_SDR   0xEB
#define MRAM3_CMD_READ_QUAD_IO_MEMORY_DDR   0xED

/**
 * @brief MRAM 3 write memory array instruction set.
 * @details Specified write memory array instruction set of MRAM 3 Click driver.
 */
#define MRAM3_CMD_WRITE_MEMORY_SDR          0x02
#define MRAM3_CMD_FAST_WRITE_MEMORY_SDR     0xDA
#define MRAM3_CMD_FAST_WRITE_MEMORY_DDR     0xDE
#define MRAM3_CMD_WRITE_DUAL_IN_MEMORY_SDR  0xA2
#define MRAM3_CMD_WRITE_QUAD_IN_MEMORY_SDR  0x32
#define MRAM3_CMD_WRITE_QUAD_IN_MEMORY_DDR  0x31
#define MRAM3_CMD_WRITE_DUAL_IO_MEMORY_SDR  0xA1
#define MRAM3_CMD_WRITE_QUAD_IO_MEMORY_SDR  0xD2
#define MRAM3_CMD_WRITE_QUAD_IO_MEMORY_DDR  0xD1

/**
 * @brief MRAM 3 augmented storage array instruction set.
 * @details Specified augmented storage array instruction set of MRAM 3 Click driver.
 */
#define MRAM3_CMD_READ_AUG_STORAGE_SDR      0x4B
#define MRAM3_CMD_WRITE_AUG_STORAGE_SDR     0x42

/*! @} */ // mram3_reg

/**
 * @defgroup mram3_set MRAM 3 Registers Settings
 * @brief Settings for registers of MRAM 3 Click driver.
 */

/**
 * @addtogroup mram3_set
 * @{
 */

/**
 * @brief MRAM 3 status register settings.
 * @details Specified status register settings of MRAM 3 Click driver.
 */
#define MRAM3_STATUS_WPEN                   0x80
#define MRAM3_STATUS_SNPEN                  0x40
#define MRAM3_STATUS_TBSEL_BOTTOM           0x20
#define MRAM3_STATUS_TBSEL_TOP              0x00
#define MRAM3_STATUS_BPSEL_NONE             0x00
#define MRAM3_STATUS_BPSEL_UPPER_1_64       0x04
#define MRAM3_STATUS_BPSEL_UPPER_1_32       0x08
#define MRAM3_STATUS_BPSEL_UPPER_1_16       0x0C
#define MRAM3_STATUS_BPSEL_UPPER_1_8        0x10
#define MRAM3_STATUS_BPSEL_UPPER_QUARTER    0x14
#define MRAM3_STATUS_BPSEL_UPPER_HALF       0x18
#define MRAM3_STATUS_BPSEL_ALL              0x1C
#define MRAM3_STATUS_WREN                   0x02

/**
 * @brief MRAM 3 config registers settings.
 * @details Specified config registers settings of MRAM 3 Click driver.
 */
#define MRAM3_CONFIG1_MAPLK_LOCK            0x04
#define MRAM3_CONFIG1_MAPLK_UNLOCK          0x00
#define MRAM3_CONFIG1_ASPLK_LOCK            0x01
#define MRAM3_CONFIG1_ASPLK_UNLOCK          0x00
#define MRAM3_CONFIG2_QUAD_SPI              0x40
#define MRAM3_CONFIG2_DUAL_SPI              0x10
#define MRAM3_CONFIG2_MLATS_0_CYCLES        0x00
#define MRAM3_CONFIG2_MLATS_1_CYCLE         0x01
#define MRAM3_CONFIG2_MLATS_2_CYCLES        0x02
#define MRAM3_CONFIG2_MLATS_3_CYCLES        0x03
#define MRAM3_CONFIG2_MLATS_4_CYCLES        0x04
#define MRAM3_CONFIG2_MLATS_5_CYCLES        0x05
#define MRAM3_CONFIG2_MLATS_6_CYCLES        0x06
#define MRAM3_CONFIG2_MLATS_7_CYCLES        0x07
#define MRAM3_CONFIG2_MLATS_8_CYCLES        0x08
#define MRAM3_CONFIG2_MLATS_9_CYCLES        0x09
#define MRAM3_CONFIG2_MLATS_10_CYCLES       0x0A
#define MRAM3_CONFIG2_MLATS_11_CYCLES       0x0B
#define MRAM3_CONFIG2_MLATS_12_CYCLES       0x0C
#define MRAM3_CONFIG2_MLATS_13_CYCLES       0x0D
#define MRAM3_CONFIG2_MLATS_14_CYCLES       0x0E
#define MRAM3_CONFIG2_MLATS_15_CYCLES       0x0F
#define MRAM3_CONFIG3_ODSEL_35OHM           0x00
#define MRAM3_CONFIG3_ODSEL_75OHM           0x20
#define MRAM3_CONFIG3_ODSEL_60OHM           0x40
#define MRAM3_CONFIG3_ODSEL_45OHM           0x60
#define MRAM3_CONFIG3_ODSEL_40OHM           0xA0
#define MRAM3_CONFIG3_ODSEL_20OHM           0xC0
#define MRAM3_CONFIG3_ODSEL_15OHM           0xE0
#define MRAM3_CONFIG3_WRAPS_ENABLE          0x10
#define MRAM3_CONFIG3_WRPLS_16BYTE          0x00
#define MRAM3_CONFIG3_WRPLS_32BYTE          0x01
#define MRAM3_CONFIG3_WRPLS_64BYTE          0x02
#define MRAM3_CONFIG3_WRPLS_128BYTE         0x03
#define MRAM3_CONFIG3_WRPLS_256BYTE         0x04
#define MRAM3_CONFIG4_WRENS_NORMAL          0x04
#define MRAM3_CONFIG4_WRENS_SRAM            0x05
#define MRAM3_CONFIG4_WRENS_BACK_TO_BACK    0x06

/**
 * @brief MRAM 3 memory address range.
 * @details Specified memory address range of MRAM 3 Click driver.
 */
#define MRAM3_MIN_ADDRESS                   0x000000
#define MRAM3_MAX_ADDRESS                   0x01FFFFul

/**
 * @brief MRAM 3 device ID.
 * @details Specified device ID of MRAM 3 Click driver.
 */
#define MRAM3_DEVICE_ID                     0xE6010102ul

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b mram3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MRAM3_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define MRAM3_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // mram3_set

/**
 * @defgroup mram3_map MRAM 3 MikroBUS Map
 * @brief MikroBUS pin mapping of MRAM 3 Click driver.
 */

/**
 * @addtogroup mram3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MRAM 3 Click to the selected MikroBUS.
 */
#define MRAM3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.io3 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // mram3_map
/*! @} */ // mram3

/**
 * @brief MRAM 3 Click context object.
 * @details Context object definition of MRAM 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t io3;          /**< Bidirectional Data 3 (DPI/QPI) pin - not used, set to LOW. */
    digital_out_t wp;           /**< Write Protect pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} mram3_t;

/**
 * @brief MRAM 3 Click configuration object.
 * @details Configuration object definition of MRAM 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  io3;            /**< Bidirectional Data 3 (DPI/QPI) pin - not used, set to LOW. */
    pin_name_t  wp;             /**< Write Protect pin. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} mram3_cfg_t;

/**
 * @brief MRAM 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MRAM3_OK = 0,
    MRAM3_ERROR = -1

} mram3_return_value_t;

/*!
 * @addtogroup mram3 MRAM 3 Click Driver
 * @brief API for configuring and manipulating MRAM 3 Click driver.
 * @{
 */

/**
 * @brief MRAM 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mram3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mram3_cfg_setup ( mram3_cfg_t *cfg );

/**
 * @brief MRAM 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mram3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_init ( mram3_t *ctx, mram3_cfg_t *cfg );

/**
 * @brief MRAM 3 default configuration function.
 * @details This function executes a default configuration of MRAM 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mram3_default_cfg ( mram3_t *ctx );

/**
 * @brief MRAM 3 write cmd function.
 * @details This function writes a desired instruction command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command opcode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_write_cmd ( mram3_t *ctx, uint8_t cmd );

/**
 * @brief MRAM 3 write cmd data function.
 * @details This function writes a desired number of data bytes to 
 * the selected instruction command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command opcode.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_write_cmd_data ( mram3_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief MRAM 3 read cmd data function.
 * @details This function reads a desired number of data bytes from
 * the selected instruction command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command opcode.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_read_cmd_data ( mram3_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief MRAM 3 write cmd address data function.
 * @details This function writes a desired number of data bytes starting from a desired address of
 * the selected instruction command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command opcode.
 * @param[in] address : Memory address (up to 0x1FFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_write_cmd_address_data ( mram3_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief MRAM 3 read cmd address data function.
 * @details This function reads a desired number of data bytes starting from a desired address of
 * the selected instruction command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] cmd : Instruction command opcode.
 * @param[in] address : Memory address (up to 0x1FFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_read_cmd_address_data ( mram3_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief MRAM 3 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x1FFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_memory_write ( mram3_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief MRAM 3 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x1FFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_memory_read ( mram3_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief MRAM 3 aug memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected augmented memory address.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00-0xFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_aug_memory_write ( mram3_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief MRAM 3 aug memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected augmented memory address.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00-0xFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_aug_memory_read ( mram3_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief MRAM 3 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_check_communication ( mram3_t *ctx );

/**
 * @brief MRAM 3 write protect function.
 * @details This function write protects the entire memory via the WP pin and WRDI command.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
err_t mram3_write_protect ( mram3_t *ctx );

/**
 * @brief MRAM 3 write enable function.
 * @details This function disables memory write-protect via the WP pin and WREN command.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
err_t mram3_write_enable ( mram3_t *ctx );

/**
 * @brief MRAM 3 soft reset function.
 * @details This function executes the soft reset command.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
err_t mram3_soft_reset ( mram3_t *ctx );

/**
 * @brief MRAM 3 write status function.
 * @details This function writes data to the status register.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[in] status : Status data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_write_status ( mram3_t *ctx, uint8_t status );

/**
 * @brief MRAM 3 read status function.
 * @details This function reads data from the status register.
 * @param[in] ctx : Click context object.
 * See #mram3_t object definition for detailed explanation.
 * @param[out] status : Status data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram3_read_status ( mram3_t *ctx, uint8_t *status );

#ifdef __cplusplus
}
#endif
#endif // MRAM3_H

/*! @} */ // mram3

// ------------------------------------------------------------------------ END

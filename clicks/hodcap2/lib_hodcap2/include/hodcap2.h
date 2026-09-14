/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file hodcap2.h
 * @brief This file contains API for HOD CAP 2 Click Driver.
 */

#ifndef HODCAP2_H
#define HODCAP2_H

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
 * @addtogroup hodcap2 HOD CAP 2 Click Driver
 * @brief API for configuring and manipulating HOD CAP 2 Click driver.
 * @{
 */

/**
 * @defgroup hodcap2_reg HOD CAP 2 Registers List
 * @brief List of registers of HOD CAP 2 Click driver.
 */

/**
 * @addtogroup hodcap2_reg
 * @{
 */

/**
 * @brief HOD CAP 2 register map.
 * @details Specified register map of HOD CAP 2 Click driver.
 */
#define HODCAP2_REG_MEMT_DATA_1                     0x00
#define HODCAP2_REG_MEMT_DATA_2                     0x01
#define HODCAP2_REG_MEMT_DATA_3                     0x02
#define HODCAP2_REG_MEMT_DATA_4                     0x03
#define HODCAP2_REG_MEMT_DATA_5                     0x04
#define HODCAP2_REG_MEMT_DATA_6                     0x05
#define HODCAP2_REG_MEMT_DATA_7                     0x06
#define HODCAP2_REG_MEMT_DATA_8                     0x07
#define HODCAP2_REG_MEMT_DATA_9                     0x08
#define HODCAP2_REG_MEMT_DATA_10                    0x09
#define HODCAP2_REG_MEMT_DATA_11                    0x0A
#define HODCAP2_REG_MEMT_DATA_12                    0x0B
#define HODCAP2_REG_MEMT_DATA_13                    0x0C
#define HODCAP2_REG_MEMT_DATA_14                    0x0D
#define HODCAP2_REG_MEMT_DATA_15                    0x0E
#define HODCAP2_REG_MEMT_DATA_16                    0x0F
#define HODCAP2_REG_BANK_SEL                        0x10
#define HODCAP2_REG_B0_MEMT_SEQ                     0x11
#define HODCAP2_REG_B0_MEMT_CTL_1                   0x12
#define HODCAP2_REG_B0_MEMT_CTL_2                   0x13
#define HODCAP2_REG_B0_MEMT_CTL_3                   0x14
#define HODCAP2_REG_B0_POLL_CYC_CNT                 0x15
#define HODCAP2_REG_B0_POLL_CYC_CNT_STS             0x16
#define HODCAP2_REG_B0_RAM_CFG_TBL_CRC              0x17
#define HODCAP2_REG_B0_TBL_CRC_CHK_TSLD             0x18
#define HODCAP2_REG_B0_DIAG_REG_1                   0x19
#define HODCAP2_REG_B0_DIAG_REG_2                   0x1A
#define HODCAP2_REG_B0_DIAG_REG_3                   0x1B
#define HODCAP2_REG_BX_MEMT_CFG1_TBLX               0x11
#define HODCAP2_REG_BX_MEMT_CFG2_TBLX               0x12
#define HODCAP2_REG_BX_MEMT_CFG3_TBLX               0x13
#define HODCAP2_REG_BX_MEMT_CFG4_TBLX               0x14
#define HODCAP2_REG_BX_MEMT_CFG5_TBLX               0x15
#define HODCAP2_REG_BX_MEMT_CFG6_TBLX               0x16
#define HODCAP2_REG_BX_MEMT_CFG7_TBLX               0x17
#define HODCAP2_REG_B17_CHIP_ID_0                   0x1C
#define HODCAP2_REG_B17_CHIP_ID_1                   0x1D
#define HODCAP2_REG_B17_CHIP_ID_2                   0x1E

/*! @} */ // hodcap2_reg

/**
 * @defgroup hodcap2_set HOD CAP 2 Registers Settings
 * @brief Settings for registers of HOD CAP 2 Click driver.
 */

/**
 * @addtogroup hodcap2_set
 * @{
 */

/**
 * @brief HOD CAP 2 BANK_SEL register setting.
 * @details Specified setting for BANK_SEL register of HOD CAP 2 Click driver.
 */
#define HODCAP2_BANK_SEL_ACCESS_WORD                0x5A00
#define HODCAP2_BANK_SEL_ACCESS_WORD_MASK           0xFF00
#define HODCAP2_BANK_SEL_BANK_0                     0x0000
#define HODCAP2_BANK_SEL_BANK_1                     0x0001
#define HODCAP2_BANK_SEL_BANK_2                     0x0002
#define HODCAP2_BANK_SEL_BANK_3                     0x0003
#define HODCAP2_BANK_SEL_BANK_4                     0x0004
#define HODCAP2_BANK_SEL_BANK_5                     0x0005
#define HODCAP2_BANK_SEL_BANK_6                     0x0006
#define HODCAP2_BANK_SEL_BANK_7                     0x0007
#define HODCAP2_BANK_SEL_BANK_8                     0x0008
#define HODCAP2_BANK_SEL_BANK_9                     0x0009
#define HODCAP2_BANK_SEL_BANK_10                    0x000A
#define HODCAP2_BANK_SEL_BANK_11                    0x000B
#define HODCAP2_BANK_SEL_BANK_12                    0x000C
#define HODCAP2_BANK_SEL_BANK_13                    0x000D
#define HODCAP2_BANK_SEL_BANK_14                    0x000E
#define HODCAP2_BANK_SEL_BANK_15                    0x000F
#define HODCAP2_BANK_SEL_BANK_16                    0x0010
#define HODCAP2_BANK_SEL_BANK_17                    0x0011
#define HODCAP2_BANK_SEL_BANK_MASK                  0x00FF

/**
 * @brief HOD CAP 2 MEMT_SEQ register setting.
 * @details Specified setting for MEMT_SEQ register of HOD CAP 2 Click driver.
 */
#define HODCAP2_MEMT_SEQ_TABLE_1_EN                 0x0001
#define HODCAP2_MEMT_SEQ_TABLE_2_EN                 0x0002
#define HODCAP2_MEMT_SEQ_TABLE_3_EN                 0x0004
#define HODCAP2_MEMT_SEQ_TABLE_4_EN                 0x0008
#define HODCAP2_MEMT_SEQ_TABLE_5_EN                 0x0010
#define HODCAP2_MEMT_SEQ_TABLE_6_EN                 0x0020
#define HODCAP2_MEMT_SEQ_TABLE_7_EN                 0x0040
#define HODCAP2_MEMT_SEQ_TABLE_8_EN                 0x0080
#define HODCAP2_MEMT_SEQ_TABLE_9_EN                 0x0100
#define HODCAP2_MEMT_SEQ_TABLE_10_EN                0x0200
#define HODCAP2_MEMT_SEQ_TABLE_11_EN                0x0400
#define HODCAP2_MEMT_SEQ_TABLE_12_EN                0x0800
#define HODCAP2_MEMT_SEQ_TABLE_13_EN                0x1000
#define HODCAP2_MEMT_SEQ_TABLE_14_EN                0x2000
#define HODCAP2_MEMT_SEQ_TABLE_15_EN                0x4000
#define HODCAP2_MEMT_SEQ_TABLE_16_EN                0x8000

/**
 * @brief HOD CAP 2 MEMT_CTL_2 register setting.
 * @details Specified setting for MEMT_CTL_2 register of HOD CAP 2 Click driver.
 */
#define HODCAP2_MEMT_CTL_2_CMD_NOP                  0x0000
#define HODCAP2_MEMT_CTL_2_CMD_STOP                 0x0100
#define HODCAP2_MEMT_CTL_2_CMD_CLEAR_NOT_INIT       0x0200
#define HODCAP2_MEMT_CTL_2_CMD_INIT_MODE            0x0300
#define HODCAP2_MEMT_CTL_2_CMD_POLLING_MODE         0x0400
#define HODCAP2_MEMT_CTL_2_CMD_SINGLE_MODE          0x0500
#define HODCAP2_MEMT_CTL_2_CMD_CONTINUOUS_MODE      0x0600
#define HODCAP2_MEMT_CTL_2_CMD_EL_CONNECTED         0x0700
#define HODCAP2_MEMT_CTL_2_CMD_EL_SHORT             0x0800
#define HODCAP2_MEMT_CTL_2_CMD_LOW_PWR_MODE         0x0900
#define HODCAP2_MEMT_CTL_2_CMD_MASK                 0x0F00
#define HODCAP2_MEMT_CTL_2_MEMT_STRT_PTR            0x00F0
#define HODCAP2_MEMT_CTL_2_MEMT_CUR_PTR             0x000F

/**
 * @brief HOD CAP 2 MEMT_CFG1_TBLX register setting.
 * @details Specified setting for MEMT_CFG1_TBLX register of HOD CAP 2 Click driver.
 */
#define HODCAP2_MEMT_CFG1_TBLX_PRESCALER_1          0x0000
#define HODCAP2_MEMT_CFG1_TBLX_PRESCALER_7          0x4000
#define HODCAP2_MEMT_CFG1_TBLX_PRESCALER_MASK       0xC000
#define HODCAP2_MEMT_CFG1_TBLX_FREQ_DEF             0x0040
#define HODCAP2_MEMT_CFG1_TBLX_FREQ_MASK            0x3FC0
#define HODCAP2_MEMT_CFG1_TBLX_SEN_E0_SEL           0x0001
#define HODCAP2_MEMT_CFG1_TBLX_SEN_E1_SEL           0x0002
#define HODCAP2_MEMT_CFG1_TBLX_SEN_E2_SEL           0x0004
#define HODCAP2_MEMT_CFG1_TBLX_SEN_E3_SEL           0x0008
#define HODCAP2_MEMT_CFG1_TBLX_SEN_REF_SEL          0x0010
#define HODCAP2_MEMT_CFG1_TBLX_SEN_SEN_TO_GND       0x0020
#define HODCAP2_MEMT_CFG1_TBLX_SEN_MASK             0x003F

/**
 * @brief HOD CAP 2 MEMT_CFG3_TBLX register setting.
 * @details Specified setting for MEMT_CFG3_TBLX register of HOD CAP 2 Click driver.
 */
#define HODCAP2_MEMT_CFG3_TBLX_PGA_OV_ISET_DEF      0x9940
#define HODCAP2_MEMT_CFG3_TBLX_PGA_OV_ISET_MASK     0xFFC0
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G0     0x0000
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G1     0x0004
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G2     0x0008
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G3     0x000C
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G4     0x0010
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G5     0x0014
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G6     0x0018
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G7     0x001C
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G8     0x0020
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G9     0x0024
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G10    0x0028
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G11    0x002C
#define HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_MASK   0x003C
#define HODCAP2_MEMT_CFG3_TBLX_ACCU_NO              0x0000
#define HODCAP2_MEMT_CFG3_TBLX_ACCU_2               0x0001
#define HODCAP2_MEMT_CFG3_TBLX_ACCU_4               0x0002
#define HODCAP2_MEMT_CFG3_TBLX_ACCU_8               0x0003
#define HODCAP2_MEMT_CFG3_TBLX_ACCU_MASK            0x0003

/**
 * @brief HOD CAP 2 bank selection setting.
 * @details Specified setting for bank selection of HOD CAP 2 Click driver.
 */
#define HODCAP2_BANK_0                              0
#define HODCAP2_BANK_1                              1
#define HODCAP2_BANK_2                              2
#define HODCAP2_BANK_3                              3
#define HODCAP2_BANK_4                              4
#define HODCAP2_BANK_5                              5
#define HODCAP2_BANK_6                              6
#define HODCAP2_BANK_7                              7
#define HODCAP2_BANK_8                              8
#define HODCAP2_BANK_9                              9
#define HODCAP2_BANK_10                             10
#define HODCAP2_BANK_11                             11
#define HODCAP2_BANK_12                             12
#define HODCAP2_BANK_13                             13
#define HODCAP2_BANK_14                             14
#define HODCAP2_BANK_15                             15
#define HODCAP2_BANK_16                             16
#define HODCAP2_BANK_17                             17

/**
 * @brief HOD CAP 2 command setting.
 * @details Specified setting for command of HOD CAP 2 Click driver.
 */
#define HODCAP2_CMD_NOP                             0
#define HODCAP2_CMD_STOP                            1
#define HODCAP2_CMD_CLEAR_NOT_INIT                  2
#define HODCAP2_CMD_INIT_MODE                       3
#define HODCAP2_CMD_POLLING_MODE                    4
#define HODCAP2_CMD_SINGLE_MODE                     5
#define HODCAP2_CMD_CONTINUOUS_MODE                 6
#define HODCAP2_CMD_EL_CONNECTED                    7
#define HODCAP2_CMD_EL_SHORT                        8
#define HODCAP2_CMD_LOW_PWR_MODE                    9

/**
 * @brief HOD CAP 2 table selection setting.
 * @details Specified setting for table selection of HOD CAP 2 Click driver.
 */
#define HODCAP2_TABLE_1                             0
#define HODCAP2_TABLE_2                             1
#define HODCAP2_TABLE_3                             2
#define HODCAP2_TABLE_4                             3
#define HODCAP2_TABLE_5                             4
#define HODCAP2_TABLE_6                             5
#define HODCAP2_TABLE_7                             6
#define HODCAP2_TABLE_8                             7
#define HODCAP2_TABLE_9                             8
#define HODCAP2_TABLE_10                            9
#define HODCAP2_TABLE_11                            10
#define HODCAP2_TABLE_12                            11
#define HODCAP2_TABLE_13                            12
#define HODCAP2_TABLE_14                            13
#define HODCAP2_TABLE_15                            14
#define HODCAP2_TABLE_16                            15

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hodcap2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HODCAP2_SET_DATA_SAMPLE_EDGE                SET_SPI_DATA_SAMPLE_EDGE
#define HODCAP2_SET_DATA_SAMPLE_MIDDLE              SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hodcap2_set

/**
 * @defgroup hodcap2_map HOD CAP 2 MikroBUS Map
 * @brief MikroBUS pin mapping of HOD CAP 2 Click driver.
 */

/**
 * @addtogroup hodcap2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HOD CAP 2 Click to the selected MikroBUS.
 */
#define HODCAP2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.trg  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hodcap2_map
/*! @} */ // hodcap2

/**
 * @brief HOD CAP 2 Click context object.
 * @details Context object definition of HOD CAP 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t trg;           /**< RES_TRIG pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t bank;               /**< Currently selected register bank. */

    uint16_t unique_id[ 3 ];    /**< Chip unique ID. */

} hodcap2_t;

/**
 * @brief HOD CAP 2 Click configuration object.
 * @details Configuration object definition of HOD CAP 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t trg;             /**< RES_TRIG pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hodcap2_cfg_t;

/**
 * @brief HOD CAP 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HODCAP2_OK = 0,
    HODCAP2_ERROR = -1

} hodcap2_return_value_t;

/*!
 * @addtogroup hodcap2 HOD CAP 2 Click Driver
 * @brief API for configuring and manipulating HOD CAP 2 Click driver.
 * @{
 */

/**
 * @brief HOD CAP 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hodcap2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hodcap2_cfg_setup ( hodcap2_cfg_t *cfg );

/**
 * @brief HOD CAP 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hodcap2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_init ( hodcap2_t *ctx, hodcap2_cfg_t *cfg );

/**
 * @brief HOD CAP 2 default configuration function.
 * @details This function executes a default configuration of HOD CAP 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hodcap2_default_cfg ( hodcap2_t *ctx );

/**
 * @brief HOD CAP 2 write register function.
 * @details This function writes a 16-bit data word to the selected register address
 * using the SPI interface with parity bit generation.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_write_reg ( hodcap2_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief HOD CAP 2 read register function.
 * @details This function reads a 16-bit data word from the selected register address
 * using the SPI interface with parity bit verification.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_read_reg ( hodcap2_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief HOD CAP 2 get TRG pin function.
 * @details This function reads the logic state of the TRG pin.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @return TRG pin logic state.
 * @note None.
 */
uint8_t hodcap2_get_trg_pin ( hodcap2_t *ctx );

/**
 * @brief HOD CAP 2 select bank function.
 * @details This function selects the active register bank if the requested bank
 * differs from the currently selected bank.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[in] bank : Bank number to be selected [0-17].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_select_bank ( hodcap2_t *ctx, uint8_t bank );

/**
 * @brief HOD CAP 2 read unique ID function.
 * @details This function reads the device unique ID words from bank 17 and then
 * restores the previously selected bank.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[out] unique_id : Output buffer for three 16-bit unique ID words.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_read_unique_id ( hodcap2_t *ctx, uint16_t *unique_id );

/**
 * @brief HOD CAP 2 send command function.
 * @details This function sends a command with the selected start table through
 * the measurement control register 2 and restores the previously selected bank.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[in] cmd : Command to be sent, see HODCAP2_CMD_x macro definitions.
 * @param[in] start_table : Start table index, see HODCAP2_TABLE_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_send_cmd ( hodcap2_t *ctx, uint8_t cmd, uint8_t start_table );

/**
 * @brief HOD CAP 2 clear diagnostic registers function.
 * @details This function reads and clears diagnostic registers from bank 0 and
 * optionally stores their previous contents to the provided output buffer.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[out] diag : Output buffer for three diagnostic register values, can be @c NULL.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_clear_diag ( hodcap2_t *ctx, uint16_t *diag );

/**
 * @brief HOD CAP 2 read measurement function.
 * @details This function performs a single measurement on the selected table,
 * stops the measurement process, and reads the result register value.
 * @param[in] ctx : Click context object.
 * See #hodcap2_t object definition for detailed explanation.
 * @param[in] table : Measurement table index, see HODCAP2_TABLE_x macro definitions.
 * @param[out] data_out : Output measurement data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap2_read_measurement ( hodcap2_t *ctx, uint8_t table, uint16_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // HODCAP2_H

/*! @} */ // hodcap2

// ------------------------------------------------------------------------ END

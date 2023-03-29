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
 * @file flash8.h
 * @brief This file contains API for Flash 8 Click Driver.
 */

#ifndef FLASH8_H
#define FLASH8_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"


/*!
 * @addtogroup flash8 Flash 8 Click Driver
 * @brief API for configuring and manipulating Flash 8 Click driver.
 * @{
 */

/**
 * @defgroup flash8_cmd Flash 8 command set List
 * @brief List of command set of Flash 8 Click driver.
 */

/**
 * @addtogroup flash8_cmd
 * @{
 */

/**
 * @brief Flash 8 description command set.
 * @details Specified command set for description of Flash 8 Click driver.
 */
#define FLASH8_CMD_READ_CELL_ARRAY                   0x13
#define FLASH8_CMD_READ_BUFFER                       0x03
#define FLASH8_CMD_READ_BUFFER_1                     0x0B
#define FLASH8_CMD_PROGRAM_LOAD                      0x02
#define FLASH8_CMD_PROGRAM_EXECUTE                   0x10
#define FLASH8_CMD_PROTECT_EXECUTE                   0x2A
#define FLASH8_CMD_PROGRAM_LOAD_RANDOM_DATA          0x84
#define FLASH8_CMD_BLOCK_ERASE                       0xD8
#define FLASH8_CMD_RESET                             0xFF
#define FLASH8_CMD_RESET_1                           0xFE
#define FLASH8_CMD_WRITE_ENABLE                      0x06
#define FLASH8_CMD_WRITE_DISABLE                     0x04
#define FLASH8_CMD_GET_FEATURE                       0x0F
#define FLASH8_CMD_SET_FEATURE                       0x1F
#define FLASH8_CMD_READ_ID                           0x9F
#define FLASH8_FEATURE_A0                            0xA0
#define FLASH8_FEATURE_B0                            0xB0
#define FLASH8_FEATURE_C0                            0xC0
#define FLASH8_FEATURE_10                            0x10
#define FLASH8_FEATURE_20                            0x20
#define FLASH8_FEATURE_30                            0x30
#define FLASH8_FEATURE_40                            0x40
#define FLASH8_FEATURE_50                            0x50
#define FLASH8_FEATURE_60                            0x60
#define FLASH8_FEATURE_70                            0x70

/*! @} */ // flash8_cmd

/**
 * @defgroup flash8_set Flash 8 Registers Settings
 * @brief Settings for registers of Flash 8 Click driver.
 */

/**
 * @addtogroup flash8_set
 * @{
 */

/**
 * @brief Flash 8 description feature table - 0xA0 setting.
 * @details Specified feature table - 0xA0 setting for description of Flash 8 Click driver.
 */
#define FLASH8_SET_BRWD_ENABLE                       0x00
#define FLASH8_SET_BRWD_DISABLE                      0x01
#define FLASH8_SET_BL_ALL_UNLOCKED                   0x00
#define FLASH8_SET_BL_UPPER_1_64_LOCKED              0x01
#define FLASH8_SET_BL_UPPER_1_32_LOCKED              0x02
#define FLASH8_SET_BL_UPPER_1_16_LOCKED              0x03
#define FLASH8_SET_BL_UPPER_1_8_LOCKED               0x04
#define FLASH8_SET_BL_UPPER_1_4_LOCKED               0x05
#define FLASH8_SET_BL_UPPER_1_2_LOCKED               0x06
#define FLASH8_SET_BL_ALLLOCKED                      0x07

/**
 * @brief Flash 8 description feature table - 0xB0 setting.
 * @details Specified feature table - 0xB0 setting for description of Flash 8 Click driver.
 */
#define FLASH8_SET_IDR_E_NORMAL_OPERATION            0x00
#define FLASH8_SET_IDR_E_PARAMETER_PAGE_READ         0x01
#define FLASH8_SET_ECC_E_INTERNAL_ECC_DISABLE        0x00
#define FLASH8_SET_ECC_E_INTERNAL_ECC_ENABLE         0x01
#define FLASH8_SET_PRT_E_NORMAL_OPERATION            0x00
#define FLASH8_SET_PRT_EBLOCK_PROTECTION_ENABLE      0x01
#define FLASH8_SET_HSE_HIGH_SPEED_MODE_DISABLE       0x00
#define FLASH8_SET_HSE_HIGH_SPEED_MODE_ENABLE        0x01
#define FLASH8_SET_HOLD_D_HOLD_IS_ENABLED            0x00
#define FLASH8_SET_HOLD_D_HOLD_IS_DISABLED           0x01

/**
 * @brief Flash 8 description feature table - 0xC0 setting.
 * @details Specified feature table - 0xC0 setting for description of Flash 8 Click driver.
 */
#define FLASH8_SET_WEL_WRITE_DISABLE                 0x00
#define FLASH8_SET_WEL_WRITE_ENABLE                  0x01


/*! @} */ // flash8_set

/**
 * @defgroup flash8_set Flash 8 Registers Settings
 * @brief Settings for registers of Flash 8 Click driver.
 */

/**
 * @addtogroup flash8_get
 * @{
 */

/**
 * @brief Flash 8 description feature table - 0xC0 setting.
 * @details Specified feature table - 0xC0 setting for description of Flash 8 Click driver.
 */
#define FLASH8_GET_ECCS_NO_BIT_FLIPS_WERE_DETECT     0x00
#define FLASH8_GET_ECCS_BIT_FLIPS_DETECT_CORRECT     0x10
#define FLASH8_GET_ECCS_MULTI_BIT_FLIPS_NOT_CORRECT  0x20
#define FLASH8_GET_ECCS_BIT_FLIPS_DETECT_CORRECTED   0x30
#define FLASH8_GET_PRG_F_PROGRAM_PASS                0x00
#define FLASH8_GET_PRG_F_PROGRAM_FAIL                0x08
#define FLASH8_GET_PRG_F_PROGRAM_PASS                0x00
#define FLASH8_GET_ERS_F_ERASE_FAIL                  0x04
#define FLASH8_GET_WEL_WRITE_DISABLE                 0x00
#define FLASH8_GET_WEL_WRITE_ENABLE                  0x02
#define FLASH8_GET_OIP_READY_STATE                   0x00
#define FLASH8_GET_OIP_BUSY_STATE                    0x01


/*! @} */ // flash8_get

/**
 * @defgroup flash8_map Flash 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 8 Click driver.
 */

/**
 * @addtogroup flash8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 8 Click to the selected MikroBUS.
 */
#define FLASH8_MAP_MIKROBUS( cfg, mikrobus )        \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // flash8_map
/*! @} */ // flash8

/**
 * @brief Flash 8 Click context object.
 * @details Context object definition of Flash 8 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  wp;          /**< Write protect pin. */
    digital_out_t  hld;         /**< Hold pin. */

    // Modules

    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} flash8_t;

/**
 * @brief Flash 8 Click configuration object.
 * @details Configuration object definition of Flash 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  wp;             /**< Write protect pin. */
    pin_name_t  hld;            /**< Hold pin. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} flash8_cfg_t;

/**
 * @brief Flash 8 Feature operation object.
 * @details Feature operation object definition of Flash 8 Click driver.
 */
typedef struct
{
   uint8_t    brwd;
   uint8_t    bl;
   uint8_t    idr_e;
   uint8_t    ecc_e;
   uint8_t    prt_e;
   uint8_t    hse;
   uint8_t    hold_d;
   uint8_t    eccs;
   uint8_t    prg_f;
   uint8_t    ers_f;
   uint8_t    wel;
   uint8_t    oip;

} feature_cfg_t;

/**
 * @brief Flash 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   FLASH8_OK = 0,
   FLASH8_ERROR = -1

} flash8_return_value_t;

/*!
 * @addtogroup flash8 Flash 8 Click Driver
 * @brief API for configuring and manipulating Flash 8 Click driver.
 * @{
 */

/**
 * @brief Flash 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash8_cfg_setup ( flash8_cfg_t *cfg );

/**
 * @brief Flash 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_init ( flash8_t *ctx, flash8_cfg_t *cfg );

/**
 * @brief Flash 8 default configuration function.
 * @details This function executes a default configuration of Flash 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t flash8_default_cfg ( flash8_t *ctx );

/**
 * @brief Flash 8 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_generic_write ( flash8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 8 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_generic_read ( flash8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Flash 8 hold enable function.
 * @details This function performs write protection enabled ( HLD is low ) 
 * of the Flash 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_hold_enable ( flash8_t *ctx );

/**
 * @brief Flash 8 hold disable function.
 * @details This function performs write protection disable ( HLD is high ) 
 * of the Flash 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_hold_disable ( flash8_t *ctx );

/**
 * @brief Flash 8 enable write protection function.
 * @details This function performs write protection enabled ( WP is low )
 * of the Flash 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_write_protect_enable ( flash8_t *ctx );

/**
 * @brief Flash 8 disable write protection function.
 * @details This function performs write protection disable ( WP is high )
 * of the Flash 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_write_protect_disable ( flash8_t *ctx );

/**
 * @brief Flash 8 read cell array function.
 * @details This function read the data from the cell array to the internal data buffer 
 * and read the status (OIP, ECCS0 and ECCS1 bits) 
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] row_address : Row Address 18-bits ( Block Address 12-bits, Page Address 6-bits ).
 * @param[in] column_address : Column Address 13 bits ( 4224 or 4352 bytes/page ).
 * @param[out] feature_status_out : Feature Table data out.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_read_cell_array ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *feature_status_out );

/**
 * @brief Flash 8 read buffer function.
 * @details This function read output the data from the internal data buffer
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] column_address : Column Address 13 bits ( 4224 or 4352 bytes/page ).
 * @param[out] read_data : Read data out.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_read_buffer ( flash8_t *ctx, uint16_t column_address, uint8_t *read_data );

/**
 * @brief Flash 8 program load function.
 * @details This function performs transfer data to the internal data buffer
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] column_address : Column Address 13 bits ( 4224 or 4352 bytes/page ).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_program_load ( flash8_t *ctx, uint16_t column_address, uint8_t *data_in, uint16_t len );

/**
 * @brief Flash 8 program execute function.
 * @details This function performs program data from the buffer to the cell array
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] row_address : Row Address 18-bits ( Block Address 12-bits, Page Address 6-bits ).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_program_execute ( flash8_t *ctx, uint32_t row_address );

/**
 * @brief Flash 8 program load random function.
 * @details This function program load random data and get feature 
 * performs transfer data to the internal data buffer
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] column_address : Column Address 13 bits ( 4224 or 4352 bytes/page ).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_program_load_random ( flash8_t *ctx, uint16_t column_address, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 8 block erase function.
 * @details This function block erase, performs erases the selected block. 
 * To complete the operation, performs write enable, erase data in the block
 * and read the status (OIP and ERS_F bits) of the device
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] row_address : Row Address 18-bits ( Block Address 12-bits, Page Address 6-bits ).
 * @param[out] feat_data : Read the status (OIP and ERS_F bits) of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_block_erase ( flash8_t *ctx, uint32_t row_address, uint8_t *feat_data );

/**
 * @brief Flash 8 soft reset function.
 * @details This function soft reset, executed to abort the operation in progress 
 * by reset command and read the status (OIP bit)
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[out] feat_data : Read the status (OIP bit) of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_sw_reset ( flash8_t *ctx, uint8_t *feat_data );

/**
 * @brief Flash 8 write enable function.
 * @details This function write enable set the WEL (Write Enable Latch) bit
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_write_enable ( flash8_t *ctx );

/**
 * @brief Flash 8 write disable function.
 * @details This function write enable reset the WEL (Write Enable Latch) bit
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_write_disable ( flash8_t *ctx );

/**
 * @brief Flash 8 set feature function.
 * @details This function set individual features for getting feature settings or status
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] feature_addr : Feature Table address.
 * @param[in] feature_data : Feature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_set_feature ( flash8_t *ctx, uint8_t feature_addr, uint8_t feature_data );

/**
 * @brief Flash 8 set config feature function.
 * @details This function set all features for getting feature settings or status
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] feature_data : Feature operation object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_set_config_feature ( flash8_t *ctx, feature_cfg_t feature_data );

/**
 * @brief Flash 8 get feature function.
 * @details This function get individual features for getting feature settings or status
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] feature_addr : Feature Table address.
 * @param[in] feature_data : Feature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_get_feature ( flash8_t *ctx, uint8_t feature_addr, uint8_t *feature_data );

/**
 * @brief Flash 8 get config feature function.
 * @details This function get all features for getting feature settings or status
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[out] feature_data : Feature operation object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_get_config_feature ( flash8_t *ctx, feature_cfg_t *feature_data );

/**
 * @brief Flash 8 protected area all unlocked function.
 * @details This function performs unlocked all protected area 
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_protected_area_all_unlocked ( flash8_t *ctx );

/**
 * @brief Flash 8 protect execute function.
 * @details This function program the operation protect desired block 
 * and read the status (OIP and PRG_F bits) of the device
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] row_address : Row Address 18-bits ( Block Address 12-bits, Page Address 6-bits ).
 * @param[out] feature_status_out : Read the status (OIP and PRG_F bits) of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_protect_execute ( flash8_t *ctx, uint32_t row_address, uint8_t *feature_status_out );

/**
 * @brief Flash 8 read ID function.
 * @details This function read manufacture, device and organization ID
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[out] manufacture_id  : Manufacture ID (KIOXIA) ( 0x98 ).
 * @param[out] device_id       : Device ID ( 0xE4 ).
 * @param[out] organization_id : Organization ID ( 0x51 ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_read_id ( flash8_t *ctx, uint8_t *manufacture_id, uint8_t *device_id, uint8_t *organization_id );

/**
 * @brief Flash 8 write memory function.
 * @details This function write, memory performs enable the program function,
 * transfer data to the internal data buffe,  program data from the buffer to the cell array
 * and read the status (OIP and PRG_F bits)
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] row_address : Row Address 18-bits ( Block Address 12-bits, Page Address 6-bits ).
 * @param[in] column_address : Column Address 13 bits ( 4224 or 4352 bytes/page ).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @param[out] feature_status_out : Read the status (OIP and PRG_F bits) of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_write_memory ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *data_in, uint16_t len, uint8_t *feature_status_out );

/**
 * @brief Flash 8 read memory function.
 * @details This function read memory, performs read the data from the cell array to the internal data buffer,
 * read the status (OIP, ECCS0 and ECCS1 bits) 
 * and output the data from the internal data buffer
 * of the KIOXIA 8Gb 3.3V Serial Interface NAND on the Flash 8 Click board™.  
 * @param[in] ctx : Click context object.
 * See #flash8_t object definition for detailed explanation.
 * @param[in] row_address : Row Address 18-bits ( Block Address 12-bits, Page Address 6-bits ).
 * @param[in] column_address : Column Address 13 bits ( 4224 or 4352 bytes/page ).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be written.
 * @param[out] feature_status_out : Read the status (OIP, ECCS0 and ECCS1 bits)  of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash8_read_memory ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *data_out, uint16_t len, uint8_t *feature_status_out );

#ifdef __cplusplus
}
#endif
#endif // FLASH8_H

/*! @} */ // flash8

// ------------------------------------------------------------------------ END

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
 * @file cdc.h
 * @brief This file contains API for CDC Click Driver.
 */

#ifndef CDC_H
#define CDC_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup cdc CDC Click Driver
 * @brief API for configuring and manipulating CDC Click driver.
 * @{
 */

/**
 * @defgroup cdc_reg CDC Registers List
 * @brief List of registers of CDC Click driver.
 */

/**
 * @addtogroup cdc_reg
 * @{
 */

 /**
 * @brief CDC opcodes list.
 * @details Specified opcodes list of CDC Click driver.
 */
#define CDC_OPCODE_WR_MEM               0xA0
#define CDC_OPCODE_RD_MEM               0x20
#define CDC_OPCODE_RD_RES               0x40
#define CDC_OPCODE_POR                  0x88
#define CDC_OPCODE_INITIALIZE           0x8A
#define CDC_OPCODE_CDC_START            0x8C
#define CDC_OPCODE_RDC_START            0x8E
#define CDC_OPCODE_DSP_TRIG             0x8D
#define CDC_OPCODE_NV_STORE             0x96
#define CDC_OPCODE_NV_RECALL            0x99
#define CDC_OPCODE_NV_ERASE             0x9C
#define CDC_OPCODE_TEST_READ            0x7E
/**
 * @brief CDC config registers list.
 * @details Specified config registers list of CDC Click driver.
 */
#define CDC_REG_CFG0                    0x00
#define CDC_REG_CFG1                    0x01
#define CDC_REG_CFG2                    0x02
#define CDC_REG_CFG3                    0x03
#define CDC_REG_CFG4                    0x04
#define CDC_REG_CFG5                    0x05
#define CDC_REG_CFG6                    0x06
#define CDC_REG_CFG7                    0x07
#define CDC_REG_CFG8                    0x08
#define CDC_REG_CFG9                    0x09
#define CDC_REG_CFG10                   0x0A
#define CDC_REG_CFG11                   0x0B
#define CDC_REG_CFG12                   0x0C
#define CDC_REG_CFG13                   0x0D
#define CDC_REG_CFG14                   0x0E
#define CDC_REG_CFG15                   0x0F
#define CDC_REG_CFG16                   0x10
#define CDC_REG_CFG17                   0x11
#define CDC_REG_CFG18                   0x12
#define CDC_REG_CFG19                   0x13
#define CDC_REG_CFG20                   0x14
#define CDC_REG_CFG21                   0x15
#define CDC_REG_CFG22                   0x16
#define CDC_REG_CFG23                   0x17
#define CDC_REG_CFG24                   0x18
#define CDC_REG_CFG25                   0x19
#define CDC_REG_CFG26                   0x1A
#define CDC_REG_CFG27                   0x1B
#define CDC_REG_CFG28                   0x1C
#define CDC_REG_CFG29                   0x1D
#define CDC_REG_CFG30                   0x1E
#define CDC_REG_CFG31                   0x1F
#define CDC_REG_CFG32                   0x20
#define CDC_REG_CFG33                   0x21
#define CDC_REG_CFG34                   0x22
#define CDC_REG_CFG35                   0x23
#define CDC_REG_CFG38                   0x26
#define CDC_REG_CFG39                   0x27
#define CDC_REG_CFG40                   0x28
#define CDC_REG_CFG41                   0x29
#define CDC_REG_CFG42                   0x2A
#define CDC_REG_CFG47                   0x2F
#define CDC_REG_CFG48                   0x30
#define CDC_REG_CFG49                   0x31
#define CDC_REG_CFG50                   0x32
#define CDC_REG_CFG54                   0x36
#define CDC_REG_CFG62                   0x3E
#define CDC_REG_CFG63                   0x3F

/**
 * @brief CDC result registers list.
 * @details Specified result registers list of CDC Click driver.
 */
#define CDC_REG_RES0                    0x00
#define CDC_REG_RES1                    0x04
#define CDC_REG_RES2                    0x08
#define CDC_REG_RES3                    0x0C
#define CDC_REG_RES4                    0x10
#define CDC_REG_RES5                    0x14
#define CDC_REG_RES6                    0x18
#define CDC_REG_RES7                    0x1C
#define CDC_REG_STATUS_0                0x20
#define CDC_REG_STATUS_1                0x21
#define CDC_REG_STATUS_2                0x22

/*! @} */ // cdc_reg

/**
 * @defgroup cdc_set CDC Registers Settings
 * @brief Settings for registers of CDC Click driver.
 */

/**
 * @addtogroup cdc_set
 * @{
 */

  /**
 * @brief CDC memory address setting.
 * @details Specified setting memory address of CDC Click driver.
 */
#define CDC_MEM_ADDRESS_START           0x0000u
#define CDC_MEM_ADDRESS_END             0x03FFu
#define CDC_MEM_ADDRESS_CFG_OFFSET      0x03C0u
#define CDC_MEM_ADDRESS_WR_BLOCK_SIZE   64

 /**
 * @brief CDC fixed-point result setting.
 * @details Specified setting fixed-point result of CDC Click driver.
 */
#define CDC_FIXED_POINT_NUM_FRACTIONAL  27

/**
 * @brief CDC test read result setting.
 * @details Specified setting test read result used for testing communication of CDC Click driver.
 */
#define CDC_TEST_READ_RES               0x11

/**
 * @brief CDC device address setting.
 * @details Specified setting for device slave address selection of
 * CDC Click driver.
 */
#define CDC_DEVICE_ADDRESS              0x28

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b cdc_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CDC_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define CDC_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // cdc_set

/**
 * @defgroup cdc_map CDC MikroBUS Map
 * @brief MikroBUS pin mapping of CDC Click driver.
 */

/**
 * @addtogroup cdc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CDC Click to the selected MikroBUS.
 */
#define CDC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sis = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // cdc_map
/*! @} */ // cdc

/**
 * @brief CDC Click driver selector.
 * @details Selects target driver interface of CDC Click driver.
 */
typedef enum
{
    CDC_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    CDC_DRV_SEL_I2C       /**< I2C driver descriptor. */

} cdc_drv_t;

/**
 * @brief CDC Click context object.
 * @details Context object definition of CDC Click driver.
 */
typedef struct cdc_s
{
    digital_out_t sis;              /**< Serial interface select pin (1-I2C, 0-SPI). */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    cdc_drv_t    drv_sel;           /**< Master driver interface selector. */

} cdc_t;

/**
 * @brief CDC Click configuration object.
 * @details Configuration object definition of CDC Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t sis;                 /**< Serial interface select pin (1-I2C, 0-SPI). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    cdc_drv_t drv_sel;              /**< Master driver interface selector. */

} cdc_cfg_t;

/**
 * @brief CDC Click results object.
 * @details Results object definition of CDC Click driver.
 */
typedef struct
{
    float res_0;                    /**< Result 0 register - 32-bit fixed-point (27-fractional) value converted to float. */
    float res_1;                    /**< Result 1 register - 32-bit fixed-point (27-fractional) value converted to float. */
    float res_2;                    /**< Result 2 register - 32-bit fixed-point (27-fractional) value converted to float. */
    float res_3;                    /**< Result 3 register - 32-bit fixed-point (27-fractional) value converted to float. */
    float res_4;                    /**< Result 4 register - 32-bit fixed-point (27-fractional) value converted to float. */
    float res_5;                    /**< Result 5 register - 32-bit fixed-point (27-fractional) value converted to float. */
    float res_6;                    /**< Result 6 register - 32-bit fixed-point (27-fractional) value converted to float. */
    float res_7;                    /**< Result 7 register - 32-bit fixed-point (27-fractional) value converted to float. */
    uint8_t status_0;               /**< Status 0 register value. */
    uint8_t status_1;               /**< Status 1 register value. */
    uint8_t status_2;               /**< Status 2 register value. */

} cdc_results_t;

/**
 * @brief CDC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CDC_OK = 0,
    CDC_ERROR = -1

} cdc_return_value_t;

/*!
 * @addtogroup cdc CDC Click Driver
 * @brief API for configuring and manipulating CDC Click driver.
 * @{
 */

/**
 * @brief CDC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #cdc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void cdc_cfg_setup ( cdc_cfg_t *cfg );

/**
 * @brief CDC driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #cdc_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #cdc_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void cdc_drv_interface_sel ( cdc_cfg_t *cfg, cdc_drv_t drv_sel );

/**
 * @brief CDC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #cdc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_init ( cdc_t *ctx, cdc_cfg_t *cfg );

/**
 * @brief CDC default configuration function.
 * @details This function executes a default configuration of CDC
 * click board.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t cdc_default_cfg ( cdc_t *ctx );

/**
 * @brief CDC write memory function.
 * @details This function writes data to memory starting from the selected address.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[in] address : Start memory address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_write_memory ( cdc_t *ctx, uint16_t address, const uint8_t *data_in, uint16_t len );

/**
 * @brief CDC read memory function.
 * @details This function reads a desired number of data bytes starting from
 * the selected memory address.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[in] address : Start memory address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_read_memory ( cdc_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief CDC write config function.
 * @details This function writes configuration data starting from the selected config address.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[in] address : Start config address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_write_config ( cdc_t *ctx, uint8_t address, const uint8_t *data_in, uint8_t len );

/**
 * @brief CDC read config function.
 * @details This function reads a desired number of configuration data registers starting from
 * the selected address.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[in] address : Start config address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_read_config ( cdc_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief CDC read result function.
 * @details This function reads a desired number of result data registers starting from
 * the selected address.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[in] address : Start result address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_read_result ( cdc_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief CDC send opcode function.
 * @details This function sends a desired opcode command byte.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[in] opcode : Opcode command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_send_opcode ( cdc_t *ctx, uint8_t opcode );

/**
 * @brief CDC check communication function.
 * @details This function checks the communication by performing a test read feature.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_check_communication ( cdc_t *ctx );

/**
 * @brief CDC read results function.
 * @details This function reads all results and status registers.
 * @param[in] ctx : Click context object.
 * See #cdc_t object definition for detailed explanation.
 * @param[out] results : Results object data output.
 * See #cdc_results_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cdc_read_results ( cdc_t *ctx, cdc_results_t *results );

#ifdef __cplusplus
}
#endif
#endif // CDC_H

/*! @} */ // cdc

// ------------------------------------------------------------------------ END

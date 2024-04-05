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
 * @file nvsram4.h
 * @brief This file contains API for nvSRAM 4 Click Driver.
 */

#ifndef NVSRAM4_H
#define NVSRAM4_H

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

/*!
 * @addtogroup nvsram4 nvSRAM 4 Click Driver
 * @brief API for configuring and manipulating nvSRAM 4 Click driver.
 * @{
 */

/**
 * @defgroup nvsram4_reg nvSRAM 4 Registers List
 * @brief List of registers of nvSRAM 4 Click driver.
 */

/**
 * @addtogroup nvsram4_reg
 * @{
 */

/**
 * @brief nvSRAM 4 description Status and RTC Register Map.
 * @details Specified RTC Register Map for description of nvSRAM 4 Click driver.
 */

#define NVSRAM4_STATUS_RDY                                         0x01
#define NVSRAM4_STATUS_WEN                                         0x02
#define NVSRAM4_STATUS_BP0                                         0x04
#define NVSRAM4_STATUS_BP1                                         0x08
#define NVSRAM4_STATUS_SNL                                         0x40
#define NVSRAM4_STATUS_WPEN                                        0x80
    
#define NVSRAM4_RTC_FLAGS                                          0x00
#define NVSRAM4_RTC_TK_CENTURIES                                   0x01
#define NVSRAM4_RTC_ALARM_SECONDS                                  0x02
#define NVSRAM4_RTC_ALARM_MINUTES                                  0x03
#define NVSRAM4_RTC_ALARM_HOURS                                    0x04
#define NVSRAM4_RTC_ALARM_DAY                                      0x05
#define NVSRAM4_RTC_INTERRUPT_STATUS                               0x06
#define NVSRAM4_RTC_WATCHDOG_TIMER                                 0x07
#define NVSRAM4_RTC_CALIBRATION                                    0x08
#define NVSRAM4_RTC_TK_SECONDS                                     0x09
#define NVSRAM4_RTC_TK_MINUTES                                     0x0A
#define NVSRAM4_RTC_TK_HOURS                                       0x0B
#define NVSRAM4_RTC_TK_DAY                                         0x0C
#define NVSRAM4_RTC_TK_DATE                                        0x0D
#define NVSRAM4_RTC_TK_MONTHS                                      0x0E
#define NVSRAM4_RTC_TK_YEARS                                       0x0F

/*! @} */ // nvsram4_reg

/**
 * @defgroup nvsram4_set nvSRAM 4 Registers Settings
 * @brief Settings for registers of nvSRAM 4 Click driver.
 */

/**
 * @addtogroup nvsram4_set
 * @{
 */

/**
 * @brief nvSRAM 4 description setting.
 * @details Specified setting for description of nvSRAM 4 Click driver.
 */

/**
 * @addtogroup status_reg
 * @{
 */

/**
 * @brief nvSRAM 4 Status Register Control Instructions setting.
 * @details Specified setting for Status Register Control Instructions
 * of nvSRAM 4 Click driver.
 */
#define NVSRAM4_STATUS_RDSR                                        0x05
#define NVSRAM4_STATUS_FRDSR                                       0x0A
#define NVSRAM4_STATUS_WRSR                                        0x01
#define NVSRAM4_STATUS_WREN                                        0x06
#define NVSRAM4_STATUS_WRDI                                        0x04

/*! @} */ // status_reg

/**
 * @addtogroup sram_cmd
 * @{
 */

/**
 * @brief nvSRAM 4 SRAM Read/Write Instructions setting.
 * @details Specified setting for SRAM Read/Write Instructions
 * of nvSRAM 4 Click driver.
 */
#define NVSRAM4_SRAM_READ                                          0x03
#define NVSRAM4_SRAM_FREAD                                         0x0B
#define NVSRAM4_SRAM_WRITE                                         0x02

/*! @} */ // sram_cmd

/**
 * @addtogroup rtc_cmd
 * @{
 */

/**
 * @brief nvSRAM 4 RTC Read/Write Instructions setting.
 * @details Specified setting for RTC Read/Write Instructions
 * of nvSRAM 4 Click driver.
 */
#define NVSRAM4_SRAM_RDRTC                                         0x13
#define NVSRAM4_SRAM_FAST_RDRTC                                    0x1D
#define NVSRAM4_SRAM_WRTC                                          0x12

/*! @} */ // rtc_cmd

/**
 * @addtogroup nv_spc_cmd
 * @{
 */

/**
 * @brief nvSRAM 4 Special NV Instructions setting.
 * @details Specified setting for Special NV Instructions
 * of nvSRAM 4 Click driver.
 */
#define NVSRAM4_SPEC_NV_STORE                                      0x3C
#define NVSRAM4_SPEC_NV_RECALL                                     0x60
#define NVSRAM4_SPEC_NV_ASENB                                      0x59
#define NVSRAM4_SPEC_NV_ASDISB                                     0x19

/*! @} */ // nv_spc_cmd

/**
 * @addtogroup spc_cmd
 * @{
 */

/**
 * @brief nvSRAM 4 Special Instructions setting.
 * @details Specified setting for Special Instructions
 * of nvSRAM 4 Click driver.
 */
#define NVSRAM4_SPEC_SLEEP                                         0xB9
#define NVSRAM4_SPEC_WRSN                                          0xC2
#define NVSRAM4_SPEC_RDSN                                          0xC3
#define NVSRAM4_SPEC_FRDSN                                         0xC9
#define NVSRAM4_SPEC_RDID                                          0x9F
#define NVSRAM4_SPEC_FRDID                                         0x99

/*! @} */ // spc_cmd

/**
 * @addtogroup status_reg_cont
 * @{
 */

/**
 * @brief nvSRAM 4 Status Register Content setting.
 * @details Specified setting for Status Register Content
 * of nvSRAM 4 Click driver.
 */
#define NVSRAM4_STATUS_RDY                                         0x01
#define NVSRAM4_STATUS_WEN                                         0x02
#define NVSRAM4_STATUS_BP0                                         0x04
#define NVSRAM4_STATUS_BP1                                         0x08
#define NVSRAM4_STATUS_SNL                                         0x40
#define NVSRAM4_STATUS_WPEN                                        0x80

/*! @} */ // status_reg_cont

/**
 * @addtogroup en_hold
 * @{
 */

/**
 * @brief nvSRAM 4 HLD pin state.
 * @details Specified HLD pin state 
 * for description of nvSRAM 4 Click driver.
 */
#define NVSRAM4_HOLD_ENABLE                                        0x00
#define NVSRAM4_HOLD_DISABLE                                       0x01


/*! @} */ // en_hold

/**
 * @addtogroup en_hw_store
 * @{
 */

/**
 * @brief nvSRAM 4 HSB pin state.
 * @details Specified HSB pin state 
 * for description of nvSRAM 4 Click driver.
 */
#define NVSRAM4_HSB_ENABLE                                        0x00
#define NVSRAM4_HSB_DISABLE                                       0x01


/*! @} */ // en_hw_store

/**
 * @addtogroup en_hw_store
 * @{
 */

/**
 * @brief nvSRAM 4 WP pin state.
 * @details Specified Write protect pin state 
 * for description of nvSRAM 4 Click driver.
 */
#define NVSRAM4_WP_ENABLE                                        0x00
#define NVSRAM4_WP_DISABLE                                       0x01


/*! @} */ // en_hw_store


/*! @} */ // nvsram4_set

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief nvSRAM 4 error status.
 * @details Specified error status 
 * for description of nvSRAM 4 Click driver.
 */
#define NVSRAM4_SUCCESS            0
#define NVSRAM4_ERROR             -1


/*! @} */ // status

/**
 * @defgroup nvsram4_map nvSRAM 4 MikroBUS Map
 * @brief MikroBUS pin mapping of nvSRAM 4 Click driver.
 */

/**
 * @addtogroup nvsram4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of nvSRAM 4 Click to the selected MikroBUS.
 */
#define NVSRAM4_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.hsb = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nvsram4_map
/*! @} */ // nvsram4

/**
 * @brief nvSRAM 4 Click context object.
 * @details Context object definition of nvSRAM 4 Click driver.
 */
typedef struct
{
    // Output pins

     digital_out_t  hld;       /**< Hold HLD Pin. */
     digital_out_t  hsb;       /**< Hardware Store and HSB pin. */
     digital_out_t  wp;        /**< Hardware Write Protection WP pin. */

    // Input pins

     digital_in_t  int_pin;    /**< Interrupt INT pin. */

    // Modules

    spi_master_t  spi;         /**< SPI driver object. */

    pin_name_t  chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} nvsram4_t;

/**
 * @brief nvSRAM 4 Click configuration object.
 * @details Configuration object definition of nvSRAM 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

     pin_name_t  hld;       /**< Hold HLD Pin. */
     pin_name_t  hsb;       /**< Hardware Store and HSB pin. */
     pin_name_t  wp;        /**< Hardware Write Protection WP pin. */
     pin_name_t  int_pin;   /**< Interrupt INT pin. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} nvsram4_cfg_t;

typedef struct 
{
    
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
    
} nvsram4_rtc_time_t;

typedef struct 
{
    
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t day_of_week;
    

} nvsram4_rtc_date_t;

typedef struct 
{
    
    uint8_t day;
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
    
} nvsram4_rtc_alarm_t;

/*!
 * @addtogroup nvsram4 nvSRAM 4 Click Driver
 * @brief API for configuring and manipulating nvSRAM 4 Click driver.
 * @{
 */

/**
 * @brief nvSRAM 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nvsram4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nvsram4_cfg_setup ( nvsram4_cfg_t *cfg );

/**
 * @brief nvSRAM 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nvsram4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_init ( nvsram4_t *ctx, nvsram4_cfg_t *cfg );

/**
 * @brief nvSRAM 4 default configuration function.
 * @details This function executes a default configuration of nvSRAM 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void nvsram4_default_cfg ( nvsram4_t *ctx );

/**
 * @brief nvSRAM 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface 
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_generic_write ( nvsram4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief nvSRAM 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_generic_read ( nvsram4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief nvSRAM 4 set command function.
 * @details This function writes a desired command
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_set_cmd ( nvsram4_t *ctx, uint8_t cmd );

/**
 * @brief nvSRAM 4 read status function.
 * @details This function reads a status register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @return Output read status data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t nvsram4_read_status ( nvsram4_t *ctx );

/**
 * @brief nvSRAM 4 write status function.
 * @details This function writes a status register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] st_data : Status data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram4_write_status ( nvsram4_t *ctx, uint8_t st_data );

/**
 * @brief nvSRAM 4 burst read memory function.
 * @details This function reads a desired memory address 
 * of data bytes starting from
 * the selected register by using SPI serial interface
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_burst_read_memory ( nvsram4_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief nvSRAM 4 burst write memory function.
 * @details This function burst write memory a desired number address
 * of data bytes starting from
 * the selected memory address by using SPI serial interface
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[in] data_in : Data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_burst_write_memory ( nvsram4_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief nvSRAM 4 read device ID function.
 * @details This function reads a device ID
 * by using SPI serial interface
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @return Device ID.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint32_t nvsram4_read_id ( nvsram4_t *ctx );

/**
 * @brief nvSRAM 4 rtc read register function.
 * @details This function reads a desired the bytes of data from
 * the selected rtc register by using SPI serial interface
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] rtc_reg : RTC register address.
 * @return Output read data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t nvsram4_rtc_read_reg ( nvsram4_t *ctx, uint8_t rtc_reg );

/**
 * @brief nvSRAM 4 rtc write register function.
 * @details This function writes a desired the bytes of data from
 * the selected rtc register by using SPI serial interface 
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] rtc_reg : RTC register address.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram4_rtc_write_reg ( nvsram4_t *ctx, uint8_t rtc_reg, uint8_t data_in );

/**
 * @brief nvSRAM 4 enable rtc register write function.
 * @details This function enable write rtc register of the
 * CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram4_enable_rtc_write ( nvsram4_t *ctx );

/**
 * @brief nvSRAM 4 disable rtc register write function.
 * @details This function disable write rtc register 
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram4_disable_rtc_write ( nvsram4_t *ctx );

/**
 * @brief nvSRAM 4 get RTC time function.
 * @details This function get RTC time data structure
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[out] rtc_time : RTC time context object.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram4_get_rtc_time ( nvsram4_t *ctx, nvsram4_rtc_time_t *rtc_time );

/**
 * @brief nvSRAM 4 set RTC time function.
 * @details This function set RTC time data structure
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] rtc_time : RTC time context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_set_rtc_time ( nvsram4_t *ctx, nvsram4_rtc_time_t rtc_time );

/**
 * @brief nvSRAM 4 get RTC date function.
 * @details This function get RTC date data structure
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[out] rtc_date : RTC date context object.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram4_get_rtc_date ( nvsram4_t *ctx, nvsram4_rtc_date_t *rtc_date );

/**
 * @brief nvSRAM 4 set RTC date function.
 * @details This function set RTC date data structure
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] rtc_date : RTC date context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_set_rtc_date ( nvsram4_t *ctx, nvsram4_rtc_date_t rtc_date );

/**
 * @brief nvSRAM 4 get RTC alarm function.
 * @details This function get RTC alarm structure
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[out] rtc_alarm : RTC alarm context object.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram4_get_rtc_alarm ( nvsram4_t *ctx, nvsram4_rtc_alarm_t *rtc_alarm );

/**
 * @brief nvSRAM 4 set RTC alarm function.
 * @details This function set RTC date alarm structure
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] rtc_alarm : RTC alarm context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_set_rtc_alarm ( nvsram4_t *ctx, nvsram4_rtc_alarm_t rtc_alarm );

/**
 * @brief nvSRAM 4 set hold function.
 * @details This function set hold by setting the HLD pin state
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] en_hold : 
 *         @li @c 0 ( NVSRAM4_HOLD_ENABLE ) - Enable hold and pause the serial communication,
 *         @li @c 1 ( NVSRAM4_HOLD_DISABLE )- Disable hold and resume the serial communication.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_hold ( nvsram4_t *ctx, uint8_t en_hold );

/**
 * @brief nvSRAM 4 hardware store function.
 * @details This function set hardware store by setting the HSB pin state
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] en_hw_store : 
 *         @li @c 0 ( NVSRAM4_HSB_ENABLE ) - Store operations,
 *         @li @c 1 ( NVSRAM4_HSB_DISABLE )- Resume the serial communication.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_hardware_store ( nvsram4_t *ctx, uint8_t en_hw_store );

/**
 * @brief nvSRAM 4 write protection function.
 * @details This function set write protection by setting the WP pin state
 * of the CY14B101P, 1-Mbit (128K × 8) Serial (SPI) nvSRAM with Real-Time Clock
 * on the nvSRAM 4 click. 
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] en_wp : 
 *         @li @c 0 ( NVSRAM4_WP_ENABLE ) - Store operations,
 *         @li @c 1 ( NVSRAM4_WP_DISABLE )- Resume the serial communication.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram4_hw_write_protection ( nvsram4_t *ctx, uint8_t en_wp );

#ifdef __cplusplus
}
#endif
#endif // NVSRAM4_H

/*! @} */ // nvsram4

// ------------------------------------------------------------------------ END

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
 * @file lightranger14.h
 * @brief This file contains API for LightRanger 14 Click Driver.
 */

#ifndef LIGHTRANGER14_H
#define LIGHTRANGER14_H

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
 * @addtogroup lightranger14 LightRanger 14 Click Driver
 * @brief API for configuring and manipulating LightRanger 14 Click driver.
 * @{
 */

/**
 * @defgroup lightranger14_reg LightRanger 14 Registers List
 * @brief List of registers of LightRanger 14 Click driver.
 */

/**
 * @addtogroup lightranger14_reg
 * @{
 */

/**
 * @brief LightRanger 14 register list.
 * @details Specified register list of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_REG_APP_ID                                0x00
#define LIGHTRANGER14_REG_MAJOR                                 0x01
#define LIGHTRANGER14_REG_MINOR                                 0x02
#define LIGHTRANGER14_REG_CMD_STAT                              0x08
#define LIGHTRANGER14_REG_BL_CMD_STAT                           0x08
#define LIGHTRANGER14_REG_BL_PAYLOAD                            0x09
#define LIGHTRANGER14_REG_BL_ADDRESS0                           0x0A
#define LIGHTRANGER14_REG_BL_ADDRESS1                           0x0B
#define LIGHTRANGER14_REG_BL_ADDRESS2                           0x0C
#define LIGHTRANGER14_REG_BL_ADDRESS3                           0x0D
#define LIGHTRANGER14_REG_BL_WORD_SIZE0                         0x0E
#define LIGHTRANGER14_REG_BL_WORD_SIZE1                         0x0F
#define LIGHTRANGER14_REG_PREV_CMD                              0x09
#define LIGHTRANGER14_REG_GPIO_VALUE                            0x10
#define LIGHTRANGER14_REG_LIVE_BEAT_0                           0x1A
#define LIGHTRANGER14_REG_LIVE_BEAT_1                           0x1B
#define LIGHTRANGER14_REG_SERIAL_NUM_0                          0x1C
#define LIGHTRANGER14_REG_SERIAL_NUM_1                          0x1D
#define LIGHTRANGER14_REG_SERIAL_NUM_2                          0x1E
#define LIGHTRANGER14_REG_SERIAL_NUM_3                          0x1F
#define LIGHTRANGER14_REG_CID_RID                               0x20
#define LIGHTRANGER14_REG_PAYLOAD                               0x21
#define LIGHTRANGER14_REG_I2C_DEVADDR                           0xE0
#define LIGHTRANGER14_REG_INT_STATUS                            0xE1
#define LIGHTRANGER14_REG_INT_ENAB                              0xE2
#define LIGHTRANGER14_REG_ID                                    0xE3
#define LIGHTRANGER14_REG_REVID                                 0xE4
#define LIGHTRANGER14_REG_INTERFACE                             0xE9
#define LIGHTRANGER14_REG_GPIOO1CFG                             0xF1
#define LIGHTRANGER14_REG_GPIO23CFG                             0xF2
#define LIGHTRANGER14_REG_GPIO45CFG                             0xF3
#define LIGHTRANGER14_REG_GPIO6CFG                              0xF4
#define LIGHTRANGER14_REG_RESET                                 0xF7
#define LIGHTRANGER14_REG_ENABLE                                0xF8
#define LIGHTRANGER14_REG_FIFOSTATUS                            0xFA
#define LIGHTRANGER14_REG_SYSTICK_0                             0xFB
#define LIGHTRANGER14_REG_SYSTICK_1                             0xFC
#define LIGHTRANGER14_REG_SYSTICK_2                             0xFD
#define LIGHTRANGER14_REG_SYSTICK_3                             0xFE
#define LIGHTRANGER14_REG_FIFO                                  0xFF

/**
 * @brief LightRanger 14 configuration registers list.
 * @details Specified configuration registers list of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_CFG_PERIOD_MS_LSB                         0x22
#define LIGHTRANGER14_CFG_PERIOD_MS_MSB                         0x23
#define LIGHTRANGER14_CFG_KILO_ITERATIONS_LSB                   0x24
#define LIGHTRANGER14_CFG_KILO_ITERATIONS_MSB                   0x25
#define LIGHTRANGER14_CFG_FP_MODE                               0x26
#define LIGHTRANGER14_CFG_SPAD_SELECT                           0x27
#define LIGHTRANGER14_CFG_REF_SPAD_SELECT                       0x28
#define LIGHTRANGER14_CFG_SPAD_DEADTIME                         0x29
#define LIGHTRANGER14_CFG_RESULT_FORMAT                         0x2A
#define LIGHTRANGER14_CFG_DUMP_HISTOGRAMS                       0x2B
#define LIGHTRANGER14_CFG_POWER_MODES                           0x2E
#define LIGHTRANGER14_CFG_VCSEL_ON                              0x30
#define LIGHTRANGER14_CFG_DITHER                                0x31
#define LIGHTRANGER14_CFG_VCDRV                                 0x32
#define LIGHTRANGER14_CFG_VCDRV_2                               0x33
#define LIGHTRANGER14_CFG_VCDRV_3                               0x34
#define LIGHTRANGER14_CFG_VCSEL_PERIOD_200PS_LSB                0x36
#define LIGHTRANGER14_CFG_VCSEL_PERIOD_200PS_MSB                0x37
#define LIGHTRANGER14_CFG_VCDRV_OFFSET_200PS_LSB                0x38
#define LIGHTRANGER14_CFG_VCDRV_OFFSET_200PS_MSB                0x39
#define LIGHTRANGER14_CFG_VCDRV_CP                              0x3A
#define LIGHTRANGER14_CFG_HISTOGRAM_BINS_LSB                    0x40
#define LIGHTRANGER14_CFG_HISTOGRAM_BINS_MSB                    0x41
#define LIGHTRANGER14_CFG_BIN_SHIFT                             0x42
#define LIGHTRANGER14_CFG_REF_BIN_SHIFT                         0x43
#define LIGHTRANGER14_CFG_TDC_OFFSET_200PS_LSB                  0x44
#define LIGHTRANGER14_CFG_TDC_OFFSET_200PS_MSB                  0x45
#define LIGHTRANGER14_CFG_TDC_PRE_PERIODS_LSB                   0x46
#define LIGHTRANGER14_CFG_TDC_PRE_PERIODS_MSB                   0x47
#define LIGHTRANGER14_CFG_HV_CP                                 0x48
#define LIGHTRANGER14_CFG_SR_KILO_ITERATIONS_LSB                0x4A
#define LIGHTRANGER14_CFG_SR_KILO_ITERATIONS_MSB                0x4B
#define LIGHTRANGER14_CFG_ENABLE_DUAL_MODE                      0x4C
#define LIGHTRANGER14_CFG_ALG_PEAK_BINS                         0x50
#define LIGHTRANGER14_CFG_ALG_REF_PEAK_BINS                     0x51
#define LIGHTRANGER14_CFG_ALG_DISTANCE                          0x52
#define LIGHTRANGER14_CFG_ALG_CONFIDENCE_THRESHOLD              0x53
#define LIGHTRANGER14_CFG_ALG_HW_PEAK_START                     0x57
#define LIGHTRANGER14_CFG_ALG_MIN_DISTANCE_LSB                  0x58
#define LIGHTRANGER14_CFG_ALG_MIN_DISTANCE_MSB                  0x59
#define LIGHTRANGER14_CFG_ALG_CALIBRATION                       0x5F
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_0                       0x60
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_1                       0x61
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_2                       0x62
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_3                       0x63
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_4                       0x64
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_5                       0x65
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_6                       0x66
#define LIGHTRANGER14_CFG_INT_ZONE_MASK_7                       0x67
#define LIGHTRANGER14_CFG_INT_THRESHOLD_LOW_LSB                 0x68
#define LIGHTRANGER14_CFG_INT_THRESHOLD_LOW_MSB                 0x69
#define LIGHTRANGER14_CFG_INT_THRESHOLD_HIGH_LSB                0x6A
#define LIGHTRANGER14_CFG_INT_THRESHOLD_HIGH_MSB                0x6B
#define LIGHTRANGER14_CFG_INT_PERSISTANCE                       0x6C
#define LIGHTRANGER14_CFG_POST_PROCESSING                       0x6D
#define LIGHTRANGER14_CFG_CROP_TOP_X                            0x70
#define LIGHTRANGER14_CFG_CROP_TOP_Y                            0x71
#define LIGHTRANGER14_CFG_CROP_BOTTOM_X                         0x72
#define LIGHTRANGER14_CFG_CROP_BOTTOM_Y                         0x73
#define LIGHTRANGER14_CFG_INFO_FOV_CORR                         0x78
#define LIGHTRANGER14_CFG_GPIO_0                                0x80
#define LIGHTRANGER14_CFG_GPIO_1                                0x81
#define LIGHTRANGER14_CFG_GPIO_2                                0x82
#define LIGHTRANGER14_CFG_GPIO_3                                0x83
#define LIGHTRANGER14_CFG_GPIO_4                                0x84
#define LIGHTRANGER14_CFG_GPIO_5                                0x85
#define LIGHTRANGER14_CFG_GPIO_6                                0x86
#define LIGHTRANGER14_CFG_GPIO                                  0x87
#define LIGHTRANGER14_CFG_I2C_ADDRESS                           0x90

/*! @} */ // lightranger14_reg

/**
 * @defgroup lightranger14_set LightRanger 14 Registers Settings
 * @brief Settings for registers of LightRanger 14 Click driver.
 */

/**
 * @addtogroup lightranger14_set
 * @{
 */

/**
 * @brief LightRanger 14 APP_ID register setting.
 * @details Specified setting for APP_ID register of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_APP_ID_RAM                                0x01
#define LIGHTRANGER14_APP_ID_BOOTLOADER                         0x80

/**
 * @brief LightRanger 14 CMD_STAT register setting.
 * @details Specified setting for CMD_STAT register of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_CMD_APP_MEASURE                           0x10
#define LIGHTRANGER14_CMD_APP_CLEAR_STATUS                      0x11
#define LIGHTRANGER14_CMD_APP_WRITE_PAGE_AND_MEASURE            0x14
#define LIGHTRANGER14_CMD_APP_WRITE_PAGE                        0x15
#define LIGHTRANGER14_CMD_APP_LOAD_CONFIG_PAGE                  0x16
#define LIGHTRANGER14_CMD_APP_OSC_TUNE_UP                       0x1E
#define LIGHTRANGER14_CMD_APP_OSC_TUNE_DOWN                     0x1F
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_8X8                      0x40
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_8X8_LONG_RANGE           0x41
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_8X8_HIGH_ACCURACY        0x42
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_16X16                    0x43
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_16X16_HIGH_ACCURACY      0x44
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_32X32                    0x45
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_32X32_HIGH_ACCURACY      0x46
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_48X32                    0x47
#define LIGHTRANGER14_CMD_APP_LOAD_CFG_48X32_HIGH_ACCURACY      0x48
#define LIGHTRANGER14_CMD_APP_STOP                              0xFF
#define LIGHTRANGER14_CMD_STAT_APP_OK                           0x00
#define LIGHTRANGER14_CMD_STAT_APP_ACCEPTED                     0x01
#define LIGHTRANGER14_CMD_STAT_APP_ERR_CONFIG                   0x02
#define LIGHTRANGER14_CMD_STAT_APP_ERR_APPLICATION              0x03
#define LIGHTRANGER14_CMD_STAT_APP_ERR_CONFIG_RESULT_SIZE       0x04
#define LIGHTRANGER14_CMD_STAT_APP_ERR_CONFIG_VCSEL             0x05
#define LIGHTRANGER14_CMD_STAT_APP_ERR_WAKEUP_TIMED             0x06
#define LIGHTRANGER14_CMD_STAT_APP_ERR_RESET_UNEXPECTED         0x07
#define LIGHTRANGER14_CMD_STAT_APP_ERR_UNKNOWN_CMD              0x08
#define LIGHTRANGER14_CMD_STAT_APP_ERR_UNKNOWN_CID              0x09
#define LIGHTRANGER14_CMD_STAT_APP_ERR_STOP                     0x0A
#define LIGHTRANGER14_CMD_STAT_APP_ERR_OSC_TUNE                 0x0E
#define LIGHTRANGER14_CMD_BL_START_RAM_APP                      0x16
#define LIGHTRANGER14_CMD_BL_SPI_OFF                            0x20
#define LIGHTRANGER14_CMD_BL_I2C_OFF                            0x22
#define LIGHTRANGER14_CMD_BL_W_FIFO_BOTH                        0x45
#define LIGHTRANGER14_CMD_STAT_BL_READY                         0x00
#define LIGHTRANGER14_CMD_STAT_BL_ERR_PARAM                     0x01
#define LIGHTRANGER14_CMD_STAT_BL_ERR_ADDR                      0x02
#define LIGHTRANGER14_CMD_STAT_BL_ERR_SIZE                      0x03
#define LIGHTRANGER14_CMD_STAT_BL_ERR_FIFO                      0x04

/**
 * @brief LightRanger 14 CID_RID register setting.
 * @details Specified setting for CID_RID register of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_CID_RID_CID_CONFIG                        0x16
#define LIGHTRANGER14_CID_RID_RID_REF_SPAD_FRAME                0x30
#define LIGHTRANGER14_CID_RID_CID_CFG_8X8                       0x40
#define LIGHTRANGER14_CID_RID_CID_CFG_8X8_LONG_RANGE            0x41
#define LIGHTRANGER14_CID_RID_CID_CFG_8X8_HIGH_ACCURACY         0x42
#define LIGHTRANGER14_CID_RID_CID_CFG_16X16                     0x43
#define LIGHTRANGER14_CID_RID_CID_CFG_16X16_HIGH_ACCURACY       0x44
#define LIGHTRANGER14_CID_RID_CID_CFG_32X32                     0x45
#define LIGHTRANGER14_CID_RID_CID_CFG_32X32_HIGH_ACCURACY       0x46
#define LIGHTRANGER14_CID_RID_CID_CFG_48X32                     0x47
#define LIGHTRANGER14_CID_RID_CID_CFG_48X32_HIGH_ACCURACY       0x48

/**
 * @brief LightRanger 14 INT_ENAB register setting.
 * @details Specified setting for INT_ENAB register of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_INT_ENAB_HISTOGRAM                        0x02
#define LIGHTRANGER14_INT_ENAB_RESULTS                          0x01

/**
 * @brief LightRanger 14 ID register setting.
 * @details Specified setting for ID register of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_CHIP_ID                                   0x9E

/**
 * @brief LightRanger 14 ENABLE register setting.
 * @details Specified setting for ENABLE register of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_ENABLE_CPU_READY                          0x80
#define LIGHTRANGER14_ENABLE_POWERUP_SEL_BOOTLOADER             0x00
#define LIGHTRANGER14_ENABLE_POWERUP_SEL_FORCE_BOOTLOADER       0x10
#define LIGHTRANGER14_ENABLE_POWERUP_SEL_RAM                    0x20
#define LIGHTRANGER14_ENABLE_POWERUP_SEL_MASK                   0x70
#define LIGHTRANGER14_ENABLE_POFF                               0x08
#define LIGHTRANGER14_ENABLE_PON                                0x04
#define LIGHTRANGER14_ENABLE_TIMED_STANDBY_MODE                 0x02
#define LIGHTRANGER14_ENABLE_STANDBY_MODE                       0x01

/**
 * @brief LightRanger 14 frame setting.
 * @details Specified setting for status of LightRanger 14 Click driver.
 */
#define LIGHRANGER14_FRAME_PREHEADER_SIZE                       5
#define LIGHRANGER14_FRAME_HEADER_SIZE                          16
#define LIGHRANGER14_FRAME_FOOTER_SIZE                          12
#define LIGHRANGER14_FRAME_ID_ID_RESULT                         0x10
#define LIGHRANGER14_FRAME_ID_ID_HISTOGRAM                      0x20
#define LIGHRANGER14_FRAME_ID_ID_MASK                           0xF0
#define LIGHRANGER14_FRAME_ID_FOCAL_FP8X8A                      0x00
#define LIGHRANGER14_FRAME_ID_FOCAL_FP8X8B                      0x01
#define LIGHRANGER14_FRAME_ID_FOCAL_FP16X16                     0x02
#define LIGHRANGER14_FRAME_ID_FOCAL_FP32X32                     0x03
#define LIGHRANGER14_FRAME_ID_FOCAL_FP32X32S                    0x04
#define LIGHRANGER14_FRAME_ID_FOCAL_FP48X32                     0x05
#define LIGHRANGER14_FRAME_ID_FOCAL_MASK                        0x0F
#define LIGHRANGER14_FRAME_STATUS_VALID                         0x01
#define LIGHRANGER14_FRAME_STATUS_WARNING                       0x08
#define LIGHRANGER14_FRAME_STATUS_INFO                          0x10
#define LIGHRANGER14_FRAME_STATUS_LIMIT                         0x20
#define LIGHRANGER14_FRAME_STATUS_ABORTED                       0xC0
#define LIGHRANGER14_FRAME_EOF_MARKER                           0xE0F7

/**
 * @brief LightRanger 14 confidence setting.
 * @details Specified setting for confidence of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_CONFIDENCE_THRESHOLD                      6
#define LIGHTRANGER14_CONFIDENCE_BREAKPOINT                     40
#define LIGHTRANGER14_CONFIDENCE_EXP_GROWTH_RATE                1.053676

/**
 * @brief LightRanger 14 measurement period setting.
 * @details Specified setting for measurement period of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_MEASUREMENT_PERIOD_MS                     500

/**
 * @brief LightRanger 14 timeout setting.
 * @details Specified setting for timeout of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_TIMEOUT_MS                                1000

/**
 * @brief LightRanger 14 max read/write buffer size setting.
 * @details Specified setting for max read/write buffer size of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_MAX_RW_BUF_SIZE                           128

/**
 * @brief LightRanger 14 load config setting.
 * @details Specified setting for load config of LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_DEFAULT_LOAD_CONFIG                       LIGHTRANGER14_CMD_APP_LOAD_CFG_8X8
#define LIGHTRANGER14_MAP_WIDTH                                 8
#define LIGHTRANGER14_MAP_HEIGHT                                8
#define LIGHTRANGER14_PIXEL_SIZE                                3
#if ( LIGHTRANGER14_MAP_HEIGHT > 16 )
    #define LIGHTRANGER14_FRAME_PAYLOAD_SIZE                    ( LIGHTRANGER14_MAP_WIDTH * \
                                                                  ( LIGHTRANGER14_MAP_HEIGHT / 2 ) * \
                                                                  LIGHTRANGER14_PIXEL_SIZE )
#else
    #define LIGHTRANGER14_FRAME_PAYLOAD_SIZE                    ( LIGHTRANGER14_MAP_WIDTH * \
                                                                  LIGHTRANGER14_MAP_HEIGHT * \
                                                                  LIGHTRANGER14_PIXEL_SIZE )
#endif

/**
 * @brief LightRanger 14 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 14 Click driver.
 */
#define LIGHTRANGER14_DEVICE_ADDRESS                            0x41

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b lightranger14_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LIGHTRANGER14_SET_DATA_SAMPLE_EDGE                      SET_SPI_DATA_SAMPLE_EDGE
#define LIGHTRANGER14_SET_DATA_SAMPLE_MIDDLE                    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // lightranger14_set

/**
 * @defgroup lightranger14_map LightRanger 14 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 14 Click driver.
 */

/**
 * @addtogroup lightranger14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 14 Click to the selected MikroBUS.
 */
#define LIGHTRANGER14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger14_map
/*! @} */ // lightranger14

/**
 * @brief LightRanger 14 Click driver selector.
 * @details Selects target driver interface of LightRanger 14 Click driver.
 */
typedef enum
{
    LIGHTRANGER14_DRV_SEL_SPI,          /**< SPI driver descriptor. */
    LIGHTRANGER14_DRV_SEL_I2C           /**< I2C driver descriptor. */

} lightranger14_drv_t;

/**
 * @brief LightRanger 14 Click driver interface.
 * @details Definition of driver interface of LightRanger 14 Click driver.
 */
struct lightranger14_s;
typedef err_t ( *lightranger14_master_io_t )( struct lightranger14_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief LightRanger 14 Click device info object.
 * @details Device info object definition of LightRanger 14 Click driver.
 */
typedef struct
{
    uint32_t serial_num;                /**< Serial number of device. */
    uint8_t app_ver[ 4 ];               /**< Application version number (APP_ID, MAJOR, MINOR, PATCH). */
    uint8_t chip_ver[ 2 ];              /**< Chip version (ID, REVID). */

} lightranger14_info_t;

/**
 * @brief LightRanger 14 Click device results object.
 * @details Device results object definition of LightRanger 14 Click driver.
 */
typedef struct
{
    // Preheader
    uint8_t fifostatus;                 /**< FIFO status data. */
    uint32_t systick;                   /**< 32-bit systick running from 125kHz clock. */

    // Frame header
    uint8_t frame_id;                   /**< Frame ID: 0x10 for result frame, 0x20 for histogram frame. */
    uint8_t res_format;                 /**< LIGHTRANGER14_CFG_RESULT_FORMAT register value */
    uint16_t payload_len;               /**< Payload length, excluding frame header and footer bytes. */
    uint32_t frame_num;                 /**< Frame number. */
    uint8_t temperature[ 3 ];           /**< Temperature [degrees Celsius] from the three temperature sensors. */
    uint8_t bdv;                        /**< BDV value (Break Down Voltage), shall be ignored by user. */
    uint16_t ref_peak_first;            /**< Optical reference peak from 1st measurement, shall be ignored by user. */
    uint16_t ref_peak_last;             /**< Optical reference peak from last measurement, shall be ignored by user. */

    // Frame data
    uint8_t *payload;                   /**< Pointer to buffer where frame data is being stored. */

    // Frame footer
    uint32_t t_first;                   /**< Internal timestamp when first integration started. */
    uint32_t t_last;                    /**< Internal timestamp when last integration started. */
    uint8_t frame_status;               /**< Frame status: LIGHRANGER14_FRAME_STATUS_VALID for frame valid. */
    uint16_t eof_marker;                /**< LIGHRANGER14_FRAME_EOF_MARKER end of frame marker. */

} lightranger14_results_t;

/**
 * @brief LightRanger 14 Click context object.
 * @details Context object definition of LightRanger 14 Click driver.
 */
typedef struct lightranger14_s
{
    digital_out_t en;                   /**< Enable pin (active high). */

    digital_in_t int_pin;               /**< Interrupt pin (active low). */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    lightranger14_drv_t drv_sel;        /**< Master driver interface selector. */

    lightranger14_master_io_t write_f;  /**< Master write function. */
    lightranger14_master_io_t read_f;   /**< Master read function. */

    lightranger14_info_t info;          /**< Device info. */
    lightranger14_results_t results;    /**< Device measurement results. */

} lightranger14_t;

/**
 * @brief LightRanger 14 Click configuration object.
 * @details Configuration object definition of LightRanger 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */

    pin_name_t en;                      /**< Enable pin (active high). */
    pin_name_t int_pin;                 /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    lightranger14_drv_t drv_sel;        /**< Master driver interface selector. */

} lightranger14_cfg_t;

/**
 * @brief LightRanger 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTRANGER14_OK = 0,
    LIGHTRANGER14_ERROR = -1,
    LIGHTRANGER14_ERROR_TIMEOUT = -2

} lightranger14_return_value_t;

/*!
 * @addtogroup lightranger14 LightRanger 14 Click Driver
 * @brief API for configuring and manipulating LightRanger 14 Click driver.
 * @{
 */

/**
 * @brief LightRanger 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger14_cfg_setup ( lightranger14_cfg_t *cfg );

/**
 * @brief LightRanger 14 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger14_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #lightranger14_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void lightranger14_drv_interface_sel ( lightranger14_cfg_t *cfg, lightranger14_drv_t drv_sel );

/**
 * @brief LightRanger 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger14_init ( lightranger14_t *ctx, lightranger14_cfg_t *cfg );

/**
 * @brief LightRanger 14 default configuration function.
 * @details This function executes the default configuration procedure which includes:
 * firmware download, communication check, configuration page load, measurement period setup,
 * writing config page, enabling interrupts, starting measurement, and clearing interrupts.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_default_cfg ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_write_reg ( lightranger14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LightRanger 14 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_read_reg ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LightRanger 14 write multiple registers function.
 * @details This function writes multiple bytes of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_write_regs ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 14 read multiple registers function.
 * @details This function reads multiple bytes of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_read_regs ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LightRanger 14 check register function.
 * @details This function checks whether a register contains the expected value within timeout.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] exp_data : Expected data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * @note None.
 */
err_t lightranger14_check_reg ( lightranger14_t *ctx, uint8_t reg, uint8_t exp_data );

/**
 * @brief LightRanger 14 write command function.
 * @details This function writes a command to the command register and waits for the expected response.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] cmd : Command to be written.
 * @param[in] exp_resp : Expected response value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * @note None.
 */
err_t lightranger14_write_cmd ( lightranger14_t *ctx, uint8_t cmd, uint8_t exp_resp );

/**
 * @brief LightRanger 14 enable device function.
 * @details This function sets the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger14_enable_device ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 disable device function.
 * @details This function sets the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger14_disable_device ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 get INT pin state function.
 * @details This function returns the current logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lightranger14_get_int_pin ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 check communication function.
 * @details This function checks the communication with the device by reading chip information,
 * application version, serial number, and chip ID.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_check_com ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 power up function.
 * @details This function powers up the device by enabling the PON bit and waiting until CPU is ready.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * @note None.
 */
err_t lightranger14_power_up ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 power down function.
 * @details This function powers down the device by setting the POFF bit if the CPU is active.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_power_down ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 firmware download function.
 * @details This function downloads firmware to the device RAM and starts the application.
 * It handles bootloader communication, sets FIFO, and transfers the firmware image.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * @note None.
 */
err_t lightranger14_download_fw ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 clear interrupts function.
 * @details This function clears pending interrupts by reading and writing back the interrupt status register.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_clear_interrupts ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 load configuration page function.
 * @details This function loads the configuration page from the device memory and verifies the configuration ID.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_load_cfg_page ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 write configuration page function.
 * @details This function writes the current configuration page into the device memory.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_write_cfg_page ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 set measurement period function.
 * @details This function sets the measurement period in milliseconds by writing to configuration registers.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] period_ms : Measurement period in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_set_meas_period ( lightranger14_t *ctx, uint16_t period_ms );

/**
 * @brief LightRanger 14 start measurement function.
 * @details This function starts measurement by writing the measure command to the command register.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_start_measurement ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 stop measurement function.
 * @details This function stops measurement by writing the stop command to the command register.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_stop_measurement ( lightranger14_t *ctx );

/**
 * @brief LightRanger 14 read results function.
 * @details This function reads the measurement results frame including header, payload, and footer.
 * The results are stored in the driver context structure.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[out] frame_data : Pointer to buffer for payload data.
 * @param[in] len : Buffer size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t lightranger14_read_results ( lightranger14_t *ctx, uint8_t *frame_data, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER14_H

/*! @} */ // lightranger14

// ------------------------------------------------------------------------ END

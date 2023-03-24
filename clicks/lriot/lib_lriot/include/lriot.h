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
 * @file lriot.h
 * @brief This file contains API for LR IoT Click Driver.
 */

#ifndef LRIOT_H
#define LRIOT_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "common/lr1110_bootloader_types.h"
#include "common/lr1110_types.h"
#include "transceiver/lr1110_crypto_engine_types.h"
#include "transceiver/lr1110_gnss_types.h"
#include "transceiver/lr1110_radio_types.h"
#include "transceiver/lr1110_system_types.h"
#include "transceiver/lr1110_wifi_types.h"
#include "modem/lr1110_modem_lorawan_types.h"
#include "modem/lr1110_modem_wifi_types.h"
#include "modem/lr1110_modem_gnss_types.h"
#include "modem/lr1110_modem_helper_types.h"
#include "modem/lr1110_modem_system_types.h"

/*!
 * @addtogroup lriot LR IoT Click Driver
 * @brief API for configuring and manipulating LR IoT Click driver.
 * @{
 */

/**
 * @defgroup lriot_set LR IoT Registers Settings
 * @brief Settings for registers of LR IoT Click driver.
 */

/**
 * @addtogroup lriot_set
 * @{
 */

/**
 * @brief LR IoT Temperature in Celsius calculation constants.
 * @details Specified constants for Temperature in Celsius calculation of LR IoT Click driver.
 */
#define LRIOT_TEMP_INT_VREF                     1.35
#define LRIOT_TEMP_VOLTAGE_AT_25C               0.7295
#define LRIOT_TEMP_RESOLUTION                   2047.0
#define LRIOT_TEMP_NOMINAL                      25
#define LRIOT_TEMP_SLOPE                        -1.7
#define LRIOT_TEMP_SLOPE_DIVIDEND               1000.0

/**
 * @brief LR IoT default duration for the 32 MHz oscillator to start and stabilize.
 * @details Specified duration for the 32 MHz oscillator to start and stabilize (in 30.52 us steps) of LR IoT Click driver.
 */
#define LRIOT_TCXO_DELAY_2SEC                   0xFFFA

/**
 * @brief LR IoT GNSS scan macros.
 * @details GNSS scan macros of LR IoT Click driver.
 */
#define LRIOT_GNSS_SCAN_MAX_SATELLITES          16
#define LRIOT_GNSS_SCAN_RESULTS_BUF_LEN         256
#define LRIOT_GNSS_SCAN_DISPLAY_ALL             0

/**
 * @brief LR IoT WiFi scan macros.
 * @details WiFi scan macros of LR IoT Click driver.
 */
#define LRIOT_WIFI_SCAN_MAX_RESULTS             12
#define LRIOT_WIFI_SCAN_DISPLAY_ALL             0

/**
 * @brief LR IoT LoRa macros.
 * @details LoRa macros of LR IoT Click driver.
 */
#define LRIOT_LORA_PKT_PAYLOAD_LEN              64
#define LRIOT_LORA_DEFAULT_FREQ                 868100000ul

/**
 * @brief LR IoT update firmware macros.
 * @details Specified macro for updating the module firmware of LR IoT Click driver.
 * @note Change the LRIOT_UPDATE_FIRMWARE macro value to 1 to update the module firmware inside 
 * the @b lriot_default_cfg to default firmware.
 * Check if the target MCU have enough available ROM space for the firmware image (at least 240kB).
 */
#define LRIOT_UPDATE_FIRMWARE                   0

/**
 * @brief LR IoT firmware selector macros.
 * @details Specified firmware selector macros of LR IoT Click driver.
 */
#define LRIOT_TRANSCEIVER_FIRMWARE              0
#define LRIOT_MODEM_FIRMWARE                    1
#define LRIOT_FIRMWARE_SELECTOR                 LRIOT_TRANSCEIVER_FIRMWARE

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b lriot_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LRIOT_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define LRIOT_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // lriot_set

/**
 * @defgroup lriot_map LR IoT MikroBUS Map
 * @brief MikroBUS pin mapping of LR IoT Click driver.
 */

/**
 * @addtogroup lriot_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR IoT Click to the selected MikroBUS.
 */
#define LRIOT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.bsy  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lriot_map
/*! @} */ // lriot

/**
 * @brief LR IoT WiFi settings object.
 * @details WiFi settings object definition of LR IoT Click driver.
 */
typedef struct 
{
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    lr1110_wifi_signal_type_scan_t  signal_type;
    lr1110_wifi_channel_mask_t      channels;     
    lr1110_wifi_mode_t              scan_mode;
#else
    lr1110_modem_wifi_signal_type_scan_t  signal_type;
    lr1110_modem_wifi_channel_t           channels;     
    lr1110_modem_wifi_mode_t              scan_mode;
    lr1110_modem_wifi_result_format_t     result_format;
#endif
    uint8_t  max_results;
    uint8_t  nb_scan_per_channel;
    uint16_t timeout_in_ms;
    bool     abort_on_timeout;
    
} lriot_wifi_settings_t;

/**
 * @brief LR IoT WiFi Scan results object.
 * @details WiFi Scan results object definition of LR IoT Click driver.
 */
typedef struct 
{
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    lr1110_wifi_extended_full_result_t scan_results[ LRIOT_WIFI_SCAN_MAX_RESULTS ];
    lr1110_wifi_cumulative_timings_t   timings;
#else  
    lr1110_modem_wifi_extended_full_result_t scan_results[ LRIOT_WIFI_SCAN_MAX_RESULTS ];
    lr1110_modem_wifi_cumulative_timings_t   timings;
#endif
    uint8_t num_wifi_results;
    
} lriot_wifi_scan_results_t;

/**
 * @brief LR IoT GNSS Scan results object.
 * @details GNSS Scan results object definition of LR IoT Click driver.
 */
typedef struct 
{
    uint8_t                             num_satellites;
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    lr1110_gnss_detected_satellite_t        satellite_id_cnr_doppler[ LRIOT_GNSS_SCAN_MAX_SATELLITES ];   
#else  
    lr1110_modem_gnss_detected_satellite_t  satellite_id_cnr[ LRIOT_GNSS_SCAN_MAX_SATELLITES ];  
#endif
    uint8_t                             scan_results[ LRIOT_GNSS_SCAN_RESULTS_BUF_LEN ];
    uint16_t                            scan_results_len;
    uint8_t                             destination_id;
    
} lriot_gnss_scan_results_t;

/**
 * @brief LR IoT chip info object.
 * @details Chip info object definition of LR IoT Click driver.
 */
typedef struct 
{
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    lr1110_system_version_t     version;
    lr1110_system_uid_t         uid;
    lr1110_system_join_eui_t    join_eui;
    lr1110_system_pin_t         pin;
#else
    lr1110_modem_version_t      version;
    lr1110_modem_chip_eui_t     chip_eui;
    lr1110_modem_join_eui_t     join_eui;
    lr1110_modem_dev_eui_t      dev_eui;
    uint32_t                    pin;
#endif
    
} lriot_chip_info_t;

/**
 * @brief LR IoT LoRa packet status object.
 * @details LoRa packet status object definition of LR IoT Click driver.
 */
typedef struct
{
    int8_t rssi_pkt_in_dbm;         /**< Average RSSI over last received packet. */
    int8_t snr_pkt_in_db;           /**< SNR estimated on last received packet. */
    int8_t signal_rssi_pkt_in_dbm;  /**< RSSI of last packet latched after. */
    
} lriot_lora_packet_status_t;

/**
 * @brief LR IoT Click context object.
 * @details Context object definition of LR IoT Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;             /**< Reset pin. */

    // Input pins
    digital_in_t   bsy;             /**< Busy indicator pin. */
    digital_in_t   int_pin;         /**< IRQ pin. */
    
    pin_name_t     bsy_pin_name;    /**< Busy indicator pin name for configuring it to I/O after init. */

    // Modules
    spi_master_t   spi;             /**< SPI driver object. */

    pin_name_t     chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    
    lriot_wifi_settings_t wifi_settings; /**< WiFi settings object. */

} lriot_t;

/**
 * @brief LR IoT Click configuration object.
 * @details Configuration object definition of LR IoT Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;                /**< Reset pin. */
    pin_name_t  bsy;                /**< Busy indicator pin. */
    pin_name_t  int_pin;            /**< IRQ pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} lriot_cfg_t;

/**
 * @brief LR IoT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LRIOT_OK = 0,
    LRIOT_ERROR = -1

} lriot_return_value_t;

/*!
 * @addtogroup lriot LR IoT Click Driver
 * @brief API for configuring and manipulating LR IoT Click driver.
 * @{
 */

/**
 * @brief LR IoT configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lriot_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lriot_cfg_setup ( lriot_cfg_t *cfg );

/**
 * @brief LR IoT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lriot_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lriot_init ( lriot_t *ctx, lriot_cfg_t *cfg );

/**
 * @brief LR IoT default configuration function.
 * @details This function executes a default configuration of LR IoT
 * click board.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lriot_default_cfg ( lriot_t *ctx );

/**
 * @brief LR IoT set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lriot_set_rst_pin ( lriot_t *ctx, uint8_t state );

/**
 * @brief LR IoT get busy pin function.
 * @details This function returns the BUSY pin logic state.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lriot_get_busy_pin ( lriot_t *ctx );

/**
 * @brief LR IoT get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lriot_get_int_pin ( lriot_t *ctx );

/**
 * @brief LR IoT get chip info function.
 * @details This function reads the chip firmware information.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[out] info : Chip information object.
 * See #lriot_chip_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lriot_get_chip_info ( lriot_t *ctx, lriot_chip_info_t *info );

#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
/**
 * @brief LR IoT get temperature function.
 * @details This function reads the chip internal temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[out] temperature : Chip internal temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function is supported in transceiver firmware only.
 */
err_t lriot_get_temperature ( lriot_t *ctx, float *temperature );

/**
 * @brief LR IoT send lora message function.
 * @details This function sends a LoRa message to the receiver.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[in] message : A message buffer to send. Should be of @b LRIOT_LORA_PKT_PAYLOAD_LEN size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function is supported in transceiver firmware only.
 */
err_t lriot_send_lora_message ( lriot_t *ctx, uint8_t *message );

/**
 * @brief LR IoT read lora message function.
 * @details This function waits for a LoRa packet to arrive and reads its payload message and packet status.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[out] pkt_status : A received LoRa packet status.
 * See #lriot_lora_packet_status_t object definition for detailed explanation.
 * @param[out] message : A received LoRa message buffer. Limited to @b LRIOT_LORA_PKT_PAYLOAD_LEN size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function is supported in transceiver firmware only.
 */
err_t lriot_read_lora_message ( lriot_t *ctx, lriot_lora_packet_status_t *pkt_status, uint8_t *message );
#endif

/**
 * @brief LR IoT get wifi scan results function.
 * @details This function performs a WiFi scanning and reads the results.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[out] results : WiFi scan results object.
 * See #lriot_wifi_scan_results_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lriot_get_wifi_scan_results ( lriot_t *ctx, lriot_wifi_scan_results_t *results );

/**
 * @brief LR IoT get gnss scan results function.
 * @details This function performs a GNSS scanning and reads the results.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @param[out] results : GNSS scan results object.
 * See #lriot_gnss_scan_results_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lriot_get_gnss_scan_results ( lriot_t *ctx, lriot_gnss_scan_results_t *results );

/**
 * @brief LR IoT update firmware function.
 * @details This function performs a firmware update depending on the @b LRIOT_UPDATE_FIRMWARE and 
 * @b LRIOT_FIRMWARE_SELECTOR macro definitions.
 * @param[in] ctx : Click context object.
 * See #lriot_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lriot_update_firmware ( lriot_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LRIOT_H

/*! @} */ // lriot

// ------------------------------------------------------------------------ END

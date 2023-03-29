/*!
 * @file main.c
 * @brief LR IoT Click example
 *
 * # Description
 * This example demonstrates the use of LR IoT click board by reading a GNSS and WiFi 
 * scanning results and displaying it on the USB UART. In the case of a tranceive firmware
 * the communication between two devices over LoRa will be demonstrated as well.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the click default configuration, and after that reads
 * and displays the chip's firmware information. In the case you need to update or change the default
 * firmware refer to the @b LRIOT_UPDATE_FIRMWARE and @b LRIOT_FIRMWARE_SELECTOR macro definition.
 *
 * ## Application Task
 * There are 3 types of the example: 
 * 1. Modem firmware: reads a GNSS and WiFi scanning results and displays them on the USB UART.
 * 2. Transcever firmware (application mode transmitter ): reads a GNSS and WiFi scanning results
 *    as well as the chip internal temperature and sends specific LoRa messages containing that information
 *    to the LoRa receiver.
 * 3. Transcever firmware (application mode receiver): reads all incoming LoRa packets and displays them
 *    on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */
#include "board.h"
#include "log.h"
#include "lriot.h"
#include "conversions.h"

static lriot_t lriot;
static log_t logger;

#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER
#endif

/**
 * @brief LR IoT display gnss scan results function.
 * @details This function parses a GNSS scan results object and displays it on the USB UART.
 * @param[in] results : GNSS scan results object.
 * See #lriot_gnss_scan_results_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void lriot_display_gnss_scan_results ( lriot_gnss_scan_results_t results );

/**
 * @brief LR IoT display wifi scan results function.
 * @details This function parses a WiFi scan results object and displays it on the USB UART.
 * @param[in] results : WiFi scan results object.
 * See #lriot_wifi_scan_results_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void lriot_display_wifi_scan_results ( lriot_wifi_scan_results_t results );

/**
 * @brief LR IoT display chip info function.
 * @details This function parses a chip firmware information object and displays it on the USB UART.
 * @param[in] info : Chip information object.
 * See #lriot_chip_info_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void lriot_display_chip_info ( lriot_chip_info_t info );

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    lriot_cfg_t lriot_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    lriot_cfg_setup( &lriot_cfg );
    LRIOT_MAP_MIKROBUS( lriot_cfg, MIKROBUS_1 );
    
    if ( SPI_MASTER_ERROR == lriot_init( &lriot, &lriot_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( LRIOT_ERROR == lriot_default_cfg ( &lriot ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    lriot_chip_info_t chip_info;
    if ( LRIOT_OK == lriot_get_chip_info ( &lriot, &chip_info ) ) 
    {
        lriot_display_chip_info ( chip_info );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    uint8_t lora_buffer[ LRIOT_LORA_PKT_PAYLOAD_LEN ] = { 0 };
    #ifdef DEMO_APP_TRANSMITTER
        lriot_gnss_scan_results_t gnss_results = { 0 };
        lriot_wifi_scan_results_t wifi_results = { 0 };
        uint8_t tmp_buf[ 30 ] = { 0 };
        float temperature = 0;
        
        if ( LRIOT_OK == lriot_get_gnss_scan_results ( &lriot, &gnss_results ) )
        {
            lriot_display_gnss_scan_results ( gnss_results );
        }
        
        memset( lora_buffer, 0, sizeof ( lora_buffer ) );
        strcpy( lora_buffer, "Number of sattelites found is " );
        uint16_to_str ( gnss_results.num_satellites, tmp_buf );
        l_trim ( tmp_buf );
        strcat( lora_buffer, tmp_buf );
        if ( LRIOT_OK == lriot_send_lora_message ( &lriot, lora_buffer ) )
        {
            log_printf( &logger, "Send LoRa message - done\r\n" );
        }
        
        if ( LRIOT_OK == lriot_get_wifi_scan_results ( &lriot, &wifi_results ) )
        {
            lriot_display_wifi_scan_results ( wifi_results );
        }
        memset( lora_buffer, 0, sizeof ( lora_buffer ) );
        strcpy( lora_buffer, "Number of WiFi scan results is " );
        uint16_to_str ( wifi_results.num_wifi_results, tmp_buf );
        l_trim ( tmp_buf );
        strcat( lora_buffer, tmp_buf );
        if ( LRIOT_OK == lriot_send_lora_message ( &lriot, lora_buffer ) )
        {
            log_printf( &logger, "Send LoRa message - done\r\n" );
        }
        
        log_printf ( &logger, "**************************************************************\r\n" );
        if ( LRIOT_OK == lriot_get_temperature ( &lriot, &temperature ) )
        {
            log_printf ( &logger, "Temperature : %.2f degC\r\n", temperature );
        }
        memset( lora_buffer, 0, sizeof ( lora_buffer ) );
        strcpy( lora_buffer, "My temperature is " );
        float_to_str ( temperature, tmp_buf );
        l_trim ( tmp_buf );
        tmp_buf[ 5 ] = 0;
        strcat( lora_buffer, tmp_buf );
        strcat( lora_buffer, " degC" );
        if ( LRIOT_OK == lriot_send_lora_message ( &lriot, lora_buffer ) )
        {
            log_printf( &logger, "Send LoRa message - done\r\n" );
        }
    #else
        lriot_lora_packet_status_t pkt_status;
        if ( LRIOT_OK == lriot_read_lora_message ( &lriot, &pkt_status, lora_buffer ) )
        {
            log_printf ( &logger, "**************************************************************\r\n" );
            log_printf ( &logger, "*                      RECEIVED LORA PACKET                  *\r\n" );
            log_printf ( &logger, "**************************************************************\r\n" );
            log_printf ( &logger, " RSSI        : %d dBm\r\n", ( uint16_t ) pkt_status.rssi_pkt_in_dbm );
            log_printf ( &logger, " Signal RSSI : %d dBm\r\n", ( uint16_t ) pkt_status.signal_rssi_pkt_in_dbm );
            log_printf ( &logger, " SNR         : %d dB\r\n", ( uint16_t ) pkt_status.snr_pkt_in_db );
            log_printf ( &logger, " Message     : \"%s\"\r\n\n", lora_buffer );
        }
    #endif
#else
    lriot_gnss_scan_results_t gnss_results = { 0 };
    lriot_wifi_scan_results_t wifi_results = { 0 };
    
    if ( LRIOT_OK == lriot_get_gnss_scan_results ( &lriot, &gnss_results ) )
    {
        lriot_display_gnss_scan_results ( gnss_results );
    }
    
    if ( LRIOT_OK == lriot_get_wifi_scan_results ( &lriot, &wifi_results ) )
    {
        lriot_display_wifi_scan_results ( wifi_results );
    }
#endif
}

void main ( void )
{
    application_init( );
    
    for ( ; ; )
    {
        application_task( );
    }
}

static void lriot_display_gnss_scan_results ( lriot_gnss_scan_results_t results )
{
    log_printf ( &logger, "**************************************************************\r\n" );
    log_printf ( &logger, "*                      GNSS SCAN RESULTS                     *\r\n" );
    log_printf ( &logger, "**************************************************************\r\n" );
    log_printf ( &logger, "Number of satellites found: %u\r\n", ( uint16_t ) results.num_satellites );
    
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    for ( uint8_t cnt = 0; cnt < results.num_satellites; cnt++ )
    {
        log_printf ( &logger, "{\r\n\tSatellite ID : %u", results.satellite_id_cnr_doppler[ cnt ].satellite_id );
        log_printf ( &logger, "\r\n\tC/N0         : %d dB-Hz", results.satellite_id_cnr_doppler[ cnt ].cnr );
        log_printf ( &logger, "\r\n\tSV doppler   : %d Hz\r\n},\r\n", results.satellite_id_cnr_doppler[ cnt ].doppler );
    }
#else
    for ( uint8_t cnt = 0; cnt < results.num_satellites; cnt++ )
    {
        log_printf ( &logger, "{\r\n\tSatellite ID : %u", results.satellite_id_cnr[ cnt ].satellite_id );
        log_printf ( &logger, "\r\n\tC/N0         : %d dB-Hz\r\n},\r\n", results.satellite_id_cnr[ cnt ].cnr );
    }
#endif
    if ( ( results.scan_results_len > 0 ) && 
         ( LR1110_GNSS_DESTINATION_SOLVER == results.destination_id ) )
    {
        log_printf ( &logger, "NAV message : " );
        for ( uint16_t cnt = 0; cnt < results.scan_results_len; cnt++ )
        {
            log_printf ( &logger, "%.2X", results.scan_results[ cnt ] );
        }
        log_printf ( &logger, "\r\n" );
    }
}

static void lriot_display_wifi_scan_results ( lriot_wifi_scan_results_t results )
{
    log_printf ( &logger, "**************************************************************\r\n" );
    log_printf ( &logger, "*                      WiFi SCAN RESULTS                     *\r\n" );
    log_printf ( &logger, "**************************************************************\r\n" );
    log_printf ( &logger, "Number of WiFi results: %u\r\n", ( uint16_t ) results.num_wifi_results );

    for ( uint8_t i = 0; i < results.num_wifi_results; i++ )
    {
        log_printf ( &logger, "{\r\n\tSSID   : \"%s\",\r\n\tMAC    : \"", results.scan_results[ i ].ssid_bytes );
        for ( uint16_t j = 0; j < LR1110_WIFI_MAC_ADDRESS_LENGTH; j++ )
        {
            log_printf ( &logger, "%.2x", ( uint16_t ) results.scan_results[ i ].mac_address_2[ j ] );
            if ( j < ( LR1110_WIFI_MAC_ADDRESS_LENGTH - 1 ) )
            {
                log_printf ( &logger, ":" );
            }
        }
        log_printf ( &logger, "\",\r\n\tChannel: %u,\r\n", ( int16_t ) results.scan_results[ i ].current_channel );
        log_printf ( &logger, "\tType   : %u,\r\n", ( int16_t ) results.scan_results[ i ].data_rate_info_byte );
        log_printf ( &logger, "\tRSSI   : %d dBm\r\n},\r\n", ( int16_t ) results.scan_results[ i ].rssi );
    }
    log_printf ( &logger, "Scanning time : %d ms\r\n",
                 ( results.timings.demodulation_us + results.timings.rx_capture_us +
                   results.timings.rx_correlation_us + results.timings.rx_detection_us ) / 1000 );
}

static void lriot_display_chip_info ( lriot_chip_info_t info )
{
    log_printf ( &logger, "**************************************************************\r\n");
    log_printf ( &logger, "*                          CHIP INFO                         *\r\n");
    log_printf ( &logger, "**************************************************************\r\n");
    
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    log_printf ( &logger, "HARDWARE   : 0x%.2X\r\n", ( uint16_t ) info.version.hw );
    log_printf ( &logger, "TYPE       : 0x%.2X\r\n", ( uint16_t ) info.version.type );
    log_printf ( &logger, "FIRMWARE   : 0x%.4X\r\n", info.version.fw );
    
    log_printf ( &logger, "UID        : " );
    for ( uint8_t cnt = 0; cnt < ( LR1110_SYSTEM_UID_LENGTH - 1 ); cnt++ )
    {
        log_printf ( &logger, "%.2X-", ( uint16_t ) info.uid[ cnt ] );
    }
    log_printf ( &logger, "%.2X\r\n", ( uint16_t ) info.uid[ LR1110_SYSTEM_UID_LENGTH - 1 ] );
    log_printf ( &logger, "JOIN EUI   : " );
    for ( uint8_t cnt = 0; cnt < ( LR1110_SYSTEM_JOIN_EUI_LENGTH - 1 ); cnt++ )
    {
        log_printf ( &logger, "%.2X-", ( uint16_t ) info.join_eui[ cnt ] );
    }
    log_printf ( &logger, "%.2X\r\n", ( uint16_t ) info.join_eui[ LR1110_SYSTEM_JOIN_EUI_LENGTH - 1 ] );
    log_printf ( &logger, "PIN        : " );
    for ( uint8_t cnt = 0; cnt < LR1110_SYSTEM_PIN_LENGTH; cnt++ )
    {
        log_printf ( &logger, "%.2X", ( uint16_t ) info.pin[ cnt ] );
    }
    log_printf ( &logger, "\r\n\n" );
#else
    log_printf ( &logger, "BOOTLOADER : 0x%.8LX\r\n", info.version.bootloader );
    log_printf ( &logger, "FIRMWARE   : 0x%.8LX\r\n", info.version.firmware );
    log_printf ( &logger, "LORAWAN    : 0x%.4X\r\n", info.version.lorawan );
    
    log_printf ( &logger, "CHIP EUI   : " );
    for ( uint8_t cnt = 0; cnt < ( LR1110_MODEM_CHIP_EUI_LENGTH - 1 ); cnt++ )
    {
        log_printf ( &logger, "%.2X-", ( uint16_t ) info.chip_eui[ cnt ] );
    }
    log_printf ( &logger, "%.2X\r\n", ( uint16_t ) info.chip_eui[ LR1110_MODEM_CHIP_EUI_LENGTH - 1 ] );
    log_printf ( &logger, "DEV EUI    : " );
    for ( uint8_t cnt = 0; cnt < ( LR1110_MODEM_DEV_EUI_LENGTH - 1 ); cnt++ )
    {
        log_printf ( &logger, "%.2X-", ( uint16_t ) info.dev_eui[ cnt ] );
    }
    log_printf ( &logger, "%.2X\r\n", ( uint16_t ) info.dev_eui[ LR1110_MODEM_DEV_EUI_LENGTH - 1 ] );
    log_printf ( &logger, "JOIN EUI   : " );
    for ( uint8_t cnt = 0; cnt < ( LR1110_MODEM_JOIN_EUI_LENGTH - 1 ); cnt++ )
    {
        log_printf ( &logger, "%.2X-", ( uint16_t ) info.join_eui[ cnt ] );
    }
    log_printf ( &logger, "%.2X\r\n", ( uint16_t ) info.join_eui[ LR1110_MODEM_JOIN_EUI_LENGTH - 1 ] );
    log_printf ( &logger, "PIN        : %.8LX\r\n\n", info.pin );
#endif
}

// ------------------------------------------------------------------------ END

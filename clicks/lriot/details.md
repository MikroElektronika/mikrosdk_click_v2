
---
# LR IoT click

> LR IoT Click is a compact add-on board that contains a long-range LoRa transceiver. This board features Semtech Corporation’s LR1110, an ultra-low power platform integrating a LoRa® transceiver, multi-constellation GNSS, and passive WiFi AP MAC address scanner. Alongside its sub-GHz capabilities, the LR1110 also has a multi-band front-end capable of receiving 802.11b/g/n WiFi Access Point MAC addresses and GNSS (GPS, BeiDou, geostationary) satellite raw data befitting geo-positioning purposes. The acquired information is then transmitted using an LPWAN network to a geolocation server, which analyzes it and correlates the position with data from a geolocation database, enabling a unique balance between low power and performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lriot_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lr-iot-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the LR IoT Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR IoT Click driver.

#### Standard key functions :

- `lriot_cfg_setup` Config Object Initialization function.
```c
void lriot_cfg_setup ( lriot_cfg_t *cfg );
```

- `lriot_init` Initialization function.
```c
err_t lriot_init ( lriot_t *ctx, lriot_cfg_t *cfg );
```

- `lriot_default_cfg` Click Default Configuration function.
```c
err_t lriot_default_cfg ( lriot_t *ctx );
```

#### Example key functions :

- `lriot_get_wifi_scan_results` This function performs a WiFi scanning and reads the results.
```c
err_t lriot_get_wifi_scan_results ( lriot_t *ctx, lriot_wifi_scan_results_t *results );
```

- `lriot_get_gnss_scan_results` This function performs a GNSS scanning and reads the results.
```c
err_t lriot_get_gnss_scan_results ( lriot_t *ctx, lriot_gnss_scan_results_t *results );
```

- `lriot_send_lora_message` This function sends a LoRa message to the receiver.
```c
err_t lriot_send_lora_message ( lriot_t *ctx, uint8_t *message );
```

## Example Description

> This example demonstrates the use of LR IoT click board by reading a GNSS and WiFi
scanning results and displaying it on the USB UART. In the case of a tranceive firmware
the communication between two devices over LoRa will be demonstrated as well.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default configuration, and after that reads
and displays the chip's firmware information. In the case you need to update or change the default
firmware refer to the @b LRIOT_UPDATE_FIRMWARE and @b LRIOT_FIRMWARE_SELECTOR macro definition.

```c

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

```

### Application Task

> There are 3 types of the example: 
1. Modem firmware: reads a GNSS and WiFi scanning results and displays them on the USB UART.
2. Transcever firmware (application mode transmitter ): reads a GNSS and WiFi scanning results
   as well as the chip internal temperature and sends specific LoRa messages containing that information
   to the LoRa receiver.
3. Transcever firmware (application mode receiver): reads all incoming LoRa packets and displays them
   on the USB UART.

```c

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

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LRIoT

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---


---
# LR IoT Click

> [LR IoT Click](https://www.mikroe.com/?pid_product=MIKROE-5447) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5447&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of LR IoT Click board by reading a GNSS and WiFi
scanning results and displaying it on the USB UART. In the case of a tranceive firmware
the communication between two devices over LoRa will be demonstrated as well.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LRIoT

### Example Key Functions

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

### Application Init

> Initializes the driver, performs the Click default configuration, and after that reads
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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---

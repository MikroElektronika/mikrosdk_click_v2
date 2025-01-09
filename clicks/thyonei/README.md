
---
# Thyone-I Click

> [Thyone-I Click](https://www.mikroe.com/?pid_product=MIKROE-6085) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6085&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the Thyone-I Click board by sending and receiving data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ThyoneI

### Example Key Functions

- `thyonei_cfg_setup` Config Object Initialization function.
```c
void thyonei_cfg_setup ( thyonei_cfg_t *cfg );
```

- `thyonei_init` Initialization function.
```c
err_t thyonei_init ( thyonei_t *ctx, thyonei_cfg_t *cfg );
```

- `thyonei_default_cfg` Click Default Configuration function.
```c
void thyonei_default_cfg ( thyonei_t *ctx );
```

- `thyonei_get_req` This command can be used to set individual setting parameters in flash of Thyone-I Click board.
```c
err_t thyonei_get_req ( thyonei_t *ctx, uint8_t settings_index, uint8_t *param_len, uint8_t *parameter );
```

- `thyonei_multicast_data_req` This command provides the multicast data transmission to a group of modules configured with the same MAC GROUP ADDRESS of Thyone-I Click board.
```c
err_t thyonei_multicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message );
```

- `thyonei_unicast_data_req` This command provides the unicast data transmission to the configured MAC DESTINATION ADDRESS of Thyone-I Click board.
```c
err_t thyonei_unicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message );
```

### Application Init

> Initializes the driver and performs the Click default configuration and setting the MAC addresses and mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    thyonei_cfg_t thyonei_cfg;  /**< Click config object. */

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
    thyonei_cfg_setup( &thyonei_cfg );
    THYONEI_MAP_MIKROBUS( thyonei_cfg, MIKROBUS_1 );
    if ( UART_ERROR == thyonei_init( &thyonei, &thyonei_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    thyonei_default_cfg ( &thyonei );

    thyonei_generic_read( &thyonei, app_buf, PROCESS_BUFFER_SIZE );

    uint8_t tmp_data [ 4 ] = { 0 };
    uint8_t len = 0;

    thyonei_get_req( &thyonei, THYONEI_INDEX_SERIAL_NUMBER, &len, tmp_data );
    log_printf( &logger, " Thyone-I serial number: 0x" );
    for( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        log_printf( &logger, "%.2X", ( uint16_t ) tmp_data[ cnt ] );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "= = = = = = = = = = = = = = =\r\n" );

    log_printf( &logger, " Thyone-I factory reset request: \r\n" );
    thyonei_send_command( &thyonei, THYONEI_CMD_FACTORY_RESET_REQ, 0, NULL );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_FACTORY_RESET_REQ );

    log_printf( &logger, " Thyone-I Set Mode to normal mode: \r\n" );
    tmp_data[ 0 ] = 0;
    thyonei_set_req( &thyonei, THYONEI_INDEX_MODULE_MODE, 1, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set RF-Profile to 0: \r\n" );
    tmp_data[ 0 ] = 0;
    thyonei_set_req( &thyonei, THYONEI_INDEX_RF_PROFILE, 1, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set MAC Group ID to 0xAA: \r\n" );
    tmp_data[ 0 ] = MAC_GROUP_ADDRESS;
    thyonei_set_req( &thyonei, THYONEI_INDEX_MAC_GROUP_ID, 1, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set Source MAC address: \r\n" );
    tmp_data[ 0 ] = ( uint8_t ) SOURCE_ADDRESS;
    tmp_data[ 1 ] = ( uint8_t ) ( SOURCE_ADDRESS >> 8 );
    tmp_data[ 2 ] = ( uint8_t ) ( SOURCE_ADDRESS >> 16 );
    tmp_data[ 3 ] = ( uint8_t ) ( SOURCE_ADDRESS >> 24 );
    thyonei_set_req( &thyonei, THYONEI_INDEX_MAC_SOURCE_ADDRESS, 4, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set Destination MAC address: \r\n" );
    tmp_data[ 0 ] = ( uint8_t ) DESTINATION_ADDRESS;
    tmp_data[ 1 ] = ( uint8_t ) ( DESTINATION_ADDRESS >> 8 );
    tmp_data[ 2 ] = ( uint8_t ) ( DESTINATION_ADDRESS >> 16 );
    tmp_data[ 3 ] = ( uint8_t ) ( DESTINATION_ADDRESS >> 24 );
    thyonei_set_req( &thyonei, THYONEI_INDEX_MAC_DEST_ADDRESS, 4, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Transmitter mode - Sending data to the devices within range ( thyonei_broadcast_data_req ), with same MAC group ( thyonei_multicast_data_req )
 and with the selected MAC destination address ( thyonei_unicast_data_req ).
> Receiver mode - Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
#if ( TRANSMITTER_MAC_ADDRESS == SOURCE_ADDRESS )
    uint8_t message_data[ PROCESS_BUFFER_SIZE ] = { 0 };

    #define BROADCAST_MESSAGE       "Broadcast"
    strcpy( message_data, MESSAGE );
    strcat( message_data, BROADCAST_MESSAGE );
    log_printf( &logger, " Thyone-I sending broadcast message: \r\n" );
    thyonei_broadcast_data_req( &thyonei, strlen( message_data ), message_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_CNF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    #define MULTICAST_MESSAGE       "Multicast"
    strcpy( message_data, MESSAGE );
    strcat( message_data, MULTICAST_MESSAGE );
    log_printf( &logger, " Thyone-I sending multicast message: \r\n" );
    thyonei_multicast_data_req( &thyonei, strlen( message_data ), message_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_CNF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    #define UNICAST_MESSAGE         "Unicast"
    strcpy( message_data, MESSAGE );
    strcat( message_data, UNICAST_MESSAGE );
    log_printf( &logger, " Thyone-I sending unicast message: \r\n" );
    thyonei_unicast_data_req( &thyonei, strlen( message_data ), message_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_CNF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_IND );
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

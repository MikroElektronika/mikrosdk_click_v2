
---
# ISM 3 Click

> [ISM 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6066) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6066&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of an ISM 3 Click board by showing the communication between the two Click boards (Server and Client).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISM3

### Example Key Functions

- `ism3_cfg_setup` Config Object Initialization function.
```c
void ism3_cfg_setup ( ism3_cfg_t *cfg );
```

- `ism3_init` Initialization function.
```c
err_t ism3_init ( ism3_t *ctx, ism3_cfg_t *cfg );
```

- `ism3_default_cfg` Click Default Configuration function.
```c
err_t ism3_default_cfg ( ism3_t *ctx );
```

- `ism3_transmit_packet` This function transmits a desired data packet.
```c
err_t ism3_transmit_packet ( ism3_t *ctx, uint8_t *data_in, uint8_t len );
```

- `ism3_receive_packet` This function waits for a data packet to arrive and reads it.
```c
err_t ism3_receive_packet ( ism3_t *ctx, uint8_t *data_out, uint8_t *len );
```

- `ism3_check_communication` This function checks the communication by reading and verifying the device part number.
```c
err_t ism3_check_communication ( ism3_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism3_cfg_t ism3_cfg;  /**< Click config object. */

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
    ism3_cfg_setup( &ism3_cfg );
    ISM3_MAP_MIKROBUS( ism3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ism3_init( &ism3, &ism3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISM3_ERROR == ism3_default_cfg ( &ism3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> There are two application modes: Server and Client.
> - Server mode: Waits for a message from client device, reads the received packet
>                and responds with an acknowledge message.
> - Client mode: Initiates communication with the server device by sending a desired
>                packet which contains the text message and a packet counter approximately 
>                every 500 milliseconds. After sending the packet it waits for an acknowledge
>                response from server. The packet counter is incremented only after
>                successfull acknowledgment for the last packet.
> All data is being displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    err_t error_flag = ISM3_OK;
    static uint16_t packet_cnt = 0;
    uint8_t data_buf[ ISM3_PACKET_LEN ] = { 0 };
#ifdef DEMO_APP_SERVER
    log_printf ( &logger, " Waiting for a packet message from client device...\r\n" );
    error_flag = ism3_receive_packet ( &ism3, data_buf, NULL );
    if ( ISM3_OK == error_flag )
    {
        packet_cnt = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        log_printf ( &logger, " Packet #%u is received with message: %s\r\n", packet_cnt, &data_buf[ 2 ] );
        Delay_ms ( 200 );
        log_printf ( &logger, " Server transmits an acknowledge message to client for packet #%u\r\n", packet_cnt );
        error_flag = ism3_transmit_packet ( &ism3, ACKNOWLEDGE_RESPONSE, strlen ( ACKNOWLEDGE_RESPONSE ) );
    }
    log_printf ( &logger, " --------------------------------------------\r\n\n" );
#else
    if ( ( strlen ( TEXT_MESSAGE_TO_SEND ) + 2 ) > ISM3_PACKET_LEN )
    {
        log_error( &logger, " Packet exceeds maximal allowable length." );
        error_flag = ISM3_ERROR;
    }
    if ( ISM3_OK == error_flag )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( packet_cnt >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( packet_cnt & 0xFF );
        memcpy ( &data_buf[ 2 ], TEXT_MESSAGE_TO_SEND, strlen ( TEXT_MESSAGE_TO_SEND ) );
        log_printf ( &logger, " Client transmits packet #%u to server\r\n", packet_cnt );
        error_flag = ism3_transmit_packet ( &ism3, data_buf, strlen ( TEXT_MESSAGE_TO_SEND ) + 2 );
    }
    if ( ISM3_OK == error_flag )
    {
        log_printf ( &logger, " Waiting for an acknowledge...\r\n" );
        error_flag = ism3_receive_packet ( &ism3, data_buf, NULL );
    }
    if ( ( ISM3_OK == error_flag ) && ( strstr ( data_buf, ACKNOWLEDGE_RESPONSE ) ) )
    {
        log_printf ( &logger, " Acknowledge message is received from server!\r\n" );
        packet_cnt++;
    }
    else
    {
        log_printf ( &logger, " Acknowledge message is NOT received from server!\r\n" );
        error_flag = ism3_go_to_rx ( &ism3 );
    }
    log_printf ( &logger, " --------------------------------------------\r\n\n" );
    Delay_ms ( 500 );
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

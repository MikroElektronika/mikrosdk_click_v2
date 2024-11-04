
---
# ISM 5 Click

> ISM 5 Click is a compact add-on board designed for seamless integration into a wide range of applications requiring efficient communication in the Sub-GHz 868MHz frequency band. This board features the Si4461, a high-performance, low-current transceiver from Silicon Labs known for its robust operation in time division duplexing (TDD) mode, enabling alternating transmission and reception of data packets.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ism5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ism-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the ISM 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISM 5 Click driver.

#### Standard key functions :

- `ism5_cfg_setup` Config Object Initialization function.
```c
void ism5_cfg_setup ( ism5_cfg_t *cfg );
```

- `ism5_init` Initialization function.
```c
err_t ism5_init ( ism5_t *ctx, ism5_cfg_t *cfg );
```

- `ism5_default_cfg` Click Default Configuration function.
```c
err_t ism5_default_cfg ( ism5_t *ctx );
```

#### Example key functions :

- `ism5_get_part_info` This function reads the device part information.
```c
err_t ism5_get_part_info ( ism5_t *ctx, ism5_part_info_t *part_info );
```

- `ism5_transmit_packet` This function transmits a desired data packet on the selected channel.
```c
err_t ism5_transmit_packet ( ism5_t *ctx, uint8_t channel, uint8_t *data_in, uint8_t len );
```

- `ism5_receive_packet` This function waits for a data packet to arrive on the selected channel and reads it.
```c
err_t ism5_receive_packet ( ism5_t *ctx, uint8_t channel, uint8_t *data_out, uint8_t *len, uint32_t timeout );
```

## Example Description

> This example demonstrates the use of an ISM 5 Click board by showing the communication between the two Click boards (Server and Client).

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the Click default configuration, then reads and displays the device part information.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism5_cfg_t ism5_cfg;  /**< Click config object. */

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
    ism5_cfg_setup( &ism5_cfg );
    ISM5_MAP_MIKROBUS( ism5_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ism5_init( &ism5, &ism5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ISM5_ERROR == ism5_default_cfg ( &ism5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    ism5_part_info_t part_info;
    if ( ISM5_OK == ism5_get_part_info ( &ism5, &part_info ) )
    {
        log_printf ( &logger, " --- PART INFO ---\r\n" );
        log_printf ( &logger, " Chip rev: 0x%.2X\r\n", ( uint16_t ) part_info.chip_rev );
        log_printf ( &logger, " Part: 0x%.4X\r\n", part_info.part );
        log_printf ( &logger, " Part build: 0x%.2X\r\n", ( uint16_t ) part_info.part_build );
        log_printf ( &logger, " ID: 0x%.4X\r\n", part_info.id );
        log_printf ( &logger, " Customer: 0x%.2X\r\n", ( uint16_t ) part_info.customer );
        log_printf ( &logger, " ROM ID: 0x%.2X\r\n\n", ( uint16_t ) part_info.rom_id );
    }
#ifdef DEMO_APP_SERVER
    log_printf ( &logger, " Application Mode: Server\r\n" );
#else
    log_printf ( &logger, " Application Mode: Client\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> There are two application modes: Server and Client.
> - Server mode: Waits for a message from client device, reads the received packet
>                and responds with an acknowledge message.
> - Client mode: Initiates communication with the server device by sending a desired
>                packet which contains the text message and a packet counter approximately 
>                once per second. After sending the packet it waits for an acknowledge
>                response from server. The packet counter is incremented only after
>                successfull acknowledgment for the last packet.
> All data is being displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    err_t error_flag = ISM5_OK;
    static uint16_t packet_cnt = 0;
    uint8_t data_buf[ ISM5_PACKET_MAX_SIZE ] = { 0 };
#ifdef DEMO_APP_SERVER
    log_printf ( &logger, " Waiting for a packet message from client device...\r\n" );
    error_flag = ism5_receive_packet ( &ism5, CHANNEL_NUMBER, data_buf, NULL, ISM5_PACKET_TIMEOUT_DISABLE );
    if ( ISM5_OK == error_flag )
    {
        packet_cnt = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        log_printf ( &logger, " Packet #%u is received with message: %s\r\n", packet_cnt, &data_buf[ 2 ] );
        Delay_ms ( 200 );
        log_printf ( &logger, " Server transmits an acknowledge message to client for packet #%u\r\n\n", packet_cnt );
        error_flag = ism5_transmit_packet ( &ism5, CHANNEL_NUMBER, ACKNOWLEDGE_RESPONSE, strlen ( ACKNOWLEDGE_RESPONSE ) );
    }
#else
    if ( ( strlen ( TEXT_MESSAGE_TO_SEND ) + 2 ) > ISM5_PACKET_MAX_SIZE )
    {
        log_error( &logger, " Packet exceeds maximal allowable length." );
        error_flag = ISM5_ERROR;
    }
    if ( ISM5_OK == error_flag )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( packet_cnt >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( packet_cnt & 0xFF );
        memcpy ( &data_buf[ 2 ], TEXT_MESSAGE_TO_SEND, strlen ( TEXT_MESSAGE_TO_SEND ) );
        log_printf ( &logger, " Client transmits packet #%u to server\r\n", packet_cnt );
        error_flag = ism5_transmit_packet ( &ism5, CHANNEL_NUMBER, data_buf, strlen ( TEXT_MESSAGE_TO_SEND ) + 2 );
    }
    if ( ISM5_OK == error_flag )
    {
        log_printf ( &logger, " Waiting for an acknowledge...\r\n" );
        error_flag = ism5_receive_packet ( &ism5, CHANNEL_NUMBER, data_buf, NULL, ISM5_PACKET_TIMEOUT_1_SEC );
    }
    if ( ( ISM5_OK == error_flag ) && ( strstr ( data_buf, ACKNOWLEDGE_RESPONSE ) ) )
    {
        log_printf ( &logger, " Acknowledge message is received from server!\r\n\n" );
        packet_cnt++;
    }
    else
    {
        log_printf ( &logger, " Acknowledge message is NOT received from server!\r\n\n" );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISM5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

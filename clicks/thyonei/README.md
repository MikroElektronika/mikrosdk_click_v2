\mainpage Main Page

---
# Thyone-I click

> Thyone-I Click is a compact add-on board for wireless communication in various devices like control systems, remote controls, and sensor nodes. This board features the WIRL-PRO2 Thyone-I (2611011021000) module from Würth Elektronik. It operates in the 2.4GHz license-free band, ensuring secure and reliable data transmission in both point-to-point and mesh configurations. It features versatile connectivity options with onboard and external antenna support, a data transmission rate of up to 2Mbit/s, and embedded security with hardware-accelerated encryption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thyonei_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thyone-i-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : UART type


# Software Support

We provide a library for the Thyone-I Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thyone-I Click driver.

#### Standard key functions :

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

#### Example key functions :

- `thyonei_get_req` This command can be used to set individual setting parameters in flash of Thyone-I click board.
```c
err_t thyonei_get_req ( thyonei_t *ctx, uint8_t settings_index, uint8_t *param_len, uint8_t *parameter );
```

- `thyonei_multicast_data_req` This command provides the multicast data transmission to a group of modules configured with the same MAC GROUP ADDRESS of Thyone-I click board.
```c
err_t thyonei_multicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message );
```

- `thyonei_unicast_data_req` This command provides the unicast data transmission to the configured MAC DESTINATION ADDRESS of Thyone-I click board.
```c
err_t thyonei_unicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message );
```

## Example Description

> This example demonstrates the use of the Thyone-I click board by sending and receiving data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration and setting the MAC addresses and mode.

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


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ThyoneI

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---


---
# WIZFI360 Click

> WIZFI360 Click is a compact add-on board for reliable WiFi connectivity in industrial applications. This board features the WIZFI360, a WiFi module from WIZnet, known for its low power consumption and full compliance with IEEE802.11 b/g/n standards. The board supports SoftAP, Station, and SoftAP+Station modes, operates within the frequency range of 2400MHz to 2483.5MHz, and offers a versatile serial port baud rate of up to 2Mbps. It features WPA_PSK and WPA2_PSK encryption for secure communication, configurable operating channels from 1 to 13, and the ability to handle up to 5 simultaneous TCP/UDP links.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wizifi360_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/wizfi360-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART type


# Software Support

We provide a library for the WIZFI360 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for WIZFI360 Click driver.

#### Standard key functions :

- `wizfi360_cfg_setup` Config Object Initialization function.
```c
void wizfi360_cfg_setup ( wizfi360_cfg_t *cfg );
```

- `wizfi360_init` Initialization function.
```c
err_t wizfi360_init ( wizfi360_t *ctx, wizfi360_cfg_t *cfg );
```

#### Example key functions :

- `wizfi360_write_command` This function writes a desired command by using the UART serial interface.
```c
err_t wizfi360_write_command ( wizfi360_t *ctx, uint8_t *command )
```

- `wizfi360_write_cmd_param` This function writes a desired command, prefix and parameter by using UART serial interface.
```c
err_t wizfi360_write_cmd_param ( wizfi360_t *ctx, uint8_t *command, uint8_t *prefix, uint8_t *param );
```

- `wizfi360_send_message` This function sends messages to the host in normal transmission mode using the UART serial interface.
```c
err_t wizfi360_send_message ( wizfi360_t *ctx, uint8_t *message );
```

## Example Description

> This example demonstrates the use of the WIZFI360 Click board 
> by processing the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, connects to the desired WiFi network, 
> and then connects to the TCP/UDP server and configures SNTP parameter.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wizfi360_cfg_t wizfi360_cfg;  /**< Click config object. */

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
    wizfi360_cfg_setup( &wizfi360_cfg );
    WIZFI360_MAP_MIKROBUS( wizfi360_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wizfi360_init( &wizfi360, &wizfi360_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    wizfi360_write_command( &wizfi360, WIZFI360_CMD_AT );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_command( &wizfi360, WIZFI360_CMD_RESTORE );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_command( &wizfi360, WIZFI360_CMD_GMR );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CWMODE_CUR, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         WIZFI360_CWMODE_STATION );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CIPMUX, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         WIZFI360_CIPMUX_SINGLE_CONN );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CWDHCP_CUR, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         WIZFI360_CWDHCP_STATION_DHCP );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    memset( cmd_buf, 0, 100 );
    strcpy( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_SSID );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_SEPARATOR );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_PASSWORD );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CWJAP_CUR, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         cmd_buf );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_inquire_command( &wizfi360, WIZFI360_CMD_CIPSTA_CUR );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    memset( cmd_buf, 0, 100 );
    strcpy( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_EXAMPLE_TCP );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_SEPARATOR );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_REMOTE_ID );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_SEPARATOR );
    strcat( cmd_buf, DEMO_REMOTE_PORT );
    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CIPSTART, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         cmd_buf );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param ( &wizfi360, WIZFI360_CMD_CIPSNTPCFG, 
                                          WIZFI360_PREFIX_SYMB_SET_VAL, 
                                          WIZFI360_ENABLE_TIMEZONE_1 );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo app displays current time data, sends data messages to the TCP/UDP server, 
> reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    wizfi360_inquire_command( &wizfi360, WIZFI360_CMD_CIPSNTPTIME );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 1000 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CIPSEND, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         DEMO_SEND_DATA_LENGTH );
    wizfi360_check_response( WIZFI360_RSP_READY_FOR_SEND );
    
    wizfi360_send_message( &wizfi360, DEMO_SEND_DATA );
    wizfi360_check_response( WIZFI360_RECEIVE );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> In order for the examples to work without using Planet Debug, 
> the user needs to set the SSID and password of the target AP.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.WIZFI360

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

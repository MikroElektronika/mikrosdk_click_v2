
---
# WIZFI360 Click

> [WIZFI360 Click](https://www.mikroe.com/?pid_product=MIKROE-6153) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6153&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the WIZFI360 Click board 
> by processing the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WIZFI360

### Example Key Functions

- `wizfi360_cfg_setup` Config Object Initialization function.
```c
void wizfi360_cfg_setup ( wizfi360_cfg_t *cfg );
```

- `wizfi360_init` Initialization function.
```c
err_t wizfi360_init ( wizfi360_t *ctx, wizfi360_cfg_t *cfg );
```

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

### Note

> In order for the examples to work without using Planet Debug, 
> the user needs to set the SSID and password of the target AP.

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

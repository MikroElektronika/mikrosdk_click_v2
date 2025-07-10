
---
# XPort EDGE Click

> [XPort EDGE Click](https://www.mikroe.com/?pid_product=MIKROE-6540) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6540&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the functionality of the XPort EDGE Click board. It initializes the module, 
retrieves the device and interface information, performs diagnostic commands such as pinging a specific 
address, and allows the user to access the device via its web interface. Additionally, it provides a 
CLI (Command Line Interface) mode to UART terminal for further interaction with the device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.XPortEDGE

### Example Key Functions

- `xportedge_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void xportedge_cfg_setup ( xportedge_cfg_t *cfg );
```

- `xportedge_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t xportedge_init ( xportedge_t *ctx, xportedge_cfg_t *cfg );
```

- `xportedge_reset_device` This function resets device by toggling the RST pin state.
```c
void xportedge_reset_device ( xportedge_t *ctx );
```

- `xportedge_send_cmd` This function sends a command string by using UART serial interface.
```c
void xportedge_send_cmd ( xportedge_t *ctx, uint8_t *cmd );
```

- `xportedge_list_commands` This function lists commands at current level by sending the question mark by using UART serial interface.
```c
void xportedge_list_commands ( xportedge_t *ctx );
```

### Application Init

> Initializes the logger and the XPort EDGE Click driver, performs a device reset, retrieves device 
information, and pings the specific address in diagnostics. The application retrieves the device's IP address, 
enabling the user to connect via a web browser and access the web interface. Finally, it enters CLI mode 
for advanced command interactions.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xportedge_cfg_t xportedge_cfg;  /**< Click config object. */

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
    xportedge_cfg_setup( &xportedge_cfg );
    XPORTEDGE_MAP_MIKROBUS( xportedge_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xportedge_init( &xportedge, &xportedge_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, "*** Reset Device ***" );
    xportedge_reset_device ( &xportedge );
    xportedge_read_response ( &xportedge );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Get Device Info ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DEVICE );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_SHOW );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Go Back to Status Level ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Get Interface Status and IP Address ***\r\n" );
    log_printf( &logger, "*** Connect to Listed IP Address Through Web Browser to Access Web Interface ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_INTERFACE_ETH0 );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_SHOW );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Go Back to Status Level ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Ping %s ***", ( char * ) ADDRESS_TO_PING );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DIAGNOSTICS );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DIAGNOSTICS_PING );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DIAGNOSTICS_PING_HOST( ADDRESS_TO_PING ) );
    xportedge_read_response ( &xportedge );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Go Back to ROOT Level ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** List ROOT Level Commands and Switch to CLI Terminal ***\r\n" );
    log_printf( &logger, "*** Now CLI Commands are Input from the UART Terminal ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_list_commands ( &xportedge );
    xportedge_read_response ( &xportedge );
}
```

### Application Task

> Continuously monitors UART communication, relaying commands and responses between the XPort EDGE Click 
board and the logger. This allows real-time interaction with the device through the UART Terminal for
configuration and diagnostics.

```c
void application_task ( void )
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &xportedge.uart, app_buf, app_buf_len );
        xportedge_clear_app_buf ( );
    }
    app_buf_len = uart_read( &xportedge.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        xportedge_clear_app_buf ( );
    }
}
```

### Note

> Ensure the XPort EDGE Click board is properly connected to the network.
The application uses a predefined address to test connectivity via the ping diagnostic command.

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

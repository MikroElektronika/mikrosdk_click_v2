
---
# XPort ETH XE Click

> [XPort ETH XE Click](https://www.mikroe.com/?pid_product=MIKROE-6538) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6538&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the XPort ETH XE Click board for Ethernet communication. 
The application initializes the XPort ETH XE module, retrieves essential information such as 
firmware version, MAC address, and network status, and demonstrates sending a ping command. 
It also allows for bidirectional UART communication between the USB UART and the XPort ETH XE UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.XPortETHXE

### Example Key Functions

- `xportethxe_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void xportethxe_cfg_setup ( xportethxe_cfg_t *cfg );
```

- `xportethxe_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t xportethxe_init ( xportethxe_t *ctx, xportethxe_cfg_t *cfg );
```

- `xportethxe_reset_device` This function resets device by toggling the RST pin state.
```c
void xportethxe_reset_device ( xportethxe_t *ctx );
```

- `xportethxe_send_cmd` This function sends a command string by using UART serial interface.
```c
void xportethxe_send_cmd ( xportethxe_t *ctx, uint8_t *cmd );
```

- `xportethxe_send_enter` This function sends enter (new line) by using UART serial interface.
```c
void xportethxe_send_enter ( xportethxe_t *ctx );
```

### Application Init

> Initializes the UART communication, logs essential information, configures the XPort ETH XE module, 
and retrieves the firmware version, MAC address, and network status. It also demonstrates basic 
command operations such as pinging the specific IP address (8.8.8.8).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xportethxe_cfg_t xportethxe_cfg;  /**< Click config object. */

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
    xportethxe_cfg_setup( &xportethxe_cfg );
    XPORTETHXE_MAP_MIKROBUS( xportethxe_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xportethxe_init( &xportethxe, &xportethxe_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Reset Device to Monitor Mode <<<\r\n" );
    xportethxe_reset_device ( &xportethxe );
    xportethxe_send_enter ( &xportethxe );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_MODE_MONITOR_WITH_NET );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Query Firmware Version <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_QUERY_FW_VERSION );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Get MAC Address <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_GET_MAC_ADDRESS );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Get Network Status and IP Address <<<\r\n" );
    log_printf( &logger, ">>> Send QU Command to Exit Monitor Mode and Connect to Listed <<<\r\n" );
    log_printf( &logger, ">>> IP Address Through Web Browser to Access Web Interface <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_NET_STAT );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Ping 8.8.8.8 and Switch to UART Terminal Commands Input <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_PING( "8.8.8.8" ) );
    xportethxe_send_enter ( &xportethxe );
    xportethxe_read_response ( &xportethxe );
}
```

### Application Task

> Continuously reads data from the USB UART and forwards it to the XPort ETH XE module, 
while also capturing responses from the module and forwarding them back to the USB UART.
This allows real-time interaction with the device through the UART Terminal for
configuration and diagnostics.

```c
void application_task ( void )
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &xportethxe.uart, app_buf, app_buf_len );
        xportethxe_clear_app_buf ( );
    }
    app_buf_len = uart_read( &xportethxe.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        xportethxe_clear_app_buf ( );
    }
}
```

### Note

> Ensure the XPort ETH XE Click board is properly connected to the network.

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

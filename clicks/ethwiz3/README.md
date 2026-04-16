
---
# ETH WIZ 3 Click

> [ETH WIZ 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6646) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6646&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ETH WIZ 3 Click board in TCP client
mode using the module AT command interface. The device is configured to use
DHCP, connect to a remote TCP echo server, and periodically send a predefined
message. When the TCP connection is active, the application transmits the
message and displays the received echo response on the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ETHWIZ3

### Example Key Functions

- `ethwiz3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ethwiz3_cfg_setup ( ethwiz3_cfg_t *cfg );
```

- `ethwiz3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ethwiz3_init ( ethwiz3_t *ctx, ethwiz3_cfg_t *cfg );
```
T
- `ethwiz3_cmd_set` This function sends a two-character command followed by the input data string and a CRLF termination.
```c
err_t ethwiz3_cmd_set ( ethwiz3_t *ctx, uint8_t *cmd, uint8_t *data_in );
```

- `ethwiz3_cmd_get` This function sends a two-character command terminated with CRLF and reads back the response data.
```c
err_t ethwiz3_cmd_get ( ethwiz3_t *ctx, uint8_t *cmd, uint8_t *data_out, uint16_t *read_len, uint16_t data_buf_len );
```

- `ethwiz3_data_write` This function writes a raw data buffer of the specified length.
```c
err_t ethwiz3_data_write ( ethwiz3_t *ctx, uint8_t *data_in, uint16_t len );
```

- `ethwiz3_data_read` This function reads raw data into the provided buffer.
```c
err_t ethwiz3_data_read ( ethwiz3_t *ctx, uint8_t *data_out, uint16_t *read_len, uint16_t data_buf_len );
```

### Application Init

> Initializes the logger and ETH WIZ 3 Click driver, resets the device to AT
mode, reads and displays basic device information (MAC address, firmware
version, product name), configures the TCP client parameters (DHCP, remote
host IP/port), saves settings, and reboots the device to data mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ethwiz3_cfg_t ethwiz3_cfg;  /**< Click config object. */

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
    ethwiz3_cfg_setup( &ethwiz3_cfg );
    ETHWIZ3_MAP_MIKROBUS( ethwiz3_cfg, MIKROBUS_POSITION_ETHWIZ3 );
    if ( ETHWIZ3_OK != ethwiz3_init( &ethwiz3, &ethwiz3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    ethwiz3_clear_app_buf ( );

    log_printf( &logger, ">>> Reset Device to AT Mode <<<\r\n" );
    ethwiz3_set_at_mode ( &ethwiz3 );
    ethwiz3_reset_device ( &ethwiz3 );
    if ( ETHWIZ3_OK == ethwiz3_data_read ( &ethwiz3, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Get MAC Address <<<\r\n" );
    if ( ETHWIZ3_OK == ethwiz3_cmd_get ( &ethwiz3, ETHWIZ3_CMD_MAC_ADDRESS, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Query Firmware Version <<<\r\n" );
    if ( ETHWIZ3_OK == ethwiz3_cmd_get ( &ethwiz3, ETHWIZ3_CMD_FIRMWARE_VERSION, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Get Product Name <<<\r\n" );
    if ( ETHWIZ3_OK == ethwiz3_cmd_get ( &ethwiz3, ETHWIZ3_CMD_PRODUCT_NAME, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Set Network Operation Mode to TCP Client <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_NETWORK_OPERATION_MODE, ETHWIZ3_OP_MODE_TCP_CLIENT );

    log_printf( &logger, ">>> Set IP Address Allocation Method to DHCP <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_IP_ADDRESS_METHOD, ETHWIZ3_IM_DHCP );

    log_printf( &logger, ">>> Set Remote Host IP Address <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_REMOTE_IP, REMOTE_IP );

    log_printf( &logger, ">>> Set Remote Host Port Number <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_REMOTE_PORT, REMOTE_PORT );

    log_printf( &logger, ">>> Save Settings <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_SAVE_SETTINGS, NULL );

    log_printf( &logger, ">>> Reboot Device to Data Mode <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_DEVICE_REBOOT, NULL );
    if ( ETHWIZ3_OK == ethwiz3_data_read ( &ethwiz3, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }
    ethwiz3_set_data_mode ( &ethwiz3 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Monitors the TCP connection status pin and reports changes. When the
connection is active, the application sends the predefined message to the
remote server and prints the received response.

```c
void application_task ( void )
{
    static uint8_t tcp_active = 0;
    uint8_t tcp_pin = ethwiz3_get_tcp_pin ( &ethwiz3 );
    if ( tcp_pin != tcp_active )
    {
        tcp_active = tcp_pin;
        log_printf( &logger, ">>> TCP Connection state: %s <<<\r\n", ( char * ) ( tcp_active ? "Active" : "Idle" ) );
        log_printf( &logger, "\r\n-----------------------------\r\n" );
    }
    if ( tcp_active )
    {
        log_printf( &logger, ">>> Write Message: " );
        if ( ETHWIZ3_OK == ethwiz3_data_write ( &ethwiz3, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) ) )
        {
            log_printf( &logger, "OK\r\n" );
            log_printf( &logger, "<<< Response: " );
            if ( ETHWIZ3_OK == ethwiz3_data_read ( &ethwiz3, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
            {
                ethwiz3_log_app_buf ( );
                ethwiz3_clear_app_buf ( );
            }
            log_printf( &logger, "\r\n" );
        }
        else
        {
            log_printf( &logger, "NOK\r\n" );
        }
    }
    Delay_ms ( 1000 );
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

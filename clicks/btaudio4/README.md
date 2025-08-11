
---
# BT Audio 4 Click

> [BT Audio 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6685) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6685&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates how to communicate with the BT Audio 4 Click board over UART.
It initializes the device, resets it, retrieves the device name, and then continuously
processes and logs any incoming UART messages from the device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BTAudio4

### Example Key Functions

- `btaudio4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void btaudio4_cfg_setup ( btaudio4_cfg_t *cfg );
```

- `btaudio4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t btaudio4_init ( btaudio4_t *ctx, btaudio4_cfg_t *cfg );
```

- `btaudio4_cmd_run` This function sends a specified command to the Click module.
```c
void btaudio4_cmd_run ( btaudio4_t *ctx, uint8_t *cmd );
```

- `btaudio4_cmd_set` This function sets a value to a specified command parameter of the Click module.
```c
void btaudio4_cmd_set ( btaudio4_t *ctx, uint8_t *param, uint8_t *value );
```

- `btaudio4_cmd_get` This function is used to get the value of a given command parameter from the Click module.
```c
void btaudio4_cmd_get ( btaudio4_t *ctx, uint8_t *param );
```

### Application Init

> Initializes the logger and the BT Audio 4 Click driver, performs a device reset, and reads the device name.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btaudio4_cfg_t btaudio4_cfg;  /**< Click config object. */

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
    btaudio4_cfg_setup( &btaudio4_cfg );
    BTAUDIO4_MAP_MIKROBUS( btaudio4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btaudio4_init( &btaudio4, &btaudio4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Reset Device\r\n" );
    btaudio4_reset_device ( &btaudio4 );
    btaudio4_read_response ( &btaudio4, BTAUDIO4_RSP_READY );

    log_printf( &logger, ">>> Get Device Name\r\n" );
    btaudio4_cmd_get ( &btaudio4, BTAUDIO4_PARAM_NAME );
    btaudio4_read_response ( &btaudio4, BTAUDIO4_RSP_OK );
    btaudio4_clear_app_buf ( );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously processes UART data received from the Click board and logs it to the terminal.
Acts as a passive receiver of incoming messages, useful for monitoring notifications.

```c
void application_task ( void )
{
    if ( BTAUDIO4_OK == btaudio4_process ( &btaudio4 ) )
    {
        btaudio4_log_app_buf ( );
        btaudio4_clear_app_buf ( );
    }
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

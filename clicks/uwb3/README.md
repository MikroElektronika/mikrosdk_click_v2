
---
# UWB 3 Click

> [UWB 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5898) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5898&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an UWB 3 Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UWB3

### Example Key Functions

- `uwb3_cfg_setup` Config Object Initialization function.
```c
void uwb3_cfg_setup ( uwb3_cfg_t *cfg );
```

- `uwb3_init` Initialization function.
```c
err_t uwb3_init ( uwb3_t *ctx, uwb3_cfg_t *cfg );
```

- `uwb3_send_cmd` This function sends a specified command to the Click module.
```c
void uwb3_send_cmd ( uwb3_t *ctx, uint8_t *cmd );
```

- `uwb3_send_cmd_with_parameter` This function sends a command with specified parameter to the Click module.
```c
void uwb3_send_cmd_with_parameter ( uwb3_t *ctx, uint8_t *cmd, uint8_t *param );
```

- `uwb3_reset_device` This function resets the device by toggling the RST pin state.
```c
void uwb3_reset_device ( uwb3_t *ctx );
```

### Application Init

> Initializes the driver and configures the Click board for the selected application mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uwb3_cfg_t uwb3_cfg;  /**< Click config object. */

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
    uwb3_cfg_setup( &uwb3_cfg );
    UWB3_MAP_MIKROBUS( uwb3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uwb3_init( &uwb3, &uwb3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    // Clear buffers
    uwb3_process( &uwb3 );
    uwb3_clear_app_buf( );
    
    // Switch to stop mode
    uwb3_send_cmd ( &uwb3, UWB3_CMD_STOP );
    uwb3_display_response ( &uwb3 );
    Delay_ms ( 1000 );
    
#if ( DEMO_APP == APP_RESPONDER_1 )
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_RESPF, RESPONDER_1_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Responder 1\r\n" );
#elif ( DEMO_APP == APP_RESPONDER_2 )
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_RESPF, RESPONDER_2_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Responder 2\r\n" );
#else
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_INITF, INITIATOR_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Initiator\r\n" );
#endif
    
    uwb3_clear_app_buf( );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and processes all incoming ranging block messages and displays them
on the USB UART. One Click board should be configured to initiator mode and
the others to responder 1 or 2. The initiator Click displays the address
and distance of each responder nodes, while the responder Click boards displays
the address and distance of the initiator Click board.

```c
void application_task ( void )
{
    if ( UWB3_OK == uwb3_process( &uwb3 ) ) 
    {
        if ( UWB3_OK == uwb3_parse_ranging_block ( ) )
        {
            uwb3_clear_app_buf( );
        }
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

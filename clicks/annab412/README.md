
---
# ANNA-B412 Click

> [ANNA-B412 Click](https://www.mikroe.com/?pid_product=MIKROE-5829) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5829&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of ANNA-B412 Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ANNAB412

### Example Key Functions

- `annab412_cfg_setup` Config Object Initialization function.
```c
void annab412_cfg_setup ( annab412_cfg_t *cfg );
```

- `annab412_init` Initialization function.
```c
err_t annab412_init ( annab412_t *ctx, annab412_cfg_t *cfg );
```

- `annab412_default_cfg` Click Default Configuration function.
```c
err_t annab412_default_cfg ( annab412_t *ctx );
```

- `annab412_set_cmd_conn_mode` ANNA-B412 set connectability mode function.
```c
err_t annab412_set_cmd_conn_mode ( annab412_t *ctx, uint8_t mode );
```

- `annab412_set_cmd_discover_mode` ANNA-B412 set discoverability mode function.
```c
err_t annab412_set_cmd_discover_mode ( annab412_t *ctx, uint8_t mode );
```

- `annab412_set_cmd_device_name` ANNA-B412 set device name function.
```c
err_t annab412_set_cmd_device_name ( annab412_t *ctx, char *device_name );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    annab412_cfg_t annab412_cfg;  /**< Click config object. */

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
    annab412_cfg_setup( &annab412_cfg );
    ANNAB412_MAP_MIKROBUS( annab412_cfg, MIKROBUS_1 );
    if ( UART_ERROR == annab412_init( &annab412, &annab412_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANNAB412_ERROR == annab412_default_cfg ( &annab412 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
    annab412_set_cmd_echo_on( &annab412 );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );
    
    annab412_set_cmd_device_name( &annab412, DEVICE_NAME );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );

    annab412_set_cmd_discover_mode( &annab412, ANNAB412_DISCOVERABLE_MODE_ON );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );

    annab412_set_cmd_enter_mode( &annab412, ANNAB412_ENTER_MODE_DATA );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );
    
    annab412_set_dsr_pin( &annab412, ANNAB412_PIN_STATE_LOW );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    annab412_process( &annab412 );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        annab412_clear_app_buf( );
    }
}
```

### Note

> We have used the BLE Scanner smartphone application for the test.

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

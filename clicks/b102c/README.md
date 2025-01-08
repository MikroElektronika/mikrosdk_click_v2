
---
# B102C Click

> [B102C Click](https://www.mikroe.com/?pid_product=MIKROE-6088) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6088&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of B102C Click board by processing
  the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.B102C

### Example Key Functions

- `b102c_cfg_setup` Config Object Initialization function.
```c
void b102c_cfg_setup ( b102c_cfg_t *cfg );
```

- `b102c_init` Initialization function.
```c
err_t b102c_init ( b102c_t *ctx, b102c_cfg_t *cfg );
```

- `b102c_default_cfg` Click Default Configuration function.
```c
err_t b102c_default_cfg ( b102c_t *ctx );
```

- `b102c_send_cmd` This function sends a specified command to the B102C Click module.
```c
void b102c_send_cmd ( b102c_t *ctx, uint8_t *cmd );
```

- `b102c_send_cmd_with_params` This function sends a command with specified parameter to the Click module.
```c
void b102c_send_cmd_with_params ( b102c_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

- `b102c_send_cmd_params_check` This function checks the command that is sent.
```c
void b102c_send_cmd_params_check ( b102c_t *ctx, uint8_t *at_cmd_buf );
```

### Application Init

> Initializes the driver, then performs a factory reset and sets the local device name.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    b102c_cfg_t b102c_cfg;  /**< Click config object. */

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
    b102c_cfg_setup( &b102c_cfg );
    B102C_MAP_MIKROBUS( b102c_cfg, MIKROBUS_1 );
    if ( UART_ERROR == b102c_init( &b102c, &b102c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_printf( &logger, " Software reset. \r\n" );
    b102c_send_cmd( &b102c, B102C_CMD_RESET );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_READY );
    
    log_printf( &logger, " Factory reset. \r\n" );
    b102c_send_cmd( &b102c, B102C_CMD_DEFAULT );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_READY );

    log_printf( &logger, " Set device name. \r\n" );
    #define DEVICE_NAME             "B102C Click"
    b102c_send_cmd_with_params( &b102c, B102C_CMD_NAME, DEVICE_NAME );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_OK );

    log_printf( &logger, " Set Auto broadcast mode. \r\n" );
    #define AUTO_BROADCAST          "1"
    b102c_send_cmd_with_params( &b102c, B102C_CMD_ADVMOD, AUTO_BROADCAST );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_OK );

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Connect to device. " );
}
```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    if ( B102C_OK == b102c_process( &b102c ) ) 
    {
        b102c_log_app_buf( );
        b102c_clear_app_buf( );
    }
}
```

### Note

> For communication with B102C Click use the android application on the link:
> https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner

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

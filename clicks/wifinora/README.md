
---
# WiFi NORA Click

> [WiFi NORA Click](https://www.mikroe.com/?pid_product=MIKROE-6217) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6217&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of WiFi NORA Click board by processing
  the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WiFiNORA

### Example Key Functions

- `wifinora_cfg_setup` Config Object Initialization function.
```c
void wifinora_cfg_setup ( wifinora_cfg_t *cfg );
```

- `wifinora_init` Initialization function.
```c
err_t wifinora_init ( wifinora_t *ctx, wifinora_cfg_t *cfg );
```

- `wifinora_hw_reset` This function is used to perform HW reset.
```c
void wifinora_hw_reset ( wifinora_t *ctx );
```

- `wifinora_send_cmd` This function is used to send a desired command.
```c
void wifinora_send_cmd ( wifinora_t *ctx, uint8_t *at_cmd_buf );
```

- `wifinora_send_cmd_with_par` This function sends a desired command with the parameter.
```c
void wifinora_send_cmd_with_par ( wifinora_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

### Application Init

> Initializes the driver, tests the communication, and after that restarts the device, and performs example configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifinora_cfg_t wifinora_cfg;  /**< Click config object. */

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
    wifinora_cfg_setup( &wifinora_cfg );
    WIFINORA_MAP_MIKROBUS( wifinora_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wifinora_init( &wifinora, &wifinora_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    wifinora_process( );
    wifinora_clear_app_buf( );

    // Hardware reset
    wifinora_hw_reset( &wifinora );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_READY );
    wifinora_error_check( error_flag );

    // Communication check
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    // Factory reset
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_USYFR );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    // Software reset
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_SW_RESET );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_READY );
    wifinora_error_check( error_flag );

    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_GMM );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    wifinora_configure_for_example( );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> It creates a connection to the TCP-UDP echo server, sends a message to it reads it back, displaces it on the UART terminal, and then closes the connection.

```c
void application_task ( void ) 
{
    wifinora_example( );
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

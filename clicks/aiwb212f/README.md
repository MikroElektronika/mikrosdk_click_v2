
---
# Ai-WB2-12F Click

> [Ai-WB2-12F Click](https://www.mikroe.com/?pid_product=MIKROE-5983) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5983&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Ai-WB2-12F Click board by processing
  the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AiWB212F

### Example Key Functions

- `aiwb212f_cfg_setup` Config Object Initialization function.
```c
void aiwb212f_cfg_setup ( aiwb212f_cfg_t *cfg );
```

- `aiwb212f_init` Initialization function.
```c
err_t aiwb212f_init ( aiwb212f_t *ctx, aiwb212f_cfg_t *cfg );
```

- `aiwb212f_send_cmd` Ai-WB2-12F send command function.
```c
void aiwb212f_send_cmd ( aiwb212f_t *ctx, uint8_t *at_cmd_buf );
```

- `aiwb212f_send_cmd_with_par` Ai-WB2-12F send command with parameter function.
```c
void aiwb212f_send_cmd_with_par ( aiwb212f_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

- `aiwb212f_send_cmd_check` Ai-WB2-12F send command check function.
```c
void aiwb212f_send_cmd_check ( aiwb212f_t *ctx, uint8_t *at_cmd_buf );
```

### Application Init

> Initializes the driver, tests the communication, and after that restarts the device, and performs example configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    aiwb212f_cfg_t aiwb212f_cfg;  /**< Click config object. */

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
    aiwb212f_cfg_setup( &aiwb212f_cfg );
    AIWB212F_MAP_MIKROBUS( aiwb212f_cfg, MIKROBUS_1 );
    if ( UART_ERROR == aiwb212f_init( &aiwb212f, &aiwb212f_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    aiwb212f_process( );
    aiwb212f_clear_app_buf( );

    aiwb212f_hw_reset( &aiwb212f );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_READY );
    aiwb212f_error_check( error_flag );

    // Check communication
    aiwb212f_send_cmd( &aiwb212f, AIWB212F_CMD_AT );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    // Restart device
    aiwb212f_send_cmd( &aiwb212f, AIWB212F_CMD_AT_SW_RESET );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_READY );
    aiwb212f_error_check( error_flag );

    aiwb212f_configure_for_example( );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected demo example, it sends a TCP/UDP echo server message and receives it or 
  creates BLE Client which receives the messages from the connected device.

```c
void application_task ( void ) 
{
    aiwb212f_example( );
}
```

### Note

> We have used the BLE Scanner Android application for the BLE Example test
  and you can find it at the link:
  https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner

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

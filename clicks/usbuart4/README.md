
---
# USB UART 4 Click

> [USB UART 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2810) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2810&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from USB UART 4 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBUART4

### Example Key Functions

- `usbuart4_cfg_setup` Config Object Initialization function.
```c
void usbuart4_cfg_setup ( usbuart4_cfg_t *cfg );
```

- `usbuart4_init` Initialization function.
```c
err_t usbuart4_init ( usbuart4_t *ctx, usbuart4_cfg_t *cfg );
```

- `usbuart4_pwr_ctrl` This function sets the Click turns Click on.
```c
void usbuart4_pwr_ctrl ( usbuart4_t *ctx, uint8_t state );
```

- `usbuart4_set_cts` This function sets CTS pin.
```c
void usbuart4_set_cts ( usbuart4_t *ctx, uint8_t state );
```

- `usbuart4_send_command` This function is used for sending commands.
```c
void usbuart4_send_command ( usbuart4_t *ctx, char *command );
```

### Application Init

> Initializes driver and power module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart4_cfg_t usbuart4_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );

    // Click initialization.

    usbuart4_cfg_setup( &usbuart4_cfg );
    USBUART4_MAP_MIKROBUS( usbuart4_cfg, MIKROBUS_1 );
    
    err_t init_flag  = usbuart4_init( &usbuart4, &usbuart4_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    
    usbuart4_pwr_ctrl( &usbuart4, USBUART4_POWER_ON );
    usbuart4_set_cts( &usbuart4, USBUART4_CTS_NO_ACTIVE );
    usbuart4_set_mode( &usbuart4, USBUART4_MODE_NORMAL );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads data and echos it back to device and logs it to board.

```c
void application_task ( void ) 
{
    app_buf_len = usbuart4_generic_read( &usbuart4, app_buf, PROCESS_BUFFER_SIZE );
    
    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        memset( app_buf, 0, PROCESS_BUFFER_SIZE );
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

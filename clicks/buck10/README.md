
---
# Buck 10 Click

> [Buck 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3569) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3569&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> Demo application shows basic usage of Buck 10 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck10

### Example Key Functions

- `buck10_cfg_setup` Config Object Initialization function.
```c
void buck10_cfg_setup ( buck10_cfg_t *cfg );
```

- `buck10_init` Initialization function.
```c
err_t buck10_init ( buck10_t *ctx, buck10_cfg_t *cfg );
```

- `buck10_set_device_mode` This function enables and disables output of this Click board.
```c
void buck10_set_device_mode ( buck10_t *ctx, uint8_t mode);
```

### Application Init

> Configuring Clicks and log objects. Settings the Click in the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck10_cfg_t buck10_cfg;  /**< Click config object. */

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

    buck10_cfg_setup( &buck10_cfg );
    BUCK10_MAP_MIKROBUS( buck10_cfg, MIKROBUS_1 );
    if ( buck10_init( &buck10, &buck10_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Enable and Disable device every 5 seconds.

```c
void application_task ( void ) 
{
    buck10_set_device_mode ( &buck10, BUCK10_DEVICE_ENABLE );
    log_printf(&logger, "Output:\t ENABLED\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck10_set_device_mode ( &buck10, BUCK10_DEVICE_DISABLE );
    log_printf(&logger, "Output:\t DISABLED\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Input voltage recommended range - from 4V to 18V Low-side valley current limit - from 3A to 3.9A Low-side negative current limit - (-2.5A) Output voltage - 3.3V or 5V

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


---
# LED Flash 3 Click

> [LED Flash 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5922) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5922&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This app demonstrate flash mode on LED Flash 3 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDFlash3

### Example Key Functions

- `ledflash3_cfg_setup` Config Object Initialization function.
```c
void ledflash3_cfg_setup ( ledflash3_cfg_t *cfg );
```

- `ledflash3_init` Initialization function.
```c
err_t ledflash3_init ( ledflash3_t *ctx, ledflash3_cfg_t *cfg );
```

- `ledflash3_default_cfg` Click Default Configuration function.
```c
err_t ledflash3_default_cfg ( ledflash3_t *ctx );
```

- `ledflash3_write_reg` LED Flash 3 register writing function.
```c
err_t ledflash3_write_reg ( ledflash3_t *ctx, uint8_t reg, uint8_t data_in );
```

- `ledflash3_set_flash_current` LED Flash 3 set flash current function.
```c
err_t ledflash3_set_flash_current ( ledflash3_t *ctx, float flash_current );
```

- `ledflash3_set_torch_current` LED Flash 3 set torch current function.
```c
err_t ledflash3_set_torch_current ( ledflash3_t *ctx, float torch_current );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledflash3_cfg_t ledflash3_cfg;  /**< Click config object. */

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
    ledflash3_cfg_setup( &ledflash3_cfg );
    LEDFLASH3_MAP_MIKROBUS( ledflash3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledflash3_init( &ledflash3, &ledflash3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDFLASH3_ERROR == ledflash3_default_cfg ( &ledflash3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task ");
}
```

### Application Task

> Turning the LED on for a second and off for another second.

```c
void application_task ( void ) 
{
    ledflash3_strobe_pin( &ledflash3 );
    Delay_ms ( 1000 );
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

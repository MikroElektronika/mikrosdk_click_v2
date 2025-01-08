
---
# LED Ring 2 Click

> [LED Ring 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5634) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5634&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for LED Ring 2 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 
> The library also includes a function for controlling LEDs.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDRing2

### Example Key Functions

- `ledring2_cfg_setup` Config Object Initialization function.
```c
void ledring2_cfg_setup ( ledring2_cfg_t *cfg );
```

- `ledring2_init` Initialization function.
```c
err_t ledring2_init ( ledring2_t *ctx, ledring2_cfg_t *cfg );
```

- `ledring2_default_cfg` Click Default Configuration function.
```c
err_t ledring2_default_cfg ( ledring2_t *ctx );
```

- `ledring2_set_led_brightness` LED Ring 2 set LED brightness function.
```c
err_t ledring2_set_led_brightness ( ledring2_t *ctx, uint8_t led_pos, uint16_t led_brightness );
```

- `ledring2_set_led_pos_state` LED Ring 2 set LED state function.
```c
err_t ledring2_set_led_pos_state ( ledring2_t *ctx, uint8_t led_pos, ledring2_led_state_t led_state );
```

- `ledring2_enable` LED Ring 2 enable function.
```c
err_t ledring2_enable ( ledring2_t *ctx );
```

### Application Init

> The initialization of I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledring2_cfg_t ledring2_cfg;  /**< Click config object. */

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
    ledring2_cfg_setup( &ledring2_cfg );
    LEDRING2_MAP_MIKROBUS( ledring2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledring2_init( &ledring2, &ledring2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( LEDRING2_ERROR == ledring2_default_cfg ( &ledring2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " LED Ring 2 Click\r\n" );
}
```

### Application Task

> This example demonstrates the use of the LED Ring 2 Click board&trade;.
> The demo example controls every LED and changes the LED brightness by PWM,
> increasing its brightness from LED1 to LED54.

```c
void application_task ( void ) 
{
    for ( uint8_t led_pos = 1; led_pos < 55; led_pos++ )
    {
        if ( LEDRING2_OK == ledring2_set_led_brightness( &ledring2, led_pos, ( led_pos * 100 ) + 255 ) )
        {
            ledring2_set_vsync( &ledring2 );
            Delay_ms ( 10 );
        }
    }
    Delay_ms ( 1000 );
    
    for ( uint8_t led_pos = 54; led_pos > 0; led_pos-- )
    {
        if ( LEDRING2_OK == ledring2_set_led_brightness( &ledring2, led_pos, 0 ) )
        {
            ledring2_set_vsync( &ledring2 );
            Delay_ms ( 10 );
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

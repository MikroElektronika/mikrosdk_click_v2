
---
# LED Driver 13 Click

> [LED Driver 13 Click](https://www.mikroe.com/?pid_product=MIKROE-4965) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4965&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This library contains API for LED Driver 13 Click driver.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver13

### Example Key Functions

- `leddriver13_cfg_setup` Config Object Initialization function.
```c
void leddriver13_cfg_setup ( leddriver13_cfg_t *cfg );
```

- `leddriver13_init` Initialization function.
```c
err_t leddriver13_init ( leddriver13_t *ctx, leddriver13_cfg_t *cfg );
```

- `leddriver13_default_cfg` Click Default Configuration function.
```c
err_t leddriver13_default_cfg ( leddriver13_t *ctx );
```

- `leddriver13_set_enable` LED Driver 13 set enable function.
```c
err_t leddriver13_set_enable ( leddriver13_t *ctx );
```

- `leddriver13_pwm_start` LED Driver 13 start PWM module.
```c
err_t leddriver13_pwm_start ( leddriver13_t *ctx );
```

- `leddriver13_set_duty_cycle` LED Driver 13 sets PWM duty cycle.
```c
err_t leddriver13_set_duty_cycle ( leddriver13_t *ctx, float duty_cycle );
```

### Application Init

> Initializes the driver and executes the Click default configuration which
> starts the PWM module and sets the LEDs current to minimum.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver13_cfg_t leddriver13_cfg;  /**< Click config object. */

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
    leddriver13_cfg_setup( &leddriver13_cfg );
    LEDDRIVER13_MAP_MIKROBUS( leddriver13_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == leddriver13_init( &leddriver13, &leddriver13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER13_ERROR == leddriver13_default_cfg ( &leddriver13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    
    leddriver13_set_duty_cycle ( &leddriver13, 0.01 );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the LED Driver 13 Click board&trade;.
> The app controls the LEDs brightness by changing the PWM duty cycle.
> The PWM duty cycle percentage will be logged on the USB UART.

```c
 void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 1000.0;
    
    leddriver13_set_duty_cycle ( &leddriver13, duty );
    log_printf( &logger, "> Duty: %.1f%%\r\n", duty * 100 );
    Delay_ms ( 100 );
    
    if ( 30 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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

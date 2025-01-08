
---
# Brushless 24 Click

> [Brushless 24 Click](https://www.mikroe.com/?pid_product=MIKROE-5478) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5478&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This application is a schowcase of controlling speed of brushless motor using Brushless 24 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless24

### Example Key Functions

- `brushless24_cfg_setup` Config Object Initialization function.
```c
void brushless24_cfg_setup ( brushless24_cfg_t *cfg );
```

- `brushless24_init` Initialization function.
```c
err_t brushless24_init ( brushless24_t *ctx, brushless24_cfg_t *cfg );
```

- `brushless24_default_cfg` Click Default Configuration function.
```c
err_t brushless24_default_cfg ( brushless24_t *ctx );
```

- `brushless24_set_duty_cycle` Brushless 24 sets PWM duty cycle.
```c
err_t brushless24_set_duty_cycle ( brushless24_t *ctx, float duty_cycle );
```

- `brushless24_pwm_start` Brushless 24 start PWM module.
```c
err_t brushless24_pwm_start ( brushless24_t *ctx );
```

- `brushless24_get_int_state` Brushless 24 get INT pin state.
```c
uint8_t brushless24_get_int_state ( brushless24_t *ctx );
```

### Application Init

> Initialization of LOG, PWM module and additional pins.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless24_cfg_t brushless24_cfg;  /**< Click config object. */

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
    brushless24_cfg_setup( &brushless24_cfg );
    BRUSHLESS24_MAP_MIKROBUS( brushless24_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless24_init( &brushless24, &brushless24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS24_ERROR == brushless24_default_cfg ( &brushless24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In a span of second changes duty cycle from 0 to 100% which is changing speed of the motor.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless24_set_duty_cycle ( &brushless24, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 1000 );
    
    if ( 10 == duty_cnt ) 
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

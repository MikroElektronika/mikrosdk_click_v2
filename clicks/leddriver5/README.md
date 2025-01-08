
---
# Led Driver 5 Click

> [Led Driver 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3297) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3297&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Mar 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This app enables usage of compact, high-efficiency, fixed frequency,
> synchronous step-up converter, optimized to drive one LED with the constant current.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver5

### Example Key Functions

- `leddriver5_cfg_setup` Config Object Initialization function. 
```c
void leddriver5_cfg_setup ( leddriver5_cfg_t *cfg );
``` 
 
- `leddriver5_init` Initialization function. 
```c
err_t leddriver5_init ( leddriver5_t *ctx, leddriver5_cfg_t *cfg );
```

- `leddriver5_default_cfg` Click Default Configuration function. 
```c
void leddriver5_default_cfg ( leddriver5_t *ctx );
```

- `leddriver5_set_duty_cycle` Generic sets PWM duty cycle. 
```c
void leddriver5_set_duty_cycle ( leddriver5_t *ctx, pwm_data_t duty_cycle );
```
 
- `leddriver5_pwm_stop` Stop PWM module. 
```c
void leddriver5_pwm_stop ( leddriver5_t *ctx );
```

- `leddriver5_pwm_start` Start PWM module. 
```c
void leddriver5_pwm_start ( leddriver5_t *ctx );
```

### Application Init

> Initialization driver enables - GPIO,
> PWM initialization set PWM duty cycle and start PWM. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver2_cfg_setup( &cfg );
    LEDDRIVER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver2_init( &leddriver2, &cfg );

    leddriver2_pwm_start( &leddriver2 );
}

  
```

### Application Task

>  This is an example that demonstrates the use of the LED Driver 5 Click board.
>  This example shows the automatic control of Led light intensity,
>  the first intensity of light is rising and then the intensity of light is falling.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver5_set_duty_cycle( &leddriver5, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
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

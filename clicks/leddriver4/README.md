
---
# LED Driver 4 Click

> [LED Driver 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3037) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3037&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This Click has the ability to dim the connected LED array, without producing any noise on the output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver4

### Example Key Functions

- `leddriver4_cfg_setup` Config Object Initialization function. 
```c
void leddriver4_cfg_setup ( leddriver4_cfg_t *cfg );
``` 
 
- `leddriver4_init` Initialization function. 
```c
err_t leddriver4_init ( leddriver4_t *ctx, leddriver4_cfg_t *cfg );
```

- `leddriver4_set_duty_cycle` Generic sets PWM duty cycle. 
```c
void leddriver4_set_duty_cycle ( leddriver4_t *ctx, float duty_cycle );
```
 
- `leddriver4_pwm_stop` Stop PWM module. 
```c
void leddriver4_pwm_stop ( leddriver4_t *ctx );
```

- `` Start PWM module. 
```c
leddriver4_pwm_start  ( leddriver4_t *ctx );
```

### Application Init

> Initializes the GPIO driver and configures the PWM peripheral for controlling the LED array intensity.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver4_cfg_t cfg;

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

    leddriver4_cfg_setup( &cfg );
    LEDDRIVER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver4_init( &leddriver4, &cfg );
    
    leddriver4_set_duty_cycle ( &leddriver4, 0.0 );
    leddriver4_pwm_start( &leddriver4 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}
```

### Application Task

>  Increases and decreases LED array intensity
>  ( first increases light intensity to the maximum and then decreases to the minimum ).
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    leddriver4_set_duty_cycle ( &leddriver4, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
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

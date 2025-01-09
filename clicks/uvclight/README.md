
---
# UVC Light Click

> [UVC Light Click](https://www.mikroe.com/?pid_product=MIKROE-4177) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4177&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This Click has ultraviolet LEDs with 275nm wavelength. UVC radiation refers to wavelengths 
> shorter than 280 nm. Because of the spectral sensitivity of DNA, only the UVC region 
> demonstrates significant germicidal properties.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UvcLight

### Example Key Functions

- `uvclight_cfg_setup` Config Object Initialization function. 
```c
void uvclight_cfg_setup ( uvclight_cfg_t *cfg );
``` 
 
- `uvclight_init` Initialization function. 
```c
err_t uvclight_init ( uvclight_t *ctx, uvclight_cfg_t *cfg );
```

- `uvclight_pwm_start` This function starts PWM module. 
```c
void uvclight_pwm_start ( uvclight_t *ctx );
```
 
- `uvclight_set_duty_cycle` This function sets the PWM duty cycle. 
```c
void uvclight_set_duty_cycle ( uvclight_t *ctx, pwm_data_t duty_cycle );
```

- `uvclight_pwm_stop` This function stops PWM module. 
```c
void uvclight_pwm_stop ( uvclight_t *ctx );
```

### Application Init

> Initializes the driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uvclight_cfg_t cfg;

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

    uvclight_cfg_setup( &cfg );
    UVCLIGHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvclight_init( &uvclight, &cfg );

    uvclight_set_duty_cycle ( &uvclight, 0.0 );
    uvclight_pwm_start( &uvclight );
    Delay_ms ( 100 );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

>  Increases and decreases the pwm duty cycle.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    uvclight_set_duty_cycle ( &uvclight, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        log_printf( &logger, "Cooldown 2 SEC\r\n");
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}
```

### Note

> CAUTION! High intensity UV Light - avoid eye and skin exposure. Avoid looking direclty at light!

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

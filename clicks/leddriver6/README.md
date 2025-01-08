
---
# LED driver 6 Click

> [LED driver 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3400) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3400&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This application designed to be used in tunable Smart Connected Lighting applications. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Leddriver6

### Example Key Functions

- `leddriver6_cfg_setup` Config Object Initialization function. 
```c
void leddriver6_cfg_setup ( leddriver6_cfg_t *cfg );
``` 
 
- `leddriver6_init` Initialization function. 
```c
err_t leddriver6_init ( leddriver6_t *ctx, leddriver6_cfg_t *cfg );
```

- `leddriver6_set_duty_cycle` Generic sets PWM duty cycle. 
```c
void leddriver6_set_duty_cycle ( leddriver6_t *ctx, pwm_data_t duty_cycle );
```
 
- `leddriver6_pwm_stop` Stop PWM module. 
```c
void leddriver6_pwm_stop ( leddriver6_t *ctx );
```

- `leddriver6_pwm_start` Start PWM module. 
```c
void leddriver6_pwm_start ( leddriver6_t *ctx );
```

### Application Init

> Initialization driver init and pwm init for LED. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    leddriver6_cfg_t leddriver6_cfg;

    //  Click initialization.

    leddriver6_cfg_setup( &leddriver6_cfg );
    LEDDRIVER6_MAP_MIKROBUS( leddriver6_cfg, MIKROBUS_1 );

    if ( leddriver6_init( &leddriver6, &leddriver6_cfg ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );
    
    leddriver6_set_duty_cycle ( &leddriver6, 0.0 );
    if ( leddriver6_pwm_start( &leddriver6 ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- PWM can't be started. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- PWM is started. ----" );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}
```

### Application Task

>  This is an example that demonstrates the use of the LED Driver 6 Click board.
>  This example shows the automatic control LED light intensity,
>  the first intensity of light is rising and then the intensity of light is falling.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    leddriver6_set_duty_cycle ( &leddriver6, duty );
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


---
# HAPTIC 2 Click

> [HAPTIC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4452) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4452&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This app shows some of the functions that Haptic 2 Click has.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic2

### Example Key Functions

- `haptic2_cfg_setup` Config Object Initialization function.
```c
void haptic2_cfg_setup ( haptic2_cfg_t *cfg );
```

- `haptic2_init` Initialization function.
```c
err_t haptic2_init ( haptic2_t *ctx, haptic2_cfg_t *cfg );
```

- `haptic2_default_cfg` Click Default Configuration function.
```c
void haptic2_default_cfg ( haptic2_t *ctx );
```

- `haptic2_set_duty_cycle` Sets PWM duty cycle.
```c
err_t haptic2_set_duty_cycle ( haptic2_t *ctx, float duty_cycle );
```

- `haptic2_pwm_stop` Stop PWM module.
```c
err_t haptic2_pwm_stop ( haptic2_t *ctx );
```

- `haptic2_pwm_start` Start PWM module.
```c
err_t haptic2_pwm_start ( haptic2_t *ctx );
```

### Application Init

> Initialization driver enables - PWM, 
> PWM signal is set to 8000 HZ and to give a 0% duty cycle 
> and start PWM module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    haptic2_cfg_t haptic2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    haptic2_cfg_setup( &haptic2_cfg );
    HAPTIC2_MAP_MIKROBUS( haptic2_cfg, MIKROBUS_1 );
    err_t init_flag  = haptic2_init( &haptic2, &haptic2_cfg );
    if ( init_flag == PWM_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    haptic2_default_cfg ( &haptic2 );

    haptic2_set_duty_cycle ( &haptic2, 0.0 );
    haptic2_pwm_start( &haptic2 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

>  This is an example that demonstrates the use of the Haptic 2 Click board.
>  In this example, we switched PWM signal back and forth 
>  from 10% duty cycle to 90% duty cycle every 500 milliseconds.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    haptic2_set_duty_cycle ( &haptic2, duty );
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

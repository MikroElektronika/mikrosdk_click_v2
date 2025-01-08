
---
# Brushless 5 Click

> [Brushless 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3032) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3032&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This library contains an API for the Brushless5 Click driver.
>  This example showcases how to initialize and use the Brushless 5 Click. 
>  The Click has a brushless 5 motor driver which controls the work 
>  of the motor through the BLDC terminal. 
>  In order for this example to work a motor and a power supply are needed.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless5

### Example Key Functions

- `brushless5_cfg_setup` Config Object Initialization function. 
```c
void brushless5_cfg_setup ( brushless5_cfg_t *cfg );
``` 
 
- `brushless5_init` Initialization function. 
```c
err_t brushless5_init ( brushless5_t *ctx, brushless5_cfg_t *cfg );
```

- `brushless5_set_duty_cycle` Generic sets PWM duty cycle. 
```c
void brushless5_set_duty_cycle ( brushless5_t *ctx, float duty_cycle );
```
 
- `brushless5_pwm_stop` Stop PWM module. 
```c
void brushless5_pwm_stop ( brushless5_t *ctx );
```

- `brushless5_pwm_start` Start PWM module. 
```c
void brushless5_pwm_start ( brushless5_t *ctx );
```

### Application Init

> Initializes the GPIO driver and configures the PWM peripheral for controlling the speed of the motor. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless5_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    brushless5_cfg_setup( &cfg );
    BRUSHLESS5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless5_init( &brushless5, &cfg );
    Delay_ms ( 100 );
    
    brushless5_set_duty_cycle ( &brushless5, 0.0 );
    brushless5_pwm_start( &brushless5 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}
```

### Application Task

>  This is an example that demonstrates the use of a Brushless 5 Click board.
>  Brushless 5 Click communicates with the register via the PWM interface.  
>  Increases and decreasing the speed of the motor demonstrate speed control.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    brushless5_set_duty_cycle ( &brushless5, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
        log_printf( &logger, " Slowing down... \r\n" );
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        log_printf( &logger, " Increasing the motor speed... \r\n" );
    }
    duty_cnt += duty_inc;
    Delay_ms ( 500 );
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

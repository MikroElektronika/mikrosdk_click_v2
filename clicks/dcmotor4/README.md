
---
# DC Motor 4 Click

> [DC Motor 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2221) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2221&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This library contains API for the DC Motor 4 Click driver.
>  Application change the speed and direction.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor4

### Example Key Functions

- `dcmotor4_cfg_setup` Config Object Initialization function. 
```c
void dcmotor4_cfg_setup ( dcmotor4_cfg_t *cfg );
``` 
 
- `dcmotor4_init` Initialization function. 
```c
err_t dcmotor4_init ( dcmotor4_t *ctx, dcmotor4_cfg_t *cfg );
```

- `dcmotor4_set_duty_cycle` Generic sets PWM duty cycle. 
```c
void dcmotor4_set_duty_cycle ( dcmotor4_t *ctx, pwm_data_t duty_cycle );
```
 
- `dcmotor4_pwm_stop` Stop PWM module. 
```c
void dcmotor4_pwm_stop ( dcmotor4_t *ctx );
```

- `dcmotor4_pwm_start` Start PWM module. 
```c
void dcmotor4_pwm_start ( dcmotor4_t *ctx );
```

### Application Init

> Initialization driver enable's - GPIO,
  set the direction-control of the motor forward movement, PWM initialization,
  set PWM duty cycle and PWM frequency, enable the motor, start PWM.
> 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor4_cfg_t cfg;

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

    dcmotor4_cfg_setup( &cfg );
    DCMOTOR4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms ( 100 );
    dcmotor4_init( &dcmotor4, &cfg );
    dcmotor4_pwm_start( &dcmotor4 );
}
```

### Application Task

>  This is an example that demonstrates the use of the DC Motor 4 Click board.
>  DC Motor 4 Click communicates with register via PWM interface.
>  It shows moving in the Clockwise direction from slow to fast speed
>  and from fast to slow speed, then rotating Counter Clockwise,
>  Results are being sent to the Usart Terminal where you can track their changes.
 

```c
void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor_direction == 1 )
    {
        dcmotor4_run_clockwise ( &dcmotor4 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
    }
    else
    {
        dcmotor4_run_counter_clockwise ( &dcmotor4 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
    }
    
    dcmotor4_set_duty_cycle ( &dcmotor4, duty );
    dcmotor4_enable_motor ( &dcmotor4 );
    
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        
        if ( dcmotor_direction == 1 )
        {
            dcmotor_direction = 0;
        }
        else
        {
            dcmotor_direction = 1;
        }
    }
    duty_cnt += duty_inc;

    dcmotor4_disable_motor ( &dcmotor4 );
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


---
# DC MOTOR  Click

> [DC MOTOR Click](https://www.mikroe.com/?pid_product=MIKROE-1526) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1526&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This application change the speed and direction of DC Motor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor

### Example Key Functions

- `dcmotor_cfg_setup` Config Object Initialization function. 
```c
void dcmotor_cfg_setup ( dcmotor_cfg_t *cfg );
``` 
 
- `dcmotor_init` Initialization function. 
```c
err_t dcmotor_init ( dcmotor_t *ctx, dcmotor_cfg_t *cfg );
```

- `dcmotor_pwm_start` Start PWM module. 
```c
void dcmotor_pwm_start ( dcmotor_t *ctx );
```
 
- `dcmotor_enable` Enable the motor function. 
```c
void dcmotor_enable ( dcmotor_t *ctx );
```

- `dcmotor_sleep_mode` Set sleep mode function. 
```c
void dcmotor_sleep_mode ( dcmotor_t *ctx );
```
### Application Init

> Initialization driver enable's - GPIO, PWM initialization, set PWM duty cycle and PWM frequency,
> enable the motor, start PWM and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor_cfg_t cfg;

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

    dcmotor_cfg_setup( &cfg );
    DCMOTOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor_init( &dcmotor, &cfg );

    log_printf( &logger, " Initialization  PWM \r\n" );
    
    dcmotor_set_duty_cycle ( &dcmotor, 0.0 );
    dcmotor_pwm_start( &dcmotor );
    log_printf( &logger, "---------------------\r\n" );
}
```

### Application Task

>  This is a example which demonstrates the use of DC Motor Click board.
>  DC Motor Click communicates with register via PWM interface.
>  It shows moving in the left direction from slow to fast speed
>  and from fast to slow speed.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor_direction == 1 )
    {
        dcmotor_sleep_mode ( &dcmotor );
        dcmotor_right_direction_slow ( &dcmotor );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
        dcmotor_enable ( &dcmotor );
    }
    else
    {
        dcmotor_sleep_mode ( &dcmotor );
        dcmotor_left_direction_slow ( &dcmotor );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        dcmotor_enable ( &dcmotor );
    }

    dcmotor_set_duty_cycle ( &dcmotor, duty );
    
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
        
        if ( dcmotor_direction == 1 )
        {
            dcmotor_direction = 0;
        }
        else if ( dcmotor_direction == 0 )
        {
            dcmotor_direction = 1;
        }
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

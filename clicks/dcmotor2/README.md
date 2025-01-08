
---
# DC Motor 2 Click

> [DC Motor 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1911) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1911&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This library contains API for the DC Motor 2 Click driver.
>  This example showcases how to initialize and use the DC Motor 2 Click. The Click contains a 
>  Driver IC for DC motors which can spin the motor clockwise, counter-clockwise, break it and
>  completely stop the motor. The example needs a DC motor and a power supply in order to work.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor2

### Example Key Functions

- `dcmotor2_cfg_setup` Config Object Initialization function. 
```c
void dcmotor2_cfg_setup ( dcmotor2_cfg_t *cfg );
``` 
 
- `dcmotor2_init` Initialization function. 
```c
err_t dcmotor2_init ( dcmotor2_t *ctx, dcmotor2_cfg_t *cfg );
```

- `dcmotor2_default_cfg` Click Default Configuration function. 
```c
void dcmotor2_default_cfg ( dcmotor2_t *ctx );
```

- This function sets the IN1/IN2 pins to 0/1 and makes the motor spin counter
  clockwise.
> void dcmotor2_spin_counter_clockwise ( dcmotor2_t *ctx );
 
- `dcmotor2_spin_clockwise` This function sets the IN1/IN2 pins to 1/0 and makes the motor spin clockwise. 
```c
void dcmotor2_spin_clockwise ( dcmotor2_t *ctx );
```

- `dcmotor2_pull_brake` This function sets the IN1/IN2 pins to 1/1 and forces the motor to break. 
```c
void dcmotor2_pull_brake ( dcmotor2_t *ctx );
```

- `dcmotor2_stop_motor` This function sets the IN1/IN2 pins to 0/0 and stops the motor completely. 
```c
void dcmotor2_stop_motor ( dcmotor2_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor2_cfg_t cfg;

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

    dcmotor2_cfg_setup( &cfg );
    DCMOTOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms ( 100 );
    dcmotor2_init( &dcmotor2, &cfg );
    dcmotor2_pwm_start( &dcmotor2 );
    Delay_ms ( 1000 );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

>  This is an example that demonstrates the use of the DC Motor 2 Click board.
>  DC Motor 2 Click communicates with register via PWM interface.
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
        dcmotor2_pull_brake ( &dcmotor2 );
        dcmotor2_spin_clockwise ( &dcmotor2 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
        dcmotor2_enable_motor ( &dcmotor2 );
    }
    else
    {
        dcmotor2_pull_brake ( &dcmotor2 );
        dcmotor2_spin_counter_clockwise ( &dcmotor2 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        dcmotor2_enable_motor ( &dcmotor2 );
    }

    dcmotor2_set_duty_cycle ( &dcmotor2, duty );
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
        else if ( dcmotor_direction == 0 )
        {
            dcmotor_direction = 1;
        }
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

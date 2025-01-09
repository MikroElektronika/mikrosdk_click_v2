
---
# DC Motor 3 Click

> [DC Motor 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2047) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2047&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This Click  has four operating modes: clockwise, counter-clockwise, short brake and stop. 
> The operating mode is configured through IN1 and IN2 pins. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor3

### Example Key Functions

- `dcmotor3_cfg_setup` Config Object Initialization function. 
```c
void dcmotor3_cfg_setup ( dcmotor3_cfg_t *cfg );
``` 
 
- `dcmotor3_init` Initialization function. 
```c
err_t dcmotor3_init ( dcmotor3_t *ctx, dcmotor3_cfg_t *cfg );
```

- `dcmotor3_default_cfg` Click Default Configuration function. 
```c
void dcmotor3_default_cfg ( dcmotor3_t *ctx );
```

- `dcmotor3_clockwise` This function set the direction of rotation in the clockwise direction by sets AN pin and clear RST pin. 
```c
void dcmotor3_clockwise ( dcmotor3_t *ctx );
```
 
- `dcmotor3_counter_clockwise` This function set the direction of rotation in the counter clockwise direction by clear AN pin and sets RST pin. 
```c
void dcmotor3_counter_clockwise ( dcmotor3_t *ctx );
```

- `dcmotor3_short_brake` This function brake the engine by sets AN and RST pins on DC Motor 3 Click board. 
```c
void dcmotor3_short_brake ( dcmotor3_t *ctx );
```

### Application Init

> Initialization driver enable's - GPIO,
> PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor3_cfg_t cfg;

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

    dcmotor3_cfg_setup( &cfg );
    DCMOTOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor3_init( &dcmotor3, &cfg );

    dcmotor3_set_duty_cycle ( &dcmotor3, 0.0 );
    dcmotor3_pwm_start( &dcmotor3 );
    Delay_ms ( 1000 );
    dcmotor3_enable( &dcmotor3 );
    Delay_ms ( 1000 );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

>  This is a example which demonstrates the use of DC Motor 3 Click board.
>  DC Motor 3 Click communicates with register via PWM interface.
>  It shows moving in the left direction from slow to fast speed
>  and from fast to slow speed.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor3_direction == 1 )
    {
        dcmotor3_clockwise( &dcmotor3 );
        log_printf( &logger, ">>>> CLOCKWISE " );
        dcmotor3_enable ( &dcmotor3 );
    }
    else
    {
        dcmotor3_counter_clockwise( &dcmotor3 );
        log_printf( &logger, "<<<< COUNTER CLOCKWISE " );
        dcmotor3_enable ( &dcmotor3 );
    }

    dcmotor3_set_duty_cycle ( &dcmotor3, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
                
        if ( dcmotor3_direction == 1 )
        {
            dcmotor3_direction = 0;
        }
        else if ( dcmotor3_direction == 0 )
        {
            dcmotor3_direction = 1;
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

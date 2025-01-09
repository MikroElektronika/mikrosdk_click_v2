
---
# DC Motor 9 Click

> [DC Motor 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3416) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3416&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> DC Motor 9 Click is a brushed DC motor driver with the current limiting and current sensing. It can
> be operated by two logic signals, allowing to drive the connected motor in two different ways: 
> it can use fixed logic levels for the direction control, or it can be controlled by a PWM signal, 
> offering an additional speed control option. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor9

### Example Key Functions

- `dcmotor9_cfg_setup` Config Object Initialization function. 
```c
void dcmotor9_cfg_setup ( dcmotor9_cfg_t *cfg );
``` 
 
- `dcmotor9_init` Initialization function. 
```c
err_t dcmotor9_init ( dcmotor9_t *ctx, dcmotor9_cfg_t *cfg );
```

- `dcmotor9_generic_read` This function read ADC data. 
```c
dcmotor9_data_t dcmotor9_generic_read ( dcmotor9_t *ctx );
```
 
- `dcmotor9_pwm_start` This function starts PWM module. 
```c
void dcmotor9_pwm_start ( dcmotor9_t *ctx );
```

- `dcmotor9_set_duty_cycle` This function sets the PWM duty cycle. 
```c
void dcmotor9_set_duty_cycle ( dcmotor9_t *ctx, float duty_cycle );
```

### Application Init

> Initializes GPIO, PWM and logger and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor9_cfg_t dcmotor9_cfg;

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

    dcmotor9_cfg_setup( &dcmotor9_cfg );
    DCMOTOR9_MAP_MIKROBUS( dcmotor9_cfg, MIKROBUS_1 );
    if ( dcmotor9_init( &dcmotor9, &dcmotor9_cfg ) == PWM_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }

    dcmotor9_set_duty_cycle ( &dcmotor9, DCMOTOR9_PWM_DUTY_PERCENT_0 );
    
    dcmotor9_enable( &dcmotor9 );
    dcmotor9_pwm_start( &dcmotor9 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}
```

### Application Task

>  This is a example which demonstrates the use of DC Motor 5 Click board.
>  DC Motor 9 Click controls DC Motor speed via PWM interface.
>  It shows moving in the both directions from slow to fast speed
>  and from fast to slow speed.
>  Results are being sent to the Usart Terminal where you can track their changes.
```c
void application_task ( void )
{
    static float duty;
    static uint8_t n_cnt;
    
    dcmotor9_clockwise ( &dcmotor9 );
    log_printf( &logger, "> CLOCKWISE <\r\n" );
    dcmotor9_enable ( &dcmotor9 );
    
    for ( n_cnt = 10; n_cnt > 0; n_cnt--  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++ )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9,  duty );
        Delay_ms ( 500 );
    }
    
    log_printf( &logger, "* Pull break *\r\n" );
    dcmotor9_short_brake( &dcmotor9 );
    Delay_ms ( 1000 );
    
    dcmotor9_counter_clockwise ( &dcmotor9 );
    log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 10; n_cnt > 0; n_cnt-- )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9,  duty );
        Delay_ms ( 500 );
    }
    
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

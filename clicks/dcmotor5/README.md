
---
# DC MOTOR 5 Click

> [DC Motor 5 Click](https://www.mikroe.com/?pid_product=MIKROE-2699) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2699&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This library contains API for the DC Motor 5 Click driver.
>  This application enables usage of brushed DC motor 5 gate driver.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor5

### Example Key Functions

- `dcmotor5_cfg_setup` Config Object Initialization function. 
```c
void dcmotor5_cfg_setup ( dcmotor5_cfg_t *cfg );
``` 
 
- `dcmotor5_init` Initialization function. 
```c
err_t dcmotor5_init ( dcmotor5_t *ctx, dcmotor5_cfg_t *cfg );
```

- `dcmotor5_short_brake` Function brakes the engine by setting IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board. 
```c
void dcmotor5_short_brake ( dcmotor5_t *ctx );
```
 
- `dcmotor5_stop` Function stops the engine by clearing IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board. 
```c
void dcmotor5_stop ( dcmotor5_t *ctx );
```

- `dcmotor5_enable` Function disables the engine by clearing SLEEP ( RST ) pin on DC Motor 5 Click board. 
```c
void dcmotor5_enable ( dcmotor5_t *ctx );
```

### Application Init

> Initializes GPIO, PWM and logger and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor5_cfg_t cfg;

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

    dcmotor5_cfg_setup( &cfg );
    DCMOTOR5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor5_init( &dcmotor5, &cfg );
    
    log_printf( &logger, " Initialization  PWM \r\n" );

    dcmotor5_pwm_start( &dcmotor5 );
    dcmotor5_enable ( &dcmotor5 );
    Delay_ms ( 500 );
    log_printf( &logger, "---------------------\r\n" );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

> This is a example which demonstrates the use of DC Motor 5 Click board.
> DC Motor 5 Click controls DC Motor speed via PWM interface.
> It shows moving in the both directions from slow to fast speed
> and from fast to slow speed.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( )
{    
    static float duty;
    static uint8_t n_cnt;
    
    
    dcmotor5_clockwise ( &dcmotor5 );
    log_printf( &logger, "\r\n> CLOCKWISE <\r\n" );
    dcmotor5_enable ( &dcmotor5 );
    
    for ( n_cnt = 10; n_cnt > 0; n_cnt--  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        log_printf( &logger, " >" );
        dcmotor5_set_duty_cycle( &dcmotor5, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++ )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        log_printf( &logger, " <" );
        dcmotor5_set_duty_cycle( &dcmotor5,  duty );
        Delay_ms ( 500 );
    }
    
    log_printf( &logger, "\r\n * Pull break *\r\n" );
    dcmotor5_short_brake( &dcmotor5 );
    Delay_ms ( 1000 );
    
    dcmotor5_counter_clockwise ( &dcmotor5 );
    log_printf( &logger, "\r\n> COUNTER CLOCKWISE <\r\n" );
        
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor5_set_duty_cycle( &dcmotor5, duty );
        log_printf( &logger, " >" );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 10; n_cnt > 0; n_cnt-- )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor5_set_duty_cycle( &dcmotor5,  duty );
        log_printf( &logger, " <" );
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

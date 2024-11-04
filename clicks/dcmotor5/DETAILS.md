
---
# DC MOTOR 5 Click

DC MOTOR 5 Click carries the DRV8701 brushed DC motor gate driver from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-5-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the DcMotor5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly from compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor5_cfg_setup ( dcmotor5_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR5_RETVAL dcmotor5_init ( dcmotor5_t *ctx, dcmotor5_cfg_t *cfg );

#### Example key functions :

- Function brakes the engine by setting IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board.
> void dcmotor5_short_brake ( dcmotor5_t *ctx );
 
- Function stops the engine by clearing IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board.
> void dcmotor5_stop ( dcmotor5_t *ctx );

- Function disables the engine by clearing SLEEP ( RST ) pin on DC Motor 5 Click board.
> void dcmotor5_enable ( dcmotor5_t *ctx );

## Examples Description

>  This library contains API for the DC Motor 5 Click driver.
>  This application enables usage of brushed DC motor 5 gate driver.

**The demo application is composed of two sections :**

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
 

The full application code, and ready to use projects can be installed directly form compilers IDE(recommended) or found on LibStock page or mikroE GitHub account.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor5

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

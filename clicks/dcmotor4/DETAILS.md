
---
# DC Motor 4 click

DC MOTOR 4 click is capable of driving motors with a supply voltage from 4.5V to 36V. It carries the MAX14870 motor driver from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-4-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the DcMotor4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor4_cfg_setup ( dcmotor4_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR4_RETVAL dcmotor4_init ( dcmotor4_t *ctx, dcmotor4_cfg_t *cfg );


#### Example key functions :

- Generic sets PWM duty cycle.
> void dcmotor4_set_duty_cycle ( dcmotor4_t *ctx, pwm_data_t duty_cycle );
 
- Stop PWM module.
> void dcmotor4_pwm_stop ( dcmotor4_t *ctx );

- Start PWM module.
> void dcmotor4_pwm_start ( dcmotor4_t *ctx );

## Examples Description
 
>  This library contains API for the DC Motor 4 Click driver.
>  Application change the speed and direction.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

\mainpage Main Page
 
---
# Brushless 5 click

Brushless 5 click is a 3 phase sensorless BLDC motor controller, with a soft-switching feature for reduced motor noise and EMI, and precise BEMF motor sensing, which eliminates the need for Hall-sensors in motor applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-5-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless5_cfg_setup ( brushless5_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS5_RETVAL brushless5_init ( brushless5_t *ctx, brushless5_cfg_t *cfg );

#### Example key functions :

- Generic sets PWM duty cycle.
> void brushless5_set_duty_cycle ( brushless5_t *ctx, float duty_cycle );
 
- Stop PWM module.
> void brushless5_pwm_stop ( brushless5_t *ctx );

- Start PWM module.
> void brushless5_pwm_start ( brushless5_t *ctx );

## Examples Description

>  This library contains an API for the Brushless5 Click driver.
>  This example showcases how to initialize and use the Brushless 5 click. 
>  The click has a brushless 5 motor driver which controls the work 
>  of the motor through the BLDC terminal. 
>  In order for this example to work a motor and a power supply are needed.

**The demo application is composed of two sections :**

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
    Delay_ms( 100 );

    //  Click initialization.

    brushless5_cfg_setup( &cfg );
    BRUSHLESS5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless5_init( &brushless5, &cfg );
    Delay_ms( 100 );
    
    brushless5_set_duty_cycle ( &brushless5, 0.0 );
    brushless5_pwm_start( &brushless5 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 1000 );
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
    Delay_ms( 500 );

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
    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless5

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

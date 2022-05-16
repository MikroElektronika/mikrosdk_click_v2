
---
# Brushless 4 click

Brushless 4 click is a 3 phase sensorless BLDC motor driver, which features a 180° sinusoidal drive, providing high efficiency and low acoustic noise. This type of drivers inherently provides higher torque in general, compared to classical 120° BLDC motor drivers. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-4-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless4_cfg_setup ( brushless4_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS4_RETVAL brushless4_init ( brushless4_t *ctx, brushless4_cfg_t *cfg );

- Click Default Configuration function.
> void brushless4_default_cfg ( brushless4_t *ctx );


#### Example key functions :

- This function sets the PWM duty cycle.
> void brushless4_set_duty_cycle ( brushless4_t *ctx, pwm_data_t duty_cycle );
 
- This function starts PWM module.
> void brushless4_pwm_start ( brushless4_t *ctx );

- This function sets the state of the PWM pin.
> void brushless4_pwm_pin ( brushless4_t *ctx, uint8_t state );

## Examples Description

> This click has many features for driving a wide range of small to medium BLDC motors.
> It provides the rotor position digital output, via the FG pin, routed to the mikroBUS INT pin. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the GPIO driver and configures the PWM peripheral for controlling the speed of the motor.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless4_cfg_t cfg;

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

    brushless4_cfg_setup( &cfg );
    BRUSHLESS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless4_init( &brushless4, &cfg );
    
    brushless4_set_duty_cycle ( &brushless4, 0.0 );
    brushless4_pwm_start( &brushless4 );  
      
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 1000 );
}
  
```

### Application Task

>  This is an example that demonstrates the use of a Brushless 4 Click board.
>  Brushless 4 Click communicates with the register via the PWM interface.  
>  Increases and decreasing the speed of the motor demonstrate speed control.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    brushless4_set_duty_cycle ( &brushless4, duty );
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
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless4

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

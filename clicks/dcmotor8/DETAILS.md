
---
# DC Motor 8 click

DC Motor 8 click is a DC motor driver. It can drive simple DC motors with brushes, providing them with a significant amount of current and voltage up to 40V. The click has one control input, that uses the PWM signal from the host MCU. It uses the half-bridge topology to regulate the speed of the motor rotation, employs advanced dead-time circuitry that monitors the output stage, providing maximum switching efficiency and features an advanced technique to avoid shoot-through currents.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-8-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the DcMotor8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor8_cfg_setup ( dcmotor8_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR8_RETVAL dcmotor8_init ( dcmotor8_t *ctx, dcmotor8_cfg_t *cfg );


#### Example key functions :

- This function sets the PWM duty cycle.
> void dcmotor8_set_duty_cycle ( dcmotor8_t *ctx, float duty_cycle );
 
- This function starts PWM module.
> void dcmotor8_pwm_start ( dcmotor8_t *ctx );

- This function stops PWM module.
> void dcmotor8_pwm_stop ( dcmotor8_t *ctx );

## Examples Description

> This click can drive simple DC motors with brushes, providing them with a significant amount 
> of current and voltage up to 40V. The click has one control input, that uses the PWM signal 
> from the host MCU. It uses the half-bridge topology to regulate the speed of the motor 
> rotation, employs advanced dead-time circuitry that monitors the output stage, providing 
> maximum switching efficiency and features an advanced technique to avoid shoot-through 
> currents.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor8_cfg_t cfg;

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

    dcmotor8_cfg_setup( &cfg );
    DCMOTOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor8_init( &dcmotor8, &cfg );

    dcmotor8_set_duty_cycle ( &dcmotor8, 0.0 );
    dcmotor8_enable ( &dcmotor8, DCMOTOR8_ENABLE );
    dcmotor8_pwm_start( &dcmotor8 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 500 );
}
  
```

### Application Task

>  This is an example that demonstrates the use of DC Motor 8 click
>  board by increasing and decreasing the motor speed.
>  DC Motor 8 Click communicates with the register via the PWM interface.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    dcmotor8_set_duty_cycle ( &dcmotor8, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}
 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor8

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

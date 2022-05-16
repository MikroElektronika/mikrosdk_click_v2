\mainpage Main Page

---
# Pwm Driver click

If you need to control DC motors with loads up to 10A, PWM driver click is the perfect solution, thanks to the Silicon Lab Si8711CC one-channel isolator. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwmdriver_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pwm-driver-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the PwmDriver Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PwmDriver Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pwmdriver_cfg_setup ( pwmdriver_cfg_t *cfg ); 
 
- Initialization function.
> PWMDRIVER_RETVAL pwmdriver_init ( pwmdriver_t *ctx, pwmdriver_cfg_t *cfg );

- Click Default Configuration function.
> void pwmdriver_default_cfg ( pwmdriver_t *ctx );


#### Example key functions :

- Generic sets PWM duty cycle
> void pwmdriver_set_duty_cycle ( pwmdriver_t *ctx, pwm_data_t duty_cycle );
 
- Stop PWM module.
> void pwmdriver_pwm_stop ( pwmdriver_t *ctx );

- Start PWM module
> void pwmdriver_pwm_start ( pwmdriver_t *ctx );

## Examples Description

> This application is controls the speed DC motors.

**The demo application is composed of two sections :**

### Application Init 

>Initialization driver enables - GPIO, PWM initialization set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start to write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwmdriver_cfg_t cfg;

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

    pwmdriver_cfg_setup( &cfg );
    PWMDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwmdriver_init( &pwmdriver, &cfg );

    Delay_ms( 100 );
    
    log_printf( &logger, "   Initialization PWM  \r\n  " );
    pwmdriver_set_duty_cycle( &pwmdriver, 0.0 );
    pwmdriver_pwm_start( &pwmdriver );
    Delay_ms( 1000 );
    log_info( &logger, "---- Application Task ----" );
}
  
```

### Application Task

> This is an example that demonstrates the use of the PWM driver Click board.
> This example shows the automatic control of PWM,
> the first increases duty cycle and then the duty cycle is falling.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    pwmdriver_set_duty_cycle ( &pwmdriver, duty );
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
- Click.PwmDriver

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

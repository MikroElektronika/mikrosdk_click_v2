\mainpage Main Page
 
---
# Led Driver 5 Click

LED Driver 5 Click is a Click board™ capable of driving an array of high-power LEDs with constant current, up to 1.5A. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/led-driver-5-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Mar 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the LedDriver5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver5_cfg_setup ( leddriver5_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER5_RETVAL leddriver5_init ( leddriver5_t *ctx, leddriver5_cfg_t *cfg );

- Click Default Configuration function.
> void leddriver5_default_cfg ( leddriver5_t *ctx );


#### Example key functions :

- Generic sets PWM duty cycle.
> void leddriver5_set_duty_cycle ( leddriver5_t *ctx, pwm_data_t duty_cycle );
 
- Stop PWM module.
> void leddriver5_pwm_stop ( leddriver5_t *ctx );

- Start PWM module
> void leddriver5_pwm_start ( leddriver5_t *ctx );

## Examples Description

> This app enables usage of compact, high-efficiency, fixed frequency,
> synchronous step-up converter, optimized to drive one LED with the constant current.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - GPIO,
> PWM initialization set PWM duty cycle and start PWM. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver2_cfg_t cfg;

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

    leddriver2_cfg_setup( &cfg );
    LEDDRIVER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver2_init( &leddriver2, &cfg );

    leddriver2_pwm_start( &leddriver2 );
}

  
```

### Application Task

>  This is an example that demonstrates the use of the LED Driver 5 Click board.
>  This example shows the automatic control of Led light intensity,
>  the first intensity of light is rising and then the intensity of light is falling.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver5_set_duty_cycle( &leddriver5, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
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
- Click.LedDriver5

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

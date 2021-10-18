
---
# LED Driver 2 click

LED driver 2 click carries the MCP1643 - LED constant current regulator, made by Microchip. It is a compact, high-efficiency, 
fixed frequency, synchronous step-up converter, optimized to drive one LED with the constant current. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the LedDriver2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver2_cfg_setup ( leddriver2_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER2_RETVAL leddriver2_init ( leddriver2_t *ctx, leddriver2_cfg_t *cfg );


#### Example key functions :

- This function sets the PWM duty cycle
> void leddriver2_set_duty_cycle ( leddriver2_t *ctx, pwm_data_t duty_cycle );
 
- This function stops PWM module.
> void leddriver2_pwm_stop ( leddriver2_t *ctx );

- This function starts PWM module.
> void leddriver2_pwm_start ( leddriver2_t *ctx );

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

> This is an example which demonstrates the use of LED Driver 2 Click board.
> This example shows the automatic control halogen bulb light intensity,
> the first intensity of light is rising and then the intensity of light is falling.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    log_printf( &logger, " Light Intensity Rising  \r\n" );
    Delay_1sec( );

    for( duty_cycle = 0.1; duty_cycle < 1.0; duty_cycle += 0.1 )
    {
        leddriver2_set_duty_cycle( &leddriver2, duty_cycle );
        log_printf( &logger, "  > " );
        Delay_ms( 500 );
    }
        
    log_printf( &logger, "\r\n-------------------------\r\n" );
    log_printf( &logger, " Light Intensity Falling \r\n" );
    Delay_1sec( );
    
    for( duty_cycle = 1.0; duty_cycle > 0.0; duty_cycle -= 0.1 )
    {
        leddriver2_set_duty_cycle( &leddriver2, duty_cycle );
        log_printf( &logger, "  < " );
        Delay_ms( 500 );
    }

    log_printf( &logger, "\r\n-------------------------\r\n" );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver2

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

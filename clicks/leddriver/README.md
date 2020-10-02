\mainpage Main Page
 
---
# LED DRIVER click

LED driver click carries the MCP1662 high-voltage step-up voltage driver from Microchip. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over PWM pin on the mikroBUS™ line

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/led-driver-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the LedDriver Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver_cfg_setup ( leddriver_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER_RETVAL leddriver_init ( leddriver_t *ctx, leddriver_cfg_t *cfg );


#### Example key functions :

## Examples Description

> This application controls the brightness. 

**The demo application is composed of two sections :**

### Application Init 

> PWM initialization set PWM duty cycle and PWM frequency and start PWM.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver_cfg_setup( &cfg );
    LEDDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver_init( &leddriver, &cfg );

    log_printf( &logger, "   Initialization PWM    \r\n" );
    leddriver_set_duty_cycle( &leddriver, duty_cycle );
    leddriver_pwm_start( &leddriver );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_100ms();
}
  
```

### Application Task

> This is an example which demonstrates the use of LED Driver Click board.LED Driver Click communicates with register via PWM interface. This example shows the automatic control halogen bulb light intensity, the first intensity of light is rising and then the intensity of light is falling. Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    
    if ( duty_cycle > leddriver.pwm_period )
    {
        duty_cycle = 100;
    }
    
    leddriver_set_duty_cycle ( &leddriver, duty_cycle );
    duty_cycle += 50;
    Delay_100ms();

    log_printf( &logger, " Light Intensity Rising  \r\n" );
    Delay_1sec();

    for ( duty_cycle = 5; duty_cycle < 255; duty_cycle += 25 )
    {
        leddriver_set_duty_cycle(  &leddriver, duty_cycle );
        log_printf( &logger, " >\r\n" );
        Delay_1sec();
    }

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, " Light Intensity Falling \r\n" );
    Delay_1sec();

    for ( duty_cycle = 255; duty_cycle > 5; duty_cycle -= 25 )
    {
        leddriver_set_duty_cycle(  &leddriver, duty_cycle );
        log_printf( &logger, " <\r\n" );
        Delay_1sec();
    }

    log_printf( &logger, "-------------------------\r\n" );
    Delay_1sec();
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver

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

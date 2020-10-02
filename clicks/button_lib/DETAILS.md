
---
# Button library click

<Every Button click is a very interesting interactive gadget on a Click board™. It is an integrated capacitive touch sensor display in the form of a button.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/button-click-group.png" height=300px>
</p>

> * [Product page - Button Play click](<https://www.mikroe.com/button-play-click>)

> * [Product page - Button Power click](<https://www.mikroe.com/button-power-click>)

> * [Product page - Button Alarm click](<https://www.mikroe.com/button-alarm-click>)

> * [Product page - Button Y click](<https://www.mikroe.com/button-y-click>)

> * [Product page - Button G click](<https://www.mikroe.com/button-g-click>)

> * [Product page - Button R click](<https://www.mikroe.com/button-r-click>)
---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type

# Software Support

We provide a library for the ButtonLibrary Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ButtonLibrary Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buttonlibrary_cfg_setup ( buttonlibrary_cfg_t *cfg ); 
 
- Initialization function.
> BUTTONLIBRARY_RETVAL buttonlibrary_init ( buttonlibrary_t *ctx, buttonlibrary_cfg_t *cfg );

- Click Default Configuration function.
> void buttonlibrary_default_cfg ( buttonlibrary_t *ctx );


#### Example key functions :

- This function sets the PWM duty cycle.
> void buttonlibrary_set_duty_cycle ( buttonlibrary_t *ctx, pwm_data_t duty_cycle );
 
- This function starts PWM module.
> void buttonlibrary_pwm_start ( buttonlibrary_t *ctx );

- This function reads the digital signal from the INT pin which tells us whether
  the button has been pressed or not.
> uint8_t buttonlibrary_get_button_state ( buttonlibrary_t *ctx );

## Examples Description

> This example showcases how to initialize and use the whole family of Button clicks. One library
  is used for every single one of them. They are simple touch detectors which send a pressed/
  released signal and receive a PWM output which controls the backlight on the button.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    buttonlibrary_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_100ms( );

    //  Click initialization.

    buttonlibrary_cfg_setup( &cfg );
    BUTTONLIBRARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms( );
    buttonlibrary_init( &buttonlibrary, &cfg );
    buttonlibrary_pwm_start( &buttonlibrary );
    Delay_100ms( );
}
  
```

### Application Task

> This function first turns the backlight on the button ON/OFF and then checks if the button
  has been pressed and reports the event in the console using UART communication.

```c

void application_task ( )
{    
    if ( duty_cycle > buttonlibrary.pwm_period )
    {
        duty_cycle = 0;
    }

    button_state = buttonlibrary_get_button_state( &buttonlibrary );

    backlight_on( );
    backligh_off( );
    button_pressed( );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ButtonLibrary

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---

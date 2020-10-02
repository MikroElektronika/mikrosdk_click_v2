 

---
# ButtonR click

Button R Click is the simplest solution for adding a single pushbutton to your design. The button itself is transparent, 6.8mm in diameter and has a red LED backlight.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](<https://www.mikroe.com/button-r-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the ButtonR Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ButtonR Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buttonr_cfg_setup ( buttonr_cfg_t *cfg ); 
 
- Initialization function.
> BUTTONR_RETVAL buttonr_init ( buttonr_t *ctx, buttonr_cfg_t *cfg );

- Click Default Configuration function.
> void buttonr_default_cfg ( buttonr_t *ctx );


#### Example key functions :

- Function detecting states when button is pressed and returns the state of the INT pin.
> uint8_t buttonr_press_button( buttonr_t *ctx );
 
- Function turn on light on the button set PWM pin high.
> void buttonr_turn_on_led( buttonr_t *ctx );

- Function turn off light on the button set PWM pin low.
> void buttonr_turn_off_led( buttonr_t *ctx );

## Examples Description

> This is a example which demonstrates the use of Button R Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - Start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buttonr_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    buttonr_cfg_setup( &cfg );
    BUTTONR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buttonr_init( &buttonr, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of Button R Click board.

```c

void application_task ( void )
{
    //  Task implementation.

    buttonr_state = buttonr_press_button( &buttonr );

    if ( buttonr_state == 1 && buttonr_state_old == 0 )
    {
        buttonr_state_old = 1;
        log_printf(&logger, "CLICK\n");

        if ( buttonr_led_state == 0 )
        {
            buttonr_led_state = 1;
            buttonr_turn_on_led( &buttonr );
            log_printf(&logger, "ON\r\n");
        }
        else
        {
            buttonr_led_state = 0;
            buttonr_turn_off_led( &buttonr );
            log_printf(&logger, "OFF\r\n");
        }

        Delay_ms( 100 );
    }

    if ( buttonr_state == 0 && buttonr_state_old == 1 )
    {
        buttonr_state_old = 0;
        Delay_ms( 100 );
    }

}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ButtonR

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

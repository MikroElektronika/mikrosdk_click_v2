

---
# Button G click

Button G click is the simplest solution for adding a single pushbutton to your design. The button itself is transparent, 6.8mm in diameter and has a green LED backlight.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](<https://www.mikroe.com/button-g-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the ButtonG Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ButtonG Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buttong_cfg_setup ( buttong_cfg_t *cfg ); 
 
- Initialization function.
> BUTTONG_RETVAL buttong_init ( buttong_t *ctx, buttong_cfg_t *cfg );

- Click Default Configuration function.
> void buttong_default_cfg ( buttong_t *ctx );


#### Example key functions :

- This function is detecting button press state.
> uint8_t buttong_press_button( buttong_t *ctx );
 
- This function turns on the light on the button.
> void buttong_turn_on_led( buttong_t *ctx );

- This function turns off the light on the button.
> void buttong_turn_off_led( buttong_t *ctx );

## Examples Description

> This example turns the light on the button on and off.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buttong_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    buttong_cfg_setup( &cfg );
    BUTTONG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buttong_init( &buttong, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of Button G Click board.

```c

void application_task ( void )
{
    buttong_state = buttong_press_button( &buttong );

    if ( buttong_state == 1 && buttong_state_old == 0 )
    {
        buttong_state_old = 1;
        log_printf( &logger, "CLICK \n");
        
        if ( led_state == 0 )
        {
            led_state = 1;
            buttong_turn_on_led( &buttong );
            log_printf( &logger, "ON\r\n");
        }
        else
        {
            led_state = 0;
            buttong_turn_off_led( &buttong );
            log_printf( &logger, "OFF\r\n");
        }
        
        Delay_ms( 100 );
    }

    if ( buttong_state == 0 && buttong_state_old == 1 )
    {
        buttong_state_old = 0;
        Delay_ms( 100 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ButtonG

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

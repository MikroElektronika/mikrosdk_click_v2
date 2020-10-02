
---
# OLED Switch click

If you are building any type of human machine interface, OLED Switch click can help you keep the design simple, clear and interactive. It can be used in designing a control panel for an industrial machine… or a DIY arcade.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oledswitch_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/oled-switch-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the OledSwitch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OledSwitch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void oledswitch_cfg_setup ( oledswitch_cfg_t *cfg ); 
 
- Initialization function.
> OLEDSWITCH_RETVAL oledswitch_init ( oledswitch_t *ctx, oledswitch_cfg_t *cfg );

- Click Default Configuration function.
> void oledswitch_default_cfg ( oledswitch_t *ctx );


#### Example key functions :

- This function writes to control and configuration registers on the chip.
> oledswitch_reg_write ( oledswitch_t *ctx, uint8_t *write_buf, uint8_t len );
 
- This function sets the digital output signal for the PWM pin.
> void oledswitch_digital_write_pwm ( oledswitch_t *ctx, uint8_t signal );

- This function sets the digital output signal for the RST pin.
> void oledswitch_digital_write_rst ( oledswitch_t *ctx, uint8_t signal );

## Examples Description

> This example showcases how to configure and use the OLED Switch click. This click is a 
  combination of a button and a full color organic LED display. Displays settings are first
  loaded onto the chip and after that you can show any 64x48 pixel image on the display. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. In order for the
  click to work properly, you need to configure display and power settings. The full init-
  ialization of the chip is done in the default_cfg(...) function. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    oledswitch_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    oledswitch_cfg_setup( &cfg );
    OLEDSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oledswitch_init( &oledswitch, &cfg );
    oledswitch_default_cfg( &oledswitch, OLEDSWITCH_BUFFER_SIZE_SMALL );
}
  
```

### Application Task

> This function shows the user how to display images on the OLED screen. Every image you'd
  like to display needs to have a resolution of 64x48 and be stored in a 6144 cell array. 

```c

void application_task ( )
{
    oledswitch_draw_image( &oledswitch, array_red, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );

    oledswitch_draw_image( &oledswitch, array_green, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );

    oledswitch_draw_image( &oledswitch, array_blue, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );
} 

```

## Note

> Every pixel on the OLED screen is displayed at the time of writing to the chip (PWM 1).
  Displaying speed can be directly controled by adding delays in the for loop section of 
  the draw_image(...) function. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OledSwitch

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

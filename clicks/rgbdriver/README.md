\mainpage Main Page
 
 

---
# RGB Driver click

RGB Driver click is an RGB LED driver, capable of driving RGB LED stripes, LED fixtures and other RGB LED applications that demand an increased amount of current and voltage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rgbdriver_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/rgb-driver-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the RgbDriver Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RgbDriver Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rgbdriver_cfg_setup ( rgbdriver_cfg_t *cfg ); 
 
- Initialization function.
> RGBDRIVER_RETVAL rgbdriver_init ( rgbdriver_t *ctx, rgbdriver_cfg_t *cfg );

- Click Default Configuration function.
> void rgbdriver_default_cfg ( rgbdriver_t *ctx );


#### Example key functions :

- This function sets the color of the rgb LEDs through the parameters for red, green and blue.
> void rgbdriver_set_rgb_color ( rgbdriver_t *ctx, uint8_t red, uint8_t green, uint8_t blue );
 
- This function sets the color.
> void rgbdriver_set_color ( rgbdriver_t *ctx, uint32_t color );

- This function shut down device.
> void rgbdriver_shut_down ( rgbdriver_t *ctx );

## Examples Description

> This app sets the brightness over rgb value.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialize.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rgbdriver_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    rgbdriver_cfg_setup( &cfg );
    RGBDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rgbdriver_init( &rgbdriver, &cfg );
}
  
```

### Application Task

> Sets the brightness over rgb value,
> Red value sets from 0x60 to 0x7F,
> Green value sets from 0x80 to 0x9F and
> Blue value sets from 0x40 to 0x5F.

```c

void application_task ( void )
{
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_RED );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_YELLOW );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_BLUE );
    Delay_1sec( );
    rgbdriver_set_rgb_color( &rgbdriver, 0x40, 0x9F, 0x60 );
    Delay_1sec( );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RgbDriver

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

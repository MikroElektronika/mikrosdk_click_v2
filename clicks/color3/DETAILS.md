
---
# Color 3 click

< Color 3 click is a mikroBUS™ add-on board with a TCS3771 color sensor (also known as a light-to-digital converter) and a narrow beam Infrared LED. The circuit can also function as a proximity sensor >

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/color3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/color-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color3_cfg_setup ( color3_cfg_t *cfg ); 
 
- Initialization function.
> COLOR3_RETVAL color3_init ( color3_t *ctx, color3_cfg_t *cfg );



#### Example key functions :

-  Function is used to figure out dominant color.
> float color3_get_color_value ( color3_t *ctx );
 
- Function is used to read clear, red, blue and green data values.
> void color_3_get_crgb_data ( color3_t *ctx, uint16_t *clear_data, uint16_t *red_data, uint16_t *green_data, uint16_t *blue_data );

- Function is used to apply default settings.
> void color3_set_default_settings ( color3_t *ctx );

## Examples Description

> This application return the color of object.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, applies default settings and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    color3_cfg_setup( &cfg );
    COLOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color3_init( &color3, &cfg );
    Delay_ms( 100 );

    color3_set_default_settings( &color3 );
    Delay_ms( 1000 );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Color 3  Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );
}
  
```

### Application Task

> This example demonstrates the use of Color 3 Click board. It reads 
  reflected color values and displays the results on USART terminal.

```c

void application_task ( void )
{
    clear_data = color3_read_clear_data( &color3 );
    log_printf( &logger, " Clear: %f\r\n", clear_data );

    red_data = color3_read_red_data( &color3 );
    log_printf( &logger, " Red: %d\r\n", red_data);

    green_data = color3_read_green_data( &color3 );
    log_printf( &logger, " Green: %d\r\n", green_data );

    blue_data = color3_read_blue_data( &color3 );
    log_printf( &logger, " Blue: %d\r\n", blue_data );

    log_printf( &logger, "-----------------\r\n" );
    Delay_ms( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color3

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

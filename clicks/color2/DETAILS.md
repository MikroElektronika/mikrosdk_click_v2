
---
# Color 2 click

Color 2 click carries the ISL29125 RGB color light sensor. It detects red, green and blue in a variety of lighting conditions, outputting 16-bit resolution data in a measuring range from 5.7 m lux to 10,000 lux.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/color2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/color-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color2_cfg_setup ( color2_cfg_t *cfg ); 
 
- Initialization function.
> COLOR2_RETVAL color2_init ( color2_t *ctx, color2_cfg_t *cfg );

- Click Default Configuration function.
> void color2_default_cfg ( color2_t *ctx );


#### Example key functions :

- Function read blue color data from ISL29125
> float color2_read_blue( color2_t *ctx );
 
- Function read byte of data from register address of ISL29125
> uint8_t color2_read_data( color2_t *ctx, uint8_t address );

- Function write byte of data to ISL29125
> void color2_write_data( color2_t *ctx, uint8_t address, uint8_t write_command );

## Examples Description

> Example demonstrates use of Color 2 click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - initialize ISL29125 RGB color light sensor and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    color2_cfg_setup( &cfg );
    COLOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color2_init( &color2, &cfg );
    color2_default_cfg ( &color2 );
}
  
```

### Application Task

> This is a example which demonstrates the use of Color 2 Click board.
> ISL29125 RGB color light sensor on Color 2 Click, detects red, green and blue in a variety of lighting conditions
> and outputting 16-bit resolution data on the USBUART.
> Also read color and check which color is detected by the sensor.
> If the color is detected, the detected color message is logged on the USBUART.
> All data logs on usb uart for aproximetly every 3 sec.

```c

void application_task ( void )
{
    //  Task implementation.

    uint16_t value_red_color;
    uint16_t value_green_color;
    uint16_t value_blue_color;
    uint8_t is_color;
    float color_value;

    color_value = color2_get_color_value( &color2 );
    is_color = color2_get_color( color_value );

    value_green_color = color2_read_green( &color2 );
    value_red_color = color2_read_red( &color2 );
    value_blue_color = color2_read_blue( &color2 );

    switch(is_color)
    {
        case 1:
        {
            log_printf( &logger, "    *** ORANGE ***");
            break;
        }
        case 2:
        {
            log_printf( &logger, "    *** RED ***");
            break;
        }
        case 3:
        {
            log_printf( &logger, "    *** PINK ***");
            break;
        }
        case 4:
        {
            log_printf( &logger, "    *** PURPLE ***");
            break;
        }
        case 5:
        {
            log_printf( &logger, "    *** BLUE ***");
            break;
        }
        case 6:
        {
            log_printf( &logger, "    *** CYAN ***");
            break;
        }
        case 7:
        {
            log_printf( &logger, "    *** GREEN ***");
            break;
        }
        case 8:
        {
            log_printf( &logger, "    *** YELLOW ***");
            break;
        }
        default:
        {
            break;
        }
    }

    log_printf( &logger, "----------------------");
    
    log_printf( &logger, " Red  value  : %d", value_red_color);
    log_printf( &logger, " Green  value  : %d", value_green_color);
    log_printf( &logger, " Blue  value  : %d", value_blue_color);

    log_printf( &logger, "----------------------");

    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color2

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

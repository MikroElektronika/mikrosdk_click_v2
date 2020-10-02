\mainpage Main Page
 
 

---
# Color 8 click

Color 8 click is a color-sensing Click board™, a part of our sensor Click board™ line. Sensing the color by utilizing ROHM’s BH1749NUC, an integrated color sensor IC, it comes in the package which also includes the mikroSDK™ software, a library with all the functions.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/color8_click.png" height=300px>
</p>>

[click Product page](<https://www.mikroe.com/color-8-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color8_cfg_setup ( color8_cfg_t *cfg ); 
 
- Initialization function.
> COLOR8_RETVAL color8_init ( color8_t *ctx, color8_cfg_t *cfg );


#### Example key functions :

- This function reads data from register.
> uint16_t color8_read_data ( color8_t *ctx, uint8_t reg_data );
 
- This functions reads 3 color filters and Clear Filters and converts the resulting color from RGB to HSL.
> float color8_get_color_value ( color8_t *ctx );

- This function detect colors.
> uint8_t color8_get_color ( color8_t *ctx, float color_value );

## Examples Description

> This demo app reads RED, GREEEN, BLUE, IR data and return detect color.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device device configuration for start measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color8_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    color8_cfg_setup( &cfg );
    COLOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color8_init( &color8, &cfg );

    color8_default_cfg( &color8 );
    log_printf( &logger, "---- Start measurement ----\r\n");
}
  
```

### Application Task

> Reads RED, GREEEN, BLUE and IR data. 
> Converts data to HSL value and return detect color.

```c

void application_task ( void )
{
    uint16_t red_data;
    uint16_t green_data;
    uint16_t blue_data;
    uint16_t ir_data;
    uint8_t is_color;
    float color_value;
    
    red_data = color8_read_data( &color8, COLOR8_REG_RED_DATA );
    log_printf( &logger, " RED data : %d \r\n", red_data );

    green_data = color8_read_data( &color8, COLOR8_REG_GREEN_DATA );
    log_printf( &logger, " GREEN data : %d \r\n", green_data );

    blue_data = color8_read_data( &color8, COLOR8_REG_BLUE_DATA );
    log_printf( &logger, " BLUE data : %d \r\n", blue_data );

    ir_data = color8_read_data( &color8, COLOR8_REG_IR_DATA );
    log_printf( &logger, " IR data : %d \r\n", ir_data );

    color_value = color8_get_color_value( &color8 );
    log_printf( &logger, " HSL color value : %f \r\n", color_value );

    is_color = color8_get_color( &color8, color_value );
    switch( is_color )
    {
        case 1:
        {
            log_printf( &logger, "--- Color: ORANGE \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, "--- Color: RED \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, "--- Color: PINK \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, "--- Color: PURPLE \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, "--- Color: BLUE \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, "--- Color: CYAN \r\n" );
            break;
        }
        case 7:
        {
            log_printf( &logger, "--- Color: GREEN \r\n" );
            break;
        }
        case 8:
        {
            log_printf( &logger, "--- Color: YELLOW \r\n" );
            break;
        }
        default:
        {
            break;
        }
    }
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color8

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

\mainpage Main Page
 
 

---
# Color 3 click

Color 3 click is a mikroBUS™ add-on board with a TCS3771 color sensor (also known as a light-to-digital converter) and a narrow beam Infrared LED. The circuit can also function as a proximity sensor

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/color-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color3_cfg_setup ( color3_cfg_t *cfg ); 
 
- Initialization function.
> COLOR3_RETVAL color3_init ( color3_t *ctx, color3_cfg_t *cfg );

#### Example key functions :

- Function is used to calculate HSL color.
> float color3_get_color_value ( color3_t *ctx );
 
- Function is used to figure out dominant color.
> uint8_t color3_get_color ( float color_value );

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

> Checks which color is detected by the sensor.
> The detected color name is being logged on the USBUART.

```c

void application_task ( void )
{
    color_value = color3_get_color_value( &color3 );
    is_color = color3_get_color( color_value );

    switch( is_color )
    {
        case COLOR3_ORANGE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: ORANGE\r\n" );
            break;
        }
        case COLOR3_RED_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: RED\r\n" );
            break;
        }
        case COLOR3_PINK_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PINK\r\n" );
            break;
        }
        case COLOR3_PURPLE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PURPLE\r\n" );
            break;
        }
        case COLOR3_BLUE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: BLUE\r\n" );
            break;
        }
        case COLOR3_CYAN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: CYAN\r\n" );
            break;
        }
        case COLOR3_GREEN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: GREEN\r\n" );
            break;
        }
        case COLOR3_YELLOW_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: YELLOW\r\n" );
            break;
        }
        default:
        {
            break;
        }
    }

    Delay_ms( 300 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color3

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

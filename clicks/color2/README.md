\mainpage Main Page
 
---
# Color 2 Click

Color 2 Click carries the ISL29125 RGB color light sensor. It detects red, green and blue in a variety of lighting conditions, outputting 16-bit resolution data in a measuring range from 5.7 m lux to 10,000 lux.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color2 Click driver.

#### Standard key functions :

- `color2_cfg_setup` Config Object Initialization function.
```c
void color2_cfg_setup ( color2_cfg_t *cfg ); 
```

- `color2_init` Initialization function.
```c
err_t color2_init ( color2_t *ctx, color2_cfg_t *cfg );
```

- `color2_default_cfg` Click Default Configuration function.
```c
err_t color2_default_cfg ( color2_t *ctx );
```

#### Example key functions :

- `color2_read_rgb` Function read red, green, and blue data from ISL29125
```c
err_t color2_read_rgb ( color2_t *ctx, color2_rgb_t *rgb );
```

- `color2_rgb_to_hsl` This function converts RGB (red, green, blue) to HSL (hue, saturation, lightness) color value.
```c
void color2_rgb_to_hsl ( color2_t *ctx, color2_rgb_t *rgb, color2_hsl_t *hsl );
```

- `color2_get_color` This function returns the color name flag from the input HSL color.
```c
uint8_t color2_get_color ( color2_hsl_t *hsl );
```

## Examples Description

> This example demonstrates the use of Color 2 Click board by reading data
from RGB channels and converting them to HSL color and displaying those data as 
well as the detected color name on the USB UART.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color2_cfg_t cfg;

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
    color2_cfg_setup( &cfg );
    COLOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color2_init( &color2, &cfg );
    
    if ( COLOR2_ERROR == color2_default_cfg ( &color2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Waits for the data ready interrupt, then reads the values of all channels and converts
them to HSL color and displays those data as well as the detected color name on the USB UART
every 100ms approximately.

```c

void application_task ( void )
{
    // Wait for the data ready interrupt indication
    while ( color2_get_int_pin ( &color2 ) );
    
    uint8_t status = 0;
    color2_rgb_t rgb;
    if ( ( COLOR2_OK == color2_read_status ( &color2, &status ) ) && 
         ( COLOR2_OK == color2_read_rgb ( &color2, &rgb ) ) )
    {
        color2_hsl_t hsl;
        color2_rgb_to_hsl ( &color2, &rgb, &hsl );
        log_printf ( &logger, "\r\n Red: %u\r\n", rgb.red );
        log_printf ( &logger, " Green: %u\r\n", rgb.green );
        log_printf ( &logger, " Blue: %u\r\n", rgb.blue );
        log_printf ( &logger, " Hue: %.1f deg\r\n", hsl.hue );
        log_printf ( &logger, " Saturation: %.1f %%\r\n", hsl.saturation );
        log_printf ( &logger, " Lightness: %.1f %%\r\n", hsl.lightness );
        log_printf ( &logger, " Dominated color: " );
        switch ( color2_get_color ( &hsl ) )
        {
            case COLOR2_RED_COLOR:
            {
                log_printf ( &logger, "RED\r\n" );
                break;
            }
            case COLOR2_YELLOW_COLOR:
            {
                log_printf ( &logger, "YELLOW\r\n" );
                break;
            }
            case COLOR2_GREEN_COLOR:
            {
                log_printf ( &logger, "GREEN\r\n" );
                break;
            }
            case COLOR2_CYAN_COLOR:
            {
                log_printf ( &logger, "CYAN\r\n" );
                break;
            }
            case COLOR2_BLUE_COLOR:
            {
                log_printf ( &logger, "BLUE\r\n" );
                break;
            }
            case COLOR2_MAGENTA_COLOR:
            {
                log_printf ( &logger, "MAGENTA\r\n" );
                break;
            }
            case COLOR2_WHITE_COLOR:
            {
                log_printf ( &logger, "WHITE\r\n" );
                break;
            }
            case COLOR2_BLACK_COLOR:
            {
                log_printf ( &logger, "BLACK\r\n" );
                break;
            }
            default:
            {
                log_printf ( &logger, "UNKNOWN\r\n" );
                break;
            }
        }
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

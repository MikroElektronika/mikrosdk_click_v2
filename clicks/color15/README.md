\mainpage Main Page

---
# Color 15 Click

> Color 15 Click is a compact add-on board representing an accurate color sensing solution. This board features the CLS-16D24-44-DF8/TR8, a low power, high sensitivity, color light sensor from Everlight Electronics. This Click board™, with an I2C configurable color sensor, senses red, green, blue, white (RGBW), and infrared light and converts them to digital values. The RGBW sensor is designed to reject IR in light sources allowing the device to operate in environments from sunlight to dark rooms. The integrating ADC rejects 50Hz and 60Hz flickers caused by artificial light sources.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-15-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Color 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color 15 Click driver.

#### Standard key functions :

- `color15_cfg_setup` Config Object Initialization function.
```c
void color15_cfg_setup ( color15_cfg_t *cfg );
```

- `color15_init` Initialization function.
```c
err_t color15_init ( color15_t *ctx, color15_cfg_t *cfg );
```

- `color15_default_cfg` Click Default Configuration function.
```c
err_t color15_default_cfg ( color15_t *ctx );
```

#### Example key functions :

- `color15_get_data` This function reads data from 5 channels (Red, Green, Blue, White, IR).
```c
err_t color15_get_data ( color15_t *ctx, color15_channels_t *channels );
```

- `color15_rgbw_to_hsl` This function converts RGBW (red, green, blue, white) to HSL (hue, saturation, lightness) color value.
```c
void color15_rgbw_to_hsl ( color15_t *ctx, color15_channels_t *rgbw, color15_hsl_t *hsl );
```

- `color15_get_color` This function returns the color name flag from the input HSL color.
```c
uint8_t color15_get_color ( color15_hsl_t *hsl );
```

## Example Description

> This example demonstrates the use of Color 15 Click board by reading data from 5 channels and converting them to HSL color and displaying those data as
well as the detected color name on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color15_cfg_t color15_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    color15_cfg_setup( &color15_cfg );
    COLOR15_MAP_MIKROBUS( color15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color15_init( &color15, &color15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR15_ERROR == color15_default_cfg ( &color15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the values of all channels and converts them to HSL color and displays those data as well as the detected color name on the USB UART
every 500ms approximately.

```c
void application_task ( void )
{
    // Wait for the data ready interrupt indication
    while ( color15_get_int_pin ( &color15 ) );
    
    color15_channels_t channels;
    if ( ( COLOR15_OK == color15_clear_interrupt ( &color15 ) ) &&
         ( COLOR15_OK == color15_get_data ( &color15, &channels ) ) )
    {
        color15_hsl_t hsl;
        color15_rgbw_to_hsl ( &color15, &channels, &hsl );
        log_printf ( &logger, "\r\n Hue: %.1f deg\r\n", hsl.hue );
        log_printf ( &logger, " Saturation: %.1f %%\r\n", hsl.saturation );
        log_printf ( &logger, " Lightness: %.1f %%\r\n", hsl.lightness );
        switch ( color15_get_color ( &hsl ) )
        {
            case COLOR15_RED_COLOR:
            {
                log_printf( &logger, " Color: RED\r\n" );
                break;
            }
            case COLOR15_YELLOW_COLOR:
            {
                log_printf( &logger, " Color: YELLOW\r\n" );
                break;
            }
            case COLOR15_GREEN_COLOR:
            {
                log_printf( &logger, " Color: GREEN\r\n" );
                break;
            }
            case COLOR15_CYAN_COLOR:
            {
                log_printf( &logger, " Color: CYAN\r\n" );
                break;
            }
            case COLOR15_BLUE_COLOR:
            {
                log_printf( &logger, " Color: BLUE\r\n" );
                break;
            }
            case COLOR15_MAGENTA_COLOR:
            {
                log_printf( &logger, " Color: MAGENTA\r\n" );
                break;
            }
            case COLOR15_WHITE_COLOR:
            {
                log_printf( &logger, " Color: WHITE\r\n" );
                break;
            }
            case COLOR15_BLACK_COLOR:
            {
                log_printf( &logger, " Color: BLACK\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, " Color: UNKNOWN\r\n" );
                break;
            }
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Color15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

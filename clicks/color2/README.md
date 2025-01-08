
---
# Color 2 Click

> [Color 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1988) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1988&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Color 2 Click board by reading data
from RGB channels and converting them to HSL color and displaying those data as 
well as the detected color name on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color2

### Example Key Functions

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---


---
# Color 15 Click

> [Color 15 Click](https://www.mikroe.com/?pid_product=MIKROE-5121) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5121&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Color 15 Click board by reading data from 5 channels and converting them to HSL color and displaying those data as
well as the detected color name on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color15

### Example Key Functions

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

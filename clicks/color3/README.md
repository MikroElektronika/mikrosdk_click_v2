
---
# Color 3 Click

> [Color 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2103) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2103&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Color 3 Click board by reading data
from RGBC channels and converting them to HSL color and displaying those data as 
well as the detected color name on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color3

### Example Key Functions

- `color3_cfg_setup` Config Object Initialization function.
```c
void color3_cfg_setup ( color3_cfg_t *cfg ); 
```

- `color3_init` Initialization function.
```c
err_t color3_init ( color3_t *ctx, color3_cfg_t *cfg );
```

- `color3_get_rgbc_data` This function reads data from 4 channels (Red, Green, Blue, Clear).
```c
err_t color3_get_rgbc_data ( color3_t *ctx, color3_channels_t *channels );
```

- `color3_rgbc_to_hsl` This function converts RGBC (red, green, blue, clear) to HSL (hue, saturation, lightness) color value.
```c
void color3_rgbc_to_hsl ( color3_t *ctx, color3_channels_t *rgbc, color3_hsl_t *hsl );
```

- `color3_get_color` This function returns the color name flag from the input HSL color.
```c
uint8_t color3_get_color ( color3_hsl_t *hsl );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

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
    Delay_ms ( 100 );

    color3_set_default_settings( &color3 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Color 3  Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );
}
```

### Application Task

> Reads the values of all channels and converts them to HSL color and displays those data
as well as the detected color name on the USB UART every 500ms approximately.

```c
void application_task ( void )
{
    color3_channels_t rgbc;
    if ( COLOR3_OK == color3_get_rgbc_data ( &color3, &rgbc ) )
    {
        color3_hsl_t hsl;
        color3_rgbc_to_hsl ( &color3, &rgbc, &hsl );
        log_printf ( &logger, "\r\n Red: %u\r\n", rgbc.red );
        log_printf ( &logger, " Green: %u\r\n", rgbc.green );
        log_printf ( &logger, " Blue: %u\r\n", rgbc.blue );
        log_printf ( &logger, " Clear: %u\r\n", rgbc.clear );
        log_printf ( &logger, " Hue: %.1f deg\r\n", hsl.hue );
        log_printf ( &logger, " Saturation: %.1f %%\r\n", hsl.saturation );
        log_printf ( &logger, " Lightness: %.1f %%\r\n", hsl.lightness );
        log_printf ( &logger, " Dominated color: " );
        switch ( color3_get_color ( &hsl ) )
        {
            case COLOR3_RED_COLOR:
            {
                log_printf ( &logger, "RED\r\n" );
                break;
            }
            case COLOR3_YELLOW_COLOR:
            {
                log_printf ( &logger, "YELLOW\r\n" );
                break;
            }
            case COLOR3_GREEN_COLOR:
            {
                log_printf ( &logger, "GREEN\r\n" );
                break;
            }
            case COLOR3_CYAN_COLOR:
            {
                log_printf ( &logger, "CYAN\r\n" );
                break;
            }
            case COLOR3_BLUE_COLOR:
            {
                log_printf ( &logger, "BLUE\r\n" );
                break;
            }
            case COLOR3_MAGENTA_COLOR:
            {
                log_printf ( &logger, "MAGENTA\r\n" );
                break;
            }
            case COLOR3_WHITE_COLOR:
            {
                log_printf ( &logger, "WHITE\r\n" );
                break;
            }
            case COLOR3_BLACK_COLOR:
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
    Delay_ms ( 500 );
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

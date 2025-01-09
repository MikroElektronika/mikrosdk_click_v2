
---
# Spectrometer 2 Click

> [Spectrometer 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5167) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5167&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Spectrometer 2 Click board by reading data from 6 ALS channels and
converting them to HSL color and displaying those data as well as the detected color name on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectrometer2

### Example Key Functions

- `spectrometer2_cfg_setup` Config Object Initialization function.
```c
void spectrometer2_cfg_setup ( spectrometer2_cfg_t *cfg );
```

- `spectrometer2_init` Initialization function.
```c
err_t spectrometer2_init ( spectrometer2_t *ctx, spectrometer2_cfg_t *cfg );
```

- `spectrometer2_default_cfg` Click Default Configuration function.
```c
err_t spectrometer2_default_cfg ( spectrometer2_t *ctx );
```

- `spectrometer2_get_data` This function reads data from 6 ALS channels (Red, Visible, Blue, Green, IR, Clear).
```c
err_t spectrometer2_get_data ( spectrometer2_t *ctx, spectrometer2_als_channels_t *als_channels );
```

- `spectrometer2_rgbc_to_hsl` This function converts RGBC (red, green, blue, clear) to HSL (hue, saturation, lightness) color value.
```c
void spectrometer2_rgbc_to_hsl ( spectrometer2_als_channels_t *rgbc, spectrometer2_hsl_t *hsl );
```

- `spectrometer2_get_color` This function returns the color name flag from the input HSL color.
```c
uint8_t spectrometer2_get_color ( spectrometer2_hsl_t *hsl );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spectrometer2_cfg_t spectrometer2_cfg;  /**< Click config object. */

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
    spectrometer2_cfg_setup( &spectrometer2_cfg );
    SPECTROMETER2_MAP_MIKROBUS( spectrometer2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == spectrometer2_init( &spectrometer2, &spectrometer2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPECTROMETER2_ERROR == spectrometer2_default_cfg ( &spectrometer2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the values of all ALS channels and converts
them to HSL color and displays those data as well as the detected color name on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    // Wait for the data ready interrupt indication
    while ( !spectrometer2_get_int_pin ( &spectrometer2 ) );
    
    spectrometer2_als_channels_t als_channels;
    if ( ( SPECTROMETER2_OK == spectrometer2_clear_interrupt ( &spectrometer2 ) ) &&
         ( SPECTROMETER2_OK == spectrometer2_get_data ( &spectrometer2, &als_channels ) ) )
    {
        spectrometer2_hsl_t hsl;
        spectrometer2_rgbc_to_hsl( &als_channels, &hsl );
        log_printf ( &logger, "\r\n Hue: %.1f deg\r\n", hsl.hue );
        log_printf ( &logger, " Saturation: %.1f %%\r\n", hsl.saturation );
        log_printf ( &logger, " Lightness: %.1f %%\r\n", hsl.lightness );
        switch ( spectrometer2_get_color ( &hsl ) )
        {
            case SPECTROMETER2_RED_COLOR:
            {
                log_printf( &logger, " Color: RED\r\n" );
                break;
            }
            case SPECTROMETER2_YELLOW_COLOR:
            {
                log_printf( &logger, " Color: YELLOW\r\n" );
                break;
            }
            case SPECTROMETER2_GREEN_COLOR:
            {
                log_printf( &logger, " Color: GREEN\r\n" );
                break;
            }
            case SPECTROMETER2_CYAN_COLOR:
            {
                log_printf( &logger, " Color: CYAN\r\n" );
                break;
            }
            case SPECTROMETER2_BLUE_COLOR:
            {
                log_printf( &logger, " Color: BLUE\r\n" );
                break;
            }
            case SPECTROMETER2_MAGENTA_COLOR:
            {
                log_printf( &logger, " Color: MAGENTA\r\n" );
                break;
            }
            case SPECTROMETER2_WHITE_COLOR:
            {
                log_printf( &logger, " Color: WHITE\r\n" );
                break;
            }
            case SPECTROMETER2_BLACK_COLOR:
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

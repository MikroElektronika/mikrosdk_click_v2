
---
# Spectrometer 2 Click

> Spectrometer 2 Click is a compact add-on board that collects light waves. This board features the VD6283TX, a color sensor with advanced light flicker extraction from STMicroelectronics. The VD6283TX performs fast and accurate light measurements thanks to an individual ADC and a readout for each color channel - red, green, blue, IR, clear, and visible. It uses hybrid color filters with precise responses allowing accurate computation of the correlated color temperature (CCT) and Lux information. Its patented architecture and a high-performance photodiode design can also extract light-flickering frequencies to avoid banding effects or check that they are safe for the human eye.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spectrometer2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/spectrometer-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Spectrometer 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Spectrometer 2 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of Spectrometer 2 Click board by reading data from 6 ALS channels and
converting them to HSL color and displaying those data as well as the detected color name on the USB UART.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectrometer2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

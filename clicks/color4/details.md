
---
# Color 4 Click

> Color 4 Click is a compact add-on board providing an accurate color-sensing solution. 
> This board features the VEML6040, a 16-bit RGBW color sensor offering spectral 
> response through a compatible I2C interface from Vishay Semiconductors. 
> The VEML6040 is based on the Filtron™ technology achieving the closest 
> ambient light spectral sensitivity to real-human eye responses. 
> Alongside the color sensor, this IC also incorporates a signal conditioning circuit consisting of photodiodes, 
> amplifiers, and A/D circuits placed into a single chip using the CMOS process. 
> It provides a selectable measurement range up to 16.496lx with the highest sensitivity of 0.007865lx/step.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Color 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color 4 Click driver.

#### Standard key functions :

- `color4_cfg_setup` Config Object Initialization function.
```c
void color4_cfg_setup ( color4_cfg_t *cfg );
```

- `color4_init` Initialization function.
```c
err_t color4_init ( color4_t *ctx, color4_cfg_t *cfg );
```

- `color4_default_cfg` Click Default Configuration function.
```c
err_t color4_default_cfg ( color4_t *ctx );
```

#### Example key functions :

- `color4_set_config` Color 4 set configuration function.
```c
err_t color4_set_config ( color4_t *ctx, color4_config_t config ) 
```

- `color4_get_color_data` Color 4 get color data function.
```c
err_t color4_get_color_data ( color4_t *ctx, color4_ch_color_t ch_color, uint16_t *color_data );
```

- `color4_get_ambient_light` Color 4 get ambient light level function.
```c
err_t color4_get_ambient_light ( color4_t *ctx, float *ambient_light );
```

## Example Description

> This library contains API for the Color 4 Click driver.
> This driver provides the functions for the sensor configuration
> and for reading RGBW and ambient light data from the device.
> This example displays RGBW data, Ambient light level, CCT data 
> and the light color names.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color4_cfg_t color4_cfg;  /**< Click config object. */

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
    color4_cfg_setup( &color4_cfg );
    COLOR4_MAP_MIKROBUS( color4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color4_init( &color4, &color4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR4_ERROR == color4_default_cfg ( &color4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This example demonstrates the use of the Color 4 Click board™.
> Reads and displays the results of the RGBW, Ambient light level, 
> calculate the correlated color temperature. 
> This example also detects and displays the light color names.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_RED, &red_data ) )
    {
        log_printf( &logger, " Red: %u\r\n", red_data );    
    }
    
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_GREEN, &green_data ) )
    {
        log_printf( &logger, " Green: %u\r\n", green_data );   
    }
    
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_BLUE, &blue_data ) )
    {
        log_printf( &logger, " Blue: %u\r\n", blue_data );
    }
    
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_WHITE, &white_data ) )
    {
        log_printf( &logger, " White: %u\r\n", white_data );    
    }
    log_printf( &logger, " - - - - - - -  - - - - \r\n" );
    
    if ( COLOR4_OK == color4_get_ambient_light( &color4, &ambient_light ) )
    {
        log_printf( &logger, " ALS lux level: %.2f\r\n", ambient_light );    
    }
    
    if ( COLOR4_OK == color4_get_cct( &color4, &cct ) )
    {
        log_printf( &logger, " CCT: %.2f\r\n", cct );   
    }
    log_printf( &logger, " - - - - - - -  - - - - \r\n" );

    display_color( );
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

## Note

> Color detection is obtained based on the analysis 
> of calculate the correlated color temperature (CCT) data 
> and the CIE 1931 chromaticity diagram.
> For more details please refer to the “Designing the VEML6040 into an Application” 
> application note (https://www.vishay.com/docs/84331/designingveml6040.pdf).

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Color4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

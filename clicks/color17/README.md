\mainpage Main Page

---
# Color 17 Click

> Color 17 Click is a compact add-on board representing an accurate color-sensing solution. 
> This board features the OPT4048, a high-speed precision tristimulus XYZ color sensor from Texas Instruments. 
> The sensor has four sensing channels and uses precision optical filters to mimic the normal vision of the human eye. 
> The OPT4048 also has 12 configurable conversion times that range from 600μs up to 800ms, 
> with measurements that can be read synchronously or asynchronously. 
> It is not excessively sensitive to micro-shadows and the small particles on the optical surface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-17-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Color 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color 17 Click driver.

#### Standard key functions :

- `color17_cfg_setup` Config Object Initialization function.
```c
void color17_cfg_setup ( color17_cfg_t *cfg );
```

- `color17_init` Initialization function.
```c
err_t color17_init ( color17_t *ctx, color17_cfg_t *cfg );
```

- `color17_default_cfg` Click Default Configuration function.
```c
err_t color17_default_cfg ( color17_t *ctx );
```

#### Example key functions :

- `color17_get_cct` Color 17 gets correlated color temperature data function.
```c
err_t color17_get_cct ( color17_t *ctx, float *cct, float *light_intensity );
```

- `color17_get_measurement` Color 17 gets light and color measurement data function.
```c
err_t color17_get_measurement ( color17_t *ctx, uint32_t *adc_codes );
```

- `color17_set_config` Color 17 set the configuration function.
```c
err_t color17_set_config ( color17_t *ctx, color17_config_t config );
```

## Example Description

> This library contains API for the Color 17 Click driver.
> This example displays CCT data, Light intensity level
> and the light color names.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color17_cfg_t color17_cfg;  /**< Click config object. */

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
    color17_cfg_setup( &color17_cfg );
    COLOR17_MAP_MIKROBUS( color17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color17_init( &color17, &color17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR17_ERROR == color17_default_cfg ( &color17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Color 17 Click board™.
> Reads and displays the correlated color temperature 
> and Light intensity level.
> This example also detects and displays the light color names.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( COLOR17_OK == color17_get_cct( &color17, &cct, &light_intensity ) )
    {
        log_printf( &logger, " CCT: %.2f\r\n", cct );
        log_printf( &logger, " LIL: %.2f\r\n", light_intensity );
        log_printf( &logger, " - - - - - - -  - - - - \r\n" );
        color17_display_color( );
    }
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

## Note

> Color detection is obtained based on the analysis 
> of calculate the correlated color temperature (CCT) data
> and the CIE 1931 chromaticity diagram. For more details please refer to the 
> “OPT4048 High Speed High Precision Tristimulus XYZ Color Sensor datasheet” 
> [OPT4048 datasheet](https://www.ti.com/lit/gpn/OPT4048).

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Color17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

\mainpage Main Page

---
# Color 12 Click

> Color 12 Click is a compact add-on board providing an accurate color-sensing solution. 
> This board features the BU27006MUC-Z, a digital color sensor from Rohm Semiconductor 
> with an integrated flicker sensing function. The BU27006MUC-Z can sense Red, Green, Blue (RGB), 
> and Infrared light and efficiently convert them into digital values via the I2C interface. 
> Its remarkable high sensitivity, wide dynamic range, and exceptional IR-cut characteristics 
> enable precise illuminance measurement, typically up to 50klx, 
> and accurate ambient light color temperature determination. 
> Moreover, this sensor can effectively detect flicker noise originating from displays and room lighting, 
> with a typical sensitivity of 10klx.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Color 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color 12 Click driver.

#### Standard key functions :

- `color12_cfg_setup` Config Object Initialization function.
```c
void color12_cfg_setup ( color12_cfg_t *cfg );
```

- `color12_init` Initialization function.
```c
err_t color12_init ( color12_t *ctx, color12_cfg_t *cfg );
```

- `color12_default_cfg` Click Default Configuration function.
```c
err_t color12_default_cfg ( color12_t *ctx );
```

#### Example key functions :

- `color12_get_color_data` Color 12 gets the color measurement result function.
```c
err_t color12_get_color_data ( color12_t *ctx, color12_color_sel_t color_sel, uint16_t *color_data );
```

- `color12_set_config` Color 12 sets the configuration function.
```c
err_t color12_set_config ( color12_t *ctx, color12_config_t config );
```

- `color12_get_config` Color 12 gets the configuration function.
```c
err_t color12_get_config ( color12_t *ctx, color12_config_t *config );
```

## Example Description

> This library contains API for the Color 12 Click driver.
> The demo application sets sensor configuration 
> and reads and displays RGB/IR measurement results.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color12_cfg_t color12_cfg;  /**< Click config object. */

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
    color12_cfg_setup( &color12_cfg );
    COLOR12_MAP_MIKROBUS( color12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color12_init( &color12, &color12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR12_ERROR == color12_default_cfg ( &color12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Color 12 Click board™.
> Reads and displays the results of the RGB/IR measurements.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_RED, &color_data ) )
    {
        log_printf( &logger, " Red : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_GREEN, &color_data ) )
    {
        log_printf( &logger, " Green : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_BLUE, &color_data ) )
    {
        log_printf( &logger, " Blue : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_IR, &color_data ) )
    {
        log_printf( &logger, " IR : %u\r\n", color_data );
    }
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Color12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

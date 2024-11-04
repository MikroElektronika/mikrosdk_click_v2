\mainpage Main Page

---
# Barometer 10 Click

> Barometer 10 Click is a compact add-on board that measures air pressure in a specific environment. 
> This board features the LPS28DFW, an ultra-compact piezoresistive absolute pressure sensor 
> that functions as a digital output barometer from STMicroelectronics. 
> The LPS28DFW comprises a sensing element and an IC chip for signal processing in one package, 
> converts pressure into a 24-bit digital value, and sends the information via I2C serial interface. 
> It has a selectable dual full-scale absolute pressure range of up to 1260hPa and 4060hPa, 
> with an absolute pressure accuracy of 0.5hPa over a wide operating temperature range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer10_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/barometer-10-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Barometer 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 10 Click driver.

#### Standard key functions :

- `barometer10_cfg_setup` Config Object Initialization function.
```c
void barometer10_cfg_setup ( barometer10_cfg_t *cfg );
```

- `barometer10_init` Initialization function.
```c
err_t barometer10_init ( barometer10_t *ctx, barometer10_cfg_t *cfg );
```

- `barometer10_default_cfg` Click Default Configuration function.
```c
err_t barometer10_default_cfg ( barometer10_t *ctx );
```

#### Example key functions :

- `barometer10_get_pressure` Barometer 10 gets pressure function.
```c
err_t barometer10_get_pressure ( barometer10_t *ctx, float *pressure )
```

- `barometer10_get_temperature` Barometer 10 gets temperature function.
```c
err_t barometer10_get_temperature ( barometer10_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of the Barometer 10 Click board™.
> The demo application reads and calculates pressure and temperature data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer10_cfg_t barometer10_cfg;  /**< Click config object. */

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
    barometer10_cfg_setup( &barometer10_cfg );
    BAROMETER10_MAP_MIKROBUS( barometer10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer10_init( &barometer10, &barometer10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER10_ERROR == barometer10_default_cfg ( &barometer10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
}
```

### Application Task

> This example displays the Pressure [mBar] and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float pressure, temperature;
    if ( BAROMETER10_OK == barometer10_get_pressure( &barometer10, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.2f [mbar] \r\n", pressure );
    }
    
    if ( BAROMETER10_OK == barometer10_get_temperature( &barometer10, &temperature ) )
    {
        log_printf( &logger, " Temperature : %.2f [deg c] \r\n", temperature );
    }
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

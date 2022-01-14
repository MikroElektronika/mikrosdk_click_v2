
---
# Barometer 5 click

> Barometer 5 Click is a compact add-on board used to measure air pressure in a specific environment. This board features the MS5637-02BA03, a high accuracy low voltage barometric and temperature sensor from TE Connectivity Measurement Specialties. The MS5637-02BA03 includes a high-linearity pressure sensor and an ultra-low-power 24-bit ΔΣ ADC with internal factory-calibrated coefficients, providing a precise digital 24-bit pressure and temperature value, and different operation modes allowing the user to optimize for conversion speed and current consumption. It comes with a configurable host interface that supports I2C serial communication and measures pressure in a range from 300mbar up to 1.2bar with an accuracy of ±2mbar over a wide operating temperature range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barometer-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Barometer5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 5 Click driver.

#### Standard key functions :

- `barometer5_cfg_setup` Config Object Initialization function.
```c
void barometer5_cfg_setup ( barometer5_cfg_t *cfg );
```

- `barometer5_init` Initialization function.
```c
err_t barometer5_init ( barometer5_t *ctx, barometer5_cfg_t *cfg );
```

- `barometer5_default_cfg` Click Default Configuration function.
```c
err_t barometer5_default_cfg ( barometer5_t *ctx );
```

#### Example key functions :

- `barometer5_get_data` Barometer 5 get data function.
```c
err_t barometer5_get_data ( barometer5_t *ctx, float *temperature, float *pressure );
```

- `barometer5_get_pressure` Barometer 5 get pressure data function.
```c
err_t barometer5_get_pressure ( barometer5_t *ctx, float *pressure );
```

- `barometer5_get_temperature` Barometer 5 get temperature data function.
```c
err_t barometer5_get_temperature ( barometer5_t *ctx, float *temperature );
```

## Example Description

> This library contains API for Barometer 5 Click driver.
> The demo application reads and calculate temperature and pressure data.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer5_cfg_t barometer5_cfg;  /**< Click config object. */

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
    barometer5_cfg_setup( &barometer5_cfg );
    BAROMETER5_MAP_MIKROBUS( barometer5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer5_init( &barometer5, &barometer5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER5_ERROR == barometer5_default_cfg ( &barometer5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Barometer 5 Click board™.
> In this example, display the Pressure ( mBar ) and Temperature ( degree Celsius ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static float temperature;
    static float pressure;
    
    if ( barometer5_get_data( &barometer5, &temperature, &pressure ) == BAROMETER5_OK )
    {
        log_printf( &logger, " Pressure    : %.2f mbar   \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C      \r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );
    }
    
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

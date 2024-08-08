
---
# Pressure 23 07BA click

> Pressure 23 Click - 07BA is a compact add-on board for accurate and reliable absolute pressure and temperature measurements in harsh environments. This board features the MS5849-07BA, an ultra-compact, chlorine-resistant sensor from TE Connectivity that delivers 24-bit resolution data via I2C or SPI interfaces. It operates within pressure ranges of 0.4 to 7 bar, features a chlorine-resistant gel coating, and measures temperatures from -20 to +85°C. The sensor's grounded metal ring provides robust protection and secure O-ring mounting, while the flexible communication options allow for optimized performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure2307ba_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-23-click-07ba)

---


#### Click library

- **Author**        : MikroE Team
- **Date**          : May 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure 23 07BA Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 23 07BA Click driver.

#### Standard key functions :

- `pressure2307ba_cfg_setup` Config Object Initialization function.
```c
void pressure2307ba_cfg_setup ( pressure2307ba_cfg_t *cfg );
```

- `pressure2307ba_init` Initialization function.
```c
err_t pressure2307ba_init ( pressure2307ba_t *ctx, pressure2307ba_cfg_t *cfg );
```

- `pressure2307ba_default_cfg` Click Default Configuration function.
```c
err_t pressure2307ba_default_cfg ( pressure2307ba_t *ctx );
```

#### Example key functions :

- `pressure2307ba_get_measurement_data` Pressure 23 07BA gets the measurement data function.
```c
err_t pressure2307ba_get_measurement_data ( pressure2307ba_t *ctx, float *pressure, float *temperature );
```

- `pressure2307ba_get_calibration_data` Pressure 23 07BA gets the calibration data function.
```c
err_t pressure2307ba_get_calibration_data ( pressure2307ba_t *ctx );
```

- `pressure2307ba_read_adc` Pressure 23 07BA ADC data reading function.
```c
err_t pressure2307ba_read_adc ( pressure2307ba_t *ctx, uint8_t sel_data, uint32_t *adc_data );
```

## Example Description

> This example demonstrates the use of Pressure 23 07BA Click board™ by reading and displaying
> the pressure and temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure2307ba_cfg_t pressure2307ba_cfg;  /**< Click config object. */

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
    pressure2307ba_cfg_setup( &pressure2307ba_cfg );
    PRESSURE2307BA_MAP_MIKROBUS( pressure2307ba_cfg, MIKROBUS_1 );
    err_t init_flag = pressure2307ba_init( &pressure2307ba, &pressure2307ba_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE2307BA_ERROR == pressure2307ba_default_cfg ( &pressure2307ba ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " _______________________ \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the Pressure [mBar] 
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static float temperature, pressure;
    if ( PRESSURE2307BA_OK == pressure2307ba_get_measurement_data( &pressure2307ba, &pressure, &temperature ) )
    {
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " _______________________ \r\n" );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure2307BA

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

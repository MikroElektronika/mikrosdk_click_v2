\mainpage Main Page

---
# Pressure 23 click

> Pressure 23 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the MS5849-30BA, an ultra-compact chlorine-resistant absolute pressure sensor from TE Connectivity. The sensor is a small digital altimeter operating from 300 up to 30000mbar, optimized for applications where chlorine is present. The sensor’s stainless-steel housing is filled with gel, which makes it robust and enables it to work in harsh environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure23_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-23-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 23 Click driver.

#### Standard key functions :

- `pressure23_cfg_setup` Config Object Initialization function.
```c
void pressure23_cfg_setup ( pressure23_cfg_t *cfg );
```

- `pressure23_init` Initialization function.
```c
err_t pressure23_init ( pressure23_t *ctx, pressure23_cfg_t *cfg );
```

- `pressure23_default_cfg` Click Default Configuration function.
```c
err_t pressure23_default_cfg ( pressure23_t *ctx );
```

#### Example key functions :

- `pressure23_get_measurement_data` Pressure 23 gets the measurement data function.
```c
err_t pressure23_get_measurement_data ( pressure23_t *ctx, float *pressure, float *temperature );
```

- `pressure23_get_calibration_data` Pressure 23 gets the calibration data function.
```c
err_t pressure23_get_calibration_data ( pressure23_t *ctx );
```

- `pressure23_read_adc` Pressure 23 ADC data reading function.
```c
err_t pressure23_read_adc ( pressure23_t *ctx, uint8_t sel_data, uint32_t *adc_data );
```

## Example Description

> This example demonstrates the use of Pressure 23 Click board™ by reading and displaying
> the pressure and temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure23_cfg_t pressure23_cfg;  /**< Click config object. */

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
    pressure23_cfg_setup( &pressure23_cfg );
    PRESSURE23_MAP_MIKROBUS( pressure23_cfg, MIKROBUS_1 );
    err_t init_flag = pressure23_init( &pressure23, &pressure23_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE23_ERROR == pressure23_default_cfg ( &pressure23 ) )
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
    if ( PRESSURE23_OK == pressure23_get_measurement_data( &pressure23, &pressure, &temperature ) )
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
- Click.Pressure23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

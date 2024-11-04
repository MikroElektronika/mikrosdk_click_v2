
---
# Thermo 22 Click

> Thermo 22 Click is a compact add-on board that provides an accurate temperature measurement. This board features the TMP75C, a high-precision digital temperature sensor from Texas Instruments. The TMP75C houses an integrated digital temperature sensor with a 12-bit analog-to-digital converter (ADC), a reference circuit, and serial interface logic functions in one package. Characterized by its high accuracy (up to ±0.25°C typical) and high resolution of 0.0625°C, this temperature sensor provides temperature data to the host controller with a configurable I2C interface. This Click board™ is appropriate for thermal management and protection of various consumer, industrial, and environmental applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo22_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 22 Click driver.

#### Standard key functions :

- `thermo22_cfg_setup` Config Object Initialization function.
```c
void thermo22_cfg_setup ( thermo22_cfg_t *cfg );
```

- `thermo22_init` Initialization function.
```c
err_t thermo22_init ( thermo22_t *ctx, thermo22_cfg_t *cfg );
```

- `thermo22_default_cfg` Click Default Configuration function.
```c
err_t thermo22_default_cfg ( thermo22_t *ctx );
```

#### Example key functions :

- `thermo22_read_temperature` This function reads the temperature data in Celsius.
```c
err_t thermo22_read_temperature ( thermo22_t *ctx, float *temperature );
```

- `thermo22_set_temperature_high_limit` This function sets the temperature high limit at which the overtemperature alert flag is being set.
```c
err_t thermo22_set_temperature_high_limit ( thermo22_t *ctx, float high_limit );
```

- `thermo22_get_int_pin` This function returns the INT pin logic state which indicates the overtemperature alert.
```c
uint8_t thermo22_get_int_pin ( thermo22_t *ctx );
```

## Example Description

> This example demonstrates the use of Thermo 22 Click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which enables continuous conversation and sets the overtemperature limits to 35.0 Celsius.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo22_cfg_t thermo22_cfg;  /**< Click config object. */

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
    thermo22_cfg_setup( &thermo22_cfg );
    THERMO22_MAP_MIKROBUS( thermo22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo22_init( &thermo22, &thermo22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO22_ERROR == thermo22_default_cfg ( &thermo22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART
every 200ms approximately. It also checks the overtemperature alert indicator and displays
an appropriate message if the indicator is active.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO22_OK == thermo22_read_temperature ( &thermo22, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f C \r\n\n", temperature );
        if ( !thermo22_get_int_pin ( &thermo22 ) )
        {
            log_printf ( &logger, " Over temperature alert! \r\n\n" );
        }
        Delay_ms ( 200 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

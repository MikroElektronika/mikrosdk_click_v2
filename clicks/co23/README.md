\mainpage Main Page

---
# CO2 3 Click

> CO2 3 Click is a compact add-on board that allows for precise and reliable indoor air quality measurements. 
> This board features XENSIV™ PASCO2V01BUMA1, a highly accurate CO2 sensor module 
> from Infineon Technologies that uses photoacoustic spectroscopy technology to measure indoor air quality. 
> The module comprises a gas measuring cell, an IR emitter, a microphone, and a microcontroller for data processing. 
> Its key components are developed in-house, ensuring the highest quality and performance. 
> Other major characteristics include high accuracy, low power consumption, and versatile configuration options.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/co23_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/co2-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the CO2 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CO2 3 Click driver.

#### Standard key functions :

- `co23_cfg_setup` Config Object Initialization function.
```c
void co23_cfg_setup ( co23_cfg_t *cfg );
```

- `co23_init` Initialization function.
```c
err_t co23_init ( co23_t *ctx, co23_cfg_t *cfg );
```

- `co23_default_cfg` Click Default Configuration function.
```c
err_t co23_default_cfg ( co23_t *ctx );
```

#### Example key functions :

- `co23_get_co2_ppm` CO2 3 get CO2 concentration function.
```c
err_t co23_get_co2_ppm ( co23_t *ctx, uint16_t *co2_ppm );
```

- `co23_set_meas_cfg` CO2 3 set measurement configuration function.
```c
err_t co23_set_meas_cfg ( co23_t *ctx, co23_meas_cfg_t meas_cfg );
```

- `co23_set_pressure_ref`  CO2 3 set reference pressure function.
```c
err_t co23_set_pressure_ref ( co23_t *ctx, uint16_t pressure_mbar );
```

## Example Description

> This library contains API for CO2 3 Click driver.
> This driver provides the functions for sensor configuration 
> and reading the CO2 gas concentration in the air.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or UART module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    co23_cfg_t co23_cfg;  /**< Click config object. */

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
    co23_cfg_setup( &co23_cfg );
    CO23_MAP_MIKROBUS( co23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == co23_init( &co23, &co23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( CO23_ERROR == co23_default_cfg ( &co23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the CO2 3 Click board™.
> The device starts a single measurement sequence,
> measures and display air CO2 gas concentration (ppm).
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{     
    co23_meas_cfg_t meas_cfg;
    meas_cfg.op_mode = CO23_OP_MODE_SINGLE;
    co23_set_meas_cfg( &co23, meas_cfg );
    Delay_ms ( 1000 );
    
    uint16_t co2_ppm = 0;
    co23_get_co2_ppm( &co23, &co2_ppm );
    log_printf( &logger, " CO2: %d ppm\r\n", co2_ppm );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CO23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

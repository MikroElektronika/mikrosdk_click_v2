
---
# VCP Monitor 5 Click

> VCP Monitor 5 Click is a compact add-on board designed for various applications' precise current, voltage, and temperature measurements. This board features the INA700A, a 16-bit digital power monitor from Texas Instruments based on an advanced EZShunt™ technology for high-accuracy sensing. This board handles full-scale current measurements up to ±15.728A, operates within a wide common-mode voltage range of -0.3V to +40V, and offers real-time power, energy, and charge monitoring with ±0.5% accuracy. The onboard temperature sensor is accurate to ±3°C, and adjustable ADC conversion times and sample averaging provide noise reduction and optimized overcurrent detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vcpmonitor5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/vcp-monitor-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the VCP Monitor 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VCP Monitor 5 Click driver.

#### Standard key functions :

- `vcpmonitor5_cfg_setup` Config Object Initialization function.
```c
void vcpmonitor5_cfg_setup ( vcpmonitor5_cfg_t *cfg );
```

- `vcpmonitor5_init` Initialization function.
```c
err_t vcpmonitor5_init ( vcpmonitor5_t *ctx, vcpmonitor5_cfg_t *cfg );
```

- `vcpmonitor5_default_cfg` Click Default Configuration function.
```c
err_t vcpmonitor5_default_cfg ( vcpmonitor5_t *ctx );
```

#### Example key functions :

- `vcpmonitor5_get_bus_voltage` This function reads the BUS voltage output measurement in volts [V] by using I2C serial interface.
```c
err_t vcpmonitor5_get_bus_voltage ( vcpmonitor5_t *ctx, float *voltage );
```

- `vcpmonitor5_get_current` This function reads the current measurement result in milliamperes [mA] by using the I2C serial interface.
```c
err_t vcpmonitor5_get_current ( vcpmonitor5_t *ctx, float *current );
```

- `vcpmonitor5_get_power` This function reads the power measurement result in Watts [W] by using the I2C serial interface.
```c
err_t vcpmonitor5_get_power ( vcpmonitor5_t *ctx, float *power );
```

## Example Description

> This library contains API for the VCP Monitor 5 Click driver 
> for measurements of the voltage, current, power, energy, charge, and die temperature.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor5_cfg_t vcpmonitor5_cfg;  /**< Click config object. */

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
    vcpmonitor5_cfg_setup( &vcpmonitor5_cfg );
    VCPMONITOR5_MAP_MIKROBUS( vcpmonitor5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == vcpmonitor5_init( &vcpmonitor5, &vcpmonitor5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VCPMONITOR5_ERROR == vcpmonitor5_default_cfg ( &vcpmonitor5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads and displays the results of the input bus voltage, 
> current, power, energy, charge accumulation measurements, and die temperature.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float app_buf = 0;
    if ( VCPMONITOR5_OK == vcpmonitor5_get_bus_voltage( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Voltage: %.2f [V]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_current( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Current: %.2f [mA]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_power( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Power: %.2f [W]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_energy( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Energy: %.2f [kJ]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_charge( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Charge: %.2f [C]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_temperature( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Temperature: %.2f [degC]\r\n", app_buf );
        Delay_ms ( 50 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

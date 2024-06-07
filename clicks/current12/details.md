
---
# Current 12 click

> Current 12 Click is a compact add-on board designed for high-precision monitoring of current, voltage, power, and temperature in various applications. This board features the TSC1641, a 60V 16-bit power monitor with an I2C interface from STMicroelectronics. The TSC1641 consist of a high-precision 16-bit dual-channel sigma-delta ADC, capable of measuring high-side, low-side, and bidirectional currents with a programmable conversion time ranging from 128µs to 32.7ms. It supports 2-wire I2C communication with clock frequencies up to 1MHz, and includes an alert interrupt pin for setting thresholds on voltage, current, power, and temperature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Current 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current 12 Click driver.

#### Standard key functions :

- `current12_cfg_setup` Config Object Initialization function.
```c
void current12_cfg_setup ( current12_cfg_t *cfg );
```

- `current12_init` Initialization function.
```c
err_t current12_init ( current12_t *ctx, current12_cfg_t *cfg );
```

- `current12_default_cfg` Click Default Configuration function.
```c
err_t current12_default_cfg ( current12_t *ctx );
```

#### Example key functions :

- `current12_get_load_voltage` This function reads the load voltage measurement values [V].
```c
err_t current12_get_load_voltage ( current12_t *ctx, float *load_voltage );
```

- `current12_get_dc_power` This function reads the DC power measurement values [W].
```c
err_t current12_get_dc_power ( current12_t *ctx, float *dc_power );
```

- `current12_get_current` This function reads the current measurement values [mA].
```c
err_t current12_get_current ( current12_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of the Current 12 click board 
> by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current12_cfg_t current12_cfg;  /**< Click config object. */

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
    current12_cfg_setup( &current12_cfg );
    CURRENT12_MAP_MIKROBUS( current12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current12_init( &current12, &current12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT12_ERROR == current12_default_cfg ( &current12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_____________________\r\n " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the results 
> of the input current, voltage, and power measurements.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float meas_data = 0;
    if ( CURRENT12_OK == current12_get_shunt_voltage( &current12, &meas_data ) )
    {
        log_printf( &logger, " Shunt Voltage: %.2f [mV]\r\n ", meas_data );
        Delay_ms ( 100 );
    }

    if ( CURRENT12_OK == current12_get_load_voltage( &current12, &meas_data ) )
    {
        log_printf( &logger, " Load Voltage: %.2f [V]\r\n ", meas_data );
        Delay_ms ( 100 );
    }

    if ( CURRENT12_OK == current12_get_dc_power( &current12, &meas_data ) )
    {
        log_printf( &logger, " DC Power: %.2f [W]\r\n ", meas_data );
        Delay_ms ( 100 );
    }

    if ( CURRENT12_OK == current12_get_current( &current12, &meas_data ) )
    {
        log_printf( &logger, " Current: %.2f [mA]\r\n", meas_data );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "_____________________\r\n " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

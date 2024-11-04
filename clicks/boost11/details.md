
---
# Boost 11 Click

> Boost 11 Click is a compact add-on board that boosts low input voltages to a stable output. This board features the XCL105B331H2-G, a synchronous step-up DC/DC converter from TOREX Semi. It operates from an input voltage as low as 0.9V, ideal for devices using single Alkaline or Nickel-metal hydride batteries, with an output fixed at 3.3V. It features an EN pin for easy start-up and standby mode and supports both 3.3V and 5V logic levels. This versatility makes Boost 11 Click suitable for industrial equipment, IoT devices, wearables, and applications prioritizing battery life.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boost11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/boost-11-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : ADC type


# Software Support

We provide a library for the Boost 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Boost 11 Click driver.

#### Standard key functions :

- `boost11_cfg_setup` Config Object Initialization function.
```c
void boost11_cfg_setup ( boost11_cfg_t *cfg );
```

- `boost11_init` Initialization function.
```c
err_t boost11_init ( boost11_t *ctx, boost11_cfg_t *cfg );
```

#### Example key functions :

- `boost11_active_mode` This function activates the boost operating mode.
```c
void boost11_active_mode ( boost11_t *ctx );
```

- `boost11_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t boost11_read_an_pin_voltage ( boost11_t *ctx, float *data_out );
```

## Example Description

> This example demonstrates the use of Boost 11 Click board 
> by controlling the output state.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module, log UART, and activate the boost operating mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    boost11_cfg_t boost11_cfg;  /**< Click config object. */

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
    boost11_cfg_setup( &boost11_cfg );
    BOOST11_MAP_MIKROBUS( boost11_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == boost11_init( &boost11, &boost11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    boost11_active_mode( &boost11 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads measurements of the output voltage level [V].
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float voltage = 0;
    if ( BOOST11_OK == boost11_read_an_pin_voltage ( &boost11, &voltage ) ) 
    {
        log_printf( &logger, " Output Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms ( 1000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

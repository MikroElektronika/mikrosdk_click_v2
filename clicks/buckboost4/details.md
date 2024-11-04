
---
# Buck-Boost 4 Click

> Buck-Boost 4 Click is a compact add-on board that contains a buck-boost DC/DC converter with four integrated MOSFETs. This board features the TPS55289, a buck-boost converter from Texas Instruments. It can deliver on its output voltages from 0.8 up to 22V, from the input voltage in a range of 3 up to 30V. The output voltage can be programmed in 10mV steps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buckboost4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/buck-boost-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Buck-Boost 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck-Boost 4 Click driver.

#### Standard key functions :

- `buckboost4_cfg_setup` Config Object Initialization function.
```c
void buckboost4_cfg_setup ( buckboost4_cfg_t *cfg );
```

- `buckboost4_init` Initialization function.
```c
err_t buckboost4_init ( buckboost4_t *ctx, buckboost4_cfg_t *cfg );
```

- `buckboost4_default_cfg` Click Default Configuration function.
```c
err_t buckboost4_default_cfg ( buckboost4_t *ctx );
```

#### Example key functions :

- `buckboost4_set_vout` Buck-Boost 4 set the output voltage function.
```c
err_t buckboost4_set_vout ( buckboost4_t *ctx, float vout_v );
```

- `buckboost4_set_vref` Buck-Boost 4 set internal reference voltage function.
```c
err_t buckboost4_set_vref ( buckboost4_t *ctx, float vref_mv );
```

- `buckboost4_fault_indicator` Buck-Boost 4 check fault indicator function.
```c
uint8_t buckboost4_fault_indicator ( buckboost4_t *ctx );
```

## Example Description

> This example demonstrates the use of the Buck-Boost 4 Click board™.
> This driver provides functions for device configurations and for the output voltage setting.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buckboost4_cfg_t buckboost4_cfg;  /**< Click config object. */

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
    buckboost4_cfg_setup( &buckboost4_cfg );
    BUCKBOOST4_MAP_MIKROBUS( buckboost4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buckboost4_init( &buckboost4, &buckboost4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCKBOOST4_ERROR == buckboost4_default_cfg ( &buckboost4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "____________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application sets the desired output voltage 
> by cycling through a couple of voltage values.
> Results are sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t vout = 1; vout < 21; vout++ )
    {
        if ( BUCKBOOST4_OK == buckboost4_set_vout( &buckboost4, ( float ) vout ) )
        {
            log_printf( &logger, " Vout: %dV\r\n", ( uint16_t ) vout );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
    log_printf( &logger, "____________\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

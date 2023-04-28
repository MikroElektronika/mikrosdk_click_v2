\mainpage Main Page

---
# HW Monitor click

> HW Monitor Click is a compact add-on board used to monitor 
> and regulate the performance of various hardware components within an embedded system. 
> This board features the LM96080, an I2C-configurable system hardware monitor 
> from Texas Instruments that contains a 10-bit delta-sigma ADC capable 
> of measuring seven positive voltages and local temperature. 
> The LM96080 also has two programmable fan speed monitoring inputs besides 
> other hardware monitoring functions like chassis intrusion detection, 
> additional external interrupt input, master reset for external purposes, 
> as well as a sequencer that performs watchdog window comparisons of all measured values.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hwmonitor_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hw-monitor-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the HW Monitor Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HW Monitor Click driver.

#### Standard key functions :

- `hwmonitor_cfg_setup` Config Object Initialization function.
```c
void hwmonitor_cfg_setup ( hwmonitor_cfg_t *cfg );
```

- `hwmonitor_init` Initialization function.
```c
err_t hwmonitor_init ( hwmonitor_t *ctx, hwmonitor_cfg_t *cfg );
```

- `hwmonitor_default_cfg` Click Default Configuration function.
```c
err_t hwmonitor_default_cfg ( hwmonitor_t *ctx );
```

#### Example key functions :

- `hwmonitor_get_analog_inputs` HW Monitor gets analog inputs voltage function.
```c
err_t hwmonitor_get_analog_inputs ( hwmonitor_t *ctx, uint8_t in_pos, float *voltage );
```

- `hwmonitor_get_temperature` HW Monitor gets temperature function.
```c
err_t hwmonitor_get_temperature ( hwmonitor_t *ctx, float *temperature );
```

- `hwmonitor_set_config` HW Monitor set the configuration function.
```c
err_t hwmonitor_set_config ( hwmonitor_t *ctx, hwmonitor_config_t config );
```

## Example Description

> This example demonstrates the use of the HW Monitor Click board™.
> The demo application monitors analog voltage inputs and local temperature data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor_cfg_t hwmonitor_cfg;  /**< Click config object. */

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
    hwmonitor_cfg_setup( &hwmonitor_cfg );
    HWMONITOR_MAP_MIKROBUS( hwmonitor_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor_init( &hwmonitor, &hwmonitor_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR_ERROR == hwmonitor_default_cfg ( &hwmonitor ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}
```

### Application Task

> This example displays the Analog Voltage Inputs (IN0-IN6) [mV] 
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float temperature, voltage;
    for ( uint8_t in_pos = 0; in_pos < 7; in_pos++ )
    {
        if ( HWMONITOR_OK == hwmonitor_get_analog_inputs( &hwmonitor, in_pos, &voltage ) )
        {
            log_printf( &logger, "IN %d: %.1f mV\r\n", ( uint16_t ) in_pos, voltage );
            Delay_ms( 100 );
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    if ( HWMONITOR_OK == hwmonitor_get_temperature ( &hwmonitor, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.3f [deg c]\r\n", temperature );
        Delay_ms( 100 );
    }
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HWMonitor

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

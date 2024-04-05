\mainpage Main Page

---
# HW Monitor 2 click

> HW Monitor 2 Click is a compact add-on board used to monitor 
> and regulate the performance of various hardware components within an embedded system. 
> This board features the AMC80, an I2C-configurable system hardware monitor 
> from Texas Instruments that contains a 10-bit ADC capable of measuring seven positive voltages 
> and local temperature. The AMC80 also has two programmable fan speed monitoring inputs 
> besides other hardware monitoring functions like chassis intrusion detection, 
> additional external interrupt input, and master reset for external purposes, 
> as well as a programmable upper over-limit and lower under-limit alarms that activate 
> when the programmed limits are exceeded.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hwmonitor2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hw-monitor-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the HW Monitor 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HW Monitor 2 Click driver.

#### Standard key functions :

- `hwmonitor2_cfg_setup` Config Object Initialization function.
```c
void hwmonitor2_cfg_setup ( hwmonitor2_cfg_t *cfg );
```

- `hwmonitor2_init` Initialization function.
```c
err_t hwmonitor2_init ( hwmonitor2_t *ctx, hwmonitor2_cfg_t *cfg );
```

- `hwmonitor2_default_cfg` Click Default Configuration function.
```c
err_t hwmonitor2_default_cfg ( hwmonitor2_t *ctx );
```

#### Example key functions :

- `hwmonitor2_get_analog_inputs` HW Monitor 2 gets analog inputs voltage function.
```c
err_t hwmonitor2_get_analog_inputs ( hwmonitor2_t *ctx, uint8_t ch_pos, float *voltage );
```

- `hwmonitor2_get_temperature` HW Monitor 2 gets temperature function.
```c
err_t hwmonitor2_get_temperature ( hwmonitor2_t *ctx, float *temperature );
```

- `hwmonitor2_set_config` HW Monitor 2 set the configuration function.
```c
err_t hwmonitor2_set_config ( hwmonitor2_t *ctx, hwmonitor2_config_t config );
```

## Example Description

> This example demonstrates the use of the HW Monitor 2 Click board™.
> The demo application monitors analog voltage inputs and local temperature data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor2_cfg_t hwmonitor2_cfg;  /**< Click config object. */

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
    hwmonitor2_cfg_setup( &hwmonitor2_cfg );
    HWMONITOR2_MAP_MIKROBUS( hwmonitor2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor2_init( &hwmonitor2, &hwmonitor2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR2_ERROR == hwmonitor2_default_cfg ( &hwmonitor2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This example displays the Analog Voltage Inputs from CH0 to CH6 [mV] 
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float temperature, voltage;
    for ( uint8_t ch_pos = 0; ch_pos < 7; ch_pos++ )
    {
        if ( HWMONITOR2_OK == hwmonitor2_get_analog_inputs( &hwmonitor2, ch_pos, &voltage ) )
        {
            log_printf( &logger, "CH %d: %.1f mV\r\n", ( uint16_t ) ch_pos, voltage );
            Delay_ms ( 100 );
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    if ( HWMONITOR2_OK == hwmonitor2_get_temperature( &hwmonitor2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.3f [deg c]\r\n", temperature );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HWMonitor2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

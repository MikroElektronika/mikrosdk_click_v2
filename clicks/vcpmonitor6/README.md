
---
# VCP Monitor 6 Click

> [VCP Monitor 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6101) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6101&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the VCP Monitor 6 Click driver 
> for measurements of the voltage, current, power, energy, charge, and die temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor6

### Example Key Functions

- `vcpmonitor6_cfg_setup` Config Object Initialization function.
```c
void vcpmonitor6_cfg_setup ( vcpmonitor6_cfg_t *cfg );
```

- `vcpmonitor6_init` Initialization function.
```c
err_t vcpmonitor6_init ( vcpmonitor6_t *ctx, vcpmonitor6_cfg_t *cfg );
```

- `vcpmonitor6_default_cfg` Click Default Configuration function.
```c
err_t vcpmonitor6_default_cfg ( vcpmonitor6_t *ctx );
```

- `vcpmonitor6_get_bus_voltage` This function reads the BUS voltage output measurement in volts [V] by using the I2C serial interface.
```c
err_t vcpmonitor6_get_bus_voltage ( vcpmonitor6_t *ctx, float *voltage );
```

- `vcpmonitor6_get_current` This function reads the current measurement result in milliamperes [mA] by using the I2C serial interface.
```c
err_t vcpmonitor6_get_current ( vcpmonitor6_t *ctx, float *current );
```

- `vcpmonitor6_get_power` This function reads the power measurement result in watts [W] by using the I2C serial interface.
```c
err_t vcpmonitor6_get_power ( vcpmonitor6_t *ctx, float *power );
```

### Application Init

> The initialization of the I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor6_cfg_t vcpmonitor6_cfg;  /**< Click config object. */

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
    vcpmonitor6_cfg_setup( &vcpmonitor6_cfg );
    VCPMONITOR6_MAP_MIKROBUS( vcpmonitor6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == vcpmonitor6_init( &vcpmonitor6, &vcpmonitor6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VCPMONITOR6_ERROR == vcpmonitor6_default_cfg ( &vcpmonitor6 ) )
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
    if ( VCPMONITOR6_OK == vcpmonitor6_get_bus_voltage( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Voltage: %.2f [V]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_current( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Current: %.2f [mA]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_power( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Power: %.2f [W]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_energy( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Energy: %.2f [kJ]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_charge( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Charge: %.2f [C]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_temperature( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Temperature: %.2f [degC]\r\n", app_buf );
        Delay_ms ( 50 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---


---
# VCP Monitor 5 Click

> [VCP Monitor 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6091) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6091&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the VCP Monitor 5 Click driver 
> for measurements of the voltage, current, power, energy, charge, and die temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor5

### Example Key Functions

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

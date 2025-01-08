
---
# CO2 3 Click

> [CO2 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5646) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5646&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for CO2 3 Click driver.
> This driver provides the functions for sensor configuration 
> and reading the CO2 gas concentration in the air.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CO23

### Example Key Functions

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

> This example demonstrates the use of the CO2 3 Click board&trade;.
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

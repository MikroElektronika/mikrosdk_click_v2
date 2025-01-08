
---
# Current 12 Click

> [Current 12 Click](https://www.mikroe.com/?pid_product=MIKROE-6065) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6065&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Current 12 Click board 
> by reading and displaying the input current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current12

### Example Key Functions

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

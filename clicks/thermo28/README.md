
---
# Thermo 28 Click

> [Thermo 28 Click](https://www.mikroe.com/?pid_product=MIKROE-5466) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5466&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 28 Click board&trade; 
> by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo28

### Example Key Functions

- `thermo28_cfg_setup` Config Object Initialization function.
```c
void thermo28_cfg_setup ( thermo28_cfg_t *cfg );
```

- `thermo28_init` Initialization function.
```c
err_t thermo28_init ( thermo28_t *ctx, thermo28_cfg_t *cfg );
```

- `thermo28_default_cfg` Click Default Configuration function.
```c
err_t thermo28_default_cfg ( thermo28_t *ctx );
```

- `thermo28_get_temperature` Thermo 28 get temperature function.
```c
err_t thermo28_get_temperature ( thermo28_t *ctx, float *temperature );
```

- `thermo28_set_config` Thermo 28 set configuration function.
```c
err_t thermo28_set_config ( thermo28_t *ctx, thermo28_config_t config );
```

- `thermo28_set_continuous_conversion` Thermo 28 set continuous conversion function.
```c
err_t thermo28_set_continuous_conversion ( thermo28_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo28_cfg_t thermo28_cfg;  /**< Click config object. */

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
    thermo28_cfg_setup( &thermo28_cfg );
    THERMO28_MAP_MIKROBUS( thermo28_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo28_init( &thermo28, &thermo28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( THERMO28_ERROR == thermo28_default_cfg ( &thermo28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a Thermo 28 Click board&trade;.
> Reads the temperature measurement in degree Celsius and displays the results.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float temperature;
   
    if ( THERMO28_OK == thermo28_get_temperature( &thermo28, &temperature ) )
    {
        log_printf( &logger, " Temperature [degC]: %.2f \r\n", temperature );
        Delay_ms ( 1000 );
    }
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

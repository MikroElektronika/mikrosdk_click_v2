
---
# ADC 23 Click

> [ADC 23 Click](https://www.mikroe.com/?pid_product=MIKROE-5861) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5861&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 23 Click board&trade; 
> by reading and writing data by using SPI serial interface and reading results of AD conversion.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC23

### Example Key Functions

- `adc23_cfg_setup` Config Object Initialization function.
```c
void adc23_cfg_setup ( adc23_cfg_t *cfg );
```

- `adc23_init` Initialization function.
```c
err_t adc23_init ( adc23_t *ctx, adc23_cfg_t *cfg );
```

- `adc23_default_cfg` Click Default Configuration function.
```c
err_t adc23_default_cfg ( adc23_t *ctx );
```

- `adc23_get_voltage` ADC 23 read get voltage level function.
```c
err_t adc23_get_voltage ( adc23_t *ctx, float *voltage );
```

- `adc23_read_conversion_data` ADC 23 read conversion data function.
```c
err_t adc23_read_conversion_data ( adc23_t *ctx, int32_t *adc_data );
```

- `adc23_start_conversion` ADC 23 start conversion function.
```c
err_t adc23_start_conversion ( adc23_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc23_cfg_t adc23_cfg;  /**< Click config object. */

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
    adc23_cfg_setup( &adc23_cfg );
    ADC23_MAP_MIKROBUS( adc23_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc23_init( &adc23, &adc23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC23_ERROR == adc23_default_cfg ( &adc23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the voltage levels from analog input and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static float voltage = 0.0;
    if ( ADC23_OK == adc23_get_voltage( &adc23, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f [mV]\r\n", voltage );
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


---
# ADC 22 Click

> [ADC 22 Click](https://www.mikroe.com/?pid_product=MIKROE-5640) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5640&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 22 Click board&trade; 
> by reading and writing data by using SPI serial interface and reading results of AD conversion.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC22

### Example Key Functions

- `adc22_cfg_setup` Config Object Initialization function.
```c
void adc22_cfg_setup ( adc22_cfg_t *cfg );
```

- `adc22_init` Initialization function.
```c
err_t adc22_init ( adc22_t *ctx, adc22_cfg_t *cfg );
```

- `adc22_default_cfg` Click Default Configuration function.
```c
err_t adc22_default_cfg ( adc22_t *ctx );
```

- `adc22_get_voltage` ADC 22 get voltage level function.
```c
err_t adc22_get_voltage ( adc22_t *ctx, float *voltage );
```

- `adc22_get_adc_raw_data` ADC 22 get ADC raw data function.
```c
err_t adc22_get_adc_raw_data ( adc22_t *ctx, uint16_t *raw_adc );
```

- `adc22_set_range` ADC 22 set range function.
```c
err_t adc22_set_range ( adc22_t *ctx, adc22_range_sel_t range );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc22_cfg_t adc22_cfg;  /**< Click config object. */

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
    adc22_cfg_setup( &adc22_cfg );
    ADC22_MAP_MIKROBUS( adc22_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc22_init( &adc22, &adc22_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( ADC22_ERROR == adc22_default_cfg ( &adc22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the voltage levels from analog input and displays the results.
> By default, the operating input range sets from 0V to 12.288V [3×Vref;Vref=4.096V].
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{   
    static float voltage = 0.0;
    if ( ADC22_OK == adc22_get_voltage ( &adc22, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f V\r\n", voltage );
        log_printf( &logger, " ----------------\r\n" );
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

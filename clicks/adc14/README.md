
---
# ADC 14 Click

> [ADC 14 Click](https://www.mikroe.com/?pid_product=MIKROE-5880) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5880&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 14 Click board&trade; 
> by reading results of AD conversion by using SPI serial interface.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC14

### Example Key Functions

- `adc14_cfg_setup` Config Object Initialization function.
```c
void adc14_cfg_setup ( adc14_cfg_t *cfg );
```

- `adc14_init` Initialization function.
```c
err_t adc14_init ( adc14_t *ctx, adc14_cfg_t *cfg );
```

- `adc14_get_voltage`  ADC 14 get voltage function.
```c
err_t adc14_get_voltage ( adc14_t *ctx, float *voltage );
```

- `adc14_read_conversion_data` ADC 14 read conversion data function.
```c
err_t adc14_read_conversion_data ( adc14_t *ctx, uint16_t *adc_data );
```

- `adc14_set_vref` ADC 14 set voltage reference function.
```c
err_t adc14_set_vref ( adc14_t *ctx, float vref );
```

### Application Init

> Initialization of SPI module and log UART and enabled internal voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc14_cfg_t adc14_cfg;  /**< Click config object. */

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
    adc14_cfg_setup( &adc14_cfg );
    ADC14_MAP_MIKROBUS( adc14_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc14_init( &adc14, &adc14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application gets the voltage levels from analog input and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float voltage = 0.0;
    if ( ADC14_OK == adc14_get_voltage( &adc14, &voltage ) )
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

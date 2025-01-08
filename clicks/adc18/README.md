
---
# ADC 18 Click

> [ADC 18 Click](https://www.mikroe.com/?pid_product=MIKROE-5132) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5132&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ADC 18 Click board by reading the voltage from 12 analog input single-ended channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC18

### Example Key Functions

- `adc18_cfg_setup` Config Object Initialization function.
```c
void adc18_cfg_setup ( adc18_cfg_t *cfg );
```

- `adc18_init` Initialization function.
```c
err_t adc18_init ( adc18_t *ctx, adc18_cfg_t *cfg );
```

- `adc18_default_cfg` Click Default Configuration function.
```c
err_t adc18_default_cfg ( adc18_t *ctx );
```

- `adc18_set_active_channel` This function sets the active channel.
```c
err_t adc18_set_active_channel ( adc18_t *ctx, uint8_t channel );
```

- `adc18_start_conversion` This function starts the conversion with the selected data rate.
```c
err_t adc18_start_conversion ( adc18_t *ctx, uint8_t data_rate );
```

- `adc18_read_voltage` This function reads RAW ADC value of previous conversion and converts it to voltage. 
```c
err_t adc18_read_voltage ( adc18_t *ctx, float *voltage );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc18_cfg_t adc18_cfg;  /**< Click config object. */

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
    adc18_cfg_setup( &adc18_cfg );
    ADC18_MAP_MIKROBUS( adc18_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc18_init( &adc18, &adc18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC18_ERROR == adc18_default_cfg ( &adc18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the voltage from 12 analog input single-ended channels on the USB UART approximately once per second.

```c
void application_task ( void )
{
    static uint8_t channel = ADC18_CH_AI1_SINGLE_ENDED;
    if ( ADC18_OK == adc18_set_active_channel ( &adc18, channel ) )
    {
        adc18_start_conversion ( &adc18, ADC18_DATA_RATE_225_SPS );
        
        // Waits for the availability of the conversion result
        while ( adc18_get_rdy_pin ( &adc18 ) );
        
        adc18_stop_conversion ( &adc18 );
        
        float voltage;
        if ( ADC18_OK == adc18_read_voltage ( &adc18, &voltage ) )
        {
            log_printf ( &logger, "Channel AI%u: %.2f V\r\n", channel + 1, voltage );
            if ( ++channel > ADC18_CH_AI12_SINGLE_ENDED )
            {
                channel = ADC18_CH_AI1_SINGLE_ENDED;
                log_printf ( &logger, "\r\n" );
                Delay_ms ( 1000 );
            }
        }
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

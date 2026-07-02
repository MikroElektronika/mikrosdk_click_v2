
---
# ADC 28 Click

> [ADC 28 Click](https://www.mikroe.com/?pid_product=MIKROE-6943) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6943&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Apr 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 28 Click board by reading
voltage levels from all 8 single-ended analog input channels (CH0-CH7)
and displaying the results via UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC28

### Example Key Functions

- `adc28_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void adc28_cfg_setup ( adc28_cfg_t *cfg );
```

- `adc28_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t adc28_init ( adc28_t *ctx, adc28_cfg_t *cfg );
```

- `adc28_default_cfg` This function executes a default configuration of ADC 28 Click board.
```c
err_t adc28_default_cfg ( adc28_t *ctx );
```

- `adc28_read_raw_adc` This function reads the RAW ADC measurement.
```c
err_t adc28_read_raw_adc ( adc28_t *ctx, uint8_t channel, uint16_t *raw_data );
```

- `adc28_read_voltage` This function reads the ADC result from the selected channel and converts it to a voltage level.
```c
err_t adc28_read_voltage ( adc28_t *ctx, uint8_t channel, float *voltage );
```

- `adc28_get_alert_pin` This function returns the logic state of the ALT (ALERT) pin.
```c
uint8_t adc28_get_alert_pin ( adc28_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc28_cfg_t adc28_cfg;  /**< Click config object. */

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
    adc28_cfg_setup( &adc28_cfg );
    ADC28_MAP_MIKROBUS( adc28_cfg, MIKROBUS_POSITION_ADC28 );
    if ( I2C_MASTER_ERROR == adc28_init( &adc28, &adc28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC28_ERROR == adc28_default_cfg ( &adc28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage from each channel (CH0 to CH7) and displays
the results on the USB UART once per second.

```c
void application_task ( void ) 
{
    float voltage = 0;

    for ( uint8_t channel = ADC28_CHANNEL_0; channel <= ADC28_CHANNEL_7; channel++ )
    {
        if ( ADC28_OK == adc28_read_voltage( &adc28, channel, &voltage ) )
        {
            log_printf( &logger, " CH%u: %.3f V\r\n", ( uint16_t ) channel, voltage );
        }
    }
    log_printf( &logger, " -------------------\r\n" );
    Delay_ms( 1000 );
}
```

### Note

> The input voltage range on each channel is 0 V to 3.3 V.
Do not apply voltages outside this range to the analog inputs.

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

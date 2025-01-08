
---
# ADC 20 Click

> [ADC 20 Click](https://www.mikroe.com/?pid_product=MIKROE-5424) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5424&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ADC 20 Click board by displaying the state of 8 channels
configured as analog inputs (CH2-CH5), digital inputs (CH0-CH1) and digital outputs (CH6-CH7).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC20

### Example Key Functions

- `adc20_cfg_setup` Config Object Initialization function.
```c
void adc20_cfg_setup ( adc20_cfg_t *cfg );
```

- `adc20_init` Initialization function.
```c
err_t adc20_init ( adc20_t *ctx, adc20_cfg_t *cfg );
```

- `adc20_default_cfg` Click Default Configuration function.
```c
err_t adc20_default_cfg ( adc20_t *ctx );
```

- `adc20_read_data` This function reads two bytes of data by using SPI serial interface.
```c
err_t adc20_read_data ( adc20_t *ctx, uint16_t *data_out );
```

- `adc20_set_gpo_value` This function sets the gpo value for the selected channels.
```c
err_t adc20_set_gpo_value ( adc20_t *ctx, uint8_t ch_mask, uint8_t value );
```

- `adc20_read_gpio_value` This function reads the gpio pins value.
```c
err_t adc20_read_gpio_value ( adc20_t *ctx, uint8_t *gpio_value );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc20_cfg_t adc20_cfg;  /**< Click config object. */

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
    adc20_cfg_setup( &adc20_cfg );
    ADC20_MAP_MIKROBUS( adc20_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc20_init( &adc20, &adc20_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC20_ERROR == adc20_default_cfg ( &adc20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Starts the auto sequence mode, reads the 12bit ADC value from analog input channels (CH2-CH5) and
displays the values converted to voltage on the USB UART. After that, stops auto sequence mode and
toggles the state of digital output pins (CH6-CH7), then reads and displays the state of all GPIO pins.

```c
void application_task ( void )
{
    adc20_start_auto_sequence ( &adc20 );
    for ( uint8_t ch_id = ADC20_CHANNEL_ID_2; ch_id <= ADC20_CHANNEL_ID_5; ch_id++ )
    {
        uint16_t adc_data = 0;
        if ( ADC20_OK == adc20_read_data ( &adc20, &adc_data ) )
        {
            float voltage = ( float ) ( adc_data >> ADC20_ADC_OFFSET ) / ADC20_RES_12BIT * ADC20_VREF_3V3;
            log_printf ( &logger, " AIN%u: %.2f V\r\n", ( adc_data & ADC20_CHANNEL_ID_MASK ), voltage );
        }
    }
    adc20_stop_auto_sequence ( &adc20 );
    static uint8_t out_logic_state = ADC20_GPIO_VALUE_LOW;
    if ( ADC20_OK == adc20_set_gpo_value ( &adc20, ( ADC20_CHANNEL_6 | ADC20_CHANNEL_7 ), out_logic_state ) )
    {
        uint8_t gpio_value = 0;
        if ( ADC20_OK == adc20_read_gpio_value ( &adc20, &gpio_value ) )
        {
            log_printf ( &logger, " GPIO state: 0x%.2X\r\n", gpio_value );
        }
    }
    out_logic_state = !out_logic_state;
    log_printf ( &logger, "\r\n" );
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


---
# ADC 21 Click

> [ADC 21 Click](https://www.mikroe.com/?pid_product=MIKROE-5531) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5531&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ADC 21 Click board by reading and displaying the voltage levels from 8 analog input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC21

### Example Key Functions

- `adc21_cfg_setup` Config Object Initialization function.
```c
void adc21_cfg_setup ( adc21_cfg_t *cfg );
```

- `adc21_init` Initialization function.
```c
err_t adc21_init ( adc21_t *ctx, adc21_cfg_t *cfg );
```

- `adc21_read_raw_adc` This function reads raw ADC value from the selected channel by using SPI serial interface.
```c
err_t adc21_read_raw_adc ( adc21_t *ctx, uint8_t channel, uint16_t *raw_adc );
```

- `adc21_read_voltage` This function reads raw ADC value from the selected channel and converts it to proportional voltage level depending on the avcc selection.
```c
err_t adc21_read_voltage ( adc21_t *ctx, uint8_t channel, float avcc, float *voltage );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc21_cfg_t adc21_cfg;  /**< Click config object. */

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
    adc21_cfg_setup( &adc21_cfg );
    ADC21_MAP_MIKROBUS( adc21_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc21_init( &adc21, &adc21_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage levels from all 8 analog input channels and displays the results on the USB UART once per second approximately.

```c
void application_task ( void )
{
    static uint8_t ch_num = ADC21_CHANNEL_0;
    float ch_voltage;
    if ( ADC21_OK == adc21_read_voltage ( &adc21, ch_num, ADC21_AVCC_3V3, &ch_voltage ) )
    {
        log_printf ( &logger, " CH%u voltage: %.2f V\r\n", ( uint16_t ) ch_num, ch_voltage );
    }
    if ( ++ch_num > ADC21_CHANNEL_7 )
    {
        log_printf ( &logger, " ------------------------\r\n\n" );
        ch_num = ADC21_CHANNEL_0;
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

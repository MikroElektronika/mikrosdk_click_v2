
---
# ADC 27 Click

> [ADC 27 Click](https://www.mikroe.com/?pid_product=MIKROE-6651) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6651&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 27 Click board by reading voltages
from multiple analog input channels configured in both single-ended and differential modes.
The measured voltage values are displayed via UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC27

### Example Key Functions

- `adc27_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void adc27_cfg_setup ( adc27_cfg_t *cfg );
```

- `adc27_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t adc27_init ( adc27_t *ctx, adc27_cfg_t *cfg );
```

- `adc27_default_cfg` This function executes a default configuration of ADC 27 Click board.
```c
err_t adc27_default_cfg ( adc27_t *ctx );
```

- `adc27_set_config` This function sets the configuration for the selected channel of the ADC 27 Click board.
```c
err_t adc27_set_config ( adc27_t *ctx, uint8_t config );
```

- `adc27_read_raw_data` This function reads raw ADC data from the selected channel.
```c
err_t adc27_read_raw_data ( adc27_t *ctx, uint8_t channel, uint16_t *data_out );
```

- `adc27_read_voltage` This function reads the ADC value from the selected channel and converts it to a voltage level using the configured range.
```c
err_t adc27_read_voltage ( adc27_t *ctx, uint8_t channel, float *voltage );
```

### Application Init

> Initializes the logger and the ADC 27 Click driver, and performs the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc27_cfg_t adc27_cfg;  /**< Click config object. */

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
    adc27_cfg_setup( &adc27_cfg );
    ADC27_MAP_MIKROBUS( adc27_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc27_init( &adc27, &adc27_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC27_ERROR == adc27_default_cfg ( &adc27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and logs voltage values from channels CH0-CH3 (single-ended) and CH4/CH5, CH6/CH7 (differential).

```c
void application_task ( void )
{
    float voltage = 0;
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_0, &voltage ) )
    {
        log_printf ( &logger, " CH0: %.3f V (gnd,vref/2)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_1, &voltage ) )
    {
        log_printf ( &logger, " CH1: %.3f V (gnd,vref)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_2, &voltage ) )
    {
        log_printf ( &logger, " CH2: %.3f V (-vref/4,vref/4)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_3, &voltage ) )
    {
        log_printf ( &logger, " CH3: %.3f V (-vref/2,vref/2)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_DIF_45, &voltage ) )
    {
        log_printf ( &logger, " CH4+/CH5-: %.3f V (-vref,vref)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_DIF_67, &voltage ) )
    {
        log_printf ( &logger, " CH6+/CH7-: %.3f V (-2xvref,2xvref)\r\n\n", voltage );
    }
    Delay_ms ( 1000 );
}
```

### Note

> CH0 and CH1 operate with respect to ground and VREF, while CH2 and CH3 provide bipolar inputs.
Channels CH4/CH5 and CH6/CH7 are differential input pairs. Measurements are taken every second.

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

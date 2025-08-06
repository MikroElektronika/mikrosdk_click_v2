
---
# ADAC 4 Click

> [ADAC 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6722) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6722&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the ADAC 4 Click board which features 
an 8-channel, 12-bit DAC and ADC. The application configures each DAC channel 
with incremental values and measures the corresponding output voltage using 
the integrated ADC, as well as logs the device die temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADAC4

### Example Key Functions

- `adac4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void adac4_cfg_setup ( adac4_cfg_t *cfg );
```

- `adac4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t adac4_init ( adac4_t *ctx, adac4_cfg_t *cfg );
```

- `adac4_default_cfg` This function executes a default configuration of ADAC 4 Click board.
```c
err_t adac4_default_cfg ( adac4_t *ctx );
```

- `adac4_write_dac` This function writes a value to the specified DAC channel.
```c
err_t adac4_write_dac ( adac4_t *ctx, uint8_t channel, uint16_t dac_data );
```

- `adac4_read_adc_voltage` This function reads an ADC voltage value from the specified channel.
```c
err_t adac4_read_adc_voltage ( adac4_t *ctx, uint8_t channel, float *voltage );
```

- `adac4_read_die_temp` This function reads and calculates internal die temperature.
```c
err_t adac4_read_die_temp ( adac4_t *ctx, float *die_temp );
```

### Application Init

> Initializes the logger and the Click board driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adac4_cfg_t adac4_cfg;  /**< Click config object. */

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
    adac4_cfg_setup( &adac4_cfg );
    ADAC4_MAP_MIKROBUS( adac4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adac4_init( &adac4, &adac4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADAC4_ERROR == adac4_default_cfg ( &adac4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Iterates through all 8 DAC/ADC channels, sets an output voltage, reads back the 
corresponding ADC voltage, and logs both values. Also reads and logs the die temperature.

```c
void application_task ( void )
{
    static uint16_t dac_data = ADAC4_DAC_DATA_MIN;
    float die_temp = 0;
    float voltage = 0;
    for ( uint8_t ch_sel = ADAC4_CHANNEL_0; ch_sel <= ADAC4_CHANNEL_7; ch_sel++ )
    {
        log_printf ( &logger, "\r\n CH%u -> ", ( uint16_t ) ch_sel, dac_data );
        if ( ADAC4_OK == adac4_write_dac ( &adac4, ch_sel, dac_data ) )
        {
            log_printf ( &logger, "DAC: %.4u, ", dac_data );
        }
        if ( ADAC4_OK == adac4_read_adc_voltage ( &adac4, ch_sel, &voltage ) )
        {
            log_printf ( &logger, "Voltage: %.3f", voltage );
        }
        dac_data += 200;
        if ( dac_data > ADAC4_DAC_DATA_MAX )
        {
            dac_data = ADAC4_DAC_DATA_MIN;
        }
    }
    if ( ADAC4_OK == adac4_read_die_temp ( &adac4, &die_temp ) )
    {
        log_printf ( &logger, "\r\n Die Temperature: %.2f degC\r\n", die_temp );
    }
    Delay_ms ( 1000 );
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

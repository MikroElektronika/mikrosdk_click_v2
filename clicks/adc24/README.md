
---
# ADC 24 Click

> [ADC 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6039) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6039&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 24 Click board 
> by reading and writing data by using the SPI serial interface 
> and reading results of AD conversion.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC24

### Example Key Functions

- `adc24_cfg_setup` Config Object Initialization function.
```c
void adc24_cfg_setup ( adc24_cfg_t *cfg );
```

- `adc24_init` Initialization function.
```c
err_t adc24_init ( adc24_t *ctx, adc24_cfg_t *cfg );
```

- `adc24_get_voltage` This function reads the results of 12-bit ADC raw data and converts them to proportional voltage levels by using the SPI serial interface.
```c
err_t adc24_get_voltage ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, float *voltage );
```

- `adc24_get_adc_data` This function reads a conversion result and selected channel by using the SPI serial interface.
```c
err_t adc24_get_adc_data ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, uint16_t *adc_data );
```

### Application Init

> Initialization of SPI module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc24_cfg_t adc24_cfg;  /**< Click config object. */

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
    adc24_cfg_setup( &adc24_cfg );
    ADC24_MAP_MIKROBUS( adc24_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc24_init( &adc24, &adc24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    ctrl.ch_sel = ADC24_CH_SEL_IN_0;
    ctrl.pm = ADC24_PM_NORMAL;
    ctrl.seq_shadow = ADC24_SEQ_SHADOW_AN_INPUT;
    ctrl.weak = ADC24_WEAK_DOUT_THREE_STATE;
    ctrl.range = ADC24_RANGE_VREF_5V;
    ctrl.coding = ADC24_CODING_BIN;

    log_info( &logger, " Application Task " );
    log_printf( &logger, "_____________\r\n" );
}
```

### Application Task

> The demo application reads the voltage levels 
> from all 15 analog input channels and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t ch_pos = 0;
    float voltage = 0;
    for ( uint8_t n_cnt = ADC24_CH_SEL_IN_0; n_cnt <= ADC24_CH_SEL_IN_15; n_cnt++ )
    {
        ctrl.ch_sel = n_cnt;
        if ( ADC24_OK == adc24_get_voltage( &adc24, ctrl, &ch_pos, &voltage ) )
        {
            log_printf( &logger, " IN%u : %.3f V\r\n", ( uint16_t ) ch_pos, voltage );
        }
        Delay_ms ( 100 );  
    }
    log_printf( &logger, "_____________\r\n" );
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

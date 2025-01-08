
---
# ADC 10 Click

> [ADC 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4488) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4488&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This is an example that demonstrates the use of the ADC 10 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc10

### Example Key Functions

- `adc10_cfg_setup` Config Object Initialization function.
```c
void adc10_cfg_setup ( adc10_cfg_t *cfg );
```

- `adc10_init` Initialization function.
```c
err_t adc10_init ( adc10_t *ctx, adc10_cfg_t *cfg );
```

- `adc10_default_cfg` Click Default Configuration function.
```c
void adc10_default_cfg ( adc10_t *ctx );
```

- `adc10_start_sync` ADC 10 Start the synchronization function.
```c
void adc10_start_sync ( adc10_t *ctx );
```

- `adc10_get_ch_output` ADC 10 Get the channel output function.
```c
int32_t adc10_get_ch_output ( adc10_t *ctx, uint8_t sel_ch );
```

- `adc10_calc_voltage` ADC 10 Calculate the voltage function.
```c
float adc10_calc_voltage ( adc10_t *ctx, int32_t adc_data, float vref, uint8_t gain );
```

### Application Init

> Initialization driver enables - UART,
select analog input channel 0, perform a hardware and software reset
and set the default device configuration, also, write a log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc10_cfg_t adc10_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n-------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    adc10_cfg_setup( &adc10_cfg );
    ADC10_MAP_MIKROBUS( adc10_cfg, MIKROBUS_1 );
    err_t init_flag  = adc10_init( &adc10, &adc10_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    select_ch = ADC10_ANALOG_INPUT_CH_3;
    
    // Hardware reset.
    
    adc10_hw_reset( &adc10 );
    Delay_ms ( 100 );
    
    // Software reset.
    
    adc10_reset( &adc10 );
    Delay_ms ( 1000 );

    // Click default configuration.
    
    adc10_default_cfg ( &adc10 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> In this example, we monitor and display
24-bits of data ( from 0 to 8388607 ) of ADC and voltage ( from 0 mV to 2048 mV )
on the selected channel ( CH-0, CH-1, CH-2 or CH-3 ).
Results are being sent to the Usart Terminal where you can track their changes.
All data logs write on USB uart changes approximately for every 1 sec.

```c
void application_task ( void ) 
{   
    adc10_start_sync( &adc10 );
    Delay_ms ( 1 );

    while ( adc10_check_drdy( &adc10 ) == ADC10_NEW_DATA_NOT_READY );

    out_data = adc10_get_ch_output( &adc10, select_ch );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  ADC CH-%u : %.0f\r\n", ( uint16_t ) select_ch, ( float ) out_data );

    voltage = adc10_calc_voltage( &adc10, out_data, ADC10_VREF_INTERNAL, ADC10_GAIN_1 );
    log_printf( &logger, "  Voltage  : %.2f mV\r\n", voltage );
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

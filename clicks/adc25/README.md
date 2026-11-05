
---
# ADC 25 Click

> [ADC 25 Click](https://www.mikroe.com/?pid_product=MIKROE-7012) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7012&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 25 Click board by reading
voltage and current levels from input channels in a continuous sequence and
displaying the results over UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC25

### Example Key Functions

- `adc25_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void adc25_cfg_setup ( adc25_cfg_t *cfg );
```

- `adc25_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t adc25_init ( adc25_t *ctx, adc25_cfg_t *cfg );
```

- `adc25_default_cfg` This function executes a default configuration of ADC 25 Click board.
```c
err_t adc25_default_cfg ( adc25_t *ctx );
```

- `adc25_start_conversion` This function starts ADC conversions by setting the START bit in the CONVERSION_CTRL register.
```c
err_t adc25_start_conversion ( adc25_t *ctx );
```

- `adc25_stop_conversion` This function stops ADC conversions by setting the STOP bit in the CONVERSION_CTRL register.
```c
err_t adc25_stop_conversion ( adc25_t *ctx );
```

- `adc25_get_voltage_seq` This function waits for the sequencer to complete a full sequence, then reads conversion results.
```c
err_t adc25_get_voltage_seq ( adc25_t *ctx, float *voltage, uint8_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc25_cfg_t adc25_cfg;  /**< Click config object. */

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
    adc25_cfg_setup( &adc25_cfg );
    ADC25_MAP_MIKROBUS( adc25_cfg, MIKROBUS_POSITION_ADC25 );
    if ( SPI_MASTER_ERROR == adc25_init( &adc25, &adc25_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC25_ERROR == adc25_default_cfg ( &adc25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the sequencer to complete a full sequence, reads all
8 conversion results and logs each channel voltage[V] or current[mA] over UART.
Results are updated once per second.

```c
void application_task ( void )
{
    float voltage[ ADC25_NUM_SEQ_STEPS ] = { 0 };

    if ( ADC25_OK == adc25_get_voltage_seq( &adc25, voltage, ADC25_NUM_SEQ_STEPS ) )
    {
        log_printf( &logger, " TB1 AIN0 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 0 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB1 AIN1 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 1 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB2 AIN6 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 2 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB2 AIN7 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 3 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB3 AIN8-AIN9   (Diff Voltage):  %.2f [V]\r\n",  voltage[ 4 ] );
        log_printf( &logger, " TB4 AIN10-AIN11 (Diff Voltage):  %.2f [V]\r\n",  voltage[ 5 ] );
        log_printf( &logger, " TB5 AIN12-AIN13 (Diff Current):  %.2f [mA]\r\n", voltage[ 6 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB6 AIN14-AIN15 (Diff Current):  %.2f [mA]\r\n", voltage[ 7 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " -----------------------------------\r\n" );
    }
    else
    {
        log_error( &logger, " Read timeout." );
    }
    Delay_ms ( 1000 );
}
```

### Note

> The absolute input voltage range on each channel is -20.5V to +20.5V.
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

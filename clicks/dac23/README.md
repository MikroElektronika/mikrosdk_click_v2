
---
# DAC 23 Click

> [DAC 23 Click](https://www.mikroe.com/?pid_product=MIKROE-6986) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6986&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the DAC 23 Click board by
configuring all four DAC output channels and verifying their output
voltages through the integrated analog multiplexer and ADC. The
application also monitors the output current of each channel.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC23

### Example Key Functions

- `dac23_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dac23_cfg_setup ( dac23_cfg_t *cfg );
```

- `dac23_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dac23_init ( dac23_t *ctx, dac23_cfg_t *cfg );
```

- `dac23_default_cfg` This function executes a default configuration of DAC 23 Click board.
```c
err_t dac23_default_cfg ( dac23_t *ctx );
```

- `dac23_set_mux_sel` This function sets the output multiplexer select for ADC reading.
```c
err_t dac23_set_mux_sel ( dac23_t *ctx, uint8_t mux_sel );
```

- `dac23_set_out_voltage` This function sets the output voltage of one or more channels by converting it to a corresponding DAC code and updating the device.
```c
err_t dac23_set_out_voltage ( dac23_t *ctx, uint8_t channel, float voltage );
```

- `dac23_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level.
```c
err_t dac23_read_voltage_avg ( dac23_t *ctx, uint16_t num_conv, float *voltage_avg );
```

### Application Init

> Initializes the logger, configures the DAC 23 Click board, and applies the default device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac23_cfg_t dac23_cfg;  /**< Click config object. */

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
    dac23_cfg_setup( &dac23_cfg );
    DAC23_MAP_MIKROBUS( dac23_cfg, MIKROBUS_POSITION_DAC23 );
    if ( SPI_MASTER_ERROR == dac23_init( &dac23, &dac23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC23_ERROR == dac23_default_cfg ( &dac23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles the output voltage of all four DAC channels across the full
0 V to 2.5 V output range, measures each output voltage using the
internal analog multiplexer and ADC, then measures and logs the
corresponding output current for every channel.

```c
void application_task ( void )
{
    static float step = DAC23_VFS_OUT_RANGE_0_TO_2_5V / NUMBER_OF_STEPS;
    static float out_voltage = DAC23_VFS_OUT_RANGE_0_TO_2_5V / NUMBER_OF_STEPS;
    float mux_voltage = 0;
    for ( uint8_t channel = DAC23_CHANNEL_0; channel <= DAC23_CHANNEL_3; channel++ )
    {
        if ( ( DAC23_OK == dac23_set_mux_sel ( &dac23, DAC23_MUX_SEL_VOUT0 + 
                                                       channel * ( DAC23_MUX_SEL_VOUT1 - 
                                                                   DAC23_MUX_SEL_VOUT0 ) ) ) && 
             ( DAC23_OK == dac23_set_out_voltage ( &dac23, channel, out_voltage ) ) )
        {
            log_printf ( &logger, " VOUT%u set: %.3f V\r\n", ( uint16_t ) channel, out_voltage );
            if ( DAC23_OK == dac23_read_voltage_avg ( &dac23, DAC23_NUM_CONVERSIONS, &mux_voltage ) ) 
            {
                log_printf ( &logger, " VOUT%u read: %.3f V\r\n", ( uint16_t ) channel, mux_voltage );
            }
        }
        if ( DAC23_OK == dac23_set_mux_sel ( &dac23, DAC23_MUX_SEL_IOUT0_SOURCE + 
                                                     channel * ( DAC23_MUX_SEL_IOUT1_SOURCE - 
                                                                 DAC23_MUX_SEL_IOUT0_SOURCE ) ) )
        {
            if ( DAC23_OK == dac23_read_voltage_avg ( &dac23, DAC23_NUM_CONVERSIONS, &mux_voltage ) ) 
            {
                log_printf ( &logger, " IOUT%u read: %.1f mA\r\n\n", 
                             ( uint16_t ) channel, mux_voltage * DAC23_MUX_CURRENT_RESOLUTION_MA );
            }
        }
    }
    out_voltage += step;
    if ( ( out_voltage > DAC23_VFS_OUT_RANGE_0_TO_2_5V ) || 
         ( out_voltage < DAC23_VZS_OUT_RANGE_0_TO_2_5V ) )
    {
        step = -step;
        out_voltage += step;
        out_voltage += step;
    }
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

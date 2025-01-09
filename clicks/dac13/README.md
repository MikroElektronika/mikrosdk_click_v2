
---
# DAC 13 Click

> [DAC 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5412) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5412&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DAC 13 Click board by changing the outputs voltage level every 2 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC13

### Example Key Functions

- `dac13_cfg_setup` Config Object Initialization function.
```c
void dac13_cfg_setup ( dac13_cfg_t *cfg );
```

- `dac13_init` Initialization function.
```c
err_t dac13_init ( dac13_t *ctx, dac13_cfg_t *cfg );
```

- `dac13_default_cfg` Click Default Configuration function.
```c
err_t dac13_default_cfg ( dac13_t *ctx );
```

- `dac13_set_output_range` This function sets the output voltage range and as well as the @b ctx->v_zero_scale and @b ctx->v_full_scale variables for the selected range.
```c
err_t dac13_set_output_range ( dac13_t *ctx, uint8_t out_range );
```

- `dac13_set_dac_value` This function sets the raw DAC value.
```c
err_t dac13_set_dac_value ( dac13_t *ctx, uint16_t dac_value );
```

- `dac13_set_output_voltage` This function sets the DAC output voltage.
```c
err_t dac13_set_output_voltage ( dac13_t *ctx, float voltage );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac13_cfg_t dac13_cfg;  /**< Click config object. */

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
    dac13_cfg_setup( &dac13_cfg );
    DAC13_MAP_MIKROBUS( dac13_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac13_init( &dac13, &dac13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC13_ERROR == dac13_default_cfg ( &dac13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 2 seconds and logs the voltage value on the USB UART.
It will go through the entire voltage range taking into account the number of steps which is defined below.

```c
void application_task ( void )
{
    float step = ( dac13.v_full_scale - dac13.v_zero_scale ) / ( NUMBER_OF_STEPS - 1 );
    float out_voltage = dac13.v_zero_scale;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC13_OK == dac13_set_output_voltage ( &dac13, out_voltage ) )
        {
            log_printf ( &logger, " Output voltage : %.2f V\r\n\n", out_voltage );
            out_voltage += step;
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
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

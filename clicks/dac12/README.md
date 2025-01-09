
---
# DAC 12 Click

> [DAC 12 Click](https://www.mikroe.com/?pid_product=MIKROE-5097) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5097&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DAC 12 Click board by changing the outputs voltage level every 2 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC12

### Example Key Functions

- `dac12_cfg_setup` Config Object Initialization function.
```c
void dac12_cfg_setup ( dac12_cfg_t *cfg );
```

- `dac12_init` Initialization function.
```c
err_t dac12_init ( dac12_t *ctx, dac12_cfg_t *cfg );
```

- `dac12_default_cfg` Click Default Configuration function.
```c
err_t dac12_default_cfg ( dac12_t *ctx );
```

- `dac12_soft_reset` This function executes the software reset command.
```c
err_t dac12_soft_reset ( dac12_t *ctx );
```

- `dac12_set_channel_value` This function sets the raw DAC value to the specific channels output.
```c
err_t dac12_set_channel_value ( dac12_t *ctx, uint8_t channel, uint16_t dac_value );
```

- `dac12_set_channel_voltage` This function sets the output voltage of the specific channels.
```c
err_t dac12_set_channel_voltage ( dac12_t *ctx, uint8_t channel, float voltage );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac12_cfg_t dac12_cfg;  /**< Click config object. */

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
    dac12_cfg_setup( &dac12_cfg );
    DAC12_MAP_MIKROBUS( dac12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac12_init( &dac12, &dac12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    DAC12_SET_DATA_SAMPLE_EDGE;
    
    if ( DAC12_ERROR == dac12_default_cfg ( &dac12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage of all channels every 2 seconds and logs the voltage value on the USB UART.
It will go through the entire voltage range taking into account the number of steps which is defined below.

```c
void application_task ( void )
{
    float step = DAC12_INTERNAL_VREF / NUMBER_OF_STEPS;
    float output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC12_OK == dac12_set_channel_voltage ( &dac12, DAC12_SELECT_CHANNEL_ALL, output_voltage ) )
        {
            log_printf( &logger, " All channels output voltage set to %.3f V\r\n", output_voltage );
            output_voltage += step;
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

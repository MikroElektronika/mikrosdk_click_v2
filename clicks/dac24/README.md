
---
# DAC 24 Click

> [DAC 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6944) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6944&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the control of DAC output voltage using the DAC 24 Click board.
The application sequentially increases the DAC output voltage on all channels in equal steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC24

### Example Key Functions

- `dac24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dac24_cfg_setup ( dac24_cfg_t *cfg );
```

- `dac24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dac24_init ( dac24_t *ctx, dac24_cfg_t *cfg );
```

- `dac24_set_power_down` This function sets the device in the selected power down mode.
```c
err_t dac24_set_power_down ( dac24_t *ctx, uint8_t pwr );
```

- `dac24_set_dac_value` This function writes the 8-bit DAC code value to one or more channels.
```c
err_t dac24_set_dac_value ( dac24_t *ctx, uint8_t channel, uint8_t value );
```

- `dac24_set_dac_voltage` This function sets the output voltage (in millivolts) for one or more channels.
```c
err_t dac24_set_dac_voltage ( dac24_t *ctx, uint8_t channel, uint16_t voltage_mv );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac24_cfg_t dac24_cfg;  /**< Click config object. */

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
    dac24_cfg_setup( &dac24_cfg );
    DAC24_MAP_MIKROBUS( dac24_cfg, MIKROBUS_POSITION_DAC24 );
    if ( SPI_MASTER_ERROR == dac24_init( &dac24, &dac24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Gradually increases the DAC output voltage on all channels in equal steps every 2 seconds.

```c
void application_task ( void )
{
    uint16_t step = DAC24_VCC_LEVEL / NUMBER_OF_STEPS;
    uint16_t output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC24_OK == dac24_set_dac_voltage ( &dac24, DAC24_CHANNEL_ALL, output_voltage ) )
        {
            log_printf ( &logger, " All channels output voltage set to %u mV\r\n", output_voltage );
        }
        output_voltage += step;
        Delay_ms ( 1000 ); 
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

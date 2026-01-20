
---
# DAC 20 Click

> [DAC 20 Click](https://www.mikroe.com/?pid_product=MIKROE-6825) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6825&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the control of DAC output voltage using the DAC 20 Click board.
The application sequentially increases the DAC output voltage on both channels in equal steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC20

### Example Key Functions

- `dac20_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dac20_cfg_setup ( dac20_cfg_t *cfg );
```

- `dac20_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dac20_init ( dac20_t *ctx, dac20_cfg_t *cfg );
```

- `dac20_default_cfg` This function executes a default configuration of DAC 20 Click board.
```c
err_t dac20_default_cfg ( dac20_t *ctx );
```

- `dac20_set_dac_value` This function writes the 12-bit DAC code value to one or more channels and latches the output values by toggling the LAT pin.
```c
err_t dac20_set_dac_value ( dac20_t *ctx, uint8_t channel, uint16_t value );
```

- `dac20_set_dac_voltage` This function sets the output voltage (in millivolts) for one or more channels by converting it to a corresponding DAC code and updating the device.
```c
err_t dac20_set_dac_voltage ( dac20_t *ctx, uint8_t channel, uint16_t voltage_mv );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac20_cfg_t dac20_cfg;  /**< Click config object. */

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
    dac20_cfg_setup( &dac20_cfg );
    DAC20_MAP_MIKROBUS( dac20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dac20_init( &dac20, &dac20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC20_ERROR == dac20_default_cfg ( &dac20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Gradually increases the DAC output voltage on both channels in equal steps every 2 seconds.

```c
void application_task ( void )
{
    uint16_t step = DAC20_VREF_INT / NUMBER_OF_STEPS;
    uint16_t output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC20_OK == dac20_set_dac_voltage ( &dac20, DAC20_CHANNEL_ALL, output_voltage ) )
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

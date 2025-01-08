
---
# Piezo Accel 2 25g Click

> [Piezo Accel 2 25g Click](https://www.mikroe.com/?pid_product=MIKROE-6408) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6408&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Piezo Accel 2 25g Click board by reading and displaying
the ADC values of X, Y, and Z axis, and the internal temperature sensor measurements. 
Those data can be visualized on the SerialPlot application.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PiezoAccel225g

### Example Key Functions

- `piezoaccel225g_cfg_setup` Config Object Initialization function.
```c
void piezoaccel225g_cfg_setup ( piezoaccel225g_cfg_t *cfg );
```

- `piezoaccel225g_init` Initialization function.
```c
err_t piezoaccel225g_init ( piezoaccel225g_t *ctx, piezoaccel225g_cfg_t *cfg );
```

- `piezoaccel225g_default_cfg` Click Default Configuration function.
```c
err_t piezoaccel225g_default_cfg ( piezoaccel225g_t *ctx );
```

- `piezoaccel225g_read_adc_data` This function reads raw ADC values of X, Y, and Z axis, and the internal temperature sensor measurements.
```c
err_t piezoaccel225g_read_adc_data ( piezoaccel225g_t *ctx, piezoaccel225g_adc_data_t *data_out );
```

- `piezoaccel225g_fast_cmd_write` This function writes the selected fast command by using SPI serial interface.
```c
err_t piezoaccel225g_fast_cmd_write ( piezoaccel225g_t *ctx, uint8_t fast_cmd );
```

- `piezoaccel225g_reg_read_multi` This function reads a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t piezoaccel225g_reg_read_multi ( piezoaccel225g_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration for ADC measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    piezoaccel225g_cfg_t piezoaccel225g_cfg;  /**< Click config object. */

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
    piezoaccel225g_cfg_setup( &piezoaccel225g_cfg );
    PIEZOACCEL225G_MAP_MIKROBUS( piezoaccel225g_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == piezoaccel225g_init( &piezoaccel225g, &piezoaccel225g_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIEZOACCEL225G_ERROR == piezoaccel225g_default_cfg ( &piezoaccel225g ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ADC values of X, Y, and Z axis, and the internal temperature sensor measurements
and displays them on the USB UART (SerialPlot) every 5ms approximately.

```c
void application_task ( void )
{
    piezoaccel225g_adc_data_t adc_data;
    if ( PIEZOACCEL225G_OK == piezoaccel225g_read_adc_data ( &piezoaccel225g, &adc_data ) )
    {
        log_printf ( &logger, "%lu;%lu;%lu;%lu;\r\n", adc_data.raw_x, adc_data.raw_y, 
                                                      adc_data.raw_z, adc_data.raw_temp );
    }
}
```

### Note

> We recommend using the SerialPlot tool for data visualization. The temperature measurements
should be visualized independently. The data format for plotter is as follows: X;Y;Z;TEMP;

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

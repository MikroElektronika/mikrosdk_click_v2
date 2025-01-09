
---
# Temp ISO Click

> [Temp ISO Click](https://www.mikroe.com/?pid_product=MIKROE-6417) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6417&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Temp ISO Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempISO

### Example Key Functions

- `tempiso_cfg_setup` Config Object Initialization function.
```c
void tempiso_cfg_setup ( tempiso_cfg_t *cfg );
```

- `tempiso_init` Initialization function.
```c
err_t tempiso_init ( tempiso_t *ctx, tempiso_cfg_t *cfg );
```

- `tempiso_read_temperature` This function reads the voltage level from AN pin and converts it to temperature in degrees Celsius.
```c
err_t tempiso_read_temperature ( tempiso_t *ctx, float *data_out );
```

- `tempiso_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level.
```c
err_t tempiso_read_voltage_avg ( tempiso_t *ctx, uint16_t num_conv, float *voltage_avg );
```

- `tempiso_set_vref` This function sets the voltage reference for Temp ISO Click driver.
```c
err_t tempiso_set_vref ( tempiso_t *ctx, float vref );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempiso_cfg_t tempiso_cfg;  /**< Click config object. */

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
    tempiso_cfg_setup( &tempiso_cfg );
    TEMPISO_MAP_MIKROBUS( tempiso_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == tempiso_init( &tempiso, &tempiso_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature = 0;
    if ( TEMPISO_OK == tempiso_read_temperature ( &tempiso, &temperature ) ) 
    {
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", temperature );
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

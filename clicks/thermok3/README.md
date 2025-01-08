
---
# Thermo K 3 Click

> [Thermo K 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5605) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5605&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Thermo K 3 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ThermoK3

### Example Key Functions

- `thermok3_cfg_setup` Config Object Initialization function.
```c
void thermok3_cfg_setup ( thermok3_cfg_t *cfg );
```

- `thermok3_init` Initialization function.
```c
err_t thermok3_init ( thermok3_t *ctx, thermok3_cfg_t *cfg );
```

- `thermok3_read_data` This function reads a raw data output by using the SPI serial interface.
```c
err_t thermok3_read_data ( thermok3_t *ctx, uint16_t *data_out );
```

- `thermok3_read_temperature` This function reads a raw data output and converts it to temperature in Celsius.
```c
err_t thermok3_read_temperature ( thermok3_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermok3_cfg_t thermok3_cfg;  /**< Click config object. */

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
    thermok3_cfg_setup( &thermok3_cfg );
    THERMOK3_MAP_MIKROBUS( thermok3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermok3_init( &thermok3, &thermok3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART approximately once per second.
If there's no thermocouple type-K probe inserted an appropriate message will be displayed instead.

```c
void application_task ( void )
{
    float temperature = 0;
    err_t error_flag = thermok3_read_temperature ( &thermok3, &temperature );
    if ( THERMOK3_OK == error_flag )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    else if ( THERMOK3_OPEN_THERMOCOUPLE == error_flag )
    {
        log_printf( &logger, " NO thermocouple input\r\n\n" );
    }
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


---
# TempHum 28 Click

> [TempHum 28 Click](https://www.mikroe.com/?pid_product=MIKROE-6904) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6904&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the TempHum 28 Click board for
ambient temperature and relative humidity measurement. The application
reads temperature and humidity data via the SPI interface and displays
the measured values on the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum28

### Example Key Functions

- `temphum28_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void temphum28_cfg_setup ( temphum28_cfg_t *cfg );
```

- `temphum28_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t temphum28_init ( temphum28_t *ctx, temphum28_cfg_t *cfg );
```

- `temphum28_heater_enable` This function enables the internal heater by setting the heater enable pin to a high logic level.
```c
void temphum28_heater_enable ( temphum28_t *ctx );
```

- `temphum28_read_humidity` This function reads the averaged humidity sensor voltage and converts it to relative humidity percentage using the reference voltage.
```c
err_t temphum28_read_humidity ( temphum28_t *ctx, float *hum );
```

- `temphum28_read_temperature` This function reads the averaged temperature sensor voltage and converts it to temperature value using the reference voltage.
```c
err_t temphum28_read_temperature ( temphum28_t *ctx, float *temp );
```

### Application Init

> Initializes the logger and TempHum 28 Click driver, disables the internal heater, and enables the device for normal operation.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum28_cfg_t temphum28_cfg;  /**< Click config object. */

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
    temphum28_cfg_setup( &temphum28_cfg );
    TEMPHUM28_MAP_MIKROBUS( temphum28_cfg, MIKROBUS_POSITION_TEMPHUM28 );
    if ( SPI_MASTER_ERROR == temphum28_init( &temphum28, &temphum28_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    temphum28_heater_disable ( &temphum28 );
    temphum28_device_enable ( &temphum28 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads temperature and humidity values from the sensor and logs the results to the serial terminal.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    if ( TEMPHUM28_OK == temphum28_read_temperature ( &temphum28, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
    }

    if ( TEMPHUM28_OK == temphum28_read_humidity ( &temphum28, &humidity ) )
    {
        log_printf ( &logger, " Humidity: %.1f %%RH\r\n\n", humidity );
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

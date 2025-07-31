
---
# TempHum 27 Click

> [TempHum 27 Click](https://www.mikroe.com/?pid_product=MIKROE-6689) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6689&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the TempHum 27 Click board by reading ambient temperature
and relative humidity values using periodic measurements. After initializing the device and 
starting the periodic mode at 1 Hz, the application waits for the ALERT pin to indicate data 
readiness and then logs the measurements to the USB UART terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum27

### Example Key Functions

- `temphum27_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void temphum27_cfg_setup ( temphum27_cfg_t *cfg );
```

- `temphum27_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t temphum27_init ( temphum27_t *ctx, temphum27_cfg_t *cfg );
```

- `temphum27_get_alert_pin` This function reads the logic level of the ALR (alert) pin.
```c
uint8_t temphum27_get_alert_pin ( temphum27_t *ctx );
```

- `temphum27_start_periodic_meas` This function configures and starts periodic measurement mode at the specified frequency.
```c
err_t temphum27_start_periodic_meas ( temphum27_t *ctx, uint8_t freq );
```

- `temphum27_read_data_periodic` This function reads temperature and/or humidity data in periodic measurement mode.
```c
err_t temphum27_read_data_periodic ( temphum27_t *ctx, float *temp, float *hum );
```

- `temphum27_read_sensor_id` This function reads the unique 32-bit sensor ID.
```c
err_t temphum27_read_sensor_id ( temphum27_t *ctx, uint32_t *sensor_id );
```

### Application Init

> Initializes the logger and the Click driver, resets the device, reads and logs the sensor ID, and starts periodic measurements with a 1-second output rate.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum27_cfg_t temphum27_cfg;  /**< Click config object. */

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
    log_cfg.is_interrupt = false;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    temphum27_cfg_setup( &temphum27_cfg );
    TEMPHUM27_MAP_MIKROBUS( temphum27_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum27_init( &temphum27, &temphum27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint32_t sensor_id = 0;
    if ( TEMPHUM27_ERROR == temphum27_read_sensor_id ( &temphum27, &sensor_id ) )
    {
        log_error( &logger, " Sensor ID read." );
        for ( ; ; );
    }
    log_printf ( &logger, " Sensor ID: 0x%.8LX\r\n", sensor_id );

    if ( TEMPHUM27_OK == temphum27_start_periodic_meas ( &temphum27, TEMPHUM27_PERIODIC_FREQ_1S ) )
    {
        log_printf ( &logger, " Periodic measurement started with 1Hz output\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the ALERT pin to go low indicating new measurement data is available, then reads and logs the temperature and humidity values.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    // Wait for a periodic data ready (alert pin falling edge)
    while ( !temphum27_get_alert_pin ( &temphum27 ) );
    while ( temphum27_get_alert_pin ( &temphum27 ) );

    if ( TEMPHUM27_OK == temphum27_read_data_periodic ( &temphum27, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
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

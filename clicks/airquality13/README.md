
---
# Air Quality 13 Click

> [Air Quality 13 Click](https://www.mikroe.com/?pid_product=MIKROE-7008) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7008&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : May 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Air Quality 13 Click board by reading
PM1.0, PM2.5 and PM10 mass concentration measurements from the Bosch BMV080
ultra-miniature particulate matter sensor and displaying the results on the
USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality13

### Example Key Functions

- `airquality13_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void airquality13_cfg_setup ( airquality13_cfg_t *cfg );
```

- `airquality13_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t airquality13_init ( airquality13_t *ctx, airquality13_cfg_t *cfg );
```

- `airquality13_default_cfg` This function executes a default configuration of Air Quality 13 Click board.
```c
err_t airquality13_default_cfg ( airquality13_t *ctx );
```

- `airquality13_start_measurement` This function starts continuous particulate matter measurement via bmv080_start_continuous_measurement.
```c
err_t airquality13_start_measurement ( airquality13_t *ctx );
```

- `airquality13_serve_interrupt` This function processes pending data from the BMV080 FIFO by calling bmv080_serve_interrupt.
```c
err_t airquality13_serve_interrupt ( airquality13_t *ctx, airquality13_data_t *meas_data );
```

- `airquality13_set_meas_alg` This function sets the PM concentration calculation algorithm via bmv080_set_parameter.
```c
err_t airquality13_set_meas_alg ( airquality13_t *ctx, airquality13_meas_alg_t algorithm );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality13_cfg_t airquality13_cfg;  /**< Click config object. */

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
    airquality13_cfg_setup( &airquality13_cfg );
    AIRQUALITY13_MAP_MIKROBUS( airquality13_cfg, MIKROBUS_POSITION_AIRQUALITY13 );
    err_t init_flag = airquality13_init( &airquality13, &airquality13_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    /* A char array with a size of 13 elements must be allocated for the sensor ID. */
    char sensor_id[ AIRQUALITY13_SENSOR_ID_LEN ] = { 0 };
    
    if ( AIRQUALITY13_OK == airquality13_get_sensor_id( &airquality13, sensor_id ) )
    {
        log_printf( &logger, " Sensor ID: %s\r\n", sensor_id );
    }
    
    if ( AIRQUALITY13_ERROR == airquality13_default_cfg ( &airquality13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Waiting for first measurement (~2s)...\r\n" );
    log_printf( &logger, " The first 100 samples should be treated as warm-up data\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Calls airquality13_serve_interrupt every 100 ms to process the sensor FIFO.
When a new measurement is ready (approximately once per second), logs the
PM1.0, PM2.5 and PM10 mass concentrations to the USB UART.
If the optical path is obstructed, a warning is printed instead.

```c
void application_task ( void )
{
    airquality13_data_t meas_data = { 0 };
    
    /* A new measurement is available approximately every 1.03 seconds in continuous mode. 
     * airquality13_serve_interrupt must be called at least once per second to prevent FIFO overflow,
     * it is recommended to call it every 100 ms. */
    if ( AIRQUALITY13_OK == airquality13_serve_interrupt( &airquality13, &meas_data ) )
    {
        if ( meas_data.data_ready )
        {
            if ( !meas_data.is_obstructed )
            {
                log_printf( &logger, " Runtime in sec : %.2f s\r\n", meas_data.runtime_in_sec );
                log_printf( &logger, " PM1.0 : %.2f ug/m3\r\n", meas_data.pm1_mass_concentration );
                log_printf( &logger, " PM2.5 : %.2f ug/m3\r\n", meas_data.pm2_5_mass_concentration );
                log_printf( &logger, " PM10  : %.2f ug/m3\r\n", meas_data.pm10_mass_concentration );
                log_printf( &logger, " ----------------------\r\n\r\n" );
            }
            else
            {
                log_printf( &logger, " WARNING: Sensor obstructed!\r\n" );
            }
        }
    }

    Delay_ms( 100 );
}
```

### Note

> This driver requires the Bosch BMV080 SDK which is not included in the repository
due to licensing restrictions. Before building, refer to the README file located
in the lib_airquality13/bosch/ directory for instructions on how to obtain the SDK
and copy the required files into the correct locations.

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

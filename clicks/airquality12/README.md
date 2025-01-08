
---
# Air Quality 12 Click

> [Air Quality 12 Click](https://www.mikroe.com/?pid_product=MIKROE-6418) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6418&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : I2C/UART type

# Software Support

## Example Description

> This example demonstrates the use of Air Quality 12 Click board by reading the IAQ 2nd Gen measurements and displays the results on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality12

### Example Key Functions

- `airquality12_cfg_setup` Config Object Initialization function.
```c
void airquality12_cfg_setup ( airquality12_cfg_t *cfg );
```

- `airquality12_init` Initialization function.
```c
err_t airquality12_init ( airquality12_t *ctx, airquality12_cfg_t *cfg );
```

- `airquality12_default_cfg` Click Default Configuration function.
```c
err_t airquality12_default_cfg ( airquality12_t *ctx );
```

- `airquality12_get_sensor_info` This function reads the device product ID, firmware version, and tracking number.
```c
err_t airquality12_get_sensor_info ( airquality12_t *ctx, airquality12_info_t *info );
```

- `airquality12_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t airquality12_get_int_pin ( airquality12_t *ctx );
```

- `airquality12_get_measurement` This function reads the sensor measurement results.
```c
err_t airquality12_get_measurement ( airquality12_t *ctx, airquality12_results_t *results );
```

### Application Init

> Initializes the driver and configures the Click board to the default configuration.
Then it reads the sensor product ID, firmware version, and the 48-bit tracking number.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality12_cfg_t airquality12_cfg;  /**< Click config object. */

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
    airquality12_cfg_setup( &airquality12_cfg );
    AIRQUALITY12_MAP_MIKROBUS( airquality12_cfg, MIKROBUS_1 );
    if ( AIRQUALITY12_OK != airquality12_init( &airquality12, &airquality12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRQUALITY12_ERROR == airquality12_default_cfg ( &airquality12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    airquality12_info_t info;
    if ( AIRQUALITY12_OK == airquality12_get_sensor_info ( &airquality12, &info ) )
    {
        log_printf( &logger, " ---- Sensor info ----\r\n" );
        log_printf( &logger, " Product ID: 0x%.4X\r\n", info.product_id );
        log_printf( &logger, " FW version: %u.%u.%u\r\n", ( uint16_t ) info.fw_ver_major, 
                                                          ( uint16_t ) info.fw_ver_minor, 
                                                          ( uint16_t ) info.fw_ver_patch );
        log_printf( &logger, " Tracking number: 0x%.2X%.2X%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) info.tracking_num[ 5 ], ( uint16_t ) info.tracking_num[ 4 ], 
                    ( uint16_t ) info.tracking_num[ 3 ], ( uint16_t ) info.tracking_num[ 2 ], 
                    ( uint16_t ) info.tracking_num[ 1 ], ( uint16_t ) info.tracking_num[ 0 ] );
        log_printf( &logger, " ---------------------\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks the data ready interrupt pin and then reads the IAQ 2nd Gen measurements
and displays the results on the USB UART. The GP1 LED turns ON during the data reading.
The data sample rate is set to 3 seconds for the IAQ 2nd Gen operating mode, and the first
100 samples upon startup should be ignored since the sensor is in the warm-up phase.

```c
void application_task ( void )
{
    airquality12_results_t results = { 0 };

    if ( airquality12_get_int_pin ( &airquality12 ) )
    {
        airquality12_set_gp1_pin ( &airquality12, 1 );
        if ( AIRQUALITY12_OK == airquality12_get_measurement ( &airquality12, &results ) )
        {
            log_printf ( &logger, " Sample number: %u\r\n", ( uint16_t ) results.sample_num );
            log_printf ( &logger, " IAQ: %.1f\r\n", results.iaq );
            log_printf ( &logger, " TVOC: %.2f mg/m^3\r\n", results.tvoc );
            log_printf ( &logger, " ETOH: %.2f ppm\r\n", results.etoh );
            log_printf ( &logger, " ECO2: %u ppm\r\n", results.eco2 );
            log_printf ( &logger, " rel_IAQ: %u\r\n\n", results.rel_iaq );
        }
        airquality12_set_gp1_pin ( &airquality12, 0 );
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


---
# Air Quality 9 Click

> [Air quality 9 Click](https://www.mikroe.com/?pid_product=MIKROE-5060) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5060&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Air Quality 9 Click board by reading and displaying outputs such as eCO2, TVOC and AQI in compliance with worldwide IAQ standards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality9

### Example Key Functions

- `airquality9_cfg_setup` Config Object Initialization function.
```c
void airquality9_cfg_setup ( airquality9_cfg_t *cfg );
```

- `airquality9_init` Initialization function.
```c
err_t airquality9_init ( airquality9_t *ctx, airquality9_cfg_t *cfg );
```

- `airquality9_default_cfg` Click Default Configuration function.
```c
err_t airquality9_default_cfg ( airquality9_t *ctx );
```

- `airquality9_read_aqi_uba` This function reads the Air Quality Index per UBA (AQI-UBA).
```c
err_t airquality9_read_aqi_uba ( airquality9_t *ctx, uint8_t *aqi_uba );
```

- `airquality9_read_tvoc` This function reads the calculated Total Volatile Organic Compounds (TVOC) concentration per ppb.
```c
err_t airquality9_read_tvoc ( airquality9_t *ctx, uint16_t *tvoc );
```

- `airquality9_read_eco2` This function reads the calculated Equivalent CO2 (eCO2) concentration per ppm.
```c
err_t airquality9_read_eco2 ( airquality9_t *ctx, uint16_t *eco2 );
```

### Application Init

> Initializes the driver and logger and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality9_cfg_t airquality9_cfg;  /**< Click config object. */

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
    airquality9_cfg_setup( &airquality9_cfg );
    AIRQUALITY9_MAP_MIKROBUS( airquality9_cfg, MIKROBUS_1 );
    err_t init_flag  = airquality9_init( &airquality9, &airquality9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRQUALITY9_ERROR == airquality9_default_cfg ( &airquality9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the new data interrupt which triggers once per second, 
and then reads the validity status, TVOC, eCO2, and AQI-UBA values. 
All values are being displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    if ( airquality9_get_int_pin ( &airquality9 ) )
    {
        uint8_t status, aqi_uba;
        uint16_t tvoc, eco2;
        if ( AIRQUALITY9_OK == airquality9_read_status ( &airquality9, &status ) )
        {
            airquality9_display_status_validity ( status );
        }
        if ( AIRQUALITY9_OK == airquality9_read_tvoc ( &airquality9, &tvoc ) )
        {
            log_printf ( &logger, " TVOC: %u ppb\r\n", tvoc );
        }
        if ( AIRQUALITY9_OK == airquality9_read_eco2 ( &airquality9, &eco2 ) )
        {
            log_printf ( &logger, " ECO2: %u ppm\r\n", eco2 );
        }
        if ( AIRQUALITY9_OK == airquality9_read_aqi_uba ( &airquality9, &aqi_uba ) )
        {
            airquality9_display_aqi_uba ( aqi_uba );
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

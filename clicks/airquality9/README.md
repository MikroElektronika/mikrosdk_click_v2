\mainpage Main Page

---
# Air Quality 9 click

> Air quality 9 Click is a compact add-on board containing a best-in-class air-quality sensing solution. This board features the ENS160, a digital multi-gas sensor solution based on metal oxide (MOX) technology with four MOx sensor elements from ScioSense. Each sensor element has independent hotplate control to detect a wide range of gases. The ENS160 series features TrueVOC™ air quality detection and supports intelligent algorithms, which calculate CO2 equivalents, TVOC, air quality index (AQI), and perform humidity and temperature compensation. This Click board™ is interface-configurable and characterized by outstanding long-term stability and lifetime.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airquality9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/air-quality-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Air Quality 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Air Quality 9 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of Air Quality 9 click board by reading and displaying outputs such as eCO2, TVOC and AQI in compliance with worldwide IAQ standards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the click default configuration.

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

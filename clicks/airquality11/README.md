\mainpage Main Page

---
# Air Quality 11 click

> Air Quality 11 Click is a compact add-on board for monitoring and analyzing indoor air quality. This board features the ENS161, a multi-gas sensor from ScioSense based on metal oxide (MOX) technology, to detect a range of volatile organic compounds with high sensitivity. The board supports I2C and SPI communication protocols, allowing flexible integration with various MCU platforms. It can calculate equivalent CO2 and TVOC levels and provide standardized air quality indices directly on-chip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airquality11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/air-quality-11-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Air Quality 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Air Quality 11 Click driver.

#### Standard key functions :

- `airquality11_cfg_setup` Config Object Initialization function.
```c
void airquality11_cfg_setup ( airquality11_cfg_t *cfg );
```

- `airquality11_init` Initialization function.
```c
err_t airquality11_init ( airquality11_t *ctx, airquality11_cfg_t *cfg );
```

- `airquality11_default_cfg` Click Default Configuration function.
```c
err_t airquality11_default_cfg ( airquality11_t *ctx );
```

#### Example key functions :

- `airquality11_get_aqi_uba` This function reads the calculated Air Quality Index according to the UBA.
```c
err_t airquality11_get_aqi_uba ( airquality11_t *ctx, uint8_t *aqi_uba );
```

- `airquality11_get_tvoc` This function reads the calculated equivalent TVOC concentration in ppb.
```c
err_t airquality11_get_tvoc ( airquality11_t *ctx, uint16_t *tvoc_ppb );
```

- `airquality11_get_aqi_s` This function reads the calculated relative Air Quality Index proprietary to ScioSense.
```c
err_t airquality11_get_aqi_s ( airquality11_t *ctx, uint16_t *aqi_s );
```

## Example Description

> This example demonstrates the use of the Air Quality 11 Click board 
> by reading and displaying the calculated Air Quality Index according to the UBA and ScioSense, 
> and equivalent TVOC and CO2 concentration.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C and SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality11_cfg_t airquality11_cfg;  /**< Click config object. */

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
    airquality11_cfg_setup( &airquality11_cfg );
    AIRQUALITY11_MAP_MIKROBUS( airquality11_cfg, MIKROBUS_1 );
    err_t init_flag = airquality11_init( &airquality11, &airquality11_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRQUALITY11_ERROR == airquality11_default_cfg ( &airquality11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application displays the Air Quality Index of the UBA information,
> concentration of the TVOC and CO2 and Air Quality Index according to ScioSense.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t aqi_uba = 0;
    uint16_t aq_data = 0;

    if ( AIRQUALITY11_OK == airquality11_get_aqi_uba( &airquality11, &aqi_uba ) )
    {
        airquality11_display_aqi_uba( aqi_uba );
        Delay_ms ( 100 );
    }

    if ( AIRQUALITY11_OK == airquality11_get_tvoc( &airquality11, &aq_data ) )
    {
        log_printf( &logger, " TVOC: %u [ppb]\r\n", aq_data );
        Delay_ms ( 100 );
    }

    if ( AIRQUALITY11_OK == airquality11_get_co2( &airquality11, &aq_data ) )
    {
        log_printf( &logger, " ECO2: %u [ppm]\r\n", aq_data );
        Delay_ms ( 100 );
    }

    if ( AIRQUALITY11_OK == airquality11_get_aqi_s( &airquality11, &aq_data ) )
    {
        log_printf( &logger, " AQIS: %u [idx]\r\n", aq_data );
        Delay_ms ( 100 );
    }
	
    log_printf( &logger, "---------------------------\r\n " );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

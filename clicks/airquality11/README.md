
---
# Air Quality 11 Click

> [Air Quality 11 Click](https://www.mikroe.com/?pid_product=MIKROE-6063) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6063&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Air Quality 11 Click board 
> by reading and displaying the calculated Air Quality Index according to the UBA and ScioSense, 
> and equivalent TVOC and CO2 concentration.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality11

### Example Key Functions

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

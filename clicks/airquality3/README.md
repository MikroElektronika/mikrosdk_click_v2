
---
# Air quality 3 Click

> [Air quality 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2953) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2953&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application shows air quality measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality3

### Example Key Functions

- `airquality3_cfg_setup` Config Object Initialization function. 
```c
void airquality3_cfg_setup ( airquality3_cfg_t *cfg );
``` 
 
- `airquality3_init` Initialization function. 
```c
err_t airquality3_init ( airquality3_t *ctx, airquality3_cfg_t *cfg );
```

- `airquality3_default_cfg` Click Default Configuration function. 
```c
void airquality3_default_cfg ( airquality3_t *ctx );
```

- `airquality3_get_co2_and_tvoc` Get CO2 and TVOC data. 
```c
uint8_t airquality3_get_co2_and_tvoc( airquality3_t *ctx, airquality3_air_data_t *air_data );
```
 
- `airquality3_set_environment_data` Temperature and humidity data settings. 
```c
void airquality3_set_environment_data( airquality3_t *ctx, uint32_t env_data );
``` 

- `airquality3_set_measurement_mode`  Function for settings sensor drive mode and interrupts. 
```c
void airquality3_set_measurement_mode ( airquality3_t *ctx, uint8_t mode );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.
> Call the procedure the wakeup function of the chip.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality3_cfg_setup( &cfg );
    AIRQUALITY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality3_init( &airquality3, &cfg );

    // Wake-up Click procedure

    airquality3_set_power( &airquality3, AIRQUALITY3_POWER_STATE_ON );
    airquality3_hardware_reset( &airquality3 );
    airquality3_app_function( &airquality3, AIRQUALITY3_APP_START );

    airquality3_default_cfg( &airquality3 );

    Delay_ms ( 500 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads CO2 and TVOC value in the air and logs this data on the USBUART.

```c
void application_task ( void )
{
    airquality3_air_data_t air_data;

    //  Task implementation.

    airquality3_get_co2_and_tvoc ( &airquality3, &air_data );
    log_printf( &logger, "\r\n---- AirQuality data ----\r\n" );
    log_printf( &logger, ">> CO2 data is %d ppm.\r\n", air_data.co2 );
    log_printf( &logger, ">> TVOC data is %d ppb.\r\n", air_data.tvoc );

    Delay_1sec();
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

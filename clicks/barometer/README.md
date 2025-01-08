
---
# Barometer Click

> [Barometer Click](https://www.mikroe.com/?pid_product=MIKROE-1817) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1817&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application measures temperature and pressure data. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer

### Example Key Functions

- `barometer_cfg_setup` Config Object Initialization function. 
```c
void barometer_cfg_setup ( barometer_cfg_t *cfg );
``` 
 
- `barometer_init` Initialization function. 
```c
err_t barometer_init ( barometer_t *ctx, barometer_cfg_t *cfg );
```

- `barometer_default_cfg` Click Default Configuration function. 
```c
void barometer_default_cfg ( barometer_t *ctx );
```

- `barometer_get_temperature_c` Read temperature in degrees Celsius function. 
```c
float barometer_get_temperature_c( barometer_t *ctx );
```
 
- `barometer_get_pressure` Read pressure in milibars function. 
```c
float barometer_get_pressure ( barometer_t *ctx );
```

- `barometer_check_status` Check sensor status function. 
```c
uint8_t barometer_check_status( barometer_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C, set default configuration and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer_cfg_t cfg;

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

    barometer_cfg_setup( &cfg );
    BAROMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer_init( &barometer, &cfg );

    barometer_default_cfg( &barometer );

    // Check sensor id
    if ( barometer_check_id( &barometer ) != BAROMETER_DEVICE_ID )
    {
        log_printf( &logger, "   ERROR  \r\n " );
    }
    else
    {
        log_printf( &logger, "   Initialization  \r\n" );
    }
        
    log_printf( &logger, "-------------------------------- \r\n" );
    Delay_100ms( );
}
```

### Application Task

> This is a example which demonstrates the use of Barometer Click board 

```c
void application_task ( void )
{
    float temperature_c;
    float pressure;

    temperature_c = barometer_get_temperature_c( &barometer );
    Delay_100ms( );

    pressure = barometer_get_pressure( &barometer );
    Delay_100ms( );

    log_printf( &logger, " Temperature : %.2f\r\n", temperature_c );

    log_printf( &logger, " Pressure    : %.2f\r\n", pressure );
    log_printf( &logger, "-------------------------------- \r\n" );

    Delay_1sec( );
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

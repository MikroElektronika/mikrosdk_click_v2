
---
# UV 3 Click

> [UV 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2736) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2736&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> Converts solar UV light intensity to digital data and measure UV radiation under long time solar UV exposure. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Uv3

### Example Key Functions

- `uv3_cfg_setup` Config Object Initialization function. 
```c
void uv3_cfg_setup ( uv3_cfg_t *cfg );
``` 
 
- `uv3_init` Initialization function. 
```c
err_t uv3_init ( uv3_t *ctx, uv3_cfg_t *cfg );
```

- `uv3_default_cfg` Click Default Configuration function. 
```c
void uv3_default_cfg ( uv3_t *ctx );
```

- `uv3_enable_sensor` Function enable sensor by sets shutdown mode bits as LOW to the target 8-bit CMD slave address. 
```c
void uv3_enable_sensor ( uv3_t *ctx );
```
 
- `uv3_read_measurements` Function read UV data measurements from to the two target 8-bit slave address. 
```c
uint16_t uv3_read_measurements ( uv3_t *ctx );
```

- `uv3_risk_level` Function calculate UV risk level of VEML6070 sensor on UV 3 Click. 
```c
uint8_t uv3_risk_level ( uint16_t uv_data );
```

### Application Init

> Initialization driver enable's - I2C, enable sensor and start write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uv3_cfg_t cfg;

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

    uv3_cfg_setup( &cfg );
    UV3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv3_init( &uv3, &cfg );
    uv3_default_cfg ( &uv3 );
}

  
```

### Application Task

> This example measures the level of the UV light and logs every 2 seconds to the terminal.

```c
void application_task ( void )
{
    uv_data = uv3_read_measurements( &uv3 );

    risk_lvl = uv3_risk_level( uv_data );

    log_printf( &logger, " UV value  : %d\r\n ", uv_data );

    log_printf( &logger, " Radiation lvl : " );

    if ( risk_lvl == UV3_RAD_LOW )
    {
        log_printf( &logger, " Low\r\n " );
    }

    if ( risk_lvl == UV3_RAD_MODERATE )
    {
        log_printf( &logger, " Moderate\r\n " );
    }

    if ( risk_lvl == UV3_RAD_HIGH )
    {
        log_printf( &logger, " High\r\n " );
    }

    if ( risk_lvl == UV3_RAD_VERY_HIGH )
    {
        log_printf( &logger, " Very High\r\n " );
    }

    if ( risk_lvl == UV3_RAD_EXTREME )
    {
        log_printf( &logger, " Extreme\r\n " );
    }

    Delay_ms ( 1000 );
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

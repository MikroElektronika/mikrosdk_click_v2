
---
# ProxFusion 2 Click

> [ProxFusion 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3205) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3205&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demontrates the use of ProxFusion 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ProxFusion2

### Example Key Functions

- `proxfusion2_cfg_setup` Config Object Initialization function.
```c
void proxfusion2_cfg_setup ( proxfusion2_cfg_t *cfg ); 
```

- `proxfusion2_init` Initialization function.
```c
err_t proxfusion2_init ( proxfusion2_t *ctx, proxfusion2_cfg_t *cfg );
```

- `proxfusion2_default_cfg` Click Default Configuration function.
```c
err_t proxfusion2_default_cfg ( proxfusion2_t *ctx );
```

- `proxfusion2_detect_touch` Function for detect Touch
```c
uint8_t proxfusion2_detect_touch ( proxfusion2_t *ctx );
```

- `proxfusion2_detect_dark_light` Function for read ambient light
```c
uint8_t proxfusion2_detect_dark_light ( proxfusion2_t *ctx, uint8_t *als_range );
```

- `proxfusion2_detect_hall` Function for read Hall-effect 
```c
uint8_t proxfusion2_detect_hall ( proxfusion2_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proxfusion2_cfg_t proxfusion2_cfg;  /**< Click config object. */

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
    proxfusion2_cfg_setup( &proxfusion2_cfg );
    PROXFUSION2_MAP_MIKROBUS( proxfusion2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proxfusion2_init( &proxfusion2, &proxfusion2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXFUSION2_ERROR == proxfusion2_default_cfg ( &proxfusion2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> - Checks whether Touch is detected and measures the output detection.
> - Measures Ambient lighting - whether it's Light or Dark, ALS range and ALS output.
> - Checks the orientation of the magnet and measures the HALL output.

```c
void application_task ( void )
{
    uint8_t als_range = 0;
    uint8_t hall_detect = 0;
    uint16_t read_data = 0;
    if ( PROXFUSION2_TOUCH_DETECTED == proxfusion2_detect_touch( &proxfusion2 ) )
    {
        log_printf( &logger, " TOUCH: YES\r\n" );
    }
    else
    {
        log_printf( &logger, " TOUCH: NO\r\n" );
    }
    read_data = proxfusion2_read_data( &proxfusion2 , PROXFUSION2_HYSTERESIS_UI_OUTPUT );
    log_printf( &logger, " LEVEL: %u\r\n\n", read_data );
 
    if ( PROXFUSION2_AMBIENT_DARK == proxfusion2_detect_dark_light( &proxfusion2, &als_range ) )
    {
        log_printf( &logger, " AMBIENT: DARK\r\n" );
    }
    else
    {
        log_printf( &logger, " AMBIENT: LIGHT\r\n" );
    }
    log_printf( &logger, " RANGE: %u\r\n", ( uint16_t ) als_range );
 
    read_data = proxfusion2_read_data( &proxfusion2, PROXFUSION2_ALS_UI_OUTPUT );

    log_printf( &logger, " LEVEL: %u\r\n\n", read_data );
 
    hall_detect = proxfusion2_detect_hall( &proxfusion2 );
    if ( PROXFUSION2_HALL_NORTH == hall_detect )
    {
        log_printf( &logger, " HALL: NORTH\r\n" );
    }
    else if ( PROXFUSION2_HALL_SOUTH == hall_detect )
    {
        log_printf( &logger, " HALL: SOUTH\r\n" );
    }
    else
    {
        log_printf( &logger, " HALL: UNKNOWN\r\n" );
    }
    read_data = proxfusion2_read_data( &proxfusion2, PROXFUSION2_HALL_EFFECT_UI_OUTPUT );
    log_printf( &logger, " LEVEL: %u\r\n", read_data );
    
    log_printf( &logger, " --------------\r\n" );
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

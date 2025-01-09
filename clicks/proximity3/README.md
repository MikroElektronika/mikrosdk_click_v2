
---
# Proximity 3 Click

> [Proximity 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2801) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2801&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads the raw ALS and proximity data from Proximity 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity3

### Example Key Functions

- `proximity3_cfg_setup` Config Object Initialization function.
```c
void proximity3_cfg_setup ( proximity3_cfg_t *cfg ); 
```

- `proximity3_init` Initialization function.
```c
err_t proximity3_init ( proximity3_t *ctx, proximity3_cfg_t *cfg );
```

- `proximity3_default_cfg` Click Default Configuration function.
```c
err_t proximity3_default_cfg ( proximity3_t *ctx );
```

- `proximity3_write_16` This function writes data to the desired register.
```c
err_t proximity3_write_16 ( proximity3_t *ctx, uint8_t reg_address, uint16_t data_in );
```

- `proximity3_read_als` This function gets the data returned by the ambient light sensor.
```c
uint16_t proximity3_read_als ( proximity3_t *ctx );
```

- `proximity3_read_proximity` This function returns the proximity.
```c
uint16_t proximity3_read_proximity ( proximity3_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity3_cfg_t proximity3_cfg;  /**< Click config object. */

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
    proximity3_cfg_setup( &proximity3_cfg );
    PROXIMITY3_MAP_MIKROBUS( proximity3_cfg, MIKROBUS_1 );
    if ( PROXIMITY3_ERROR == proximity3_init( &proximity3, &proximity3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY3_ERROR == proximity3_default_cfg ( &proximity3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the raw ALS and proximity data and displays the results on the USB UART every 500ms.

```c
void application_task ( void )
{
    uint16_t proximity = 0;
    uint16_t als = 0;
    
    proximity = proximity3_read_proximity( &proximity3 );
    log_printf( &logger, " Proximity: %u\r\n", proximity );

    als = proximity3_read_als( &proximity3 );
    log_printf( &logger, " ALS: %u\r\n", als );

    log_printf( &logger, "-----------------\r\n" );
    Delay_ms ( 500 );
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

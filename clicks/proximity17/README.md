
---
# Proximity 17 Click

> [Proximity 17 Click](https://www.mikroe.com/?pid_product=MIKROE-5084) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5084&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 17 Click board by reading and displaying the proximity data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity17

### Example Key Functions

- `proximity17_cfg_setup` Config Object Initialization function.
```c
void proximity17_cfg_setup ( proximity17_cfg_t *cfg );
```

- `proximity17_init` Initialization function.
```c
err_t proximity17_init ( proximity17_t *ctx, proximity17_cfg_t *cfg );
```

- `proximity17_default_cfg` Click Default Configuration function.
```c
err_t proximity17_default_cfg ( proximity17_t *ctx );
```

- `proximity17_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t proximity17_get_int_pin ( proximity17_t *ctx );
```

- `proximity17_read_proximity` This function reads the raw proximity data. The higher the value, the closer the detected object is.
```c
err_t proximity17_read_proximity ( proximity17_t *ctx, uint16_t *prox_data );
```

- `proximity17_soft_reset` This function executes the defice software reset command.
```c
err_t proximity17_soft_reset ( proximity17_t *ctx );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity17_cfg_t proximity17_cfg;  /**< Click config object. */

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
    proximity17_cfg_setup( &proximity17_cfg );
    PROXIMITY17_MAP_MIKROBUS( proximity17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity17_init( &proximity17, &proximity17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY17_ERROR == proximity17_default_cfg ( &proximity17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity data and displays it on the USB UART approximately once per second. The higher the proximity value, the closer the detected object is.

```c
void application_task ( void )
{
    uint16_t proximity;
    if ( PROXIMITY17_OK == proximity17_read_proximity ( &proximity17, &proximity ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n\n", proximity );
        Delay_ms ( 1000 );
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

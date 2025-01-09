
---
# Proximity 19 Click

> [Proximity 19 Click](https://www.mikroe.com/?pid_product=MIKROE-6062) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6062&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Proximity 19 Click board 
> by measuring and displaying the distance data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity19

### Example Key Functions

- `proximity19_cfg_setup` Config Object Initialization function.
```c
void proximity19_cfg_setup ( proximity19_cfg_t *cfg );
```

- `proximity19_init` Initialization function.
```c
err_t proximity19_init ( proximity19_t *ctx, proximity19_cfg_t *cfg );
```

- `proximity19_default_cfg` Click Default Configuration function.
```c
err_t proximity19_default_cfg ( proximity19_t *ctx );
```

- `proximity19_get_distance` This function reads the distance measured by the sensor in millimeters by using the I2C serial interface.
```c
err_t proximity19_get_distance ( proximity19_t *ctx, float *distance );
```

- `proximity19_set_ps_gain` This function adjusts the gain of the sensor's sensitivity to light reception.
```c
err_t proximity19_set_ps_gain ( proximity19_t *ctx, uint8_t ps_gain );
```

- `proximity19_set_period` This function sets the desired data measurement period value.
```c
err_t proximity19_set_period ( proximity19_t *ctx, uint8_t period );
```

### Application Init

> Initialization of I2C module and log UART.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity19_cfg_t proximity19_cfg;  /**< Click config object. */

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
    proximity19_cfg_setup( &proximity19_cfg );
    PROXIMITY19_MAP_MIKROBUS( proximity19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity19_init( &proximity19, &proximity19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY19_ERROR == proximity19_default_cfg ( &proximity19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo app measures the distance between the sensor and the object in millimeters 
> and displays the result approximately every 100 milliseconds.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float distance = 0;
    if ( PROXIMITY19_OK == proximity19_get_distance( &proximity19, &distance ) )
    {
        log_printf( &logger, " Distance: %.2f [mm] \r\n\n", distance );
    }
    Delay_ms ( 100 );
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

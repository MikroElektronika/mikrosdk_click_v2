
---
# Compass 8 Click

> [Compass 8 Click](https://www.mikroe.com/?pid_product=MIKROE-6099) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6099&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Compass 8 Click driver.
> The library initializes and defines the I2C drivers to 
> write and read data from registers, as well as the default 
> configuration for reading measurement data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass8

### Example Key Functions

- `compass8_cfg_setup` Config Object Initialization function.
```c
void compass8_cfg_setup ( compass8_cfg_t *cfg );
```

- `compass8_init` Initialization function.
```c
err_t compass8_init ( compass8_t *ctx, compass8_cfg_t *cfg );
```

- `compass8_default_cfg` Click Default Configuration function.
```c
err_t compass8_default_cfg ( compass8_t *ctx );
```

- `compass8_get_magnetic_data` This function reads the raw magnetic sensor measurement data and calculates magnetic flux density [microTesla] using the I2C serial interface.
```c
err_t compass8_get_magnetic_data ( compass8_t *ctx, compass8_axes_t *axis );
```

- `compass8_set_operation_mode` This function sets the desired sensor operation mode by using the I2C serial interface.
```c
err_t compass8_set_operation_mode ( compass8_t *ctx, uint8_t op_mode );
```

- `compass8_sw_reset` This function performs software reset by using the I2C serial interface.
```c
err_t compass8_sw_reset ( compass8_t *ctx );
```

### Application Init

> The initialization of the I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass8_cfg_t compass8_cfg;  /**< Click config object. */

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
    compass8_cfg_setup( &compass8_cfg );
    COMPASS8_MAP_MIKROBUS( compass8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == compass8_init( &compass8, &compass8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS8_ERROR == compass8_default_cfg ( &compass8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Compass 8 Click board.
> Measures and displays magnetic flux density in microtesla (uT) for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    compass8_axes_t axis; 
    if ( COMPASS8_OK == compass8_get_magnetic_data( &compass8, &axis ) ) 
    {
        log_printf( &logger, " X-axis: %.2f uT\r\n", axis.x );
        log_printf( &logger, " Y-axis: %.2f uT\r\n", axis.y );
        log_printf( &logger, " Z-axis: %.2f uT\r\n", axis.z );      
        log_printf( &logger,  "--------------------\r\n" );
        Delay_ms ( 100 );
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

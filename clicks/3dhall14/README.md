
---
# 3D Hall 14 Click

> [3D Hall 14 Click](https://www.mikroe.com/?pid_product=MIKROE-6242) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6242&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of 3D Hall 14 Click board by reading the magnetic field strength from 3 axes and the sensor internal temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall14

### Example Key Functions

- `c3dhall14_cfg_setup` Config Object Initialization function.
```c
void c3dhall14_cfg_setup ( c3dhall14_cfg_t *cfg );
```

- `c3dhall14_init` Initialization function.
```c
err_t c3dhall14_init ( c3dhall14_t *ctx, c3dhall14_cfg_t *cfg );
```

- `c3dhall14_default_cfg` Click Default Configuration function.
```c
err_t c3dhall14_default_cfg ( c3dhall14_t *ctx );
```

- `c3dhall14_get_magnetic_flux` This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux data in microTesla.
```c
err_t c3dhall14_get_magnetic_flux ( c3dhall14_t *ctx, float *x_axis, float *y_axis, float *z_axis );
```

- `c3dhall14_get_temperature` This function reads the raw temperature value and converts it to Celsius.
```c
err_t c3dhall14_get_temperature ( c3dhall14_t *ctx, float *temperature );
```

- `c3dhall14_set_range` This function sets the magnetic flux measurement range.
```c
err_t c3dhall14_set_range ( c3dhall14_t *ctx, uint8_t range );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall14_cfg_t c3dhall14_cfg;  /**< Click config object. */

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
    c3dhall14_cfg_setup( &c3dhall14_cfg );
    C3DHALL14_MAP_MIKROBUS( c3dhall14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall14_init( &c3dhall14, &c3dhall14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL14_ERROR == c3dhall14_default_cfg ( &c3dhall14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads data from the sensor and displays them on the USB UART every 200ms.

```c
void application_task ( void )
{
    float x_axis = 0;
    float y_axis = 0;
    float z_axis = 0;
    float temperature = 0;
    if ( C3DHALL14_OK == c3dhall14_get_magnetic_flux ( &c3dhall14, &x_axis, &y_axis, &z_axis ) )
    {
        log_printf( &logger, " X-axis: %.1f uT\r\n", x_axis );
        log_printf( &logger, " Y-axis: %.1f uT\r\n", y_axis );
        log_printf( &logger, " Z-axis: %.1f uT\r\n", z_axis );
    }
    if ( C3DHALL14_OK == c3dhall14_get_temperature ( &c3dhall14, &temperature ) )
    {
        log_printf( &logger, " Internal temperature: %.2f C\r\n\n", temperature );
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

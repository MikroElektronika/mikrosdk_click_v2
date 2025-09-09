
---
# 3D Hall 12 I2C Click

> [3D Hall 12 I2C Click](https://www.mikroe.com/?pid_product=MIKROE-6654) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6654&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of 3D Hall 12 I2C Click board by reading the magnetic
flux density from 3 axes, and the angle and magnitude between X and Y axes  
as well as the sensor internal temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall12I2C

### Example Key Functions

- `c3dhall12i2c_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c3dhall12i2c_cfg_setup ( c3dhall12i2c_cfg_t *cfg );
```

- `c3dhall12i2c_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c3dhall12i2c_init ( c3dhall12i2c_t *ctx, c3dhall12i2c_cfg_t *cfg );
```

- `c3dhall12i2c_default_cfg` This function executes a default configuration of 3D Hall 12 I2C Click board.
```c
err_t c3dhall12i2c_default_cfg ( c3dhall12i2c_t *ctx );
```

- `c3dhall12i2c_read_data` This function reads the temperature, X, Y, Z magnetic field, angle, and magnitude from the device.
```c
err_t c3dhall12i2c_read_data ( c3dhall12i2c_t *ctx, c3dhall12i2c_data_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall12i2c_cfg_t c3dhall12i2c_cfg;  /**< Click config object. */

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
    c3dhall12i2c_cfg_setup( &c3dhall12i2c_cfg );
    C3DHALL12I2C_MAP_MIKROBUS( c3dhall12i2c_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall12i2c_init( &c3dhall12i2c, &c3dhall12i2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL12I2C_ERROR == c3dhall12i2c_default_cfg ( &c3dhall12i2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads data from the sensor approximately every 100ms and displays the measurement values on the USB UART.

```c
void application_task ( void )
{
    c3dhall12i2c_data_t sensor_data;
    if ( C3DHALL12I2C_OK == c3dhall12i2c_read_data ( &c3dhall12i2c, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.2f mT\r\n", sensor_data.x );
        log_printf( &logger, " Y-axis: %.2f mT\r\n", sensor_data.y );
        log_printf( &logger, " Z-axis: %.2f mT\r\n", sensor_data.z );
        log_printf( &logger, " Angle: %.1f deg\r\n", sensor_data.angle );
        log_printf( &logger, " Magnitude: %.1f\r\n", sensor_data.magnitude );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", sensor_data.temperature );
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

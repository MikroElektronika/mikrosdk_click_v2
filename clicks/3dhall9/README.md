
---
# 3D Hall 9 Click

> [3D Hall 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4948) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4948&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of 3D Hall 9 Click board by reading the magnetic
flux density from 3 axes as well as the angles between axes and the sensor temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall9

### Example Key Functions

- `c3dhall9_cfg_setup` Config Object Initialization function.
```c
void c3dhall9_cfg_setup ( c3dhall9_cfg_t *cfg );
```

- `c3dhall9_init` Initialization function.
```c
err_t c3dhall9_init ( c3dhall9_t *ctx, c3dhall9_cfg_t *cfg );
```

- `c3dhall9_default_cfg` Click Default Configuration function.
```c
err_t c3dhall9_default_cfg ( c3dhall9_t *ctx );
```

- `c3dhall9_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t c3dhall9_write_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t data_in );
```

- `c3dhall9_read_register` This function reads a desired data from the selected register by using I2C serial interface.
```c
err_t c3dhall9_read_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t *data_out );
```

- `c3dhall9_read_data` This function reads new data which consists of X, Y, and Z axis values in Gauss, and temperature in Celsius. It also calculates the angles between all axes in Degrees based on the raw axes data read.
```c
err_t c3dhall9_read_data ( c3dhall9_t *ctx, c3dhall9_data_t *data_out );
```

### Application Init

> Initializes the driver and the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall9_cfg_t c3dhall9_cfg;  /**< Click config object. */

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
    c3dhall9_cfg_setup( &c3dhall9_cfg );
    C3DHALL9_MAP_MIKROBUS( c3dhall9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall9_init( &c3dhall9, &c3dhall9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL9_ERROR == c3dhall9_default_cfg ( &c3dhall9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the new data from the sensor approximately every 300ms and displays the measurement values on the USB UART.

```c
void application_task ( void )
{
    c3dhall9_data_t sensor_data;
    
    if ( C3DHALL9_OK == c3dhall9_read_data ( &c3dhall9, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.1f Gauss\r\n", sensor_data.x_axis );
        log_printf( &logger, " Y-axis: %.1f Gauss\r\n", sensor_data.y_axis );
        log_printf( &logger, " Z-axis: %.1f Gauss\r\n", sensor_data.z_axis );
        log_printf( &logger, " Angle XY: %.1f Degrees\r\n", sensor_data.angle_xy );
        log_printf( &logger, " Angle XZ: %.1f Degrees\r\n", sensor_data.angle_xz );
        log_printf( &logger, " Angle YZ: %.1f Degrees\r\n", sensor_data.angle_yz );
        log_printf( &logger, " Temperature: %.2f Celsius\r\n\n", sensor_data.temperature );
        Delay_ms ( 300 );
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

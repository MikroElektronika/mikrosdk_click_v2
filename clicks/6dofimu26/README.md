
---
# 6DOF IMU 26 Click

> [6DOF IMU 26 Click](https://www.mikroe.com/?pid_product=MIKROE-6572) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6572&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the 6DOF IMU 26 Click board, which provides 
3-axis accelerometer and 3-axis gyroscope measurements, as well as temperature data. 
The example initializes the device and continuously logs sensor readings.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU26

### Example Key Functions

- `c6dofimu26_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c6dofimu26_cfg_setup ( c6dofimu26_cfg_t *cfg );
```

- `c6dofimu26_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c6dofimu26_init ( c6dofimu26_t *ctx, c6dofimu26_cfg_t *cfg );
```

- `c6dofimu26_default_cfg` This function executes a default configuration of 6DOF IMU 26 Click board.
```c
err_t c6dofimu26_default_cfg ( c6dofimu26_t *ctx );
```

- `c6dofimu26_get_data` This function reads the accelerometer, gyroscope, and temperature data.
```c
err_t c6dofimu26_get_data ( c6dofimu26_t *ctx, c6dofimu26_data_t *data_out );
```

### Application Init

> Initializes the logger and configures the 6DOF IMU 26 Click board. Sets up SPI communication and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu26_cfg_t c6dofimu26_cfg;  /**< Click config object. */

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
    c6dofimu26_cfg_setup( &c6dofimu26_cfg );
    C6DOFIMU26_MAP_MIKROBUS( c6dofimu26_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c6dofimu26_init( &c6dofimu26, &c6dofimu26_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU26_ERROR == c6dofimu26_default_cfg ( &c6dofimu26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads and logs acceleration (g), gyroscope (dps), and temperature (degC) values from the sensor.

```c
void application_task ( void )
{
    c6dofimu26_data_t meas_data;
    if ( C6DOFIMU26_OK == c6dofimu26_get_data ( &c6dofimu26, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Gyro X: %.1f dps\r\n", meas_data.gyro.x );
        log_printf( &logger, " Gyro Y: %.1f dps\r\n", meas_data.gyro.y );
        log_printf( &logger, " Gyro Z: %.1f dps\r\n", meas_data.gyro.z );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", meas_data.temperature );
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

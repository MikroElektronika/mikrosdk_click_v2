
---
# 6DOF IMU 25 Click

> [6DOF IMU 25 Click](https://www.mikroe.com/?pid_product=MIKROE-6421) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6421&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of 6DOF IMU 25 Click board by reading and displaying 
the accelerometer and gyroscope data (X, Y, and Z axis) as well as a temperature measurement in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU25

### Example Key Functions

- `c6dofimu25_cfg_setup` Config Object Initialization function.
```c
void c6dofimu25_cfg_setup ( c6dofimu25_cfg_t *cfg );
```

- `c6dofimu25_init` Initialization function.
```c
err_t c6dofimu25_init ( c6dofimu25_t *ctx, c6dofimu25_cfg_t *cfg );
```

- `c6dofimu25_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu25_default_cfg ( c6dofimu25_t *ctx );
```

- `c6dofimu25_get_int1_pin` This function returns the interrupt 1 pin logic state.
```c
uint8_t c6dofimu25_get_int1_pin ( c6dofimu25_t *ctx );
```

- `c6dofimu25_get_data` This function reads the accelerometer, gyroscope, and temperature measurement data.
```c
err_t c6dofimu25_get_data ( c6dofimu25_t *ctx, c6dofimu25_data_t *data_out );
```

- `c6dofimu25_set_accel_fsr` This function sets the accel measurement full scale range.
```c
err_t c6dofimu25_set_accel_fsr ( c6dofimu25_t *ctx, uint8_t fsr );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu25_cfg_t c6dofimu25_cfg;  /**< Click config object. */

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
    c6dofimu25_cfg_setup( &c6dofimu25_cfg );
    C6DOFIMU25_MAP_MIKROBUS( c6dofimu25_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu25_init( &c6dofimu25, &c6dofimu25_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU25_ERROR == c6dofimu25_default_cfg ( &c6dofimu25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready indication and then reads the accelerometer, gyroscope, and temperature
measurements. The results are displayed on the USB UART at 7.5 Hz output data rate.

```c
void application_task ( void )
{
    c6dofimu25_data_t meas_data;
    if ( c6dofimu25_get_int1_pin ( &c6dofimu25 ) ) 
    {
        if ( C6DOFIMU25_OK == c6dofimu25_get_data ( &c6dofimu25, &meas_data ) )
        {
            log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
            log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
            log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
            log_printf( &logger, " Gyro X: %.1f dps\r\n", meas_data.gyro.x );
            log_printf( &logger, " Gyro Y: %.1f dps\r\n", meas_data.gyro.y );
            log_printf( &logger, " Gyro Z: %.1f dps\r\n", meas_data.gyro.z );
            log_printf( &logger, " Temperature: %.2f degC\r\n\n", meas_data.temperature );
        }
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


---
# 6DOF IMU 23 Click

> [6DOF IMU 23 Click](https://www.mikroe.com/?pid_product=MIKROE-5999) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5999&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for 6DOF IMU 23 Click driver.
> The library initializes and defines the SPI bus drivers 
> to write and read data. The library also includes a function for reading 
> accelerometer and gyroscope X-axis, Y-axis, and Z-axis data as well as the internal temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU23

### Example Key Functions

- `c6dofimu23_cfg_setup` Config Object Initialization function.
```c
void c6dofimu23_cfg_setup ( c6dofimu23_cfg_t *cfg );
```

- `c6dofimu23_init` Initialization function.
```c
err_t c6dofimu23_init ( c6dofimu23_t *ctx, c6dofimu23_cfg_t *cfg );
```

- `c6dofimu23_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu23_default_cfg ( c6dofimu23_t *ctx );
```

- `c6dofimu23_get_accel_data` This function reads the accelerometer sensor axes measurement data.
```c
err_t c6dofimu23_get_accel_data ( c6dofimu23_t *ctx, c6dofimu23_axis_t *acc_axis );
```

- `c6dofimu23_get_gyro_data` This function reads the gyroscope sensor axes measurement data.
```c
err_t c6dofimu23_get_gyro_data ( c6dofimu23_t *ctx, c6dofimu23_axis_t *gyro_axis );
```

- `c6dofimu23_get_temperature` This function reads the internal temperature measurement data.
```c
err_t c6dofimu23_get_temperature ( c6dofimu23_t *ctx, float *temperature );
```

### Application Init

> The initialization of SPI module, log UART and enable the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu23_cfg_t c6dofimu23_cfg;  /**< Click config object. */

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
    c6dofimu23_cfg_setup( &c6dofimu23_cfg );
    C6DOFIMU23_MAP_MIKROBUS( c6dofimu23_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c6dofimu23_init( &c6dofimu23, &c6dofimu23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU23_ERROR == c6dofimu23_default_cfg ( &c6dofimu23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the 6DOF IMU 23 Click board.
> Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis, and the internal temperature data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float temperature = 0;
    c6dofimu23_axis_t acc_axis, gyro_axis;
    if ( ( C6DOFIMU23_OK == c6dofimu23_get_accel_data( &c6dofimu23, &acc_axis ) ) &&
         ( C6DOFIMU23_OK == c6dofimu23_get_gyro_data( &c6dofimu23, &gyro_axis ) ) &&
         ( C6DOFIMU23_OK == c6dofimu23_get_temperature( &c6dofimu23, &temperature ) ) )
    {
        log_printf( &logger, " Accel X: %.2f g | Gyro X: %.2f dps\r\n", acc_axis.x, gyro_axis.x );
        log_printf( &logger, " Accel Y: %.2f g | Gyro Y: %.2f dps\r\n", acc_axis.y, gyro_axis.y );
        log_printf( &logger, " Accel Z: %.2f g | Gyro Z: %.2f dps\r\n", acc_axis.z, gyro_axis.z );
        log_printf( &logger, " Internal temperature: %.2f degC\r\n", temperature );
        log_printf( &logger, " ----------------------------------\r\n" );
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

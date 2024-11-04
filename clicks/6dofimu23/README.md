\mainpage Main Page

---
# 6DOF IMU 23 Click

> 6DOF IMU 23 Click is a compact add-on board for precise motion tracking and measurement. This board features the IIM-20670, a high-performance 6-axis MotionTracking device from TDK InvenSense that integrates a 3-axis gyroscope and a 3-axis accelerometer. The gyroscope offers a full-scale range of up to ±1966 dps with high accuracy, while the accelerometer provides a range of ±2g to ±65g. Key features also include a 10MHz SPI interface, shock tolerance up to 10,000 g, on-chip 16-bit ADCs, and low current consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu23_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/6dof-imu-23-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the 6DOF IMU 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 6DOF IMU 23 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This library contains API for 6DOF IMU 23 Click driver.
> The library initializes and defines the SPI bus drivers 
> to write and read data. The library also includes a function for reading 
> accelerometer and gyroscope X-axis, Y-axis, and Z-axis data as well as the internal temperature data.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

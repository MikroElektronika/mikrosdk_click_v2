\mainpage Main Page

---
# 6DOF IMU 16 Click

> 6DOF IMU 16 Click is a compact add-on board with a 6-axis inertial measurement device. This board features the ICM-42605, a premium performance 6-axis MotionTracking™ IMU from TDK InvenSense. It combines a 3-axis gyroscope and a 3-axis accelerometer, supporting the lowest gyroscope and accelerometer sensor noise in this IMU class. It also has the highest stability against temperature, shock, SMT/bend-induced offset, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/6dof-imu-16-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DOF IMU 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 6DOF IMU 16 Click driver.

#### Standard key functions :

- `c6dofimu16_cfg_setup` Config Object Initialization function.
```c
void c6dofimu16_cfg_setup ( c6dofimu16_cfg_t *cfg );
```

- `c6dofimu16_init` Initialization function.
```c
err_t c6dofimu16_init ( c6dofimu16_t *ctx, c6dofimu16_cfg_t *cfg );
```

- `c6dofimu16_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu16_default_cfg ( c6dofimu16_t *ctx );
```

#### Example key functions :

- `c6dofimu16_sw_reset` This function performs the device software reset.
```c
err_t c6dofimu16_sw_reset ( c6dofimu16_t *ctx );
```

- `c6dofimu16_get_gyro_data` This function reads the angular rate of X, Y, and Z axis in degrees per second (mdps).
```c
err_t c6dofimu16_get_gyro_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *gyro_data );
```

- `c6dofimu16_get_accel_data` This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (mg).
```c
err_t c6dofimu16_get_accel_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *accel_data );
```

## Example Description

> This example demonstrates the use of 6DOF IMU 16 Click board by reading and displaying 
 the accelerometer and gyroscope data (X, Y, and Z axis).

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver performs the Click default configuration, 
  and checks communication by reading device ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu16_cfg_t c6dofimu16_cfg;  /**< Click config object. */

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
    c6dofimu16_cfg_setup( &c6dofimu16_cfg );
    C6DOFIMU16_MAP_MIKROBUS( c6dofimu16_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu16_init( &c6dofimu16, &c6dofimu16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU16_ERROR == c6dofimu16_default_cfg ( &c6dofimu16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t dev_id = 0;
    c6dofimu16_reg_read( &c6dofimu16, C6DOFIMU16_REG_WHO_AM_I, &dev_id );
    if ( C6DOFIMU16_DEVICE_ID != dev_id )
    {
        log_error( &logger, " Communication error " );
        for ( ; ; );
    }
    log_printf( &logger, " Device ID: 0x%.2X \r\n", ( uint16_t ) dev_id );

    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reading the accelerometer and gyroscope measurements, results are displayed on the USB UART every second.

```c
void application_task ( void )
{
    c6dofimu16_axis_t accel_data;
    c6dofimu16_axis_t gyro_data;

    c6dofimu16_get_accel_data( &c6dofimu16, &accel_data );
    c6dofimu16_get_gyro_data( &c6dofimu16, &gyro_data );
    log_printf( &logger, " Accel data | Gyro data \r\n" );
    log_printf( &logger, " X: %.2f g  | %.2f dps \r\n", accel_data.x_data, gyro_data.x_data );
    log_printf( &logger, " Y: %.2f g  | %.2f dps \r\n", accel_data.y_data, gyro_data.y_data );
    log_printf( &logger, " Z: %.2f g  | %.2f dps \r\n", accel_data.z_data, gyro_data.z_data );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.C6DOFIMU16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

\mainpage Main Page

---
# 6DOF IMU 22 click

> 6DOF IMU 22 Click is a compact add-on board for advanced motion tracking. This board features the ICM-42670-P, a high-performance 6-axis MEMS MotionTracking IMU from TDK InvenSense. The ICM-42670-P integrates a 3-axis gyroscope and accelerometer, offering exceptional precision in motion detection. It supports both I2C and SPI interfaces for communication, features a substantial 2.25Kbytes FIFO, and includes two programmable interrupts that enhance power efficiency through a wake-on-motion feature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu22_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DOF IMU 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 6DOF IMU 22 Click driver.

#### Standard key functions :

- `c6dofimu22_cfg_setup` Config Object Initialization function.
```c
void c6dofimu22_cfg_setup ( c6dofimu22_cfg_t *cfg );
```

- `c6dofimu22_init` Initialization function.
```c
err_t c6dofimu22_init ( c6dofimu22_t *ctx, c6dofimu22_cfg_t *cfg );
```

- `c6dofimu22_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu22_default_cfg ( c6dofimu22_t *ctx );
```

#### Example key functions :

- `c6dofimu22_read_data` This function reads the accelerometer, gyroscope, and temperature measurement data.
```c
err_t c6dofimu22_read_data ( c6dofimu22_t *ctx, c6dofimu22_data_t *data_out );
```

- `c6dofimu22_get_int1_pin` This function returns the INT1 pin logic state.
```c
uint8_t c6dofimu22_get_int1_pin ( c6dofimu22_t *ctx );
```

- `c6dofimu22_clear_data_ready` This function clears the data ready interrupt by reading the INT_STATUS_DRDY register.
```c
err_t c6dofimu22_clear_data_ready ( c6dofimu22_t *ctx );
```

## Example Description

> This example demonstrates the use of 6DOF IMU 22 click board by reading and displaying 
the accelerometer and gyroscope data (X, Y, and Z axis) as well as a temperature measurement in degrees Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu22_cfg_t c6dofimu22_cfg;  /**< Click config object. */

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
    c6dofimu22_cfg_setup( &c6dofimu22_cfg );
    C6DOFIMU22_MAP_MIKROBUS( c6dofimu22_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu22_init( &c6dofimu22, &c6dofimu22_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU22_ERROR == c6dofimu22_default_cfg ( &c6dofimu22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a data ready indication and then reads the accelerometer, gyroscope, and temperature measurements.
The results are displayed on the USB UART every 80ms as per the accel and gyro output data rate which is set to 12.5 Hz.

```c
void application_task ( void )
{
    static c6dofimu22_data_t meas_data;
    if ( !c6dofimu22_get_int1_pin ( &c6dofimu22 ) )
    {
        c6dofimu22_clear_data_ready ( &c6dofimu22 );
        if ( C6DOFIMU22_OK == c6dofimu22_read_data ( &c6dofimu22, &meas_data ) )
        {
            log_printf ( &logger, " Accel X: %.2f g\r\n", meas_data.accel.x );
            log_printf ( &logger, " Accel Y: %.2f g\r\n", meas_data.accel.y );
            log_printf ( &logger, " Accel Z: %.2f g\r\n", meas_data.accel.z );
            log_printf ( &logger, " Gyro X: %.1f dps\r\n", meas_data.gyro.x );
            log_printf ( &logger, " Gyro Y: %.1f dps\r\n", meas_data.gyro.y );
            log_printf ( &logger, " Gyro Z: %.1f dps\r\n", meas_data.gyro.z );
            log_printf ( &logger, " Temperature: %.2f C\r\n\n", meas_data.temperature );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

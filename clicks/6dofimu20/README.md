\mainpage Main Page

---
# 6DOF IMU 20 click

> 6DOF IMU 20 Click is a compact add-on board with a 6-axis inertial measurement unit. This board features the BMI323, a high-performance, low-power inertial measurement unit (IMU) from Bosch Sensortec.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu20_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-20-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DOF IMU 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 6DOF IMU 20 Click driver.

#### Standard key functions :

- `c6dofimu20_cfg_setup` Config Object Initialization function.
```c
void c6dofimu20_cfg_setup ( c6dofimu20_cfg_t *cfg );
```

- `c6dofimu20_init` Initialization function.
```c
err_t c6dofimu20_init ( c6dofimu20_t *ctx, c6dofimu20_cfg_t *cfg );
```

- `c6dofimu20_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu20_default_cfg ( c6dofimu20_t *ctx );
```

#### Example key functions :

- `c6dofimu20_get_gyr_data` 6DOF IMU 20 gyro data reading function.
```c
err_t c6dofimu20_get_gyr_data ( c6dofimu20_t *ctx, c6dofimu20_data_t *gyr_data );
```

- `c6dofimu20_get_temperature` 6DOF IMU 20 temperature reading function.
```c
err_t c6dofimu20_get_temperature ( c6dofimu20_t *ctx, float *temp_data );
```

- `c6dofimu20_sw_reset` 6DOF IMU 20 software reset function.
```c
err_t c6dofimu20_sw_reset ( c6dofimu20_t *ctx );
```

## Example Description

> This library contains API for 6DOF IMU 20 Click driver. 
 The library initializes and defines the I2C and SPI bus drivers to 
 write and read data from registers, as well as the default 
 configuration for reading gyroscope and accelerator data, and temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver after that resets the device and 
 performs default configuration and reads the device id.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu20_cfg_t c6dofimu20_cfg;  /**< Click config object. */

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
    c6dofimu20_cfg_setup( &c6dofimu20_cfg );
    C6DOFIMU20_MAP_MIKROBUS( c6dofimu20_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu20_init( &c6dofimu20, &c6dofimu20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t chip_id;
    
    c6dofimu20_get_id( &c6dofimu20, &chip_id );
    if ( C6DOFIMU20_CHIP_ID != chip_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU20_ERROR == c6dofimu20_default_cfg ( &c6dofimu20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the 6DOF IMU 20 Click board by 
 measuring and displaying acceleration and gyroscope data for X-axis, 
 Y-axis, and Z-axis as well as temperature in degrees Celsius.

```c
void application_task ( void )
{
    c6dofimu20_data_t accel_data;
    c6dofimu20_data_t gyro_data;
    uint16_t data_rdy;
    float temperature;
    c6dofimu20_get_reg( &c6dofimu20, C6DOFIMU20_REG_STATUS, &data_rdy );
    if ( C6DOFIMU20_STATUS_DRDY_ACC_FLAG & data_rdy )
    {
        c6dofimu20_get_acc_data( &c6dofimu20, &accel_data );
        log_printf( &logger, " Accel: X: %d, Y: %d, Z: %d \r\n", accel_data.data_x, accel_data.data_y, accel_data.data_z ); 
    }
    if ( C6DOFIMU20_STATUS_DRDY_GYR_FLAG & data_rdy )
    {
        c6dofimu20_get_gyr_data( &c6dofimu20, &gyro_data );
        log_printf( &logger, " Gyro: X: %d, Y: %d, Z: %d \r\n", gyro_data.data_x, gyro_data.data_y, gyro_data.data_z ); 
    }
    if ( C6DOFIMU20_STATUS_DRDY_TEMP_FLAG & data_rdy )
    {
        c6dofimu20_get_temperature( &c6dofimu20, &temperature );
        log_printf( &logger, " Temperature: %.2f degC \r\n", temperature );
    }
    log_printf( &logger, " - - - - - - - - - - - - - - - - - - - - - - - - \r\n" ); 
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

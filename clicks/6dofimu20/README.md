
---
# 6DOF IMU 20 Click

> [6DOF IMU 20 Click](https://www.mikroe.com/?pid_product=MIKROE-5606) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5606&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for 6DOF IMU 20 Click driver. 
 The library initializes and defines the I2C and SPI bus drivers to 
 write and read data from registers, as well as the default 
 configuration for reading gyroscope and accelerator data, and temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU20

### Example Key Functions

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
    Delay_ms ( 500 );
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

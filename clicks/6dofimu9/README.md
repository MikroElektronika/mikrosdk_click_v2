
---
# 6DOF IMU 9 Click

> [6DOF IMU 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3827) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3827&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application measure 3-axis gyroscope and a 3-axis accelerometer.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU9

### Example Key Functions

- `c6dofimu9_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu9_cfg_setup ( c6dofimu9_cfg_t *cfg );
``` 
 
- `c6dofimu9_init` Initialization function. 
```c
err_t c6dofimu9_init ( c6dofimu9_t *ctx, c6dofimu9_cfg_t *cfg );
```

- `c6dofimu9_set_gyro_config` Set Gyro configuration function. 
```c
void c6dofimu9_set_gyro_config( c6dofimu9_t *ctx, uint8_t gyro_config_data );
```
 
- `c6dofimu9_set_gyro_measurement_range` Set Gyro measurement range configuration function. 
```c
void c6dofimu9_set_gyro_measurement_range( c6dofimu9_t *ctx, uint16_t gyro_full_scale_range );
```

- `c6dofimu9_set_accel_measurement_range` Set Accel measurement range configuration function. 
```c
void c6dofimu9_set_accel_measurement_range( c6dofimu9_t *ctx, uint8_t accel_full_scale_range );
```

### Application Init

> Initialization driver enables - I2C, check device ID,
> configure accelerometer and gyroscope, also write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu9_cfg_t cfg;
    uint8_t device_id;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu9_cfg_setup( &cfg );
    C6DOFIMU9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu9_init( &c6dofimu9, &cfg );

    log_printf( &logger, "       Driver  Initialization        \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_100ms( );
    
    device_id = c6dofimu9_get_device_id( &c6dofimu9 );

    if ( device_id == C6DOFIMU9_DEVICE_ID )
    {
        log_printf( &logger, "       SUCCESS        \r\n" );
        log_printf( &logger, "-------------------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "                ERROR              \r\n" );
        log_printf( &logger, "            RESET DEVICE           \r\n" );
        log_printf( &logger, "-----------------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu9_set_gyro_config_lp_mode( &c6dofimu9, C6DOFIMU9_GYRO_AVERAGE_1x );
    c6dofimu9_set_gyro_measurement_range( &c6dofimu9, C6DOFIMU9_GYRO_FULL_SCALE_250dps );
    c6dofimu9_set_accel_measurement_range( &c6dofimu9, C6DOFIMU9_ACCEL_FULL_SCALE_2g );
    c6dofimu9_set_accel_avg_filter_mode( &c6dofimu9, C6DOFIMU9_ACCEL_AVERAGE_4_SAMPLES );
    
    log_printf( &logger, "            Start measurement             \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_100ms( );
}
```

### Application Task

> This is an example which demonstrates the use of 6DOF IMU 9 Click board.
> Measured and display Accel and Gyro data coordinates values for X-axis, Y-axis and Z-axis.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.

```c
void application_task ( )
{
    int16_t accel_axis_x;
    int16_t accel_axis_y;
    int16_t accel_axis_z;
    int16_t gyro_axis_x;
    int16_t gyro_axis_y;
    int16_t gyro_axis_z;

    c6dofimu9_get_accel_data( &c6dofimu9, &accel_axis_x, &accel_axis_y, &accel_axis_z );
    Delay_10ms( );
    c6dofimu9_get_gyro_data( &c6dofimu9, &gyro_axis_x,  &gyro_axis_y, &gyro_axis_z );
    Delay_10ms( );

    log_printf( &logger, " Accel X : %d ", accel_axis_x );
    log_printf( &logger, "    |     ");
    log_printf( &logger, " Gyro X : %d \r\n", gyro_axis_x );

    log_printf( &logger, " Accel Y : %d ", accel_axis_y );
    log_printf( &logger, "    |     ");
    log_printf( &logger, " Gyro Y : %d \r\n", gyro_axis_y);

    log_printf( &logger, " Accel Z : %d ", accel_axis_z );
    log_printf( &logger, "    |     ");
    log_printf( &logger, " Gyro Z : %d \r\n", gyro_axis_z);

    log_printf(&logger, "-------------------------------------\r\n");
    Delay_1sec( );
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

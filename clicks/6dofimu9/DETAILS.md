
---
# 6DOF IMU 9 click

The 6DOF IMU 9 Click is a Click board™ which features the IAM-20680, a 6-axis MotionTracking device that combines a 3-axis gyroscope and a 3-axis accelerometer, from TDK InvenSense.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/6dofimu9_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/6dof-imu-9-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DOFIMU9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DOFIMU9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu9_cfg_setup ( c6dofimu9_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU9_RETVAL c6dofimu9_init ( c6dofimu9_t *ctx, c6dofimu9_cfg_t *cfg );

#### Example key functions :

- Set Gyro configuration function
> void c6dofimu9_set_gyro_config ( c6dofimu9_t *ctx, uint8_t gyro_config_data );
 
- Set Gyro measurement range configuration function
> void c6dofimu9_set_gyro_measurement_range ( c6dofimu9_t *ctx, uint16_t gyro_full_scale_range );

- Set Accel measurement range configuration function
> void c6dofimu9_set_accel_measurement_range ( c6dofimu9_t *ctx, uint8_t accel_full_scale_range );

## Examples Description

> This application measure 3-axis gyroscope and a 3-axis accelerometer.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C, check device ID,
> configure accelerometer and gyroscope, also write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu9_cfg_t cfg;
    uint8_t device_id;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU9

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---

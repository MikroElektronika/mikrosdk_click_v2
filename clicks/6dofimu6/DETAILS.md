
---
# 6DOF IMU 6 click

6DOF IMU 6 Click features a 6-axis MotionTracking device that combines a 3-axis gyroscope, a 3-axis accelerometer, and a Digital Motion Processor™ (DMP) labeled as ICM-20689. The ICM-20689 from company TDK InvenSense includes on-chip 16-bit ADCs, programmable digital filters, an embedded temperature sensor, and programmable interrupts. The gyroscope and accelerometer are full-scale range, user-programmable sensors with factory-calibrated initial sensitivity for reduced production-line calibration requirements.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/6dof-imu-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DofImu6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu6_cfg_setup ( c6dofimu6_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU6_RETVAL c6dofimu6_init ( c6dofimu6_t *ctx, c6dofimu6_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu6_default_cfg ( c6dofimu6_t *ctx );


#### Example key functions :

- This function executes default configuration for 6DOF IMU 6 click.
> void c6dofimu6_default_cfg ( c6dofimu6_t *ctx );
 
- Function is used to calculate angular rate.
> void c6dofimu6_angular_rate ( c6dofimu6_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte );

- Function is used to calculate acceleration rate.
> void c6dofimu6_acceleration_rate ( c6dofimu6_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte );

## Examples Description

> 6DOF IMU 6 Click features a 6-axis MotionTracking device that combines a 3-axis gyroscope, 
> a 3-axis accelerometer, and a Digital Motion Processor. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI and I2C drivers, performs safety check, applies default and barometer 
> setups and writes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu6_cfg_setup( &cfg );
    C6DOFIMU6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu6_init( &c6dofimu6, &cfg );

    Delay_ms( 100 );
    c6dofimu6_generic_read ( &c6dofimu6, C6DOFIMU6_WHO_AM_I, &id_val, 1 );
    if ( id_val == C6DOFIMU6_WHO_AM_I_VAL )
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   6DOF  IMU  6  click   \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        c6dofimu6_power ( &c6dofimu6, C6DOFIMU6_POWER_ON );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu6_default_cfg( &c6dofimu6 );

    log_printf( &logger, "    ---Initialised---    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    Delay_ms( 100 );
}
  
```

### Application Task

> Demonstrates use of 6DOF IMU 6 click board by reading angular rate, acceleration rate 
> and displaying data via USART terminal.

```c

void application_task ( void )
{
    c6dofimu6_angular_rate( &c6dofimu6, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Angular rate: \r\n" );

    FloatToStr( x_gyro, log_txt );
    log_printf( &logger, "X-axis: %f\r\n", x_gyro );
    log_printf( &logger, "Y-axis: %f\r\n", y_gyro );
    log_printf( &logger, "Z-axis: %f\r\n", z_gyro );
    log_printf( &logger, "---------------------\r\n" );

    c6dofimu6_acceleration_rate( &c6dofimu6, &x_accel, &y_accel, &z_accel );

    log_printf( &logger, "Acceleration rate: \r\n" );

    FloatToStr( x_accel, log_txt );
    log_printf( &logger, "X-axis: %f\r\n", x_accel );
    log_printf( &logger, "Y-axis: %f\r\n", y_accel );
    log_printf( &logger, "Z-axis: %f\r\n", z_accel );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu6

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

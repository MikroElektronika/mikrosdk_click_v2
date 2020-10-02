\mainpage Main Page
 
---
# 6 Dof imu 3 click

6 DOF IMU 3 Click is a complete 6-axis detection development board suitable for movement and position tracking devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/6dof-imu-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6Dofimu3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6Dofimu3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void C6dotimu3_cfg_setup ( C6dotimu3_cfg_t *cfg ); 
 
- Initialization function.
> C6DOTIMU3_RETVAL C6dotimu3_init ( C6dotimu3_t *ctx, C6dotimu3_cfg_t *cfg );

- Click Default Configuration function.
> void C6dotimu3_default_cfg ( C6dotimu3_t *ctx );


#### Example key functions :

- Function check device ID by read ID value from the sensor ID register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> C6DOFIMU3_RETVAL_T c6dofimu3_check_id ( C6dotimu3_t *ctx );
 
- Function read 16-bit ( signed ) Magnetometer
   X-axis, Y-axis data and Z-axis data from the 6
  targeted starts from C6DOFIMU3_M_OUT_X_MSB register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> void c6dofimu3_read_mag_data ( C6dotimu3_t *ctx, c6dofimu3_mag_t *mag_data );

- Function read 14-bit ( signed ) Accel
   X-axis, Y-axis data and Z-axis data from the 6
  targeted starts from C6DOFIMU3_OUT_X_MSB register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> void c6dofimu3_read_accel_data ( C6dotimu3_t *ctx, c6dofimu3_accel_t *accel_data );

## Examples Description

> This application shows functionality of this Click board/

**The demo application is composed of two sections :**

### Application Init 

> Initialization of communication module and configuration of device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    C6dotimu3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    C6dotimu3_cfg_setup( &cfg );
    C6DOTIMU3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    C6dotimu3_init( &C6dotimu3, &cfg );

    C6dotimu3_default_cfg( &C6dotimu3 );
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads sensor measurements and logs it.

```c

void application_task ( void )
{
    if ( c6dofimu3_check_data_ready( &C6dotimu3 ) )
    {
        c6dofimu3_get_data ( &C6dotimu3, &accel_data, &mag_data );

        log_printf( &logger, " Accel X : %d   |    Mag X : %d\r\n", accel_data.x, mag_data.x );

        log_printf( &logger, " Accel Y : %d   |    Mag Y : %d\r\n", accel_data.y, mag_data.y );
        
        log_printf( &logger, " Accel Z : %d   |    Mag Z : %d\r\n", accel_data.z, mag_data.z );
        
        log_printf( &logger, "-------------------------------------\r\n" );

        Delay_ms( 800 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6Dofimu3

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

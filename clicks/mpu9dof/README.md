\mainpage Main Page
 
---
# MPU 9DOF click

MPU 9DOF click carries the MPU–9250 System in Package, which is the world’s first 9-axis Motion Tracking device. MPU–9250 comprises two chips. One is the MPU–6050 that contains a 3-axis accelerometer, a 3-axis gyroscope, and a DMP (digital motion processor); the other is AK8975, a 3-axis digital compass. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mpu9dof_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/mpu-9dof-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Mpu9Dof Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mpu9Dof Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mpu9dof_cfg_setup ( mpu9dof_cfg_t *cfg ); 
 
- Initialization function.
> MPU9DOF_RETVAL mpu9dof_init ( mpu9dof_t *ctx, mpu9dof_cfg_t *cfg );

- Click Default Configuration function.
> void mpu9dof_default_cfg ( mpu9dof_t *ctx );


#### Example key functions :

- Function read Gyro X-axis, Y-axis and Z-axis axis.
> void mpu9dof_read_accel ( mpu9dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );
 
- Function read Gyro X-axis, Y-axis and Z-axis axis.
> void mpu9dof_read_gyro ( mpu9dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

- Function read Magnetometar X-axis, Y-axis and Z-axis axis.
> void mpu9dof_read_mag ( mpu9dof_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z );

## Examples Description

> MPU 9DOF click carries the world’s first 9-axis Motion Tracking device. It comprises two chips: one that contains 
> a 3-axis accelerometer, a 3-axis gyroscope, and a DMP (digital motion processor); 
> the other is a 3-axis digital compass. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, initialize MPU-9150 XL G & MPU-9150 MAG and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mpu9dof_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mpu9dof_cfg_setup( &cfg );
    MPU9DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mpu9dof_init( &mpu9dof, &cfg );

    Delay_10ms( );
    mpu9dof_default_cfg ( &mpu9dof );
}
  
```

### Application Task

> This is a example which demonstrates the use of MPU 9DOF Click board.
> Measured accel, gyro and magnetometar coordinates values ( X, Y, Z )
> and temperature value in degrees celsius [ �C ] are being sent to the uart where you can track their changes.
> All data logs on usb uart for aproximetly every 1 sec. 

```c

void application_task ( void )
{
    mpu9dof_read_accel( &mpu9dof, &accel_x, &accel_y, &accel_z );
    Delay_10ms( );
    mpu9dof_read_gyro( &mpu9dof, &gyro_x,  &gyro_y, &gyro_z );
    Delay_10ms( );
    mpu9dof_read_mag( &mpu9dof, &mag_x,  &mag_y, &mag_z );
    Delay_10ms( );
    temperature = mpu9dof_read_temperature( &mpu9dof );
    Delay_10ms( );

    log_printf( &logger, " Accel X : %d   |   Gyro X : %d   |   Mag X : %d \r\n", accel_x, gyro_x, mag_x );
    log_printf( &logger, " Accel Y : %d   |   Gyro Y : %d   |   Mag Y : %d \r\n", accel_y, gyro_y, mag_y );
    log_printf( &logger, " Accel Z : %d   |   Gyro Z : %d   |   Mag Z : %d \r\n", accel_z, gyro_z, mag_z );
    Delay_10ms( );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n" );
    Delay_10ms( );
    log_printf( &logger, "Temperature: %.2f C\r\n", temperature );
    Delay_100ms( );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "\r\n");
    Delay_ms( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mpu9Dof

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

\mainpage Main Page
 
 

---
# 9 DOF click

9DOF click carries ST’s LSM9DS1 inertial measurement module that combines a 3D accelerometer, a 3D gyroscope and a 3D magnetometer into a single device outputting so called nine degrees of freedom data...

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/9dof_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/9dof-click>)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the 9Dof Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 9Dof Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c9dof_cfg_setup ( c9dof_cfg_t *cfg ); 
 
- Initialization function.
> C9DOF_RETVAL c9dof_init ( c9dof_t *ctx, c9dof_cfg_t *cfg );

- Click Default Configuration function.
> void c9dof_default_cfg ( c9dof_t *ctx );


#### Example key functions :

- Generic accelerometer read function.
> void c9dof_read_accel ( c9dof_t *ctx, c9dof_accel_data_t *accel_data );
 
- Get gyroscope data function.
> void c9dof_read_gyro ( c9dof_t *ctx, c9dof_gyro_data_t *gyro_data );

- Get magnetometer data function.
> void c9dof_read_mag ( c9dof_t *ctx, c9dof_mag_data_t *mag_data );

## Examples Description

> 
> This application shows accelerometer, gyroscope
> and magnetometer axes values.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes GPIO pins, I2C, LOG modules and
> sets default configuration.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "----       Application Init       ----\r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );

    //  Click initialization.

    c9dof_cfg_setup( &cfg );
    C9DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof_init( &c9dof, &cfg );
    
    c9dof_default_cfg ( &c9dof );
    Delay_ms( 1000 );
    
    log_printf( &logger, "              9DOF Click\r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );
}
  
```

### Application Task

>
> Gets accelerometer, gyroscope
> and magnetometer axes data and LOGs those values.
> 

```c

void application_task ( void )
{
    c9dof_read_accel( &c9dof, &accel_data );
    Delay_ms( 10 );
    
    c9dof_read_gyro( &c9dof, &gyro_data );
    Delay_ms( 10 );
    
    c9dof_read_mag( &c9dof, &mag_data );
    Delay_ms( 10 );
    
    log_printf( &logger, "   Accel    |    Gyro    |    Mag\r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );
    log_printf( &logger, " X = %6d | X = %6d | X = %6d\r\n", accel_data.x, gyro_data.x, mag_data.x );
    log_printf( &logger, " Y = %6d | Y = %6d | Y = %6d\r\n", accel_data.y, gyro_data.y, mag_data.y );
    log_printf( &logger, " Z = %6d | Z = %6d | Z = %6d\r\n", accel_data.z, gyro_data.z, mag_data.z );
    log_printf( &logger, "--------------------------------------\r\n" );
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.9Dof

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

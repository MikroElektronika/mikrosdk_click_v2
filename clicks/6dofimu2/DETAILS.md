
 

---
# 6DOF IMU 2 click

6DOF IMU 2 Click is capable of precise acceleration and angular rate (gyroscopic) measurement.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-2-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DofImu2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu2_cfg_setup ( c6dofimu2_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU2_RETVAL c6dofimu2_init ( c6dofimu2_t *ctx, c6dofimu2_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu2_default_cfg ( c6dofimu2_t *ctx );


#### Example key functions :

- This function executes default configuration for 6DOF IMU 2 click.
> void c6dofimu2_default_cfg ( c6dofimu2_t *ctx, c6dofimu2_cfg_t *cfg );
 
- This function read Accel X-axis, Y-axis and Z-axis.
> void c6dofimu2_read_accel ( c6dofimu2_t *ctx, c6dofimu2_accel_data_t *accel_data );

- This function read Gyro X-axis, Y-axis and Z-axis.
> void c6dofimu2_read_gyro ( c6dofimu2_t *ctx, c6dofimu2_gyro_data_t *gyro_data );

## Examples Description

> 
> Example Code presents acceleration and angular rate (gyroscopic) measurement.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    c6dofimu2_cfg_setup( &cfg );
    C6DOFIMU2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu2_init( &c6dofimu2, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " --- 6DOF IMU 2 Click ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 100 );
    
    c6dofimu2_default_cfg( &c6dofimu2, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

>
> This is an example which demonstrates the usage of 6DOF IMU 2 Click board.
> It measures accel and gyro coordinates (X,Y,Z) and then the results 
> are being sent to the UART Terminal where you can track their changes for every 1 sec.
> 

```c

void application_task ( void )
{
    c6dofimu2_read_accel( &c6dofimu2, &accel_data );
    Delay_ms ( 100 );
    c6dofimu2_read_gyro( &c6dofimu2, &gyro_data );
    Delay_ms ( 100 );
    
    log_printf( &logger, "    Accel    |    Gyro    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " X = %d  | X = %d \r\n", accel_data.accel_x, gyro_data.gyro_x );
    log_printf( &logger, " Y = %d  | Y = %d \r\n", accel_data.accel_y, gyro_data.gyro_y );
    log_printf( &logger, " Z = %d  | Z = %d \r\n", accel_data.accel_z, gyro_data.gyro_z );
    log_printf( &logger, "--------------------------\r\n" );    
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu2

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

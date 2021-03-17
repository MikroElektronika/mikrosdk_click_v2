\mainpage Main Page
 
 

---
# c6DOF IMU 4 click

6DOF IMU 4 Click is an advanced 6-axis motion tracking Click board™, which utilizes the ICM-20602, a high-performance integrated motion sensor, equipped with a 3-axis gyroscope and a 3-axis accelerometer. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/6dof-imu-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the c6DofImu4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c6DofImu4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu4_cfg_setup ( c6dofimu4_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU4_RETVAL c6dofimu4_init ( c6dofimu4_t *ctx, c6dofimu4_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu4_default_cfg ( c6dofimu4_t *ctx );


#### Example key functions :

- Sync Pin Setting function
> void c6dofimu4_set_sync_pin ( c6dofimu4_t *ctx, uint8_t state );
 
- Data Get function
> void c6dofimu4_get_data ( c6dofimu4_t *ctx, c6dofimu4_axis_t *accel_out, c6dofimu4_axis_t *gyro_out, int8_t *temp_out );

- Full Scale Setting function
> uint8_t c6dofimu4_set_fsr ( c6dofimu4_t *ctx, uint8_t gyro_resol, uint8_t accel_resol );

## Examples Description

> This application measures gyroscopic, accelerometer, and temperature data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and performs a device reset and configurations.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu4_cfg_setup( &cfg );
    C6DOFIMU4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu4_init( &c6dofimu4, &cfg );
    c6dofimu4_reset( &c6dofimu4 );

    c6dofimu4_default_cfg( &c6dofimu4 );
    Delay_ms( 200 );

    log_printf( &logger, "** 6DOF IMU 4 is initialized **\r\n" );
}
  
```

### Application Task

> Waits until data is ready and then reads the all data registers,
> accelerometer, gyroscope and temperature data, and shows results to the uart terminal every 500ms.

```c

void application_task ( void )
{
    c6dofimu4_axis_t  accel_data;
    c6dofimu4_axis_t  gyro_data;
    uint8_t data_ready;
    int8_t temperature;

    data_ready = c6dofimu4_get_status( &c6dofimu4, C6DOFIMU4_DATA_RDY_INT_MASK );

    while ( data_ready != C6DOFIMU4_DATA_RDY_INT_OCCURED )
    {
        data_ready = c6dofimu4_get_status( &c6dofimu4, C6DOFIMU4_DATA_RDY_INT_MASK );
    }
    
    c6dofimu4_get_data( &c6dofimu4, &accel_data, &gyro_data, &temperature );
    
    log_printf( &logger,"** Accelerometer values :\r\n" );
    log_printf( &logger, "* X-axis : %.2lf g ", accel_data.x );
    log_printf( &logger, "* Y-axis : %.2lf g ", accel_data.y );
    log_printf( &logger, "* Z-axis : %.2lf g ", accel_data.z );
    log_printf( &logger,"\r\n" );
    
    log_printf( &logger,"** Gyroscope values :\r\n" );
    log_printf( &logger, "* X-axis : %.2lf dps ", gyro_data.x );
    log_printf( &logger, "* Y-axis : %.2lf dps ", gyro_data.y );
    log_printf( &logger, "* Z-axis : %.2lf dps ", gyro_data.z );
    log_printf( &logger,"\r\n" );
    
    log_printf( &logger, "** Temperature value : %d C\r\n", temperature );
    log_printf( &logger,"------------------------------------------------- \r\n" );
    
    Delay_ms( 500 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.c6DofImu4

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

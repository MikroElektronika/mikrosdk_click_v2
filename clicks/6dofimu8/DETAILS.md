
---
# c6DOF IMU 8 click

6DOF IMU 8 click is an advanced 6-axis motion tracking Click board™, which utilizes the ISM330DLC, a high-performance System in Package (SiP), equipped with a 3-axis gyroscope, and a 3-axis accelerometer.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/6dofimu8_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/6dof-imu-8-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the c6DofImu8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c6DofImu8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu8_cfg_setup ( c6dofimu8_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU8_RETVAL c6dofimu8_init ( c6dofimu8_t *ctx, c6dofimu8_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu8_default_cfg ( c6dofimu8_t *ctx );


#### Example key functions :

- This function checks does interrupt generated on the INT1 pin.
> uint8_t c6dofimu8_get_int_1_pin ( c6dofimu8_t *ctx );
 
- This function checks a data ready status for all measurements.
> uint8_t c6dofimu8_get_drdy_status ( c6dofimu8_t *ctx, uint8_t bit_mask );

- This function performs a magnetometer data reading.
> void c6dofimu8_get_magnetometer_data ( c6dofimu8_t *ctx, t_c6dofimu8_axis *magneto_out );

## Examples Description

> This app gets three-axis gyroscope value, three-axis accelerometer value and temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and performs a device software reset and configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu8_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n " );

    //  Click initialization.

    c6dofimu8_cfg_setup( &cfg );
    C6DOFIMU8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu8_init( &c6dofimu8, &cfg );

    Delay_ms( 500 );

    c6dofimu8_default_cfg( &c6dofimu8 );

    log_printf( &logger, "** 6DOF IMU 8 is initialized **\r\n" );
    Delay_ms( 300 );
}
  
```

### Application Task

>Waits until any new data is entered to the data registers and then reads the accelerometer,
> gyroscope and temperature data which will be converted and calculated to the properly units every 300ms.

```c

void application_task ( void )
{
    uint8_t data_ready;
    int8_t temperature;
    t_c6dofimu8_axis  accel_data;
    t_c6dofimu8_axis  gyro_data;

    char accel_unit[ 3 ] = { ' ', 'g', 0 };
    char gyro_unit[ 5 ] = { ' ', 'd', 'p', 's', 0 };
    char temp_unit[ 4 ] = { ' ', 176, 'C', 0 };

    data_ready = c6dofimu8_get_drdy_status( &c6dofimu8, C6DOFIMU8_TEMP_DRDY_MASK | C6DOFIMU8_G_DRDY_MASK | C6DOFIMU8_XL_DRDY_MASK );
    while ( data_ready == C6DOFIMU8_EVENT_NOT_DETECTED )
    {
        data_ready = c6dofimu8_get_drdy_status( &c6dofimu8, C6DOFIMU8_TEMP_DRDY_MASK | C6DOFIMU8_G_DRDY_MASK | C6DOFIMU8_XL_DRDY_MASK );
    }

    c6dofimu8_get_data( &c6dofimu8, &accel_data, &gyro_data, &temperature );

    log_printf( &logger, "** Accelerometer values : \r\n" );
    log_axis( &accel_data, &accel_unit[ 0 ] );

    log_printf( &logger, "** Gyroscope values : \r\n" );
    log_axis( &gyro_data, &gyro_unit[ 0 ] );

    log_printf( &logger, "** Temperature value : %d %c \r\n", temperature, temp_unit );
    log_printf( &logger, "-------------------------------------------------\r\n" );

    Delay_ms( 300 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.c6DofImu8

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

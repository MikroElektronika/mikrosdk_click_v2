\mainpage Main Page
 
 
 

---
# 10DOF click

10DOF click is a mikroBUS add-on board for enhancing hardware prototypes with 10DOF functionality (10 degrees of freedom). The click board carries two modules from Bosch: BNO055, a 9-axis absolute orientation sensor and BMP180, a digital pressure sensor.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/10dof_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/10dof-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the C10Dof Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for C10Dof Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c10dof_cfg_setup ( c10dof_cfg_t *cfg ); 
 
- Initialization function.
> C10DOF_RETVAL c10dof_init ( c10dof_t *ctx, c10dof_cfg_t *cfg );

- Click Default Configuration function.
> void c10dof_default_cfg ( c10dof_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> void c10dof_write_byte( c10dof_t *ctx, uint8_t reg, uint8_t data_in, uint8_t slave_addr );
 
- This function reads the ID value od the BMP180 chip.
> uint8_t c10dof_bmp180_chip_ID ( c10dof_t *ctx );

- This function sets default configuration for the BMP180 sensor function.
> void c10dof_default_configuration_BMP180 ( c10dof_t *ctx );

## Examples Description

> This is a example which demonstrates the use of 10DOF Click board.
> It measures temperature, humidity and pressure data from the BME180 chip sensor
> and accel, gyro and magnetometar coordinates values for X-axis, Y-axis and Z-axis.


**The demo application is composed of two sections :**

### Application Init 

> Initialize the driver and sets the default configuration of BMP180 and BNO055 chip.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c10dof_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c10dof_cfg_setup( &cfg );
    C10DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c10dof_init( &c10dof, &cfg );
    c10dof_default_cfg( &c10dof );
}
  
```

### Application Task

> Displays temperature, humidity and pressure data from the BMP180 and BNO055 sensors.

```c

void application_task ( void )
{
    c10dof_read_accel( &c10dof, &accelX, &accelY, &accelZ );
    Delay_ms( 10 );
    c10dof_read_gyro( &c10dof, &gyroX,  &gyroY, &gyroZ );
    Delay_ms( 10 );
    c10dof_read_mag( &c10dof, &magX,  &magY, &magZ );
    Delay_ms( 10 );
    
    temperature = c10dof_get_temperature( &c10dof );
    Delay_ms( 10 );
    c10dof_get_measurements( &c10dof, &temperature, &pressure );
    Delay_ms( 10 );

    log_printf( &logger, "Accel X : %d  |  ", accelX );
    log_printf( &logger, "Gyro X  : %d  |  ", gyroX );
    log_printf( &logger, "Mag X   : %d  |  ", magX );
    log_printf( &logger, "Temp.   : %.2f C  \r\n", temperature, deg_cel);

    log_printf( &logger, "Accel Y : %d  |  ", accelY);
    log_printf( &logger, "Gyro Y  : %d  |  ", gyroY);
    log_printf( &logger, "Mag Y   : %d  |  \r\n", magY);

    log_printf( &logger, "Accel Z : %d  |  ", accelZ);
    log_printf( &logger, "Gyro Z  : %d  |  ", gyroZ);
    log_printf( &logger, "Mag Z   : %d  |  ", magZ);
    log_printf( &logger, "Press.  : %.2f mbar \r\n", pressure);

    log_printf( &logger, "--------------------------------------------------------------------\r\n", pressure);
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.C10Dof

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

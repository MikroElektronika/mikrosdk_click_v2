
---
# 6DOF IMU click

<6DOF IMU click carries ST’s LSM6DS33TR 6-axis inertial measurement unit comprising a 3-axis gyroscope and a 3-axis accelerometer. The chip is a highly accurate 6 DOF inertial measurement unit with long-term stable operation over a wide range of temperatures.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type

# Software Support

We provide a library for the 6DofImu Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu_cfg_setup ( c6dofimu_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU_RETVAL c6dofimu_init ( c6dofimu_t *ctx, c6dofimu_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu_default_cfg ( c6dofimu_t *ctx );

#### Example key functions :

- This function reads axis data for the gyroscope or the accelerometer from
  predefined data register addresses.
> void c6dofimu_read_axis_data ( c6dofimu_t *ctx, uint8_t read_mode );
 
- This function reads temperature data from predefined data registers.
> float c6dofimu_read_temperature ( c6dofimu_t *ctx );

- This function reads the digital signal from the INT pin.
> uint8_t c6dofimu_digital_read_int ( c6dofimu_t *ctx );

## Examples Description

> This example showcases how to initalize and use the 6DOF IMU click. The click contains a 
  6-axis inertial measurement unit ( accelerometer + gyroscope ). After configuring the click
  module for proper use, axis and temperature data will be measured every second. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. In order for the 
  device to work well, proper data needs to be written to the measurement control
  registers as is done in the default_cfg(...) function. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    c6dofimu_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_100ms( );

    //  Click initialization.

    c6dofimu_cfg_setup( &cfg );
    C6DOFIMU_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu_init( &c6dofimu, &cfg );
    Delay_100ms( );
    c6dofimu_default_cfg( &c6dofimu );
}
  
```

### Application Task

> This function reads and displays temperature and accelerometer/gyroscope axis data from
  predefined registers. There is a 1 second delay between every read from the data output
  registers. 

```c

void application_task ( )
{
    float temperature; 

    c6dofimu_read_axis_data( &c6dofimu, C6DOFIMU_ACCEL_READ_MODE );
    Delay_1sec( );
    c6dofimu_read_axis_data( &c6dofimu, C6DOFIMU_GYRO_READ_MODE );
    Delay_1sec( );
    temperature = c6dofimu_read_temperature( &c6dofimu );

    log_printf( &logger, "--------------------------------------------\r\n" );
    log_printf( &logger, " * ACCEL * X: %6.d Y: %6.d Z: %6.d\r\n", c6dofimu.accel_axis.x,
                                                                   c6dofimu.accel_axis.y,
                                                                   c6dofimu.accel_axis.z );
    log_printf( &logger, " * GYRO * X: %6.d Y: %6.d Z: %6.d\r\n", c6dofimu.gyro_axis.x,
                                                                  c6dofimu.gyro_axis.y,
                                                                  c6dofimu.gyro_axis.z );
    log_printf( &logger, " * Temperature: %.3f C\r\n", temperature );
    Delay_1sec( );
}  

```

## Note

> <WARNING> If you write data to any of the "reserved" register addresses, you can permanently
  damage the chip. If you are feeling adventurous, read the LSM6DS33 chip datasheet.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu

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

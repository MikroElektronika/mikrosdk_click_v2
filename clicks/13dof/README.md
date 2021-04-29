\mainpage Main Page
 
 

---
# 13DOF click

13DOF Click is an advanced 13-axis motion tracking Click board™, which utilizes three different sensor ICs onboard: BME680, a digital gas, humidity, pressure and temperature sensor and BMM150, a geomagnetic sensor and a BMI088, small, versatile 6DoF sensor module. All integrated sensors ICs are made by Bosch Sensortec, featuring the state-of-the-art sensor technology processes, in order to fulfill the requirements for immersive gaming and navigation applications, which require highly accurate sensor data fusion.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/13dof_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/13dof-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the c13DOF Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c13DOF Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c13dof_cfg_setup ( c13dof_cfg_t *cfg ); 
 
- Initialization function.
> C13DOF_RETVAL c13dof_init ( c13dof_t *ctx, c13dof_cfg_t *cfg );

- Click Default Configuration function.
> void c13dof_default_cfg ( c13dof_t *ctx );


#### Example key functions :

- Function reads 16-bit X-axis, Y-axis data and Z-axis data.
> void c13dof_bmi088_read_accel ( c13dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );
 
- Function read a sequential data starting from the targeted 8-bit register address.
> C13DOF_BMI088_RETVAL_T c13dof_bmi088_accel_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes );

- Function reads 16-bit X-axis, Y-axis data and Z-axis data of BMM150 sensor on 13DOF Click board.
> void c13dof_bmi088_read_gyro ( c13dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

## Examples Description

> This example displays values registered by sensors on click board.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables -
> BME680 Low power gas, pressure, temperature & humidity sensor, 
> BMI088 6-axis Motion Tracking Sensor and
> BMM150 Geomagnetic Sensor, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c13dof_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c13dof_cfg_setup( &cfg );
    C13DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c13dof_init( &c13dof, &cfg );
    c13dof_default_cfg( &c13dof );
}
  
```

### Application Task

> This is a example which demonstrates the use of 13DOF Click board.
> Measures and display temperature in degrees Celsius [ C ], humidity data [ % ], 
> pressure [ mbar ] and gas resistance data from the BME680 sensor.
> Measures and display Accel and Gyro data coordinates values 
> for X-axis, Y-axis and Z-axis from the BMI088 sensor.
> Measures and display Geomagnetic data coordinates values for 
> X-axis, Y-axis and Z-axis from the BMM150 sensor.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for each second.

```c

void application_task ( void )
{
    temperature = c13dof_bme680_get_temperature( &c13dof );

    log_printf( &logger, "----------------------------------------------------------\n");
    log_printf( &logger, "Temperature : %.2f C \r\n", temperature );

    humidity = c13dof_bme680_get_humidity( &c13dof );
    log_printf( &logger, "Humidity : %.2f %% \r\n", humidity );

    pressure = c13dof_bme680_get_pressure( &c13dof );
    log_printf( &logger, "Pressure : %.2f mbar \r\n", pressure );

    gas_res = c13dof_bme680_get_gas_resistance( &c13dof );
    log_printf( &logger, "Gas Resistance : %ld \r\n", gas_res );
    
    ready_check = c13dof_bmm150_check_ready( &c13dof );

    while ( ready_check != C13DOF_BMM150_DATA_READY )
    {
        ready_check = c13dof_bmm150_check_ready( &c13dof );
    }
    
    c13dof_bmi088_read_accel( &c13dof, &accel_x, &accel_y, &accel_z );
    c13dof_bmi088_read_gyro( &c13dof, &gyro_x, &gyro_y, &gyro_z );
    c13dof_bmm150_read_geo_mag_data( &c13dof, &mag_x, &mag_y, &mag_z, &r_hall );
    
    log_printf( &logger, "Accel X : %d ", accel_x );
    log_printf( &logger, " Y : %d ", accel_y );
    log_printf( &logger, " Z : %d \r\n", accel_z );
    
    log_printf( &logger, "Gyro X : %d ", gyro_x );
    log_printf( &logger, " Y : %d ", gyro_y );
    log_printf( &logger, " Z : %d \r\n", gyro_z );
        
    log_printf( &logger, "Mag X : %d ", mag_x );
    log_printf( &logger, " Y : %d ", mag_y );
    log_printf( &logger, " Z : %d \r\n", mag_z );

    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.c13DOF

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

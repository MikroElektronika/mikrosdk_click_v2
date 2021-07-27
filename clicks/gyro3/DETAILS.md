

---
# Gyro 3 click

Gyro 3 click is a three-axis gyroscope Click board™ that can sense motion over three perpendicular axes. It is equipped with the I3G4250, a three-axis digital gyroscope. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gyro-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Gyro3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gyro3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gyro3_cfg_setup ( gyro3_cfg_t *cfg ); 
 
- Initialization function.
> GYRO3_RETVAL gyro3_init ( gyro3_t *ctx, gyro3_cfg_t *cfg );

- Click Default Configuration function.
> void gyro3_default_cfg ( gyro3_t *ctx );


#### Example key functions :

- This function reads value stored in temperature register (26h).
> void gyro3_get_temp ( gyro3_t *ctx, uint8_t *temperature_value );

- This function reads data level value in FIFO register from FIFO SRC register (2Fh) and stores result in fifo_data_level.
> void gyro3_get_fifo_data_level ( gyro3_t *ctx, uint8_t * fifo_data_level );

- This function reads values from XYZ axes registers and converts them to degrees per second value.
> void gyro3_get_axes ( gyro3_t *ctx, float *x_axis, float *y_axis, float *z_axis, uint8_t measurement_range );




## Examples Description

> This example checks if new data is available on all three axes, If yes then reads and logs their values.

**The demo application is composed of two sections :**

### Application Init 

> Initialize I2C driver, basic device configuration, I2C interface, LOG interface and GPIO pins.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gyro3_cfg_setup( &cfg );
    GYRO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro3_init( &gyro3, &cfg );
    gyro3_default_cfg( &gyro3 );

    Delay_ms( 3000 );
}
  
```

### Application Task

Check if new data is available on all three axes, If yes then read and log their values.

```c

void application_task ( void )
{
    //  Task implementation.

    gyro3_get_status( &gyro3, &status_register );

    if ((status_register & GYRO3_ZYX_NEW_DATA_MASK) == GYRO3_ZYX_NEW_DATA_MASK)
    {

        gyro3_get_axes( &gyro3, &x_axis, &y_axis, &z_axis, GYRO3_MEAS_RANGE_2000 );

        log_printf( &logger, "\r\nx_axis : %.2f %s\t", x_axis, degrees_per_second );
        log_printf( &logger, "y_axis : %.2f %s\t", y_axis, degrees_per_second );
        log_printf( &logger, "z_axis : %.2f %s\r\n", z_axis, degrees_per_second );      
    } 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro3

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

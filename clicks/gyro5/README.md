\mainpage Main Page
 
 

---
# Gyro 5 click

Gyro 5 Click is a three-axis gyroscope Click board™ that can sense motion over three perpendicular axes. It is equipped with the ITG-3701, a three-axis digital gyroscope. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gyro-5-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Gyro5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gyro5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gyro5_cfg_setup ( gyro5_cfg_t *cfg ); 
 
- Initialization function.
> GYRO5_RETVAL gyro5_init ( gyro5_t *ctx, gyro5_cfg_t *cfg );

- Click Default Configuration function.
> void gyro5_default_cfg ( gyro5_t *ctx );


#### Example key functions :

- Getting gyroscope axes values
> void gyro5_get_axes ( gyro5_t *ctx, float *x_axis, float *y_axis, float *z_axis );
 
- Getting temperature value
> void gyro5_get_temperature ( gyro5_t *ctx, float *temperature );

- Click Default Configuration function.
> void gyro5_default_cfg ( gyro5_t *ctx );

## Examples Description

> This application shows temperature and gyroscope axes values

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO pins, I2C and LOG modules.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro5_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gyro5_cfg_setup( &cfg );
    GYRO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro5_init( &gyro5, &cfg );
    gyro5_default_cfg ( &gyro5 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "      Gyro 5 Click\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
  
```

### Application Task

> Checks data ready INT, gets temperature and axes data and LOGs those values

```c

void application_task ( void )
{
    //  Task implementation.
    
    data_ready_flag = gyro5_int_status( &gyro5, GYRO5_INT_DATA_RDY );
    
    if ( data_ready_flag == GYRO5_STATUS_INT_DATA_RDY )
    {
        gyro5_get_temperature( &gyro5, &temperature_value );
        Delay_ms( 10 );
        gyro5_get_axes(  &gyro5, &x_axis_value, &y_axis_value, &z_axis_value );
        Delay_ms( 10 );
        log_printf( &logger, " Temperature = %.2f C\r\n", temperature_value );
        log_printf( &logger, " X axis = %.2f deg/s\r\n", x_axis_value );
        log_printf( &logger, " Y axis = %.2f deg/s\r\n", y_axis_value );
        log_printf( &logger, " Z axis = %.2f deg/s\r\n", z_axis_value );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms( 2000 );
    }
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro5

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

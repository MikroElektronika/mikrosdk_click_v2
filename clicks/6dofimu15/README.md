\mainpage Main Page
 
---
# 6DOF-IMU-15 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DofImu15 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu15 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu15_cfg_setup ( c6dofimu15_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU15_RETVAL c6dofimu15_init ( c6dofimu15_t *ctx, c6dofimu15_cfg_t *cfg );

#### Example key functions :

- Enable the proper device configuration function
> void c6dofimu15_device_conf_set ( c6dofimu15_t *ctx, uint8_t dev_cfg );
 
- Accelerometer data rate selection function
> void c6dofimu15_accel_data_rate ( c6dofimu15_t *ctx, uint8_t data_rate );

- Accelerometer full-scale selection function
> void c6dofimu15_accel_full_scale ( c6dofimu15_t *ctx, uint8_t fs_sel );

## Examples Description

> This demo exaple measures Angular rate and Acceleration rate.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI and I2C drivers, performs safety
> check, applies default setup and writes an log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu15_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu15_cfg_setup( &cfg );
    C6DOFIMU15_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu15_init( &c6dofimu15, &cfg );
    Delay_ms( 100 );

    if ( c6dofimu15_who_im_i( &c6dofimu15 ) )
    {
        log_printf( &logger, "---------------------- \r\n" );
        log_printf( &logger, "   6DOF IMU 6 click    \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "---------------------- \r\n" );
        log_printf( &logger, "    FATAL ERROR!!      \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
        for ( ; ; );
    }

    c6dofimu15_device_conf_set( &c6dofimu15, C6DOFIMU15_PROP_EN );
    c6dofimu15_auto_inc_set( &c6dofimu15, C6DOFIMU15_PROP_EN );
    c6dofimu15_block_data_update_set( &c6dofimu15, C6DOFIMU15_PROP_EN );
    c6dofimu15_fifo_mode_set( &c6dofimu15, C6DOFIMU15_FIFO_DIS );
    c6dofimu15_accel_data_rate( &c6dofimu15, C6DOFIMU15_ODR_XL_104_HZ );
    c6dofimu15_accel_full_scale( &c6dofimu15, C6DOFIMU15_FS_XL_2_G );
    c6dofimu15_gyro_data_rate( &c6dofimu15, C6DOFIMU15_ODR_G_104_HZ );
    c6dofimu15_gyro_full_scale( &c6dofimu15, C6DOFIMU15_FS_G_2000_DPS );

    log_printf( &logger, "  ---Initialised---    \r\n" );
    log_printf( &logger, "---------------------- \r\n" );

    Delay_ms( 100 );
}
  
```

### Application Task

> Demonstrates use of 6DOF IMU 6 click board by reading
> angular rate in milidegrees per second, and linear
> acceleration rate in milligravities and displaying data
> via USART terminal. 

```c

void application_task ( void )
{
    float x_accel;
    float y_accel;
    float z_accel;
    float x_gyro;
    float y_gyro;
    float z_gyro;

    c6dofimu15_angular_rate( &c6dofimu15, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Angular rate:  \r\n" );
    log_printf( &logger, "X-axis: %.2f mdps \r\n", x_gyro );
    log_printf( &logger, "Y-axis: %.2f mdps \r\n", y_gyro );
    log_printf( &logger, "Z-axis: %.2f mdps \r\n", z_gyro );
    log_printf( &logger, "---------------------- \r\n" );

    c6dofimu15_acceleration_rate( &c6dofimu15, &x_accel, &y_accel, &z_accel );
    
    log_printf( &logger, "Acceleration rate:  \r\n" );
    log_printf( &logger, "X-axis: %.2f mg \r\n", x_accel );
    log_printf( &logger, "Y-axis: %.2f mg \r\n", y_accel );
    log_printf( &logger, "Z-axis: %.2f mg \r\n", z_accel );
    log_printf( &logger, "---------------------- \r\n" );

    Delay_ms( 1000 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu15

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

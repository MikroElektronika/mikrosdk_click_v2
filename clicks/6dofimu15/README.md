\mainpage Main Page
 
---
# 6DOF IMU 15 Click

6DOF IMU 15 Click is a compact add-on board that contains a 6-axis MEMS motion tracking device combining a 3-axis gyroscope and a 3-axis accelerometer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu15_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/6dof-imu-15-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DofImu15 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu15 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu15_cfg_setup ( c6dofimu15_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU15_RETVAL c6dofimu15_init ( c6dofimu15_t *ctx, c6dofimu15_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu15_default_cfg ( c6dofimu15_t *ctx );

#### Example key functions :

- Enable the proper device configuration function
> void c6dofimu15_device_conf_set ( c6dofimu15_t *ctx, uint8_t dev_cfg );
 
- Accelerometer data rate selection function
> void c6dofimu15_accel_data_rate ( c6dofimu15_t *ctx, uint8_t data_rate );

- Accelerometer full-scale selection function
> void c6dofimu15_accel_full_scale ( c6dofimu15_t *ctx, uint8_t fs_sel );

## Examples Description

> This example demonstrates the use of 6DOF IMU 15 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, checks the communication and sets the device default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu15_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu15_cfg_setup( &cfg );
    C6DOFIMU15_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu15_init( &c6dofimu15, &cfg );
    Delay_ms ( 100 );

    if ( c6dofimu15_who_im_i( &c6dofimu15 ) )
    {
        log_printf( &logger, "---------------------- \r\n" );
        log_printf( &logger, "   6DOF IMU 15 Click    \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "---------------------- \r\n" );
        log_printf( &logger, "    FATAL ERROR!!      \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
        for ( ; ; );
    }

    c6dofimu15_default_cfg( &c6dofimu15 );

    log_printf( &logger, "  ---Initialised---    \r\n" );
    log_printf( &logger, "---------------------- \r\n" );

    Delay_ms ( 100 );
}
  
```

### Application Task

> Measures acceleration and gyroscope data and displays the results on USB UART each second.

```c

void application_task ( void )
{
    float x_accel;
    float y_accel;
    float z_accel;
    float x_gyro;
    float y_gyro;
    float z_gyro;

    c6dofimu15_acceleration_rate( &c6dofimu15, &x_accel, &y_accel, &z_accel );
    c6dofimu15_angular_rate( &c6dofimu15, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, " Accel X: %.2f \t Gyro X: %.2f\r\n", x_accel, x_gyro );
    log_printf( &logger, " Accel Y: %.2f \t Gyro Y: %.2f\r\n", y_accel, y_gyro );
    log_printf( &logger, " Accel Z: %.2f \t Gyro Z: %.2f\r\n", z_accel, z_gyro );
    log_printf( &logger, "----------------------------------\r\n");

    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu15

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

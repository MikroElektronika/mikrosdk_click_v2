\mainpage Main Page
 
---
# 6DOF IMU 7 Click

6DOF IMU 7 Click is based on the ICM-20649, a high-performance, 6-axis MEMS MotionTracking™ IC from TDK Invensense. It is an advanced, integrated microelectromechanical gyroscope and accelerometer sensor (MEMS). This allows very high integration and very small dimensions, at an affordable cost.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/6dof-imu-7-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

We provide a library for the 6DofImu7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu7_cfg_setup ( c6dofimu7_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU7_RETVAL c6dofimu7_init ( c6dofimu7_t *ctx, c6dofimu7_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu7_default_cfg ( c6dofimu7_t *ctx );


#### Example key functions :

- This function reads gyroscope axis data and configures the gyro axis struct.
> void c6dofimu7_get_gyro_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *gyro, float sensitivity );
 
- This function reads accelerometer axis data and configures the accel axis struct.
> void c6dofimu7_get_accel_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *accel, float sensitivity );

- This function reads and returns temperature data.
> float c6dofimu7_get_temp_data ( c6dofimu7_t *ctx, float temp_sensitivity, float temp_offset );

## Examples Description

> This example showcases how to initialize and configure the logger and Click modules and read
  and display temperature measurements and axis data from the gyroscope and accelerometer. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and Click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    c6dofimu7_cfg_t cfg;

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

    c6dofimu7_cfg_setup( &cfg );
    C6DOFIMU7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu7_init( &c6dofimu7, &cfg );
    c6dofimu7_default_cfg( &c6dofimu7 );
}
  
```

### Application Task

> This function reads and displays accelerometer, gyroscope and temperature data every second. 

```c

void application_task ( )
{
    float temperature;

    c6dofimu7_get_gyro_data( &c6dofimu7, &gyro, C6DOFIMU7_GYRO_SENSITIVITY );

    log_printf( &logger, " * Gyro_X: %.5f * \r\n", gyro.x_axis );
    log_printf( &logger, " * Gyro_Y: %.5f * \r\n", gyro.y_axis );
    log_printf( &logger, " * Gyro_Z: %.5f * \r\n", gyro.z_axis );
    log_printf( &logger, " ---------------------------- \r\n" );

    c6dofimu7_get_accel_data( &c6dofimu7, &accel, C6DOFIMU7_ACCEL_SENSITIVITY );

    log_printf( &logger, " * Accel_X: %.5f * \r\n", accel.x_axis );
    log_printf( &logger, " * Accel_Y: %.5f * \r\n", accel.y_axis );
    log_printf( &logger, " * Accel_Z: %.5f * \r\n", accel.z_axis );
    log_printf( &logger, " ---------------------------- \r\n" );

    temperature = c6dofimu7_get_temp_data( &c6dofimu7, C6DOFIMU7_TEMPERATURE_SENSITIVITY,
                                                       C6DOFIMU7_TEMPERATURE_OFFSET );

    log_printf( &logger, " * Temperature: %.5f C * \r\n\r\n", temperature );
    Delay_ms ( 1000 );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu7

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

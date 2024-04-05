\mainpage Main Page
 
---
# c6DOF IMU 10 click

6DOF IMU 10 Click is a 6 Degrees-of-Freedom inertial sensor module, that features KMX62 sensor whcih consist of tri-axial magnetometer (range ±2g / ±4g / ±8g / ±16g) plus a triaxial accelerometer (±1200µT).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-10-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the c6DofImu10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c6DofImu10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu10_cfg_setup ( c6dofimu10_cfg_t *cfg ); 
 
- Initialization function.
> c6DOFIMU10_RETVAL c6dofimu10_init ( c6dofimu10_t *ctx, c6dofimu10_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu10_default_cfg ( c6dofimu10_t *ctx );


#### Example key functions :

- This function gets accelerometer axis data.
> void c6dofimu10_get_accel_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis );
 
- This function gets magnetometer axis data.
> void c6dofimu10_get_mag_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis );

- This function gets temperature data.
> float c6dofimu10_get_temperature ( c6dofimu10_t *ctx, uint8_t temp_format );

## Examples Description

> This app reads the accelerometer and magnetometer axis data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and runs a communication test that reads device id (registry Who_I_AM).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu10_cfg_t cfg;
    uint8_t com_test;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    c6dofimu10_cfg_setup( &cfg );
    c6DOFIMU10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu10_init( &c6dofimu10, &cfg );

    // TEST COMMUNICATION
    com_test = c6dofimu10_communication_test( &c6dofimu10 );
    if ( com_test != C6DOFIMU10_DEVICE_OK )
    {
        log_printf( &logger, "-- Device communication ERROR --\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "-- Device communication OK --\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    c6dofimu10_default_cfg ( &c6dofimu10 );
    log_printf( &logger, "-- Device configuration --\r\n" );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Reads the accelerometer and magnetometer axis data.
> And reads temperature values. All data logs on the USBUART.

```c

void application_task ( void )
{
    c6dofimu10_axis_t accel_axis;
    c6dofimu10_axis_t mag_axis;
    float temperature;

    c6dofimu10_get_accel_axis ( &c6dofimu10, &accel_axis );
    c6dofimu10_get_mag_axis ( &c6dofimu10, &mag_axis );
    temperature = c6dofimu10_get_temperature( &c6dofimu10, C6DOFIMU10_TEMP_FORMAT_CELSIUS );

    log_printf( &logger, "-- Accelerometer axis --\r\n" );
    app_display_axis_data( &accel_axis );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-- Magnetometer axis --\r\n" );
    app_display_axis_data( &mag_axis );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-- Temperature data --\r\n" );
    app_display_temp_data( temperature );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu10

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

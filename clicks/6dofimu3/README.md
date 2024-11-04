\mainpage Main Page
 
---
# 6DOF IMU 3 Click

6DOF IMU 3 Click is a complete 6-axis detection development board suitable for movement and position tracking devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/6dof-imu-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6Dofimu3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6Dofimu3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu3_cfg_setup ( c6dofimu3_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU3_RETVAL c6dofimu3_init ( c6dofimu3_t *ctx, c6dofimu3_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu3_default_cfg ( c6dofimu3_t *ctx );


#### Example key functions :

- Function check device ID by read ID value from the sensor ID register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> C6DOFIMU3_RETVAL_T c6dofimu3_check_id ( c6dofimu3_t *ctx );
 
- Function read 16-bit ( signed ) Magnetometer
   X-axis, Y-axis data and Z-axis data from the 6
  targeted starts from C6DOFIMU3_M_OUT_X_MSB register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> void c6dofimu3_read_mag_data ( c6dofimu3_t *ctx, c6dofimu3_mag_t *mag_data );

- Function read 14-bit ( signed ) Accel
   X-axis, Y-axis data and Z-axis data from the 6
  targeted starts from C6DOFIMU3_OUT_X_MSB register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> void c6dofimu3_read_accel_data ( c6dofimu3_t *ctx, c6dofimu3_accel_t *accel_data );

## Examples Description

> This example demonstrates the use of 6DOF IMU 3 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and sets the device default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu3_cfg_t cfg;

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

    c6dofimu3_cfg_setup( &cfg );
    C6DOFIMU3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu3_init( &c6dofimu3, &cfg );

    c6dofimu3_default_cfg( &c6dofimu3 );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Measures acceleration and magnetometer data and displays the results on USB UART each second.

```c

void application_task ( void )
{
    if ( c6dofimu3_check_data_ready( &c6dofimu3 ) )
    {
        c6dofimu3_get_data ( &c6dofimu3, &accel_data, &mag_data );

        log_printf( &logger, " Accel X : %.2f mg \t Mag X : %.2f uT\r\n", accel_data.x, mag_data.x );

        log_printf( &logger, " Accel Y : %.2f mg \t Mag Y : %.2f uT\r\n", accel_data.y, mag_data.y );
        
        log_printf( &logger, " Accel Z : %.2f mg \t Mag Z : %.2f uT\r\n", accel_data.z, mag_data.z );
        
        log_printf( &logger, "-------------------------------------\r\n" );

        Delay_ms ( 800 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6Dofimu3

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

\mainpage Main Page
 
 
---
# 6DOF IMU 11 click

The 6DOF IMU 11 click is a Click board™ based on the KMX63, a 6 Degrees-of-Freedom inertial sensor system on a single, silicon chip, which is designed to strike a balance between current consumption and noise performance with excellent bias stability over temperature. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the 6DofImu11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu11_cfg_setup ( c6dofimu11_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU11_RETVAL c6dofimu11_init ( c6dofimu11_t *ctx, c6dofimu11_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu11_default_cfg ( c6dofimu11_t *ctx );


#### Example key functions :

- Configuration Accel function
> void c6dofimu11_config_accel ( c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_range, uint8_t data_resolution )

- Configuration Magnetometer function
> void c6dofimu11_config_mag ( c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_resolution )

- Get axis data function
> int16_t c6dofimu11_get_axis ( c6dofimu11_t *ctx, uint8_t reg_add_lsb )

- Read Accel X-axis, Y-axis and Z-axis function
> void c6dofimu11_get_accel_data ( c6dofimu11_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z )

- Read Magnetometer X-axis, Y-axis and Z-axis function
> void c6dofimu11_get_mag_data ( c6dofimu11_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z )

- Get Accel range X, Y and Z value ( g ) function
> void c6dofimu11_read_accel (  c6dofimu11_t *ctx, c6dofimu11_accel_t *accel_data )

- Get Magnetometer magnetic field strength X, Y and Z value ( nT ) function
> void c6dofimu11_read_mag ( c6dofimu11_t *ctx, c6dofimu11_mag_t *mag_data )


## Examples Description

> Designed to strike a balance between current consumption and noise performance with excellent bias stability over temperature

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C, check device ID,
  sets default configuration, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu11_cfg_t cfg;

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

    c6dofimu11_cfg_setup( &cfg );
    C6DOFIMU11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu11_init( &c6dofimu11, &cfg );

    if ( c6dofimu11_check_id( &c6dofimu11 ) == C6DOFIMU11_CHECK_ID_SUCCESS )
    {
        log_printf( &logger, "         SUCCESS          \r\n" );
        log_printf( &logger, "--------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "          ERROR           \r\n" );
        log_printf( &logger, "     Reset the device     \r\n" );
        log_printf( &logger, "--------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu11_default_cfg(  &c6dofimu11 );

    log_printf( &logger, "    Set default config    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

> This is an example which demonstrates the use of 6DOF IMU 11 Click board.
> Measured and display Accel and Magnetometer magnetic field strength values for X-axis, Y-axis and Z-axis.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 2 sec. 

```c

void application_task ( void )
{
c6dofimu11_mag_t mag_data;
   c6dofimu11_accel_t accel_data;
   
   c6dofimu11_read_accel ( &c6dofimu11, &accel_data );
    Delay_ms ( 10 );
    c6dofimu11_read_mag ( &c6dofimu11, &mag_data );
    Delay_ms ( 10 );

    log_printf( &logger, " Accel X : %d %c g\r\n", accel_data.x  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Accel Y : %d %c g\r\n", accel_data.y  );
    c6dofimu11_uart_sign_print (  ); 

    
    log_printf( &logger, " Accel Z : %d %c g\r\n", accel_data.z  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Mag X : %d %c uT\r\n", mag_data.x  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Mag Y : %d %c uT\r\n", mag_data.y  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Mag Z : %d %c uT\r\n", mag_data.z  );
    c6dofimu11_uart_sign_print (  );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu11

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

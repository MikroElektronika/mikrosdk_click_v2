
---
# 9DOF 2 click

9DOF 2 Click is a compact add-on board for applications which require lowest power motion tracking and magnetometer functionality. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/9dof2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/9dof-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the 9dof2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 9dof2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c9dof2_cfg_setup ( c9dof2_cfg_t *cfg ); 
 
- Initialization function.
> C9DOF2_RETVAL c9dof2_init ( c9dof2_t *ctx, c9dof2_cfg_t *cfg );

- Click Default Configuration function.
> void c9dof2_default_cfg ( c9dof2_t *ctx );


#### Example key functions :

- Turns the device on or off.
> void c9dof2_power ( c9dof2_t *ctx, uint8_t on_off );
 
- Function is used to read gyroscope data.
> void c9dof2_read_gyroscope ( c9dof2_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

- Function is used to read accelerometer data.
> void c9dof2_read_accelerometer ( c9dof2_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );

## Examples Description

> This example demonstrates the use of 9DOF 2 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI and device drivers, performs safety check, applies default configuration and writes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof2_cfg_t cfg;

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

    c9dof2_cfg_setup( &cfg );
    C9DOF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof2_init( &c9dof2, &cfg );

    c9dof2_dev_rst( &c9dof2 );
    Delay_ms( 1000 );

    id_val = c9dof2_read_byte ( &c9dof2, C9DOF2_WHO_AM_I_ICM20948 );
     
    if ( id_val == C9DOF2_WHO_AM_I_ICM20948_VAL )
    {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "   9DOF  2  click   \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        c9dof2_power ( &c9dof2, C9DOF2_POWER_ON );
    }
    else
    {
        log_printf(  &logger, "--------------------\r\n" );
        log_printf(  &logger, "   FATAL ERROR!!!   \r\n" );
        log_printf(  &logger, "--------------------\r\n" );
        for ( ; ; );
    }
    
    c9dof2_def_settings( &c9dof2 );

    log_printf(  &logger, "--- Initialised ---\r\n" );
    log_printf(  &logger, "--------------------\r\n" );

    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads the angular and acceleration rates and displays the values of X, Y, and Z axis on the USB UART each second.

```c

void application_task ( void )
{
    //  Task implementation.
    
    c9dof2_angular_rate( &c9dof2, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Angular rate: \r\n" );

    log_printf( &logger, "X-axis: %.2f \r\n", x_gyro );

    log_printf( &logger, "Y-axis: %.2f \r\n", y_gyro );

    log_printf( &logger, "Z-axis: %.2f \r\n", z_gyro );

    log_printf( &logger, "---------------------\r\n" );

    c9dof2_acceleration_rate( &c9dof2, &x_accel, &y_accel, &z_accel );

    log_printf( &logger, "Acceleration rate: \r\n" );

    log_printf( &logger, "X-axis: %.2f \r\n", x_accel );

    log_printf( &logger, "Y-axis: %.2f \r\n", y_accel );

    log_printf( &logger, "Z-axis: %.2f \r\n", z_accel );

    log_printf( &logger, "---------------------\r\n" );

    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.9dof2

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

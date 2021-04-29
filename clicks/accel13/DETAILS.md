
---
# Accel 13 click

Accel 13 Click features an ultra-low power triaxial accelerometer sensor with embedded intelligence, labeled as the IIS2DLPC. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-13-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel13 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel13 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel13_cfg_setup ( accel13_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL13_RETVAL accel13_init ( accel13_t *ctx, accel13_cfg_t *cfg );

- Click Default Configuration function.
> void accel13_default_cfg ( accel13_t *ctx );


#### Example key functions :

- This function reads the status data and stores it in the status object.
> void accel13_get_status ( accel13_t *ctx, accel13_status_t *status);
 
- This function reads the tap status data and stores it in the tap_status object.
> void accel13_get_tap_status ( accel13_t *ctx, accel13_tap_t *tap_status );

- This function reads the 6D status data and stores it in the sixd_status object.
> void accel13_get_6d_status ( accel13_t *ctx, accel13_6d_t *sixd_status );

## Examples Description

> This application enables reading acceleration and tapping data on all 3 axes,
> using I2C or SPI communication.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, Test communication, 
> starts chip configuration for measurement and Temperature reads.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel13_cfg_t cfg;
    uint8_t device_id;
    float temperature;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    accel13_cfg_setup( &cfg );
    ACCEL13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel13_init( &accel13, &cfg );

    accel13_generic_read_bytes( &accel13, ACCEL13_REG_WHO_AM_I, &device_id, 1 );

    if ( device_id != ACCEL13_DEF_WHO_AM_I )
    {
        log_printf( &logger, "*\\*/*\\*/ Communication ERROR !!! \\*/*\\*/*" );
        for ( ; ; );
    }
    log_printf( &logger, "---- Communication OK!!! ----\r\n" );
    Delay_100ms( );

    // Configuration

    accel13_default_cfg ( &accel13 );

    accel13_generic_write_single_byte( &accel13, ACCEL13_REG_CTRL_6, ACCEL13_CTRL6_BW_FILT_ODR_2 |
                                                                     ACCEL13_CTRL6_FULL_SCALE_2g |
                                                                     ACCEL13_CTRL6_FDS_LOW_PASS |
                                                                     ACCEL13_CTRL6_LOW_NOISE_ENABLE );

    // Temperature

    temperature = accel13_get_temperature( &accel13 );
    log_printf( &logger, " Temperature : %f.2 \r\n", temperature);
}
  
```

### Application Task

> Reads Accelerometer data and detects tap on the axis

```c

void application_task ( void )
{
    //  Task implementation.

    // Reads Accel data
    accel13_get_axis_data( &accel13, &axis );

    log_printf( &logger, "---- Accel axis data ----\r\n\n" );
    
    log_printf( &logger, "* X : %d \r\n", axis.x );
   
    log_printf( &logger, "* Y : %d \r\n", axis.y);

    log_printf( &logger, "* Z : %d \r\n", axis.z);
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 300 );
    
    // Detections Tap on the axis
    accel13_get_tap_status( &accel13, &tap );

    if ( tap.tap_x == 0x01 )
    {
        log_printf( &logger, "---- Tap on the X axis ----\r\n" );
    }

    if( tap.tap_y == 0x01 )
    {
        log_printf( &logger,"---- Tap on the Y axis ----\r\n" );
    }

    if( tap.tap_z == 0x01 )
    {
        log_printf( &logger,"---- Tap on the Z axis ----\r\n" );
    }
}

```

## Note
 
> The example is the basic functionality of the IIS2DLPC sensor, 
> it is possible to read the acceleration data and detect Tap on all 3 axes.
> For other settings and improvements in reading accuracy, 
> you need to further set up the registers and set the sensor to your conditions. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel13

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
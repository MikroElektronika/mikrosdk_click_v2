\mainpage Main Page
 
 

---
# 3D Hall 7 click

3D Hall 7 click is a very accurate, magnetic field sensing Click board™, used to measure the intensity of the magnetic field across three perpendicular axes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 3dHall7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3dHall7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3dhall7_cfg_setup ( c3dhall7_cfg_t *cfg ); 
 
- Initialization function.
> C3DHALL7_RETVAL c3dhall7_init ( c3dhall7_t *ctx, c3dhall7_cfg_t *cfg );

- Click Default Configuration function.
> void c3dhall7_default_cfg ( c3dhall7_t *ctx );


#### Example key functions :

- Get Axis data function.
> void c3dhall7_get_axis_data( c3dhall7_t *ctx, T_C3DHALL7_AXIS *axis)
 
- Measurement status function.
> void c3dhall7_get_status ( c3dhall7_t *ctx, T_C3DHALL7_STATUS *status );

- Measurement status function.
> void c3dhall7_get_status ( c3dhall7_t *ctx, T_C3DHALL7_STATUS *status );

## Examples Description

> 
> Read magnet positions.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes driver init, test communication and configuration device for measurement.
> 

```c

void application_init ( c3dhall7_t *ctx, void )
{
    c3dhall7_dev_info_t info;

    log_cfg_t log_cfg;
    c3dhall7_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall7_cfg_setup( &cfg );
    C3DHALL7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall7_init( &c3dhall7, &cfg );

    c3dhall7_device_reset( &c3dhall7 );
    Delay_ms( 1000 );
    c3dhall7_read_data( &c3dhall7, 0x01, &red_data, 1 );

    Delay_100ms( );

    for ( ; ; );
    // Test communication 
    c3dhall7_deviceInfo( &info );
    if ( info.device_id == C3DHALL7_DEVICE_ID )
    {
        mikrobus_logW_write( "---- Communication [ OK ]!!! ----", LOG_LINE );
    }
    else
    {
        mikrobus_log_write( "---- Communication [ ERROR ]!!! ----", LOG_LINE );

        for ( ; ; );
    }

    // Configuration 
    c3dhall7_default_cfg ( &c3dhall7 );
}
  
```

### Application Task

>
> Reads 3 Axis of the magnetic sensor and logs this data to USBUART every 500ms.
> 

```c

void application_task ( void )
{
    c3dhall7_axix_t axis;

    char demo_text[ 50 ];
    
    c3dhall7_get_axis_data( &axis );
    
    mikrobus_log_write( "---- Measurement data of magnetic sensor ----", LOG_LINE );
    
    log_printf( &logger, "X axis: %d \r\n", axis.x );

    log_printf( &logger, "Y axis: %d \r\n", axis.y );

    log_printf( &logger, "Z axis: %d \r\n", axis.z );
    
    mikrobus_log_write( "---------------------------------------------", LOG_LINE);
    Delay_ms( 500 );
}

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall7

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

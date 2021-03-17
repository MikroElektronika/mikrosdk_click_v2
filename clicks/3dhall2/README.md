\mainpage Main Page
 
 

---
# 3D Hall 2 click

3D Hall 2 click is a very accurate magnetic field sensing Click board™, used to sense the magnetic field strength in three perpendicular axes. It relies on a TLV493D-A1B6, a low power 3D magnetic sensor from Infineon. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/3d-hall-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the C3dHall2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for C3dHall2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3dhall2_cfg_setup ( c3dhall2_cfg_t *cfg ); 
 
- Initialization function.
> C3DHALL2_RETVAL c3dhall2_init ( c3dhall2_t *ctx, c3dhall2_cfg_t *cfg );


#### Example key functions :


- This function reads data from register.
> void c3dhall2_read_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len );

- This function gets temperature and axis data.
> void c3dhall2_get_axis_temp_data ( c3dhall2_t *ctx, float *axis_data, float *temp_data );

- This function configures the chip for measurement.
> void c3dhall2_configuration( c3dhall2_t *ctx, uint8_t settings1, uint8_t settings2);


## Examples Description

> This example reads X/Y/Z hall axis and temperature data and converts it to human readable format.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and configuration chip.

```c

void application_init ( void )
{
     c3dhall2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall2_cfg_setup( &cfg );
    C3DHALL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall2_init( &c3dhall2, &cfg );
    c3dhall2_default_cfg( &c3dhall2 );
}
  
```

### Application Task

> Reads X/Y/Z hall axis and Temperature data and logs values every 3 seconds.

```c

void application_task ( void )
{
    c3dhall2_get_axis_temp_data( &c3dhall2, &xyz_axis[ 0 ], &temperature );

    log_printf( &logger, " Axis X: %.2f mT\r\n", xyz_axis[ 0 ] );
    log_printf( &logger, " Axis Y: %.2f mT\r\n", xyz_axis[ 1 ] );
    log_printf( &logger, " Axis Z: %.2f mT\r\n", xyz_axis[ 2 ] );

    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );

    Delay_ms( 3000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.C3dHall2

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


 

---
# 3D Hall 5 click

3D HALL 5 click is a very accurate, magnetic field sensing Click board, used to measure the intensity of the magnetic field across three perpendicular axes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall5_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/3d-hall-5-click>)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 3dHall5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3dHall5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3dhall5_cfg_setup ( c3dhall5_cfg_t *cfg ); 
 
- Initialization function.
> C3DHALL5_RETVAL c3dhall5_init ( c3dhall5_t *ctx, c3dhall5_cfg_t *cfg );

- Click Default Configuration function.
> void c3dhall5_default_cfg ( c3dhall5_t *ctx );


#### Example key functions :

- Axis data
> int16_t c3dhall5_get_axis_data ( c3dhall5_t *ctx, uint8_t axis );
 
- Set offest
> void c3dhall5_set_offset ( c3dhall5_t *ctx, uint8_t offset_axis, int16_t offset );

- Interrupt state
> uint8_t c3dhall5_get_interrupt_state ( c3dhall5_t *ctx );

## Examples Description

>  The Demo application displays and reads 3 magnetic axes.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects. 
> Reads device ID for check communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall5_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall5_cfg_setup( &cfg );
    C3DHALL5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall5_init( &c3dhall5, &cfg );

    c3dhall5_default_cfg ( &c3dhall5 );
    
    device_id = c3dhall5_get_device_id ( &c3dhall5 );
    log_info( &logger, "** Device ID: 0x%x", device_id );
}
```

### Application Task

> Reads the magnetics X / Y / Z axis data every 1 seconds.

```c
void application_task ( void )
{
    int16_t axis_X;
    int16_t axis_Y;
    int16_t axis_Z;

    //  Task implementation.
    
    axis_X = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_X );
    axis_Y = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_Y );
    axis_Z = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_Z );
    
    log_printf( &logger, "----- AXIS -----\r\n" );
    log_printf( &logger, "** X: %d \r\n", axis_X );
    log_printf( &logger, "** Y: %d \r\n", axis_Y );
    log_printf( &logger, "** Z: %d \r\n", axis_Z );
    log_printf( &logger, "----------------\r\n" );
    
    Delay_ms( 1000 );
}
```

## Note

> Default communication that is set is I2C communication. 
> If you want to use SPI, you have to set up the cfg structure.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall5

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

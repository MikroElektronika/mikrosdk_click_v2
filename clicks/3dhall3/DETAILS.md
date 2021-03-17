
---
# 3D Hall 3 click

3D Hall 3 click is a very accurate, magnetic field sensing Click board™, used to measure the intensity of the magnetic field across three perpendicular axes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/3d-hall-3-click>)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 3DHall3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3DHall3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3dhall3_cfg_setup ( c3dhall3_cfg_t *cfg ); 
 
- Initialization function.
> C3DHALL3_RETVAL c3dhall3_init ( c3dhall3_t *ctx, c3dhall3_cfg_t *cfg );

- Click Default Configuration function.
> void c3dhall3_default_cfg ( c3dhall3_t *ctx );


#### Example key functions :

- This function reads xyz values from the module.
> void c3dhall3_read_xyz ( c3dhall3_t *ctx, int16_t *out_xyz );
 
- This function writes offest values to the module.
> void c3dhall3_write_offset (c3dhall3_t *ctx, uint8_t axis, uint16_t offset );

- This function sets desired threshold value.
> void c3dhall3_interrupt_threshold ( c3dhall3_t *ctx, uint16_t threshold );

## Examples Description

> This example returns values of X,Y and Z axes.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and sets basic configuration. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall3_cfg_setup( &cfg );
    C3DHALL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall3_init( &c3dhall3, &cfg );
    c3dhall3_default_cfg ( &c3dhall3 );
    log_info( &logger, "---- System Init ----" );
}
  
```

### Application Task

> Reads the values of the X,Y and Z axes.

```c

void application_task ( void )
{
    int16_t axes_xyz[3];

    //  Task implementation.
    
    c3dhall3_read_xyz( &c3dhall3, axes_xyz );
    log_printf( &logger, "X: %d \r\n", axes_xyz[ 0 ] );
    log_printf( &logger, "Y: %d \r\n", axes_xyz[ 1 ] );
    log_printf( &logger, "Z: %d \r\n", axes_xyz[ 2 ] );

    Delay_ms( 100 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall3

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

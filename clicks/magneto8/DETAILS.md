
---
# Magneto 8 click

Magneto 8 Click is a compact add-on board that contains an easy-to-program magnetic rotary position sensor with incremental quadrature (A/B) and 12-bit digital outputs. This board features the AS5601, 12-bit programmable contactless encoder IC from AMS-AG.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto8_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/magneto-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Magneto8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Magneto8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneto8_cfg_setup ( magneto8_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETO8_RETVAL magneto8_init ( magneto8_t *ctx, magneto8_cfg_t *cfg );

- Click Default Configuration function.
> void magneto8_default_cfg ( magneto8_t *ctx );


#### Example key functions :

- Gets magnitude data
> uint16_t magneto8_get_magnitude ( magneto8_t *ctx );
 
- Gets Angle data
> uint16_t magneto8_get_angle_data ( magneto8_t *ctx );

- Gets PSH pin state
> uint8_t magneto8_psh_pin_state ( magneto8_t *ctx );

## Examples Description

> This example demonstrates the use of Magneto 8 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and applies the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    magneto8_cfg_setup( &cfg );
    MAGNETO8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto8_init( &magneto8, &cfg );

    magneto8_default_cfg( &magneto8 );
    log_printf( &logger, "--- Configuration done ---- \r\n" );
    Delay_ms( 500 );
}
  
```

### Application Task

> Reads angle and magnitude data and displays it on the USB UART every 500ms.

```c

void application_task ( void )
{
    uint16_t angle;
    uint16_t mag;

    mag  = magneto8_get_magnitude( &magneto8 );
    log_printf( &logger, "Magnitude: %d \r\n", mag );
    
    angle = magneto8_get_angle_data( &magneto8 );
    log_printf( &logger, "Angle : %d \r\n", angle );

    log_printf( &logger, "---------------------- \r\n" );
    Delay_ms( 500 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto8

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

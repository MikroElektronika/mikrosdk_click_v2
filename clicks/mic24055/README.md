\mainpage Main Page
 
 

---
# MIC24055  click

MIC24055 click is the buck regulator that can deliver continuous output current up to 8A and can step down voltages from up to 19V which makes this click board easy to use with many power sources commonly available.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic24055_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mic24055-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mic24055 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic24055 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mic24055_cfg_setup ( mic24055_cfg_t *cfg ); 
 
- Initialization function.
> MIC24055_RETVAL mic24055_init ( mic24055_t *ctx, mic24055_cfg_t *cfg );

#### Example key functions :

- Generic transfer function.
> void mic24055_generic_transfer ( mic24055_t *ctx, spi_master_transfer_data_t *block );
 
- Generic transfer function.
> void mic24055_dac_output ( mic24055_t *ctx, uint16_t value_dac );

- Set output voltage.
> void mic24055_set_vout ( mic24055_t *ctx, uint16_t voltage );

## Examples Description

> This application is the buck regulator.

**The demo application is composed of two sections :**

### Application Init 

> Initializes click driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24055_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mic24055_cfg_setup( &cfg );
    MIC24055_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24055_init( &mic24055, &cfg );
}
  
```

### Application Task

> Slowly alternates the click output between two values.

```c

void application_task ( void )
{
    mic24055_set_vout( &mic24055, 1500 );
    log_printf( &logger, "VOUT set to 1500mV \r\n" );
    log_printf( &logger, "-------------------------- \r\n" );
    Delay_ms( 3000 );
    mic24055_set_vout( &mic24055, 3300 );
    log_printf( &logger, "VOUT set to 3300mV \r\n" );
    log_printf( &logger, "-------------------------- \r\n" );
    Delay_ms( 3000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic24055

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

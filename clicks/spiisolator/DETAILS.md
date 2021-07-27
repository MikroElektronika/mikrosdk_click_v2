

---
# SPI Isolator click

SPI Isolator click carries the ADuM4154 5kV digital isolator optimized for a serial peripheral interface (SPI).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spiisolator_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/spi-isolator-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Spiisolator Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Spiisolator Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void spiisolator_cfg_setup ( spiisolator_cfg_t *cfg ); 
 
- Initialization function.
> SPIISOLATOR_RETVAL spiisolator_init ( spiisolator_t *ctx, spiisolator_cfg_t *cfg );

#### Example key functions :

- Generic transfer function.
> void spiisolator_generic_transfer ( spiisolator_t *ctx, spi_master_transfer_data_t *block );
 
- Write the byte of data function.
> void spiisolator_write_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint8_t write_data );

- Read the byte of data function.
> uint8_t spiisolator_read_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t read_cmd );

## Examples Description
 
> TThe click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over SPI interface.
> In this example we have used an 8x8 click board connected to a SPI Isolator click board. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI, set default configuration, also write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    spiisolator_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    spiisolator_cfg_setup( &cfg );
    SPIISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spiisolator_init( &spiisolator, &cfg );
    
    c8x8_default_cfg( &spiisolator );

    Delay_100ms( );
}
  
```

### Application Task

> Controls an 8x8 click board and displays the steps on UART Terminal.

```c

void application_task ( void )
{
    log_info( &logger, "> Display Character ..." );
    c8x8_display_byte( &spiisolator, demo_char );
    Delay_ms( 1000 );

    log_info( &logger, "> Display String ..." );
    c8x8_display_string( &spiisolator, &demo_string[ 0 ] );
    Delay_ms( 1000 );

    log_info( &logger, "> Display Image ON ..." );
    c8x8_display_image( &spiisolator, &demo_img_on[ 0 ] );
    Delay_ms( 500 );

    log_info( &logger, "> Display Image OFF ..." );
    c8x8_display_image( &spiisolator, &demo_img_off[ 0 ] );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Spiisolator

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

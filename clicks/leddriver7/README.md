\mainpage Main Page
 
---
# LED Driver 7 click

LED Driver 7 click is a Click board™ equipped with the LTC3490, single cell 350mA LED driver from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver7_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/led-driver-7-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the LedDriver7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver7_cfg_setup ( leddriver7_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER7_RETVAL leddriver7_init ( leddriver7_t *ctx, leddriver7_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void leddriver7_generic_write ( leddriver7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- Generic read function.
> void leddriver7_generic_read ( leddriver7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This application is portable lighting and rechargeable flashlights.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver and writes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver7_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver7_cfg_setup( &cfg );
    LEDDRIVER7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver7_init( &leddriver7, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, " LED Driver 7 click  \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
}
  
```

### Application Task

> This example demonstrates the use of LED Driver 7 Click board,
> by cycling wiper positions of AD5171 Digital Potentiometer.

```c

void application_task ( void )
{
    uint8_t n_pos = 0;
    uint8_t pos_num = 64;

    for ( n_pos = 12; n_pos < pos_num; n_pos++ )
    {
        leddriver7_generic_write( &leddriver7, LEDDRIVER7_NORM_OP_MODE, &n_pos, 1 );
        log_printf( &logger, "Position : %d \r\n", n_pos );
        Delay_ms( 500 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver7

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

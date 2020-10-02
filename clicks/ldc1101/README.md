\mainpage Main Page
 
 

---
# LDC 1101 click

LDC1101 click is an inductance-to-digital converter Click Board™. It is designed for a range of different applications, based on the inductivity measurements. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ldc1101_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ldc1101-click>)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Ldc1101 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ldc1101 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ldc1101_cfg_setup ( ldc1101_cfg_t *cfg ); 
 
- Initialization function.
> LDC1101_RETVAL ldc1101_init ( ldc1101_t *ctx, ldc1101_cfg_t *cfg );

- Click Default Configuration function.
> void ldc1101_default_cfg ( ldc1101_t *ctx );


#### Example key functions :

- Functions for reads RP data
> uint16_t ldc1101_get_rp_data ( ldc1101_t *ctx );
 
- Functions for reads L data
> uint16_t ldc1101_get_l_data ( ldc1101_t *ctx );

- Functions for get interrupt pin status
> uint8_t ldc1101_get_interrupt( ldc1101_t *ctx );

## Examples Description

> Example demonstrates measurement of inductance change depending on the linear motion 
> of the metal object.
> Induction of the linear metal position depends on the type of metal and the configuration.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C module and sets CS pin as OUTPUT and PWM and INT pin sa INPUT.
> Driver intialization, standard configurations and start measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ldc1101_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ldc1101_cfg_setup( &cfg );
    LDC1101_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ldc1101_init( &ldc1101, &cfg );

    log_printf( &logger, "     LDC1101 Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    ldc1101_default_cfg ( &ldc1101 );
    Delay_ms( 100 );
}
```

### Application Task

> Reads RP data and logs data to USBUART every 1 sec.

```c
void application_task ( void )
{
    uint16_t rp_data;
    
    rp_data = ldc1101_get_rp_data( &ldc1101 );
    log_printf( &logger, " Inductive Linear Position : %u\r\n", rp_data );
    
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ldc1101

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

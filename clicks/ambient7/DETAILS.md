# Ambient 7 click

Ambient 7 Click is a light intensity-sensing and measuring Click board™, which features an accurate light-intensity sensor labeled as SFH 5701 A01, made by Osram Opto Semiconductors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-7-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Ambient7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient7_cfg_setup ( ambient7_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT7_RETVAL ambient7_init ( ambient7_t *ctx, ambient7_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> ambient7_data_t ambient7_generic_read ( ambient7_t *ctx );

## Examples Description

> Reads 12-bit ADC value.

**The demo application is composed of two sections :**

### Application Init 

> Initializes ADC and LOG for logging data.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient7_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    log_printf( &logger, "------------------\r\n" );

    //  Click initialization.

    ambient7_cfg_setup( &cfg );
    AMBIENT7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient7_init( &ambient7, &cfg );
    
    log_printf( &logger, " Ambient 7 Click\r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads ADC value and this data logs to USBUART every 1 sec.

```c

void application_task ( void )
{
    ambient7_data_t tmp;
    
    //  Task implementation.
    
    tmp = ambient7_generic_read ( &ambient7 );
    log_printf( &logger, "     ADC value \r\n" );
    log_printf( &logger, " [ DEC ]  : %d\r\n", tmp );
    log_printf( &logger, " [ HEX ]  : 0x%x \r\n", tmp );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 1000 );
}  

```

## Note

> Illuminance range [ EV ] - from 0.01 [ lx ] to 10k [ lx ] 
> depending on the ADC you are using.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient7

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

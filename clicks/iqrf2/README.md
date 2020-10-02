\mainpage Main Page
 
---
# iqRF 2 click

IQRF click carries the DCTR-76DA RF transceiver, operating in the 868/916 MHz frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/iqrf2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/iqrf-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the iqrf2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for iqrf2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void iqrf2_cfg_setup ( iqrf2_cfg_t *cfg ); 
 
- Initialization function.
> IQRF2_RETVAL iqrf2_init ( iqrf2_t *ctx, iqrf2_cfg_t *cfg );

- Click Default Configuration function.
> void iqrf2_default_cfg ( iqrf2_t *ctx );


#### Example key functions :

- Generic read function
> uint16_t iqrf2_generic_read ( iqrf2_t *ctx, char *data_buf, uint16_t max_len );
 
- Generic write function
> void iqrf2_generic_write ( iqrf2_t *ctx, char *data_buf, uint16_t len );

## Examples Description

> This example reads and processes data from iqRF 2 clicks

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    iqrf2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    iqrf2_cfg_setup( &cfg );
    IQRF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    iqrf2_init( &iqrf2, &cfg );

    Delay_ms( 500 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    #ifdef TRANSIVER
    
    iqrf2_generic_write( &iqrf2, message, 9 );
        
    Delay_ms( 2000 );
    
    #endif
     
    #ifdef RECIEVER
    
    iqrf2_process(  );
     
    #endif

}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.iqrf2

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

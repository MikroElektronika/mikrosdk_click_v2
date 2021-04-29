
---
# 4G LTE click

4G LTE click is an LTE Cat 1 / 2G multimode cellular network solution, featuring the compact LARA-R2 series modem from u-blox.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4glte_click.png" height=300px>
</p>

 - [click Product page 4G LTE-AT&T CLICK ](https://www.mikroe.com/4g-lte-e-click)

 - [click Product page 4G LTE-E CLICK ](https://www.mikroe.com/4g-lte-att-click)

 - [click Product page 4G LTE-APJ CLICK ](https://www.mikroe.com/4g-lte-apj-click)

 - [click Product page 4G LTE-NA CLICK ](https://www.mikroe.com/4g-lte-na-click)


---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the 4gLte Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 4gLte Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c4glte_cfg_setup ( c4glte_cfg_t *cfg ); 
 
- Initialization function.
> C4GLTE_RETVAL c4glte_init ( c4glte_t *ctx, c4glte_cfg_t *cfg );

#### Example key functions :

- Power module.
> void c4glte_module_power ( c4glte_t *ctx, uint8_t power_state );

- Send command.
> void c4glte_send_command ( c4glte_t *ctx, char *command );

## Examples Description

> This example reads and processes data from 4G LTE clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4glte_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c4glte_cfg_setup( &cfg );
    C4GLTE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4glte_init( &c4glte, &cfg );

    c4glte_module_power( &c4glte, C4GLTE_MODULE_POWER_ON );

    // MODULE INIT
    
    c4glte_send_command( &c4glte, C4GLTE_AT );
    c4glte_process( );
    c4glte_send_command( &c4glte, C4GLTE_ATE1 );
    c4glte_process( );
    c4glte_send_command( &c4glte, C4GLTE_AT_IFC );
    c4glte_process( );
    c4glte_send_command( &c4glte, C4GLTE_AT_CMGF );
    c4glte_process( );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    c4glte_process( ); 

    if ( send_data_cnt == 5 )
    {
        c4glte_send_command ( &c4glte, C4GLTE_ATH );
        c4glte_process( ); 
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.4gLte

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

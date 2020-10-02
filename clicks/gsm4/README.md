\mainpage Main Page
 
---
# GSM 4 click

GSM 4 click is a compact quad-band GSM cellular network communication solution, featuring the quad-band 2.5G GSM/GPRS SARA-G350 module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsm4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gsm-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Gsm4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gsm4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsm4_cfg_setup ( gsm4_cfg_t *cfg ); 
 
- Initialization function.
> GSM4_RETVAL gsm4_init ( gsm4_t *ctx, gsm4_cfg_t *cfg );

#### Example key functions :

- Enables or disables module power.
> void gsm4_module_power( gsm4_t *ctx );
 
- Reset module.
> void gsm4_reset ( gsm4_t *ctx );

- Command function.
> void gsm4_send_command ( gsm4_t *ctx, char *command );

## Examples Description
 
> This example reads and processes data from GSM 4 clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsm4_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    gsm4_cfg_setup( &cfg );
    GSM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsm4_init( &gsm4, &cfg );

    gsm4_module_power( &gsm4 );

    gsm4_process(  );
    
    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_AT );
    gsm4_process(  );

    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_AT );
    gsm4_process(  );

    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_AT );
    gsm4_process(  );

    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_ATE0 );
    gsm4_process(  );

    gsm4_send_command( &gsm4, "AT+IFC=2,2" );
    gsm4_process(  );

    gsm4_send_command( &gsm4, "AT+CMGF=1" );
    gsm4_process(  );

    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it. 

```c

void application_task ( void )
{
  gsm4_process(  );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gsm4

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

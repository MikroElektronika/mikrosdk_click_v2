
# GSM 2 click

GSM2 click is a compact quad-band GSM cellular network communication solution, featuring the GSM/GPRS Quectel M95. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsm2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gsm-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Gsm2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gsm2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsm2_cfg_setup ( gsm2_cfg_t *cfg ); 
 
- Initialization function.
> GSM2_RETVAL gsm2_init ( gsm2_t *ctx, gsm2_cfg_t *cfg );


#### Example key functions :

- Enables or disables module power.
> void gsm2_module_power( gsm2_t *ctx );
 
- Reset module.
> void gsm2_reset ( gsm2_t *ctx );

- Command function.
> void gsm2_send_command ( gsm2_t *ctx, char *command );

## Examples Description

> This example reads and processes data from GSM 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsm2_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    gsm2_cfg_setup( &cfg );
    GSM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsm2_init( &gsm2, &cfg );

    gsm2_module_power( &gsm2 );

    gsm2_process(  );
    
    gsm2_send_command( &gsm2, GSM2_SINGLE_CMD_AT );
    gsm2_process(  );

    gsm2_send_command( &gsm2, GSM2_SINGLE_CMD_AT );
    gsm2_process(  );

    gsm2_send_command( &gsm2, GSM2_SINGLE_CMD_AT );
    gsm2_process(  );

    gsm2_send_command( &gsm2, GSM2_SINGLE_CMD_ATE0 );
    gsm2_process(  );

    gsm2_send_command( &gsm2, "AT+IFC=2,2" );
    gsm2_process(  );

    gsm2_send_command( &gsm2, "AT+CMGF=1" );
    gsm2_process(  );
    
    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it. 

```c

void application_task ( void )
{
  gsm2_process(  );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gsm2

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

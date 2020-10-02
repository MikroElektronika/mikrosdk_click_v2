\mainpage Main Page
 
---
# GSM click

GSM click is a compact and powerful GSM cellular network communication solution, featuring the GSM/GPRS Telit GL865-QUAD module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsm_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gsm-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Gsm Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gsm Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsm_cfg_setup ( gsm_cfg_t *cfg ); 
 
- Initialization function.
> GSM_RETVAL gsm_init ( gsm_t *ctx, gsm_cfg_t *cfg );

#### Example key functions :

- Enables or disables module power.
> void gsm_module_power( gsm_t *ctx );
 
- Generic write function.
> void gsm_generic_write ( gsm_t *ctx, char *data_buf, uint16_t len );

- Command function.
> void gsm_send_command ( gsm_t *ctx, char *command );

## Examples Description

> This example reads and processes data from GSM clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, power on module and sends few command for the default module configuration. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsm_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    gsm_cfg_setup( &cfg );
    GSM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsm_init( &gsm, &cfg );

    gsm_process(  );

    gsm_send_command( &gsm, GSM_SINGLE_CMD_AT );
    gsm_process(  );
    
    gsm_send_command( &gsm, GSM_SINGLE_CMD_AT );
    gsm_process(  );

    gsm_send_command( &gsm, GSM_SINGLE_CMD_AT );
    gsm_process(  );

    gsm_send_command( &gsm, GSM_SINGLE_CMD_ATE0 );
    gsm_process(  );

    gsm_send_command( &gsm, "AT+IFC=2,2" );
    gsm_process(  );

    gsm_send_command( &gsm, "AT+CMGF=1" );

    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
     gsm_process( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gsm

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

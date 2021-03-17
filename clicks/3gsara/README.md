\mainpage Main Page
 
---
# 3G SARA click

3G SARA click is a versatile cellular network communication solution, featuring the compact 3.75G UMTS/HSPA SARA U-201 modem from u-blox.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3gsara_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/3g-sara-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the 3gSara Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3gSara Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3gsara_cfg_setup ( c3gsara_cfg_t *cfg ); 
 
- Initialization function.
> C3GSARA_RETVAL c3gsara_init ( c3gsara_t *ctx, c3gsara_cfg_t *cfg );

#### Example key functions :

- Power module.
> void c3gsara_module_power( c3gsara_t *ctx, uint8_t power_state );

- Send command.
> void c3gsara_send_command ( c3gsara_t *ctx, char *command );

## Examples Description

> This example reads and processes data from 3G SARA clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3gsara_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3gsara_cfg_setup( &cfg );
    C3GSARA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3gsara_init( &c3gsara, &cfg );

    c3gsara_module_power( &c3gsara, true );

    c3gsara_send_command( &c3gsara, C3GSARA_AT_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_ATE0_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_IFC_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_CMGF_COMMAND ); 
    c3gsara_process( );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    c3gsara_process( );
    
    if ( send_data_cnt == 5 )
    {
        c3gsara_send_command( &c3gsara, C3GSARA_ATH_COMMAND );
        c3gsara_process( );
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
- Click.3gSara

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

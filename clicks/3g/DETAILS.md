
---
# 3G click

3G-EA click is a versatile cellular network communication solution, featuring the compact 3G UMTS/HSPA Quectel UG95 module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3g_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/3g-ea-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the 3g Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3g Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3g_cfg_setup ( c3g_cfg_t *cfg ); 
 
- Initialization function.
> C3G_RETVAL c3g_init ( c3g_t *ctx, c3g_cfg_t *cfg );

#### Example key functions :

- Send Command. 
> void c3g_send_command ( c3g_t *ctx, char *command );
 
- Power up, module.
> void c3g_module_power ( c3g_t *ctx, bool power_state );

- Generic read function.
> uint16_t c3g_generic_read ( c3g_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from 3G clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3g_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3g_cfg_setup( &cfg );
    C3G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3g_init( &c3g, &cfg );

    c3g_module_power( &c3g, true );

    c3g_process( );

    c3g_send_command( &c3g, AT_COMMAND );
    c3g_send_command( &c3g, AT_COMMAND );
    c3g_send_command( &c3g, AT_COMMAND );
    c3g_send_command( &c3g, ATE0_COMMAND );
    c3g_send_command( &c3g, AT_IFC_COMMAND );
    c3g_send_command( &c3g, AT_CMGF_COMMAND );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    c3g_process( );
    
    if ( send_data_cnt == 3 )
    {
       c3g_send_command( &c3g, ATH_COMMAND );
       c3g_process( );
       send_data_cnt = 0;
    }
    send_data_cnt++;
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3g

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

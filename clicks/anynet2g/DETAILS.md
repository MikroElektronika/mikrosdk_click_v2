
---
# AnyNet 2G click

AnyNet 2G Click is a cellular to AWS gateway device, which provides developers with the complete solution for various IoT applications.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/anynet2g_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/anynet-2g-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the AnyNet2g Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AnyNet2g Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void anynet2g_cfg_setup ( anynet2g_cfg_t *cfg ); 
 
- Initialization function.
> ANYNET2G_RETVAL anynet2g_init ( anynet2g_t *ctx, anynet2g_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void anynet2g_generic_write ( anynet2g_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> uint16_t anynet2g_generic_read ( anynet2g_t *ctx, char *data_buf, uint16_t max_len );

- Send command.
> void anynet2g_send_command ( anynet2g_t *ctx, char *command );

## Examples Description

> This example reads and processes data from AnyNet 2G clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    anynet2g_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    anynet2g_cfg_setup( &cfg );
    ANYNET2G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    anynet2g_init( &anynet2g, &cfg );

    anynet2g_send_command( &anynet2g, AT );
    anynet2g_process( );
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_AWSVER );
    anynet2g_process( );
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_QCCID );
    anynet2g_process( );
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_AWSSTATE_GET );  
    anynet2g_process( );                     
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_AWSPUBOPEN_SET );
    anynet2g_process( );
    Delay_ms( 3000 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    anynet2g_send_command( &anynet2g, AT_AWSPUBLISH_SET );
    anynet2g_process( );
    Delay_ms( 3000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AnyNet2g

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

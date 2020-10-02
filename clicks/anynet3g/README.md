\mainpage Main Page
 
---
# AnyNet 3G click

AnyNet 3G-EA/AA Click is a cellular to AWS gateway device, which provides developers with the complete solution for various IoT applications, by using the AWS IoT and Cloud Storage services for the data storage, analyzing and processing.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/anynet3g_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/anynet-3g-ea-click>)
[click Product page](<https://www.mikroe.com/anynet-3g-aa-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the AnyNet3g Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AnyNet3g Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void anynet3g_cfg_setup ( anynet3g_cfg_t *cfg ); 
 
- Initialization function.
> ANYNET3G_RETVAL anynet3g_init ( anynet3g_t *ctx, anynet3g_cfg_t *cfg );

- Click Default Configuration function.
> void anynet3g_default_cfg ( anynet3g_t *ctx );


#### Example key functions :

- This function sends comamnd.
> void anynet3g_send_command ( anynet3g_t *ctx, char *command );
 
- Generic read function.
> uint16_t anynet3g_generic_read ( anynet3g_t *ctx, char *data_buf, uint16_t max_len );

- Reset module.
> void anynet3g_reset ( anynet3g_t *ctx );

## Examples Description

> This example reads and processes data from AnyNet 3G clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    anynet3g_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 56000;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    anynet3g_cfg_setup( &cfg );
    ANYNET3G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    anynet3g_init( &anynet3g, &cfg );

    Delay_ms( 1000 );
    anynet3g_process(  );
    
    anynet3g_send_command( &anynet3g, ANYNET3G_SINGLE_CMD_AT );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_AWSVER );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_QCCID );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_AWSSTATE );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_AWSPUBOPEN );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_PUBLISH_SET );
    anynet3g_process(  );

    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    anynet3g_process(  );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AnyNet3g

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

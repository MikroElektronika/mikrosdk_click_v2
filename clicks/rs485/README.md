\mainpage Main Page
 
---
# RS485 click

RS485 click 3.3V is a RS422/485 transceiver Click board™, which can be used as an interface between the TTL level UART and the RS422/485 communication bus.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/rs-485-click-group.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/rs485-33v-click>)

[click Product page](<https://www.mikroe.com/rs485-5v-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs485 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs485 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs485_cfg_setup ( rs485_cfg_t *cfg ); 
 
- Initialization function.
> RS485_RETVAL rs485_init ( rs485_t *ctx, rs485_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void rs485_generic_write ( rs485_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> uint16_t rs485_generic_read ( rs485_t *ctx, char *data_buf, uint16_t max_len );

- Send command
> void rs485_send_command ( rs485_t *ctx, char *command );

## Examples Description

> This example reads and processes data from RS485 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs485_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs485_cfg_setup( &cfg );
    RS485_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485_init( &rs485, &cfg );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER 
    rs485_process( );
#endif 

#ifdef DEMO_APP_TRANSMITER     
    rs485_send_command( &rs485, TEXT_TO_SEND );
    rs485_process(  );
    Delay_ms( 2000 );
#endif   
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs485

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

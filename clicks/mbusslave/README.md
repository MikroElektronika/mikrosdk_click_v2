\mainpage Main Page
 
---
# M-Bus Slave click

M-Bus Slave Click is a Click board™ equipped with the TSS721A, a single chip transceiver developed by Texas Instruments for Meter-Bus applications according to EN1434-3 standard. The connection to the bus is polarity independent and serves as a slave node in the system. M-Bus Slave Click has full galvanic isolation with optocouplers to improve the reliability of the whole circuit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mbusslave_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/m-bus-slave-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the MBusSlave Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MBusSlave Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mbusslave_cfg_setup ( mbusslave_cfg_t *cfg ); 
 
- Initialization function.
> MBUSSLAVE_RETVAL mbusslave_init ( mbusslave_t *ctx, mbusslave_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void mbusslave_generic_write ( mbusslave_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> uint16_t mbusslave_generic_read ( mbusslave_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from M-Bus Slave clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusslave_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mbusslave_cfg_setup( &cfg );
    MBUSSLAVE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusslave_init( &mbusslave, &cfg );
}
  
```

### Application Task

> Reads the received data. 

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITER
    mbusslave_generic_write( &mbusslave, demo_message_data, 9 );
    log_printf( &logger, " >> MESSAGE SENT << \r\n" );
    Delay_ms( 2000 );
#endif 

#ifdef DEMO_APP_RECEIVER
    mbusslave_process( );
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MBusSlave

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

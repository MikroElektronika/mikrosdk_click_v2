
---
# NB IoT click

NB IoT click is a Click board™ that allows LTE Cat NB1 connectivity by utilizing Quectel BC95-G, a specialized multi-band IoT module with very low power requirements and compact form factor, making it perfectly suited for various IoT-based applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nbiot_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/nb-iot-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the NbIot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NbIot Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nbiot_cfg_setup ( nbiot_cfg_t *cfg ); 
 
- Initialization function.
> NBIOT_RETVAL nbiot_init ( nbiot_t *ctx, nbiot_cfg_t *cfg );

- Click Default Configuration function.
> void nbiot_default_cfg ( nbiot_t *ctx );


#### Example key functions :

- Send Command function.
> void nbiot_send_command ( nbiot_t *ctx, char *command );
 
- Power up modules.
> void nbiot_module_power ( nbiot_t *ctx );

- Generic write function.
> void nbiot_generic_write ( nbiot_t *ctx, char *data_buf, uint16_t len );

## Examples Description

> This example reads and processes data from NB IoT clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    nbiot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nbiot_cfg_setup( &cfg );
    NBIOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nbiot_init( &nbiot, &cfg );

    nbiot_module_power( &nbiot );
    
    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_AT );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_ATE1 );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_ATI );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_SET_AT_CFUN );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_AT_CIMI );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_TEST_ATAT_CGDCONT );
    nbiot_process(  );

    nbiot_send_command( &nbiot, C5GNBIOT_SINGLE_CMD_GET_AT_CGATT );
    nbiot_process(  );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "--- UDP server - AT command ---\r\n" );

    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NCONFIG );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NCONFIG1 );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NCONFIG2 );
    nbiot_process(  );


    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NBAND );
    nbiot_process(  );

    nbiot_send_command( &nbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CGDCONT_1 );
    nbiot_process(  );


    
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_CEREG );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_COPS ); 
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NSOCR ); 
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NSOST );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NSOCL );
    nbiot_process(  );

    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_AT_CIMI );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NbIot

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

\mainpage Main Page
 
---
# M-BUS RF 4 click

M-BUS RF 4 Click is a mikroBUS™ add-on board with a MIPOT 32001324 RF wireless transceiver. This module operates in the 868 MHz SRD Band. Thanks to its small LCC form factor (15 x 25 mm only) and its low power consumption this module allows the implementation of highly integrated low power (battery operated) solutions for water, gas, heat or electricity metering applications, both on meter or concentrator devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mbusrf4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/m-bus-rf-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the MBusRf4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MBusRf4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mbusrf4_cfg_setup ( mbusrf4_cfg_t *cfg ); 
 
- Initialization function.
> MBUSRF4_RETVAL mbusrf4_init ( mbusrf4_t *ctx, mbusrf4_cfg_t *cfg );


#### Example key functions :

- Header and checksum are calculated and sent at the beginning (header) and finally (checksum)
> void mbusrf4_send_command ( mbusrf4_t *ctx, uint8_t command, uint8_t length, uint8_t *payload_buff );
 
- This function write specific number of data.
> void mbusrf4_generic_write ( mbusrf4_t *ctx, char *data_buf, uint16_t len )

- This function read data of maximum length.
> uint16_t mbusrf4_generic_read ( mbusrf4_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from M-BUS RF 4 clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, reads basic information and checks communication

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusrf4_cfg_t cfg;

    uint8_t payload_buff[ 20 ] = { 0 };

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mbusrf4_cfg_setup( &cfg );
    MBUSRF4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusrf4_init( &mbusrf4, &cfg );

    mbusrf4_process( );

    //Command SET mode
    payload_buff[ 0 ] = MBUSRF4_SET_VALUE_IN_EEPROM_MEMORY;
    payload_buff[ 1 ] = MBUSRF4_EEPARAM_WMBUS_MODE_S2_SHORT_PREAMBLE;

    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_SET_MODE, 2, &payload_buff[ 0 ] );
    mbusrf4_process( );
    Delay_ms( 1500 );
    
    // Reads FW version
    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_GET_FW_VERSION, 0, &payload_buff[ 0 ] );

    log_printf( &logger, " ------ FW Version ------ \r\n" );
    mbusrf4_process( );
    log_printf( &logger, " ------------------------ \r\n" );

    Delay_ms( 3000 );

    // Read EEPROM parameter
    payload_buff[ 0 ] = MBUSRF4_EEADDR_WMBUS_C_FIELD;
    payload_buff[ 1 ] = 0x01;
    
    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_EEPROM_READ, 2, payload_buff );
    
    log_printf( &logger, " ------ EEPROM READ ------ \r\n" );
    mbusrf4_process( );
    log_printf( &logger, " ------------------------- \r\n" );

    Delay_ms( 3000 );
}
  
```

### Application Task

> In the RX mode it is waiting to receive data from another module...
> In the TX mode sends the data packet....

```c

void application_task ( void )
{
    // RX App mode
    #ifdef DEMO_APP_RECEIVER
   
       log_printf ( &logger, " ----- NEW - RX DATA ---- \r\n" );
       mbusrf4_process(  );
       log_printf ( &logger, " ------------------------ \r\n" );

    #endif
    
    // TX App Mode
    #ifdef DEMO_APP_TRANSMITER
    
        mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_TX_MSG, 18, &tx_buffer[ 0 ] );
        log_printf ( &logger, " ----- SEND - TX DATA ---- \r\n" );
        mbusrf4_process(  );
        log_printf ( &logger, " ------------------------ \r\n" );
        
        Delay_ms( 1500 );

    #endif
}

```

## Note

> ## Additional Function
> - mbusrf4_process ( ) - The general process of collecting presponce that sends a module.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MBusRf4

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

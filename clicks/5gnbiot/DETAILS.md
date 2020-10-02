
---
# 5G NB IoT click

5G NB IoT Click is a Click board™ based on Gemalto's Cinterion® ENS22 NB-IoT Wireless Module platform that boosts highly efficient future 5G connectivity for the IoT.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/5g-nb-iot-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the 5gNbIot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 5gNbIot Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c5gnbiot_cfg_setup ( c5gnbiot_cfg_t *cfg ); 
 
- Initialization function.
> C5GNBIOT_RETVAL c5gnbiot_init ( c5gnbiot_t *ctx, c5gnbiot_cfg_t *cfg );

- Click Default Configuration function.
> void c5gnbiot_default_cfg ( c5gnbiot_t *ctx );


#### Example key functions :

- Generic write function.
> void c5gnbiot_generic_write ( c5gnbiot_t *ctx, char *data_buf, uint16_t len );
 
- This function sends comamnd.
> void c5gnbiot_send_command ( c5gnbiot_t *ctx, char *command );

- Power up modules.
> void c5gnbiot_module_power ( c5gnbiot_t *ctx );

## Examples Description

> This example reads and processes data from 5G NB IoT clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c5gnbiot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c5gnbiot_cfg_setup( &cfg );
    C5GNBIOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c5gnbiot_init( &c5gnbiot, &cfg );

    c5gnbiot_module_power( &c5gnbiot );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_AT );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_ATI );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CFUN_1 );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CEREG_2 );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CGDCONT_1 );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_AT_CIMI );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_GET_AT_CGATT );
    c5gnbiot_process( 50 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_GET_AT_CEREG );
    c5gnbiot_process( 50 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.5gNbIot

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

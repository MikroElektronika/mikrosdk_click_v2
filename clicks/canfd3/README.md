\mainpage Main Page
 
---
# CAN FD 3 click

CAN FD 3 Click is a add-on board based on TLE9251V CAN network transceiver, designed for HS CAN networks up to 5 Mbit/s in automotive and industrial applications.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-fd-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the CanFd3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanFd3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void canfd3_cfg_setup ( canfd3_cfg_t *cfg ); 
 
- Initialization function.
> CANFD3_RETVAL canfd3_init ( canfd3_t *ctx, canfd3_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> uint16_t canfd3_generic_read ( canfd3_t *ctx, char *data_buf, uint16_t max_len );
 
- Sets state of pin
> void canfd3_set_cs_pin ( canfd3_t *ctx, uint8_t mode );

- Function for send command.
> void canfd3_send_command ( canfd3_t *ctx, char *command );

## Examples Description

> This example reads and processes data from CAN FD 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    canfd3_cfg_setup( &cfg );
    CANFD3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd3_init( &canfd3, &cfg );

    canfd3_set_cs_pin( &canfd3, CANFD3_MODE_NORMAL );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    canfd3_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    canfd3_process( );
    if ( cnt == 2 )
    {
        canfd3_send_command( &canfd3, TEXT_TO_SEND ); 
        canfd3_process( );
        cnt = 0;
    }
    cnt ++;
#endif    
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd3

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

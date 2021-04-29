\mainpage Main Page
 
---
# CAN FD 3 click

CAN FD 3 Click is a add-on board based on TLE9251V CAN network transceiver, designed for HS CAN networks up to 5 Mbit/s in automotive and industrial applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canfd3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-fd-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the CanFd3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

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
> int32_t canfd3_generic_read ( canfd3_t *ctx, char *data_buf, uint16_t max_len );
 
- Generic write function.
> void canfd3_generic_write ( canfd3_t *ctx, char *data_buf, uint16_t len );

- Sets the CS pin state.
> void canfd3_set_cs_pin ( canfd3_t *ctx, uint8_t mode );

## Examples Description

> This example reads and processes data from CAN FD 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the click board.

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
    Delay_ms( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    canfd3_process( );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd3_generic_write( &canfd3, TEXT_TO_SEND, 8 );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms( 2000 );
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
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---


---
# CAN FD click

CAN FD Click is a add-on board based on TLE9252V CAN network transceiver, designed for HS CAN networks up to 5 Mbit/s in automotive and industrial applications.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-fd-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the CanFd Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanFd Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void canfd_cfg_setup ( canfd_cfg_t *cfg ); 
 
- Initialization function.
> CANFD_RETVAL canfd_init ( canfd_t *ctx, canfd_cfg_t *cfg );

- Click Default Configuration function.
> void canfd_default_cfg ( canfd_t *ctx );


#### Example key functions :

- Sends a command or a piece of data byte by byte.
> void canfd_send_command ( canfd_t *ctx, char *command );
 
- Generic read function.
> uint16_t canfd_generic_read ( canfd_t *ctx, char *data_buf, uint16_t max_len );

- Operation mode.
> void canfd_set_operating_mode ( canfd_t *ctx, uint8_t op_mode );

## Examples Description

> This example reads and processes data from CAN FD clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    canfd_cfg_setup( &cfg );
    CANFD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd_init( &canfd, &cfg );

    Delay_ms( 500 );

   #ifdef TRANSIVER
    
        canfd_set_operating_mode( &canfd, CANFD_OPERATING_MODE_NORMAL );

        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      mikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );

        Delay_ms( 1000 );

    #endif

    #ifdef RECIEVER

        canfd_set_operating_mode( &canfd, CANFD_OPERATING_MODE_RECEIVE );

        log_printf( &logger,  "------------------\r\n" );
        log_printf( &logger, "   Receive data  \r\n " );
        Delay_ms( 2000 );
    
    #endif
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    #ifdef TRANSIVER
    
    canfd_send_command( &canfd, message );
        
    Delay_ms( 2000 );
    
    #endif
     
    #ifdef RECIEVER
    
    canfd_process(  );
     
    #endif

}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd

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

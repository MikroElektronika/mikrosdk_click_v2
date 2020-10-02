\mainpage Main Page
 
---
# CAN FD 2 click

CAN FD 2 Click is a HS CAN transceiver add on board, suitable for evaluation of TLE9255W CAN network transceiver from Infineon.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-fd-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the CanFd2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanFd2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void canfd2_cfg_setup ( canfd2_cfg_t *cfg ); 
 
- Initialization function.
> CANFD2_RETVAL canfd2_init ( canfd2_t *ctx, canfd2_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> uint16_t canfd2_generic_read ( canfd2_t *ctx, char *data_buf, uint16_t max_len );
 
- Generic write the byte of data function
> void canfd2_write_data ( canfd2_t *ctx, uint8_t reg_addr, uint8_t write_data );

- Get operating mode function
> uint8_t canfd2_get_mode ( canfd2_t *ctx );

## Examples Description

> This example reads and processes data from CAN FD 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    canfd2_cfg_setup( &cfg );
    CANFD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd2_init( &canfd2, &cfg );

    Delay_ms( 300 );
    
    log_printf( &logger,  "-------------------\r\n" );
    log_printf( &logger,  "   CAN FD 2 click  \r\n" );
    log_printf( &logger,  "-------------------\r\n" );
    log_printf( &logger,  "--- Initialized ---\r\n" );
    log_printf( &logger,  "-------------------\r\n" );

    
    #ifdef DEMO_APP_RECEIVER

        canfd2_set_mode( &canfd2, CANFD2_OP_MODE_RECEIVE_ONLY );
        log_printf( &logger,  "   RECEIVER MODE   \r\n" );
        log_printf( &logger,  "-------------------\r\n" );

    #endif
    #ifdef DEMO_APP_TRANSMITER

        canfd2_set_mode( &canfd2, CANFD2_OP_MODE_NORMAL );
        log_printf( &logger,  "  TRANSMITER MODE  \r\n" );
        log_printf( &logger,  "-------------------\r\n" );

    #endif
    
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    #ifdef DEMO_APP_RECEIVER

        // RECEIVER - UART polling
        canfd2_process( );

    #endif
    #ifdef DEMO_APP_TRANSMITER

        // TRANSMITER - TX each 2 sec
        canfd2_generic_write( &canfd2, &demo_message_data[ 0 ], 8 );
        Delay_ms( 3000 );

    #endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd2

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

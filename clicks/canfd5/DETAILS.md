
---
# CAN FD 5 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the CanFd5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanFd5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void canfd5_cfg_setup ( canfd5_cfg_t *cfg ); 
 
- Initialization function.
> CANFD5_RETVAL canfd5_init ( canfd5_t *ctx, canfd5_cfg_t *cfg );

#### Example key functions :

- Set WAK pin state function
> uint8_t canfd5_get_cts_pin_state ( canfd5_t *ctx );
 
- Set stand-by operating mode function
> void canfd5_set_standby_operating_mode ( canfd5_t *ctx );

- Set operating mode function
> void canfd5_set_operating_mode ( canfd5_t *ctx, uint8_t op_mode );

## Examples Description

> This is an example that demonstrates the use of the CAN FD 5 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and set mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    canfd5_cfg_setup( &cfg );
    CANFD5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd5_init( &canfd5, &cfg );

    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "  Set Normal Op. Mode  \r\n" );
    canfd5_set_normal_operating_mode( &canfd5 );
    Delay_ms( 100 );
}
  
```

### Application Task

> This application task writes message data via UART every 3 seconds.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, " \r\n" );
    
    canfd5_generic_write( &canfd5, &demo_message_data[ 0 ], 9 );
    
    log_printf( &logger, "  TX Data: %s \r\n", demo_message_data );
    Delay_ms( 3000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd5

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

\mainpage Main Page
 
---
# MUX 3 click

MUX 3 Click is the general purpose multiplexer which offers multiplexing one input channel to eight single-ended output channels. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mux3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mux-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Mux3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mux3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mux3_cfg_setup ( mux3_cfg_t *cfg ); 
 
- Initialization function.
> MUX3_RETVAL mux3_init ( mux3_t *ctx, mux3_cfg_t *cfg );


#### Example key functions :

- Set active MUX channel function
> void mux3_set_channel ( mux3_t *ctx, uint8_t select_channel );

## Examples Description

> This application sets multiplexing one input channel to eight single-ended output channels. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mux3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mux3_cfg_setup( &cfg );
    MUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux3_init( &mux3, &cfg );
}
  
```

### Application Task

> This is an example which demonstrates the use of MUX 3 Click board.
> Sets the current active and changes the channel every 1 sec.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on Usart Terminal changes for every 1 sec.

```c

void application_task ( void )
{
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S1 );
    log_printf( &logger, "Active channel: S1\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S2 );
    log_printf( &logger, "Active channel: S2\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S3 );
    log_printf( &logger, "Active channel: S3\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S4 );
    log_printf( &logger, "Active channel: S4\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S5 );
    log_printf( &logger, "Active channel: S5\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S6 );
    log_printf( &logger, "Active channel: S6\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S7 );
    log_printf( &logger, "Active channel: S7\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S8 );
    log_printf( &logger, "Active channel: S8\r\n" );
    Delay_1sec( );
    
    mux3_set_channel( &mux3, MUX3_DISABLE_ALL_CHANNELS );
    log_printf( &logger, "Active channel: none\r\n" );
    log_printf( &logger, "-------------------\r\n" );
    Delay_1sec( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mux3

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

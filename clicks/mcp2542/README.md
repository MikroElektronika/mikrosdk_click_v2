\mainpage Main Page
 
 

---
# MCP2542 click

MCP2542 click is the CAN bus transceiver, which allows TTL/CMOS level signals typically found on MCUs, to be used for the communication via the CAN bus, which uses the higher voltage levels and differential signals

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp2542_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/mcp2542-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : UART type


# Software Support

We provide a library for the Mcp2542 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp2542 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp2542_cfg_setup ( mcp2542_cfg_t *cfg ); 
 
- Initialization function.
> MCP2542_RETVAL mcp2542_init ( mcp2542_t *ctx, mcp2542_cfg_t *cfg );

- Click Default Configuration function.
> void mcp2542_default_cfg( mcp2542_t *ctx );


#### Example key functions :

- Generic single read function.
> mcp2542_data_t mcp2542_generic_single_read ( mcp2542_t *ctx );
 
- Generic single write function.
> void mcp2542_generic_single_write ( mcp2542_t *ctx, mcp2542_data_t tx_data );

- Generic multi write function.
> void mcp2542_generic_multi_write ( mcp2542_t *ctx, mcp2542_data_t *data_buf,  uart_length_t len );

## Examples Description

> This application use for comunication.

**The demo application is composed of two sections :**

### Application Init 

> Driver intialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp2542_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp2542_cfg_setup( &cfg );
    MCP2542_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp2542_init( &mcp2542, &cfg );

     mcp2542_default_cfg( &mcp2542 );
}
  
```

### Application Task

> Checks if new data byte have received in rx buffer (ready for reading), and if ready than reads one byte from rx buffer. In second case aplication task writes message data via UART.

```c

void application_task ( void )
{
    uint8_t tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp =  mcp2542_generic_single_read( &mcp2542 );
       log_write( &logger, &tmp, LOG_FORMAT_BYTE );
#endif
#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       mcp2542_generic_multi_write( &mcp2542, demo_message, 9 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );
#endif

}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp2542

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

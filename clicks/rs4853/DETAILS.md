
---
# RS 485 3 click

RS485 3 click is an RS422/485 transceiver Click board™, which can be used as an interface between the TTL level UART and the RS422/485 communication bus. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs4853_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs485-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs4853 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs4853 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs4853_cfg_setup ( rs4853_cfg_t *cfg ); 
 
- Initialization function.
> RS4853_RETVAL rs4853_init ( rs4853_t *ctx, rs4853_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void rs4853_generic_write ( rs4853_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> uint16_t rs4853_generic_read ( rs4853_t *ctx, char *data_buf, uint16_t max_len );

- Function ofr send command
> void rs4853_send_command ( rs4853_t *ctx, char *command );

## Examples Description

> This application is used to communicate between two RS485 clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4853_cfg_t cfg;

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

    rs4853_cfg_setup( &cfg );
    RS4853_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4853_init( &rs4853, &cfg );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4853_process( );
#endif    

#ifdef DEMO_APP_TRANSMITER
    rs4853_send_command( &rs4853, TEXT_TO_SEND );
    rs4853_process( );
    Delay_ms( 2000 );
#endif     
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs4853

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

\mainpage Main Page
 
---
# RS232 Isolator click

RS232 Isolator click is a fully isolated dual transceiver click, used to provide secure and easy UART to RS232 conversion, with the galvanic isolation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs232isolator_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs232-isolator-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs232Isolator Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs232Isolator Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs232isolator_cfg_setup ( rs232isolator_cfg_t *cfg ); 
 
- Initialization function.
> RS232ISOLATOR_RETVAL rs232isolator_init ( rs232isolator_t *ctx, rs232isolator_cfg_t *cfg );

#### Example key functions :

- Function settings RTS state.
> void rs232_2_set_rts ( rs232isolator_t *ctx, uint8_t state );
 
- Read CTS state.
> uint8_t rs232_2_get_cts ( rs232isolator_t *ctx );

- Function for send command.
> void rs232isolator_send_command ( rs232isolator_t *ctx, char *command );

## Examples Description

> This example reads and processes data from RS232 Isolator clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs232isolator_cfg_t cfg;

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

    rs232isolator_cfg_setup( &cfg );
    RS232ISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232isolator_init( &rs232isolator, &cfg );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs232isolator_process( );
#endif
    
#ifdef DEMO_APP_TRANSMITER
    rs232isolator_send_command( &rs232isolator, TEXT_TO_SEND );
    rs232isolator_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif    
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232Isolator

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

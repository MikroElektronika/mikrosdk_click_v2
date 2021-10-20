
---
# RS485 4 click

RS485 4 Click offers an UART to RS485 signal conversion, featuring the ADM2795E specialized IC with the complete galvanic isolation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs4854_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs485-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs4854 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs4854 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs4854_cfg_setup ( rs4854_cfg_t *cfg ); 
 
- Initialization function.
> RS4854_RETVAL rs4854_init ( rs4854_t *ctx, rs4854_cfg_t *cfg );

#### Example key functions :

- Rx disable function.
> void rs4854_rx_disable ( rs4854_t *ctx );
 
- Tx enable function.
> void rs4854_tx_enable ( rs4854_t *ctx );

- Function for send command
> void rs4854_send_command ( rs4854_t *ctx, char *command );

## Examples Description

> This example reads and processes data from RS485 4 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4854_cfg_t cfg;

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

    rs4854_cfg_setup( &cfg );
    RS4854_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4854_init( &rs4854, &cfg );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4854_process( );
#endif    

#ifdef DEMO_APP_TRANSMITER
    rs4854_send_command( &rs4854, TEXT_TO_SEND );
    rs4854_process( );
    Delay_ms( 2000 );
#endif    
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs4854

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

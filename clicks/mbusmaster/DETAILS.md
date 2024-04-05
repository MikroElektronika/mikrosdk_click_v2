
---
# M Bus Master click

The M-Bus Master is a Click board™ is complete solution for a master node in M-Bus networks.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mbusmaster_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/m-bus-master-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : UART type


# Software Support

We provide a library for the MBusMaster Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MBusMaster Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mbusmaster_cfg_setup ( mbusmaster_cfg_t *cfg ); 
 
- Initialization function.
> MBUSMASTER_RETVAL mbusmaster_init ( mbusmaster_t *ctx, mbusmaster_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void mbusmaster_generic_write ( mbusmaster_t *ctx, char *data_buf, uint16_t len );

- Generic read function.
> int32_t mbusmaster_generic_read ( mbusmaster_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from M-Bus Master clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusmaster_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    mbusmaster_cfg_setup( &cfg );
    MBUSMASTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusmaster_init( &mbusmaster, &cfg );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    mbusmaster_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    mbusmaster_generic_write( &mbusmaster, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif  
}  

```

## Note

> M-Bus master communication works at 36v.
> This click acts only as 'master', therefore it must be connected to appropriate 'slave'.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MBusMaster

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

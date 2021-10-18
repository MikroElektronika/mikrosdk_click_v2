
---
# USB UART 3 click

USB UART 3 click is a versatile and feature-rich USB to UART interface from Silicon Labs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbuart3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-uart-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the UsbUart3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UsbUart3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void usbuart3_cfg_setup ( usbuart3_cfg_t *cfg ); 
 
- Initialization function.
> USBUART3_RETVAL usbuart3_init ( usbuart3_t *ctx, usbuart3_cfg_t *cfg );

#### Example key functions :

- Function for reset
> void usbuart3_reset ( usbuart3_t *ctx );
 
- Set device mode
> uint8_t usbuart3_get_susp ( usbuart3_t *ctx );

- Function for send command
> void usbuart3_send_command ( usbuart3_t *ctx, char *command );

## Examples Description

> This example reads and processes data from USB UART 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    usbuart3_cfg_t cfg;

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

    usbuart3_cfg_setup( &cfg );
    USBUART3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    usbuart3_init( &usbuart3, &cfg );
    
    usbuart3_reset( &usbuart3 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    rsp_size = usbuart3_generic_read( &usbuart3, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        usbuart3_generic_write( &usbuart3, uart_rx_buffer, rsp_size );
        log_printf( &logger, "%s", uart_rx_buffer );
        memset( uart_rx_buffer, 0, rsp_size );
    } 
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UsbUart3

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


---
# RS232 click

RS232 click provides an interface between the TTL/CMOS logic levels commonly used on microcontrollers and the RS-232 bus.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs232_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs232-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs232 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs232 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs232_cfg_setup ( rs232_cfg_t *cfg ); 
 
- Initialization function.
> RS232_RETVAL rs232_init ( rs232_t *ctx, rs232_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void rs232_generic_write ( rs232_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> int32_t rs232_generic_read ( rs232_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from RS232 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs232_cfg_t cfg;

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

    rs232_cfg_setup( &cfg );
    RS232_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232_init( &rs232, &cfg );
    
    Delay_ms ( 100 );
#ifdef RS232_RECEIVER
    log_printf( &logger, " ** RS232 Receiver **\r\n" );
#endif
    
#ifdef RS232_TRANSMITTER
    log_printf( &logger, " ** RS232 Transmitter **\r\n" );
#endif
}
  
```

### Application Task

> Depending on the selected mode (receiver/transmitter) this function reads/sends an appropriate message.
> All data is displayed on USB UART.

```c

void application_task ( void )
{
#ifdef RS232_RECEIVER
    rsp_size = rs232_generic_read( &rs232, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size == strlen( message ) )
    {  
        log_printf( &logger, "Message received: %s", uart_rx_buffer );
        log_printf( &logger, "\r\n-------------------------\r\n" );
        memset( uart_rx_buffer, 0, rsp_size );
    }  
    Delay_ms ( 100 );
#endif
    
#ifdef RS232_TRANSMITTER
    rs232_generic_write( &rs232, message, strlen( message ) );
    log_printf( &logger, "Message sent: %s", message );
    log_printf( &logger, "\r\n-------------------------\r\n" );
    Delay_ms ( 1000 );
#endif   
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232

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

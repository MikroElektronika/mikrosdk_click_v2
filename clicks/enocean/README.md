\mainpage Main Page
 
---
# EnOcean click

EnOcean click carries a TCM 310 transceiver, which is a bidirectional gateway for EnOcean’s 868 MHz radio systems. The click is designed to run on a 3.3V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/enocean_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/enocean-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the enOcean Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for enOcean Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void enocean_cfg_setup ( enocean_cfg_t *cfg ); 
 
- Initialization function.
> ENOCEAN_RETVAL enocean_init ( enocean_t *ctx, enocean_cfg_t *cfg );

#### Example key functions :

- Response Ready function
> uint8_t enocean_response_ready( enocean_t *ctx );
 
- UART Interrupt Routine function
> void enocean_uart_isr( enocean_t *ctx );

- Packet Send function.
> uint8_t enocean_send_packet( enocean_t *ctx, enocean_packet_t *packet );

## Examples Description

> This example reads and processes data from EnOcean clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and sets the driver handler.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean_cfg_t cfg;

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

    enocean_cfg_setup( &cfg );
    ENOCEAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean_init( &enocean, &cfg );

    Delay_ms( 500 );
    
    enocean_response_handler_set( &enocean, &make_response );
}
  
```

### Application Task

> Reads the received data and parses it on the USB UART if the response buffer is ready.

```c

void application_task ( void )
{
    enocean_uart_isr ( &enocean );
    check_response ( );
    Delay_1ms( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.EnOcean

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

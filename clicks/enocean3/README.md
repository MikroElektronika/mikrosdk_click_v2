\mainpage Main Page
 
---
# EnOcean 3 Click

EnOcean 3 Click carries an ultra-low power TCM515 transceiver gateway module which operates at 868MHz radio band, perfectly suited for the realization of transceiver gateways, actuators and controllers for systems communicating based on the EnOcean radio standard.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/enocean3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/enocean-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Enocean3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Enocean3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void enocan3_cfg_setup ( enocan3_cfg_t *cfg ); 
 
- Initialization function.
> ENOCEAN3_RETVAL enocan3_init ( enocan3_t *ctx, enocan3_cfg_t *cfg );

#### Example key functions :

- UART Interrupt Routine function
> void enocean3_uart_isr( enocean3_t *ctx );
 
- Handler Set function.
> void enocean3_response_handler_set ( enocan3_t *ctx, enocean3_hdl_t handler );

- Packet Send function.
> uint8_t enocean3_send_packet( enocan3_t *ctx, enocean3_packet_t *packet );

## Examples Description

> This example reads and processes data from EnOcean 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and sets the driver handler.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean3_cfg_t cfg;

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

    enocean3_cfg_setup( &cfg );
    ENOCEAN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean3_init( &enocean3, &cfg );

    Delay_ms ( 500 );

    enocean3_response_handler_set( &enocean3, &make_response );
    rsp_check = 1;
}
  
```

### Application Task

> Reads the received data and parses it on the USB UART if the response buffer is ready.

```c

void application_task ( void )
{
    enocean3_uart_isr ( &enocean3 );
    check_response ( );
    Delay_1ms( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Enocean3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

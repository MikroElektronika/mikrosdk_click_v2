
---
# EnOcean 2 click

EnOcean 2 click carries the TCM 515Z transceiver, based on the 2.4 GHz IEEE 802.15.4 radio standard. The click is designed to run on a 3.3V power supply. It communicates with the target microcontroller over UART interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/enocean2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/enocean-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the EnOcean2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for EnOcean2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void enocean2_cfg_setup ( enocean2_cfg_t *cfg ); 
 
- Initialization function.
> ENOCEAN2_RETVAL enocean2_init ( enocean2_t *ctx, enocean2_cfg_t *cfg );


#### Example key functions :

- EnOcean Serial Protocol ( ESP3 ) module initialization.
> void enocean2_init_rx_buff ( enocean2_t *ctx, enocean2_ring_buffer_t *rb, enocean2_rx_data_t *rx_str );
 
- The function push recieved character to ring buffer.
> uint8_t enocean2_rx ( enocean2_ring_buffer_t *rb, uint8_t rx_data );

- Implements state machine for recieving packets. It should be called in loop.
> uint8_t enocean2_packet_recieve ( enocean2_t *ctx, enocean2_ring_buffer_t *rb );

## Examples Description

> This example reads and processes data from EnOcean 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and initializes chip and sets callback handler.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    enocean2_cfg_setup( &cfg );
    ENOCEAN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean2_init( &enocean2, &cfg );

    enocean2_rx.rx_buffer   = &rx_buffer[ 0 ];
    enocean2_rx.rx_size     = ENOCEAN2_RX_BUFFER_SIZE;
    enocean2_rx.data_buffer = &data_buffer[ 0 ];
    enocean2_rx.data_size   = ENOCEAN2_RX_BUFFER_SIZE;

    enocean2_init_rx_buff( &enocean2, &enocean2_rb, &enocean2_rx );
    enocean2_set_callback_handler( &enocean2, callback_handler );
}
  
```

### Application Task

> It checks if a switch is pressed, and logs an appropriate message to the uart terminal.

```c

void application_task ( void )
{
    enocean2_process( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.EnOcean2

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

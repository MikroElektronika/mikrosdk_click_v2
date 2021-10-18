
---
# Nano LR click

Nano LR Click is a compact add-on board that contains a long-range transceiver. This board features the EMB-LR1276S, RF technology-based SRD transceiver, which operates at a frequency of 868MHz from Embit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanolr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nano-lr-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the NanoLR Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NanoLR Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nanolr_cfg_setup ( nanolr_cfg_t *cfg ); 
 
- Initialization function.
> NANOLR_RETVAL nanolr_init ( nanolr_t *ctx, nanolr_cfg_t *cfg );

- Click Default Configuration function.
> void nanolr_default_cfg ( nanolr_t *ctx );


#### Example key functions :

- This function sends data command depends on the chosen network protocol.
> void nanolr_send_data ( nanolr_t *ctx, uint8_t *tx_data, uint8_t length );
 
- This function reads response bytes from the device and sets flag after each received byte.
> void nanolr_uart_isr ( nanolr_t *ctx );

- This function checks if the response is ready.
> uint8_t nanolr_rsp_rdy ( nanolr_t *ctx );

## Examples Description

> This example reads and processes data from Nano LR clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanolr_cfg_t cfg;

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

    nanolr_cfg_setup( &cfg );
    NANOLR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanolr_init( &nanolr, &cfg );

    nanolr_default_cfg( &nanolr );

    log_printf( &logger,  "----  Nano LR Click ----\r\n" );

#ifdef DEMO_APP_RECEIVER
    log_printf( &logger,  "---- RECEIVER MODE ----\r\n" );
#endif
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger,  "---- TRANSMITER MODE ----\r\n" );
#endif 
    Delay_ms( 2000 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends a desired message
> every 2 seconds. All data is being displayed on the USB UART.

```c

void application_task ( void )
{    
#ifdef DEMO_APP_RECEIVER
    nanolr_process( );
#endif

#ifdef DEMO_APP_TRANSMITTER
    nanolr_send_data( &nanolr, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, "The message \"%s\" has been sent!\r\n", ( uint8_t * ) TEXT_TO_SEND );
    log_printf( &logger, "------------------------------------------------------------\r\n" );
    Delay_ms( 2000 );
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoLR

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

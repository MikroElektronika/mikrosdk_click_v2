\mainpage Main Page

---
# IrDA click

IrDA click is a compact and easy solution for adding infrared communication to your device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/IrDa-group-click.png" height=300px>
</p>

> - [IrDa 2 click - Product page](<https://www.mikroe.com/irda2-click>)
> - [IrDa 3 click - Product page](<https://www.mikroe.com/irda-3-click>)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : UART type


# Software Support

We provide a library for the Irda Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for IrDA Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void irda_cfg_setup( irda_cfg_t *cfg );
 
- Click Initialization function.
> irda_err_t irda_init( irda_t *ctx, irda_cfg_t *cfg );

- Click Default Configuration function.
> void irda_default_cfg( irda_t *ctx );

#### Example key functions :

- Generic Single Send function.
> void irda_generic_single_send( irda_t *ctx, uart_data_t tx_data );

- Generic Multiple Receive function.
> void irda_generic_multiple_receive( irda_t *ctx, uart_data_t *rx_data, uart_data_t termination_char );

- Data Ready function.
> bool irda_data_ready( irda_t *ctx );

## Examples Description

> This example demonstrates the use of IrDA Click board.
> The example can perform both roles, transceiver and receiver.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART driver and all used control pins.
> Also clears the response buffer.

```c

void application_init( void )
{
    irda_cfg_t irda_cfg;
    log_cfg_t console_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( console_cfg );
    console_cfg.level = LOG_LEVEL_DEBUG;
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_printf( &console, "***  IrDA initialization done  ***\r\n" );
    log_printf( &console, "**********************************\r\n" );

    //  Click initialization.
    irda_cfg_setup( &irda_cfg );
    IRDA_MAP_MIKROBUS( irda_cfg, MIKROBUS_1 );
    irda_init( &irda, &irda_cfg );
    irda_default_cfg( &irda );
    irda_reset( &irda );

    //  Clear response.
    memset( rx_message, 0, sizeof( rx_message ) );
}

```

### Application Task

> Demonstrates the use of IrDA click which can be used as transceiver or receiver.
> A message bytes can be send and receive all at once or byte to byte.

```c

void application_task( void )
{

#ifdef DEMO_APP_RECEIVER_1

    rx_message[ 0 ] = irda_generic_single_receive( &irda );

    log_printf( &console, "%c", ( char ) rx_message[ 0 ] );
    Delay_ms( 100 );

#endif

#ifdef DEMO_APP_RECEIVER_2

    irda_generic_multiple_receive( &irda, rx_message, '\n' );

    log_printf( &console, "RECEIVED MESSAGE : " );
    log_printf( &console, "%s\r\n", rx_message );
    Delay_ms( 100 );

#endif
    
#ifdef DEMO_APP_TRANSCEIVER_1

    irda_generic_multiple_send( &irda, tx_message );

    log_printf( &console, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif
    
#ifdef DEMO_APP_TRANSCEIVER_2

    idx = 0;

    while ( tx_message[ idx ] != '\0' )
    {
        irda_generic_single_send( &irda, tx_message[ idx++ ] );
    }

    log_printf( &console, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif

}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Irda

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

\mainpage Main Page
 
 

---
# CAN Isolator click

CAN Isolator click provides isolated CAN communication. It carries the ADM3053 signal and power isolated CAN transceiver with an integrated isolated DC-to-DC converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canisolator_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-isolator-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : UART type


# Software Support

We provide a library for the CanIsolator Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanIsolator Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void canisolator_cfg_setup ( canisolator_cfg_t *cfg ); 
 
- Initialization function.
> CANISOLATOR_RETVAL canisolator_init ( canisolator_t *ctx, canisolator_cfg_t *cfg );

- Click Default Configuration function.
> void canisolator_default_cfg ( canisolator_t *ctx );


#### Example key functions :

- Generic multi write function.
> void canisolator_generic_multi_write ( canisolator_t *ctx, canisolator_data_t *data_buf,  uart_length_t len );
 
- Generic multi read function.
> void canisolator_generic_multi_read ( canisolator_t *ctx, canisolator_data_t *data_buf,  uart_length_t len );

- Generic single read function.
> canisolator_data_t canisolator_generic_single_read ( canisolator_t *ctx );

- Generic single write function.
> void canisolator_generic_single_write ( canisolator_t *ctx, canisolator_data_t tx_data );

## Examples Description

> 
> This is a example which demonstrates the use of Can Isolator Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canisolator_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    canisolator_cfg_setup( &cfg );
    CANISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canisolator_init( &canisolator, &cfg );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, " CAN Isolator  Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

>
> Checks if new data byte has received in RX buffer ( ready for reading )
> and if ready than reads one byte from RX buffer.
> In the second case, the application task writes message data via UART.
> Results are being sent to the Usart Terminal where you can track their changes.
> 

```c

void application_task ( void )
{
    canisolator_data_t tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  canisolator_generic_single_read( &canisolator );
    log_printf( &logger, " %c ", tmp );
    
#endif
#ifdef DEMO_APP_TRANSMITER

    // TRANSMITER - TX each 2 sec
    
    uint8_t cnt;
        
    for ( cnt = 0; cnt < 9; cnt ++ )
    {
        canisolator_generic_single_write( &canisolator, demo_message[ cnt ] );
        Delay_ms ( 100 );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
#endif

}

```

## Note



The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanIsolator

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

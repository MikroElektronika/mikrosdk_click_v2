
---
# ccRF 2 click

ccRF2 click carries CC1120, the fully integrated, high-performance single-chip radio transceiver with extremely low power consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ccrf2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ccrf-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the ccRf2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ccRf2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ccrf2_cfg_setup ( ccrf2_cfg_t *cfg ); 
 
- Initialization function.
> CCRF2_RETVAL ccrf2_init ( ccrf2_t *ctx, ccrf2_cfg_t *cfg );

- Click Default Configuration function.
> void ccrf2_default_cfg ( ccrf2_t *ctx );


#### Example key functions :

- Function receives RX data from the transmit module of the CC1120 single-chip radio transceiver.
> uint8_t ccrf2_receive_rx_data ( ccrf2_t *ctx, uint8_t *rx_data );
 
- Function sends TX data to the receive module of the CC1120 single-chip radio transceiver.
> void ccrf2_send_tx_data ( ccrf2_t *ctx, uint8_t *tx_data, uint8_t n_bytes );

- Function sets RX mode of the CC1120 single-chip radio transceiver on the ccRF 2 Click board.
> void ccrf2_set_rx_mode ( ccrf2_t *ctx );

## Examples Description

> This example demonstrates the use of ccRF 2 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, performs the default configuration and enables the selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf2_cfg_t cfg;

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

    ccrf2_cfg_setup( &cfg );
    CCRF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf2_init( &ccrf2, &cfg );
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Hardware reset\r\n" );
    ccrf2_hw_reset( &ccrf2 );
    Delay_ms( 1000 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Default config\r\n" );
    ccrf2_default_cfg( &ccrf2 );
    Delay_ms( 1000 );

    log_printf( &logger, "----------------------\r\n" );

#ifdef DEMO_APP_RECEIVER
    ccrf2_set_rx_mode( &ccrf2 );
    
    log_printf( &logger, " Receiver mode\r\n" );
#endif
#ifdef DEMO_APP_TRANSMITTER
    ccrf2_set_tx_mode( &ccrf2 );
    
    log_printf( &logger, " Transmitter mode\r\n" );
#endif

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads the received data or sends the desired message
> every 2 seconds. All data is being logged on the USB UART where you can track their changes.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    uint8_t num_bytes = ccrf2_receive_rx_data( &ccrf2, &rx_buffer[ 0 ] );
    if ( num_bytes )
    {
        log_printf( &logger, " Received message: " );
        for ( uint8_t cnt = 3; cnt < rx_buffer[ 0 ]; cnt++ )
        {
            log_printf( &logger, "%c", rx_buffer[ cnt ] );
        }
        log_printf( &logger, " Packet number: %u", ccrf2.packet_counter );
        log_printf( &logger, "\r\n----------------------\r\n" );
    }
#endif
#ifdef DEMO_APP_TRANSMITTER
    ccrf2_send_tx_data( &ccrf2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, " Sent message: MikroE\r\n" );
    log_printf( &logger, " Packet number: %u\r\n", ccrf2.packet_counter );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 2000 );
#endif
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ccRf2

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

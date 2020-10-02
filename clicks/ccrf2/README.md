\mainpage Main Page
 
---
# ccRF2 click

ccRF2 click carries CC1120, the fully integrated, high-performance single-chip radio transceiver with extremely low power consumption.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ccrf2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ccrf-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the ccRf2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

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

- Function receive RX data from the transmit module of the CC1120 single-chip radio transceiver.
> void ccrf2_receive_rx_data ( ccrf2_t *ctx, uint8_t *rx_data );
 
- Function send TX data to the receive module of the CC1120 single-chip radio transceiver.
> void ccrf2_send_tx_data ( ccrf2_t *ctx, uint8_t *tx_data, uint8_t n_bytes );

- Function manual calibration the CC1120 single-chip radio transceiver on the ccRF 2 Click board.
> void ccrf2_manual_calibration ( ccrf2_t *ctx );

## Examples Description

> This click carries CC1120, single-chip radio transceiver. Designed mainly for the ISM 
> (Industrial, Scientific, and Medical) and SRD (Short Range Device) frequency bands at 
> 820–960 MHz, CC1120 provides extensive hardware support for packet handling, data buffering, 
> burst transmissions, clear channel assessment, link quality indication, and Wake-On-Radio. 
> It also has exceptional receiver sensibility. ccRF2 click communicates with the target board 
> through SPI (MISO, MOSI, CSK), and AN, RST, CS, PWM and INT lines.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI, hardware reset chip, sets default configuration, 
> sets manual calibration, sets operation mode, also write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ccrf2_cfg_setup( &cfg );
    CCRF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf2_init( &ccrf2, &cfg );
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "    Hardware reset    \r\n" );
    ccrf2_hw_reset( &ccrf2 );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Set Default Config.  \r\n" );
    ccrf2_default_cfg( &ccrf2 );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "  Manual Calibration  \r\n" );
    ccrf2_manual_calibration( &ccrf2 );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "    Operation Mode:   \r\n" );
    mode_selected = CCRF2_IDLE_MODE;

    switch ( mode_selected )
    {
        case CCRF2_TX_MODE :
        {
            ccrf2_set_tx_mode( &ccrf2 );
            send_flag = 1;

            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF2_RX_MODE :
        {
            ccrf2_set_rx_mode( &ccrf2 );
            receive_flag = 1;

            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF2_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example which demonstrates the use of ccRF 2 click board.
> If RX mode selected, checks if new data byte has received in RX buffer ( ready for reading ),
> and if ready than reads one byte from RX buffer.
> In the second case, the application task writes received message data via UART.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    mode_selected = CCRF2_TX_MODE;

    switch ( mode_selected )
    {
        case CCRF2_TX_MODE :
        {
            send_flag = 0;
            reading_flag = 0;
            Delay_ms( 200 );
            ccrf2_set_tx_mode( &ccrf2 );
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF2_RX_MODE :
        {
            receive_flag = 0;
            ccrf2_set_rx_mode( &ccrf2 );
            reading_flag = 1;
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF2_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    switch( mode_selected )
    {
        case CCRF2_TX_MODE :
        {
            ccrf2_send_tx_data( &ccrf2, &tx_buffer[ 0 ], 9 );
            length_tx = sizeof( tx_buffer );

            for ( cnt = 0; cnt < length_tx; cnt++ )
            {
                log_printf( &logger, " tx_buffer[ %d ]= %c\r\n", cnt, tx_buffer[ cnt ] );
            }

            Delay_ms( 1000 );
            log_printf( &logger, "----------------------\r\n" );
            break;
        }
        case CCRF2_RX_MODE :
        {
            if ( reading_flag )
            {
                ccrf2_receive_rx_data( &ccrf2, &rx_buffer[ 0 ] );
                length_rx = sizeof( rx_buffer );

                for ( cnt = 0; cnt < length_rx; cnt++ )
                {
                    log_printf( &logger, " rx_buffer[ %d ]= %d\r\n", cnt, rx_buffer[ cnt ] );
                    Delay_ms( 200 );
                }

                Delay_ms( 1000 );
                log_printf( &logger, "----------------------\r\n" );
                Delay_ms( 200 );
            }
            break;
        }
    }
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ccRf2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

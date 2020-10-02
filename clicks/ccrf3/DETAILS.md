
---
# ccRF 3 click

ccRF 3 click carries the CC1120 high-performance RF transceiver for narrowband systems from Texas Instruments. The clicks will enable you to add a low-power consumption radio transceiver at 433 MHz frequency. ccRF 3 click is designed to run on a 3.3V power supply. It communicates with the target microcontroller over SPI interface.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ccrf3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ccrf-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the ccRf3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ccRf3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ccrf3_cfg_setup ( ccrf3_cfg_t *cfg ); 
 
- Initialization function.
> CCRF3_RETVAL ccrf3_init ( ccrf3_t *ctx, ccrf3_cfg_t *cfg );

- Click Default Configuration function.
> void ccrf3_default_cfg ( ccrf3_t *ctx );


#### Example key functions :

- Function set TX mode of the CC1120 single-chip radio transceiver on the ccRF 3 Click board.
> void ccrf3_set_tx_mode ( ccrf3_t *ctx );
 
- Function set TX mode of the CC1120 single-chip radio transceiver on the ccRF 3 Click board.
> void ccrf3_set_rx_mode ( ccrf3_t *ctx );

- Function send TX data to the receive module of the CC1120 single-chip radio transceiver on the ccRF 3 Click board.
> void ccrf3_send_tx_data ( ccrf3_t *ctx, uint8_t *tx_data, uint8_t n_bytes );

## Examples Description

> The clicks will enable you to add a low-power consumption radio transceiver at 433 MHz 
> frequency. ccRF 3 click is designed to run on a 3.3V power supply. It communicates with 
> the target microcontroller over SPI interface. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI,
> hardware reset chip, sets default configuration, sets manual calibration, 
> sets operation mode, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ccrf3_cfg_setup( &cfg );
    CCRF3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf3_init( &ccrf3, &cfg );

    log_printf( &logger, "    Hardware reset    \r\n" );
    ccrf3_hw_reset( &ccrf3 );
    Delay_ms( 100 );

    log_printf( &logger, " Set Default Config.  \r\n" );
    ccrf3_default_cfg( &ccrf3 );
    Delay_ms( 100 );

    log_printf( &logger, "  Manual Calibration  \r\n" );
    ccrf3_manual_calibration( &ccrf3 );
    Delay_ms( 100 );

    log_printf( &logger, "    Operation Mode:   \r\n" );
    mode_selected = CCRF3_IDLE_MODE;

    switch ( mode_selected )
    {
        case CCRF3_TX_MODE :
        {
            ccrf3_set_tx_mode( &ccrf3 );
            send_flag = 1;

            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF3_RX_MODE :
        {
            ccrf3_set_rx_mode( &ccrf3 );
            receive_flag = 1;

            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF3_IDLE_MODE :
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

> This is an example which demonstrates the use of ccRF 3 click board.
> If RX mode selected, checks if new data byte has received in RX buffer ( ready for reading ),
> and if ready than reads one byte from RX buffer.
> In the second case, the application task writes received message data via UART.
> Results are being sent to the Usart Terminal where you can track their changes.
   

```c

void application_task ( void )
{
    mode_selected = CCRF3_TX_MODE;

    switch ( mode_selected )
    {
        case CCRF3_TX_MODE :
        {
            send_flag = 0;
            reading_flag = 0;
            Delay_ms( 200 );
            ccrf3_set_tx_mode( &ccrf3 );
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF3_RX_MODE :
        {
            receive_flag = 0;
            ccrf3_set_rx_mode( &ccrf3 );
            reading_flag = 1;
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF3_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    switch( mode_selected )
    {
        case CCRF3_TX_MODE :
        {
            ccrf3_send_tx_data( &ccrf3, &tx_buffer[ 0 ], 9 );
            length_tx = sizeof( tx_buffer );

            for ( cnt = 0; cnt < length_tx; cnt++ )
            {
                log_printf( &logger, " tx_buffer[ %d ]= %d\r\n", cnt, tx_buffer[ cnt ] );
            }

            Delay_ms( 1000 );
            log_printf( &logger, "----------------------\r\n" );
            break;
        }
        case CCRF3_RX_MODE :
        {
            if ( reading_flag )
            {
                ccrf3_receive_rx_data( &ccrf3, &rx_buffer[ 0 ] );
                length_rx = sizeof( rx_buffer );

                for ( cnt = 0; cnt < length_rx; cnt++ )
                {
                    log_printf( &logger, " rx_buffer[ %d ]= %d\r\n", cnt, rx_buffer[ cnt ] );
                }

                Delay_ms( 1000 );
                log_printf( &logger, "----------------------\r\n" );
            }
            break;
        }
    }
}  

```

## Note

> 
> <NOTE>
> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ccRf3

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

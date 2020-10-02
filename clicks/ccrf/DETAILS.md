
---
# ccRF click

ccRF click is a low-power 2.4 GHz transceiver designed for the 2400- 2483.5 MHz ISM and SRD frequency bands. It features CC2500 Low-Power 2.4 GHz RF transceiver as well as PCB trace antenna. The CC2500 is integrated with a highly configurable baseband modem that supports various modulation formats and has data rate up to 500 kBaud.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ccrf_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ccrf-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the ccRf Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ccRf Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ccrf_cfg_setup ( ccrf_cfg_t *cfg ); 
 
- Initialization function.
> CCRF_RETVAL ccrf_init ( ccrf_t *ctx, ccrf_cfg_t *cfg );

- Click Default Configuration function.
> void ccrf_default_cfg ( ccrf_t *ctx );


#### Example key functions :

- Function transmit a packet with packet length up to 63 bytes to the targeted 8-bit register address
> void ccrf_transmit_packet ( ccrf_t *ctx, uint8_t *tx_buffer, uint8_t n_bytes );
 
- Function receive a packet of variable packet length ( first byte in the packet must be the length byte )
> uint8_t ccrf_receive_packet ( ccrf_t *ctx, uint8_t *rx_buffer, uint8_t *length_buff );

- Function for getting state of GD0 pin function
> uint8_t ccrf_get_start( ctx );

## Examples Description

> ccRF click communicates with the target microcontroller via mikroBUS SPI, RST and PWM lines.
> It features Low-Power RF transceiver as well as PCB trace antenna. Maximum device range is 
> up to 20 meters in open space. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI,
> hardware reset chip, sets default configuration, sets operation mode, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ccrf_cfg_setup( &cfg );
    CCRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf_init( &ccrf, &cfg );

    log_printf( &logger, "    Hardware reset    \r\n" );
    ccrf_hw_reset( &ccrf );
    Delay_ms( 100 );
    
    ccrf_sw_reset( &ccrf );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Default Config.  \r\n" );
    ccrf_default_cfg( &ccrf );
    Delay_ms( 100 );
    ccrf_write_byte( &ccrf, CCRF_PATABLE, 0xFE );
    Delay_ms( 100 );
    
    log_printf( &logger, "    Operation Mode:   \r\n" );
    mode_selected = CCRF_IDLE_MODE;

    switch ( mode_selected )
    {
        case CCRF_TX_MODE :
        {
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF_RX_MODE :
        {
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF_IDLE_MODE :
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

> This is an example which demonstrates the use of ccRF click board.
> If RX mode selected, checks if new data byte has received in RX buffer ( ready for reading ),
> and if ready than reads one byte from RX buffer.
> In the second case, the application task writes received message data via UART.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    mode_selected = CCRF_RX_MODE;

    switch ( mode_selected )
    {
        case CCRF_TX_MODE :
        {
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF_RX_MODE :
        {
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    switch( mode_selected )
    {
        case CCRF_TX_MODE :
        {
            length_tx = sizeof( tx_buffer );

            ccrf_transmit_packet( &ccrf, &tx_buffer[ 0 ], length_tx );

            Delay_ms( 1000 );
            break;
        }
        case CCRF_RX_MODE :
        {
            length_rx = sizeof( rx_buffer );

            if ( ccrf_receive_packet( &ccrf, &rx_buffer[ 0 ], &length_rx ) )
            {
                for ( cnt = 0; cnt < length_rx; cnt++ )
                {
                    log_printf( &logger, " rx_buffer[ %d ] = %c \r\n",  cnt, rx_buffer[ cnt ] );
                }

                log_printf( &logger, "----------------------\r\n" );
                Delay_ms( 1000 );
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
- Click.ccRf

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

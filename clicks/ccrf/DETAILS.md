
---
# ccRF Click

> ccRF Click is a low-power 2.4 GHz transceiver designed for the 2400- 2483.5 MHz ISM and SRD frequency bands. It features CC2500 Low-Power 2.4 GHz RF transceiver as well as PCB trace antenna. The CC2500 is integrated with a highly configurable baseband modem that supports various modulation formats and has data rate up to 500 kBaud.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ccrf_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ccrf-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the ccRf Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ccRf Click driver.

#### Standard key functions :

- `ccrf_cfg_setup` Config Object Initialization function.
```c
void ccrf_cfg_setup ( ccrf_cfg_t *cfg ); 
```

- `ccrf_init` Initialization function.
```c
err_t ccrf_init ( ccrf_t *ctx, ccrf_cfg_t *cfg );
```

- `ccrf_default_cfg` Click Default Configuration function.
```c
void ccrf_default_cfg ( ccrf_t *ctx );
```

#### Example key functions :

- `ccrf_transmit_packet` Function transmit a packet with packet length up to 63 bytes to the targeted 8-bit register address.
```c
void ccrf_transmit_packet ( ccrf_t *ctx, uint8_t *tx_buffer, uint8_t n_bytes );
```

- `ccrf_receive_packet` Function receive a packet of variable packet length.
```c
uint8_t ccrf_receive_packet ( ccrf_t *ctx, uint8_t *rx_buffer, uint8_t *length_buff );
```

- `ccrf_get_start` Function for getting state of GD0 pin function.
```c
uint8_t ccrf_get_start( ctx );
```

## Examples Description

> This example demonstrates the use of an ccRF Click board by showing the communication between the two Click boards configured as a receiver and transmitter.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger, performs the Click default configuration and displays the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    ccrf_cfg_setup( &cfg );
    CCRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf_init( &ccrf, &cfg );

    ccrf_default_cfg( &ccrf );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ccrf_transmit_packet( &ccrf, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t data_buf[ 64 ] = { 0 };
    uint8_t data_len = sizeof( data_buf );
    if ( CCRF_CRC_OK == ccrf_receive_packet( &ccrf, data_buf, &data_len ) )
    {
        log_printf( &logger, " A new message has received: \"" );
        for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
        {
            log_printf( &logger, "%c", data_buf[ cnt ] );
        }
        log_printf( &logger, "\"\r\n" );
    }
#endif
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ccRf

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

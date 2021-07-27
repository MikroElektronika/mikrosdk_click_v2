
---
# ISM click

<PRVIH_PAR_RECENICA_SA_PRODUCT_PAGE_DA_ISPRATE_CELINU>

<p align="center">
  <img src="CLICK_IMAGE_LINK" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Ism Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ism Click driver.

#### Standard key functions :

- `ism_cfg_setup` Config Object Initialization function.
```c
void ism_cfg_setup ( ism_cfg_t *cfg );
```

- `ism_init` Initialization function.
```c
ISM_RETVAL ism_init ( ism_t *ctx, ism_cfg_t *cfg );
```

- `ism_default_cfg` Click Default Configuration function.
```c
void ism_default_cfg ( ism_t *ctx );
```

#### Example key functions :

- `ism_device_config` ISM device configuration function.
```c
err_t ism_device_config ( ism_t *ctx );
```

- `ism_receive_packet` ISM receive packet function.
```c
err_t ism_receive_packet ( ism_t *ctx, uint8_t *rx_data );
```

- `ism_transmit_packet` ISM transmit package function.
```c
err_t ism_transmit_packet ( ism_t *ctx, uint8_t type, uint8_t *tx_data, uint8_t len );
```

## Example Description

> This library contains API for the ISM Click driver.
> This example transmits/receives and processes data from ISM clicks.
> The library initializes and defines the UART bus drivers 
> to transmit or receive data.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and set performs the default configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism_cfg_t ism_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ism_cfg_setup( &ism_cfg );
    ISM_MAP_MIKROBUS( ism_cfg, MIKROBUS_1 );
    err_t init_flag  = ism_init( &ism, &ism_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ism_default_cfg ( &ism );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );

    #ifdef RECEIVER   
        ism_switch_rx_mode( &ism );
        log_printf( &logger, "   Receive data  \r\n" );
    #endif
   
    #ifdef TRANSMITTER
        ism_switch_tx_mode( &ism );
        log_printf( &logger, "  Transmit data   \r\n" );
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}

```

### Application Task

> Transmitter/Receiver task depends  on uncommented code.
> Receiver logging each received byte to the UART for data logging,
> while transmitted send messages every 1 second.

```c

void application_task ( void ) {
    #ifdef RECEIVER
        uint8_t rx_buf[ ISM_MAX_PACKET_LEN ] = { 0 };

        ism_receive_packet( &ism, &rx_buf[ 0 ] );
    
        if ( rx_buf[ 0 ] != 0 ) {
            log_printf( &logger, "  Rx : %s", rx_buf );
        }
    #endif

    #ifdef TRANSMITTER
        ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, &demo_message_1[ 0 ], 9 );
        log_printf( &logger, "  Tx : %s", demo_message_1 );
        Delay_ms( 1000 );
    
        ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, &demo_message_2[ 0 ], 12 );
        log_printf( &logger, "  Tx : %s", demo_message_2 );
        Delay_ms( 1000 );
    #endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ism

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

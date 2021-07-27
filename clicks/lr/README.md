\mainpage Main Page

---
# LR click

LR Click is a compact add-on board that contains a low-power, long-range transceiver. This board features the RN2483, RF technology-based SRD transceiver, which operates at a frequency of 433/868MHz from Microchip Technology. This Click board™ features an embedded LoRaWAN Class A compliant stack, providing a long-range spread spectrum communication with high interference immunity. The RN2483 module is a fully certified 433/868MHz European R&TTE directive assessed radio modem combined with the advanced and straightforward command interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lr-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the LR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR Click driver.

#### Standard key functions :

- `lr_cfg_setup` Config Object Initialization function.
```c
void lr_cfg_setup ( lr_cfg_t *cfg );
```

- `lr_init` Initialization function.
```c
err_t lr_init ( lr_t *ctx, lr_cfg_t *cfg );
```

- `lr_default_cfg` Click Default Configuration function.
```c
void lr_default_cfg ( lr_t *ctx, bool cb_default, void ( *response_p )( char *response ) );
```

#### Example key functions :

- `lr_mac_tx` Function for writing mac parameters
```c
uint8_t lr_mac_tx ( lr_t *ctx, lr_mac_t *mac );
```

- `lr_join` Function for setting join mode
```c
uint8_t lr_join ( lr_t *ctx, char *join_mode, char *response );
```

- `lr_tick_conf` Timer Configuration
```c
void lr_tick_conf ( lr_t *ctx, uint32_t timer_limit );
```

## Example Description

> This example reads and processes data from LR clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver init and LR init.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;
    lr_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lr_cfg_setup( &cfg );
    LR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr_init( &lr, &cfg );

    lr_default_cfg( &lr, 0, &lr_cbk );

    lr_cmd( &lr, LR_CMD_SYS_GET_VER, &tmp_txt[ 0 ] );

    lr_cmd( &lr, LR_CMD_MAC_PAUSE,  &tmp_txt[ 0 ] );
    log_printf( &logger, "mac pause\r\n" );
    for ( cnt = 0; cnt < 10; cnt++ ) {
        log_printf( &logger, "%c", tmp_txt[ cnt ] );
    }

    log_printf( &logger, "\r\n" );

    lr_cmd( &lr, LR_CMD_RADIO_SET_WDT, &tmp_txt[ 0 ] );

    log_printf( &logger, "radio set wdt 0\r\n" );
    log_printf( &logger, "%s\r\n", &tmp_txt[ 0 ] );
}

```

### Application Task

> Transmitter mode - sends one by one byte sequence of the desired message each second and checks if it is sent successfully. Receiver mode - displays all the received characters on USB UART.

```c

void application_task ( void ) {
    char *ptr;
    lr_process( );
    
#ifdef DEMO_APP_RECEIVER
    rx_state = lr_rx( &lr, LR_ARG_0, &tmp_txt[ 0 ] );
    if ( rx_state == 0 ) {
        tmp_txt[ 12 ] = 0;
        ptr = ( char* )&int_data;
        hex_to_int( &tmp_txt[ 10 ], ptr );

        log_printf( &logger, "%c", int_data  );
    }
#endif

#ifdef DEMO_APP_TRANSMITTER
    for ( cnt = 0; cnt < 9; cnt++ ) {
        send_data = send_message[ cnt ] ;
        int8_to_hex( send_data, send_hex );
        tx_state = lr_tx( &lr, &send_hex[ 0 ] );
        if ( tx_state == 0 ) {
            log_printf( &logger, "  Response : %s\r\n", &tmp_txt[ 0 ] );
        }
        Delay_ms( 1000 );
    }
#endif
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LR

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

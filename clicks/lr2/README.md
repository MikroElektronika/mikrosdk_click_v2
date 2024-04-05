\mainpage Main Page

---
# LR 2 click

> LR 2 Click is a compact add-on board that contains a low-power, long-range transceiver. This board features the RN2903, RF technology-based SRD transceiver, which operates at a frequency of 915MHz from Microchip Technology. This Click board™ features an embedded LoRaWAN Class A compliant stack, providing a long-range spread spectrum communication with high interference immunity. The RN2903 module is fully compliant with the United States (FCC) and Canada (IC) regulations combined with the advanced and straightforward command interface allowing easy integration into the final application. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr_2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lr-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the LR2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR2 Click driver.

#### Standard key functions :

- `lr2_cfg_setup` Config Object Initialization function.
```c
void lr2_cfg_setup ( lr2_cfg_t *cfg );
```

- `lr2_init` Initialization function.
```c
err_t lr2_init ( lr2_t *ctx, lr2_cfg_t *cfg );
```

- `lr2_default_cfg` Click Default Configuration function.
```c
void lr2_default_cfg ( lr2_t *ctx, bool cb_default, void ( *response_p )( char *response ) );
```

#### Example key functions :

- `lr2_mac_tx` Function for writing mac parameters
```c
uint8_t lr2_mac_tx ( lr2_t *ctx, lr2_mac_t *mac );
```

- `lr2_join` Function for setting join mode
```c
uint8_t lr2_join ( lr2_t *ctx, char *join_mode, char *response );
```

- `lr2_tick_conf` Timer Configuration
```c
void lr2_tick_conf ( lr2_t *ctx, uint32_t timer_limit );
```

## Example Description

> This example shows the usage of the LR 2 Click board by transmitting and receiving data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs default configuration and reads System version.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr2_cfg_t lr2_cfg;  /**< Click config object. */

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
    lr2_cfg_setup( &lr2_cfg );
    LR2_MAP_MIKROBUS( lr2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr2_init( &lr2, &lr2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lr2_default_cfg( &lr2, 0, 0 );
    lr2_process( );

    lr2_cmd( &lr2, LR2_CMD_SYS_GET_VER, resp_buf );
    log_printf( &logger, " System VER: %s \r\n", resp_buf );
    
    lr2_cmd( &lr2, LR2_CMD_MAC_PAUSE, resp_buf );
    log_printf( &logger, " MAC PAUSE: %s \r\n", resp_buf );

    lr2_cmd( &lr2, LR2_CMD_RADIO_SET_WDT, resp_buf );
    log_printf( &logger, " RADIO SET WDT 0: %s \r\n", resp_buf );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Transmitter mode - sends a desired message each second and checks if it is sent successfully.
Receiver mode - displays all the received characters on USB UART.

```c

void application_task ( void ) 
{
    lr2_process( );
    
#ifdef DEMO_APP_TRANSMITTER
    uint8_t hex_buf[ 50 ] = { 0 };
    uint8_t cnt = 0;
    for ( cnt = 0; cnt < strlen( send_message ); cnt++ ) 
    {
        uint8_to_hex( send_message[ cnt ], &hex_buf[ cnt * 2 ] );
    }
    if ( LR2_OK == lr2_tx( &lr2, hex_buf ) ) 
    {
        log_printf( &logger, " Sent message: %s", send_message );
        log_printf( &logger, " Response : %s\r\n", resp_buf );
    }
    Delay_ms ( 1000 );
#else
    if ( LR2_OK == lr2_rx( &lr2, LR2_ARG_0, resp_buf ) ) 
    {
        uint8_t text_buf[ 20 ] = { 0 };
        uint8_t hex_buf[ 3 ] = { 0 };
        uint8_t cnt = 0;
        for ( cnt = 0; cnt < ( strlen( resp_buf ) - 10 ); cnt += 2 )
        {
            hex_buf[ 0 ] = resp_buf[ 10 + cnt ];
            hex_buf[ 1 ] = resp_buf[ 11 + cnt ];
            text_buf[ cnt / 2 ] = hex_to_uint8( hex_buf );
        }
        log_printf( &logger, "Received message: %s\r\n", text_buf );
    }
#endif
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LR2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

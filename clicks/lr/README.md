\mainpage Main Page

---
# LR Click

LR Click is a compact add-on board that contains a low-power, long-range transceiver. This board features the RN2483, RF technology-based SRD transceiver, which operates at a frequency of 433/868MHz from Microchip Technology. This Click board™ features an embedded LoRaWAN Class A compliant stack, providing a long-range spread spectrum communication with high interference immunity. The RN2483 module is a fully certified 433/868MHz European R&TTE directive assessed radio modem combined with the advanced and straightforward command interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lr-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
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

> This example shows the usage of the LR Click board by transmitting and receiving data.

**The demo application is composed of two sections :**

### Application Init

> IInitializes the driver and performs default configuration and reads System version.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr_cfg_t lr_cfg;  /**< Click config object. */

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
    lr_cfg_setup( &lr_cfg );
    LR_MAP_MIKROBUS( lr_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr_init( &lr, &lr_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lr_default_cfg( &lr, 0, 0 );

    lr_cmd( &lr, LR_CMD_SYS_GET_VER, resp_buf );
    log_printf( &logger, "System VER: %s \r\n", resp_buf );
    
    lr_cmd( &lr, LR_CMD_MAC_PAUSE, resp_buf );
    log_printf( &logger, "MAC PAUSE: %s \r\n", resp_buf );

    lr_cmd( &lr, LR_CMD_RADIO_SET_WDT, resp_buf );
    log_printf( &logger, "RADIO SET WDT 0: %s \r\n", resp_buf );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Transmitter mode - sends one-by-one byte sequence of the desired message each second and 
 checks if it is sent successfully
 Receiver mode - displays all the received characters on USB UART.

```c

void application_task ( void ) 
{
    lr_process( );
    
#ifdef DEMO_APP_RECEIVER
    char *ptr;
    uint8_t int_data;
    if ( LR_OK == lr_rx( &lr, LR_ARG_0, resp_buf ) ) 
    {
        resp_buf[ 12 ] = 0;
        ptr = ( char* ) &int_data;
        hex_to_int( &resp_buf[ 10 ], ptr );
        log_printf( &logger, "%c", int_data  );
    }
#endif
#ifdef DEMO_APP_TRANSMITTER
    for ( uint8_t cnt = 0; cnt < 9; cnt++ ) 
    {
        int8_to_hex( send_message[ cnt ], send_hex );
        if ( LR_OK == lr_tx( &lr, &send_hex[ 0 ] ) ) 
        {
            log_printf( &logger, " Response : %s \r\n", resp_buf );
        }
        Delay_ms ( 1000 );
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
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

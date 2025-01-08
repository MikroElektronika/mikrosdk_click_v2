
---
# LR 2 Click

> [LR 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4615) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4615&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example shows the usage of the LR 2 Click board by transmitting and receiving data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR2

### Example Key Functions

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


## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---

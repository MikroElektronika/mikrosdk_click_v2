
---
# LR Click

> [LR Click](https://www.mikroe.com/?pid_product=MIKROE-4470) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4470&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example shows the usage of the LR Click board by transmitting and receiving data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR

### Example Key Functions

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

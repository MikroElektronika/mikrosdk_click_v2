
---
# EnOcean 4 Click

> [EnOcean 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3637) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3637&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from EnOcean 4 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Enocean4

### Example Key Functions

- `enocean4_cfg_setup` Config Object Initialization function. 
```c
void enocean4_cfg_setup ( enocean4_cfg_t *cfg );
``` 
 
- `enocean4_init` Initialization function. 
```c
err_t enocean4_init ( enocean4_t *ctx, enocean4_cfg_t *cfg );
```

- `enocean4_response_handler_set( enocean4_t *ctx, void` Handler Set function. 
```c
void enocean4_response_handler_set( enocean4_t *ctx, void ( *handler )( enocean4_packet_t*, uint8_t* ) );
```
 
- `enocean4_process` Response Proccesing function. 
```c
uint8_t enocean4_process ( enocean4_t *ctx );
```

- `enocean4_response_ready` Response Ready Check function. 
```c
uint8_t enocean4_response_ready ( enocean4_t *ctx );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean4_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    enocean4_cfg_setup( &cfg );
    ENOCEAN4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean4_init( &enocean4, &cfg );

    Delay_ms ( 500 );

    enocean4_response_handler_set( &enocean4, &make_response );
    Delay_ms ( 300 );
    rsp_check = 1;
    enocean4_reset( &enocean4 );

    log_printf( &logger, "** EnOcean 4 initialization done **\r\n" );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms ( 500 );
    
    // Clearing RX buffer
    {
        uint8_t tmp_buf[ 100 ];
        enocean4_generic_read( &enocean4, tmp_buf, 100 );
    }

    log_printf( &logger, "Device version reading...\r\n" );
    message.data_length    = 0x0001;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_RD_VERSION;
    enocean4_send_packet( &enocean4, &message );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );

    log_printf( &logger, "Add filter to filter list...\r\n" );
    message.data_length    = 0x0007;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_WR_FILTER_ADD;
    message.data_buff[ 1 ] = ENOCEAN4_FILTER_TYPE_RORG;
    message.data_buff[ 2 ] = 0x00;
    message.data_buff[ 3 ] = 0x00;
    message.data_buff[ 4 ] = 0x00;
    message.data_buff[ 5 ] = ENOCEAN4_RORG_ADT;
    message.data_buff[ 6 ] = ENOCEAN4_APPLY_RADIO_INTER;
    enocean4_send_packet( &enocean4, &message );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );

    log_printf( &logger, "Supplied filters reading...\r\n" );
    message.data_length    = 0x0001;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_RD_FILTER;
    enocean4_send_packet( &enocean4, &message );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
    log_printf( &logger, "Ready to exchange telegrams\r\n" );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
}
```

### Application Task

> In the receiver mode, it waits for a telegram, then replies to it with the certain message.
> In the transmitter mode, first it sends the telegram with the certain message, 
> then waits for a response.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    log_printf( &logger, "Waiting for a telegram...\r\n" );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );

    log_printf( &logger, "Replying to the received telegram...\r\n" );
    send_telegram( DEMO_ANSWER, ENOCEAN4_RORG_ADT );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
#endif
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "Sending a telegram...\r\n" );
    send_telegram( DEMO_MESSAGE, ENOCEAN4_RORG_ADT );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );

    log_printf( &logger, "Waiting for a response...\r\n" );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

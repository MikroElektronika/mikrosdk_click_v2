
---
# M-BUS RF 4 Click

> [M-BUS RF 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3692) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3692&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from M-BUS RF 4 Clicks. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MBusRf4

### Example Key Functions

- `mbusrf4_cfg_setup` Config Object Initialization function. 
```c
void mbusrf4_cfg_setup ( mbusrf4_cfg_t *cfg );
``` 
 
- `mbusrf4_init` Initialization function. 
```c
err_t mbusrf4_init ( mbusrf4_t *ctx, mbusrf4_cfg_t *cfg );
```

- `mbusrf4_send_command` Header and checksum are calculated and sent at the beginning (header) and finally (checksum). 
```c
void mbusrf4_send_command ( mbusrf4_t *ctx, uint8_t command, uint8_t length, uint8_t *payload_buff );
```
 
- `mbusrf4_generic_write` This function write specific number of data. 
```c
void mbusrf4_generic_write ( mbusrf4_t *ctx, char *data_buf, uint16_t len );
```

- `mbusrf4_generic_read` This function read data of maximum length. 
```c
uint16_t mbusrf4_generic_read ( mbusrf4_t *ctx, char *data_buf, uint16_t max_len );
```

### Application Init

> Initializes driver init, reads basic information and checks communication

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusrf4_cfg_t cfg;

    uint8_t payload_buff[ 20 ] = { 0 };

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
    log_info( &logger, "Application Init" );

    //  Click initialization.

    mbusrf4_cfg_setup( &cfg );
    MBUSRF4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusrf4_init( &mbusrf4, &cfg );
    
    parser_cnt = 0;
    parser_ptr = &parser_buf[ 0 ];
    mbusrf4_process( );
    mbrusrf4_clear_buff();

    //Command SET mode
    payload_buff[ 0 ] = MBUSRF4_SET_VALUE_IN_EEPROM_MEMORY;
    payload_buff[ 1 ] = MBUSRF4_EEPARAM_WMBUS_MODE_S2_SHORT_PREAMBLE;

    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_SET_MODE, 2, &payload_buff[ 0 ] );
    Delay_ms ( 500 );
    mbusrf4_process( );
    mbusrf4_parser_tx();
    mbrusrf4_clear_buff();
    
    // Reads FW version
    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_GET_FW_VERSION, 0, &payload_buff[ 0 ] );
    Delay_ms ( 500 );
    mbusrf4_process( );
    log_info( &logger, "FW version:" );
    mbusrf4_parser_rx( LOG_HEX );
    log_printf( &logger, "-----------------------------------------------------------\r\n" );
    mbusrf4_process( );

    Delay_ms ( 1000 );
    log_info( &logger, "Application Task" );
}
```

### Application Task

> In the RX mode it is waiting to receive data from another module...
> In the TX mode sends the data packet....

```c
void application_task ( void )
{
    // RX App mode
    #ifdef DEMO_APP_RECEIVER

    if ( mbusrf4_get_state_ind( &mbusrf4 ) == 0 )
    {     
        Delay_ms ( 100 );
        mbusrf4_process( );
        
        mbusrf4_parser_rx( LOG_STR );
    }
    
    #endif
    
    // TX App Mode
    #ifdef DEMO_APP_TRANSMITER
    
    mbusrf4_transmit_data( &mbusrf4, msg, 17 );
    Delay_ms ( 100 );
    mbrusrf4_clear_buff();
    mbusrf4_parser_tx();
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    #endif
}
```

### Note

> ## Additional Function
> mbusrf4_process ( ) - The general process of collecting data and adding it to application buffer;
 
>  mbrusrf4_clear_buff ( void ) - Clear application buffer data;
 
>  mbusrf4_parser_tx ( void ) - Transmit data status parser;
 
>  mbusrf4_parser_rx ( uint8_t logg_type ) - Receiver data parser;
 
>  mbusrf4_log_data ( uint8_t log_type, uint8_t *log_buf, int32_t log_len ) - Log application buffer;
 
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

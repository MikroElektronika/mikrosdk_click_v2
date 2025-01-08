
---
# Wirepas Click

> [Wirepas Click](https://www.mikroe.com/?pid_product=MIKROE-5874) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5874&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Wirepas Click board by processing
  the incoming data and displaying them on the USB UART in sink mode, and sending data to 
  the sinks in router mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Wirepas

### Example Key Functions

- `wirepas_cfg_setup` Config Object Initialization function.
```c
void wirepas_cfg_setup ( wirepas_cfg_t *cfg );
```

- `wirepas_init` Initialization function.
```c
err_t wirepas_init ( wirepas_t *ctx, wirepas_cfg_t *cfg );
```

- `wirepas_default_cfg` Click Default Configuration function.
```c
void wirepas_default_cfg ( wirepas_t *ctx );
```

- `wirepas_send_command` Wirepas send command function.
```c
err_t wirepas_send_command ( wirepas_t *ctx, uint8_t primitive_id, uint8_t payload_length, uint8_t *payload );
```

- `wirepas_write_csap_attribute` Wirepas write CSAP attribute function.
```c
err_t wirepas_write_csap_attribute ( wirepas_t *ctx, uint16_t attribute_id, uint8_t attribute_len, uint8_t *attribute_val );
```

- `wirepas_send_data` Wirepas send data function.
```c
err_t wirepas_send_data ( wirepas_t *ctx, wirepas_sink_data sink_data, uint8_t tx_op, uint8_t apdu_length, uint8_t *apdu );
```

### Application Init

> Initializes the driver and performs the Click default configuration, setting device mode, node,
  net and channel addresses, and starting stack.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wirepas_cfg_t wirepas_cfg;  /**< Click config object. */

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
    wirepas_cfg_setup( &wirepas_cfg );
    WIREPAS_MAP_MIKROBUS( wirepas_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wirepas_init( &wirepas, &wirepas_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    wirepas_default_cfg ( &wirepas );
   
    wirepas.tx_frame_id = 0;
    do
    {
        log_printf( &logger, " Wirepas stack stop request:" );
        wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_STOP_REQUEST, 0, NULL );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_MSAP_STACK_STOP_CONFIRM ) );
    Delay_ms ( 1000 );
    
    do
    {
        log_printf( &logger, " Wirepas factory reset request:" );
        wirepas_send_command( &wirepas, WIREPAS_CSAP_FACTORY_RESET_REQUEST,
                              strlen( WIREPAS_FACTORY_RESET_CODE ), WIREPAS_FACTORY_RESET_CODE );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_FACTORY_RESET_CONFIRM ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    do
    {
        log_printf( &logger, " Set node address:" );
        wirepas_set_node_address( &wirepas, NODE_ADDRESS );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_ms ( 1000 );
    
    do
    {
        log_printf( &logger, " Set net address:" );
        wirepas_set_net_address( &wirepas, NET_ADDRESS );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_ms ( 1000 );
    
    uint8_t channel_net = CHANNEL_ADDRESS;
    do
    {
        log_printf( &logger, " Set channel address:" );
        wirepas_write_csap_attribute( &wirepas, WIREPAS_CSAP_ATTRIBUTE_NETWORK_CHANNEL, 1, &channel_net );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_ms ( 1000 );


    uint8_t role;
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    role = WIREPAS_ROUTER_NODE_MODE;
#else
    role = WIREPAS_SINK_NODE_MODE;
#endif
    do
    {
        log_printf( &logger, " Set role:" );
        wirepas_write_csap_attribute( &wirepas, WIREPAS_CSAP_ATTRIBUTE_NODE_ROLE, 1, &role );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_1sec( );
    
    do
    {
        log_printf( &logger, " Wirepas Stack start request:" ); 
        wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_START_REQUEST, 1, &stack_auto_start );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_MSAP_STACK_START_CONFIRM ) );
    Delay_1sec( );
        
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )

    sink_1.pduid = 0x00;
    sink_1.source_endpoint = 0x01;
    sink_1.destination_addr = SINK_1_NODE_ADDRESS;
    sink_1.destination_endpoint = 0x01;
    #if defined MULTI_SINK_MODE
        sink_2.pduid = 0x00;
        sink_2.source_endpoint = 0x01;
        sink_2.destination_addr = SINK_2_NODE_ADDRESS;
        sink_2.destination_endpoint = 0x01;
    #endif
#endif
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Router mode - Sending data to the sinks at the same network.
  Sink mode - Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    wirepas_poll_indication ( &wirepas );
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    if ( wirepas_get_din_state ( &wirepas ) && ( pdu_capacity > 0 ) )
    {
        log_printf( &logger, " Sending data to the first Sink node: \n" );
        wirepas_send_data ( &wirepas,  sink_1, 0x01, strlen( TX_DATA ), TX_DATA );
        wirepas_wait_response ( &wirepas, WIREPAS_DSAP_DATA_TX_CONFIRM );
        Delay_ms ( 1000 );
        
        #if defined MULTI_SINK_MODE
            log_printf( &logger, " Sending data to the second Sink node: \n" );
            wirepas_send_data ( &wirepas,  sink_2, 0x01, strlen( TX_DATA ), TX_DATA );
            wirepas_wait_response ( &wirepas, WIREPAS_DSAP_DATA_TX_CONFIRM );
            Delay_ms ( 1000 );
        #endif
    }
#endif
}
```

### Note

> For the best experience use two Clicks in sink mode and one in router.

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

\mainpage Main Page

---
# Wirepas click

> Wirepas Click is a compact add-on board that allows you to implement the Wirepas Mesh wireless connectivity stack to your application. This board features the WIRL-PRO2 Thetis-I (2611011021010), a radio module with Wirepas Mesh Protocol from Würth Elektronik. It supports creating a Wirepas routing mesh protocol and is optimized for ultra-low energy consumption. The large scalability is ideal for extensive IoT networks and can work as a host-controlled device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wirepas_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/wirepas-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : UART type


# Software Support

We provide a library for the Wirepas Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Wirepas Click driver.

#### Standard key functions :

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

#### Example key functions :

- `wirepas_send_command` Wirepas send command function.
```c
err_t wirepas_send_command ( wirepas_t *ctx, uint8_t primitive_id, uint8_t frame_id, uint8_t payload_length, uint8_t *payload );
```

- `wirepas_write_csap_attribute` Wirepas write CSAP attribute function.
```c
err_t wirepas_write_csap_attribute ( wirepas_t *ctx, uint8_t frame_id, uint16_t attribute_id, uint8_t attribute_len, uint8_t *attribute_val );
```

- `wirepas_send_data` Wirepas send data function.
```c
err_t wirepas_send_data ( wirepas_t *ctx, uint8_t frame_id, wirepas_sink_data sink_data, uint8_t tx_op, uint8_t apdu_length, uint8_t *apdu );
```

## Example Description

> This example demonstrates the use of Wirepas click board by processing
  the incoming data and displaying them on the USB UART in sink mode, and sending data to 
  the sinks in router mode.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration, setting device mode, node,
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
   
    uint8_t tmp_data[ 1 ] = { 0x00 };
    
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
   
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
    
    Delay_ms( 1000 );
    log_printf( &logger, " Wirepas stack stop request: \n" );
    wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_STOP_REQUEST, frame_id, 0x00, tmp_data );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Wirepas factory reset request: \n" );
    wirepas_send_command( &wirepas, WIREPAS_CSAP_FACTORY_RESET_REQUEST, frame_id, strlen( WIREPAS_FACTORY_RESET_CODE ), WIREPAS_FACTORY_RESET_CODE );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
    
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set node address: \n" );
    wirepas_set_node_address( &wirepas, frame_id, NODE_ADDRESS );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set net address: \n" );
    wirepas_set_net_address( &wirepas, frame_id, NET_ADDRESS );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set channel address: \n" );
    uint8_t channel_net = CHANNEL_ADDRESS;
    wirepas_write_csap_attribute( &wirepas, frame_id, WIREPAS_CSAP_ATTRIBUTE_NETWORK_CHANNEL, 1, &channel_net );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set role: \n" );
    uint8_t role;
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    role = WIREPAS_ROUTER_NODE_MODE;
#else
    role = WIREPAS_SINK_NODE_MODE;
#endif
    wirepas_write_csap_attribute( &wirepas, frame_id, WIREPAS_CSAP_ATTRIBUTE_NODE_ROLE, 1, &role );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Wirepas Stack start request: \n" ); 
    tmp_data[ 0 ] = 0x01;
    wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_START_REQUEST, frame_id, 0x01, tmp_data );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    uint8_t data_buf[ WIREPAS_RX_DRV_BUFFER_SIZE ] = { 0 };
    
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, data_buf, NULL );
    frame_id++;
        
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
#else
    uint8_t data_rd = 0;
    while ( 0 == data_rd )
    {
        wirepas_poll_indication( &wirepas, frame_id, data_buf, &data_rd );
        frame_id++;
        Delay_ms( 1000 );
    }
#endif
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Router mode - Sending data to the sinks at the same network.
  Sink mode - Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    
    log_printf( &logger, " Sending data to the first Sink node: \n" );
    wirepas_send_data ( &wirepas, frame_id, sink_1, 0x01, strlen( TX_DATA ), TX_DATA );
    frame_id++;
    wirepas_get_resp( &wirepas );
    Delay_ms( 5000 );
    
    #if defined MULTI_SINK_MODE
        log_printf( &logger, " Sending data to the second Sink node: \n" );
        wirepas_send_data ( &wirepas, frame_id, sink_2, 0x01, strlen( TX_DATA ), TX_DATA );
        frame_id++;
        wirepas_get_resp( &wirepas );
        Delay_ms( 5000 );
    #endif
#else
    
    uint8_t data_buf[ WIREPAS_RX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t data_rdy = 0;
    err_t error = wirepas_poll_indication( &wirepas, frame_id, data_buf, &data_rdy );
    frame_id++;
    if ( 1 == data_rdy )
    {
        log_printf( &logger, "%s \r\n", data_buf );
    }
    Delay_ms( 2000 );
#endif
}
```

## Note

> For the best experience use two clicks in sink mode and one in router.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Wirepas

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

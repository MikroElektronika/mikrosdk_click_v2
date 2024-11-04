\mainpage Main Page

---
# NeoMesh 2 Click

> NeoMesh 2 Click is a compact add-on board with a low-power, long-range transceiver, ideal for Mesh wireless networking. This board features the NC2400, a wireless Mesh network module from NeoCortec. With an additional antenna that MikroE offers connected to the module’s u.Fl connector, you can create a fully functional wireless Mesh network node that will work in the Sub-GHz frequency band of 2.4GHz. The module has a generic application layer that can be configured to suit applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/neomesh2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/neomesh-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART type


# Software Support

We provide a library for the NeoMesh 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NeoMesh 2 Click driver.

#### Standard key functions :

- `neomesh2_cfg_setup` Config Object Initialization function.
```c
void neomesh2_cfg_setup ( neomesh2_cfg_t *cfg );
```

- `neomesh2_init` Initialization function.
```c
err_t neomesh2_init ( neomesh2_t *ctx, neomesh2_cfg_t *cfg );
```

#### Example key functions :

- `neomesh2_send_aapi_frame` This function sends a desired AAPI frame by using UART serial interface.
```c
err_t neomesh2_send_aapi_frame ( neomesh2_t *ctx, neomesh2_aapi_frame_t *frame );
```

- `neomesh2_read_aapi_frame` This function reads an AAPI frame by using UART serial interface.
```c
err_t neomesh2_read_aapi_frame ( neomesh2_t *ctx, neomesh2_aapi_frame_t *frame );
```

- `neomesh2_send_sapi_frame` This function sends a desired SAPI frame by using UART serial interface.
```c
err_t neomesh2_send_sapi_frame ( neomesh2_t *ctx, neomesh2_sapi_frame_t *frame );
```

## Example Description

> This example demonstrates the use of NeoMesh 2 Click board by showing the communication between the two Click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the Click board for the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    neomesh2_cfg_t neomesh2_cfg;  /**< Click config object. */

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
    neomesh2_cfg_setup( &neomesh2_cfg );
    NEOMESH2_MAP_MIKROBUS( neomesh2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == neomesh2_init( &neomesh2, &neomesh2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "\r\n Enable SAPI over AAPI\r\n" );
    aapi_frame.cmd = NEOMESH2_CMD_SAPI_TO_AAPI;
    aapi_frame.len = 0;
    neomesh2_send_aapi_frame ( &neomesh2, &aapi_frame );
    neomesh2_parse_sapi_rsp ( NEOMESH2_SAPI_RSP_BOOTLOADER_START );
    
    log_printf( &logger, "\r\n Login with password\r\n" );
    sapi_frame.cmd = NEOMESH2_SAPI_CMD_LOGIN;
    sapi_frame.len = 5;
    sapi_frame.payload[ 0 ] = NEOMESH2_SAPI_LOGIN_PASSWORD_0;
    sapi_frame.payload[ 1 ] = NEOMESH2_SAPI_LOGIN_PASSWORD_1;
    sapi_frame.payload[ 2 ] = NEOMESH2_SAPI_LOGIN_PASSWORD_2;
    sapi_frame.payload[ 3 ] = NEOMESH2_SAPI_LOGIN_PASSWORD_3;
    sapi_frame.payload[ 4 ] = NEOMESH2_SAPI_LOGIN_PASSWORD_4;
    neomesh2_send_sapi_frame ( &neomesh2, &sapi_frame );
    neomesh2_parse_sapi_rsp ( NEOMESH2_SAPI_RSP_OK );
    
    log_printf( &logger, "\r\n Set NODE ID to: " );
    sapi_frame.cmd = NEOMESH2_SAPI_CMD_SET_SETTING;
    sapi_frame.len = 3;
    sapi_frame.payload[ 0 ] = NEOMESH2_SAPI_SETTINGS_ID_NODE_ID;
#if ( DEMO_APP == APP_RECEIVER_1 )
    log_printf( &logger, "%.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_1 );
    sapi_frame.payload[ 1 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_1 >> 8 ) & 0xFF );
    sapi_frame.payload[ 2 ] = ( uint8_t ) ( NODE_ID_RECEIVER_1 & 0xFF );
#elif ( DEMO_APP == APP_RECEIVER_2 )
    log_printf( &logger, "%.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_2 );
    sapi_frame.payload[ 1 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_2 >> 8 ) & 0xFF );
    sapi_frame.payload[ 2 ] = ( uint8_t ) ( NODE_ID_RECEIVER_2 & 0xFF );
#elif ( DEMO_APP == APP_ORIGINATOR )
    log_printf( &logger, "%.4X\r\n", ( uint16_t ) NODE_ID_ORIGINATOR );
    sapi_frame.payload[ 1 ] = ( uint8_t ) ( ( NODE_ID_ORIGINATOR >> 8 ) & 0xFF );
    sapi_frame.payload[ 2 ] = ( uint8_t ) ( NODE_ID_ORIGINATOR & 0xFF );
#endif
    neomesh2_send_sapi_frame ( &neomesh2, &sapi_frame );
    neomesh2_parse_sapi_rsp ( NEOMESH2_SAPI_RSP_OK );
    
    log_printf( &logger, "\r\n Commit settings\r\n" );
    sapi_frame.cmd = NEOMESH2_SAPI_CMD_COMMIT_SETTINGS;
    sapi_frame.len = 0;
    neomesh2_send_sapi_frame ( &neomesh2, &sapi_frame );
    neomesh2_parse_sapi_rsp ( NEOMESH2_SAPI_RSP_OK );
    
    log_printf( &logger, "\r\n Start protocol stack\r\n" );
    sapi_frame.cmd = NEOMESH2_SAPI_CMD_START_PROTOCOL_STACK;
    sapi_frame.len = 0;
    neomesh2_send_sapi_frame ( &neomesh2, &sapi_frame );
    neomesh2_parse_sapi_rsp ( NEOMESH2_SAPI_RSP_PROTOCOL_STACK_START );
    // Wait for the device to actually switch back to application layer
    while ( !neomesh2_get_cts_pin ( &neomesh2 ) );
    
    log_printf( &logger, "\r\n Get NODE info\r\n" );
    aapi_frame.cmd = NEOMESH2_CMD_NODE_INFO;
    aapi_frame.len = 0;
    neomesh2_send_aapi_frame ( &neomesh2, &aapi_frame );
    neomesh2_parse_aapi_rsp ( NEOMESH2_RSP_NODE_INFO );
    
    log_printf( &logger, "\r\n Get neighbour list\r\n" );
    aapi_frame.cmd = NEOMESH2_CMD_NEIGHBOUR_LIST;
    aapi_frame.len = 0;
    neomesh2_send_aapi_frame ( &neomesh2, &aapi_frame );
    neomesh2_parse_aapi_rsp ( NEOMESH2_RSP_NEIGHBOUR_LIST );
    
#if ( DEMO_APP == APP_RECEIVER_1 )
    log_printf( &logger, "\r\n Application Mode: Receiver 1\r\n" );
#elif ( DEMO_APP == APP_RECEIVER_2 )
    log_printf( &logger, "\r\n Application Mode: Receiver 2\r\n" );
#elif ( DEMO_APP == APP_ORIGINATOR )
    log_printf( &logger, "\r\n Application Mode: Originator\r\n" );
#else
    #error "Selected application mode is not supported!"
#endif
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> One Click board should be set to originator mode and the others to receiver 1 or 2.
If the SINGLE_RECEIVER_MODE is enabled, the originator device sends a desired message
to RECEIVER_1 node and waits for an acknowledge response, otherwise it sends the same
message to both RECEIVER_1 and RECEIVER_2 nodes. The receiver devices reads and parses
all incoming AAPI frames and displays them on the USB UART.

```c
void application_task ( void )
{
#if ( DEMO_APP == APP_ORIGINATOR )
    log_printf( &logger, "\r\n Send message to node: %.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_1 );
    aapi_frame.cmd = NEOMESH2_CMD_ACK_SEND;
    aapi_frame.len = 3 + strlen ( DEMO_TEXT_MESSAGE );
    aapi_frame.payload[ 0 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_1 >> 8 ) & 0xFF );
    aapi_frame.payload[ 1 ] = ( uint8_t ) ( NODE_ID_RECEIVER_1 & 0xFF );
    aapi_frame.payload[ 2 ] = DEFAULT_PORT;
    strcpy ( &aapi_frame.payload[ 3 ], DEMO_TEXT_MESSAGE );
    if ( NEOMESH2_OK == neomesh2_send_aapi_frame ( &neomesh2, &aapi_frame ) )
    {
        neomesh2_parse_aapi_rsp ( NEOMESH2_RSP_ACK );
    }
    #ifndef SINGLE_RECEIVER_MODE
        log_printf( &logger, "\r\n Send message to node: %.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_2 );
        aapi_frame.cmd = NEOMESH2_CMD_ACK_SEND;
        aapi_frame.len = 3 + strlen ( DEMO_TEXT_MESSAGE );
        aapi_frame.payload[ 0 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_2 >> 8 ) & 0xFF );
        aapi_frame.payload[ 1 ] = ( uint8_t ) ( NODE_ID_RECEIVER_2 & 0xFF );
        aapi_frame.payload[ 2 ] = DEFAULT_PORT;
        strcpy ( &aapi_frame.payload[ 3 ], DEMO_TEXT_MESSAGE );
        if ( NEOMESH2_OK == neomesh2_send_aapi_frame ( &neomesh2, &aapi_frame ) )
        {
            neomesh2_parse_aapi_rsp ( NEOMESH2_RSP_ACK );
        }
    #endif
#else
   neomesh2_parse_aapi_rsp ( NULL );
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NeoMesh2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

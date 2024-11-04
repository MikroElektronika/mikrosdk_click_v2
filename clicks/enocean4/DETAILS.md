
---
# EnOcean 4 Click

EnOcean 4 Click carries a ultra-low power TCM515U transceiver gateway module which operates at 902MHz radio band, perfectly suited for the realization of transceiver gateways, actuators and controllers for systems communicating based on the EnOcean radio standard.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/enocean4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/enocean-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Enocean4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Enocean4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void enocean4_cfg_setup ( enocean4_cfg_t *cfg ); 
 
- Initialization function.
> ENOCEAN4_RETVAL enocean4_init ( enocean4_t *ctx, enocean4_cfg_t *cfg );

#### Example key functions :

- Handler Set function.
> void enocean4_response_handler_set( enocean4_t *ctx, void ( *handler )( enocean4_packet_t*, uint8_t* ) );
 
- Response Proccesing function.
> uint8_t enocean4_process ( enocean4_t *ctx );

- Response Ready Check function.
> uint8_t enocean4_response_ready ( enocean4_t *ctx );

## Examples Description
 
> This example reads and processes data from EnOcean 4 clicks.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Enocean4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

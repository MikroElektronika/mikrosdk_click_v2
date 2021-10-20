
---
# Thingstream click

Thingstream Click is an IoT gateway Click board™ with the Thingstream client SDK preinstalled.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thingstream_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thingstream-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Thingstream Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thingstream Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thingstream_cfg_setup ( thingstream_cfg_t *cfg ); 
 
- Initialization function.
> THINGSTREAM_RETVAL thingstream_init ( thingstream_t *ctx, thingstream_cfg_t *cfg );

#### Example key functions :

- Set RST pin state.
> uint8_t thingstream_reset_pin_state ( thingstream_t *ctx, uint8_t state );
 
- Send command.
> void thingstream_send_command ( thingstream_t *ctx, char *command );

- Generic parser function.
> thingstream_error_t thingstream_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

## Examples Description

> This example reads and processes data from Thingstream clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thingstream_cfg_t cfg;

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

    thingstream_cfg_setup( &cfg );
    THINGSTREAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thingstream_init( &thingstream, &cfg );

    thingstream_module_power( &thingstream, true );
    Delay_ms( 3000 );

    log_printf( &logger, " --->>> INFO.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_INFO );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );
        
    log_printf( &logger, " --->>> CREATE.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_CREATE );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> CONNECT.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_CONNECT );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> GPS POWER.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_GPS_PWR );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> SUBSCRIBE.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_SUBSCRIBE );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> PUBLISH.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_PUBLISH );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> APP INIT <<<--- \r\n" );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    thingstream_send_command( &thingstream, THINGSTREAM_GPS_INFO );  
    thingstream_process( );
    parser_application( current_parser_buf );
} 

```

## Note

> The click board needs to be registered with a redemption code to a Thingstream Domain.
> For more information please refer to the Thingstream click user manual available on the product page.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thingstream

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

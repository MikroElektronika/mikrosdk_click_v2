 
---
# Wifi ESP click

WiFi ESP click carries the ESP-WROOM-02 module that integrates ESP8266EX.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wifiesp_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/wifi-esp-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the WifiEsp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for WifiEsp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void wifiesp_cfg_setup ( wifiesp_cfg_t *cfg ); 
 
- Initialization function.
> WIFIESP_RETVAL wifiesp_init ( wifiesp_t *ctx, wifiesp_cfg_t *cfg );

- Click Default Configuration function.
> void wifiesp_default_cfg ( wifiesp_t *ctx );


#### Example key functions :

- Reset module.
> void wifiesp_reset ( wifiesp_t *ctx );
 
- Generic write function.
> void wifiesp_generic_write ( wifiesp_t *ctx, char *data_buf, uint16_t len );

- Generic read function.
> uint16_t wifiesp_generic_read ( wifiesp_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from Wifi ESP clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifiesp_cfg_t cfg;

    char temp[ PROCESS_RX_BUFFER_SIZE ] = { 0 } ;
    char ip_address[ 17 ];
    uint8_t length;
    char *txt_val;
    char *data_buff;
    uint8_t i;
    uint8_t flag;
    uint8_t cnt;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifiesp_cfg_setup( &cfg );
    WIFIESP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifiesp_init( &wifiesp, &cfg );

    wifiesp_reset( &wifiesp );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_RST );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );
    
    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_SET_AT_CWMODE_1 );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    strcat( temp, "AT+CWJAP=" );
    strcat( temp, SSID );
    strcat( temp, PASSWORD );
 
    wifiesp_send_command ( &wifiesp, temp );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );
    
    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_CIPSTATUS );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    flag = 0;

    for ( ; ; )
    {
        wifiesp_process(  );
        
        for ( i = 0; i < strlen( current_parser_buf ); i++ )
        {
              if ( current_parser_buf[ i ] == 'K' )
            {
                flag = 1;
              break;
            }
        }
        
        if( flag == 1 )
        {
            break;
        }
        
    }
    
    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_SET_AT_CIPMUX_1 );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_SET_AT_CIPSERVER_1_80 );

    wifiesp_process(  );
    
    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_GET_AT_CIPSTO );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    //returns ip address and mac address

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_CIFSR ); 

    wifiesp_process(  ); 

    flag = 0;
    cnt = 0;

    memset( ip_address, 0, 17 );
    
    for ( i = 0; i < strlen( current_parser_buf); i++ )
    {

        if ( ( current_parser_buf[ i ] == 34 ) && ( flag == 0 ) ) 
        {
            flag = 1;
           
        }
        else if ( ( current_parser_buf[ i ] == 13 ) && ( flag == 1 ) )
        {
            memset( &ip_address[ cnt - 2 ], 0, 2 );
            flag = 0;
            break;
        }
        
        if ( flag == 1 )
        {
            ip_address[ cnt++ ] = current_parser_buf[ i + 1 ];

        }
    }
  
    log_printf( &logger, " \r\n--------------------------- \r\n" );
        
    log_printf( &logger, "%s", ip_address );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_CIPSTATUS );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    strcat( temp, "AT+CIPSTART=4,\"TCP\",\"" );
    strcat( temp, ip_address );
    strcat( temp, "\",80" );

    wifiesp_send_command ( &wifiesp, temp );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    wifiesp_process(  );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.WifiEsp

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

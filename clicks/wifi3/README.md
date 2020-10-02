\mainpage Main Page
 
---
# wifi3 click

WiFi3 click is a complete self-contained WiFi solution carrying the 
ESP8266 module with a system on a chip. The click is designed to run on 
a 3.3V power supply only. It communicates with the targetboard 
microcontroller through the mikroBUS™ RX, TX, CS and RST lines.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wifi3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/wifi-3-click>)

---


#### Click library 
`
- **Author**        : MikroE Team
- **Date**          : Aug 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the wifi3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for wifi3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void wifi3_cfg_setup ( wifi3_cfg_t *cfg ); 
 
- Initialization function.
> WIFI3_RETVAL wifi3_init ( wifi3_t *ctx, wifi3_cfg_t *cfg );


#### Example key functions :

- Checking module and initializes connection with network, starts web server
> uint8_t wifi_communication_init( void )
 
- This function sends AT commant to wifi3 click, logs sent and received data. 
> uint8_t wifi3_send_cmd( wifi3_t* ctx , log_t* logger , const wifi3_atcmd_t* cmd , uint8_t* args);
>

- This function reads data received from Wifi3 click.
> uint8_t wifi3_read( wifi3_t* ctx , uint8_t* r_buf );

## Examples Description

> 
> This example initializes wifi connestion to a network and starts web server,
> writes "MikroeE - Wifi3" to the client web application (for example web browser).
> 

**The demo application is composed of two sections :**

### Application Init 

>Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi3_cfg_t cfg;
    uint8_t init_pass = 0;
    
    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi3_cfg_setup( &cfg );
    WIFI3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi3_init( &wifi3, &cfg );
    
    // Communication initialization
    
     init_pass = wifi_communication_init( );
}
  
```

### Application Task

> Waits for client request (paste IP in web browser and refresh to send request),
> writes "MikroeE - Wifi3" to client application.

```c

void application_task ( void )
{
    uint8_t str[ 100 ] = { 0 };
    
    strcat( str , page_begin );
    strcat( str, "MikroE - Wifi3" );
    strcat( str , page_end );
    
    wifi3_read( &wifi3 , r_buf );
    wifi3_send_cmd( &wifi3 , &logger , &WIFI3_SEND , "0,34" );
    Delay_ms( 500 );
    
    wifi3_generic_write( &wifi3 , str , strlen( str ) );
    Delay_ms( 500 );
}  

```

## Note

> 
> Algorithm for communication initialization is:
> # Turn all 3 connected click pins ON
> # Set baud rate to 74880.
> # Do wifi check and reset
> # Change baud rate to 115200
> # Set working mode
> # Set multi or singe connection mode
> # Connect
> # Start communication with client/server
> 
> More related AT commands and their argumets format could be found on the following link:
> https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.wifi3

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

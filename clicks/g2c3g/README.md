\mainpage Main Page
 
---
# G2C 3G click

Go to Cloud (G2C) 3G click is a gateway Click board™ which provides a simple and reliable connection to the Click Cloud platform

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/g2c3g_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/go-to-cloud-g2c-3g-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : mar 2020.
- **Type**          : UART type


# Software Support

We provide a library for the G2c3G Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for G2c3G Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void g2c3g_cfg_setup ( g2c3g_cfg_t *cfg ); 
 
- Initialization function.
> G2C3G_RETVAL g2c3g_init ( g2c3g_t *ctx, g2c3g_cfg_t *cfg );

#### Example key functions :

- Function for send command.
> void g2c3g_send_command( g2c3g_t *ctx, char *command );
 
- Broker configuration.
> void g2c3g_send_broker_cfg( g2c3g_t *ctx, char *brc_key, char *brc_password );

- String parser function.
> g2c3g_error_t g2c3g_actuator_str_parser( char *rsp, char *act_ref, g2c3g_actuator_str_t *str_data );

## Examples Description

> This example reads and processes data from G2C 3G clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    g2c3g_cfg_t cfg;

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

    g2c3g_cfg_setup( &cfg );
    
    G2C3G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    g2c3g_init( &g2c3g, &cfg );
    
    //g2c3g_module_reset( &g2c3g );
    g2c3g_process( );
    while ( ( g2c3g_led_net( &g2c3g ) != 0 ) || ( g2c3g_led_conn( &g2c3g ) != 0 ) );
    g2c3g_process( );
    
    
    g2c3g_send_command( &g2c3g, G2C3G_AT );
    g2c3g_process( );
    
    g2c3g_send_command( &g2c3g, G2C3G_AT_GMR );
    g2c3g_process( );

    g2c3g_send_command( &g2c3g, G2C3G_AT_CEN );
    g2c3g_process( );
    
    g2c3g_send_operator_cfg( &g2c3g, OPERATOR_APN, OPERATOR_USERNAME, OPERATOR_PASSWORD );
    
    g2c3g_process( );
    g2c3g_send_command( &g2c3g, G2C3G_AT_NWC );
    g2c3g_process( );
    
    while ( g2c3g_led_net( &g2c3g  ) != 1 );
    
    g2c3g_send_broker_cfg( &g2c3g, DEVICE_KEY, DEVICE_PASSWORD );
    g2c3g_process( );

    g2c3g_send_command( &g2c3g, G2C3G_AT_BRC );
    g2c3g_process( );

    while ( g2c3g_led_conn( &g2c3g ) != 1 );
    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    g2c3g_process( );
    actuator_demo( current_parser_buf );
    
    if ( send_data_cnt == 5 )
    {
       g2c3g_send_data_ref( &g2c3g, SENSOR_REF, &data_buf[ 0 ] );
       g2c3g_process( );
       g2c3g_send_command( &g2c3g, G2C3G_AT_PUB );
       g2c3g_process( );
       send_data_cnt = 0;
    }
    send_data_cnt++;
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.G2c3G

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

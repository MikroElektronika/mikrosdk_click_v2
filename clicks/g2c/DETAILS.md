
---
# G2C click

Go to Cloud (G2C) click is a gateway Click board™ which provides a simple and reliable connection to the Click Cloud platform.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/g2c_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/g2c-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the G2C Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for G2C Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void g2c_cfg_setup ( g2c_cfg_t *cfg ); 
 
- Initialization function.
> G2C_RETVAL g2c_init ( g2c_t *ctx, g2c_cfg_t *cfg );

#### Example key functions :

- Function for send command.
> void g2c_send_command ( g2c_t *ctx, char *command );
 
- Send data reference.
> void g2c_send_data_ref(  g2c_t *ctx, char *reference_buf, char *data_buf );

- String parser function.
> g2c_error_t g2c_actuator_str_parser ( char *rsp, char *act_ref, g2c_actuator_str_t *str_data );

## Examples Description

> This example reads and processes data from G2C clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    g2c_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    g2c_cfg_setup( &cfg );
    G2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    g2c_init( &g2c, &cfg );

    // Power module.

    g2c_module_power( &g2c, true, 0 );
    g2c_reset( &g2c );
    
    // Send command.

    log_printf( &logger, ">> ATE \r\n" );
    g2c_send_command( &g2c, ATE );
    Delay_ms( 3000 );
    g2c_process( );

    log_printf( &logger, ">> AT \r\n" );
    g2c_send_command( &g2c, AT );
    Delay_ms( 3000 );
    g2c_process( );

    log_printf( &logger, ">> AT_CEN \r\n" );
    g2c_send_command( &g2c, AT_CEN );
    g2c_process( );

    log_printf( &logger, ">> NETWORK \r\n" );
    g2c_send_operator_cfg( &g2c, NETWORK_USERNAME, NETWORK_PASSWORD );
    g2c_process( );

    log_printf( &logger, ">> AT NWC \r\n" );
    g2c_send_command( &g2c, AT_NWC );
    g2c_process( );

    log_printf( &logger, ">> DEVICE \r\n" );
    g2c_send_broker_cfg( &g2c, DEVICE_KEY, DEVICE_PASSWORD );
    g2c_process( );

    log_printf( &logger, ">> AT BRC \r\n" );
    g2c_send_command( &g2c, AT_BRC ); 
    g2c_process( );

    Delay_ms( 3000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c


void application_task ( void )
{
    g2c_process( );
    actuator_demo( current_parser_buf );
    
    if ( send_data_cnt == 5 )
    {
       log_printf( &logger, ">> ACTUATOR REF \r\n" );  
       g2c_send_data_ref( &g2c, ACTUATOR_STR_REF, data_buf );
       g2c_process( );

       log_printf( &logger, ">> AT PUB \r\n" );
       g2c_send_command( &g2c, AT_PUB );
       g2c_process( );
       send_data_cnt = 0;
    }
    send_data_cnt++;
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.G2C

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

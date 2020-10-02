\mainpage Main Page
 
---
# LTE IoT click

LTE IoT click is a Click board™ that allows connection to the LTE and 2G networks.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/lte-iot-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the LteIot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LteIot Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lteiot_cfg_setup ( lteiot_cfg_t *cfg ); 
 
- Initialization function.
> LTEIOT_RETVAL lteiot_init ( lteiot_t *ctx, lteiot_cfg_t *cfg );

#### Example key functions :

- Power module.
> void lteiot_module_power( lteiot_t *ctx, uint8_t power_state );

- Send command.
> void lteiot_send_command ( lteiot_t *ctx, char *command );

## Examples Description

> This example reads and processes data from LTE IoT clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lteiot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lteiot_cfg_setup( &cfg );
    LTEIOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lteiot_init( &lteiot, &cfg );

    lteiot_module_power( &lteiot, LTEIOT_MODULE_POWER_ON );

    // MODULE INIT
    
    lteiot_send_command( &lteiot, LTEIOT_AT );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_ATE1 );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_CMEE );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_CGATT );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_CEREG );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_COPS );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_COPS_1 );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USOCR );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USOST );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USORF );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USOCL );
    lteiot_process( );
    Delay_1sec( );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    if ( send_data_cnt == 5 )
    {
        lteiot_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LteIot

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

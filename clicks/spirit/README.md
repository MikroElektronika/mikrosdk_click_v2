\mainpage Main Page
 
---
# Spirit click

SPIRIT click carries the SP1ML 868MHz ultra low-power RF module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/spirit-click-group.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/spirit-click>)

[click Product page](<https://www.mikroe.com/spirit-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Spirit Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Spirit Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void spirit_cfg_setup ( spirit_cfg_t *cfg ); 
 
- Initialization function.
> SPIRIT_RETVAL spirit_init ( spirit_t *ctx, spirit_cfg_t *cfg );

#### Example key functions :

- Function for power module
> void spirit_power_module ( spirit_t *ctx, uint8_t power_state );
 
- function for software reset
> void spirit_set_mode ( spirit_t *ctx, uint8_t mode );

- Send command
> void spirit_send_command ( spirit_t *ctx, char *command );

## Examples Description

> This example reads and processes data from Spirit clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power, reset and set module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    spirit_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    spirit_cfg_setup( &cfg );
    SPIRIT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spirit_init( &spirit, &cfg );

    spirit_power_module( &spirit, SPIRIT_MODULE_WAKE_UP );
    spirit_reset( &spirit );
    spirit_set_mode( &spirit, SPIRIT_OPERATING_MODE );
    log_printf( &logger, "---- SPIRIT POWER ON ---- \r\n" );

    Delay_ms( 1500 );

    spirit_send_command( &spirit, SPIRIT_CMD_READ_MODULE_VERSION );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_WRITE_CFG_TXRX_LED );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_STORE_CURRENT_CONFIG );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_READ_ALL_CONFIG_REG );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_ENTER_OPERATING_MODE );
    spirit_process( );

    Delay_ms( 1000 );

    log_printf( &logger, "---- SPIRIT START TASK ---- \r\n" );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    spirit_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITER 
    spirit_send_command( &spirit, DATA_TO_BE_SENT );
    spirit_process( );
    Delay_ms( 1000 );
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Spirit

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

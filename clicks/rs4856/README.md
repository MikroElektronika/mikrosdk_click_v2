\mainpage Main Page
 
---
# RS485 6 click

RS485 6 Click offers a half-duplex RS-485 communication with integrated surge protection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs4856_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/rs485-6-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs4856 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs4856 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs4856_cfg_setup ( rs4856_cfg_t *cfg ); 
 
- Initialization function.
> RS4856_RETVAL rs4856_init ( rs4856_t *ctx, rs4856_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> uint16_t rs4856_generic_read ( rs4856_t *ctx, char *data_buf, uint16_t max_len );
 
- Sets RE pin to high or low state
> void rs4856_re_pin_set (rs4856_t *ctx,  uint8_t pin_state );

- Sets DE pin to high or low state
> void rs4856_de_pin_set ( rs4856_t *ctx,  uint8_t pin_state );

## Examples Description

> This example reads and processes data from RS485 6 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4856_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs4856_cfg_setup( &cfg );
    RS4856_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4856_init( &rs4856, &cfg );

#ifdef DEMO_APP_RECEIVER
    rs4856_re_pin_set( &rs4856, RS4856_PIN_STATE_LOW );
    rs4856_de_pin_set( &rs4856, RS4856_PIN_STATE_LOW );
#endif

#ifdef DEMO_APP_TRANSMITER
    rs4856_re_pin_set( &rs4856, RS4856_PIN_STATE_HIGH );
    rs4856_de_pin_set( &rs4856, RS4856_PIN_STATE_HIGH );
#endif  
    log_info( &logger, " Start sending info" );  
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4856_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    rs4856_send_command( &rs4856, TEXT_TO_SEND );
    rs4856_process( );
    Delay_ms( 2000 ); 
#endif    
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs4856

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

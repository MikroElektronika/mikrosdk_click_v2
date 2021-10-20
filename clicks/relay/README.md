\mainpage Main Page
 
 

---
# Relay click

Relay click is a dual relay Click board, which can be operated by the host MCU. This Click board offers an elegant and easy solution for controlling a wide range of high power applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/relay_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/relay-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Relay Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Relay Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void relay_cfg_setup ( relay_cfg_t *cfg ); 
 
- Initialization function.
> RELAY_RETVAL relay_init ( relay_t *ctx, relay_cfg_t *cfg );

- Click Default Configuration function.
> void relay_default_cfg ( relay_t *ctx );


#### Example key functions :

- Relay set state
> void relay_set_state ( relay_t *ctx, uint8_t relay, uint8_t state );

## Examples Description

> Demo application is used to shows basic controls Relay click

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects. 
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    relay_cfg_t cfg;

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

    relay_cfg_setup( &cfg );
    RELAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay_init( &relay, &cfg );
    
    relay_default_cfg ( &relay );
    Delay_ms( 1500 );
}
```

### Application Task

> Alternately sets relays to ON-OFF state...

```c
void application_task ( void )
{
    uint8_t cnt;
    
    //  Task implementation.
    
    for ( cnt = 1; cnt <= 2; cnt++)
    {
        log_info( &logger, "*** Relay %d state is ON \r\n", cnt);
        relay_set_state( &relay, cnt, RELAY_STATE_ON );
        Delay_ms ( 1000 );
        log_info( &logger, "*** Relay %d state is OFF \r\n", cnt);
        relay_set_state( &relay, cnt, RELAY_STATE_OFF );
        Delay_ms ( 200 );
    }
    
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay

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

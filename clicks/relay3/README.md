\mainpage Main Page
 
---
# Relay 3 click

Relay click 3 is a dual relay Click board, featuring two single-pole double-throw relays which can be operated by output pins of the host microcontroller (MCU). It offers an elegant and easy solution for controlling a wide range of power applications. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/relay3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/relay-3-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Relay3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Relay3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void relay3_cfg_setup ( relay3_cfg_t *cfg ); 
 
- Initialization function.
> RELAY3_RETVAL relay3_init ( relay3_t *ctx, relay3_cfg_t *cfg );

#### Example key functions :

- This function turns on either the 1st or the 2nd relay on the click.
> void relay3_relay_on ( uint8_t relay );
 
- This function turns off either the 1st or the 2nd relay on the click.
> relay3_relay_off ( uint8_t relay );

## Examples Description

> This example starts off with the initialization and configuration of the click and logger
  modules and later on showcases how to turn specified relays ON/OFF using the output pins.

**The demo application is composed of two sections :**

### Application Init 

> This function initialises and configures the logger and click modules.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    relay3_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    relay3_cfg_setup( &cfg );
    RELAY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay3_init( &relay3, &cfg );
}
  
```

### Application Task

> This function turns on the 1st and the 2nd relay and then turns them both off.

```c

void application_task ( )
{
    case_1( );
    Delay_ms ( 1000 );

    case_2( );
    Delay_ms ( 1000 );

    case_3( );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay3

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

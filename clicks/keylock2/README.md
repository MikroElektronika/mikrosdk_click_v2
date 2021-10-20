\mainpage Main Page
 
 

---
# Key Lock 2 click

Keylock 2 Click carries antistatic process sealed keylock mechanism that has three positions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/keylock2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/keylock-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the KeyLock2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for KeyLock2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void keylock2_cfg_setup ( keylock2_cfg_t *cfg ); 
 
- Initialization function.
> KEYLOCK2_RETVAL keylock2_init ( keylock2_t *ctx, keylock2_cfg_t *cfg );

- Click Default Configuration function.
> void keylock2_default_cfg ( keylock2_t *ctx );


#### Example key functions :

- This function gets states of pins out1, out2 and out3 on Key Lock 2 click.
> uint8_t keylock2_get_pin_state ( uint8_t pin );
 
- This function gets Position (First, Second, Third) of pins 
out1, out2 and out3 on Key Lock 2 click.
> uint8_t keylock2_get_position ( keylock2_t *ctx )


## Examples Description

> Keylock 2 Click carries antistatic process sealed keylock mechanism that has three positions.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    keylock2_cfg_t cfg;

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

    keylock2_cfg_setup( &cfg );
    KEYLOCK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    keylock2_init( &keylock2, &cfg );
}
```

### Application Task

> Checks the current key position and logs the current position on the USB UART.

```c
void application_task ( void )
{
    key_position = keylock2_get_position( &keylock2 );
    
    if ( old_position != key_position )
    {
        if ( key_position == KEYLOCK2_POSITION_1 )
        {
            log_printf( &logger, " -- FIRST position -- \r\n " );
        }
        else if ( key_position == KEYLOCK2_POSITION_2 )
        {
            log_printf( &logger, " -- SECOND position -- \r\n " );
        }
        else
        {
            log_printf( &logger, " -- THIRD position -- \r\n " );
        }
    }
    old_position = key_position;

    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.KeyLock2

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

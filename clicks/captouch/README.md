\mainpage Main Page
 
 

---
# Cap Touch click

Cap Touch click is a capacitive touch sensing button, integrated on a click board. It can be activated by touch.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/captouch_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-touch-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the CapTouch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapTouch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void captouch_cfg_setup ( captouch_cfg_t *cfg ); 
 
- Initialization function.
> CAPTOUCH_RETVAL captouch_init ( captouch_t *ctx, captouch_cfg_t *cfg );

- Click Default Configuration function.
> void captouch_default_cfg ( captouch_t *ctx );


#### Example key functions :

- Select mode
> void captouch_set_mode( captouch_t *ctx, uint8_t mode );
 
- Get touch state
> uint8_t captouch_get_touch( captouch_t *ctx );

## Examples Description

>  Demo application is used to shows basic controls Cap Touch click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch_cfg_t cfg;

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

    captouch_cfg_setup( &cfg );
    CAPTOUCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch_init( &captouch, &cfg );

    captouch_default_cfg( &captouch );
}
```

### Application Task

> Checks for a new touch event. If so, prints the message to USBUART.

```c
void application_task ( void )
{
    uint8_t touch;

    //  Task implementation.

    touch = captouch_get_touch( &captouch );
    if ( touch != 0 )
    {
        log_printf( &logger, "-- New Touch\r\n" );
        Delay_ms( 200 );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch

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

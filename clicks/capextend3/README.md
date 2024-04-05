\mainpage Main Page
 
 

---
# Cap Extend 3 click

Cap Extend 3 click features four capacitive sensor pads integrated on the PCB, that can sense touch through a variety of different materials.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/capextend3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-extend-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the CapExtend3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapExtend3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void capextend3_cfg_setup ( capextend3_cfg_t *cfg ); 
 
- Initialization function.
> CAPEXTEND3_RETVAL capextend3_init ( capextend3_t *ctx, capextend3_cfg_t *cfg );

#### Example key functions :

- Function reads state of AN pin
> uint8_t capextend3_Touch_0 ( capextend3_t *ctx );
 
- Function reads state of RST pin
> uint8_t capextend3_Touch_1 ( capextend3_t *ctx );

- Function reads state of CS pin
> uint8_t capextend3_Touch_2 ( capextend3_t *ctx );

## Examples Description

> This application features four capacitive sensor pads, that can sense touch through a variety of different materials.

**The demo application is composed of two sections :**

### Application Init 

> Initialize GPIO Driver

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    capextend3_cfg_t cfg;

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
    capextend3_cfg_setup( &cfg );
    CAPEXTEND3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capextend3_init( &capextend3, &cfg );
}
```

### Application Task

> Depending on which button is touched the usb uart will show number of that button.

```c
void application_task ( void )
{
    uint8_t touch_0;
    uint8_t touch_1;
    uint8_t touch_2;
    uint8_t touch_3;
    uint8_t touch_4;

    touch_0 = capextend3_touch_0( &capextend3 );
    touch_1 = capextend3_touch_1( &capextend3 );
    touch_2 = capextend3_touch_2( &capextend3 );
    touch_3 = capextend3_touch_3( &capextend3 );
    touch_4 = capextend3_touch_4( &capextend3 );
    
    if ( touch_2 == 0 )
    {
       log_printf( &logger, "Active Guard\r\n" ); 
    }
    if ( touch_0 == 0 )
    {
       log_printf( &logger, "Touch 0 \r\n" ); 
    }
    if ( touch_1 == 0 )
    {
       log_printf( &logger, "Touch 1 \r\n" ); 
    }
    if ( touch_3 == 0 )
    {
       log_printf( &logger, "Touch 3 \r\n" ); 
    }
    if ( touch_4 == 0 )
    {
       log_printf( &logger, "Touch 4 \r\n" ); 
    }
    if ( ( touch_0 && touch_1 && touch_2 && touch_3 && touch_4 ) == 0 ) 
    {
        log_printf( &logger, "------------------------\r\n" ); 
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapExtend3

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

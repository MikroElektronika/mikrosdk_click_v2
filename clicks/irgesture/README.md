\mainpage Main Page
 
 

---
# IR Gesture click

IR Gesture Click is a mikroBUS add-on board that enables contactless gesture recognition, along with ambient light and proximity sensing capabilities with the APDS-9960 IC. This sensor integrates an LED and four directional photodiodes that receive the reflecting light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irgesture_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ir-gesture-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the IrGesture Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrGesture Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irgesture_cfg_setup ( irgesture_cfg_t *cfg ); 
 
- Initialization function.
> IRGESTURE_RETVAL irgesture_init ( irgesture_t *ctx, irgesture_cfg_t *cfg );

- Click Default Configuration function.
> void irgesture_default_cfg ( irgesture_t *ctx );


#### Example key functions :

- Function starts the gesture recognition engine on the APDS-9960 IC on IR Gesture Click.
> void irgesture_enable_gesture_sensor ( irgesture_t *ctx )

- Function processes a gesture event and returns best guessed position engine on IR Gesture Click.
> uint8_t irgesture_detect_gesture ( irgesture_t *ctx );
 
- Function compares input data and returns position of gesture
> static uint8_t compare_data ( uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3 )


## Examples Description

> This Click enables contactless gesture recognition: 
> basic directional swipes (up, down, left or right).  

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, set default configuration, enable geasture sensor and start write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irgesture_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    irgesture_cfg_setup( &cfg );
    IRGESTURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irgesture_init( &irgesture, &cfg );
    irgesture_default_cfg( &irgesture );
}
  
```

### Application Task

> This is a example which demonstrates the use of IR Gesture Click board.
> IR Gesture Click detects gestures and sends the movement to terminal every 1 second.

```c

void application_task ( void )
{
    position = irgesture_detect_gesture( &irgesture );

    if ( position_old != position )
    {
        if ( position == IRGESTURE_FAR )
        {
            log_printf( &logger, "       F A R        \r\n" );
        }
        if ( position == IRGESTURE_RIGHT )
        {
            log_printf( &logger, "     R I G H T      \r\n" );
        }
        if ( position == IRGESTURE_LEFT )
        {
            log_printf( &logger, "      L E F T       \r\n" );
        }
        if ( position == IRGESTURE_UP )
        {
            log_printf( &logger, "        U P         \r\n" );
        }
        if ( position == IRGESTURE_DOWN )
        {
            log_printf( &logger, "      D O W N       \r\n" );
        }
        if ( position == IRGESTURE_NEAR )
        {
            log_printf( &logger, "      N E A R       \r\n" );
        }

        position_old = position;
        log_printf( &logger, "--------------------\r\n" );

        Delay_ms( 1000 );
    }
}

```
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrGesture

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

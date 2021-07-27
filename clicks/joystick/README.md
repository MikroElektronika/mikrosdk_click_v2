\mainpage Main Page
 
 

---
# Joystick click

Joystick click is a smart navigation key concept based on contactless, magnetic movement detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/joystick_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/joystick-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Joystick Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Joystick Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void joystick_cfg_setup ( joystick_cfg_t *cfg ); 
 
- Initialization function.
> JOYSTCIK_RETVAL joystick_init ( joystick_t *ctx, joystick_cfg_t *cfg );

- Click Default Configuration function.
> void joystick_default_cfg ( joystick_t *ctx );


#### Example key functions :

- Get joystick position function
> uint8_t joystick_get_position( joystick_t *ctx );
 
- Get state of Joystick button function
> uint8_t joystick_press_button( joystick_t *ctx );

- General soft reset function
> void joystick_soft_reset( joystick_t *ctx );

## Examples Description

> This application configures and enables use of the joystick.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - device, sets default configuration and starts write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    joystick_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    joystick_cfg_setup( &cfg );
    JOYSTCIK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    joystick_init( &joystick, &cfg );

    Delay_100ms( );

    joystick_default_cfg( &joystick );

    log_printf( &logger,  "*********************\r\n" );
    log_printf( &logger,  "    Configuration    \r\n" );
    log_printf( &logger,  "*********************\r\n" );
    log_printf( &logger,  "    Joystick Click   \r\n" );
    log_printf( &logger,  "*********************\r\n" );

    Delay_100ms( );
}
  
```

### Application Task

> This is a example which demonstrates the use of Joystick Click board.
> Joystick Click communicates with register via I2C by write and read from register,
> read joystick position and press button state.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when the sensor is triggered.

```c

void application_task ( void ) 
{
    //  Task implementation.

    button_state = joystick_press_button( &joystick );

    position = joystick_get_position( &joystick );

    Delay_10ms( );

    if ( ( button_state == 1 ) && ( button_state_old == 0 ) )
    {
        button_state_old = 1;

        log_printf( &logger, "  Button is pressed \r\n" );
        log_printf( &logger, "*********************\r\n" );
    }

    if ( ( button_state == 0 ) && ( button_state_old == 1 ) )
    {
        button_state_old = 0;
    }

    if ( position_old != position )
    {
        switch ( position )
        {
            case 0 :
            {
                log_printf( &logger,"    Start position    \r\n" );
                break;
            }
            case 1 :
            {
                log_printf( &logger, "         Top    \r\n" );
                break;
            }
            case 2 :
            {
                log_printf( &logger, "      Top-Right    \r\n" );
                break;
            }
            case 3 :
            {
                log_printf( &logger, "        Right    \r\n" );
                break;
            }
            case 4 :
            {
                log_printf( &logger, "     Bottom-Right    \r\n" );
                break;
            }
            case 5 :
            {
                log_printf( &logger, "        Bottom    \r\n" );
                break;
            }
            case 6 :
            {
                log_printf( &logger, "     Bottom-Left    \r\n" );
                break;
            }
            case 7 :
            {
                log_printf( &logger, "         Left    \r\n" );
                break;
            }
            case 8 :
            {
                log_printf( &logger, "       Top-Left    \r\n" );
                break;
            }
        }

        log_printf( &logger, "*********************\r\n" );

        position_old = position;

        Delay_100ms();
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Joystick

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

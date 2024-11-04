\mainpage Main Page
 
 

---
# Tilt Click

Tilt Click carries RPI-1035, a 4-directional optical tilt sensor. This type of sensor provides positional feedback for left, right, backward or forward movement (tilt).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tilt_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/tilt-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Tilt Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Tilt Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tilt_cfg_setup ( tilt_cfg_t *cfg ); 
 
- Initialization function.
> TILT_RETVAL tilt_init ( tilt_t *ctx, tilt_cfg_t *cfg );

- Click Default Configuration function.
> void tilt_default_cfg ( tilt_t *ctx );


#### Example key functions :

- Check the tilt movement's direction function.
> uint8_t tilt_direction ( tilt_t *ctx );
 
## Examples Description

> 
> This is a example which demonstrates the use of Tilt Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tilt_cfg_t cfg;

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
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    tilt_cfg_setup( &cfg );
    TILT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tilt_init( &tilt, &cfg );
    
    tilt_direction_old = 0;
    
    log_printf(&logger, "-------------\r\n");
    log_printf(&logger, " Tilt  Click \r\n");
    log_printf(&logger, "-------------\r\n");
    Delay_ms ( 100 );
}
  
```

### Application Task

>
> Detect the movement's direction 
> of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt Click board.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when the movement's direction is changed.
> 

```c

void application_task ( void )
{
    tilt_direction = tilt_direction( &tilt );

    if ( tilt_direction_old != tilt_direction )
    {
        if ( tilt_direction == TILT_LEFT_DETECTION )
        {
            log_printf(&logger, "    LEFT     \r\n");
        }

        if ( tilt_direction == TILT_RIGHT_DETECTION )
        {
            log_printf(&logger, "    RIGHT    \r\n");
        }

        if ( tilt_direction == TILT_UP_DETECTION )
        {
            log_printf(&logger, "     UP      \r\n");
        }

        if ( tilt_direction == TILT_DOWN_DETECTION )
        {
            log_printf(&logger, "    DOWN     \r\n");
        }

        tilt_direction_old = tilt_direction;
        log_printf(&logger, "-------------\r\n");
    }
} 

```

## Note


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

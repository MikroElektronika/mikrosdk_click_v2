\mainpage Main Page
 
 

---
# Thumbstick click

Thumbstick click is a high precision input device. It features a dual axis, spring return, pushbutton enabled joystick (similar to the ones used on joypads on popular gaming consoles), and a MCP3204 12-bit A/D converter.

It features a dual axis, spring return, pushbutton enabled joystick, and a MCP3204 12-bit A/D converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thumbstick_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thumbstick-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Thumbstick Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thumbstick Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thumbstick_cfg_setup ( thumbstick_cfg_t *cfg ); 
 
- Initialization function.
> THUMBSTICK_RETVAL thumbstick_init ( thumbstick_t *ctx, thumbstick_cfg_t *cfg );

#### Example key functions :

- Get state of thumbstick button function
> uint8_t thumbstick_button_state( thumbstick_t *ctx );
 
- Get thumbstick position by axis function
> void thumbstick_get_position ( thumbstick_t *ctx, thumbstick_position_t *position );

- Generic read 2 byte of data function
uint16_t thumbstick_read_rawadc ( thumbstick_t *ctx, uint8_t type, uint8_t channel );

## Examples Description

> The demo application shows clickboard axis postioning and button state.

**The demo application is composed of two sections :**

### Application Init 

> Initialization of click board's and log's objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thumbstick_cfg_t cfg;

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

    thumbstick_cfg_setup( &cfg );
    THUMBSTICK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thumbstick_init( &thumbstick, &cfg );
    
    thumbstick_set_sensitivity( POSTION_SENS_DEFAULT );
    
    thumbstick_get_position( &thumbstick, &old_pos );
    old_butt_state = thumbstick_button_state( &thumbstick );
    timer_cnt = 0;
    change_state = false;
}
```

### Application Task


>It reads the position of the thumbstick:
    - You will get data on log on every change of thumbstick axis position, or if you hold 
        thumbstick in one postion it will repeat the same log when timer reaches timeout.
    - You will get data on log whenever you press thumbstick button and release it.

```c
void application_task ( void )
{
    //Button pressed
    button_state = thumbstick_button_state( &thumbstick );

    if ( old_butt_state != button_state )
    {
        if ( button_state == THUMBSTICK_PRESS_BUTTON )
        {
            log_printf( &logger, ">> Button is pressed \r\n" );
            Delay_ms( 100 );
        }
        else
        {
            log_printf( &logger, ">> Button is released \r\n" );
            Delay_ms( 100 );
        }
        old_butt_state = button_state;
    }

    //Thumbstick postion
    thumbstick_get_position( &thumbstick, &thumbstick_pos );
    
    if ( ( old_pos.vertical != thumbstick_pos.vertical ) || ( timer_cnt >= TIMER_FLAG ) )
    {
        if ( thumbstick_pos.vertical == THUMBSTICK_POSITION_TOP )
        {
            log_printf( &logger, ">> TOP \r\n" );
            change_state = true;
        }
        else if ( thumbstick_pos.vertical == THUMBSTICK_POSITION_BOTTOM )
        {
            log_printf( &logger, ">> BOTTOM \r\n" );
            change_state = true;
        }
        
        old_pos = thumbstick_pos;
    }
    
    if ( (old_pos.horizontal != thumbstick_pos.horizontal ) || ( timer_cnt >= TIMER_FLAG )  )
    {
        if ( thumbstick_pos.horizontal == THUMBSTICK_POSITION_LEFT )
        {
            log_printf( &logger, ">> LEFT \r\n" );
            change_state = true;
        }
        else if ( thumbstick_pos.horizontal == THUMBSTICK_POSITION_RIGHT )
        {
            log_printf( &logger, ">> RIGHT \r\n" );
            change_state = true;
        }
        
        old_pos = thumbstick_pos;
    }
    
    if ( ( timer_cnt >= TIMER_FLAG ) || ( change_state == true )  )
    {
        timer_cnt = 0;
        change_state = false;
    }
    
    timer_cnt++;
    Delay_ms( 1 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thumbstick

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

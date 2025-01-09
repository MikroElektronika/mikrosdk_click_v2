
---
# Thumbstick Click

> [Thumbstick Click](https://www.mikroe.com/?pid_product=MIKROE-1627) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1627&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> The demo application shows Clickboard axis postioning and button state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thumbstick

### Example Key Functions

- `thumbstick_cfg_setup` Config Object Initialization function. 
```c
void thumbstick_cfg_setup ( thumbstick_cfg_t *cfg );
``` 
 
- `thumbstick_init` Initialization function. 
```c
err_t thumbstick_init ( thumbstick_t *ctx, thumbstick_cfg_t *cfg );
```

- `thumbstick_button_state` Get state of thumbstick button function. 
```c
uint8_t thumbstick_button_state ( thumbstick_t *ctx );
```
 
- `thumbstick_get_position` Get thumbstick position by axis function. 
```c
void thumbstick_get_position ( thumbstick_t *ctx, thumbstick_position_t *position );
```

- Generic read 2 byte of data function
uint16_t thumbstick_read_rawadc ( thumbstick_t *ctx, uint8_t type, uint8_t channel );

### Application Init

> Initialization of Click board's and log's objects.

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


> It reads the position of the thumbstick:
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
            Delay_ms ( 100 );
        }
        else
        {
            log_printf( &logger, ">> Button is released \r\n" );
            Delay_ms ( 100 );
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
    Delay_ms ( 1 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---

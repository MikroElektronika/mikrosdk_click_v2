
---
# TouchKey Click

> [TouchKey Click](https://www.mikroe.com/?pid_product=MIKROE-1906) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1906&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application has four capacitive pads powered by TTP224, a touchpad detector IC. 
> Capacitive buttons like these can be toggled even when placed under a layer of glass or paper.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchKey

### Example Key Functions

- `touchkey_cfg_setup` Config Object Initialization function. 
```c
void touchkey_cfg_setup ( touchkey_cfg_t *cfg );
``` 
 
- `touchkey_init` Initialization function. 
```c
err_t touchkey_init ( touchkey_t *ctx, touchkey_cfg_t *cfg );
```

- `touchkey_default_cfg` Click Default Configuration function. 
```c
void touchkey_default_cfg ( touchkey_t *ctx );
```

- `touchkey_a` Function gets state of "a" (RST) pin on TouchKey Click board. . 
```c
uint8_t touchkey_a ( touchkey_t *ctx );
```

- `touchkey_b` Function gets state of "b" (AN) pin on TouchKey Click board. 
```c
uint8_t touchkey_b ( touchkey_t *ctx );
```

- `touchkey_c` Function gets state of "c" (PWM) pin on TouchKey Click board. 
```c
uint8_t touchkey_c ( touchkey_t *ctx );
```

- `touchkey_d` Function gets state of "d" (INT) pin on TouchKey Click board. 
```c
uint8_t touchkey_d ( touchkey_t *ctx );
```

### Application Init

> Initialization driver enables GPIO and also starts write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey_cfg_t cfg;

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

    touchkey_cfg_setup( &cfg );
    TOUCHKEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey_init( &touchkey, &cfg );
}
```

### Application Task

> This example demonstrates the use of TouchKey Click board.
> Detects whether any of the keys is pressed. 
> Results are being sent to the Usart Terminal, where you can track changes.

```c
void application_task ( void )
{
    
    key_state = touchkey_a( &touchkey ) | touchkey_b( &touchkey ) | touchkey_c( &touchkey ) | touchkey_d( &touchkey );

    if( key_state == 1 && key_state_old == 0  )
    {
        log_info( &logger,"Pressed : " );

        if( touchkey_a( &touchkey ) )
        {
            log_info( &logger, "A " );
        }
        if( touchkey_b( &touchkey) )
        {
            log_info( &logger, "B " );
        }
        if( touchkey_c( &touchkey ) )
        {
            log_info( &logger, "C " );;
        }
        if( touchkey_d( &touchkey ) )
        {
            log_info( &logger, "D " );
        }

        log_info( &logger, "" );
        key_state_old = 1;
    }
    if ( key_state == 0 && key_state_old == 1 )
    {
        key_state_old = 0;
    }

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

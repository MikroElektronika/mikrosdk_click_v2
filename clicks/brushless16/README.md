
---
# Brushless 16 Click

> [Brushless 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4742) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4742&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example showcases ability to enable and disable motor output,
and check the status pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless16

### Example Key Functions

- `brushless16_cfg_setup` Config Object Initialization function.
```c
void brushless16_cfg_setup ( brushless16_cfg_t *cfg );
```

- `brushless16_init` Initialization function.
```c
err_t brushless16_init ( brushless16_t *ctx, brushless16_cfg_t *cfg );
```

- `brushless16_set_en` Set en pin state
```c
void brushless16_set_en ( brushless16_t *ctx, uint8_t state );
```

- `brushless16_get_rd` Get rd pin state.
```c
uint8_t brushless16_get_rd ( brushless16_t *ctx );
```

- `brushless16_get_fg` Get fg pin state.
```c
uint8_t brushless16_get_fg ( brushless16_t *ctx );
```

### Application Init

> Initializon of UART module for log and pins for motor control.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless16_cfg_t brushless16_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    brushless16_cfg_setup( &brushless16_cfg );
    BRUSHLESS16_MAP_MIKROBUS( brushless16_cfg, MIKROBUS_1 );
    if ( brushless16_init( &brushless16, &brushless16_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks state of information pins every ms, and stop and start motor
output every second.

```c
void application_task ( void ) 
{
    static uint16_t timer = 5000;
    static uint8_t state = 1;
    
    if ( brushless16_get_rd( &brushless16 ) )
    {
        log_info( &logger, " Motor Lock" );
        Delay_ms ( 500 );
    }
    
    if ( brushless16_get_fg( &brushless16 ) )
    {
        log_info( &logger, " FG" );
        Delay_ms ( 500 );
    }
    
    if ( !( timer-- ) )
    {
        timer = 5000;
        
        if ( state )
        {
            log_info( &logger, " Motor stop" );
        }
        else
        {
            log_info( &logger, " Motor rotating" );
        }
        
        brushless16_set_en( &brushless16, state );
        state = !state;
    }
    
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

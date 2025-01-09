
---
# TouchClamp Click

> [TouchClamp Click](https://www.mikroe.com/?pid_product=MIKROE-2294) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2294&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This demo-app shows the touch position using TouchClamp Click.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchClamp

### Example Key Functions

- `touchclamp_cfg_setup` Config Object Initialization function. 
```c
void touchclamp_cfg_setup ( touchclamp_cfg_t *cfg );
``` 
 
- `touchclamp_init` Initialization function. 
```c
err_t touchclamp_init ( touchclamp_t *ctx, touchclamp_cfg_t *cfg );
```

- `touchclamp_default_cfg` Click Default Configuration function. 
```c
void touchclamp_default_cfg ( touchclamp_t *ctx );
```

- `touchclamp_get_touch_data` Get touch data function. 
```c
uint16_t touchclamp_get_touch_data ( touchclamp_t *ctx );
```

### Application Init

>
> Configuring Clicks and log objects.
> Setting the Click in the default configuration.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchclamp_cfg_t cfg;

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
    log_printf( &logger, " Application Init \r\n" );

    //  Click initialization.

    touchclamp_cfg_setup( &cfg );
    TOUCHCLAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchclamp_init( &touchclamp, &cfg );
    Delay_ms ( 100 );
    
    touchclamp_soft_reset( &touchclamp );
    Delay_ms ( 100 );
    
    touchclamp_default_cfg( &touchclamp );
    Delay_ms ( 100 );
    
    touch_data_old = TOUCHCLAMP_NO_TOUCH;
    
    log_printf( &logger, "-------------------\r\n" );
    log_printf( &logger, " Touch Clamp Click \r\n" );
    log_printf( &logger, "-------------------\r\n" );
}
```

### Application Task

>
> Detect and dispay touch position when the Click is triggered.
> 

```c
void application_task ( void )
{
    touch_data = touchclamp_get_touch_data( &touchclamp );
    
    if ( touch_data_old != touch_data )
    {
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_H )
            log_printf( &logger, "  - - - - - - - H\r\n" );
            
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_G )
            log_printf( &logger, "  - - - - - - G -\r\n" );
            
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_F )
            log_printf( &logger, "  - - - - - F - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_E )                       
            log_printf( &logger, "  - - - - E - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_D )                       
            log_printf( &logger, "  - - - D - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_C )                       
            log_printf( &logger, "  - - C - - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_B )                       
            log_printf( &logger, "  - B - - - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_A )                       
            log_printf( &logger, "  A - - - - - - -\r\n" );
      
        touch_data_old = touch_data;
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

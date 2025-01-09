
---
# Touchkey 2 Click

> [Touchkey 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2474) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2474&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : UART type

# Software Support

## Example Description

> This application is touch controller. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchkey2

### Example Key Functions

- `touchkey2_cfg_setup` Config Object Initialization function. 
```c
void touchkey2_cfg_setup ( touchkey2_cfg_t *cfg );
``` 
 
- `touchkey2_init` Initialization function. 
```c
err_t touchkey2_init ( touchkey2_t *ctx, touchkey2_cfg_t *cfg );
```

- `touchkey2_default_cfg` Click Default Configuration function. 
```c
void touchkey2_default_cfg ( touchkey2_t *ctx );
```

- `touchkey2_set_reset_pin` Set reset pin function. 
```c
void touchkey2_set_reset_pin ( touchkey2_t *ctx );
```
 
- `touchkey2_clear_reset_pin` Clear reset pin function. 
```c
void touchkey2_clear_reset_pin ( touchkey2_t *ctx );
```

- `touchkey2_target_reset` Reset function. 
```c
void touchkey2_target_reset ( touchkey2_t *ctx );
```

### Application Init

> Initalizes device and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey2_cfg_t cfg;

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

    touchkey2_cfg_setup( &cfg );
    TOUCHKEY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey2_init( &touchkey2, &cfg );
}
```

### Application Task

> Checks if new data byte have received in rx buffer (ready for reading),
  and if ready than reads one byte from rx buffer, that show if and what key is pressed. 

```c
void application_task ( void )
{
    char tmp;

    tmp = touchkey2_generic_single_read( &touchkey2 );
    
    if( tmp == 0x00 )
    {
        log_printf( &logger, "   Key released   %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x01 )
    {
        log_printf( &logger, "   Key A pressed %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x02 )
    {
        log_printf( &logger, "   Key B pressed %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x04 )
    {
        log_printf( &logger, "   Key C pressed %c\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x08 )
    {
        log_printf( &logger, "   Key D pressed \r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "   Error!!!   " );
        touchkey2_target_reset( &touchkey2 );
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

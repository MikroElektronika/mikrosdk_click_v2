
---
# MOTION Click

> [MOTION Click](https://www.mikroe.com/?pid_product=MIKROE-1589) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1589&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application detects any motion around it and shows message

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion

### Example Key Functions

- `motion_cfg_setup` Config Object Initialization function. 
```c
void motion_cfg_setup ( motion_cfg_t *cfg );
``` 
 
- `motion_init` Initialization function. 
```c
err_t motion_init ( motion_t *ctx, motion_cfg_t *cfg );
```

- `motion_default_cfg` Click Default Configuration function. 
```c
void motion_default_cfg ( motion_t *ctx );
```

- `motion_get_detected` Motion detected function. 
```c
motion_pin_state_t motion_get_detected ( motion_t *ctx );
```
 
- `motion_set_en_pin` Set states of the enable pin. 
```c
void motion_set_en_pin (  motion_t *ctx, motion_pin_state_t en_state );
```

### Application Init

> Initializes Driver enable's the motion detection.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    motion_cfg_t cfg;

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
    log_printf( &logger, "------------------------\r\n" );

    //  Click initialization.

    motion_cfg_setup( &cfg );
    MOTION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion_init( &motion, &cfg );
    log_printf( &logger, "      Motion Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );

    motion_default_cfg ( &motion );
    log_printf( &logger, "  Enable Motion sensor\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 );

    motion_state = MOTION_NO_DETECT;
    motion_old_state = MOTION_DETECTED;
}
```

### Application Task

> Detect the motion and send a notification to the UART.

```c
void application_task ( void )
{
    //  Task implementation.

    motion_state = motion_detected( &motion );

    if ( motion_state == MOTION_DETECTED &&  motion_old_state == MOTION_NO_DETECT )
    {
        motion_old_state = MOTION_DETECTED;
        log_printf( &logger, "  > Motion detected! <\r\n" );
        log_printf( &logger, "------------------------\r\n" );
   }

   if ( motion_old_state == MOTION_DETECTED &  motion_state == MOTION_NO_DETECT )
   {
        log_printf( &logger, "  There is no movement\r\n" );
        log_printf( &logger, "------------------------\r\n" );
        motion_old_state = MOTION_NO_DETECT;
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

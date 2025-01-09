
---
# UNI HALL Click

> [UNI HALL Click](https://www.mikroe.com/?pid_product=MIKROE-1647) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1647&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This is a example which demonstrates the use of UNI HALL Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UniHall

### Example Key Functions

- `unihall_cfg_setup` Config Object Initialization function. 
```c
void unihall_cfg_setup ( unihall_cfg_t *cfg );
``` 
 
- `unihall_init` Initialization function. 
```c
err_t unihall_init ( unihall_t *ctx, unihall_cfg_t *cfg );
```

- `unihall_default_cfg` Click Default Configuration function. 
```c
void unihall_default_cfg ( unihall_t *ctx );
```

- `unihall_detecting_magnetic_fields` Detecting north pole magnetic fields status function. 
```c
uint8_t unihall_detecting_magnetic_fields ( unihall_t *ctx );
```

### Application Init

>
> Initialization driver enable's - GPIO and start write log.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    unihall_cfg_t cfg;

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
    log_printf(&logger, " --- Application Init ---\r\n");

    //  Click initialization.

    unihall_cfg_setup( &cfg );
    UNIHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    unihall_init( &unihall, &cfg );

    unihall_state = UNIHALL_NORTH_POLE_DETECTED;
    unihall_state_old = UNIHALL_NORTH_POLE_DETECTED;

    log_printf(&logger, "---------------------------\r\n");
    log_printf(&logger, "        Initialization     \r\n");
    log_printf(&logger, "---------------------------\r\n");
    log_printf(&logger, " Detecting magnetic fields \r\n");
    log_printf(&logger, "---------------------------\r\n");

    Delay_ms ( 100 );
}
```

### Application Task

>
> Detect the north pole magnetic fields near the UNI HALL Click.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.
> 

```c
void application_task ( void )
{
    unihall_state = unihall_detecting_magnetic_fields( &unihall );

    if ( ( unihall_state == UNIHALL_NORTH_POLE_NOT_DETECTED ) && ( unihall_state_old == UNIHALL_NORTH_POLE_DETECTED ) )
    {
        unihall_state_old = UNIHALL_NORTH_POLE_NOT_DETECTED;
        log_printf(&logger, "      ~ NOT DETECTED ~\r\n");
    }

    if ( ( unihall_state == UNIHALL_NORTH_POLE_DETECTED ) && ( unihall_state_old == UNIHALL_NORTH_POLE_NOT_DETECTED ) )
    {
        
        log_printf(&logger, "        ~ DETECTED ~\r\n");
        unihall_state_old = UNIHALL_NORTH_POLE_DETECTED;
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

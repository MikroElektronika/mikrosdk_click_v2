
---
# Tamper 2 Click

> [Tamper 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2552) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2552&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application sets switch on ON or OFF.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tamper2

### Example Key Functions

- `tamper2_cfg_setup` Config Object Initialization function. 
```c
void tamper2_cfg_setup ( tamper2_cfg_t *cfg );
``` 
 
- `tamper2_init` Initialization function. 
```c
err_t tamper2_init ( tamper2_t *ctx, tamper2_cfg_t *cfg );
```

- `tamper2_get_on_state` Switch ON detect. 
```c
uint8_t tamper2_get_on_state ( tamper2_t *ctx );
```
 
- `tamper2_get_off_state` Switch OFF detect. 
```c
uint8_t tamper2_get_off_state ( tamper2_t *ctx );
```

### Application Init

> Sends HAL pointers

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    tamper2_cfg_t cfg;

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

    tamper2_cfg_setup( &cfg );
    TAMPER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tamper2_init( &tamper2, &cfg );
}
```

### Application Task

> Detects whether the state of switch on Tamper 2 Click is ON or OFF.

```c
void application_task ( )
{
    uint8_t on_state;
    uint8_t off_state;

    on_state = tamper2_get_on_state( &tamper2 );
    off_state = tamper2_get_off_state( &tamper2 );

    if ( on_state == 1 )
    {
        log_printf( &logger, "Tamper 2 Click is in ON state.\r\n" );
		
    }

    if ( off_state == 1 )
    {
       log_printf( &logger, "Tamper 2 Click is in OFF state.\r\n" );
		
    }

    Delay_ms ( 200 );
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

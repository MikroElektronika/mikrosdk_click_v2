
---
# REED Click

> [REED Click](https://www.mikroe.com/?pid_product=MIKROE-1998) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1998&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This is a example which demonstrates the use of REED Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Reed

### Example Key Functions

- `reed_cfg_setup` Config Object Initialization function. 
```c
void reed_cfg_setup ( reed_cfg_t *cfg );
``` 
 
- `reed_init` Initialization function. 
```c
err_t reed_init ( reed_t *ctx, reed_cfg_t *cfg );
```

- `reed_default_cfg` Click Default Configuration function. 
```c
void reed_default_cfg ( reed_t *ctx );
```

- `reed_get_status` Get magnetic detected status function. 
```c
uint8_t reed_get_status ( reed_t *ctx );
```

### Application Init

>
> Configuring Clicks and log objects.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    reed_cfg_t cfg;

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
    log_printf(&logger, "- Application Init -\r\n");

    //  Click initialization.

    reed_cfg_setup( &cfg );
    REED_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    reed_init( &reed, &cfg );

    reed_state = REED_NO_MAGNETIC_FIELD;
    reed_state_old = REED_NO_MAGNETIC_FIELD;

    log_printf(&logger, "--------------------\r\n");
    log_printf(&logger, "     REED Click\r\n");
    log_printf(&logger, "--------------------\r\n");
    Delay_100ms();
}
```

### Application Task

>
> Detect the magnetic field near the REED Click.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.
> 

```c
void application_task ( void )
{
    reed_state = reed_get_status( &reed );

    if ( ( reed_state == REED_MAGNETIC_FIELD_DETECTED ) && ( reed_state_old == REED_NO_MAGNETIC_FIELD ) )
    {
        reed_state_old = REED_MAGNETIC_FIELD_DETECTED;
        log_printf(&logger, "     ~ LOCKED ~\r\n");
        log_printf(&logger, "--------------------\r\n");
    }

    if ( ( reed_state == REED_NO_MAGNETIC_FIELD ) && ( reed_state_old == REED_MAGNETIC_FIELD_DETECTED ) )
    {
        log_printf(&logger, "    ~ UNLOCKED ~\r\n");
        log_printf(&logger, "--------------------\r\n");
        reed_state_old = REED_NO_MAGNETIC_FIELD;
    }
}
```

### Note 

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

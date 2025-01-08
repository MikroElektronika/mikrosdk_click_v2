
---
# BI HALL Click

> [BI HALL Click](https://www.mikroe.com/?pid_product=MIKROE-1646) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1646&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> Detect the south & north pole magnetic fields.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BiHall

### Example Key Functions

- `bihall_cfg_setup` Config Object Initialization function. 
```c
void bihall_cfg_setup ( bihall_cfg_t *cfg );
``` 
 
- `bihall_init` Initialization function. 
```c
err_t bihall_init ( bihall_t *ctx, bihall_cfg_t *cfg );
```

- `bihall_default_cfg` Click Default Configuration function. 
```c
void bihall_default_cfg ( bihall_t *ctx );
```

- `bihall_det_mag_field` Detecting south & north pole magnetic fields status function. 
```c
uint8_t bihall_det_mag_field ( bihall_t *ctx );
```

### Application Init

>
> Configuring Clicks and log objects.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    bihall_cfg_t cfg;

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
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    bihall_cfg_setup( &cfg );
    BIHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bihall_init( &bihall, &cfg );
    
    log_printf(&logger, " Detecting magnetic fields\r\n");
    log_printf(&logger, "--------------------------\r\n");
    
    bihall_state = BIHALL_MAG_POLE_NORTH;
    bihall_state_old = BIHALL_MAG_POLE_NORTH;
}
```

### Application Task

>
> This is a example which demonstrates the use of BI HALL Click board.
> Detect the south & north pole magnetic fields near the BI HALL Click.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.
> 

```c
void application_task ( void )
{
    bihall_state = bihall_det_mag_field( &bihall );

    if ( ( bihall_state == BIHALL_MAG_POLE_SOUTH ) && ( bihall_state_old == BIHALL_MAG_POLE_NORTH ) )
    {
        bihall_state_old = BIHALL_MAG_POLE_SOUTH;
        log_printf(&logger, "         ~ SOUTH ~\r\n");
        log_printf(&logger, "--------------------------\r\n");
    }

    if ( ( bihall_state == BIHALL_MAG_POLE_NORTH ) && ( bihall_state_old == BIHALL_MAG_POLE_SOUTH ) )
    {
        log_printf(&logger, "         ~ NORTH ~\r\n");
        log_printf(&logger, "--------------------------\r\n");
        bihall_state_old = BIHALL_MAG_POLE_NORTH;
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

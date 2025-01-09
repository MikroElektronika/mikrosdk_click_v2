
---
# CAN FD 5 Click

> [CAN FD 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4286) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4286&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This is an example that demonstrates the use of the CAN FD 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd5

### Example Key Functions

- `canfd5_cfg_setup` Config Object Initialization function. 
```c
void canfd5_cfg_setup ( canfd5_cfg_t *cfg );
``` 
 
- `canfd5_init` Initialization function. 
```c
err_t canfd5_init ( canfd5_t *ctx, canfd5_cfg_t *cfg );
```

- `canfd5_generic_write` Generic write function. 
```c
void canfd5_generic_write ( canfd5_t *ctx, char *data_buf, uint16_t len );
```
 
- `canfd5_generic_read` Generic read function. 
```c
int32_t canfd5_generic_read ( canfd5_t *ctx, char *data_buf, uint16_t max_len );
```

- `canfd5_set_normal_operating_mode` Set normal operating mode function. 
```c
void canfd5_set_normal_operating_mode ( canfd5_t *ctx );
```

### Application Init

> Initializes the driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd5_cfg_t cfg;

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

    canfd5_cfg_setup( &cfg );
    CANFD5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd5_init( &canfd5, &cfg );

    canfd5_set_normal_operating_mode( &canfd5 );
    Delay_ms ( 100 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    canfd5_process( );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd5_generic_write( &canfd5, TEXT_TO_SEND, 8 );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif 
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

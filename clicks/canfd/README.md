
---
# CAN FD Click

> [CAN FD Click](https://www.mikroe.com/?pid_product=MIKROE-3933) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3933&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from CAN FD Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd

### Example Key Functions

- `canfd_cfg_setup` Config Object Initialization function. 
```c
void canfd_cfg_setup ( canfd_cfg_t *cfg );
``` 
 
- `canfd_init` Initialization function. 
```c
err_t canfd_init ( canfd_t *ctx, canfd_cfg_t *cfg );
```

- `canfd_generic_write` Generic write function. 
```c
void canfd_generic_write ( canfd_t *ctx, char *data_buf, uint16_t len );
```
 
- `canfd_generic_read` Generic read function. 
```c
int32_t canfd_generic_read ( canfd_t *ctx, char *data_buf, uint16_t max_len );
```

- `canfd_set_operating_mode` Operation mode. 
```c
void canfd_set_operating_mode ( canfd_t *ctx, uint8_t op_mode );
```

### Application Init

> Initializes the driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd_cfg_t cfg;

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

    canfd_cfg_setup( &cfg );
    CANFD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd_init( &canfd, &cfg );

    Delay_ms ( 500 );

#ifdef DEMO_APP_RECEIVER
    canfd_set_operating_mode( &canfd, CANFD_OPERATING_MODE_RECEIVE );
    log_info( &logger, "--- RECEIVER MODE ---" );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd_set_operating_mode( &canfd, CANFD_OPERATING_MODE_NORMAL );
    log_info( &logger, "--- TRANSMITTER MODE ---" );
#endif 
    Delay_ms ( 100 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    canfd_process( );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd_generic_write( &canfd, TEXT_TO_SEND, 8 );
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


---
# UART Mux Click

> [UART Mux Click](https://www.mikroe.com/?pid_product=MIKROE-3878) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3878&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from UART Mux Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UartMux

### Example Key Functions

- `uartmux_cfg_setup` Config Object Initialization function. 
```c
void uartmux_cfg_setup ( uartmux_cfg_t *cfg );
``` 
 
- `uartmux_init` Initialization function. 
```c
err_t uartmux_init ( uartmux_t *ctx, uartmux_cfg_t *cfg );
```

- `uartmux_send_command` Send command. 
```c
void uartmux_send_command ( uartmux_t *ctx, char *command, uartmux_channel_t *channel );
```
 
- `uartmux_set_inhibit_communication` Set INT pin. 
```c
void uartmux_set_inhibit_communication ( uartmux_t *ctx, uint8_t state );
```

- `uartmux_choose_channel` Choose channel. 
```c
void uartmux_choose_channel ( uartmux_t *ctx, uartmux_channel_t *channel );
```

### Application Init

> Initializes driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uartmux_cfg_t cfg;

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

    uartmux_cfg_setup( &cfg );
    UARTMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uartmux_init( &uartmux, &cfg );

    uartmux_set_inhibit_communication( &uartmux, UARTMUX_PIN_STATE_LOW );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    uartmux_process( );
#endif

#ifdef DEMO_APP_TRANSMITER
    uartmux_process( );

    channel.state_a = UARTMUX_STATE_A_CHANNEL_1;
    channel.state_b = UARTMUX_STATE_B_CHANNEL_1;

    if ( send_data_cnt == 2 )
    {
        uartmux_send_command( &uartmux, TEXT_TO_SEND, &channel );
        uartmux_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
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

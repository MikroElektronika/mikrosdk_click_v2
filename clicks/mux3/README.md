
---
# MUX 3 Click

> [MUX 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3916) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3916&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application sets multiplexing one input channel to eight single-ended output channels. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mux3

### Example Key Functions

- `mux3_cfg_setup` Config Object Initialization function. 
```c
void mux3_cfg_setup ( mux3_cfg_t *cfg );
``` 
 
- `mux3_init` Initialization function. 
```c
err_t mux3_init ( mux3_t *ctx, mux3_cfg_t *cfg );
```

- `mux3_set_channel` Set active MUX channel function. 
```c
void mux3_set_channel ( mux3_t *ctx, uint8_t select_channel );
```

### Application Init

> Initialization driver enable's - GPIO, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mux3_cfg_t cfg;

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

    //  Click initialization.

    mux3_cfg_setup( &cfg );
    MUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux3_init( &mux3, &cfg );
}
```

### Application Task

> This is an example which demonstrates the use of MUX 3 Click board.
> Sets the current active and changes the channel every 1 sec.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on Usart Terminal changes for every 1 sec.

```c
void application_task ( void )
{
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S1 );
    log_printf( &logger, "Active channel: S1\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S2 );
    log_printf( &logger, "Active channel: S2\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S3 );
    log_printf( &logger, "Active channel: S3\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S4 );
    log_printf( &logger, "Active channel: S4\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S5 );
    log_printf( &logger, "Active channel: S5\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S6 );
    log_printf( &logger, "Active channel: S6\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S7 );
    log_printf( &logger, "Active channel: S7\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S8 );
    log_printf( &logger, "Active channel: S8\r\n" );
    Delay_1sec( );
    
    mux3_set_channel( &mux3, MUX3_DISABLE_ALL_CHANNELS );
    log_printf( &logger, "Active channel: none\r\n" );
    log_printf( &logger, "-------------------\r\n" );
    Delay_1sec( );
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

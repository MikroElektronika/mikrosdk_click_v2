
---
# CAN FD 2 Click

> [CAN FD 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4062) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4062&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from CAN FD 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd2

### Example Key Functions

- `canfd2_cfg_setup` Config Object Initialization function.
```c
void canfd2_cfg_setup ( canfd2_cfg_t *cfg );
```
 
- `canfd2_init` Initialization function.
```c
err_t canfd2_init ( canfd2_t *ctx, canfd2_cfg_t *cfg );
```

- `canfd2_generic_read` Generic read function.
```c
int32_t canfd2_generic_read ( canfd2_t *ctx, uint8_t *data_buf, uint16_t max_len );
```
 
- `canfd2_write_data` Generic write the byte of data function
```c
void canfd2_write_data ( canfd2_t *ctx, uint8_t reg_addr, uint8_t write_data );
```

- `canfd2_get_mode` Get operating mode function
```c
uint8_t canfd2_get_mode ( canfd2_t *ctx );
```

### Application Init

> Initializes the driver and configures the Click board for the selected mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd2_cfg_t cfg;

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

    canfd2_cfg_setup( &cfg );
    CANFD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd2_init( &canfd2, &cfg );
    
    CANFD2_SET_DATA_SAMPLE_EDGE;
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    canfd2_set_mode( &canfd2, CANFD2_OP_MODE_NORMAL );
    if ( CANFD2_OP_MODE_NORMAL == canfd2_get_mode ( &canfd2 ) )
    {
        log_info( &logger, "--- TRANSMITTER MODE ---" );
    }
    else
    {
        log_info( &logger, "--- ERROR ---" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
#else
    canfd2_set_mode( &canfd2, CANFD2_OP_MODE_RECEIVE_ONLY );
    if ( CANFD2_OP_MODE_RECEIVE_ONLY == canfd2_get_mode ( &canfd2 ) )
    {
        log_info( &logger, "--- RECEIVER MODE ---" );
    }
    else
    {
        log_info( &logger, "--- ERROR ---" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
#endif
    Delay_ms ( 100 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    canfd2_generic_write( &canfd2, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    canfd2_process( &canfd2 );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        canfd2_process ( &canfd2 );
        log_printf( &logger, "Received data: %s", app_buf );
        canfd2_clear_app_buf( );
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


---
# RF Switch Click

> [RF Switch Click](https://www.mikroe.com/?pid_product=MIKROE-4168) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4168&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This is an example that demonstrates the use of the RF Switch Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RFSwitch

### Example Key Functions

- `rfswitch_cfg_setup` Config Object Initialization function.
```c
void rfswitch_cfg_setup ( rfswitch_cfg_t *cfg );
```

- `rfswitch_init` Initialization function.
```c
err_t rfswitch_init ( rfswitch_t *ctx, rfswitch_cfg_t *cfg );
```

- `rfswitch_power_on` RF Switch power on function.
```c
void rfswitch_power_on ( rfswitch_t *ctx );
```

- `rfswitch_switch_channel` RF Switch switch channel function.
```c
void rfswitch_switch_channel ( rfswitch_t *ctx );
```

- `rfswitch_select_channel` RF Switch select channel function.
```c
void rfswitch_select_channel ( rfswitch_t *ctx, uint8_t select_channel );
```

### Application Init

> Initialization driver enable's - GPIO, also write log and powers on device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfswitch_cfg_t rfswitch_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    rfswitch_cfg_setup( &rfswitch_cfg );
    RFSWITCH_MAP_MIKROBUS( rfswitch_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == rfswitch_init( &rfswitch, &rfswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "   Powering device on   \r\n" );
    rfswitch_power_on( &rfswitch );
    Delay_ms ( 100 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "   Select option to     \r\n" );
    log_printf( &logger, "    select channel      \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, " 1. Channel 1 selected  \r\n" );
    log_printf( &logger, " 2. Channel 2 selected  \r\n" );
    log_printf( &logger, " 3. Switching channel   \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
```

### Application Task

> Waiting for valid user input and executes functions based on set of valid commands.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    uint8_t tx_buf;
    if ( log_read( &logger, &tx_buf, 1 ) ) {
        switch ( tx_buf ) {
            case '1' : {
                rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_1 );
                log_printf( &logger, " Switching to RF port 1 \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            case '2' : {
                rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_2 );
                log_printf( &logger, " Switching to RF port 2 \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            case '3' : {
                rfswitch_switch_channel( &rfswitch );
                log_printf( &logger, "   Switching RF port    \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            default : {
                log_printf( &logger, "   Select option to     \r\n" );
                log_printf( &logger, "    select channel      \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                log_printf( &logger, " 1. Channel 1 selected  \r\n" );
                log_printf( &logger, " 2. Channel 2 selected  \r\n" );
                log_printf( &logger, " 3. Switching channel   \r\n" );
                log_printf( &logger, "------------------------\r\n" );
            }
        }
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

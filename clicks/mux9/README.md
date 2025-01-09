
---
# MUX 9 Click

> [MUX 9 Click](https://www.mikroe.com/?pid_product=MIKROE-5500) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5500&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of MUX 9 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MUX9

### Example Key Functions

- `mux9_cfg_setup` Config Object Initialization function.
```c
void mux9_cfg_setup ( mux9_cfg_t *cfg );
```

- `mux9_init` Initialization function.
```c
err_t mux9_init ( mux9_t *ctx, mux9_cfg_t *cfg );
```

- `mux9_active_channel` MUX 9 active channel function.
```c
err_t mux9_active_channel ( mux9_t *ctx, uint8_t sel_ch );
```

- `mux9_reset` MUX 9 reset function.
```c
void mux9_reset ( mux9_t *ctx );
```

- `mux9_disable` MUX 9 disable function.
```c
void mux9_disable ( mux9_t *ctx );
```

### Application Init

> Initializes the driver and performs the reset.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    mux9_cfg_t mux9_cfg;  /**< Click config object. */

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
    mux9_cfg_setup( &mux9_cfg );
    MUX9_MAP_MIKROBUS( mux9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mux9_init( &mux9, &mux9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    mux9_reset( &mux9 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------\r\n" );
}
```

### Application Task

> This is an example that shows the use of a MUX 9 Click board&trade;.
> This example shows switching channels (from CH 1 to CH 8) on and off.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    for ( uint8_t ch_pos = MUX9_SELECT_CH_1; ch_pos <= MUX9_SELECT_CH_8; ch_pos++ )
    {
        if ( MUX9_OK == mux9_active_channel( &mux9, ch_pos ) )
        {
            log_printf( &logger, " The Channel %d is activated. \r\n", ( uint16_t ) ch_pos );
            Delay_ms ( 1000 );
        }
    }
    log_printf( &logger, " -----------\r\n" );
    Delay_ms ( 1000 );
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

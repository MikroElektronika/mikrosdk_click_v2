
---
# MUX 10 Click

> [MUX 10 Click](https://www.mikroe.com/?pid_product=MIKROE-7066) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7066&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the MUX 10 Click board by selecting
analog channels one by one within the active bank(S1-S4, S5-28), routing each selected
channel ( Sx ) to the common drain ( D ) pin of the MUX808-Q1 multiplexer.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MUX10

### Example Key Functions

- `mux10_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void mux10_cfg_setup ( mux10_cfg_t *cfg );
```

- `mux10_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t mux10_init ( mux10_t *ctx, mux10_cfg_t *cfg );
```

- `mux10_set_a0` This function sets the A0 pin to desired logic state.
```c
void mux10_set_a0 ( mux10_t *ctx, uint8_t state );
```

- `mux10_set_a1` This function sets the A1 pin to desired logic state.
```c
void mux10_set_a1 ( mux10_t *ctx, uint8_t state );
```

- `mux10_active_channel_sel` This function selects the active channel of the device by driving the A0 and A1 address lines.
```c
err_t mux10_active_channel_sel ( mux10_t *ctx, uint8_t sel_ch );
```

### Application Init

> Initializes the driver and selects the first channel of the active bank.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mux10_cfg_t mux10_cfg;  /**< Click config object. */

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
    mux10_cfg_setup( &mux10_cfg );
    MUX10_MAP_MIKROBUS( mux10_cfg, MIKROBUS_POSITION_MUX10 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == mux10_init( &mux10, &mux10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    mux10_active_channel_sel( &mux10, MUX10_SELECT_CH_1 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Selects channels 1 to 4 within the active bank(S1-S4, S5-28) in a loop, routing each
selected channel to the common D pin, and logs the selected channel via USB UART.

```c
void application_task ( void ) 
{
    for ( uint8_t cnt = MUX10_SELECT_CH_1; cnt <= MUX10_SELECT_CH_4; cnt++ ) 
    {
        if ( MUX10_OK == mux10_active_channel_sel( &mux10, cnt ) ) 
        {
            log_printf( &logger, " Channel %u selected\r\n", ( uint16_t ) cnt );
            Delay_ms ( 1000 );
        }
    }
    log_printf( &logger, " -----------\r\n" );
}
```

### Note

> The A2 address line is not set by the driver but by the SW1 onboard
switch and selects the channel bank ( A2 low: S1-S4, A2 high: S5-S8 ).

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


---
# RF Switch 2 Click

> [RF Switch 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6914) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6914&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the RF Switch 2 Click board to control
RF signal routing by switching between available RF paths. The application
cycles through all available switching modes, enabling each RF channel one
at a time and also demonstrating the all-off state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RFSwitch2

### Example Key Functions

- `rfswitch2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rfswitch2_cfg_setup ( rfswitch2_cfg_t *cfg );
```

- `rfswitch2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rfswitch2_init ( rfswitch2_t *ctx, rfswitch2_cfg_t *cfg );
```

- `rfswitch2_set_mode` This function sets the RF switch mode by setting V1, V2, and V3 pins logic state.
```c
void rfswitch2_set_mode ( rfswitch2_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the logger and RF Switch 2 Click driver, sets up mikroBUS mapping, and prepares digital output pins for controlling the RF switch.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfswitch2_cfg_t rfswitch2_cfg;  /**< Click config object. */

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
    rfswitch2_cfg_setup( &rfswitch2_cfg );
    RFSWITCH2_MAP_MIKROBUS( rfswitch2_cfg, MIKROBUS_POSITION_RFSWITCH2 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == rfswitch2_init( &rfswitch2, &rfswitch2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles through all switch modes, selecting each RF output sequentially (RF1–RF4) followed by the ALL OFF mode, with delay between changes.

```c
void application_task ( void )
{
    static uint8_t mode = RFSWITCH2_MODE_ALL_OFF;

    rfswitch2_set_mode( &rfswitch2, mode );
    if ( RFSWITCH2_MODE_ALL_OFF == mode )
    {
        log_printf( &logger, " Mode: ALL OFF\r\n\n" );
    }
    else
    {
        log_printf( &logger, " Mode: RF%u ON\r\n\n", ( uint16_t ) mode );
    }

    if ( ++mode > RFSWITCH2_MODE_RF4_ON )
    {
        mode = RFSWITCH2_MODE_ALL_OFF;
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

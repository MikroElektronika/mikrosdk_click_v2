
---
# Expand 3 Click

> [Expand 3 Click](https://www.mikroe.com/?pid_product=MIKROE-1874) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1874&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example demonstrates the use of Expand 3 Click board by setting and reading the port state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand3

### Example Key Functions

- `expand3_cfg_setup` Config Object Initialization function.
```c
void expand3_cfg_setup ( expand3_cfg_t *cfg );
```

- `expand3_init` Initialization function.
```c
err_t expand3_init ( expand3_t *ctx, expand3_cfg_t *cfg );
```

- `expand3_default_cfg` Click Default Configuration function.
```c
err_t expand3_default_cfg ( expand3_t *ctx );
```

- `expand3_write_state` This function writes data to the PIO output-latch state register which controls the open-drain output transistors of the PIO channels.
```c
err_t expand3_write_state ( expand3_t *ctx, uint8_t state );
```

- `expand3_read_last_state` This function reads the latest data written to the PIO using
```c
err_t expand3_read_last_state ( expand3_t *ctx, uint8_t *last_state );
```

- `expand3_read_current_state` This function reads the current logic state of the PIO pins.
```c
err_t expand3_read_current_state ( expand3_t *ctx, uint8_t *curr_state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand3_cfg_t expand3_cfg;  /**< Click config object. */

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
    expand3_cfg_setup( &expand3_cfg );
    EXPAND3_MAP_MIKROBUS( expand3_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == expand3_init( &expand3, &expand3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND3_ERROR == expand3_default_cfg ( &expand3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a counter data to the port output pins and reads the status of the same port input pins approximately every 500ms. All data are displayed on the USB UART.

```c
void application_task ( void )
{
    static uint8_t out_state = 0;
    static uint8_t in_state = 0;
    if ( ( EXPAND3_OK == expand3_write_state ( &expand3, out_state ) ) && 
         ( EXPAND3_OK == expand3_read_last_state ( &expand3, &out_state ) ) )
    {
        log_printf( &logger, " Output state: 0x%.2X\r\n\n", out_state++ );
    }
    if ( EXPAND3_OK == expand3_read_current_state ( &expand3, &in_state ) )
    {
        log_printf( &logger, " Input state: 0x%.2X\r\n\n", in_state );
    }
    Delay_ms ( 500 );
}
```

### Note

> The PIO pins are in the open-drain mode, therefore a pull-up resistor must be added to each pin.
This Click board can be used in a combination with an EasyLED [MIKROE-571] and EasyPULL [MIKROE-575] boards.

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

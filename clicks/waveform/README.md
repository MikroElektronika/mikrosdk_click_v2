
---
# Waveform  Click

> [Waveform Click](https://www.mikroe.com/?pid_product=MIKROE-3309) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3309&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Waveform Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Waveform

### Example Key Functions

- `waveform_cfg_setup` Config Object Initialization function.
```c
void waveform_cfg_setup ( waveform_cfg_t *cfg ); 
```

- `waveform_init` Initialization function.
```c
err_t waveform_init ( waveform_t *ctx, waveform_cfg_t *cfg );
```

- `waveform_sine_output` Sinusoide output function
```c
void waveform_sine_output ( waveform_t *ctx, uint32_t freq );
```

- `waveform_triangle_output` Triangle output function
```c
void waveform_triangle_output ( waveform_t *ctx, uint32_t freq );
```

- `waveform_square_output` Square output function
```c
void waveform_square_output ( waveform_t *ctx, uint32_t freq );
```

### Application Init

> Initializes the communication interface and configures the Click board.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    waveform_cfg_t waveform_cfg;

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
    waveform_cfg_setup( &waveform_cfg );
    WAVEFORM_MAP_MIKROBUS( waveform_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == waveform_init( &waveform, &waveform_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    waveform_sine_output( &waveform, frequency );
    log_printf( &logger, "Sine wave output set with approx. frequency: %lu Hz\r\n", frequency );
    waveform_display_commands ( );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Predefined commands are inputed from the serial port.
> Changes the signal frequency, waveform or amplitude depending on the receiver command.

```c
void application_task ( )
{
    uint8_t command = 0;
    if ( 1 == log_read ( &logger, &command, 1 ) ) 
    {
        waveform_parse_command ( command );
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

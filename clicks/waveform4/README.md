
---
# Waveform 4 Click

> [Waveform 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4908) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4908&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Waveform 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Waveform4

### Example Key Functions

- `waveform4_cfg_setup` Config Object Initialization function.
```c
void waveform4_cfg_setup ( waveform4_cfg_t *cfg );
```

- `waveform4_init` Initialization function.
```c
err_t waveform4_init ( waveform4_t *ctx, waveform4_cfg_t *cfg );
```

- `waveform4_default_cfg` Click Default Configuration function.
```c
err_t waveform4_default_cfg ( waveform4_t *ctx );
```

- `waveform4_set_frequency` This function sets the sine and cosine (DDS) waves output frequency.
```c
err_t waveform4_set_frequency ( waveform4_t *ctx, uint32_t freq );
```

- `waveform4_set_gain` This function sets the gain level of a desired channel.
```c
err_t waveform4_set_gain ( waveform4_t *ctx, uint8_t channel, float gain );
```

- `waveform4_set_wave_output` This function sets a desired output signal wave to the selected channel.
```c
err_t waveform4_set_wave_output ( waveform4_t *ctx, uint8_t channel, uint8_t wave );
```

### Application Init

> Initializes the driver and performs the Click default configuration which resets the registers and sets the sine wave output with default gain and 
> default frequency for all channels. After that it displays the list of supported commands on the USB UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waveform4_cfg_t waveform4_cfg;  /**< Click config object. */

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
    waveform4_cfg_setup( &waveform4_cfg );
    WAVEFORM4_MAP_MIKROBUS( waveform4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == waveform4_init( &waveform4, &waveform4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( WAVEFORM4_ERROR == waveform4_default_cfg ( &waveform4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    waveform4_display_commands ( );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the command character received from USB UART it changes the signal frequency, gain or wave of the selected channel.

```c
void application_task ( void )
{
    uint8_t command = 0;
    if ( log_read ( &logger, &command, 1 ) > 0 ) 
    {
        waveform4_parse_command ( command );
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

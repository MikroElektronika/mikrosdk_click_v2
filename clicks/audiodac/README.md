
---
# Audio DAC Click

> [Audio DAC Click](https://www.mikroe.com/?pid_product=MIKROE-5587) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5587&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Audio DAC Click board by controling the volume level of both output channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioDAC

### Example Key Functions

- `audiodac_cfg_setup` Config Object Initialization function.
```c
void audiodac_cfg_setup ( audiodac_cfg_t *cfg );
```

- `audiodac_init` Initialization function.
```c
err_t audiodac_init ( audiodac_t *ctx, audiodac_cfg_t *cfg );
```

- `audiodac_default_cfg` Click Default Configuration function.
```c
err_t audiodac_default_cfg ( audiodac_t *ctx );
```

- `audiodac_get_gpio4_pin` This function returns the GPIO4 pin logic state. The GPIO4 pin is mapped to auto mute flag output for both L and R channels by default.
```c
uint8_t audiodac_get_gpio4_pin ( audiodac_t *ctx );
```

- `audiodac_volume_control` This function sets the volume level for the selected output channel.
```c
err_t audiodac_volume_control ( audiodac_t *ctx, uint8_t channel, uint8_t volume );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audiodac_cfg_t audiodac_cfg;  /**< Click config object. */

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
    audiodac_cfg_setup( &audiodac_cfg );
    AUDIODAC_MAP_MIKROBUS( audiodac_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == audiodac_init( &audiodac, &audiodac_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AUDIODAC_ERROR == audiodac_default_cfg ( &audiodac ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if the auto mute flag is set and then changes the volume level of both output channels
every 100ms. All data is being displayed on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static uint8_t volume = AUDIODAC_VOLUME_MUTE;
    if ( audiodac_get_gpio4_pin ( &audiodac ) )
    {
        log_printf ( &logger, " Auto mute flag (both L and R channels are auto muted)\r\n" );
        // Wait until the channels are auto unmuted, i.e. until a valid digital signal is received
        while ( audiodac_get_gpio4_pin ( &audiodac ) );
    }
    if ( AUDIODAC_OK == audiodac_volume_control ( &audiodac, AUDIODAC_CHANNEL_BOTH, volume ) )
    {
        log_printf ( &logger, "\r\n Volume: " );
        if ( AUDIODAC_VOLUME_MUTE == volume )
        {
            log_printf ( &logger, "MUTE\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
        else if ( AUDIODAC_VOLUME_MAX == volume )
        {
            log_printf ( &logger, "MAX\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
        else
        {
            log_printf ( &logger, "%u\r\n", ( uint16_t ) volume );
            Delay_ms ( 100 );
        }
        volume++; 
        if ( volume > AUDIODAC_VOLUME_MAX )
        {
            volume = AUDIODAC_VOLUME_MUTE;
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

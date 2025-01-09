
---
# SolidSwitch 3 Click

> [SolidSwitch 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5079) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5079&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of SolidSwitch 3 Click board by controlling the output state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch3

### Example Key Functions

- `solidswitch3_cfg_setup` Config Object Initialization function.
```c
void solidswitch3_cfg_setup ( solidswitch3_cfg_t *cfg );
```

- `solidswitch3_init` Initialization function.
```c
err_t solidswitch3_init ( solidswitch3_t *ctx, solidswitch3_cfg_t *cfg );
```

- `solidswitch3_default_cfg` Click Default Configuration function.
```c
err_t solidswitch3_default_cfg ( solidswitch3_t *ctx );
```

- `solidswitch3_enable_output` This function enables the specified output channel.
```c
err_t solidswitch3_enable_output ( solidswitch3_t *ctx, uint8_t channel );
```

- `solidswitch3_disable_output` This function disables the specified output channel.
```c
err_t solidswitch3_disable_output ( solidswitch3_t *ctx, uint8_t channel );
```

- `solidswitch3_reset` This function resets the device by toggling the reset pin.
```c
void solidswitch3_reset ( solidswitch3_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch3_cfg_t solidswitch3_cfg;  /**< Click config object. */

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
    solidswitch3_cfg_setup( &solidswitch3_cfg );
    SOLIDSWITCH3_MAP_MIKROBUS( solidswitch3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch3_init( &solidswitch3, &solidswitch3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    SET_SPI_DATA_SAMPLE_EDGE;
    
    if ( SOLIDSWITCH3_ERROR == solidswitch3_default_cfg ( &solidswitch3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Enables all outputs one by one in the span of 8 seconds, and after that disables
all outputs for 3 seconds. Accordingly, the outputs status will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t cnt = SOLIDSWITCH3_CH_OUT1; cnt <= SOLIDSWITCH3_CH_OUT8; cnt <<= 1 )
    {
        if ( SOLIDSWITCH3_OK == solidswitch3_enable_output ( &solidswitch3, cnt ) )
        {
            solidswitch3_display_enabled_channels( &solidswitch3 );
            Delay_ms ( 1000 );
        }
    }
    
    if ( SOLIDSWITCH3_OK == solidswitch3_disable_output ( &solidswitch3, SOLIDSWITCH3_ALL_CHANNELS ) )
    {
        solidswitch3_display_enabled_channels( &solidswitch3 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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

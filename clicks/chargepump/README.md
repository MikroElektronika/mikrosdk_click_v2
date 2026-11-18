
---
# Charge Pump Click

> [Charge Pump Click](https://www.mikroe.com/?pid_product=MIKROE-7093) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7093&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Aug 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Charge Pump Click board by cycling the
LT7826 switched capacitor converter between switching and standby mode,
while monitoring the fault indication pin.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ChargePump

### Example Key Functions

- `chargepump_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void chargepump_cfg_setup ( chargepump_cfg_t *cfg );
```

- `chargepump_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t chargepump_init ( chargepump_t *ctx, chargepump_cfg_t *cfg );
```

- `chargepump_enable_device` This function wakes the device from shutdown mode.
```c
void chargepump_enable_device ( chargepump_t *ctx );
```

- `chargepump_disable_device` This function puts the device into shutdown mode.
```c
void chargepump_disable_device ( chargepump_t *ctx );
```

- `chargepump_enable_switching` This function enables switching capacitors.
```c
void chargepump_enable_switching ( chargepump_t *ctx );
```

- `chargepump_disable_switching` This function disables switching capacitors.
```c
void chargepump_disable_switching ( chargepump_t *ctx );
```

### Application Init

> Initializes the driver and enables the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    chargepump_cfg_t chargepump_cfg;  /**< Click config object. */

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
    chargepump_cfg_setup( &chargepump_cfg );
    CHARGEPUMP_MAP_MIKROBUS( chargepump_cfg, MIKROBUS_POSITION_CHARGEPUMP );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == chargepump_init( &chargepump, &chargepump_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    chargepump_enable_device( &chargepump );
    Delay_10ms( );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Enables switching and waits for the fault pin to be released, keeps the converter
running for 5 seconds, then returns it to standby mode for one second. The
state of the converter is displayed on the USB UART.

```c
void application_task ( void ) 
{
    /* Enable switching capacitors and wait for the output to become ready. */
    chargepump_enable_switching( &chargepump );
    if ( CHARGEPUMP_OK == chargepump_wait_output_ready( &chargepump ) )
    {
        log_printf( &logger, " Switching - output ready\r\n" );
    }
    else
    {
        log_printf( &logger, " Switching - output not ready\r\n" );
    }
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );

    /* Enter standby mode */
    chargepump_disable_switching( &chargepump );
    log_printf( &logger, " Standby\r\n\n" );
    Delay_ms( 1000 );
}
```

### Note

> The load current must stay below 30mA while the device is in the pre-balance phase,
otherwise the device never enters full-power switching.

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

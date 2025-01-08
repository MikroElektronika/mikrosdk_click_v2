
---
# Clock Gen 6 Click

> [Clock Gen 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4973) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4973&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Clock Gen 6 Click board which acts as an astable oscillator.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen6

### Example Key Functions

- `clockgen6_cfg_setup` Config Object Initialization function.
```c
void clockgen6_cfg_setup ( clockgen6_cfg_t *cfg );
```

- `clockgen6_init` Initialization function.
```c
err_t clockgen6_init ( clockgen6_t *ctx, clockgen6_cfg_t *cfg );
```

- `clockgen6_default_cfg` This function executes a default configuration of Clock Gen 6 Click board.
```c
err_t clockgen6_default_cfg ( clockgen6_t *ctx );
```

- `clockgen6_set_digipot` This function sets the digital potentiometer position by using SPI serial interface.
```c
err_t clockgen6_set_digipot ( clockgen6_t *ctx, uint8_t position );
```

- `clockgen6_enable_output` This function enables the output by setting the EN pin to high logic state.
```c
void clockgen6_enable_output ( clockgen6_t *ctx );
```

- `clockgen6_disable_output` This function disables the output by setting the EN pin to low logic state.
```c
void clockgen6_disable_output ( clockgen6_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the digital potentiometer to max position and enables the clock output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen6_cfg_t clockgen6_cfg;  /**< Click config object. */

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
    clockgen6_cfg_setup( &clockgen6_cfg );
    CLOCKGEN6_MAP_MIKROBUS( clockgen6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == clockgen6_init( &clockgen6, &clockgen6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLOCKGEN6_ERROR == clockgen6_default_cfg ( &clockgen6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the clock output frequency by changing the digital potentiometer position every second. The potentiometer position value will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( int16_t pos = CLOCKGEN6_DIGIPOT_POSITION_MAX; pos >= CLOCKGEN6_DIGIPOT_POSITION_MIN; )
    {
        if ( CLOCKGEN6_OK == clockgen6_set_digipot ( &clockgen6, pos ) )
        {
            log_printf( &logger, " DIGIPOT position: %u\r\n", pos );
            Delay_ms ( 1000 );
            pos -= 5;
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

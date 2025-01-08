
---
# SolidSwitch 8 Click

> [SolidSwitch 8 Click](https://www.mikroe.com/?pid_product=MIKROE-6064) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6064&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of SolidSwitch 8 Click board by switching state of the switch.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch8

### Example Key Functions

- `solidswitch8_cfg_setup` Config Object Initialization function.
```c
void solidswitch8_cfg_setup ( solidswitch8_cfg_t *cfg );
```

- `solidswitch8_init` Initialization function.
```c
err_t solidswitch8_init ( solidswitch8_t *ctx, solidswitch8_cfg_t *cfg );
```

- `solidswitch8_default_cfg` Click Default Configuration function.
```c
err_t solidswitch8_default_cfg ( solidswitch8_t *ctx );
```

- `solidswitch8_set_err_pin` This function sets the err pin state to the selected level of SolidSwitch 8 Click board.
```c
void solidswitch8_set_err_pin ( solidswitch8_t *ctx, uint8_t pin_state );
```

- `solidswitch8_set_in_pin` This function sets the in pin state to the selected level of SolidSwitch 8 Click board.
```c
void solidswitch8_set_in_pin ( solidswitch8_t *ctx, uint8_t pin_state );
```

- `solidswitch8_get_sts_pin` This function reads the state of the status pin of SolidSwitch 8 Click board.
```c
uint8_t solidswitch8_get_sts_pin ( solidswitch8_t *ctx );
```

### Application Init

> Initializes the driver, performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch8_cfg_t solidswitch8_cfg;  /**< Click config object. */

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
    solidswitch8_cfg_setup( &solidswitch8_cfg );
    SOLIDSWITCH8_MAP_MIKROBUS( solidswitch8_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == solidswitch8_init( &solidswitch8, &solidswitch8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    solidswitch8_default_cfg ( &solidswitch8 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Switching state of the output every 5 seconds, and monitoring the status of the device.

```c
void application_task ( void ) 
{
    if ( SOLIDSWITCH8_PIN_STATE_LOW == solidswitch8_get_sts_pin( &solidswitch8 ) )
    {
        solidswitch8_set_err_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_HIGH );
        log_error( &logger, " Detected over temperature condition." );
        for ( ; ; );
    }

    log_printf( &logger, " Switch state closed. \r\n" );
    solidswitch8_set_in_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Switch state open. \r\n" );
    solidswitch8_set_in_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_LOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

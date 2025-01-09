
---
# LED Driver 17 Click

> [LED Driver 17 Click](https://www.mikroe.com/?pid_product=MIKROE-5565) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5565&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of LED Driver 17 Click board by changing the LEDs dimming level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver17

### Example Key Functions

- `leddriver17_cfg_setup` Config Object Initialization function.
```c
void leddriver17_cfg_setup ( leddriver17_cfg_t *cfg );
```

- `leddriver17_init` Initialization function.
```c
err_t leddriver17_init ( leddriver17_t *ctx, leddriver17_cfg_t *cfg );
```

- `leddriver17_default_cfg` Click Default Configuration function.
```c
err_t leddriver17_default_cfg ( leddriver17_t *ctx );
```

- `leddriver17_get_fault_pin` This function returns the fault (FLT) pin logic state.
```c
uint8_t leddriver17_get_fault_pin ( leddriver17_t *ctx );
```

- `leddriver17_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t leddriver17_set_duty_cycle ( leddriver17_t *ctx, float duty_cycle );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver17_cfg_t leddriver17_cfg;  /**< Click config object. */

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
    leddriver17_cfg_setup( &leddriver17_cfg );
    LEDDRIVER17_MAP_MIKROBUS( leddriver17_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == leddriver17_init( &leddriver17, &leddriver17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER17_ERROR == leddriver17_default_cfg ( &leddriver17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the LEDs dimming level by setting the PWM duty cycle every 500ms. The duty cycle percentage will be displayed on the USB UART.
It also checks the fault indication pin and displays it accordingly.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    if ( !leddriver17_get_fault_pin ( &leddriver17 ) )
    {
        log_printf( &logger, " Fault detected!\r\n" );
    }
    leddriver17_set_duty_cycle ( &leddriver17, duty );
    log_printf( &logger, " Duty: %u%%\r\n\n", ( uint16_t ) ( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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

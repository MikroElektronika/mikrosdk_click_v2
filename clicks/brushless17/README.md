
---
# Brushless 17 Click

> [Brushless 17 Click](https://www.mikroe.com/?pid_product=MIKROE-5000) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5000&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 17 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless17

### Example Key Functions

- `brushless17_cfg_setup` Config Object Initialization function.
```c
void brushless17_cfg_setup ( brushless17_cfg_t *cfg );
```

- `brushless17_init` Initialization function.
```c
err_t brushless17_init ( brushless17_t *ctx, brushless17_cfg_t *cfg );
```

- `brushless17_default_cfg` Click Default Configuration function.
```c
err_t brushless17_default_cfg ( brushless17_t *ctx );
```

- `brushless17_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless17_set_duty_cycle ( brushless17_t *ctx, float duty_cycle );
```

- `brushless17_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless17_switch_direction ( brushless17_t *ctx );
```

- `brushless17_get_diagnostic_pin` This function returns the DIAG pin logic state.
```c
uint8_t brushless17_get_diagnostic_pin ( brushless17_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless17_cfg_t brushless17_cfg;  /**< Click config object. */

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
    brushless17_cfg_setup( &brushless17_cfg );
    BRUSHLESS17_MAP_MIKROBUS( brushless17_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless17_init( &brushless17, &brushless17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS17_ERROR == brushless17_default_cfg ( &brushless17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500ms.
The duty cycle ranges from 40% to 80%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 4;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless17_set_duty_cycle ( &brushless17, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    duty_cnt += duty_inc;
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 3 == duty_cnt ) 
    {
        duty_inc = 1;
        duty_cnt = 4;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless17_switch_direction ( &brushless17 );
    }
    
    if ( !brushless17_get_diagnostic_pin ( &brushless17 ) )
    {
        log_info ( &logger, " An overcurrent or overtemperature event has occured " );
    }

    Delay_ms ( 500 );
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

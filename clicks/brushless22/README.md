
---
# Brushless 22 Click

> [Brushless 22 Click](https://www.mikroe.com/?pid_product=MIKROE-4995) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4995&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 22 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless22

### Example Key Functions

- `brushless22_cfg_setup` Config Object Initialization function.
```c
void brushless22_cfg_setup ( brushless22_cfg_t *cfg );
```

- `brushless22_init` Initialization function.
```c
err_t brushless22_init ( brushless22_t *ctx, brushless22_cfg_t *cfg );
```

- `brushless22_default_cfg` Click Default Configuration function.
```c
err_t brushless22_default_cfg ( brushless22_t *ctx );
```

- `brushless22_set_slew_rate_resistance` This function sets the slew rate resistance by configuring the onboard digital potentiometer.
```c
err_t brushless22_set_slew_rate_resistance ( brushless22_t *ctx, uint16_t res_ohm );
```

- `brushless22_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless22_set_duty_cycle ( brushless22_t *ctx, float duty_cycle );
```

- `brushless22_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless22_switch_direction ( brushless22_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless22_cfg_t brushless22_cfg;  /**< Click config object. */

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
    brushless22_cfg_setup( &brushless22_cfg );
    BRUSHLESS22_MAP_MIKROBUS( brushless22_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless22_init( &brushless22, &brushless22_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS22_ERROR == brushless22_default_cfg ( &brushless22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500ms.
The duty cycle ranges from 0% to 100%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless22_set_duty_cycle ( &brushless22, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless22_switch_direction ( &brushless22 );
    }
    duty_cnt += duty_inc;

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

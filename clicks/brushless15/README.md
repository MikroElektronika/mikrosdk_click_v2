
---
# Brushless 15 Click

> [Brushless 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4885) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4885&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 15 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless15

### Example Key Functions

- `brushless15_cfg_setup` Config Object Initialization function.
```c
void brushless15_cfg_setup ( brushless15_cfg_t *cfg );
```

- `brushless15_init` Initialization function.
```c
err_t brushless15_init ( brushless15_t *ctx, brushless15_cfg_t *cfg );
```

- `brushless15_default_cfg` Click Default Configuration function.
```c
err_t brushless15_default_cfg ( brushless15_t *ctx );
```

- `brushless15_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless15_set_duty_cycle ( brushless15_t *ctx, float duty_cycle );
```

- `brushless15_enable_device` This function enables the device by setting the EN pin to low logic state.
```c
void brushless15_enable_device ( brushless15_t *ctx );
```

- `brushless15_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless15_switch_direction ( brushless15_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless15_cfg_t brushless15_cfg;  /**< Click config object. */

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
    brushless15_cfg_setup( &brushless15_cfg );
    BRUSHLESS15_MAP_MIKROBUS( brushless15_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless15_init( &brushless15, &brushless15_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS15_ERROR == brushless15_default_cfg ( &brushless15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle once per second.
> The duty cycle ranges from 20% to 80%. At the minimal speed, the motor switches direction.
> Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 2;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless15_set_duty_cycle ( &brushless15, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 1000 );
    duty_cnt += duty_inc;
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 1 == duty_cnt ) 
    {
        duty_inc = 1;
        duty_cnt = 2;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless15_switch_direction ( &brushless15 );
    }
}
```

### Note

> The maximal PWM Clock frequency for this Click board is 1 kHz. 
> So, depending on the selected setup the user will need to lower the MCU's main clock frequency 
> in the setup in order to get the PWM clock frequency down to 1 kHz.

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

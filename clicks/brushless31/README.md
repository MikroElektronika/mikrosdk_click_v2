
---
# Brushless 31 Click

> [Brushless 31 Click](https://www.mikroe.com/?pid_product=MIKROE-6348) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6348&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 31 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless31

### Example Key Functions

- `brushless31_cfg_setup` Config Object Initialization function.
```c
void brushless31_cfg_setup ( brushless31_cfg_t *cfg );
```

- `brushless31_init` Initialization function.
```c
err_t brushless31_init ( brushless31_t *ctx, brushless31_cfg_t *cfg );
```

- `brushless31_default_cfg` Click Default Configuration function.
```c
err_t brushless31_default_cfg ( brushless31_t *ctx );
```

- `brushless31_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless31_set_duty_cycle ( brushless31_t *ctx, float duty_cycle );
```

- `brushless31_pull_brake` This function pulls brake by setting the BRAKE pin to low logic state.
```c
void brushless31_pull_brake ( brushless31_t *ctx );
```

- `brushless31_switch_direction` This function switches the direction of motor rotation by toggling the DIR pin logic state.
```c
void brushless31_switch_direction ( brushless31_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless31_cfg_t brushless31_cfg;  /**< Click config object. */

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
    brushless31_cfg_setup( &brushless31_cfg );
    BRUSHLESS31_MAP_MIKROBUS( brushless31_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless31_init( &brushless31, &brushless31_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS31_ERROR == brushless31_default_cfg ( &brushless31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500 milliseconds.
The duty cycle ranges from 80% to 0%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 8;
    static int8_t duty_inc = -1;
    float duty = duty_cnt / 10.0;
    
    brushless31_set_duty_cycle ( &brushless31, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 8 ) 
    {        
        duty_cnt = 8;
        duty_inc = -1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless31_pull_brake ( &brushless31 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Switch direction\r\n" );
        brushless31_switch_direction ( &brushless31 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless31_release_brake ( &brushless31 );
        Delay_ms ( 1000 );
    }
    else if ( duty_cnt < 0 ) 
    {
        duty_cnt = 1;
        duty_inc = 1;
    }
}
```

### Note

> This Click board is designed for 5V systems but can also be controlled with 3V3 GPIO lines.
Ensure your MCU is 5V tolerant on mikroBUS GPIO lines before turning on the power supply.

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


---
# Brushless 33 Click

> [Brushless 33 Click](https://www.mikroe.com/?pid_product=MIKROE-6481) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6481&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the control of an A2212/13T 1000KV motor using
the Brushless 33 Click board. The example showcases basic motor operations, including
speed adjustments, direction switching, and fault handling. The motor speed is
controlled by varying the PWM duty cycle.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless33

### Example Key Functions

- `brushless33_cfg_setup` Config Object Initialization function.
```c
void brushless33_cfg_setup ( brushless33_cfg_t *cfg );
```

- `brushless33_init` Initialization function.
```c
err_t brushless33_init ( brushless33_t *ctx, brushless33_cfg_t *cfg );
```

- `brushless33_default_cfg` Click Default Configuration function.
```c
err_t brushless33_default_cfg ( brushless33_t *ctx );
```

- `brushless33_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless33_set_duty_cycle ( brushless33_t *ctx, float duty_cycle );
```

- `brushless33_switch_direction` This function switches the direction of motor rotation by toggling the DIR pin logic state.
```c
void brushless33_switch_direction ( brushless33_t *ctx );
```

- `brushless33_get_fault_pin` This function returns the fault indication pin logic state.
```c
uint8_t brushless33_get_fault_pin ( brushless33_t *ctx );
```

### Application Init

> Initializes the logger and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless33_cfg_t brushless33_cfg;  /**< Click config object. */

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
    brushless33_cfg_setup( &brushless33_cfg );
    BRUSHLESS33_MAP_MIKROBUS( brushless33_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless33_init( &brushless33, &brushless33_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS33_ERROR == brushless33_default_cfg ( &brushless33 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Adjusts the motor's duty cycle to control its speed, alternating between increasing
and decreasing duty values. Fault conditions are checked and resolved to maintain
stable operation. Additional motor controls, such as switching direction and braking,
are triggered based on the duty cycle limits. Each step will be logged on the USB UART
where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 0;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    uint32_t gate_drv_flt = 0;
    uint32_t controller_flt = 0;

    if ( !brushless33_get_fault_pin ( &brushless33 ) )
    {
        if ( BRUSHLESS33_OK == brushless33_read_fault ( &brushless33, &gate_drv_flt, &controller_flt ) )
        {
            if ( gate_drv_flt )
            {
                log_printf( &logger, " GATE DRIVER FAULT: 0x%.8LX\r\n", gate_drv_flt );
            }
            if ( controller_flt )
            {
                log_printf( &logger, " CONTROLLER FAULT: 0x%.8LX\r\n", controller_flt );
            }
        }
        brushless33_clear_fault ( &brushless33 );
        // Motor startup delay
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    brushless33_set_duty_cycle ( &brushless33, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( ( 1 == duty_cnt ) && ( 1 == duty_inc ) )
    {
        // Motor startup delay
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    Delay_ms ( 1000 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 10 ) 
    {        
        duty_cnt = 9;
        duty_inc = -1;
    }
    else if ( duty_cnt < 0 ) 
    {
        duty_cnt = 0;
        duty_inc = 1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless33_pull_brake ( &brushless33 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Switch direction\r\n" );
        brushless33_switch_direction ( &brushless33 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless33_release_brake ( &brushless33 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The library is configured for an A2212/13T 1000KV motor with a 12V power supply.

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

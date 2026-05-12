
---
# Brushless 28 Click

> [Brushless 28 Click](https://www.mikroe.com/?pid_product=MIKROE-6919) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6919&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 28 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless28

### Example Key Functions

- `brushless28_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void brushless28_cfg_setup ( brushless28_cfg_t *cfg );
```

- `brushless28_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t brushless28_init ( brushless28_t *ctx, brushless28_cfg_t *cfg );
```

- `brushless28_default_cfg` This function executes a default configuration of Brushless 28 Click board.
```c
err_t brushless28_default_cfg ( brushless28_t *ctx );
```

- `brushless28_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless28_set_duty_cycle ( brushless28_t *ctx, float duty_cycle );
```

- `brushless28_switch_direction` This function switches the direction of motor rotation by toggling the DIR pin logic state.
```c
void brushless28_switch_direction ( brushless28_t *ctx );
```

- `brushless28_release_brake` This function releases brake by setting the BRAKE pin to high logic state.
```c
void brushless28_release_brake ( brushless28_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless28_cfg_t brushless28_cfg;  /**< Click config object. */

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
    brushless28_cfg_setup( &brushless28_cfg );
    BRUSHLESS28_MAP_MIKROBUS( brushless28_cfg, MIKROBUS_POSITION_BRUSHLESS28 );
    if ( BRUSHLESS28_OK != brushless28_init( &brushless28, &brushless28_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS28_OK != brushless28_default_cfg ( &brushless28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500 milliseconds.
The duty cycle ranges from 0% to 100%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 0;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless28_set_duty_cycle ( &brushless28, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 10 ) 
    {        
        duty_cnt = 9;
        duty_inc = -1;
    }
    else if ( duty_cnt < 0 ) 
    {
        duty_cnt = 1;
        duty_inc = 1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless28_pull_brake ( &brushless28 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Switch direction\r\n" );
        brushless28_switch_direction ( &brushless28 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless28_release_brake ( &brushless28 );
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


---
# DC Motor 32 Click

> [DC Motor 32 Click](https://www.mikroe.com/?pid_product=MIKROE-6832) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6832&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the DC Motor 32 Click board for
controlling a DC motor. The application switches between different
operation modes (forward, brake, reverse, and off) and measures the
output current in each state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor32

### Example Key Functions

- `dcmotor32_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dcmotor32_cfg_setup ( dcmotor32_cfg_t *cfg );
```

- `dcmotor32_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dcmotor32_init ( dcmotor32_t *ctx, dcmotor32_cfg_t *cfg );
```

- `dcmotor32_default_cfg` This function executes a default configuration of DC Motor 32 Click board.
```c
err_t dcmotor32_default_cfg ( dcmotor32_t *ctx );
```

- `dcmotor32_set_operation_mode` This function sets the selected device operation mode.
```c
err_t dcmotor32_set_operation_mode ( dcmotor32_t *ctx, uint8_t mode );
```

- `dcmotor32_get_out_current` This function calculates the output current from the measured ADC voltage.
```c
err_t dcmotor32_get_out_current ( dcmotor32_t *ctx, float *current );
```

### Application Init

> Initializes the logger and DC Motor 32 Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor32_cfg_t dcmotor32_cfg;  /**< Click config object. */

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
    dcmotor32_cfg_setup( &dcmotor32_cfg );
    DCMOTOR32_MAP_MIKROBUS( dcmotor32_cfg, MIKROBUS_POSITION_DCMOTOR32 );
    if ( DCMOTOR32_OK != dcmotor32_init( &dcmotor32, &dcmotor32_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR32_OK != dcmotor32_default_cfg ( &dcmotor32 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles through motor operation modes, measures the output current, and logs the results to the serial terminal.

```c
void application_task ( void )
{
    float current = 0;
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_FORWARD_HSB ) )
    {
        log_printf( &logger, " MODE: Forward\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
        }
    }
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_SLOW_DECAY_LSA ) )
    {
        log_printf( &logger, " MODE: Brake\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
        }
    }
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_REVERSE_HSA ) )
    {
        log_printf( &logger, " MODE: Reverse\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
        }
    }
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_HALF_BRIDGE_A_TRI_STATE ) )
    {
        log_printf( &logger, " MODE: Off\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
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


---
# Stepper 3 Click

> [Stepper 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2035) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2035&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Stepper 3 Click board by driving the motor in both directions for a desired number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper3

### Example Key Functions

- `stepper3_cfg_setup` Config Object Initialization function.
```c
void stepper3_cfg_setup ( stepper3_cfg_t *cfg );
```

- `stepper3_init` Initialization function.
```c
err_t stepper3_init ( stepper3_t *ctx, stepper3_cfg_t *cfg );
```

- `stepper3_set_step_mode` This function sets the step mode resolution settings in ctx->step_mode.
```c
void stepper3_set_step_mode ( stepper3_t *ctx, uint8_t mode );
```

- `stepper3_set_direction` This function sets the motor direction to clockwise or counter-clockwise in ctx->direction.
```c
void stepper3_set_direction ( stepper3_t *ctx, uint8_t dir );
```

- `stepper3_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper3_drive_motor ( stepper3_t *ctx, uint32_t steps, uint8_t speed );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper3_cfg_t stepper3_cfg;  /**< Click config object. */

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
    stepper3_cfg_setup( &stepper3_cfg );
    STEPPER3_MAP_MIKROBUS( stepper3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper3_init( &stepper3, &stepper3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 64 full steps and then counter-clockiwse for 128 half
steps with 2 seconds delay before changing the direction. All data is being logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 64 full steps clockwise \r\n\n" );
    stepper3_set_step_mode ( &stepper3, STEPPER3_MODE_FULL_STEP );
    stepper3_set_direction ( &stepper3, STEPPER3_DIR_CW );
    stepper3_drive_motor ( &stepper3, 64, STEPPER3_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 128 half steps counter-clockwise \r\n\n" );
    stepper3_set_step_mode ( &stepper3, STEPPER3_MODE_HALF_STEP );
    stepper3_set_direction ( &stepper3, STEPPER3_DIR_CCW );
    stepper3_drive_motor ( &stepper3, 128, STEPPER3_SPEED_VERY_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Step Motor 5v [MIKROE-1530] is a fully compatible stepper motor for this Click board: https://www.mikroe.com/step-motor-5v

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


---
# Stepper 13 Click

> [Stepper 13 Click](https://www.mikroe.com/?pid_product=MIKROE-3736) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3736&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Stepper 13 Click board by driving the motor in both directions for a desired number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper13

### Example Key Functions

- `stepper13_cfg_setup` Config Object Initialization function.
```c
void stepper13_cfg_setup ( stepper13_cfg_t *cfg );
```

- `stepper13_init` Initialization function.
```c
err_t stepper13_init ( stepper13_t *ctx, stepper13_cfg_t *cfg );
```

- `stepper13_default_cfg` Click Default Configuration function.
```c
err_t stepper13_default_cfg ( stepper13_t *ctx );
```

- `stepper13_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
err_t stepper13_set_direction ( stepper13_t *ctx, uint8_t dir );
```

- `stepper13_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper13_set_step_mode ( stepper13_t *ctx, uint8_t mode );
```

- `stepper13_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t stepper13_drive_motor ( stepper13_t *ctx, uint32_t steps, uint8_t speed );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper13_cfg_t stepper13_cfg;  /**< Click config object. */

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
    stepper13_cfg_setup( &stepper13_cfg );
    STEPPER13_MAP_MIKROBUS( stepper13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper13_init( &stepper13, &stepper13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER13_ERROR == stepper13_default_cfg ( &stepper13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockwise for 200 half
steps and 400 quarter steps with 2 seconds delay on driving mode change. All data is
being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_FULL_STEP );
    stepper13_drive_motor ( &stepper13, 200, STEPPER13_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CCW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_HALF_STEP );
    stepper13_drive_motor ( &stepper13, 200, STEPPER13_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CCW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_QUARTER_STEP );
    stepper13_drive_motor ( &stepper13, 400, STEPPER13_SPEED_FAST );
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

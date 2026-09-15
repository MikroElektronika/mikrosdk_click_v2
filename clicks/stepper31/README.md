
---
# Stepper 31 Click

> [Stepper 31 Click](https://www.mikroe.com/?pid_product=MIKROE-7083) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7083&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Stepper 31 Click by driving a bipolar
stepper motor in both directions for a specified number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper31

### Example Key Functions

- `stepper31_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void stepper31_cfg_setup ( stepper31_cfg_t *cfg );
```

- `stepper31_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t stepper31_init ( stepper31_t *ctx, stepper31_cfg_t *cfg );
```

- `stepper31_default_cfg` This function resets and verifies the expander, then applies the default motor and fault settings with both windings off.
```c
err_t stepper31_default_cfg ( stepper31_t *ctx );
```

- `stepper31_set_direction` This function stores the direction for the next drive_motor call.
```c
err_t stepper31_set_direction ( stepper31_t *ctx, uint8_t dir );
```

- `stepper31_set_step_mode` This function selects the step resolution and resets the sequence index.
```c
err_t stepper31_set_step_mode ( stepper31_t *ctx, uint8_t mode );
```

- `stepper31_drive_motor` This function drives the requested steps, then releases both windings.
```c
err_t stepper31_drive_motor ( stepper31_t *ctx, uint32_t steps, uint8_t speed );
```

### Application Init

> Initializes the logger and Click driver, verifies expander communication,
and selects the stepping mode while leaving both motor windings off.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper31_cfg_t stepper31_cfg;  /**< Click config object. */

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
    stepper31_cfg_setup( &stepper31_cfg );
    STEPPER31_MAP_MIKROBUS( stepper31_cfg, MIKROBUS_POSITION_STEPPER31 );
    if ( SPI_MASTER_ERROR == stepper31_init( &stepper31, &stepper31_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER31_ERROR == stepper31_default_cfg ( &stepper31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockwise for
200 half steps and 400 quarter steps, with a 1 second pause on mode change.
Each move is logged before starting. The driver checks fault inputs during
motion and de-energizes the windings when the move ends.

```c
void application_task ( void )
{
    log_printf( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper31_set_direction( &stepper31, STEPPER31_DIR_CW );
    stepper31_set_step_mode( &stepper31, STEPPER31_MODE_FULL_STEP );
    if ( STEPPER31_ERROR == stepper31_drive_motor( &stepper31, 200, STEPPER31_SPEED_SLOW ) )
    {
        log_error( &logger, " Motor movement or driver fault." );
        for ( ; ; );
    }
    Delay_ms( 1000 );

    log_printf( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper31_set_direction( &stepper31, STEPPER31_DIR_CCW );
    stepper31_set_step_mode( &stepper31, STEPPER31_MODE_HALF_STEP );
    if ( STEPPER31_ERROR == stepper31_drive_motor( &stepper31, 200, STEPPER31_SPEED_MEDIUM ) )
    {
        log_error( &logger, " Motor movement or driver fault." );
        for ( ; ; );
    }
    Delay_ms( 1000 );

    log_printf( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper31_set_direction( &stepper31, STEPPER31_DIR_CCW );
    stepper31_set_step_mode( &stepper31, STEPPER31_MODE_QUARTER_STEP );
    if ( STEPPER31_ERROR == stepper31_drive_motor( &stepper31, 400, STEPPER31_SPEED_FAST ) )
    {
        log_error( &logger, " Motor movement or driver fault." );
        for ( ; ; );
    }
    Delay_ms( 1000 );
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

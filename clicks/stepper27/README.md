
---
# Stepper 27 Click

> [Stepper 27 Click](https://www.mikroe.com/?pid_product=MIKROE-6613) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6613&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Stepper 27 Click board by driving the motor in both directions for a desired number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper27

### Example Key Functions

- `stepper27_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void stepper27_cfg_setup ( stepper27_cfg_t *cfg );
```

- `stepper27_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t stepper27_init ( stepper27_t *ctx, stepper27_cfg_t *cfg );
```

- `stepper27_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper27_set_direction ( stepper27_t *ctx, uint8_t dir );
```

- `stepper27_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper27_drive_motor ( stepper27_t *ctx, uint32_t steps, uint8_t speed );
```

### Application Init

> Initializes the driver and resets the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper27_cfg_t stepper27_cfg;  /**< Click config object. */

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
    stepper27_cfg_setup( &stepper27_cfg );
    STEPPER27_MAP_MIKROBUS( stepper27_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper27_init( &stepper27, &stepper27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    stepper27_reset_device ( &stepper27 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 100 slow steps and 300 medium speed steps and
then counter-clockwise for 400 fast steps with a 1 second delay on driving mode change. 
All data is being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 100 steps clockwise, speed: slow\r\n\n" );
    stepper27_set_direction ( &stepper27, STEPPER27_DIR_CW );
    stepper27_drive_motor ( &stepper27, 100, STEPPER27_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 300 steps clockwise, speed: medium\r\n\n" );
    stepper27_set_direction ( &stepper27, STEPPER27_DIR_CW );
    stepper27_drive_motor ( &stepper27, 300, STEPPER27_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 steps counter-clockwise, speed: fast\r\n\n" );
    stepper27_set_direction ( &stepper27, STEPPER27_DIR_CCW );
    stepper27_drive_motor ( &stepper27, 400, STEPPER27_SPEED_FAST );
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

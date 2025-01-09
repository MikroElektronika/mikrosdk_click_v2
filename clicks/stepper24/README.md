
---
# Stepper 24 Click

> [Stepper 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6254) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6254&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Stepper 24 Click board by driving the motor in both directions for a desired number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper24

### Example Key Functions

- `stepper24_cfg_setup` Config Object Initialization function.
```c
void stepper24_cfg_setup ( stepper24_cfg_t *cfg );
```

- `stepper24_init` Initialization function.
```c
err_t stepper24_init ( stepper24_t *ctx, stepper24_cfg_t *cfg );
```

- `stepper24_default_cfg` Click Default Configuration function.
```c
err_t stepper24_default_cfg ( stepper24_t *ctx );
```

- `stepper24_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper24_set_direction ( stepper24_t *ctx, uint8_t dir );
```

- `stepper24_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper24_set_step_mode ( stepper24_t *ctx, uint8_t mode );
```

- `stepper24_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper24_drive_motor ( stepper24_t *ctx, uint32_t steps, uint8_t speed );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper24_cfg_t stepper24_cfg;  /**< Click config object. */

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
    stepper24_cfg_setup( &stepper24_cfg );
    STEPPER24_MAP_MIKROBUS( stepper24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper24_init( &stepper24, &stepper24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER24_ERROR == stepper24_default_cfg ( &stepper24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
steps and 400 quarter steps with a 1 second delay on driving mode change. All data is
being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper24_set_direction ( &stepper24, STEPPER24_DIR_CW );
    stepper24_set_step_mode ( &stepper24, STEPPER24_MODE_FULL_STEP );
    stepper24_drive_motor ( &stepper24, 200, STEPPER24_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper24_set_direction ( &stepper24, STEPPER24_DIR_CCW );
    stepper24_set_step_mode ( &stepper24, STEPPER24_MODE_HALF_STEP_TYPE_A );
    stepper24_drive_motor ( &stepper24, 200, STEPPER24_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper24_set_direction ( &stepper24, STEPPER24_DIR_CCW );
    stepper24_set_step_mode ( &stepper24, STEPPER24_MODE_QUARTER_STEP );
    stepper24_drive_motor ( &stepper24, 400, STEPPER24_SPEED_FAST );
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


---
# H-Bridge Click

> [H-Bridge Click](https://www.mikroe.com/?pid_product=MIKROE-3031) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3031&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge Click board by driving the motor in both directions for a desired number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge

### Example Key Functions

- `hbridge_cfg_setup` Config Object Initialization function.
```c
void hbridge_cfg_setup ( hbridge_cfg_t *cfg );
```

- `hbridge_init` Initialization function.
```c
err_t hbridge_init ( hbridge_t *ctx, hbridge_cfg_t *cfg );
```

- `hbridge_set_step_mode` This function sets the step mode resolution settings in @b ctx->step_mode.
```c
void hbridge_set_step_mode ( hbridge_t *ctx, uint8_t mode );
```

- `hbridge_set_direction` This function sets the motor direction to clockwise or counter-clockwise in @b ctx->direction.
```c
void hbridge_set_direction ( hbridge_t *ctx, uint8_t dir );
```

- `hbridge_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void hbridge_drive_motor ( hbridge_t *ctx, uint32_t steps, uint8_t speed );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge_cfg_t hbridge_cfg;  /**< Click config object. */

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
    hbridge_cfg_setup( &hbridge_cfg );
    HBRIDGE_MAP_MIKROBUS( hbridge_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridge_init( &hbridge, &hbridge_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 400 half
steps with a 2 seconds delay before changing the direction. All data is being logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    hbridge_set_step_mode ( &hbridge, HBRIDGE_MODE_FULL_STEP );
    hbridge_set_direction ( &hbridge, HBRIDGE_DIR_CW );
    hbridge_drive_motor ( &hbridge, 200, HBRIDGE_SPEED_MEDIUM );
    log_printf ( &logger, " Move 200 full steps clockwise\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge_set_step_mode ( &hbridge, HBRIDGE_MODE_HALF_STEP );
    hbridge_set_direction ( &hbridge, HBRIDGE_DIR_CCW );
    hbridge_drive_motor ( &hbridge, 400, HBRIDGE_SPEED_FAST );
    log_printf ( &logger, " Move 400 half steps counter-clockwise\r\n\n" );
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

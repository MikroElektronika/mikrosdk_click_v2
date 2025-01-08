
---
# Stepper 4 Click

> [Stepper 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2748) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2748&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Stepper 4 Click board by driving the motor in both directions for a desired number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper4

### Example Key Functions

- `stepper4_cfg_setup` Config Object Initialization function.
```c
void stepper4_cfg_setup ( stepper4_cfg_t *cfg );
```

- `stepper4_init` Initialization function.
```c
err_t stepper4_init ( stepper4_t *ctx, stepper4_cfg_t *cfg );
```

- `stepper4_default_cfg` Click Default Configuration function.
```c
void stepper4_default_cfg ( stepper4_t *ctx );
```

- `stepper4_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper4_set_direction ( stepper4_t *ctx, uint8_t dir );
```

- `stepper4_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper4_drive_motor ( stepper4_t *ctx, uint32_t steps, uint8_t speed );
```

- `stepper4_reset_device` This function resets the device by toggling the RST pin.
```c
void stepper4_reset_device ( stepper4_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper4_cfg_t stepper4_cfg;  /**< Click config object. */

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
    stepper4_cfg_setup( &stepper4_cfg );
    STEPPER4_MAP_MIKROBUS( stepper4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper4_init( &stepper4, &stepper4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepper4_default_cfg ( &stepper4 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 200 steps and then counter-clockiwse for 100 steps with 2 seconds delay before changing the direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 steps clockwise \r\n\n" );
    stepper4_set_direction ( &stepper4, STEPPER4_DIR_CW );
    stepper4_drive_motor ( &stepper4, 200, STEPPER4_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
    stepper4_set_direction ( &stepper4, STEPPER4_DIR_CCW );
    stepper4_drive_motor ( &stepper4, 100, STEPPER4_SPEED_FAST );
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

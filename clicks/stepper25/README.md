
---
# Stepper 25 Click

> [Stepper 25 Click](https://www.mikroe.com/?pid_product=MIKROE-6561) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6561&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the operation of the Stepper 25 Click board, 
which is used to control a bipolar stepper motor. The application initializes 
the board and executes different step modes, directions, and speeds to 
showcase precise motor control.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper25

### Example Key Functions

- `stepper25_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void stepper25_cfg_setup ( stepper25_cfg_t *cfg );
```

- `stepper25_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t stepper25_init ( stepper25_t *ctx, stepper25_cfg_t *cfg );
```

- `stepper25_default_cfg` Click Default Configuration function.
```c
err_t stepper25_default_cfg ( stepper25_t *ctx );
```

- `stepper25_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper25_set_direction ( stepper25_t *ctx, uint8_t dir );
```

- `stepper25_set_step_mode` This function sets the step mode (microstepping level) of the Stepper 25 device.
```c
err_t stepper25_set_step_mode ( stepper25_t *ctx, uint8_t step_mode );
```

- `stepper25_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t stepper25_drive_motor ( stepper25_t *ctx, uint32_t steps, uint8_t speed );
```

### Application Init

> Initializes the logger and Stepper 25 Click board. Configures the motor driver 
with default settings, preparing it for stepper motor control.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper25_cfg_t stepper25_cfg;  /**< Click config object. */

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
    stepper25_cfg_setup( &stepper25_cfg );
    STEPPER25_MAP_MIKROBUS( stepper25_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == stepper25_init( &stepper25, &stepper25_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER25_ERROR == stepper25_default_cfg ( &stepper25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Moves the stepper motor in different step modes and directions at varying speeds. 
The motor completes a predefined number of steps in each mode, switching between 
clockwise (CW) and counterclockwise (CCW) directions with different step resolutions.

```c
void application_task ( void )
{
    log_printf ( &logger, " Step mode: 1/16\r\n" );
    log_printf ( &logger, " Direction: CW\r\n" );
    log_printf ( &logger, " Steps: 1600\r\n" );
    log_printf ( &logger, " Speed: Medium\r\n\n" );
    stepper25_set_direction ( &stepper25, STEPPER25_DIR_CW );
    stepper25_set_step_mode ( &stepper25, STEPPER25_STEP_MODE_1_OVER_16 );
    stepper25_drive_motor ( &stepper25, 1600, STEPPER25_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Step mode: 1/8\r\n" );
    log_printf ( &logger, " Direction: CCW\r\n" );
    log_printf ( &logger, " Steps: 1600\r\n" );
    log_printf ( &logger, " Speed: Fast\r\n\n" );
    stepper25_set_direction ( &stepper25, STEPPER25_DIR_CCW );
    stepper25_set_step_mode ( &stepper25, STEPPER25_STEP_MODE_1_OVER_8 );
    stepper25_drive_motor ( &stepper25, 1600, STEPPER25_SPEED_FAST );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Step mode: 1/4\r\n" );
    log_printf ( &logger, " Direction: CW\r\n" );
    log_printf ( &logger, " Steps: 400\r\n" );
    log_printf ( &logger, " Speed: Slow\r\n\n" );
    stepper25_set_direction ( &stepper25, STEPPER25_DIR_CW );
    stepper25_set_step_mode ( &stepper25, STEPPER25_STEP_MODE_QUARTER );
    stepper25_drive_motor ( &stepper25, 400, STEPPER25_SPEED_SLOW );
    Delay_ms ( 1000 );
}
```

### Note

> Ensure proper power supply and motor connections before running the example.

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

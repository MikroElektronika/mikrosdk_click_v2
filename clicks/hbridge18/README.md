
---
# H-Bridge 18 Click

> [H-Bridge 18 Click](https://www.mikroe.com/?pid_product=MIKROE-6508) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6508&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the operation of the H-Bridge 18 Click board, which
provides control over two DC motors using an H-Bridge driver. The application
initializes the board and alternates between different motor states, including
forward, reverse, coast, and braking, to demonstrate bidirectional motor control.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge18

### Example Key Functions

- `hbridge18_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void hbridge18_cfg_setup ( hbridge18_cfg_t *cfg );
```

- `hbridge18_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t hbridge18_init ( hbridge18_t *ctx, hbridge18_cfg_t *cfg );
```

- `hbridge18_default_cfg` Click Default Configuration function.
```c
err_t hbridge18_default_cfg ( hbridge18_t *ctx );
```

- `hbridge18_enable_device` This function enables the H-Bridge 18 device by setting the sleep pin high.
```c
void hbridge18_enable_device ( hbridge18_t *ctx );
```

- `hbridge18_disable_device` This function disables the H-Bridge 18 device by setting the sleep pin low.
```c
void hbridge18_disable_device ( hbridge18_t *ctx );
```

- `hbridge18_set_motor_state` This function sets the motor state for the selected motor (coast, forward, reverse, brake low-side, or brake high-side).
```c
err_t hbridge18_set_motor_state ( hbridge18_t *ctx, uint8_t motor, uint8_t state );
```

### Application Init

> Initializes the logger and the H-Bridge 18 Click board. Configures the motor driver to the default settings, preparing it for operation.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge18_cfg_t hbridge18_cfg;  /**< Click config object. */

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
    hbridge18_cfg_setup( &hbridge18_cfg );
    HBRIDGE18_MAP_MIKROBUS( hbridge18_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge18_init( &hbridge18, &hbridge18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE18_ERROR == hbridge18_default_cfg ( &hbridge18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Alternates motor states in a sequence to demonstrate different control functionalities.
The motors are set to move forward and reverse, followed by coasting and braking, repeating the cycle continuously.

```c
void application_task ( void )
{
    log_printf( &logger, " Motor 0: Forward\r\n" );
    log_printf( &logger, " Motor 1: Reverse\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_FORWARD );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Motor 0: Coast\r\n" );
    log_printf( &logger, " Motor 1: Brake LS\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_COAST );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_BRAKE_LS );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Motor 0: Reverse\r\n" );
    log_printf( &logger, " Motor 1: Forward\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_REVERSE );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Motor 0: Brake HS\r\n" );
    log_printf( &logger, " Motor 1: Coast\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_BRAKE_HS );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_COAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Ensure proper power supply (4.5V-32V, depending on motor specifications) and motor connections (motor 0: O1-O2; motor 1: O3-O4) before running the example.

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


---
# H-Bridge 19 Click

> [H-Bridge 19 Click](https://www.mikroe.com/?pid_product=MIKROE-7004) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7004&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 19 Click board by
driving the DC motors connected between OUT1A-OUT1B and OUT2A-OUT2B in both directions. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge19

### Example Key Functions

- `hbridge19_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void hbridge19_cfg_setup ( hbridge19_cfg_t *cfg );
```

- `hbridge19_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t hbridge19_init ( hbridge19_t *ctx, hbridge19_cfg_t *cfg );
```

- `hbridge19_default_cfg` This function executes a default configuration of H-Bridge 19 Click board.
```c
err_t hbridge19_default_cfg ( hbridge19_t *ctx );
```

- `hbridge19_enable_device` This function enables the device by setting the PS pin to high logic state.
```c
err_t hbridge19_enable_device ( hbridge19_t *ctx );
```

- `hbridge19_set_motor_state` This function sets the operating state for the selected motor.
```c
err_t hbridge19_set_motor_state ( hbridge19_t *ctx, uint8_t motor, uint8_t state );
```

- `hbridge19_get_fault` This function checks whether overcurrent protection or thermal shutdown circuit is activated.
```c
err_t hbridge19_get_fault ( hbridge19_t *ctx, uint8_t *fault );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge19_cfg_t hbridge19_cfg;  /**< Click config object. */

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
    hbridge19_cfg_setup( &hbridge19_cfg );
    HBRIDGE19_MAP_MIKROBUS( hbridge19_cfg, MIKROBUS_POSITION_HBRIDGE19 );
    if ( I2C_MASTER_ERROR == hbridge19_init( &hbridge19, &hbridge19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE19_ERROR == hbridge19_default_cfg ( &hbridge19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motors connected between OUT1A-OUT1B and OUT2A-OUT2B in both directions
in the span of 12 seconds, and logs data on the USB UART where you can track the program flow.

```c
void application_task ( void ) 
{
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_FORWARD );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_FORWARD );
    log_printf( &logger, "\r\n MOTOR 1: FORWARD\r\n" );
    log_printf( &logger, " MOTOR 2: FORWARD\r\n" );
    hbridge19_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_BRAKE );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_BRAKE );
    log_printf( &logger, "\r\n MOTOR 1: BRAKE\r\n" );
    log_printf( &logger, " MOTOR 2: BRAKE\r\n" );
    hbridge19_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_REVERSE );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_REVERSE );
    log_printf( &logger, "\r\n MOTOR 1: REVERSE\r\n" );
    log_printf( &logger, " MOTOR 2: REVERSE\r\n" );
    hbridge19_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_HI_Z );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_HI_Z );
    log_printf( &logger, "\r\n MOTOR 1: DISCONNECTED\r\n" );
    log_printf( &logger, " MOTOR 2: DISCONNECTED\r\n" );
    hbridge19_check_fault ( );
    Delay_ms ( 1000 );
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

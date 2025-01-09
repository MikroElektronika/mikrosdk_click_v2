
---
# H-Bridge 11 Click

> [H-Bridge 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5636) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5636&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 11 Click board by driving the DC motors connected between OUT0-OUT1 and OUT2-OUT3 in both directions. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge11

### Example Key Functions

- `hbridge11_cfg_setup` Config Object Initialization function.
```c
void hbridge11_cfg_setup ( hbridge11_cfg_t *cfg );
```

- `hbridge11_init` Initialization function.
```c
err_t hbridge11_init ( hbridge11_t *ctx, hbridge11_cfg_t *cfg );
```

- `hbridge11_default_cfg` Click Default Configuration function.
```c
err_t hbridge11_default_cfg ( hbridge11_t *ctx );
```

- `hbridge11_get_fault_pin` This function returns the fault pin logic state.
```c
uint8_t hbridge11_get_fault_pin ( hbridge11_t *ctx );
```

- `hbridge11_read_flags` This function reads and clears the fault flags from the status register.
```c
err_t hbridge11_read_flags ( hbridge11_t *ctx, uint8_t *fault_flags );
```

- `hbridge11_set_motor_state` This function sets the operating state for the selected motor from the half-bridge pairs 0-1, 2-3, 4-5, or 6-7.
```c
err_t hbridge11_set_motor_state ( hbridge11_t *ctx, uint8_t motor, uint8_t state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge11_cfg_t hbridge11_cfg;  /**< Click config object. */

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
    hbridge11_cfg_setup( &hbridge11_cfg );
    HBRIDGE11_MAP_MIKROBUS( hbridge11_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge11_init( &hbridge11, &hbridge11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE11_ERROR == hbridge11_default_cfg ( &hbridge11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motors connected between OUT0-OUT1 and OUT2-OUT3 in both directions in the span of 12 seconds, and logs data on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_FORWARD );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_FORWARD );
    log_printf( &logger, "\r\n MOTOR 0: FORWARD\r\n" );
    log_printf( &logger, " MOTOR 1: FORWARD\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_BRAKE );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_BRAKE );
    log_printf( &logger, "\r\n MOTOR 0: BRAKE\r\n" );
    log_printf( &logger, " MOTOR 1: BRAKE\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_REVERSE );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_REVERSE );
    log_printf( &logger, "\r\n MOTOR 0: REVERSE\r\n" );
    log_printf( &logger, " MOTOR 1: REVERSE\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_HI_Z );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_HI_Z );
    log_printf( &logger, "\r\n MOTOR 0: DISCONNECTED\r\n" );
    log_printf( &logger, " MOTOR 1: DISCONNECTED\r\n" );
    hbridge11_check_fault ( );
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

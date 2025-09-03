
---
# DC Motor 31 Click

> [DC Motor 31 Click](https://www.mikroe.com/?pid_product=MIKROE-6712) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6712&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the operation of the DC Motor 31 Click board by
alternating the motor direction between forward and reverse with braking in between.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor31

### Example Key Functions

- `dcmotor31_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dcmotor31_cfg_setup ( dcmotor31_cfg_t *cfg );
```

- `dcmotor31_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dcmotor31_init ( dcmotor31_t *ctx, dcmotor31_cfg_t *cfg );
```

- `dcmotor31_default_cfg` This function executes a default configuration of DC Motor 31 Click board.
```c
err_t dcmotor31_default_cfg ( dcmotor31_t *ctx );
```

- `dcmotor31_set_mode` This function sets the motor control mode to forward, reverse, or brake.
```c
void dcmotor31_set_mode ( dcmotor31_t *ctx, uint8_t mode );
```

- `dcmotor31_set_torque` This function sets the output torque by writing to the OUTPUT register.
```c
err_t dcmotor31_set_torque ( dcmotor31_t *ctx, uint8_t torque );
```

### Application Init

> Initializes the logger and the Click board, then applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor31_cfg_t dcmotor31_cfg;  /**< Click config object. */

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
    dcmotor31_cfg_setup( &dcmotor31_cfg );
    DCMOTOR31_MAP_MIKROBUS( dcmotor31_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor31_init( &dcmotor31, &dcmotor31_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR31_ERROR == dcmotor31_default_cfg ( &dcmotor31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the motor direction from forward to reverse with a brake period in between,
and logs the current motor state on the UART terminal.

```c
void application_task ( void )
{
    log_printf( &logger, " Motor state : FORWARD\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor state : BRAKE\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_BRAKE );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor state : REVERSE\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Motor state : BRAKE\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_BRAKE );
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


---
# DC Motor 30 Click

> [DC Motor 30 Click](https://www.mikroe.com/?pid_product=MIKROE-6595) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6595&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the control of a DC motor using the DC Motor 30 Click board. 
It performs motor driving in different modes (forward, brake, reverse, and coast) 
and periodically reads the output current and fault status.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor30

### Example Key Functions

- `dcmotor30_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dcmotor30_cfg_setup ( dcmotor30_cfg_t *cfg );
```

- `dcmotor30_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dcmotor30_init ( dcmotor30_t *ctx, dcmotor30_cfg_t *cfg );
```

- `dcmotor30_default_cfg` This function executes a default configuration of DC Motor 30 Click board.
```c
err_t dcmotor30_default_cfg ( dcmotor30_t *ctx );
```

- `dcmotor30_drive_motor` This function drives the motor in the selected PWM control mode state.
```c
void dcmotor30_drive_motor ( dcmotor30_t *ctx, uint8_t state );
```

- `dcmotor30_get_out_current` This function reads the current output measurement in mA.
```c
err_t dcmotor30_get_out_current ( dcmotor30_t *ctx, float *current );
```

### Application Init

> Initializes the logger and the Click board driver, then sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor30_cfg_t dcmotor30_cfg;  /**< Click config object. */

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
    dcmotor30_cfg_setup( &dcmotor30_cfg );
    DCMOTOR30_MAP_MIKROBUS( dcmotor30_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor30_init( &dcmotor30, &dcmotor30_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR30_ERROR == dcmotor30_default_cfg ( &dcmotor30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor in different states and monitors the current consumption and possible fault conditions.

```c
void application_task ( void )
{
    float current = 0;

    log_printf( &logger, " Motor state : FORWARD\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : BRAKE\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : REVERSE\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : COAST\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_COAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }
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

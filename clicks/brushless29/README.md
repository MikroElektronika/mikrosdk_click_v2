
---
# Brushless 29 Click

> [Brushless 29 Click](https://www.mikroe.com/?pid_product=MIKROE-7085) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7085&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates motor speed and direction control with Brushless 29 Click. 
It sweeps the common motor command from zero to maximum and back to zero in both
directions using the selected PWM or SPI speed mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless29

### Example Key Functions

- `brushless29_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void brushless29_cfg_setup ( brushless29_cfg_t *cfg );
```

- `brushless29_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t brushless29_init ( brushless29_t *ctx, brushless29_cfg_t *cfg );
```

- `brushless29_default_cfg` This function executes a default configuration of Brushless 29 Click board.
```c
err_t brushless29_default_cfg ( brushless29_t *ctx );
```

- `brushless29_run_motor` This function sets the rotation direction and applies a common 0 to 512 speed command through the selected speed control mode.
```c
err_t brushless29_run_motor ( brushless29_t *ctx, uint8_t direction, uint16_t speed );
```

- `brushless29_stop_motor` This function clears the speed command and disables the motor gate driver.
```c
err_t brushless29_stop_motor ( brushless29_t *ctx );
```

### Application Init

> Initializes the communication and applies the default motor-control configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless29_cfg_t brushless29_cfg;  /**< Click config object. */

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
    brushless29_cfg_setup( &brushless29_cfg );
    BRUSHLESS29_MAP_MIKROBUS( brushless29_cfg, MIKROBUS_POSITION_BRUSHLESS29 );
    if ( BRUSHLESS29_OK != brushless29_init( &brushless29, &brushless29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS29_OK != brushless29_default_cfg ( &brushless29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the controller status, runs a stepped motor-speed sweep clockwise,
waits for the motor to stop, and repeats the sweep counter-clockwise.

```c
void application_task ( void )
{
    uint8_t pin_status = 0;
    err_t error_flag = BRUSHLESS29_OK;

    if ( !brushless29_get_int_pin ( &brushless29 ) )
    {
        error_flag = brushless29_read_exp_reg ( &brushless29, BRUSHLESS29_EXP_REG_INPUT, &pin_status );
        if ( BRUSHLESS29_ERROR == error_flag )
        {
            log_error( &logger, " Status read." );
            brushless29_stop_motor( &brushless29 );
        }
        else
        {
            if ( 0 == ( pin_status & BRUSHLESS29_EXP_PIN_PG ) )
            {
                log_error( &logger, " Motor supply is not ready." );
                error_flag = BRUSHLESS29_ERROR; 
            }
            if ( 0 == ( pin_status & BRUSHLESS29_EXP_PIN_FAULT ) )
            {
                log_error( &logger, " Gate driver fault." );
                brushless29_stop_motor( &brushless29 );
                error_flag = BRUSHLESS29_ERROR; 
            }
        }
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        log_printf( &logger, " Direction: clockwise\r\n" );
        error_flag = application_speed_sweep( BRUSHLESS29_DIR_CW );

        if ( BRUSHLESS29_OK == error_flag )
        {
            log_printf( &logger, " Stop motor\r\n\n" );
            error_flag = brushless29_stop_motor( &brushless29 );
        }

        if ( BRUSHLESS29_OK == error_flag )
        {
            log_printf( &logger, " Direction: counter-clockwise\r\n" );
            error_flag = application_speed_sweep( BRUSHLESS29_DIR_CCW );
        }

        if ( BRUSHLESS29_ERROR == error_flag )
        {
            log_error( &logger, " Motor control." );
        }

        log_printf( &logger, " Stop motor\r\n\n" );
        brushless29_stop_motor( &brushless29 );
    }

    Delay_ms( 1000 );
}
```

### Note

> Connect the external motor supply to VM, the three motor phases to SHA, SHB, and SHC,
and the Hall sensor connector to J2 before running the example. The library applies
each command through the speed mode selected by #BRUSHLESS29_SPEED_MODE.

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

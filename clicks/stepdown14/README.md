
---
# Step Down 14 Click

> [Step Down 14 Click](https://www.mikroe.com/?pid_product=MIKROE-6965) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6965&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Step Down 14 Click board for
adjustable output voltage control. The application continuously changes
the output voltage within the supported range and monitors the power-good
pin for fault indication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown14

### Example Key Functions

- `stepdown14_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void stepdown14_cfg_setup ( stepdown14_cfg_t *cfg );
```

- `stepdown14_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t stepdown14_init ( stepdown14_t *ctx, stepdown14_cfg_t *cfg );
```

- `stepdown14_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void stepdown14_enable_device ( stepdown14_t *ctx );
```

- `stepdown14_set_vout` This function calculates and sets the wiper value for the target output voltage.
```c
err_t stepdown14_set_vout ( stepdown14_t *ctx, float target_vout, float *set_vout );
```

- `stepdown14_get_pg_pin` This function returns the PG pin logic state.
```c
uint8_t stepdown14_get_pg_pin ( stepdown14_t *ctx );
```

### Application Init

> Initializes the logger and Step Down 14 Click driver, and enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown14_cfg_t stepdown14_cfg;  /**< Click config object. */

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
    stepdown14_cfg_setup( &stepdown14_cfg );
    STEPDOWN14_MAP_MIKROBUS( stepdown14_cfg, MIKROBUS_POSITION_STEPDOWN14 );
    if ( I2C_MASTER_ERROR == stepdown14_init( &stepdown14, &stepdown14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    stepdown14_enable_device ( &stepdown14 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Adjusts the output voltage between minimum and maximum values, logs the
target and actual configured voltage values, and checks the PG pin status
for fault detection.

```c
void application_task ( void )
{
    static float target_vout = STEPDOWN14_VOUT_MIN;
    static float step = 0.25;
    float set_vout = 0;

    if ( STEPDOWN14_OK == stepdown14_set_vout ( &stepdown14, target_vout, &set_vout ) )
    {
        log_printf( &logger, "Target VOUT: %.2f V\r\n\n", target_vout );
        log_printf( &logger, "Set VOUT: %.2f V\r\n\n", set_vout );
        target_vout += ( target_vout * step );
        if ( target_vout > STEPDOWN14_VOUT_MAX )
        {
            step = -step;
            target_vout = STEPDOWN14_VOUT_MAX;
        }
        else if ( target_vout < STEPDOWN14_VOUT_MIN )
        {
            step = -step;
            target_vout = STEPDOWN14_VOUT_MIN;
        }
    }

    if ( !stepdown14_get_pg_pin ( &stepdown14 ) )
    {
        log_error( &logger, "Fault detected via PG pin\r\n" );
    }

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

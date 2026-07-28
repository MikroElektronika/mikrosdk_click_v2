
---
# Step Down 15 Click

> [Step Down 15 Click](https://www.mikroe.com/?pid_product=MIKROE-7007) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7007&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Step Down 15 Click board for
adjustable output voltage control and power monitoring. The application
changes the output voltage within the supported range and reads PVIN,
VOUT, VCC, temperature, and status information.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown15

### Example Key Functions

- `stepdown15_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void stepdown15_cfg_setup ( stepdown15_cfg_t *cfg );
```

- `stepdown15_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t stepdown15_init ( stepdown15_t *ctx, stepdown15_cfg_t *cfg );
```

- `stepdown15_default_cfg` This function executes a default configuration of Step Down 15 Click board.
```c
err_t stepdown15_default_cfg ( stepdown15_t *ctx );
```

- `stepdown15_set_vout` This function sets the output voltage command value.
```c
err_t stepdown15_set_vout ( stepdown15_t *ctx, float voltage );
```

- `stepdown15_read_pvin` This function reads and calculates the input voltage value.
```c
err_t stepdown15_read_pvin ( stepdown15_t *ctx, float *voltage );
```

- `stepdown15_read_temperature` This function reads and calculates the average temperature value.
```c
err_t stepdown15_read_temperature ( stepdown15_t *ctx, float *temp_c );
```

### Application Init

> Initializes the logger and Step Down 15 Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown15_cfg_t stepdown15_cfg;  /**< Click config object. */

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
    stepdown15_cfg_setup( &stepdown15_cfg );
    STEPDOWN15_MAP_MIKROBUS( stepdown15_cfg, MIKROBUS_POSITION_STEPDOWN15 );
    if ( I2C_MASTER_ERROR == stepdown15_init( &stepdown15, &stepdown15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN15_ERROR == stepdown15_default_cfg ( &stepdown15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Adjusts the output voltage between minimum and maximum values, reads
voltage and temperature measurements, checks the status register for
fault conditions, and logs the results to the serial terminal.

```c
void application_task ( void )
{
    static float target_vout = STEPDOWN15_VOUT_MIN;
    static float step = 0.1;
    float set_vout = 0;
    float pvin = 0;
    float temp = 0;
    float vcc = 0;
    uint8_t status = 0;

    if ( STEPDOWN15_OK == stepdown15_set_vout ( &stepdown15, target_vout ) )
    {
        log_printf( &logger, "Target VOUT: %.3f V\r\n", target_vout );
    }
    Delay_ms ( 500 );
    
    if ( STEPDOWN15_OK == stepdown15_read_vout ( &stepdown15, &set_vout ) )
    {
        log_printf( &logger, "Set VOUT: %.3f V\r\n", set_vout );
    }

    if ( STEPDOWN15_OK == stepdown15_read_pvin ( &stepdown15, &pvin ) )
    {
        log_printf( &logger, "PVIN: %.3f V\r\n", pvin );
    }

    if ( STEPDOWN15_OK == stepdown15_read_vcc ( &stepdown15, &vcc ) )
    {
        log_printf( &logger, "VCC: %.3f V\r\n", vcc );
    }

    if ( STEPDOWN15_OK == stepdown15_read_temperature ( &stepdown15, &temp ) )
    {
        log_printf( &logger, "TEMP: %.1f degC\r\n", temp );
    }

    if ( STEPDOWN15_OK == stepdown15_read_reg( &stepdown15, STEPDOWN15_REG_STATUS, &status ) )
    {
        if ( STEPDOWN15_STATUS_POWER_GOOD != ( status & STEPDOWN15_STATUS_POWER_GOOD ) )
        {
            log_error( &logger, "Power Not Good" );
        }
        if ( status & STEPDOWN15_STATUS_OVERVOLTAGE )
        {
            log_error( &logger, "Overvoltage fault" );
        }
        if ( status & STEPDOWN15_STATUS_OVERCURRENT )
        {
            log_error( &logger, "Overcurrent fault" );
        }
        if ( status & STEPDOWN15_STATUS_TEMPERATURE )
        {
            log_error( &logger, "Temperature fault" );
        }
    }
    log_printf( &logger, "-----------------------------\r\n" );

    target_vout += step;
    if ( target_vout > STEPDOWN15_VOUT_MAX )
    {
        step = -step;
        target_vout = STEPDOWN15_VOUT_MAX;
    }
    else if ( target_vout < STEPDOWN15_VOUT_MIN )
    {
        step = -step;
        target_vout = STEPDOWN15_VOUT_MIN;
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


---
# Step Down 3 Click

> [Step Down 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5169) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5169&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Step Down 3 Click board by iterating through the entire output voltage range.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown3

### Example Key Functions

- `stepdown3_cfg_setup` Config Object Initialization function.
```c
void stepdown3_cfg_setup ( stepdown3_cfg_t *cfg );
```

- `stepdown3_init` Initialization function.
```c
err_t stepdown3_init ( stepdown3_t *ctx, stepdown3_cfg_t *cfg );
```

- `stepdown3_enable_device` This function enables the auxiliary output (VOUT_AUX) by setting the AUX pin to HIGH logic state.
```c
void stepdown3_enable_device ( stepdown3_t *ctx );
```

- `stepdown3_enable_aux_output` This function disables the auxiliary output (VOUT_AUX) by setting the AUX pin to LOW logic state.
```c
void stepdown3_enable_aux_output ( stepdown3_t *ctx );
```

- `stepdown3_set_output_voltage` This function sets the output voltage by setting the D2, D1, and D0 pins to a desired state.
```c
void stepdown3_set_output_voltage ( stepdown3_t *ctx, uint8_t vout );
```

### Application Init

> Initializes the driver and logger, then enables the Click board and disables the auxiliary output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown3_cfg_t stepdown3_cfg;  /**< Click config object. */

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
    stepdown3_cfg_setup( &stepdown3_cfg );
    STEPDOWN3_MAP_MIKROBUS( stepdown3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepdown3_init( &stepdown3, &stepdown3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepdown3_enable_device ( &stepdown3 );
    stepdown3_disable_aux_output ( &stepdown3 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 3 seconds and displays the set voltage output value on the USB UART.

```c
void application_task ( void )
{
    static uint8_t vout = STEPDOWN3_OUT_VOLTAGE_1V6;
    stepdown3_set_output_voltage ( &stepdown3, vout );
    switch ( vout )
    {
        case STEPDOWN3_OUT_VOLTAGE_1V6:
        {
            log_printf( &logger, " Output voltage: 1.6 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_1V8:
        {
            log_printf( &logger, " Output voltage: 1.8 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V1:
        {
            log_printf( &logger, " Output voltage: 2.1 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V5:
        {
            log_printf( &logger, " Output voltage: 2.5 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V7:
        {
            log_printf( &logger, " Output voltage: 2.7 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V8:
        {
            log_printf( &logger, " Output voltage: 2.8 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V0:
        {
            log_printf( &logger, " Output voltage: 3.0 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V3:
        {
            log_printf( &logger, " Output voltage: 3.3 V\r\n\n" );
            break;
        }
    }
    if ( ++vout > STEPDOWN3_OUT_VOLTAGE_3V3 )
    {
        vout = STEPDOWN3_OUT_VOLTAGE_1V6;
    }
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

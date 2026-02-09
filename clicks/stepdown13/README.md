
---
# Step Down 13 Click

> [Step Down 13 Click](https://www.mikroe.com/?pid_product=MIKROE-6846) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6846&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates how to initialize the Step Down 13 Click board
and how to control its output voltage by adjusting the potentiometer value over I2C.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown13

### Example Key Functions

- `stepdown13_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void stepdown13_cfg_setup ( stepdown13_cfg_t *cfg );
```

- `stepdown13_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t stepdown13_init ( stepdown13_t *ctx, stepdown13_cfg_t *cfg );
```

- `stepdown13_set_cot_mode` This function selects the constant on-time (COT) operating mode by setting the MODE pin.
```c
void stepdown13_set_cot_mode ( stepdown13_t *ctx );
```

- `stepdown13_enable_output` This function enables the device output by setting the EN pin.
```c
void stepdown13_enable_output ( stepdown13_t *ctx );
```

- `stepdown13_set_vout` This function calculates the required wiper position of the internal digital potentiometer based on the desired output voltage and programs the VREG control register accordingly.
```c
err_t stepdown13_set_vout ( stepdown13_t *ctx, float vout );
```

### Application Init

> Initializes the logger and Step Down 13 Click driver and enables the device in COT mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown13_cfg_t stepdown13_cfg;  /**< Click config object. */

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
    stepdown13_cfg_setup( &stepdown13_cfg );
    STEPDOWN13_MAP_MIKROBUS( stepdown13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown13_init( &stepdown13, &stepdown13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    stepdown13_set_cot_mode ( &stepdown13 );
    stepdown13_enable_output ( &stepdown13 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Gradually increases and decreases the output voltage across the supported range
and logs the current VOUT value. The VIN must always be higher than the VOUT set.

```c
void application_task ( void )
{
    static float vout = STEPDOWN13_VOUT_MIN;
    static float step = ( STEPDOWN13_VOUT_MAX - STEPDOWN13_VOUT_MIN ) / 20;

    if ( STEPDOWN13_OK == stepdown13_set_vout ( &stepdown13, vout ) )
    {
        log_printf( &logger, " VOUT: %.2f V\r\n\n", vout );
        vout += step;
        if ( ( vout > ( STEPDOWN13_VOUT_MAX + STEPDOWN13_FLOAT_COMPARE_OFFSET ) ) || 
             ( vout < ( STEPDOWN13_VOUT_MIN - STEPDOWN13_FLOAT_COMPARE_OFFSET ) ) )
        {
            step = -step;
            vout += step;
        }
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

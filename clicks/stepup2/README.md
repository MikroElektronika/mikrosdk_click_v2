
---
# Step Up 2 Click

> [Step Up 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6076) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6076&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Step Up 2 Click board by changing the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepUp2

### Example Key Functions

- `stepup2_cfg_setup` Config Object Initialization function.
```c
void stepup2_cfg_setup ( stepup2_cfg_t *cfg );
```

- `stepup2_init` Initialization function.
```c
err_t stepup2_init ( stepup2_t *ctx, stepup2_cfg_t *cfg );
```

- `stepup2_default_cfg` Click Default Configuration function.
```c
err_t stepup2_default_cfg ( stepup2_t *ctx );
```

- `stepup2_set_vout` This function sets the voltage output level.
```c
err_t stepup2_set_vout ( stepup2_t *ctx, stepup2_vout_t vout );
```

- `stepup2_set_resistance` This function sets a desired resistance by writing to the volatile memory register and the wiper position.
```c
err_t stepup2_set_resistance ( stepup2_t *ctx, float res_kohm );
```

- `stepup2_enable` This function turns on the power switch and enables the boost mode.
```c
void stepup2_enable ( stepup2_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepup2_cfg_t stepup2_cfg;  /**< Click config object. */

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
    stepup2_cfg_setup( &stepup2_cfg );
    STEPUP2_MAP_MIKROBUS( stepup2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepup2_init( &stepup2, &stepup2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPUP2_ERROR == stepup2_default_cfg ( &stepup2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application changes the output voltage and displays the current voltage output value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float vout_table[ 15 ] = { STEPUP2_VOUT_LIST };
    for ( stepup2_vout_t vout = STEPUP2_VOUT_5V5; vout <= STEPUP2_VOUT_3V3; vout++ )
    {
        if ( STEPUP2_OK == stepup2_set_vout( &stepup2, vout ) )
        {
            log_printf( &logger, " Voltage: %.2f[V]\r\n\n", vout_table[ vout ] );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
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

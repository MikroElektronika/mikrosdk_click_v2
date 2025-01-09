
---
# Step Down 12 Click

> [Step Down 12 Click](https://www.mikroe.com/?pid_product=MIKROE-6126) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6126&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Step Down 12 Click board by changing the output voltage every 3 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown12

### Example Key Functions

- `stepdown12_cfg_setup` Config Object Initialization function.
```c
void stepdown12_cfg_setup ( stepdown12_cfg_t *cfg );
```

- `stepdown12_init` Initialization function.
```c
err_t stepdown12_init ( stepdown12_t *ctx, stepdown12_cfg_t *cfg );
```

- `stepdown12_default_cfg` Click Default Configuration function.
```c
void stepdown12_default_cfg ( stepdown12_t *ctx );
```

- `stepdown12_get_pg_pin` This function returns the power good (PG) pin logic state.
```c
uint8_t stepdown12_get_pg_pin ( stepdown12_t *ctx );
```

- `stepdown12_set_vout` This function sets the voltage output by setting the digipot wiper resistance.
```c
err_t stepdown12_set_vout ( stepdown12_t *ctx, float vout );
```

- `stepdown12_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void stepdown12_enable_device ( stepdown12_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown12_cfg_t stepdown12_cfg;  /**< Click config object. */

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
    stepdown12_cfg_setup( &stepdown12_cfg );
    STEPDOWN12_MAP_MIKROBUS( stepdown12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown12_init( &stepdown12, &stepdown12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepdown12_default_cfg ( &stepdown12 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 3 seconds from MAX (5.5V) to MIN (1.05V) in steps of 0.5V
and displays the currently set voltage output value on the USB UART. It also monitors
the power good fault indication.

```c
void application_task ( void )
{
    static float vout = STEPDOWN12_VOUT_MAX;

    if ( !stepdown12_get_pg_pin ( &stepdown12 ) )
    {
        log_error( &logger, " Power Good Fault - Vout is below nominal regulation\r\n" );
    }

    if ( STEPDOWN12_OK == stepdown12_set_vout ( &stepdown12, vout ) )
    {
        log_printf( &logger, " Vout: %.3f V\r\n\n", vout );
        vout -= 0.5;
        if ( vout < STEPDOWN12_VOUT_MIN )
        {
            vout = STEPDOWN12_VOUT_MAX;
        }
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


---
# Step Down 8 Click

> [Step Down 8 Click](https://www.mikroe.com/?pid_product=MIKROE-5813) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5813&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Step Down 8 Click driver.
  This driver provides the functions to set the output voltage treshold.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown8

### Example Key Functions

- `stepdown8_cfg_setup` Config Object Initialization function.
```c
void stepdown8_cfg_setup ( stepdown8_cfg_t *cfg );
```

- `stepdown8_init` Initialization function.
```c
err_t stepdown8_init ( stepdown8_t *ctx, stepdown8_cfg_t *cfg );
```

- `stepdown8_default_cfg` Click Default Configuration function.
```c
err_t stepdown8_default_cfg ( stepdown8_t *ctx );
```

- `stepdown8_set_en_pin` Step Down 8 set EN pin state function.
```c
void stepdown8_set_en_pin ( stepdown8_t *ctx, uint8_t pin_state );
```

- `stepdown8_set_wiper_pos` Step Down 8 set wiper position.
```c
err_t stepdown8_set_wiper_pos ( stepdown8_t *ctx, uint16_t wiper_pos );
```

- `stepdown8_set_output` Step Down 8 set output voltage.
```c
err_t stepdown8_set_output ( stepdown8_t *ctx, float voltage );
```

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 3 V.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown8_cfg_t stepdown8_cfg;  /**< Click config object. */

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
    stepdown8_cfg_setup( &stepdown8_cfg );
    STEPDOWN8_MAP_MIKROBUS( stepdown8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown8_init( &stepdown8, &stepdown8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN8_ERROR == stepdown8_default_cfg ( &stepdown8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Step Down 8 Click board&trade; by changing 
  output voltage every 2 seconds starting from 3 V up to 18 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN8_MIN_OUTPUT; n_cnt <= STEPDOWN8_MAX_OUTPUT; n_cnt++ )
    {
        stepdown8_set_output( &stepdown8, ( float ) n_cnt );
        log_printf( &logger, " Output voltage %d V\r\n", ( uint16_t ) n_cnt );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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


---
# Step Down 11 Click

> [Step Down 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5936) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5936&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Step Down 11 Click driver.
  This driver provides the functions to set the output voltage treshold.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown11

### Example Key Functions

- `stepdown11_cfg_setup` Config Object Initialization function.
```c
void stepdown11_cfg_setup ( stepdown11_cfg_t *cfg );
```

- `stepdown11_init` Initialization function.
```c
err_t stepdown11_init ( stepdown11_t *ctx, stepdown11_cfg_t *cfg );
```

- `stepdown11_default_cfg` Click Default Configuration function.
```c
err_t stepdown11_default_cfg ( stepdown11_t *ctx );
```

- `stepdown11_get_resistance` Step Down 11 get the resistance function.
```c
err_t stepdown11_get_resistance ( stepdown11_t *ctx, uint8_t wiper_sel, float *res_kohm );
```

- `stepdown11_set_voltage` Step Down 11 set voltage output function.
```c
err_t stepdown11_set_voltage ( stepdown11_t *ctx, float v_out );
```

- `stepdown11_set_mode` Step Down 11 set S-CONF device configuration mode function.
```c
err_t stepdown11_set_mode ( stepdown11_t *ctx, float sconf_mode );
```

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 1 V.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown11_cfg_t stepdown11_cfg;  /**< Click config object. */

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
    stepdown11_cfg_setup( &stepdown11_cfg );
    STEPDOWN11_MAP_MIKROBUS( stepdown11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown11_init( &stepdown11, &stepdown11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN11_ERROR == stepdown11_default_cfg ( &stepdown11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Step Down 11 Click board&trade; by changing 
  output voltage every 5 seconds starting from 1 V up to 5 V.

```c
void application_task ( void ) 
{
    for ( uint8_t vout = 1; vout <= 5; vout++ )
    {
        log_printf( &logger, " Set output voltage %dV \r\n", ( uint16_t ) vout );
        stepdown11_set_voltage ( &stepdown11, vout );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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

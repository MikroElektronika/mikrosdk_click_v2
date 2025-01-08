
---
# Step Down 6 Click

> [Step Down 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5776) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5776&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Step Down 6 Click driver.
  This driver provides the functions to set the output voltage threshold.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown6

### Example Key Functions

- `stepdown6_cfg_setup` Config Object Initialization function.
```c
void stepdown6_cfg_setup ( stepdown6_cfg_t *cfg );
```

- `stepdown6_init` Initialization function.
```c
err_t stepdown6_init ( stepdown6_t *ctx, stepdown6_cfg_t *cfg );
```

- `stepdown6_default_cfg` Click Default Configuration function.
```c
err_t stepdown6_default_cfg ( stepdown6_t *ctx );
```

- `stepdown6_set_en_pin` Step Down 6 set EN pin state function.
```c
void stepdown6_set_en_pin ( stepdown6_t *ctx, uint8_t pin_state );
```

- `stepdown6_write_reg` Step Down 6 Register writing function.
```c
err_t stepdown6_write_reg ( stepdown6_t *ctx, uint8_t reg, uint8_t data_in );
```

- `stepdown6_set_out_voltage` Step Down 6 Set output voltage function.
```c
err_t stepdown6_set_out_voltage ( stepdown6_t *ctx, uint8_t out_sel, uint16_t out_val );
```

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 550 mV.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown6_cfg_t stepdown6_cfg;  /**< Click config object. */

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
    stepdown6_cfg_setup( &stepdown6_cfg );
    STEPDOWN6_MAP_MIKROBUS( stepdown6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown6_init( &stepdown6, &stepdown6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN6_ERROR == stepdown6_default_cfg ( &stepdown6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Step Down 6 Click board&trade; by changing 
  output voltage every 5 seconds starting from 550 mV up to 1820 mV.

```c
void application_task ( void ) 
{
    err_t error_flag = STEPDOWN6_OK;
    for ( uint16_t n_cnt = STEPDOWN6_MIN_VOUT_VAL; n_cnt <= STEPDOWN6_MAX_VOUT_VAL; n_cnt += STEPDOWN6_INCREMENT_VOUT_VAL )
    {
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT1, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT2, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT3, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT4, n_cnt );
        log_printf( &logger, "  Set voltage : %d mV \r\n", n_cnt );
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

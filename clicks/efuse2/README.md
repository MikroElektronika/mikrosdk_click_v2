
---
# eFuse 2 Click

> [eFuse 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4335) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4335&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrate the use of the eFuse 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse2

### Example Key Functions

- `efuse2_cfg_setup` Config Object Initialization function.
```c
void efuse2_cfg_setup ( efuse2_cfg_t *cfg );
```

- `efuse2_init` Initialization function.
```c
err_t efuse2_init ( efuse2_t *ctx, efuse2_cfg_t *cfg );
```

- `efuse2_default_cfg` Click Default Configuration function.
```c
err_t efuse2_default_cfg ( efuse2_t *ctx );
```

- `efuse2_set_operating_voltage` Set operating voltage function.
```c
err_t efuse2_set_operating_voltage ( efuse2_t *ctx, float voltage, float *min_voltage, float *max_voltage );
```

- `efuse2_set_current_limit` Set operating current function.
```c
err_t efuse2_set_current_limit ( efuse2_t *ctx, float current );
```

- `efuse2_get_fault` Get fault function.
```c
uint8_t efuse2_get_fault ( efuse2_t *ctx );
```

### Application Init

> Initialization driver enables - I2C,  
> AD5175: enable write, set the normal operating mode and operating  current to the 1,2 A;  
> AD5241: set operating voltage to the 12,0 V; 
> Display diagnostic states.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse2_cfg_t efuse2_cfg;  /**< Click config object. */

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
    efuse2_cfg_setup( &efuse2_cfg );
    EFUSE2_MAP_MIKROBUS( efuse2_cfg, MIKROBUS_1 );
    err_t init_flag = efuse2_init( &efuse2, &efuse2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( EFUSE2_ERROR == efuse2_default_cfg ( &efuse2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    op_current = 1.2;
    op_voltage = 12.0;

    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "    Set operating  value:    \r\n" );
    log_printf( &logger, "       Voltage: 12.0 V       \r\n" );
    efuse2_set_operating_voltage( &efuse2, op_voltage, &min_voltage, &max_voltage );
    Delay_ms ( 1000 );

    log_printf( &logger, "       Current:  1.2 A       \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    efuse2_set_current_limit( &efuse2, op_current );
    Delay_ms ( 1000 );

    log_printf( &logger, "    Turn ON Power Supply     \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> eFuse 2 Click board uses USB UART log to display operating voltage, OVLO, UVLO and current limit condition. This firmware provides the functions to set the operating voltage and current limiting conditions in order to provide the threshold of the fault conditions.
> When one of the fault conditions is met, the microcontroller is notified via INT pin which is checked by the app to initiate a shutdown mode. All data logs write on USB UART changes every 2000 milliseconds.

```c
void application_task ( void ) 
{
    if ( EFUSE2_FAULT == efuse2_get_fault( &efuse2 ) ) 
    {
        efuse2_operating_mode( &efuse2, EFUSE2_AD5175_SHUTDOWN_MODE );
        Delay_ms ( 1000 );

        log_printf( &logger, "        Shutdown Mode        \r\n" );
        log_printf( &logger, "  Turn OFF the Power Supply  \r\n" );
        log_printf( &logger, "   and restart the system    \r\n" );
        log_printf( &logger, "-----------------------------\r\n" );
        
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, " Oper. Voltage : %.3f V \r\n", op_voltage );
        log_printf( &logger, " Undervoltage  : %.3f V \r\n", min_voltage );
        log_printf( &logger, " Overvoltage   : %.3f V \r\n", max_voltage );
        log_printf( &logger, " Current Limit : %.3f A \r\n", op_current );
        log_printf( &logger, "-----------------------------\r\n" );
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

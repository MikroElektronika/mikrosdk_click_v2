
---
# Temp Alarm Click

> [Temp Alarm Click](https://www.mikroe.com/?pid_product=MIKROE-5872) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5872&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Temp Alarm Click board by reading and displaying
  the temperature measurements and monitoring it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempAlarm

### Example Key Functions

- `tempalarm_cfg_setup` Config Object Initialization function.
```c
void tempalarm_cfg_setup ( tempalarm_cfg_t *cfg );
```

- `tempalarm_init` Initialization function.
```c
err_t tempalarm_init ( tempalarm_t *ctx, tempalarm_cfg_t *cfg );
```

- `tempalarm_default_cfg` Click Default Configuration function.
```c
err_t tempalarm_default_cfg ( tempalarm_t *ctx );
```

- `tempalarm_write_reg` Temp Alarm register writing function.
```c
err_t tempalarm_write_reg ( tempalarm_t *ctx, uint8_t reg, uint8_t data_in );
```

- `tempalarm_read_remote_temperature` Temp Alarm remote sensor read temperature function.
```c
err_t tempalarm_read_remote_temperature ( tempalarm_t *ctx, float *temperature );
```

- `tempalarm_set_alarm_high_limit` Temp Alarm remote sensor set limit high temperature function.
```c
err_t tempalarm_set_alarm_high_limit ( tempalarm_t *ctx, float max_temperature );
```

### Application Init

> Initializes the driver and sets the Local sensor critical temperature at 30 degC with hysteresis of 1 degC,
  and Remote sensor alarm temperature at 30 degC.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempalarm_cfg_t tempalarm_cfg;  /**< Click config object. */

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
    tempalarm_cfg_setup( &tempalarm_cfg );
    TEMPALARM_MAP_MIKROBUS( tempalarm_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == tempalarm_init( &tempalarm, &tempalarm_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPALARM_ERROR == tempalarm_default_cfg ( &tempalarm ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
  approximately once per second. Monitoring alarm and critical state.

```c
void application_task ( void ) 
{
    uint8_t flag_data = 0; 
    int8_t local_temp = 0;
    float remote_temp = 0;
    tempalarm_get_alarms( &tempalarm, &flag_data );
    if ( TEMPALARM_ADC_BUSY_MASK != ( TEMPALARM_ADC_BUSY_MASK & flag_data ) )
    {
        tempalarm_read_temperature( &tempalarm, &local_temp );
        tempalarm_read_remote_temp( &tempalarm, &remote_temp );
        log_printf( &logger, " Local temperature : %d degC \r\n" , ( int16_t ) local_temp );
        log_printf( &logger, " Remote temperature : %.3f degC \r\n" , remote_temp );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    if ( TEMPALARM_PIN_STATE_LOW == tempalarm_get_alr_pin( &tempalarm ) )
    {
        log_printf( &logger, " Alarm is on, remote temperature  \r\n" );
        log_printf( &logger, "      is higher then 30 degC      \r\n" );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    if ( TEMPALARM_PIN_STATE_LOW == tempalarm_get_tcr_pin( &tempalarm ) )
    {
        log_printf( &logger, " Alarm is on, local temperature  \r\n" );
        log_printf( &logger, "      is higher then 30 degC      \r\n" );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
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


---
# BATT-MON 2 Click

> [BATT-MON 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5019) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5019&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of BATT-MON 2 Click board by monitoring
the measurements of battery voltage, current, capacity, percentage, time-to-empty or time-to-full,
as well as the chip internal temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMON2

### Example Key Functions

- `battmon2_cfg_setup` Config Object Initialization function.
```c
void battmon2_cfg_setup ( battmon2_cfg_t *cfg );
```

- `battmon2_init` Initialization function.
```c
err_t battmon2_init ( battmon2_t *ctx, battmon2_cfg_t *cfg );
```

- `battmon2_get_battery_voltage` This function reads the battery voltage in mV.
```c
err_t battmon2_get_battery_voltage ( battmon2_t *ctx, float *voltage );
```

- `battmon2_get_battery_current` This function reads the battery current in mA.
```c
err_t battmon2_get_battery_current ( battmon2_t *ctx, float *current );
```

- `battmon2_get_battery_percentage` This function reads the battery remaining SOC percentage.
```c
err_t battmon2_get_battery_percentage ( battmon2_t *ctx, float *percentage );
```

### Application Init

> Initializes the driver and checks the communication by reading and verifying the device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon2_cfg_t battmon2_cfg;  /**< Click config object. */

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
    battmon2_cfg_setup( &battmon2_cfg );
    BATTMON2_MAP_MIKROBUS( battmon2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon2_init( &battmon2, &battmon2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON2_ERROR == battmon2_check_communication ( &battmon2 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays on the USB UART the measurements of battery voltage, current, capacity, percentage, 
time-to-empty or time-to-full, as well as the chip internal temperature approximately once per second.

```c
void application_task ( void )
{
    float voltage, capacity, percentage, current, die_temp;
    if ( BATTMON2_OK == battmon2_get_battery_voltage ( &battmon2, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %.1f mV \r\n", voltage );
    }
    if ( BATTMON2_OK == battmon2_get_battery_current ( &battmon2, &current ) )
    {
        log_printf ( &logger, " Current: %.1f mA \r\n", current );
    }
    if ( BATTMON2_OK == battmon2_get_battery_capacity ( &battmon2, &capacity ) )
    {
        log_printf ( &logger, " Capacity: %.1f mAh \r\n", capacity );
    }
    if ( BATTMON2_OK == battmon2_get_battery_percentage ( &battmon2, &percentage ) )
    {
        log_printf ( &logger, " Percentage: %.1f %% \r\n", percentage );
    }
    if ( current > 0 )
    {
        uint32_t time_to_full;
        if ( BATTMON2_OK == battmon2_get_battery_ttf ( &battmon2, &time_to_full ) )
        {
            log_printf ( &logger, " Time to full: %uh %umin %usec \r\n", ( uint16_t ) ( time_to_full / 3600 ), 
                                                                         ( uint16_t ) ( time_to_full % 3600 ) / 60,
                                                                         ( uint16_t ) ( time_to_full % 60 ) );
        }
    }
    else if ( current < 0 )
    {
        uint32_t time_to_empty;
        if ( BATTMON2_OK == battmon2_get_battery_tte ( &battmon2, &time_to_empty ) )
        {
            log_printf ( &logger, " Time to empty: %uh %umin %usec \r\n", ( uint16_t ) ( time_to_empty / 3600 ), 
                                                                          ( uint16_t ) ( time_to_empty % 3600 ) / 60,
                                                                          ( uint16_t ) ( time_to_empty % 60 ) );
        }
    }
    if ( BATTMON2_OK == battmon2_get_die_temperature ( &battmon2, &die_temp ) )
    {
        log_printf ( &logger, " Internal temperature: %.2f C \r\n\n", die_temp );
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

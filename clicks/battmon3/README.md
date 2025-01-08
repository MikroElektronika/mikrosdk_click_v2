
---
# BATT-MON 3 Click

> [BATT-MON 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5098) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5098&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of BATT-MON 3 Click by measuring the battery
voltage, current and used capacity, as well as the chip internal temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMON3

### Example Key Functions

- `battmon3_cfg_setup` Config Object Initialization function.
```c
void battmon3_cfg_setup ( battmon3_cfg_t *cfg );
```

- `battmon3_init` Initialization function.
```c
err_t battmon3_init ( battmon3_t *ctx, battmon3_cfg_t *cfg );
```

- `battmon3_default_cfg` Click Default Configuration function.
```c
err_t battmon3_default_cfg ( battmon3_t *ctx );
```

- `battmon3_read_voltage` This function reads the battery voltage in millivolts.
```c
err_t battmon3_read_voltage ( battmon3_t *ctx, uint16_t *voltage );
```

- `battmon3_read_current` This function reads the battery current load from BATT+ to GND in milliampers.
```c
err_t battmon3_read_current ( battmon3_t *ctx, int16_t *current );
```

- `battmon3_read_used_capacity` This function reads the used battery capacity in mAh.
```c
err_t battmon3_read_used_capacity ( battmon3_t *ctx, float *used_capacity );
```

### Application Init

> Initialized the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon3_cfg_t battmon3_cfg;  /**< Click config object. */

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
    battmon3_cfg_setup( &battmon3_cfg );
    BATTMON3_MAP_MIKROBUS( battmon3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon3_init( &battmon3, &battmon3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON3_ERROR == battmon3_default_cfg ( &battmon3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the battery voltage (mV), current (mA), used capacity (mAh) and the chip internal 
temperature (Celsius) and displays the results on the USB UART approximately once per second. 

```c
void application_task ( void )
{
    uint16_t voltage;
    int16_t current;
    float temperature, used_capacity;
    if ( BATTMON3_OK == battmon3_read_voltage ( &battmon3, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %u mV\r\n", voltage );
    }
    
    if ( BATTMON3_OK == battmon3_read_current ( &battmon3, &current ) )
    {
        log_printf ( &logger, " Current: %d mA\r\n", current );
    }
    
    if ( BATTMON3_OK == battmon3_read_temperature ( &battmon3, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.3f C\r\n", temperature );
    }
    
    if ( BATTMON3_OK == battmon3_read_used_capacity ( &battmon3, &used_capacity ) )
    {
        log_printf ( &logger, " Used Capacity: %.3f mAh\r\n\n", used_capacity );
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

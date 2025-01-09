
---
# BATT-MON 4 Click

> [BATT-MON 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5092) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5092&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of BATT-MON 4 Click board by reading the battery voltage and the chip internal temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMON4

### Example Key Functions

- `battmon4_cfg_setup` Config Object Initialization function.
```c
void battmon4_cfg_setup ( battmon4_cfg_t *cfg );
```

- `battmon4_init` Initialization function.
```c
err_t battmon4_init ( battmon4_t *ctx, battmon4_cfg_t *cfg );
```

- `battmon4_get_die_temperature` This function reads the chip DIE temperature in Celsius.
```c
err_t battmon4_get_die_temperature ( battmon4_t *ctx, float *temperature );
```

- `battmon4_get_batt_in_voltage` This function reads the voltage from BATT IN when Ipeak is ON and OFF.
```c
err_t battmon4_get_batt_in_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off );
```

- `battmon4_get_batt_out_voltage` This function reads the voltage from BATT OUT when Ipeak is ON and OFF.
```c
err_t battmon4_get_batt_out_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon4_cfg_t battmon4_cfg;  /**< Click config object. */

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
    battmon4_cfg_setup( &battmon4_cfg );
    BATTMON4_MAP_MIKROBUS( battmon4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon4_init( &battmon4, &battmon4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the chip DIE temperature and voltage from BATT IN and BATT OUT and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float die_temperature, batt_in_v_ipeak_on, batt_in_v_ipeak_off, batt_out_v_ipeak_on, batt_out_v_ipeak_off;

    if ( BATTMON4_OK == battmon4_get_die_temperature ( &battmon4, &die_temperature ) )
    {
        log_printf ( &logger, " Die Temperature: %.2f C \r\n\n", die_temperature );
    }
    
    if ( BATTMON4_OK == battmon4_get_batt_in_voltage ( &battmon4, &batt_in_v_ipeak_on, &batt_in_v_ipeak_off ) )
    {
        log_printf ( &logger, " BATT IN \r\n Ipeak ON: %.1f mV \r\n Ipeak OFF: %.1f mV \r\n\n", 
                     batt_in_v_ipeak_on, batt_in_v_ipeak_off );
    }
    
    if ( BATTMON4_OK == battmon4_get_batt_out_voltage ( &battmon4, &batt_out_v_ipeak_on, &batt_out_v_ipeak_off ) )
    {
        log_printf ( &logger, " BATT OUT \r\n Ipeak ON: %.1f mV \r\n Ipeak OFF: %.1f mV \r\n\n", 
                     batt_out_v_ipeak_on, batt_out_v_ipeak_off );
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

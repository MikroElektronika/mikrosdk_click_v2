
---
# HW Monitor 3 Click

> [HW Monitor 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6346) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6346&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of HW Monitor 3 Click board by reading and displaying the voltage level from 6 analog input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HWMonitor3

### Example Key Functions

- `hwmonitor3_cfg_setup` Config Object Initialization function.
```c
void hwmonitor3_cfg_setup ( hwmonitor3_cfg_t *cfg );
```

- `hwmonitor3_init` Initialization function.
```c
err_t hwmonitor3_init ( hwmonitor3_t *ctx, hwmonitor3_cfg_t *cfg );
```

- `hwmonitor3_default_cfg` Click Default Configuration function.
```c
err_t hwmonitor3_default_cfg ( hwmonitor3_t *ctx );
```

- `hwmonitor3_enable_channel` This function enables the selected monitoring channels.
```c
err_t hwmonitor3_enable_channel ( hwmonitor3_t *ctx, uint8_t ch_mask );
```

- `hwmonitor3_set_scaling` This function sets the scaling level for the selected monitoring channels.
```c
err_t hwmonitor3_set_scaling ( hwmonitor3_t *ctx, uint8_t scaling, uint8_t ch_mask );
```

- `hwmonitor3_read_voltage` This function reads the voltage level from all 6 monitoring analog input channels.
```c
err_t hwmonitor3_read_voltage ( hwmonitor3_t *ctx, hwmonitor3_ch_mon_t *ch_mon );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor3_cfg_t hwmonitor3_cfg;  /**< Click config object. */

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
    hwmonitor3_cfg_setup( &hwmonitor3_cfg );
    HWMONITOR3_MAP_MIKROBUS( hwmonitor3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor3_init( &hwmonitor3, &hwmonitor3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR3_ERROR == hwmonitor3_default_cfg ( &hwmonitor3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage level from all 6 analog input channels and displays the results on the USB UART once per second approximately.

```c
void application_task ( void )
{
    hwmonitor3_ch_mon_t ch_mon;
    if ( HWMONITOR3_OK == hwmonitor3_read_voltage ( &hwmonitor3, &ch_mon ) )
    {
        log_printf ( &logger, " CH1: %.3f V\r\n", ch_mon.ch1_v );
        log_printf ( &logger, " CH2: %.3f V\r\n", ch_mon.ch2_v );
        log_printf ( &logger, " CH3: %.3f V\r\n", ch_mon.ch3_v );
        log_printf ( &logger, " CH4: %.3f V\r\n", ch_mon.ch4_v );
        log_printf ( &logger, " CH5: %.3f V\r\n", ch_mon.ch5_v );
        log_printf ( &logger, " CH6: %.3f V\r\n\n", ch_mon.ch6_v );
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

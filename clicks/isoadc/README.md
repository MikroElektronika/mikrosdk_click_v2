
---
# ISO ADC Click

> [ISO ADC Click](https://www.mikroe.com/?pid_product=MIKROE-4088) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4088&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ISO ADC Click board by reading the shunt voltage, current, and power.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC

### Example Key Functions

- `isoadc_cfg_setup` Config Object Initialization function.
```c
void isoadc_cfg_setup ( isoadc_cfg_t *cfg );
```

- `isoadc_init` Initialization function.
```c
err_t isoadc_init ( isoadc_t *ctx, isoadc_cfg_t *cfg );
```

- `isoadc_read_voltage` This function reads a raw ADC in ISOADC_ADC_NUM_AVERAGES number of samples and converts it to a shunt voltage in millivolts.
```c
err_t isoadc_read_voltage ( isoadc_t *ctx, float *voltage );
```

- `isoadc_get_current` This function converts a shunt voltage input to a load current in milliampers.
```c
float isoadc_get_current ( float voltage );
```

- `isoadc_get_power` This function converts a shunt voltage input to electrical power in watts.
```c
float isoadc_get_power ( isoadc_t *ctx, float voltage );
```

### Application Init

> Initializes the driver and sets the external voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc_cfg_t isoadc_cfg;  /**< Click config object. */

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
    isoadc_cfg_setup( &isoadc_cfg );
    ISOADC_MAP_MIKROBUS( isoadc_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc_init( &isoadc, &isoadc_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    isoadc_set_vext ( &isoadc, ISOADC_VEXT_5V );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads a 10 samples of a shunt voltage measurement, then averages and calculates the current and power from it. All data is displayed on the USB UART.

```c
void application_task ( void )
{
    float voltage = 0;
    float avg_voltage = 0;
    uint16_t avg_cnt = 0; 

    log_printf( &logger, " --- MEASUREMENT IN PROGRESS ---\r\n" );
    log_info( &logger, "Keep the load and power supply stable during the measurement process\r\n" );

    while ( avg_cnt < ISOADC_VOLTAGE_NUM_AVERAGES )
    {
        if ( ISOADC_OK == isoadc_read_voltage ( &isoadc, &voltage ) )
        {
            avg_voltage += voltage;
            avg_cnt++;
        }
    }
    voltage = avg_voltage / ISOADC_VOLTAGE_NUM_AVERAGES;
    log_printf( &logger, " Shunt Voltage: %.1f mV\r\n", voltage );
    log_printf( &logger, " Current: %.3f mA\r\n", isoadc_get_current ( voltage ) );
    log_printf( &logger, " Power: %.3f W\r\n", isoadc_get_power ( &isoadc, voltage ) );
    log_printf( &logger, "-------------------------\r\n\n" );
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

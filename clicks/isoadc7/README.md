
---
# ISO ADC 7 Click

> [ISO ADC 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6210) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6210&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ISO ADC 7 Click board by reading and displaying the voltage levels from 3 isolated analog input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC7

### Example Key Functions

- `isoadc7_cfg_setup` Config Object Initialization function.
```c
void isoadc7_cfg_setup ( isoadc7_cfg_t *cfg );
```

- `isoadc7_init` Initialization function.
```c
err_t isoadc7_init ( isoadc7_t *ctx, isoadc7_cfg_t *cfg );
```

- `isoadc7_default_cfg` Click Default Configuration function.
```c
err_t isoadc7_default_cfg ( isoadc7_t *ctx );
```

- `isoadc7_read_voltage` This function reads the voltage measurements of all three channels.
```c
err_t isoadc7_read_voltage ( isoadc7_t *ctx, float *ch0, float *ch1, float *ch2 );
```

- `isoadc7_read_data` This function reads the status register and raw data of all three channels.
```c
err_t isoadc7_read_data ( isoadc7_t *ctx, isoadc7_data_t *data_out );
```

- `isoadc7_set_gain` This function sets the gain level for all channels.
```c
err_t isoadc7_set_gain ( isoadc7_t *ctx, uint8_t gain_ch0, uint8_t gain_ch1, uint8_t gain_ch2 );
```

### Application Init

> Initializes the driver and performs the Click default configuration. The full-scale voltage input range is set to +-1.2V for all channels.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc7_cfg_t isoadc7_cfg;  /**< Click config object. */

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
    isoadc7_cfg_setup( &isoadc7_cfg );
    ISOADC7_MAP_MIKROBUS( isoadc7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc7_init( &isoadc7, &isoadc7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISOADC7_ERROR == isoadc7_default_cfg ( &isoadc7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage levels from all 3 isolated analog input channels and displays the results on the USB UART once per second approximately.

```c
void application_task ( void )
{
    float ch0 = 0;
    float ch1 = 0;
    float ch2 = 0;
    if ( ISOADC7_OK == isoadc7_read_voltage ( &isoadc7, &ch0, &ch1, &ch2 ) )
    {
        log_printf ( &logger, " CH0: %.1f mV\r\n", ch0 );
        log_printf ( &logger, " CH1: %.1f mV\r\n", ch1 );
        log_printf ( &logger, " CH2: %.1f mV\r\n\n", ch2 );
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

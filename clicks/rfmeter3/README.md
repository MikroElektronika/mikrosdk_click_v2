
---
# RF Meter 3 Click

> [RF Meter 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4906) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4906&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of RF Meter 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RFMeter3

### Example Key Functions

- `rfmeter3_cfg_setup` Config Object Initialization function.
```c
void rfmeter3_cfg_setup ( rfmeter3_cfg_t *cfg );
```

- `rfmeter3_init` Initialization function.
```c
err_t rfmeter3_init ( rfmeter3_t *ctx, rfmeter3_cfg_t *cfg );
```

- `rfmeter3_enable_device` This function enables device by setting EN pin to HIGH logic level.
```c
void rfmeter3_enable_device ( rfmeter3_t *ctx );
```

- `rfmeter3_disable_device` This function disables device by setting EN pin to LOW logic level.
```c
void rfmeter3_disable_device ( rfmeter3_t *ctx );
```

- `rfmeter3_get_rf_input_power` This function reads the voltage from AN pin and converts it to RF input power in dBm.
```c
err_t rfmeter3_get_rf_input_power ( rfmeter3_t *ctx, float *data_out );
```

### Application Init

> Initializes the driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    rfmeter3_cfg_t rfmeter3_cfg;  /**< Click config object. */

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
    rfmeter3_cfg_setup( &rfmeter3_cfg );
    RFMETER3_MAP_MIKROBUS( rfmeter3_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == rfmeter3_init( &rfmeter3, &rfmeter3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    rfmeter3_enable_device ( &rfmeter3 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures the RF input signal power in dBm and displays the results on the USB UART every 100ms.

```c
void application_task ( void )
{
    float rfmeter3_rf_input_power = 0;

    if ( RFMETER3_ERROR != rfmeter3_get_rf_input_power ( &rfmeter3, &rfmeter3_rf_input_power ) ) 
    {
        log_printf( &logger, " RF Input Power: %.2f dBm\r\n", rfmeter3_rf_input_power );
        Delay_ms ( 100 );
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

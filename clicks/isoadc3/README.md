
---
# ISO ADC 3 Click

> [ISO ADC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4383) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4383&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows the capabilities of the ISO ADC 3 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC3

### Example Key Functions

- `isoadc3_cfg_setup` Config Object Initialization function.
```c
void isoadc3_cfg_setup ( isoadc3_cfg_t *cfg );
```

- `isoadc3_init` Initialization function.
```c
err_t isoadc3_init ( isoadc3_t *ctx, isoadc3_cfg_t *cfg );
```

- `isoadc3_read_adc` Read ADC function.
```c
uint16_t isoadc3_read_adc ( isoadc3_t *ctx );
```

- `isoadc3_get_adc_voltage` Read ADC voltage function.
```c
uint16_t isoadc3_get_adc_voltage ( isoadc3_t *ctx, uint16_t v_ref );
```

- `isoadc3_read_voltage` Read voltage function.
```c
uint16_t isoadc3_read_voltage ( isoadc3_t *ctx, uint16_t v_ref );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc3_cfg_t isoadc3_cfg;  /**< Click config object. */

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
    isoadc3_cfg_setup( &isoadc3_cfg );
    ISOADC3_MAP_MIKROBUS( isoadc3_cfg, MIKROBUS_1 );
    err_t init_flag = isoadc3_init( &isoadc3, &isoadc3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures ADC voltage level and prints it via USB UART terminal.

```c
void application_task ( void ) 
{
    voltage = isoadc3_read_voltage( &isoadc3, ISOADC3_VREF_3V3 );
    log_printf( &logger, " ADC voltage Level: %d mV \r\n", voltage );
    log_printf( &logger, "------------------------\r\n" );
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

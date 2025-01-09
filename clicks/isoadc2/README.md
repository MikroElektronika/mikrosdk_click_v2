
---
# ISO ADC 2 Click

> [ISO ADC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4166) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4166&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the ISO ADC 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IsoAdc2

### Example Key Functions

- `isoadc2_cfg_setup` Config Object Initialization function.
```c
void isoadc2_cfg_setup ( isoadc2_cfg_t *cfg );
```

- `isoadc2_init` Initialization function.
```c
err_t isoadc2_init ( isoadc2_t *ctx, isoadc2_cfg_t *cfg );
```

- `isoadc2_read_adc` ISO ADC 2 ADC data reading function.
```c
err_t isoadc2_read_adc ( isoadc2_t *ctx, uint16_t *adc_val );
```

- `isoadc2_get_mv` ISO ADC 2 voltage data reading function.
```c
err_t isoadc2_get_mv ( isoadc2_t *ctx, uint16_t *voltage );
```

### Application Init

> Initialization of SPI module and additional GPIO pins.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc2_cfg_t isoadc2_cfg;  /**< Click config object. */

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

    isoadc2_cfg_setup( &isoadc2_cfg );
    ISOADC2_MAP_MIKROBUS( isoadc2_cfg, MIKROBUS_1 );
    err_t init_flag  = isoadc2_init( &isoadc2, &isoadc2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Every second reads ADC data and voltage in mV and logs result.

```c
void application_task ( void ) 
{
    uint16_t rx_data;
    uint16_t mv_data;
    
    isoadc2_read_adc( &isoadc2, &rx_data );
    Delay_ms ( 100 );
    isoadc2_get_mv( &isoadc2, &mv_data );
    
    log_printf( &logger, " ADC: %d \r\n", rx_data );
    log_printf( &logger, " VIN: %d mV\r\n", mv_data );
    log_printf( &logger, "---------------\r\n" );

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

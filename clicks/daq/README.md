
---
# DAQ Click

> [DAQ Click](https://www.mikroe.com/?pid_product=MIKROE-4495) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4495&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases ability of the device to read ADC 
data and calculate voltage for set configuration.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAQ

### Example Key Functions

- `daq_cfg_setup` Config Object Initialization function.
```c
void daq_cfg_setup ( daq_cfg_t *cfg );
```

- `daq_init` Initialization function.
```c
err_t daq_init ( daq_t *ctx, daq_cfg_t *cfg );
```

- `daq_default_cfg` Click Default Configuration function.
```c
err_t daq_default_cfg ( daq_t *ctx );
```

- `daq_set_gain` Set gain range.
```c
err_t daq_set_gain ( daq_t *ctx, daq_gain gain );
```

- `daq_read_data` Reading adc data.
```c
err_t daq_read_data ( daq_t *ctx, int32_t *adc_data );
```

- `daq_calculate_voltage` Convert data from raw ADC to voltage.
```c
void daq_calculate_voltage ( daq_t *ctx, int32_t adc_data, float *voltage );
```

### Application Init

> Initialization of communication modules (SPI, UART) and
additional pins for controling device. Resets device and
then configures default configuration and sets read range
by setting gain to +-12V. In the end reads vendor and 
device ID to confirm communication.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    daq_cfg_t daq_cfg;  /**< Click config object. */

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
    daq_cfg_setup( &daq_cfg );
    DAQ_MAP_MIKROBUS( daq_cfg, MIKROBUS_1 );
    err_t init_flag  = daq_init( &daq, &daq_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    if ( daq_default_cfg ( &daq ) ) 
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t id = 0;
    daq_generic_read( &daq, DAQ_REG_VENDOR_H, &id, 1 );
    log_printf( &logger, " > Vendor: \t0x%.2X", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_VENDOR_L, &id, 1 );
    log_printf( &logger, "%.2X\r\n", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_PRODUCT_ID_H, &id, 1 );
    log_printf( &logger, " > ID: \t\t0x%.2X", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_PRODUCT_ID_L, &id, 1 );
    log_printf( &logger, "%.2X\r\n", ( uint16_t )id );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads ADC data and calculates voltage from it, every 0.3 seconds.

```c
void application_task ( void ) 
{
    int32_t adc_data = 0;
    float voltage = 0.0;
    daq_read_data( &daq, &adc_data );
    daq_calculate_voltage( &daq, adc_data, &voltage );
    
    log_printf( &logger, " > Data: %ld\r\n", adc_data );
    log_printf( &logger, " > Voltage: %.2f\r\n", voltage );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms ( 300 );  
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

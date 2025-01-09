
---
# ISO ADC 5 Click

> [ISO ADC 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4758) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4758&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ISO ADC 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC5

### Example Key Functions

- `isoadc5_cfg_setup` Config Object Initialization function.
```c
void isoadc5_cfg_setup ( isoadc5_cfg_t *cfg );
```

- `isoadc5_init` Initialization function.
```c
err_t isoadc5_init ( isoadc5_t *ctx, isoadc5_cfg_t *cfg );
```

- `isoadc5_write_register` This function writes two bytes of data to the selected register by using the SPI serial interface.
```c
err_t isoadc5_write_register ( isoadc5_t *ctx, uint8_t reg, uint16_t data_in );
```

- `isoadc5_read_register` This function reads two bytes of data from the selected register by using the SPI serial interface.
```c
err_t isoadc5_read_register ( isoadc5_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `isoadc5_read_voltage` This function reads the raw adc data from a desired input channel and converts it to voltage.
```c
err_t isoadc5_read_voltage( isoadc5_t *ctx, uint8_t filt, uint8_t ch, float *volt );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    isoadc5_cfg_t isoadc5_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    isoadc5_cfg_setup( &isoadc5_cfg );
    ISOADC5_MAP_MIKROBUS( isoadc5_cfg, MIKROBUS_1 );
    err_t init_flag  = isoadc5_init( &isoadc5, &isoadc5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage from all input channels and displays the values of each channel on the USB UART approximately every second.

```c
void application_task ( void )
{
    float v_ain1 = 0, v_ain2 = 0, v_ain3 = 0, v_ain4 = 0;
    err_t error_flag = isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_1, &v_ain1 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_2, &v_ain2 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_3, &v_ain3 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_4, &v_ain4 );
    
    if ( ISOADC5_OK == error_flag )
    {
        log_printf( &logger, " AIN 1 voltage: %.3f V\r\n", v_ain1 );
        log_printf( &logger, " AIN 2 voltage: %.3f V\r\n", v_ain2 );
        log_printf( &logger, " AIN 3 voltage: %.3f V\r\n", v_ain3 );
        log_printf( &logger, " AIN 4 voltage: %.3f V\r\n\r\n", v_ain4 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The voltage input range is from 0 to 48V.

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


---
# ADC 12 Click

> [ADC 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4376) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4376&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of ADC 12 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC12

### Example Key Functions

- `adc12_cfg_setup` Config Object Initialization function.
```c
void adc12_cfg_setup ( adc12_cfg_t *cfg );
```

- `adc12_init` Initialization function.
```c
err_t adc12_init ( adc12_t *ctx, adc12_cfg_t *cfg );
```

- `adc12_read_voltage` This function reads the voltage in milivolts from the desired channel.
```c
err_t adc12_read_voltage ( adc12_t *ctx, uint8_t ch, uint16_t vref, float *data_out );
```

- `adc12_read_raw_data` This function reads raw 12-bit ADC data from the desired channel. 
```c
err_t adc12_read_raw_data ( adc12_t *ctx, uint8_t ch, uint16_t *data_out );
```

- `adc12_set_sd_mode` This function sets the input mode.
```c
void adc12_set_sd_mode ( adc12_t *ctx, uint8_t sd_mode );
```

### Application Init

> Initializes the driver and sets the input and power-down modes.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc12_cfg_t adc12_cfg;  /**< Click config object. */

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

    adc12_cfg_setup( &adc12_cfg );
    ADC12_MAP_MIKROBUS( adc12_cfg, MIKROBUS_1 );
    err_t init_flag = adc12_init( &adc12, &adc12_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    adc12_set_sd_mode ( &adc12, ADC12_CMD_SD_SINGLE_END );
    adc12_set_pd_mode( &adc12, ADC12_CMD_PD_IRON_ADON );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the RAW ADC data and converts it to voltage in milivolts and displays
> both values on the USB UART every second.

```c
void application_task ( void )
{
    uint16_t raw_adc;
    float voltage;

    adc12_read_raw_data ( &adc12, ADC12_SINGLE_END_CH0, &raw_adc );
    adc12_read_voltage ( &adc12, ADC12_SINGLE_END_CH0, ADC12_INTERNAL_VREF, &voltage );
    
    log_printf( &logger, " RAW ADC: %u \r\n", raw_adc );
    log_printf( &logger, " Voltage from Channel 0: %.2f mV \r\n", voltage );
    log_printf( &logger, " ---------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> With internal reference voltage set the Click measures up to 2500 mV.

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

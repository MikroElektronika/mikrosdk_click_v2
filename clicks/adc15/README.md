
---
# ADC 15 Click

> [ADC 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4890) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4890&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases ability of the Click board to 
read adc data from 2 different channels. It's also configuratable
to read data in different output rate, resolutions( word/data len ),
and gain.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC15

### Example Key Functions

- `adc15_cfg_setup` Config Object Initialization function.
```c
void adc15_cfg_setup ( adc15_cfg_t *cfg );
```

- `adc15_init` Initialization function.
```c
err_t adc15_init ( adc15_t *ctx, adc15_cfg_t *cfg );
```

- `adc15_default_cfg` Click Default Configuration function.
```c
err_t adc15_default_cfg ( adc15_t *ctx );
```

- `adc15_read_voltage` Get voltage value.
```c
err_t adc15_read_voltage ( adc15_t *ctx, uint16_t *status, float *ch1_out, float *ch2_out );
```

- `adc15_set_gain` Set gain for channel.
```c
err_t adc15_set_gain ( adc15_t *ctx, adc15_channel_t channel, adc15_gain_t gain );
```

- `adc15_set_word_len` Set word len.
```c
err_t adc15_set_word_len ( adc15_t *ctx, adc15_word_t word_len );
```

### Application Init

> Initialization of communication modules (SPI, UART) and additional
pins for control of the device. Sets default configuration, that 
sets gain of 1 for both channels(+/-1.2V range) and word/data length
of 24bit. In the end reads device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc15_cfg_t adc15_cfg;  /**< Click config object. */

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
    adc15_cfg_setup( &adc15_cfg );
    ADC15_MAP_MIKROBUS( adc15_cfg, MIKROBUS_1 );
    err_t init_flag  = adc15_init( &adc15, &adc15_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Communication Init. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    } 

    if ( adc15_default_cfg ( &adc15 ) )
    {
        log_error( &logger, " Default configuration. " );
        for( ; ; );
    }
    
    uint16_t reg_val;
    adc15_reg_read( &adc15, ADC15_REG_ID, &reg_val );
    log_printf( &logger, " > ID: 0x%.4X\r\n", reg_val );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
}
```

### Application Task

> Waits for data ready signal and reads voltage value of both channels,
and logs read status and channel voltage level.

```c
void application_task ( void )
{
    while ( adc15_data_ready( &adc15 ) );
    float channel1 = 0;
    float channel2 = 0;
    uint16_t status = 0;
    if ( !adc15_read_voltage( &adc15, &status, &channel1, &channel2 ) )
    {
        log_printf( &logger, " > Status: 0x%.4X\r\n", status );
        log_printf( &logger, " > V ch1: %f\r\n", channel1 );
        log_printf( &logger, " > V ch2: %f\r\n", channel2 );    
        log_printf( &logger, "************************\r\n" );
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

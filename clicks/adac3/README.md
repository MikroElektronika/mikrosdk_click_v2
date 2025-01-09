
---
# ADAC 3 Click

> [ADAC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5198) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5198&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of ADAC 3 Click board by setting the DAC output
and reading the ADC results from 2 single-ended channels (AIN0, AIN1) and from a
differential channel (AIN2+, AIN3-).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADAC3

### Example Key Functions

- `adac3_cfg_setup` Config Object Initialization function.
```c
void adac3_cfg_setup ( adac3_cfg_t *cfg );
```

- `adac3_init` Initialization function.
```c
err_t adac3_init ( adac3_t *ctx, adac3_cfg_t *cfg );
```

- `adac3_default_cfg` Click Default Configuration function.
```c
err_t adac3_default_cfg ( adac3_t *ctx );
```

- `adac3_write_control` This function writes a control byte by using I2C serial interface.
```c
err_t adac3_write_control ( adac3_t *ctx, uint8_t control );
```

- `adac3_write_dac` This function writes a DAC byte by using I2C serial interface.
```c
err_t adac3_write_dac ( adac3_t *ctx, uint8_t dac );
```

- `adac3_read_adc` This function reads the AD conversion byte by using I2C serial interface.
```c
err_t adac3_read_adc ( adac3_t *ctx, uint8_t *adc );
```

### Application Init

> Initializes the driver and performs the Click default configuration which enables
DAC output, sets the analog input mode to single-ended (AIN0, AIN1) and
differential (AIN2+, AIN3-), and enables the auto increment mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adac3_cfg_t adac3_cfg;  /**< Click config object. */

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
    adac3_cfg_setup( &adac3_cfg );
    ADAC3_MAP_MIKROBUS( adac3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adac3_init( &adac3, &adac3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADAC3_ERROR == adac3_default_cfg ( &adac3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the DAC output increasing the value by 1 after each iteration, and reads the
ADC results from 2 single-ended and 1 differential channels, and displays the results
on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    static uint8_t dac = 0;
    uint8_t ain0, ain1, ain2_ain3_diff;
    if ( ADAC3_OK == adac3_write_dac ( &adac3, dac ) )
    {
        log_printf ( &logger, " DAC : %u mV\r\n", 
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * dac++ ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain0 ) )
    {
        log_printf ( &logger, " AIN0+: %u mV\r\n", 
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ain0 ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain1 ) )
    {
        log_printf ( &logger, " AIN1+: %u mV\r\n",
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ain1 ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain2_ain3_diff ) )
    {
        log_printf ( &logger, " AIN2+ - AIN3-: %d mV\r\n\n",
                     ( int16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ( int8_t ) ain2_ain3_diff ) );
    }
    Delay_ms ( 100 );
}
```

### Note

> Inputs should be connected to GND when not in use.

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

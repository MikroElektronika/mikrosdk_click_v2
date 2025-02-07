
---
# Waveform 2 Click

> [Waveform 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4346) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4346&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Waveform 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Waveform2

### Example Key Functions

- `waveform2_cfg_setup` Config Object Initialization function.
```c
void waveform2_cfg_setup ( waveform2_cfg_t *cfg );
```

- `waveform2_init` Initialization function.
```c
err_t waveform2_init ( waveform2_t *ctx, waveform2_cfg_t *cfg );
```

- `waveform2_default_cfg` Click Default Configuration function.
```c
err_t waveform2_default_cfg ( waveform2_t *ctx );
```

- `waveform2_eeprom_read_string` Waveform 2 read string function.
```c
void waveform2_eeprom_read_string ( waveform2_t *ctx, uint16_t addr, uint8_t *data_buf, uint16_t len );
```

- `waveform2_eeprom_write_string` Waveform 2 write string function.
```c
void waveform2_eeprom_write_string ( waveform2_t *ctx, uint16_t addr, uint8_t *data_buf, uint16_t len );
```

- `waveform2_sine_output` Waveform 2 set sine output function.
```c
void waveform2_sine_output ( waveform2_t *ctx );
```

### Application Init

> Initialize the communication interface, preforming hardware reset, and configure the Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waveform2_cfg_t waveform2_cfg;  /**< Click config object. */

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
    waveform2_cfg_setup( &waveform2_cfg );
    WAVEFORM2_MAP_MIKROBUS( waveform2_cfg, MIKROBUS_1 );
    err_t init_flag  = waveform2_init( &waveform2, &waveform2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    waveform2_default_cfg ( &waveform2 );

    log_printf( &logger, "---- EEPROM test ----\r\n " );
    log_printf( &logger, ">> Write [MikroE] to address 0x0123\r\n " );
    waveform2_eeprom_write_string( &waveform2, 0x0123, demo_tx_buf, 6 );
    waveform2_eeprom_read_string ( &waveform2, 0x0123, demo_rx_buf, 6 );
    log_printf( &logger, ">> Read data: %s  from address 0x0123.... \r\n ", demo_rx_buf );
    Delay_ms ( 1000 );
    waveform2_hw_reset( &waveform2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---- Waveform set freqency ----\r\n" );
    int32_t freqency;
    freqency = aprox_freq_calculation( value );
    waveform2_set_freq( &waveform2, freqency );
    waveform2_triangle_output( &waveform2 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Predefined characters are inputed from the serial port. Depending on the character sent the signal frequency, waveform or amplitude will be changed.

```c
void application_task ( void ) 
{
    char rx_data;
    uint32_t freq_data;

    if ( log_read( &logger, &rx_data, 1 ) ) {
        switch ( rx_data ) {
            case '+': {
                if ( value > 200000 ) {
                    value = 0;
                }
                value += 100000;
                freq_data = aprox_freq_calculation( value );
                waveform2_set_freq( &waveform2, freq_data );
                log_printf( &logger, ">> Increasing the frequency \r\n " );
                break;
            }

            case '-': {
                if ( value < 200000 ) {
                    value = 400000;
                }
                value -= 100000;
                freq_data = aprox_freq_calculation( value );
                waveform2_set_freq( &waveform2, freq_data );
                log_printf( &logger, ">> Decreasing the frequency \r\n " );
                break;
            }

            case 't': {
                waveform2_triangle_output( &waveform2 );
                log_printf( &logger, ">> Triangle output \r\n " );
                break;
            }

            case 's': {
                waveform2_sine_output( &waveform2 );
                log_printf( &logger,  ">> Sinusoid output \r\n " );
                break;
            }
        }
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


---
# ISM RX 3 Click

> [ISM RX 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4828) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4828&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka FIlipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases ability of Click board to configure 
and read incoming rf signal and parses data using data and clock line.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMRX3

### Example Key Functions

- `ismrx3_cfg_setup` Config Object Initialization function.
```c
void ismrx3_cfg_setup ( ismrx3_cfg_t *cfg );
```

- `ismrx3_init` Initialization function.
```c
err_t ismrx3_init ( ismrx3_t *ctx, ismrx3_cfg_t *cfg );
```

- `ismrx3_default_cfg` Click Default Configuration function.
```c
err_t ismrx3_default_cfg ( ismrx3_t *ctx );
```

- `ismrx3_reset` Reset function.
```c
void ismrx3_reset( ismrx3_t *ctx );
```

- `ismrx3_get_data` Read data output.
```c
uint8_t ismrx3_get_data( ismrx3_t *ctx );
```

- `ismrx3_get_clk` Read clock output.
```c
uint8_t ismrx3_get_clk( ismrx3_t *ctx );
```

### Application Init

> Initialization of communication modules (SPI, UART), and additional 
communication pins. Resets device, reads device ID, and sets default
configuration that sets ASK modulation and 433.92MHz with 5bps data rate.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ismrx3_cfg_t ismrx3_cfg;  /**< Click config object. */

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
    ismrx3_cfg_setup( &ismrx3_cfg );
    ISMRX3_MAP_MIKROBUS( ismrx3_cfg, MIKROBUS_1 );
    err_t init_flag  = ismrx3_init( &ismrx3, &ismrx3_cfg );
    if ( init_flag == SPI_MASTER_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    ismrx3_reset( &ismrx3 );
    
    uint8_t read_data;
    ismrx3_generic_read( &ismrx3, 0x1E, &read_data );
    log_info( &logger, " > ID: 0x%.2X", ( uint16_t )read_data );
    Delay_ms ( 500 );
    
    ismrx3.modulation = ISMRX3_MODULATION_ASK;
    ismrx3.reference_freq = ISMRX3_FREQUENCY_MHZ_433p92;
    ismrx3.data_rate = ISMRX3_DATA_RATE_KBPS_5;
    ismrx3.freq_deviation = ISMRX3_DEVIATION_KHZ_40;
    
    if ( ISMRX3_ERROR == ismrx3_default_cfg ( &ismrx3 ) )
    {
        log_error( &logger, " Configuration Error. " );
        log_info( &logger, " Please, change device configuration parameters and run program again... " );

        for ( ; ; );
    }
    
    manchester_counter = 0;
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads clock pin and gets samples of data pin state, converts it in manchester
data that stores in buffer. When it fills out manchester buffer checks if 
expected preamble data is received. If it is checks the next byte(it should be
received data length). Then parses rest of data and if it's correct shows it on log.

```c
void application_task ( void )
{    
    if ( ismrx3_get_clk( &ismrx3 ) )
    {
        sample = ismrx3_get_data( &ismrx3 );
        if ( last_sample == sample )
        {
            consecutive++; 
        }
        else
        {
            if ( consecutive < 4 )//Single sample
            {
                manchester_buf[ manchester_counter++ ] = last_sample + 48;//Convert to ascii 1/0
            }
            else if ( consecutive < 6 )//Two samples
            {
                manchester_buf[ manchester_counter++ ] = last_sample + 48;//Convert to ascii 1/0
                manchester_buf[ manchester_counter++ ] = last_sample + 48;//Convert to ascii 1/0
            }
            consecutive = 1;
            last_sample = sample;
        }
        
        while ( ismrx3_get_clk( &ismrx3 ) );
    }
    
    if ( manchester_counter >= MANCHESTER_BUF_LEN - 1 )
    {
        parse_samples(  ); 
        manchester_counter = 0;
    }
}
```

### Note

> - The expected data that is received is:
  >> _PREAMBLE_WORD_(2bytes), _DATA_LENGTH_(1byte), _DATA_(1..255bytes) 
> - By default _PREAMBLE_WORD_ is set to be 0xAAAA.

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

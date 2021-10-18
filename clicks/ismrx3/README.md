\mainpage Main Page

---
# ISM RX 3 click

ISM RX 3 Click is a compact add-on board that contains a Sub-GHz RF receiver. This board features the MAX41470, a high-performance, low-power receiver ideal for amplitude shift-keyed (ASK) and frequency shift-keyed (FSK) data from Maxim Integrated, now part of Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ismrx3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ism-rx-3-click)

---


#### Click library

- **Author**        : Luka FIlipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ISMRX3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISMRX3 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example showcases ability of click board to configure 
and read incoming rf signal and parses data using data and clock line.

**The demo application is composed of two sections :**

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
    Delay_ms( 500 );
    
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

## Note

> - The expected data that is received is:
  >> _PREAMBLE_WORD_(2bytes), _DATA_LENGTH_(1byte), _DATA_(1..255bytes) 
> - By default _PREAMBLE_WORD_ is set to be 0xAAAA.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMRX3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---

\mainpage Main Page

---
# ADC 15 click

> ADC 15 Click is a compact add-on board that contains a high-performance data converter. This board features the ADS131M02, a two-channel, simultaneously sampling, 24-bit, delta-sigma (ΔΣ), analog-to-digital converter from Texas Instruments. The ADC inputs can be independently configured via serial peripheral interface depending on the sensor input. A low noise, programmable gain amplifier (PGA) provides gains ranging from 1 to 128 to amplify low-level signals.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc15_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-15-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC15 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example showcases ability of the click board to 
read adc data from 2 different channels. It's also configuratable
to read data in different output rate, resolutions( word/data len ),
and gain.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---

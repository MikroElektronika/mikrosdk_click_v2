
---
# DAC 16 Click

> DAC 16 Click is a compact add-on board, a digital-to-analog converter (DAC) designed for precise voltage and current output applications. This board features the DAC63204-Q1, an automotive-qualified 12-bit DAC from Texas Instruments. This Click board™ features four output channels with flexible configuration options, including adjustable voltage gains and selectable current ranges from ±25μA to ±250μA. It also supports both internal and external voltage references and offers a Hi-Z power-down mode for enhanced protection. Communication with the host MCU is enabled through either a 4-wire SPI or I2C interface, with configurable I2C addresses and a general-purpose I/O pin for additional functionality.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dac-16-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the DAC 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 16 Click driver.

#### Standard key functions :

- `dac16_cfg_setup` Config Object Initialization function.
```c
void dac16_cfg_setup ( dac16_cfg_t *cfg );
```

- `dac16_init` Initialization function.
```c
err_t dac16_init ( dac16_t *ctx, dac16_cfg_t *cfg );
```

- `dac16_default_cfg` Click Default Configuration function.
```c
err_t dac16_default_cfg ( dac16_t *ctx );
```

#### Example key functions :

- `dac16_set_dac_data` This function sets the raw DAC data for the selected DAC channel.
```c
err_t dac16_set_dac_data ( dac16_t *ctx, uint8_t dac, uint16_t dac_data );
```

- `dac16_start_function_gen` This function starts the function generator for the selected DAC channel.
```c
err_t dac16_start_function_gen ( dac16_t *ctx, uint8_t dac );
```

- `dac16_stop_function_gen` This function stops the function generator for the selected DAC channel.
```c
err_t dac16_stop_function_gen ( dac16_t *ctx, uint8_t dac );
```

## Example Description

> This example demonstrates the use of DAC 16 Click board by changing the voltage level
on the OUT0 as well as the waveform signals from a function generator on the OUT1.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac16_cfg_t dac16_cfg;  /**< Click config object. */

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
    dac16_cfg_setup( &dac16_cfg );
    DAC16_MAP_MIKROBUS( dac16_cfg, MIKROBUS_1 );
    err_t init_flag = dac16_init( &dac16, &dac16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC16_ERROR == dac16_default_cfg ( &dac16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the voltage level on the OUT0 as well as the waveform signals from a function
generator on the OUT1 every 3 seconds. The state of all outputs will be displayed on the USB UART.

```c
void application_task ( void )
{
    static uint16_t dac = 0;
    static uint8_t waveform = DAC16_WAVEFORM_TRIANGULAR;
    if ( DAC16_OK == dac16_set_dac_data ( &dac16, DAC16_SEL_DAC_0, dac ) )
    {
        log_printf( &logger, "\r\n OUT0: %u -> %.2f V\r\n", 
                    dac, ( float ) dac * DAC16_VDD_3V3 / DAC16_DAC_DATA_MAX );
        dac += 100;
        if ( dac > DAC16_DAC_DATA_MAX )
        {
            dac = DAC16_DAC_DATA_MIN;
        }
    }
    err_t error_flag = dac16_stop_function_gen ( &dac16, DAC16_SEL_DAC_1 );
    error_flag |= dac16_config_function_gen ( &dac16, DAC16_SEL_DAC_1, waveform,
                                              DAC16_CODE_STEP_32_LSB, DAC16_SLEW_RATE_4_US );
    error_flag |= dac16_start_function_gen ( &dac16, DAC16_SEL_DAC_1 );
    if ( DAC16_OK == error_flag )
    {
        log_printf( &logger, " OUT1: " );
        switch ( waveform )
        {
            case DAC16_WAVEFORM_TRIANGULAR:
            {
                log_printf( &logger, "triangular wave at about 1kHz\r\n" );
                waveform = DAC16_WAVEFORM_SAWTOOTH;
                break;
            }
            case DAC16_WAVEFORM_SAWTOOTH:
            {
                log_printf( &logger, "sawtooth wave at about 2kHz\r\n" );
                waveform = DAC16_WAVEFORM_INV_SAWTOOTH;
                break;
            }
            case DAC16_WAVEFORM_INV_SAWTOOTH:
            {
                log_printf( &logger, "inverse sawtooth wave at about 2kHz\r\n" );
                waveform = DAC16_WAVEFORM_SINE;
                break;
            }
            case DAC16_WAVEFORM_SINE:
            {
                log_printf( &logger, "sine wave at about 10.5kHz\r\n" );
                waveform = DAC16_WAVEFORM_DISABLE;
                break;
            }
            case DAC16_WAVEFORM_DISABLE:
            {
                log_printf( &logger, "function generator disabled\r\n" );
                waveform = DAC16_WAVEFORM_TRIANGULAR;
                break;
            }
            default:
            {
                log_printf( &logger, "unknown state\r\n" );
                break;
            }
        }
        // OUT2 and OUT3 are set in dac16_default_cfg
        log_printf( &logger, " OUT2: sine wave at about 10.5kHz\r\n" );
        log_printf( &logger, " OUT3: sawtooth wave at about 2kHz\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

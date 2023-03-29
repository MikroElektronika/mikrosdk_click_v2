
---
# DAC 14 click

> DAC 14 Click is a compact add-on board providing highly accurate digital-to-analog conversion. This board features the DAC53202, a 10-bit dual-channel programmable voltage/current-output DAC from Texas Instruments. The DAC53202 supports high-speed I2C and SPI serial interface alongside Hi-Z Power-Down mode and Hi-Z output during Power-OFF conditions. It has a programmable comparator mode for both DAC channels and one general-purpose I/O pin configurable as multiple functions allowing this smart DAC for processor-less applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the DAC 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 14 Click driver.

#### Standard key functions :

- `dac14_cfg_setup` Config Object Initialization function.
```c
void dac14_cfg_setup ( dac14_cfg_t *cfg );
```

- `dac14_init` Initialization function.
```c
err_t dac14_init ( dac14_t *ctx, dac14_cfg_t *cfg );
```

- `dac14_default_cfg` Click Default Configuration function.
```c
err_t dac14_default_cfg ( dac14_t *ctx );
```

#### Example key functions :

- `dac14_set_dac_data` This function sets the raw DAC data for the selected DAC channel.
```c
err_t dac14_set_dac_data ( dac14_t *ctx, uint8_t dac, uint16_t dac_data );
```

- `dac14_start_function_gen` This function starts the function generator for the selected DAC channel.
```c
err_t dac14_start_function_gen ( dac14_t *ctx, uint8_t dac );
```

- `dac14_config_function_gen` This function configures the function generator for the selected DAC channel.
```c
err_t dac14_config_function_gen ( dac14_t *ctx, uint8_t dac, uint8_t waveform, uint8_t code_step, uint8_t slew_rate );
```

## Example Description

> This example demonstrates the use of DAC 14 click board by changing the voltage level
on the OUT0 as well as the waveform signals from a function generator on the OUT1.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac14_cfg_t dac14_cfg;  /**< Click config object. */

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
    dac14_cfg_setup( &dac14_cfg );
    DAC14_MAP_MIKROBUS( dac14_cfg, MIKROBUS_1 );
    err_t init_flag = dac14_init( &dac14, &dac14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC14_ERROR == dac14_default_cfg ( &dac14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the voltage level on the OUT0 as well as the waveform signals from a function
generator on the OUT1 every 3 seconds. The state of both outputs will be displayed on the USB UART.

```c
void application_task ( void )
{
    static uint16_t dac = 0;
    static uint8_t waveform = DAC14_WAVEFORM_TRIANGULAR;
    if ( DAC14_OK == dac14_set_dac_data ( &dac14, DAC14_SEL_DAC_0, dac ) )
    {
        log_printf( &logger, "\r\n OUT0: %u -> %.2f V\r\n", 
                    dac, ( float ) dac * DAC14_VDD_3V3 / DAC14_DAC_DATA_MAX );
        dac += 100;
        if ( dac > DAC14_DAC_DATA_MAX )
        {
            dac = DAC14_DAC_DATA_MIN;
        }
    }
    err_t error_flag = dac14_stop_function_gen ( &dac14, DAC14_SEL_DAC_1 );
    error_flag |= dac14_config_function_gen ( &dac14, DAC14_SEL_DAC_1, waveform,
                                              DAC14_CODE_STEP_32_LSB, DAC14_SLEW_RATE_4_US );
    error_flag |= dac14_start_function_gen ( &dac14, DAC14_SEL_DAC_1 );
    if ( DAC14_OK == error_flag )
    {
        log_printf( &logger, " OUT1: " );
        switch ( waveform )
        {
            case DAC14_WAVEFORM_TRIANGULAR:
            {
                log_printf( &logger, "triangular wave at about 4kHz\r\n" );
                waveform = DAC14_WAVEFORM_SAWTOOTH;
                break;
            }
            case DAC14_WAVEFORM_SAWTOOTH:
            {
                log_printf( &logger, "sawtooth wave at about 7.8kHz\r\n" );
                waveform = DAC14_WAVEFORM_INV_SAWTOOTH;
                break;
            }
            case DAC14_WAVEFORM_INV_SAWTOOTH:
            {
                log_printf( &logger, "inverse sawtooth wave at about 7.8kHz\r\n" );
                waveform = DAC14_WAVEFORM_SINE;
                break;
            }
            case DAC14_WAVEFORM_SINE:
            {
                log_printf( &logger, "sine wave at about 10.7kHz\r\n" );
                waveform = DAC14_WAVEFORM_DISABLE;
                break;
            }
            case DAC14_WAVEFORM_DISABLE:
            {
                log_printf( &logger, "function generator disabled\r\n" );
                waveform = DAC14_WAVEFORM_TRIANGULAR;
                break;
            }
            default:
            {
                log_printf( &logger, "unknown state\r\n" );
                break;
            }
        }
    }
    Delay_ms ( 3000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---


---
# ADC 18 click

> ADC 18 Click is a compact add-on board that contains a high-performance data converter. This board features the MAX22005, an SPI-configurable twelve-channel 24-bit analog-to-digital converter (ADC) from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc18_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 18 Click driver.

#### Standard key functions :

- `adc18_cfg_setup` Config Object Initialization function.
```c
void adc18_cfg_setup ( adc18_cfg_t *cfg );
```

- `adc18_init` Initialization function.
```c
err_t adc18_init ( adc18_t *ctx, adc18_cfg_t *cfg );
```

- `adc18_default_cfg` Click Default Configuration function.
```c
err_t adc18_default_cfg ( adc18_t *ctx );
```

#### Example key functions :

- `adc18_set_active_channel` This function sets the active channel.
```c
err_t adc18_set_active_channel ( adc18_t *ctx, uint8_t channel );
```

- `adc18_start_conversion` This function starts the conversion with the selected data rate.
```c
err_t adc18_start_conversion ( adc18_t *ctx, uint8_t data_rate );
```

- `adc18_read_voltage` This function reads RAW ADC value of previous conversion and converts it to voltage. 
```c
err_t adc18_read_voltage ( adc18_t *ctx, float *voltage );
```

## Example Description

> This example demonstrates the use of ADC 18 click board by reading the voltage from 12 analog input single-ended channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc18_cfg_t adc18_cfg;  /**< Click config object. */

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
    adc18_cfg_setup( &adc18_cfg );
    ADC18_MAP_MIKROBUS( adc18_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc18_init( &adc18, &adc18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC18_ERROR == adc18_default_cfg ( &adc18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the voltage from 12 analog input single-ended channels on the USB UART approximately once per second.

```c
void application_task ( void )
{
    static uint8_t channel = ADC18_CH_AI1_SINGLE_ENDED;
    if ( ADC18_OK == adc18_set_active_channel ( &adc18, channel ) )
    {
        adc18_start_conversion ( &adc18, ADC18_DATA_RATE_225_SPS );
        
        // Waits for the availability of the conversion result
        while ( adc18_get_rdy_pin ( &adc18 ) );
        
        adc18_stop_conversion ( &adc18 );
        
        float voltage;
        if ( ADC18_OK == adc18_read_voltage ( &adc18, &voltage ) )
        {
            log_printf ( &logger, "Channel AI%u: %.2f V\r\n", channel + 1, voltage );
            if ( ++channel > ADC18_CH_AI12_SINGLE_ENDED )
            {
                channel = ADC18_CH_AI1_SINGLE_ENDED;
                log_printf ( &logger, "\r\n" );
                Delay_ms ( 1000 );
            }
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

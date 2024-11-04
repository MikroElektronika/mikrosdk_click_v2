
---
# ADC 19 Click

> ADC 19 Click is a compact add-on board that contains a high-performance data converter. This board features the ADC122S101, a low-power two-channel CMOS 12-bit analog-to-digital converter from Texas Instruments. This SPI configurable analog-to-digital converter (ADC) is fully specified over a sample rate range of 500ksps to 1Msps, offering high reliability and performance. The converter is based on a successive-approximation register architecture with an internal track-and-hold circuit configurable to accept one or two input signals at its input channels.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 19 Click driver.

#### Standard key functions :

- `adc19_cfg_setup` Config Object Initialization function.
```c
void adc19_cfg_setup ( adc19_cfg_t *cfg );
```

- `adc19_init` Initialization function.
```c
err_t adc19_init ( adc19_t *ctx, adc19_cfg_t *cfg );
```

#### Example key functions :

- `adc19_set_vref` This function sets the voltage reference value that will be used for voltage calculation.
```c
void adc19_set_vref ( adc19_t *ctx, float vref );
```

- `adc19_set_input_channel` This function sets the selected input channel active by modifying the control register.
```c
err_t adc19_set_input_channel ( adc19_t *ctx, uint8_t input_ch );
```

- `adc19_get_voltage` This function reads the voltage from the previously selected channel by using SPI serial interface.
```c
err_t adc19_get_voltage ( adc19_t *ctx, float *voltage );
```

## Example Description

> This example demonstrates the use of ADC 19 Click board by reading the voltage from the two analog input channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and sets the ADC voltage reference.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc19_cfg_t adc19_cfg;  /**< Click config object. */

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
    adc19_cfg_setup( &adc19_cfg );
    ADC19_MAP_MIKROBUS( adc19_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc19_init( &adc19, &adc19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    adc19_set_vref ( &adc19, ADC19_VREF_3V3 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the voltage from the two analog input channels on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    float voltage;
    if ( ADC19_OK == adc19_set_input_channel ( &adc19, ADC19_INPUT_CHANNEL_1 ) )
    {
        if ( ADC19_OK == adc19_get_voltage ( &adc19, &voltage ) )
        {
            log_printf ( &logger, " IN1 : %.3f V \r\n", voltage );
        }
    }
    if ( ADC19_OK == adc19_set_input_channel ( &adc19, ADC19_INPUT_CHANNEL_2 ) )
    {
        if ( ADC19_OK == adc19_get_voltage ( &adc19, &voltage ) )
        {
            log_printf ( &logger, " IN2 : %.3f V \r\n\n", voltage );
        }
    }
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

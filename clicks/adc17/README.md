\mainpage Main Page

---
# ADC 17 Click

> ADC 17 Click is a compact add-on board that contains a high-performance data converter. This board features the MAX11645, a low-power two-channel 12-bit analog-to-digital converter from Analog Devices. The MAX11645 measures two single-ended or one differential input. The fully differential analog inputs are software configurable (I2C interface) for unipolar or bipolar, and single-ended or differential operation. The 2.048V internal reference determines its full-scale analog input range. This Click board™ offers complete, high accuracy solutions for the most demanding applications from energy-harvesting sensors to portable consumer electronics, point-of-load monitoring (voltage, current, and temperature), and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the ADC 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 17 Click driver.

#### Standard key functions :

- `adc17_cfg_setup` Config Object Initialization function.
```c
void adc17_cfg_setup ( adc17_cfg_t *cfg );
```

- `adc17_init` Initialization function.
```c
err_t adc17_init ( adc17_t *ctx, adc17_cfg_t *cfg );
```

- `adc17_default_cfg` Click Default Configuration function.
```c
err_t adc17_default_cfg ( adc17_t *ctx );
```

#### Example key functions :

- `adc17_set_channel` This function sets the selected channel active by modifying the config byte.
```c
err_t adc17_set_channel ( adc17_t *ctx, uint8_t channel );
```

- `adc17_get_voltage` This function reads the voltage from the previously selected channel by using I2C serial interface.
```c
err_t adc17_get_voltage ( adc17_t *ctx, float *voltage );
```

- `adc17_write_setup_byte` This function writes a setup byte to the ADC chip by using I2C serial interface.
```c
err_t adc17_write_setup_byte ( adc17_t *ctx, uint8_t setup_byte );
```

## Example Description

> This example demonstrates the use of ADC 17 Click board by reading the voltage from the two analog input channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the input channels to single-ended unipolar mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc17_cfg_t adc17_cfg;  /**< Click config object. */

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
    adc17_cfg_setup( &adc17_cfg );
    ADC17_MAP_MIKROBUS( adc17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc17_init( &adc17, &adc17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC17_ERROR == adc17_default_cfg ( &adc17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the voltage from the two analog input channels on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    float voltage;
    if ( ADC17_OK == adc17_set_channel ( &adc17, ADC17_CHANNEL_0 ) )
    {
        if ( ADC17_OK == adc17_get_voltage ( &adc17, &voltage ) )
        {
            log_printf ( &logger, " AIN0 voltage: %.3f V \r\n\n", voltage );
        }
    }
    if ( ADC17_OK == adc17_set_channel ( &adc17, ADC17_CHANNEL_1 ) )
    {
        if ( ADC17_OK == adc17_get_voltage ( &adc17, &voltage ) )
        {
            log_printf ( &logger, " AIN1 voltage: %.3f V \r\n\n", voltage );
        }
    }
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

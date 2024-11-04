\mainpage Main Page

---
# ADAC 2 Click

> ADAC 2 Click is a compact add-on board providing the ADC/DAC combo solution. This board features the MAX22000, a 24-bit ADC, an 18-bit DAC, and an analog front-end (AFE) from Analog Devices. It allows users to create a software-configurable (SPI interface) input/output that supports all standard industrial analog interfaces: -10V to +10V analog input or output, -20mA to +20mA analog input or output, as well as an RTD or thermocouple input for temperature measurement.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adac2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adac-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the ADAC 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADAC 2 Click driver.

#### Standard key functions :

- `adac2_cfg_setup` Config Object Initialization function.
```c
void adac2_cfg_setup ( adac2_cfg_t *cfg );
```

- `adac2_init` Initialization function.
```c
err_t adac2_init ( adac2_t *ctx, adac2_cfg_t *cfg );
```

- `adac2_default_cfg` Click Default Configuration function.
```c
err_t adac2_default_cfg ( adac2_t *ctx );
```

#### Example key functions :

- `adac2_set_active_ain_channel` This function sets the active analog input channel. 
```c
err_t adac2_set_active_ain_channel ( adac2_t *ctx, uint8_t channel );
```

- `adac2_read_voltage` This function reads RAW ADC value of previous conversion and converts it to voltage. 
```c
err_t adac2_read_voltage ( adac2_t *ctx, float fsr, float *voltage );
```

- `adac2_write_dac` This function sets the analog output by writing to the AO_DATA_WR register. 
```c
err_t adac2_write_dac ( adac2_t *ctx, int32_t dac );
```

## Example Description

> This example demonstrates the use of ADAC 2 Click board by setting the DAC output (CIO)
and reading the ADC results from a single-ended channel (AI4) and from a differential
channel (AI5+, AI6-) as well as toggling all GPIO pins.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which enables
DAC voltage output, sets the analog input mode to single-ended for AI4 and
differential (AI5+, AI6-), and enables all GPIOs as output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adac2_cfg_t adac2_cfg;  /**< Click config object. */

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
    adac2_cfg_setup( &adac2_cfg );
    ADAC2_MAP_MIKROBUS( adac2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adac2_init( &adac2, &adac2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADAC2_ERROR == adac2_default_cfg ( &adac2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ADC results from a single-ended (AI4) and a differential (AI5+, AI6-) channels,
then sets the raw DAC output increasing the value by 10000 after each iteration, and toggles
all GPIO pins. The results will be displayed on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float voltage;
    if ( ADAC2_OK == adac2_set_active_ain_channel ( &adac2, ADAC2_CH_AI4_SINGLE_ENDED ) )
    {
        adac2_start_conversion ( &adac2, ADAC2_DATA_RATE_450_SPS );
        // Waits for the availability of the conversion result
        while ( adac2_get_rdy_pin ( &adac2 ) );
        adac2_stop_conversion ( &adac2 );
        if ( ADAC2_OK == adac2_read_voltage ( &adac2, ADAC2_FULL_SCALE_RANGE_12p5V, &voltage ) )
        {
            log_printf ( &logger, " Channel AI4 single-ended: %.2f V\r\n", voltage );
        }
    }
    if ( ADAC2_OK == adac2_set_active_ain_channel ( &adac2, ADAC2_CH_AI5_AI6_DIFFERENTIAL_25V ) )
    {
        adac2_start_conversion ( &adac2, ADAC2_DATA_RATE_450_SPS );
        // Waits for the availability of the conversion result
        while ( adac2_get_rdy_pin ( &adac2 ) );
        adac2_stop_conversion ( &adac2 );
        if ( ADAC2_OK == adac2_read_voltage ( &adac2, ADAC2_FULL_SCALE_RANGE_25V, &voltage ) )
        {
            log_printf ( &logger, " Channel AI5-AI6 differential: %.2f V\r\n", voltage );
        }
    }
    
    static int32_t dac = ADAC2_DAC_MIN_VALUE;
    if ( ADAC2_OK == adac2_write_dac ( &adac2, dac ) )
    {
        log_printf ( &logger, " DAC: %ld\r\n", dac );
        dac += 5000;
        if ( dac > ADAC2_DAC_MAX_VALUE )
        {
            dac = ADAC2_DAC_MIN_VALUE;
        }
    }
    
    uint32_t gpio_data;
    if ( ADAC2_OK == adac2_read_register ( &adac2, ADAC2_REG_GEN_GPIO_CTRL, &gpio_data ) )
    {
        gpio_data ^= ADAC2_GPIO_ALL_MASK;
        if ( ADAC2_OK == adac2_write_register ( &adac2, ADAC2_REG_GEN_GPIO_CTRL, gpio_data ) )
        {
            log_printf ( &logger, " GPIO: 0x%.2X\r\n\n", ( uint16_t ) ( gpio_data & ADAC2_GPIO_ALL_MASK ) );
        }
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADAC2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

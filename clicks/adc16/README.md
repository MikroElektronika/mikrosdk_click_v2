\mainpage Main Page

---
# ADC 16 click

> ADC 16 Click is a compact add-on board that contains a high-performance data converter. This board features the ADS7142-Q1, a low-power two-channel 12-bit analog-to-digital converter from Texas Instruments. This I2C configurable 140kSPS successive approximation register (SAR) analog-to-digital converter (ADC) can autonomously monitor signals while maximizing system power, reliability, and performance. It implements event-triggered interrupts per channel using a digital window comparator with programmable high and low thresholds, hysteresis, and event counter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-16-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the ADC 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 16 Click driver.

#### Standard key functions :

- `adc16_cfg_setup` Config Object Initialization function.
```c
void adc16_cfg_setup ( adc16_cfg_t *cfg );
```

- `adc16_init` Initialization function.
```c
err_t adc16_init ( adc16_t *ctx, adc16_cfg_t *cfg );
```

- `adc16_default_cfg` Click Default Configuration function.
```c
err_t adc16_default_cfg ( adc16_t *ctx );
```

#### Example key functions :

- `adc16_single_register_write` This function writes a single data to the selected register.
```c
err_t adc16_single_register_write ( adc16_t *ctx, uint8_t reg, uint8_t data_in );
```

- `adc16_single_register_read` This function reads a single data from the selected register.
```c
err_t adc16_single_register_read ( adc16_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `adc16_get_voltage` This function reads the voltage from two analog input single-ended channels.
```c
err_t adc16_get_voltage ( adc16_t *ctx, float *ain0_voltage, float *ain1_voltage );
```

## Example Description

> This example demonstrates the use of ADC 16 click board by reading the voltage from the two analog input channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the two analog input channels to single-ended mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc16_cfg_t adc16_cfg;  /**< Click config object. */

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
    adc16_cfg_setup( &adc16_cfg );
    ADC16_MAP_MIKROBUS( adc16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc16_init( &adc16, &adc16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC16_ERROR == adc16_default_cfg ( &adc16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the voltage from the two analog input channels on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float ain0_voltage, ain1_voltage;
    if ( ADC16_OK == adc16_get_voltage ( &adc16, &ain0_voltage, &ain1_voltage ) )
    {
        log_printf ( &logger, " AIN0 voltage: %.3f V \r\n", ain0_voltage );
        log_printf ( &logger, " AIN1 voltage: %.3f V \r\n\n", ain1_voltage );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

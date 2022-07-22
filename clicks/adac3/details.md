
---
# ADAC 3 click

> ADAC 3 Click is a compact add-on board representing the ADC/DAC combo solution. This board features the PCF8591, a low-power 8-bit CMOS data acquisition device with four analog inputs, one analog output, and a serial I2C interface from NXP Semiconductors. The PCF8591 includes analog input multiplexing, an on-chip track and hold function and 8-bit analog-to-digital conversion alongside an 8-bit digital-to-analog conversion. In addition, the user is given the option to select the PCF8591 reference voltage value, choosing between 2,048 and 4,096V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adac3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adac-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the ADAC 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADAC 3 Click driver.

#### Standard key functions :

- `adac3_cfg_setup` Config Object Initialization function.
```c
void adac3_cfg_setup ( adac3_cfg_t *cfg );
```

- `adac3_init` Initialization function.
```c
err_t adac3_init ( adac3_t *ctx, adac3_cfg_t *cfg );
```

- `adac3_default_cfg` Click Default Configuration function.
```c
err_t adac3_default_cfg ( adac3_t *ctx );
```

#### Example key functions :

- `adac3_write_control` This function writes a control byte by using I2C serial interface.
```c
err_t adac3_write_control ( adac3_t *ctx, uint8_t control );
```

- `adac3_write_dac` This function writes a DAC byte by using I2C serial interface.
```c
err_t adac3_write_dac ( adac3_t *ctx, uint8_t dac );
```

- `adac3_read_adc` This function reads the AD conversion byte by using I2C serial interface.
```c
err_t adac3_read_adc ( adac3_t *ctx, uint8_t *adc );
```

## Example Description

> This example demonstrates the use of ADAC 3 click board by setting the DAC output
and reading the ADC results from 2 single-ended channels (AIN0, AIN1) and from a
differential channel (AIN2+, AIN3-).

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which enables
DAC output, sets the analog input mode to single-ended (AIN0, AIN1) and
differential (AIN2+, AIN3-), and enables the auto increment mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adac3_cfg_t adac3_cfg;  /**< Click config object. */

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
    adac3_cfg_setup( &adac3_cfg );
    ADAC3_MAP_MIKROBUS( adac3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adac3_init( &adac3, &adac3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADAC3_ERROR == adac3_default_cfg ( &adac3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the DAC output increasing the value by 1 after each iteration, and reads the
ADC results from 2 single-ended and 1 differential channels, and displays the results
on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    static uint8_t dac = 0;
    uint8_t ain0, ain1, ain2_ain3_diff;
    if ( ADAC3_OK == adac3_write_dac ( &adac3, dac ) )
    {
        log_printf ( &logger, " DAC : %u mV\r\n", 
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * dac++ ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain0 ) )
    {
        log_printf ( &logger, " AIN0+: %u mV\r\n", 
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ain0 ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain1 ) )
    {
        log_printf ( &logger, " AIN1+: %u mV\r\n",
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ain1 ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain2_ain3_diff ) )
    {
        log_printf ( &logger, " AIN2+ - AIN3-: %d mV\r\n\n",
                     ( int16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ( int8_t ) ain2_ain3_diff ) );
    }
    Delay_ms ( 100 );
}
```

## Note

> Inputs should be connected to GND when not in use.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADAC3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

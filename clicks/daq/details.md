
---
# DAQ click

> DAQ Click is a compact add-on board representing a data acquisition solution. This board features the ADAQ7768-1, a 24-bit precision data acquisition (DAQ) μModule system that encapsulates signal conditioning, conversion, and processing blocks into one SiP from Analog Devices. It supports a fully differential input signal with a maximum voltage range of ±12V with an excellent common-mode rejection ratio (CMRR). The input signal is fully buffered with a low input bias current, enabling the ADAQ7768-1 to interface to sensors with high output impedance directly.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/daq_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/daq-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the DAQ Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAQ Click driver.

#### Standard key functions :

- `daq_cfg_setup` Config Object Initialization function.
```c
void daq_cfg_setup ( daq_cfg_t *cfg );
```

- `daq_init` Initialization function.
```c
err_t daq_init ( daq_t *ctx, daq_cfg_t *cfg );
```

- `daq_default_cfg` Click Default Configuration function.
```c
err_t daq_default_cfg ( daq_t *ctx );
```

#### Example key functions :

- `daq_set_gain` Set gain range.
```c
err_t daq_set_gain ( daq_t *ctx, daq_gain gain );
```

- `daq_read_data` Reading adc data.
```c
err_t daq_read_data ( daq_t *ctx, int32_t *adc_data );
```

- `daq_calculate_voltage` Convert data from raw ADC to voltage.
```c
void daq_calculate_voltage ( daq_t *ctx, int32_t adc_data, float *voltage );
```

## Example Description

> This example showcases ability of the device to read ADC 
data and calculate voltage for set configuration.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules (SPI, UART) and
additional pins for controling device. Resets device and
then configures default configuration and sets read range
by setting gain to +-12V. In the end reads vendor and 
device ID to confirm communication.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    daq_cfg_t daq_cfg;  /**< Click config object. */

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
    daq_cfg_setup( &daq_cfg );
    DAQ_MAP_MIKROBUS( daq_cfg, MIKROBUS_1 );
    err_t init_flag  = daq_init( &daq, &daq_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    if ( daq_default_cfg ( &daq ) ) 
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t id = 0;
    daq_generic_read( &daq, DAQ_REG_VENDOR_H, &id, 1 );
    log_printf( &logger, " > Vendor: \t0x%.2X", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_VENDOR_L, &id, 1 );
    log_printf( &logger, "%.2X\r\n", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_PRODUCT_ID_H, &id, 1 );
    log_printf( &logger, " > ID: \t\t0x%.2X", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_PRODUCT_ID_L, &id, 1 );
    log_printf( &logger, "%.2X\r\n", ( uint16_t )id );
    Delay_ms( 1000 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads ADC data and calculates voltage from it, every 0.3 seconds.

```c

void application_task ( void ) 
{
    int32_t adc_data = 0;
    float voltage = 0.0;
    daq_read_data( &daq, &adc_data );
    daq_calculate_voltage( &daq, adc_data, &voltage );
    
    log_printf( &logger, " > Data: %ld\r\n", adc_data );
    log_printf( &logger, " > Voltage: %.2f\r\n", voltage );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 300 );  
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAQ

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

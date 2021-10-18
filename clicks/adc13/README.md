\mainpage Main Page

---
# ADC 13 click

ADC 13 Click is a compact add-on board that contains a high-performance data converter. This board features the ADS1262, a 32-bit, high precision, 38-kSPS, analog-to-digital converter with programmable gain amplifier and voltage reference from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc_13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC13 Click driver.

#### Standard key functions :

- `adc13_cfg_setup` Config Object Initialization function.
```c
void adc13_cfg_setup ( adc13_cfg_t *cfg );
```

- `adc13_init` Initialization function.
```c
err_t adc13_init ( adc13_t *ctx, adc13_cfg_t *cfg );
```

- `adc13_default_cfg` Click Default Configuration function.
```c
err_t adc13_default_cfg ( adc13_t *ctx );
```

#### Example key functions :

- `adc13_measure_voltage` This function starts ADC conversation, reads RAW ADC data then calculates the voltage using the input vref for calculations.
```c
err_t adc13_measure_voltage ( adc13_t *ctx, float vref, float *voltage );
```

- `adc13_measure_temperature` This function measures the internal temperature in Celsius.
```c
err_t adc13_measure_temperature ( adc13_t *ctx, float *temperature );
```

- `adc13_set_input_channel` This function sets the ADC input positive and negative channels.
```c
err_t adc13_set_input_channel ( adc13_t *ctx, uint8_t pos, uint8_t neg );
```

## Example Description

> This example demonstrates the use of ADC 13 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc13_cfg_t adc13_cfg;  /**< Click config object. */

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

    adc13_cfg_setup( &adc13_cfg );
    ADC13_MAP_MIKROBUS( adc13_cfg, MIKROBUS_1 );
    err_t init_flag  = adc13_init( &adc13, &adc13_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    adc13_default_cfg ( &adc13 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage between AIN0 and AIN1 channels, and the module internal temperature as well. 
> All values are being displayed on the USB UART where you can track their changes.

```c

void application_task ( void )
{
    float voltage = 0;
    float temperature = 0;
    
    adc13_measure_voltage ( &adc13, ADC13_VREF_INTERNAL, &voltage );
    log_printf( &logger, " Voltage: %.3f V\r\n", voltage );
    adc13_measure_temperature ( &adc13, &temperature );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    log_printf( &logger, " ---------------------------\r\n" );
    
    Delay_ms( 500 );
}

```

## Note

> An internal 2.5V reference is set by default. 
> If you want, you can change it using the adc13_set_voltage_reference function.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC13

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

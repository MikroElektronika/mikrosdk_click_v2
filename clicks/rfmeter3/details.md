
---
# RF Meter 3 click

> RF Meter 3 Click is a compact add-on board that collects information, analyzes RF power, and displays information in an easy-to-read digital format. This board features the LT5581, a low-power monolithic precision RMS power detector from Analog Devices. The RMS detector uses a proprietary technique to accurately measure the RF power in a range from 2GHz up to 2.6GHz, well-suited for signals with high crest factors. It outputs a DC voltage in linear scale proportional to an RF input signal power in dBm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rfmeter3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rf-meter-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the RFMeter3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RFMeter3 Click driver.

#### Standard key functions :

- `rfmeter3_cfg_setup` Config Object Initialization function.
```c
void rfmeter3_cfg_setup ( rfmeter3_cfg_t *cfg );
```

- `rfmeter3_init` Initialization function.
```c
err_t rfmeter3_init ( rfmeter3_t *ctx, rfmeter3_cfg_t *cfg );
```

#### Example key functions :

- `rfmeter3_enable_device` This function enables device by setting EN pin to HIGH logic level.
```c
void rfmeter3_enable_device ( rfmeter3_t *ctx );
```

- `rfmeter3_disable_device` This function disables device by setting EN pin to LOW logic level.
```c
void rfmeter3_disable_device ( rfmeter3_t *ctx );
```

- `rfmeter3_get_rf_input_power` This function reads the voltage from AN pin and converts it to RF input power in dBm.
```c
err_t rfmeter3_get_rf_input_power ( rfmeter3_t *ctx, float *data_out );
```

## Example Description

> This example demonstrates the use of RF Meter 3 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    rfmeter3_cfg_t rfmeter3_cfg;  /**< Click config object. */

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
    rfmeter3_cfg_setup( &rfmeter3_cfg );
    RFMETER3_MAP_MIKROBUS( rfmeter3_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == rfmeter3_init( &rfmeter3, &rfmeter3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    rfmeter3_enable_device ( &rfmeter3 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Measures the RF input signal power in dBm and displays the results on the USB UART every 100ms.

```c

void application_task ( void )
{
    float rfmeter3_rf_input_power = 0;

    if ( RFMETER3_ERROR != rfmeter3_get_rf_input_power ( &rfmeter3, &rfmeter3_rf_input_power ) ) 
    {
        log_printf( &logger, " RF Input Power: %.2f dBm\r\n", rfmeter3_rf_input_power );
        Delay_ms( 100 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RFMeter3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

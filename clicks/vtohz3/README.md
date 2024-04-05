\mainpage Main Page

---
# V to Hz 3 click

> V to Hz 3 Click is a compact add-on board that converts an analog voltage input signal into a specific frequency pulse wave signal. This board features the AD7740, an ultrasmall synchronous voltage-to-frequency converter from Analog Devices. The AD7740 has a linear response, so applying a voltage from 3V up to 5V on its VIN terminal will generate the pulse with a frequency linearly proportional to the input voltage. It contains an integrated 2.5V bandgap reference defining the span of the VFC and can be overdriven using an external reference. The full-scale output frequency is synchronous with the input clock signal provided by the LTC6903 programmable oscillator, with a maximum input frequency of 1MHz. Based on the analog input value, the output frequency goes from 10% to 90% of the input frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vtohz3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/v-to-hz-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the VtoHz3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VtoHz3 Click driver.

#### Standard key functions :

- `vtohz3_cfg_setup` Config Object Initialization function.
```c
void vtohz3_cfg_setup ( vtohz3_cfg_t *cfg );
```

- `vtohz3_init` Initialization function.
```c
err_t vtohz3_init ( vtohz3_t *ctx, vtohz3_cfg_t *cfg );
```

#### Example key functions :

- `vtohz3_set_input_frequency` This function enables and sets output frequency of the programmable oscillator, which is the AD7740 input frequency.
```c
err_t vtohz3_set_input_frequency ( vtohz3_t *ctx, uint32_t freq );
```

- `vtohz3_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t vtohz3_read_an_pin_voltage ( vtohz3_t *ctx, float *data_out );
```

- `vtohz3_get_frequency` This function converts voltage to the estimated output frequency in Hz.
```c
uint32_t vtohz3_get_frequency ( vtohz3_t *ctx, float voltage, float vref_in );
```

## Example Description

> This example demonstrates the use of the V to Hz 3 click board by calculating the estimated output frequency from the input voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the input frequency.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    vtohz3_cfg_t vtohz3_cfg;  /**< Click config object. */

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
    vtohz3_cfg_setup( &vtohz3_cfg );
    VTOHZ3_MAP_MIKROBUS( vtohz3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == vtohz3_init( &vtohz3, &vtohz3_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    vtohz3_set_input_frequency ( &vtohz3, VTOHZ3_DEFAULT_IN_FREQUENCY );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the input voltage from AN pin and calculates the output frequency from it. The results are being displayed on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float voltage;
    if ( VTOHZ3_OK == vtohz3_read_an_pin_voltage ( &vtohz3, &voltage ) ) 
    {
        log_printf( &logger, " Voltage : %.2f V\r\n", voltage );
        log_printf( &logger, " Output frequency : %lu Hz\r\n\n", 
                    vtohz3_get_frequency ( &vtohz3, voltage, VTOHZ3_VREF_INTERNAL_2V5 ) );
    }
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VtoHz3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

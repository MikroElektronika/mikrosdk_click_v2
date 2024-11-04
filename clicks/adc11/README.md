\mainpage Main Page

---
# ADC 11 Click

ADC 11 Click is a compact add-on board that contains a high-performance data converter. This board features the LTC1864, a 16-bit 250ksps analog-to-digital converter from Analog Devices. With a typical supply current of only 850µA at the maximum sampling frequency, the LTC1864 is among the lowest power consumption ADCs available. After conversion, the LTC1864 goes into a low-power Sleep mode, further reducing the supply current. That’s why it can run at proper micro-power levels in applications that do not require the maximum sampling rate of the LTC1864.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-11-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Adc11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Adc11 Click driver.

#### Standard key functions :

- `adc11_cfg_setup` Config Object Initialization function.
```c
void adc11_cfg_setup ( adc11_cfg_t *cfg );
```

- `adc11_init` Initialization function.
```c
ADC11_RETVAL adc11_init ( adc11_t *ctx, adc11_cfg_t *cfg );
```

- `adc11_default_cfg` Click Default Configuration function.
```c
void adc11_default_cfg ( adc11_t *ctx );
```

#### Example key functions :

- `adc11_generic_read` ADC 11 data reading function.
```c
err_t adc11_generic_read ( adc11_t *ctx, uint16_t *adc_data );
```

- `adc11_set_calibration` ADC 11 set calibration function.
```c
err_t adc11_set_calibration ( adc11_t *ctx, adc11_calibration_data_t *adc_val );
```

- `adc11_get_voltage` ADC 11 get voltage function.
```c
err_t adc11_get_voltage ( adc11_t *ctx, adc11_calibration_data_t *adc_val, float *voltage );
```

## Example Description

> This library contains API for ADC 11 Click driver.
> The library contains drivers for measuring ADC values  
> and for calculation voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI driver and triggers the built-in calibration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc11_cfg_t adc11_cfg;  /**< Click config object. */

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

    // Click initialization.

    adc11_cfg_setup( &adc11_cfg );
    ADC11_MAP_MIKROBUS( adc11_cfg, MIKROBUS_1 );
    err_t init_flag  = adc11_init( &adc11, &adc11_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "        Calibration        \r\n");
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n");
    log_printf( &logger, "> Turn OFF the Power unit <\r\n");
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n");
    log_printf( &logger, "  In the following 5 sec.  \r\n");
    log_printf( &logger, " turn OFF the Power Supply \r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start calibration    \r\n");
    
    if ( adc11_set_calibration( &adc11, &avg_adc_data ) == ADC11_OK ) {
        log_printf( &logger, "---------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");
        Delay_ms ( 1000 );    
    }
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "    Start measurements :   \r\n");
    log_printf( &logger, "---------------------------\r\n");
}

```

### Application Task

> This is an example that demonstrates the use of the ADC 11 Click board.
> In this example, we monitor and display voltage [ V ].
> Results are being sent to the Usart Terminal, where you can track their changes.
> All data logs write on USB UART changes every 2 sec.

```c

void application_task ( void ) {
    adc11_get_voltage( &adc11, &avg_adc_data, &voltage );
    log_printf( &logger, "     Volatge : %.3f V      \r\n", voltage );
    log_printf( &logger, "---------------------------\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---


---
# ADC 21 Click

> ADC 21 Click is a compact add-on board that converts an analog voltage into a digital representation. This board features the ADC1283, a low-power, eight-channel pure CMOS 12-bit analog-to-digital converter from STMicroelectronics. The ADC1283 is specified for conversion from 50ksps to 200ksps. Its architecture is based on a successive approximation register with an internal track-and-hold cell. It features eight single-ended multiplexed inputs, where the output serial data is straight binary and SPI-compatible.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc21_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 21 Click driver.

#### Standard key functions :

- `adc21_cfg_setup` Config Object Initialization function.
```c
void adc21_cfg_setup ( adc21_cfg_t *cfg );
```

- `adc21_init` Initialization function.
```c
err_t adc21_init ( adc21_t *ctx, adc21_cfg_t *cfg );
```

#### Example key functions :

- `adc21_read_raw_adc` This function reads raw ADC value from the selected channel by using SPI serial interface.
```c
err_t adc21_read_raw_adc ( adc21_t *ctx, uint8_t channel, uint16_t *raw_adc );
```

- `adc21_read_voltage` This function reads raw ADC value from the selected channel and converts it to proportional voltage level depending on the avcc selection.
```c
err_t adc21_read_voltage ( adc21_t *ctx, uint8_t channel, float avcc, float *voltage );
```

## Example Description

> This example demonstrates the use of ADC 21 Click board by reading and displaying the voltage levels from 8 analog input channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc21_cfg_t adc21_cfg;  /**< Click config object. */

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
    adc21_cfg_setup( &adc21_cfg );
    ADC21_MAP_MIKROBUS( adc21_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc21_init( &adc21, &adc21_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage levels from all 8 analog input channels and displays the results on the USB UART once per second approximately.

```c
void application_task ( void )
{
    static uint8_t ch_num = ADC21_CHANNEL_0;
    float ch_voltage;
    if ( ADC21_OK == adc21_read_voltage ( &adc21, ch_num, ADC21_AVCC_3V3, &ch_voltage ) )
    {
        log_printf ( &logger, " CH%u voltage: %.2f V\r\n", ( uint16_t ) ch_num, ch_voltage );
    }
    if ( ++ch_num > ADC21_CHANNEL_7 )
    {
        log_printf ( &logger, " ------------------------\r\n\n" );
        ch_num = ADC21_CHANNEL_0;
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

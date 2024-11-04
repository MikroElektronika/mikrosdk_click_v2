
---
# ADC 24 Click

> ADC 24 Click is a compact add-on board for high-speed analog to digital conversion. This board features the AD7490, a 12-bit, 16-channel successive approximation ADC from Analog Devices, optimized for efficient power usage with a consumption of just 2.5mA from a 5V supply while achieving up to 1MSPS throughput rates. The board features 16 single-ended analog inputs with a configurable input range, supported by a channel sequencer for sequential channel conversion and multiple operational modes for flexible power management. This makes ADC 24 Click ideal for extensive system monitoring applications such as multichannel system monitoring, power line monitoring, data acquisition, instrumentation, and process control, serving various industrial and tech applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc24_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-24-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC 24 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 24 Click driver.

#### Standard key functions :

- `adc24_cfg_setup` Config Object Initialization function.
```c
void adc24_cfg_setup ( adc24_cfg_t *cfg );
```

- `adc24_init` Initialization function.
```c
err_t adc24_init ( adc24_t *ctx, adc24_cfg_t *cfg );
```

#### Example key functions :

- `adc24_get_voltage` This function reads the results of 12-bit ADC raw data and converts them to proportional voltage levels by using the SPI serial interface.
```c
err_t adc24_get_voltage ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, float *voltage );
```

- `adc24_get_adc_data` This function reads a conversion result and selected channel by using the SPI serial interface.
```c
err_t adc24_get_adc_data ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, uint16_t *adc_data );
```

## Example Description

> This example demonstrates the use of the ADC 24 Click board 
> by reading and writing data by using the SPI serial interface 
> and reading results of AD conversion.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc24_cfg_t adc24_cfg;  /**< Click config object. */

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
    adc24_cfg_setup( &adc24_cfg );
    ADC24_MAP_MIKROBUS( adc24_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc24_init( &adc24, &adc24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    ctrl.ch_sel = ADC24_CH_SEL_IN_0;
    ctrl.pm = ADC24_PM_NORMAL;
    ctrl.seq_shadow = ADC24_SEQ_SHADOW_AN_INPUT;
    ctrl.weak = ADC24_WEAK_DOUT_THREE_STATE;
    ctrl.range = ADC24_RANGE_VREF_5V;
    ctrl.coding = ADC24_CODING_BIN;

    log_info( &logger, " Application Task " );
    log_printf( &logger, "_____________\r\n" );
}
```

### Application Task

> The demo application reads the voltage levels 
> from all 15 analog input channels and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t ch_pos = 0;
    float voltage = 0;
    for ( uint8_t n_cnt = ADC24_CH_SEL_IN_0; n_cnt <= ADC24_CH_SEL_IN_15; n_cnt++ )
    {
        ctrl.ch_sel = n_cnt;
        if ( ADC24_OK == adc24_get_voltage( &adc24, ctrl, &ch_pos, &voltage ) )
        {
            log_printf( &logger, " IN%u : %.3f V\r\n", ( uint16_t ) ch_pos, voltage );
        }
        Delay_ms ( 100 );  
    }
    log_printf( &logger, "_____________\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC24

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

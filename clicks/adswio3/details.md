
---
# AD-SWIO 3 click

> AD-SWIO 3 Click is a compact add-on board representing a software configurable input/output solution for various purposes. This board features the AD74115H, a single-channel, software-configurable input and output with HART mode from Analog Devices. It provides many functionality for analog input, analog output, digital input, digital output, 2-wire, 3-wire, and 4-wire resistance temperature detector (RTD), and thermocouple measurement capability. The supply power and isolation part are managed by the ADP1034, a 3-channel isolated micropower management unit with seven digital isolators and programmable power control, also from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adswio3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ad-swio-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the AD-SWIO 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AD-SWIO 3 Click driver.

#### Standard key functions :

- `adswio3_cfg_setup` Config Object Initialization function.
```c
void adswio3_cfg_setup ( adswio3_cfg_t *cfg );
```

- `adswio3_init` Initialization function.
```c
err_t adswio3_init ( adswio3_t *ctx, adswio3_cfg_t *cfg );
```

- `adswio3_default_cfg` Click Default Configuration function.
```c
err_t adswio3_default_cfg ( adswio3_t *ctx );
```

#### Example key functions :

- `adswio3_get_voltage_input` This function reads the raw ADC value and converts them to a proportional voltage level measured by the voltage between the I/OP and I/ON screw terminals.
```c
err_t adswio3_get_voltage_input ( adswio3_t *ctx, uint8_t adc_sel, float *voltage );
```

- `adswio3_get_diag_res` This function is used to read the desired diagnostic conversion results.
```c
err_t adswio3_get_diag_res ( adswio3_t *ctx, uint8_t diag_sel, uint16_t *adc_diag_data );
```

- `adswio3_set_adc_cnv` This function is used to control the ADC conversions that must be performed.
```c
err_t adswio3_set_adc_cnv ( adswio3_t *ctx, adswio3_adc_cnv_ctrl_t adc_cnv_ctrl );
```

## Example Description

> This library contains API for the AD-SWIO 3 Click driver 
> for measurements of the analog output, analog input, digital input, 
> resistance temperature detector (RTD), and thermocouple measurements.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI and log UART.
> After driver initialization, the app executes a default configuration 
> that enables and sets it to measure IOP/ION voltage input from 0V to 12V, 
> with 4.8k SPS and enabled four diagnostics measurements (AVDD, VASS, VACC and LVIN).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adswio3_cfg_t adswio3_cfg;  /**< Click config object. */

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
    adswio3_cfg_setup( &adswio3_cfg );
    ADSWIO3_MAP_MIKROBUS( adswio3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adswio3_init( &adswio3, &adswio3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADSWIO3_ERROR == adswio3_default_cfg ( &adswio3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );

    for ( uint8_t n_cnt = ADSWIO3_GPIO_CONFIG_SEL_A; n_cnt <= ADSWIO3_GPIO_CONFIG_SEL_D; n_cnt ++ )
    {
        if ( ADSWIO3_ERROR == adswio3_set_gpio_config( &adswio3, n_cnt, 
                                                              ADSWIO3_GPIO_CONFIG_GPO_DATA_HIGH, 
                                                              ADSWIO3_GPIO_CONFIG_GP_WK_PD_DIS, 
                                                              ADSWIO3_GPIO_CONFIG_MODE_OUT ) )
        {
            log_error( &logger, " Set GPIO configuration. " );
            for ( ; ; );
        }
        Delay_ms( 100 );
    }

    float diag_vtg = 0;
    log_printf( &logger, "_________________________\r\n" );
    log_printf( &logger, " > Diagnostic Voltages <\r\n" );
    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_0, &diag_vtg ) )
    {
        log_printf( &logger, " AVDD: %.2f V\r\n", diag_vtg );
        Delay_ms( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_1, &diag_vtg ) )
    {
        log_printf( &logger, " VASS: %.2f V\r\n", diag_vtg );
        Delay_ms( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_2, &diag_vtg ) )
    {
        log_printf( &logger, " VACC: %.2f V\r\n", diag_vtg );
        Delay_ms( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_3, &diag_vtg ) )
    {
        log_printf( &logger, " LVIN: %.2f V\r\n", diag_vtg );
        Delay_ms( 100 );
    }
    log_printf( &logger, "_________________________\r\n" );
    Delay_ms( 1000 );
}
```

### Application Task

> This example demonstrates the use of the AD-SWIO 3 Click board. 
> The demo application reads and displays the voltage level input, 
> measured by the voltage between the I/OP and I/ON screw terminals 
> and NTC thermistor temperature in degrees Celsius.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float ntc_temp = 0, iop_ion_vtg = 0;
    if ( ADSWIO3_OK == adswio3_get_ntc_temp( &adswio3, ADSWIO3_DIAG_RESULT_SEL_3, &ntc_temp ) )
    {
        log_printf( &logger, " NTC Temperature: %.2f degC\r\n", ntc_temp );
        
        Delay_ms( 100 );
    }
    
    if ( ADSWIO3_OK == adswio3_get_voltage_input( &adswio3, 0, &iop_ion_vtg ) )
    {
        log_printf( &logger, "IOP/ION Voltage: %.3f V\r\n", iop_ion_vtg );
        Delay_ms( 100 );
    }
    log_printf( &logger, "_________________________\r\n" );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADSWIO3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

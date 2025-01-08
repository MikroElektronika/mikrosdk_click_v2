
---
# AD-SWIO 3 Click

> [AD-SWIO 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5946) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5946&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the AD-SWIO 3 Click driver 
> for measurements of the analog output, analog input, digital input, 
> resistance temperature detector (RTD), and thermocouple measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADSWIO3

### Example Key Functions

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
    Delay_ms ( 100 );

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
        Delay_ms ( 100 );
    }

    float diag_vtg = 0;
    log_printf( &logger, "_________________________\r\n" );
    log_printf( &logger, " > Diagnostic Voltages <\r\n" );
    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_0, &diag_vtg ) )
    {
        log_printf( &logger, " AVDD: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_1, &diag_vtg ) )
    {
        log_printf( &logger, " VASS: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_2, &diag_vtg ) )
    {
        log_printf( &logger, " VACC: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_3, &diag_vtg ) )
    {
        log_printf( &logger, " LVIN: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "_________________________\r\n" );
    Delay_ms ( 1000 );
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
        
        Delay_ms ( 100 );
    }
    
    if ( ADSWIO3_OK == adswio3_get_voltage_input( &adswio3, 0, &iop_ion_vtg ) )
    {
        log_printf( &logger, "IOP/ION Voltage: %.3f V\r\n", iop_ion_vtg );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "_________________________\r\n" );
    Delay_ms ( 1000 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---

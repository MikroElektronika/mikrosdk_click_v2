\mainpage Main Page


---
# ADC 10 click

ADC 10 Click is a compact add-on board that contains a high-performance data converter. This board features the ADS122U04, a 24-bit precision ?S analog-to-digital converter with UART compatible interface from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc10-click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-10-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Adc10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Adc10 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void adc10_cfg_setup ( adc10_cfg_t *cfg );
```

- Initialization function.
```
ADC10_RETVAL adc10_init ( adc10_t *ctx, adc10_cfg_t *cfg );
```

- Click Default Configuration function.
```
void adc10_default_cfg ( adc10_t *ctx );
```

#### Example key functions :

- ADC 10 Start the synchronization function.
```
void adc10_start_sync ( adc10_t *ctx );
```

- ADC 10 Get the channel output function.
```
int32_t adc10_get_ch_output ( adc10_t *ctx, uint8_t sel_ch );
```

- ADC 10 Calculate the voltage function.
```
float adc10_calc_voltage ( adc10_t *ctx, int32_t adc_data, float vref, uint8_t gain );
```

## Examples Description

This is an example that demonstrates the use of the ADC 10 click board.

**The demo application is composed of two sections :**

### Application Init

Initialization driver enables - UART,
select analog input channel 0, perform a hardware and software reset
and set the default device configuration, also, write a log.

```
void application_init ( void ) {
    log_cfg_t log_cfg;       /**< Logger config object. */
    adc10_cfg_t adc10_cfg;   /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n-------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    adc10_cfg_setup( &adc10_cfg );
    ADC10_MAP_MIKROBUS( adc10_cfg, MIKROBUS_1 );
    err_t init_flag  = adc10_init( &adc10, &adc10_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    select_ch = ADC10_ANALOG_INPUT_CH_3;
    
    // Hardware reset.
    
    adc10_hw_reset( &adc10 );
    Delay_ms( 100 );
    
    // Software reset.
    
    adc10_reset( &adc10 );
    Delay_ms( 1000 );

    // Click default configuration.
    
    adc10_default_cfg ( &adc10 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}
```

### Application Task

In this example, we monitor and display
24-bits of data ( from 0 to 8388607 ) of ADC and voltage ( from 0 mV to 2048 mV )
on the selected channel ( CH-0, CH-1, CH-2 or CH-3 ).
Results are being sent to the Usart Terminal where you can track their changes.
All data logs write on USB uart changes approximately for every 1 sec.

```
void application_task ( void ) {   
    adc10_start_sync( &adc10 );
    Delay_ms( 1 );

    while ( adc10_check_drdy( &adc10 ) == ADC10_NEW_DATA_NOT_READY );

    out_data = adc10_get_ch_output( &adc10, select_ch );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  ADC CH-%u : %.0f\r\n", ( uint16_t ) select_ch, ( float ) out_data );

    voltage = adc10_calc_voltage( &adc10, out_data, ADC10_VREF_INTERNAL, ADC10_GAIN_1 );
    log_printf( &logger, "  Voltage  : %.2f mV\r\n", voltage );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---

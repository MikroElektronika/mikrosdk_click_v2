
---
# Hall Current 12 click

> Hall Current 12 Click is a compact add-on board that provides economical and precise AC or DC current sensing solutions. This board features the TMCS1100, a galvanically isolated Hall-effect current sensor capable of DC or AC current measurement with high accuracy, excellent linearity, and temperature stability from Texas Instruments. It enables the lowest drift, <1% full-scale error, and highest accuracy over time and temperature. It also provides a reliable 600V lifetime working voltage and 3kVRMS isolation between the current path and circuitry with uni/bidirectional current sensing. Besides, the user is allowed to process the output signal in analog or digital form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the HallCurrent12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HallCurrent12 Click driver.

#### Standard key functions :

- `hallcurrent12_cfg_setup` Config Object Initialization function.
```c
void hallcurrent12_cfg_setup ( hallcurrent12_cfg_t *cfg );
```

- `hallcurrent12_init` Initialization function.
```c
err_t hallcurrent12_init ( hallcurrent12_t *ctx, hallcurrent12_cfg_t *cfg );
```

#### Example key functions :

- `hallcurrent12_calibration` Hall Current 12 calibration function.
```c
err_t hallcurrent12_calibration ( hallcurrent12_t *ctx )
```

- `hallcurrent12_get_adc` Hall Current 12 get ADC function.
```c
err_t hallcurrent12_get_adc ( hallcurrent12_t *ctx, float *adc_vtg );
```

- `hallcurrent12_get_current` Hall Current 12 get current function.
```c
err_t hallcurrent12_get_current ( hallcurrent12_t *ctx, float *current );
```

## Example Description

> This library contains API for Hall Current 12 Click driver. The demo application reads ADC voltage ( V ) and current ( A ).

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and calibrates the device offset.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent12_cfg_t hallcurrent12_cfg;  /**< Click config object. */

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
    hallcurrent12_cfg_setup( &hallcurrent12_cfg );
    HALLCURRENT12_MAP_MIKROBUS( hallcurrent12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hallcurrent12_init( &hallcurrent12, &hallcurrent12_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Calibrating device, remove input current in the next 5 seconds..." );
    Delay_ms( 5000 );
    
    if ( I2C_MASTER_ERROR == hallcurrent12_calibration ( &hallcurrent12 ) )
    {
        log_error( &logger, " Calibration Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_info( &logger, " Calibration done!" );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Hall Current 12 Click board™.
> In this example, we read and display the ADC voltage ( V ) and current ( A ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static float adc_voltage = 0;
    static float current = 0;
    if ( HALLCURRENT12_OK == hallcurrent12_get_adc( &hallcurrent12, &adc_voltage ) )
    {
        log_printf( &logger, " ADC voltage : %.3f V \r\n", adc_voltage );
    }
    if ( HALLCURRENT12_OK == hallcurrent12_get_current ( &hallcurrent12, &current ) )
    {
        log_printf( &logger, " Current     : %.3f A \r\n", current );
        log_printf( &logger, "--------------------------\r\n" );
    }
    Delay_ms( 1000 );
}

```

## Note

> Switches: 
>    Sensitivity : Low ( GAIN = 1 ),
>    Vout_Sel    : AN  ( Analog interface ),
>    Vref_Sel    : VCC/2 ( bidirectional measurement ).

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

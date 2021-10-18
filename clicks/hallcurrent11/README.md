\mainpage Main Page

---
# Hall Current 11 click

> Hall Current 11 Click is a compact add-on board that provides economical and precise AC or DC current sensing solutions. This board features the TMCS1108A2U, a galvanically isolated Hall-effect current sensor with high accuracy, excellent linearity, and temperature stability from Texas Instruments. The input current flows through an internal 1.8mΩ conductor that generates a magnetic field measured by an integrated Hall-effect sensor. It features a 100V functional isolation working voltage with both unidirectional and bidirectional current sensing. Based on the selected logic voltage VCC, the TMCS1108A2U allows the user to measure current in two appropriate ranges, where after that, can process the output signal in analog or digital form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-11-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HallCurrent11 Click driver.

#### Standard key functions :

- `hallcurrent11_cfg_setup` Config Object Initialization function.
```c
void hallcurrent11_cfg_setup ( hallcurrent11_cfg_t *cfg );
```

- `hallcurrent11_init` Initialization function.
```c
err_t hallcurrent11_init ( hallcurrent11_t *ctx, hallcurrent11_cfg_t *cfg );
```

- `hallcurrent11_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent11_default_cfg ( hallcurrent11_t *ctx );
```

#### Example key functions :

- `hallcurrent11_get_adc` Hall Current 11 ADC reading function.
```c
err_t hallcurrent11_get_adc ( hallcurrent11_t *ctx, uint16_t *data_out );
```

- `hallcurrent11_get_adc_voltage` Hall Current 11 get ADC voltage function.
```c
err_t hallcurrent11_get_adc_voltage ( hallcurrent11_t *ctx, float *adc_vtg );
```

- `hallcurrent11_get_current` Hall Current 11 get current function.
```c
err_t hallcurrent11_get_current ( hallcurrent11_t *ctx, float *current );
```

## Example Description

> This library contains API for Hall Current 11 Click driver.
> The demo application reads ADC value and current ( A ).

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent11_cfg_t hallcurrent11_cfg;  /**< Click config object. */

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
    hallcurrent11_cfg_setup( &hallcurrent11_cfg );
    HALLCURRENT11_MAP_MIKROBUS( hallcurrent11_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent11_init( &hallcurrent11, &hallcurrent11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hallcurrent11_default_cfg ( &hallcurrent11 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Hall Current 11 Click board™.
> In this example, we read and display the ADC values and current ( A ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static uint16_t adc_data;
    static float current;
    
    hallcurrent11_get_adc( &hallcurrent11, &adc_data );
    log_printf( &logger, " ADC Value   : %d \r\n", adc_data );
    log_printf( &logger, "- - - - - - - - - - -  - -\r\n" );
    Delay_ms( 100 );

    hallcurrent11_get_current ( &hallcurrent11, &current );
    log_printf( &logger, " Current     : %.3f A \r\n", current );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

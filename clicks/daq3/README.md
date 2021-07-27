\mainpage Main Page

---
# DAQ 3 click

DAQ 3 Click is a compact add-on board representing a precision data acquisition solution. This board features the ADAQ4003, fast and precise μModule precision data acquisition (DAQ) signal chain solution from Analog Devices. Using SIP technology, the ADAQ4003 reduces end system component count by combining multiple standard signal processing and conditioning blocks into a single device. These blocks include a high-resolution 18-bit, 2 MSPS successive approximation register ADC, fully differential ADC driver amplifier, and a stable reference buffer along with selectable gain options. This Click board™ is suitable for process control and machine automation applications, as automatic test equipment, digital control loops, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/daq3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/daq-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Daq3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Daq3 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void daq3_cfg_setup ( daq3_cfg_t *cfg );
```

- Initialization function.
```
DAQ3_RETVAL daq3_init ( daq3_t *ctx, daq3_cfg_t *cfg );
```

- Click Default Configuration function.
```
void daq3_default_cfg ( daq3_t *ctx );
```

#### Example key functions :

- DAQ 3 get voltage function.
```
float daq3_get_voltage ( daq3_t *ctx );
```

- DAQ 3 get conversion result function.
```
int32_t daq3_get_conversion_result ( daq3_t *ctx, daq3_reg_cfg_t cfg_data );
```

- DAQ 3 data reading function.
```
err_t daq3_generic_read ( daq3_t *ctx, uint8_t reg, uint8_t *data_out );
```

## Examples Description

The demo application reads ADC value, calculate and display voltage ( mV ).

**The demo application is composed of two sections :**

### Application Init

Initializes SPI driver and start to write log.

```
void application_init ( void ) {
    log_cfg_t log_cfg;    /**< Logger config object. */
    daq3_cfg_t daq3_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    daq3_cfg_setup( &daq3_cfg );
    DAQ3_MAP_MIKROBUS( daq3_cfg, MIKROBUS_1 );
    err_t init_flag  = daq3_init( &daq3, &daq3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    daq3_default_cfg ( &daq3 );
    log_info( &logger, " Application Task \r\n" );
    Delay_ms( 100 );
    daq3_get_voltage( &daq3 );
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "         DAQ 3 click       \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

This is an example that demonstrates the use of the DAQ 3 click board.
In this example, we read ADC value, calculate and display the voltage ( mV ) data.
The maximum output voltage ( Vout ) is 4V and 
depends on the gain that is set at the click.
The formula used to calculate is Vin = Vout / gain. 
Keep in mind that Vout should not exceed 4V.
For example, if the gain is set to 2 the maximum Vin is 2V ( 2V = 4V / 2 ). 
Results are being sent to the Usart Terminal where you can track their changes.

```
void application_task ( void ) {   
    float voltage = daq3_get_voltage( &daq3 );
    log_printf( &logger, "   Voltage : %.3f mV       \r\n", voltage );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Daq3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---

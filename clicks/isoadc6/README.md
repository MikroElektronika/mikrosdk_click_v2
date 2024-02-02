\mainpage Main Page

---
# ISO ADC 6 click

> ISO ADC 6 Click is a compact add-on board that contains an eight-channel isolated ADC. This board features the AD7124-8, an 8-channel, low noise, low power, 24-bit, sigma-delta ADC from Analog Devices. The ADC has a programmable gain array (PGA) that allows gains of 1, 2, 4, 8, 16, 32, 64, and 128. Additionally, the ADC contains a 2.5V reference, which can be used with reference buffers, along with the externally applied references. The host MCU is isolated from the ADC by the ADuM341E, a 5kVrms quad digital isolator from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/isoadc6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/iso-adc-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the ISO ADC 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISO ADC 6 Click driver.

#### Standard key functions :

- `isoadc6_cfg_setup` Config Object Initialization function.
```c
void isoadc6_cfg_setup ( isoadc6_cfg_t *cfg );
```

- `isoadc6_init` Initialization function.
```c
err_t isoadc6_init ( isoadc6_t *ctx, isoadc6_cfg_t *cfg );
```

- `isoadc6_default_cfg` Click Default Configuration function.
```c
err_t isoadc6_default_cfg ( isoadc6_t *ctx );
```

#### Example key functions :

- `isoadc6_get_voltage` ISO ADC 6 get voltage level function.
```c
err_t isoadc6_get_voltage ( isoadc6_t* ctx, float *voltage );
```

- `isoadc6_get_adc_data` ISO ADC 6 get ADC data function.
```c
err_t isoadc6_get_adc_data ( isoadc6_t* ctx, uint32_t *adc_data );
```

- `isoadc6_set_adc_control` ISO ADC 6 set ADC control function.
```c
err_t isoadc6_set_adc_control ( isoadc6_t* ctx, uint16_t adc_ctrl_data );
```

## Example Description

> This example demonstrates the use of the ISO ADC 6 Click board™ 
> by reading and writing data by using SPI serial interface 
> and reading results of AD conversion.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration which enables channel 0,
> puts A0 on positive analog input and A1 on negative analog input,
> enables internal reference voltage (approximately 2.65V (AVDD = 3.3V)),
> and also enables bipolar operation mode and puts device on full power mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc6_cfg_t isoadc6_cfg;  /**< Click config object. */

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
    isoadc6_cfg_setup( &isoadc6_cfg );
    ISOADC6_MAP_MIKROBUS( isoadc6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc6_init( &isoadc6, &isoadc6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISOADC6_ERROR == isoadc6_default_cfg ( &isoadc6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads the voltage levels from analog input (A0-A1) and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( ISOADC6_OK == isoadc6_get_voltage( &isoadc6, &voltage ) )
    {
        log_printf( &logger, " Voltage: %.3f [V]\r\n", voltage );
        Delay_ms( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

\mainpage Main Page

---
# ISO ADC 7 Click

> ISO ADC 7 Click is a compact add-on board designed for precise multi-channel data acquisition in various industrial applications. This board features the AMC131M03, a three-channel, 24-bit delta-sigma ADC from Texas Instruments. The AMC131M03 features a silicon-dioxide-based isolation barrier providing 5000-VRMS isolation, integrated digital decimation filters for reduced quantization noise, and a programmable gain amplifier with gains up to 128 for high-accuracy measurements. Additionally, it includes an internal temperature sensor with options for external or onboard temperature sensing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/isoadc7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/iso-adc-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the ISO ADC 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISO ADC 7 Click driver.

#### Standard key functions :

- `isoadc7_cfg_setup` Config Object Initialization function.
```c
void isoadc7_cfg_setup ( isoadc7_cfg_t *cfg );
```

- `isoadc7_init` Initialization function.
```c
err_t isoadc7_init ( isoadc7_t *ctx, isoadc7_cfg_t *cfg );
```

- `isoadc7_default_cfg` Click Default Configuration function.
```c
err_t isoadc7_default_cfg ( isoadc7_t *ctx );
```

#### Example key functions :

- `isoadc7_read_voltage` This function reads the voltage measurements of all three channels.
```c
err_t isoadc7_read_voltage ( isoadc7_t *ctx, float *ch0, float *ch1, float *ch2 );
```

- `isoadc7_read_data` This function reads the status register and raw data of all three channels.
```c
err_t isoadc7_read_data ( isoadc7_t *ctx, isoadc7_data_t *data_out );
```

- `isoadc7_set_gain` This function sets the gain level for all channels.
```c
err_t isoadc7_set_gain ( isoadc7_t *ctx, uint8_t gain_ch0, uint8_t gain_ch1, uint8_t gain_ch2 );
```

## Example Description

> This example demonstrates the use of ISO ADC 7 Click board by reading and displaying the voltage levels from 3 isolated analog input channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration. The full-scale voltage input range is set to +-1.2V for all channels.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc7_cfg_t isoadc7_cfg;  /**< Click config object. */

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
    isoadc7_cfg_setup( &isoadc7_cfg );
    ISOADC7_MAP_MIKROBUS( isoadc7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc7_init( &isoadc7, &isoadc7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISOADC7_ERROR == isoadc7_default_cfg ( &isoadc7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage levels from all 3 isolated analog input channels and displays the results on the USB UART once per second approximately.

```c
void application_task ( void )
{
    float ch0 = 0;
    float ch1 = 0;
    float ch2 = 0;
    if ( ISOADC7_OK == isoadc7_read_voltage ( &isoadc7, &ch0, &ch1, &ch2 ) )
    {
        log_printf ( &logger, " CH0: %.1f mV\r\n", ch0 );
        log_printf ( &logger, " CH1: %.1f mV\r\n", ch1 );
        log_printf ( &logger, " CH2: %.1f mV\r\n\n", ch2 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

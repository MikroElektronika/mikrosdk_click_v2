
---
# ISO ADC 5 click

ISO ADC 5 Click is a compact add-on board that contains quad-channel isolated ADC with field supply. This board features the MAX22530, galvanically isolated, 4-channel, multiplexed, 12-bit, analog-to-digital converter (ADC), providing 5kVRMS isolation from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/isoadc5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/iso-adc-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ISOADC5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISOADC5 Click driver.

#### Standard key functions :

- `isoadc5_cfg_setup` Config Object Initialization function.
```c
void isoadc5_cfg_setup ( isoadc5_cfg_t *cfg );
```

- `isoadc5_init` Initialization function.
```c
err_t isoadc5_init ( isoadc5_t *ctx, isoadc5_cfg_t *cfg );
```

#### Example key functions :

- `isoadc5_write_register` This function writes two bytes of data to the selected register by using the SPI serial interface.
```c
err_t isoadc5_write_register ( isoadc5_t *ctx, uint8_t reg, uint16_t data_in );
```

- `isoadc5_read_register` This function reads two bytes of data from the selected register by using the SPI serial interface.
```c
err_t isoadc5_read_register ( isoadc5_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `isoadc5_read_voltage` This function reads the raw adc data from a desired input channel and converts it to voltage.
```c
err_t isoadc5_read_voltage( isoadc5_t *ctx, uint8_t filt, uint8_t ch, float *volt );
```

## Example Description

> This example demonstrates the use of ISO ADC 5 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    isoadc5_cfg_t isoadc5_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    isoadc5_cfg_setup( &isoadc5_cfg );
    ISOADC5_MAP_MIKROBUS( isoadc5_cfg, MIKROBUS_1 );
    err_t init_flag  = isoadc5_init( &isoadc5, &isoadc5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage from all input channels and displays the values of each channel on the USB UART approximately every second.

```c

void application_task ( void )
{
    float v_ain1 = 0, v_ain2 = 0, v_ain3 = 0, v_ain4 = 0;
    err_t error_flag = isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_1, &v_ain1 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_2, &v_ain2 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_3, &v_ain3 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_4, &v_ain4 );
    
    if ( ISOADC5_OK == error_flag )
    {
        log_printf( &logger, " AIN 1 voltage: %.3f V\r\n", v_ain1 );
        log_printf( &logger, " AIN 2 voltage: %.3f V\r\n", v_ain2 );
        log_printf( &logger, " AIN 3 voltage: %.3f V\r\n", v_ain3 );
        log_printf( &logger, " AIN 4 voltage: %.3f V\r\n\r\n", v_ain4 );
        Delay_ms( 1000 );
    }
}

```

## Note

> The voltage input range is from 0 to 48V.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---

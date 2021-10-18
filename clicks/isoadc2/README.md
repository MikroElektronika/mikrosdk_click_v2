\mainpage Main Page

---
# ISO ADC 2 click

> ISO ADC 2 Click is a compact add-on board that represents a completely isolated 12-bit, 300 kSPS data acquisition system. This board features the AD7091R, successive-approximation analog-to-digital converter (ADC) from Analog Devices. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/isoadc2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/iso-adc-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the IsoAdc2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IsoAdc2 Click driver.

#### Standard key functions :

- `isoadc2_cfg_setup` Config Object Initialization function.
```c
void isoadc2_cfg_setup ( isoadc2_cfg_t *cfg );
```

- `isoadc2_init` Initialization function.
```c
err_t isoadc2_init ( isoadc2_t *ctx, isoadc2_cfg_t *cfg );
```

#### Example key functions :

- `isoadc2_read_adc` ISO ADC 2 ADC data reading function.
```c
err_t isoadc2_read_adc ( isoadc2_t *ctx, uint16_t *adc_val );
```

- `isoadc2_get_mv` ISO ADC 2 voltage data reading function.
```c
err_t isoadc2_get_mv ( isoadc2_t *ctx, uint16_t *voltage );
```

## Example Description

> This is an example that demonstrates the use of the ISO ADC 2 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and additional GPIO pins.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc2_cfg_t isoadc2_cfg;  /**< Click config object. */

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

    isoadc2_cfg_setup( &isoadc2_cfg );
    ISOADC2_MAP_MIKROBUS( isoadc2_cfg, MIKROBUS_1 );
    err_t init_flag  = isoadc2_init( &isoadc2, &isoadc2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Every second reads ADC data and voltage in mV and logs result.

```c

void application_task ( void ) {
    uint16_t rx_data;
    uint16_t mv_data;
    
    isoadc2_read_adc( &isoadc2, &rx_data );
    Delay_ms( 100 );
    isoadc2_get_mv( &isoadc2, &mv_data );
    
    log_printf( &logger, " ADC: %d \r\n", rx_data );
    log_printf( &logger, " VIN: %d mV\r\n", mv_data );
    log_printf( &logger, "---------------\r\n" );

    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IsoAdc2

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

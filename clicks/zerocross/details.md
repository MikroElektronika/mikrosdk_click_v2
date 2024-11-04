
---
# Zero-Cross Click

> Zero-Cross Click is a compact add-on board that has the ability to detect the change from positive to negative or negative to a positive level of a sinusoidal waveform. This board features circuitry that provides Zero Crossing Detection (ZCD). Whenever the sine wave crosses the ground potential, the output shifts from HIGH logic to LOW or vice-versa. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/zerocross_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/zero-cross-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Zero-Cross Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Zero-Cross Click driver.

#### Standard key functions :

- `zerocross_cfg_setup` Config Object Initialization function.
```c
void zerocross_cfg_setup ( zerocross_cfg_t *cfg );
```

- `zerocross_init` Initialization function.
```c
err_t zerocross_init ( zerocross_t *ctx, zerocross_cfg_t *cfg );
```

#### Example key functions :

- `zerocross_pin_read` Zero-Cross pin reading function.
```c
uint8_t zerocross_pin_read ( zerocross_t *ctx );
```

- `zerocross_get_freq` Zero-Cross frequency reading function.
```c
void zerocross_get_freq ( zerocross_t *ctx, float *freq );
```

## Example Description

> This example demonstrates the use of the Zero-Cross Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization of the log UART and basic Click initialisation.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    zerocross_cfg_t zerocross_cfg;  /**< Click config object. */

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
    zerocross_cfg_setup( &zerocross_cfg );
    ZEROCROSS_MAP_MIKROBUS( zerocross_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == zerocross_init( &zerocross, &zerocross_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reading frequency value approximately once every second.

```c
void application_task ( void ) 
{
    float freq_val = 0;
    zerocross_get_freq( &zerocross, &freq_val );
    log_printf( &logger, " Freq %.2f Hz \n\r", freq_val );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ZeroCross

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

\mainpage Main Page

---
# ECG 5 Click

> ECG 5 Click can be used for the development of ECG and Heart-Rate (HR) applications. The Click board™ features the AD8232, an integrated bio-signal front end. This IC has many features necessary for providing accurate ECG measurements, including very high common-mode rejection ratio, high gain with DC blocking capability, adjustable high-pass and low-pass filters, integrated right leg drive (RLD), etc.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ecg-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the ECG5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ECG5 Click driver.

#### Standard key functions :

- `ecg5_cfg_setup` Config Object Initialization function.
```c
void ecg5_cfg_setup ( ecg5_cfg_t *cfg );
```

- `ecg5_init` Initialization function.
```c
err_t ecg5_init ( ecg5_t *ctx, ecg5_cfg_t *cfg );
```

#### Example key functions :

- `ecg5_set_mode` Mode Setting function.
```c
void ecg5_setMode( ecg5_t *ctx, uint8_t state );
```

- `ecg5_check_lod_negative` LOD- Checking function.
```c
err_t ecg5_check_LOD_negative( ecg5_t *ctx );
```

- `ecg5_check_lod_positive` LOD+ Checking function.
```c
err_t ecg5_check_lod_positive( ecg5_t *ctx );
```

## Example Description

> This is an example which demonstrates the use of ECG 5 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes ADC and GPIO.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg5_cfg_t ecg5_cfg;  /**< Click config object. */

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
    ecg5_cfg_setup( &ecg5_cfg );
    ECG5_MAP_MIKROBUS( ecg5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ecg5_init( &ecg5, &ecg5_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads ADC value and sends results on serial plotter every 5 ms.

```c

void application_task ( void ) {
    uint16_t ecg5_an = 0;
    if ( ecg5_read_an_pin_value( &ecg5, &ecg5_an ) == ADC_SUCCESS ) {
        log_printf( &logger, " %u,%lu\r\n ", ecg5_an, time );
    }
    time += 5;
    Delay_ms ( 5 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ECG5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

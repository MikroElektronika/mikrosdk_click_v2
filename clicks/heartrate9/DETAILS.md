
---
# Heart Rate 9 click

The Heart Rate 9 click is a Click board™ which features PIC16F1779 8-bit MCU and SFH 7060 heart rate and pulse oximetry monitoring sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heart-rate-9-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type


# Software Support

We provide a library for the HeartRate9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for HeartRate9 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void heartrate9_cfg_setup ( heartrate9_cfg_t *cfg );
```

- Initialization function.
```
HEARTRATE9_RETVAL heartrate9_init ( heartrate9_t *ctx, heartrate9_cfg_t *cfg );
```

- Click Default Configuration function.
```
void heartrate9_default_cfg ( heartrate9_t *ctx );
```

#### Example key functions :

- Heart Rate 9 data writing function.
```
err_t heartrate9_generic_write ( heartrate9_t *ctx, char *data_buf, uint16_t len );
```

- Heart Rate 9 data reading function.
```
err_t heartrate9_generic_read ( heartrate9_t *ctx, char *data_buf, uint16_t max_len );
```

- Sets state of the rst pin setting.
```
void heartrate9_set_rst ( heartrate9_t *ctx, uint8_t state );
```

## Examples Description

> This example reads and processes data from Heart Rate 9 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module.

```
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate9_cfg_t heartrate9_cfg;  /**< Click config object. */

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

    // Click initialization.
    heartrate9_cfg_setup( &heartrate9_cfg );
    HEARTRATE9_MAP_MIKROBUS( heartrate9_cfg, MIKROBUS_1 );
    err_t init_flag  = heartrate9_init( &heartrate9, &heartrate9_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
}

```

### Application Task

> Reads the received data and logs it.

```
void application_task ( void )
{
   heartrate9_process();

    if ( app_buf_len > 0 )
    {
        log_printf( &logger, "%s", app_buf );
        heartrate9_clear_app_buf(  );
    }
}

```

## Note

> Data structure is:
>>AA;BB;CC;DD;EE;
>>>AA -> Data header.\
BB -> Red diode.\
CC -> IR diode.\
DD -> Green diode.\
EE -> BPM.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---

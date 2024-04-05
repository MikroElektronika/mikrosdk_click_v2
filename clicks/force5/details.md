
---
# Force 5 click

> Force 5 Click is a compact add-on board that contains a stable and flexible compensated/amplified micro force sensor. This board features the FMAMSDXX025WC2C3, a piezoresistive-based force sensors offering a digital output for reading force over the specified full-scale force span and a temperature range from Honeywell Sensing and Productivity Solutions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/force5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/force-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Force5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Force5 Click driver.

#### Standard key functions :

- `force5_cfg_setup` Config Object Initialization function.
```c
void force5_cfg_setup ( force5_cfg_t *cfg );
```

- `force5_init` Initialization function.
```c
err_t force5_init ( force5_t *ctx, force5_cfg_t *cfg );
```

#### Example key functions :

- `force5_calibration` Calibration the sensor function.
```c
uint8_t force5_calibration ( force5_t *ctx, force5_calibration_t *calib_data );
```

- `force5_get_force` Get force function.
```c
float force5_get_force ( force5_t *ctx, force5_calibration_t calib_data );
```

- `force5_get_temperature` Get temperature function.
```c
float force5_get_temperature ( force5_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the Force 5 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C, calibration the device, display diagnostic states and temperature.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    force5_cfg_t force5_cfg;  /**< Click config object. */

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
    force5_cfg_setup( &force5_cfg );
    FORCE5_MAP_MIKROBUS( force5_cfg, MIKROBUS_1 );
    err_t init_flag = force5_init( &force5, &force5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      Calibration... \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    
    status = force5_calibration( &force5, &calib_data );
    Delay_ms ( 100 );
    
    log_printf( &logger, "      Completed \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    log_printf( &logger, "      Diagnostic States: \r\n" );
    if ( status == FORCE5_STATES_NORMAL_OPERATION ) {
        log_printf( &logger, "    Normal Operation \r\n" );
    }
    if ( status == FORCE5_STATES_COMMAND_MODE ) {
        log_printf( &logger, "      Command Mode \r\n" );
    }
    if ( status == FORCE5_STATES_STALE_DATA ) {
        log_printf( &logger, "       Stale Data \r\n" );
    }
    if ( status == FORCE5_STATES_DIAGNOSTIC_CONDITION ) {
        log_printf( &logger, "   Diagnostic Condition \r\n" );
    }
    log_printf( &logger, "-------------------------\r\n" );
    
    temperature = force5_get_temperature( &force5 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    log_printf( &logger, "-------------------------\r\n" );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Force 5 Click board is measuring force ( N ). All data logs write on USB uart changes every 500 milliseconds.

```c

void application_task ( void ) {
    force_n = force5_get_force( &force5, calib_data );
    log_printf( &logger, " Force : %.4f N \r\n", force_n );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 500 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Force5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

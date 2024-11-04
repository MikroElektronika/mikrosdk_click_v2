\mainpage Main Page

---
# Thermo 27 Click

> Thermo 27 Click is a compact add-on board that accurately measures temperature. This board features the TMP114, a high-accuracy digital temperature sensor from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo27_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-27-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo 27 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 27 Click driver.

#### Standard key functions :

- `thermo27_cfg_setup` Config Object Initialization function.
```c
void thermo27_cfg_setup ( thermo27_cfg_t *cfg );
```

- `thermo27_init` Initialization function.
```c
err_t thermo27_init ( thermo27_t *ctx, thermo27_cfg_t *cfg );
```

- `thermo27_default_cfg` Click Default Configuration function.
```c
err_t thermo27_default_cfg ( thermo27_t *ctx );
```

#### Example key functions :

- `thermo27_write_register` Thermo 27 register writing function.
```c
err_t thermo27_write_register ( thermo27_t *ctx, uint8_t reg, uint16_t data_in );
```

- `thermo27_get_device_id` Thermo 27 get device id function.
```c
err_t thermo27_get_device_id ( thermo27_t *ctx, uint16_t *device_id );
```

- `thermo27_read_temp` Thermo 27 get read temperature function.
```c
err_t thermo27_read_temp ( thermo27_t *ctx, float *temp_out );
```

## Example Description

> This example demonstrates the use of Thermo 27 Click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and reads the device id, and after that resets the device and performs default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo27_cfg_t thermo27_cfg;  /**< Click config object. */

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
    thermo27_cfg_setup( &thermo27_cfg );
    THERMO27_MAP_MIKROBUS( thermo27_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo27_init( &thermo27, &thermo27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t device_id;
    thermo27_get_device_id( &thermo27, &device_id );
    if ( THERMO27_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( THERMO27_ERROR == thermo27_default_cfg( &thermo27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
   
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ======================= \r\n");
}

```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART at a rate of once per second.

```c

void application_task ( void ) 
{
    float temperature;
    uint8_t status;
    
    thermo27_get_alert_reg( &thermo27, &status );
    if ( THERMO27_DATA_READY_FLAG & status )
    {
        thermo27_read_temp( &thermo27, &temperature );
        log_printf( &logger, " Temperature: %f degC \r\n", temperature );
        log_printf( &logger, " ======================= \r\n");
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo27

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

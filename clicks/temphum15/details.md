---
# Temp&Hum 15 click

> Temp&Hum 15 Click is a compact add-on board that contains the 4th generation of best-in-class SHT humidity sensing solution from Sensirion. This board features the SHT40, a high-accuracy ultra-low-power 16-bit relative humidity, and temperature sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum15_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/blog/temphum-15-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum15 Click driver.

#### Standard key functions :

- `temphum15_cfg_setup` Config Object Initialization function.
```c
void temphum15_cfg_setup ( temphum15_cfg_t *cfg );
```

- `temphum15_init` Initialization function.
```c
TEMPHUM15_RETVAL temphum15_init ( temphum15_t *ctx, temphum15_cfg_t *cfg );
```

- `temphum15_default_cfg` Click Default Configuration function.
```c
void temphum15_default_cfg ( temphum15_t *ctx );
```

#### Example key functions :

- `temphum15_get_temp_and_hum` This function reads temperature and humidity with the power consumption based on the precision mode selected.
```c
err_t temphum15_get_temp_and_hum ( temphum15_t *ctx, uint8_t precision_mode, float *temp_val, float *hum_val );
```

- `temphum15_soft_reset` This function sends soft reset command to the sensor.
```c
err_t temphum15_soft_reset ( temphum15_t *ctx );
```

- `temphum15_read_serial` This function reads unique serial number of the sensor.
```c
err_t temphum15_read_serial ( temphum15_t *ctx, uint32_t *serial_number );
```

## Example Description

> This demo app represents the performance of the Temp&Hum 15 click board. The log displays the temperature and humidity obtained from the sensor.

**The demo application is composed of two sections :**

### Application Init

> Initialization of UART LOG and I2C drivers. The application also performs reset upon init.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    temphum15_cfg_t temphum15_cfg;  /**< Click config object. */

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

    temphum15_cfg_setup( &temphum15_cfg );
    TEMPHUM15_MAP_MIKROBUS( temphum15_cfg, MIKROBUS_1 );
    err_t init_flag = temphum15_init( &temphum15, &temphum15_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    Delay_ms( 100 );
    temphum15_default_cfg( &temphum15 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

```

### Application Task

 > Temperature and humidity data are being acquired every two seconds. If the acquisition fails, LOG states that no data is available.

```c

void application_task ( void ) {
    err_t status_data;
    
    status_data = temphum15_get_temp_and_hum( &temphum15, TEMPHUM15_MODE_HIGH_PRECISION, &temperature, &humidity );
    if ( status_data == TEMPHUM15_SUCCESS ) {
        log_printf( &logger, "----------------------------\r\n" );
        log_printf( &logger, "> Temperature : %.2f C\r\n", temperature );
        log_printf( &logger, "> Humidity: %.2f %RH\r\n", humidity );
    } else {
        log_printf( &logger, "----------------------------\r\n" );
        log_printf( &logger, "> No data\r\n" );
    }
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---


---
# Compass 5 click

> Compass 5 Click is a compact add-on board that contains a 3-axis magnetometer device suitable for compass application. This board features the AK09918C, a 3-axis electronic compass with high sensitive Hall sensor technology from AKM Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/compass-5-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Compass5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Compass5 Click driver.

#### Standard key functions :

- `compass5_cfg_setup` Config Object Initialization function.
```c
void compass5_cfg_setup ( compass5_cfg_t *cfg );
```

- `compass5_init` Initialization function.
```c
err_t compass5_init ( compass5_t *ctx, compass5_cfg_t *cfg );
```

#### Example key functions :

- `compass5_write_byte` This function writes a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
void compass5_write_byte ( compass5_t *ctx, uint8_t reg, uint8_t tx_data );
```

- `compass5_read_byte` This function read 1 byte.
```c
uint8_t compass5_read_byte ( compass5_t *ctx, uint8_t reg );
```

- `compass5_sw_reset` This function for software reset.
```c
void compass5_sw_reset ( compass5_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of Compass 5 Click board that reads data 
from magnetic sensors for X, Y, and Z axes,processes it and displays it via the UART terminal.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C and starts to write log, performs power down mode, sets continuous measurement mode; also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                /**< Logger config object. */
    compass5_cfg_t compass5_cfg;      /**< Click config object. */

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
    Delay_ms ( 100 );
    
    // Click initialization.
    compass5_cfg_setup( &compass5_cfg );
    COMPASS5_MAP_MIKROBUS( compass5_cfg, MIKROBUS_1 );
    err_t init_flag = compass5_init( &compass5, &compass5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    compass5_sw_reset( &compass5 );
    Delay_ms ( 500 );
    
    compass5_get_id( &compass5, &company_id, &device_id );
    
    if  ( ( company_id == COMPASS5_COMPANI_ID_NUM ) && ( device_id == COMPASS5_DEVICE_ID_NUM ) ) {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "  Compass 3 click   \r\n" );
        log_printf( &logger, "--------------------\r\n" );
    }
    else {
        log_printf( &logger, "   Fatal error!!!   \r\n" );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, "  Power Down Mode  \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    compass5_set_operation_mode( &compass5, COMPASS5_MODE_POWER_DOWN );
    Delay_ms ( 100 );

    log_printf( &logger, "    Continuous     \r\n" );
    log_printf( &logger, " Measurement Mode  \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    compass5_set_operation_mode( &compass5, COMPASS5_MODE_CON_MEASUREMENT_100HZ );
    Delay_ms ( 100 );

    log_printf( &logger, " Start Measurement \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> When Compass 5 click is connected to a mikroBUS, this example collects data on the current position of the X, 
Y and Z axes via I2C communication, processes and displays the data via the UART terminal. All axis data is printed every 2 seconds.

```c

void application_task ( void ) {
    int16_t x_val;
    int16_t y_val;
    int16_t z_val;
    
    if ( compass5_check_data_ready( &compass5 ) == COMPASS5_DATA_READY ) {
        compass5_measurement_axis( &compass5, &x_val, &y_val, &z_val );
        Delay_ms ( 10 );
    
        log_printf( &logger, " X-axis: %d mG\r\n", x_val );
        log_printf( &logger, " Y-axis: %d mG\r\n", y_val );
        log_printf( &logger, " Z-axis: %d mG\r\n", z_val );        
        log_printf( &logger,  "--------------------\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

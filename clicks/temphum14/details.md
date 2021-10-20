
---
# TempHum 14 click

Temp & Hum 14 Click is a compact add-on board that contains one of the smallest and most accurate humidity and temperature sensors on the market. This board features the HTU31D, a highly accurate digital relative humidity sensor with temperature output from TE Connectivity. With power consumption down to 3.78μW and accuracy of ±2%RH and ±0.2°C, this Click board™ provides fast response time, precision measurement, low hysteresis, and sustained performance even when exposed to extreme temperature up to 125°C and humidity environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temphum-14-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum14 Click driver.

#### Standard key functions :

- `temphum14_cfg_setup` Config Object Initialization function.
```c
void temphum14_cfg_setup ( temphum14_cfg_t *cfg );
```

- `temphum14_init` Initialization function.
```c
err_t temphum14_init ( temphum14_t *ctx, temphum14_cfg_t *cfg );
```

#### Example key functions :

- `temphum14_set_conversion` The function set conversion a single temperature and humidity conversion and select data resolution to the HTU31D RH/T SENSOR IC Digital Relative Humidity sensor with Temperature output on the Temp-Hum 14 click board.
```c
void temphum14_set_conversion ( temphum14_t *ctx, uint8_t hum_osr, uint8_t temp_osr );
```

- `temphum14_read_t_and_rh` The function read temperature and humidity data of the HTU31D RH/T SENSOR IC Digital Relative Humidity sensor with Temperature output on the Temp-Hum 14 click board.
```c
void temphum14_read_t_and_rh ( temphum14_t *ctx, uint8_t *p_rx_data );
```

- `temphum14_get_temp_and_hum` The function get temperature and humidity value of the HTU31D RH/T SENSOR IC Digital Relative Humidity sensor with Temperature output on the Temp-Hum 14 click board.
```c
void temphum14_get_temp_and_hum ( temphum14_t *ctx, float *temp, float *hum );
```

## Example Description

> This is an example that demonstrates the use of the Temp-Hum 14 Click board. Temp-Hum 14 Click board can be used to measure temperature and relative humidity. All data logs write on USB uart changes every 3 sec.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables I2C, and hardware reset the device and read the serial number.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum14_cfg_t temphum14_cfg;  /**< Click config object. */

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
    log_printf( &logger, "-----------------------------\r\n" );
    log_info( &logger, " Application Init " );
    log_printf( &logger, "-----------------------------\r\n" );

    // Click initialization.
    temphum14_cfg_setup( &temphum14_cfg );
    TEMPHUM14_MAP_MIKROBUS( temphum14_cfg, MIKROBUS_1 );
    err_t init_flag = temphum14_init( &temphum14, &temphum14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 100 );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Hardware Reset \r\n" );
    temphum14_hw_reset( &temphum14 );
    Delay_ms( 100 );
    
    ser_numb = temphum14_get_serial_number( &temphum14 );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Serial Number : %lu \r\n", ser_numb );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Software Reset \r\n" );
    temphum14_soft_reset( &temphum14 );
    Delay_ms( 100 );
    
    temphum14_get_diagnostic( &temphum14, &status_data );
    Delay_ms( 10 );

    display_diagnostic( );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
}

```

### Application Task

> Reading temperature and humidity, and loging it on the USB uart. 

```c

void application_task ( void ) {
    temphum14_set_conversion( &temphum14, TEMPHUM14_CONVERSION_HUM_OSR_0_020, TEMPHUM14_CONVERSION_TEMP_0_040 );
    Delay_ms( 10 );
    
    temphum14_get_temp_and_hum( &temphum14, &temperature, &humidity );
    Delay_ms( 10 );
    
    log_printf( &logger, "  Temperature : %.2f C \r\n", temperature );
    log_printf( &logger, "  Humidity    : %.2f %% \r\n", humidity );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 3000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

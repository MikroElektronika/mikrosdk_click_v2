
---
# Heart Rate 7 click

> Heart Rate 7 click is an optical biosensor Click board™ which can be used for heart-rate monitoring (HRM). This Click board™ employs a very sensitive analog front-end IC with high dynamic range, which ensures accurate and reliable readings. This analog front-end IC is coupled with the optical front end, which consists of a sensitive photo-diode (PD) and two high brightness green LEDs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heart-rate-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Heart Rate 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Heart Rate 7 Click driver.

#### Standard key functions :

- `heartrate7_cfg_setup` Config Object Initialization function.
```c
void heartrate7_cfg_setup ( heartrate7_cfg_t *cfg );
```

- `heartrate7_init` Initialization function.
```c
err_t heartrate7_init ( heartrate7_t *ctx, heartrate7_cfg_t *cfg );
```

- `heartrate7_default_cfg` Click Default Configuration function.
```c
err_t heartrate7_default_cfg ( heartrate7_t *ctx );
```

#### Example key functions :

- `heartrate7_write_reg` Heart Rate 7 register write function.
```c
void heartrate7_write_reg( heartrate7_t *ctx, uint8_t reg_addr, uint32_t write_data ); 
```

- `heartrate7_read_reg` Heart Rate 7 register reading function.
```c
uint32_t heartrate7_read_reg( heartrate7_t *ctx, uint8_t reg_addr ); 
```

- `heartrate7_sw_reset` Heart Rate 7 software reset function.
```c
void heartrate7_sw_reset( heartrate7_t *ctx );
```

## Example Description

> This example showcases ability for device to read Heart Rate 7 Click Board.

**The demo application is composed of two sections :**

### Application Init

> Configures the micro controller for communication and initializes the click board. 

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate7_cfg_t heartrate7_cfg;  /**< Click config object. */

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
    heartrate7_cfg_setup( &heartrate7_cfg );
    HEARTRATE7_MAP_MIKROBUS( heartrate7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate7_init( &heartrate7, &heartrate7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE7_ERROR == heartrate7_default_cfg ( &heartrate7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This section shows how the data is processed and sent to the MikroPlot application.

```c
void application_task ( void ) 
{
    sensor_value = heartrate7_get_aled1_val( &heartrate7 );
    log_printf( &logger, "%lu,%lu \r\n", sensor_value, time );
    time += 10;
    Delay_ms( 10 );
}
```

## Note

> For testing this example application SerialPlot was used. 
> There you can see heart rate graphicly shown.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

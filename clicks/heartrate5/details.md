
---
# Heart Rate 5 Click

> Heart Rate 5 Click is the optical biosensor Click board™ which can be used for the heart-rate monitoring (HRM), as well as the peripheral capillary oxygen saturation monitoring (SpO2). This Click board™ employs a very sensitive analog front-end IC with high dynamic range, which ensures accurate and reliable readings. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/heart-rate-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Heart Rate 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Heart Rate 5 Click driver.

#### Standard key functions :

- `heartrate5_cfg_setup` Config Object Initialization function.
```c
void heartrate5_cfg_setup ( heartrate5_cfg_t *cfg );
```

- `heartrate5_init` Initialization function.
```c
err_t heartrate5_init ( heartrate5_t *ctx, heartrate5_cfg_t *cfg );
```

- `heartrate5_default_cfg` Click Default Configuration function.
```c
err_t heartrate5_default_cfg ( heartrate5_t *ctx );
```

#### Example key functions :

- `heartrate5_write_reg` Heart Rate 5 register write function.
```c
void heartrate5_write_reg( heartrate5_t *ctx, uint8_t reg_addr, uint32_t write_data ); 
```

- `heartrate5_read_reg` Heart Rate 5 register reading function.
```c
uint32_t heartrate5_read_reg( heartrate5_t *ctx, uint8_t reg_addr ); 
```

- `heartrate5_sw_reset` Heart Rate 5 software reset function.
```c
void heartrate5_sw_reset( heartrate5_t *ctx );
```

## Example Description

> This example showcases ability for device to read Heart Rate 5 Click Board

**The demo application is composed of two sections :**

### Application Init

> Configures the micro controller for communication and initializes the Click board. 

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate5_cfg_t heartrate5_cfg;  /**< Click config object. */

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
    heartrate5_cfg_setup( &heartrate5_cfg );
    HEARTRATE5_MAP_MIKROBUS( heartrate5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate5_init( &heartrate5, &heartrate5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE5_ERROR == heartrate5_default_cfg ( &heartrate5 ) )
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
    if( heartrate5_get_led2_aled2_val( &heartrate5 ) < 10 )
    {
        sensor_value = heartrate5_get_aled1_val( &heartrate5 );
        log_printf( &logger, "%lu,%lu \r\n", sensor_value, time );
        time += 10;
        Delay_ms ( 10 );
    }
}
```

## Note

> For testing this example application SerialPlot was used. 
> There you can see heart rate graphicly shown.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

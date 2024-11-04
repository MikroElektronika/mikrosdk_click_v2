\mainpage Main Page

---
# Air Quality 8 Click

> Air quality 8 Click is a compact add-on board containing a best-in-class air-quality sensing solution. This board features the ZMOD4510, a fully calibrated digital sensor solution that detects air quality in various indoor and outdoor applications from Renesas. The ZMOD4510 comes with selective ozone measurement capabilities, offering visibility into the air quality in users' environments for a personalized experience. This Click board™ is an I2C configurable and characterized by outstanding long-term stability and lifetime. Many additional features such as low power consumption, wide NO2 and O3 detection range, and high sensitivity make this Click board™ an excellent choice for detecting unhealthy conditions in outdoor air, such as personal air-quality monitor, HVAC, and other various air quality-related applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airquality8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/air-quality-8-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the AirQuality8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AirQuality8 Click driver.

#### Standard key functions :

- `airquality8_cfg_setup` Config Object Initialization function.
```c
void airquality8_cfg_setup ( airquality8_cfg_t *cfg );
```

- `airquality8_init` Initialization function.
```c
err_t airquality8_init ( airquality8_t *ctx, airquality8_cfg_t *cfg );
```

- `airquality8_default_cfg` Click Default Configuration function.
```c
err_t airquality8_default_cfg ( airquality8_t *ctx );
```

#### Example key functions :

- `airquality8_calc_oaq` Air Quality 8 calculates AQI function.
```c
float airquality8_calc_oaq ( float *rmox, uint8_t rcda_strategy, uint8_t gas_detection_strategy );
```

- `airquality8_read_rmox` Air Quality 8 calculate rmox resistance function.
```c
err_t airquality8_read_rmox ( airquality8_t *ctx, float *rmox, uint16_t mox_lr, uint16_t mox_er );
```

- `airquality8_start_measurement` Air Quality 8 start measurement function.
```c
err_t airquality8_start_measurement ( airquality8_t *ctx );
```

## Example Description

> This library contains API for Air Quality 8 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 
> The library also includes a function for configuring sensor and measurement, 
> read and calculate mox resistance ( RMOX ) and air quality index ( AQI ), etc.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART, and additional pins.
> After the driver inits and executes a default configuration, 
> the app read product ID and configuration parameters, 
> initializes the sensor and measurement.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality8_cfg_t airquality8_cfg;  /**< Click config object. */

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
    airquality8_cfg_setup( &airquality8_cfg );
    AIRQUALITY8_MAP_MIKROBUS( airquality8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == airquality8_init( &airquality8, &airquality8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRQUALITY8_ERROR == airquality8_default_cfg ( &airquality8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    static uint8_t cfg_data[ 6 ];
    static uint8_t prod_data[ 5 ];
    static uint16_t pid;
    
    airquality8_get_sensor_info( &airquality8, &cfg_data[ 0 ], &prod_data[ 0 ], &pid );
    
    if ( pid != AIRQUALITY8_PRODUCT_ID )
    {
        status_flag = AIRQUALITY8_ERROR_I2C;
        display_error( );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, " Product ID : 0x%.2X  \r\n", pid );
    Delay_ms ( 100 );
    
    airquality8_init_sensor( &airquality8, &mox_lr, &mox_er );
    Delay_ms ( 10 );
    
    airquality8_init_measurement( &airquality8 );
    Delay_ms ( 10 );
    
    log_printf( &logger, "---------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Air Quality Index\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Air Quality 8 Click board™.
> In this example, the app performs the start of the measurement,
> reads an array of the 15 mox resistances measurements ( RMOX ), 
> and calculates the air quality index ( AQI ), the app also, displays if an error occurs.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{   
    static uint8_t status_data;
    static float rmox;
    static float rmox_seq[ 15 ];
    static float aqi;
    
    status_flag = airquality8_start_measurement( &airquality8 );

    airquality8_get_status( &airquality8, &status_data );
    Delay_ms ( 10 );
    
    while ( ( status_data & AIRQUALITY8_STATUS_LAST_SEQ_STEP_MASK ) != AIRQUALITY8_OK )
    {
        airquality8_get_status( &airquality8, &status_data );
        Delay_ms ( 10 );
    }

    for ( uint8_t n_cnt = 0; n_cnt < 15; n_cnt++ )
    {        
        status_flag = airquality8_read_rmox( &airquality8, &rmox, mox_lr, mox_er );
        rmox_seq[ n_cnt ] = rmox;
        Delay_ms ( 100 ); 
        
        if ( status_flag != AIRQUALITY8_OK )
        {
            display_error( );
        }
    }       
    
    aqi = airquality8_calc_oaq( rmox_seq, AIRQUALITY8_RCDA_STRATEGY_ADJ, AIRQUALITY8_GAS_DETECTION_STRATEGY_AUTO );
    log_printf( &logger, " \tAQI : %.3f \r\n", aqi );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

## Additional Function
- `display_error` This function displays error messages.
```c
static void display_error ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

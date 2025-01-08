
---
# Air Quality 8 Click

> [Air Quality 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4904) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4904&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Air Quality 8 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 
> The library also includes a function for configuring sensor and measurement, 
> read and calculate mox resistance ( RMOX ) and air quality index ( AQI ), etc.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality8

### Example Key Functions

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

> This is an example that demonstrates the use of the Air Quality 8 Click board&trade;.
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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---

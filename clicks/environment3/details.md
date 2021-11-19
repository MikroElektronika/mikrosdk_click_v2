
---
# Environment 3 click

Environment 3 Click is a compact add-on board that contains a four-in-one environmental measurement solution. This board features BME688, a first gas sensor with Artificial Intelligence (AI), and integrated high-linearity/high-accuracy pressure, humidity, and temperature sensors from Bosch Sensortech. The BME688 can detect Volatile Organic Compounds (VOCs), Volatile Sulfur Compounds (VSCs), and other gases such as carbon monoxide and hydrogen in part per billion (ppb) range. It provides absolute temperature accuracy, typical of ±1°C, and best performance when operated within the pressure, temperature, and humidity range of 300-110hPa, 0-65°C, and 10-90%RH.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/enviroment3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/environment-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Environment3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Environment3 Click driver.

#### Standard key functions :

- `environment3_cfg_setup` Config Object Initialization function.
```c
void environment3_cfg_setup ( environment3_cfg_t *cfg );
```

- `environment3_init` Initialization function.
```c
err_t environment3_init ( environment3_t *ctx, environment3_cfg_t *cfg );
```

- `environment3_default_cfg` Click Default Configuration function.
```c
err_t environment3_default_cfg ( environment3_t *ctx );
```

#### Example key functions :

- `environment3_get_all_data` This function reads the temperature, humidity, pressure, and gas resistance data from the sensor.
```c
int8_t environment3_get_all_data ( environment3_t *ctx, float *temp, float *hum, float *pres, uint32_t *gas );
```

- `environment3_enable_heater` This function enables or disables the gas sensor heater.
```c
int8_t environment3_enable_heater ( environment3_t *ctx, uint8_t state );
```

- `environment3_soft_reset` This function soft-resets the sensor.
```c
int8_t environment3_soft_reset ( environment3_t *ctx );
```

## Example Description

> This example demonstrates the use of Environment 3 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, sets the default configuration, and disables the gas sensor heater.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    environment3_cfg_t environment3_cfg;  /**< Click config object. */

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

    environment3_cfg_setup( &environment3_cfg );
    ENVIRONMENT3_MAP_MIKROBUS( environment3_cfg, MIKROBUS_1 );
    err_t init_flag  = environment3_init( &environment3, &environment3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( ENVIRONMENT3_OK != environment3_default_cfg ( &environment3 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    environment3_enable_heater ( &environment3, ENVIRONMENT3_DISABLE );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature, humidity, pressure, and gas resistance data from the sensor and 
> displays all values on the USB UART approximately every second.

```c

void application_task ( void )
{
    float temperature, pressure, humidity;
    uint32_t gas_resistance;
    if ( ENVIRONMENT3_OK == environment3_get_all_data ( &environment3, 
                                                        &temperature, 
                                                        &humidity, 
                                                        &pressure, 
                                                        &gas_resistance ) )
    {
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    
        log_printf( &logger, " Humidity : %.2f %%\r\n", humidity );
        
        log_printf( &logger, " Pressure : %.3f mBar\r\n", pressure );
        
        if ( ENVIRONMENT3_ENABLE == environment3.gas_sett.enable )
        {
            log_printf( &logger, " Gas Resistance : %ld Ohms\r\n", gas_resistance );
            log_printf( &logger, "--------------------------------\r\n" );
        }
        else
        {
            log_printf( &logger, "--------------------------------\r\n" );
            Delay_ms( 1000 );
        }
    }
}

```

## Note

> The heater is disabled by default, enable it in the Application Init if you need gas resistance data.
> Gas resistance data is RAW data, if you need VOCs, please contact Bosch Sensortec for VOC calculation library.
> The temperature and humidity data don't represent the real environmental data when the heater is enabled.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

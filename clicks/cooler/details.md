
---
# Cooler Click

> Cooler Click is a compact add-on board designed as a cooling solution to manage heat in electronic systems efficiently. This board features the DRV8213, a brushless DC motor driver from Texas Instruments, ensuring a high-performance operation. This board also directly integrates a TMP007 temperature sensor and an MF25060V2-1000U-A99 cooling fan onto its platform, offering a compact and ready-to-use cooling system. It operates across a wide PWM frequency range from 0 to 100kHz, supports both 3.3V and 5V logic levels, and features several protection mechanisms, including undervoltage lockout, overcurrent protection, and overtemperature shutdown.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/cooler_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/cooler-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Cooler Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Cooler Click driver.

#### Standard key functions :

- `cooler_cfg_setup` Config Object Initialization function.
```c
void cooler_cfg_setup ( cooler_cfg_t *cfg );
```

- `cooler_init` Initialization function.
```c
err_t cooler_init ( cooler_t *ctx, cooler_cfg_t *cfg );
```

- `cooler_default_cfg` Click Default Configuration function.
```c
err_t cooler_default_cfg ( cooler_t *ctx );
```

#### Example key functions :

- `cooler_get_object_temperature` This function reads the object's temperature data in degrees Celsius.
```c
err_t cooler_get_object_temperature ( cooler_t *ctx, float *temperature );
```

- `cooler_set_out_state` This function controls the operation of the cooler - on/off.
```c
err_t cooler_set_out_state ( cooler_t *ctx, cooler_out_state_t out_state );
```

## Example Description

> This example demonstrates the use of the Cooler Click board
 by reading the target object temperature and controlling the cooler.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART, and additional pins.
 After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cooler_cfg_t cooler_cfg;  /**< Click config object. */

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
    cooler_cfg_setup( &cooler_cfg );
    COOLER_MAP_MIKROBUS( cooler_cfg, MIKROBUS_1 );
    err_t init_flag = cooler_init( &cooler, &cooler_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COOLER_ERROR == cooler_default_cfg ( &cooler ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application measures the temperature of the target object in degrees Celsius
 and enables a cooler if the temperature exceeds the temperature high limit value. 
 Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float temperature = 0;
    if ( COOLER_OK == cooler_get_object_temperature( &cooler, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf( &logger, " Cooler: " );
        if ( COOLER_TEMP_HIGH_LIMIT < temperature )
        {
            if ( COOLER_OK == cooler_set_out_state( &cooler, COOLER_ENABLE ) )
            {
                log_printf( &logger, " Enabled.\r\n\n" );
            }
        }
        else
        {
            if ( COOLER_OK == cooler_set_out_state( &cooler, COOLER_DISABLE ) )
            {
                log_printf( &logger, " Disabled.\r\n\n" );
            }
        }
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Cooler

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

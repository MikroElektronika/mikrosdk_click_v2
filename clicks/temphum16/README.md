\mainpage Main Page

---
# Temp&Hum 16 Click

Temp&Hum 16 Click is a compact add-on board that represents temperature and humidity sensing solutions. This board features the WSEN-HIDS (2525020210001), a MEMS-based capacitive humidity sensor with an integrated ASIC and I2C and SPI serial communication from Würth Elektronik. A silicon-based temperature sensor is also integrated within the same package. ASIC contains the multiplier, operational amplifier, analog-to-digital converter, and other signal conditioning blocks like controller logics and interrupts. It converts the analog signal from humidity and temperature sensing elements into 16-bit digital humidity and temperature values. The 2525020210001 is factory calibrated for both humidity and temperature measurements with no further calibration required. This Click board™ is an ideal solution to be used in various temperature and humidity-related applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-16-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the TempHum16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum16 Click driver.

#### Standard key functions :

- `temphum16_cfg_setup` Config Object Initialization function.
```c
void temphum16_cfg_setup ( temphum16_cfg_t *cfg );
```

- `temphum16_init` Initialization function.
```c
TEMPHUM16_RETVAL temphum16_init ( temphum16_t *ctx, temphum16_cfg_t *cfg );
```

- `temphum16_default_cfg` Click Default Configuration function.
```c
void temphum16_default_cfg ( temphum16_t *ctx );
```

#### Example key functions :

- `temphum16_check_ready` Temp&Hum 16 check ready function.
```c
uint8_t temphum16_check_ready ( temphum16_t *ctx );
```

- `temphum16_get_humidity` Temp&Hum 16 get humidity function.
```c
err_t temphum16_get_humidity ( temphum16_t *ctx, float *humidity );
```

- `temphum16_get_temperature` Temp&Hum 16 get temperature function.
```c
err_t temphum16_get_temperature ( temphum16_t *ctx, float *temperature );
```

## Example Description

> This library contains API for the Temp&Hum 16 Click driver.
> This demo application shows an example of 
> humidity and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI or I2C module and log UART.
> After driver initialization and default settings, 
> the app display retrieves the sensor parameters 
> such as temperature and humidity.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    temphum16_cfg_t temphum16_cfg;  /**< Click config object. */

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

    temphum16_cfg_setup( &temphum16_cfg );
    TEMPHUM16_MAP_MIKROBUS( temphum16_cfg, MIKROBUS_1 );
    err_t init_flag  = temphum16_init( &temphum16, &temphum16_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) {
        log_info( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    temphum16_default_cfg ( &temphum16 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );

    temphum16_get_device_id( &temphum16, &device_id );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Check communication  \r\n" ); 
    if ( device_id == TEMPHUM16_DEVICE_ID ){
        log_printf( &logger, "      Successful   \r\n" );    
    } else {
        log_printf( &logger, "        Failed     \r\n" );
        
        for ( ; ; );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   Start measurements  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

```

### Application Task

> This is an example that shows the use of a Temp&Hum 16 Click board™.
> Logs humidity [ % ] and temperature [ degree Celsius ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    if ( temphum16_check_ready( &temphum16 ) == TEMPHUM16_DRDY ) {
        temphum16_get_temperature( &temphum16, &temperature );
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature ); 
        
        temphum16_get_humidity( &temphum16, &humidity );
        log_printf( &logger, " Humidity    : %.2f %%\r\n", humidity ); 
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

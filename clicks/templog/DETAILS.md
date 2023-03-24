

---
# Temp-Log click

Temp-Log click is a precise ambient temperature measurement device, equipped with 8Kbit (1024 bytes) of EEPROM memory, which can be used to permanently store system configuration or log application specific or user preference data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/templog_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-log-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempLog Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempLog Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void templog_cfg_setup ( templog_cfg_t *cfg ); 
 
- Initialization function.
> TEMPLOG_RETVAL templog_init ( templog_t *ctx, templog_cfg_t *cfg );

- Click Default Configuration function.
> void templog_default_cfg ( templog_t *ctx );


#### Example key functions :

- This function reads decimal value of temp.
> uint16_t temp_log_read_temp_dec ( templog_t *ctx, uint16_t resolution);
 
- This function converts temperature data to celsius value.
> float temp_log_convert_to_celsius ( uint16_t temperature_data);

- This function alerts user if temperature limit is alarming.
> uint8_t temp_log_get_alert ( templog_t *ctx);

## Examples Description

> This example returns values of the temperature from the sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes click driver. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    templog_cfg_t cfg;

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
    templog_cfg_setup ( &cfg );    
    TEMPLOG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( TEMPLOG_OK != templog_init ( &templog, &cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    templog_default_cfg ( &templog );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads temperature from temperature register in decimal value in 9-bit resolution,
> converts that decimal value in celsius value and checks Alert pin witch goes active (low)
> if the measured temperature meets or exceeds the high temperature limit.

```c

void application_task ( void )
{
    uint16_t temp_in_dec = 0;
    float temp_in_cels = 0;
    
    temp_in_dec = temp_log_read_temp_dec(&templog, TEMP_LOG_RESOLUTION_9_BITS);
    temp_in_cels = temp_log_convert_to_celsius(temperature);
    
    log_printf(&logger, "Temperature in decimal value is: %d\n", temp_in_dec);
    log_printf(&logger, "Temperature in celsius value is: %f\n", temp_in_cels);

    if(temp_log_get_alert(&templog) == 0)
    {
        log_printf( &logger, "TEMPERATURE LIMIT ALARMING!\r\n" );
    }
    
    Delay_ms(1000);
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

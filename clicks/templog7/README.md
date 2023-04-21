\mainpage Main Page

---
# Temp-Log 7 click

> Temp-Log 7 Click is a compact add-on board used to measure and record the temperature of an environment over time. This board features the TMP1826, a high-accuracy, 1-Wire® compatible digital output temperature sensor from Texas Instruments with integrated 2-kbit EEPROM. It supports a wide operating temperature range from –20°C to +85°C with its high accuracy of ±0.1°C (typical)/±0.3°C (maximum) and comes with a factory-programmed 64-bit unique identification number for addressing and NIST traceability. Besides a programmable alarm function that outputs an interrupt signal to the MCU when a specific temperature event occurs, it also has three digital I/O pins configurable for general purposes or to identify the device's position on a shared bus.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/templog7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-log-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : One Wire type


# Software Support

We provide a library for the Temp-Log 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Temp-Log 7 Click driver.

#### Standard key functions :

- `templog7_cfg_setup` Config Object Initialization function.
```c
void templog7_cfg_setup ( templog7_cfg_t *cfg );
```

- `templog7_init` Initialization function.
```c
err_t templog7_init ( templog7_t *ctx, templog7_cfg_t *cfg );
```

- `templog7_default_cfg` Click Default Configuration function.
```c
err_t templog7_default_cfg ( templog7_t *ctx );
```

#### Example key functions :

- `templog7_read_temperature` This function starts the one shot measurement and reads the temperature value in Celsius.
```c
err_t templog7_read_temperature ( templog7_t *ctx, float *temperature );
```

- `templog7_write_eeprom` This function writes a desired number of data bytes to the EEPROM memory.
```c
err_t templog7_write_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len );
```

- `templog7_read_eeprom` This function reads a desired number of data bytes from the EEPROM memory.
```c
err_t templog7_read_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );
```

## Example Description

> This example demonstrates the use of Temp-Log 7 click board by reading the temperature in Celsius,
then writing the specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which
clears the EEPROM memory, sets the temperature resolution to 16-bit, enables
alert interrupt and sets the temperature alerts to 5 degrees Celsius for low
and 40 degrees for high level. Other three IO pins are configured as INPUT.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    templog7_cfg_t templog7_cfg;  /**< Click config object. */

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
    templog7_cfg_setup( &templog7_cfg );
    TEMPLOG7_MAP_MIKROBUS( templog7_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == templog7_init( &templog7, &templog7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPLOG7_ERROR == templog7_default_cfg ( &templog7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature in degrees Celsius and the gpio state. After that writes
a desired number of bytes to the memory and then verifies if it is written
correctly by reading from the same memory location and displaying the memory
content. All data is displayed on the USB UART where you can track changes.

```c
void application_task ( void )
{
    uint8_t eeprom_data[ 64 ] = { 0 };
    uint8_t gpio_state = 0;
    float temperature = 0;
    if ( TEMPLOG7_OK == templog7_read_temperature ( &templog7, &temperature ) )
    {
        log_printf( &logger, "\r\n Temperature: %.2f C\r\n", temperature );
    }
    if ( TEMPLOG7_OK == templog7_read_gpio ( &templog7, &gpio_state ) )
    {
        log_printf( &logger, " GPIO state: 0x%.2X\r\n", ( uint16_t ) gpio_state );
    }
    if ( TEMPLOG7_OK == templog7_write_eeprom ( &templog7, STARTING_ADDRESS, DEMO_TEXT_MESSAGE, 
                                                    sizeof ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " EEPROM write: %s\r\n", ( uint8_t * ) DEMO_TEXT_MESSAGE );
    }
    if ( TEMPLOG7_OK == templog7_read_eeprom ( &templog7, STARTING_ADDRESS, eeprom_data, 
                                                   sizeof ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " EEPROM read: %s\r\n", eeprom_data );
    }
    if ( !templog7_get_alert_pin ( &templog7 ) )
    {
        log_info( &logger, " ALERT detected " );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

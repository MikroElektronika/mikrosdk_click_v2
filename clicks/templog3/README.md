\mainpage Main Page
 
---
# Temp-Log 3 click

Temp-Log 3 click is a temperature measuring Click board™ featuring the MCP9843 IC, an accurate temperature sensor IC with integrated EEPROM

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/templog3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-log-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the TempLog3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempLog3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void templog3_cfg_setup ( templog3_cfg_t *cfg ); 
 
- Initialization function.
> TEMPLOG3_RETVAL templog3_init ( templog3_t *ctx, templog3_cfg_t *cfg );

- Click Default Configuration function.
> void templog3_default_cfg ( templog3_t *ctx );


#### Example key functions :

- Set Temperature function
> uint8_t templog3_set_temp ( templog3_t *ctx, uint8_t temp_sel, float temp_in );
 
- EEPROM Single Write function
> void templog3_eeprom_byte_write ( templog3_t *ctx, uint8_t reg_addr, uint8_t data_in, uint8_t eeprom_mode );

- EEPROM Sequential Read function
> uint8_t templog3_eeprom_sequential_read ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint16_t num_bytes );

## Examples Description

> This application measures temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and performs a device default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    templog3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    templog3_cfg_setup( &cfg );
    TEMPLOG3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog3_init( &templog3, &cfg );

    Delay_ms ( 500 );
    
    templog3_default_cfg( &templog3 );
    
    Delay_ms ( 200 );

    log_printf( &logger, "** Temp-Log 3 click is initialized ** \r\n" );
}
  
```

### Application Task

> First ensures that the minimum conversion time is met, and then reads the
> ambient temperature calculated to the Celsius degrees, and logs the results to the USB UART.

```c

void application_task ( void )
{
    float temperature;
    uint8_t ret_status;

    templog3_wait_conv_done( &templog3 );

    ret_status = templog3_get_temp( &templog3, TEMPLOG3_TEMP_AMBIENT_REG, &temperature );

    log_printf( &logger, "**  Ambient temperature is : %.2f C  **\r\n", temperature );
    
    check_limit_status( ret_status );
    
    Delay_ms ( 300 );
}

```

## Note

> The temperature range that can be measured or written is from -40 to +125 Celsius degrees.
> The user can change the measured temperature resolution, but the range remains the same.
> The limit of the temperature resolution is always a 10bit, or 0.25 Celsius degrees.
> If user wants to enable the EEPROM Write Protection, the A0 pin on the device 
> must be set to the high voltage level.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog3

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

\mainpage Main Page
 
 

---
# Temp-Log 5 Click

Temp-Log 5 Click is a temperature measuring Click board™ featuring the CAT34TS02, an accurate temperature sensor IC with integrated Serial Presence Detect EEPROM. Temperature Sensor measures and store temperatures at least 10 times in second. Temperature measurement results can be retrieved by the host MCU via I2C interface, and are compared to critical limits stored into internal registers. It also features programmable event output function and supports three modes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/templog5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temp-log-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempLog5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempLog5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void templog5_cfg_setup ( templog5_cfg_t *cfg ); 
 
- Initialization function.
> TEMPLOG5_RETVAL templog5_init ( templog5_t *ctx, templog5_cfg_t *cfg );

- Click Default Configuration function.
> void templog5_default_cfg ( templog5_t *ctx );


#### Example key functions :

- This function write data to the EEPROM address
> void templog5_write_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_byte );

- This function read data to the EEPROM address.
> void templog5_read_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_byte );

- This function read from the TS register
> uint16_t templog5_read_data ( templog5_t *ctx, uint8_t reg );

## Examples Description

> Measures and stores temperatures values at least 10 times in second and logs it on terminal.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, tests comunication and EEPROM read/write and sets default configuration parameters.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    templog5_cfg_t cfg;
    uint16_t tmp;
    uint8_t ee_test_write[1];
    uint8_t ee_test_read[1];

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
    log_info( &logger, "Application Init" );

    //  Click initialization.

    templog5_cfg_setup( &cfg );
    TEMPLOG5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog5_init( &templog5, &cfg );

    tmp = templog5_read_data( &templog5, TEMPLOG5_REG_MANUFACTURER_ID );

    if ( tmp == TEMPLOG5_MANUFACTURER_ID )
    {
        log_info( &logger, "Comunication OK!!!" );
    }
    else
    {
        log_info( &logger, "Comunication ERROR!!!" );
        while( 1 );
    }
   
    ee_test_write[ 0 ] = 0xAA;
    templog5_write_eeprom( &templog5, 0x10, &ee_test_write[ 0 ], 1);
    Delay_ms ( 200 );
    
    templog5_read_eeprom( &templog5, 0x10, &ee_test_read[ 0 ], 1);
 
    log_info( &logger," EEPROM TEST READ:  %u\r\n", ee_test_read[ 0 ] ); 

    templog5_default_cfg ( &templog5 );
}
  
```

### Application Task

> Reads Temperature data and logs data to the terminal every 1 sec.

```c

void application_task ( void )
{
    float temperature;

    temperature = templog5_get_temperature( &templog5 );
    log_info( &logger,"Temperature:  %.2f\r\n", temperature );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog5

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

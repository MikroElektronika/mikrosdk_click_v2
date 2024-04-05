
---
# EEPROM 6 click

> EEPROM 6 Click is a compact add-on board that contains a serial EEPROM memory that operates from the 1-Wire interface. This board features the DS28EC20, a 20480-bit EEPROM organized as 80 memory pages of 256 bits each from Analog Devices. As a specific feature, blocks of eight memory pages can be write-protected or put in “EPROM-Emulation” Mode, where bits can only be changed from a 1 to a 0 state. It communicates with MCU at 15.4kbps or 90kbps over the 1-Wire protocol and has a 64-bit registration number that ensures error-free device selection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-6-click)

---


#### Click library

- **Author**        : Nikola Citakovic
- **Date**          : Mar 2022.
- **Type**          : One Wire type


# Software Support

We provide a library for the EEPROM 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM 6 Click driver.

#### Standard key functions :

- `eeprom6_cfg_setup` Config Object Initialization function.
```c
void eeprom6_cfg_setup ( eeprom6_cfg_t *cfg );
```

- `eeprom6_init` Initialization function.
```c
err_t eeprom6_init ( eeprom6_t *ctx, eeprom6_cfg_t *cfg );
```

- `eeprom6_default_cfg` Click Default Configuration function.
```c
err_t eeprom6_default_cfg ( eeprom6_t *ctx );
```

#### Example key functions :

- `eeprom6_write_mem` This function writes a sequential data starting of the targeted 16b register address of the targeted 16-bit register address of the DS28EC20.
```c
err_t eeprom6_write_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_in, uint16_t n_len );
```

- `eeprom6_read_mem` This function reads a sequential data starting from the targeted 16-bit register address of the DS28EC20.
```c
err_t eeprom6_read_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_in, uint16_t n_len );
```

## Example Description

> This example demonstrates the use of EEPROM6 click board by writing string to a memory at some specific location and then reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
	log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom6_cfg_t eeprom6_cfg;  /**< Click config object. */

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
    eeprom6_cfg_setup( &eeprom6_cfg );
    EEPROM6_MAP_MIKROBUS( eeprom6_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == eeprom6_init( &eeprom6, &eeprom6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM6_ERROR == eeprom6_default_cfg ( &eeprom6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example shows capabilities of EEPROM 6 Click board by writting a string into memory location from a specific address, and then reading it back every 5 seconds.

```c
void application_task ( void )
{
    log_printf( &logger, "Writing \"%s\" to memory address 0x%.4X\r\n", 
                ( uint8_t * ) EEPROM6_DEMO_TEXT, EEPROM6_TEXT_ADDRESS );
    eeprom6_write_mem( &eeprom6, EEPROM6_TEXT_ADDRESS, ( char * ) EEPROM6_DEMO_TEXT,
                       strlen ( EEPROM6_DEMO_TEXT ) );
    Delay_ms ( 100 );    
    uint8_t read_buf[ 100 ] = { 0 };
    eeprom6_read_mem ( &eeprom6, EEPROM6_TEXT_ADDRESS,read_buf,
                       strlen ( EEPROM6_DEMO_TEXT ) );
    log_printf( &logger, "Reading \"%s\" from memory address 0x%.4X\r\n\n",
                read_buf, ( uint16_t ) EEPROM6_TEXT_ADDRESS );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

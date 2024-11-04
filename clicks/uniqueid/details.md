
---
# UNIQUE ID Click

> Unique ID Click carries DS2401, an enhanced silicon serial number IC. It’s a low cost solution for providing a unique registration number to your design. The chip consists of a factory-lasered 64-bit ROM that includes a uniques a 48-bit serial number, an 8-bit CRC, and an 8-bit family code. It uses 1-wire communications for interfacing with the target board microcontroller, either through a GP1 or GP0 pin (here in place of the default AN and PWM mikroBUS pins). The board is designed to use either a 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uniqueid_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/unique-id-click)

---


#### Click library

- **Author**        : Aleksandra Cvjeticanin
- **Date**          : Feb 2022.
- **Type**          : One Wire type


# Software Support

We provide a library for the UNIQUE ID Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UNIQUE ID Click driver.

#### Standard key functions :

- `uniqueid_cfg_setup` Config Object Initialization function.
```c
void uniqueid_cfg_setup ( uniqueid_cfg_t *cfg );
```

- `uniqueid_init` Initialization function.
```c
err_t uniqueid_init ( uniqueid_t *ctx, uniqueid_cfg_t *cfg );
```

#### Example key functions :

- `uniqueid_read_id` This function reads Family Code and Serial Number of device's ROM memory.
```c
err_t uniqueid_read_id ( uniqueid_t *ctx, uint8_t *family, uint8_t *serial_num ); 
```

## Example Description

> This example demonstrates the use of UNIQUE ID Click board by reading and displaying Family Code and Serial Number on the UART Terminal.

**The demo application is composed of two sections :**

### Application Init

> Initionalizes both logger config object and Click config object. 

```c

void application_init ( void )
{
	log_cfg_t log_cfg;  /**< Logger config object. */
    uniqueid_cfg_t uniqueid_cfg;  /**< Click config object. */

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

    // Click initialization
    uniqueid_cfg_setup( &uniqueid_cfg );
    UNIQUEID_MAP_MIKROBUS( uniqueid_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == uniqueid_init( &uniqueid, &uniqueid_cfg ) ) 
    {
        log_error( &logger, " Initialization error." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Demonstrates the usage of uniqueid_read_id function,
which stores the Family Code and Serial Number of the Click in 
family_code and serial_num variables. Both values will be displayed 
on the UART Terminal.

```c
void application_task ( void )
{
	uint8_t family_code;
    uint8_t serial_num[ 6 ];
    
    if ( UNIQUEID_OK == uniqueid_read_id( &uniqueid, &family_code, &serial_num[ 0 ] ) )
    {
        log_printf( &logger, "Family Code = 0x%.2X\r\n", ( uint16_t ) family_code ); 
        log_printf( &logger, "Serial Number = 0x%.2X%.2X%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) serial_num[ 0 ], ( uint16_t ) serial_num[ 1 ], 
                    ( uint16_t ) serial_num[ 2 ], ( uint16_t ) serial_num[ 3 ], 
                    ( uint16_t ) serial_num[ 4 ], ( uint16_t ) serial_num[ 5 ] ); 
    }      
    
    Delay_ms ( 1000 ); 
}
```

## Note

The full application code and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UNIQUEID

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

\mainpage Main Page

---
# BM78 click

> BM78 Click is a compact add-on board designed to integrate dual-mode Bluetooth wireless capability into various projects. This board features the BM78, a fully certified 2.4GHz Bluetooth (BR/EDR/LE) wireless module from Microchip. The BM78 module includes an on-board Bluetooth stack, power management subsystem, 2.4GHz transceiver, and RF power amplifier. It supports GAP, SDP, SPP, and GATT profiles, with data transfer facilitated through transparent UART mode. It features a MODE SEL switch for operational modes, a reset pin, status indicators, a software power button, and a WAKE button.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bm78_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bm78-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : UART type


# Software Support

We provide a library for the BM78 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BM78 Click driver.

#### Standard key functions :

- `bm78_cfg_setup` Config Object Initialization function.
```c
void bm78_cfg_setup ( bm78_cfg_t *cfg );
```

- `bm78_init` Initialization function.
```c
err_t bm78_init ( bm78_t *ctx, bm78_cfg_t *cfg );
```

#### Example key functions :

- `bm78_eeprom_send_cmd` This function is used to send specific EEPROM command by using UART serial interface.
```c
err_t bm78_eeprom_send_cmd ( bm78_t *ctx, uint16_t op_code, uint8_t *param, uint8_t len );
```

- `bm78_eeprom_write` This function is used to write data into the EEPROM location specified by the address parameter.
```c
err_t bm78_eeprom_write ( bm78_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );
```

- `bm78_flash_eeprom` This function is used write default configuration into the EEPROM.
```c
err_t bm78_flash_eeprom ( bm78_t *ctx );
```

## Example Description

> This example demonstrates the use of BM78 click board by processing
 the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration by writing it into the EEPROM.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bm78_cfg_t bm78_cfg;  /**< Click config object. */

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
    bm78_cfg_setup( &bm78_cfg );
    BM78_MAP_MIKROBUS( bm78_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bm78_init( &bm78, &bm78_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t tmp_data[ 16 ];
    bm78_generic_read( &bm78, &tmp_data, 1 );  
    Delay_ms ( 100 );

    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Place Click into Write EEPROM mode \r\n" );
    log_printf( &logger, " By setting MODE SEL in the following configuration \r\n" );
    log_printf( &logger, "         | 1 | 2 | 3 |             \r\n" );
    log_printf( &logger, "         | H | L | L |             \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Send YES once you placed Click into Write EEPROM mode \r\n" );
    #define WANTED_ANSWER "YES/r/n"
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    while ( 1 )
    {
        log_read( &logger, &tmp_data, 5 );
        
        if ( 0 == strstr ( WANTED_ANSWER, tmp_data ) )
        {
            break;
        }
        else
        {
            log_printf( &logger, " Send YES once you placed Click into Write EEPROM mode \r\n" );
        }
    }
    bm78_hw_reset( &bm78 );
    log_printf( &logger, " Writing into the EEPROM \r\n" );
    if ( BM78_ERROR == bm78_flash_eeprom ( &bm78 ) )
    {
        log_error( &logger, " EEPROM Flash failed. " );
        log_printf( &logger, " Check Selected Click mode. \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Place Click into Application mode \r\n" );
    log_printf( &logger, " By setting MODE SEL in the following configuration \r\n" );
    log_printf( &logger, "         | 1 | 2 | 3 |             \r\n" );
    log_printf( &logger, "         | L | L | L |             \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Send YES once you placed Click into Application mode \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    while ( 1 )
    {
        log_read( &logger, &tmp_data, 5 );
        
        if ( 0 == strstr ( WANTED_ANSWER, tmp_data ) )
        {
            break;
        }
        else
        {
            log_printf( &logger, " Send YES once you placed Click into Application mode \r\n" );
        }
    }
    bm78_hw_reset( &bm78 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Connect to the device using the Serial Bluetooth Terminal App \r\n\r\n" );
}

```

### Application Task

> Reads and processes all incoming data from the Serial Bluetooth Terminal smartphone application and displays them on the USB UART.

```c
void application_task ( void ) 
{
    if ( BM78_OK == bm78_process( &bm78 ) ) 
    {
        bm78_log_app_buf( );
        bm78_clear_app_buf( );
    }
}
```

## Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
  A smartphone and the click board must be paired in order to exchange messages with each other.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BM78

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

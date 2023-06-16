
---
# SPI Isolator 2 click

> SPI Isolator 2 Click is a compact add-on board that contains a digital isolator optimized for a serial peripheral interface. This board features the ISO7741, a high-performance quad-channel digital isolator with a double capacitive silicon dioxide insulation barrier capable of galvanic isolation up to 5000Vrms from Texas Instruments. The ISO7741 provides high electromagnetic immunity and low emissions at low power consumption while isolating digital I/Os. It has three forward and one reverse-direction channel with enable pins that can be used to put the respective outputs in Hi-Z state. This Click board™ provides a simple, compact solution for isolated SPI data communication.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spiisolator2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/spi-isolator-2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the SPIIsolator2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SPIIsolator2 Click driver.

#### Standard key functions :

- `spiisolator2_cfg_setup` Config Object Initialization function.
```c
void spiisolator2_cfg_setup ( spiisolator2_cfg_t *cfg );
```

- `spiisolator2_init` Initialization function.
```c
err_t spiisolator2_init ( spiisolator2_t *ctx, spiisolator2_cfg_t *cfg );
```

#### Example key functions :

- `spiisolator2_output_enable` The function enable or disable output ( isolation ) of the ISO7741DWR High-Speed, Robust-EMC Reinforced and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
```c
void spiisolator2_output_enable( spiisolator2_t *ctx, uint8_t en_out );
```

- `spiisolator2_set_cmd` The function sends the desired command to the ISO7741DWR High-Speed, Robust-EMC Reinforced and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
```c
void spiisolator2_set_cmd ( spiisolator2_t *ctx, uint8_t cmd );
```

- `spiisolator2_write_byte` The function writes the byte of data to the targeted 8-bit register address of the ISO7741DWR High-Speed, Robust-EMC Reinforcedand Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
```c
void spiisolator2_write_byte ( spiisolator2_t *ctx, uint8_t reg, uint8_t tx_data );
```

## Example Description

> This is an example that demonstrates the use of the SPI Isolator 2 click board.
This board uses the ISO7741 which provides high electromagnetic immunity and low
emissions at low power consumption while isolating digital I/Os. In this example,
we write and then read data from the connected EEPROM 5 click to the SPI Isolator 2
click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI, set RST and CS pin as outputs, begins to write log, set write/read memory address, enable output.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                         /**< Logger config object. */
    spiisolator2_cfg_t spiisolator2_cfg;       /**< Click config object. */

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
    spiisolator2_cfg_setup( &spiisolator2_cfg );
    SPIISOLATOR2_MAP_MIKROBUS( spiisolator2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator2_init( &spiisolator2, &spiisolator2_cfg ) ) 
    {        
        log_error( &logger, " Application Init Error. \r\n" );
        log_info( &logger, " Please, run program again... \r\n" );
        for ( ; ; );
    }
    Delay_ms( 100 );

    spiisolator2_output_enable( &spiisolator2, SPIISOLATOR2_OUT_ENABLE );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

```

### Application Task

> Enables write to EEPROM, then writes the specified text message, and reads it back.
All data is being displayed on the USB UART where you can track the program flow.

```c

void application_task ( void ) 
{
    spiisolator2_set_cmd( &spiisolator2, SPIISOLATOR2_EEPROM5_CMD_WREN );
    Delay_ms( 10 );

    spiisolator2_multi_write( &spiisolator2, 
                              ( ( uint32_t ) SPIISOLATOR2_EEPROM5_CMD_WRITE << 24 ) | memory_address, 4, demo_data, 7 );
    log_printf( &logger," Write data : %s\r\n", demo_data );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
    Delay_ms( 100 );

    spiisolator2_multi_read( &spiisolator2, 
                             ( ( uint32_t ) SPIISOLATOR2_EEPROM5_CMD_READ << 24 ) | memory_address, 4, read_data, 7 );
    Delay_ms( 1000 );
    
    log_printf( &logger, " Read data  : %s\r\n", read_data );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 5000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---


---
# SWI EEPROM Click

> SWI EEPROM Click is a compact add-on board that provides a highly reliable memory solution. This board features the AT21CS01, a single-wire serial EEPROM with a unique, factory-programmed 64-bit serial number from Microchip Technology. The AT21CS01 has an ultra-high write endurance capability allowing more than one million cycles for each memory location to meet the requirements for today's high-write endurance applications. It is internally as 128 words of 8 bits each with achieved communication through a single I/O pin with Standard-Speed and High-Speed mode options. Also, it offers a security register with a factory-programmed serial number, which makes it the easiest way to add identification to various accessories and consumables.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/swi_eeprom_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/swi-eeprom-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the SWI EEPROM Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SWI EEPROM Click driver.

#### Standard key functions :

- `swieeprom_cfg_setup` Config Object Initialization function.
```c
void swieeprom_cfg_setup ( swieeprom_cfg_t *cfg );
```

- `swieeprom_init` Initialization function.
```c
err_t swieeprom_init ( swieeprom_t *ctx, swieeprom_cfg_t *cfg );
```

#### Example key functions :

- `swieeprom_mem_write_page` This function writes data to the specified memory address page.
```c
err_t swieeprom_mem_write_page ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t len );
```

- `swieeprom_mem_read` This function reads data from the specified memory address.
```c
err_t swieeprom_mem_read ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t len );
```

- `swieeprom_mem_clear` This function clears the whole memory to zero.
```c
err_t swieeprom_mem_clear ( swieeprom_t *ctx );
```

## Example Description

> This example demonstrates the use of SWI EEPROM Click board by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and checks the communication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */

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
    swieeprom.swi_reset = &swieeprom_reset;
    swieeprom.swi_start_stop = &swieeprom_start_stop;
    swieeprom.swi_logic_0 = &swieeprom_logic_write_0;
    swieeprom.swi_logic_1 = &swieeprom_logic_write_1;
    swieeprom.swi_logic_read = &swieeprom_logic_read;
    if ( SWIEEPROM_ERROR == swieeprom_init ( &swieeprom ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SWIEEPROM_ERROR == swieeprom_check_communication ( &swieeprom ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes the specified text message to the memory and reads it back. After that, erases
the whole memory and tries to read the same message verifying that the memory is erased.
All data is being displayed on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    uint8_t data_buf[ 8 ] = { 0 };
    // Write data to the specified address
    log_printf ( &logger, " Memory address: 0x%.2X\r\n", ( uint16_t ) STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    if ( SWIEEPROM_OK == swieeprom_mem_write_page ( &swieeprom, STARTING_ADDRESS, 
                                                    data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    // Read data from the specified address to verify the previous memory write
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( SWIEEPROM_OK == swieeprom_mem_read ( &swieeprom, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    // Clear whole memory
    if ( SWIEEPROM_OK == swieeprom_mem_clear ( &swieeprom ) )
    {
        log_printf ( &logger, " Memory clear\r\n" );
        Delay_ms ( 100 );
    }
    // Read data from the specified address to verify the previous memory clear
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( SWIEEPROM_OK == swieeprom_mem_read ( &swieeprom, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

## Note

> This application is written for the following MCUs and specifically for MIKROBUS 1:
STM32F407ZG, MK64FN1M0VDC12, TM4C129XNCZAD, GD32VF103VBT6, PIC32MX795F512L
In order to use it on another MCUs the pin_x functions must be defined in a way
it matches the required timing specifications for the Single Wire interface.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SWIEEPROM

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

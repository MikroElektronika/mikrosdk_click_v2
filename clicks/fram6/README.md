\mainpage Main Page

---
# FRAM 6 click

> FRAM 6 Click is a compact add-on board that contains highly reliable ferroelectric random access memory. This board features the CY15B102Q, a 2Mbit nonvolatile memory employing an advanced ferroelectric process organized as 256K words of 8 bits each from Cypress Semiconductor, now part of Infineon.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fram6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fram-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the FRAM6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for FRAM6 Click driver.

#### Standard key functions :

- `fram6_cfg_setup` Config Object Initialization function.
```c
void fram6_cfg_setup ( fram6_cfg_t *cfg );
```

- `fram6_init` Initialization function.
```c
err_t fram6_init ( fram6_t *ctx, fram6_cfg_t *cfg );
```

- `fram6_default_cfg` Click Default Configuration function.
```c
err_t fram6_default_cfg ( fram6_t *ctx );
```

#### Example key functions :

- `fram6_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t fram6_memory_write ( fram6_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );
```

- `fram6_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t fram6_memory_read ( fram6_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );
```

- `fram6_set_block_protection` This function sets the block protection bits of the Status register.
```c
err_t fram6_set_block_protection ( fram6_t *ctx, uint8_t block_protect );
```

## Example Description

> This example demonstrates the use of FRAM 6 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    fram6_cfg_t fram6_cfg;  /**< Click config object. */

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

    fram6_cfg_setup( &fram6_cfg );
    FRAM6_MAP_MIKROBUS( fram6_cfg, MIKROBUS_1 );
    
    if ( SPI_MASTER_ERROR == fram6_init( &fram6, &fram6_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( FRAM6_ERROR == fram6_default_cfg ( &fram6 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a desired number of bytes to the memory and then verifies that it's written correctly
> by reading from the same memory location and displaying the memory content on the USB UART.

```c

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    if ( FRAM6_OK == fram6_memory_write ( &fram6, STARTING_ADDRESS, 
                                          DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5lx: \t%s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                             ( char * ) DEMO_TEXT_MESSAGE );
    }
    if ( FRAM6_OK == fram6_memory_read ( &fram6, STARTING_ADDRESS, 
                                         data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address 0x%.5lx: \t%s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                         data_buf );
        Delay_ms ( 3000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM6

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

\mainpage Main Page

---
# FRAM 5 click

> FRAM 5 Click is a compact add-on board representing a highly reliable ferroelectric random access memory solution. This board features the FM24V10, a 1Mbit nonvolatile memory employing an advanced ferroelectric process organized as 128K words of 8 bits each from Infineon. This I2C configurable FRAM performs read and write operations similar to a RAM providing reliable data retention for 151 years while eliminating the complexities, overhead, and system-level reliability problems caused by EEPROM and other nonvolatile memories.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fram5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fram-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the FRAM 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for FRAM 5 Click driver.

#### Standard key functions :

- `fram5_cfg_setup` Config Object Initialization function.
```c
void fram5_cfg_setup ( fram5_cfg_t *cfg );
```

- `fram5_init` Initialization function.
```c
err_t fram5_init ( fram5_t *ctx, fram5_cfg_t *cfg );
```

#### Example key functions :

- `fram5_check_communication` This function checks the communication by reading and verifying the device ID.
```c
err_t fram5_check_communication ( fram5_t *ctx );
```

- `fram5_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t fram5_memory_write ( fram5_t *ctx, uint32_t address, uint8_t *data_in, uint8_t len );
```

- `fram5_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t fram5_memory_read ( fram5_t *ctx, uint32_t address, uint8_t *data_out, uint8_t len );
```

## Example Description

> This example demonstrates the use of FRAM 5 click board by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and checks the communication with the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fram5_cfg_t fram5_cfg;  /**< Click config object. */

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
    fram5_cfg_setup( &fram5_cfg );
    FRAM5_MAP_MIKROBUS( fram5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == fram5_init( &fram5, &fram5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FRAM5_ERROR == fram5_check_communication ( &fram5 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a desired number of bytes to the memory and then verifies that it's written correctly
by reading from the same memory location and displaying the memory content on the USB UART.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    if ( FRAM5_OK == fram5_memory_write ( &fram5, STARTING_ADDRESS, 
                                          DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5lx: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                           ( char * ) DEMO_TEXT_MESSAGE );
    }
    if ( FRAM5_OK == fram5_memory_read ( &fram5, STARTING_ADDRESS, 
                                         data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5lx: %s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                        data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

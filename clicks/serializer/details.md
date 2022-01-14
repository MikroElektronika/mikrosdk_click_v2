
---
# Serializer click

> Serializer Click is a compact add-on board that contains a digital input translator/serializer. This board features the MAX31910, an eight-channel digital input serializer for high-channel density digital input modules in industrial and process automation from Analog Devices. The MAX31910 translates, conditions, and serializes the 24V digital output of sensors and switches to 5V CMOS-compatible signals required by the MCU. It provides the front-end interface circuit of a programmable logic controller (PLC) digital input module. It communicates with MCU via the SPI interface and comes in configuration with an installed digital isolator. This Click board™ is suited for various applications such as industrial, process, and building automation, digital input modules for PLCs, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/serializer_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/serializer-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Serializer Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Serializer Click driver.

#### Standard key functions :

- `serializer_cfg_setup` Config Object Initialization function.
```c
void serializer_cfg_setup ( serializer_cfg_t *cfg );
```

- `serializer_init` Initialization function.
```c
err_t serializer_init ( serializer_t *ctx, serializer_cfg_t *cfg );
```

#### Example key functions :

- `serializer_get_flt_pin` This function returns the fault pin logic state.
```c
uint8_t serializer_get_flt_pin ( serializer_t *ctx );
```

- `serializer_read_input` This function reads the input data by using SPI serial interface, and then checks the data integrity by verifying the CRC byte.
```c
err_t serializer_read_input ( serializer_t *ctx, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of a Serializer click board by reading the state of all inputs and displaying the results on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    serializer_cfg_t serializer_cfg;  /**< Click config object. */

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
    serializer_cfg_setup( &serializer_cfg );
    SERIALIZER_MAP_MIKROBUS( serializer_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == serializer_init( &serializer, &serializer_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the state of all inputs and displays the results on the USB UART approximately once per second. Also, if there's any fault indication detected, it will be displayed accordingly.

```c

void application_task ( void )
{
    uint8_t input_data = 0;
    err_t status = serializer_read_input ( &serializer, &input_data );
    
    if ( SERIALIZER_ERROR != status )
    {
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            log_printf( &logger, " IN%u: %s\r\n", ( uint16_t ) cnt + 1, 
                                                  ( char * ) ( ( input_data & ( 1 << cnt ) ) ? "High" : "Low" ) );
        }
        if ( status & SERIALIZER_STATUS_UNDERVOLTAGE )
        {
            log_info( &logger, "Undervoltage fault" );
        }
        if ( status & SERIALIZER_STATUS_OVERTEMPERATURE )
        {
            log_info( &logger, "Overtemperature fault" );
        }
        log_printf( &logger, "\r\n" );
        Delay_ms( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Serializer

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

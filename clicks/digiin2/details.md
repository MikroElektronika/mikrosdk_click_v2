
---
# DIGI IN 2 click

> DIGI IN 2 Click is a compact add-on board designed for converting high-voltage industrial signals into logic-level outputs, ideal for enhancing industrial control systems. This board features the MAX22196, a high-performance octal industrial sink/source digital input IC from Analog Devices. This Click board™ stands out for its ability to interface eight industrial inputs (8V-24V) via SPI, configurable as either sinking or sourcing with built-in current limiters, ensuring adherence to IEC 61131-2 standards.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digiin2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-in-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the DIGI IN 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI IN 2 Click driver.

#### Standard key functions :

- `digiin2_cfg_setup` Config Object Initialization function.
```c
void digiin2_cfg_setup ( digiin2_cfg_t *cfg );
```

- `digiin2_init` Initialization function.
```c
err_t digiin2_init ( digiin2_t *ctx, digiin2_cfg_t *cfg );
```

- `digiin2_default_cfg` Click Default Configuration function.
```c
err_t digiin2_default_cfg ( digiin2_t *ctx );
```

#### Example key functions :

- `digiin2_get_flt_pin` This function is used to get state of the FLT pin.
```c
uint8_t digiin2_get_flt_pin ( digiin2_t *ctx );
```

- `digiin2_write_reg` This function is used to write data into the selected register by using SPI serial interface.
```c
err_t digiin2_write_reg ( digiin2_t *ctx, uint8_t reg, uint8_t data_in );
```

- `digiin2_read_reg` This function reads a data byte from the selected register by using SPI serial interface.
```c
err_t digiin2_read_reg ( digiin2_t *ctx, uint8_t reg, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of DIGI IN 2 Click board by reading and displaying the state of the channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiin2_cfg_t digiin2_cfg;  /**< Click config object. */

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
    digiin2_cfg_setup( &digiin2_cfg );
    DIGIIN2_MAP_MIKROBUS( digiin2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiin2_init( &digiin2, &digiin2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIIN2_ERROR == digiin2_default_cfg ( &digiin2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays on the USB UART the channel state every second.

```c
void application_task ( void )
{    
    uint8_t channel_data = 0;

    digiin2_pulse_latch( &digiin2 );

    if ( DIGIIN2_OK == digiin2_read_reg( &digiin2, DIGIIN2_REG_DISTATE, &channel_data ) )
    {
        if ( channel_data & DIGIIN2_CHANNEL_1_MASK )
        {
            log_printf( &logger, "Channel 1 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 1 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_2_MASK )
        {
            log_printf( &logger, "Channel 2 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 2 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_3_MASK )
        {
            log_printf( &logger, "Channel 3 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 3 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_4_MASK )
        {
            log_printf( &logger, "Channel 4 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 4 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_5_MASK )
        {
            log_printf( &logger, "Channel 5 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 5 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_6_MASK )
        {
            log_printf( &logger, "Channel 6 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 6 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_7_MASK )
        {
            log_printf( &logger, "Channel 7 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 7 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_8_MASK )
        {
            log_printf( &logger, "Channel 8 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 8 counter: LOW \r\n" );
        }
        log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    }
    else
    {
        log_error( &logger, " Read error." );
    }
    
    if ( DIGIIN2_PIN_STATE_HIGH == digiin2_get_flt_pin( &digiin2 ) )
    {
        uint8_t flt_data = 0;
        digiin2_read_reg( &digiin2, DIGIIN2_REG_FAULT, &flt_data );
        log_printf( &logger, "Fault1 data: 0x%.2X \r\n", ( uint16_t ) flt_data );
        digiin2_read_reg( &digiin2, DIGIIN2_REG_FAULT2, &flt_data );
        log_printf( &logger, "Fault2 data: 0x%.2X \r\n", ( uint16_t ) flt_data );
        log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    }

    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIN2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

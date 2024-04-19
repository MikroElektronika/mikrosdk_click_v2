\mainpage Main Page

---
# DIGI IN click

> DIGI IN Click is a compact add-board that converts industrial inputs into serialized SPI-compatible output. This board features the MAX22199, an octal industrial digital input from Analog Devices. It stands out for its compliance with the IEC 61131-2 standard, ensuring reliability and efficiency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digiin_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-in-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the DIGI IN Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI IN Click driver.

#### Standard key functions :

- `digiin_cfg_setup` Config Object Initialization function.
```c
void digiin_cfg_setup ( digiin_cfg_t *cfg );
```

- `digiin_init` Initialization function.
```c
err_t digiin_init ( digiin_t *ctx, digiin_cfg_t *cfg );
```

- `digiin_default_cfg` Click Default Configuration function.
```c
err_t digiin_default_cfg ( digiin_t *ctx );
```

#### Example key functions :

- `digiin_write_reg` This function is used to write data into the selected register by using SPI serial interface.
```c
err_t digiin_write_reg ( digiin_t *ctx, uint8_t reg, uint8_t data_in );
```

- `digiin_read_reg` This function reads a data byte from the selected register by using SPI serial interface.
```c
err_t digiin_read_reg ( digiin_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `digiin_pulse_latch` This function is used to generate LATCH pulse for capturing channel data.
```c
void digiin_pulse_latch ( digiin_t *ctx );
```

## Example Description

> This example demonstrates the use of DIGI IN Click board by reading and displaying the state of the channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiin_cfg_t digiin_cfg;  /**< Click config object. */

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
    digiin_cfg_setup( &digiin_cfg );
    DIGIIN_MAP_MIKROBUS( digiin_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiin_init( &digiin, &digiin_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    while ( DIGIIN_PIN_STATE_HIGH == digiin_get_rdy_pin( &digiin ) )
    {
        log_printf( &logger, "Please check if 24V is connected \r\n" );
        Delay_ms ( 1000 );
    }

    if ( DIGIIN_ERROR == digiin_default_cfg ( &digiin ) )
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

    digiin_pulse_latch( &digiin );

    if ( DIGIIN_OK == digiin_read_reg( &digiin, DIGIIN_REG_DISTATE, &channel_data ) )
    {
        if ( channel_data & DIGIIN_CHANNEL_1_MASK )
        {
            log_printf( &logger, "Channel 1 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 1 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_2_MASK )
        {
            log_printf( &logger, "Channel 2 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 2 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_3_MASK )
        {
            log_printf( &logger, "Channel 3 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 3 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_4_MASK )
        {
            log_printf( &logger, "Channel 4 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 4 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_5_MASK )
        {
            log_printf( &logger, "Channel 5 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 5 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_6_MASK )
        {
            log_printf( &logger, "Channel 6 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 6 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_7_MASK )
        {
            log_printf( &logger, "Channel 7 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 7 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_8_MASK )
        {
            log_printf( &logger, "Channel 8 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 8 State: LOW \r\n" );
        }
        log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    }
    else
    {
        log_error( &logger, " Read error." );
    }
    
    if ( DIGIIN_PIN_STATE_HIGH == digiin_get_flt_pin( &digiin ) )
    {
        uint8_t flt_data = 0;
        digiin_read_reg( &digiin, DIGIIN_REG_FAULT1, &flt_data );
        log_printf( &logger, "Fault1 data: 0x%.2X \r\n", ( uint16_t ) flt_data );
        digiin_read_reg( &digiin, DIGIIN_REG_FAULT2, &flt_data );
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
- Click.DIGIIN

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

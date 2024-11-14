
---
# DIGI IO Click

> DIGI I/O Click is a compact add-on board for flexible industrial digital input and output control. This board features the MAX14906, a quad-channel industrial digital input/output IC from Analog Devices, compliant with IEC 61131-2 standard. Each channel can be individually configured as a high-side switch, push-pull driver, or digital input, supporting various operating modes with current limiting up to 1.2A and fast signal transmission. The board supports 24V operation by default, with options for individual channel power configuration, and includes built-in diagnostics like overvoltage and undervoltage detection, thermal overload, and wire-break detection. DIGI I/O Click is ideal for industrial automation, motor control systems, PLCs, and Distributed Control Systems (DCS).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digiio_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/digi-io-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the DIGI IO Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI IO Click driver.

#### Standard key functions :

- `digiio_cfg_setup` Config Object Initialization function.
```c
void digiio_cfg_setup ( digiio_cfg_t *cfg );
```

- `digiio_init` Initialization function.
```c
err_t digiio_init ( digiio_t *ctx, digiio_cfg_t *cfg );
```

- `digiio_default_cfg` Click Default Configuration function.
```c
err_t digiio_default_cfg ( digiio_t *ctx );
```

#### Example key functions :

- `digiio_write_reg` This function writes data to the selected register by using SPI serial interface.
```c
err_t digiio_write_reg ( digiio_t *ctx, uint8_t reg, uint8_t data_in );
```

- `digiio_read_reg` This function reads data from the selected register by using SPI serial interface.
```c
err_t digiio_read_reg ( digiio_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `digiio_sync_io` This function synchronizes registers by toggling the SYNC pin logic state.
```c
void digiio_sync_io ( digiio_t *ctx );
```

## Example Description

> This example demonstrates the use of DIGI IO Click board by setting and reading the DOI channels state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the DOI1 and DOI2 as output and the DOI3 and DOI4 as inputs.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiio_cfg_t digiio_cfg;  /**< Click config object. */

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
    digiio_cfg_setup( &digiio_cfg );
    DIGIIO_MAP_MIKROBUS( digiio_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiio_init( &digiio, &digiio_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIIO_ERROR == digiio_default_cfg ( &digiio ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Toggles the DOI1 and DOI2 pins state and then reads the status of all four DOI pins and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t set_out = 0;
    uint8_t doi_level = 0;
    digiio_sync_io ( &digiio );
    if ( DIGIIO_OK == digiio_read_reg ( &digiio, DIGIIO_REG_SET_OUT, &set_out ) )
    {
        set_out ^= ( DIGIIO_SET_OUT_HIGH_O1_MASK | DIGIIO_SET_OUT_HIGH_O2_MASK );
        if ( DIGIIO_OK == digiio_write_reg ( &digiio, DIGIIO_REG_SET_OUT, set_out ) )
        {
            digiio_sync_io ( &digiio );
        }
    }
    if ( DIGIIO_OK == digiio_read_reg ( &digiio, DIGIIO_REG_DOI_LEVEL, &doi_level ) )
    {
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI1 )
        {
            log_printf ( &logger, " DOI1: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI1: LOW\r\n" );
        }
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI2 )
        {
            log_printf ( &logger, " DOI2: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI2: LOW\r\n" );
        }
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI3 )
        {
            log_printf ( &logger, " DOI3: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI3: LOW\r\n" );
        }
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI4 )
        {
            log_printf ( &logger, " DOI4: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI4: LOW\r\n" );
        }
        log_printf ( &logger, "\r\n" );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIO

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

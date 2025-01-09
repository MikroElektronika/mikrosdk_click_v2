
---
# DIGI IO Click

> [DIGI IO Click](https://www.mikroe.com/?pid_product=MIKROE-6236) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6236&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DIGI IO Click board by setting and reading the DOI channels state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIO

### Example Key Functions

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---

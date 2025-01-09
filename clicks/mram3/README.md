
---
# MRAM 3 Click

> [MRAM 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5191) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5191&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of MRAM 3 Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MRAM3

### Example Key Functions

- `mram3_cfg_setup` Config Object Initialization function.
```c
void mram3_cfg_setup ( mram3_cfg_t *cfg );
```

- `mram3_init` Initialization function.
```c
err_t mram3_init ( mram3_t *ctx, mram3_cfg_t *cfg );
```

- `mram3_default_cfg` Click Default Configuration function.
```c
err_t mram3_default_cfg ( mram3_t *ctx );
```

- `mram3_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t mram3_memory_write ( mram3_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );
```

- `mram3_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t mram3_memory_read ( mram3_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

- `mram3_aug_memory_write` This function writes a desired number of data bytes starting from the selected augmented memory address.
```c
err_t mram3_aug_memory_write ( mram3_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mram3_cfg_t mram3_cfg;  /**< Click config object. */

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
    mram3_cfg_setup( &mram3_cfg );
    MRAM3_MAP_MIKROBUS( mram3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mram3_init( &mram3, &mram3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MRAM3_ERROR == mram3_default_cfg ( &mram3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is written correctly by reading from the same memory location and displaying the memory content on the USB UART.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( MRAM3_OK == mram3_memory_write ( &mram3, STARTING_ADDRESS, 
                                          data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( MRAM3_OK == mram3_memory_read ( &mram3, STARTING_ADDRESS, 
                                         data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( MRAM3_OK == mram3_memory_write ( &mram3, STARTING_ADDRESS, 
                                          data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( MRAM3_OK == mram3_memory_read ( &mram3, STARTING_ADDRESS, 
                                         data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5LX: %s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                        data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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

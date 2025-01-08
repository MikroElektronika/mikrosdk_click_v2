
---
# FRAM 5 Click

> [FRAM 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5119) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5119&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of FRAM 5 Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM5

### Example Key Functions

- `fram5_cfg_setup` Config Object Initialization function.
```c
void fram5_cfg_setup ( fram5_cfg_t *cfg );
```

- `fram5_init` Initialization function.
```c
err_t fram5_init ( fram5_t *ctx, fram5_cfg_t *cfg );
```

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

### Application Init

> Initializes the driver and checks the communication with the Click board.

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

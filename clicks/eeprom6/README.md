
---
# EEPROM 6 Click

> [EEPROM 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4296) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4296&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Citakovic
- **Date**          : Mar 2022.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM6 Click board by writing string to a memory at some specific location and then reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM6

### Example Key Functions

- `eeprom6_cfg_setup` Config Object Initialization function.
```c
void eeprom6_cfg_setup ( eeprom6_cfg_t *cfg );
```

- `eeprom6_init` Initialization function.
```c
err_t eeprom6_init ( eeprom6_t *ctx, eeprom6_cfg_t *cfg );
```

- `eeprom6_default_cfg` Click Default Configuration function.
```c
err_t eeprom6_default_cfg ( eeprom6_t *ctx );
```

- `eeprom6_write_mem` This function writes a sequential data starting of the targeted 16b register address of the targeted 16-bit register address of the DS28EC20.
```c
err_t eeprom6_write_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_in, uint16_t n_len );
```

- `eeprom6_read_mem` This function reads a sequential data starting from the targeted 16-bit register address of the DS28EC20.
```c
err_t eeprom6_read_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_in, uint16_t n_len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
	log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom6_cfg_t eeprom6_cfg;  /**< Click config object. */

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
    eeprom6_cfg_setup( &eeprom6_cfg );
    EEPROM6_MAP_MIKROBUS( eeprom6_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == eeprom6_init( &eeprom6, &eeprom6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM6_ERROR == eeprom6_default_cfg ( &eeprom6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example shows capabilities of EEPROM 6 Click board by writting a string into memory location from a specific address, and then reading it back every 5 seconds.

```c
void application_task ( void )
{
    log_printf( &logger, "Writing \"%s\" to memory address 0x%.4X\r\n", 
                ( uint8_t * ) EEPROM6_DEMO_TEXT, EEPROM6_TEXT_ADDRESS );
    eeprom6_write_mem( &eeprom6, EEPROM6_TEXT_ADDRESS, ( char * ) EEPROM6_DEMO_TEXT,
                       strlen ( EEPROM6_DEMO_TEXT ) );
    Delay_ms ( 100 );    
    uint8_t read_buf[ 100 ] = { 0 };
    eeprom6_read_mem ( &eeprom6, EEPROM6_TEXT_ADDRESS,read_buf,
                       strlen ( EEPROM6_DEMO_TEXT ) );
    log_printf( &logger, "Reading \"%s\" from memory address 0x%.4X\r\n\n",
                read_buf, ( uint16_t ) EEPROM6_TEXT_ADDRESS );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

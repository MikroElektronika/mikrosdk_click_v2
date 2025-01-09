
---
# SPI Isolator 2 Click

> [SPI Isolator 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4415) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4415&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the SPI Isolator 2 Click board.
This board uses the ISO7741 which provides high electromagnetic immunity and low
emissions at low power consumption while isolating digital I/Os. In this example,
we write and then read data from the connected EEPROM 5 Click to the SPI Isolator 2
Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator2

### Example Key Functions

- `spiisolator2_cfg_setup` Config Object Initialization function.
```c
void spiisolator2_cfg_setup ( spiisolator2_cfg_t *cfg );
```

- `spiisolator2_init` Initialization function.
```c
err_t spiisolator2_init ( spiisolator2_t *ctx, spiisolator2_cfg_t *cfg );
```

- `spiisolator2_output_enable` The function enable or disable output ( isolation ) of the ISO7741DWR High-Speed, Robust-EMC Reinforced and Basic Quad-Channel Digital Isolators on SPI Isolator 2 Click board.
```c
void spiisolator2_output_enable( spiisolator2_t *ctx, uint8_t en_out );
```

- `spiisolator2_set_cmd` The function sends the desired command to the ISO7741DWR High-Speed, Robust-EMC Reinforced and Basic Quad-Channel Digital Isolators on SPI Isolator 2 Click board.
```c
void spiisolator2_set_cmd ( spiisolator2_t *ctx, uint8_t cmd );
```

- `spiisolator2_write_byte` The function writes the byte of data to the targeted 8-bit register address of the ISO7741DWR High-Speed, Robust-EMC Reinforcedand Basic Quad-Channel Digital Isolators on SPI Isolator 2 Click board.
```c
void spiisolator2_write_byte ( spiisolator2_t *ctx, uint8_t reg, uint8_t tx_data );
```

### Application Init

> Initializes SPI, set RST and CS pin as outputs, begins to write log, set write/read memory address, enable output.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                         /**< Logger config object. */
    spiisolator2_cfg_t spiisolator2_cfg;       /**< Click config object. */

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
    spiisolator2_cfg_setup( &spiisolator2_cfg );
    SPIISOLATOR2_MAP_MIKROBUS( spiisolator2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator2_init( &spiisolator2, &spiisolator2_cfg ) ) 
    {        
        log_error( &logger, " Application Init Error. \r\n" );
        log_info( &logger, " Please, run program again... \r\n" );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    spiisolator2_output_enable( &spiisolator2, SPIISOLATOR2_OUT_ENABLE );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> Enables write to EEPROM, then writes the specified text message, and reads it back.
All data is being displayed on the USB UART where you can track the program flow.

```c
void application_task ( void ) 
{
    spiisolator2_set_cmd( &spiisolator2, SPIISOLATOR2_EEPROM5_CMD_WREN );
    Delay_ms ( 10 );

    spiisolator2_multi_write( &spiisolator2, 
                              ( ( uint32_t ) SPIISOLATOR2_EEPROM5_CMD_WRITE << 24 ) | memory_address, 4, demo_data, 7 );
    log_printf( &logger," Write data : %s\r\n", demo_data );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
    Delay_ms ( 100 );

    spiisolator2_multi_read( &spiisolator2, 
                             ( ( uint32_t ) SPIISOLATOR2_EEPROM5_CMD_READ << 24 ) | memory_address, 4, read_data, 7 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Read data  : %s\r\n", read_data );
    log_printf( &logger, "---------------------\r\n" );
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

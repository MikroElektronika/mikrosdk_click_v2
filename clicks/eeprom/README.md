
---
# EEPROM Click

> [EEPROM Click](https://www.mikroe.com/?pid_product=MIKROE-1200) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1200&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : I2C type

# Software Support

## Example Description

>
> This is a example which demonstrates the use of EEPROM Click board.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom

### Example Key Functions

- `eeprom_cfg_setup` Config Structure Setup function. 
```c
void eeprom_cfg_setup ( eeprom_cfg_t *cfg );
```
 
- `eeprom_init` Click Initialization function. 
```c
eeprom_retval_t eeprom_init ( eeprom_t *context, eeprom_cfg_t *cfg );
```

- `eeprom_write_page` Page Write function. 
```c
void eeprom_write_page ( eeprom_t *context, uint8_t reg_addr, eeprom_i2c_data_t *data_in );
```
 
- `eeprom_read_sequential` Sequential Read function. 
```c
eeprom_retval_t eeprom_read_sequential ( eeprom_t *context, uint8_t reg_addr, uint16_t n_bytes, eeprom_i2c_data_t *data_out );
```

- `eeprom_write_protect` Write Protect function. 
```c
void eeprom_write_protect ( eeprom_t *context );
```

### Application Init

>
> Initializes peripherals and pins used by EEPROM Click.
> Initializes SPI serial interface and puts a device to the initial state.
>

```c
void application_init( void )
{
    eeprom_cfg_t eeprom_cfg;
    log_cfg_t log_cfg;

    //  Click initialization.
    eeprom_cfg_setup( &eeprom_cfg );
    EEPROM_MAP_MIKROBUS( eeprom_cfg, MIKROBUS_1 );
    eeprom_init( &eeprom, &eeprom_cfg );

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
    log_info( &logger, "----  Application Init Done  ----\r\n" );
}
```

### Application Task

>
> First page of memory block 1 will be written with data values starting from
> 1 to 16. This memory page will be read by the user, to verify successfully
> data writing. Data writing to memory will be protected upon memory writing,
> and before memory reading.
>

```c
void application_task( void )
{
    eeprom_i2c_data_t transfer_data[ EEPROM_NBYTES_PAGE ];
    uint8_t cnt;

    transfer_data[ EEPROM_BLOCK_ADDR_START ] = 1;

    for (cnt = EEPROM_BLOCK_ADDR_START + 1; cnt < EEPROM_NBYTES_PAGE; cnt++)
    {
        transfer_data[ cnt ] = transfer_data[ cnt - 1 ] + 1;
    }

    eeprom_write_enable( &eeprom );
    eeprom_write_page( &eeprom, EEPROM_BLOCK_ADDR_START, transfer_data );
    eeprom_write_protect( &eeprom );

    Delay_ms ( 1000 );
    memset( transfer_data, 0, sizeof(transfer_data) );

    eeprom_read_sequential( &eeprom, EEPROM_BLOCK_ADDR_START, EEPROM_NBYTES_PAGE, transfer_data );

    for (cnt = EEPROM_BLOCK_ADDR_START; cnt < EEPROM_NBYTES_PAGE; cnt++)
    {
        log_printf( &logger, " %d", transfer_data[ cnt ] );
        Delay_ms ( 300 );
    }
    log_printf( &logger, "\r\n" );
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

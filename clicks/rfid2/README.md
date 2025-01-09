
---
# RFID 2 Click

> [RFID 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4208) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4208&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Aug 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from RFID 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RFID2

### Example Key Functions

- `rfid2_cfg_setup` Config Object Initialization function.
```c
void rfid2_cfg_setup ( rfid2_cfg_t *cfg );
```

- `rfid2_init` Initialization function.
```c
err_t rfid2_init ( rfid2_t *ctx, rfid2_cfg_t *cfg );
```

- `rfid2_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t rfid2_generic_write ( rfid2_t *ctx, char *data_buf, uint16_t len );
```

- `rfid2_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rfid2_generic_read ( rfid2_t *ctx, char *data_buf, uint16_t max_len );
```

- `rfid2_reset` This function resets the chip.
```c
void rfid2_reset( rfid2_t *ctx );
```

### Application Init

> Initializes UART module and sets RST pin as OUTPUT and INT pin as INPUT. Also, initializes Driver init and reset chip.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    rfid2_cfg_t rfid2_cfg;  /**< Click config object. */

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
    rfid2_cfg_setup( &rfid2_cfg );
    RFID2_MAP_MIKROBUS( rfid2_cfg, MIKROBUS_1 );
    err_t init_flag  = rfid2_init( &rfid2, &rfid2_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    rfid2_reset( &rfid2 );
    Delay_ms ( 100 );

    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    log_printf( &logger, "*** Please, put your ID card.***\r\n" );
    log_printf( &logger, "*** ID card :\r\n" );
}
```

### Application Task

> Reads the ID card (HEX) and logs data on the USBUART-a.

```c
void application_task ( void ) 
{
    app_buf_len = rfid2_generic_read( &rfid2, app_buf, PROCESS_BUFFER_SIZE );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        memset( app_buf, 0, PROCESS_BUFFER_SIZE );    
    }
}
```## Application Output

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


---
# USB-C Sink Click

> [USB-C Sink Click](https://www.mikroe.com/?pid_product=MIKROE-4328) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4328&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example which demonstrates the use of USB-C Sink Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink

### Example Key Functions

- `usbcsink_cfg_setup` Config Object Initialization function.
```c
void usbcsink_cfg_setup ( usbcsink_cfg_t *cfg );
```

- `usbcsink_init` Initialization function.
```c
err_t usbcsink_init ( usbcsink_t *ctx, usbcsink_cfg_t *cfg );
```

- `usbcsink_hw_reset` HW reset function.
```c
void usbcsink_hw_reset ( usbcsink_t *ctx );
```

- `usbcsink_get_pdo2` Get PO2 pin state function.
```c
uint8_t usbcsink_get_pdo2 ( usbcsink_t *ctx );
```

- `usbcsink_write_byte` Write byte function.
```c
void usbcsink_write_byte ( usbcsink_t *ctx, uint8_t reg, uint8_t tx_data );
```

### Application Init

> Initialization driver enables - I2C, set hw reset, set PDO2 profile and current value for PDO2 1.5A,
> upload new data and reset device to write NVM settings to the STUSB450, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink_cfg_t usbcsink_cfg;  /**< Click config object. */

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
    usbcsink_cfg_setup( &usbcsink_cfg );
    USBCSINK_MAP_MIKROBUS( usbcsink_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsink_init( &usbcsink, &usbcsink_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    usbcsink_hw_reset( &usbcsink );
    Delay_ms ( 1000 );
    
    usbcsink_set_pdo_num( USBCSINK_SET_PDO_2 );
    usbcsink_set_current( USBCSINK_SET_PDO_2, 1.5 );
    
    sel_profile = usbcsink_get_pdo_num( );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );
    log_printf( &logger , "   Setting PDO ~ PDO%d \r\n", ( uint16_t ) sel_profile );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );
    
    usbcsink_upload_new_data( &usbcsink, USBCSINK_UPLOAD_NEW_DATA_VAL );
    Delay_ms ( 1000 );
    
    usbcsink_hw_reset( &usbcsink );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> USB-C Sink Click board can be used to read the Power Data Objects (PDO) highest priority profile:
> PDO1 :  5V,
> PDO2 : 12V,
> PDO3 : 20V.
> All data logs write on USB uart changes for every 5 sec.

```c
void application_task ( void ) 
{
    usbcsink_load_data( &usbcsink );

    log_printf( &logger , "     New Parameters     \r\n" );
    log_printf( &logger , "------------------------\r\n" );
    
    sel_profile = usbcsink_get_pdo_num( );
    
    log_printf( &logger , "    PDO Number ~ PDO%d\r\n", ( uint16_t ) sel_profile );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );

    demo_data = usbcsink_get_voltage( sel_profile );
    log_printf( &logger , " Voltage : %.2f V\r\n", demo_data );

    demo_data = usbcsink_get_current( sel_profile );
    log_printf( &logger , " Current :  %.2f A\r\n", demo_data );

    log_printf( &logger , "------------------------\r\n" );
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

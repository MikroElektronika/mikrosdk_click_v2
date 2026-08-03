
---
# USB-C Power 3 Click

> [USB-C Power 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6954) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6954&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the USB-C Power 3 Click board for
monitoring USB Type-C connection and power status. The application reads
CC and power status registers, detects connection changes, and logs
detailed information about VBUS state, connection type, and cable orientation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCPower3

### Example Key Functions

- `usbcpower3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void usbcpower3_cfg_setup ( usbcpower3_cfg_t *cfg );
```

- `usbcpower3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t usbcpower3_init ( usbcpower3_t *ctx, usbcpower3_cfg_t *cfg );
```

- `usbcpower3_ptn_read_info` This function reads device identification and revision information from PTN USB PD registers.
```c
err_t usbcpower3_ptn_read_info ( usbcpower3_t *ctx );
```

- `usbcpower3_ptn_read_reg_byte` This function reads one byte from the selected PTN USB PD register using the block read function.
```c
err_t usbcpower3_ptn_read_reg_byte ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `usbcpower3_ptn_write_reg_byte` This function writes one byte to the selected PTN USB PD register using the block write function.
```c
err_t usbcpower3_ptn_write_reg_byte ( usbcpower3_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the logger and USB-C Power 3 Click driver, and reads device identification information.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcpower3_cfg_t usbcpower3_cfg;  /**< Click config object. */

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
    usbcpower3_cfg_setup( &usbcpower3_cfg );
    USBCPOWER3_MAP_MIKROBUS( usbcpower3_cfg, MIKROBUS_POSITION_USBCPOWER3 );
    if ( USBCPOWER3_OK != usbcpower3_init( &usbcpower3, &usbcpower3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCPOWER3_OK != usbcpower3_ptn_read_info ( &usbcpower3 ) )
    {
        log_error( &logger, " PTN read info." );
        for ( ; ; );
    }
    log_printf( &logger, " --- PTN info ---\r\n" );
    log_printf( &logger, " Vendor ID: 0x%.4X\r\n", usbcpower3.info.vendor_id );
    log_printf( &logger, " Product ID: 0x%.4X\r\n", usbcpower3.info.product_id );
    log_printf( &logger, " Device ID: 0x%.4X\r\n", usbcpower3.info.device_id );
    log_printf( &logger, " USB-C rev: 0x%.4X\r\n", usbcpower3.info.usbtypec_rev );
    log_printf( &logger, " USB-PD rev/ver: 0x%.4X\r\n", usbcpower3.info.usbpd_rev_ver );
    log_printf( &logger, " PD interface rev: 0x%.4X\r\n\n", usbcpower3.info.pd_interface_rev );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously monitors CC and power status registers, detects changes, parses connection state, and controls VBUS direction (sink/source) accordingly.

```c
void application_task ( void )
{
    err_t error_flag = USBCPOWER3_OK;
    static uint8_t cc_status_old = 0;
    static uint8_t power_status_old = 0;
    uint8_t cc_status = 0;
    uint8_t power_status = 0;

    // Read CC and power status registers
    error_flag = usbcpower3_ptn_read_reg_byte ( &usbcpower3, USBCPOWER3_PTN_REG_CC_STATUS, &cc_status );
    if ( USBCPOWER3_OK == error_flag )
    {
        error_flag = usbcpower3_ptn_read_reg_byte ( &usbcpower3, USBCPOWER3_PTN_REG_POWER_STATUS, &power_status );
    }
    
    // Check if any of them are updated
    if ( ( USBCPOWER3_OK == error_flag ) && 
         ( ( cc_status_old != cc_status ) || ( power_status_old != power_status ) ) )
    {
        cc_status_old = cc_status;
        power_status_old = power_status;
        log_printf ( &logger, "###############################\r\n" );
        usbcpower3_parse_power_status ( power_status );
        error_flag = usbcpower3_parse_cc_status ( &usbcpower3, cc_status );
        log_printf ( &logger, "*******************************\r\n\n" );
    }
    else
    {
        // No updates in status registers, check again in 100ms
        Delay_ms ( 100 );
    }
}
```

### Note

> The application automatically handles USB connection and disconnection events, including VBUS control based on detected role.

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

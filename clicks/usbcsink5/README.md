
---
# USB-C Sink 5 Click

> [USB-C Sink 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6934) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6934&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the USB-C Sink 5 Click board for
monitoring USB Type-C sink operation. The application reads VBUS and CC
status registers, detects connection changes, and logs information about
power availability, current capability, cable orientation, and device attachment.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink5

### Example Key Functions

- `usbcsink5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void usbcsink5_cfg_setup ( usbcsink5_cfg_t *cfg );
```

- `usbcsink5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t usbcsink5_init ( usbcsink5_t *ctx, usbcsink5_cfg_t *cfg );
```

- `usbcsink5_read_info` This function reads device identification and revision information from the registers.
```c
err_t usbcsink5_read_info ( usbcsink5_t *ctx );
```

- `usbcsink5_write_reg_byte` This function writes one byte to the selected register using the block write function.
```c
err_t usbcsink5_write_reg_byte ( usbcsink5_t *ctx, uint8_t reg, uint8_t data_in );
```

- `usbcsink5_read_reg_byte` This function reads one byte from the selected register using the block read function.
```c
err_t usbcsink5_read_reg_byte ( usbcsink5_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes the logger and USB-C Sink 5 Click driver, and reads device identification information.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink5_cfg_t usbcsink5_cfg;  /**< Click config object. */

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
    usbcsink5_cfg_setup( &usbcsink5_cfg );
    USBCSINK5_MAP_MIKROBUS( usbcsink5_cfg, MIKROBUS_POSITION_USBCSINK5 );
    if ( I2C_MASTER_ERROR == usbcsink5_init( &usbcsink5, &usbcsink5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCSINK5_ERROR == usbcsink5_read_info ( &usbcsink5 ) )
    {
        log_error( &logger, " Read info." );
        for ( ; ; );
    }
    log_printf( &logger, " --- Device info ---\r\n" );
    log_printf( &logger, " Vendor ID: 0x%.4X\r\n", usbcsink5.info.vendor_id );
    log_printf( &logger, " Product ID: 0x%.4X\r\n", usbcsink5.info.product_id );
    log_printf( &logger, " USB XID: 0x%.8LX\r\n", usbcsink5.info.usb_xid );
    log_printf( &logger, " FW version: 0x%.2X\r\n", ( uint16_t ) usbcsink5.info.fw_ver );
    log_printf( &logger, " HW version: 0x%.2X\r\n", ( uint16_t ) usbcsink5.info.hw_ver );
    log_printf( &logger, " PD revision: 0x%.2X\r\n", ( uint16_t ) usbcsink5.info.pd_rev );
    log_printf( &logger, " PD version: 0x%.2X\r\n\n", ( uint16_t ) usbcsink5.info.pd_ver );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously monitors VBUS and CC status registers, detects changes,
and logs sink state, current level (default, 1.5A, 3.0A), cable orientation,
and attachment status.

```c
void application_task ( void )
{
    err_t error_flag = USBCSINK5_OK;
    static uint8_t vbus_status_old = 0;
    static uint8_t cc_status_old = 0;
    uint8_t vbus_status = 0;
    uint8_t cc_status = 0;

    // Read VBUS and CC status registers
    error_flag = usbcsink5_read_reg_byte ( &usbcsink5, USBCSINK5_REG_VBUS_STATUS, &vbus_status );
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_byte ( &usbcsink5, USBCSINK5_REG_CC_STATUS, &cc_status );
    }
    else
    {
        log_printf ( &logger, "###############################\r\n" );
        log_printf ( &logger, " No communication, check USB source connection.\r\n" );
        log_printf ( &logger, "*******************************\r\n\n" );
    }

    // Check if any of them are updated
    if ( ( USBCSINK5_OK == error_flag ) && 
         ( ( vbus_status_old != vbus_status ) || ( cc_status_old != cc_status ) ) )
    {
        vbus_status_old = vbus_status;
        cc_status_old = cc_status;
        log_printf ( &logger, "###############################\r\n" );
        if ( USBCSINK5_VBUS_STATUS_SWITCH_CLOSED & vbus_status )
        {
            log_printf ( &logger, " Sinking VBUS to VSNK is enabled\r\n" );
        }
        else
        {
            log_printf ( &logger, " Sinking VBUS to VSNK is disabled\r\n" );
        }
        
        if ( ( USBCSINK5_CC_STATUS_CC2_SINK_DEFAULT == ( cc_status & USBCSINK5_CC_STATUS_CC2_MASK ) ) || 
             ( USBCSINK5_CC_STATUS_CC1_SINK_DEFAULT == ( cc_status & USBCSINK5_CC_STATUS_CC1_MASK ) ) )
        {
            log_printf ( &logger, " Sink default\r\n" );
        }
        else if ( ( USBCSINK5_CC_STATUS_CC2_SINK_POWER_1_5 == ( cc_status & USBCSINK5_CC_STATUS_CC2_MASK ) ) || 
                  ( USBCSINK5_CC_STATUS_CC1_SINK_POWER_1_5 == ( cc_status & USBCSINK5_CC_STATUS_CC1_MASK ) ) )
        {
            log_printf ( &logger, " Sink 1.5A\r\n" );
        }
        else if ( ( USBCSINK5_CC_STATUS_CC2_SINK_POWER_3_0 == ( cc_status & USBCSINK5_CC_STATUS_CC2_MASK ) ) || 
                  ( USBCSINK5_CC_STATUS_CC1_SINK_POWER_3_0 == ( cc_status & USBCSINK5_CC_STATUS_CC1_MASK ) ) )
        {
            log_printf ( &logger, " Sink 3.0A\r\n" );
        }
        else
        {
            log_printf ( &logger, " Both CC1 and CC2 are open\r\n" );
        }
        
        if ( cc_status & USBCSINK5_CC_STATUS_PLUG_ORIENTATION_REVERSED )
        {
            log_printf ( &logger, " Orientation reversed\r\n" );
        }
        else
        {
            log_printf ( &logger, " Orientation normal\r\n" );
        }

        if ( cc_status & USBCSINK5_CC_STATUS_DEVICE_ATTACHED )
        {
            log_printf ( &logger, " Device attached\r\n" );
        }
        else
        {
            log_printf ( &logger, " Device not attached\r\n" );
        }
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

> If there is no communication, check the USB source connection.

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

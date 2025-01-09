
---
# ECG GSR Click

> [ECG GSR Click](https://www.mikroe.com/?pid_product=MIKROE-4500) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4500&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click is made for PPG, ECG and GSR,
> equipped with an ultra-low power, multi channel, integrated biopotential AFE and EFE.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ECGGSR

### Example Key Functions

- `ecggsr_cfg_setup` Config Object Initialization function.
```c
void ecggsr_cfg_setup ( ecggsr_cfg_t *cfg ); 
```

- `ecggsr_init` Initialization function.
```c
err_t ecggsr_init( ecggsr_t *ctx, ecggsr_cfg_t* cfg );
```

- `ecggsr_default_cfg` Click Default Configuration function.
```c
void ecggsr_default_cfg( ecggsr_t *ctx, ecggsr_cfg_t *cfg );
```

- `ecggsr_read_reg` Function performs reading of an ID of the device.
```c
err_t ecggsr_read_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t num_of_regs );
```

- `ecggsr_write_reg` Function writes 8-bit data to the register.
```c
err_t ecggsr_write_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t transfer_data );
```

- `ecggsr_reset` Function performs the SW reset of the device and waits until the device returns back to normal state.
```c
void ecggsr_reset( ecggsr_t *ctx );
```

### Application Init

> Initializes driver, performs SW reset of all the registers, which puts the registers in their initial state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    
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
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.
    ecggsr_cfg_setup( &ecggsr_cfg );
    ECGGSR_MAP_MIKROBUS( ecggsr_cfg, MIKROBUS_1 );
    ecggsr_init( &ecggsr, &ecggsr_cfg );
    Delay_1sec();
    ecggsr_default_cfg( &ecggsr, &ecggsr_cfg );
    Delay_1sec();
}
```

### Application Task

> Depending on the user selection, application measures:
> 1. value of oxygen level in human's blood or
> 2. heartrate or
> 3. galvanic skin response

```c
void application_task( void )
{
    // ------------------------------------------------------------
    // Check the presence of the ECG GSR Click by reading device ID.
    // ------------------------------------------------------------
    ecggsr_read_dev_id( &ecggsr, &dev_id );
    if ( ECGGSR_DEV_ID == dev_id  )
    {
        // ------------------------------------------------------------
        // Enable desired functionality of the ECG GSR Click.
        // ------------------------------------------------------------
        if ( ENABLE_OXIMETER_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_oxy_saturation( );
        } 
        else if ( ENABLE_HEARTRATE_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_heartrate( );
        } 
        else if ( ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_gal_skin_resp( );
        } 
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

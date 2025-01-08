
---
# Light mix sens Click

> [Light mix-sens Click](https://www.mikroe.com/?pid_product=MIKROE-4148) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4148&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example show usage of Light Mix Sens Click. It switches the IR light for separate and 
> measure sectar of RGB lights. Click also measure proximity from the object using light source.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightMixSens

### Example Key Functions

- `lightmixsens_cfg_setup` Config Object Initialization function.
```c
void lightmixsens_cfg_setup ( lightmixsens_cfg_t *cfg );
```

- `lightmixsens_init` Initialization function.
```c
err_t lightmixsens_init ( lightmixsens_t *ctx, lightmixsens_cfg_t *cfg );
```

- `lightmixsens_default_cfg` Light mix sens default configuration function.
```c
void lightmixsens_default_cfg ( lightmixsens_t *ctx );
```

- `lightmixsens_write_byte` Generic Write Byte function.
```c
err_t lightmixsens_write_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t data_in );
```

- `lightmixsens_read_byte` Generic Read Byte function.
```c
err_t lightmixsens_read_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t *data_out );
```

- `lightmixsens_switch_ir_to_prox` Switch IR To Proximity function.
```c
void lightmixsens_switch_ir_to_prox ( lightmixsens_t *ctx );
```

### Application Init

> Initializes all necessary peripherals and pins, initializes I2C driver and performs 
> the Click board default configuration to allow ALS/Color and Proximity measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lightmixsens_cfg_t cfg;

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

    lightmixsens_cfg_setup( &cfg );
    LIGHTMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightmixsens_init( &lightmixsens, &cfg );

    lightmixsens_default_cfg( &lightmixsens );

    lightmixsens_cdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_rdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_gdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_bdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_pdata = LIGHTMIXSENS_DUMMY_DATA;

    log_printf( &logger, "*  Light mix-sens Click initialization done.  *\r\n" );
}
```

### Application Task

> Waits until ALS/Color integration cycle was done and then reads the entire measurement.
> The all results will be sent to the selected UART terminal.

```c
void application_task ( void )
{
    lightmixsens_wait_atime( &lightmixsens );
    
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_CDATA, &lightmixsens_cdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_RDATA, &lightmixsens_rdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_GDATA_IRDATA, &lightmixsens_gdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_BDATA, &lightmixsens_bdata );
    lightmixsens_read_byte( &lightmixsens, LIGHTMIXSENS_REG_PDATA, &lightmixsens_pdata );
    
    log_printf( &logger, "- Clear light:  %d lx\r\n", lightmixsens_cdata );
    log_printf( &logger, "- Red light:    %d lx\r\n", lightmixsens_rdata );
    log_printf( &logger, "- Green light:  %d lx\r\n", lightmixsens_gdata );
    log_printf( &logger, "- Blue light:   %d lx\r\n", lightmixsens_bdata );
    
    prox_app( );
    log_printf( &logger, "** Proximity:   %s\r\n", prox_str );
    
    log_printf( &logger, "\r\n" );
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

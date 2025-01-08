
---
# Buck 14 Click

> [Buck 14 Click](https://www.mikroe.com/?pid_product=MIKROE-3847) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3847&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This app enables usage of high-efficiency step-down converter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck14

### Example Key Functions

- `buck14_cfg_setup` Config Object Initialization function. 
```c
void buck14_cfg_setup ( buck14_cfg_t *cfg );
``` 
 
- `buck14_init` Initialization function. 
```c
err_t buck14_init ( buck14_t *ctx, buck14_cfg_t *cfg );
```

- `buck14_default_cfg` Click Default Configuration function. 
```c
void buck14_default_cfg ( buck14_t *ctx );
```

- `buck14_power_ctrl` This function sets state of the power control pin on cs. 
```c
void buck14_power_ctrl ( buck14_t *ctx, uint8_t state );
```
 
- `buck14_salert` This function gets manufacturer id. 
```c
uint8_t buck14_salert ( buck14_t *ctx );
```

- `buc14_write_vout` This function sets output V. 
```c
uint8_t buc14_write_vout ( buck14_t *ctx, float vout );
```

### Application Init

> Configure device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck14_cfg_t cfg;
    uint8_t write_data;
    uint8_t status_data;

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

    buck14_cfg_setup( &cfg );
    BUCK14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck14_init( &buck14, &cfg );

    buck14_reset( &buck14 );

    write_data  = BUCK14_CTRL_ENABLE_NO_MARGIN;
    buck14_generic_write( &buck14, BUCK14_CMD_OPERATION, write_data , 1 );
    Delay_ms ( 300 );

    status_data = buck14_check_mfr_id(  &buck14 );
    error_handler( status_data );
    log_printf( &logger, "-Device ID OK!\r\n" );
    
    buck14_power_ctrl( &buck14, BUCK14_PIN_STATE_HIGH );

    buck14_default_cfg( &buck14 );
    log_printf( &logger, " ***** App init ***** \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Sends 4 different commands for VOUT in span of 8sec

```c
void application_task ( void )
{
    uint8_t status_data;
    float vout_value;

    vout_value = 1.2;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    vout_value = 3.7;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data( &buck14 );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    vout_value = 2.5;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    vout_value = 4.5;
    status_data = buc14_write_vout(  &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "```````````````\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> When you send data you should send LSB first.
> Device input V should be beetween 4.5 - 14 V.
> Device output V could be from 0.5 - 5 V deepending from limits you set currently it is set to 1V.

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

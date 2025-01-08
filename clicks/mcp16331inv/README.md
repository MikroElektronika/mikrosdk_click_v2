
---
# MCP16331 INV Click

> [MCP16331 INV Click](https://www.mikroe.com/?pid_product=MIKROE-2917) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2917&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application enables usage of this Click as a buck-boost voltage regulator.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp16331Inv

### Example Key Functions

- `mcp16331inv_cfg_setup` Config Object Initialization function. 
```c
void mcp16331inv_cfg_setup ( mcp16331inv_cfg_t *cfg );
``` 
 
- `mcp16331inv_init` Initialization function. 
```c
err_t mcp16331inv_init ( mcp16331inv_t *ctx, mcp16331inv_cfg_t *cfg );
```

- `mcp16331inv_default_cfg` Click Default Configuration function. 
```c
void mcp16331inv_default_cfg ( mcp16331inv_t *ctx );
```

- `mcp16331inv_enable_vin` Function enables or disables internal VIN pull up. 
```c
void mcp16331inv_enable_vin ( mcp16331inv_t *ctx, uint8_t state );
```
 
- Function determines DAC output voltage value in depending on the input DAC_value (0x0000 - 0x0FFF) and gain_value.
- `mcp16331inv_set_dac_vout` Function also can put device on active or shutdown mode. 
```c
void mcp16331inv_set_dac_vout ( mcp16331inv_t *ctx, uint16_t dac_value, uint8_t gain_value, uint8_t mode );
```

- `mcp16331inv_generic_transfer` Generic SPI transfer, for sending and receiving packages. 
```c
void mcp16331inv_generic_transfer ( mcp16331inv_t *ctx, spi_master_transfer_data_t *block );
```

### Application Init

> Initializes Click driver and enables VIN Pull Up.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp16331inv_cfg_t cfg;

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

    mcp16331inv_cfg_setup( &cfg );
    MCP16331INV_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    Delay_ms ( 100 );

    mcp16331inv_init( &mcp16331inv, &cfg );

    Delay_ms ( 100 );

    mcp16331inv_enable_vin( &mcp16331inv, MCP16331INV_ENABLE_VIN_PULL_UP );
}
```

### Application Task

> Sets DAC output voltage on 3500mV, when gain is set up on 1x VREF,
> on 4s delay time, and then sets DAC output voltage on 5000mV, when gain is now set up on 2x VREF,
> on also 4s delay time. VIN Pull Up voltage must be greater than 4V. 

```c
void application_task ( void )
{
    //  Task implementation.

    mcp16331inv_set_dac_vout( &mcp16331inv, MCP16331INV_3500_MV_1X_GAIN, MCP16331INV_GAIN_1X_VREF, MCP16331INV_ACTIVE_MODE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    mcp16331inv_set_dac_vout( &mcp16331inv, MCP16331INV_5000_MV_2X_GAIN, MCP16331INV_GAIN_2X_VREF, MCP16331INV_ACTIVE_MODE );
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

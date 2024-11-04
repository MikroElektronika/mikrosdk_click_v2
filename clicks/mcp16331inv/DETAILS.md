
---
# MCP16331 INV Click

MCP16331 INV Click works as a buck-boost voltage regulator, a switching regulator topology that combines principles of the buck conversion (step-down) and the boost conversion (step-up).


<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp16331inv_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mcp16331-inv-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mcp16331Inv Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp16331Inv Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp16331inv_cfg_setup ( mcp16331inv_cfg_t *cfg ); 
 
- Initialization function.
> MCP16331INV_RETVAL mcp16331inv_init ( mcp16331inv_t *ctx, mcp16331inv_cfg_t *cfg );

- Click Default Configuration function.
> void mcp16331inv_default_cfg ( mcp16331inv_t *ctx );


#### Example key functions :

- Function enables or disables internal VIN pull up.
> void mcp16331inv_enable_vin ( mcp16331inv_t *ctx, uint8_t state );
 
- Function determines DAC output voltage value in depending on the input DAC_value (0x0000 - 0x0FFF) and gain_value.
- Function also can put device on active or shutdown mode.
> void mcp16331inv_set_dac_vout ( mcp16331inv_t *ctx, uint16_t dac_value, uint8_t gain_value, uint8_t mode );

- Generic SPI transfer, for sending and receiving packages
> void mcp16331inv_generic_transfer ( mcp16331inv_t *ctx, spi_master_transfer_data_t *block );

## Examples Description

> This application enables usage of this Click as a buck-boost voltage regulator.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp16331Inv

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
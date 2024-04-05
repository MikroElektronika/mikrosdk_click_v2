 
---
# Clock Gen click

Clock Gen Click offers an ideal replacement for crystals, crystal oscillators, VCXOs, phase-locked loops (PLLs), and fanout buffers in cost-sensitive applications. This click features the Si5351A from Silicon Labs, an I2C configurable clock generator based on a PLL + high resolution MultiSynth fractional divider architecture which can generate any frequency up to 200 MHz on each of its outputs with 0 ppm error.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clockgen_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/clock-gen-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the ClockGen Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ClockGen Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void clockgen_cfg_setup ( clockgen_cfg_t *cfg ); 
 
- Initialization function.
> CLOCKGEN_RETVAL clockgen_init ( clockgen_t *ctx, clockgen_cfg_t *cfg );

- Click Default Configuration function.
> void clockgen_default_cfg ( clockgen_t *ctx );


#### Example key functions :

- This function sets clock divider
> void clockgen_set_frequency ( clockgen_t *ctx, uint8_t clk_num, uint8_t pll_num, uint32_t freq );
 
- This function sets pll.
> void clockgen_setup_pll ( clockgen_t *ctx, uint8_t pll, uint8_t mult, uint32_t num );

- This function sets clock frequency on specific clock.
> void clockgen_setup_multisyinth ( clockgen_t *ctx, uint8_t clk_num, uint32_t divider, uint32_t num );

## Examples Description

> Clock Gen Click represent a replacement for crystals, crystal oscillators, VCXOs, phase-locked 
> loops (PLLs), and fanout buffers. This click features an I2C configurable clock generator 
> based on a PLL + high resolution MultiSynth fractional divider architecture which can generate
> any frequency up to 200 MHz with 0 ppm error. The chip on click is capable of generating 
> synchronous or free-running non-integer related clock frequencies at each of its outputs 
> (CLK0, CLK1, and CLK2), enabling one device to synthesize clocks for multiple clock domains in a design.

**The demo application is composed of two sections :**

### Application Init 

> Configures device to default function that enables clock 0 and disables all others.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen_cfg_t cfg;

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

    clockgen_cfg_setup( &cfg );
    CLOCKGEN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen_init( &clockgen, &cfg );

    clockgen_default_cfg( &clockgen );
    
    Delay_ms ( 500 );
}

```

### Application Task

> Changes 4 different frequency in span of 5 seconds.

```c

void application_task ( void )
{
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 5 );
    Delay_ms ( 1000 );
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
- Click.ClockGen

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---

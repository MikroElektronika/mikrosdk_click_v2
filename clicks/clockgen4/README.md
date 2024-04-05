\mainpage Main Page

---
# Clock Gen 4 click

> Clock Gen 4 Click is a compact add-on board that contains both a clock generator and a multiplier/jitter reduced clock frequency synthesizer. This board features the CS2200-CP, an analog PLL architecture comprised of a Delta-Sigma fractional-N frequency synthesizer from Cirrus Logic. This clocking device utilizes a programmable phase lock loop and allows frequency synthesis and clock generation from a stable reference clock. It generates a low-jitter PLL clock from an external crystal, supports both I²C and SPI for full software control, and also has configurable auxiliary clock output. This Click board™ is suitable for MCU clock source, or in applications like digital effects processors, digital mixing consoles, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clockgen4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/clock-gen-4-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the ClockGen4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ClockGen4 Click driver.

#### Standard key functions :

- `clockgen4_cfg_setup` Config Object Initialization function.
```c
void clockgen4_cfg_setup ( clockgen4_cfg_t *cfg );
```

- `clockgen4_init` Initialization function.
```c
err_t clockgen4_init ( clockgen4_t *ctx, clockgen4_cfg_t *cfg );
```

- `clockgen4_default_cfg` Click Default Configuration function.
```c
err_t clockgen4_default_cfg ( clockgen4_t *ctx );
```

#### Example key functions :

- `clockgen4_dev_ctl` Function is used to write to device control register in order to apply settings.
```c
void clockgen4_dev_ctl ( clockgen4_t *ctx, uint8_t dev_ctl );
```

- `clockgen4_dev_cfg` Function is used to write to device configuration 1 register in order to apply settings.
```c
void clockgen4_dev_cfg ( clockgen4_t *ctx, uint8_t dev_cfg );
```

- `clockgen4_glob_cfg` Function is used to write to function configuration 2 register in order to apply settings.
```c
void clockgen4_glob_cfg ( clockgen4_t *ctx, uint8_t glob_cfg );
```

## Example Description

> This example demonstrates the uses of Clock Gen 4 click which is based on CS2200-CP for changing the channel clock. The CS2200-CP is an extremely versatile system clocking 
device that utilizes a programmable phase lock loop. The CS2200-CP is based on an analog PLL architecture and this architecture allows for frequency synthesis and clock generation
from a stable reference clock. The CS2200-CP supports both I²C and SPI for full software control.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C and SPI, sets CS pin as output and starts to write log, applies default settings and adjusted ratio to obtain a frequency.

```c

void application_init ( void ){
    log_cfg_t log_cfg;                     /**< Logger config object. */
    clockgen4_cfg_t clockgen4_cfg;         /**< Click config object. */

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
    
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------" );
    log_printf( &logger, "  Clock Gen 4 Click  " );
    log_printf( &logger, "---------------------" );
    
    // Click initialization.
    clockgen4_cfg_setup( &clockgen4_cfg );
    CLOCKGEN4_MAP_MIKROBUS( clockgen4_cfg, MIKROBUS_1 );
    err_t init_flag  = clockgen4_init( &clockgen4, &clockgen4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    clockgen4_default_cfg ( &clockgen4 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> Clock Gen 4 click is used in this example to generate and change the clock on the output channel.

```c

void application_task ( void ){
    clockgen4_dev_ctl ( &clockgen4, CLOCKGEN4_AUX_OUT_DIS | CLOCKGEN4_CLK_OUT_EN );
    log_printf( &logger, "  PLL Clock          \r\n" );
    log_printf( &logger, "  output enabled!    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    clockgen4_dev_ctl ( &clockgen4, CLOCKGEN4_AUX_OUT_EN | CLOCKGEN4_CLK_OUT_DIS );
    log_printf( &logger, "  AUX Clock          \r\n" );
    log_printf( &logger, "  output enabled!    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

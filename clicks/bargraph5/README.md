\mainpage Main Page

---
# BarGraph 5 Click

> BarGraph 5 Click is a compact add-on board designed for visual data representation through LED bargraph displays. This board features three HLMP-2685 red LED bargraph displays from Broadcom Limited, controlled by the TLC5947, a 12-bit PWM LED driver from Texas Instruments. These rectangular red light bars are housed in single-in-line packages, delivering a luminous intensity of 83.4mcd with a peak wavelength of 626nm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bargraph5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/bargraph-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the BarGraph 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BarGraph 5 Click driver.

#### Standard key functions :

- `bargraph5_cfg_setup` Config Object Initialization function.
```c
void bargraph5_cfg_setup ( bargraph5_cfg_t *cfg );
```

- `bargraph5_init` Initialization function.
```c
err_t bargraph5_init ( bargraph5_t *ctx, bargraph5_cfg_t *cfg );
```

- `bargraph5_default_cfg` Click Default Configuration function.
```c
err_t bargraph5_default_cfg ( bargraph5_t *ctx );
```

#### Example key functions :

- `bargraph5_set_bar_level` This function sets the level of a selected BarGraph channel at the selected brightness.
```c
err_t bargraph5_set_bar_level ( bargraph5_t *ctx, bargraph5_bar_sel_t bar_num, bargraph5_level_t level, uint16_t brightness );
```

- `bargraph5_output_enable` This function enables the BarGraph LEDs output by setting the BLANK pin to low logic state.
```c
void bargraph5_output_enable ( bargraph5_t *ctx );
```

- `bargraph5_output_disable` This function disables the BarGraph LEDs output by setting the BLANK pin to high logic state.
```c
void bargraph5_output_disable ( bargraph5_t *ctx );
```

## Example Description

> This example demonstrates the use of BarGraph 5 Click board by changing the level of all BarGraph output channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bargraph5_cfg_t bargraph5_cfg;  /**< Click config object. */

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
    bargraph5_cfg_setup( &bargraph5_cfg );
    BARGRAPH5_MAP_MIKROBUS( bargraph5_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == bargraph5_init( &bargraph5, &bargraph5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BARGRAPH5_ERROR == bargraph5_default_cfg ( &bargraph5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the level of all BarGraph channels once per second. The channels level is displayed on the USB UART.

```c
void application_task ( void )
{
    for ( bargraph5_level_t cnt = BARGRAPH5_LEVEL_0; cnt <= BARGRAPH5_LEVEL_4; cnt++ )
    {
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_0, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_1, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_2, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_3, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_4, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_5, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        log_printf( &logger, " Bars 0-2-4 level: %u\r\n", ( uint16_t ) cnt );
        log_printf( &logger, " Bars 1-3-5 level: %u\r\n\n", ( uint16_t ) ( BARGRAPH5_LEVEL_4 - cnt ) );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BarGraph5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---


---
# BarGraph 4 click

> BarGraph 4 Click is a compact add-on board that contains four green four-segment LED bar graph displays. This board features the TLC59283, a 16-channel, constant-current sink light-emitting diode (LED) driver from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bargraph_4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bargraph-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the BarGraph4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BarGraph4 Click driver.

#### Standard key functions :

- `bargraph4_cfg_setup` Config Object Initialization function.
```c
void bargraph4_cfg_setup ( bargraph4_cfg_t *cfg );
```

- `bargraph4_init` Initialization function.
```c
err_t bargraph4_init ( bargraph4_t *ctx, bargraph4_cfg_t *cfg );
```

#### Example key functions :

- `bargraph4_enable_output` This function enables all outputs.
```c
void bargraph4_enable_output ( bargraph4_t *ctx );
```

- `bargraph4_set_output` This function sets all outputs to desired value by using SPI serial interface.
```c
err_t bargraph4_set_output ( bargraph4_t *ctx, uint16_t ch_mask );
```

- `bargraph4_set_channel_level` This function sets the level of a desired bar graph channel.
```c
err_t bargraph4_set_channel_level ( bargraph4_t *ctx, bargraph4_sel_ch_t channel, bargraph4_level_t level );
```

## Example Description

> This example demonstrates the use of BarGraph 4 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    bargraph4_cfg_t bargraph4_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    bargraph4_cfg_setup( &bargraph4_cfg );
    BARGRAPH4_MAP_MIKROBUS( bargraph4_cfg, MIKROBUS_1 );
    err_t init_flag  = bargraph4_init( &bargraph4, &bargraph4_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    bargraph4_enable_output( &bargraph4 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the level of all bar graph channels every second. The channels level will be logged on the USB UART.

```c

void application_task ( void )
{
    for ( bargraph4_level_t cnt = BARGRAPH4_LEVEL_0; cnt <= BARGRAPH4_LEVEL_4; cnt++ )
    {
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_A, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_B, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_C, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_D, cnt );
        log_printf( &logger, " All channels set to level %u\r\n\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BarGraph4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---

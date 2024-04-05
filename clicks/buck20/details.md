
---
# Buck 20 click

> Buck 20 Click is a compact add-on board that contains a DC-DC power converter that steps down the voltage from its input to its output. This board features the MP2316, a fully-integrated, high-efficiency, synchronous, step-down switch-mode converter from Monolithic Power Systems (MPS). The MP2316 achieves 3A continuous output current over a wide input supply range from 4V to 19V. It has excellent load and line regulation and can operate efficiently over a vast output voltage load range. The MP2316 also offers advanced protection features such as undervoltage, overcurrent, and short-circuit detections.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck20_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-20-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Buck 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck 20 Click driver.

#### Standard key functions :

- `buck20_cfg_setup` Config Object Initialization function.
```c
void buck20_cfg_setup ( buck20_cfg_t *cfg );
```

- `buck20_init` Initialization function.
```c
err_t buck20_init ( buck20_t *ctx, buck20_cfg_t *cfg );
```

#### Example key functions :

- `buck20_set_wiper_1` This function sets wiper 1 to desired value.
```c
err_t buck20_set_wiper_1 ( buck20_t *ctx, uint16_t data_in );
```

- `buck20_enable_device` This function enables the buck device by setting the RST pin to high logic state.
```c
void buck20_enable_device ( buck20_t *ctx );
```

- `buck20_disable_device` This function disables the buck device by setting the RST pin to low logic state.
```c
void buck20_disable_device ( buck20_t *ctx );
```

## Example Description

> This example demonstrates the use of Buck 20 click by changing the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck20_cfg_t buck20_cfg;  /**< Click config object. */

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
    buck20_cfg_setup( &buck20_cfg );
    BUCK20_MAP_MIKROBUS( buck20_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == buck20_init( &buck20, &buck20_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    buck20_set_wiper_1 ( &buck20, BUCK20_WIPER_ZERO_SCALE );
    buck20_enable_device ( &buck20 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage every 3 seconds and displays on the USB UART the digipot wiper position, as well as an approximate buck R1 and voltage output.

```c
void application_task ( void )
{
    static uint16_t digipot_wiper = BUCK20_WIPER_ZERO_SCALE;
    float buck_r1_kohm, buck_vout;
    if ( BUCK20_OK == buck20_set_wiper_1 ( &buck20, digipot_wiper ) )
    {
        buck_r1_kohm = BUCK20_RESISTOR_R6_KOHM + 
                       ( float ) ( BUCK20_DIGIPOT_MAX_KOHM * digipot_wiper ) / BUCK20_WIPER_FULL_SCALE;
        buck_vout = BUCK20_BUCK_VREF + ( buck_r1_kohm * BUCK20_BUCK_VREF ) / BUCK20_BUCK_R2_KOHM;
        log_printf( &logger, " Digipot wiper position: %u\r\n", digipot_wiper );
        log_printf( &logger, " Approximate R1 (Digipot+R6): %.2f kOhm\r\n", buck_r1_kohm );
        log_printf( &logger, " Approximate buck voltage output: %.2f V\r\n\n", buck_vout );
        digipot_wiper += 50;
        if ( digipot_wiper > BUCK20_WIPER_FULL_SCALE )
        {
            digipot_wiper = BUCK20_WIPER_ZERO_SCALE;
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> An approximate buck R1 and VOUT values do not have to be 100% accurate for all wiper settings
but they are a good reference point. VOUT ranges from ~1.3V to ~5V, and it is the most accurate
around 3.3V since all passive components are set for that output.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

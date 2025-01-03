\mainpage Main Page

---
# LR 11 915MHz Click

> LR 11 Click - 915MHz is a compact add-on board for long-range, low-power wireless communication in IoT applications. This board features the 453-00139R, an ultra-low power LoraWAN module Ezurio (part of the RM126x series), integrating the Silicon Labs EFR32 SoC and the Semtech SX1262 radio. It supports LoRaWAN classes A, B, and C, offering secure, scalable, and bi-directional communication. It operates in the 902-928MHz frequency range with a typical transmit power of up to 22dBm and a communication range of up to 15km.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr11915mhz_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lr-11-click-915mhz)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LR 11 915MHz Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR 11 915MHz Click driver.

#### Standard key functions :

- `lr11915mhz_cfg_setup` Config Object Initialization function.
```c
void lr11915mhz_cfg_setup ( lr11915mhz_cfg_t *cfg );
```

- `lr11915mhz_init` Initialization function.
```c
err_t lr11915mhz_init ( lr11915mhz_t *ctx, lr11915mhz_cfg_t *cfg );
```

#### Example key functions :

- `lr11915mhz_reset_device` This function resets the device by toggling the reset pin logic state.
```c
void lr11915mhz_reset_device ( lr11915mhz_t *ctx );
```

- `lr11915mhz_cmd_run` This function sends a specified command with or without parameters to the Click module.
```c
void lr11915mhz_cmd_run ( lr11915mhz_t *ctx, uint8_t *cmd, uint8_t *param );
```

- `lr11915mhz_cmd_set` This function sets a value to a specified command parameter of the Click module.
```c
void lr11915mhz_cmd_set ( lr11915mhz_t *ctx, uint8_t *cmd, uint8_t *param_id, uint8_t *value );
```

## Example Description

> This example demonstrates the use of LR 11 915MHz Click board by showing the communication between two Click boards configured in P2P network mode.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr11915mhz_cfg_t lr11915mhz_cfg;  /**< Click config object. */

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
    lr11915mhz_cfg_setup( &lr11915mhz_cfg );
    LR11915MHZ_MAP_MIKROBUS( lr11915mhz_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr11915mhz_init( &lr11915mhz, &lr11915mhz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LR11915MHZ_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - LR11915MHZ_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LR11915MHZ_CONFIG_EXAMPLE: 
   > Configures device for the LoRa P2P network mode.
 - LR11915MHZ_EXAMPLE:
   > Performs a LoRa P2P example by exchanging messages with another LR 11 915MHz Click board.
> One device should be set to NODE_0_ADDRESS, and the other to NODE_1_ADDRESS.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LR11915MHZ_POWER_UP:
        {
            if ( LR11915MHZ_OK == lr11915mhz_power_up( &lr11915mhz ) )
            {
                app_state = LR11915MHZ_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR11915MHZ_CONFIG_EXAMPLE:
        {
            if ( LR11915MHZ_OK == lr11915mhz_config_example( &lr11915mhz ) )
            {
                app_state = LR11915MHZ_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR11915MHZ_EXAMPLE:
        {
            lr11915mhz_example( &lr11915mhz );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
            break;
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LR11915MHz

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

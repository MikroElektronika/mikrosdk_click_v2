\mainpage Main Page

---
# LR 14 Click

> LR 14 Click is a compact add-on board for low-power, long-range wireless communication in IoT networks. This board features the RAK3172, a Class A/B/C LoRaWAN 1.0.3-compliant module from RAKwireless Technology, featuring the STM32WLE5CC ARM Cortex-M4 32-bit chip. This board supports LoRaWAN and LoRa Point-to-Point communication modes and integrates multiple frequency bands for flexibility across various regions. Key features include UART, SPI, and I2C interfaces, a USB Type-C connector for power and configuration, and a rechargeable battery option for standalone operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr14_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lr-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LR 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR 14 Click driver.

#### Standard key functions :

- `lr14_cfg_setup` Config Object Initialization function.
```c
void lr14_cfg_setup ( lr14_cfg_t *cfg );
```

- `lr14_init` Initialization function.
```c
err_t lr14_init ( lr14_t *ctx, lr14_cfg_t *cfg );
```

#### Example key functions :

- `lr14_cmd_run` This function sends a specified command to the Click module.
```c
void lr14_cmd_run ( lr14_t *ctx, uint8_t *cmd );
```

- `lr14_cmd_set` This function sets a value to a specified command of the Click module.
```c
void lr14_cmd_set ( lr14_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `lr14_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void lr14_cmd_get ( lr14_t *ctx, uint8_t *cmd );
```

## Example Description

> This example demonstrates the use of LR 14 Click board by showing the communication between two Click boards configured in P2P network mode.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr14_cfg_t lr14_cfg;  /**< Click config object. */

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
    lr14_cfg_setup( &lr14_cfg );
    LR14_MAP_MIKROBUS( lr14_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr14_init( &lr14, &lr14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = LR14_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - LR14_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LR14_CONFIG_EXAMPLE: 
   > Configures device for the LoRa P2P network mode.
 - LR14_EXAMPLE:
   > Performs a LoRa P2P example by exchanging messages with another LR 14 Click board.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LR14_POWER_UP:
        {
            if ( LR14_OK == lr14_power_up( &lr14 ) )
            {
                app_state = LR14_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR14_CONFIG_EXAMPLE:
        {
            if ( LR14_OK == lr14_config_example( &lr14 ) )
            {
                app_state = LR14_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR14_EXAMPLE:
        {
            lr14_example( &lr14 );
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
- Click.LR14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---

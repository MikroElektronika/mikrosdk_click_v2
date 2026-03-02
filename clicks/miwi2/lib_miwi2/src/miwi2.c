/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file miwi2.c
 * @brief MiWi 2 Click Driver.
 */

#include "miwi2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void miwi2_cfg_setup ( miwi2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->csdat = HAL_PIN_NC;
    cfg->csc = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->in0 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
}

err_t miwi2_init ( miwi2_t *ctx, miwi2_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    digital_out_init( &ctx->csc, cfg->csc );
    digital_out_init( &ctx->csdat, cfg->csdat );
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->in1, cfg->in1 );
    digital_in_init( &ctx->in0, cfg->in0 );

    /* Deassert CSCON */
    digital_out_high( &ctx->csc );

    /* Deassert CSDAT */
    digital_out_high( &ctx->csdat );

    /* reset */
    miwi2_reset( ctx );

    return SPI_MASTER_SUCCESS;
}

err_t miwi2_default_cfg ( miwi2_t *ctx ) 
{
    err_t error_flag = MIWI2_OK;

    /* GCONREG: Standby mode, 915-928 MHz band, VCOT=1, RPS=R1/P1/S1
     *   CMOD[7:5] = 001 (Standby)
     *   FBS[4:3]  = 01  (915-928 MHz)
     *   VCOT[2:1] = 01
     *   RPS[0]    = 0 */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_GCONREG, MIWI2_GCONREG_STBY_915_VCOT1_RSP1 );

    /* DMODREG: FSK modulation, Packet mode
     *   MODSEL[7:6] = 10  (FSK)
     *   DMODE0[5]   = 0
     *   OOKTYP[4:3] = 01 
     *   DMODE1[2]   = 1   (Packet mode: DMODE1=1, DMODE0=x)
     *   IFGAIN[1:0] = 00  (0 dB, maximum gain) */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_DMODREG, MIWI2_DMODREG_FSK_PACKET_MODE );
    
    /* FDEVREG: frequency deviation
     *   fdev = 12.8 MHz / (32 * (11 + 1)) = 33.3 kHz */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_FDEVREG, MIWI2_FDEVREG_33_KHZ );

    /* BRSREG: bit rate
     *   BRVAL = 39  ->  BR = 12.8 MHz / (64 * (39+1)) = 5 kbps */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_BRSREG, MIWI2_BRSREG_BIT_RATE_5KPBS );

    /* FIFOCREG: FIFO size = 64 bytes, FIFO threshold interrupt at 1 byte
     *   FSIZE[7:6] = 11  (64 bytes)
     *   FTINT[5:0] = 000001 (1 byte threshold) */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_FIFOCREG, MIWI2_FIFOCREG_FIFO_64_THR1 );

    /* PLL frequency dividers for 915 MHz 
     * Frequency formula: frf = (9/8) * 12.8 MHz * (75*(P1+1) + S1) / (R1+1)
     * With R1=0x77, P1=0x64, S1=0x32:
     *   frf = (9/8) * 12.8 MHz * (75*(100+1) + 50) / (119+1) = 915 MHz */ 
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_R1CREG, MIWI2_R1CREG_915_KHZ );
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_P1CREG, MIWI2_P1CREG_915_KHZ );
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_S1CREG, MIWI2_S1CREG_915_KHZ );

    /* FTXRXIREG: IRQ sources
     *   IRQ0RXS[7:6] = 00  -> Packet mode: IRQ0 = PLREADY (payload ready)
     *   IRQ1RXS[5:4] = 00  -> Packet mode: IRQ1 = CRCOK
     *   IRQ1TX[3]    = 1   -> Packet/Buffered TX: IRQ1 = TXDONE
     *   FIFOFULL[2]  = 0
     *   FIFOEMPTY[1] = 0
     *   FOVRRUN[0]   = 0 */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_FTXRXIREG, MIWI2_FTXRXIREG_RX_PLREADY_CRCOK_TX_TXDONE );

    /* FTPRIREG: FIFO fill method, PLL lock
     *   FIFOFM[7]    = 0   -> auto-fill on sync word detection
     *   FIFOFSC[6]   = 0
     *   TXDONE[5]    = 0
     *   IRQ0TXST[4]  = 0
     *   ENRIRQS[3]   = 0   
     *   RIRQS[2]     = 0
     *   LSTSPLL[1]   = 0   -> PLL lock status (W1C, writing 0 leaves it)
     *   LENPLL[0]    = 0   -> PLOCK pin output disabled */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_FTPRIREG, MIWI2_FTPRIREG_FIFO_SYNC_AUTOFILL );

    /* FILCREG: passive RC filter bandwidth and Butterworth filter
     *   POR default 0xA3 is suitable for 5 kbps / 100 kHz deviation  */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_FILCREG, MIWI2_FILCREG_5KPBS_100KHZ_DEV );

    /* SYNCREG: sync word control
     *   POLFILE N[7] = 0   -> polyphase filter off (FSK mode)
     *   BSYNCEN[6]   = 0   -> bit synchronizer enabled
     *   SYNCREN[5]   = 1   -> sync word recognition ON
     *   SYNCWSZ[4:3] = 11  -> 32-bit sync word
     *   SYNCTEN[2:1] = 00  -> 0 errors tolerated
     *   reserved[0]  = 0 */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_SYNCREG, MIWI2_SYNCREG_32BIT_SYNC_ENABLE );
    
    /* Sync word (32-bit) */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_SYNCV31REG, MIWI2_SYNCV31REG_VALUE );
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_SYNCV23REG, MIWI2_SYNCV23REG_VALUE );
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_SYNCV15REG, MIWI2_SYNCV15REG_VALUE );
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_SYNCV07REG, MIWI2_SYNCV07REG_VALUE );

    /* TXCONREG: interpolation filter cut-off = 200 kHz, TX power = 13 dBm
     *   TXIPOLFV[7:4] = 0111  -> fc = 200 kHz
     *   TXOPVAL[3:1]  = 000   -> +13 dBm (maximum output power)
     *   reserved[0]   = 0 */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_TXCONREG, MIWI2_TXCONREG_200_KHZ_13_DBM );

    /* CLKOREG: clock output to MCU
     *   CLKOCNTRL[7] = 1     -> enabled
     *   CLKOFREQ[6:2]= 01111 -> 427 kHz
     *   reserved[1:0]= 00 */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_CLKOREG, MIWI2_CLKOREG_427_KHZ );

    /* PLOADREG: payload length
     *   MCHSTREN[7]   = 0   -> Manchester encoding OFF
     *   PLDPLEN[6:0]  = 16  -> fixed packet payload = 16 bytes */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_PLOADREG, MIWI2_PLOADREG_PAYLOAD_16_BYTES );

    /* PKTCREG: packet format
     *   PKTLENF[7]   = 0    -> fixed length format
     *   PRESIZE[6:5] = 10   -> 3-byte preamble
     *   WHITEON[4]   = 0    -> data whitening OFF
     *   CHKCRCEN[3]  = 1    -> CRC check ON
     *   ADDFIL[2:1]  = 00   -> no address filtering
     *   STSCRCEN[0]  = 0    -> CRC status bit in FIFO OFF  */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_PKTCREG, MIWI2_PKTCREG_FIXED_LENGHT_CRC_ON );

    /* FCRCREG: FIFO CRC configuration
     *   ACFCRC[7] = 0  -> auto-clear FIFO on CRC failure (enabled when 0)
     *   FRWAXS[6] = 0  -> FIFO in write mode during Standby */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_FCRCREG, MIWI2_FCRCREG_WRITE_MODE_AUTO_CLEAR );
    
    /* PLL initialization sequence  
     *   enter frequency synthesizer mode
     *   wait for PLL to lock
     *   clear LSTPLL flag 
     *   go back to standby mode */
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_GCONREG, MIWI2_GCONREG_FS_915_VCOT1_RSP1 );  
    Delay_5ms ( );                                       
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_FTPRIREG, MIWI2_FTPRIREG_LSTSPLL_MASK );
    Delay_1ms ( );
    error_flag |= miwi2_reg_write( ctx, MIWI2_REG_GCONREG, MIWI2_GCONREG_STBY_915_VCOT1_RSP1 );  

    return error_flag;
}

err_t miwi2_reg_write ( miwi2_t *ctx, uint8_t addr, uint8_t value )
{  
    err_t error_flag = MIWI2_OK;
    uint8_t tx_buf[ 2 ] = { 0 };
    
    /* create command
     *   bit[7] = 0    ->  start 
     *   bit[6] = 0    ->  write
     *   bit[5...1]    ->  addr
     *   bit[0] = 0    ->  stop */
    tx_buf[ 0 ] = ( ( addr & 0x1F ) << 1 );
    tx_buf[ 1 ] = value;

    /* assert CSCON */
    digital_out_low( &ctx->csc );   

    if ( SPI_MASTER_SUCCESS != spi_master_write( &ctx->spi, tx_buf, 2 ) )
    {
        return SPI_MASTER_ERROR;
    }
    Delay_10ms ( );
    
    /* Deassert CSCON */
    digital_out_high( &ctx->csc );  

    return error_flag;
}

err_t miwi2_reg_read ( miwi2_t *ctx, uint8_t addr, uint8_t *value )
{ 
    err_t error_flag = MIWI2_OK;
    uint8_t cmd;
    uint8_t rx_val = 0;

    /* assert CSCON */
    digital_out_low( &ctx->csc );   
    
    /* create command
     *   bit[7] = 0    ->  start 
     *   bit[6] = 1    ->  read
     *   bit[5...1]    ->  addr
     *   bit[0] = 0    ->  stop */
    cmd = ( ( ( addr & 0x1F ) << 1 ) | 0x40 );  

    if ( SPI_MASTER_SUCCESS != spi_master_write_then_read( &ctx->spi, &cmd, 1, &rx_val, 1 ) )
    {
        return SPI_MASTER_ERROR;
    }
    
    /* Deassert CSCON */
    digital_out_high( &ctx->csc );

    *value = rx_val;
    return error_flag;
}

err_t miwi2_reg_update ( miwi2_t *ctx, uint8_t addr, uint8_t field_mask, uint8_t value_shifted )
{   
    err_t error_flag = MIWI2_OK;
    uint8_t reg_val;
    
    if ( SPI_MASTER_SUCCESS != miwi2_reg_read( ctx, addr, &reg_val ) )
    {
        return SPI_MASTER_ERROR;
    }
    
    /* update only specified bits */
    reg_val = ( ( reg_val & ( ~field_mask ) ) | ( value_shifted & field_mask ) );

    if ( SPI_MASTER_SUCCESS != miwi2_reg_write( ctx, addr, reg_val ) )
    {
        return SPI_MASTER_ERROR;
    }

    return error_flag;
}

err_t miwi2_fifo_write ( miwi2_t *ctx, uint8_t value )
{
    err_t error_flag = MIWI2_OK;

    /* assert CSDAT */
    digital_out_low( &ctx->csdat );

    if ( SPI_MASTER_SUCCESS != spi_master_write( &ctx->spi, &value, 1 ) )
    {
        return SPI_MASTER_ERROR;
    }

    /* Deassert CSDAT */
    digital_out_high( &ctx->csdat );

    return error_flag;
}

err_t miwi2_fifo_read ( miwi2_t *ctx, uint8_t *value )
{   
    err_t error_flag = MIWI2_OK;
    uint8_t rx_val;

    /* assert CSDAT */
    digital_out_low( &ctx->csdat );

    if ( SPI_MASTER_SUCCESS != spi_master_read( &ctx->spi, &rx_val, 1 ) )
    {
        return SPI_MASTER_ERROR;
    }

    /* Deassert CSDAT */
    digital_out_high( &ctx->csdat );

    *value = rx_val;

    return error_flag;
}

err_t miwi2_reg_set_bit ( miwi2_t *ctx, uint8_t addr, uint8_t bit_mask )
{   
    err_t error_flag = MIWI2_OK;
    uint8_t reg_val;

    if ( SPI_MASTER_SUCCESS != miwi2_reg_read( ctx, addr, &reg_val ) )
    {
        return SPI_MASTER_ERROR;
    }

    reg_val |= bit_mask;

    if ( SPI_MASTER_SUCCESS != miwi2_reg_write( ctx, addr, reg_val ) )
    {
        return SPI_MASTER_ERROR;
    }

    return error_flag;
}

err_t miwi2_reg_clear_bit ( miwi2_t *ctx, uint8_t addr, uint8_t bit_mask )
{
    err_t error_flag = MIWI2_OK;
    uint8_t reg_val;

    if ( SPI_MASTER_SUCCESS != miwi2_reg_read( ctx, addr, &reg_val ) )
    {
        return SPI_MASTER_ERROR;
    }

    reg_val &= ~bit_mask;

    if ( SPI_MASTER_SUCCESS != miwi2_reg_write( ctx, addr, reg_val ) )
    {
        return SPI_MASTER_ERROR;
    }

    return error_flag;
}

err_t miwi2_set_mode ( miwi2_t *ctx, uint8_t mode )
{
    return miwi2_reg_update( ctx, MIWI2_REG_GCONREG, MIWI2_GCONREG_CMOD_MASK, mode << 5 );
}

err_t miwi2_tx_packet ( miwi2_t *ctx, uint8_t *payload )
{
    uint8_t cnt;

    /* FIFO write mode */
    if ( MIWI2_OK != miwi2_reg_clear_bit( ctx, MIWI2_REG_FCRCREG, MIWI2_FCRCREG_FIFO_WRITE_MASK ) )
    {
        return MIWI2_ERROR;
    }
    Delay_5ms ( );

    /* Load FIFO */
    for ( cnt = 0; cnt < MIWI2_PAYLOAD_LEN; cnt++ )
    {
        if ( MIWI2_OK != miwi2_fifo_write( ctx, payload[ cnt ] ) )
        {
            return MIWI2_ERROR;
        }
        Delay_1ms ( );
        Delay_1ms ( );
    }
    Delay_10ms ( );

    /* TX mode */
    if ( MIWI2_OK != miwi2_set_mode( ctx, MIWI2_RF_TRANSMITTER ) )
    {
        return MIWI2_ERROR;
    }

    /* Wait for TXDONE on IRQ1 */
    uint16_t waited = 0;
    while ( waited < MIWI2_TX_TIMEOUT_MS )
    {
        if ( digital_in_read( &ctx->in1 ) )
        {
            break;
        }
        Delay_1ms ( );
        waited++;
    }

    /* Back to Standby */
    if ( MIWI2_OK != miwi2_set_mode( ctx, MIWI2_RF_STANDBY ) )
    {
        return MIWI2_ERROR;
    }
    Delay_5ms ( );

    return ( waited >= MIWI2_TX_TIMEOUT_MS ) ? MIWI2_ERROR : MIWI2_OK;
}

err_t miwi2_rx_packet ( miwi2_t *ctx, uint8_t *payload )
{
    uint8_t cnt;
    uint16_t waited = 0;

    /* Poll IRQ0 until payload ready or timeout */
    while ( !digital_in_read( &ctx->in0 ) )
    {
        if ( ++waited > MIWI2_RX_TIMEOUT_MS )
        {
            return MIWI2_ERROR;
        }
        Delay_1ms ( );
    }

    /* Go to Standby to read FIFO safely */
    if ( MIWI2_OK != miwi2_set_mode( ctx, MIWI2_RF_STANDBY ) )
    {
        return MIWI2_ERROR;
    }
    Delay_5ms ( );

    /* FIFO read mode */
    if ( MIWI2_OK != miwi2_reg_set_bit( ctx, MIWI2_REG_FCRCREG, MIWI2_FCRCREG_FIFO_WRITE_MASK ) )
    {
        return MIWI2_ERROR;
    }
    Delay_5ms ( );

    /* Read payload from FIFO */
    for ( cnt = 0; cnt < MIWI2_PAYLOAD_LEN; cnt++ )
    {
        if ( MIWI2_OK != miwi2_fifo_read( ctx, &payload[ cnt ] ) )
        {
            return MIWI2_ERROR;
        }
        Delay_1ms ( );
        Delay_1ms ( );
    }

    /* Restore FIFO write mode */
    if ( MIWI2_OK != miwi2_reg_clear_bit( ctx, MIWI2_REG_FCRCREG, MIWI2_FCRCREG_FIFO_WRITE_MASK ) )
    {
        return MIWI2_ERROR;
    }
    Delay_5ms ( );

    /* Back to RX mode */
    if ( MIWI2_OK != miwi2_set_mode( ctx, MIWI2_RF_RECEIVER ) )
    {
        return MIWI2_ERROR;
    }

    return MIWI2_OK;
}

void miwi2_reset ( miwi2_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_1ms ( );
    digital_out_low( &ctx->rst );
    Delay_10ms ( );
}

// ------------------------------------------------------------------------- END

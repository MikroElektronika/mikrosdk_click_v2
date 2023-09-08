#include "nanobeacon_adv.h"
#include "string.h"

typedef struct 
{
    uint16_t size_in_word;
    uint8_t cs_offset[ 3 ];
    uint8_t adv_cnt;
    adv_ctl_t adv_ctl_struct;
    
} adv_ctl_table_t;

static uint8_t adv_data_buffer[ 96 ] = { 0 };
static adv_ctl_table_t adv_ctl_table = { 0 };

static uint16_t nanobeacon_get_packet_len ( pkt_ctl_t *pkt_ctl );

static uint16_t nanobeacon_get_cs_only_len ( adv_ctl_t *adv_ctl );

static uint16_t nanobeacon_get_adv_ctl_len ( adv_ctl_t *adv_ctl );

static uint16_t nanobeacon_f1to7_to_raw ( pkt_f1to7_t *pkt_f, pkt_ctl_t *pkt_ctl, uint8_t *buffer );

static uint16_t nanobeacon_pkt_ctl_to_raw ( pkt_ctl_t *pkt_ctl, uint8_t *buffer );

static uint16_t nanobeacon_adv_ctl_to_raw ( adv_ctl_t *adv_ctl, uint8_t cs_offset, uint8_t *buffer );

void nanobeacon_adv_data_reset ( void )
{
    memset( &adv_ctl_table, 0, sizeof ( adv_ctl_table_t ) );
    adv_ctl_table.cs_offset[ 0 ] = 6;
    adv_ctl_table.adv_ctl_struct.pkt_ctl.data_buffer = &adv_data_buffer[ 0 ];
    adv_ctl_table.adv_ctl_struct.pkt_ctl.pkt_f0.header[ 0 ] = 0x02;
}

void nanobeacon_adv_tx_set ( uint32_t tx_interval, adv_channel_ctl_t ch_ctl, adv_mode_t mode )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    tx_interval = tx_interval * 1000ul / 625;
    if ( tx_interval > 0xFFFFFF ) 
    {
        tx_interval = 0xFFFFFF;
    }
    adv_ctl->adv_interval[ 0 ] = ( uint8_t ) ( tx_interval & 0xFF );
    adv_ctl->adv_interval[ 1 ] = ( uint8_t ) ( ( tx_interval >> 8 ) & 0xFF );
    adv_ctl->adv_interval[ 2 ] = ( uint8_t ) ( ( tx_interval >> 16 ) & 0xFF );
    adv_ctl->byte0.uni.adv_type = mode;
    adv_ctl->byte8.uni.adv_channel_control = ch_ctl;
}

void nanobeacon_adv_address_set ( address_type_t addr_type, uint8_t *mac_addr, 
                                  uint16_t addr_gen_interval, uint8_t key_idx )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    if ( ADDR_NOT_PRESENT == addr_type ) 
    {
        adv_ctl->pkt_ctl.pkt_f0.addr_not_present = 1;
    }
    else 
    {
        adv_ctl->addr_private_data.uni.adv_addr_type = addr_type;
        adv_ctl->addr_private_data.uni.addr_key_sel = key_idx;
        adv_ctl->addr_gen_interval[ 0 ] = ( uint8_t ) ( addr_gen_interval & 0xFF );
        adv_ctl->addr_gen_interval[ 1 ] = ( uint8_t ) ( ( addr_gen_interval >> 8 ) & 0xFF );
        if ( mac_addr ) 
        {
            memcpy ( adv_ctl->adv_addr, mac_addr, 6 );
        }
        if ( ADDR_PUBLIC == addr_type ) 
        {
            adv_ctl->pkt_ctl.pkt_f0.header[ 0 ] = 0x02;
        }
        else 
        {
            adv_ctl->pkt_ctl.pkt_f0.header[ 0 ] = 0x42;
        }
    }
}

int32_t nanobeacon_adv_add_data ( uint8_t *data_in, uint8_t length, uint8_t encrypt_en )
{
    adv_ctl_t *adv_ctl = &adv_ctl_table.adv_ctl_struct;
    pkt_f1to7_t *f1to7 = adv_ctl->pkt_ctl.pkt_f;
    uint16_t tmp = 0;
    if ( ( 0 == data_in ) || ( length > 31 ) ) 
    {
        return RET_INVALID_PARAMETER;
    }
    if ( ( adv_ctl->pkt_ctl.cur_pos + length ) >= 31 ) 
    {
        return RET_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < adv_ctl->pkt_ctl.f1to7_cnt; cnt++ ) 
    {
        f1to7 = &adv_ctl->pkt_ctl.pkt_f[ cnt ];
        tmp += f1to7->length;
    }
    if ( ( tmp + length ) > 31 ) 
    {
        return RET_ERROR;
    }
    if ( adv_ctl->pkt_ctl.f1to7_cnt < 7 ) 
    {
        f1to7 = &adv_ctl->pkt_ctl.pkt_f[ adv_ctl->pkt_ctl.f1to7_cnt ];
        f1to7->data_src = ADV_DATA_TYPE_PREDEF;
        f1to7->endian = 0;
        f1to7->encryption = encrypt_en;
        f1to7->encryption_last = encrypt_en;
        if ( encrypt_en && ( adv_ctl->pkt_ctl.f1to7_cnt > 0 ) ) 
        {
            adv_ctl->pkt_ctl.pkt_f[ adv_ctl->pkt_ctl.f1to7_cnt - 1 ].encryption_last = 0;
        }
        f1to7->length = length;
        memcpy ( adv_ctl->pkt_ctl.data_buffer + adv_ctl->pkt_ctl.cur_pos, data_in, length );
        f1to7->data_offset = adv_ctl->pkt_ctl.cur_pos;
        adv_ctl->pkt_ctl.cur_pos += length;
        
        adv_ctl->pkt_ctl.f1to7_cnt++;

        return RET_OK;
    }
    return RET_ERROR;
}

int32_t nanobeacon_adv_add_cnt ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    pkt_ctl_t *pkt_ctl = &adv_ctl->pkt_ctl;
    pkt_f1to7_t* f1to7 = 0;
    uint16_t tmp = 0;
    if ( length > 4 ) 
    {
        return RET_INVALID_PARAMETER;
    }
    for ( uint8_t cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        tmp += pkt_ctl->pkt_f[ cnt ].length;
    }
    if ( ( tmp + length ) > 31 ) 
    {
        return RET_ERROR;
    }
    if ( pkt_ctl->f1to7_cnt < 7 ) 
    {
        f1to7 = &pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt ];
        f1to7->data_src = ADV_DATA_TYPE_ADV_EVNT_CNT;
        f1to7->endian = big_endian;
        f1to7->encryption = encrypt_en;
        f1to7->encryption_last = encrypt_en;
        if ( encrypt_en && ( pkt_ctl->f1to7_cnt > 0 ) ) 
        {
            pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt - 1 ].encryption_last = 0;
        }
        f1to7->length = length;
        adv_ctl->pkt_ctl.f1to7_cnt++;
        return RET_OK;
    }
    return RET_ERROR;
}

int32_t nanobeacon_adv_add_sec_cnt ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    pkt_ctl_t* pkt_ctl = &adv_ctl->pkt_ctl;
    pkt_f1to7_t* f1to7 = 0;
    uint16_t tmp = 0;
    if ( length > 4 ) 
    {
        return RET_INVALID_PARAMETER;
    }
    for ( uint8_t cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        tmp += pkt_ctl->pkt_f[ cnt ].length;
    }
    if ( ( tmp + length ) > 31 ) 
    {
        return RET_ERROR;
    }
    if ( pkt_ctl->f1to7_cnt < 7 ) 
    {
        f1to7 = &pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt ];
        f1to7->data_src = ADV_DATA_TYPE_TIMER;
        f1to7->uni.timer_sel = 1;
        f1to7->endian = big_endian;
        f1to7->encryption = encrypt_en;
        f1to7->encryption_last = encrypt_en;
        if ( encrypt_en && ( pkt_ctl->f1to7_cnt > 0 ) ) 
        {
            pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt - 1 ].encryption_last = 0;
        }
        f1to7->length = length;
        adv_ctl->pkt_ctl.f1to7_cnt++;
        return RET_OK;
    }
    return RET_ERROR;
}

int32_t nanobeacon_adv_add_100ms_cnt ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    pkt_ctl_t* pkt_ctl = &adv_ctl->pkt_ctl;
    pkt_f1to7_t* f1to7 = 0;
    uint16_t tmp = 0;
    if ( length > 4 ) 
    {
        return RET_INVALID_PARAMETER;
    }
    for ( uint8_t cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        tmp += pkt_ctl->pkt_f[ cnt ].length;
    }
    if ( ( tmp + length ) > 31 ) 
    {
        return RET_ERROR;
    }
    if ( pkt_ctl->f1to7_cnt < 7 ) 
    {
        f1to7 = &pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt ];
        f1to7->data_src = ADV_DATA_TYPE_TIMER;
        f1to7->uni.timer_sel = 0;
        f1to7->endian = big_endian;
        f1to7->encryption = encrypt_en;
        f1to7->encryption_last = encrypt_en;
        if ( encrypt_en && ( pkt_ctl->f1to7_cnt > 0 ) ) 
        {
            pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt - 1 ].encryption_last = 0;
        }
        f1to7->length = length;
        adv_ctl->pkt_ctl.f1to7_cnt++;
        return RET_OK;
    }
    return RET_ERROR;
}

int32_t nanobeacon_adv_add_gpio_stat ( uint8_t encrypt_en )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    pkt_ctl_t* pkt_ctl = &adv_ctl->pkt_ctl;
    pkt_f1to7_t* f1to7 = 0;
    uint16_t tmp = 0;
    for ( uint8_t cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        tmp += pkt_ctl->pkt_f[ cnt ].length;
    }
    if ( ( tmp + 1 ) > 31 ) 
    {
        return RET_ERROR;
    }
    if ( pkt_ctl->f1to7_cnt < 7 ) 
    {
        f1to7 = &pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt ];
        f1to7->data_src = ADV_DATA_TYPE_GPIO_VAL;
        f1to7->endian = 0;
        f1to7->encryption = encrypt_en;
        f1to7->encryption_last = encrypt_en;
        if ( encrypt_en && ( pkt_ctl->f1to7_cnt > 0 ) ) 
        {
            pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt - 1 ].encryption_last = 0;
        }
        f1to7->length = 1;
        adv_ctl->pkt_ctl.f1to7_cnt++;
        return RET_OK;
    }
    return RET_ERROR;
}

int32_t nanobeacon_adv_add_vcc ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    pkt_ctl_t* pkt_ctl = &adv_ctl->pkt_ctl;
    pkt_f1to7_t* f1to7 = 0;
    uint16_t tmp = 0;
    if ( length > 4 ) 
    {
        return RET_INVALID_PARAMETER;
    }
    for ( uint8_t cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        tmp += pkt_ctl->pkt_f[ cnt ].length;
    }
    if ( ( tmp + length ) > 31 ) 
    {
        return RET_ERROR;
    }
    if ( pkt_ctl->f1to7_cnt < 7 ) 
    {
        f1to7 = &pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt ];
        f1to7->data_src = ADV_DATA_TYPE_VBAT;
        f1to7->endian = big_endian;
        f1to7->encryption = encrypt_en;
        f1to7->encryption_last = encrypt_en;
        if ( encrypt_en && ( pkt_ctl->f1to7_cnt > 0 ) ) 
        {
            pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt - 1 ].encryption_last = 0;
        }
        f1to7->length = length;
        adv_ctl->pkt_ctl.f1to7_cnt++;
        return RET_OK;
    }
    return RET_ERROR;
}

int32_t nanobeacon_adv_add_temp ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en )
{
    adv_ctl_t* adv_ctl = &adv_ctl_table.adv_ctl_struct;
    pkt_ctl_t* pkt_ctl = &adv_ctl->pkt_ctl;
    pkt_f1to7_t* f1to7 = 0;
    uint16_t tmp = 0;
    if ( length > 4 ) 
    {
        return RET_INVALID_PARAMETER;
    }
    for ( uint8_t cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        tmp += pkt_ctl->pkt_f[ cnt ].length;
    }
    if ( ( tmp + length ) > 31 ) 
    {
        return RET_ERROR;
    }
    if ( pkt_ctl->f1to7_cnt < 7 ) 
    {
        f1to7 = &pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt ];
        f1to7->data_src = ADV_DATA_TYPE_TEMP;
        f1to7->endian = big_endian;
        f1to7->encryption = encrypt_en;
        f1to7->encryption_last = encrypt_en;
        if ( encrypt_en && ( pkt_ctl->f1to7_cnt > 0 ) ) 
        {
            pkt_ctl->pkt_f[ pkt_ctl->f1to7_cnt - 1 ].encryption_last = 0;
        }
        f1to7->length = length;
        adv_ctl->pkt_ctl.f1to7_cnt++;
        return RET_OK;
    }
    return RET_ERROR;
}

uint16_t nanobeacon_adv_data_to_raw ( uint8_t *buffer )
{
    adv_ctl_t *adv_ctl = &adv_ctl_table.adv_ctl_struct;
    uint8_t adv_set_idx = 0;
    uint16_t total_size = 0;
    adv_ctl_table.size_in_word = 0;
    if ( 0 != adv_ctl->pkt_ctl.f1to7_cnt ) 
    {
        adv_ctl_table.cs_offset[ adv_set_idx ] = total_size + 6;
        total_size += nanobeacon_adv_ctl_to_raw ( adv_ctl, adv_ctl_table.cs_offset[ adv_set_idx ], buffer );
        adv_set_idx++;
    }
    adv_ctl_table.adv_cnt = adv_set_idx;
    if ( 1 == ( total_size % 2 ) ) 
    {
        buffer[ total_size + 6 ] = 0;
        total_size += 1;
    }

    if ( total_size > 0 ) 
    {
        adv_ctl_table.size_in_word = total_size / 2 + 2;
        buffer[ 0 ] = adv_ctl_table.size_in_word & 0xFF;
        buffer[ 1 ] = ( adv_ctl_table.size_in_word >> 8 ) & 0xFF;
        buffer[ 2 ] = adv_set_idx;
        buffer[ 3 ] = adv_ctl_table.cs_offset[ 0 ];
        buffer[ 4 ] = adv_ctl_table.cs_offset[ 1 ];
        buffer[ 5 ] = adv_ctl_table.cs_offset[ 2 ];
    }
    return ( total_size + 6 );
}

static uint16_t nanobeacon_get_packet_len ( pkt_ctl_t *pkt_ctl )
{
    uint16_t length = 3;
    if ( pkt_ctl->byte0.uni.sync_pattern_en ) 
    {
        length += 4;
    }
    length += ( 1 + pkt_ctl->pkt_f0.header_len );
    for ( uint8_t cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        length += 2;
        if ( ADV_DATA_TYPE_PREDEF == pkt_ctl->pkt_f[ cnt ].data_src ) 
        {
            length += pkt_ctl->pkt_f[ cnt ].length;
        }
        else if ( ADV_DATA_TYPE_REG_DATA == pkt_ctl->pkt_f[ cnt ].data_src ) 
        {
            length += 2;
        }
    }
    return length;
}

static uint16_t nanobeacon_get_cs_only_len ( adv_ctl_t *adv_ctl )
{
    uint16_t length = 9;
    if ( 1 == adv_ctl->byte0.uni.adv_type ) 
    {
        length += 5;
    }
    length++;
    if ( ADDR_PUBLIC == adv_ctl->addr_private_data.uni.adv_addr_type ) 
    {
        length += 6;
    }
    else if ( ( ADDR_RANDOM_NON_RESOLVABLE == adv_ctl->addr_private_data.uni.adv_addr_type ) ||
              ( ADDR_RANDOM_RESOLVABLE == adv_ctl->addr_private_data.uni.adv_addr_type ) ) 
    {
        length += 2;
    }
    return length;
}

static uint16_t nanobeacon_get_adv_ctl_len ( adv_ctl_t *adv_ctl )
{
    uint16_t length = 0;
    if ( 0 == adv_ctl->pkt_ctl.f1to7_cnt ) 
    {
        return 0;
    }
    length = nanobeacon_get_cs_only_len ( adv_ctl );
    length += nanobeacon_get_packet_len ( &adv_ctl->pkt_ctl );
    return length;
}

static uint16_t nanobeacon_f1to7_to_raw ( pkt_f1to7_t *pkt_f, pkt_ctl_t *pkt_ctl, uint8_t *buffer )
{
    uint16_t idx = 0;
    uint16_t tmp = 0;
    uint8_t *pdata = 0;
    buffer[ idx++ ] = ( ( pkt_f->encryption_last & 0x01 ) << 7 ) | ( ( pkt_f->encryption & 0x01 ) << 6 ) | 
                      ( ( pkt_f->endian & 0x01 ) << 5 ) | ( pkt_f->data_src & 0x1F );
    switch ( pkt_f->data_src )
    {
        case ADV_DATA_TYPE_PREDEF:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 1 ) << 6 ) | 
                              ( pkt_f->length & 0x3F );
            pdata = pkt_ctl->data_buffer + pkt_f->data_offset;
            for ( uint16_t cnt = 0; cnt < pkt_f->length; cnt++ ) 
            {
                buffer[ idx++ ] = pdata[ cnt ];
            }
            break;
        }
        case ADV_DATA_TYPE_TIMER:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( ( pkt_f->length & 0x07 ) << 3 ) | ( pkt_f->uni.timer_sel & 0x07 );
            break;
        }
        case ADV_DATA_TYPE_RAND:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( ( pkt_f->length & 0x0F ) << 2 ) | ( pkt_f->uni.rand_num_sel & 0x03 );
            break;
        }
        case ADV_DATA_TYPE_TEMP:
        case ADV_DATA_TYPE_VBAT:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( ( pkt_f->length - 1 ) & 0x01 );
            break;
        }
        case ADV_DATA_TYPE_SENSOR:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( ( pkt_f->length & 0x03 ) << 4 ) | ( pkt_f->uni.sensor_idx & 0x0F );
            break;
        }
        case ADV_DATA_TYPE_TAG:
        {
            buffer[ idx++ ] =  ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                               ( pkt_f->length & 0x0F );
            break;
        }
        case ADV_DATA_TYPE_MTS_DATA:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( ( pkt_f->length & 0x03 ) << 4 ) | ( pkt_f->uni.sensor_idx & 0x0F );
            break;
        }
        case ADV_DATA_TYPE_CUS_UUID:
        case ADV_DATA_TYPE_INP_UUID:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( pkt_f->length & 0x07 );
            break;
        }
        case ADV_DATA_TYPE_EID:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 8;
            break;
        }
        case ADV_DATA_TYPE_ADV_EVNT_CNT:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( pkt_f->length & 0x3F );
            break;
        }
        case ADV_DATA_TYPE_SLEEP_CNT:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( pkt_f->length & 0x1 );
            break;
        }
        case ADV_DATA_TYPE_GPIO_VAL:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( ( pkt_f->length & 0x01 ) << 2 ) | ( pkt_f->uni.gpio_sel & 0x03 );
            break;
        }
        case ADV_DATA_TYPE_PLSDTCT:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( ( ( pkt_f->length - 1 ) & 0x01 ) << 1 ) | ( pkt_f->uni.plsdtct_sel & 0x01 );
            break;
        }
        case ADV_DATA_TYPE_GPIO_CNT:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) |
                              ( pkt_f->length & 0x3 );
            break;
        }
        case ADV_DATA_TYPE_REG_DATA:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( pkt_f->length & 0x3F );
            if ( pkt_f->endian ) 
            {
                tmp = pkt_f->uni.reg_addr + pkt_f->length - 1;
            }
            else 
            {
                tmp = pkt_f->uni.reg_addr;
            }
            buffer[ idx++ ] = tmp & 0xFF;
            buffer[ idx++ ] = tmp & 0xFF;
            break;
        }
        default:
        {
            buffer[ idx++ ] = ( ( pkt_f->msb_lsb_sel & 1 ) << 7 ) | ( ( pkt_f->encryption_output_order & 0x01 ) << 6 ) | 
                              ( pkt_f->length & 0x3F );
            break;
        }
    }
    return idx;
}

static uint16_t nanobeacon_pkt_ctl_to_raw ( pkt_ctl_t *pkt_ctl, uint8_t *buffer )
{
    uint16_t idx = 0;
    uint16_t tmp = 0;
    uint16_t cnt = 0;
    pkt_ctl->byte0.uni.num_fields = 1 + pkt_ctl->f1to7_cnt;
    buffer[ idx++ ] = pkt_ctl->byte0.data_buf;
    buffer[ idx++ ] = pkt_ctl->byte1.data_buf;
    buffer[ idx++ ] = pkt_ctl->byte2.data_buf;
    if ( pkt_ctl->byte0.uni.sync_pattern_en ) 
    {
        buffer[ idx++ ] = pkt_ctl->sync_pattern & 0xFF;
        buffer[ idx++ ] = ( pkt_ctl->sync_pattern >> 8 ) & 0xFF;
        buffer[ idx++ ] = ( pkt_ctl->sync_pattern >> 16 ) & 0xFF;
        buffer[ idx++ ] = ( pkt_ctl->sync_pattern >> 24 ) & 0xFF;
    }
    /*field 0*/
    for ( cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        tmp += pkt_ctl->pkt_f[ cnt ].length;
    }
    if ( pkt_ctl->pkt_f0.addr_not_present ) 
    {
        pkt_ctl->pkt_f0.header[ 1 ] = tmp;
    }
    else
    {
        pkt_ctl->pkt_f0.header[ 1 ] = tmp + 6;
    }
    pkt_ctl->pkt_f0.header_len = 2;
    buffer[ idx++ ] = ( ( pkt_ctl->pkt_f0.header_len - 2 ) & 0x03 ) | ( ( pkt_ctl->pkt_f0.addr_not_present & 0x01 ) << 2 );
    for ( cnt = 0; cnt < pkt_ctl->pkt_f0.header_len; cnt++ ) 
    {
        buffer[ idx++ ] = pkt_ctl->pkt_f0.header[ cnt ];
    }

    /*field 1 ~ 7*/
    for ( cnt = 0; cnt < pkt_ctl->f1to7_cnt; cnt++ ) 
    {
        idx += nanobeacon_f1to7_to_raw ( &pkt_ctl->pkt_f[ cnt ], pkt_ctl, buffer + idx );
    }
    return idx;
}

static uint16_t nanobeacon_adv_ctl_to_raw ( adv_ctl_t *adv_ctl, uint8_t cs_offset, uint8_t *buffer )
{
    uint16_t idx = 0;
    uint8_t *pbuff = buffer + cs_offset;
    if ( 0 == adv_ctl->pkt_ctl.f1to7_cnt ) 
    {
        return 0;
    }
    adv_ctl->packet_table_location = cs_offset + nanobeacon_get_cs_only_len ( adv_ctl );
    pbuff[ idx++ ] = adv_ctl->byte0.data_buf;
    pbuff[ idx++ ] = adv_ctl->gpio_source;
    pbuff[ idx++ ] = adv_ctl->byte2;
    pbuff[ idx++ ] = adv_ctl->adv_interval[ 0 ];
    pbuff[ idx++ ] = adv_ctl->adv_interval[ 1 ];
    pbuff[ idx++ ] = adv_ctl->adv_interval[ 2 ];
    pbuff[ idx++ ] = adv_ctl->packet_table_location & 0xFF;
    pbuff[ idx++ ] = ( adv_ctl->packet_table_location >> 8 ) & 0xFF;
    pbuff[ idx++ ] = adv_ctl->byte8.data_buf;
    if ( 1 == adv_ctl->byte0.uni.adv_type ) 
    {
        pbuff[ idx++ ] = adv_ctl->evnt_wakeup_period[ 0 ];
        pbuff[ idx++ ] = adv_ctl->evnt_wakeup_period[ 1 ];
        pbuff[ idx++ ] = adv_ctl->evnt_wakeup_period[ 2 ];
        pbuff[ idx++ ] = adv_ctl->num_event_control[ 0 ];
        pbuff[ idx++ ] = adv_ctl->num_event_control[ 1 ];
    }
    pbuff[ idx++ ] = adv_ctl->addr_private_data.data_buf;
    if ( ADDR_PUBLIC == adv_ctl->addr_private_data.uni.adv_addr_type ) 
    {
        for ( uint8_t cnt = 0; cnt < 6; cnt++ ) 
        {
            pbuff[ idx++ ] = adv_ctl->adv_addr[ cnt ];
        }
    }
    else if ( ( ADDR_RANDOM_NON_RESOLVABLE == adv_ctl->addr_private_data.uni.adv_addr_type ) ||
              ( ADDR_RANDOM_RESOLVABLE == adv_ctl->addr_private_data.uni.adv_addr_type ) ) 
    {
        pbuff[ idx++ ] = adv_ctl->addr_gen_interval[ 0 ];
        pbuff[ idx++ ] = adv_ctl->addr_gen_interval[ 1 ];
    }
    idx += nanobeacon_pkt_ctl_to_raw ( &adv_ctl->pkt_ctl, pbuff + idx );
    return idx;
}

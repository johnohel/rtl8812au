/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __RTW_MI_H_
#define __RTW_MI_H_

void rtw_mi_update_union_chan_inf(_adapter *adapter, u8 ch, u8 offset , u8 bw);
int rtw_mi_get_ch_setting_union(_adapter *adapter, u8 *ch, u8 *bw, u8 *offset);
int rtw_mi_get_ch_setting_union_no_self(_adapter *adapter, u8 *ch, u8 *bw, u8 *offset);

struct mi_state {
	u8 sta_num;			/*WIFI_FW_STATION_STATE*/
	u8 ld_sta_num;		/*WIFI_FW_STATION_STATE |_FW_LINKED*/
	u8 lg_sta_num;		/*WIFI_FW_STATION_STATE |_FW_UNDER_LINKING*/
	u8 ap_num;			/*WIFI_FW_AP_STATE|_FW_LINKED*/
	u8 ld_ap_num;		/*WIFI_FW_AP_STATE|_FW_LINKED && asoc_sta_count > 2*/
	u8 adhoc_num;		/* WIFI_FW_ADHOC_STATE */
	u8 ld_adhoc_num;	/* WIFI_FW_ADHOC_STATE && asoc_sta_count > 2 */
	u8 uwps_num;		/*WIFI_UNDER_WPS*/

#ifdef CONFIG_IOCTL_CFG80211
	#ifdef CONFIG_P2P
	u8 roch_num;
	#endif
	u8 mgmt_tx_num;
#endif

	u8 union_ch;
	u8 union_bw;
	u8 union_offset;
};

#define MSTATE_STA_NUM(_mstate)			((_mstate)->sta_num)
#define MSTATE_STA_LD_NUM(_mstate)		((_mstate)->ld_sta_num)
#define MSTATE_STA_LG_NUM(_mstate)		((_mstate)->lg_sta_num)
#define MSTATE_AP_NUM(_mstate)			((_mstate)->ap_num)
#define MSTATE_AP_LD_NUM(_mstate)		((_mstate)->ld_ap_num)
#define MSTATE_ADHOC_NUM(_mstate)		((_mstate)->adhoc_num)
#define MSTATE_ADHOC_LD_NUM(_mstate)	((_mstate)->ld_adhoc_num)
#define MSTATE_WPS_NUM(_mstate)			((_mstate)->uwps_num)

#if defined(CONFIG_IOCTL_CFG80211) && defined(CONFIG_P2P)
#define MSTATE_ROCH_NUM(_mstate)		((_mstate)->roch_num)
#else
#define MSTATE_ROCH_NUM(_mstate)		0
#endif

#if defined(CONFIG_IOCTL_CFG80211)
#define MSTATE_MGMT_TX_NUM(_mstate)		((_mstate)->mgmt_tx_num)
#else
#define MSTATE_MGMT_TX_NUM(_mstate)		0
#endif

#define MSTATE_U_CH(_mstate)			((_mstate)->union_ch)
#define MSTATE_U_BW(_mstate)			((_mstate)->union_bw)
#define MSTATE_U_OFFSET(_mstate)		((_mstate)->union_offset)

#define rtw_mi_get_union_chan(adapter)	adapter_to_dvobj(adapter)->iface_state.union_ch
#define rtw_mi_get_union_bw(adapter)		adapter_to_dvobj(adapter)->iface_state.union_bw
#define rtw_mi_get_union_offset(adapter)	adapter_to_dvobj(adapter)->iface_state.union_offset

#define rtw_mi_get_assoced_sta_num(adapter)	DEV_STA_LD_NUM(adapter_to_dvobj(adapter))
#define rtw_mi_get_ap_num(adapter)			DEV_AP_NUM(adapter_to_dvobj(adapter))

/* For now, not return union_ch/bw/offset */
void rtw_mi_status(_adapter *adapter, struct mi_state *mstate);
void rtw_mi_status_no_self(_adapter *adapter, struct mi_state *mstate);

void rtw_mi_update_iface_status(struct mlme_priv *pmlmepriv, sint state);

u8 rtw_mi_netif_stop_queue(_adapter *padapter, bool carrier_off);
u8 rtw_mi_buddy_netif_stop_queue(_adapter *padapter, bool carrier_off);

u8 rtw_mi_netif_wake_queue(_adapter *padapter);
u8 rtw_mi_buddy_netif_wake_queue(_adapter *padapter);

u8 rtw_mi_netif_carrier_on(_adapter *padapter);
u8 rtw_mi_buddy_netif_carrier_on(_adapter *padapter);

void rtw_mi_scan_abort(_adapter *adapter, bool bwait);
void rtw_mi_buddy_scan_abort(_adapter *adapter, bool bwait);
void rtw_mi_start_drv_threads(_adapter *adapter);
void rtw_mi_buddy_start_drv_threads(_adapter *adapter);
void rtw_mi_stop_drv_threads(_adapter *adapter);
void rtw_mi_buddy_stop_drv_threads(_adapter *adapter);
void rtw_mi_cancel_all_timer(_adapter *adapter);
void rtw_mi_buddy_cancel_all_timer(_adapter *adapter);
void rtw_mi_reset_drv_sw(_adapter *adapter);
void rtw_mi_buddy_reset_drv_sw(_adapter *adapter);

extern void rtw_intf_start(_adapter *adapter);
extern void rtw_intf_stop(_adapter *adapter);
void rtw_mi_intf_start(_adapter *adapter);
void rtw_mi_buddy_intf_start(_adapter *adapter);
void rtw_mi_intf_stop(_adapter *adapter);
void rtw_mi_buddy_intf_stop(_adapter *adapter);

void rtw_mi_suspend_free_assoc_resource(_adapter *adapter);
void rtw_mi_buddy_suspend_free_assoc_resource(_adapter *adapter);

#ifdef CONFIG_SET_SCAN_DENY_TIMER
void rtw_mi_set_scan_deny(_adapter *adapter, u32 ms);
void rtw_mi_buddy_set_scan_deny(_adapter *adapter, u32 ms);
#else
#define rtw_mi_set_scan_deny(adapter, ms) do {} while (0)
#define rtw_mi_buddy_set_scan_deny(adapter, ms) do {} while (0)
#endif

u8 rtw_mi_is_scan_deny(_adapter *adapter);
u8 rtw_mi_buddy_is_scan_deny(_adapter *adapter);

u8 rtw_mi_issue_nulldata(_adapter *padapter, unsigned char *da, unsigned int power_mode, int try_cnt, int wait_ms);
u8 rtw_mi_buddy_issue_nulldata(_adapter *padapter, unsigned char *da, unsigned int power_mode, int try_cnt, int wait_ms);

void rtw_mi_beacon_update(_adapter *padapter);
void rtw_mi_buddy_beacon_update(_adapter *padapter);

void rtw_mi_hal_dump_macaddr(_adapter *padapter);
void rtw_mi_buddy_hal_dump_macaddr(_adapter *padapter);

#ifdef CONFIG_PCI_HCI
void rtw_mi_xmit_tasklet_schedule(_adapter *padapter);
void rtw_mi_buddy_xmit_tasklet_schedule(_adapter *padapter);
#endif

u8 rtw_mi_busy_traffic_check(_adapter *padapter, bool check_sc_interval);
u8 rtw_mi_buddy_busy_traffic_check(_adapter *padapter, bool check_sc_interval);

u8 rtw_mi_check_mlmeinfo_state(_adapter *padapter, u32 state);
u8 rtw_mi_buddy_check_mlmeinfo_state(_adapter *padapter, u32 state);

u8 rtw_mi_check_fwstate(_adapter *padapter, sint state);
u8 rtw_mi_buddy_check_fwstate(_adapter *padapter, sint state);
enum {
	MI_LINKED,
	MI_ASSOC,
	MI_UNDER_WPS,
	MI_AP_MODE,
	MI_AP_ASSOC,
	MI_ADHOC,
	MI_ADHOC_ASSOC,
	MI_STA_NOLINK, /* this is misleading, but not used now */
	MI_STA_LINKED,
	MI_STA_LINKING,
};
u8 rtw_mi_check_status(_adapter *adapter, u8 type);

void dump_dvobj_mi_status(void *sel, const char *fun_name, _adapter *adapter);
#ifdef DBG_IFACE_STATUS
#define DBG_IFACE_STATUS_DUMP(adapter)	dump_dvobj_mi_status(RTW_DBGDUMP, __func__, adapter)
#endif
void dump_mi_status(void *sel, struct dvobj_priv *dvobj);

u8 rtw_mi_traffic_statistics(_adapter *padapter);
u8 rtw_mi_check_miracast_enabled(_adapter *padapter);

#ifdef CONFIG_XMIT_THREAD_MODE
u8 rtw_mi_check_pending_xmitbuf(_adapter *padapter);
u8 rtw_mi_buddy_check_pending_xmitbuf(_adapter *padapter);
#endif

#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
#ifdef CONFIG_RTL8822B
	#include <rtl8822b_hal.h>
#else
	extern s32 _dequeue_writeport(PADAPTER padapter);
#endif
u8 rtw_mi_dequeue_writeport(_adapter *padapter);
u8 rtw_mi_buddy_dequeue_writeport(_adapter *padapter);
#endif

void rtw_mi_adapter_reset(_adapter *padapter);
void rtw_mi_buddy_adapter_reset(_adapter *padapter);

u8 rtw_mi_dynamic_check_timer_handlder(_adapter *padapter);
u8 rtw_mi_buddy_dynamic_check_timer_handlder(_adapter *padapter);

u8 rtw_mi_dev_unload(_adapter *padapter);
u8 rtw_mi_buddy_dev_unload(_adapter *padapter);

extern void rtw_iface_dynamic_chk_wk_hdl(_adapter *padapter);
u8 rtw_mi_dynamic_chk_wk_hdl(_adapter *padapter);
u8 rtw_mi_buddy_dynamic_chk_wk_hdl(_adapter *padapter);

u8 rtw_mi_os_xmit_schedule(_adapter *padapter);
u8 rtw_mi_buddy_os_xmit_schedule(_adapter *padapter);

u8 rtw_mi_report_survey_event(_adapter *padapter, union recv_frame *precv_frame);
u8 rtw_mi_buddy_report_survey_event(_adapter *padapter, union recv_frame *precv_frame);

extern void sreset_start_adapter(_adapter *padapter);
extern void sreset_stop_adapter(_adapter *padapter);
u8 rtw_mi_sreset_adapter_hdl(_adapter *padapter, u8 bstart);
u8 rtw_mi_buddy_sreset_adapter_hdl(_adapter *padapter, u8 bstart);

u8 rtw_mi_tx_beacon_hdl(_adapter *padapter);
u8 rtw_mi_buddy_tx_beacon_hdl(_adapter *padapter);

u8 rtw_mi_set_tx_beacon_cmd(_adapter *padapter);
u8 rtw_mi_buddy_set_tx_beacon_cmd(_adapter *padapter);

#ifdef CONFIG_P2P
u8 rtw_mi_p2p_chk_state(_adapter *padapter, enum P2P_STATE p2p_state);
u8 rtw_mi_buddy_p2p_chk_state(_adapter *padapter, enum P2P_STATE p2p_state);
u8 rtw_mi_stay_in_p2p_mode(_adapter *padapter);
u8 rtw_mi_buddy_stay_in_p2p_mode(_adapter *padapter);
#endif

_adapter *rtw_get_iface_by_id(_adapter *padapter, u8 iface_id);
_adapter *rtw_get_iface_by_macddr(_adapter *padapter, u8 *mac_addr);
_adapter *rtw_get_iface_by_hwport(_adapter *padapter, u8 hw_port);

void rtw_mi_buddy_clone_bcmc_packet(_adapter *padapter, union recv_frame *precvframe, u8 *pphy_status);

#ifdef CONFIG_PCI_HCI
/*API be create temporary for MI, caller is interrupt-handler, PCIE's interrupt handler cannot apply to multi-AP*/
_adapter *rtw_mi_get_ap_adapter(_adapter *padapter);
#endif

void rtw_mi_update_ap_bmc_camid(_adapter *padapter, u8 camid_a, u8 camid_b);

#ifdef CONFIG_AP_MODE
void rtw_mi_ap_acdata_control(_adapter *padapter, u8 power_mode);
void rtw_mi_buddy_ap_acdata_control(_adapter *padapter, u8 power_mode);
#endif /*CONFIG_AP_MODE*/

#endif /*__RTW_MI_H_*/

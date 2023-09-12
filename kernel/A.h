/*
 * A.h
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#ifndef KERNEL_A_H_
#define KERNEL_A_H_

#define MAX_PROCESS				5
#define USR_PROCESS				(MAX_PROCESS-1)
#define MAX_TIMERS				8
#define	MAILBOX_NUM				8
#define	PERIPHERAL_NUM			32



#define DUMMY_XPSR  				0x01000000U

typedef struct
{
	uint8_t		*nxt_link;
	uint8_t		*pre_link;
	uint8_t		*mem_ptr;
	uint8_t		chunk_count;
	uint8_t		chunk_index;
	uint8_t		process;
	uint8_t		flags;
}MEMpool_t;

/* flags */
#define		MEM_IN_USE			0x01
#define		MEM_CHANGED_OWNER	0x02
#define		MEM_IN_LIST			0x04
#define		LAST_IN_LIST		0x80


typedef struct
{
	uint8_t 	process;
	uint8_t		status;
	uint16_t	rxlen;
	uint32_t	flags;
	uint8_t		*rx_buf;
}HWMngr_t;

#define	HWMAN_STATUS_FREE		0
#define	HWMAN_STATUS_ALLOCATED	1


typedef struct
{
	uint8_t		current_process;
	uint32_t	g_tick_count;
	uint32_t	g_os_started;
	uint8_t		*first_mem;
	uint32_t	num_buf_in_use;
	uint32_t	first_data_address;
	MEMpool_t 	*first_of_list;
	MEMpool_t 	*last_of_list;
	uint32_t	system_flags;
	uint8_t		failed_process;
	uint8_t		fail_rsn;
	uint8_t		lwip_state;
	uint8_t		IP_ADDR[4],NETMASK_ADDR[4],GW_ADDR[4];
}Asys_t;

/* system_flags */
#define	SYS_MEM_DEFRAG_REQUEST	0x00000001

typedef struct
{
	uint8_t		IP_ADDR0;
	uint8_t		IP_ADDR1;
	uint8_t		IP_ADDR2;
	uint8_t		IP_ADDR3;
	uint8_t		NETMASK_ADDR0;
	uint8_t		NETMASK_ADDR1;
	uint8_t		NETMASK_ADDR2;
	uint8_t		NETMASK_ADDR3;
	uint8_t		GW_ADDR0;
	uint8_t		GW_ADDR1;
	uint8_t		GW_ADDR2;
	uint8_t		GW_ADDR3;
}A_IpAddr_t;

extern	void A_bzero(uint8_t *ptr,uint16_t count);
extern	void A_memcpy(uint8_t *dest,uint8_t *source,uint16_t size);
extern	void schedule(void);
extern	void mem_init(void);
extern	void defrag_mem(void);
extern	void MX_USB_Device_Init(void);
extern	void MX_LWIP_Init(A_IpAddr_t *A_IpAddr);

extern	void supervisor(void);
extern	void process_1(void);
extern	void process_2(void);
extern	void process_3(void);
extern	void process_4(void);

extern	Asys_t		Asys;


#endif /* KERNEL_A_H_ */

/**
 ******************************************************************************
 *              Copyright (c) 2019 temp. All Rights Reserved.
 * @file    debug.h
 * @author  
 * @brief   ���Ժ�ͷ�ļ�
 * @version V1.0
 * @data    2019/08/09
 * @note    None
 ******************************************************************************
 */
 
#ifndef __DEBUG_H
#define __DEBUG_H
 
#include <rtthread.h>
 
#define MYDEBUG
 
#ifdef MYDEBUG
 
#define debug_line() 																												\
rt_kprintf("Log: [%s]: %s() line = %d\n", __FILE__, __func__, __LINE__)

// Usage: DEBUG_INFO("���ǵ�%d�����Դ�ӡ", 6);
#define debug_info(fmt, ...)                                                \
rt_kprintf("Log: [%s]: %s() line = %d, DEBUGINFO: " fmt "\n", __FILE__, __func__, __LINE__, \
         ##__VA_ARGS__)

#endif
 
#endif /* __DEBUG_H */

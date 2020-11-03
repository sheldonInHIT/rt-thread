/*
 * �����嵥������һ�� hwtimer �豸ʹ������
 * ���̵����� hwtimer_sample ��������ն�
 * ������ø�ʽ��hwtimer_sample
 * �����ܣ�Ӳ����ʱ����ʱ�ص����������ԵĴ�ӡ��ǰtickֵ��2��tickֵ֮���Ϊʱ���ͬ�ڶ�ʱʱ��ֵ��
*/

#include <rtthread.h>
#include <rtdevice.h>
#include "mydebug.h"

#define HWTIMER_DEV_NAME   "timer13"     /* ��ʱ������ */

/* ��ʱ����ʱ�ص����� */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;      /* ��ʱ����ʱֵ */
    rt_device_t hw_dev = RT_NULL;   /* ��ʱ���豸��� */
    rt_hwtimer_mode_t mode;         /* ��ʱ��ģʽ */

    /* ���Ҷ�ʱ���豸 */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    /* �Զ�д��ʽ���豸 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /* ���ó�ʱ�ص����� */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* ����ģʽΪ�����Զ�ʱ�� */
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* ���ö�ʱ����ʱֵΪ5s��������ʱ�� */
    timeout_s.sec = 5;      /* �� */
    timeout_s.usec = 0;     /* ΢�� */

    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    /* ��ʱ3500ms */
    rt_thread_mdelay(3500);

    /* ��ȡ��ʱ����ǰֵ */
    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
		debug_line();
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);
		
    return ret;
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT_ALIAS(hwtimer_sample, tm_test,hwtimer sample);


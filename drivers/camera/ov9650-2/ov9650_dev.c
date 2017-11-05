#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/slab.h>

static struct i2c_board_info ov9650_info = {	
	I2C_BOARD_INFO("ov9650", 0x30),
};

static struct i2c_client *ov9650_client;

static int ov9650_dev_init(void)
{
	struct i2c_adapter *i2c_adap;

	i2c_adap = i2c_get_adapter(0);
	ov9650_client = i2c_new_device(i2c_adap, &ov9650_info);
	i2c_put_adapter(i2c_adap);

	return 0;
}

static void ov9650_dev_exit(void)
{
	i2c_unregister_device(ov9650_client);
}

module_init(ov9650_dev_init);
module_exit(ov9650_dev_exit);

MODULE_LICENSE("GPL");


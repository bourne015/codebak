#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd0a8ddc4, "module_layout" },
	{ 0xf6d8fc65, "kmalloc_caches" },
	{ 0x3da70386, "nand_scan" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x3ec0f0a8, "kmem_cache_alloc_trace" },
	{ 0x7ad7d0ea, "clk_enable" },
	{ 0x3a5c1d77, "clk_get" },
	{ 0x27e1a049, "printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x37a0cba, "kfree" },
	{ 0x45a55ec8, "__iounmap" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E811C4BBC77DE2FF02E111E");

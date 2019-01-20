#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Exovii <iivoxe@gmail.com>");
MODULE_DESCRIPTION("A Mikrotik RB-951G-2HnD specific module, which enables proper communication between CPU and ethernet switch chip.");
MODULE_VERSION("0.0.1");

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

void writeregl(void* map_base, unsigned long addr, unsigned long value) {
  int res;
  res = readl(map_base + addr);
  printk(KERN_INFO "%s: 0x%lx value before write: 0x%08x\n", THIS_MODULE->name, addr, res);
  writel(value, map_base + addr);
  printk(KERN_INFO "%s: Wrote 0x%08lx to address 0x%lx\n", THIS_MODULE->name, value, addr);
  res = readl(map_base + addr);
  printk(KERN_INFO "%s: 0x%lx value after write: 0x%08x\n", THIS_MODULE->name, addr, res);
}

int init_module(void) {
  void __iomem *map_base;

  // Create memory map
  map_base = ioremap(0, MAP_SIZE);
  printk(KERN_INFO "%s: Memory mapped at address 0x%p.\n", THIS_MODULE->name, map_base);

  // Write 0x00004041 to address 0x18070000
  printk(KERN_INFO "%s: Set (AR934X_ETH_CFG_RGMII_GMAC0|AR934X_ETH_CFG_RXD_DELAY|AR934X_ETH_CFG_SW_ONLY_MODE) to AR9344 ETH_XMII_CONTROL register\n", THIS_MODULE->name);
  writeregl(map_base, 0x18070000, 0x00004041);

  // Write 0x6f000000 to address 0x1805002c
  printk(KERN_INFO "%s: Set 0x6f000000 to AR9344 ETH_XMII_CONTROL register\n", THIS_MODULE->name);
  writeregl(map_base, 0x1805002c, 0x6f000000);

  // Clean memory map
  iounmap(map_base);
  printk(KERN_INFO "%s: The switch chip should be working now!\n", THIS_MODULE->name);
  return 0;
}

void cleanup_module(void) {
}

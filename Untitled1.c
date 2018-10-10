#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>
//probe function
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
printk(KERN_INFO "[*] Soliduscode Pen Drive (%04X:%04X) plugged\n", id->idVendor, id-
>idProduct);
return 0;
}
//disconnect
static void pen_disconnect(struct usb_interface *interface){ printk(KERN_INFO "[*]
Soliduscode Pen Drive removed\n");
}
//usb_device_id
static struct usb_device_id pen_table[] = { //( 0781:5567)
{ USB_DEVICE( 0x0781, 0x5567) },{} /* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, pen_table);
// usb_driver
static struct usb_driver pen_driver =
{
.name = "pen_driver",
.id_table = pen_table, //usb_device_id
.probe = pen_probe,
.disconnect = pen_disconnect,
};
static int pen_init(void){ int ret = -1;
printk(KERN_INFO "[*] Constructor of Driver"); printk(KERN_INFO "\tRegistering Driver
with Kernel"); ret = usb_register(&pen_driver);
printk(KERN_INFO "\tRegistration is complete"); return ret;
}
static void pen_exit(void){ //deregister
printk(KERN_INFO "[*] Destructor of driver"); usb_deregister(&pen_driver);
printk(KERN_INFO "\tunregistration complete!");
}
module_init(pen_init); module_exit(pen_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vitians");
MODULE_DESCRIPTION("USB Pen Registration Driver");

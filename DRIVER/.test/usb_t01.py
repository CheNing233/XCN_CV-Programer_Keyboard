import os
import usb.core
import usb.util
import usb.backend.libusb1

# be = usb.backend.libusb1.get_backend()
# dev = usb.core.find(backend=be)

be_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "libusb-1.0.dll")

backend = usb.backend.libusb1.get_backend(find_library=lambda x: be_path)
dev = usb.core.find(idVendor=0x413D, idProduct=0x2107, backend=backend)

# dev = usb.core.find()
# print(dev)

if dev is None:
    raise ValueError("Device not found")

# config = dev.get_active_configuration()
# interfaces = config.interfaces()



dev.set_configuration()

RSTATE = False

msg_w = (ord('w'),6,0,0,0,0,0,0)
msg_r = (ord('r'),64)

msg = msg_r if RSTATE else msg_w
assert dev.write(0x4, msg, 100) == len(msg)

# read(endpoint, size_or_buffer, timeout = None)
data = dev.read(0x83, 64, 1000)
print(data)


usb.util.dispose_resources(device=dev)

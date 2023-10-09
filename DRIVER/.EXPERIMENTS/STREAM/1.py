import struct
from array import array

num = 1600

bs = num.to_bytes(4, "little")

print("%d %d %d %d" % (bs[0], bs[1], bs[2], bs[3]))

for i in range(4):
    print("%d" % (bs[i]))

format_str = "<I"

# 解析字节流
data = struct.unpack(format_str, bs)

print(data)

# 打包数据
packed_data = struct.pack(format_str, *data)

# 打印字节流
for i in range(4):
    print("%d" % (packed_data[i]))

print("next=====")
# 假设有一个字节流数据
packed_data = b"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C"

# 定义格式字符串
format_str = "<8s4B"

# 解包字节流
unpacked_data = struct.unpack(format_str, packed_data)

unpacked_data = list(unpacked_data)

unpacked_data[0] = list(unpacked_data[0])

# 打印解包后的数据
print(unpacked_data)


def flatten(lst):
    flattened_lst = []
    for item in lst:
        if isinstance(item, list):
            flattened_lst.extend(flatten(item))
        else:
            flattened_lst.append(item)
    return flattened_lst

unpacked_data = flatten(unpacked_data)

print(unpacked_data)

# 定义格式字符串
format_str = "<8B4B"

# 将列表打包成字节流
packed_data = struct.pack(format_str, *unpacked_data)

# 打印打包后的字节流
for b in packed_data:
    print(b)
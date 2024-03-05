import os
import sys

LOCAL_PATH = os.path.abspath(os.path.dirname(__file__))
HOME_PATH = LOCAL_PATH + "/../../.."
IMGSIGN_KEY_PATH = HOME_PATH + "/tools/imgsign"
sys.path.append(IMGSIGN_KEY_PATH)

import rsa
import ctypes
import traceback
import struct

aes_key_file = None
def gen_rsa_2048_keys():
    try:
        (pubkey, prvkey) = rsa.newkeys(2048)
        print("pub: ", pubkey)
        print("prv: ", prvkey)

        data = pubkey.save_pkcs1(format='PEM')
        with open('public.pem', 'wb') as f:
            f.write(data)

        data = prvkey.save_pkcs1(format='PEM')
        with open('private.pem', 'wb') as f:
            f.write(data)
    except:
        print(sys.exc_info())
        print(traceback.format_exc())



def print_usage():
    print('\nsec_boot_AX620E_sign.py -i <spl_file> -pub <public_key_file(*.pem)> -prv <private_key_file(*.pem)> -o <out_file>')
    print('  -i   :  input file path')
    print('  -pub :  input rsa public key file (*.pem) path')
    print('  -prv :  input rsa private key file (*.pem) path')
    print('  -o   :  output new signed file')
    print('  -cap  :  input capability of header field\n')
    print('  -key  :  input aes key file for encryption\n')
    print('  -key_bit  :  input rsa key len, 2048 or 3072\n')

'''
struct img_header{
	u32 check_sum;//0x00
	u32 magic_data;//0x04, should be 0x55543322
	u32 capability;
	u32 img_size;
	u32 reserved0;
	u32 img_check_sum;
	u32 reserved1[2];
	u32 boot_bak_flash_addr;
	u32 reserved2[2];
	u32 key_n_header;
	u32 rsa_key_n[96];
	u32 key_e_header;
	u32 rsa_key_e;
	u32 sig_header;
	u32 signature[96];
	u32 reserved3[20];
	u32 aes_key[12];
	u32 reserved4[17];
};
'''

header_size = 1024
class image_header(ctypes.Structure):
    _pack_ = 4
    _fields_ = [
        ("check_sum", ctypes.c_uint),
        ("magic_data", ctypes.c_uint),
        ("capability", ctypes.c_uint),
        ("img_size", ctypes.c_uint),
        ("reserved0", ctypes.c_uint),
        ("img_check_sum", ctypes.c_uint),
        ("reserved1", ctypes.c_uint*2),
        ("boot_bak_flash_addr", ctypes.c_uint),
        ("reserved2", ctypes.c_uint*2),
        ("key_n_header", ctypes.c_uint),  # 0x02000800 //0x00, 0x08, 0x00, 0x02
        ("rsa_key_n", ctypes.c_uint8*384),
        ("key_e_header", ctypes.c_uint),  # 0x02010020 //0x20, 0x00, 0x01, 0x02
        ("rsa_key_e", ctypes.c_uint8*4),
        ("sig_header", ctypes.c_uint),    # 0x01000800 //0x00, 0x08, 0x00, 0x01
        ("signature", ctypes.c_uint8*384),
        ("reserved3", ctypes.c_uint*20),
        ("aes_key", ctypes.c_uint8*48),
        ("reserved", ctypes.c_uint*17)
    ]


def to_bytes(n, length, byteorder='big'):
    if sys.version > '3':
        return n.to_bytes(length, byteorder=byteorder, signed=False)
    else:
        if byteorder == 'big':
            data = b''
            for i in reversed(range(length)):
                d = (n >> i * 8) & 0xff
                data += struct.pack("B", d)
            return data
        else:
            data = b''
            for i in range(length):
                d = (n >> i * 8) & 0xff
                data += struct.pack("B", d)
            return data

def copy_data_by_bytes(src, dst, length, dst_offset= 0, revers=False, flag=False):
    if sys.version > '3':
        for i in range(length):
            if revers:
                dst[dst_offset + i] = ctypes.c_uint8(src[length - i - 1])
            else:
                dst[dst_offset + i] = ctypes.c_uint8(src[i])
    else:
        for i in range(length):
            if revers:
                dst[dst_offset + i] = ctypes.c_uint8(ord(src[length - i - 1]))
            else:
                if flag:
                    dst[dst_offset + i] = ctypes.c_uint8((src[i]))
                else:
                    dst[dst_offset + i] = ctypes.c_uint8(ord(src[i]))

def make_image(input_file, pub_file, prv_file, output_file, capability, key_bit):
    # load pub and private key file
    try:
        with open(pub_file, 'rb') as f:
            pub_key = rsa.PublicKey.load_pkcs1(f.read())

        with open(prv_file, 'rb') as f:
            prv_key = rsa.PrivateKey.load_pkcs1(f.read())
    except:
        print('[error] load public or private key file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False

    # load in file data
    in_size = os.path.getsize(in_file)

    try:
        with open(in_file, 'rb') as f:
            file_data = f.read()
    except:
        print('[error] load image file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False

    out_data = (ctypes.c_uint8 * (in_size + header_size))(0)
    copy_data_by_bytes(file_data, out_data, in_size, header_size*1)
    # calc img check sum

    img_check_sum = ctypes.c_int(0)
    for i in range(header_size//4, in_size//4+(header_size//4)):
        data = out_data[4*i] + (out_data[4*i + 1] << 8) + (out_data[4*i + 2] << 16) + (out_data[4*i + 3] << 24)
        img_check_sum.value += ctypes.c_int(data).value

    # construct image_header
    hdr = image_header()
    hdr.magic_data = 0x55543322
    if key_bit == 2048:
        key_byte = 256
        hdr.key_n_header = 0x02000800
    elif key_bit == 3072:
        key_byte = 384
        hdr.key_n_header = 0x02000C00
    else:
        print('key size not valid')
        exit(-1)
    hdr.key_e_header = 0x02010020
    # key_bit = 2048 or 3072
    if key_bit == 2048:
        hdr.sig_header = 0x01000800
    else:
        hdr.sig_header = 0x01000C00

    hdr.capability = capability
    hdr.img_size = in_size

    hdr.img_check_sum = img_check_sum.value
#    hdr.boot_bak_flash_addr = boot_bak_flash_addr

    try:
        if (aes_key_file is not None):
            with open(aes_key_file, 'rb') as f:
                aes_key = f.read()
                copy_data_by_bytes(aes_key, hdr.aes_key, 48)
    except:
        print('[error] load aes key file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False

    pub_n = to_bytes(pub_key.n, key_byte, byteorder='little')
    copy_data_by_bytes(pub_n, hdr.rsa_key_n, key_byte)

    pub_e = to_bytes(pub_key.e, 4, byteorder='little')
    copy_data_by_bytes(pub_e, hdr.rsa_key_e, 4)

    # sign data
    _message = file_data
    signature = rsa.sign(_message, prv_key, 'SHA-256')
    copy_data_by_bytes(signature, hdr.signature, key_byte, 0, True)

    # verify test
    try:
        ret = rsa.verify(_message, signature, pub_key)
    except e:
        print('[error] verify failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        exit(-1)

    # put hdr in first 1k
    p = ctypes.cast(ctypes.pointer(hdr), ctypes.POINTER(ctypes.c_uint8 * header_size))
    for i in range(header_size):
        out_data[i] = p.contents[i]

    # calc header check sum
    header_check_sum = ctypes.c_int(0)
    for i in range(2, (header_size-8)//4):
        data = out_data[4*i] + (out_data[4*i + 1] << 8) + (out_data[4*i + 2] << 16) + (out_data[4*i + 3] << 24)
        header_check_sum.value += ctypes.c_int(data).value
    # update check sum in buffer
    p = ctypes.cast(ctypes.pointer(header_check_sum), ctypes.POINTER(ctypes.c_uint8 * 4))
    for i in range(4):
        out_data[i] = p.contents[i]

    packed_data = (ctypes.c_uint8 * (in_size + header_size))(0)
    #copy header
    copy_data_by_bytes(out_data, packed_data, header_size, 0, False, False)

    # load in file back data
    copy_data_by_bytes(file_data, packed_data, in_size, header_size*1)
    # save data to out file
    try:
        with open(out_file, 'wb') as f:
            f.write(packed_data)
    except:
        print('[error] create spl file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False
    return True


if __name__ == '__main__':
    #gen_rsa_2048_keys()

    in_file = None
    pub_file = None
    prv_file = None
    out_file = None
    key_bit = None

    capability=0
    if len(sys.argv) < 12:
        print('[error] param is invalid\n')
        print_usage()
        exit(-1)

    for i in range(1, len(sys.argv)):
        if sys.argv[i] == '-i':
            in_file = sys.argv[i+1]
        elif sys.argv[i] == '-pub':
            pub_file = sys.argv[i+1]
        elif sys.argv[i] == '-prv':
            prv_file = sys.argv[i+1]
        elif sys.argv[i] == '-o':
            out_file = sys.argv[i + 1]
        elif sys.argv[i] == '-cap':
            capability = int(sys.argv[i + 1], 16)
        elif sys.argv[i] == '-key':
            aes_key_file = sys.argv[i + 1]
        elif sys.argv[i] == '-key_bit':
            key_bit = int(sys.argv[i + 1])

    if in_file is None or pub_file is None or prv_file is None or out_file is None:
        print('[error] param is invalid\n')
        print_usage()
        exit(-1)
    if (not os.path.exists(in_file)) or (not os.path.exists(pub_file)) or (not os.path.exists(prv_file)):
        print('[error] sign input file does not exist\n')
        exit(-1)
    '''
    # test
    in_file = 'D:/fdl1.bin'
    pub_file = 'D:/public.pem'
    prv_file = 'D:/private.pem'
    out_file = 'D:/fdl1_sign.bin'
    '''
    ret = make_image(in_file, pub_file, prv_file, out_file, capability, key_bit)
    if ret:
        print('sign complete')


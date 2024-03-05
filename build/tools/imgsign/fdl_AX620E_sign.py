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
    print('\nbuild_spl.py -i <spl_file> -pub <public_key_file(*.pem)> -prv <private_key_file(*.pem)> -o <out_file>')
    print('  -i   :  input original spl file path, the file size must be less than 79K bytes')
    print('  -pub :  input rsa public key file (*.pem) path')
    print('  -prv :  input rsa private key file (*.pem) path')
    print('  -o   :  output new spl file with 512K bytes\n')
    print('  -fw  :  input original fw file path, the file size must be less than 80K bytes\n')
    print('  -packsize :  input image packed size, the packsize must be aligned at 0x20000\n')
    print('  -cap  :  input capability of header field\n')

'''
struct img_header{
	u32 check_sum;//0x00
	u32 magic_data;//0x04, should be 0x55543322
	u32 capability;
	u32 img_size;
	u32 fw_size;
	u32 img_check_sum;
	u32 fw_check_sum;
	/*
	 * [1:0]: nand page_size, page_size = 2^(nand_nor_cfg[1:0] + 11), 2KB ~ 16KB
	 * [4:2]: nand block_size, block_size = 2^(nand_nor_cfg[4:2] + 16), 64KB ~ 8MB
	 * [6:5]: nand oob_size, oob_size = 2^(nand_nor_cfg[6:5] + 6), 64Bytes ~ 512Bytes
	 * [7]: nand bad block marker size, if nand_nor_cfg[7] is 0, the bad block marker
	 * is 1 byte, if nand_type[7] is 1, bad block marker is 2 bytes.
	 * [15: 8]: nor QE read status register cmd
	 * [23:16]: nor QE write status register cmd
	 * [31:24]: nor QE bit offset
	 */
	u32 nand_nor_cfg;
	u32 boot_bak_flash_addr;
	u32 fw_flash_addr;
	u32 fw_bak_flash_addr;
	u32 key_n_header;
	u32 rsa_key_n[96];
	u32 key_e_header;
	u32 rsa_key_e;
	u32 sig_header;
	u32 signature[96];
	u32 reserved[49];
};
'''

IMG_ALIGN=0x20000
class spl_header(ctypes.Structure):
    _pack_ = 4
    _fields_ = [
        ("check_sum", ctypes.c_uint),
        ("magic_data", ctypes.c_uint),
        ("capability", ctypes.c_uint),
        ("img_size", ctypes.c_uint),
        ("fw_size", ctypes.c_uint),
        ("img_check_sum", ctypes.c_uint),
        ("fw_check_sum", ctypes.c_uint),
        ("nand_nor_cfg", ctypes.c_uint),
        ("boot_bak_flash_addr", ctypes.c_uint),
        ("fw_flash_addr", ctypes.c_uint),
        ("fw_bak_flash_addr", ctypes.c_uint),
        ("key_n_header", ctypes.c_uint),  # 0x02000800 //0x00, 0x08, 0x00, 0x02
        ("rsa_key_n", ctypes.c_uint8*256),
        ("key_e_header", ctypes.c_uint),  # 0x02010020 //0x20, 0x00, 0x01, 0x02
        ("rsa_key_e", ctypes.c_uint8*4),
        ("reserved1", ctypes.c_uint8*128),
        ("sig_header", ctypes.c_uint),    # 0x01000800 //0x00, 0x08, 0x00, 0x01
        ("signature", ctypes.c_uint8*384),
        ("nand_ext_cfg", ctypes.c_uint),
        ("nand_rx_sample_delay", ctypes.c_uint*3),
        ("nor_rx_sample_delay", ctypes.c_uint*3),
        ("ocm_start_addr", ctypes.c_uint),
        ("reserved", ctypes.c_uint*41)
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

def do_spl(in_file, pub_file, prv_file, out_file, fw_file, pack_size, capability):
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
    header_size = 1024
    in_size = os.path.getsize(in_file)
    max_img_size = pack_size - header_size
    all_img_pack_size = pack_size
    if in_size > (max_img_size):
        print('[error] file size({}) too big, must not be larger than %d'.format(in_size),max_img_size)
        return False

    try:
        with open(in_file, 'rb') as f:
            file_data = f.read()
    except:
        print('[error] load image file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False

    out_data = (ctypes.c_uint8 * all_img_pack_size)(0)
    # load fw file data
    fw_size = os.path.getsize(fw_file)
    if fw_size > 80*1024:
        print('[error] file size({}) too big, must not be larger than 80K'.format(fw_size))
        return False

    try:
        with open(fw_file, 'rb') as f:
            fw_data = f.read()
    except:
        print('[error] load fw file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False

    img_size = in_size
    boot_bak_flash_addr = (header_size*2+in_size + (IMG_ALIGN - 1)) & (~(IMG_ALIGN - 1))
    fw_flash_addr = (boot_bak_flash_addr+in_size + (IMG_ALIGN - 1)) & (~(IMG_ALIGN - 1))
    fw_bak_flash_addr = fw_flash_addr + IMG_ALIGN

    # create 80k buffer and put the file data offset 2K
    copy_data_by_bytes(file_data, out_data, in_size, header_size*1)
    # calc img check sum
    check_sum = ctypes.c_uint32(0)
    for i in range(header_size//4, in_size//4+(header_size//4)):
        data = out_data[4*i] + (out_data[4*i + 1] << 8) + (out_data[4*i + 2] << 16) + (out_data[4*i + 3] << 24)
        check_sum.value += ctypes.c_uint32(data).value

    # construct spl_header
    hdr = spl_header()
    hdr.magic_data = 0x55543322
    hdr.key_n_header = 0x02000800
    hdr.key_e_header = 0x02010020
    hdr.sig_header = 0x01000800
    hdr.nand_nor_cfg = 0x06010504
    hdr.ocm_start_addr = 0x03000400
    hdr.capability = capability
    hdr.img_size = in_size
    hdr.img_check_sum = check_sum.value
    hdr.fw_size = fw_size
    hdr.boot_bak_flash_addr = boot_bak_flash_addr
    hdr.fw_flash_addr = fw_flash_addr
    hdr.fw_bak_flash_addr = fw_bak_flash_addr

    pub_n = to_bytes(pub_key.n, 256, byteorder='little')
    copy_data_by_bytes(pub_n, hdr.rsa_key_n, 256)

    pub_e = to_bytes(pub_key.e, 4, byteorder='little')
    copy_data_by_bytes(pub_e, hdr.rsa_key_e, 4)

    # sign data
    _message = file_data
    signature = rsa.sign(_message, prv_key, 'SHA-256')
    copy_data_by_bytes(signature, hdr.signature, 256, 0, True)

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
    header_check_sum = ctypes.c_uint32(0)
    for i in range(2, (header_size-8)//4):
        data = out_data[4*i] + (out_data[4*i + 1] << 8) + (out_data[4*i + 2] << 16) + (out_data[4*i + 3] << 24)
        header_check_sum.value += ctypes.c_uint32(data).value

    # update check sum in buffer
    p = ctypes.cast(ctypes.pointer(header_check_sum), ctypes.POINTER(ctypes.c_uint8 * 4))
    for i in range(4):
        out_data[i] = p.contents[i]

    packed_data = (ctypes.c_uint8 * (all_img_pack_size))(0)
	#copy header once
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
    fw_file = None
    pack_size=0
    capability=0
    if len(sys.argv) < 15:
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
        elif sys.argv[i] == '-fw':
            fw_file = sys.argv[i + 1]
        elif sys.argv[i] == '-packsize':
            pack_size = int(sys.argv[i + 1],16)
        elif sys.argv[i] == '-cap':
            capability = int(sys.argv[i + 1],16)

    if in_file is None or pub_file is None or prv_file is None or out_file is None or fw_file is None:
        print('[error] param is invalid\n')
        print_usage()
        exit(-1)
    if (not os.path.exists(in_file)) or (not os.path.exists(pub_file)) or (not os.path.exists(prv_file)) or (not os.path.exists(fw_file)):
        print('[error] sign input file does not exist\n')
        exit(-1)
    '''
    # test
    in_file = 'D:/fdl1.bin'
    pub_file = 'D:/public.pem'
    prv_file = 'D:/private.pem'
    out_file = 'D:/fdl1_sign.bin'
    '''
    ret = do_spl(in_file, pub_file, prv_file, out_file, fw_file, pack_size, capability)
    if ret:
        print('sign complete')


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
small_size_nor = None
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
    print('  -i   :  input original spl file path, the file size must be less than 155K bytes')
    print('  -pub :  input rsa public key file (*.pem) path')
    print('  -prv :  input rsa private key file (*.pem) path')
    print('  -o   :  output new spl file with 512K bytes\n')
    print('  -fw  :  input original fw file path, the file size must be less than 80K bytes\n')
    print('  -cap  :  input capability of header field\n')
    print('  -riscv  :  input original riscv file path, the file size must be less than 512K bytes\n')
    print('  -small_size_nor  :  Declares that the nor project generates an image of small memory\n')

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
	u32 nand_ext_cfg;
	u32 nand_rx_sample_delay[3];
	u32 nor_rx_sample_delay[3];
	u32 ocm_start_addr;
	u32 riscv_flash_addr;
	u32 riscv_check_sum;
	u32 riscv_img_size;
	u32 nand_phy_setting[3];
	u32 nor_phy_setting[3];
	u32 emmc_phy_legacy_delayline;
	u32 emmc_phy_hs_delayline;
	u32 sd_phy_default_delayline;
	u32 aes_key[12];
	u32 reserved[17];
};
'''

IMG_ALIGN=0x20000
PKG_SIZE=0x20000
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
        ("riscv_flash_addr", ctypes.c_uint),
        ("riscv_check_sum", ctypes.c_uint),
        ("riscv_img_size", ctypes.c_uint),
        ("nand_phy_setting", ctypes.c_uint*3),
        ("nor_phy_setting", ctypes.c_uint*3),
        ("emmc_phy_legacy_delayline", ctypes.c_uint),
        ("emmc_phy_hs_delayline", ctypes.c_uint),
        ("sd_phy_legacy_delayline", ctypes.c_uint),
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

def do_spl(in_file, pub_file, prv_file, out_file, fw_file, riscv_file, capability):
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
    max_img_size = PKG_SIZE - header_size - 0x13400 # max spl img = 128K -77K - 1K = 50K

    if (riscv_file is None):
        print('riscv file is not exists\n')
        all_img_pack_size = PKG_SIZE*2 #256K
        riscv_size = 0
        riscv_check_sum = ctypes.c_uint32(0)
        riscv_check_sum.value = 0
        capability &= 0xFF7FFFFF #bit23 clr 0
        riscv_flash_addr = 0

    else:
        print('riscv file is exists\n')
        all_img_pack_size = PKG_SIZE * 6  #768K
        riscv_size = os.path.getsize(riscv_file)
        if riscv_size > PKG_SIZE*2:
            print('[error] file size({}) too big, must not be larger than %d'.format(riscv_size), PKG_SIZE*2)
            return False
        try:
            with open(riscv_file, 'rb') as f:
                riscv_data = f.read()
        except:
            print('[error] load riscv image file failed\n')
            print(sys.exc_info())
            print(traceback.format_exc())
            return False

        capability |= 0x800000 #bit23 set 1
        riscv_flash_addr = 0x40000 #256k
        out_data = (ctypes.c_uint8 * all_img_pack_size)(0)  # clr 0
        copy_data_by_bytes(riscv_data, out_data, riscv_size)
        # calc fw check sum
        riscv_check_sum = ctypes.c_uint32(0)
        for i in range(0, riscv_size // 4):
            data = out_data[4 * i] + (out_data[4 * i + 1] << 8) + (out_data[4 * i + 2] << 16) + (
                        out_data[4 * i + 3] << 24)
            riscv_check_sum.value += ctypes.c_uint32(data).value

    if in_size > max_img_size:
        print('[error] file size({}) too big, must not be larger than %d'.format(in_size), max_img_size)
        return False

    try:
        with open(in_file, 'rb') as f:
            file_data = f.read()
    except:
        print('[error] load image file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False

    out_data = (ctypes.c_uint8 * all_img_pack_size)(0) #清0
    # load fw file data
    fw_size = os.path.getsize(fw_file)
    if fw_size > 77*1024:
        print('[error] file size({}) too big, must not be larger than 77K'.format(fw_size))
        return False

    try:
        with open(fw_file, 'rb') as f:
            fw_data = f.read()
    except:
        print('[error] load fw file failed\n')
        print(sys.exc_info())
        print(traceback.format_exc())
        return False

    img_size = in_size #bin的大小
    boot_bak_flash_addr = (header_size + PKG_SIZE) #0x20400
    fw_flash_addr = (PKG_SIZE - 0x13400) #0x20000 - 0x13400 = 0xCC00 , 128K - 77K = 51K
    fw_bak_flash_addr = fw_flash_addr + PKG_SIZE # 0x2CC00, 51K + 128K = 179K
    copy_data_by_bytes(fw_data, out_data, fw_size)
    # calc fw check sum
    fw_check_sum = ctypes.c_uint32(0)
    for i in range(0, fw_size//4):
        data = out_data[4*i] + (out_data[4*i + 1] << 8) + (out_data[4*i + 2] << 16) + (out_data[4*i + 3] << 24)
        fw_check_sum.value += ctypes.c_uint32(data).value

    # create 80k buffer and put the file data offset 1K
    copy_data_by_bytes(file_data, out_data, in_size, header_size)
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
    if PKG_SIZE == 0x40000:
        hdr.nand_nor_cfg = 0x06010509
    else:
        hdr.nand_nor_cfg = 0x06010504
    hdr.ocm_start_addr = 0x03000400
    hdr.capability = capability
    hdr.img_size = in_size
    hdr.img_check_sum = check_sum.value
    hdr.fw_size = fw_size
    hdr.fw_check_sum = fw_check_sum.value
    hdr.boot_bak_flash_addr = boot_bak_flash_addr
    hdr.fw_flash_addr = fw_flash_addr
    hdr.fw_bak_flash_addr = fw_bak_flash_addr
    hdr.riscv_flash_addr = riscv_flash_addr #256K or 0
    hdr.riscv_check_sum = riscv_check_sum.value
    hdr.riscv_img_size = riscv_size

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
    small_nor_packed_data = (ctypes.c_uint8 * (max_img_size + header_size))(0)
    if small_size_nor == 1:
        copy_data_by_bytes(out_data, small_nor_packed_data, header_size, 0, False, False)
        copy_data_by_bytes(file_data, small_nor_packed_data, in_size, header_size)
    # copy header twice
    copy_data_by_bytes(out_data, packed_data, header_size, 0, False, False)
    copy_data_by_bytes(out_data, packed_data, header_size, PKG_SIZE, False, False)

    # load in file back data
    copy_data_by_bytes(file_data, packed_data, in_size, header_size)
    copy_data_by_bytes(file_data, packed_data, in_size, boot_bak_flash_addr)
    # load fw file and back data
    copy_data_by_bytes(fw_data, packed_data, fw_size, fw_flash_addr)
    copy_data_by_bytes(fw_data, packed_data, fw_size, fw_bak_flash_addr)
    # load riscv file
    if riscv_flash_addr != 0:
        copy_data_by_bytes(riscv_data, packed_data, riscv_size, riscv_flash_addr)
    # save data to out file
    try:
        with open(out_file, 'wb') as f:
            if small_size_nor == 1:
                f.write(small_nor_packed_data)
            else:
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
    riscv_file = None
    pack_size=0
    capability=0
    if len(sys.argv) < 13:
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
        elif sys.argv[i] == '-cap':
            capability = int(sys.argv[i + 1], 16)
        elif sys.argv[i] == '-riscv':
            riscv_file = sys.argv[i + 1]
        elif sys.argv[i] == '-nand_4k':
            PKG_SIZE=0x40000
        elif sys.argv[i] == '-key':
            aes_key_file = sys.argv[i + 1]
        elif sys.argv[i] == '-small_size_nor':
            small_size_nor = 1

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
    ret = do_spl(in_file, pub_file, prv_file, out_file, fw_file, riscv_file, capability)
    if ret:
        print('sign complete')

import os
import sys
import traceback
import struct
import shutil
import fnmatch


def print_usage():
    print('\nsdk_update_pack.py -type <name> -path <path>')
    print('-type <name>: sd_update or sd_boot\n')
    print('-path <path>: eg: ./out/AX630C_emmc_arm64_k515/images\n')
    print('-xml <xml>:   path/AX620X_XXX.xml\n')
    print('-optee <optee>: eg: true or false\n')
    print('-ab yes/no\n')

def pack_sd_update(path, xmlpath, optee=False, support_ab=False):
    f = os.listdir(path)
    print('package image file for sd update...')
    os.chdir(path)
    if os.path.exists('sd_update_pack'):
        os.system("rm -f sd_update_pack/*")
    else:
        os.mkdir('sd_update_pack')
    for file in f:
        try:
            if(file == 'u-boot_signed.bin'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'uboot.bin')
            if(file == 'boot_signed.bin'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'kernel.img')
            if(file == 'atf_bl31_signed.bin'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'atf.img')
            if(fnmatch.fnmatch(file, '*_signed.dtb') == True):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'dtb.img')
            if(file == 'rootfs_sparse.ext4'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'rootfs.img')
            if(file == 'rootfs.img'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'rootfs.img')
            if(file == 'rootfs_soc_opt.ubi'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'rootfs.img')
            if(file == 'param_sparse.ext4'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'param.img')
            if(file == 'param.ubi'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'param.img')
            if(file == 'opt_sparse.ext4'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'opt.img')
            if(file == 'opt.img'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'opt.img')
            if(file == 'soc_sparse.ext4'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'soc.img')
            if(file == 'customer.img'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'customer.img')
            if(fnmatch.fnmatch(file, 'spl_*_k???_signed.bin') == True):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'spl.bin')
            if(optee and (file == 'optee_signed.bin')):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'optee.img')
            if(fnmatch.fnmatch(file, 'ddrinit_*_signed.bin') == True):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'ddrinit.img')
            if(fnmatch.fnmatch(file, '*.xml') == True):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'AX620E.xml')
            if(file == 'axera_logo.bmp'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'logo.img')
            if(support_ab):
                if((file == 'atf_bl31_signed.bin')):
                    shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'atf_b.img')
                if(optee and (file == 'optee_signed.bin')):
                    shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'optee_b.img')
                if(fnmatch.fnmatch(file, '*_signed.dtb') == True):
                    shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'dtb_b.img')
                if((file == 'u-boot_signed.bin')):
                    shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'uboot_b.bin')
                if((file == 'boot_signed.bin')):
                    shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'kernel_b.img')
                if(file == 'axera_logo.bmp'):
                    shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/' + 'logo_b.img')
        except:
            continue
    f = os.listdir(os.path.dirname(os.path.realpath(file)) + '/sd_update_pack/')
    print(f)


def pack_sd_boot(path, optee=False):
    f = os.listdir(path)
    print('package sd boot image file...')
    os.chdir(path)
    if os.path.exists('sd_boot_pack'):
        os.system("rm sd_boot_pack/*")
    else:
        os.mkdir('sd_boot_pack')
    for file in f:
        try:
            if(file == 'u-boot_signed.bin'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/' + 'uboot.bin')
            if(file == 'boot_signed.bin'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/' + 'kernel.img')
            if(fnmatch.fnmatch(file, '*_signed.dtb') == True):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/' + 'dtb.img')
            if(file == 'atf_bl31_signed.bin'):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/' + 'atf.img')
            if(fnmatch.fnmatch(file, 'spl*_k???_sd_signed.bin') == True):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/' + 'boot.bin')
            if(optee and (file == 'optee_signed.bin')):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/' + 'optee.img')
            if(fnmatch.fnmatch(file, 'ddrinit_*_signed.bin') == True):
                shutil.copyfile(os.path.realpath(file), os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/' + 'ddrinit.img')
        except:
            continue
    f = os.listdir(os.path.dirname(os.path.realpath(file)) + '/sd_boot_pack/')
    print(f)


def main(type, path, xmlpath, optee=False, support_ab=False):
    if(type == 'sd_update'):
        pack_sd_update(path, xmlpath, optee, support_ab)
    elif(type == 'sd_boot'):
        pack_sd_boot(path, optee)
    else:
        print_usage()

if __name__ == '__main__':
    if len(sys.argv) < 6:
        print('[error] param is invalid\n')
        print_usage()
        exit(-1)

    support_ab = False

    for i in range(1, len(sys.argv)):
        if sys.argv[i] == '-type':
            name = sys.argv[i+1]
        if sys.argv[i] == '-path':
            path = sys.argv[i+1]
        if sys.argv[i] == '-xml':
            xmlpath = sys.argv[i+1]
        if sys.argv[i] == '-optee':
            optee = sys.argv[i+1].lower()=="true"
        if sys.argv[i] == '-ab':
            support_ab = sys.argv[i+1].lower()=="yes"

    main(name, path, xmlpath, optee, support_ab)

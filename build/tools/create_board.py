#encoding=utf-8
import sys
import os
import re

PLATFORM = "AX620E"
KERNEL   = "linux-5.15.73"
UBOOT    = "u-boot-2020.04"

flash_types = ("emmc", "nand", "nor")

def exit(n):
    sys.exit(n)

def exec_cmd(cmd):
    print(cmd)
    os.system(cmd)

def construct_build(build_path, template_board, new_board, line_num):
    project_mak = os.path.join(build_path, "project.mak")
    cmd = '''sed -i "{}iAX_PRJ_LIST += {}\n" {}'''.format(line_num, new_board, project_mak)
    exec_cmd(cmd)
    template_folder = os.path.join(build_path, "projects", template_board)
    new_folder      = os.path.join(build_path, "projects", new_board)
    cmd = f"cp -r {template_folder} {new_folder}"
    exec_cmd(cmd)
    print("construct build done !!!")

def construct_kernel(linux_path, linux_ver, template_board, new_board):
    template_dts = os.path.join(linux_path, linux_ver, "arch/arm64/boot/dts/axera", f"{template_board}.dts")
    new_dts      = os.path.join(linux_path, linux_ver, "arch/arm64/boot/dts/axera", f"{new_board}.dts")
    template_defconfig = os.path.join(linux_path, linux_ver, "arch/arm64/configs", f"axera_{template_board}_defconfig")
    new_defconfig      = os.path.join(linux_path, linux_ver, "arch/arm64/configs", f"axera_{new_board}_defconfig")
    cmd = f"cp {template_dts} {new_dts}"
    exec_cmd(cmd)
    cmd = f"cp {template_defconfig} {new_defconfig}"
    exec_cmd(cmd)
    makefile = os.path.join(linux_path, linux_ver, "arch/arm64/boot/dts/axera/Makefile")
    with open(makefile, 'rt') as f:
        lines = f.readlines()
    for line in lines:
        if line.find(f"{new_board}.dtb") != -1:
            print(f"Already contains {new_board}.dtb")
            exit(-1)
    exec_cmd(f"sed -i '$a dtb-$(CONFIG_ARCH_AXERA) += {new_board}.dtb' {makefile}")
    print("construct kernel done !!!")

def construct_boot(boot_path, template_board, new_board, flash_type):
    uboot_path = os.path.join(boot_path, "uboot", UBOOT)
    if flash_type in ("emmc", "nand", "none"):
        template_defconfig = os.path.join(uboot_path, "configs", f"{template_board}_defconfig")
        new_defconfig      = os.path.join(uboot_path, "configs", f"{new_board}_defconfig")
        exec_cmd(f"cp {template_defconfig} {new_defconfig}")
    elif flash_type in ("nor"):
        template_defconfig = os.path.join(uboot_path, "configs", f"{template_board}_fdl2_defconfig")
        new_defconfig      = os.path.join(uboot_path, "configs", f"{new_board}_fdl2_defconfig")
        exec_cmd(f"cp {template_defconfig} {new_defconfig}")
        template_defconfig = os.path.join(uboot_path, "configs", f"{template_board}_uboot_defconfig")
        new_defconfig      = os.path.join(uboot_path, "configs", f"{new_board}_uboot_defconfig")
        exec_cmd(f"cp {template_defconfig} {new_defconfig}")
    else:
        print(f"Unsupport flash type: {flash_type}")
        exit(-1)

    print("construct boot done !!!")

def create_board(home_path, template_board, new_board, flash_type):
    home_path   = os.path.abspath(home_path)
    build_path  = os.path.join(home_path, "build")
    kernel_path = os.path.join(home_path, "kernel", "linux")
    boot_path   = os.path.join(home_path, "boot")
    project_mak = os.path.join(build_path, "project.mak")
    project_cfg = os.path.join(build_path, "projects", template_board, "project.mak")

    if new_board.split("_")[0] != PLATFORM:
        print(f"Invalid board name {new_board}")
        exit(-1)

    if flash_type not in flash_types:
        print(f"Unsupported flash type: {flash_type}")
        print(f"Please select one of : {flash_types}")
        exit(-1)

    with open(project_mak, "rt") as f:
        lines = f.readlines()
    project_list = []
    line_num = 0
    line_pos = 0
    ptn = r"AX_PRJ_LIST\s*([:,+]?=)\s*(\w+)"
    for line in lines:
        line_num += 1
        line = line.strip()
        if line.startswith("#"):
            continue
        line = line.split("#")[0].strip()
        matched = re.search(ptn, line)
        if matched:
            assignment, prj = matched.groups()
            if assignment == ":=":
                project_list = []
            project_list.append(prj)
            line_pos = line_num

    if template_board not in project_list:
        print(f"not supported template board: {template_board}")
        print(f"Detected template boards: {project_list}")
        exit(-1)

    if new_board in project_list:
        print(f"{new_board} already exists!!!")
        exit(-1)

    with open(project_cfg, "rt") as f:
        lines = f.readlines()

    ptn = r"FLASH_TYPE\s*[:,+]?=\s*(\w+)"
    template_flash_type = "unknow"
    for line in lines:
        line = line.strip()
        if line.startswith("#"):
            continue
        line = line.split("#")[0].strip()
        matched = re.search(ptn, line)
        if matched:
            template_flash_type = matched.groups()[0]
            break

    if template_flash_type == "unknow":
        print(f"unknow flash type of template board {template_board}")
        exit(-1)

    construct_build(build_path, template_board, new_board, line_pos+1)
    construct_kernel(kernel_path, KERNEL, template_board, new_board)
    construct_boot(boot_path, template_board, new_board, flash_type)

def clean():
    pass

if __name__ == "__main__":
    '''args = "/home/lihua/projects/nor_leopard AX620Q_nor_arm32_k419 AX620Q_fastnor_arm32_k419 nor".split()
    for arg in args:
        sys.argv.append(arg)'''
    if len(sys.argv) != 5:
        print("para error!")
        print(f"usage: python3 create_board.py home_path template_board new_board flash_type{flash_types}")
        exit(-1)

    home_path, template_board, new_board, flash_type = sys.argv[1:]

    create_board(home_path, template_board, new_board, flash_type)

    print("Done!!!")

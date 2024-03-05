#encoding=utf-8
import re
import os
import sys
import subprocess
import random

try:
    import lxml.etree as ET
except ModuleNotFoundError as e:
    os.system("python3 -m pip install --upgrade pip")
    os.system("pip3 install lxml")
    import lxml.etree as ET

append_target='''
.PHONY: {target}
{target}:
	@$(ECHO) -e $(GREEN) "uboot $@..." $(DONE)
'''

def get_project_cfg(prj_name, prj_mak):
    prj_mak = os.path.abspath(prj_mak)
    if not os.path.exists(prj_mak):
        raise Exception(f"file: {prj_mak} not exists!!!")
        sys.exit(-1)
    fdir  = os.path.dirname(prj_mak)
    fname = os.path.basename(prj_mak)
    rand_num = random.randint(1000, 10000)
    ftmp  = os.path.join(fdir, f"{fname.split('.')[0]}_{rand_num}.tmp")
    os.system(f"cp {prj_mak} {ftmp}")
    target_name = f"get_info{rand_num}"
    get_info = append_target.format(target=target_name)
    with open(ftmp, "a") as f:
        f.write(get_info)
    cmd = f"make -f {ftmp} p={prj_name} {target_name} -p"
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    os.system(f"rm -rf {ftmp}")
    if process.returncode == 0:
        outputs = output.decode('utf-8')
    else:
        print(f" failed to execut cmd {cmd}, returncode: {process.returncode}, error: {error.decode('utf-8')}")
        sys.exit(-1)
    lines = [line.strip() for line in outputs.split("\n") if line.strip() and not line.startswith("#")]

    return lines

def get_partition_sizes(prj_name, filename):
    partition_sizes = {}
    lines = get_project_cfg(prj_name, filename)

    auto_fit_partition_name = None
    for line in lines:
        line = line.strip()
        if line.startswith("#"):
            continue
        match = re.search(r'(\w+)_PARTITION_SIZE\s+:=\s+(\w+)', line)
        if match:
            partition_name = match.group(1).lower()
            partition_size = match.group(2)
            partition_sizes[partition_name] = partition_size
        else:
            match = re.search(r'AUTO_FIT_PARTITION\s+:=\s+(\w+)', line)
            if match:
                auto_fit_partition_name = match.group(1).lower()

    if auto_fit_partition_name in partition_sizes.keys():
        partition_sizes[auto_fit_partition_name] = "0xffffffff"

    return partition_sizes

def convert_to_MB(size):
    if size.endswith('K'):
        return str(int(size[:-1])//1024)
    elif size.endswith('M'):
        return str(int(size[:-1]))
    else:
        if (str(size).lower() == "0xffffffff"):
            return str(size).lower()
        raise ValueError(f"Invalid size: {size}")

def convert_to_512KB(size):
    if size.endswith('K'):
        return str(int(size[:-1]) // 512)
    elif size.endswith('M'):
        return str( (int(size[:-1]) * 1024) // 512)
    else:
        if (str(size).lower() == "0xffffffff"):
            return str(size).lower()
        raise ValueError(f"Invalid size: {size}")

def convert_to_KB(size):
    if size.endswith('K'):
        return str(int(size[:-1]))
    elif size.endswith('M'):
        return str(int(size[:-1]) * 1024)
    else:
        if (str(size).lower() == "0xffffffff"):
            return str(size).lower()
        raise ValueError(f"Invalid size: {size}")

def convert_to_Byte(size):
    if size.endswith('K'):
        return str(int(size[:-1])*1024)
    elif size.endswith('M'):
        return str(int(size[:-1]) * 1048576)
    else:
        if (str(size).lower() == "0xffffffff"):
            return str(size).lower()
        raise ValueError(f"Invalid size: {size}")

def convert_to_sector(size):
    raise ValueError(f"Unsupported sector unit!")

def gen_new_xml(src_xml, dst_xml, partitions_info):
    tree = ET.parse(src_xml)
    root = tree.getroot()
    #Unit: 0, 1M Byte; 1, 512K Byte; 2, 1K Byte; 3, 1 Byte; 4, 1Sector
    convert_size = {
        0 : convert_to_MB,
        1 : convert_to_512KB,
        2 : convert_to_KB,
        3 : convert_to_Byte,
        4 : convert_to_sector
    }
    for partitions in root.iter('Partitions'):
        for partName, partSize in partitions_info.items():
            matched = False
            unit = int(partitions.attrib.get('unit'))
            for partition in partitions:
                if partition.attrib.get('id') == partName:
                    partition.set('size', convert_size[unit](partSize))
                    matched = True
                    print(f"matched partition: {partName}, set size to: {partSize}")
            if not matched:
                raise AttributeError(f"{src_xml} 文件没有 '{partName}'分区!")
    tree.write(dst_xml, encoding="utf-8", xml_declaration=True, method="xml", pretty_print=True)

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("para error!")
        print("usage:{project} gen_axp_xml.py src_xml project.mak dst_xml")
        sys.exit(-1)

    prj_name    = sys.argv[1]
    src_xml     = sys.argv[2]
    project_mak = sys.argv[3]
    dst_xml     = sys.argv[4]

    partition_sizes = get_partition_sizes(prj_name, project_mak)
    gen_new_xml(src_xml, dst_xml, partition_sizes)
    print("gen axp xml done!!!")


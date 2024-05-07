#encoding=utf-8
import re
import os
import sys
import subprocess
import random

try:
    from lxml import etree
except ModuleNotFoundError as e:
    os.system("python3 -m pip install --upgrade pip")
    os.system("pip3 install lxml")
    from lxml import etree

append_target='''
.PHONY: {target}
{target}:
	@$(ECHO) -e $(GREEN) "uboot $@..." $(DONE)
'''

img_node_configs={
    "param":{"select":0,},
    "rawdata":{"flag":0, "select":0, "type":"ERASEFLASH"},
}

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

def overlay_img_node_configs(prj_name, filename, node_configs=img_node_configs):
    lines = get_project_cfg(prj_name, filename)
    match = re.search(r"'XML_IMG_OPTION *:= *(.*?)'", str(lines))
    if match:
        match = match.group(1).replace("'","").replace('"','').replace(" ","").split(',')
        for pair in match:
            key, value = pair.split(':')
            node_key, node_value = value.split('=')
            tmp_node_dict = {node_key : node_value}
            if not node_configs.get(key):
                node_configs[key] = tmp_node_dict
            else:
                node_configs[key].update(tmp_node_dict)
    return node_configs

def get_partitions_info(prj_name, filename):
    partition_sizes = {}
    flash_partitions = None
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
            else:
                match = re.search(r'FLASH_PARTITIONS\s+[:,+]=\s+(.+)', line)
                if match:
                    flash_partitions=match.group(1)

    if auto_fit_partition_name in partition_sizes.keys():
        partition_sizes[auto_fit_partition_name] = "0xffffffff"

    if flash_partitions is None:
        raise Exception(f"critical: no FLASH_PARTITIONS found in {filename}")
    fpts = flash_partitions.split(",")
    partition_list = []
    partition_map={}
    for fpt in fpts:
        matched = re.search(r'(\w+)\((\w+)\)', fpt)
        if not matched:
            raise Exception(f"invalid partition: {fpt}")
        sz,name=matched.groups()
        if name in partition_map.keys():
            raise Exception(f"multiple partion found: {name}")
        if name == auto_fit_partition_name:
            sz = "0xffffffff"
        partition_map[name] = sz
        partition_list.append([name,sz])

    return partition_list

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

def gen_partitions_node(partitions_info, parent_node):
    #Unit: 0, 1M Byte; 1, 512K Byte; 2, 1K Byte; 3, 1 Byte; 4, 1Sector
    convert_size = {
        0 : convert_to_MB,
        1 : convert_to_512KB,
        2 : convert_to_KB,
        3 : convert_to_Byte,
        4 : convert_to_sector
    }
    unit = int(parent_node.attrib.get('unit'))
    print(f"[DEBUG] unit:{unit}")
    for info in partitions_info:
        name, size = info
        new_partition_node = etree.Element("Partition", gap="0", id=f"{name}", size=f"{convert_size[unit](size)}")
        parent_node.append(new_partition_node)

def new_img_node(name,size, parent_node):
    attr_type = None
    if name in img_node_configs.keys():
        attr_select = img_node_configs[name].get("select", 1)
        attr_flag = img_node_configs[name].get("flag", 1)
        attr_type = img_node_configs[name].get("type", "CODE")
        img_node = etree.SubElement(parent_node, "Img", flag=f"{attr_flag}", name=f"{name.upper()}", select=f"{attr_select}")
    else:
        img_node = etree.SubElement(parent_node, "Img", flag="1", name=f"{name.upper()}", select="1")
    id_node = etree.SubElement(img_node, "ID")
    id_node.text = f"{name.upper()}"
    img_node.append(id_node)
    type_node = etree.SubElement(img_node, "Type")
    if attr_type is not None:
         type_node.text = attr_type
    else:
        type_node.text = "CODE"
    img_node.append(type_node)
    block_node = etree.SubElement(img_node, "Block", id=f"{name}")
    img_node.append(block_node)
    base_node = etree.SubElement(block_node, "Base")
    base_node.text = "0x0"
    size_node = etree.SubElement(block_node, "Size")
    size_node.text = "0x0"
    block_node.append(base_node)
    block_node.append(size_node)
    file_node = etree.SubElement(img_node, "File")
    auth_node = etree.SubElement(img_node, "Auth", algo="0")
    description_node = etree.SubElement(img_node, "Description")
    description_node.text = f"Download {name} image file"
    img_node.append(file_node)
    img_node.append(auth_node)
    img_node.append(description_node)
    return img_node

def gen_ImgList_node(partitions_info, imglist_node):
    spl_info = None
    for info in partitions_info:
        name,size=info
        if name == "spl":
            spl_info = info
            continue
        if name == "env":
            continue
        new_img_node(name, size, imglist_node)

    if spl_info is None:
        raise Exception("no SPL img found!!!")

    name,size=spl_info
    new_img_node(name, size, imglist_node)

    return imglist_node

def gen_new_xml(src_xml, dst_xml, partitions_info):
    parser = etree.XMLParser(remove_blank_text=True)
    tree = etree.parse(src_xml, parser)
    root = tree.getroot()
    partitions_node = tree.xpath("//Partitions")[0]
    imglist_node    = tree.xpath("//ImgList")[0]
    gen_partitions_node(partitions_info, partitions_node)
    gen_ImgList_node(partitions_info, imglist_node)
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

    overlay_img_node_configs(prj_name, project_mak, img_node_configs)
    partitions_info = get_partitions_info(prj_name, project_mak)
    gen_new_xml(src_xml, dst_xml, partitions_info)
    print("gen axp xml done!!!")


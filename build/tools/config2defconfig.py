#encoding=utf-8
import sys
import os
import re
import subprocess
import random

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

def usage():
    print('''usage:
    {} project makefile config_maps.txt in_defconfig out_defconfig
    '''.format(os.path.basename(sys.argv[0])))

def merge_defconfig(src_defconfig, config_maps, out_defconfig):

    out_dir = os.path.dirname(os.path.abspath(out_defconfig))

    if not os.path.exists(src_defconfig):
        print("[error] cannot find deconfig file: {}".format(src_defconfig))
        return False

    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    patched_configs = []
    with open(src_defconfig) as f:
        src_lines = f.readlines()

    ptn=r"(\w+)\s*=\s*(\w+)"
    new_config_lines = []
    for line in src_lines:
        if line.strip().startswith("#"):
            new_config_lines.append(line)
            continue
        matched = re.search(ptn, line)
        if not matched:
            new_config_lines.append(line)
            continue
        k,_ = matched.groups()
        if k in config_maps.keys():
            patched_configs.append(k)
            new_config="{}={}\n".format(k,config_maps[k])
            new_config_lines.append(new_config)
        else:
            new_config_lines.append(line)

    for k in config_maps.keys():
        if k not in patched_configs:
            new_config="{}={}\n".format(k,config_maps[k])
            new_config_lines.append(new_config)

    with open(out_defconfig, "wt") as f:
        f.writelines(new_config_lines)

    print("patch {} done!".format(src_defconfig))

def parse_config_maps(cfg_map):
    with open(cfg_map) as f:
        lines = [line.strip() for line in f if line.strip() and not line.startswith("#")]

    cfg_maps = {}
    for line in lines:
        k,v = line.split(":")
        cfg_maps.update({k.strip():v.strip()})

    return cfg_maps

def parse_project_mak(prj_name, prj_mak, cfg_maps):
    lines = get_project_cfg(prj_name, prj_mak)
    ptn=r"(\w+)\s*:?=\s*(\w+)"
    config_maps = {}
    for line in lines:
        matched = re.search(ptn, line)
        if not matched:
            continue
        k,v = matched.groups()
        if k in cfg_maps.keys():
            val = v.lower()
            if val in ("true", "yes"):
                config_val = 'y'
            elif val in ("false", "no"):
                config_val = 'n'
            else:
                config_val = v
            print(f"set {cfg_maps[k]}={config_val}")
            config_maps.update({cfg_maps[k]:config_val})

    return config_maps


if __name__ == "__main__":
    args_count = len(sys.argv)
    if args_count != 6:
        usage()
        sys.exit(0)

    prj_name, prj_mak,cfg_map,src_defconfig,out_defconfig = sys.argv[1:6]
    config_maps = parse_config_maps(cfg_map)
    print("##################################################################")
    print(config_maps)
    configs_to_merge = parse_project_mak(prj_name, prj_mak, config_maps)
    print("##################################################################")
    merge_defconfig(src_defconfig, configs_to_merge, out_defconfig)
    print(f"patch {src_defconfig} success!!!")

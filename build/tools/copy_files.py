#encoding=utf-8
import re
import os
import sys
import subprocess
import random

append_target='''
.PHONY: {target}
{target}:
	@$(ECHO) -e $(GREEN) "$@..." $(DONE)
'''

global_variables = {
    "PROJECT"       : None,
    "LIBC"          : None,
    "ARCH"          : None,
    "MSP_OUT_DIR"   : None,
    "OSDRV_OUT_DIR" : None,
    "KERNEL_DIR"    : None
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

def get_global_variables(prj_name, filename):
    lines = get_project_cfg(prj_name, filename)
    for line in lines:
        line = line.strip()
        if line.startswith("#"):
            continue
        for k in global_variables.keys():
            ptn = r"{}\s*[?,:,+]?=\s*([^#\s]+)".format(k)
            matched = re.search(ptn, line)
            if matched:
                global_variables[k] = matched.groups()[0]
                print("global_variables: {}:{}".format(k, global_variables[k]))

    for k in global_variables.keys():
        if global_variables[k] is None:
            raise ValueError("global_variables: {} is None !!!".format(k))

def copy_files(src_dir, src_file_list, dst_dir):
    '''if not os.path.exists(src_dir):
        print(f"Error: {src_dir} does not exist.")
        return False'''

    if not os.path.exists(src_file_list):
        print(f"Error: {src_file_list} does not exist.")
        return False

    with open(src_file_list, "r") as f:
        file_list = [line.strip() for line in f if line.strip() and not line.startswith("#")]
    file_content = "\n".join(file_list)

    for key, value in global_variables.items():
        if value:
            file_content = file_content.replace(f"$({key})", value)

    print("========================================")
    print(file_content)
    print("========================================")
    file_list = file_content.split("\n")

    rm_file_list = []
    file_dir = ""
    for file_path in file_list:
        if (file_path.startswith("@dir:")):
            file_dir = file_path.split("@dir:")[-1].strip()
            continue
        if file_path.startswith("-"):
            rm_file_path = os.path.join(dst_dir, file_path[1:])
            rm_file_list.append(rm_file_path)
        else:
            if " " in file_path:
                src_path, dst_path = file_path.split()
            else:
                src_path = file_path
                dst_path = file_path
                if "*" in os.path.basename(src_path):
                    if (-1 != src_path.find(os.path.sep)):
                        dst_path = "{}{}".format(os.path.dirname(dst_path), os.path.sep)
                    else:
                        dst_path = os.path.dirname(dst_path)

            src_file = os.path.join(src_dir, file_dir, src_path)
            dst_file = os.path.join(dst_dir, dst_path)

            try:
                dst_dirname = os.path.dirname(dst_file)
                if not os.path.exists(dst_dirname):
                    os.makedirs(dst_dirname)
                if os.path.islink(src_file):
                    link_file = os.readlink(src_file)
                    #避免多次install报错
                    if os.path.exists(dst_file):
                        os.system(f"rm -rf {dst_file}")
                    print(f"ln -s {link_file} {dst_file}")
                    os.system(f"ln -s {link_file} {dst_file}")
                else:
                    print(f"cp -Rf {src_file} {dst_file}")
                    os.system(f"cp -Rf {src_file} {dst_file}")
            except Exception as e:
                print(f"Error: {e}")
                return False

    for rm_file_path in rm_file_list:
        print(f"rm -rf {rm_file_path}")
        os.system(f"rm -rf {rm_file_path}")

    return True

if __name__ == "__main__":
    if len(sys.argv) != 6:
        print("para error!")
        print("usage: {project} {project_mak} cpoy_files.py src_dir src_file_list dst_dir")
        sys.exit(-1)

    prj_name      = sys.argv[1]
    project_mak   = sys.argv[2]
    src_dir       = sys.argv[3]
    src_file_list = sys.argv[4]
    dst_dir       = sys.argv[5]

    global_variables["PROJECT"]=prj_name.strip()
    get_global_variables(prj_name, project_mak)

    if not copy_files(src_dir, src_file_list, dst_dir):
        sys.exit(-1)

    print("Copied files successfully!")

#encoding=utf-8
import os
import sys

def copy_files(src_dir, src_file_list, dst_dir):
    if not os.path.exists(src_dir):
        print(f"Error: {src_dir} does not exist.")
        return False

    if not os.path.exists(src_file_list):
        print(f"Error: {src_file_list} does not exist.")
        return False

    with open(src_file_list, "r") as f:
        file_list = [line.strip() for line in f if line.strip() and not line.startswith("#")]

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
    if len(sys.argv) != 4:
        print("para error!")
        print("usage: cpoy_files.py src_dir src_file_list dst_dir")
        sys.exit(-1)

    src_dir = sys.argv[1]
    src_file_list = sys.argv[2]
    dst_dir = sys.argv[3]

    if not copy_files(src_dir, src_file_list, dst_dir):
        sys.exit(-1)

    print("Copied files successfully!")

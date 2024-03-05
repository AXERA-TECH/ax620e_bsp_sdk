#encoding=utf-8
import os
import sys

def copy_debug(dbg_dir, dbg_type, dst_dir, dst_type):
    '''
    step 1: list all {files}.'dst_type' files in dst_dir
    step 2: find all {files}.'dbg_type' files in dbg_dir
    step 3: use {files}.'dbg_type' files cover {files}.'dst_type' files
    '''
    if not os.path.exists(dbg_dir):
        print(f"[error] path {dbg_dir} does not exists!!!")
        return False
    if not os.path.exists(dst_dir):
        print(f"[error] path {dst_dir} does not exists!!!")
        return False
    flist = os.listdir(dst_dir)
    for f in flist:
        dst_file_path = os.path.join(dst_dir,f)
        fname = f.split(".")[0]
        ftype = f.split(".")[-1]
        if os.path.isfile(dst_file_path) and ftype == dst_type:
            dbg_file = f"{fname}.{dbg_type}"
            dbg_file_path = os.path.join(dbg_dir, dbg_file)
        else:
            continue
        if not os.path.exists(dbg_file_path):
            print(f"[WARN]: cannot find {dbg_file_path}")
            continue
        cmd = f"cp {dbg_file_path} {dst_file_path}"
        print(cmd)
        os.system(cmd)

    return True

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("para error!")
        print("usage: cpoy_debug.py dbg_dir dbg_type dst_dir dst_type")
        sys.exit(-1)

    dbg_dir, dbg_type, dst_dir, dst_type = sys.argv[1:]
    dbg_type = dbg_type.strip().split(".")[-1]
    dst_type = dst_type.strip().split(".")[-1]

    if not copy_debug(dbg_dir, dbg_type, dst_dir, dst_type):
        print(f"[error] failed to copy {dbg_type} from {dbg_dir} to {dst_dir}")
        sys.exit(-1)

    print("Copy debug files successfully!")

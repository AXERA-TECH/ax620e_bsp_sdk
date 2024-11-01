1) Description
Runs CA/TA to read/write efuse value


2) Usage
./sample_optee_efuse  param1 param2 param3
param1: 0 read  1 write
param2: blk_id in decimal
param3: write val in hex, if param1 is 1

./sample_optee_efuse 0 13
./sample_optee_efuse 1 13 0x80       //warning!!! efuse blk bit can only write once and cannot be written again!!!
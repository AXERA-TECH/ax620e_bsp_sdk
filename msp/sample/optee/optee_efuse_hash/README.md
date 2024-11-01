1) Description
1.1) Runs CA to generate RSA publick key hash value and write to efuse through TA
1.2)本测试案例用于生成RSA2048和RSA3072两种pub hash值，根据用户使用的签名加密算法，生成的hash是进行熔丝，用于后续校验签名的镜像；
1.3)用户如果自己生成了公私密钥，需要替换key_n_2048[256] 或者key_n_3072[384] 数组，可通过命令openssl rsa -modulus -in private.pem -text
获取key信息；
#: openssl rsa -modulus -in private.pem -text
RSA Private-Key: (2048 bit, 2 primes)
modulus:
    00:90:e1:31:81:d2:22:72:c3:13:63:b4:04:54:a4:
    f5:45:95:e6:36:86:d7:27:77:c8:18:68:b9:09:59:
    a9:fa:4a:9a:eb:3b:8b:dc:2c:7c:cd:1d:6d:be:0e:
    5e:ae:ff:4f:9f:f0:40:90:e1:31:81:d2:22:72:c3:
    13:63:b4:04:54:a4:f5:45:95:e6:36:86:d7:27:77:
    c8:18:68:b9:09:59:a9:fa:4a:9a:eb:3b:8b:dc:2c:
    7c:cd:1d:6d:be:0e:5e:ae:ff:4f:9f:f0:40:90:e1:
    31:81:d2:22:72:c3:13:63:b4:04:54:a4:f5:45:95:
    e6:36:86:d7:27:77:c8:1b:d9:38:e8:98:47:f7:a7:
    57:06:b6:66:15:c5:75:24:d4:84:33:e3:93:42:f2:
    a2:52:01:b1:61:10:c0:70:1f:cf:7f:2e:de:8e:3d:
    ed:9d:4c:fc:ac:5c:0b:bb:6b:1a:ca:7a:29:d9:89:
    38:e8:98:47:f7:a7:57:06:b6:66:15:c5:75:24:d4:
    84:33:e3:93:42:f2:a2:52:01:b1:61:10:c0:70:1f:
    cf:7f:2e:de:8e:3d:ed:9d:4c:fc:ac:5c:0b:bb:6b:
    1a:ca:7a:29:d9:89:38:e8:98:47:f7:a7:57:06:b6:
    66:15:c5:75:24:d4:84:33:e3:93:42:f2:a2:52:06:
    be:2b
publicExponent: 65537 (0x10001)


2) Usage
2.1)  ./sample_optee_efuse_hash

2.2) result show following result
RSA2048 hash value is:
78ddfe9e, 698a9288, ccad1548,5ca04574
9f1aa945, f57eb822, b807db67,29140398
RSA3072 hash value is:
6c1dda30, 53cd22c1, 97beb790,aaeda709
ef49ed74, ec82d080, 90175efb,637dd4e5

2.3) efuse can only write once, the writing action not really done in code
if need it, please enable the commented out code and modify which hash value to be written, then compile it again.
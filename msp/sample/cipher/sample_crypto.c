/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <linux/if_alg.h>

static unsigned char sha1_msg[] = {"abc"};

static unsigned char sha1_digest[20] =
{
    0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a, 0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c, 0x9c, 0xd0, 0xd8, 0x9d
};

static char aes_key[] = {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
};

static char aes_ptx[] = {
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
    0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
    0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10
};

static char aes_ctx[] = {
    0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
    0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
    0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
    0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7
};

static char aes_iv[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

int SAMPLE_CIPHER_CrypoHashTest()
{
    int opfd;
    int tfmfd;
    struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "hash",
        .salg_name = "axcipher-sha1"
    };
    char buf[20];

    tfmfd = socket(AF_ALG, SOCK_SEQPACKET, 0);
    if (tfmfd == -1) {
        printf("socket error errno is %d\n", errno);
        perror("socket error");
    }

    if (0 == bind(tfmfd, (struct sockaddr *)&sa, sizeof(sa))) {

        opfd = accept(tfmfd, NULL, 0);

        write(opfd, sha1_msg, 3);

        read(opfd, buf, 20);

        if (memcmp(buf, sha1_digest, 20) != 0) {
            printf("%s, hash compare fail \n", __func__);
            return -1;
        }

        printf("%s PASS\n", __func__);

        close(opfd);
    }

    close(tfmfd);
    return 0;
}

int SAMPLE_CIPHER_CrypoAesTest()
{
    int opfd;
    int tfmfd;
    struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "skcipher",
        .salg_name = "axcipher-cbc-aes"
    };
    struct msghdr msg = {};
    struct cmsghdr *cmsg;
    char cbuf[CMSG_SPACE(4) + CMSG_SPACE(20)] = {0};
    char buf[64];
    struct af_alg_iv *iv;
    struct iovec iov;

    tfmfd = socket(AF_ALG, SOCK_SEQPACKET, 0);

    if (0 == bind(tfmfd, (struct sockaddr *)&sa, sizeof(sa))) {

        setsockopt(tfmfd, SOL_ALG, ALG_SET_KEY, aes_key, 16);

        opfd = accept(tfmfd, NULL, 0);

        msg.msg_control = cbuf;
        msg.msg_controllen = sizeof(cbuf);

        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_ALG;
        cmsg->cmsg_type = ALG_SET_OP;
        cmsg->cmsg_len = CMSG_LEN(4);
        *(__u32 *)CMSG_DATA(cmsg) = ALG_OP_ENCRYPT;

        cmsg = CMSG_NXTHDR(&msg, cmsg);
        cmsg->cmsg_level = SOL_ALG;
        cmsg->cmsg_type = ALG_SET_IV;
        cmsg->cmsg_len = CMSG_LEN(20);
        iv = (void *)CMSG_DATA(cmsg);
        iv->ivlen = 16;
        memcpy(iv->iv, aes_iv, 16);

        iov.iov_base = aes_ptx;
        iov.iov_len = sizeof(aes_ptx);

        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;

        sendmsg(opfd, &msg, 0);
        read(opfd, buf, sizeof(aes_ctx));

        if (memcmp(buf, aes_ctx, sizeof(aes_ctx)) != 0) {
            printf("%s, aes compare fail \n", __func__);
            return -1;
        }

        printf("%s PASS\n", __func__);

        close(opfd);
    }
    close(tfmfd);

    return 0;
}

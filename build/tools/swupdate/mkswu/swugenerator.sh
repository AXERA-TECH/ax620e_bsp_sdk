#!/bin/bash

SW_DES_SOURCE='sw-description-source'
PRIV="./priv.pem"

ENCRYPT_MODE="NULL" #"RSA"
SW_DES="sw-description"

IMAGES=`cat sw-description-source | grep filename | sed 's#filename = "\(.\+\)";#\1#' | sort | uniq`

echo "===== calc sha ======="
cp ${SW_DES_SOURCE} ${SW_DES}
for i in $IMAGES;
do
    file_str='filename = "'${i}'"'
    file_gz_str='filename = "'${i}.gz'"'
    compressed='compressed = "zlib"'
    gzip -k -f $i

    # add hash line
    # hash='sha256="'`openssl dgst -sha256 ${i}.gz | awk '{ print $2}'`'"'
    # echo $i.gz $hash
    # sed -i '/'"${file_str}"'/{p;s/'"${file_str}"'/'"${hash}"'/g;}' ${SW_DES}

    # add compressed line
    sed -i '/'"${file_str}"'/{p;s/'"${file_str}"'/'"${compressed}"'/g;}' ${SW_DES}
    # modify filename to filename.gz
    sed -i 's/'"${file_str}"'/'"${file_gz_str}"'/g' ${SW_DES}
done
echo "===== calc sha ======="

if ! [ x"${ENCRYPT_MODE}" = "xNULL" ]; then
    #if you use RSA
    if [ x"${ENCRYPT_MODE}" = "xRSA" ]; then
        openssl dgst -sha256 -passin pass:123456 -sign ${PRIV} sw-description > sw-description.sig
    else
        openssl cms -sign -in  sw-description -out sw-description.sig -signer mycert.cert.pem \
            -inkey mycert.key.pem -outform DER -nosmimecap -binary
    fi
fi

IMAGES=`cat sw-description | grep filename | sed 's#filename = "\(.\+\)";#\1#' | sort | uniq`
FILES="$SW_DES $IMAGES"
for i in $FILES;do
        echo $i;done | cpio -ov -H crc >  $1

for i in $FILES;do
	rm ${i}
done

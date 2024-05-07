#!/usr/bin/env bash

set -e

PROJECT=$1
OTA_PKG=${PROJECT}_$(date "+%Y%m%d%H%M%S").swu
SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

BUILD_PATH=${SCRIPT_DIR}/../../

echo "PROJECT=${PROJECT}"
OUT_PATH=${BUILD_PATH}/out/${PROJECT}/images

cp -rf ${BUILD_PATH}/tools/swupdate/mkswu/ota.sh ${OUT_PATH}
cp -rf ${BUILD_PATH}/tools/swupdate/mkswu/swugenerator.sh ${OUT_PATH}
# cp -rf ${BUILD_PATH}/tools/swupdate/mkswu/priv.pem ${OUT_PATH}
cp -rf ${BUILD_PATH}/projects/${PROJECT}/swupdate/sw-description-source ${OUT_PATH}

cd ${OUT_PATH}
sh swugenerator.sh ${OTA_PKG}
mv ${OTA_PKG} ../../
rm -rf swugenerator.sh
rm -rf ota.sh
# rm -rf priv.pem
rm -rf sw-description-source
cd -

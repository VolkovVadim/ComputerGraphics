#!/bin/bash

BIN_DIR=Build
CURR_DIR=${PWD}
PROJECT_DIR="$( cd "$(dirname "$0")" ; pwd -P )"
CLEAN_SCRIPT=clean.sh
CONFIG=$1

CLEAN_SCRIPT=${PROJECT_DIR}/${CLEAN_SCRIPT}
BIN_DIR=${PROJECT_DIR}/${BIN_DIR}

if [ -f /proc/cpuinfo ]
then
    MAKE_THREADS=`grep -c ^processor /proc/cpuinfo`
else
    MAKE_THREADS=8
fi

if [ -x ${CLEAN_SCRIPT} ]
then
    ${CLEAN_SCRIPT}
else
    if [ -d ${BIN_DIR} ]
    then
        rm -rfv ${BIN_DIR}/*
    fi
fi

if [ ! -d ${BIN_DIR} ]
then
    echo "Creating build directory..."
    mkdir -pv ${BIN_DIR}
fi

if [ -z ${CONFIG} ]
then
    CONFIG=debug
fi

echo "Project configuration : ${CONFIG}"
cd ${BIN_DIR}
cmake ${PROJECT_DIR} -DCONFIG=${CONFIG} && make -j${MAKE_THREADS}
cp -v ${PROJECT_DIR}/Textures/* ${BIN_DIR}/${CONFIG}/Bin
cd ${CURR_DIR}

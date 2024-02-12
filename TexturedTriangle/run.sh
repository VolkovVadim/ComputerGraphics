#!/bin/bash

BIN_DIR=Build
APP_NAME=AppLauncher
CONFIG=Release
ARGS=$*
PROJECT_DIR="$( cd "$(dirname "$0")" ; pwd -P )"

APP=${PROJECT_DIR}/${BIN_DIR}/${CONFIG}/Bin/${APP_NAME}
if [ ! -f ${APP} ]
then
    CONFIG=Debug
    APP=${PROJECT_DIR}/${BIN_DIR}/${CONFIG}/Bin/${APP_NAME}

    if [ ! -f ${APP} ]
    then
        echo "Error : unable to find app binary ${APP}"
        exit 1
    fi
fi

cd ${PROJECT_DIR}/${BIN_DIR}/${CONFIG}/Bin
echo "Starting application ${APP_NAME}"
./${APP_NAME} ${ARGS}

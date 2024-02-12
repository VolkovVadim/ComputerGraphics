#!/bin/bash

echo "Clearing..."

BIN_DIR=Build
PROJECT_DIR="$( cd "$(dirname "$0")" ; pwd -P )"

BIN_DIR=${PROJECT_DIR}/${BIN_DIR}

if [ -d ${BIN_DIR} ]
then
    rm -rfv ${BIN_DIR}/*
fi

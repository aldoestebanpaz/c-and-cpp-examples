#!/usr/bin/env bash


SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd ${SCRIPT_DIR}/libcentralizedresources/translations
lupdate .. -ts libcentralized.ts -locations absolute -no-obsolete
lupdate .. -ts libcentralized_*.ts -locations absolute -no-obsolete

cd ${SCRIPT_DIR}/sample-app-01/translations/ts
lupdate ../.. -ts sampleapp01.ts -locations absolute -no-obsolete
lupdate ../.. -ts sampleapp01_*.ts -locations absolute -no-obsolete

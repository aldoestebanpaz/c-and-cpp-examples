#!/usr/bin/env bash


SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd ${SCRIPT_DIR}/libsample/translations
lupdate .. -ts libsample.ts -locations absolute -no-obsolete
lupdate .. -ts libsample_*.ts -locations absolute -no-obsolete

cd ${SCRIPT_DIR}/sample-client/translations/ts
lupdate ../.. -ts sampleclient.ts -locations absolute -no-obsolete
lupdate ../.. -ts sampleclient_*.ts -locations absolute -no-obsolete

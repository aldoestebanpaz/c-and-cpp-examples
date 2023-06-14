#!/usr/bin/env bash


SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd ${SCRIPT_DIR}/sample-app/translations/ts
lupdate ../.. -ts sample-app.ts -locations absolute -no-obsolete
lupdate ../.. -ts sample-app_*.ts -locations absolute -no-obsolete

cd ${SCRIPT_DIR}/sample-app/translations/desktop
cat <<EOT > sample-app.desktop.yaml
Desktop Entry/Name: "Aldo's Sample App"
Desktop Entry/Comment: "Example app created with Qt"
Desktop Entry/GenericName: "Sample App"

EOT

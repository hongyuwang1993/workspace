#!/bin/bash
SCRIPT_NAME=$(basename $0)
SCRIPT_DIR=$(cd "$(dirname $0)"; pwd)
SCRIPT_DIR_NAME=$(basename "${SCRIPT_DIR}")

cd "${SCRIPT_DIR}"
source init-vars.sh

cd ..

echo "running cpplint..."

report_file="${REPORT_DIR_NAME}/report-cppcheck-cpplint.xml"
cpplint_options="--filter=-whitespace,-readability/utf8,-build/namespaces,-build/include,-runtime/references,-runtime/int"
changed_files=$(getLastChangedFileListsWithFilter ".*\.\(cpp\|h\|hpp\|hh\)")

if [ "" = "${changed_files}" ] ; then
    echo '<?xml version="1.0" encoding="UTF-8"?><results></results>' > "${report_file}"
    exit 0
fi

python "${TOOL_DIR_NAME}/cpplint.py" ${cpplint_options} ${changed_files} 2>&1 | python "${TOOL_DIR_NAME}/cpplint_to_cppcheckxml.py" 2>&1 | tee "${report_file}"

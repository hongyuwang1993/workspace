#!/bin/bash
SCRIPT_NAME=$(basename $0)
SCRIPT_DIR=$(cd "$(dirname $0)"; pwd)
SCRIPT_DIR_NAME=$(basename "${SCRIPT_DIR}")

cd "${SCRIPT_DIR}"
source init-vars.sh

cd ..

echo "running cppcheck..."

report_file="${REPORT_DIR_NAME}/report-cppcheck.xml"
suppressions_list="--suppressions-list=${SCRIPT_DIR_NAME}/cppcheck_suppress.rule"
changed_files=$(getLastChangedFileListsWithFilter ".*\.\(cpp\|h\|hh\)")

if [ "" = "${changed_files}" ] ; then
    echo '<?xml version="1.0" encoding="UTF-8"?><results></results>' > "${report_file}"
    exit 0
fi

# Run most of the checks in parallel
cppcheck --xml --enable=style,performance,portability,information -j 4 -q "${suppressions_list}" ${changed_files} 2>&1 | tee "${report_file}"

# Unused function checking must happen in one job
 cppcheck --xml --enable=unusedFunction -q "${suppressions_list}" source 2>&1 | tee "${REPORT_DIR_NAME}/report-cppcheck-unused-functions.xml"

# Finally, check the configuration
 cppcheck --xml --enable=missingInclude -j 4 --force -q "${suppressions_list}" ${changed_files} 2>&1 | tee "${REPORT_DIR_NAME}/report-cppcheck-configuration.xml"

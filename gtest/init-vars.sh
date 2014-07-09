#!/bin/bash
TOOL_DIR_NAME="build_tools"
REPORT_DIR_NAME="build_reports"

if [ ! -e "${SCRIPT_DIR}/../${REPORT_DIR_NAME}" ] ; then
    mkdir -p "${SCRIPT_DIR}/../${REPORT_DIR_NAME}"
fi

function getLastChangedFileLists {
    git log -n 1 --oneline --name-only | sed 1d | tr "\n" " "
}

function getLastChangedFileListsWithFilter {
    git log -n 1 --oneline --name-only | sed 1d | grep $1 | tr "\n" " "
}

function clearReports {
    find "${SCRIPT_DIR}/../${REPORT_DIR_NAME}" -iname 'report-*.xml' -exec rm {} \;
}

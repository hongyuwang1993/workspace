#!/bin/bash
SCRIPT_NAME=$(basename $0)
SCRIPT_DIR=$(cd "$(dirname $0)"; pwd)
SCRIPT_DIR_NAME=$(basename "${SCRIPT_DIR}")

cd "${SCRIPT_DIR}"
source init-vars.sh

cd ..

echo "running simian..."

java -jar "${TOOL_DIR_NAME}/simian-2.3.34.jar" -threshold=6 -formatter=xml:"${REPORT_DIR_NAME}/report-simian.xml" \
            -excludes="**/Services/Common/*.*" \
            -excludes="**/Services/AccountService/*.*" \
            -excludes="**/Services/ChartsService/*.*" \
            -excludes="**/Services/FeedbackService/*.*" \
            -excludes="**/Services/LimitationService/*.*" \
            -excludes="**/Services/MessageService/*.*" \
            -excludes="**/Services/PaymentService/*.*" \
            -excludes="**/Services/ProbabilityService/*.*" \
            -excludes="**/Services/PushService/*.*" \
            -excludes="**/Services/SSOService/*.*" \
            'source/**/*.h' 'source/**/*.hpp' 'source/**/*.cpp'

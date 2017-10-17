#!/bin/bash

#
#   Copyright 2017 American Printing House for the Blind Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

OUTPUT=build/test/output-tools.txt

echo testing tools
echo testing tools > $OUTPUT
echo >> $OUTPUT
if (( $? != 0 )) ; then exit ; fi

FAIL_CNT=0

echo -n "lou_convert:  "
echo "lou_convert ⠒⠭⠒⠀⠒⠭⠿⠭⠒" >> $OUTPUT

FAIL_PRV=$FAIL_CNT

RESULT=`echo '⠒⠭⠒⠀⠒⠭⠿⠭⠒' | ./build/tools/lou_convert test/tables/tools.cvt 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=#=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '⠒⠭⠒⠀⠒⠭⠿⠭⠒' | ./build/tools/lou_convert -p test/tables tools.cvt 2>&1`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=#=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=#=-' | ./build/tools/lou_convert -b test/tables/tools.cvt 2>&1`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠭⠿⠭⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=#=-' | ./build/tools/lou_convert -b -p test/tables tools.cvt 2>&1`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠭⠿⠭⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`./build/tools/lou_convert -d ⠁⠂⠄⠈⠐⠠⠉⠛⠒⠶⠇⠸⠿ 2>&1`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '1-2-3-4-5-6-14-1245-25-2356-123-456-123456' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`./build/tools/lou_convert -u 1-2-3-4-5-6-14-1245-25-2356-123-456-123456 2>&1`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠁⠂⠄⠈⠐⠠⠉⠛⠒⠶⠇⠸⠿' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi


if (( FAIL_PRV == FAIL_CNT )); then echo PASS; else echo FAIL; fi



echo -n "lou_translate:  "
echo >> $OUTPUT
echo "lou_translate -=- -=-=-" >> $OUTPUT

FAIL_PRV=$FAIL_CNT

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate test/tables/tools.rst 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠿⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate -p test/tables tools.rst 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠿⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate test/tables/tools.rst test/tables/tools.cvt 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -#-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate -p test/tables tools.rst tools.cvt 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -#-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '⠒⠭⠒⠀⠒⠿⠒' | ./build/tools/lou_translate -b test/tables/tools.rst 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '⠒⠭⠒⠀⠒⠿⠒' | ./build/tools/lou_translate -b -p test/tables tools.rst 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -#-' | ./build/tools/lou_translate -b test/tables/tools.rst test/tables/tools.cvt 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -#-' | ./build/tools/lou_translate -b -p test/tables tools.rst tools.cvt 2>&1`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi


if (( FAIL_PRV == FAIL_CNT )); then echo PASS; else echo FAIL; fi

echo

exit $FAIL_CNT

#!/bin/bash

# LibLouisAPH Braille Translation and Back-Translation Library
#
# Copyright (C) 2017 American Printing House for the Blind, Inc.
#
# This file is part of LibLouisAPH.
#
# LibLouisAPH is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 2.1 of the License, or
# (at your option) any later version.
#
# LibLouisAPH is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with LibLouisAPH. If not, see <http://www.gnu.org/licenses/>.

OUTPUT=build/test/output-tools.txt

echo testing tools
echo testing tools > $OUTPUT
echo >> $OUTPUT
if (( $? != 0 )) ; then exit ; fi

FAIL_CNT=0

echo -n "lou_convert:  "
echo "lou_convert ⠒⠭⠒⠀⠒⠭⠿⠭⠒" >> $OUTPUT

FAIL_PRV=$FAIL_CNT

RESULT=`echo '⠒⠭⠒⠀⠒⠭⠿⠭⠒' | ./build/tools/lou_convert test/tables/tools.cvt`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=#=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '⠒⠭⠒⠀⠒⠭⠿⠭⠒' | ./build/tools/lou_convert -p test/tables tools.cvt`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=#=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=#=-' | ./build/tools/lou_convert -b test/tables/tools.cvt`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠭⠿⠭⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=#=-' | ./build/tools/lou_convert -b -p test/tables tools.cvt`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠭⠿⠭⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`./build/tools/lou_convert -d ⠁⠂⠄⠈⠐⠠⠉⠛⠒⠶⠇⠸⠿`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '1-2-3-4-5-6-14-1245-25-2356-123-456-123456' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`./build/tools/lou_convert -u 1-2-3-4-5-6-14-1245-25-2356-123-456-123456`
if (( $? != 0 )); then FAIL_CNT=$((FAIL_CNT++)); fi
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠁⠂⠄⠈⠐⠠⠉⠛⠒⠶⠇⠸⠿' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi


if (( FAIL_PRV == FAIL_CNT )); then echo PASS; else echo FAIL; fi



echo -n "lou_translate:  "
echo >> $OUTPUT
echo "lou_translate -=- -=-=-" >> $OUTPUT

FAIL_PRV=$FAIL_CNT

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate test/tables/tools.rst`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠿⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate -p test/tables tools.rst`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '⠒⠭⠒⠀⠒⠿⠒' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate test/tables/tools.rst test/tables/tools.cvt`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -#-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -=-=-' | ./build/tools/lou_translate -p test/tables tools.rst tools.cvt`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -#-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '⠒⠭⠒⠀⠒⠿⠒' | ./build/tools/lou_translate -b test/tables/tools.rst`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '⠒⠭⠒⠀⠒⠿⠒' | ./build/tools/lou_translate -b -p test/tables tools.rst`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -#-' | ./build/tools/lou_translate -b test/tables/tools.rst test/tables/tools.cvt`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi

RESULT=`echo '-=- -#-' | ./build/tools/lou_translate -b -p test/tables tools.rst tools.cvt`
echo -n "$RESULT  " >> $OUTPUT
if [ "$RESULT" != '-=- -=-=-' ]; then FAIL_CNT=$((FAIL_CNT + 1)); echo FAIL >> $OUTPUT; else echo PASS >> $OUTPUT; fi


if (( FAIL_PRV == FAIL_CNT )); then echo PASS; else echo FAIL; fi

echo

exit $FAIL_CNT

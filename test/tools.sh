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

FAIL_CNT=0

################################################################################

echo >> $OUTPUT
echo -n "lou_table:  "

LOU_TABLE='./build/tools/lou_table'
#LOU_TABLE='valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/tools/lou_table'

FAIL_PRV=$FAIL_CNT

echo >> $OUTPUT
echo '################################################################################' >> $OUTPUT
echo $LOU_TABLE >> $OUTPUT
$LOU_TABLE >> $OUTPUT 2>&1


echo >> $OUTPUT
echo "lou_table test/tables/tools.rst" >> $OUTPUT
RESULT=`$LOU_TABLE test/tables/tools.rst 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
CORRECT="$(cat <<'EOI'
test/tables/tools.rst

process:  generic

control:  0xf001   0xf002   0xf003   0xf004   0xf005   0xf006   0xf007

characters:

character hash:
most = 0

modes:  [0]
   -  -  -  -  -  0  nocontract
   -  -  -  -  -  0  capital
   -  -  -  -  -  0  numeric

emphases:  [0]

subpatterns:

filters:

init chars hash:  [0]

init dots hash:  [0]

premode chars hash:  [0]

premode dots hash:  [0]

postmode chars hash:  [0]

postmode dots hash:  [0]

pretrans chars hash:  [0]

pretrans dots hash:  [0]

trans chars hash:  [6]
[   18]     1
   − ⠒
[   32]     1
   \s ⠀
[   45]     1
   - ⠒
[   61]     3
   =-= ⠿
   = ⠭
   = ⣉
most = 3

trans dots hash:  [6]
[    0]     1
   ⠀ \s
[   18]     2
   ⠒ -
   ⠒ −
[   45]     1
   ⠭ =
[   63]     1
   ⠿ =-=
[  201]     1
   ⣉ =
most = 2

posttrans chars hash:  [0]

posttrans dots hash:  [0]

fini chars hash:  [0]

fini dots hash:  [0]
EOI
)"
if [ "$RESULT" != "$CORRECT" ]
then
	FAIL_CNT=$((FAIL_CNT + 1))
	echo FAIL >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$RESULT" >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$CORRECT" >> $OUTPUT
	echo ===== >> $OUTPUT
else
	echo "$RESULT" >> $OUTPUT
	echo PASS >> $OUTPUT
fi

echo >> $OUTPUT
echo "lou_table -a test/tables/tools.rst" >> $OUTPUT
RESULT=`$LOU_TABLE -a test/tables/tools.rst 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
CORRECT="$(cat <<'EOI'
test/tables/tools.rst

ambiguous char rules:

chars init:

chars pretrans:

chars trans:
=   	⠭	⣉   	\x282d   \x28c9

ambiguous dot rules:

dots init:

dots pretrans:

dots trans:
⠒   	-	−   	\x002d   \x2212
EOI
)"
if [ "$RESULT" != "$CORRECT" ]
then
	FAIL_CNT=$((FAIL_CNT + 1))
	echo FAIL >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$RESULT" >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$CORRECT" >> $OUTPUT
	echo ===== >> $OUTPUT
else
	echo "$RESULT" >> $OUTPUT
	echo PASS >> $OUTPUT
fi


if (( FAIL_PRV == FAIL_CNT )); then echo PASS; else echo FAIL; fi

################################################################################

echo >> $OUTPUT
echo -n "lou_convert:  "

LOU_CONVERT='./build/tools/lou_convert'
#LOU_CONVERT='valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/tools/lou_convert'

FAIL_PRV=$FAIL_CNT

echo >> $OUTPUT
echo '################################################################################' >> $OUTPUT
echo $LOU_CONVERT >> $OUTPUT
$LOU_CONVERT >> $OUTPUT 2>&1


echo >> $OUTPUT
echo "lou_convert -o test/tables/tools.cvt" >> $OUTPUT
RESULT=`$LOU_CONVERT -o test/tables/tools.cvt 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
CORRECT="$(cat <<'EOI'
test/tables/tools.cvt
unknown:  ?

 ⠀  ⠁  ⠂  ⠃  ⠄  ⠅  ⠆  ⠇  ⠈  ⠉  ⠊  ⠋  ⠌  ⠍  ⠎  ⠏
 ⠐  ⠑ -⠒  ⠓  ⠔  ⠕  ⠖  ⠗  ⠘  ⠙  ⠚  ⠛  ⠜  ⠝  ⠞  ⠟
 ⠠  ⠡  ⠢  ⠣  ⠤  ⠥  ⠦  ⠧  ⠨  ⠩  ⠪  ⠫  ⠬ =⠭  ⠮  ⠯
 ⠰  ⠱  ⠲  ⠳  ⠴  ⠵  ⠶  ⠷  ⠸  ⠹  ⠺  ⠻  ⠼  ⠽  ⠾ #⠿
 ⡀  ⡁  ⡂  ⡃  ⡄  ⡅  ⡆  ⡇  ⡈  ⡉  ⡊  ⡋  ⡌  ⡍  ⡎  ⡏
 ⡐  ⡑  ⡒  ⡓  ⡔  ⡕  ⡖  ⡗  ⡘  ⡙  ⡚  ⡛  ⡜  ⡝  ⡞  ⡟
 ⡠  ⡡  ⡢  ⡣  ⡤  ⡥  ⡦  ⡧  ⡨  ⡩  ⡪  ⡫  ⡬  ⡭  ⡮  ⡯
 ⡰  ⡱  ⡲  ⡳  ⡴  ⡵  ⡶  ⡷  ⡸  ⡹  ⡺  ⡻  ⡼  ⡽  ⡾  ⡿
 ⢀  ⢁  ⢂  ⢃  ⢄  ⢅  ⢆  ⢇  ⢈  ⢉  ⢊  ⢋  ⢌  ⢍  ⢎  ⢏
 ⢐  ⢑  ⢒  ⢓  ⢔  ⢕  ⢖  ⢗  ⢘  ⢙  ⢚  ⢛  ⢜  ⢝  ⢞  ⢟
 ⢠  ⢡  ⢢  ⢣  ⢤  ⢥  ⢦  ⢧  ⢨  ⢩  ⢪  ⢫  ⢬  ⢭  ⢮  ⢯
 ⢰  ⢱  ⢲  ⢳  ⢴  ⢵  ⢶  ⢷  ⢸  ⢹  ⢺  ⢻  ⢼  ⢽  ⢾  ⢿
 ⣀  ⣁  ⣂  ⣃  ⣄  ⣅  ⣆  ⣇  ⣈  ⣉  ⣊  ⣋  ⣌  ⣍  ⣎  ⣏
 ⣐  ⣑  ⣒  ⣓  ⣔  ⣕  ⣖  ⣗  ⣘  ⣙  ⣚  ⣛  ⣜  ⣝  ⣞  ⣟
 ⣠  ⣡  ⣢  ⣣  ⣤  ⣥  ⣦  ⣧  ⣨  ⣩  ⣪  ⣫  ⣬  ⣭  ⣮  ⣯
 ⣰  ⣱  ⣲  ⣳  ⣴  ⣵  ⣶  ⣷  ⣸  ⣹  ⣺  ⣻  ⣼  ⣽  ⣾  ⣿
EOI
)"
if [ "$RESULT" != "$CORRECT" ]
then
	FAIL_CNT=$((FAIL_CNT + 1))
	echo FAIL >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$RESULT" >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$CORRECT" >> $OUTPUT
	echo ===== >> $OUTPUT
else
	echo "$RESULT" >> $OUTPUT
	echo PASS >> $OUTPUT
fi


CONVERT_TABLE=
CONVERT_OPTIONS=

function test_convert
{
	SOURCE=$1
	TARGET=$2

	echo >> $OUTPUT
	if [ -n "$CONVERT_OPTIONS" ]
	then
		echo "lou_convert $CONVERT_OPTIONS $CONVERT_TABLE < $SOURCE" >> $OUTPUT
	else
		echo "lou_convert $CONVERT_TABLE < $SOURCE" >> $OUTPUT
	fi

	if [ -z "$CONVERT_TABLE" ] ; then echo TEST FAILURE >> $OUTPUT ; exit 1 ; fi

	RESULT=`echo -n "$SOURCE" | $LOU_CONVERT $CONVERT_OPTIONS "$CONVERT_TABLE" 2>&1`
	if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$TARGET" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$TARGET" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

	RESULT=`echo "$SOURCE" | $LOU_CONVERT $CONVERT_OPTIONS "$CONVERT_TABLE" 2>&1`
	if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$TARGET" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$TARGET" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

}


CONVERT_TABLE="test/tables/tools.cvt"

CONVERT_OPTIONS=
test_convert ''        ''
test_convert '⠿'       '#'
test_convert '==⠿'     '??#'
test_convert '⠿⠿'      '##'
test_convert '===⠿'    '???#'
test_convert '====⠿'   '????#'
test_convert '⠿⠿⠿'     '###'
test_convert '⠿⠿⠿⠿⠿⠿'  '######'
test_convert '⠿⠿⠿⠿⠿⠿⠿' '#######'

CONVERT_OPTIONS="-b"
test_convert '##'      '⠿⠿'
test_convert '###'     '⠿⠿⠿'
test_convert '######'  '⠿⠿⠿⠿⠿⠿'
test_convert '#######' '⠿⠿⠿⠿⠿⠿⠿'


echo >> $OUTPUT
echo "lou_convert < ⠿⠿⠿⠿⠿⠿\\n⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿" >> $OUTPUT
RESULT=`printf "⠿⠿⠿⠿⠿⠿\\n⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿" | $LOU_CONVERT test/tables/tools.cvt 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
echo "$RESULT" >> $OUTPUT
CORRECT=`printf "######\\n##################"`
if [ "$RESULT" != "$CORRECT" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$CORRECT" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

echo >> $OUTPUT
echo "lou_convert -b < ######\\n##################" >> $OUTPUT
RESULT=`printf "######\\n##################" | $LOU_CONVERT -b test/tables/tools.cvt 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
echo "$RESULT" >> $OUTPUT
CORRECT=`printf "⠿⠿⠿⠿⠿⠿\\n⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿"`
if [ "$RESULT" != "$CORRECT" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$CORRECT" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi


CONVERT_TABLE="test/tables/tools.cvt"

CONVERT_OPTIONS=
test_convert '⠒⠭⠒⠀⠒⠭⠿⠭⠒' '-=- -=#=-'

CONVERT_OPTIONS="-b"
test_convert '-=- -=#=-' '⠒⠭⠒⠀⠒⠭⠿⠭⠒'

CONVERT_TABLE="tools.cvt"

CONVERT_OPTIONS="-p test/tables"
test_convert '⠒⠭⠒⠀⠒⠭⠿⠭⠒' '-=- -=#=-'

CONVERT_OPTIONS="-b -p test/tables"
test_convert '-=- -=#=-' '⠒⠭⠒⠀⠒⠭⠿⠭⠒'


DOTS_6="⠀⠁⠂⠃⠄⠅⠆⠇⠈⠉⠊⠋⠌⠍⠎⠏⠐⠑⠒⠓⠔⠕⠖⠗⠘⠙⠚⠛⠜⠝⠞⠟⠠⠡⠢⠣⠤⠥⠦⠧⠨⠩⠪⠫⠬⠭⠮⠯⠰⠱⠲⠳⠴⠵⠶⠷⠸⠹⠺⠻⠼⠽⠾⠿"
DIGITS_6="0-1-2-12-3-13-23-123-4-14-24-124-34-134-234-1234-5-15-25-125-35-135-235-1235-45-145-245-1245-345-1345-2345-12345-6-16-26-126-36-136-236-1236-46-146-246-1246-346-1346-2346-12346-56-156-256-1256-356-1356-2356-12356-456-1456-2456-12456-3456-13456-23456-123456"
DOTS_6_7="⡀⡁⡂⡃⡄⡅⡆⡇⡈⡉⡊⡋⡌⡍⡎⡏⡐⡑⡒⡓⡔⡕⡖⡗⡘⡙⡚⡛⡜⡝⡞⡟⡠⡡⡢⡣⡤⡥⡦⡧⡨⡩⡪⡫⡬⡭⡮⡯⡰⡱⡲⡳⡴⡵⡶⡷⡸⡹⡺⡻⡼⡽⡾⡿"
DIGITS_6_7="7-17-27-127-37-137-237-1237-47-147-247-1247-347-1347-2347-12347-57-157-257-1257-357-1357-2357-12357-457-1457-2457-12457-3457-13457-23457-123457-67-167-267-1267-367-1367-2367-12367-467-1467-2467-12467-3467-13467-23467-123467-567-1567-2567-12567-3567-13567-23567-123567-4567-14567-24567-124567-34567-134567-234567-1234567"
DOTS_6_8="⢀⢁⢂⢃⢄⢅⢆⢇⢈⢉⢊⢋⢌⢍⢎⢏⢐⢑⢒⢓⢔⢕⢖⢗⢘⢙⢚⢛⢜⢝⢞⢟⢠⢡⢢⢣⢤⢥⢦⢧⢨⢩⢪⢫⢬⢭⢮⢯⢰⢱⢲⢳⢴⢵⢶⢷⢸⢹⢺⢻⢼⢽⢾⢿"
DIGITS_6_8="8-18-28-128-38-138-238-1238-48-148-248-1248-348-1348-2348-12348-58-158-258-1258-358-1358-2358-12358-458-1458-2458-12458-3458-13458-23458-123458-68-168-268-1268-368-1368-2368-12368-468-1468-2468-12468-3468-13468-23468-123468-568-1568-2568-12568-3568-13568-23568-123568-4568-14568-24568-124568-34568-134568-234568-1234568"
DOTS_6_7_8="⣀⣁⣂⣃⣄⣅⣆⣇⣈⣉⣊⣋⣌⣍⣎⣏⣐⣑⣒⣓⣔⣕⣖⣗⣘⣙⣚⣛⣜⣝⣞⣟⣠⣡⣢⣣⣤⣥⣦⣧⣨⣩⣪⣫⣬⣭⣮⣯⣰⣱⣲⣳⣴⣵⣶⣷⣸⣹⣺⣻⣼⣽⣾⣿"
DIGITS_6_7_8="78-178-278-1278-378-1378-2378-12378-478-1478-2478-12478-3478-13478-23478-123478-578-1578-2578-12578-3578-13578-23578-123578-4578-14578-24578-124578-34578-134578-234578-1234578-678-1678-2678-12678-3678-13678-23678-123678-4678-14678-24678-124678-34678-134678-234678-1234678-5678-15678-25678-125678-35678-135678-235678-1235678-45678-145678-245678-1245678-345678-1345678-2345678-12345678"

function test_dots
{
	DOTS=$1
	DIGITS=$2

	echo >> $OUTPUT
	echo "lou_convert -d $DOTS" >> $OUTPUT
	RESULT=`$LOU_CONVERT -d $DOTS 2>&1`
	if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$DIGITS" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$DIGITS" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi
}

function test_digits
{
	DIGITS=$1
	DOTS=$2

	echo >> $OUTPUT
	echo "lou_convert -u $DIGITS" >> $OUTPUT
	RESULT=`$LOU_CONVERT -u $DIGITS 2>&1`
	if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$DOTS" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$DOTS" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi
}

function test_dots_digits
{
	DOTS=$1
	DIGITS=$2

	test_dots   "$DOTS"   "$DIGITS"
	test_digits "$DIGITS" "$DOTS"
}

test_dots_digits "$DOTS_6" "$DIGITS_6"
test_dots_digits "$DOTS_6_7" "$DIGITS_6_7"
test_dots_digits "$DOTS_6_8" "$DIGITS_6_8"
test_dots_digits "$DOTS_6_7_8" "$DIGITS_6_7_8"

test_dots '⠿⣿' '123456-12345678'
test_dots '⠿?⣿' '123456-'

test_digits '1-2-3'  '⠁⠂⠄'
test_digits '1-2-3?' '⠁⠂⠄'
test_digits '1-2-?3' '⠁⠂'
test_digits '1-2?-3' '⠁⠂'
test_digits '1-?2-3' '⠁'
test_digits '1?-2-3' '⠁'
test_digits '?1-2-3' ''


test_digits '12345678'  '⣿'
test_digits '123456780' '⠀'
test_digits '123456708' '⢀'
test_digits '123456078' '⣀'
test_digits '123450678' '⣠'
test_digits '123405678' '⣰'
test_digits '123045678' '⣸'
test_digits '120345678' '⣼'
test_digits '102345678' '⣾'
test_digits '012345678' '⣿'


echo >> $OUTPUT
echo "lou_convert -d <<EOI" >> $OUTPUT
echo "$DOTS_6" >> $OUTPUT
echo "$DOTS_6_7" >> $OUTPUT
echo "$DOTS_6_8" >> $OUTPUT
echo "$DOTS_6_7_8" >> $OUTPUT
echo "EOI" >> $OUTPUT
RESULT=`printf "$DOTS_6\\n$DOTS_6_7\\n$DOTS_6_8\\n$DOTS_6_7_8" | $LOU_CONVERT -d 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
echo "$RESULT" >> $OUTPUT
CORRECT=`printf "$DIGITS_6\\n$DIGITS_6_7\\n$DIGITS_6_8\\n$DIGITS_6_7_8"`
if [ "$RESULT" != "$CORRECT" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$CORRECT" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

echo >> $OUTPUT
echo "lou_convert -u <<EOI" >> $OUTPUT
echo "$DIGITS_6" >> $OUTPUT
echo "$DIGITS_6_7" >> $OUTPUT
echo "$DIGITS_6_8" >> $OUTPUT
echo "$DIGITS_6_7_8" >> $OUTPUT
echo "EOI" >> $OUTPUT
RESULT=`printf "$DIGITS_6\\n$DIGITS_6_7\\n$DIGITS_6_8\\n$DIGITS_6_7_8" | $LOU_CONVERT -u 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
echo "$RESULT" >> $OUTPUT
CORRECT=`printf "$DOTS_6\\n$DOTS_6_7\\n$DOTS_6_8\\n$DOTS_6_7_8"`
if [ "$RESULT" != "$CORRECT" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$CORRECT" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi


if (( FAIL_PRV == FAIL_CNT )); then echo PASS; else echo FAIL; fi

################################################################################

echo >> $OUTPUT
echo -n "lou_translate:  "

LOU_TRANSLATE='./build/tools/lou_translate'
#LOU_TRANSLATE='valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/tools/lou_translate'

FAIL_PRV=$FAIL_CNT

echo >> $OUTPUT
echo '################################################################################' >> $OUTPUT
echo $LOU_TRANSLATE >> $OUTPUT
$LOU_TRANSLATE >> $OUTPUT 2>&1


TRANSLATE_TABLE=
TRANSLATE_OPTIONS=

function test_translate_forward
{
	SOURCE=$1
	TARGET=$2

	echo >> $OUTPUT
	if [ -n "$TRANSLATE_OPTIONS" ]
	then
		echo "lou_translate $TRANSLATE_OPTIONS $TRANSLATE_TABLE < $SOURCE" >> $OUTPUT
	else
		echo "lou_translate $TRANSLATE_TABLE < $SOURCE" >> $OUTPUT
	fi

	RESULT=`echo -n "$SOURCE" | $LOU_TRANSLATE $TRANSLATE_OPTIONS "$TRANSLATE_TABLE" 2>&1`
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$TARGET" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$TARGET" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

	RESULT=`echo "$SOURCE" | $LOU_TRANSLATE $TRANSLATE_OPTIONS "$TRANSLATE_TABLE" 2>&1`
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$TARGET" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$TARGET" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

}

function test_translate_backward
{
	SOURCE=$1
	TARGET=$2

	echo >> $OUTPUT
	if [ -n "$TRANSLATE_OPTIONS" ]
	then
		echo "lou_translate -b $TRANSLATE_OPTIONS $TRANSLATE_TABLE < $SOURCE" >> $OUTPUT
	else
		echo "lou_translate -b $TRANSLATE_TABLE < $SOURCE" >> $OUTPUT
	fi

	RESULT=`echo -n "$SOURCE" | $LOU_TRANSLATE -b $TRANSLATE_OPTIONS "$TRANSLATE_TABLE" 2>&1`
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$TARGET" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$TARGET" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

	RESULT=`echo "$SOURCE" | $LOU_TRANSLATE -b $TRANSLATE_OPTIONS "$TRANSLATE_TABLE" 2>&1`
	echo -n "$RESULT  " >> $OUTPUT
	if [ "$RESULT" != "$TARGET" ] ; then FAIL_CNT=$((FAIL_CNT + 1)) ; echo FAIL >> $OUTPUT ; echo "$TARGET" >> $OUTPUT ; else echo PASS >> $OUTPUT ; fi

}

function test_translate
{
	SOURCE=$1
	TARGET=$2

	test_translate_forward  "$SOURCE" "$TARGET"
	test_translate_backward "$TARGET" "$SOURCE"
}

TRANSLATE_TABLE='test/tables/tools.rst'
TRANSLATE_OPTIONS=
test_translate ''        ''
test_translate '='       '⠭'
test_translate '??='     '??⠭'
test_translate '=='      '⠭⠭'
test_translate '???='    '???⠭'
test_translate '????='   '????⠭'
test_translate '==='     '⠭⠭⠭'
test_translate '======'  '⠭⠭⠭⠭⠭⠭'
test_translate '=======' '⠭⠭⠭⠭⠭⠭⠭'


test_translate '-=- -=-=-' '⠒⠭⠒⠀⠒⠿⠒'

TRANSLATE_TABLE='tools.rst'
TRANSLATE_OPTIONS='-p test/tables'
test_translate '-=- -=-=-' '⠒⠭⠒⠀⠒⠿⠒'

echo >> $OUTPUT
echo "lou_translate -m test/tables/tools.rst < -=- -=-=-" >> $OUTPUT
RESULT=`echo '-=- -=-=-' | $LOU_TRANSLATE -m test/tables/tools.rst 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
CORRECT="$(cat <<'EOI'
0        
012345678
-=- -=-=-
0        
012345556

0      
0123456
⠒⠭⠒⠀⠒⠿⠒
0      
0123458
EOI
)"
if [ "$RESULT" != "$CORRECT" ]
then
	FAIL_CNT=$((FAIL_CNT + 1))
	echo FAIL >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$RESULT" >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$CORRECT" >> $OUTPUT
	echo ===== >> $OUTPUT
else
	echo "$RESULT" >> $OUTPUT
	echo PASS >> $OUTPUT
fi

echo >> $OUTPUT
echo "lou_translate -b -m test/tables/tools.rst < ⠒⠭⠒⠀⠒⠿⠒" >> $OUTPUT
RESULT=`echo '⠒⠭⠒⠀⠒⠿⠒' | $LOU_TRANSLATE -b -m test/tables/tools.rst 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
CORRECT="$(cat <<'EOI'
0      
0123456
⠒⠭⠒⠀⠒⠿⠒
0      
0123458

0        
012345678
-=- -=-=-
0        
012345556
EOI
)"
if [ "$RESULT" != "$CORRECT" ]
then
	FAIL_CNT=$((FAIL_CNT + 1))
	echo FAIL >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$RESULT" >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$CORRECT" >> $OUTPUT
	echo ===== >> $OUTPUT
else
	echo "$RESULT" >> $OUTPUT
	echo PASS >> $OUTPUT
fi


echo >> $OUTPUT
echo "lou_translate -M test/tables/tools.rst < -=- -=-=-" >> $OUTPUT
RESULT=`echo '-=- -=-=-' | $LOU_TRANSLATE -M test/tables/tools.rst 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
CORRECT="$(cat <<'EOI'
[0]	-	0
[1]	=	1
[2]	-	2
[3]	 	3
[4]	-	4
[5]	=	5
[6]	-	5
[7]	=	5
[8]	-	6

[0]	⠒	0
[1]	⠭	1
[2]	⠒	2
[3]	⠀	3
[4]	⠒	4
[5]	⠿	5
[6]	⠒	8
EOI
)"
if [ "$RESULT" != "$CORRECT" ]
then
	FAIL_CNT=$((FAIL_CNT + 1))
	echo FAIL >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$RESULT" >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$CORRECT" >> $OUTPUT
	echo ===== >> $OUTPUT
else
	echo "$RESULT" >> $OUTPUT
	echo PASS >> $OUTPUT
fi

echo >> $OUTPUT
echo "lou_translate -b -M test/tables/tools.rst < ⠒⠭⠒⠀⠒⠿⠒" >> $OUTPUT
RESULT=`echo '⠒⠭⠒⠀⠒⠿⠒' | $LOU_TRANSLATE -b -M test/tables/tools.rst 2>&1`
if (( $? != 0 )) ; then echo EXE FAILURE >> $OUTPUT ; exit 1 ; fi
CORRECT="$(cat <<'EOI'
[0]	⠒	0
[1]	⠭	1
[2]	⠒	2
[3]	⠀	3
[4]	⠒	4
[5]	⠿	5
[6]	⠒	8

[0]	-	0
[1]	=	1
[2]	-	2
[3]	 	3
[4]	-	4
[5]	=	5
[6]	-	5
[7]	=	5
[8]	-	6
EOI
)"
if [ "$RESULT" != "$CORRECT" ]
then
	FAIL_CNT=$((FAIL_CNT + 1))
	echo FAIL >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$RESULT" >> $OUTPUT
	echo ===== >> $OUTPUT
	echo "$CORRECT" >> $OUTPUT
	echo ===== >> $OUTPUT
else
	echo "$RESULT" >> $OUTPUT
	echo PASS >> $OUTPUT
fi


if (( FAIL_PRV == FAIL_CNT )); then echo PASS; else echo FAIL; fi

################################################################################

exit $FAIL_CNT

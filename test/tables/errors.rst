
UNKNOWN_OPCODE

include
include UNKNOWN_FILE

set
set variable INVALID_VALUE

mode
mode name
mode name INVALID_DOTS - 1
mode name - - - - ⠭⠭⠭⠭⠭⠭⠭ 1
mode name - - - - - INVALID_VALUE

chars \xff 1
chars x INVALID_VALUE

join
join 0
join 0 X
join 0 X x INVALID_VALUE
join 0 X x 1 INVALID_VALUE
join INVALID_VALUE X x 1 2
join 4 X x 1 2

attrs
attrs = INVALID_VALUE

pattern
pattern \xff
pattern name [x

filter
filter name
filter name -
filter \xff - -
filter name [x -
filter name - [x

use INVALID_FILTER
use - INVALID_FILTER

uses -
uses - -
uses INVALID_FILTER - rule trans x ⠭
uses - INVALID_FILTER rule trans x ⠭

rule
rule premode
rule pretrans x
rule trans x =
rule UNKNOWN_TYPE x ⠭
rule premode \xff =
rule postmode x \;x;

match
match trans
match trans -
match trans - x
match trans - x -
match trans - x - -
match trans - x - - ⠭
match UNKNOWN_TYPE - x - - ⠭ -
match pretrans [x x - - ⠭ -
match pretrans - \xff - - ⠭ -
match pretrans - x [x - ⠭ -
match pretrans - x - [x ⠭ -
match pretrans - x - - \x;x; -
match pretrans - x - - ⠭ [x

macro

macro macro
@macro
eom
@macro

macro args
$1 $2
eom
@args 1 2 3 4 5 6 7 8 9 x
@args
@args 1

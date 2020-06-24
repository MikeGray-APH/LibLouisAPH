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

################################################################################


#                   01234567890123456789012345678901
#                   0123456789ABCDEFGHIJKLMNOPQRSTUV
config attrs_chars _~<>{}aULcv#n.=lupmJKWMNOPQRSTXV
#config control begin ⟪
#config control end   ⟫

set space                bit00
set seq_delimiter        bit01
set seq_before           bit02
set seq_after            bit03
set seq_before_no_caps   bit04
set seq_after_no_caps    bit05

set letter               bit06
set upper_case           bit07
set lower_case           bit08
set consonant            bit09
set vowel                bit10

set digit                bit11
set numeric_char         bit12
set numeric_cont         bit13
set numeric_term         bit14

set lower_dots           bit15
set upper_dots           bit16
set private              bit17

set modifier             bit18


#   Mark translation like a modifier because it contains cells that could be
#   mistaken as indicators.
macro mark_mod_trans
rule trans $1 $2
rule -backward init \M\;$2;\M \;$2;
eom


########################################
#   Modes
########################################

mode nocontract   56-56-56    56-3     56-56   56-3   56   0
mode capital      6-6-6       6-3      6-6     6-3    6    3
mode numeric      3456-3456   3456-3   3456    56     5    0

mode bold     45-2356         45-3         45-2         45-3         45-23         3
mode italic   46-2356         46-3         46-2         46-3         46-23         3
mode uline    456-2356        456-3        456-2        456-3        456-23        3
mode script   4-2356          4-3          4-2          4-3          4-23          3
mode trans1   4-3456-2356     4-3456-3     4-3456-2     4-3456-3     4-3456-23     3
mode trans2   45-3456-2356    45-3456-3    45-3456-2    45-3456-3    45-3456-23    3
mode trans3   456-3456-2356   456-3456-3   456-3456-2   456-3456-3   456-3456-23   3
mode trans4   5-3456-2356     5-3456-3     5-3456-2     5-3456-3     5-3456-23     3
mode trans5   46-3456-2356    46-3456-3    46-3456-2    46-3456-3    46-3456-23    3
mode tnote    4-46-126        4-46-345


########################################
#   Subpatterns
########################################

pattern APOST_+   (['’](\H⠠?⠠\H)?([dst]|ll|[rv]e))?
pattern APOST_-   (⠄(\S⠠⠠?\S)?([⠙⠎⠞]|⠇⠇|[⠗⠧]⠑))?

pattern APOSS_+   (s|['’](\H⠠\H)?s)?
pattern APOSS_-   (⠎|⠄(\S⠠\S)?⠎)?

#   ⠠?⠠?⠠⠄?⠀⠀⠀⠀⠀⠀   capital
#   [⠨⠘⠸⠈][⠆⠂⠶⠄]⠀   typeforms
#   [⠈⠘⠸⠐⠨]⠼[⠆⠂⠶]   transcriber defined typeforms
#   ⠈⠨⠜|⠈⠨⠣⠀⠀⠀⠀⠀⠀   transcriber note
#   [⠰⠠]?⠦⠀⠀⠀⠀⠀⠀⠀   “ ?
#   [⠐⠨⠸]⠣⠀⠀⠀⠀⠀⠀⠀   ([{
pattern SEQ_INDCS_<    ⠠?⠠?⠠⠄?|[⠨⠘⠸⠈][⠆⠂⠶⠄]|[⠈⠘⠸⠐⠨]⠼[⠆⠂⠶]|⠈⠨⠣|[⠰⠠]⠄|[\H\S]
pattern SEQ_CHARS_<-   [⠰⠠]?⠦|[⠐⠨⠸]⠣
pattern SEQ_<-         @[SEQ_INDCS_<]|@[SEQ_CHARS_<-]
pattern SEQ_<+         @[SEQ_INDCS_<]|%<

#   ⠠?⠠?⠠⠄?⠀⠀   capital
#   [⠨⠘⠸⠈]⠄⠀⠀   typeforms   [⠆⠂⠶⠄] fails
#   [⠈⠘⠸⠐⠨]⠼⠄   transcriber defined typeforms
#   ⠈⠨⠜|⠈⠨⠣⠀⠀   transcriber note
#   [⠐⠨⠸]⠜⠀⠀⠀   ([{
#   ⠄⠀⠀⠀⠀⠀⠀⠀⠀   ’
#   ⠠?⠴⠀⠀⠀⠀⠀⠀   ”
#   ⠲?⠲?⠲⠀⠀⠀⠀   .…
#   [⠂⠆⠒⠖⠦]⠀⠀   ,;:!?
pattern SEQ_INDCS_>    ⠈⠨⠜|[⠈⠘⠸⠐⠨]⠼⠄|[⠨⠘⠸⠈]⠄|⠠?⠠?⠠⠄?|[\H\S]
pattern SEQ_CHARS_>-   [⠐⠨⠸]⠜|⠄|⠠?⠴|⠲?⠲?⠲|[⠂⠆⠒⠖⠦]
pattern SEQ_>-         @[SEQ_INDCS_>]|@[SEQ_CHARS_>-]
pattern SEQ_>+         %>|@[SEQ_INDCS_>]

#   (^|![⠈⠨])⠤   hyphen, not macron or underscore
#   ⠐?⠠⠤⠀⠀⠀⠀⠀⠀   dash and longer
#   ⠐?⠠?⠤⠀⠀⠀⠀⠀   hyphen or dash
pattern DLT_<+   ^|%[_~]
pattern DLT_<-   ^|%_|(^|![⠈⠨])⠤|⠐?⠠⠤
pattern DLT_>+   %[_~]|^
pattern DLT_>-   ⠐?⠠?⠤|%_|^

pattern WORD_<+   @[DLT_<+]@[SEQ_<+]*
pattern WORD_>+   @[SEQ_>+]*@[DLT_>+]
pattern WORD_<-   @[DLT_<-]@[SEQ_<-]*
pattern WORD_>-   @[SEQ_>-]*@[DLT_>-]


########################################
#   Letters
########################################

chars ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz $letter

#   needed to match marked indicators and modifiers
chars \M $letter
chars \H\S $private

chars BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz $consonant   # no vowels (except w, 10.9.3)

set join_case 0


macro uplo
chars $1$2 $letter
join $join_case $1 $2 $upper_case $lower_case
rule trans $2 $3
eom

use
@uplo A a 1       # ⠁
@uplo B b 12      # ⠃
@uplo C c 14      # ⠉
@uplo D d 145     # ⠙
@uplo E e 15      # ⠑
@uplo F f 124     # ⠋
@uplo G g 1245    # ⠛
@uplo H h 125     # ⠓
@uplo I i 24      # ⠊
@uplo J j 245     # ⠚
@uplo K k 13      # ⠅
@uplo L l 123     # ⠇
@uplo M m 134     # ⠍
@uplo N n 1345    # ⠝
@uplo O o 135     # ⠕
@uplo P p 1234    # ⠏
@uplo Q q 12345   # ⠟
@uplo R r 1235    # ⠗
@uplo S s 234     # ⠎
@uplo T t 2345    # ⠞
@uplo U u 136     # ⠥
@uplo V v 1236    # ⠧
@uplo W w 2456    # ⠺
@uplo X x 1346    # ⠭
@uplo Y y 13456   # ⠽
@uplo Z z 1356    # ⠵

#   Subpattern to check if preceded by letter while backward translating.
#
#   The alphabetic wordsigns are not included because they stand alone.
#
#   The lower wordsigns ⠢enough, ⠦his, ⠴was, and ⠶were are not included because
#   they stand alone.  The lower wordsigns ⠆be and ⠔in are included because they
#   are also lower groupsigns.
#
#   ⠁a   ⠂ea
#   ⠃b   ⠆bb
#   ⠉c   ⠒cc
#   ⠙d   ⠯and ⠡child ⠫ed ⠸⠓had ⠐⠇lord ⠨⠙ound ⠘⠺word ⠸⠺world
#   ⠑e   ⠨⠑ance ⠆be ⠰⠑ence ⠐⠓here ⠐⠎some ⠮the ⠮there ⠘⠮these ⠘⠹those ⠐⠞time ⠐⠱where ⠘⠱whose   not ⠶were
#   ⠋f   ⠖ff ⠷of
#   ⠛g   ⠶gg ⠬ing ⠰⠛ong ⠐⠽young
#   ⠓h   ⠡ch ⠣gh ⠩sh ⠹th ⠐⠹through ⠱wh ⠱which ⠾with   not ⠢enough
#   ⠊i
#   ⠚j
#   ⠅k   ⠐⠺work
#   ⠇l   ⠰⠇ful
#   ⠍m
#   ⠝n   ⠒con ⠢en ⠔in ⠐⠟question ⠨⠝sion ⠰⠝tion ⠘⠥upon
#   ⠕o
#   ⠏p
#   ⠟q
#   ⠗r   ⠜ar ⠐⠡character ⠻er ⠐⠑ever ⠐⠋father ⠿for ⠐⠍mother ⠸⠮their ⠐⠥under
#   ⠎s   ⠲dis ⠨⠎less ⠰⠎ness   not ⠦his ⠴was
#   ⠞t   ⠸⠉cannot ⠰⠞ment ⠐⠳ought ⠳out ⠐⠏part ⠐⠗right ⠸⠎spirit ⠌st
#   ⠥u   ⠳ou
#   ⠧v
#   ⠺w   ⠐⠅know ⠪ow
#   ⠭x
#   ⠽y   ⠐⠙day ⠰⠽ity ⠸⠍many
#   ⠵z
#
#   These are letters only when the preceding character is a letter:
#   ⠂(,)ea ⠆(;)bb ⠒(:)cc ⠖(!)ff ⠶(=)gg
#
#   These are letters only when the preceding character is a delimiter:
#   ⠲(.)dis
#
#   These are letters only when the preceding character is a letter or
#   delimiter:
#   ⠆(e)be ⠒(n)con ⠣(h)gh ⠜(r)ar
#
#   More efficient letter before pattern than just oring all the individual
#   letter patterns together if they were present.
#
#   letters:        ABCDDDDEEFFGGHHHHHIJKLMNNNOPQRRRSTTUUVWWXYZ             ehnr.   ,;:!=hr
pattern LETTER_<- ([⠁⠃⠉⠙⠡⠯⠫⠑⠮⠋⠷⠛⠬⠓⠱⠾⠩⠹⠊⠚⠅⠇⠍⠝⠢⠔⠕⠏⠟⠗⠿⠻⠎⠞⠳⠌⠥⠧⠺⠪⠭⠽⠵]|@[WORD_<-][⠆⠣⠒⠜⠲])[⠂⠆⠒⠖⠶⠣⠜]*

#   Subpattern to check if followed by letter while backward translating.
#
#   The alphabetic wordsigns are not included because they stand alone.
#
#   The lower groupsigns ⠆be, ⠒con, and ⠲dis are not included because they must
#   be at the beginning of a word.
#
#   The lower wordsigns ⠢enough, ⠦his, ⠴was, and ⠶were are not included because
#   they stand alone.  The lower wordsign ⠔in are included because it is also a
#   lower groupsign.
#
#   ⠁a   ⠨⠑ance ⠯and ⠜ar
#   ⠃b   ⠆bb ⠃but   not ⠆be
#   ⠉c   ⠉can ⠉cannot ⠒cc ⠡ch ⠐⠡character ⠡child   not ⠒con
#   ⠙d   ⠐⠙day ⠙do   not ⠲dis
#   ⠑e   ⠂ea ⠫ed ⠢en ⠰⠑ence ⠻er ⠐⠑ever ⠑every   not ⠢enough
#   ⠋f   ⠐⠋father ⠖ff ⠿for ⠋from ⠰⠇ful
#   ⠛g   ⠶gg ⠣gh ⠛go
#   ⠓h   ⠸⠓had ⠓have ⠐⠓here   not ⠦his
#   ⠊i   ⠔in ⠬ing ⠰⠽ity
#   ⠚j   ⠚just
#   ⠅k   ⠐⠅know ⠅knowledge
#   ⠇l   ⠨⠎less ⠇like ⠐⠇lord
#   ⠍m   ⠸⠍many ⠰⠞ment ⠍more ⠐⠍mother
#   ⠝n   ⠐⠝name ⠰⠎ness ⠝not
#   ⠕o   ⠷of ⠐⠕one ⠰⠛ong ⠳ou ⠐⠳ought ⠨⠙ound ⠨⠞ount ⠳out ⠪ow
#   ⠏p   ⠐⠏part ⠏people
#   ⠟q   ⠐⠟question ⠟quite
#   ⠗r   ⠗rather ⠐⠗right
#   ⠎s   ⠩sh ⠩shall ⠨⠝sion ⠎so ⠐⠎some ⠸⠎spirit ⠌st ⠌still
#   ⠞t   ⠹th ⠞that ⠮the ⠸⠮their ⠐⠮there ⠘⠮these ⠹this ⠘⠹those ⠐⠹through ⠐⠞time ⠰⠝tion
#   ⠥u   ⠐⠥under ⠘⠥upon ⠥us
#   ⠧v   ⠧very
#   ⠺w   ⠱wh ⠐⠱where ⠱which ⠘⠱whose ⠺will ⠾with ⠘⠺word ⠐⠺work ⠸⠺world   not ⠴was ⠶were
#   ⠭x
#   ⠽y   ⠽you ⠐⠽young
#   ⠵z
#
#   These are letters only when the character after them is also a letter.
#   ⠆(;)bb ⠒(:)cc ⠂(,)ea ⠖(!)ff
#
#   Modifers are always followed by a letter
#   ⠈⠬(˘)breve ⠈⠤(¯)macron ⠈⠡(/)solidus ⠈⠒(-)stroke
#   ⠘⠌(´)acute ⠘⠬(ᵛ)caron ⠘⠯(¸)cedilla ⠘⠩(^)circumflex ⠘⠒(¨)diaeresis ⠘⠡(`)grave ⠘⠫(°)ring ⠘⠻(~)tilde
#   ⠘⠸⠂(1)first ⠘⠸⠆(2)second ⠘⠸⠤(3)third
#   ⠘⠖(+)ligature
#
#   More efficient letter after pattern than just oring all the individual
#   letter patterns together.
#
#   letters:       ;:,!    AAABCCDEEEEFFGGGHIIIJKLMNOOOOPQRSSSTTTUVWWWXYZ    CDEFHKLMNOOPQRSTTTUWWY    TTUWW¸`^°~¨´ᵛ+    EFIMNOT    ALOOS    HMSTW    /-˘¯     123
pattern LETTER_>- [⠆⠒⠂⠖]*([⠁⠯⠜⠃⠉⠡⠙⠑⠫⠻⠢⠋⠿⠛⠣⠶⠓⠊⠬⠔⠚⠅⠇⠍⠝⠕⠳⠷⠪⠏⠟⠗⠎⠌⠩⠞⠹⠮⠥⠧⠺⠱⠾⠭⠽⠵]|⠐[⠡⠙⠑⠋⠓⠅⠇⠍⠝⠕⠳⠏⠟⠗⠎⠮⠹⠞⠥⠱⠺⠽]|⠘[⠮⠹⠥⠱⠺⠯⠡⠩⠫⠻⠒⠌⠬⠖]|⠰[⠑⠇⠽⠞⠎⠛⠝]|⠨[⠑⠎⠙⠞⠝]|⠸[⠓⠍⠎⠮⠺]|⠈[⠡⠒⠬⠤]|⠘⠸[⠂⠆⠤])

pattern MODIFER_<   ⠘[⠯⠩⠫⠻⠌⠖]|[⠈⠘][⠡⠒⠬]|⠘⠸[⠂⠆⠤]|⠈⠤
pattern MODIFER_>   ⠘[⠯⠡⠩⠫⠻⠒⠌⠬⠖]|⠈[⠡⠒⠬⠤]|⠘⠸[⠂⠆⠤]
pattern LETTER_>+   %a|@[MODIFER_>]

pattern A_>-   [⠁⠯⠜]|⠨⠑
pattern B_>-   ⠃|⠆@[LETTER_>-]
pattern C_>-   [⠉⠡]|⠐⠡|⠒@[LETTER_>-]
pattern D_>-   ⠙|⠐⠙
pattern E_>-   [⠑⠫⠢⠻]|[⠐⠰]⠑|⠂@[LETTER_>-]
pattern F_>-   [⠋⠿]|⠐⠋|⠰⠇|⠖@[LETTER_>-]
pattern G_>-   [⠛⠶⠣]
pattern H_>-   ⠓|[⠸⠐]⠓
pattern I_>-   [⠊⠔⠬]|⠰⠽
pattern J_>-   ⠚
pattern K_>-   ⠅|⠐⠅
pattern L_>-   ⠇|⠨⠎|⠐⠇
pattern M_>-   ⠍|[⠸⠐]⠍|⠰⠞
pattern N_>-   ⠝|⠐⠝|⠰⠎
pattern O_>-   [⠕⠷⠳⠪]|⠐[⠕⠳]|⠨[⠙⠞]|⠰⠛
pattern P_>-   ⠏|⠐⠏
pattern Q_>-   ⠟|⠐⠟
pattern R_>-   ⠗|⠐⠗
pattern S_>-   [⠎⠩⠌]|[⠐⠸]⠎|⠨⠝
pattern T_>-   [⠞⠹⠮]|⠸⠮|⠐[⠮⠹⠞]|⠘[⠮⠹]|⠰⠝
pattern U_>-   ⠥|[⠐⠘]⠥
pattern V_>-   ⠧
pattern W_>-   [⠺⠱⠾]|[⠐⠘][⠱⠺]|⠸⠺
pattern X_>-   ⠭
pattern Y_>-   ⠽|⠐⠽
pattern Z_>-   ⠵


########################################
#   Digits
########################################

set join_digit 1

join $join_digit 1 a $digit $numeric_char
join $join_digit 2 b $digit $numeric_char
join $join_digit 3 c $digit $numeric_char
join $join_digit 4 d $digit $numeric_char
join $join_digit 5 e $digit $numeric_char
join $join_digit 6 f $digit $numeric_char
join $join_digit 7 g $digit $numeric_char
join $join_digit 8 h $digit $numeric_char
join $join_digit 9 i $digit $numeric_char
join $join_digit 0 j $digit $numeric_char


chars abcdefghij $numeric_term
chars ⠁⠃⠉⠙⠑⠋⠛⠓⠊⠚ $numeric_char
chars .,⠐⠲⠂ $numeric_cont
chars ⁄⠌ $numeric_cont

pattern DIGITS_+   [abcdefghij]
pattern DIGITS_-   [⠁⠃⠉⠙⠑⠋⠛⠓⠊⠚]

#                               DDDEFGHHHHKLMNNNOPQRRRSTTUUVWWXYZ             ehnr.      ABCDDDDEEFFGGHHHHHIJKLMNNNOPQRRRSTTUUVWWXYZ             ehnr.   ,;:!=hr
pattern LETTER_DIGITLESS_<-   ([⠡⠯⠫⠮⠷⠬⠱⠾⠩⠹⠅⠇⠍⠝⠢⠔⠕⠏⠟⠗⠿⠻⠎⠞⠳⠌⠥⠧⠺⠪⠭⠽⠵]|@[WORD_<-][⠆⠣⠒⠜⠲])|(([⠁⠃⠉⠙⠡⠯⠫⠑⠮⠋⠷⠛⠬⠓⠱⠾⠩⠹⠊⠚⠅⠇⠍⠝⠢⠔⠕⠏⠟⠗⠿⠻⠎⠞⠳⠌⠥⠧⠺⠪⠭⠽⠵]|@[WORD_<-][⠆⠣⠒⠜⠲])[⠂⠆⠒⠖⠶⠣⠜]+)

#   Make sure numeric space is a numeric space.  If it is not then mark it like
#   a modifer.
#
#   The following are non-numeric uses of ⠐:
#
#   ⠐⠣( ⠐⠜) ⠐⠖+ ⠐⠔* ⠐⠶=
#   ⠐⠡character ⠐⠅know ⠐⠇lord ⠐⠍mother ⠐⠝name ⠐⠕one ⠐⠳ought ⠐⠏part ⠐⠟question
#   ⠐⠗right ⠐⠎some ⠐⠮there ⠐⠹through ⠐⠞time ⠐⠥under ⠐⠱where ⠐⠺work ⠐⠽young
#
#   ⠐⠙day ⠐⠑ever ⠐⠋father ⠐⠓here
#
#                                     ()+*=cklmnoopqrstttuwwy
match -backward init - \M⠐\M -   - ⠐ [⠣⠜⠖⠔⠶⠡⠅⠇⠍⠝⠕⠳⠏⠟⠗⠎⠮⠹⠞⠥⠱⠺⠽]
#                                                                                                defh
match -backward init - \M⠐\M -   (^|!⠼)(@[DIGITS_-]|@[DIGITS_-][⠐⠲⠌])+|@[LETTER_DIGITLESS_<-] ⠐ [⠙⠑⠋⠓]


########################################
#   Unicode Modified Letters
########################################

pattern NOT_MOD_4_-      (^|!\;4;)
pattern NOT_MOD_45_-     (^|!\;45;)
pattern NOT_MOD_4_45_-   (^|![\;4;\;45;])

filter not_modifier_4_-      (^|!⠈)      -
filter not_modifier_45_-     (^|!⠘)      -
filter not_modifier_4_45_-   (^|![⠈⠘])   -

filter not_modifier_<+ ^|!([\;16;\;25;\;346;\;36;\;12346;\;1246;\;146;\;12456;\;34;\;235;]) -


#   Mark modifier because it contains cells that could be mistaken as
#   indicators.
macro mark_modifier
rule -backward init \M$1\M $1
eom

macro modifier
chars $2$3 $letter
join $join_case $2 $3 $upper_case $lower_case
rule pretrans $2 $1$4
rule pretrans $3 $1$5
eom

macro modifier_cyrillic
chars $2$3 $letter
join $join_case $2 $3 $upper_case $lower_case
rule -after pretrans $2 $1$4
rule -after pretrans $3 $1$5
eom

# acute accent   \x00b4   ´   combining \x0301   ́
@mark_modifier \;45-34;

@modifier \;45-34; \x00c1 \x00e1 A a   # Áá
@modifier \;45-34; \x00c9 \x00e9 E e   # Éé
@modifier \;45-34; \x00cd \x00ed I i   # Íí
@modifier \;45-34; \x00d3 \x00f3 O o   # Óó
@modifier \;45-34; \x00da \x00fa U u   # Úú
@modifier \;45-34; \x00dd \x00fd Y y   # Ýý
@modifier \;45-34; \x0106 \x0107 C c   # Ćć
@modifier \;45-34; \x0139 \x013a L l   # Ĺĺ
@modifier \;45-34; \x0143 \x0144 N n   # Ńń
@modifier \;45-34; \x0154 \x0155 R r   # Ŕŕ
@modifier \;45-34; \x015a \x015b S s   # Śś
@modifier \;45-34; \x0179 \x017a Z z   # Źź
@modifier \;45-34; \x01f4 \x01f5 G g   # Ǵǵ
@modifier \;45-34; \x1e30 \x1e31 K k   # Ḱḱ
@modifier \;45-34; \x1e3e \x1e3f M m   # Ḿḿ
@modifier \;45-34; \x1e54 \x1e55 P p   # Ṕṕ
@modifier \;45-34; \x1e54 \x1e55 W w   # Ẃẃ

@modifier_cyrillic \;45-34; \x040c \x045c K k   # Ќќ   cyrillic kje

# breve   \x02d8   ˘   combining \x0306   ̆
@mark_modifier \;4-346;

@modifier \;4-346; \x0102 \x0103 A a   # Ăă
@modifier \;4-346; \x0114 \x0115 E e   # Ĕĕ
@modifier \;4-346; \x011e \x011f G g   # Ğğ
@modifier \;4-346; \x012c \x012d I i   # Ĭĭ
@modifier \;4-346; \x014e \x014f O o   # Ŏŏ
@modifier \;4-346; \x016c \x016d U u   # Ŭŭ

# caron   \x02c7   ˇ   combining \x030c   ̌
@mark_modifier \;45-346;

@modifier \;45-346; \x010c \x010d C c   # Čč
@modifier \;45-346; \x010e \x010f D d   # Ďď
@modifier \;45-346; \x011a \x011b E e   # Ěě
@modifier \;45-346; \x013d \x013e L l   # Ľľ
@modifier \;45-346; \x0147 \x0148 N n   # Ňň
@modifier \;45-346; \x0158 \x0159 R r   # Řř
@modifier \;45-346; \x0160 \x0161 S s   # Šš
@modifier \;45-346; \x0164 \x0165 T t   # Ťť
@modifier \;45-346; \x017d \x017e Z z   # Žž
@modifier \;45-346; \x01cd \x01ce A a   # Ǎǎ
@modifier \;45-346; \x01cf \x01d0 L l   # Ǐǐ
@modifier \;45-346; \x01d1 \x01d2 O o   # Ǒǒ
@modifier \;45-346; \x01d3 \x01d4 U u   # Ǔǔ
@modifier \;45-346; \x01e6 \x01e7 G g   # Ǧǧ
@modifier \;45-346; \x01e8 \x01e9 K k   # Ǩǩ
@modifier \;45-346; \x021e \x021f H h   # Ȟȟ

@modifier_cyrillic \;45-346;    \x040e \x04e5 Y y   # Ўў   cyrillic short u
@modifier_cyrillic \;45-346;    \x04d6 \x04d7 E e   # Ӗӗ   cyrillic ie

# cedilla   \x00b8   ¸   combining \x0327   ̧
@mark_modifier \;45-12346;

@modifier \;45-12346; \x00c7 \x00e7 C c   # Çç
@modifier \;45-12346; \x0122 \x0123 G g   # Ģģ
@modifier \;45-12346; \x0136 \x0137 K k   # Ķķ
@modifier \;45-12346; \x013b \x013c L l   # Ļļ
@modifier \;45-12346; \x0145 \x0146 N n   # Ņņ
@modifier \;45-12346; \x0156 \x0157 R r   # Ŗŗ
@modifier \;45-12346; \x015e \x015f S s   # Şş
@modifier \;45-12346; \x0162 \x0163 T t   # Ţţ
@modifier \;45-12346; \x0228 \x0229 E e   # Ȩȩ

@modifier_cyrillic \;45-12346; \x04aa \x04ab C c   # Ҫҫ   cyrillic es

# circumflex   \x02c6   ˆ   combining \x0302   ̂
@mark_modifier \;45-146;

@modifier \;45-146; \x00c2 \x00e2 A a   # Ââ
@modifier \;45-146; \x00ca \x00ea E e   # Êê
@modifier \;45-146; \x00ce \x00ee I i   # Îî
@modifier \;45-146; \x00d4 \x00f4 O o   # Ôô
@modifier \;45-146; \x00db \x00fb U u   # Ûû
@modifier \;45-146; \x0108 \x0109 C c   # Ĉĉ
@modifier \;45-146; \x011c \x011d G g   # Ĝĝ
@modifier \;45-146; \x0124 \x0125 H h   # Ĥĥ
@modifier \;45-146; \x0134 \x0135 J j   # Ĵĵ
@modifier \;45-146; \x015c \x015d S s   # Ŝŝ
@modifier \;45-146; \x0174 \x0175 W w   # Ŵŵ
@modifier \;45-146; \x0176 \x0177 Y y   # Ŷŷ

# diaeresis   \x00a8   ¨   combining \x0308   ̆
@mark_modifier \;45-25;

@modifier \;45-25; \x00c4 \x00e4 A a   # Ää
@modifier \;45-25; \x00cb \x00eb E e   # Ëë
@modifier \;45-25; \x00cf \x00ef I i   # Ïï
@modifier \;45-25; \x00d6 \x00f6 O o   # Öö
@modifier \;45-25; \x00dc \x00fc U u   # Üü
@modifier \;45-25; \x0178 \x00ff Y y   # Ÿÿ
@modifier \;45-25; \x1e26 \x1e27 H h   # Ḧḧ
@modifier \;45-25; \x1e84 \x1e85 W w   # Ẅẅ
@modifier \;45-25; \x1e8c \x1e8d X x   # Ẍẍ

@modifier_cyrillic \;45-25; \x04d2 \x04d3 A a   # Ӓӓ   cyrillic a
@modifier_cyrillic \;45-25; \x0401 \x0451 E e   # Ёё   cyrillic io
@modifier_cyrillic \;45-25; \x0407 \x0457 I i   # Її   cyrillic yi
@modifier_cyrillic \;45-25; \x04f0 \x04f1 Y y   # Ӱӱ   cyrillic u

# grave accent   \x0060   `   \x02cb   ˋ   combining \x0300   ̀
@mark_modifier \;45-16;

@modifier \;45-16; \x00c0 \x00e0 A a   # Àà
@modifier \;45-16; \x00c8 \x00e8 E e   # Èè
@modifier \;45-16; \x00cc \x00ec I i   # Ìì
@modifier \;45-16; \x00d2 \x00f2 O o   # Òò
@modifier \;45-16; \x00d9 \x00f9 U u   # Ùù
@modifier \;45-16; \x01f8 \x01f9 N n   # Ǹǹ

@modifier_cyrillic \;45-16; \x0400 \x0450 E e   # Ѐѐ   cyrillic ie

# macron   \x00af   ¯   combining \x0304   ̄
@mark_modifier \;4-36;

@modifier \;4-36; \x0100 \x0101 A a   # Āā
@modifier \;4-36; \x0112 \x0113 E e   # Ēē
@modifier \;4-36; \x012a \x012b I i   # Īī
@modifier \;4-36; \x014c \x014d O o   # Ōō
@modifier \;4-36; \x016a \x016b U u   # Ūū
@modifier \;4-36; \x0232 \x0233 Y y   # Ȳȳ
@modifier \;4-36; \x1e20 \x1e21 G g   # Ḡḡ

@modifier_cyrillic \;4-36; \x04ee \x04ef Y y   # Ӯӯ   cyrillic u

# ring   \x02da   ˚   combining \x030a   ̊
@mark_modifier \;45-1246;

@modifier \;45-1246; \x00c5 \x00e5 A a   # Åå
@modifier \;45-1246; \x016e \x016f U u   # Ůů

# solidus   combining \x0337   ̷   combining \x0338   ̸
@mark_modifier \;4-16;

@modifier \;4-16; \x00d8 \x00f8 O o   # Øø
@modifier \;4-16; \x0141 \x0142 L l   # Łł
@modifier \;4-16; \x023a \x2c65 A a   # Ⱥⱥ
@modifier \;4-16; \x023b \x023c C c   # Ȼȼ
@modifier \;4-16; \x023e \x2c66 T t   # Ⱦⱦ
@modifier \;4-16; \x0246 \x0247 E e   # Ɇɇ
@modifier \;4-16; \xa742 \xa743 K k   # Ꝃꝃ
@modifier \;4-16; \xa758 \xa759 Q q   # Ꝙꝙ
@modifier \;4-16; \xa75e \xa75f V v   # Ꝟꝟ

# stroke   combining \x0335   ̵   combining \x0336   ̶
@mark_modifier \;4-25;

@modifier \;4-25; \x0110 \x0111 D d   # Đđ
@modifier \;4-25; \x0126 \x0127 H h   # Ħħ
@modifier \;4-25; \x0166 \x0167 T t   # Ŧŧ
@modifier \;4-25; \x0197 \x0268 I i   # Ɨɨ
@modifier \;4-25; \x01b5 \x01b6 Z z   # Ƶƶ
@modifier \;4-25; \x01e4 \x01e5 G g   # Ǥǥ
@modifier \;4-25; \x0243 \x0180 B b   # Ƀƀ
@modifier \;4-25; \x0248 \x0249 J j   # Ɉɉ
@modifier \;4-25; \x024c \x024d R e   # Ɍɍ
@modifier \;4-25; \x024e \x024f Y y   # Ɏɏ
@modifier \;4-25; \x2c63 \x1d7d P p   # Ᵽᵽ
@modifier \;4-25; \xa740 \xa741 K k   # Ꝁꝁ
@modifier \;4-25; \xa750 \xa751 P p   # Ꝑꝑ
@modifier \;4-25; \xa756 \xa757 Q q   # Ꝗꝗ
@modifier \;4-25; \xa798 \xa798 F f   # Ꞙꞙ

@modifier_cyrillic \;4-25; \x04b0 \x04b1 Y y   # Ұұ   cyrillic straight u

# \xa7f8   ꟸ   H stroke

# tilde   \x02dc   ˜   combining \x0303   ̃
@mark_modifier \;45-12456;

@modifier \;45-12456;   \x00c3 \x00e3 A a   # Ãã
@modifier \;45-12456;   \x00d1 \x00f1 N n   # Ññ
@modifier \;45-12456;   \x00d5 \x00f5 O o   # Õõ
@modifier \;45-12456;   \x0168 \x0169 U u   # Ũũ
@modifier \;45-12456;   \x1e7c \x1e7d V v   # Ṽṽ
@modifier \;45-12456;   \x1ebc \x1ebd E e   # Ẽẽ
@modifier \;45-12456;   \x1ef8 \x1ef9 Y y   # Ỹỹ


#   \x1e97   45-25-2345      ẗ
#   \x1e98   45-1246-2456    ẘ   http://archives.miloush.net/michkap/archive/2012/04/17/10294366.html
#   \x1e99   45-1246-13456   ẙ


########################################
#   Unicode Ligatured Letters
########################################

filter ligature_capital_symbol (^|!⠠)⠠ -

@mark_modifier \;45-235;
@mark_modifier \;6-45-235;

chars Ææ $letter
join $join_case \x00c6 \x00e6 $upper_case $lower_case
uses ligature_capital_symbol - rule pretrans æ a\;6-45-235;e
rule pretrans æ a\;45-235;e

chars Ӕӕ $letter   # cyrillic
join $join_case \x04d4 \x04d5 $upper_case $lower_case
uses ligature_capital_symbol - rule pretrans ӕ a\;6-45-235;e
rule -after pretrans ӕ a\;45-235;e

chars Œœ $letter
join $join_case \x0152 \x0153 $upper_case $lower_case
uses ligature_capital_symbol - rule pretrans œ o\;6-45-235;e
rule pretrans œ o\;45-235;e

chars Ĳĳ $letter
join $join_case \x0132 \x0133 $upper_case $lower_case
uses ligature_capital_symbol - rule pretrans ĳ i\;6-45-235;j
rule pretrans ĳ i\;45-235;j


#   \x01e2 1-36-126-1-6-45-235-15-345 Ǣ
#   \x01e3 1-36-126-1-45-235-15-345 ǣ
#   \x01e2 45-34-126-1-6-45-235-15-345 Ǽ
#   \x01e3 45-34-126-1-45-235-15-345 ǽ
#   \xfb00 124-45-235-124 ﬀ
#   \xfb01 124-45-235-24 ﬁ
#   \xfb04 124-45-235-2345 ﬅ
#   \xfb05 234-45-235-2345 ﬆ


########################################
#   Delimiters
########################################

chars \s\t\n\r\x00a0\x2000\x2001\x2002\x2003\x2004\x2005\x2006\x2007\x2008\x2009\x200a\x200b $space
chars \x2800 $space

#   spaces
rule trans \t       0
#ule trans \n       0
#ule trans \r       0
rule trans \x00a0   0
rule trans \x2000   0
rule trans \x2001   0
rule trans \x2002   0
rule trans \x2003   0
rule trans \x2004   0
rule trans \x2005   0
rule trans \x2006   0
rule trans \x2007   0
rule trans \x2008   0
rule trans \x2009   0
rule trans \x200a   0
rule trans \x200b   0
#ule trans \x2800   0
rule trans \s       0   # default back translation

chars -\x2010\x2011\x2012\x2013\x2014\x2015 $seq_delimiter

#   all hyphens and dashes contain at least \;36;, so no need for special
#   function to determine backward delimiters
chars ⠤ $seq_delimiter

chars ([{"“'‘ $seq_before_no_caps
chars )]}"”'’.,;:.!?… $seq_after_no_caps

chars ([{"“'‘ $seq_before
chars )]}"”'’.,;:.!?… $seq_after

#   leave the \;36; outside to signify it is a sequence delimiter
rule -backward init \M\;5-6;\M\;36; \;5-6-36;
rule -backward init \M\;6;\M\;36; \;6-36;

rule trans \x2012 6-36   ‒
rule trans \x2013 6-36   –   # default back translation
rule trans \x2015 5-6-36   ―
rule trans \x2014 5-6-36   —   # default back translation

## -   ⠈⠤macron
use - not_modifier_4_-
rule trans \x00ad 36   # soft hyphen
rule trans \x2010 36
rule trans \x2011 36   # non-breaking hyphen
rule trans \x002d 36   # default back translation
use


########################################
#   Quotation
########################################

## "
match trans @[WORD_<+] " -            @[WORD_<-] 236 -
match trans -          " @[WORD_>+]   -          356 @[WORD_>-]

## “
match trans @[WORD_<+] “ -   @[WORD_<-] 236 -

## ”
match trans - ” @[WORD_>+]   - 356 @[WORD_>-]

## ?   7.5   word<his>word
match premode @[WORD_<+] ? @[WORD_>+]     @[WORD_<+]   \;56;? -              # 7.5.3
match premode @[WORD_<+] ? -              @[WORD_<+]   \;56;? -              # 7.5.4
match premode %a         ? @[LETTER_>+]   @[LETTER_<-] \;56;? @[LETTER_>-]

rule trans ? 236

## '
rule trans ' 3

## ‘   word<his>word
match trans - \x2018 -   - 6-236 @[SEQ_<-]*@[LETTER_>-]
match -backward init - \M\;6-236;\M -   - \;6-236; @[SEQ_<-]*@[LETTER_>-]

## ’
rule trans \x2019 6-356
match -backward init - \M\;6-356;\M -   @[LETTER_<-]@[SEQ_>-]* \;6-356; -

#   Unicode prefers \x2019 for apostrophe instead of \x0027
match trans %a \x2019 ([dst]|ll|[rv]e)@[WORD_>+]   @[LETTER_<-] 3 ([⠙⠎⠞]|⠇⠇|[⠗⠧]⠑)@[WORD_>-]


########################################
#   ;:,!.
########################################

## ;   letter< bb >letter   word< be >word|letter
rule trans ; 23
match premode @[WORD_<+]|%a ; [,:;!]*@[LETTER_>+]|;@[WORD_>+]   - \;56;; -
match premode @[WORD_<+]    ; @[WORD_>+]                        - \;56;; -

## :   letter< cc >letter   word< con >letter   ⠈⠒stroke   ⠘⠒diaeresis
uses - not_modifier_4_45_- rule trans : 25
match premode @[WORD_<+]|%a : [,:;!]*@[LETTER_>+]   - \;56;: -

## ,   letter< ea >letter
rule trans , 2
match premode %a , [,:;!]*@[LETTER_>+]|[,:;!]+@[LETTER_>+]?   - \;56;, -

## !   letter< ff >letter   ⠘⠖ligature
uses - not_modifier_45_- rule trans ! 235
match premode %a ! [,:;!]*@[LETTER_>+]|[,:;!]+@[LETTER_>+]?   - \;56;! -

## .   word< dis >letter
rule trans . 256
match premode @[WORD_<+] . [,:;!]*@[LETTER_>+]|[,:;!]+@[LETTER_>+]?   - \;56;. -


########################################
#   ASCII
########################################

rule trans      # 456-1456
rule trans      $ 4-234
rule trans      % 46-356
rule trans      & 4-12346
@mark_mod_trans ( 5-126
@mark_mod_trans ) 5-345
rule trans      * 5-35
rule trans      + 5-235
rule trans      / 456-34     # does not match simple fractions
rule trans      < 4-126
rule trans      = 5-2356
rule trans      > 4-345
rule trans      @ 4-1
rule trans      [ 46-126
rule trans      \\ 456-16
rule trans      ] 46-345
rule trans      ^ 4-26
rule trans      _ 46-36
rule trans      } 456-345
rule trans      | 456-1256
rule trans      { 456-126
rule trans      ~ 4-35       # tilde (swung dash)


########################################
#   Unicode Punctuation and Signs
########################################

rule trans \x00a1 45-56-235   # ¡ inverted exclamation
rule trans \x00a2 4-14        # ¢ cent
rule trans \x00a3 4-123       # £ pound

rule -forward trans \x00a4 1246   # ¤ curency   conflicts with ring modifier

rule trans \x00a5 4-13456     # ¥ yen
rule trans \x00a6 46-1256     # ¦ broken bar
rule trans \x00a7 45-234      # § section
rule trans \x00a9 45-14       # © copyright
#ule trans \x00aa 0           # ª feminine ordinal
rule trans \x00ab 456-236     # « opening double angle quotation
rule trans \x00ac 4-1456      # ¬ not
rule trans \x00ae 45-1235     # ® registered
#ule trans \x00ba 0           # º masculine ordinal
rule trans \x00b6 45-1234     # ¶ pilcrow
rule trans \x00bb 456-356     # » closing double angle quotation
rule trans \x00bf 45-56-236   # ¿ inverted question

@uplo \x014a \x014b 45-1345   # Ŋŋ eng
@uplo \x018e \x01dd 456-26    # Ǝǝ not schwa
@uplo \x018f \x0259 456-26    # Əə schwa
@uplo \x04d8 \x04d9 456-26    # Әә cyrillic schwa

@mark_mod_trans \x2020 4-6-1456      # † dagger
@mark_mod_trans \x2021 4-6-12456     # ‡ double dagger
rule trans      \x2022 456-256       # • bullet
rule trans      \x2026 256-256-256   # … ellipse
rule trans      \x20a3 4-124         # ₣ franc
rule trans      \x20a6 4-1345        # ₦ naira
rule trans      \x20ac 4-15          # € euro

rule trans      \x2122 45-2345           # ™ trademark
@mark_mod_trans \x2190 56-1256-246       # ←
@mark_mod_trans \x2191 56-1256-346       # ↑
@mark_mod_trans \x2192 56-1256-135       # →
@mark_mod_trans \x2193 56-1256-146       # ↓
@mark_mod_trans \x21b5 56-1256-256-146   # ↵

rule -forward trans \x25aa 456-256   # ▪   conflicts with •

rule trans      \x2640 45-1346    # ♀ female
rule trans      \x2642 45-13456   # ♂ male
@mark_mod_trans \x266D 3456-126   # ♭ flat
@mark_mod_trans \x266E 3456-16    # ♮ natural
@mark_mod_trans \x266F 3456-146   # ♯ sharp

rule trans \x3003 5-2   # 〃 ditto mark


########################################
#   Unicode Math
########################################

rule trans \x00b0 45-245    # ° degree
rule trans \x00b1 456-235   # ± plus or minus
rule trans \x00b5 46-134    # µ micro   may be used instead of \x03bc μ

rule -forward trans \x00b7 4-16   # · dot   conflicts with solidus modifier

@mark_mod_trans \x00d7 5-236   # × times
rule trans \x00f7 5-34         # ÷ divide

match trans %n \x2044 %n   %n 34 %n   # ⁄ fraction   used for simple fractions

rule trans \x2032 2356        # ′ prime (feet, minutes, derivative)
rule trans \x2033 2356-2356   # ″ double prime (inches, seconds, second derivative)

rule trans      \x2200 45-1           # ∀ for all
rule trans      \x2202 4-145          # ∂ partial derivative
rule trans      \x2203 45-26          # ∃ there exists
rule trans      \x2204 45-26-4-156    # ∄ there does not exist
rule trans      \x2205 4-245          # ∅ empty set
rule trans      \x2207 45-145         # ∇ nabla
rule trans      \x2208 45-15          # ∈ element of
rule trans      \x2209 45-15-4-156    # ∉ not element of
rule trans      \x220b 4-45-15        # ∋ contains (such that)
rule trans      \x2211 6-46-234       # ∑ sum (capitol sigma)
@mark_mod_trans \x2212 5-36           # − minus sign   not hyphen, not delimiter
rule trans      \x2213 456-36         # ∓ minus or plus

rule -forward trans \x2217 5-35   # ∗ asterick   conflicts with *

rule trans      \x2218 5-356          # ∘ hollow dot (ring operator)
rule trans      \x221a 5-146          # √ square root
rule trans      \x221d 456-5-2356     # ∝ proportional to
@mark_mod_trans \x221e 3456-123456    # ∞ infinity
rule trans      \x2220 456-246        # ∠ angle
rule trans      \x2221 46-456-246     # ∡ measured angle
@mark_mod_trans \x2225 3456-123       # ∥ parallel to
rule trans      \x2227 4-236          # ∧ logical and
rule trans      \x2228 4-235          # ∨ logical or
rule trans      \x2229 46-236         # ∩ set intersection
rule trans      \x222a 46-235         # ∪ set union

rule -forward trans \x222b 2346   # ∫ integral   conflicts with the

rule trans      \x222e 4-2346         # ∮ contour integral

rule -forward trans \x2234 6-16   # ∴ therefore   conlicts with Child

rule trans      \x2235 4-34           # ∵ because

rule -forward trans \x2237 25-25   # ∷ proportion   conflicts with ::

rule trans      \x2243 456-35         # ≃ asymptotically equal to
rule trans      \x2245 5-456-35       # ≅ approximately equal to
rule trans      \x2248 45-35          # ≈ almost equal to
rule trans      \x224f 45-5-2356      # ≏ difference between
rule trans      \x2251 46-5-2356      # ≑ geometrically equal
rule trans      \x2260 5-2356-4-156   # ≠ not equal to
rule trans      \x2261 456-123456     # ≡ identical (equivalent) to
rule trans      \x2264 456-4-126      # ≤ less than or equal to
rule trans      \x2265 456-4-345      # ≥ greater than or equal to
rule trans      \x226a 46-4-126       # ≪ much less than
rule trans      \x226b 46-4-345       # ≫ much greater than
rule trans      \x2282 45-126         # ⊂ subset of
rule trans      \x2283 45-345         # ⊃ superset of
rule trans      \x2286 456-45-126     # ⊆ subset or equal to
rule trans      \x2287 456-45-345     # ⊇ superset or equal to
rule trans      \x228a 46-45-126      # ⊊ proper subset
rule trans      \x228b 46-45-345      # ⊋ proper superset
rule trans      \x22a3 4-456-25       # ⊣ left tack
@mark_mod_trans \x22a5 3456-36        # ⊥ up tack
rule trans      \x22a6 456-25         # ⊦ assertion
rule trans      \x22a8 45-456-25      # ⊨ valid
rule trans      \x22b2 4-456-126      # ⊲ normal subgroup
rule trans      \x22b3 4-456-345      # ⊳ contains as normal subgroup
rule trans      \x22b4 456-456-126    # ⊴ normal subgroup or equal
rule trans      \x22b5 456-456-345    # ⊵ contains as normal subgroup or equal
@mark_mod_trans \x22be 3456-456-246   # ⊾ right angle with arc
rule trans      \x22c5 5-256          # ⋅ dot operator

rule -after trans \x2329 4-126   # 〈 left angle
rule -after trans \x232A 4-345   # 〉 right angle

rule trans \x2ae4 46-456-25   # ⫤ reverse 'is valid' sign

rule -after trans \x3008 4-126   # 〈 left angle
rule -after trans \x3009 4-345   # 〉 right angle


########################################
#   Unicode vulgar fractions
########################################

pattern NUMERIC_SOFT \S\;3456;\S
filter numeric_soft_< @[NUMERIC_SOFT] -


macro vulgar_fraction
rule -forward premode $1 \S\;3456;\S$2\x2044$3
uses - numeric_soft_< rule -backward premode $1 $2\x2044$3
eom

@vulgar_fraction ¼ 1 4    # \x00bc
@vulgar_fraction ½ 1 2    #
@vulgar_fraction ¾ 3 4    #
@vulgar_fraction ⅐ 1 7    # \x2150
@vulgar_fraction ⅑ 1 9    #
@vulgar_fraction ⅒ 1 10   #
@vulgar_fraction ⅓ 1 3    #
@vulgar_fraction ⅔ 2 3    #
@vulgar_fraction ⅕ 1 5    #
@vulgar_fraction ⅖ 2 5    #
@vulgar_fraction ⅗ 3 5    #
@vulgar_fraction ⅘ 4 5    #
@vulgar_fraction ⅙ 1 6    #
@vulgar_fraction ⅚ 5 6    #
@vulgar_fraction ⅛ 1 8    #
@vulgar_fraction ⅜ 3 8    #
@vulgar_fraction ⅝ 5 8    #
@vulgar_fraction ⅞ 7 8    #
@vulgar_fraction ↉ 0 3    #

#ule premode ⅟ 1/


########################################
#   Unicode super/subscripts
########################################

#\x00b2 ²
#\x00b3 ³
#\x00b9 ¹
#\x1d62 ᵢᵣᵤᵥᵦᵧᵨᵩᵪ
#\x2070 ⁰ⁱ⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾ⁿ
#\x2080 ₀₁₂₃₄₅₆₇₈₉₊₋₌₍₎ₐₑₒₓₔₕₖₗₘₙₚₛₜ
#\x2c7c ⱼ


########################################
#   Unicode Greek
########################################

@uplo \x0391 \x03b1 46-1       # Αα Alpha
@uplo \x0392 \x03b2 46-12      # Ββ Beta
@uplo \x0393 \x03b3 46-1245    # Γγ Gamma
@uplo \x0394 \x03b4 46-145     # Δδ Delta
@uplo \x0395 \x03b5 46-15      # Εε Epsilon
@uplo \x0396 \x03b6 46-1356    # Ζζ Zeta
@uplo \x0397 \x03b7 46-156     # Ηη Eta
@uplo \x0398 \x03b8 46-1456    # Θθ Theta
@uplo \x0399 \x03b9 46-24      # Ιι Iota
@uplo \x039a \x03ba 46-13      # Κκ Kappa
@uplo \x039b \x03bb 46-123     # Λλ Lamda
@uplo \x039c \x03bc 46-134     # Μμ Mu
@uplo \x039d \x03bd 46-1345    # Νν Nu
@uplo \x039e \x03be 46-1346    # Ξξ Xi
@uplo \x039f \x03bf 46-135     # Οο Omicron
@uplo \x03a0 \x03c0 46-1234    # Ππ Pi
@uplo \x03a1 \x03c1 46-1235    # Ρρ Rho
@uplo \x03a3 \x03c3 46-234     # Σσ Sigma
@uplo \x03a4 \x03c4 46-2345    # Ττ Tau
@uplo \x03a5 \x03c5 46-136     # Υυ Upsilon
@uplo \x03a6 \x03c6 46-124     # Φφ Phi
@uplo \x03a7 \x03c7 46-12346   # Χχ Chi
@uplo \x03a8 \x03c8 46-13456   # Ψψ Psi
@uplo \x03a9 \x03c9 46-2456    # Ωω Omega

rule -after trans \x03c2 46-234   # ς


#   ambiguous with final-letters
match premode %a Δ -   @[LETTER_<-] \;56;Δ -
match premode %a δ -   @[LETTER_<-] \;56;δ -
match premode %a Ε -   @[LETTER_<-] \;56;Ε -
match premode %a ε -   @[LETTER_<-] \;56;ε -
match premode %a Ν -   @[LETTER_<-] \;56;Ν -
match premode %a ν -   @[LETTER_<-] \;56;ν -
match premode %a Τ -   @[LETTER_<-] \;56;Τ -
match premode %a τ -   @[LETTER_<-] \;56;τ -
match premode %a Σ -   @[LETTER_<-] \;56;Σ -
match premode %a σ -   @[LETTER_<-] \;56;σ -


########################################
#   Unicode Miscellaneous
########################################

rule trans \x21cc 45-456-2356   # ⇌

rule trans \x29b5 46-245   # ⦵

@uplo \x00de \x00fe 3456-2346    # Þþ thorn
@uplo \x00d0 \x00f0 3456-1246    # Ðð eth
@uplo \x01f7 \x01bf 3456-2456    # Ƿƿ wynn (wen)
@uplo \x021c \x021d 3456-13456   # Ȝȝ yogh

rule trans \x02e6 45-46-14   # ˦ high tone
rule trans \x02e7 45-46-25   # ˧ mid tone
rule trans \x02e8 45-46-36   # ˨ low tone

rule trans \x2713 4-146   # ✓ check mark


################################################################################

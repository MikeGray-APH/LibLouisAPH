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

#   letters   ⠁⠃⠉⠙⠑⠋⠛⠓⠊⠚⠅⠇⠍⠝⠕⠏⠟⠗⠎⠞⠥⠧⠺⠭⠽⠵
#   ⠁a ⠃b ⠉c ⠙d ⠑e ⠋f ⠛g ⠓h ⠊i ⠚j ⠅k ⠇l ⠍m ⠝n ⠕o ⠏p ⠟q ⠗r ⠎s ⠞t ⠥u ⠧v ⠺w ⠭x ⠽y ⠵z
#
#   modifiers   ⠈[⠬⠤⠡⠒] ⠘[⠌⠬⠯⠩⠒⠡⠫⠻⠖] ⠘⠸[⠂⠆⠤]
#   ⠈⠬breve ⠈⠤macron ⠈⠡solidus ⠈⠒stroke
#   ⠘⠌acute ⠘⠬caron ⠘⠯cedilla ⠘⠩circumflex ⠘⠒diaeresis ⠘⠡grave ⠘⠫ring ⠘⠻tilde
#   ⠘⠸⠂first ⠘⠸⠆second ⠘⠸⠤third
#   ⠘⠖ligature
#
#   symbols
#   ⠂, ⠄' ⠆; ⠒: ⠤- ⠖! ⠦? ⠦“‘"' ⠲. ⠴”’"'
#   ⠸⠌/ ⠐⠔* ⠐⠣( ⠐⠖+ ⠐⠜) ⠐⠶=
#   ⠈⠁@ ⠈⠢^ ⠈⠣< ⠈⠎$ ⠈⠜> ⠈⠯&
#   ⠘⠦“ ⠘⠴”
#   ⠨⠤_ ⠨⠣[ ⠨⠜] ⠨⠴%
#   ⠸⠡\ ⠸⠣{ ⠸⠜} ⠸⠳| ⠸⠹#
#   ⠠⠦‘ ⠠⠴’ ⠠⠶"
#   ⠈⠠⠹†
#
#   alphabetic wordsigns   ⠵⠃⠉⠙⠑⠋⠛⠓⠭⠚⠅⠇⠍⠝⠏⠟⠗⠎⠞⠥⠧⠺⠽
#   ⠵as ⠃but ⠉can ⠙do ⠑every ⠋from ⠛go ⠓have ⠭it ⠚just ⠅knowledge ⠇like ⠍more
#   ⠝not ⠏people ⠟quite ⠗rather ⠎so ⠞that ⠥us ⠧very ⠺will ⠽you
#
#   strong wordsigns   ⠡⠳⠩⠌⠹⠱
#   ⠡child ⠳out ⠩shall ⠌still ⠹this ⠱which
#
#   strong contractions   ⠯⠿⠷⠮⠾
#   ⠯and ⠿for ⠷of ⠮the ⠾with
#
#   strong groupsigns   ⠜⠡⠫⠻⠣⠬⠳⠪⠩⠌⠹⠱
#   ⠜ar ⠡ch ⠫ed ⠻er ⠣gh ⠬ing ⠳ou ⠪ow ⠩sh ⠌st ⠹th ⠱wh
#
#   lower wordsigns   ⠆⠢⠦⠔⠴⠶
#   ⠆be ⠢enough ⠦his ⠔in ⠴was ⠶were
#
#   lower groupsigns   ⠆⠒⠲⠂⠢⠖⠶⠔
#   ⠆bb ⠆be ⠒cc ⠒con ⠲dis ⠂ea ⠢en ⠖ff ⠶gg ⠔in
#
#   initial-letter   ⠘[⠮⠹⠥⠱⠺]|⠸[⠉⠓⠍⠎⠮⠺]|⠐[⠡⠙⠑⠋⠓⠅⠇⠍⠝⠕⠳⠏⠟⠗⠎⠮⠹⠞⠥⠱⠺⠽]
#   ⠘⠮these ⠘⠹those ⠘⠥upon ⠘⠱whose ⠘⠺word
#   ⠸⠉cannot ⠸⠓had ⠸⠍many ⠸⠎spirit ⠸⠮their ⠸⠺world
#   ⠐⠡character ⠐⠙day ⠐⠑ever ⠐⠋father ⠐⠓here ⠐⠅know ⠐⠇lord ⠸⠍many ⠐⠍mother
#   ⠐⠝name ⠐⠕one ⠐⠳ought ⠐⠏part ⠐⠟question ⠐⠗right ⠐⠎some ⠐⠮there ⠘⠮these
#   ⠐⠹through ⠐⠞time ⠐⠥under ⠘⠥upon ⠐⠱where ⠘⠱whose ⠘⠺word ⠐⠺work ⠸⠺world
#   ⠐⠽young
#
#   final-letter   ⠨[⠑⠎⠙⠞⠝]|⠰[⠑⠇⠽⠞⠎⠛⠝]
#   ⠨⠑ance ⠨⠎less ⠨⠙ound ⠨⠞ount ⠨⠝sion
#   ⠰⠑ence ⠰⠇ful ⠰⠽ity ⠰⠞ment ⠰⠎ness ⠰⠛ong ⠰⠝tion
#
#   capital indicators
#   ⠠symbol ⠠⠠word ⠠⠠⠠passage ⠠⠄terminator
#
#   numeric indicators
#   ⠐space ⠼word ⠼⠼passage ⠼⠄terminator
#
#   grade 1 indicators
#   ⠰symbol ⠰⠰word ⠰⠰⠰passage ⠰⠄terminator
#
#   typeform indicators
#   ⠨italic ⠘bold ⠸underline ⠈script ⠈⠼first ⠘⠼second ⠸⠼third ⠐⠼fourth ⠨⠼fifth
#   ⠆symbol ⠂word ⠶passage ⠄terminator
#

################################################################################

include english-ueb-grade1.rst

set contraction bit00
attrs + $contraction


########################################
#   word filters
########################################

filter word_whole_+         @[WORD_<+]                @[APOST_+]@[WORD_>+]
filter word_whole_begin_+   @[WORD_<+]                @[LETTER_>+]*@[APOST_+]@[WORD_>+]
filter word_whole_end_+     @[WORD_<+]%a*             @[APOST_+]@[WORD_>+]
filter word_begin_+         @[WORD_<+]                @[LETTER_>+]
filter word_begin_mid_+     @[WORD_<+]%a*             @[LETTER_>+]
filter word_mid_+           %a                        @[LETTER_>+]
filter word_mid_end_+       %a                        @[LETTER_>+]*@[APOST_+]@[WORD_>+]
filter word_end_+           %a                        @[APOST_+]@[WORD_>+]

filter word_whole_-         @[WORD_<-]                @[APOST_-]@[WORD_>-]
filter word_whole_begin_-   @[WORD_<-]                @[LETTER_>-]*@[APOST_-]@[WORD_>-]
filter word_whole_end_-     @[WORD_<-]@[LETTER_<-]*   @[APOST_-]@[WORD_>-]
filter word_begin_-         @[WORD_<-]                @[LETTER_>-]
filter word_begin_mid_+     @[WORD_<-]@[LETTER_<-]*   @[LETTER_>-]
filter word_mid_-           @[LETTER_<-]              @[LETTER_>-]
filter word_mid_end_-       @[LETTER_<-]              @[LETTER_>-]*@[APOST_-]@[WORD_>-]
filter word_end_-           @[LETTER_<-]              @[APOST_-]@[WORD_>-]


########################################
#   10.1   Alphabetic Wordsigns
########################################

use word_whole_+ word_whole_-
rule trans as          1356
rule trans but         12
rule trans can         14
rule trans do          145
rule trans every       15
rule trans from        124
rule trans go          1245
rule trans have        125
rule trans it          1346
rule trans just        245
rule trans knowledge   13
rule trans like        123
rule trans more        134
rule trans not         1345
rule trans people      1234
rule trans quite       12345
rule trans rather      1235
rule trans so          234
rule trans that        2345
rule trans us          136
rule trans very        1236
rule trans will        2456
rule trans you         13456
use


macro uplo_grade_1
rule premode $1 \H\;56;\H$1
rule premode $2 \H\;56;\H$2
eom

use word_whole_+ -
#uplo_grade_1 A a
@uplo_grade_1 B b
@uplo_grade_1 C c
@uplo_grade_1 D d
@uplo_grade_1 E e
@uplo_grade_1 F f
@uplo_grade_1 G g
@uplo_grade_1 H h
#uplo_grade_1 I i
@uplo_grade_1 J j
@uplo_grade_1 K k
@uplo_grade_1 L l
@uplo_grade_1 M m
@uplo_grade_1 N n
#uplo_grade_1 O o
@uplo_grade_1 P p
@uplo_grade_1 Q q
@uplo_grade_1 R r
@uplo_grade_1 S s
@uplo_grade_1 T t
@uplo_grade_1 U u
@uplo_grade_1 V v
@uplo_grade_1 W w
@uplo_grade_1 X x
@uplo_grade_1 Y y
@uplo_grade_1 Z z
use


########################################
#   10.2   Strong Wordsigns
########################################

use word_whole_+ word_whole_-
rule trans child   16
rule trans out     1256
rule trans shall   146
rule trans still   34
rule trans this    1456
rule trans which   156
use


########################################
#   10.3   Strong Contractions
########################################

use word_whole_begin_+ word_whole_begin_-

## and   ⠘⠯cedilla
uses - not_modifier_45_- rule trans and 12346

## for
uses - - rule trans for 123456

rule trans gifford ⠛⠊⠋⠿⠙
rule trans spafford ⠎⠏⠁⠋⠿⠙
rule trans trafford ⠞⠗⠁⠋⠿⠙
rule trans afforce ⠁⠋⠿⠉⠑
rule trans chifforobe ⠡⠊⠖⠕⠗⠕⠃⠑
rule trans countereffort ⠉⠨⠞⠻⠑⠋⠿⠞
rule trans disafforest ⠲⠁⠋⠿⠑⠌
rule trans efformation ⠑⠋⠿⠍⠁⠰⠝
rule trans overeffort ⠕⠧⠻⠑⠋⠿⠞
rule trans unaffordable ⠥⠝⠁⠋⠿⠙⠁⠃⠇⠑
rule trans deafforest ⠙⠑⠁⠋⠿⠑⠌
rule trans deafforestation ⠙⠑⠁⠋⠿⠑⠌⠁⠰⠝
rule trans reafforest ⠗⠑⠁⠋⠿⠑⠌


## of
uses - - rule trans of 12356

rule trans aeroflot 1-12456-135-124-123-135-2345
rule trans aerofoil ⠁⠻⠕⠋⠕⠊⠇
rule trans anterofixation ⠁⠝⠞⠻⠕⠋⠊⠭⠁⠰⠝
rule trans autofermentation ⠁⠥⠞⠕⠋⠻⠰⠞⠁⠰⠝
rule trans autofit ⠁⠥⠞⠕⠋⠊⠞
rule trans autofluorescence ⠁⠥⠞⠕⠋⠇⠥⠕⠗⠑⠎⠉⠰⠑
rule trans autofocus ⠁⠥⠞⠕⠋⠕⠉⠥⠎
rule trans autoformation ⠁⠥⠞⠕⠿⠍⠁⠰⠝
rule trans autoforming ⠁⠥⠞⠕⠿⠍⠬
rule trans benzofulvene ⠃⠢⠵⠕⠰⠇⠧⠢⠑
rule trans benzofuran ⠃⠢⠵⠕⠋⠥⠗⠁⠝
rule trans benzothiofuran ⠃⠢⠵⠕⠹⠊⠕⠋⠥⠗⠁⠝
rule trans biofeedback 12-24-135-124-15-1246-12-1-14-13
rule trans bioform ⠃⠊⠕⠿⠍
rule trans biofuel ⠃⠊⠕⠋⠥⠑⠇
rule trans chlorofluorocarbon 16-123-135-1235-135-124-123-136-135-1235-135-14-345-12-135-1345
rule trans chloroform 16-123-135-1235-135-123456-134
rule trans cofactor ⠉⠕⠋⠁⠉⠞⠕⠗
rule trans cofather ⠉⠕⠐⠋
rule trans cofeature ⠉⠕⠋⠂⠞⠥⠗⠑
rule trans coferment ⠉⠕⠋⠻⠰⠞
rule trans cofield ⠉⠕⠋⠊⠑⠇⠙
rule trans cofighter ⠉⠕⠋⠊⠣⠞⠻
rule trans cofinal ⠉⠕⠋⠔⠁⠇
rule trans cofinance ⠉⠕⠋⠔⠨⠑
rule trans cofinancing ⠉⠕⠋⠔⠁⠝⠉⠬
rule trans coforeknow ⠉⠕⠿⠑⠐⠅
rule trans coformulator ⠉⠕⠿⠍⠥⠇⠁⠞⠕⠗
rule trans cofound ⠉⠕⠋⠨⠙
rule trans cofunction ⠉⠕⠋⠥⠝⠉⠰⠝
rule trans deuterofibrinose ⠙⠑⠥⠞⠻⠕⠋⠊⠃⠗⠔⠕⠎⠑
rule trans electroforming ⠑⠇⠑⠉⠞⠗⠕⠿⠍⠬
rule trans electrofusion ⠑⠇⠑⠉⠞⠗⠕⠋⠥⠨⠝
rule trans filofax 124-24-123-135-124-1-1346
rule trans fluoroform ⠋⠇⠥⠕⠗⠕⠿⠍
rule trans galvanofaradization ⠛⠁⠇⠧⠁⠝⠕⠋⠜⠁⠙⠊⠵⠁⠰⠝
rule trans ganglioform ⠛⠁⠝⠛⠇⠊⠕⠿⠍
rule trans griseofulvin ⠛⠗⠊⠎⠑⠕⠰⠇⠧⠔
rule trans heterofermentative ⠓⠑⠞⠻⠕⠋⠻⠰⠞⠁⠞⠊⠧⠑
rule trans heterofertilization ⠓⠑⠞⠻⠕⠋⠻⠞⠊⠇⠊⠵⠁⠰⠝
rule trans homofermentative ⠓⠕⠍⠕⠋⠻⠰⠞⠁⠞⠊⠧⠑
rule trans hydrofoil 125-13456-145-1235-135-124-135-24-123
rule trans hydroforming ⠓⠽⠙⠗⠕⠿⠍⠬
rule trans hypofunction ⠓⠽⠏⠕⠋⠥⠝⠉⠰⠝
rule trans insofar 35-234-135-124-345
rule trans luteofulvous ⠇⠥⠞⠑⠕⠰⠇⠧⠳⠎
rule trans luteofuscous ⠇⠥⠞⠑⠕⠋⠥⠎⠉⠳⠎
rule trans macrofossil ⠍⠁⠉⠗⠕⠋⠕⠎⠎⠊⠇
rule trans microfiche 134-24-14-1235-135-124-24-16-15
rule trans microfilm 134-24-14-1235-135-124-24-123-134
rule trans microflora ⠍⠊⠉⠗⠕⠋⠇⠕⠗⠁
rule trans microfoliation ⠍⠊⠉⠗⠕⠋⠕⠇⠊⠁⠰⠝
rule trans monofilament ⠍⠕⠝⠕⠋⠊⠇⠁⠰⠞
rule trans monofuel ⠍⠕⠝⠕⠋⠥⠑⠇
rule trans microwave 134-24-14-1235-135-2456-1-1236-15
rule trans microwaved 134-24-14-1235-135-2456-1-1236-1246
rule trans microwaving 134-24-14-1235-135-2456-1-1236-346
rule trans myofilament ⠍⠽⠕⠋⠊⠇⠁⠰⠞
rule trans neoformation ⠝⠑⠕⠿⠍⠁⠰⠝
rule trans nitrofuran ⠝⠊⠞⠗⠕⠋⠥⠗⠁⠝
rule trans octofoil ⠕⠉⠞⠕⠋⠕⠊⠇
rule trans photofission ⠏⠓⠕⠞⠕⠋⠊⠎⠨⠝
rule trans photoflash 1234-125-135-2345-135-124-123-1-146
rule trans pianoforte 1234-24-1-1345-135-123456-2345-15
rule trans picofarad ⠏⠊⠉⠕⠋⠜⠁⠙
rule trans portofino ⠏⠕⠗⠞⠕⠋⠔⠕
rule trans prechloroform ⠏⠗⠑⠡⠇⠕⠗⠕⠿⠍
rule trans proforma 1234-1235-135-123456-134-1
rule trans pseudofaithful ⠏⠎⠑⠥⠙⠕⠋⠁⠊⠹⠰⠇
rule trans pseudofamous ⠏⠎⠑⠥⠙⠕⠋⠁⠍⠳⠎
rule trans pseudofatherly ⠏⠎⠑⠥⠙⠕⠐⠋⠇⠽
rule trans pseudofeminine ⠏⠎⠑⠥⠙⠕⠋⠑⠍⠔⠔⠑
rule trans pseudofever ⠏⠎⠑⠥⠙⠕⠋⠐⠑
rule trans pseudofinal ⠏⠎⠑⠥⠙⠕⠋⠔⠁⠇
rule trans pseudofluctuation ⠏⠎⠑⠥⠙⠕⠋⠇⠥⠉⠞⠥⠁⠰⠝
rule trans pseudofossil ⠏⠎⠑⠥⠙⠕⠋⠕⠎⠎⠊⠇
rule trans retrofire ⠗⠑⠞⠗⠕⠋⠊⠗⠑
rule trans retrofit 1235-15-2345-1235-135-124-24-2345
rule trans retroflection ⠗⠑⠞⠗⠕⠋⠇⠑⠉⠰⠝
rule trans retroflex ⠗⠑⠞⠗⠕⠋⠇⠑⠭
rule trans retroflexive ⠗⠑⠞⠗⠕⠋⠇⠑⠭⠊⠧⠑
rule trans retroflux ⠗⠑⠞⠗⠕⠋⠇⠥⠭
rule trans retroform ⠗⠑⠞⠗⠕⠿⠍
rule trans retrofract ⠗⠑⠞⠗⠕⠋⠗⠁⠉⠞
rule trans retrofrontal ⠗⠑⠞⠗⠕⠋⠗⠕⠝⠞⠁⠇
rule trans riboflavin 1235-24-12-135-124-123-1-1236-35
rule trans styrofoam 34-13456-1235-135-124-135-1-134
rule trans sulfofication ⠎⠥⠇⠋⠕⠋⠊⠉⠁⠰⠝
rule trans sulphofication ⠎⠥⠇⠏⠓⠕⠋⠊⠉⠁⠰⠝
rule trans synchroflash ⠎⠽⠝⠡⠗⠕⠋⠇⠁⠩
rule trans thermoform ⠮⠗⠍⠕⠿⠍
rule trans turbofan ⠞⠥⠗⠃⠕⠋⠁⠝
rule trans twofer 2345-2456-135-124-12456
rule trans twofold 2345-2456-135-124-135-123-145
rule trans ventrofixation ⠧⠢⠞⠗⠕⠋⠊⠭⠁⠰⠝
rule trans heredofamilial ⠓⠻⠫⠕⠋⠁⠍⠊⠇⠊⠁⠇


## the
uses - - rule trans the 2346

rule trans acenesthesia ⠁⠉⠢⠑⠎⠮⠎⠊⠁
rule trans acmesthesia ⠁⠉⠍⠑⠎⠮⠎⠊⠁
rule trans acoenesthesia ⠁⠉⠕⠢⠑⠎⠮⠎⠊⠁
rule trans aesthesia ⠁⠑⠎⠮⠎⠊⠁
rule trans aesthete 1-15-234-2346-2345-15
rule trans aesthetic 1-15-234-2346-2345-24-14
rule trans altheim ⠁⠇⠞⠓⠑⠊⠍
rule trans altheim ⠁⠇⠞⠓⠑⠊⠍
rule trans ammotherapy ⠁⠍⠍⠕⠮⠗⠁⠏⠽
rule trans ampthill ⠁⠍⠏⠞⠓⠊⠇⠇
rule trans ampthill's ⠁⠍⠏⠞⠓⠊⠇⠇⠄⠎
rule trans anaesthesia 1-1345-1-15-234-2346-234-24-1
rule trans anaesthetic 1-1345-1-15-234-2346-2345-24-14
rule trans anaesthetist 1-1345-1-15-234-2346-2345-24-34
rule trans anaesthetize 1-1345-1-15-234-2346-2345-24-1356-15
rule trans anaesthetized 1-1345-1-15-234-2346-2345-24-1356-1246
rule trans anaesthetizing 1-1345-1-15-234-2346-2345-24-1356-346
rule trans anesthesia 1-1345-15-234-2346-234-24-1
rule trans anesthesiologist 1-1345-15-234-2346-234-24-135-123-135-1245-24-34
rule trans anesthesiology 1-1345-15-234-2346-234-24-135-123-135-1245-13456
rule trans anesthetic 1-1345-15-234-2346-2345-24-14
rule trans anesthetist 1-1345-15-234-2346-2345-24-34
rule trans anesthetize 1-1345-15-234-2346-2345-24-1356-15
rule trans anesthetized 1-1345-15-234-2346-2345-24-1356-1246
rule trans anesthetizing 1-1345-15-234-2346-2345-24-1356-346
rule trans antiaesthetic ⠁⠝⠞⠊⠁⠑⠎⠮⠞⠊⠉
rule trans aunthood ⠁⠥⠝⠞⠓⠕⠕⠙
rule trans autohemotherapy ⠁⠥⠞⠕⠓⠑⠍⠕⠮⠗⠁⠏⠽
rule trans autoplasmotherapy ⠁⠥⠞⠕⠏⠇⠁⠎⠍⠕⠮⠗⠁⠏⠽
rule trans bathorse ⠃⠁⠞⠓⠕⠗⠎⠑
rule trans bathorses ⠃⠁⠞⠓⠕⠗⠎⠑⠎
rule trans benzothiofuran ⠃⠢⠵⠕⠹⠊⠕⠋⠥⠗⠁⠝
rule trans blythedale ⠃⠇⠽⠮⠙⠁⠇⠑
rule trans blythedale's ⠃⠇⠽⠮⠙⠁⠇⠑⠄⠎
rule trans boathook ⠃⠕⠁⠞⠓⠕⠕⠅
rule trans boathook's ⠃⠕⠁⠞⠓⠕⠕⠅⠄⠎
rule trans boathooks ⠃⠕⠁⠞⠓⠕⠕⠅⠎
rule trans boathouse ⠃⠕⠁⠞⠓⠳⠎⠑
rule trans boathouse's ⠃⠕⠁⠞⠓⠳⠎⠑⠄⠎
rule trans boathouses ⠃⠕⠁⠞⠓⠳⠎⠑⠎
rule trans bolthole ⠃⠕⠇⠞⠓⠕⠇⠑
rule trans boltholes ⠃⠕⠇⠞⠓⠕⠇⠑⠎
rule trans bootholder ⠃⠕⠕⠞⠓⠕⠇⠙⠻
rule trans bootholders ⠃⠕⠕⠞⠓⠕⠇⠙⠻⠎
rule trans calisthenic 14-1-123-24-234-2346-1345-24-14
rule trans carthorse ⠉⠜⠞⠓⠕⠗⠎⠑
rule trans carthorses ⠉⠜⠞⠓⠕⠗⠎⠑⠎
rule trans cathouse ⠉⠁⠞⠓⠳⠎⠑
rule trans cathouses ⠉⠁⠞⠓⠳⠎⠑⠎
rule trans cenesthesia ⠉⠢⠑⠎⠮⠎⠊⠁
rule trans cenesthesis ⠉⠢⠑⠎⠮⠎⠊⠎
rule trans cenesthetic ⠉⠢⠑⠎⠮⠞⠊⠉
rule trans charthouse ⠡⠜⠞⠓⠳⠎⠑
rule trans charthouses ⠡⠜⠞⠓⠳⠎⠑⠎
rule trans chemotherapeutic ⠡⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉
rule trans chemotherapeutically ⠡⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉⠁⠇⠇⠽
rule trans chemotherapist ⠡⠑⠍⠕⠮⠗⠁⠏⠊⠌
rule trans chemotherapists ⠡⠑⠍⠕⠮⠗⠁⠏⠊⠌⠎
rule trans christhood ⠡⠗⠊⠌⠓⠕⠕⠙
rule trans chromesthesia ⠡⠗⠕⠍⠑⠎⠮⠎⠊⠁
rule trans chromotherapist ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠊⠌
rule trans chromotherapists ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠊⠌⠎
rule trans chromotherapy ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠽
rule trans coathanger ⠉⠕⠁⠞⠓⠁⠝⠛⠻
rule trans coathanger's ⠉⠕⠁⠞⠓⠁⠝⠛⠻⠄⠎
rule trans coathangers ⠉⠕⠁⠞⠓⠁⠝⠛⠻⠎
rule trans coathole ⠉⠕⠁⠞⠓⠕⠇⠑
rule trans coathole's ⠉⠕⠁⠞⠓⠕⠇⠑⠄⠎
rule trans coatholes ⠉⠕⠁⠞⠓⠕⠇⠑⠎
rule trans coathook ⠉⠕⠁⠞⠓⠕⠕⠅
rule trans coathook's ⠉⠕⠁⠞⠓⠕⠕⠅⠄⠎
rule trans coathooks ⠉⠕⠁⠞⠓⠕⠕⠅⠎
rule trans coenaesthesis ⠉⠕⠢⠁⠑⠎⠮⠎⠊⠎
rule trans coenesthesia ⠉⠕⠢⠑⠎⠮⠎⠊⠁
rule trans coenesthesis ⠉⠕⠢⠑⠎⠮⠎⠊⠎
rule trans cofather ⠉⠕⠐⠋
rule trans crosthwaite ⠉⠗⠕⠎⠹⠺⠁⠊⠞⠑
rule trans crosthwaite's ⠉⠗⠕⠎⠹⠺⠁⠊⠞⠑⠄⠎
rule trans crymotherapy ⠉⠗⠽⠍⠕⠮⠗⠁⠏⠽
rule trans cryotherapy ⠉⠗⠽⠕⠮⠗⠁⠏⠽
rule trans demosthenes 145-15-134-135-234-2346-1345-15-234
rule trans diathermotherapy ⠙⠊⠁⠮⠗⠍⠕⠮⠗⠁⠏⠽
rule trans draughthouse ⠙⠗⠁⠥⠣⠞⠓⠳⠎⠑
rule trans draughthouse's ⠙⠗⠁⠥⠣⠞⠓⠳⠎⠑⠄⠎
rule trans draughthouses ⠙⠗⠁⠥⠣⠞⠓⠳⠎⠑⠎
rule trans dysaesthesia ⠙⠽⠎⠁⠑⠎⠮⠎⠊⠁
rule trans dysaesthetic ⠙⠽⠎⠁⠑⠎⠮⠞⠊⠉
rule trans dysesthesia ⠙⠽⠎⠑⠎⠮⠎⠊⠁
rule trans dysesthetic ⠙⠽⠎⠑⠎⠮⠞⠊⠉
rule trans ectotherm ⠑⠉⠞⠕⠮⠗⠍
rule trans ectothermic ⠑⠉⠞⠕⠮⠗⠍⠊⠉
rule trans elasmotherium ⠑⠇⠁⠎⠍⠕⠮⠗⠊⠥⠍
rule trans electroanesthesia ⠑⠇⠑⠉⠞⠗⠕⠁⠝⠑⠎⠮⠎⠊⠁
rule trans eratosthenes 12456-1-2345-135-234-2346-1345-15-234
rule trans esther 15-234-2346-1235
rule trans estheses ⠑⠎⠮⠎⠑⠎
rule trans esthesia ⠑⠎⠮⠎⠊⠁
rule trans esthesiology ⠑⠎⠮⠎⠊⠕⠇⠕⠛⠽
rule trans esthesiometer ⠑⠎⠮⠎⠊⠕⠍⠑⠞⠻
rule trans esthesiometers ⠑⠎⠮⠎⠊⠕⠍⠑⠞⠻⠎
rule trans esthesiometry ⠑⠎⠮⠎⠊⠕⠍⠑⠞⠗⠽
rule trans esthesis ⠑⠎⠮⠎⠊⠎
rule trans esthete 15-234-2346-2345-15
rule trans esthetic 15-234-2346-2345-24-14
rule trans esthetical ⠑⠎⠮⠞⠊⠉⠁⠇
rule trans esthetically ⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans esthetician ⠑⠎⠮⠞⠊⠉⠊⠁⠝
rule trans estheticians ⠑⠎⠮⠞⠊⠉⠊⠁⠝⠎
rule trans estheticism ⠑⠎⠮⠞⠊⠉⠊⠎⠍
rule trans esthwaite ⠑⠎⠹⠺⠁⠊⠞⠑
rule trans esthwaite's ⠑⠎⠹⠺⠁⠊⠞⠑⠄⠎
rule trans fainthearted 124-1-35-2345-125-15-345-2345-1246
rule trans fathead 124-1-2345-125-2-145
rule trans flatholm ⠋⠇⠁⠞⠓⠕⠇⠍
rule trans flatholm's ⠋⠇⠁⠞⠓⠕⠇⠍⠄⠎
rule trans gianthood ⠛⠊⠁⠝⠞⠓⠕⠕⠙
rule trans glossokinesthetic ⠛⠇⠕⠎⠎⠕⠅⠔⠑⠎⠮⠞⠊⠉
rule trans gotthard ⠛⠕⠞⠞⠓⠜⠙
rule trans gotthard's ⠛⠕⠞⠞⠓⠜⠙⠄⠎
rule trans grandparenthood ⠛⠗⠯⠏⠜⠢⠞⠓⠕⠕⠙
rule trans guesthouse ⠛⠥⠑⠌⠓⠳⠎⠑
rule trans guesthouse's ⠛⠥⠑⠌⠓⠳⠎⠑⠄⠎
rule trans guesthouses ⠛⠥⠑⠌⠓⠳⠎⠑⠎
rule trans hemianesthesia ⠓⠑⠍⠊⠁⠝⠑⠎⠮⠎⠊⠁
rule trans hemidysesthesia ⠓⠑⠍⠊⠙⠽⠎⠑⠎⠮⠎⠊⠁
rule trans hemihyperesthesia ⠓⠑⠍⠊⠓⠽⠏⠻⠑⠎⠮⠎⠊⠁
rule trans hemihypesthesia ⠓⠑⠍⠊⠓⠽⠏⠑⠎⠮⠎⠊⠁
rule trans hemihypoesthesia ⠓⠑⠍⠊⠓⠽⠏⠕⠑⠎⠮⠎⠊⠁
rule trans hemiparanesthesia ⠓⠑⠍⠊⠏⠜⠁⠝⠑⠎⠮⠎⠊⠁
rule trans hemiparesthesia ⠓⠑⠍⠊⠏⠜⠑⠎⠮⠎⠊⠁
rule trans hemotherapeutic ⠓⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉
rule trans hemotherapeutics ⠓⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉⠎
rule trans hemotherapy ⠓⠑⠍⠕⠮⠗⠁⠏⠽
rule trans hesther ⠓⠑⠎⠮⠗
rule trans hesther's ⠓⠑⠎⠮⠗⠄⠎
rule trans homotherm ⠓⠕⠍⠕⠮⠗⠍
rule trans homothermic ⠓⠕⠍⠕⠮⠗⠍⠊⠉
rule trans homotherms ⠓⠕⠍⠕⠮⠗⠍⠎
rule trans hothead 125-135-2345-125-2-145
rule trans hypaesthesia ⠓⠽⠏⠁⠑⠎⠮⠎⠊⠁
rule trans hyperaesthesia ⠓⠽⠏⠻⠁⠑⠎⠮⠎⠊⠁
rule trans hyperaesthete ⠓⠽⠏⠻⠁⠑⠎⠮⠞⠑
rule trans hyperaesthetic ⠓⠽⠏⠻⠁⠑⠎⠮⠞⠊⠉
rule trans hyperesthesia ⠓⠽⠏⠻⠑⠎⠮⠎⠊⠁
rule trans hyperesthete ⠓⠽⠏⠻⠑⠎⠮⠞⠑
rule trans hyperesthetic ⠓⠽⠏⠻⠑⠎⠮⠞⠊⠉
rule trans hypesthesia ⠓⠽⠏⠑⠎⠮⠎⠊⠁
rule trans inaesthetic ⠔⠁⠑⠎⠮⠞⠊⠉
rule trans inesthetic ⠔⠑⠎⠮⠞⠊⠉
rule trans infanthood ⠔⠋⠁⠝⠞⠓⠕⠕⠙
rule trans kinaesthesia ⠅⠔⠁⠑⠎⠮⠎⠊⠁
rule trans kinaesthesis ⠅⠔⠁⠑⠎⠮⠎⠊⠎
rule trans kinaesthetic ⠅⠔⠁⠑⠎⠮⠞⠊⠉
rule trans kinaesthetically ⠅⠔⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans kinestheses ⠅⠔⠑⠎⠮⠎⠑⠎
rule trans kinesthesia ⠅⠔⠑⠎⠮⠎⠊⠁
rule trans kinesthesis ⠅⠔⠑⠎⠮⠎⠊⠎
rule trans kinesthetic ⠅⠔⠑⠎⠮⠞⠊⠉
rule trans kinesthetically ⠅⠔⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans lefthand ⠇⠑⠋⠞⠓⠯
rule trans lightheaded 123-24-126-2345-125-2-145-1246
rule trans lighthearted 123-24-126-2345-125-15-345-2345-1246
rule trans malthouse ⠍⠁⠇⠞⠓⠳⠎⠑
rule trans malthouse's ⠍⠁⠇⠞⠓⠳⠎⠑⠄⠎
rule trans malthouses ⠍⠁⠇⠞⠓⠳⠎⠑⠎
rule trans masthand ⠍⠁⠌⠓⠯
rule trans masthand's ⠍⠁⠌⠓⠯⠄⠎
rule trans masthands ⠍⠁⠌⠓⠯⠎
rule trans merchanthood ⠍⠻⠡⠁⠝⠞⠓⠕⠕⠙
rule trans motheaten 134-135-1456-2-2345-26
rule trans narcoanesthesia ⠝⠜⠉⠕⠁⠝⠑⠎⠮⠎⠊⠁
rule trans nonaesthetic ⠝⠕⠝⠁⠑⠎⠮⠞⠊⠉
rule trans nonaesthetically ⠝⠕⠝⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans nonanesthetic ⠝⠕⠝⠁⠝⠑⠎⠮⠞⠊⠉
rule trans nonanesthetized ⠝⠕⠝⠁⠝⠑⠎⠮⠞⠊⠵⠫
rule trans nonsynesthetic ⠝⠕⠝⠎⠽⠝⠑⠎⠮⠞⠊⠉
rule trans normothermia ⠝⠕⠗⠍⠕⠮⠗⠍⠊⠁
rule trans normothermic ⠝⠕⠗⠍⠕⠮⠗⠍⠊⠉
rule trans northeast 1345-135-1235-1456-2-34
rule trans northesk ⠝⠕⠗⠹⠑⠎⠅
rule trans nuthook ⠝⠥⠞⠓⠕⠕⠅
rule trans nuthooks ⠝⠥⠞⠓⠕⠕⠅⠎
rule trans nuthouse ⠝⠥⠞⠓⠳⠎⠑
rule trans nuthouse's ⠝⠥⠞⠓⠳⠎⠑⠄⠎
rule trans nuthouses ⠝⠥⠞⠓⠳⠎⠑⠎
rule trans oasthouse ⠕⠁⠌⠓⠳⠎⠑
rule trans oasthouse's ⠕⠁⠌⠓⠳⠎⠑⠄⠎
rule trans oasthouses ⠕⠁⠌⠓⠳⠎⠑⠎
rule trans ophthalmothermometer ⠕⠏⠓⠹⠁⠇⠍⠕⠮⠗⠍⠕⠍⠑⠞⠻
rule trans ophthalmothermometers ⠕⠏⠓⠹⠁⠇⠍⠕⠮⠗⠍⠕⠍⠑⠞⠻⠎
rule trans osmotherapy ⠕⠎⠍⠕⠮⠗⠁⠏⠽
rule trans pallanesthesia ⠏⠁⠇⠇⠁⠝⠑⠎⠮⠎⠊⠁
rule trans pallesthesia ⠏⠁⠇⠇⠑⠎⠮⠎⠊⠁
rule trans palmesthesia ⠏⠁⠇⠍⠑⠎⠮⠎⠊⠁
rule trans panaesthesia ⠏⠁⠝⠁⠑⠎⠮⠎⠊⠁
rule trans panaesthetic ⠏⠁⠝⠁⠑⠎⠮⠞⠊⠉
rule trans panesthesia ⠏⠁⠝⠑⠎⠮⠎⠊⠁
rule trans panesthetic ⠏⠁⠝⠑⠎⠮⠞⠊⠉
rule trans paraesthesia ⠏⠜⠁⠑⠎⠮⠎⠊⠁
rule trans paraesthetic ⠏⠜⠁⠑⠎⠮⠞⠊⠉
rule trans paresthesia ⠏⠜⠑⠎⠮⠎⠊⠁
rule trans paresthesis ⠏⠜⠑⠎⠮⠎⠊⠎
rule trans paresthetic ⠏⠜⠑⠎⠮⠞⠊⠉
rule trans pesthouse ⠏⠑⠌⠓⠳⠎⠑
rule trans pesthouse's ⠏⠑⠌⠓⠳⠎⠑⠄⠎
rule trans pesthouses ⠏⠑⠌⠓⠳⠎⠑⠎
rule trans photaesthesia ⠏⠓⠕⠞⠁⠑⠎⠮⠎⠊⠁
rule trans photaesthesis ⠏⠓⠕⠞⠁⠑⠎⠮⠎⠊⠎
rule trans photaesthetic ⠏⠓⠕⠞⠁⠑⠎⠮⠞⠊⠉
rule trans photesthesis ⠏⠓⠕⠞⠑⠎⠮⠎⠊⠎
rule trans photoaesthetic ⠏⠓⠕⠞⠕⠁⠑⠎⠮⠞⠊⠉
rule trans photoesthesis ⠏⠓⠕⠞⠕⠑⠎⠮⠎⠊⠎
rule trans photoesthetic ⠏⠓⠕⠞⠕⠑⠎⠮⠞⠊⠉
rule trans pneumotherapeutic ⠏⠝⠑⠥⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉
rule trans pneumotherapeutics ⠏⠝⠑⠥⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉⠎
rule trans pneumotherapies ⠏⠝⠑⠥⠍⠕⠮⠗⠁⠏⠊⠑⠎
rule trans pneumotherapy ⠏⠝⠑⠥⠍⠕⠮⠗⠁⠏⠽
rule trans poethood ⠏⠕⠑⠞⠓⠕⠕⠙
rule trans polyesthesia ⠏⠕⠇⠽⠑⠎⠮⠎⠊⠁
rule trans polyesthetic ⠏⠕⠇⠽⠑⠎⠮⠞⠊⠉
rule trans porthook ⠏⠕⠗⠞⠓⠕⠕⠅
rule trans porthook's ⠏⠕⠗⠞⠓⠕⠕⠅⠄⠎
rule trans porthooks ⠏⠕⠗⠞⠓⠕⠕⠅⠎
rule trans porthouse ⠏⠕⠗⠞⠓⠳⠎⠑
rule trans porthouse's ⠏⠕⠗⠞⠓⠳⠎⠑⠄⠎
rule trans porthouses ⠏⠕⠗⠞⠓⠳⠎⠑⠎
rule trans postanaesthetic ⠏⠕⠌⠁⠝⠁⠑⠎⠮⠞⠊⠉
rule trans posthouse ⠏⠕⠌⠓⠳⠎⠑
rule trans posthouse's ⠏⠕⠌⠓⠳⠎⠑⠄⠎
rule trans posthouses ⠏⠕⠌⠓⠳⠎⠑⠎
rule trans pothat ⠏⠕⠞⠓⠁⠞
rule trans pothat's ⠏⠕⠞⠓⠁⠞⠄⠎
rule trans pothats ⠏⠕⠞⠓⠁⠞⠎
rule trans potherb ⠏⠕⠞⠓⠻⠃
rule trans potherb's ⠏⠕⠞⠓⠻⠃⠄⠎
rule trans potherbs ⠏⠕⠞⠓⠻⠃⠎
rule trans pothouse ⠏⠕⠞⠓⠳⠎⠑
rule trans pothouse's ⠏⠕⠞⠓⠳⠎⠑⠄⠎
rule trans pothouses ⠏⠕⠞⠓⠳⠎⠑⠎
rule trans pothunter ⠏⠕⠞⠓⠥⠝⠞⠻
rule trans pothunter's ⠏⠕⠞⠓⠥⠝⠞⠻⠄⠎
rule trans pothunters ⠏⠕⠞⠓⠥⠝⠞⠻⠎
rule trans proaesthetic ⠏⠗⠕⠁⠑⠎⠮⠞⠊⠉
rule trans prophethood ⠏⠗⠕⠏⠓⠑⠞⠓⠕⠕⠙
rule trans prostheses 1234-1235-135-234-2346-234-15-234
rule trans prosthesis 1234-1235-135-234-2346-234-24-234
rule trans prosthetic 1234-1235-135-234-2346-2345-24-14
rule trans psammotherapy ⠏⠎⠁⠍⠍⠕⠮⠗⠁⠏⠽
rule trans pseudesthesia ⠏⠎⠑⠥⠙⠑⠎⠮⠎⠊⠁
rule trans pseudoaesthetic ⠏⠎⠑⠥⠙⠕⠁⠑⠎⠮⠞⠊⠉
rule trans pseudoaesthetically ⠏⠎⠑⠥⠙⠕⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans pseudofaithful ⠏⠎⠑⠥⠙⠕⠋⠁⠊⠹⠰⠇
rule trans pseudofatherly ⠏⠎⠑⠥⠙⠕⠐⠋⠇⠽
rule trans psychesthesia ⠏⠎⠽⠡⠑⠎⠮⠎⠊⠁
rule trans psychesthetic ⠏⠎⠽⠡⠑⠎⠮⠞⠊⠉
rule trans questhouse ⠟⠥⠑⠌⠓⠳⠎⠑
rule trans questhouse's ⠟⠥⠑⠌⠓⠳⠎⠑⠄⠎
rule trans questhouses ⠟⠥⠑⠌⠓⠳⠎⠑⠎
rule trans rathole ⠗⠁⠞⠓⠕⠇⠑
rule trans rathole's ⠗⠁⠞⠓⠕⠇⠑⠄⠎
rule trans ratholes ⠗⠁⠞⠓⠕⠇⠑⠎
rule trans resthouse ⠗⠑⠌⠓⠳⠎⠑
rule trans resthouse's ⠗⠑⠌⠓⠳⠎⠑⠄⠎
rule trans resthouses ⠗⠑⠌⠓⠳⠎⠑⠎
rule trans righthand ⠐⠗⠓⠯
rule trans roothold ⠗⠕⠕⠞⠓⠕⠇⠙
rule trans rootholds ⠗⠕⠕⠞⠓⠕⠇⠙⠎
rule trans salthouse ⠎⠁⠇⠞⠓⠳⠎⠑
rule trans salthouse's ⠎⠁⠇⠞⠓⠳⠎⠑⠄⠎
rule trans salthouses ⠎⠁⠇⠞⠓⠳⠎⠑⠎
rule trans samothere ⠎⠁⠍⠕⠮⠗⠑
rule trans samotherium ⠎⠁⠍⠕⠮⠗⠊⠥⠍
rule trans seismotherapy ⠎⠑⠊⠎⠍⠕⠮⠗⠁⠏⠽
rule trans semianaesthetic ⠎⠑⠍⠊⠁⠝⠁⠑⠎⠮⠞⠊⠉
rule trans semianesthetic ⠎⠑⠍⠊⠁⠝⠑⠎⠮⠞⠊⠉
rule trans sighthole ⠎⠊⠣⠞⠓⠕⠇⠑
rule trans sighthole's ⠎⠊⠣⠞⠓⠕⠇⠑⠄⠎
rule trans sightholes ⠎⠊⠣⠞⠓⠕⠇⠑⠎
rule trans slothound ⠎⠇⠕⠞⠓⠨⠙
rule trans softhearted 234-12356-2345-125-15-345-2345-1246
rule trans sontheim 234-135-1345-2345-125-15-24-134
rule trans sontheim ⠎⠕⠝⠞⠓⠑⠊⠍
rule trans sontheimer 234-135-1345-2345-125-15-24-134-12456
rule trans sontheimer ⠎⠕⠝⠞⠓⠑⠊⠍⠻
rule trans soothill ⠎⠕⠕⠞⠓⠊⠇⠇
rule trans soothill's ⠎⠕⠕⠞⠓⠊⠇⠇⠄⠎
rule trans soothills ⠎⠕⠕⠞⠓⠊⠇⠇⠎
rule trans southeast 234-1256-1456-2-34
rule trans southend 234-1256-1456-26-145
rule trans southend ⠎⠳⠹⠢⠙
rule trans southesk ⠎⠳⠹⠑⠎⠅
rule trans studenthood ⠌⠥⠙⠢⠞⠓⠕⠕⠙
rule trans suithold ⠎⠥⠊⠞⠓⠕⠇⠙
rule trans suitholds ⠎⠥⠊⠞⠓⠕⠇⠙⠎
rule trans sulfonmethane ⠎⠥⠇⠋⠕⠝⠍⠑⠹⠁⠝⠑
rule trans sulphonmethane ⠎⠥⠇⠏⠓⠕⠝⠍⠑⠹⠁⠝⠑
rule trans superaesthetic ⠎⠥⠏⠻⠁⠑⠎⠮⠞⠊⠉
rule trans superaesthetically ⠎⠥⠏⠻⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans sweetheart 234-2456-15-15-2345-125-15-345-2345
rule trans synaesthesia ⠎⠽⠝⠁⠑⠎⠮⠎⠊⠁
rule trans synaesthesis ⠎⠽⠝⠁⠑⠎⠮⠎⠊⠎
rule trans synaesthetic ⠎⠽⠝⠁⠑⠎⠮⠞⠊⠉
rule trans synesthesia ⠎⠽⠝⠑⠎⠮⠎⠊⠁
rule trans synesthetic ⠎⠽⠝⠑⠎⠮⠞⠊⠉
rule trans telaesthesia ⠞⠑⠇⠁⠑⠎⠮⠎⠊⠁
rule trans telaesthetic ⠞⠑⠇⠁⠑⠎⠮⠞⠊⠉
rule trans telesthesia ⠞⠑⠇⠑⠎⠮⠎⠊⠁
rule trans telesthetic ⠞⠑⠇⠑⠎⠮⠞⠊⠉
rule trans thence 1456-56-15
rule trans thermaesthesia ⠮⠗⠍⠁⠑⠎⠮⠎⠊⠁
rule trans thermanesthesia ⠮⠗⠍⠁⠝⠑⠎⠮⠎⠊⠁
rule trans thermesthesia ⠮⠗⠍⠑⠎⠮⠎⠊⠁
rule trans thermoanesthesia ⠮⠗⠍⠕⠁⠝⠑⠎⠮⠎⠊⠁
rule trans thermoesthesia ⠮⠗⠍⠕⠑⠎⠮⠎⠊⠁
rule trans thermoform ⠮⠗⠍⠕⠿⠍
rule trans thermoform's ⠮⠗⠍⠕⠿⠍⠄⠎
rule trans thermoformed ⠮⠗⠍⠕⠿⠍⠫
rule trans thermoforming ⠮⠗⠍⠕⠿⠍⠬
rule trans thermoforms ⠮⠗⠍⠕⠿⠍⠎
rule trans thermotherapies ⠮⠗⠍⠕⠮⠗⠁⠏⠊⠑⠎
rule trans thermotherapy ⠮⠗⠍⠕⠮⠗⠁⠏⠽
rule trans thermotherapy's ⠮⠗⠍⠕⠮⠗⠁⠏⠽⠄⠎
rule trans thessaloníki ⠮⠎⠎⠁⠇⠕⠝⠘⠌⠊⠅⠊
rule trans thiever ⠹⠊⠑⠧⠻
rule trans thievers ⠹⠊⠑⠧⠻⠎
rule trans threedimensional ⠹⠗⠑⠑⠙⠊⠍⠢⠨⠝⠁⠇
rule trans tothill ⠞⠕⠞⠓⠊⠇⠇
rule trans tothill's ⠞⠕⠞⠓⠊⠇⠇⠄⠎
rule trans unaesthetic ⠥⠝⠁⠑⠎⠮⠞⠊⠉
rule trans unaesthetically ⠥⠝⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans unesthetic ⠥⠝⠑⠎⠮⠞⠊⠉
rule trans unphilanthropic ⠥⠝⠏⠓⠊⠇⠁⠝⠹⠗⠕⠏⠊⠉
rule trans unphilanthropically ⠥⠝⠏⠓⠊⠇⠁⠝⠹⠗⠕⠏⠊⠉⠁⠇⠇⠽
rule trans unrhythmic ⠥⠝⠗⠓⠽⠹⠍⠊⠉
rule trans unrhythmical ⠥⠝⠗⠓⠽⠹⠍⠊⠉⠁⠇
rule trans unrhythmically ⠥⠝⠗⠓⠽⠹⠍⠊⠉⠁⠇⠇⠽
rule trans venthole ⠧⠢⠞⠓⠕⠇⠑
rule trans venthole's ⠧⠢⠞⠓⠕⠇⠑⠄⠎
rule trans ventholes ⠧⠢⠞⠓⠕⠇⠑⠎
rule trans visuokinesthetic ⠧⠊⠎⠥⠕⠅⠔⠑⠎⠮⠞⠊⠉
rule trans wertheim ⠺⠻⠞⠓⠑⠊⠍
rule trans zomotherapy ⠵⠕⠍⠕⠮⠗⠁⠏⠽


uses word_end_+ word_end_- rule trans rtheim ⠗⠞⠓⠑⠊⠍

## with
uses - - rule trans with 23456

use


########################################
#   10.4   Strong Groupsigns
########################################

use word_whole_begin_+ word_whole_begin_-

## ar
uses - - rule trans ar 345

rule trans aright 1-5-1235
#rule trans flearidden 124-123-15-1-1235-24-145-145-26   fywk
rule trans indiarubber 35-145-24-1-1235-136-23-12456   fywk
rule trans infrared 35-124-1235-1-1235-1246
rule trans tearoom 2345-2-1235-135-135-134

## ch   10.4.2   ⠘⠡grave   ⠈⠡solidus
uses word_whole_+ word_whole_- rule trans ch 14-125
uses - not_modifier_4_45_- rule trans ch 16

rule trans overreact 135-1236-12456-1235-15-1-14-2345
rule trans overreaction 135-1236-12456-1235-15-1-14-56-1345
rule trans react 1235-15-1-14-2345
rule trans reaction 1235-15-1-14-56-1345


## ed   ⠘⠫ring
uses not_modifier_<+ not_modifier_45_- rule trans ed 1246

rule trans airedale 1-24-1235-15-145-1-123-15
rule trans appledore ⠁⠏⠏⠇⠑⠙⠕⠗⠑
rule trans basedow ⠃⠁⠎⠑⠙⠪
rule trans battledore ⠃⠁⠞⠞⠇⠑⠙⠕⠗⠑
rule trans battledores ⠃⠁⠞⠞⠇⠑⠙⠕⠗⠑⠎
rule trans blythedale ⠃⠇⠽⠮⠙⠁⠇⠑
rule trans blythedale's ⠃⠇⠽⠮⠙⠁⠇⠑⠄⠎
rule trans byrnedale ⠃⠽⠗⠝⠑⠙⠁⠇⠑
rule trans castledale ⠉⠁⠌⠇⠑⠙⠁⠇⠑
rule trans clarkedale ⠉⠇⠜⠅⠑⠙⠁⠇⠑
rule trans clarkedale's ⠉⠇⠜⠅⠑⠙⠁⠇⠑⠄⠎
rule trans cliveden ⠉⠇⠊⠧⠑⠙⠢
rule trans closedown ⠉⠇⠕⠎⠑⠙⠪⠝
rule trans codenamed ⠉⠕⠙⠑⠐⠝⠙
rule trans cofinanced ⠉⠕⠋⠔⠨⠑⠙
rule trans cokedale ⠉⠕⠅⠑⠙⠁⠇⠑
rule trans cokedale's ⠉⠕⠅⠑⠙⠁⠇⠑⠄⠎
rule trans comedown 14-135-134-15-145-246-1345
rule trans corriedale ⠉⠕⠗⠗⠊⠑⠙⠁⠇⠑
rule trans corriedale's ⠉⠕⠗⠗⠊⠑⠙⠁⠇⠑⠄⠎
rule trans daredevil 145-345-15-145-15-1236-24-123
rule trans denamed ⠙⠑⠐⠝⠙
rule trans doubleday 145-1256-12-123-15-5-145
rule trans dumbledore 145-136-134-12-123-15-145-135-1235-15
rule trans eyedrop ⠑⠽⠑⠙⠗⠕⠏
rule trans eyedrop's ⠑⠽⠑⠙⠗⠕⠏⠄⠎
rule trans eyedropper ⠑⠽⠑⠙⠗⠕⠏⠏⠻
rule trans eyedropper's ⠑⠽⠑⠙⠗⠕⠏⠏⠻⠄⠎
rule trans eyedroppers ⠑⠽⠑⠙⠗⠕⠏⠏⠻⠎
rule trans eyedrops ⠑⠽⠑⠙⠗⠕⠏⠎
rule trans facedown ⠋⠁⠉⠑⠙⠪⠝
rule trans gravedigger ⠛⠗⠁⠧⠑⠙⠊⠶⠻
rule trans gravedigger's ⠛⠗⠁⠧⠑⠙⠊⠶⠻⠄⠎
rule trans gravediggers ⠛⠗⠁⠧⠑⠙⠊⠶⠻⠎
rule trans gwynedd ⠛⠺⠽⠝⠑⠙⠙
rule trans gwynedd's ⠛⠺⠽⠝⠑⠙⠙⠄⠎
rule trans hoedown 125-135-15-145-246-1345
rule trans homedale ⠓⠕⠍⠑⠙⠁⠇⠑
rule trans hopedale ⠓⠕⠏⠑⠙⠁⠇⠑
rule trans housedress ⠓⠳⠎⠑⠙⠗⠑⠎⠎
rule trans housedresses ⠓⠳⠎⠑⠙⠗⠑⠎⠎⠑⠎
rule trans idledale ⠊⠙⠇⠑⠙⠁⠇⠑
rule trans ingledew ⠔⠛⠇⠑⠙⠑⠺
rule trans ingledew's ⠔⠛⠇⠑⠙⠑⠺⠄⠎
rule trans ingledews ⠔⠛⠇⠑⠙⠑⠺⠎
rule trans junedale ⠚⠥⠝⠑⠙⠁⠇⠑
rule trans kettledrum 13-15-2345-2345-123-15-145-1235-136-134
rule trans knuckleduster ⠅⠝⠥⠉⠅⠇⠑⠙⠥⠌⠻
rule trans knuckleduster's ⠅⠝⠥⠉⠅⠇⠑⠙⠥⠌⠻⠄⠎
rule trans knuckledusters ⠅⠝⠥⠉⠅⠇⠑⠙⠥⠌⠻⠎
rule trans languedoc ⠇⠁⠝⠛⠥⠑⠙⠕⠉
rule trans nosedive 1345-135-234-15-145-24-1236-15
rule trans nosedived 1345-135-234-15-145-24-1236-1246
rule trans nosediving 1345-135-234-15-145-24-1236-346
rule trans nosedove ⠝⠕⠎⠑⠙⠕⠧⠑
rule trans pagedale ⠏⠁⠛⠑⠙⠁⠇⠑
rule trans piedish ⠏⠊⠑⠙⠊⠩
rule trans piedish's ⠏⠊⠑⠙⠊⠩⠄⠎
rule trans piedishes ⠏⠊⠑⠙⠊⠩⠑⠎
rule trans pinedale ⠏⠔⠑⠙⠁⠇⠑
rule trans pinedrops ⠏⠔⠑⠙⠗⠕⠏⠎
rule trans pricedale ⠏⠗⠊⠉⠑⠙⠁⠇⠑
rule trans priedieu ⠏⠗⠊⠑⠙⠊⠑⠥
rule trans redevelop ⠗⠫⠑⠧⠑⠇⠕⠏
rule trans ridgedale ⠗⠊⠙⠛⠑⠙⠁⠇⠑
rule trans rosedale ⠗⠕⠎⠑⠙⠁⠇⠑
rule trans rosedrop ⠗⠕⠎⠑⠙⠗⠕⠏
rule trans rosedrops ⠗⠕⠎⠑⠙⠗⠕⠏⠎
rule trans shakedown 146-1-13-15-145-246-1345
rule trans shoreditch ⠩⠕⠗⠑⠙⠊⠞⠡
rule trans shoreditch's ⠩⠕⠗⠑⠙⠊⠞⠡⠄⠎
rule trans slatedale ⠎⠇⠁⠞⠑⠙⠁⠇⠑
rule trans swaledale ⠎⠺⠁⠇⠑⠙⠁⠇⠑
rule trans takedown ⠞⠁⠅⠑⠙⠪⠝
rule trans takedownable ⠞⠁⠅⠑⠙⠪⠝⠁⠃⠇⠑
rule trans takedowns ⠞⠁⠅⠑⠙⠪⠝⠎
rule trans thistledown 1456-24-34-123-15-145-246-1345
rule trans threedimensional ⠹⠗⠑⠑⠙⠊⠍⠢⠨⠝⠁⠇
rule trans tumbledown 2345-136-134-12-123-15-145-246-1345
rule trans turtledove 2345-136-1235-2345-123-15-145-135-1236-15
rule trans tweedledee 2345-2456-15-1246-123-15-145-15-15
rule trans tweedledum 2345-2456-15-1246-123-15-145-136-134
rule trans undervinedresser ⠐⠥⠧⠔⠑⠙⠗⠑⠎⠎⠻
rule trans undervinedressers ⠐⠥⠧⠔⠑⠙⠗⠑⠎⠎⠻⠎
rule trans unperceived ⠥⠝⠏⠻⠉⠧⠙
rule trans upsidedown ⠥⠏⠎⠊⠙⠑⠙⠪⠝
rule trans viced ⠧⠊⠉⠫
rule trans vinedresser ⠧⠔⠑⠙⠗⠑⠎⠎⠻
rule trans vinedresser's ⠧⠔⠑⠙⠗⠑⠎⠎⠻⠄⠎
rule trans vinedressers ⠧⠔⠑⠙⠗⠑⠎⠎⠻⠎
rule trans wharfedale ⠱⠜⠋⠑⠙⠁⠇⠑
rule trans wharfedale's ⠱⠜⠋⠑⠙⠁⠇⠑⠄⠎
rule trans wharfedales ⠱⠜⠋⠑⠙⠁⠇⠑⠎


## er   ⠘⠻tilde
uses not_modifier_<+ not_modifier_45_- rule trans er 12456

rule trans castlereagh 14-1-34-123-15-1235-2-126
rule trans hedgerow 125-1246-1245-15-1235-246
rule trans homeroom 125-135-134-15-1235-135-135-134
rule trans horseradish 125-135-1235-234-15-1235-1-145-24-146
rule trans spareribs 234-1234-345-15-1235-24-12-234
rule trans stateroom 34-1-2345-15-1235-135-135-134
rule trans storeroom 34-135-1235-15-1235-135-135-134
rule trans viceregal 1236-24-14-15-1235-15-1245-1-123
rule trans viceroy 1236-24-14-15-1235-135-13456

## gh
uses - - rule trans gh 126

rule trans alilonghi ⠁⠇⠊⠇⠕⠝⠣⠊
rule trans bergholt ⠃⠻⠛⠓⠕⠇⠞
rule trans bergholt ⠃⠻⠛⠓⠕⠇⠞
rule trans bergholt's ⠃⠻⠛⠓⠕⠇⠞⠄⠎
rule trans bergholt's ⠃⠻⠛⠓⠕⠇⠞⠄⠎
rule trans bergholz ⠃⠻⠛⠓⠕⠇⠵
rule trans bergholz ⠃⠻⠛⠓⠕⠇⠵
rule trans bighead ⠃⠊⠛⠓⠂⠙
rule trans bigheaded ⠃⠊⠛⠓⠂⠙⠫
rule trans bigheads ⠃⠊⠛⠓⠂⠙⠎
rule trans bighearted 12-24-1245-125-15-345-2345-1246
rule trans bighorn 12-24-1245-125-135-1235-1345
rule trans brighouse ⠃⠗⠊⠛⠓⠳⠎⠑
rule trans brighouse ⠃⠗⠊⠛⠓⠳⠎⠑
rule trans bughouse ⠃⠥⠛⠓⠳⠎⠑
rule trans bughouse ⠃⠥⠛⠓⠳⠎⠑
rule trans bunghole 12-136-1345-1245-125-135-123-15
rule trans cleghorn ⠉⠇⠑⠛⠓⠕⠗⠝
rule trans cleghorn ⠉⠇⠑⠛⠓⠕⠗⠝
rule trans cofighter ⠉⠕⠋⠊⠣⠞⠻
rule trans cofighters ⠉⠕⠋⠊⠣⠞⠻⠎
rule trans coghill ⠉⠕⠛⠓⠊⠇⠇
rule trans coghill ⠉⠕⠛⠓⠊⠇⠇
rule trans coghill's ⠉⠕⠛⠓⠊⠇⠇⠄⠎
rule trans coghill's ⠉⠕⠛⠓⠊⠇⠇⠄⠎
rule trans cunnyngham 14-136-1345-1345-13456-1345-1245-125-1-134
rule trans doghead ⠙⠕⠛⠓⠂⠙
rule trans doghouse 145-135-1245-125-1256-234-15
rule trans draghound ⠙⠗⠁⠛⠓⠨⠙
rule trans draghound ⠙⠗⠁⠛⠓⠨⠙
rule trans draghounds ⠙⠗⠁⠛⠓⠨⠙⠎
rule trans draghounds ⠙⠗⠁⠛⠓⠨⠙⠎
rule trans draught ⠙⠗⠁⠥⠣⠞
rule trans draught's ⠙⠗⠁⠥⠣⠞⠄⠎
rule trans draughtboard ⠙⠗⠁⠥⠣⠞⠃⠕⠜⠙
rule trans draughtboard's ⠙⠗⠁⠥⠣⠞⠃⠕⠜⠙⠄⠎
rule trans draughtboards ⠙⠗⠁⠥⠣⠞⠃⠕⠜⠙⠎
rule trans draughthouse ⠙⠗⠁⠥⠣⠞⠓⠳⠎⠑
rule trans draughthouse's ⠙⠗⠁⠥⠣⠞⠓⠳⠎⠑⠄⠎
rule trans draughthouses ⠙⠗⠁⠥⠣⠞⠓⠳⠎⠑⠎
rule trans draughts ⠙⠗⠁⠥⠣⠞⠎
rule trans draughty ⠙⠗⠁⠥⠣⠞⠽
rule trans dungheap ⠙⠥⠝⠛⠓⠂⠏
rule trans dungheaps ⠙⠥⠝⠛⠓⠂⠏⠎
rule trans dunghill ⠙⠥⠝⠛⠓⠊⠇⠇
rule trans dunghill ⠙⠥⠝⠛⠓⠊⠇⠇
rule trans dunghills ⠙⠥⠝⠛⠓⠊⠇⠇⠎
rule trans dunghills ⠙⠥⠝⠛⠓⠊⠇⠇⠎
rule trans foghorn 124-135-1245-125-135-1235-1345
rule trans froghop ⠋⠗⠕⠛⠓⠕⠏
rule trans froghop ⠋⠗⠕⠛⠓⠕⠏
rule trans froghopped ⠋⠗⠕⠛⠓⠕⠏⠏⠫
rule trans froghopped ⠋⠗⠕⠛⠓⠕⠏⠏⠫
rule trans froghopping ⠋⠗⠕⠛⠓⠕⠏⠏⠬
rule trans froghopping ⠋⠗⠕⠛⠓⠕⠏⠏⠬
rule trans froghops ⠋⠗⠕⠛⠓⠕⠏⠎
rule trans froghops ⠋⠗⠕⠛⠓⠕⠏⠎
rule trans gastight ⠛⠁⠎⠞⠊⠣⠞
rule trans ghillie ⠣⠊⠇⠇⠊⠑
rule trans ghillies ⠣⠊⠇⠇⠊⠑⠎
rule trans havighurst ⠓⠁⠧⠊⠛⠓⠥⠗⠌
rule trans havighurst ⠓⠁⠧⠊⠛⠓⠥⠗⠌
rule trans heretogh ⠓⠻⠑⠞⠕⠣
rule trans heretoghs ⠓⠻⠑⠞⠕⠣⠎
rule trans hwangho ⠓⠺⠁⠝⠛⠓⠕
rule trans hwangho ⠓⠺⠁⠝⠛⠓⠕
rule trans ingham ⠔⠣⠁⠍
rule trans jughead ⠚⠥⠛⠓⠂⠙
rule trans jugheads ⠚⠥⠛⠓⠂⠙⠎
rule trans kinghorn ⠅⠬⠓⠕⠗⠝
rule trans kinghorn ⠅⠬⠓⠕⠗⠝
rule trans kinghorn's ⠅⠬⠓⠕⠗⠝⠄⠎
rule trans kinghorn's ⠅⠬⠓⠕⠗⠝⠄⠎
rule trans knight's ⠅⠝⠊⠣⠞⠄⠎
rule trans langhaire ⠇⠁⠝⠛⠓⠁⠊⠗⠑
rule trans leghorn ⠇⠑⠛⠓⠕⠗⠝
rule trans longhi ⠇⠕⠝⠣⠊
rule trans longhi's ⠇⠕⠝⠣⠊⠄⠎
rule trans mesolonghi ⠍⠑⠎⠕⠇⠕⠝⠣⠊
rule trans missolonghi ⠍⠊⠎⠎⠕⠇⠕⠝⠣⠊
rule trans missolonghi's ⠍⠊⠎⠎⠕⠇⠕⠝⠣⠊⠄⠎
rule trans mughouse ⠍⠥⠛⠓⠳⠎⠑
rule trans mughouse ⠍⠥⠛⠓⠳⠎⠑
rule trans mughouses ⠍⠥⠛⠓⠳⠎⠑⠎
rule trans mughouses ⠍⠥⠛⠓⠳⠎⠑⠎
rule trans pigheaded 1234-24-1245-125-2-145-1246
rule trans ploughtail ⠏⠇⠳⠣⠞⠁⠊⠇
rule trans ploughtails ⠏⠇⠳⠣⠞⠁⠊⠇⠎
rule trans plughole ⠏⠇⠥⠛⠓⠕⠇⠑
rule trans plughole ⠏⠇⠥⠛⠓⠕⠇⠑
rule trans plughole's ⠏⠇⠥⠛⠓⠕⠇⠑⠄⠎
rule trans plughole's ⠏⠇⠥⠛⠓⠕⠇⠑⠄⠎
rule trans plugholes ⠏⠇⠥⠛⠓⠕⠇⠑⠎
rule trans plugholes ⠏⠇⠥⠛⠓⠕⠇⠑⠎
rule trans righthand ⠐⠗⠓⠯
rule trans righthand ⠐⠗⠓⠯
rule trans rightheaded ⠐⠗⠓⠂⠙⠫
rule trans roughtail ⠗⠳⠣⠞⠁⠊⠇
rule trans roughtail's ⠗⠳⠣⠞⠁⠊⠇⠄⠎
rule trans roughtailed ⠗⠳⠣⠞⠁⠊⠇⠫
rule trans roughtails ⠗⠳⠣⠞⠁⠊⠇⠎
rule trans senghor 234-26-1245-125-135-1235
rule trans shanghai 146-1-1345-1245-125-1-24
rule trans sighthole ⠎⠊⠣⠞⠓⠕⠇⠑
rule trans sighthole's ⠎⠊⠣⠞⠓⠕⠇⠑⠄⠎
rule trans sightholes ⠎⠊⠣⠞⠓⠕⠇⠑⠎
rule trans slagheap ⠎⠇⠁⠛⠓⠂⠏
rule trans songhai 234-135-1345-126-1-24
rule trans staghead ⠌⠁⠛⠓⠂⠙
rule trans stagheads ⠌⠁⠛⠓⠂⠙⠎
rule trans staghorn ⠌⠁⠛⠓⠕⠗⠝
rule trans staghorn ⠌⠁⠛⠓⠕⠗⠝
rule trans staghorns ⠌⠁⠛⠓⠕⠗⠝⠎
rule trans staghorns ⠌⠁⠛⠓⠕⠗⠝⠎
rule trans staghound ⠌⠁⠛⠓⠨⠙
rule trans staghound ⠌⠁⠛⠓⠨⠙
rule trans staghounds ⠌⠁⠛⠓⠨⠙⠎
rule trans staghounds ⠌⠁⠛⠓⠨⠙⠎
rule trans unright ⠥⠝⠐⠗
rule trans unright ⠥⠝⠐⠗
rule trans unrightable ⠥⠝⠐⠗⠁⠃⠇⠑
rule trans unrightable ⠥⠝⠐⠗⠁⠃⠇⠑
rule trans unrighted ⠥⠝⠐⠗⠫
rule trans unrighted ⠥⠝⠐⠗⠫
rule trans unrighteous ⠥⠝⠐⠗⠑⠳⠎
rule trans unrighteous ⠥⠝⠐⠗⠑⠳⠎
rule trans unrighteously ⠥⠝⠐⠗⠑⠳⠎⠇⠽
rule trans unrighteously ⠥⠝⠐⠗⠑⠳⠎⠇⠽
rule trans unrighteousness ⠥⠝⠐⠗⠑⠳⠎⠰⠎
rule trans unrighteousness ⠥⠝⠐⠗⠑⠳⠎⠰⠎
#rule trans yoghourt 13456-135-1245-125-1256-1235-2345
rule trans yoghourt ⠽⠕⠣⠳⠗⠞


## ing   ⠈⠬breve   ⠘⠬caron
uses - not_modifier_4_45_- match trans %a@[SEQ_<+]* ing -   = 346 =

rule trans disingenuous 256-35-1245-26-136-1256-234
rule trans leningrad 123-26-35-1245-1235-1-145
rule trans stalingrad 34-1-123-35-1245-1235-1-145
rule trans vainglorious 1236-1-35-1245-123-135-1235-24-1256-234
rule trans vainglory 1236-1-35-1245-123-135-1235-13456

## ou   10.4.2
uses word_whole_+ word_whole_- rule trans ou 135-136
uses - - rule trans ou 1256

uses word_whole_+ word_whole_- rule trans prounion 1234-1235-135-136-1345-24-135-1345

## ow
uses - - rule trans ow 246

rule trans autoworker 1-136-2345-135-5-2456-12456
rule trans coforeknow ⠉⠕⠿⠑⠐⠅
rule trans coworker 14-135-5-2456-12456
rule trans kilowatt 13-24-123-135-2456-1-2345-2345
rule trans kiloword ⠅⠊⠇⠕⠘⠺
rule trans locoweed 123-135-14-135-2456-15-1246
rule trans microwatt ⠍⠊⠉⠗⠕⠺⠁⠞⠞
rule trans microword ⠍⠊⠉⠗⠕⠘⠺
rule trans monowheel 134-135-1345-135-156-15-15-123
rule trans nanoword ⠝⠁⠝⠕⠘⠺
rule trans noway 1345-135-2456-1-13456
rule trans nowhere 1345-135-5-156
rule trans nowise 1345-135-2456-24-234-15
rule trans picowatt ⠏⠊⠉⠕⠺⠁⠞⠞


## sh   10.4.2   ⠘⠩circumflex
uses word_whole_+ word_whole_- rule trans sh 234-125
uses - not_modifier_45_- rule trans sh 146

rule trans almshouse ⠁⠇⠍⠎⠓⠳⠎⠑
rule trans almshouse's ⠁⠇⠍⠎⠓⠳⠎⠑⠄⠎
rule trans almshouses ⠁⠇⠍⠎⠓⠳⠎⠑⠎
rule trans asshole 1-234-234-125-135-123-15
rule trans betshanger ⠃⠑⠞⠎⠓⠁⠝⠛⠻
rule trans betshanger's ⠃⠑⠞⠎⠓⠁⠝⠛⠻⠄⠎
rule trans bosham ⠃⠕⠎⠓⠁⠍
rule trans chisholm 16-24-234-125-135-123-134
rule trans crailsheim ⠉⠗⠁⠊⠇⠎⠓⠑⠊⠍
rule trans crosshead ⠉⠗⠕⠎⠎⠓⠂⠙
rule trans crossheads ⠉⠗⠕⠎⠎⠓⠂⠙⠎
rule trans customshouse ⠉⠥⠌⠕⠍⠎⠓⠳⠎⠑
rule trans customshouses ⠉⠥⠌⠕⠍⠎⠓⠳⠎⠑⠎
rule trans dachshound ⠙⠁⠡⠎⠓⠨⠙
rule trans dachshound's ⠙⠁⠡⠎⠓⠨⠙⠄⠎
rule trans dachshounds ⠙⠁⠡⠎⠓⠨⠙⠎
rule trans dachshund 145-1-16-234-125-136-1345-145
rule trans deash ⠙⠑⠁⠩
rule trans deashed ⠙⠑⠁⠩⠫
rule trans deashes ⠙⠑⠁⠩⠑⠎
rule trans deashing ⠙⠑⠁⠩⠬
rule trans deidesheim ⠙⠑⠊⠙⠑⠎⠓⠑⠊⠍
rule trans demihogshead ⠙⠑⠍⠊⠓⠕⠛⠎⠓⠂⠙
rule trans demihogsheads ⠙⠑⠍⠊⠓⠕⠛⠎⠓⠂⠙⠎
rule trans deshabille 145-15-234-125-1-12-24-123-123-15
rule trans deshabille ⠙⠑⠎⠓⠁⠃⠊⠇⠇⠑
rule trans dishabille ⠲⠓⠁⠃⠊⠇⠇⠑
rule trans disherent ⠲⠓⠻⠢⠞
rule trans dishouse ⠲⠓⠳⠎⠑
rule trans dishoused ⠲⠓⠳⠎⠫
rule trans dishouses ⠲⠓⠳⠎⠑⠎
rule trans dishousing ⠲⠓⠳⠎⠬
rule trans dosshouse ⠙⠕⠎⠎⠓⠳⠎⠑
rule trans dosshouses ⠙⠕⠎⠎⠓⠳⠎⠑⠎
rule trans florsheim 124-123-135-1235-234-125-15-24-134
rule trans frederikshavn ⠋⠗⠫⠻⠊⠅⠎⠓⠁⠧⠝
rule trans gashouse ⠛⠁⠎⠓⠳⠎⠑
rule trans gashouses ⠛⠁⠎⠓⠳⠎⠑⠎
rule trans gateshead ⠛⠁⠞⠑⠎⠓⠂⠙
rule trans gateshead's ⠛⠁⠞⠑⠎⠓⠂⠙⠄⠎
rule trans gemshorn ⠛⠑⠍⠎⠓⠕⠗⠝
rule trans gemshorn ⠛⠑⠍⠎⠓⠕⠗⠝
rule trans gemshorns ⠛⠑⠍⠎⠓⠕⠗⠝⠎
rule trans glasshouse ⠛⠇⠁⠎⠎⠓⠳⠎⠑
rule trans glasshouse's ⠛⠇⠁⠎⠎⠓⠳⠎⠑⠄⠎
rule trans glasshouses ⠛⠇⠁⠎⠎⠓⠳⠎⠑⠎
rule trans goddesshood ⠛⠕⠙⠙⠑⠎⠎⠓⠕⠕⠙
rule trans goshawk ⠛⠕⠎⠓⠁⠺⠅
rule trans goshawks ⠛⠕⠎⠓⠁⠺⠅⠎
rule trans governesshood ⠛⠕⠧⠻⠰⠎⠓⠕⠕⠙
rule trans grasshopper 1245-1235-1-234-234-125-135-1234-1234-12456
rule trans grasshouse ⠛⠗⠁⠎⠎⠓⠳⠎⠑
rule trans grasshouses ⠛⠗⠁⠎⠎⠓⠳⠎⠑⠎
rule trans grimsholm ⠛⠗⠊⠍⠎⠓⠕⠇⠍
rule trans grimsholm's ⠛⠗⠊⠍⠎⠓⠕⠇⠍⠄⠎
rule trans hartshorn ⠓⠜⠞⠎⠓⠕⠗⠝
rule trans heiresshood ⠓⠑⠊⠗⠑⠎⠎⠓⠕⠕⠙
rule trans hergesheimer ⠓⠻⠛⠑⠎⠓⠑⠊⠍⠻
rule trans hergesheimers ⠓⠻⠛⠑⠎⠓⠑⠊⠍⠻⠎
rule trans hildesheim ⠓⠊⠇⠙⠑⠎⠓⠑⠊⠍
rule trans hogshead 125-135-1245-234-125-2-145
rule trans hollinshead ⠓⠕⠇⠇⠔⠎⠓⠂⠙
rule trans keeshond ⠅⠑⠑⠎⠓⠕⠝⠙
rule trans keeshonds ⠅⠑⠑⠎⠓⠕⠝⠙⠎
rule trans malesherbes ⠍⠁⠇⠑⠎⠓⠻⠃⠑⠎
rule trans malesherbia ⠍⠁⠇⠑⠎⠓⠻⠃⠊⠁
rule trans mansholt ⠍⠁⠝⠎⠓⠕⠇⠞
rule trans mishandle 134-24-234-125-12346-123-15
rule trans mishandled 134-24-234-125-12346-123-1246
rule trans mishandling 134-24-234-125-12346-123-346
rule trans mishap 134-24-234-125-1-1234
rule trans mishear 134-24-234-125-15-345
rule trans mishear ⠍⠊⠎⠓⠑⠜
rule trans misheard ⠍⠊⠎⠓⠑⠜⠙
rule trans mishearing ⠍⠊⠎⠓⠑⠜⠬
rule trans mishears ⠍⠊⠎⠓⠑⠜⠎
rule trans mishit ⠍⠊⠎⠓⠊⠞
rule trans mishits ⠍⠊⠎⠓⠊⠞⠎
rule trans mishitting ⠍⠊⠎⠓⠊⠞⠞⠬
rule trans misshood ⠍⠊⠎⠎⠓⠕⠕⠙
rule trans mistresshood ⠍⠊⠌⠗⠑⠎⠎⠓⠕⠕⠙
rule trans monkshood ⠍⠕⠝⠅⠎⠓⠕⠕⠙
rule trans mosheim ⠍⠕⠎⠓⠑⠊⠍
rule trans mosshead ⠍⠕⠎⠎⠓⠂⠙
rule trans mossheads ⠍⠕⠎⠎⠓⠂⠙⠎
rule trans nagshead ⠝⠁⠛⠎⠓⠂⠙
rule trans newshawk ⠝⠑⠺⠎⠓⠁⠺⠅
rule trans newshawks ⠝⠑⠺⠎⠓⠁⠺⠅⠎
rule trans newshen ⠝⠑⠺⠎⠓⠢
rule trans newshens ⠝⠑⠺⠎⠓⠢⠎
rule trans newshound ⠝⠑⠺⠎⠓⠨⠙
rule trans newshounds ⠝⠑⠺⠎⠓⠨⠙⠎
rule trans peakeshole ⠏⠂⠅⠑⠎⠓⠕⠇⠑
rule trans photoflash ⠏⠓⠕⠞⠕⠋⠇⠁⠩
rule trans photoflashes ⠏⠓⠕⠞⠕⠋⠇⠁⠩⠑⠎
rule trans piedish ⠏⠊⠑⠙⠊⠩
rule trans piedish's ⠏⠊⠑⠙⠊⠩⠄⠎
rule trans piedishes ⠏⠊⠑⠙⠊⠩⠑⠎
rule trans preaccomplished ⠏⠗⠑⠁⠒⠕⠍⠏⠇⠊⠩⠫
rule trans ramshorn ⠗⠁⠍⠎⠓⠕⠗⠝
rule trans ramshorn's ⠗⠁⠍⠎⠓⠕⠗⠝⠄⠎
rule trans ramshorns ⠗⠁⠍⠎⠓⠕⠗⠝⠎
rule trans reastonish ⠗⠑⠁⠌⠕⠝⠊⠩
rule trans reastonished ⠗⠑⠁⠌⠕⠝⠊⠩⠫
rule trans reastonishes ⠗⠑⠁⠌⠕⠝⠊⠩⠑⠎
rule trans reastonishing ⠗⠑⠁⠌⠕⠝⠊⠩⠬
rule trans rosmersholm ⠗⠕⠎⠍⠻⠎⠓⠕⠇⠍
rule trans rudesheim ⠗⠥⠙⠑⠎⠓⠑⠊⠍
rule trans rudesheimer ⠗⠥⠙⠑⠎⠓⠑⠊⠍⠻
rule trans severish ⠎⠑⠧⠻⠊⠩
rule trans shakespearean ⠩⠁⠅⠑⠎⠏⠑⠜⠂⠝
rule trans sheading ⠩⠂⠙⠬
rule trans sheepshead ⠩⠑⠑⠏⠎⠓⠂⠙
rule trans sheepsheads ⠩⠑⠑⠏⠎⠓⠂⠙⠎
rule trans shoreditch ⠩⠕⠗⠑⠙⠊⠞⠡
rule trans shoreditch's ⠩⠕⠗⠑⠙⠊⠞⠡⠄⠎
rule trans shorthead ⠩⠕⠗⠞⠓⠂⠙
rule trans shoshoni ⠩⠕⠩⠕⠝⠊
rule trans shoshonis ⠩⠕⠩⠕⠝⠊⠎
rule trans synchroflash ⠎⠽⠝⠡⠗⠕⠋⠇⠁⠩
rule trans synchroflashes ⠎⠽⠝⠡⠗⠕⠋⠇⠁⠩⠑⠎
rule trans townshend ⠞⠪⠝⠎⠓⠢⠙
rule trans townshend's ⠞⠪⠝⠎⠓⠢⠙⠄⠎
rule trans tranship ⠞⠗⠁⠝⠩⠊⠏
rule trans transhipment ⠞⠗⠁⠝⠩⠊⠏⠰⠞
rule trans transhipments ⠞⠗⠁⠝⠩⠊⠏⠰⠞⠎
rule trans transhipped ⠞⠗⠁⠝⠩⠊⠏⠏⠫
rule trans transhipping ⠞⠗⠁⠝⠩⠊⠏⠏⠬
rule trans tranships ⠞⠗⠁⠝⠩⠊⠏⠎
rule trans transhuman ⠞⠗⠁⠝⠎⠓⠥⠍⠁⠝
rule trans transhumanate ⠞⠗⠁⠝⠎⠓⠥⠍⠁⠝⠁⠞⠑
rule trans transhumance ⠞⠗⠁⠝⠎⠓⠥⠍⠨⠑
rule trans transhumanize ⠞⠗⠁⠝⠎⠓⠥⠍⠁⠝⠊⠵⠑
rule trans transhumant ⠞⠗⠁⠝⠎⠓⠥⠍⠁⠝⠞
rule trans undisheartened ⠥⠝⠙⠊⠎⠓⠑⠜⠞⠢⠫
rule trans unperished ⠥⠝⠏⠻⠊⠩⠫
rule trans unperishing ⠥⠝⠏⠻⠊⠩⠬
rule trans unshackle ⠥⠝⠩⠁⠉⠅⠇⠑
rule trans unshackled ⠥⠝⠩⠁⠉⠅⠇⠫
rule trans unshackles ⠥⠝⠩⠁⠉⠅⠇⠑⠎
rule trans unshackling ⠥⠝⠩⠁⠉⠅⠇⠬
rule trans unshaded ⠥⠝⠩⠁⠙⠫
rule trans unshadow ⠥⠝⠩⠁⠙⠪
rule trans unshadowed ⠥⠝⠩⠁⠙⠪⠫
rule trans unshakably ⠥⠝⠩⠁⠅⠁⠃⠇⠽
rule trans unshakeably ⠥⠝⠩⠁⠅⠂⠃⠇⠽
rule trans unshaken ⠥⠝⠩⠁⠅⠢
rule trans unshaking ⠥⠝⠩⠁⠅⠬
rule trans unshamed ⠥⠝⠩⠁⠍⠫
rule trans unshamefaced ⠥⠝⠩⠁⠍⠑⠋⠁⠉⠫
rule trans unshaped ⠥⠝⠩⠁⠏⠫
rule trans unshapeliness ⠥⠝⠩⠁⠏⠑⠇⠊⠰⠎
rule trans unshapely ⠥⠝⠩⠁⠏⠑⠇⠽
rule trans unshapen ⠥⠝⠩⠁⠏⠢
rule trans unshared ⠥⠝⠩⠜⠫
rule trans unsharing ⠥⠝⠩⠜⠬
rule trans unsharpen ⠥⠝⠩⠜⠏⠢
rule trans unsharpened ⠥⠝⠩⠜⠏⠢⠫
rule trans unsharpening ⠥⠝⠩⠜⠏⠢⠬
rule trans unsharpens ⠥⠝⠩⠜⠏⠢⠎
rule trans unshattered ⠥⠝⠩⠁⠞⠞⠻⠫
rule trans unshaved ⠥⠝⠩⠁⠧⠫
rule trans weisshorn ⠺⠑⠊⠎⠎⠓⠕⠗⠝
rule trans wilhelmshaven ⠺⠊⠇⠓⠑⠇⠍⠎⠓⠁⠧⠢
rule trans windesheim ⠺⠔⠙⠑⠎⠓⠑⠊⠍


## st   10.4.2   ⠘⠌acute
uses word_whole_+ word_whole_- rule trans st 234-2345
uses - not_modifier_45_- rule trans st 34

rule trans abbottstown ⠁⠆⠕⠞⠞⠎⠞⠪⠝
rule trans acenesthesia ⠁⠉⠢⠑⠎⠮⠎⠊⠁
rule trans acmesthesia ⠁⠉⠍⠑⠎⠮⠎⠊⠁
rule trans acoenesthesia ⠁⠉⠕⠢⠑⠎⠮⠎⠊⠁
rule trans adamstown ⠁⠙⠁⠍⠎⠞⠪⠝
rule trans aesthesia ⠁⠑⠎⠮⠎⠊⠁
rule trans antiaesthetic ⠁⠝⠞⠊⠁⠑⠎⠮⠞⠊⠉
rule trans antrustion ⠁⠝⠞⠗⠥⠎⠰⠝
rule trans asthma 1-234-1456-134-1
rule trans autocombustion ⠁⠥⠞⠕⠉⠕⠍⠃⠥⠎⠰⠝
rule trans autodigestion ⠁⠥⠞⠕⠙⠊⠛⠑⠎⠰⠝
rule trans autosuggestion ⠁⠥⠞⠕⠎⠥⠶⠑⠎⠰⠝
rule trans bakerstown ⠃⠁⠅⠻⠎⠞⠪⠝
rule trans baptistown ⠃⠁⠏⠞⠊⠎⠞⠪⠝
rule trans bardstown ⠃⠜⠙⠎⠞⠪⠝
rule trans bastion 12-1-234-56-1345
rule trans beardstown ⠃⠑⠜⠙⠎⠞⠪⠝
rule trans blairstown ⠃⠇⠁⠊⠗⠎⠞⠪⠝
rule trans blakestown ⠃⠇⠁⠅⠑⠎⠞⠪⠝
rule trans blountstown ⠃⠇⠨⠞⠎⠞⠪⠝
rule trans bowmanstown ⠃⠪⠍⠁⠝⠎⠞⠪⠝
rule trans boystown ⠃⠕⠽⠎⠞⠪⠝
rule trans brasstown ⠃⠗⠁⠎⠎⠞⠪⠝
rule trans brownstown ⠃⠗⠪⠝⠎⠞⠪⠝
rule trans bundestag 12-136-1345-145-15-234-2345-1-1245
rule trans byrdstown ⠃⠽⠗⠙⠎⠞⠪⠝
rule trans casstown ⠉⠁⠎⠎⠞⠪⠝
rule trans castledale ⠉⠁⠌⠇⠑⠙⠁⠇⠑
rule trans cenesthesia ⠉⠢⠑⠎⠮⠎⠊⠁
rule trans cenesthesis ⠉⠢⠑⠎⠮⠎⠊⠎
rule trans cenesthetic ⠉⠢⠑⠎⠮⠞⠊⠉
rule trans charlestown ⠡⠜⠇⠑⠎⠞⠪⠝
rule trans charlestown's ⠡⠜⠇⠑⠎⠞⠪⠝⠄⠎
rule trans chemotherapist ⠡⠑⠍⠕⠮⠗⠁⠏⠊⠌
rule trans chemotherapists ⠡⠑⠍⠕⠮⠗⠁⠏⠊⠌⠎
rule trans christhood ⠡⠗⠊⠌⠓⠕⠕⠙
rule trans chromesthesia ⠡⠗⠕⠍⠑⠎⠮⠎⠊⠁
rule trans chromotherapist ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠊⠌
rule trans chromotherapists ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠊⠌⠎
rule trans coenaesthesis ⠉⠕⠢⠁⠑⠎⠮⠎⠊⠎
rule trans coenesthesia ⠉⠕⠢⠑⠎⠮⠎⠊⠁
rule trans coenesthesis ⠉⠕⠢⠑⠎⠮⠎⠊⠎
rule trans combustion 14-135-134-12-136-234-56-1345
rule trans congestion 25-1245-15-234-56-1345
uses - - rule trans connellstown ⠉⠕⠝⠝⠑⠇⠇⠎⠞⠪⠝
rule trans cookstown ⠉⠕⠕⠅⠎⠞⠪⠝
rule trans cooperstown 14-135-135-1234-12456-234-2345-246-1345
rule trans cosuggestion ⠉⠕⠎⠥⠶⠑⠎⠰⠝
rule trans cosuggestions ⠉⠕⠎⠥⠶⠑⠎⠰⠝⠎
rule trans countersuggestion ⠉⠨⠞⠻⠎⠥⠶⠑⠎⠰⠝
rule trans countersuggestion's ⠉⠨⠞⠻⠎⠥⠶⠑⠎⠰⠝⠄⠎
rule trans countersuggestions ⠉⠨⠞⠻⠎⠥⠶⠑⠎⠰⠝⠎
rule trans crosstown 14-1235-135-234-234-2345-246-1345
rule trans crosthwaite ⠉⠗⠕⠎⠹⠺⠁⠊⠞⠑
rule trans crosthwaite's ⠉⠗⠕⠎⠹⠺⠁⠊⠞⠑⠄⠎
rule trans customshouse ⠉⠥⠌⠕⠍⠎⠓⠳⠎⠑
rule trans customshouses ⠉⠥⠌⠕⠍⠎⠓⠳⠎⠑⠎
rule trans dallastown ⠙⠁⠇⠇⠁⠎⠞⠪⠝     
rule trans decongestion ⠙⠑⠉⠰⠛⠑⠎⠰⠝
rule trans demibastion ⠙⠑⠍⠊⠃⠁⠎⠰⠝
rule trans demibastions ⠙⠑⠍⠊⠃⠁⠎⠰⠝⠎
rule trans destouches ⠙⠑⠎⠞⠳⠡⠑⠎
rule trans dewhurst ⠙⠑⠺⠓⠥⠗⠌
rule trans dewhurst's ⠙⠑⠺⠓⠥⠗⠌⠄⠎
rule trans diastereoisomer ⠙⠊⠁⠌⠻⠑⠕⠊⠎⠕⠍⠻
rule trans digestion 145-24-1245-15-234-56-1345
rule trans disafforest ⠲⠁⠋⠿⠑⠌
rule trans doylestown ⠙⠕⠽⠇⠑⠎⠞⠪⠝
rule trans dysaesthesia ⠙⠽⠎⠁⠑⠎⠮⠎⠊⠁
rule trans dysaesthetic ⠙⠽⠎⠁⠑⠎⠮⠞⠊⠉
rule trans dysesthesia ⠙⠽⠎⠑⠎⠮⠎⠊⠁
rule trans dysesthetic ⠙⠽⠎⠑⠎⠮⠞⠊⠉
rule trans egestion ⠑⠛⠑⠎⠰⠝
rule trans electroanesthesia ⠑⠇⠑⠉⠞⠗⠕⠁⠝⠑⠎⠮⠎⠊⠁
rule trans esterházy ⠑⠌⠻⠓⠘⠌⠁⠵⠽
rule trans estheses ⠑⠎⠮⠎⠑⠎
rule trans esthesia ⠑⠎⠮⠎⠊⠁
rule trans esthesiology ⠑⠎⠮⠎⠊⠕⠇⠕⠛⠽
rule trans esthesiometer ⠑⠎⠮⠎⠊⠕⠍⠑⠞⠻
rule trans esthesiometers ⠑⠎⠮⠎⠊⠕⠍⠑⠞⠻⠎
rule trans esthesiometry ⠑⠎⠮⠎⠊⠕⠍⠑⠞⠗⠽
rule trans esthesis ⠑⠎⠮⠎⠊⠎
rule trans esthetical ⠑⠎⠮⠞⠊⠉⠁⠇
rule trans esthetically ⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans esthetician ⠑⠎⠮⠞⠊⠉⠊⠁⠝
rule trans estheticians ⠑⠎⠮⠞⠊⠉⠊⠁⠝⠎
rule trans estheticism ⠑⠎⠮⠞⠊⠉⠊⠎⠍
rule trans esthwaite ⠑⠎⠹⠺⠁⠊⠞⠑
rule trans esthwaite's ⠑⠎⠹⠺⠁⠊⠞⠑⠄⠎
rule trans exhaustion 15-1346-125-1-136-234-56-1345
rule trans fittstown ⠋⠊⠞⠞⠎⠞⠪⠝
rule trans forbestown ⠿⠃⠑⠎⠞⠪⠝
rule trans francestown ⠋⠗⠨⠑⠎⠞⠪⠝
rule trans gainestown ⠛⠁⠔⠑⠎⠞⠪⠝
rule trans gastight ⠛⠁⠎⠞⠊⠣⠞
rule trans gerrardstown ⠛⠻⠗⠜⠙⠎⠞⠪⠝
rule trans gestion ⠛⠑⠎⠰⠝
rule trans gibbstown ⠛⠊⠆⠎⠞⠪⠝
rule trans glossokinesthetic ⠛⠇⠕⠎⠎⠕⠅⠔⠑⠎⠮⠞⠊⠉
rule trans gordonstoun ⠛⠕⠗⠙⠕⠝⠎⠞⠳⠝
rule trans guesstimate 1245-136-15-234-234-2345-24-134-1-2345-15
rule trans guesstimated 1245-136-15-234-234-2345-24-134-1-2345-1246
rule trans guesstimating 1245-136-15-234-234-2345-24-134-1-2345-346
rule trans guesthouse ⠛⠥⠑⠌⠓⠳⠎⠑
rule trans guesthouse's ⠛⠥⠑⠌⠓⠳⠎⠑⠄⠎
rule trans guesthouses ⠛⠥⠑⠌⠓⠳⠎⠑⠎
rule trans hannastown ⠓⠁⠝⠝⠁⠎⠞⠪⠝
rule trans harristown ⠓⠜⠗⠊⠎⠞⠪⠝
rule trans hartstown ⠓⠜⠞⠎⠞⠪⠝
rule trans havighurst ⠓⠁⠧⠊⠛⠓⠥⠗⠌
rule trans hemianesthesia ⠓⠑⠍⠊⠁⠝⠑⠎⠮⠎⠊⠁
rule trans hemidysesthesia ⠓⠑⠍⠊⠙⠽⠎⠑⠎⠮⠎⠊⠁
rule trans hemihyperesthesia ⠓⠑⠍⠊⠓⠽⠏⠻⠑⠎⠮⠎⠊⠁
rule trans hemihypesthesia ⠓⠑⠍⠊⠓⠽⠏⠑⠎⠮⠎⠊⠁
rule trans hemihypoesthesia ⠓⠑⠍⠊⠓⠽⠏⠕⠑⠎⠮⠎⠊⠁
rule trans hemiparanesthesia ⠓⠑⠍⠊⠏⠜⠁⠝⠑⠎⠮⠎⠊⠁
rule trans hemiparesthesia ⠓⠑⠍⠊⠏⠜⠑⠎⠮⠎⠊⠁
rule trans hephaestion ⠓⠑⠏⠓⠁⠑⠌⠊⠕⠝
rule trans hesther ⠓⠑⠎⠮⠗
rule trans hesther's ⠓⠑⠎⠮⠗⠄⠎
rule trans heterosuggestion ⠓⠑⠞⠻⠕⠎⠥⠶⠑⠎⠰⠝
rule trans hookstown ⠓⠕⠕⠅⠎⠞⠪⠝
rule trans howardstown ⠓⠪⠜⠙⠎⠞⠪⠝
rule trans hypaesthesia ⠓⠽⠏⠁⠑⠎⠮⠎⠊⠁
rule trans hyperaesthesia ⠓⠽⠏⠻⠁⠑⠎⠮⠎⠊⠁
rule trans hyperaesthete ⠓⠽⠏⠻⠁⠑⠎⠮⠞⠑
rule trans hyperaesthetic ⠓⠽⠏⠻⠁⠑⠎⠮⠞⠊⠉
rule trans hyperesthesia ⠓⠽⠏⠻⠑⠎⠮⠎⠊⠁
rule trans hyperesthete ⠓⠽⠏⠻⠑⠎⠮⠞⠑
rule trans hyperesthetic ⠓⠽⠏⠻⠑⠎⠮⠞⠊⠉
rule trans hypesthesia ⠓⠽⠏⠑⠎⠮⠎⠊⠁
rule trans hypsometrist ⠓⠽⠏⠎⠕⠍⠑⠞⠗⠊⠌
rule trans inaesthetic ⠔⠁⠑⠎⠮⠞⠊⠉
rule trans incombustion ⠔⠉⠕⠍⠃⠥⠎⠰⠝
rule trans indigestion 35-145-24-1245-15-234-56-1345
rule trans inesthetic ⠔⠑⠎⠮⠞⠊⠉
rule trans ingestion 35-1245-15-234-56-1345
rule trans inhaustion ⠔⠓⠁⠥⠎⠰⠝
rule trans inustion ⠔⠥⠎⠰⠝
rule trans investion ⠔⠧⠑⠎⠰⠝
rule trans isthmi 24-234-1456-134-24
rule trans isthmus 24-234-1456-134-136-234
rule trans jamestown 245-1-134-15-234-2345-246-1345
rule trans jennerstown ⠚⠢⠝⠻⠎⠞⠪⠝
rule trans johnstown ⠚⠕⠓⠝⠎⠞⠪⠝
rule trans jonestown ⠚⠐⠕⠎⠞⠪⠝
rule trans jonestown ⠚⠐⠕⠎⠞⠪⠝
rule trans kinaesthesia ⠅⠔⠁⠑⠎⠮⠎⠊⠁
rule trans kinaesthesis ⠅⠔⠁⠑⠎⠮⠎⠊⠎
rule trans kinaesthetic ⠅⠔⠁⠑⠎⠮⠞⠊⠉
rule trans kinaesthetically ⠅⠔⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans kinestheses ⠅⠔⠑⠎⠮⠎⠑⠎
rule trans kinesthesia ⠅⠔⠑⠎⠮⠎⠊⠁
rule trans kinesthesis ⠅⠔⠑⠎⠮⠎⠊⠎
rule trans kinesthetic ⠅⠔⠑⠎⠮⠞⠊⠉
rule trans kinesthetically ⠅⠔⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans kingstown 13-346-234-2345-246-1345
rule trans knightstown ⠅⠝⠊⠣⠞⠎⠞⠪⠝
rule trans knuckleduster ⠅⠝⠥⠉⠅⠇⠑⠙⠥⠌⠻
rule trans knuckleduster's ⠅⠝⠥⠉⠅⠇⠑⠙⠥⠌⠻⠄⠎
rule trans knuckledusters ⠅⠝⠥⠉⠅⠇⠑⠙⠥⠌⠻⠎
rule trans kreistag ⠅⠗⠑⠊⠎⠞⠁⠛
rule trans kurtistown ⠅⠥⠗⠞⠊⠎⠞⠪⠝
rule trans laestrygonian ⠇⠁⠑⠌⠗⠽⠛⠕⠝⠊⠁⠝
rule trans laestrygonian's ⠇⠁⠑⠌⠗⠽⠛⠕⠝⠊⠁⠝⠄⠎
rule trans laestrygonians ⠇⠁⠑⠌⠗⠽⠛⠕⠝⠊⠁⠝⠎
rule trans leopardstown ⠇⠑⠕⠏⠜⠙⠎⠞⠪⠝
rule trans lewistown ⠇⠑⠺⠊⠎⠞⠪⠝
rule trans liebestod ⠇⠊⠑⠃⠑⠎⠞⠕⠙
rule trans littlestown ⠇⠇⠎⠞⠪⠝
rule trans maeystown ⠍⠁⠑⠽⠎⠞⠪⠝
rule trans maldigestion ⠍⠁⠇⠙⠊⠛⠑⠎⠰⠝
rule trans masthand ⠍⠁⠌⠓⠯
rule trans masthand's ⠍⠁⠌⠓⠯⠄⠎
rule trans masthands ⠍⠁⠌⠓⠯⠎
rule trans mechanicstown ⠍⠑⠡⠁⠝⠊⠉⠎⠞⠪⠝
rule trans merrittstown ⠍⠻⠗⠊⠞⠞⠎⠞⠪⠝
rule trans microcombustion ⠍⠊⠉⠗⠕⠉⠕⠍⠃⠥⠎⠰⠝
rule trans millerstown ⠍⠊⠇⠇⠻⠎⠞⠪⠝
rule trans missuggestion ⠍⠊⠎⠎⠥⠶⠑⠎⠰⠝
rule trans missuggestion's ⠍⠊⠎⠎⠥⠶⠑⠎⠰⠝⠄⠎
rule trans missuggestions ⠍⠊⠎⠎⠥⠶⠑⠎⠰⠝⠎
rule trans mistime 134-24-234-5-2345
rule trans mistresshood ⠍⠊⠌⠗⠑⠎⠎⠓⠕⠕⠙
rule trans moorestown ⠍⠕⠕⠗⠑⠎⠞⠪⠝
rule trans morristown ⠍⠕⠗⠗⠊⠎⠞⠪⠝
rule trans moxibustion ⠍⠕⠭⠊⠃⠥⠎⠰⠝
rule trans myerstown ⠍⠽⠻⠎⠞⠪⠝
rule trans narcoanesthesia ⠝⠜⠉⠕⠁⠝⠑⠎⠮⠎⠊⠁
rule trans nonaesthetic ⠝⠕⠝⠁⠑⠎⠮⠞⠊⠉
rule trans nonaesthetically ⠝⠕⠝⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans nonanesthetic ⠝⠕⠝⠁⠝⠑⠎⠮⠞⠊⠉
rule trans nonanesthetized ⠝⠕⠝⠁⠝⠑⠎⠮⠞⠊⠵⠫
rule trans noncombustion ⠝⠕⠝⠉⠕⠍⠃⠥⠎⠰⠝
rule trans noncongestion ⠝⠕⠝⠉⠰⠛⠑⠎⠰⠝
rule trans nondigestion ⠝⠕⠝⠙⠊⠛⠑⠎⠰⠝
rule trans nongestic ⠝⠕⠝⠛⠑⠌⠊⠉
rule trans nongymnast ⠝⠕⠝⠛⠽⠍⠝⠁⠌
rule trans nongymnasts ⠝⠕⠝⠛⠽⠍⠝⠁⠌⠎
rule trans nonpersistance ⠝⠕⠝⠏⠻⠎⠊⠌⠨⠑
rule trans nonpersistant ⠝⠕⠝⠏⠻⠎⠊⠌⠁⠝⠞
rule trans nonpersistantly ⠝⠕⠝⠏⠻⠎⠊⠌⠁⠝⠞⠇⠽
rule trans nonpersisting ⠝⠕⠝⠏⠻⠎⠊⠌⠬
rule trans nonsuggestion ⠝⠕⠝⠎⠥⠶⠑⠎⠰⠝
rule trans nonsynesthetic ⠝⠕⠝⠎⠽⠝⠑⠎⠮⠞⠊⠉
rule trans norristown ⠝⠕⠗⠗⠊⠎⠞⠪⠝
rule trans oasthouse ⠕⠁⠌⠓⠳⠎⠑
rule trans oasthouse's ⠕⠁⠌⠓⠳⠎⠑⠄⠎
rule trans oasthouses ⠕⠁⠌⠓⠳⠎⠑⠎
rule trans orrstown ⠕⠗⠗⠎⠞⠪⠝
rule trans painstaking 1234-1-35-234-2345-1-13-346
rule trans pallanesthesia ⠏⠁⠇⠇⠁⠝⠑⠎⠮⠎⠊⠁
rule trans pallesthesia ⠏⠁⠇⠇⠑⠎⠮⠎⠊⠁
rule trans palmesthesia ⠏⠁⠇⠍⠑⠎⠮⠎⠊⠁
rule trans panaesthesia ⠏⠁⠝⠁⠑⠎⠮⠎⠊⠁
rule trans panaesthetic ⠏⠁⠝⠁⠑⠎⠮⠞⠊⠉
rule trans panesthesia ⠏⠁⠝⠑⠎⠮⠎⠊⠁
rule trans panesthetic ⠏⠁⠝⠑⠎⠮⠞⠊⠉
rule trans paraesthesia ⠏⠜⠁⠑⠎⠮⠎⠊⠁
rule trans paraesthetic ⠏⠜⠁⠑⠎⠮⠞⠊⠉
rule trans paresthesia ⠏⠜⠑⠎⠮⠎⠊⠁
rule trans paresthesis ⠏⠜⠑⠎⠮⠎⠊⠎
rule trans paresthetic ⠏⠜⠑⠎⠮⠞⠊⠉
rule trans pastime 1234-1-234-5-2345
rule trans pesthouse ⠏⠑⠌⠓⠳⠎⠑
rule trans pesthouse's ⠏⠑⠌⠓⠳⠎⠑⠄⠎
rule trans pesthouses ⠏⠑⠌⠓⠳⠎⠑⠎
rule trans peterstown ⠏⠑⠞⠻⠎⠞⠪⠝
rule trans photaesthesia ⠏⠓⠕⠞⠁⠑⠎⠮⠎⠊⠁
rule trans photaesthesis ⠏⠓⠕⠞⠁⠑⠎⠮⠎⠊⠎
rule trans photaesthetic ⠏⠓⠕⠞⠁⠑⠎⠮⠞⠊⠉
rule trans photesthesis ⠏⠓⠕⠞⠑⠎⠮⠎⠊⠎
rule trans photoaesthetic ⠏⠓⠕⠞⠕⠁⠑⠎⠮⠞⠊⠉
rule trans photocombustion ⠏⠓⠕⠞⠕⠉⠕⠍⠃⠥⠎⠰⠝
rule trans photoesthesis ⠏⠓⠕⠞⠕⠑⠎⠮⠎⠊⠎
rule trans photoesthetic ⠏⠓⠕⠞⠕⠑⠎⠮⠞⠊⠉
rule trans pickstown ⠏⠊⠉⠅⠎⠞⠪⠝
rule trans pittstown ⠏⠊⠞⠞⠎⠞⠪⠝
rule trans polyesthesia ⠏⠕⠇⠽⠑⠎⠮⠎⠊⠁
rule trans polyesthetic ⠏⠕⠇⠽⠑⠎⠮⠞⠊⠉
rule trans postanaesthetic ⠏⠕⠌⠁⠝⠁⠑⠎⠮⠞⠊⠉
rule trans posthouse ⠏⠕⠌⠓⠳⠎⠑
rule trans posthouse's ⠏⠕⠌⠓⠳⠎⠑⠄⠎
rule trans posthouses ⠏⠕⠌⠓⠳⠎⠑⠎
rule trans precombustion ⠏⠗⠑⠉⠕⠍⠃⠥⠎⠰⠝
rule trans precongestion ⠏⠗⠑⠉⠰⠛⠑⠎⠰⠝
rule trans predigestion ⠏⠗⠫⠊⠛⠑⠎⠰⠝
rule trans preexhaustion ⠏⠗⠑⠑⠭⠓⠁⠥⠎⠰⠝
rule trans presuggestion ⠏⠗⠑⠎⠥⠶⠑⠎⠰⠝
rule trans proaesthetic ⠏⠗⠕⠁⠑⠎⠮⠞⠊⠉
rule trans pseudesthesia ⠏⠎⠑⠥⠙⠑⠎⠮⠎⠊⠁
rule trans pseudoaesthetic ⠏⠎⠑⠥⠙⠕⠁⠑⠎⠮⠞⠊⠉
rule trans pseudoaesthetically ⠏⠎⠑⠥⠙⠕⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans psychesthesia ⠏⠎⠽⠡⠑⠎⠮⠎⠊⠁
rule trans psychesthetic ⠏⠎⠽⠡⠑⠎⠮⠞⠊⠉
rule trans queenstown ⠟⠥⠑⠢⠎⠞⠪⠝
rule trans questhouse ⠟⠥⠑⠌⠓⠳⠎⠑
rule trans questhouse's ⠟⠥⠑⠌⠓⠳⠎⠑⠄⠎
rule trans questhouses ⠟⠥⠑⠌⠓⠳⠎⠑⠎
rule trans randallstown ⠗⠯⠁⠇⠇⠎⠞⠪⠝
rule trans readstown ⠗⠂⠙⠎⠞⠪⠝
rule trans recongestion ⠗⠑⠉⠰⠛⠑⠎⠰⠝
rule trans redigestion ⠗⠫⠊⠛⠑⠎⠰⠝
rule trans reichstag 1235-15-24-16-234-2345-1-1245
rule trans resthouse ⠗⠑⠌⠓⠳⠎⠑
rule trans resthouse's ⠗⠑⠌⠓⠳⠎⠑⠄⠎
rule trans resthouses ⠗⠑⠌⠓⠳⠎⠑⠎
rule trans resuggestion ⠗⠑⠎⠥⠶⠑⠎⠰⠝
rule trans robstown ⠗⠕⠃⠎⠞⠪⠝
rule trans royston ⠗⠕⠽⠌⠕⠝
rule trans rumbustion ⠗⠥⠍⠃⠥⠎⠰⠝
rule trans saunderstown ⠎⠁⠥⠝⠙⠻⠎⠞⠪⠝
rule trans semianaesthetic ⠎⠑⠍⠊⠁⠝⠁⠑⠎⠮⠞⠊⠉
rule trans semianesthetic ⠎⠑⠍⠊⠁⠝⠑⠎⠮⠞⠊⠉
rule trans semibastion ⠎⠑⠍⠊⠃⠁⠎⠰⠝
rule trans semibastions ⠎⠑⠍⠊⠃⠁⠎⠰⠝⠎
rule trans shepherdstown ⠩⠑⠏⠓⠻⠙⠎⠞⠪⠝
rule trans spinnerstown ⠎⠏⠔⠝⠻⠎⠞⠪⠝
rule trans staghorn ⠌⠁⠛⠓⠕⠗⠝
rule trans staghorns ⠌⠁⠛⠓⠕⠗⠝⠎
rule trans staghound ⠌⠁⠛⠓⠨⠙
rule trans staghounds ⠌⠁⠛⠓⠨⠙⠎
rule trans stereoisomeric ⠌⠻⠑⠕⠊⠎⠕⠍⠻⠊⠉
rule trans stereoisomerism ⠌⠻⠑⠕⠊⠎⠕⠍⠻⠊⠎⠍
rule trans stewartstown ⠌⠑⠺⠜⠞⠎⠞⠪⠝
rule trans stewhouse ⠌⠑⠺⠓⠳⠎⠑
rule trans stewhouse's ⠌⠑⠺⠓⠳⠎⠑⠄⠎
rule trans stewhouses ⠌⠑⠺⠓⠳⠎⠑⠎
rule trans stownet ⠌⠪⠝⠑⠞
rule trans stownets ⠌⠪⠝⠑⠞⠎
rule trans strausstown ⠌⠗⠁⠥⠎⠎⠞⠪⠝
rule trans strawhat ⠌⠗⠁⠺⠓⠁⠞
rule trans strawhat's ⠌⠗⠁⠺⠓⠁⠞⠄⠎
rule trans strawhats ⠌⠗⠁⠺⠓⠁⠞⠎
rule trans studenthood ⠌⠥⠙⠢⠞⠓⠕⠕⠙
rule trans sturgeon ⠌⠥⠗⠛⠑⠕⠝
rule trans suggestion 234-136-2356-15-234-56-1345
rule trans superaesthetic ⠎⠥⠏⠻⠁⠑⠎⠮⠞⠊⠉
rule trans superaesthetically ⠎⠥⠏⠻⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans supercongestion ⠎⠥⠏⠻⠉⠰⠛⠑⠎⠰⠝
rule trans synaesthesia ⠎⠽⠝⠁⠑⠎⠮⠎⠊⠁
rule trans synaesthesis ⠎⠽⠝⠁⠑⠎⠮⠎⠊⠎
rule trans synaesthetic ⠎⠽⠝⠁⠑⠎⠮⠞⠊⠉
rule trans synesthesia ⠎⠽⠝⠑⠎⠮⠎⠊⠁
rule trans synesthetic ⠎⠽⠝⠑⠎⠮⠞⠊⠉
rule trans taylorstown ⠞⠁⠽⠇⠕⠗⠎⠞⠪⠝
rule trans telaesthesia ⠞⠑⠇⠁⠑⠎⠮⠎⠊⠁
rule trans telaesthetic ⠞⠑⠇⠁⠑⠎⠮⠞⠊⠉
rule trans telesthesia ⠞⠑⠇⠑⠎⠮⠎⠊⠁
rule trans telesthetic ⠞⠑⠇⠑⠎⠮⠞⠊⠉
rule trans thermaesthesia ⠮⠗⠍⠁⠑⠎⠮⠎⠊⠁
rule trans thermanesthesia ⠮⠗⠍⠁⠝⠑⠎⠮⠎⠊⠁
rule trans thermesthesia ⠮⠗⠍⠑⠎⠮⠎⠊⠁
rule trans thermoanesthesia ⠮⠗⠍⠕⠁⠝⠑⠎⠮⠎⠊⠁
rule trans thermoesthesia ⠮⠗⠍⠕⠑⠎⠮⠎⠊⠁
rule trans thomastown ⠹⠕⠍⠁⠎⠞⠪⠝
rule trans unaesthetic ⠥⠝⠁⠑⠎⠮⠞⠊⠉
rule trans unaesthetically ⠥⠝⠁⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans undersuggestion ⠐⠥⠎⠥⠶⠑⠎⠰⠝
rule trans undigested ⠥⠝⠙⠊⠛⠑⠌⠫
rule trans undigestion ⠥⠝⠙⠊⠛⠑⠎⠰⠝
rule trans unesthetic ⠥⠝⠑⠎⠮⠞⠊⠉
rule trans unexhausted ⠥⠝⠑⠭⠓⠁⠥⠌⠫
rule trans unexhaustion ⠥⠝⠑⠭⠓⠁⠥⠎⠰⠝
rule trans unpessimistic ⠥⠝⠏⠑⠎⠎⠊⠍⠊⠌⠊⠉
rule trans unpessimistically ⠥⠝⠏⠑⠎⠎⠊⠍⠊⠌⠊⠉⠁⠇⠇⠽
rule trans unpestered ⠥⠝⠏⠑⠌⠻⠫
rule trans unrested ⠥⠝⠗⠑⠌⠫
rule trans unresting ⠥⠝⠗⠑⠌⠬
rule trans unrestricting ⠥⠝⠗⠑⠌⠗⠊⠉⠞⠬
rule trans unrestrictive ⠥⠝⠗⠑⠌⠗⠊⠉⠞⠊⠧⠑
rule trans unrests ⠥⠝⠗⠑⠌⠎
rule trans unstably ⠥⠝⠌⠁⠃⠇⠽
rule trans unstack ⠥⠝⠌⠁⠉⠅
rule trans unstackable ⠥⠝⠌⠁⠉⠅⠁⠃⠇⠑
rule trans unstacked ⠥⠝⠌⠁⠉⠅⠫
rule trans unstacking ⠥⠝⠌⠁⠉⠅⠬
rule trans unstacks ⠥⠝⠌⠁⠉⠅⠎
rule trans unstaffed ⠥⠝⠌⠁⠖⠫
rule trans unstaged ⠥⠝⠌⠁⠛⠫
rule trans unstaggered ⠥⠝⠌⠁⠶⠻⠫
rule trans unstaggering ⠥⠝⠌⠁⠶⠻⠬
rule trans unstaid ⠥⠝⠌⠁⠊⠙
rule trans unstainable ⠥⠝⠌⠁⠔⠁⠃⠇⠑
rule trans unstained ⠥⠝⠌⠁⠔⠫
rule trans unstammering ⠥⠝⠌⠁⠍⠍⠻⠬
rule trans unstammeringly ⠥⠝⠌⠁⠍⠍⠻⠬⠇⠽
rule trans unstamped ⠥⠝⠌⠁⠍⠏⠫
rule trans unstandard ⠥⠝⠌⠯⠜⠙
rule trans unstandardizable ⠥⠝⠌⠯⠜⠙⠊⠵⠁⠃⠇⠑
rule trans unstandardized ⠥⠝⠌⠯⠜⠙⠊⠵⠫
rule trans unstapled ⠥⠝⠌⠁⠏⠇⠫
rule trans unstar ⠥⠝⠌⠜
rule trans unstarched ⠥⠝⠌⠜⠡⠫
rule trans unstarlike ⠥⠝⠌⠜⠇⠊⠅⠑
rule trans unstarred ⠥⠝⠌⠜⠗⠫
rule trans unstarted ⠥⠝⠌⠜⠞⠫
rule trans unstarting ⠥⠝⠌⠜⠞⠬
rule trans unstartled ⠥⠝⠌⠜⠞⠇⠫
rule trans unstartling ⠥⠝⠌⠜⠞⠇⠬
rule trans unstarved ⠥⠝⠌⠜⠧⠫
rule trans unstately ⠥⠝⠌⠁⠞⠑⠇⠽
rule trans unstatesmanlike ⠥⠝⠌⠁⠞⠑⠎⠍⠁⠝⠇⠊⠅⠑
rule trans unstatic ⠥⠝⠌⠁⠞⠊⠉
rule trans unstatically ⠥⠝⠌⠁⠞⠊⠉⠁⠇⠇⠽
rule trans unstation ⠥⠝⠌⠁⠰⠝
rule trans unstationary ⠥⠝⠌⠁⠰⠝⠜⠽
rule trans unstatistical ⠥⠝⠌⠁⠞⠊⠌⠊⠉⠁⠇
rule trans unstatistically ⠥⠝⠌⠁⠞⠊⠌⠊⠉⠁⠇⠇⠽
rule trans unstatuesque ⠥⠝⠌⠁⠞⠥⠑⠎⠟⠥⠑
rule trans unstatuesquely ⠥⠝⠌⠁⠞⠥⠑⠎⠟⠥⠑⠇⠽
rule trans unstatutable ⠥⠝⠌⠁⠞⠥⠞⠁⠃⠇⠑
rule trans unstatutory ⠥⠝⠌⠁⠞⠥⠞⠕⠗⠽
rule trans visuokinesthetic ⠧⠊⠎⠥⠕⠅⠔⠑⠎⠮⠞⠊⠉
rule trans wadestown ⠺⠁⠙⠑⠎⠞⠪⠝
rule trans whitestown ⠱⠊⠞⠑⠎⠞⠪⠝
rule trans williamstown ⠺⠊⠇⠇⠊⠁⠍⠎⠞⠪⠝
rule trans woodstown ⠺⠕⠕⠙⠎⠞⠪⠝
rule trans wrightstown ⠺⠐⠗⠎⠞⠪⠝
rule trans youngstown 5-13456-234-2345-246-1345
rule trans Ångström ⠘⠫⠁⠝⠛⠌⠗⠘⠒⠕⠍


## th   10.4.2
uses word_whole_+ word_whole_- rule trans th 2345-125
uses - - rule trans th 1456

rule trans adulthood 1-145-136-123-2345-125-135-135-145
rule trans ampthill ⠁⠍⠏⠞⠓⠊⠇⠇
rule trans anthill 1-1345-2345-125-24-123-123
rule trans bartholdi 12-345-2345-125-135-123-145-24
rule trans beethoven 12-15-15-2345-125-135-1236-26
rule trans billethead ⠃⠊⠇⠇⠑⠞⠓⠂⠙
rule trans bitthead ⠃⠊⠞⠞⠓⠂⠙
rule trans blunthead ⠃⠇⠥⠝⠞⠓⠂⠙
rule trans boathead ⠃⠕⠁⠞⠓⠂⠙
rule trans bolthead ⠃⠕⠇⠞⠓⠂⠙
rule trans bonnethead ⠃⠕⠝⠝⠑⠞⠓⠂⠙
rule trans bullethead ⠃⠥⠇⠇⠑⠞⠓⠂⠙
rule trans carthorse 14-345-2345-125-135-1235-234-15
rule trans cathead ⠉⠁⠞⠓⠂⠙
rule trans courthouse 14-1256-1235-2345-125-1256-234-15
rule trans crosshead ⠉⠗⠕⠎⠎⠓⠂⠙
rule trans crossheads ⠉⠗⠕⠎⠎⠓⠂⠙⠎
rule trans demihogshead ⠙⠑⠍⠊⠓⠕⠛⠎⠓⠂⠙
rule trans demihogsheads ⠙⠑⠍⠊⠓⠕⠛⠎⠓⠂⠙⠎
rule trans doghead ⠙⠕⠛⠓⠂⠙
rule trans drawhead ⠙⠗⠁⠺⠓⠂⠙
rule trans drawhead's ⠙⠗⠁⠺⠓⠂⠙⠄⠎
rule trans drawheads ⠙⠗⠁⠺⠓⠂⠙⠎
rule trans flathead ⠋⠇⠁⠞⠓⠂⠙
rule trans flighthead ⠋⠇⠊⠣⠞⠓⠂⠙
rule trans flightheads ⠋⠇⠊⠣⠞⠓⠂⠙⠎
rule trans flinthead ⠋⠇⠔⠞⠓⠂⠙
rule trans foothill 124-135-135-2345-125-24-123-123
rule trans foothold 124-135-135-2345-125-135-123-145
rule trans gilthead ⠛⠊⠇⠞⠓⠂⠙
rule trans goatherd 1245-135-1-2345-125-12456-145
rule trans hothouse 125-135-2345-125-1256-234-15
rule trans jughead ⠚⠥⠛⠓⠂⠙
rule trans jugheads ⠚⠥⠛⠓⠂⠙⠎
rule trans knighthead ⠅⠝⠊⠣⠞⠓⠂⠙
rule trans knighthood 13-1345-24-126-2345-125-135-135-145
rule trans knothead ⠅⠝⠕⠞⠓⠂⠙
rule trans knotheads ⠅⠝⠕⠞⠓⠂⠙⠎
rule trans knothole 13-1345-135-2345-125-135-123-15
rule trans lighthouse 123-24-126-2345-125-1256-234-15
rule trans lufthansa 123-136-124-2345-125-1-1345-234-1
rule trans meathead ⠍⠂⠞⠓⠂⠙
rule trans meatheads ⠍⠂⠞⠓⠂⠙⠎
rule trans meathook ⠍⠂⠞⠓⠕⠕⠅
rule trans microwatt ⠍⠊⠉⠗⠕⠺⠁⠞⠞
rule trans mosshead ⠍⠕⠎⠎⠓⠂⠙
rule trans mossheads ⠍⠕⠎⠎⠓⠂⠙⠎
rule trans nighthawk 1345-24-126-2345-125-1-2456-13
rule trans nuthatch 1345-136-2345-125-1-2345-16
rule trans outhouse 1256-2345-125-1256-234-15
rule trans overlightheaded ⠕⠧⠻⠇⠊⠣⠞⠓⠂⠙⠫
rule trans parenthood 1234-345-26-2345-125-135-135-145
rule trans peasanthood ⠏⠂⠎⠁⠝⠞⠓⠕⠕⠙
rule trans peathouse ⠏⠂⠞⠓⠳⠎⠑
rule trans penthouse 1234-26-2345-125-1256-234-15
rule trans picowatt ⠏⠊⠉⠕⠺⠁⠞⠞
rule trans pilothouse 1234-24-123-135-2345-125-1256-234-15
rule trans pithead ⠏⠊⠞⠓⠂⠙
rule trans pithead's ⠏⠊⠞⠓⠂⠙⠄⠎
rule trans pitheads ⠏⠊⠞⠓⠂⠙⠎
rule trans porthole 1234-135-1235-2345-125-135-123-15
rule trans potholder 1234-135-2345-125-135-123-145-12456
rule trans pothole 1234-135-2345-125-135-123-15
rule trans pothook 1234-135-2345-125-135-135-13
rule trans puppethead ⠏⠥⠏⠏⠑⠞⠓⠂⠙
rule trans rawhead ⠗⠁⠺⠓⠂⠙
rule trans rawhead's ⠗⠁⠺⠓⠂⠙⠄⠎
rule trans rawheads ⠗⠁⠺⠓⠂⠙⠎
rule trans richthofen 1235-24-16-2345-125-12356-26
rule trans rightheaded ⠐⠗⠓⠂⠙⠫
rule trans rivethead ⠗⠊⠧⠑⠞⠓⠂⠙
rule trans sainthood 234-1-35-2345-125-135-135-145
rule trans screwhead ⠎⠉⠗⠑⠺⠓⠂⠙
rule trans screwhead's ⠎⠉⠗⠑⠺⠓⠂⠙⠄⠎
rule trans screwheads ⠎⠉⠗⠑⠺⠓⠂⠙⠎
rule trans sethead ⠎⠑⠞⠓⠂⠙
rule trans sheading ⠩⠂⠙⠬
rule trans sheepshead ⠩⠑⠑⠏⠎⠓⠂⠙
rule trans sheepsheads ⠩⠑⠑⠏⠎⠓⠂⠙⠎
rule trans shorthand 146-135-1235-2345-125-12346
rule trans shorthead ⠩⠕⠗⠞⠓⠂⠙
rule trans shorthorn 146-135-1235-2345-125-135-1235-1345
rule trans softheaded ⠎⠷⠞⠓⠂⠙⠫
rule trans spithead ⠎⠏⠊⠞⠓⠂⠙
rule trans spitheads ⠎⠏⠊⠞⠓⠂⠙⠎
rule trans staghead ⠌⠁⠛⠓⠂⠙
rule trans stagheads ⠌⠁⠛⠓⠂⠙⠎
rule trans straighthead ⠌⠗⠁⠊⠣⠞⠓⠂⠙
rule trans sweathouse ⠎⠺⠂⠞⠓⠳⠎⠑
rule trans tilthead ⠞⠊⠇⠞⠓⠂⠙
rule trans turrethead ⠞⠥⠗⠗⠑⠞⠓⠂⠙
rule trans warthog 2456-345-2345-125-135-1245


## wh   10.4.2
uses word_whole_+ word_whole_- rule trans wh 2456-125
uses - - rule trans wh 156

rule trans bawhorse ⠃⠁⠺⠓⠕⠗⠎⠑
rule trans bawhorses ⠃⠁⠺⠓⠕⠗⠎⠑⠎
rule trans blowhole ⠃⠇⠪⠓⠕⠇⠑
rule trans blowhole's ⠃⠇⠪⠓⠕⠇⠑⠄⠎
rule trans blowholes ⠃⠇⠪⠓⠕⠇⠑⠎
rule trans brewhouse ⠃⠗⠑⠺⠓⠳⠎⠑
rule trans brewhouse's ⠃⠗⠑⠺⠓⠳⠎⠑⠄⠎
rule trans brewhouses ⠃⠗⠑⠺⠓⠳⠎⠑⠎
rule trans chowhound ⠡⠪⠓⠨⠙
rule trans clawhammer ⠉⠇⠁⠺⠓⠁⠍⠍⠻
rule trans clawhammer's ⠉⠇⠁⠺⠓⠁⠍⠍⠻⠄⠎
rule trans clawhammers ⠉⠇⠁⠺⠓⠁⠍⠍⠻⠎
rule trans cowherd ⠉⠪⠓⠻⠙
rule trans cowherd's ⠉⠪⠓⠻⠙⠄⠎
rule trans cowherds ⠉⠪⠓⠻⠙⠎
rule trans cowhouse ⠉⠪⠓⠳⠎⠑
rule trans cowhouse's ⠉⠪⠓⠳⠎⠑⠄⠎
rule trans cowhouses ⠉⠪⠓⠳⠎⠑⠎
rule trans dewhurst ⠙⠑⠺⠓⠥⠗⠌
rule trans dewhurst's ⠙⠑⠺⠓⠥⠗⠌⠄⠎
rule trans drawhead ⠙⠗⠁⠺⠓⠂⠙
rule trans drawhead's ⠙⠗⠁⠺⠓⠂⠙⠄⠎
rule trans drawheads ⠙⠗⠁⠺⠓⠂⠙⠎
rule trans drawhorse ⠙⠗⠁⠺⠓⠕⠗⠎⠑
rule trans drawhorse's ⠙⠗⠁⠺⠓⠕⠗⠎⠑⠄⠎
rule trans drawhorses ⠙⠗⠁⠺⠓⠕⠗⠎⠑⠎
rule trans grewhound ⠛⠗⠑⠺⠓⠨⠙
rule trans grewhound's ⠛⠗⠑⠺⠓⠨⠙⠄⠎
rule trans grewhounds ⠛⠗⠑⠺⠓⠨⠙⠎
rule trans hewhall ⠓⠑⠺⠓⠁⠇⠇
rule trans hewhalls ⠓⠑⠺⠓⠁⠇⠇⠎
rule trans hewhole ⠓⠑⠺⠓⠕⠇⠑
rule trans hewholes ⠓⠑⠺⠓⠕⠇⠑⠎
rule trans jawhole ⠚⠁⠺⠓⠕⠇⠑
rule trans jawholes ⠚⠁⠺⠓⠕⠇⠑⠎
rule trans jewhood ⠚⠑⠺⠓⠕⠕⠙
rule trans newhall ⠝⠑⠺⠓⠁⠇⠇
rule trans newhall's ⠝⠑⠺⠓⠁⠇⠇⠄⠎
rule trans newham ⠝⠑⠺⠓⠁⠍
rule trans newham's ⠝⠑⠺⠓⠁⠍⠄⠎
rule trans newhaven 1345-15-2456-125-1-1236-26
rule trans newhouse ⠝⠑⠺⠓⠳⠎⠑
rule trans newhouse's ⠝⠑⠺⠓⠳⠎⠑⠄⠎
rule trans pewholder ⠏⠑⠺⠓⠕⠇⠙⠻
rule trans pewholder's ⠏⠑⠺⠓⠕⠇⠙⠻⠄⠎
rule trans pewholders ⠏⠑⠺⠓⠕⠇⠙⠻⠎
rule trans rawhead ⠗⠁⠺⠓⠂⠙
rule trans rawhead's ⠗⠁⠺⠓⠂⠙⠄⠎
rule trans rawheads ⠗⠁⠺⠓⠂⠙⠎
rule trans rawhide 1235-1-2456-125-24-145-15
rule trans rawhided ⠗⠁⠺⠓⠊⠙⠫
rule trans rawhides ⠗⠁⠺⠓⠊⠙⠑⠎
rule trans rawhiding ⠗⠁⠺⠓⠊⠙⠬
rule trans sawhorse 234-1-2456-125-135-1235-234-15
rule trans screwhead ⠎⠉⠗⠑⠺⠓⠂⠙
rule trans screwhead's ⠎⠉⠗⠑⠺⠓⠂⠙⠄⠎
rule trans screwheads ⠎⠉⠗⠑⠺⠓⠂⠙⠎
rule trans screwhole ⠎⠉⠗⠑⠺⠓⠕⠇⠑
rule trans screwhole's ⠎⠉⠗⠑⠺⠓⠕⠇⠑⠄⠎
rule trans screwholes ⠎⠉⠗⠑⠺⠓⠕⠇⠑⠎
rule trans snowhouse ⠎⠝⠪⠓⠳⠎⠑
rule trans snowhouse's ⠎⠝⠪⠓⠳⠎⠑⠄⠎
rule trans snowhouses ⠎⠝⠪⠓⠳⠎⠑⠎
rule trans stewhouse ⠌⠑⠺⠓⠳⠎⠑
rule trans stewhouse's ⠌⠑⠺⠓⠳⠎⠑⠄⠎
rule trans stewhouses ⠌⠑⠺⠓⠳⠎⠑⠎
rule trans strawhat ⠌⠗⠁⠺⠓⠁⠞
rule trans strawhat's ⠌⠗⠁⠺⠓⠁⠞⠄⠎
rule trans strawhats ⠌⠗⠁⠺⠓⠁⠞⠎
rule trans unwhole ⠥⠝⠱⠕⠇⠑
rule trans whaddaya ⠱⠁⠙⠙⠁⠽⠁
rule trans whall ⠱⠁⠇⠇
rule trans whalls ⠱⠁⠇⠇⠎
rule trans wharfedale ⠱⠜⠋⠑⠙⠁⠇⠑
rule trans wharfedale's ⠱⠜⠋⠑⠙⠁⠇⠑⠄⠎
rule trans wharfedales ⠱⠜⠋⠑⠙⠁⠇⠑⠎
rule trans whatsomever ⠱⠁⠞⠎⠕⠍⠐⠑
rule trans whensomever ⠱⠢⠎⠕⠍⠐⠑
rule trans wheresomever ⠐⠱⠎⠕⠍⠐⠑
rule trans whitestown ⠱⠊⠞⠑⠎⠞⠪⠝
rule trans whitestown ⠱⠊⠞⠑⠎⠞⠪⠝
rule trans whitestown's ⠱⠊⠞⠑⠎⠞⠪⠝⠄⠎
rule trans whosomever ⠱⠕⠎⠕⠍⠐⠑



use


########################################
#   10.5   Lower Wordsigns
########################################

chars +=*,.;:?!"'“”‘’ $lower_dots
chars ()[]{} $upper_dots

#                      upper dots except ⠘quote                              “”
pattern UPPER_DOTS     [⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠙⠚⠛⠜⠝⠞⠟⠡⠣⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠸⠹⠺⠻⠼⠽⠾⠿]|⠘(![⠦⠴]|^)

#                      upper dots                                           %_   ^
pattern UPPER_DOTS_<   [⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠘⠙⠚⠛⠜⠝⠞⠟⠡⠣⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠸⠹⠺⠻⠼⠽⠾⠿]|⠨[⠴⠤]|⠈⠢

#                      upper dots except ⠘quote                            ()      “”
pattern UPPER_DOTS_>   [⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠙⠚⠛⠜⠝⠞⠟⠡⠣⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠸⠹⠺⠻⠼⠽⠾⠿]|⠐[⠣⠜]|⠘(![⠦⠴]|^)

pattern CAPS_~      [\H\S](⠠?⠠?⠠|⠠⠄)[\H\S]
pattern NO_CAPS_<   [\H\S]([⠨⠘⠸⠈][⠆⠂⠶]|[⠈⠘⠸⠐⠨]⠼[⠆⠂⠶]|⠈⠨⠣|[⠰⠠]⠄)[\H\S]
pattern NO_CAPS_>   [\H\S](⠈⠨⠜|[⠈⠘⠸⠐⠨]⠼⠄|[⠨⠘⠸⠈]⠄)[\H\S]

pattern SPACE_<+   (^|%_)@[SEQ_<+]*|(^|%[_~])@[SEQ_<+]*@[SEQ_<+]
pattern SPACE_>+   @[SEQ_>+]*@[SEQ_>+](%[_~]|^)|@[SEQ_>+]*(%_|^)
pattern SPACE_<-   (^|%_)@[SEQ_<-]*|(^|%[_~])@[SEQ_<-]*@[SEQ_<-]
pattern SPACE_>-   @[SEQ_>-]*@[SEQ_>-](%[_~]|^)|@[SEQ_>-]*(%_|^)

filter space_+   @[SPACE_<+]   @[SPACE_>+]
filter space_-   @[SPACE_<-]   @[SPACE_>-]

## be (word)
uses space_+ - rule -forward pretrans be \M\;12-15;\M
match -forward posttrans (^|%_|@[NO_CAPS_<]|@[UPPER_DOTS_<])@[CAPS_~]* \M\;12-15;\M @[CAPS_~]*(@[UPPER_DOTS_>]|@[NO_CAPS_>]|%_|^)   - \;23; -
uses - word_whole_- rule -backward trans be 23

## his
uses space_+ - rule -forward pretrans his \M\;125-24-234;\M
match -forward posttrans (^|%_|@[NO_CAPS_<]|@[UPPER_DOTS_<])@[CAPS_~]* \M\;125-24-234;\M @[CAPS_~]*(@[UPPER_DOTS_>]|@[NO_CAPS_>]|%_|^)   - \;236; -
uses - word_whole_- rule -backward trans his 236

## was
uses space_+ - rule -forward pretrans was \M\;2456-1-234;\M
match -forward posttrans (^|%_|@[NO_CAPS_<]|@[UPPER_DOTS_<])@[CAPS_~]* \M\;2456-1-234;\M @[CAPS_~]*(@[UPPER_DOTS_>]|@[NO_CAPS_>]|%_|^)   - \;356; -
uses - word_whole_- rule -backward trans was 356

## were
uses space_+ - rule -forward pretrans were \M\;2456-124565-15;\M
match -forward posttrans (^|%_|@[NO_CAPS_<]|@[UPPER_DOTS_<])@[CAPS_~]* \M\;2456-124565-15;\M @[CAPS_~]*(@[UPPER_DOTS_>]|@[NO_CAPS_>]|%_|^)   - \;2356; -
uses - word_whole_- rule -backward trans were 2356

## enough
uses word_whole_+ - rule -forward pretrans enough \M\;26-1256-126;\M
match -forward posttrans (^|%_)@[CAPS_~]*            \M\;26-1256-126;\M @[CAPS_~]*(%_|^)              - \;26; -
match -forward posttrans @[UPPER_DOTS]!%_*@[CAPS_~]* \M\;26-1256-126;\M -                             - \;26; -
match -forward posttrans -                           \M\;26-1256-126;\M @[CAPS_~]*!%_*@[UPPER_DOTS]   - \;26; -
uses - word_whole_- rule -backward trans enough 26

uses word_whole_+ - rule -forward  pretrans enough’s \M\;26-3-234;\M
uses - word_whole_- rule -backward trans enough’s 26-3-234
uses word_whole_+ - rule -forward  pretrans enough's \M\;26-3-234;\M
uses - word_whole_- rule -backward trans enough's 26-3-234

## in (word)
uses word_whole_+ - rule -forward pretrans in \M\;24-1345;\M
match -forward posttrans (^|%_)@[CAPS_~]*            \M\;24-1345;\M @[CAPS_~]*(%_|^)              - \;35; -
match -forward posttrans @[UPPER_DOTS]!%_*@[CAPS_~]* \M\;24-1345;\M -                             - \;35; -
match -forward posttrans -                           \M\;24-1345;\M @[CAPS_~]*!%_*@[UPPER_DOTS]   - \;35; -
uses - word_whole_- rule -backward trans in 35


########################################
#   10.6   Lower Groupsigns
########################################

#   needed with not %[_l] for en and in
chars ⠯⠩⠫⠻⠌⠡⠒⠬⠂⠆⠤ $modifier

## bb   10.6.5   10.6.6
uses word_mid_+ word_mid_- rule trans bb 23

use word_whole_begin_+ word_whole_begin_-
rule trans dumbbell 145-136-134-12-12-15-123-123
rule trans subbasement 234-136-12-12-1-234-15-56-2345
rule trans subbing 234-136-12-12-346
use

## be (prefix)   10.6.1   10.6.2   10.6.3   10.6.4
match trans @[WORD_<+] be @[MODIFER_>]   @[WORD_<-] 23 @[MODIFER_>]
match trans @[WORD_<+] be ati!n          @[WORD_<-] 23 ⠁(⠐⠞|⠰⠝|⠞(⠰⠽|⠊!@[N_>-]))                                           # a(time|tion|t(ity|i!n))
match trans @[WORD_<+] be atr            @[WORD_<-] 23 ⠁⠞@[R_>-]
match trans @[WORD_<+] be c![hkq]        @[WORD_<-] 23 ⠸⠉|⠒@[LETTER_>-]|⠉!(@[H_>-]|@[K_>-]|@[Q_>-])                       # cannot|cc%|c![hkq]
match trans @[WORD_<+] be da             @[WORD_<-] 23 ⠐⠙|⠙@[A_>-]                                                        # day|da
match trans @[WORD_<+] be de             @[WORD_<-] 23 ⠙@[E_>-]
match trans @[WORD_<+] be dra            @[WORD_<-] 23 ⠙⠗@[A_>-]
match trans @[WORD_<+] be elz            @[WORD_<-] 23 ⠑⠇@[Z_>-]
match trans @[WORD_<+] be g![gs]         @[WORD_<-] 23 ⠣|⠛!(⠛|⠣|⠎|⠩|⠌|⠶@[LETTER_>-]|[⠐⠸]⠎|⠨⠝)                             # gh|g!(g|gh|s|sh|st|gg%|[some spirit]|sion)
match trans @[WORD_<+] be in             @[WORD_<-] 23 ⠔|⠬|⠊@[N_>-]                                                       # in|ing|in
match trans @[WORD_<+] be l[aeiouwy]     @[WORD_<-] 23 ⠐⠇|⠨⠎|⠇(@[A_>-]|@[E_>-]|@[I_>-]|@[O_>-]|@[U_>-]|@[W_>-]|@[Y_>-])   # like|less|l[aeiouwy]
match trans @[WORD_<+] be n[aiu]         @[WORD_<-] 23 ⠐⠝|⠝(@[A_>-]|@[I_>-]|@[U_>-])                                      # name|n[aiu]
match trans @[WORD_<+] be ne![dft]       @[WORD_<-] 23 ⠝(⠢|⠻|[⠐⠰]⠑|⠂@[LETTER_>-]|⠑!(@[D_>-]|@[F_>-]|@[T_>-]))             # n(en|er|[ever ence]|ea%|e![dft])
match trans @[WORD_<+] be neficen        @[WORD_<-] 23 ⠝⠑⠋⠊⠉(⠢|⠰⠑|⠑(⠝|⠐⠝|⠰⠎))                                             # nefic(en|ence|e(n|name|ness))
match trans @[WORD_<+] be ra             @[WORD_<-] 23 ⠗@[A_>-]
match trans @[WORD_<+] be re!n           @[WORD_<-] 23 ⠗(⠫|⠻|⠐⠑|⠂@[LETTER_>-]|⠑!(@[N_>-]))                                # r(ea|ed|er|ever|ea%|e!n)
match trans @[WORD_<+] be stir           @[WORD_<-] 23 ⠌⠊@[R_>-]|⠎⠞⠊@[R_>-]                                               # stir|stir
match trans @[WORD_<+] be st[or]         @[WORD_<-] 23 (⠌|⠎⠞)(@[O_>-]|@[R_>-])                                            # (st|st)[or]
match trans @[WORD_<+] be s![st]         @[WORD_<-] 23 ⠩|⠐⠎|⠨⠝|⠸⠎|⠎!(@[S_>-]|@[T_>-])                                     # sh|some|sion|spirit|s![st]
match trans @[WORD_<+] be tho            @[WORD_<-] 23 ⠘⠹|⠹@[O_>-]|⠞⠓@[O_>-]                                              # those|tho|tho
match trans @[WORD_<+] be t![chst]       @[WORD_<-] 23 ⠐⠞|⠰⠝|⠞!(@[C_>-]|@[H_>-]|@[S_>-]|@[T_>-])                          # time|tion|t![chst]

match trans @[WORD_<+] be [bfhjmopqwxz]   @[WORD_<-] 23 @[B_>-]|@[F_>-]|@[H_>-]|@[J_>-]|@[M_>-]|@[O_>-]|@[P_>-]|@[Q_>-]|@[W_>-]|@[X_>-]|@[Z_>-]

#   be[cfhlnsty] are handled in 10.9.5

use word_whole_+ word_whole_-
rule trans bede 12-1246-15
rule trans bein 23-24-1345
rule trans bela ⠆⠇⠁
use

use word_whole_begin_+ word_whole_begin_-
rule trans beretta 12-12456-15-2345-2345-1
rule trans betws 12-15-2345-2456-234
use

match trans @[WORD_<+] benet @[APOSS_+]@[WORD_>+]   @[WORD_<-] 23-1345-15-2345 @[APOSS_-]@[WORD_>-]

## cc   10.6.5   10.6.6   ⠈⠒stroke      ⠘⠒diaeresis
uses word_mid_+ word_mid_- rule trans cc 25

use word_whole_begin_+ word_whole_begin_-
rule trans arccosine 345-14-14-135-234-35-15
rule trans bacchanal 12-1-14-16-1-1345-1-123
rule trans bacchus 12-1-14-16-136-234
rule trans boccherini ⠃⠕⠉⠡⠻⠔⠊
rule trans gnocchi ⠛⠝⠕⠉⠡⠊
rule trans gracchus 1245-1235-1-14-16-136-234
rule trans pinocchio 1234-35-135-14-16-24-135
rule trans saccharin 234-1-14-16-345-35
rule trans saccharide ⠎⠁⠉⠡⠜⠊⠙⠑
rule trans zacchaeus ⠵⠁⠉⠡⠁⠑⠥⠎
rule trans zucchini 1356-136-14-16-35-24
use

## con   10.6.1   10.6.2   10.6.3   10.6.4
match trans @[WORD_<+] con @[MODIFER_>]   @[WORD_<-] 25 @[MODIFER_>]
match trans @[WORD_<+] con c!h            @[WORD_<-] 25 ⠡|⠸⠉|⠒@[LETTER_>-]|⠉!@[H_>-]   # ch|cannot|cc%|c!h
match trans @[WORD_<+] con est            @[WORD_<-] 25 ⠑(⠌|⠎@[T_>-])                  # e(st|st)

#   letters:             ;:,!    AAABDFFGGGHIIIJKLMNOOOOPQRSSSTTTUVWWWXYZ    DFHKLMNOOPQRSTTTUWWY    TTUWW¸`^°~¨´ᵛ+    FIMNOT    ALOOS    HMSTW    /-˘¯     123
pattern LETTER_NO_CE_>- [⠆⠒⠂⠖]*([⠁⠯⠜⠃⠙⠋⠿⠛⠣⠶⠓⠊⠬⠔⠚⠅⠇⠍⠝⠕⠳⠷⠪⠏⠟⠗⠎⠌⠩⠞⠹⠮⠥⠧⠺⠱⠾⠭⠽⠵]|⠐[⠙⠋⠓⠅⠇⠍⠝⠕⠳⠏⠟⠗⠎⠮⠹⠞⠥⠱⠺⠽]|⠘[⠮⠹⠥⠱⠺⠯⠡⠩⠫⠻⠒⠌⠬⠖]|⠰[⠇⠽⠞⠎⠛⠝]|⠨[⠑⠎⠙⠞⠝]|⠸[⠓⠍⠎⠮⠺]|⠈[⠡⠒⠬⠤]|⠘⠸[⠂⠆⠤])
#atch trans @[WORD_<+] con [abdfghijlmnopqrstuvwxyz]   @[WORD_<-] 25 @[A_>-]|@[B_>-]|@[D_>-]|@[F_>-]|@[G_>-]|@[H_>-]|@[I_>-]|@[J_>-]|@[L_>-]|@[M_>-]|@[N_>-]|@[O_>-]|@[P_>-]|@[Q_>-]|@[R_>-]|@[S_>-]|@[T_>-]|@[U_>-]|@[V_>-]|@[W_>-]|@[X_>-]|@[Y_>-]|@[Z_>-]
match trans @[WORD_<+] con [abdfghijlmnopqrstuvwxyz]   @[WORD_<-] 25 @[LETTER_NO_CE_>-]

use word_whole_+ word_whole_-
rule trans cong 14-56-1245
rule trans cons 14-135-1345-234

use word_whole_begin_+ word_whole_begin_-
rule trans conakry 14-135-1345-1-13-1235-13456
rule trans conan 14-135-1345-1-1345
rule trans conned 14-135-1345-1345-1246
rule trans conurbation 14-135-1345-136-1235-12-1-56-1345

use

## dis   10.6.1   10.6.2   10.6.3   10.6.4
match trans @[WORD_<+] dis @[MODIFER_>]   @[WORD_<-] 256 @[MODIFER_>]
match trans @[WORD_<+] dis c!s            @[WORD_<-] 256 ⠡|⠐⠡|⠸⠉|⠒@[LETTER_>-]|⠉!@[S_>-]                                  # ch|character|cannot|cc%|c!s
match trans @[WORD_<+] dis he![dsv]       @[WORD_<-] 256 ⠐⠓|⠓(⠂|⠢|⠻|[⠐⠰]⠑|⠑!(@[D_>-]|@[S_>-]|@[V_>-]))                    # here|h(ea|en|er|[ever ence]|e![dsv])
match trans @[WORD_<+] dis h![ceiprtw]    @[WORD_<-] 256 ⠸⠓|⠓!(@[C_>-]|@[E_>-]|@[I_>-]|@[P_>-]|@[R_>-]|@[T_>-]|@[W_>-])   # have|h![ceiprtw]
match trans @[WORD_<+] dis p!i            @[WORD_<-] 256 ⠐⠏|⠏!@[I_>-]                                                     # part|p!i

#   letters:               ;:,!    AAABDEEEEFFGGGIIIJLMNOOOOQRSSSTTTUVWWWXYZ    DEFLMNOOQRSTTTUWWY    TTUWW¸`^°~¨´ᵛ+    EFIMNOT    ALOOS    MSTW    /-˘¯     123
pattern LETTER_NO_CHKP_>- [⠆⠒⠂⠖]*([⠁⠯⠜⠃⠙⠑⠫⠻⠢⠋⠿⠛⠣⠶⠊⠬⠔⠚⠇⠍⠝⠕⠳⠷⠪⠟⠗⠎⠌⠩⠞⠹⠮⠥⠧⠺⠱⠾⠭⠽⠵]|⠐[⠙⠑⠋⠇⠍⠝⠕⠳⠟⠗⠎⠮⠹⠞⠥⠱⠺⠽]|⠘[⠮⠹⠥⠱⠺⠯⠡⠩⠫⠻⠒⠌⠬⠖]|⠰[⠑⠇⠽⠞⠎⠛⠝]|⠨[⠑⠎⠙⠞⠝]|⠸[⠍⠎⠮⠺]|⠈[⠡⠒⠬⠤]|⠘⠸[⠂⠆⠤])
#atch trans @[WORD_<+] dis [abdefgijlmnoqrstuvwxyz]   @[WORD_<-] 256 @[A_>-]|@[B_>-]|@[D_>-]|@[E_>-]|@[F_>-]|@[G_>-]|@[I_>-]|@[J_>-]|@[L_>-]|@[M_>-]|@[N_>-]|@[O_>-]|@[Q_>-]|@[R_>-]|@[S_>-]|@[T_>-]|@[U_>-]|@[V_>-]|@[W_>-]|@[X_>-]|@[Y_>-]|@[Z_>-]   # @[LETTER_>-]
match trans @[WORD_<+] dis [abdefgijlmnoqrstuvwxyz]   @[WORD_<-] 256 @[LETTER_NO_CHKP_>-]

use word_whole_+ word_whole_-
rule trans disc 145-24-234-14
rule trans discharacter 256-5-16
rule trans dish 145-24-146
rule trans diss 145-24-234-234
rule trans disulphide 145-24-234-136-123-1234-125-24-145-15
use

## ea   10.6.5   10.6.6   10.6.7
uses word_mid_+ word_mid_- rule trans ea 2

use word_whole_+ word_whole_-
rule trans flearidden ⠋⠇⠂⠗⠊⠙⠙⠢
rule trans giveable ⠛⠊⠧⠂⠃⠇⠑
rule trans learig ⠇⠂⠗⠊⠛
rule trans preadolescence ⠏⠗⠑⠁⠙⠕⠇⠑⠎⠉⠰⠑
rule trans preaudience ⠏⠗⠑⠁⠥⠙⠊⠰⠑

rule trans leann 123-15-1-1345-1345       # leanness
rule trans leanne 123-15-1-1345-1345-15   # leanness
rule trans preadmit 1234-1235-15-1-145-134-24-2345

use

rule trans ear 15-345
rule trans pineapple 1234-35-15-1-1234-1234-123-15
rule trans wiseacr 2456-24-234-15-1-14-1235

use word_whole_+ word_whole_-
rule trans beatrice ⠆⠁⠞⠗⠊⠉⠑
rule trans beatrice's ⠆⠁⠞⠗⠊⠉⠑⠄⠎
rule trans beatrix ⠆⠁⠞⠗⠊⠭
rule trans beatrix's ⠆⠁⠞⠗⠊⠭⠄⠎
rule trans beatriz ⠆⠁⠞⠗⠊⠵
rule trans beatriz's ⠆⠁⠞⠗⠊⠵⠄⠎
rule trans strathearn ⠌⠗⠁⠹⠑⠜⠝
rule trans theadora ⠮⠁⠙⠕⠗⠁
rule trans flinthearted ⠋⠇⠔⠞⠓⠑⠜⠞⠫
rule trans hothearted ⠓⠕⠞⠓⠑⠜⠞⠫
rule trans mishear ⠍⠊⠎⠓⠑⠜
rule trans misheard ⠍⠊⠎⠓⠑⠜⠙
rule trans mishearing ⠍⠊⠎⠓⠑⠜⠬
rule trans mishears ⠍⠊⠎⠓⠑⠜⠎
rule trans preamble ⠏⠗⠑⠁⠍⠃⠇⠑
rule trans preamble's ⠏⠗⠑⠁⠍⠃⠇⠑⠄⠎
rule trans preambled ⠏⠗⠑⠁⠍⠃⠇⠫
rule trans preambles ⠏⠗⠑⠁⠍⠃⠇⠑⠎
rule trans preambling ⠏⠗⠑⠁⠍⠃⠇⠬
rule trans publichearted ⠏⠥⠃⠇⠊⠉⠓⠑⠜⠞⠫
rule trans publicheartedness ⠏⠥⠃⠇⠊⠉⠓⠑⠜⠞⠫⠰⠎
rule trans reanesthetize ⠗⠑⠁⠝⠑⠎⠮⠞⠊⠵⠑
rule trans reanesthetized ⠗⠑⠁⠝⠑⠎⠮⠞⠊⠵⠫
rule trans reanesthetizes ⠗⠑⠁⠝⠑⠎⠮⠞⠊⠵⠑⠎
rule trans reanesthetizing ⠗⠑⠁⠝⠑⠎⠮⠞⠊⠵⠬
rule trans stouthearted ⠌⠳⠞⠓⠑⠜⠞⠫
rule trans stoutheartedly ⠌⠳⠞⠓⠑⠜⠞⠫⠇⠽
rule trans stoutheartedness ⠌⠳⠞⠓⠑⠜⠞⠫⠰⠎
rule trans undisheartened ⠥⠝⠙⠊⠎⠓⠑⠜⠞⠢⠫
rule trans vacanthearted ⠧⠁⠉⠁⠝⠞⠓⠑⠜⠞⠫
rule trans vacantheartedness ⠧⠁⠉⠁⠝⠞⠓⠑⠜⠞⠫⠰⠎
rule trans abreact ⠁⠃⠗⠑⠁⠉⠞
rule trans abreacted ⠁⠃⠗⠑⠁⠉⠞⠫
rule trans abreacting ⠁⠃⠗⠑⠁⠉⠞⠬
rule trans abreaction ⠁⠃⠗⠑⠁⠉⠰⠝
rule trans abreaction's ⠁⠃⠗⠑⠁⠉⠰⠝⠄⠎
rule trans abreactions ⠁⠃⠗⠑⠁⠉⠰⠝⠎
rule trans abreacts ⠁⠃⠗⠑⠁⠉⠞⠎
rule trans antireaction ⠁⠝⠞⠊⠗⠑⠁⠉⠰⠝
rule trans antireactions ⠁⠝⠞⠊⠗⠑⠁⠉⠰⠝⠎
rule trans archreactionaries ⠜⠡⠗⠑⠁⠉⠰⠝⠜⠊⠑⠎
rule trans archreactionary ⠜⠡⠗⠑⠁⠉⠰⠝⠜⠽
rule trans archreactionary's ⠜⠡⠗⠑⠁⠉⠰⠝⠜⠽⠄⠎
rule trans battleax ⠃⠁⠞⠞⠇⠑⠁⠭
rule trans battleax's ⠃⠁⠞⠞⠇⠑⠁⠭⠄⠎
rule trans battleaxe ⠃⠁⠞⠞⠇⠑⠁⠭⠑
rule trans battleaxe's ⠃⠁⠞⠞⠇⠑⠁⠭⠑⠄⠎
rule trans battleaxes ⠃⠁⠞⠞⠇⠑⠁⠭⠑⠎
rule trans bioreaction ⠃⠊⠕⠗⠑⠁⠉⠰⠝
rule trans bioreactions ⠃⠊⠕⠗⠑⠁⠉⠰⠝⠎
rule trans counterreaction ⠉⠨⠞⠻⠗⠑⠁⠉⠰⠝
rule trans counterreactions ⠉⠨⠞⠻⠗⠑⠁⠉⠰⠝⠎
rule trans deaccession ⠙⠑⠁⠒⠑⠎⠨⠝
rule trans deaccessioning ⠙⠑⠁⠒⠑⠎⠨⠝⠬
rule trans deaccessions ⠙⠑⠁⠒⠑⠎⠨⠝⠎
rule trans deacetylate ⠙⠑⠁⠉⠑⠞⠽⠇⠁⠞⠑
rule trans deacetylated ⠙⠑⠁⠉⠑⠞⠽⠇⠁⠞⠫
rule trans deacetylating ⠙⠑⠁⠉⠑⠞⠽⠇⠁⠞⠬
rule trans deacetylation ⠙⠑⠁⠉⠑⠞⠽⠇⠁⠰⠝
rule trans deacidification ⠙⠑⠁⠉⠊⠙⠊⠋⠊⠉⠁⠰⠝
rule trans deacidified ⠙⠑⠁⠉⠊⠙⠊⠋⠊⠫
rule trans deacidifies ⠙⠑⠁⠉⠊⠙⠊⠋⠊⠑⠎
rule trans deacidify ⠙⠑⠁⠉⠊⠙⠊⠋⠽
rule trans deacidifying ⠙⠑⠁⠉⠊⠙⠊⠋⠽⠬
rule trans deacquisition ⠙⠑⠁⠉⠟⠥⠊⠎⠊⠰⠝
rule trans deaerate ⠙⠑⠁⠻⠁⠞⠑
rule trans deaerated ⠙⠑⠁⠻⠁⠞⠫
rule trans deaerates ⠙⠑⠁⠻⠁⠞⠑⠎
rule trans deaerating ⠙⠑⠁⠻⠁⠞⠬
rule trans deaeration ⠙⠑⠁⠻⠁⠰⠝
rule trans deaeration's ⠙⠑⠁⠻⠁⠰⠝⠄⠎
rule trans deafforest ⠙⠑⠁⠋⠿⠑⠌
rule trans deafforestation ⠙⠑⠁⠋⠿⠑⠌⠁⠰⠝
rule trans deair ⠙⠑⠁⠊⠗
rule trans deaired ⠙⠑⠁⠊⠗⠫
rule trans deairing ⠙⠑⠁⠊⠗⠬
rule trans deairs ⠙⠑⠁⠊⠗⠎
rule trans dealate ⠙⠑⠁⠇⠁⠞⠑
rule trans dealated ⠙⠑⠁⠇⠁⠞⠫
rule trans dealates ⠙⠑⠁⠇⠁⠞⠑⠎
rule trans dealation ⠙⠑⠁⠇⠁⠰⠝
rule trans dealbate ⠙⠑⠁⠇⠃⠁⠞⠑
rule trans dealbuminize ⠙⠑⠁⠇⠃⠥⠍⠔⠊⠵⠑
rule trans dealcoholize ⠙⠑⠁⠇⠉⠕⠓⠕⠇⠊⠵⠑
rule trans dealkalize ⠙⠑⠁⠇⠅⠁⠇⠊⠵⠑
rule trans dealkylate ⠙⠑⠁⠇⠅⠽⠇⠁⠞⠑
rule trans deallocate ⠙⠑⠁⠇⠇⠕⠉⠁⠞⠑
rule trans deallocated ⠙⠑⠁⠇⠇⠕⠉⠁⠞⠫
rule trans deallocates ⠙⠑⠁⠇⠇⠕⠉⠁⠞⠑⠎
rule trans deallocating ⠙⠑⠁⠇⠇⠕⠉⠁⠞⠬
rule trans deallocation ⠙⠑⠁⠇⠇⠕⠉⠁⠰⠝
rule trans deallocation's ⠙⠑⠁⠇⠇⠕⠉⠁⠰⠝⠄⠎
rule trans deallocations ⠙⠑⠁⠇⠇⠕⠉⠁⠰⠝⠎
rule trans deambulate ⠙⠑⠁⠍⠃⠥⠇⠁⠞⠑
rule trans deambulation ⠙⠑⠁⠍⠃⠥⠇⠁⠰⠝
rule trans deambulatory ⠙⠑⠁⠍⠃⠥⠇⠁⠞⠕⠗⠽
rule trans deamidase ⠙⠑⠁⠍⠊⠙⠁⠎⠑
rule trans deamidate ⠙⠑⠁⠍⠊⠙⠁⠞⠑
rule trans deamidation ⠙⠑⠁⠍⠊⠙⠁⠰⠝
rule trans deamidization ⠙⠑⠁⠍⠊⠙⠊⠵⠁⠰⠝
rule trans deamidize ⠙⠑⠁⠍⠊⠙⠊⠵⠑
rule trans deaminase ⠙⠑⠁⠍⠔⠁⠎⠑
rule trans deaminate ⠙⠑⠁⠍⠔⠁⠞⠑
rule trans deaminated ⠙⠑⠁⠍⠔⠁⠞⠫
rule trans deaminates ⠙⠑⠁⠍⠔⠁⠞⠑⠎
rule trans deaminating ⠙⠑⠁⠍⠔⠁⠞⠬
rule trans deamination ⠙⠑⠁⠍⠔⠁⠰⠝
rule trans deaminization ⠙⠑⠁⠍⠔⠊⠵⠁⠰⠝
rule trans deaminize ⠙⠑⠁⠍⠔⠊⠵⠑
rule trans deaminized ⠙⠑⠁⠍⠔⠊⠵⠫
rule trans deaminizing ⠙⠑⠁⠍⠔⠊⠵⠬
rule trans deanathematize ⠙⠑⠁⠝⠁⠮⠍⠁⠞⠊⠵⠑
rule trans deanimalize ⠙⠑⠁⠝⠊⠍⠁⠇⠊⠵⠑
rule trans deanthropomorphic ⠙⠑⠁⠝⠹⠗⠕⠏⠕⠍⠕⠗⠏⠓⠊⠉
rule trans deappetizing ⠙⠑⠁⠏⠏⠑⠞⠊⠵⠬
rule trans dearticulate ⠙⠑⠜⠞⠊⠉⠥⠇⠁⠞⠑
rule trans dearticulation ⠙⠑⠜⠞⠊⠉⠥⠇⠁⠰⠝
rule trans deash ⠙⠑⠁⠩
rule trans deashed ⠙⠑⠁⠩⠫
rule trans deashes ⠙⠑⠁⠩⠑⠎
rule trans deashing ⠙⠑⠁⠩⠬
rule trans deaspirate ⠙⠑⠁⠎⠏⠊⠗⠁⠞⠑
rule trans deaspirated ⠙⠑⠁⠎⠏⠊⠗⠁⠞⠫
rule trans deaspiration ⠙⠑⠁⠎⠏⠊⠗⠁⠰⠝
rule trans deassign ⠙⠑⠁⠎⠎⠊⠛⠝
rule trans deassigned ⠙⠑⠁⠎⠎⠊⠛⠝⠫
rule trans deassigning ⠙⠑⠁⠎⠎⠊⠛⠝⠬
rule trans deassigns ⠙⠑⠁⠎⠎⠊⠛⠝⠎
rule trans deassimilation ⠙⠑⠁⠎⠎⠊⠍⠊⠇⠁⠰⠝
rule trans deaurate ⠙⠑⠁⠥⠗⠁⠞⠑
rule trans deaurated ⠙⠑⠁⠥⠗⠁⠞⠫
rule trans deaurates ⠙⠑⠁⠥⠗⠁⠞⠑⠎
rule trans deaurating ⠙⠑⠁⠥⠗⠁⠞⠬
rule trans deauthorization ⠙⠑⠁⠥⠹⠕⠗⠊⠵⠁⠰⠝
rule trans deauthorize ⠙⠑⠁⠥⠹⠕⠗⠊⠵⠑
rule trans deauthorized ⠙⠑⠁⠥⠹⠕⠗⠊⠵⠫
rule trans deauthorizes ⠙⠑⠁⠥⠹⠕⠗⠊⠵⠑⠎
rule trans deauthorizing ⠙⠑⠁⠥⠹⠕⠗⠊⠵⠬
rule trans dermoreaction ⠙⠻⠍⠕⠗⠑⠁⠉⠰⠝
rule trans dermoreactions ⠙⠻⠍⠕⠗⠑⠁⠉⠰⠝⠎
rule trans driveaway ⠙⠗⠊⠧⠑⠁⠺⠁⠽
rule trans driveaways ⠙⠗⠊⠧⠑⠁⠺⠁⠽⠎
rule trans fadeaway ⠋⠁⠙⠑⠁⠺⠁⠽
rule trans fadeaways ⠋⠁⠙⠑⠁⠺⠁⠽⠎
rule trans geanticline ⠛⠑⠁⠝⠞⠊⠉⠇⠔⠑
rule trans houseagent ⠓⠳⠎⠑⠁⠛⠢⠞
rule trans houseagent's ⠓⠳⠎⠑⠁⠛⠢⠞⠄⠎
rule trans houseagents ⠓⠳⠎⠑⠁⠛⠢⠞⠎
rule trans limeades ⠇⠊⠍⠑⠁⠙⠑⠎
rule trans macroreaction ⠍⠁⠉⠗⠕⠗⠑⠁⠉⠰⠝
rule trans macroreactions ⠍⠁⠉⠗⠕⠗⠑⠁⠉⠰⠝⠎
rule trans microreaction ⠍⠊⠉⠗⠕⠗⠑⠁⠉⠰⠝
rule trans microreactions ⠍⠊⠉⠗⠕⠗⠑⠁⠉⠰⠝⠎
rule trans nonreaction ⠝⠕⠝⠗⠑⠁⠉⠰⠝
rule trans nonreactions ⠝⠕⠝⠗⠑⠁⠉⠰⠝⠎
rule trans orangeades ⠕⠗⠁⠝⠛⠑⠁⠙⠑⠎
rule trans photoreaction ⠏⠓⠕⠞⠕⠗⠑⠁⠉⠰⠝
rule trans photoreactions ⠏⠓⠕⠞⠕⠗⠑⠁⠉⠰⠝⠎
rule trans photoreactive ⠏⠓⠕⠞⠕⠗⠑⠁⠉⠞⠊⠧⠑
rule trans poleax ⠏⠕⠇⠑⠁⠭
rule trans poleax's ⠏⠕⠇⠑⠁⠭⠄⠎
rule trans poleaxe ⠏⠕⠇⠑⠁⠭⠑
rule trans poleaxe's ⠏⠕⠇⠑⠁⠭⠑⠄⠎
rule trans poleaxed ⠏⠕⠇⠑⠁⠭⠫
rule trans poleaxes ⠏⠕⠇⠑⠁⠭⠑⠎
rule trans poleaxing ⠏⠕⠇⠑⠁⠭⠬
rule trans preabdomen ⠏⠗⠑⠁⠃⠙⠕⠍⠢
rule trans preaccessible ⠏⠗⠑⠁⠒⠑⠎⠎⠊⠃⠇⠑
rule trans preaccomplished ⠏⠗⠑⠁⠒⠕⠍⠏⠇⠊⠩⠫
rule trans preaccredit ⠏⠗⠑⠁⠒⠗⠫⠊⠞
rule trans preaccredited ⠏⠗⠑⠁⠒⠗⠫⠊⠞⠫
rule trans preachieve ⠏⠗⠑⠁⠡⠊⠑⠧⠑
rule trans preachieved ⠏⠗⠑⠁⠡⠊⠑⠧⠫
rule trans preacid ⠏⠗⠑⠁⠉⠊⠙
rule trans preacknowledge ⠏⠗⠑⠁⠉⠐⠅⠇⠫⠛⠑
rule trans preacknowledged ⠏⠗⠑⠁⠉⠐⠅⠇⠫⠛⠫
rule trans preacknowledgement ⠏⠗⠑⠁⠉⠐⠅⠇⠫⠛⠑⠰⠞
rule trans preacquaint ⠏⠗⠑⠁⠉⠟⠥⠁⠔⠞
rule trans preacquaintance ⠏⠗⠑⠁⠉⠟⠥⠁⠔⠞⠨⠑
rule trans preacquainted ⠏⠗⠑⠁⠉⠟⠥⠁⠔⠞⠫
rule trans preacquired ⠏⠗⠑⠁⠉⠟⠥⠊⠗⠫
rule trans preacquisition ⠏⠗⠑⠁⠉⠟⠥⠊⠎⠊⠰⠝
rule trans preacquit ⠏⠗⠑⠁⠉⠟⠥⠊⠞
rule trans preacquittal ⠏⠗⠑⠁⠉⠟⠥⠊⠞⠞⠁⠇
rule trans preact ⠏⠗⠑⠁⠉⠞
rule trans preacted ⠏⠗⠑⠁⠉⠞⠫
rule trans preacting ⠏⠗⠑⠁⠉⠞⠬
rule trans preaction ⠏⠗⠑⠁⠉⠰⠝
rule trans preactive ⠏⠗⠑⠁⠉⠞⠊⠧⠑
rule trans preacts ⠏⠗⠑⠁⠉⠞⠎
rule trans preadamic ⠏⠗⠑⠁⠙⠁⠍⠊⠉
rule trans preadapt ⠏⠗⠑⠁⠙⠁⠏⠞
rule trans preadaptation ⠏⠗⠑⠁⠙⠁⠏⠞⠁⠰⠝
rule trans preadaptations ⠏⠗⠑⠁⠙⠁⠏⠞⠁⠰⠝⠎
rule trans preadapted ⠏⠗⠑⠁⠙⠁⠏⠞⠫
rule trans preadapting ⠏⠗⠑⠁⠙⠁⠏⠞⠬
rule trans preadapts ⠏⠗⠑⠁⠙⠁⠏⠞⠎
rule trans preaddition ⠏⠗⠑⠁⠙⠙⠊⠰⠝
rule trans preaddress ⠏⠗⠑⠁⠙⠙⠗⠑⠎⠎
rule trans preaddressed ⠏⠗⠑⠁⠙⠙⠗⠑⠎⠎⠫
rule trans preadequate ⠏⠗⠑⠁⠙⠑⠟⠥⠁⠞⠑
rule trans preadhere ⠏⠗⠑⠁⠙⠐⠓
rule trans preadhered ⠏⠗⠑⠁⠙⠓⠻⠫
rule trans preadherent ⠏⠗⠑⠁⠙⠓⠻⠢⠞
rule trans preadheres ⠏⠗⠑⠁⠙⠐⠓⠎
rule trans preadhering ⠏⠗⠑⠁⠙⠓⠻⠬
rule trans preadjust ⠏⠗⠑⠁⠙⠚⠥⠌
rule trans preadjusted ⠏⠗⠑⠁⠙⠚⠥⠌⠫
rule trans preadjusting ⠏⠗⠑⠁⠙⠚⠥⠌⠬
rule trans preadjustment ⠏⠗⠑⠁⠙⠚⠥⠌⠰⠞
rule trans preadjustments ⠏⠗⠑⠁⠙⠚⠥⠌⠰⠞⠎
rule trans preadjusts ⠏⠗⠑⠁⠙⠚⠥⠌⠎
rule trans preadmission ⠏⠗⠑⠁⠙⠍⠊⠎⠨⠝
rule trans preadmissions ⠏⠗⠑⠁⠙⠍⠊⠎⠨⠝⠎
rule trans preadmit ⠏⠗⠑⠁⠙⠍⠊⠞
rule trans preadmits ⠏⠗⠑⠁⠙⠍⠊⠞⠎
rule trans preadmitted ⠏⠗⠑⠁⠙⠍⠊⠞⠞⠫
rule trans preadmitting ⠏⠗⠑⠁⠙⠍⠊⠞⠞⠬
rule trans preadolescent ⠏⠗⠑⠁⠙⠕⠇⠑⠎⠉⠢⠞
rule trans preadolescents ⠏⠗⠑⠁⠙⠕⠇⠑⠎⠉⠢⠞⠎
rule trans preadult ⠏⠗⠑⠁⠙⠥⠇⠞
rule trans preadulthood ⠏⠗⠑⠁⠙⠥⠇⠞⠓⠕⠕⠙
rule trans preadults ⠏⠗⠑⠁⠙⠥⠇⠞⠎
rule trans preadvice ⠏⠗⠑⠁⠙⠧⠊⠉⠑
rule trans preadvise ⠏⠗⠑⠁⠙⠧⠊⠎⠑
rule trans preadvised ⠏⠗⠑⠁⠙⠧⠊⠎⠫
rule trans preadvises ⠏⠗⠑⠁⠙⠧⠊⠎⠑⠎
rule trans preadvising ⠏⠗⠑⠁⠙⠧⠊⠎⠬
rule trans preaffirm ⠏⠗⠑⠁⠖⠊⠗⠍
rule trans preaffirmation ⠏⠗⠑⠁⠖⠊⠗⠍⠁⠰⠝
rule trans preaffirmed ⠏⠗⠑⠁⠖⠊⠗⠍⠫
rule trans preaffirming ⠏⠗⠑⠁⠖⠊⠗⠍⠬
rule trans preaffirms ⠏⠗⠑⠁⠖⠊⠗⠍⠎
rule trans preaggression ⠏⠗⠑⠁⠶⠗⠑⠎⠨⠝
rule trans preagree ⠏⠗⠑⠁⠛⠗⠑⠑
rule trans preagreed ⠏⠗⠑⠁⠛⠗⠑⠫
rule trans preagreeing ⠏⠗⠑⠁⠛⠗⠑⠑⠬
rule trans preagreement ⠏⠗⠑⠁⠛⠗⠑⠑⠰⠞
rule trans preagreements ⠏⠗⠑⠁⠛⠗⠑⠑⠰⠞⠎
rule trans preagrees ⠏⠗⠑⠁⠛⠗⠑⠑⠎
rule trans preagricultural ⠏⠗⠑⠁⠛⠗⠊⠉⠥⠇⠞⠥⠗⠁⠇
rule trans preagriculture ⠏⠗⠑⠁⠛⠗⠊⠉⠥⠇⠞⠥⠗⠑
rule trans preallocate ⠏⠗⠑⠁⠇⠇⠕⠉⠁⠞⠑
rule trans preallocated ⠏⠗⠑⠁⠇⠇⠕⠉⠁⠞⠫
rule trans preallot ⠏⠗⠑⠁⠇⠇⠕⠞
rule trans preallotted ⠏⠗⠑⠁⠇⠇⠕⠞⠞⠫
rule trans preamp ⠏⠗⠑⠁⠍⠏
rule trans preamplifier ⠏⠗⠑⠁⠍⠏⠇⠊⠋⠊⠻
rule trans preamplifier's ⠏⠗⠑⠁⠍⠏⠇⠊⠋⠊⠻⠄⠎
rule trans preamplifiers ⠏⠗⠑⠁⠍⠏⠇⠊⠋⠊⠻⠎
rule trans preamps ⠏⠗⠑⠁⠍⠏⠎
rule trans preanesthetic ⠏⠗⠑⠁⠝⠑⠎⠮⠞⠊⠉
rule trans preanesthetic's ⠏⠗⠑⠁⠝⠑⠎⠮⠞⠊⠉⠄⠎
rule trans preanesthetics ⠏⠗⠑⠁⠝⠑⠎⠮⠞⠊⠉⠎
rule trans preannounce ⠏⠗⠑⠁⠝⠝⠳⠝⠉⠑
rule trans preannounced ⠏⠗⠑⠁⠝⠝⠳⠝⠉⠫
rule trans preannouncement ⠏⠗⠑⠁⠝⠝⠳⠝⠉⠑⠰⠞
rule trans preannouncements ⠏⠗⠑⠁⠝⠝⠳⠝⠉⠑⠰⠞⠎
rule trans preannounces ⠏⠗⠑⠁⠝⠝⠳⠝⠉⠑⠎
rule trans preannouncing ⠏⠗⠑⠁⠝⠝⠳⠝⠉⠬
rule trans preantepenultimate ⠏⠗⠑⠁⠝⠞⠑⠏⠢⠥⠇⠞⠊⠍⠁⠞⠑
rule trans preapplication ⠏⠗⠑⠁⠏⠏⠇⠊⠉⠁⠰⠝
rule trans preapplications ⠏⠗⠑⠁⠏⠏⠇⠊⠉⠁⠰⠝⠎
rule trans preapplied ⠏⠗⠑⠁⠏⠏⠇⠊⠫
rule trans preapply ⠏⠗⠑⠁⠏⠏⠇⠽
rule trans preappoint ⠏⠗⠑⠁⠏⠏⠕⠔⠞
rule trans preappointed ⠏⠗⠑⠁⠏⠏⠕⠔⠞⠫
rule trans preappointing ⠏⠗⠑⠁⠏⠏⠕⠔⠞⠬
rule trans preappointment ⠏⠗⠑⠁⠏⠏⠕⠔⠞⠰⠞
rule trans preappointments ⠏⠗⠑⠁⠏⠏⠕⠔⠞⠰⠞⠎
rule trans preappoints ⠏⠗⠑⠁⠏⠏⠕⠔⠞⠎
rule trans preapproval ⠏⠗⠑⠁⠏⠏⠗⠕⠧⠁⠇
rule trans preapproval's ⠏⠗⠑⠁⠏⠏⠗⠕⠧⠁⠇⠄⠎
rule trans preapprovals ⠏⠗⠑⠁⠏⠏⠗⠕⠧⠁⠇⠎
rule trans preapprove ⠏⠗⠑⠁⠏⠏⠗⠕⠧⠑
rule trans preapproved ⠏⠗⠑⠁⠏⠏⠗⠕⠧⠫
rule trans preapproves ⠏⠗⠑⠁⠏⠏⠗⠕⠧⠑⠎
rule trans preapproving ⠏⠗⠑⠁⠏⠏⠗⠕⠧⠬
rule trans prearmed ⠏⠗⠑⠜⠍⠫
rule trans preassembled ⠏⠗⠑⠁⠎⠎⠑⠍⠃⠇⠫
rule trans preassemblies ⠏⠗⠑⠁⠎⠎⠑⠍⠃⠇⠊⠑⠎
rule trans preassembly ⠏⠗⠑⠁⠎⠎⠑⠍⠃⠇⠽
rule trans preassign ⠏⠗⠑⠁⠎⠎⠊⠛⠝
rule trans preassigned ⠏⠗⠑⠁⠎⠎⠊⠛⠝⠫
rule trans preassigning ⠏⠗⠑⠁⠎⠎⠊⠛⠝⠬
rule trans preassigns ⠏⠗⠑⠁⠎⠎⠊⠛⠝⠎
rule trans preatomic ⠏⠗⠑⠁⠞⠕⠍⠊⠉
rule trans preaudit ⠏⠗⠑⠁⠥⠙⠊⠞
rule trans preauthorize ⠏⠗⠑⠁⠥⠹⠕⠗⠊⠵⠑
rule trans preauthorized ⠏⠗⠑⠁⠥⠹⠕⠗⠊⠵⠫
rule trans preauthorizes ⠏⠗⠑⠁⠥⠹⠕⠗⠊⠵⠑⠎
rule trans preauthorizing ⠏⠗⠑⠁⠥⠹⠕⠗⠊⠵⠬
rule trans preaxial ⠏⠗⠑⠁⠭⠊⠁⠇
rule trans reabbreviate ⠗⠑⠁⠆⠗⠑⠧⠊⠁⠞⠑
rule trans reabbreviated ⠗⠑⠁⠆⠗⠑⠧⠊⠁⠞⠫
rule trans reabbreviates ⠗⠑⠁⠆⠗⠑⠧⠊⠁⠞⠑⠎
rule trans reabbreviating ⠗⠑⠁⠆⠗⠑⠧⠊⠁⠞⠬
rule trans reabsorb ⠗⠑⠁⠃⠎⠕⠗⠃
rule trans reabsorbed ⠗⠑⠁⠃⠎⠕⠗⠃⠫
rule trans reabsorbing ⠗⠑⠁⠃⠎⠕⠗⠃⠬
rule trans reabsorbs ⠗⠑⠁⠃⠎⠕⠗⠃⠎
rule trans reabsorption ⠗⠑⠁⠃⠎⠕⠗⠏⠰⠝
rule trans reaccelerate ⠗⠑⠁⠒⠑⠇⠻⠁⠞⠑
rule trans reaccelerated ⠗⠑⠁⠒⠑⠇⠻⠁⠞⠫
rule trans reaccelerates ⠗⠑⠁⠒⠑⠇⠻⠁⠞⠑⠎
rule trans reaccelerating ⠗⠑⠁⠒⠑⠇⠻⠁⠞⠬
rule trans reacceleration ⠗⠑⠁⠒⠑⠇⠻⠁⠰⠝
rule trans reaccept ⠗⠑⠁⠒⠑⠏⠞
rule trans reacceptance ⠗⠑⠁⠒⠑⠏⠞⠨⠑
rule trans reaccepted ⠗⠑⠁⠒⠑⠏⠞⠫
rule trans reaccepting ⠗⠑⠁⠒⠑⠏⠞⠬
rule trans reaccepts ⠗⠑⠁⠒⠑⠏⠞⠎
rule trans reaccess ⠗⠑⠁⠒⠑⠎⠎
rule trans reaccessed ⠗⠑⠁⠒⠑⠎⠎⠫
rule trans reaccesses ⠗⠑⠁⠒⠑⠎⠎⠑⠎
rule trans reaccessing ⠗⠑⠁⠒⠑⠎⠎⠬
rule trans reaccession ⠗⠑⠁⠒⠑⠎⠨⠝
rule trans reacclimatization ⠗⠑⠁⠒⠇⠊⠍⠁⠞⠊⠵⠁⠰⠝
rule trans reacclimatize ⠗⠑⠁⠒⠇⠊⠍⠁⠞⠊⠵⠑
rule trans reacclimatized ⠗⠑⠁⠒⠇⠊⠍⠁⠞⠊⠵⠫
rule trans reacclimatizes ⠗⠑⠁⠒⠇⠊⠍⠁⠞⠊⠵⠑⠎
rule trans reacclimatizing ⠗⠑⠁⠒⠇⠊⠍⠁⠞⠊⠵⠬
rule trans reaccommodate ⠗⠑⠁⠒⠕⠍⠍⠕⠙⠁⠞⠑
rule trans reaccommodated ⠗⠑⠁⠒⠕⠍⠍⠕⠙⠁⠞⠫
rule trans reaccommodates ⠗⠑⠁⠒⠕⠍⠍⠕⠙⠁⠞⠑⠎
rule trans reaccommodating ⠗⠑⠁⠒⠕⠍⠍⠕⠙⠁⠞⠬
rule trans reaccommodation ⠗⠑⠁⠒⠕⠍⠍⠕⠙⠁⠰⠝
rule trans reaccommodations ⠗⠑⠁⠒⠕⠍⠍⠕⠙⠁⠰⠝⠎
rule trans reaccount ⠗⠑⠁⠒⠨⠞
rule trans reaccounted ⠗⠑⠁⠒⠨⠞⠫
rule trans reaccounting ⠗⠑⠁⠒⠨⠞⠬
rule trans reaccounts ⠗⠑⠁⠒⠨⠞⠎
rule trans reaccredit ⠗⠑⠁⠒⠗⠫⠊⠞
rule trans reaccreditation ⠗⠑⠁⠒⠗⠫⠊⠞⠁⠰⠝
rule trans reaccreditations ⠗⠑⠁⠒⠗⠫⠊⠞⠁⠰⠝⠎
rule trans reaccredited ⠗⠑⠁⠒⠗⠫⠊⠞⠫
rule trans reaccrediting ⠗⠑⠁⠒⠗⠫⠊⠞⠬
rule trans reaccredits ⠗⠑⠁⠒⠗⠫⠊⠞⠎
rule trans reacetylate ⠗⠑⠁⠉⠑⠞⠽⠇⠁⠞⠑
rule trans reacetylation ⠗⠑⠁⠉⠑⠞⠽⠇⠁⠰⠝
rule trans reachieve ⠗⠑⠁⠡⠊⠑⠧⠑
rule trans reachieved ⠗⠑⠁⠡⠊⠑⠧⠫
rule trans reachieves ⠗⠑⠁⠡⠊⠑⠧⠑⠎
rule trans reachieving ⠗⠑⠁⠡⠊⠑⠧⠬
rule trans reacidified ⠗⠑⠁⠉⠊⠙⠊⠋⠊⠫
rule trans reacidifies ⠗⠑⠁⠉⠊⠙⠊⠋⠊⠑⠎
rule trans reacidify ⠗⠑⠁⠉⠊⠙⠊⠋⠽
rule trans reacidifying ⠗⠑⠁⠉⠊⠙⠊⠋⠽⠬
rule trans reacknowledge ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠑
rule trans reacknowledged ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠫
rule trans reacknowledgement ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠑⠰⠞
rule trans reacknowledgements ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠑⠰⠞⠎
rule trans reacknowledges ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠑⠎
rule trans reacknowledging ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠬
rule trans reacknowledgment ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠰⠞
rule trans reacknowledgments ⠗⠑⠁⠉⠐⠅⠇⠫⠛⠰⠞⠎
rule trans reacquaint ⠗⠑⠁⠉⠟⠥⠁⠔⠞
rule trans reacquaintance ⠗⠑⠁⠉⠟⠥⠁⠔⠞⠨⠑
rule trans reacquainted ⠗⠑⠁⠉⠟⠥⠁⠔⠞⠫
rule trans reacquainting ⠗⠑⠁⠉⠟⠥⠁⠔⠞⠬
rule trans reacquaints ⠗⠑⠁⠉⠟⠥⠁⠔⠞⠎
rule trans reacquire ⠗⠑⠁⠉⠟⠥⠊⠗⠑
rule trans reacquired ⠗⠑⠁⠉⠟⠥⠊⠗⠫
rule trans reacquires ⠗⠑⠁⠉⠟⠥⠊⠗⠑⠎
rule trans reacquiring ⠗⠑⠁⠉⠟⠥⠊⠗⠬
rule trans reacquisition ⠗⠑⠁⠉⠟⠥⠊⠎⠊⠰⠝
rule trans reacquisition's ⠗⠑⠁⠉⠟⠥⠊⠎⠊⠰⠝⠄⠎
rule trans reacquisitions ⠗⠑⠁⠉⠟⠥⠊⠎⠊⠰⠝⠎
rule trans reactance ⠗⠑⠁⠉⠞⠨⠑
rule trans reactant ⠗⠑⠁⠉⠞⠁⠝⠞
rule trans reactuate ⠗⠑⠁⠉⠞⠥⠁⠞⠑
rule trans reactuated ⠗⠑⠁⠉⠞⠥⠁⠞⠫
rule trans reactuates ⠗⠑⠁⠉⠞⠥⠁⠞⠑⠎
rule trans reactuating ⠗⠑⠁⠉⠞⠥⠁⠞⠬
rule trans readapt ⠗⠑⠁⠙⠁⠏⠞
rule trans readaptation ⠗⠑⠁⠙⠁⠏⠞⠁⠰⠝
rule trans readapted ⠗⠑⠁⠙⠁⠏⠞⠫
rule trans readapting ⠗⠑⠁⠙⠁⠏⠞⠬
rule trans readapts ⠗⠑⠁⠙⠁⠏⠞⠎
rule trans readd ⠗⠑⠁⠙⠙
rule trans readded ⠗⠑⠁⠙⠙⠫
rule trans readding ⠗⠑⠁⠙⠙⠬
rule trans readdress ⠗⠑⠁⠙⠙⠗⠑⠎⠎
rule trans readdressed ⠗⠑⠁⠙⠙⠗⠑⠎⠎⠫
rule trans readdresses ⠗⠑⠁⠙⠙⠗⠑⠎⠎⠑⠎
rule trans readdressing ⠗⠑⠁⠙⠙⠗⠑⠎⠎⠬
rule trans readds ⠗⠑⠁⠙⠙⠎
rule trans readhere ⠗⠑⠁⠙⠐⠓
rule trans readhered ⠗⠑⠁⠙⠓⠻⠫
rule trans readheres ⠗⠑⠁⠙⠐⠓⠎
rule trans readhering ⠗⠑⠁⠙⠓⠻⠬
rule trans readhesion ⠗⠑⠁⠙⠓⠑⠨⠝
rule trans readjourn ⠗⠑⠁⠙⠚⠳⠗⠝
rule trans readjourned ⠗⠑⠁⠙⠚⠳⠗⠝⠫
rule trans readjourning ⠗⠑⠁⠙⠚⠳⠗⠝⠬
rule trans readjournment ⠗⠑⠁⠙⠚⠳⠗⠝⠰⠞
rule trans readjournments ⠗⠑⠁⠙⠚⠳⠗⠝⠰⠞⠎
rule trans readjourns ⠗⠑⠁⠙⠚⠳⠗⠝⠎
rule trans readminister ⠗⠑⠁⠙⠍⠔⠊⠌⠻
rule trans readministered ⠗⠑⠁⠙⠍⠔⠊⠌⠻⠫
rule trans readministering ⠗⠑⠁⠙⠍⠔⠊⠌⠻⠬
rule trans readministers ⠗⠑⠁⠙⠍⠔⠊⠌⠻⠎
rule trans readministration ⠗⠑⠁⠙⠍⠔⠊⠌⠗⠁⠰⠝
rule trans readministrations ⠗⠑⠁⠙⠍⠔⠊⠌⠗⠁⠰⠝⠎
rule trans readmission ⠗⠑⠁⠙⠍⠊⠎⠨⠝
rule trans readmission's ⠗⠑⠁⠙⠍⠊⠎⠨⠝⠄⠎
rule trans readmissions ⠗⠑⠁⠙⠍⠊⠎⠨⠝⠎
rule trans readmittance ⠗⠑⠁⠙⠍⠊⠞⠞⠨⠑
rule trans readopt ⠗⠑⠁⠙⠕⠏⠞
rule trans readopted ⠗⠑⠁⠙⠕⠏⠞⠫
rule trans readopting ⠗⠑⠁⠙⠕⠏⠞⠬
rule trans readoption ⠗⠑⠁⠙⠕⠏⠰⠝
rule trans readoptions ⠗⠑⠁⠙⠕⠏⠰⠝⠎
rule trans readopts ⠗⠑⠁⠙⠕⠏⠞⠎
rule trans readorn ⠗⠑⠁⠙⠕⠗⠝
rule trans readorned ⠗⠑⠁⠙⠕⠗⠝⠫
rule trans readorning ⠗⠑⠁⠙⠕⠗⠝⠬
rule trans readornment ⠗⠑⠁⠙⠕⠗⠝⠰⠞
rule trans readornments ⠗⠑⠁⠙⠕⠗⠝⠰⠞⠎
rule trans readorns ⠗⠑⠁⠙⠕⠗⠝⠎
rule trans readvance ⠗⠑⠁⠙⠧⠨⠑
rule trans readvanced ⠗⠑⠁⠙⠧⠨⠑⠙
rule trans readvances ⠗⠑⠁⠙⠧⠨⠑⠎
rule trans readvancing ⠗⠑⠁⠙⠧⠁⠝⠉⠬
rule trans readventure ⠗⠑⠁⠙⠧⠢⠞⠥⠗⠑
rule trans readvertise ⠗⠑⠁⠙⠧⠻⠞⠊⠎⠑
rule trans readvertised ⠗⠑⠁⠙⠧⠻⠞⠊⠎⠫
rule trans readvertises ⠗⠑⠁⠙⠧⠻⠞⠊⠎⠑⠎
rule trans readvertising ⠗⠑⠁⠙⠧⠻⠞⠊⠎⠬
rule trans readvise ⠗⠑⠁⠙⠧⠊⠎⠑
rule trans readvised ⠗⠑⠁⠙⠧⠊⠎⠫
rule trans readvises ⠗⠑⠁⠙⠧⠊⠎⠑⠎
rule trans readvising ⠗⠑⠁⠙⠧⠊⠎⠬
rule trans reaerate ⠗⠑⠁⠻⠁⠞⠑
rule trans reaeration ⠗⠑⠁⠻⠁⠰⠝
rule trans reaffect ⠗⠑⠁⠖⠑⠉⠞
rule trans reaffected ⠗⠑⠁⠖⠑⠉⠞⠫
rule trans reaffecting ⠗⠑⠁⠖⠑⠉⠞⠬
rule trans reaffects ⠗⠑⠁⠖⠑⠉⠞⠎
rule trans reaffiliate ⠗⠑⠁⠖⠊⠇⠊⠁⠞⠑
rule trans reaffiliated ⠗⠑⠁⠖⠊⠇⠊⠁⠞⠫
rule trans reaffiliates ⠗⠑⠁⠖⠊⠇⠊⠁⠞⠑⠎
rule trans reaffiliating ⠗⠑⠁⠖⠊⠇⠊⠁⠞⠬
rule trans reaffiliation ⠗⠑⠁⠖⠊⠇⠊⠁⠰⠝
rule trans reaffix ⠗⠑⠁⠖⠊⠭
rule trans reaffixed ⠗⠑⠁⠖⠊⠭⠫
rule trans reaffixes ⠗⠑⠁⠖⠊⠭⠑⠎
rule trans reaffixing ⠗⠑⠁⠖⠊⠭⠬
rule trans reafforest ⠗⠑⠁⠋⠿⠑⠌
rule trans reafforestation ⠗⠑⠁⠋⠿⠑⠌⠁⠰⠝
rule trans reafforested ⠗⠑⠁⠋⠿⠑⠌⠫
rule trans reafforesting ⠗⠑⠁⠋⠿⠑⠌⠬
rule trans reafforests ⠗⠑⠁⠋⠿⠑⠌⠎
rule trans reagency ⠗⠑⠁⠛⠢⠉⠽
rule trans reaggregate ⠗⠑⠁⠶⠗⠑⠛⠁⠞⠑
rule trans reaggregated ⠗⠑⠁⠶⠗⠑⠛⠁⠞⠫
rule trans reaggregates ⠗⠑⠁⠶⠗⠑⠛⠁⠞⠑⠎
rule trans reaggregating ⠗⠑⠁⠶⠗⠑⠛⠁⠞⠬
rule trans reaggregation ⠗⠑⠁⠶⠗⠑⠛⠁⠰⠝
rule trans reagitate ⠗⠑⠁⠛⠊⠞⠁⠞⠑
rule trans reagitated ⠗⠑⠁⠛⠊⠞⠁⠞⠫
rule trans reagitates ⠗⠑⠁⠛⠊⠞⠁⠞⠑⠎
rule trans reagitating ⠗⠑⠁⠛⠊⠞⠁⠞⠬
rule trans reagitation ⠗⠑⠁⠛⠊⠞⠁⠰⠝
rule trans reagree ⠗⠑⠁⠛⠗⠑⠑
rule trans reagreed ⠗⠑⠁⠛⠗⠑⠫
rule trans reagreeing ⠗⠑⠁⠛⠗⠑⠑⠬
rule trans reagreement ⠗⠑⠁⠛⠗⠑⠑⠰⠞
rule trans reagreements ⠗⠑⠁⠛⠗⠑⠑⠰⠞⠎
rule trans reagrees ⠗⠑⠁⠛⠗⠑⠑⠎
rule trans realarm ⠗⠑⠁⠇⠜⠍
rule trans realarmed ⠗⠑⠁⠇⠜⠍⠫
rule trans realarming ⠗⠑⠁⠇⠜⠍⠬
rule trans realarms ⠗⠑⠁⠇⠜⠍⠎
rule trans realert ⠗⠑⠁⠇⠻⠞
rule trans realerted ⠗⠑⠁⠇⠻⠞⠫
rule trans realerting ⠗⠑⠁⠇⠻⠞⠬
rule trans realerts ⠗⠑⠁⠇⠻⠞⠎
rule trans realienate ⠗⠑⠁⠇⠊⠢⠁⠞⠑
rule trans realienated ⠗⠑⠁⠇⠊⠢⠁⠞⠫
rule trans realienates ⠗⠑⠁⠇⠊⠢⠁⠞⠑⠎
rule trans realienating ⠗⠑⠁⠇⠊⠢⠁⠞⠬
rule trans realienation ⠗⠑⠁⠇⠊⠢⠁⠰⠝
rule trans realigned ⠗⠑⠁⠇⠊⠛⠝⠫
rule trans realigning ⠗⠑⠁⠇⠊⠛⠝⠬
rule trans realignment ⠗⠑⠁⠇⠊⠛⠝⠰⠞
rule trans realignment's ⠗⠑⠁⠇⠊⠛⠝⠰⠞⠄⠎
rule trans realignments ⠗⠑⠁⠇⠊⠛⠝⠰⠞⠎
rule trans realigns ⠗⠑⠁⠇⠊⠛⠝⠎
rule trans reallege ⠗⠑⠁⠇⠇⠑⠛⠑
rule trans realleged ⠗⠑⠁⠇⠇⠑⠛⠫
rule trans realleges ⠗⠑⠁⠇⠇⠑⠛⠑⠎
rule trans realleging ⠗⠑⠁⠇⠇⠑⠛⠬
rule trans realliance ⠗⠑⠁⠇⠇⠊⠨⠑
rule trans realliances ⠗⠑⠁⠇⠇⠊⠨⠑⠎
rule trans reallocations ⠗⠑⠁⠇⠇⠕⠉⠁⠰⠝⠎
rule trans reallot ⠗⠑⠁⠇⠇⠕⠞
rule trans reallotment ⠗⠑⠁⠇⠇⠕⠞⠰⠞
rule trans reallotments ⠗⠑⠁⠇⠇⠕⠞⠰⠞⠎
rule trans reallots ⠗⠑⠁⠇⠇⠕⠞⠎
rule trans reallotted ⠗⠑⠁⠇⠇⠕⠞⠞⠫
rule trans reallotting ⠗⠑⠁⠇⠇⠕⠞⠞⠬
rule trans realter ⠗⠑⠁⠇⠞⠻
rule trans realteration ⠗⠑⠁⠇⠞⠻⠁⠰⠝
rule trans realterations ⠗⠑⠁⠇⠞⠻⠁⠰⠝⠎
rule trans realtered ⠗⠑⠁⠇⠞⠻⠫
rule trans realtering ⠗⠑⠁⠇⠞⠻⠬
rule trans realters ⠗⠑⠁⠇⠞⠻⠎
rule trans reamalgamate ⠗⠑⠁⠍⠁⠇⠛⠁⠍⠁⠞⠑
rule trans reamalgamated ⠗⠑⠁⠍⠁⠇⠛⠁⠍⠁⠞⠫
rule trans reamalgamates ⠗⠑⠁⠍⠁⠇⠛⠁⠍⠁⠞⠑⠎
rule trans reamalgamating ⠗⠑⠁⠍⠁⠇⠛⠁⠍⠁⠞⠬
rule trans reamalgamation ⠗⠑⠁⠍⠁⠇⠛⠁⠍⠁⠰⠝
rule trans reamalgamations ⠗⠑⠁⠍⠁⠇⠛⠁⠍⠁⠰⠝⠎
rule trans reamass ⠗⠑⠁⠍⠁⠎⠎
rule trans reamassed ⠗⠑⠁⠍⠁⠎⠎⠫
rule trans reamasses ⠗⠑⠁⠍⠁⠎⠎⠑⠎
rule trans reamassing ⠗⠑⠁⠍⠁⠎⠎⠬
rule trans reambitious ⠗⠑⠁⠍⠃⠊⠞⠊⠳⠎
rule trans reamend ⠗⠑⠁⠍⠢⠙
rule trans reamended ⠗⠑⠁⠍⠢⠙⠫
rule trans reamending ⠗⠑⠁⠍⠢⠙⠬
rule trans reamendment ⠗⠑⠁⠍⠢⠙⠰⠞
rule trans reamendments ⠗⠑⠁⠍⠢⠙⠰⠞⠎
rule trans reamends ⠗⠑⠁⠍⠢⠙⠎
rule trans reamputation ⠗⠑⠁⠍⠏⠥⠞⠁⠰⠝
rule trans reamuse ⠗⠑⠁⠍⠥⠎⠑
rule trans reamused ⠗⠑⠁⠍⠥⠎⠫
rule trans reamuses ⠗⠑⠁⠍⠥⠎⠑⠎
rule trans reamusing ⠗⠑⠁⠍⠥⠎⠬
rule trans reanalyses ⠗⠑⠁⠝⠁⠇⠽⠎⠑⠎
rule trans reanalysis ⠗⠑⠁⠝⠁⠇⠽⠎⠊⠎
rule trans reanalyze ⠗⠑⠁⠝⠁⠇⠽⠵⠑
rule trans reanalyzed ⠗⠑⠁⠝⠁⠇⠽⠵⠫
rule trans reanalyzes ⠗⠑⠁⠝⠁⠇⠽⠵⠑⠎
rule trans reanalyzing ⠗⠑⠁⠝⠁⠇⠽⠵⠬
rule trans reapologize ⠗⠑⠁⠏⠕⠇⠕⠛⠊⠵⠑
rule trans reapologized ⠗⠑⠁⠏⠕⠇⠕⠛⠊⠵⠫
rule trans reapologizes ⠗⠑⠁⠏⠕⠇⠕⠛⠊⠵⠑⠎
rule trans reapologizing ⠗⠑⠁⠏⠕⠇⠕⠛⠊⠵⠬
rule trans reapplication ⠗⠑⠁⠏⠏⠇⠊⠉⠁⠰⠝
rule trans reapplication's ⠗⠑⠁⠏⠏⠇⠊⠉⠁⠰⠝⠄⠎
rule trans reapplications ⠗⠑⠁⠏⠏⠇⠊⠉⠁⠰⠝⠎
rule trans rearguard ⠗⠑⠜⠛⠥⠜⠙
rule trans reargue ⠗⠑⠜⠛⠥⠑
rule trans reargued ⠗⠑⠜⠛⠥⠫
rule trans reargues ⠗⠑⠜⠛⠥⠑⠎
rule trans rearguing ⠗⠑⠜⠛⠥⠬
rule trans reargument ⠗⠑⠜⠛⠥⠰⠞
rule trans rearguments ⠗⠑⠜⠛⠥⠰⠞⠎
rule trans rearrest ⠗⠑⠜⠗⠑⠌
rule trans rearrested ⠗⠑⠜⠗⠑⠌⠫
rule trans rearresting ⠗⠑⠜⠗⠑⠌⠬
rule trans rearrests ⠗⠑⠜⠗⠑⠌⠎
rule trans rearticulate ⠗⠑⠜⠞⠊⠉⠥⠇⠁⠞⠑
rule trans rearticulated ⠗⠑⠜⠞⠊⠉⠥⠇⠁⠞⠫
rule trans rearticulates ⠗⠑⠜⠞⠊⠉⠥⠇⠁⠞⠑⠎
rule trans rearticulating ⠗⠑⠜⠞⠊⠉⠥⠇⠁⠞⠬
rule trans rearticulation ⠗⠑⠜⠞⠊⠉⠥⠇⠁⠰⠝
rule trans rearview ⠗⠑⠜⠧⠊⠑⠺
rule trans reascend ⠗⠑⠁⠎⠉⠢⠙
rule trans reascendance ⠗⠑⠁⠎⠉⠢⠙⠨⠑
rule trans reascendancy ⠗⠑⠁⠎⠉⠢⠙⠁⠝⠉⠽
rule trans reascendant ⠗⠑⠁⠎⠉⠢⠙⠁⠝⠞
rule trans reascended ⠗⠑⠁⠎⠉⠢⠙⠫
rule trans reascending ⠗⠑⠁⠎⠉⠢⠙⠬
rule trans reascends ⠗⠑⠁⠎⠉⠢⠙⠎
rule trans reascension ⠗⠑⠁⠎⠉⠢⠨⠝
rule trans reascensions ⠗⠑⠁⠎⠉⠢⠨⠝⠎
rule trans reascent ⠗⠑⠁⠎⠉⠢⠞
rule trans reascertain ⠗⠑⠁⠎⠉⠻⠞⠁⠔
rule trans reascertained ⠗⠑⠁⠎⠉⠻⠞⠁⠔⠫
rule trans reascertaining ⠗⠑⠁⠎⠉⠻⠞⠁⠔⠬
rule trans reascertainment ⠗⠑⠁⠎⠉⠻⠞⠁⠔⠰⠞
rule trans reascertainments ⠗⠑⠁⠎⠉⠻⠞⠁⠔⠰⠞⠎
rule trans reascertains ⠗⠑⠁⠎⠉⠻⠞⠁⠔⠎
rule trans reask ⠗⠑⠁⠎⠅
rule trans reaspire ⠗⠑⠁⠎⠏⠊⠗⠑
rule trans reaspired ⠗⠑⠁⠎⠏⠊⠗⠫
rule trans reaspires ⠗⠑⠁⠎⠏⠊⠗⠑⠎
rule trans reaspiring ⠗⠑⠁⠎⠏⠊⠗⠬
rule trans reastonish ⠗⠑⠁⠌⠕⠝⠊⠩
rule trans reastonished ⠗⠑⠁⠌⠕⠝⠊⠩⠫
rule trans reastonishes ⠗⠑⠁⠌⠕⠝⠊⠩⠑⠎
rule trans reastonishing ⠗⠑⠁⠌⠕⠝⠊⠩⠬
rule trans reattach ⠗⠑⠁⠞⠞⠁⠡
rule trans reattached ⠗⠑⠁⠞⠞⠁⠡⠫
rule trans reattaches ⠗⠑⠁⠞⠞⠁⠡⠑⠎
rule trans reattaching ⠗⠑⠁⠞⠞⠁⠡⠬
rule trans reattachment ⠗⠑⠁⠞⠞⠁⠡⠰⠞
rule trans reattachments ⠗⠑⠁⠞⠞⠁⠡⠰⠞⠎
rule trans reattack ⠗⠑⠁⠞⠞⠁⠉⠅
rule trans reattacked ⠗⠑⠁⠞⠞⠁⠉⠅⠫
rule trans reattacking ⠗⠑⠁⠞⠞⠁⠉⠅⠬
rule trans reattacks ⠗⠑⠁⠞⠞⠁⠉⠅⠎
rule trans reattain ⠗⠑⠁⠞⠞⠁⠔
rule trans reattained ⠗⠑⠁⠞⠞⠁⠔⠫
rule trans reattaining ⠗⠑⠁⠞⠞⠁⠔⠬
rule trans reattainment ⠗⠑⠁⠞⠞⠁⠔⠰⠞
rule trans reattainments ⠗⠑⠁⠞⠞⠁⠔⠰⠞⠎
rule trans reattains ⠗⠑⠁⠞⠞⠁⠔⠎
rule trans reattempt ⠗⠑⠁⠞⠞⠑⠍⠏⠞
rule trans reattempted ⠗⠑⠁⠞⠞⠑⠍⠏⠞⠫
rule trans reattempting ⠗⠑⠁⠞⠞⠑⠍⠏⠞⠬
rule trans reattempts ⠗⠑⠁⠞⠞⠑⠍⠏⠞⠎
rule trans reattribute ⠗⠑⠁⠞⠞⠗⠊⠃⠥⠞⠑
rule trans reattributed ⠗⠑⠁⠞⠞⠗⠊⠃⠥⠞⠫
rule trans reattributes ⠗⠑⠁⠞⠞⠗⠊⠃⠥⠞⠑⠎
rule trans reattributing ⠗⠑⠁⠞⠞⠗⠊⠃⠥⠞⠬
rule trans reattribution ⠗⠑⠁⠞⠞⠗⠊⠃⠥⠰⠝
rule trans reattributions ⠗⠑⠁⠞⠞⠗⠊⠃⠥⠰⠝⠎
rule trans reaudit ⠗⠑⠁⠥⠙⠊⠞
rule trans reaudited ⠗⠑⠁⠥⠙⠊⠞⠫
rule trans reauditing ⠗⠑⠁⠥⠙⠊⠞⠬
rule trans reaudition ⠗⠑⠁⠥⠙⠊⠰⠝
rule trans reauditioning ⠗⠑⠁⠥⠙⠊⠰⠝⠬
rule trans reauditions ⠗⠑⠁⠥⠙⠊⠰⠝⠎
rule trans reaudits ⠗⠑⠁⠥⠙⠊⠞⠎
rule trans reauthenticate ⠗⠑⠁⠥⠮⠝⠞⠊⠉⠁⠞⠑
rule trans reauthenticated ⠗⠑⠁⠥⠮⠝⠞⠊⠉⠁⠞⠫
rule trans reauthenticates ⠗⠑⠁⠥⠮⠝⠞⠊⠉⠁⠞⠑⠎
rule trans reauthenticating ⠗⠑⠁⠥⠮⠝⠞⠊⠉⠁⠞⠬
rule trans reauthentication ⠗⠑⠁⠥⠮⠝⠞⠊⠉⠁⠰⠝
rule trans reauthentications ⠗⠑⠁⠥⠮⠝⠞⠊⠉⠁⠰⠝⠎
rule trans reauthorization ⠗⠑⠁⠥⠹⠕⠗⠊⠵⠁⠰⠝
rule trans reauthorization's ⠗⠑⠁⠥⠹⠕⠗⠊⠵⠁⠰⠝⠄⠎
rule trans reauthorizations ⠗⠑⠁⠥⠹⠕⠗⠊⠵⠁⠰⠝⠎
rule trans reauthorize ⠗⠑⠁⠥⠹⠕⠗⠊⠵⠑
rule trans reauthorized ⠗⠑⠁⠥⠹⠕⠗⠊⠵⠫
rule trans reauthorizes ⠗⠑⠁⠥⠹⠕⠗⠊⠵⠑⠎
rule trans reauthorizing ⠗⠑⠁⠥⠹⠕⠗⠊⠵⠬
rule trans reavail ⠗⠑⠁⠧⠁⠊⠇
rule trans reavails ⠗⠑⠁⠧⠁⠊⠇⠎
rule trans reaver ⠗⠑⠁⠧⠻
rule trans reavers ⠗⠑⠁⠧⠻⠎
rule trans reavoid ⠗⠑⠁⠧⠕⠊⠙
rule trans reavoidance ⠗⠑⠁⠧⠕⠊⠙⠨⠑
rule trans reavoids ⠗⠑⠁⠧⠕⠊⠙⠎
rule trans reavow ⠗⠑⠁⠧⠪
rule trans reavowal ⠗⠑⠁⠧⠪⠁⠇
rule trans reavowals ⠗⠑⠁⠧⠪⠁⠇⠎
rule trans reavowed ⠗⠑⠁⠧⠪⠫
rule trans reavowing ⠗⠑⠁⠧⠪⠬
rule trans reavows ⠗⠑⠁⠧⠪⠎
rule trans reaward ⠗⠑⠁⠺⠜⠙
rule trans reawarded ⠗⠑⠁⠺⠜⠙⠫
rule trans reawarding ⠗⠑⠁⠺⠜⠙⠬
rule trans reawards ⠗⠑⠁⠺⠜⠙⠎
rule trans reawoke ⠗⠑⠁⠺⠕⠅⠑
rule trans semireactionary ⠎⠑⠍⠊⠗⠑⠁⠉⠰⠝⠜⠽
rule trans superreaction ⠎⠥⠏⠻⠗⠑⠁⠉⠰⠝
rule trans superreactions ⠎⠥⠏⠻⠗⠑⠁⠉⠰⠝⠎
rule trans takeaway ⠞⠁⠅⠑⠁⠺⠁⠽
rule trans takeaway's ⠞⠁⠅⠑⠁⠺⠁⠽⠄⠎
rule trans unreactive ⠥⠝⠗⠑⠁⠉⠞⠊⠧⠑
rule trans unreassured ⠥⠝⠗⠑⠁⠎⠎⠥⠗⠫
rule trans unreassuring ⠥⠝⠗⠑⠁⠎⠎⠥⠗⠬
rule trans unreassuringly ⠥⠝⠗⠑⠁⠎⠎⠥⠗⠬⠇⠽
rule trans wideawake ⠺⠊⠙⠑⠁⠺⠁⠅⠑
use

use word_whole_begin_+ word_whole_begin_-
rule trans boreas 12-135-1235-15-1-234
rule trans deandre 145-15-1-1345-145-1235-15
rule trans deanna 145-15-1-1345-1345-1
rule trans geanticline 1245-15-1-1345-2345-24-14-123-35-15
rule trans gilead 1245-24-123-15-1-145
rule trans hideaway 125-24-145-15-1-2456-1-13456
rule trans leah 123-15-1-125
rule trans leanna 123-15-1-1345-1345-1
rule trans limeade 123-24-134-15-1-145-15
rule trans orangeade 135-1235-1-1345-1245-15-1-145-15
rule trans pream 1234-1235-15-1-134                              # preamble
rule trans reagent 1235-15-1-1245-26-2345
rule trans roseann 1235-135-234-15-1-1345-1345
#rule trans shakespearean 146-1-13-15-234-1234-15-345-15-1-1345
rule trans takeaway 2345-1-13-15-1-2456-1-13456

use word_begin_+ word_begin_-
rule trans deact 145-15-1-14-2345         # deactivate
rule trans deallo 145-15-1-123-123-135    # deallocate
rule trans givea 1245-24-1236-15-1        # giveaway
rule trans readj 1235-15-1-145-245        # eadjust
rule trans readm 1235-15-1-145-134        # readmit
rule trans reaff 1235-15-1-235
rule trans realig 1235-15-1-123-24-1245   # realign
rule trans reallo 1235-15-1-123-123-135   # reallocate - really
rule trans rean 1235-15-1-1345            # reanalyze, reanimate
rule trans reapp 1235-15-1-1234-1234      # reappear
rule trans reass 1235-15-1-234-234
rule trans reaw 1235-15-1-2456            # reawaken

use word_mid_end_+ word_mid_end_-
rule trans eance 15-46-15   # vengeance
rule trans eand 15-12346    # meander

use

## ff   10.6.5   10.6.6   ⠘⠖ligature
uses word_mid_+ word_mid_- rule trans ff 235

use word_whole_begin_+ word_whole_begin_-
rule trans afforce ⠁⠋⠿⠉⠑
rule trans afford 1-124-123456-145
rule trans afforest 1-124-123456-15-34
rule trans clifford 14-123-24-124-123456-145
rule trans effort 15-124-123456-2345
rule trans stafford 34-1-124-123456-145
use

## gg
uses word_mid_+ word_mid_- rule trans gg 2356

## en   10.6.8   10.6.9
uses word_whole_+ word_whole_- rule trans en 15-1345
match trans ^|!%m      en %l*!%[_l]   - 26 -
match trans !%[_lm]%l* en -           - 26 -

use word_whole_begin_+ word_whole_begin_-
rule trans acetocinnamene ⠁⠉⠑⠞⠕⠉⠔⠝⠁⠍⠢⠑
rule trans acetocinnamene's ⠁⠉⠑⠞⠕⠉⠔⠝⠁⠍⠢⠑⠄⠎
rule trans alternamente ⠁⠇⠞⠻⠝⠁⠰⠞⠑
rule trans anamelech ⠁⠝⠁⠍⠑⠇⠑⠡
rule trans anamelech's ⠁⠝⠁⠍⠑⠇⠑⠡⠄⠎
rule trans anamelek ⠁⠝⠁⠍⠑⠇⠑⠅
rule trans anamelek's ⠁⠝⠁⠍⠑⠇⠑⠅⠄⠎
rule trans anamesite ⠁⠝⠁⠍⠑⠎⠊⠞⠑
rule trans anametadromous ⠁⠝⠁⠍⠑⠞⠁⠙⠗⠕⠍⠳⠎
rule trans annamese ⠁⠝⠝⠁⠍⠑⠎⠑
rule trans basename ⠃⠁⠎⠑⠐⠝
rule trans basename's ⠃⠁⠎⠑⠐⠝⠄⠎
rule trans basenames ⠃⠁⠎⠑⠐⠝⠎
rule trans bluenose 12-123-136-15-1345-135-234-15
rule trans bottleneck 12-135-2345-2345-123-15-1345-15-14-13
rule trans chinamen ⠡⠔⠁⠍⠢
rule trans cinnamein ⠉⠔⠝⠁⠍⠑⠔
rule trans cinnamene ⠉⠔⠝⠁⠍⠢⠑
rule trans cinnamenyl ⠉⠔⠝⠁⠍⠢⠽⠇
rule trans codename ⠉⠕⠙⠑⠐⠝
rule trans codename's ⠉⠕⠙⠑⠐⠝⠄⠎
rule trans codenamed ⠉⠕⠙⠑⠐⠝⠙
rule trans codenames ⠉⠕⠙⠑⠐⠝⠎
rule trans coname ⠉⠕⠐⠝
rule trans coname's ⠉⠕⠐⠝⠄⠎
rule trans conames ⠉⠕⠐⠝⠎
rule trans coronamen ⠉⠕⠗⠕⠝⠁⠍⠢
rule trans dename ⠙⠑⠐⠝
rule trans denamed ⠙⠑⠐⠝⠙
rule trans denames ⠙⠑⠐⠝⠎
rule trans dynameter ⠙⠽⠝⠁⠍⠑⠞⠻
rule trans dynameter's ⠙⠽⠝⠁⠍⠑⠞⠻⠄⠎
rule trans dynameters ⠙⠽⠝⠁⠍⠑⠞⠻⠎
rule trans dynametric ⠙⠽⠝⠁⠍⠑⠞⠗⠊⠉
rule trans dynametrical ⠙⠽⠝⠁⠍⠑⠞⠗⠊⠉⠁⠇
rule trans ekename ⠑⠅⠑⠐⠝
rule trans ekenames ⠑⠅⠑⠐⠝⠎
rule trans filename ⠋⠊⠇⠑⠐⠝
rule trans filename's ⠋⠊⠇⠑⠐⠝⠄⠎
rule trans filenames ⠋⠊⠇⠑⠐⠝⠎
rule trans forenoon 123456-15-1345-135-135-1345
rule trans forerunner 123456-15-1235-136-1345-1345-12456
rule trans hemadynameter ⠓⠑⠍⠁⠙⠽⠝⠁⠍⠑⠞⠻
rule trans hemadynameter's ⠓⠑⠍⠁⠙⠽⠝⠁⠍⠑⠞⠻⠄⠎
rule trans hemadynameters ⠓⠑⠍⠁⠙⠽⠝⠁⠍⠑⠞⠻⠎
rule trans lanameter ⠇⠁⠝⠁⠍⠑⠞⠻
rule trans lanameter's ⠇⠁⠝⠁⠍⠑⠞⠻⠄⠎
rule trans lanameters ⠇⠁⠝⠁⠍⠑⠞⠻⠎
rule trans nonamenable ⠝⠕⠝⠁⠍⠢⠁⠃⠇⠑
rule trans nonamendable ⠝⠕⠝⠁⠍⠢⠙⠁⠃⠇⠑
rule trans nonamendment ⠝⠕⠝⠁⠍⠢⠙⠰⠞
rule trans nonamendments ⠝⠕⠝⠁⠍⠢⠙⠰⠞⠎
rule trans nonornamental ⠝⠕⠝⠕⠗⠝⠁⠰⠞⠁⠇
rule trans overornamented ⠕⠧⠻⠕⠗⠝⠁⠰⠞⠫
rule trans prename ⠏⠗⠑⠐⠝
rule trans prenames ⠏⠗⠑⠐⠝⠎
rule trans preornamental ⠏⠗⠑⠕⠗⠝⠁⠰⠞⠁⠇
rule trans pretournament ⠏⠗⠑⠞⠳⠗⠝⠁⠰⠞
rule trans reornament ⠗⠑⠕⠗⠝⠁⠰⠞
rule trans reornamentation ⠗⠑⠕⠗⠝⠁⠰⠞⠁⠰⠝
rule trans reornamented ⠗⠑⠕⠗⠝⠁⠰⠞⠫
rule trans reornamenting ⠗⠑⠕⠗⠝⠁⠰⠞⠬
rule trans reornaments ⠗⠑⠕⠗⠝⠁⠰⠞⠎
rule trans superornamental ⠎⠥⠏⠻⠕⠗⠝⠁⠰⠞⠁⠇
rule trans superornamentally ⠎⠥⠏⠻⠕⠗⠝⠁⠰⠞⠁⠇⠇⠽
rule trans toenail 2345-135-15-1345-1-24-123
rule trans tradename ⠞⠗⠁⠙⠑⠐⠝
rule trans tradename's ⠞⠗⠁⠙⠑⠐⠝⠄⠎
rule trans tradenames ⠞⠗⠁⠙⠑⠐⠝⠎
rule trans turtleneck 2345-136-1235-2345-123-15-1345-15-14-13
rule trans unameliorated ⠥⠝⠁⠍⠑⠇⠊⠕⠗⠁⠞⠫
rule trans unamenability ⠥⠝⠁⠍⠢⠁⠃⠊⠇⠰⠽
rule trans unamenable ⠥⠝⠁⠍⠢⠁⠃⠇⠑
rule trans unamenably ⠥⠝⠁⠍⠢⠁⠃⠇⠽
rule trans unamendable ⠥⠝⠁⠍⠢⠙⠁⠃⠇⠑
rule trans unamended ⠥⠝⠁⠍⠢⠙⠫
rule trans unamerceable ⠥⠝⠁⠍⠻⠉⠂⠃⠇⠑
rule trans unamerced ⠥⠝⠁⠍⠻⠉⠫
rule trans unamerican ⠥⠝⠁⠍⠻⠊⠉⠁⠝
rule trans unornamented ⠥⠝⠕⠗⠝⠁⠰⠞⠫
use

uses word_mid_end_+ word_mid_end_- rule trans eness 15-56-234   # closeness

## in (prefix)   10.6.8    94190   94746
match trans ^|!%m      in %l*!%[_l]   - 35 -
match trans !%[_lm]%l* in -           - 35 -

#   iness overridden by ness

uses word_whole_begin_+ word_whole_begin_- rule trans multinational 134-136-123-2345-35-1-56-1345-1-123


########################################
#   10.7   Initial-Letter Contractions
########################################

## canont
uses not_modifier_<+ - rule trans cannot 456-14

## character
uses not_modifier_<+ - rule trans character 5-16

## day
uses not_modifier_<+ - rule trans day 5-145

use word_whole_begin_+ word_whole_begin_-
rule trans dayan 145-1-13456-1-1345
rule trans whaddaya 156-1-145-145-1-13456-1
use

## ever   10.7.4
uses not_modifier_<+ - rule trans ever 5-15

use word_whole_begin_+ word_whole_begin_-

rule trans achiever 1-16-24-15-1236-12456
rule trans anteversion ⠁⠝⠞⠑⠧⠻⠨⠝
rule trans antevert ⠁⠝⠞⠑⠧⠻⠞
rule trans anteverted ⠁⠝⠞⠑⠧⠻⠞⠫
rule trans anteverting ⠁⠝⠞⠑⠧⠻⠞⠬
rule trans anteverts ⠁⠝⠞⠑⠧⠻⠞⠎
rule trans beevers ⠃⠑⠑⠧⠻⠎
rule trans believer 23-123-24-15-1236-12456
rule trans bellevernon ⠃⠑⠇⠇⠑⠧⠻⠝⠕⠝
rule trans bouleverse ⠃⠳⠇⠑⠧⠻⠎⠑
rule trans cheever 16-15-15-1236-12456
rule trans cheever's ⠡⠑⠑⠧⠻⠄⠎
rule trans cobeliever ⠉⠕⠃⠑⠇⠊⠑⠧⠻
rule trans cobeliever's ⠉⠕⠃⠑⠇⠊⠑⠧⠻⠄⠎
rule trans cobelievers ⠉⠕⠃⠑⠇⠊⠑⠧⠻⠎
rule trans deverbal ⠙⠑⠧⠻⠃⠁⠇
rule trans deverbals ⠙⠑⠧⠻⠃⠁⠇⠎
rule trans deverbative ⠙⠑⠧⠻⠃⠁⠞⠊⠧⠑
rule trans deverbatives ⠙⠑⠧⠻⠃⠁⠞⠊⠧⠑⠎
rule trans devertebrate ⠙⠑⠧⠻⠞⠑⠃⠗⠁⠞⠑
rule trans devertebrated ⠙⠑⠧⠻⠞⠑⠃⠗⠁⠞⠫
rule trans devertebrates ⠙⠑⠧⠻⠞⠑⠃⠗⠁⠞⠑⠎
rule trans devertebration ⠙⠑⠧⠻⠞⠑⠃⠗⠁⠰⠝
rule trans disbeliever ⠲⠃⠑⠇⠊⠑⠧⠻
rule trans disbelievers ⠲⠃⠑⠇⠊⠑⠧⠻⠎
rule trans echeveria ⠑⠡⠑⠧⠻⠊⠁
rule trans evernia ⠑⠧⠻⠝⠊⠁
rule trans everse ⠑⠧⠻⠎⠑
rule trans eversed ⠑⠧⠻⠎⠫
rule trans everses ⠑⠧⠻⠎⠑⠎
rule trans eversible ⠑⠧⠻⠎⠊⠃⠇⠑
rule trans eversing ⠑⠧⠻⠎⠬
rule trans eversion 15-1236-12456-46-1345
rule trans eversive ⠑⠧⠻⠎⠊⠧⠑
rule trans evert 15-1236-12456-2345
rule trans everton ⠐⠑⠞⠕⠝
rule trans everton's ⠐⠑⠞⠕⠝⠄⠎
rule trans grevera ⠛⠗⠑⠧⠻⠁
rule trans grevera's ⠛⠗⠑⠧⠻⠁⠄⠎
rule trans griever ⠛⠗⠊⠑⠧⠻
rule trans griever's ⠛⠗⠊⠑⠧⠻⠄⠎
rule trans grievers ⠛⠗⠊⠑⠧⠻⠎
rule trans guenevere ⠛⠥⠢⠑⠧⠻⠑
rule trans guenevere's ⠛⠥⠢⠑⠧⠻⠑⠄⠎
rule trans guinevere 1245-136-35-15-1236-12456-15
rule trans imperseverant ⠊⠍⠏⠻⠎⠑⠧⠻⠁⠝⠞
rule trans irreversibility ⠊⠗⠗⠑⠧⠻⠎⠊⠃⠊⠇⠰⠽
rule trans irreversibleness ⠊⠗⠗⠑⠧⠻⠎⠊⠃⠇⠑⠰⠎
rule trans irrevertible ⠊⠗⠗⠑⠧⠻⠞⠊⠃⠇⠑
rule trans keever ⠅⠑⠑⠧⠻
rule trans keever's ⠅⠑⠑⠧⠻⠄⠎
rule trans longsleever ⠇⠰⠛⠎⠇⠑⠑⠧⠻
rule trans longsleevers ⠇⠰⠛⠎⠇⠑⠑⠧⠻⠎
rule trans mckeever ⠍⠉⠠⠅⠑⠑⠧⠻
rule trans mckeever's ⠍⠉⠠⠅⠑⠑⠧⠻⠄⠎
rule trans monteverdi 134-135-1345-2345-15-1236-12456-145-24
rule trans nevers ⠝⠑⠧⠻⠎
rule trans nonbeliever 1345-135-1345-12-15-123-24-15-1236-12456
rule trans nonperseverance ⠝⠕⠝⠏⠻⠎⠑⠧⠻⠨⠑
rule trans nonperseverant ⠝⠕⠝⠏⠻⠎⠑⠧⠻⠁⠝⠞
rule trans nonpersevering ⠝⠕⠝⠏⠻⠎⠑⠧⠻⠬
rule trans nonreverence ⠝⠕⠝⠗⠐⠑⠰⠑
rule trans nonreverent ⠝⠕⠝⠗⠐⠑⠢⠞
rule trans nonreverential ⠝⠕⠝⠗⠐⠑⠢⠞⠊⠁⠇
rule trans nonreverentially ⠝⠕⠝⠗⠐⠑⠢⠞⠊⠁⠇⠇⠽
rule trans nonreverently ⠝⠕⠝⠗⠐⠑⠢⠞⠇⠽
rule trans nonreverse ⠝⠕⠝⠗⠑⠧⠻⠎⠑
rule trans nonreversed ⠝⠕⠝⠗⠑⠧⠻⠎⠫
rule trans nonreversibility ⠝⠕⠝⠗⠑⠧⠻⠎⠊⠃⠊⠇⠰⠽
rule trans nonreversible ⠝⠕⠝⠗⠑⠧⠻⠎⠊⠃⠇⠑
rule trans nonreversibleness ⠝⠕⠝⠗⠑⠧⠻⠎⠊⠃⠇⠑⠰⠎
rule trans nonreversibly ⠝⠕⠝⠗⠑⠧⠻⠎⠊⠃⠇⠽
rule trans nonreversing ⠝⠕⠝⠗⠑⠧⠻⠎⠬
rule trans nonreversion ⠝⠕⠝⠗⠑⠧⠻⠨⠝
rule trans nonrevertible ⠝⠕⠝⠗⠑⠧⠻⠞⠊⠃⠇⠑
rule trans nonrevertive ⠝⠕⠝⠗⠑⠧⠻⠞⠊⠧⠑
rule trans nonseverable ⠝⠕⠝⠎⠐⠑⠁⠃⠇⠑
rule trans nonseverance ⠝⠕⠝⠎⠐⠑⠨⠑
rule trans nonseverities ⠝⠕⠝⠎⠑⠧⠻⠊⠞⠊⠑⠎
rule trans nonseverity ⠝⠕⠝⠎⠑⠧⠻⠰⠽
rule trans overachiever 135-1236-12456-1-16-24-15-1236-12456
rule trans oversevere ⠕⠧⠻⠎⠑⠧⠻⠑
rule trans overseverely ⠕⠧⠻⠎⠑⠧⠻⠑⠇⠽
rule trans oversevereness ⠕⠧⠻⠎⠑⠧⠻⠑⠰⠎
rule trans overseverity ⠕⠧⠻⠎⠑⠧⠻⠰⠽
rule trans perseverate ⠏⠻⠎⠐⠑⠁⠞⠑
rule trans perseveration ⠏⠻⠎⠐⠑⠁⠰⠝
rule trans prereversal ⠏⠗⠻⠑⠧⠻⠎⠁⠇
rule trans prereverse ⠏⠗⠻⠑⠧⠻⠎⠑
rule trans prereversed ⠏⠗⠻⠑⠧⠻⠎⠫
rule trans prereverses ⠏⠗⠻⠑⠧⠻⠎⠑⠎
rule trans prereversing ⠏⠗⠻⠑⠧⠻⠎⠬
rule trans preverbal ⠏⠗⠑⠧⠻⠃⠁⠇
rule trans preverification ⠏⠗⠑⠧⠻⠊⠋⠊⠉⠁⠰⠝
rule trans preverified ⠏⠗⠑⠧⠻⠊⠋⠊⠫
rule trans preverifies ⠏⠗⠑⠧⠻⠊⠋⠊⠑⠎
rule trans preverify ⠏⠗⠑⠧⠻⠊⠋⠽
rule trans preverifying ⠏⠗⠑⠧⠻⠊⠋⠽⠬
rule trans prevernal ⠏⠗⠑⠧⠻⠝⠁⠇
rule trans preversion ⠏⠗⠑⠧⠻⠨⠝
rule trans prevertebral ⠏⠗⠑⠧⠻⠞⠑⠃⠗⠁⠇
rule trans primeverin ⠏⠗⠊⠍⠑⠧⠻⠔
rule trans primeverose ⠏⠗⠊⠍⠑⠧⠻⠕⠎⠑
rule trans pseudofever ⠏⠎⠑⠥⠙⠕⠋⠐⠑
rule trans quinqueverbal ⠟⠥⠔⠟⠥⠑⠧⠻⠃⠁⠇
rule trans quinqueverbial ⠟⠥⠔⠟⠥⠑⠧⠻⠃⠊⠁⠇
rule trans retriever 1235-15-2345-1235-24-15-1236-12456
rule trans reverbatory ⠗⠑⠧⠻⠃⠁⠞⠕⠗⠽
rule trans reverbed ⠗⠑⠧⠻⠃⠫
rule trans reverberant ⠗⠑⠧⠻⠃⠻⠁⠝⠞
rule trans reverdi ⠗⠑⠧⠻⠙⠊
rule trans reverdure ⠗⠑⠧⠻⠙⠥⠗⠑
rule trans reverer's ⠗⠑⠧⠻⠻⠄⠎
rule trans reverers ⠗⠑⠧⠻⠻⠎
rule trans reverification ⠗⠑⠧⠻⠊⠋⠊⠉⠁⠰⠝
rule trans reverification's ⠗⠑⠧⠻⠊⠋⠊⠉⠁⠰⠝⠄⠎
rule trans reverifications ⠗⠑⠧⠻⠊⠋⠊⠉⠁⠰⠝⠎
rule trans reverified ⠗⠑⠧⠻⠊⠋⠊⠫
rule trans reverifies ⠗⠑⠧⠻⠊⠋⠊⠑⠎
rule trans reverify ⠗⠑⠧⠻⠊⠋⠽
rule trans reverifying ⠗⠑⠧⠻⠊⠋⠽⠬
rule trans reversability ⠗⠑⠧⠻⠎⠁⠃⠊⠇⠰⠽
rule trans reversable ⠗⠑⠧⠻⠎⠁⠃⠇⠑
rule trans reverser ⠗⠑⠧⠻⠎⠻
rule trans reversi ⠗⠑⠧⠻⠎⠊
rule trans reversi's ⠗⠑⠧⠻⠎⠊⠄⠎
rule trans reversibility ⠗⠑⠧⠻⠎⠊⠃⠊⠇⠰⠽
rule trans reversibly ⠗⠑⠧⠻⠎⠊⠃⠇⠽
rule trans reversification ⠗⠑⠧⠻⠎⠊⠋⠊⠉⠁⠰⠝
rule trans reversification's ⠗⠑⠧⠻⠎⠊⠋⠊⠉⠁⠰⠝⠄⠎
rule trans reversifications ⠗⠑⠧⠻⠎⠊⠋⠊⠉⠁⠰⠝⠎
rule trans reversified ⠗⠑⠧⠻⠎⠊⠋⠊⠫
rule trans reversifies ⠗⠑⠧⠻⠎⠊⠋⠊⠑⠎
rule trans reversify ⠗⠑⠧⠻⠎⠊⠋⠽
rule trans reversifying ⠗⠑⠧⠻⠎⠊⠋⠽⠬
rule trans reversion 1235-15-1236-12456-46-1345
rule trans reversive ⠗⠑⠧⠻⠎⠊⠧⠑
rule trans reverso ⠗⠑⠧⠻⠎⠕
rule trans reverso's ⠗⠑⠧⠻⠎⠕⠄⠎
rule trans revert 1235-15-1236-12456-2345
rule trans revertendi ⠗⠐⠑⠞⠢⠙⠊
rule trans riever ⠗⠊⠑⠧⠻
rule trans rievers ⠗⠊⠑⠧⠻⠎
rule trans schriever ⠎⠡⠗⠊⠑⠧⠻
rule trans schriever's ⠎⠡⠗⠊⠑⠧⠻⠄⠎
rule trans semievergreen ⠎⠑⠍⠊⠐⠑⠛⠗⠑⠢
rule trans semievergreens ⠎⠑⠍⠊⠐⠑⠛⠗⠑⠢⠎
rule trans semireverberatory ⠎⠑⠍⠊⠗⠑⠧⠻⠃⠻⠁⠞⠕⠗⠽
rule trans semisevere ⠎⠑⠍⠊⠎⠑⠧⠻⠑
rule trans semiseverely ⠎⠑⠍⠊⠎⠑⠧⠻⠑⠇⠽
rule trans semiseverity ⠎⠑⠍⠊⠎⠑⠧⠻⠰⠽
rule trans severish ⠎⠑⠧⠻⠊⠩
rule trans severities ⠎⠑⠧⠻⠊⠞⠊⠑⠎
rule trans supersevere ⠎⠥⠏⠻⠎⠑⠧⠻⠑
rule trans superseverely ⠎⠥⠏⠻⠎⠑⠧⠻⠑⠇⠽
rule trans supersevereness ⠎⠥⠏⠻⠎⠑⠧⠻⠑⠰⠎
rule trans superseverity ⠎⠥⠏⠻⠎⠑⠧⠻⠰⠽
rule trans thiever ⠹⠊⠑⠧⠻
rule trans thievers ⠹⠊⠑⠧⠻⠎
rule trans thievery 1456-24-15-1236-12456-13456
rule trans ultrasevere ⠥⠇⠞⠗⠁⠎⠑⠧⠻⠑
rule trans unbeliever 136-1345-12-15-123-24-15-1236-12456
rule trans underachiever 5-136-1-16-24-15-1236-12456
rule trans uneversible ⠥⠝⠑⠧⠻⠎⠊⠃⠇⠑
rule trans uneverted ⠥⠝⠑⠧⠻⠞⠫
rule trans unperseverance ⠥⠝⠏⠻⠎⠑⠧⠻⠨⠑
rule trans unpersevering ⠥⠝⠏⠻⠎⠑⠧⠻⠬
rule trans unperseveringly ⠥⠝⠏⠻⠎⠑⠧⠻⠬⠇⠽
rule trans unreverberant ⠥⠝⠗⠑⠧⠻⠃⠻⠁⠝⠞
rule trans unreverberated ⠥⠝⠗⠑⠧⠻⠃⠻⠁⠞⠫
rule trans unreverberating ⠥⠝⠗⠑⠧⠻⠃⠻⠁⠞⠬
rule trans unreverberative ⠥⠝⠗⠑⠧⠻⠃⠻⠁⠞⠊⠧⠑
rule trans unrevered ⠥⠝⠗⠑⠧⠻⠫
rule trans unreverenced ⠥⠝⠗⠐⠑⠰⠑⠙
rule trans unreverend ⠥⠝⠗⠐⠑⠢⠙
rule trans unreverent ⠥⠝⠗⠐⠑⠢⠞
rule trans unreversable ⠥⠝⠗⠑⠧⠻⠎⠁⠃⠇⠑
rule trans unreversed ⠥⠝⠗⠑⠧⠻⠎⠫
rule trans unreversible ⠥⠝⠗⠑⠧⠻⠎⠊⠃⠇⠑
rule trans unreverted ⠥⠝⠗⠑⠧⠻⠞⠫
rule trans unrevertible ⠥⠝⠗⠑⠧⠻⠞⠊⠃⠇⠑
rule trans unreverting ⠥⠝⠗⠑⠧⠻⠞⠬
rule trans unseverable ⠥⠝⠎⠐⠑⠁⠃⠇⠑
rule trans unsevere ⠥⠝⠎⠑⠧⠻⠑
rule trans unsevered ⠥⠝⠎⠐⠑⠫
rule trans unseverely ⠥⠝⠎⠑⠧⠻⠑⠇⠽
rule trans unsevereness ⠥⠝⠎⠑⠧⠻⠑⠰⠎
rule trans viceversa ⠧⠊⠉⠑⠧⠻⠎⠁



#   reverend,revery <> reverse,revert,reverb,irreversible

rule trans irreversibl 24-1235-1235-15-1236-12456-234-24-12-123

rule trans reverbera 1235-15-1236-12456-12-12456-1

rule trans revere 1235-15-1236-12456-15
rule trans revered 1235-15-1236-12456-1246
rule trans reverify 1235-15-1236-12456-24-124-13456
rule trans revering 1235-15-1236-12456-346
rule trans reversal 1235-15-1236-12456-234-1-123
rule trans reverse 1235-15-1236-12456-234-15
rule trans reversed 1235-15-1236-12456-234-1246
rule trans reversible 1235-15-1236-12456-234-24-12-123-15
rule trans reversing 1235-15-1236-12456-234-346

rule trans reverence 1235-5-15-56-15
rule trans reverencing 1235-5-15-26-14-346
rule trans reverend 1235-5-15-26-145
rule trans reverent 1235-5-15-26-2345

#   sever <> severe

rule trans persever 1234-12456-234-15-1236-12456
rule trans severe 234-15-1236-12456-15
rule trans severer 234-15-1236-12456-12456
rule trans severity 234-15-1236-12456-56-13456
rule trans severus 234-15-1236-12456-136-234

rule trans severed 234-5-15-1246

use

rule trans keever 13-15-15-1236-12456   fywk

## father
uses not_modifier_<+ - rule trans father 5-124

## had   10.7.3
uses not_modifier_<+ - rule trans had 456-125

use word_whole_begin_+ word_whole_begin_-
rule trans hades 125-1-145-15-234
rule trans hadrian 125-1-145-1235-24-1-1345
rule trans menhaden 134-26-125-1-145-26
use

## here   10.7.5
uses not_modifier_<+ - rule trans here 5-125

use word_whole_begin_+ word_whole_begin_-
rule trans adhered 1-145-125-12456-1246
rule trans adherence 1-145-125-12456-56-15
rule trans adherency ⠁⠙⠓⠻⠢⠉⠽
rule trans adherend ⠁⠙⠓⠻⠢⠙
rule trans adherent 1-145-125-12456-26-2345
rule trans adherer 1-145-125-12456-12456
rule trans adherer ⠁⠙⠓⠻⠻
rule trans adherescence ⠁⠙⠓⠻⠑⠎⠉⠰⠑
rule trans adherescent ⠁⠙⠓⠻⠑⠎⠉⠢⠞
rule trans aphereses ⠁⠏⠓⠻⠑⠎⠑⠎
rule trans apheresis ⠁⠏⠓⠻⠑⠎⠊⠎
rule trans apheretic ⠁⠏⠓⠻⠑⠞⠊⠉
rule trans archheresies ⠜⠡⠓⠻⠑⠎⠊⠑⠎
rule trans archheresy ⠜⠡⠓⠻⠑⠎⠽
rule trans archheretic ⠜⠡⠓⠻⠑⠞⠊⠉
rule trans archheretics ⠜⠡⠓⠻⠑⠞⠊⠉⠎
rule trans archiheretical ⠜⠡⠊⠓⠻⠑⠞⠊⠉⠁⠇
rule trans atmosphered ⠁⠞⠍⠕⠎⠏⠓⠻⠫
rule trans autocoherer ⠁⠥⠞⠕⠉⠕⠓⠻⠻
rule trans bohereen ⠃⠕⠓⠻⠑⠢
rule trans bohereens ⠃⠕⠓⠻⠑⠢⠎
rule trans ciphered 14-24-1234-125-12456-1246
rule trans cipherer ⠉⠊⠏⠓⠻⠻
rule trans cipherers ⠉⠊⠏⠓⠻⠻⠎
rule trans cohered 14-135-125-12456-1246
rule trans coherence 14-135-125-12456-56-15
rule trans coherency ⠉⠕⠓⠻⠢⠉⠽
rule trans coherent 14-135-125-12456-26-2345
rule trans coherer ⠉⠕⠓⠻⠻
rule trans coherers ⠉⠕⠓⠻⠻⠎
rule trans coheretic ⠉⠕⠓⠻⠑⠞⠊⠉
rule trans coheretics ⠉⠕⠓⠻⠑⠞⠊⠉⠎
rule trans coinhered ⠉⠕⠔⠓⠻⠫
rule trans coinherence ⠉⠕⠔⠓⠻⠰⠑
rule trans coinherent ⠉⠕⠔⠓⠻⠢⠞
rule trans cryptoheresies ⠉⠗⠽⠏⠞⠕⠓⠻⠑⠎⠊⠑⠎
rule trans cryptoheresy ⠉⠗⠽⠏⠞⠕⠓⠻⠑⠎⠽
rule trans cryptoheretic ⠉⠗⠽⠏⠞⠕⠓⠻⠑⠞⠊⠉
rule trans cryptoheretical ⠉⠗⠽⠏⠞⠕⠓⠻⠑⠞⠊⠉⠁⠇
rule trans cyphered ⠉⠽⠏⠓⠻⠫
rule trans deciphered 145-15-14-24-1234-125-12456-1246
rule trans decipherer ⠙⠑⠉⠊⠏⠓⠻⠻
rule trans decipherers ⠙⠑⠉⠊⠏⠓⠻⠻⠎
rule trans decoherence ⠙⠑⠉⠕⠓⠻⠰⠑
rule trans decoherer ⠙⠑⠉⠕⠓⠻⠻
rule trans discoherent ⠲⠉⠕⠓⠻⠢⠞
rule trans disherent ⠲⠓⠻⠢⠞
rule trans enciphered ⠢⠉⠊⠏⠓⠻⠫
rule trans encipherer ⠢⠉⠊⠏⠓⠻⠻
rule trans encipherers ⠢⠉⠊⠏⠓⠻⠻⠎
rule trans ensphered ⠢⠎⠏⠓⠻⠫
rule trans exheredate ⠑⠭⠓⠻⠫⠁⠞⠑
rule trans hemisphered ⠓⠑⠍⠊⠎⠏⠓⠻⠫
rule trans heredes ⠓⠻⠫⠑⠎
rule trans heredia ⠓⠻⠫⠊⠁
rule trans heredipety ⠓⠻⠫⠊⠏⠑⠞⠽
rule trans hereditability ⠓⠻⠫⠊⠞⠁⠃⠊⠇⠰⠽
rule trans hereditable ⠓⠻⠫⠊⠞⠁⠃⠇⠑
rule trans heredital ⠓⠻⠫⠊⠞⠁⠇
rule trans hereditament ⠓⠻⠫⠊⠞⠁⠰⠞
rule trans hereditarian ⠓⠻⠫⠊⠞⠜⠊⠁⠝
rule trans hereditary 125-12456-1246-24-2345-345-13456
rule trans hereditas ⠓⠻⠫⠊⠞⠁⠎
rule trans hereditative ⠓⠻⠫⠊⠞⠁⠞⠊⠧⠑
rule trans heredities ⠓⠻⠫⠊⠞⠊⠑⠎
rule trans heredity 125-12456-1246-56-13456
rule trans heredofamilial ⠓⠻⠫⠕⠋⠁⠍⠊⠇⠊⠁⠇
rule trans hereford 125-12456-15-123456-145
rule trans hereld ⠓⠻⠑⠇⠙
rule trans hereld's ⠓⠻⠑⠇⠙⠄⠎
rule trans herenach ⠓⠻⠢⠁⠡
rule trans herero 125-12456-12456-135
rule trans heresiarch ⠓⠻⠑⠎⠊⠜⠡
rule trans heresiarchs ⠓⠻⠑⠎⠊⠜⠡⠎
rule trans heresies 125-12456-15-234-24-15-234
rule trans heresiology ⠓⠻⠑⠎⠊⠕⠇⠕⠛⠽
rule trans heresy 125-12456-15-234-13456
rule trans heretic 125-12456-15-2345-24-14
rule trans heretoch ⠓⠻⠑⠞⠕⠡
rule trans heretochs ⠓⠻⠑⠞⠕⠡⠎
rule trans heretofore 5-125-2345-135-123456-15
rule trans heretoga ⠓⠻⠑⠞⠕⠛⠁
rule trans heretogas ⠓⠻⠑⠞⠕⠛⠁⠎
rule trans heretogh ⠓⠻⠑⠞⠕⠣
rule trans heretoghs ⠓⠻⠑⠞⠕⠣⠎
rule trans heretrices ⠓⠻⠑⠞⠗⠊⠉⠑⠎
rule trans heretrix ⠓⠻⠑⠞⠗⠊⠭
rule trans heretrix's ⠓⠻⠑⠞⠗⠊⠭⠄⠎
rule trans hereupon 5-125-45-136
rule trans hereward ⠓⠻⠑⠺⠜⠙
rule trans herez ⠓⠻⠑⠵
rule trans herezeld ⠓⠻⠑⠵⠑⠇⠙
rule trans hyperphospheremia ⠓⠽⠏⠻⠏⠓⠕⠎⠏⠓⠻⠑⠍⠊⠁
rule trans inadherent ⠔⠁⠙⠓⠻⠢⠞
rule trans incoherence 35-14-135-125-12456-56-15
rule trans incoherencies ⠔⠉⠕⠓⠻⠢⠉⠊⠑⠎
rule trans incoherency ⠔⠉⠕⠓⠻⠢⠉⠽
rule trans incoherent 35-14-135-125-12456-26-2345
rule trans inhered 35-125-12456-1246
rule trans inherence ⠔⠓⠻⠰⠑
rule trans inherency ⠔⠓⠻⠢⠉⠽
rule trans inherent 35-125-12456-26-2345
rule trans insphered ⠔⠎⠏⠓⠻⠫
rule trans nonadherence ⠝⠕⠝⠁⠙⠓⠻⠰⠑
rule trans nonadherent ⠝⠕⠝⠁⠙⠓⠻⠢⠞
rule trans noncoherence ⠝⠕⠝⠉⠕⠓⠻⠰⠑
rule trans noncoherency ⠝⠕⠝⠉⠕⠓⠻⠢⠉⠽
rule trans noncoherent ⠝⠕⠝⠉⠕⠓⠻⠢⠞
rule trans nonhereditable ⠝⠕⠝⠓⠻⠫⠊⠞⠁⠃⠇⠑
rule trans nonhereditary ⠝⠕⠝⠓⠻⠫⠊⠞⠜⠽
rule trans nonheretical ⠝⠕⠝⠓⠻⠑⠞⠊⠉⠁⠇
rule trans noninherence ⠝⠕⠝⠔⠓⠻⠰⠑
rule trans noninherent ⠝⠕⠝⠔⠓⠻⠢⠞
rule trans ovaherero ⠕⠧⠁⠓⠻⠻⠕
rule trans phereclus ⠏⠓⠻⠑⠉⠇⠥⠎
rule trans pherecratean ⠏⠓⠻⠑⠉⠗⠁⠞⠂⠝
rule trans pherecrateans ⠏⠓⠻⠑⠉⠗⠁⠞⠂⠝⠎
rule trans pherecratian ⠏⠓⠻⠑⠉⠗⠁⠞⠊⠁⠝
rule trans pherecratians ⠏⠓⠻⠑⠉⠗⠁⠞⠊⠁⠝⠎
rule trans pherecratic ⠏⠓⠻⠑⠉⠗⠁⠞⠊⠉
rule trans pherecratics ⠏⠓⠻⠑⠉⠗⠁⠞⠊⠉⠎
rule trans pheres ⠏⠓⠻⠑⠎
rule trans philosopheress ⠏⠓⠊⠇⠕⠎⠕⠏⠓⠻⠑⠎⠎
rule trans philosopheresses ⠏⠓⠊⠇⠕⠎⠕⠏⠓⠻⠑⠎⠎⠑⠎
rule trans photographeress ⠏⠓⠕⠞⠕⠛⠗⠁⠏⠓⠻⠑⠎⠎
rule trans photographeresses ⠏⠓⠕⠞⠕⠛⠗⠁⠏⠓⠻⠑⠎⠎⠑⠎
rule trans plasmaphereses ⠏⠇⠁⠎⠍⠁⠏⠓⠻⠑⠎⠑⠎
rule trans plasmapheresis ⠏⠇⠁⠎⠍⠁⠏⠓⠻⠑⠎⠊⠎
rule trans preadhered ⠏⠗⠑⠁⠙⠓⠻⠫
rule trans preadherence ⠏⠗⠑⠁⠙⠓⠻⠰⠑
rule trans preadherent ⠏⠗⠑⠁⠙⠓⠻⠢⠞
rule trans preinhered ⠏⠗⠑⠔⠓⠻⠫
rule trans protoheresiarch ⠏⠗⠕⠞⠕⠓⠻⠑⠎⠊⠜⠡
rule trans readhered ⠗⠑⠁⠙⠓⠻⠫
rule trans readherence ⠗⠑⠁⠙⠓⠻⠰⠑
rule trans samothere ⠎⠁⠍⠕⠮⠗⠑
rule trans semiadherent ⠎⠑⠍⠊⠁⠙⠓⠻⠢⠞
rule trans semiheretical ⠎⠑⠍⠊⠓⠻⠑⠞⠊⠉⠁⠇
rule trans sphered ⠎⠏⠓⠻⠫
rule trans superheresies ⠎⠥⠏⠻⠓⠻⠑⠎⠊⠑⠎
rule trans superheresy ⠎⠥⠏⠻⠓⠻⠑⠎⠽
rule trans syphered ⠎⠽⠏⠓⠻⠫
rule trans telphered ⠞⠑⠇⠏⠓⠻⠫
rule trans unadherence ⠥⠝⠁⠙⠓⠻⠰⠑
rule trans unadherent ⠥⠝⠁⠙⠓⠻⠢⠞
rule trans uncoherent ⠥⠝⠉⠕⠓⠻⠢⠞
rule trans undeciphered ⠥⠝⠙⠑⠉⠊⠏⠓⠻⠫
rule trans unenciphered ⠥⠝⠢⠉⠊⠏⠓⠻⠫
rule trans unhereditary ⠥⠝⠓⠻⠫⠊⠞⠜⠽
rule trans unheretical ⠥⠝⠓⠻⠑⠞⠊⠉⠁⠇
rule trans uninherent ⠥⠝⠔⠓⠻⠢⠞
rule trans unsphered ⠥⠝⠎⠏⠓⠻⠫
rule trans wheresomever ⠐⠱⠎⠕⠍⠐⠑
use


## know
uses not_modifier_<+ - rule trans know 5-13

uses word_whole_begin_+ word_whole_begin_- rule trans lucknow 123-136-14-13-1345-246

## lord
uses not_modifier_<+ - rule trans lord 5-123

use word_whole_begin_+ word_whole_begin_-
rule trans bachelordom ⠃⠁⠡⠑⠇⠕⠗⠙⠕⠍
rule trans chlordan ⠡⠇⠕⠗⠙⠁⠝
rule trans chlordane 16-123-135-1235-145-1-1345-15
rule trans chlordiazepoxide ⠡⠇⠕⠗⠙⠊⠁⠵⠑⠏⠕⠭⠊⠙⠑
rule trans tailordom ⠞⠁⠊⠇⠕⠗⠙⠕⠍
use


## many
uses not_modifier_<+ - rule trans many 456-134

## mother
uses not_modifier_<+ - rule trans mother 5-134

use word_whole_begin_+ word_whole_begin_-
rule trans ammotherapy ⠁⠍⠍⠕⠮⠗⠁⠏⠽
rule trans autohemotherapy ⠁⠥⠞⠕⠓⠑⠍⠕⠮⠗⠁⠏⠽
rule trans autoplasmotherapy ⠁⠥⠞⠕⠏⠇⠁⠎⠍⠕⠮⠗⠁⠏⠽
rule trans chemotherapeutic ⠡⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉
rule trans chemotherapeutically ⠡⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉⠁⠇⠇⠽
rule trans chemotherapist ⠡⠑⠍⠕⠮⠗⠁⠏⠊⠌
rule trans chemotherapists ⠡⠑⠍⠕⠮⠗⠁⠏⠊⠌⠎
rule trans chemotherapy 16-15-134-135-2346-1235-1-1234-13456
rule trans chromotherapist ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠊⠌
rule trans chromotherapists ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠊⠌⠎
rule trans chromotherapy ⠡⠗⠕⠍⠕⠮⠗⠁⠏⠽
rule trans crymotherapy ⠉⠗⠽⠍⠕⠮⠗⠁⠏⠽
rule trans diathermotherapy ⠙⠊⠁⠮⠗⠍⠕⠮⠗⠁⠏⠽
rule trans elasmotherium ⠑⠇⠁⠎⠍⠕⠮⠗⠊⠥⠍
rule trans hemotherapeutic ⠓⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉
rule trans hemotherapeutics ⠓⠑⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉⠎
rule trans hemotherapy ⠓⠑⠍⠕⠮⠗⠁⠏⠽
rule trans homotherm ⠓⠕⠍⠕⠮⠗⠍
rule trans homothermic ⠓⠕⠍⠕⠮⠗⠍⠊⠉
rule trans homotherms ⠓⠕⠍⠕⠮⠗⠍⠎
rule trans normothermia ⠝⠕⠗⠍⠕⠮⠗⠍⠊⠁
rule trans normothermic ⠝⠕⠗⠍⠕⠮⠗⠍⠊⠉
rule trans ophthalmothermometer ⠕⠏⠓⠹⠁⠇⠍⠕⠮⠗⠍⠕⠍⠑⠞⠻
rule trans osmotherapy ⠕⠎⠍⠕⠮⠗⠁⠏⠽
rule trans pneumotherapeutic ⠏⠝⠑⠥⠍⠕⠮⠗⠁⠏⠑⠥⠞⠊⠉
rule trans pneumotherapies ⠏⠝⠑⠥⠍⠕⠮⠗⠁⠏⠊⠑⠎
rule trans pneumotherapy ⠏⠝⠑⠥⠍⠕⠮⠗⠁⠏⠽
rule trans psammotherapy ⠏⠎⠁⠍⠍⠕⠮⠗⠁⠏⠽
rule trans samothere ⠎⠁⠍⠕⠮⠗⠑
rule trans samotherium ⠎⠁⠍⠕⠮⠗⠊⠥⠍
rule trans seismotherapy ⠎⠑⠊⠎⠍⠕⠮⠗⠁⠏⠽
rule trans thermotherapies ⠮⠗⠍⠕⠮⠗⠁⠏⠊⠑⠎
rule trans thermotherapy ⠮⠗⠍⠕⠮⠗⠁⠏⠽
rule trans zomotherapy ⠵⠕⠍⠕⠮⠗⠁⠏⠽
use

## name   10.7.5
uses not_modifier_<+ - rule trans name 5-1345

use word_whole_begin_+ word_whole_begin_-
rule trans acetocinnamene ⠁⠉⠑⠞⠕⠉⠔⠝⠁⠍⠢⠑
rule trans alternamente ⠁⠇⠞⠻⠝⠁⠰⠞⠑
rule trans anamelech ⠁⠝⠁⠍⠑⠇⠑⠡
rule trans anamelek ⠁⠝⠁⠍⠑⠇⠑⠅
rule trans anamesite ⠁⠝⠁⠍⠑⠎⠊⠞⠑
rule trans anametadromous ⠁⠝⠁⠍⠑⠞⠁⠙⠗⠕⠍⠳⠎
rule trans annamese ⠁⠝⠝⠁⠍⠑⠎⠑
rule trans chinamen ⠡⠔⠁⠍⠢
rule trans cinnamein ⠉⠔⠝⠁⠍⠑⠔
rule trans cinnamene ⠉⠔⠝⠁⠍⠢⠑
rule trans cinnamenyl ⠉⠔⠝⠁⠍⠢⠽⠇
rule trans coronamen ⠉⠕⠗⠕⠝⠁⠍⠢
rule trans dynameter ⠙⠽⠝⠁⠍⠑⠞⠻
rule trans dynametric ⠙⠽⠝⠁⠍⠑⠞⠗⠊⠉
rule trans dynametrical ⠙⠽⠝⠁⠍⠑⠞⠗⠊⠉⠁⠇
rule trans filename 124-24-123-15-5-1345
rule trans forename 123456-15-5-1345
rule trans hemadynameter ⠓⠑⠍⠁⠙⠽⠝⠁⠍⠑⠞⠻
rule trans lanameter ⠇⠁⠝⠁⠍⠑⠞⠻
rule trans nonamenable ⠝⠕⠝⠁⠍⠢⠁⠃⠇⠑
rule trans nonamendable ⠝⠕⠝⠁⠍⠢⠙⠁⠃⠇⠑
rule trans nonamendment ⠝⠕⠝⠁⠍⠢⠙⠰⠞
rule trans nonornamental ⠝⠕⠝⠕⠗⠝⠁⠰⠞⠁⠇
rule trans ornament 135-1235-1345-1-56-2345
rule trans overornamented ⠕⠧⠻⠕⠗⠝⠁⠰⠞⠫
rule trans preornamental ⠏⠗⠑⠕⠗⠝⠁⠰⠞⠁⠇
rule trans pretournament ⠏⠗⠑⠞⠳⠗⠝⠁⠰⠞
rule trans rename 1235-15-5-1345
rule trans reornament ⠗⠑⠕⠗⠝⠁⠰⠞
rule trans reornamentation ⠗⠑⠕⠗⠝⠁⠰⠞⠁⠰⠝
rule trans reornamented ⠗⠑⠕⠗⠝⠁⠰⠞⠫
rule trans reornamenting ⠗⠑⠕⠗⠝⠁⠰⠞⠬
rule trans reornaments ⠗⠑⠕⠗⠝⠁⠰⠞⠎
rule trans superornamental ⠎⠥⠏⠻⠕⠗⠝⠁⠰⠞⠁⠇
rule trans superornamentally ⠎⠥⠏⠻⠕⠗⠝⠁⠰⠞⠁⠇⠇⠽
rule trans tournament 2345-1256-1235-1345-1-56-2345
rule trans unameliorated ⠥⠝⠁⠍⠑⠇⠊⠕⠗⠁⠞⠫
rule trans unamenability ⠥⠝⠁⠍⠢⠁⠃⠊⠇⠰⠽
rule trans unamenable ⠥⠝⠁⠍⠢⠁⠃⠇⠑
rule trans unamenably ⠥⠝⠁⠍⠢⠁⠃⠇⠽
rule trans unamendable ⠥⠝⠁⠍⠢⠙⠁⠃⠇⠑
rule trans unamended 136-1345-1-134-26-145-1246
rule trans unamended ⠥⠝⠁⠍⠢⠙⠫
rule trans unamerceable ⠥⠝⠁⠍⠻⠉⠂⠃⠇⠑
rule trans unamerced ⠥⠝⠁⠍⠻⠉⠫
rule trans unamerican ⠥⠝⠁⠍⠻⠊⠉⠁⠝
rule trans unornamented ⠥⠝⠕⠗⠝⠁⠰⠞⠫
rule trans vietnamese 1236-24-15-2345-1345-1-134-15-234-15
use

## one   10.7.6
uses not_modifier_<+ - rule trans one 5-135

use word_whole_begin_+ word_whole_begin_-
rule trans abalone 1-12-1-123-135-1345-15
rule trans abandonee ⠁⠃⠯⠕⠝⠑⠑
rule trans acetonemia ⠁⠉⠑⠞⠕⠝⠑⠍⠊⠁
rule trans acetonemic ⠁⠉⠑⠞⠕⠝⠑⠍⠊⠉
rule trans acroneurosis ⠁⠉⠗⠕⠝⠑⠥⠗⠕⠎⠊⠎
rule trans acrophonetic ⠁⠉⠗⠕⠏⠓⠕⠝⠑⠞⠊⠉
rule trans actinonema ⠁⠉⠞⠔⠕⠝⠑⠍⠁
rule trans actinoneuritis ⠁⠉⠞⠔⠕⠝⠑⠥⠗⠊⠞⠊⠎
rule trans adenoneural ⠁⠙⠢⠕⠝⠑⠥⠗⠁⠇
rule trans adenoneure ⠁⠙⠢⠕⠝⠑⠥⠗⠑
rule trans adonean ⠁⠙⠕⠝⠂⠝
rule trans aerodonetic ⠁⠻⠕⠙⠕⠝⠑⠞⠊⠉
rule trans aeronef ⠁⠻⠕⠝⠑⠋
rule trans aeroneurosis ⠁⠻⠕⠝⠑⠥⠗⠕⠎⠊⠎
rule trans aethionema ⠁⠑⠹⠊⠕⠝⠑⠍⠁
rule trans agastroneuria ⠁⠛⠁⠌⠗⠕⠝⠑⠥⠗⠊⠁
rule trans aglaonema ⠁⠛⠇⠁⠕⠝⠑⠍⠁
rule trans aidoneus ⠁⠊⠙⠕⠝⠑⠥⠎
rule trans alcyone 1-123-14-13456-135-1345-15
rule trans ammonea ⠁⠍⠍⠕⠝⠑⠁
rule trans anconeal ⠁⠝⠉⠕⠝⠂⠇
rule trans anconei ⠁⠝⠉⠕⠝⠑⠊
rule trans anconeous ⠁⠝⠉⠕⠝⠑⠳⠎
rule trans anconeus ⠁⠝⠉⠕⠝⠑⠥⠎
rule trans anemone 1-1345-15-134-135-1345-15
rule trans angioneoplasm ⠁⠝⠛⠊⠕⠝⠑⠕⠏⠇⠁⠎⠍
rule trans angioneurotic ⠁⠝⠛⠊⠕⠝⠑⠥⠗⠕⠞⠊⠉
rule trans anthraconecrosis ⠁⠝⠹⠗⠁⠉⠕⠝⠑⠉⠗⠕⠎⠊⠎
rule trans antigone 1-1345-2345-24-1245-135-1345-15
rule trans antiphonetic ⠁⠝⠞⠊⠏⠓⠕⠝⠑⠞⠊⠉
rule trans antone ⠁⠝⠞⠐⠕
rule trans antonella ⠁⠝⠞⠕⠝⠑⠇⠇⠁
rule trans antonet ⠁⠝⠞⠕⠝⠑⠞
rule trans antonetta ⠁⠝⠞⠕⠝⠑⠞⠞⠁
rule trans antonescu ⠁⠝⠞⠕⠝⠑⠎⠉⠥
rule trans aponeurology ⠁⠏⠕⠝⠑⠥⠗⠕⠇⠕⠛⠽
rule trans aponeurotomy ⠁⠏⠕⠝⠑⠥⠗⠕⠞⠕⠍⠽
rule trans aragonese ⠜⠁⠛⠕⠝⠑⠎⠑
rule trans archdeaconess ⠜⠡⠙⠂⠉⠕⠰⠎
rule trans archiphoneme ⠜⠡⠊⠏⠓⠕⠝⠑⠍⠑
rule trans argemone ⠜⠛⠑⠍⠕⠝⠑
rule trans argyroneta ⠜⠛⠽⠗⠕⠝⠑⠞⠁
rule trans arterionecrosis ⠜⠞⠻⠊⠕⠝⠑⠉⠗⠕⠎⠊⠎
rule trans arthroneuralgia ⠜⠹⠗⠕⠝⠑⠥⠗⠁⠇⠛⠊⠁
rule trans asmonean ⠁⠎⠍⠕⠝⠂⠝
rule trans assonet ⠁⠎⠎⠕⠝⠑⠞
rule trans asterionella ⠁⠌⠻⠊⠕⠝⠑⠇⠇⠁
rule trans austronesia ⠁⠥⠌⠗⠕⠝⠑⠎⠊⠁
rule trans austronesian 1-136-34-1235-135-1345-15-234-24-1-1345
rule trans autonegation ⠁⠥⠞⠕⠝⠑⠛⠁⠰⠝
rule trans autonephrectomy ⠁⠥⠞⠕⠝⠑⠏⠓⠗⠑⠉⠞⠕⠍⠽
rule trans autonetics ⠁⠥⠞⠕⠝⠑⠞⠊⠉⠎
rule trans autoneurotoxin ⠁⠥⠞⠕⠝⠑⠥⠗⠕⠞⠕⠭⠔
rule trans avignonese ⠁⠧⠊⠛⠝⠕⠝⠑⠎⠑
rule trans axonemal ⠁⠭⠕⠝⠑⠍⠁⠇
rule trans axoneme ⠁⠭⠕⠝⠑⠍⠑
rule trans axoneuron ⠁⠭⠕⠝⠑⠥⠗⠕⠝
rule trans bagonet ⠃⠁⠛⠕⠝⠑⠞
rule trans balconette ⠃⠁⠇⠉⠕⠝⠑⠞⠞⠑
rule trans ballonet ⠃⠁⠇⠇⠕⠝⠑⠞
rule trans balloonet ⠃⠁⠇⠇⠕⠕⠝⠑⠞
rule trans barceloneta ⠃⠜⠉⠑⠇⠕⠝⠑⠞⠁
rule trans baroness 12-345-135-56-234
rule trans baronet 12-345-135-1345-15-2345
rule trans baronethood ⠃⠜⠕⠝⠑⠞⠓⠕⠕⠙
rule trans barronett ⠃⠜⠗⠕⠝⠑⠞⠞
rule trans bartonella ⠃⠜⠞⠕⠝⠑⠇⠇⠁
rule trans bastonet ⠃⠁⠌⠕⠝⠑⠞
rule trans batoneer ⠃⠁⠞⠕⠝⠑⠻
rule trans bayonet 12-1-13456-135-1345-15-2345
rule trans beforementioned ⠆⠿⠑⠍⠢⠰⠝⠫
rule trans biggonet ⠃⠊⠶⠕⠝⠑⠞
rule trans binalonen ⠃⠔⠁⠇⠕⠝⠢
rule trans bludgeoneer ⠃⠇⠥⠙⠛⠑⠕⠝⠑⠻
rule trans bonedog ⠃⠐⠕⠙⠕⠛
rule trans bonedry ⠃⠐⠕⠙⠗⠽
rule trans boneen ⠃⠕⠝⠑⠢
rule trans bonellia ⠃⠕⠝⠑⠇⠇⠊⠁
rule trans bonen ⠃⠕⠝⠢
rule trans boneo ⠃⠕⠝⠑⠕
rule trans bonesteel ⠃⠐⠕⠌⠑⠑⠇
rule trans bonetta ⠃⠕⠝⠑⠞⠞⠁
rule trans boone 12-135-135-1345-15
rule trans bostonese ⠃⠕⠌⠕⠝⠑⠎⠑
rule trans botonee ⠃⠕⠞⠕⠝⠑⠑
rule trans bourbonesque ⠃⠳⠗⠃⠕⠝⠑⠎⠟⠥⠑
rule trans britoness ⠃⠗⠊⠞⠕⠰⠎
rule trans broussonetia ⠃⠗⠳⠎⠎⠕⠝⠑⠞⠊⠁
rule trans buffoonesque ⠃⠥⠖⠕⠕⠝⠑⠎⠟⠥⠑
rule trans burgonet ⠃⠥⠗⠛⠕⠝⠑⠞
rule trans byronesque ⠃⠽⠗⠕⠝⠑⠎⠟⠥⠑
rule trans calonectria ⠉⠁⠇⠕⠝⠑⠉⠞⠗⠊⠁
rule trans cannoneer ⠉⠁⠝⠝⠕⠝⠑⠻
rule trans canoness ⠉⠁⠝⠕⠰⠎
rule trans cantonese 14-1-1345-2345-135-1345-15-234-15
rule trans canzone ⠉⠁⠝⠵⠕⠝⠑
rule trans canzonet ⠉⠁⠝⠵⠕⠝⠑⠞
rule trans canzonetta ⠉⠁⠝⠵⠕⠝⠑⠞⠞⠁
rule trans caponette ⠉⠁⠏⠕⠝⠑⠞⠞⠑
rule trans carbonemia ⠉⠜⠃⠕⠝⠑⠍⠊⠁
rule trans cardionecrosis ⠉⠜⠙⠊⠕⠝⠑⠉⠗⠕⠎⠊⠎
rule trans cardionephric ⠉⠜⠙⠊⠕⠝⠑⠏⠓⠗⠊⠉
rule trans cardioneural ⠉⠜⠙⠊⠕⠝⠑⠥⠗⠁⠇
rule trans carilloneur ⠉⠜⠊⠇⠇⠕⠝⠑⠥⠗
rule trans cassone ⠉⠁⠎⠎⠕⠝⠑
rule trans castiglione ⠉⠁⠌⠊⠛⠇⠊⠕⠝⠑
rule trans ceylonese ⠉⠑⠽⠇⠕⠝⠑⠎⠑
rule trans chaeronea ⠡⠁⠻⠕⠝⠑⠁
rule trans championess ⠡⠁⠍⠏⠊⠕⠰⠎
rule trans chansonette ⠡⠁⠝⠎⠕⠝⠑⠞⠞⠑
rule trans chervonetz ⠡⠻⠧⠕⠝⠑⠞⠵
rule trans chevronel ⠡⠑⠧⠗⠕⠝⠑⠇
rule trans chevronelly ⠡⠑⠧⠗⠕⠝⠑⠇⠇⠽
rule trans chevronels ⠡⠑⠧⠗⠕⠝⠑⠇⠎
rule trans chiastoneural ⠡⠊⠁⠌⠕⠝⠑⠥⠗⠁⠇
rule trans chiastoneury ⠡⠊⠁⠌⠕⠝⠑⠥⠗⠽
rule trans chitarrone ⠡⠊⠞⠜⠗⠕⠝⠑
rule trans choristoneura ⠡⠕⠗⠊⠌⠕⠝⠑⠥⠗⠁
rule trans chromonema ⠡⠗⠕⠍⠕⠝⠑⠍⠁
rule trans chromonemata ⠡⠗⠕⠍⠕⠝⠑⠍⠁⠞⠁
rule trans chromonematic ⠡⠗⠕⠍⠕⠝⠑⠍⠁⠞⠊⠉
rule trans chromonemic ⠡⠗⠕⠍⠕⠝⠑⠍⠊⠉
rule trans cicerone ⠉⠊⠉⠻⠕⠝⠑
rule trans citronella 14-24-2345-1235-135-1345-15-123-123-1
rule trans citronelle ⠉⠊⠞⠗⠕⠝⠑⠇⠇⠑
rule trans clarionet ⠉⠇⠜⠊⠕⠝⠑⠞
rule trans cleone ⠉⠇⠑⠕⠝⠑
rule trans clione ⠉⠇⠊⠕⠝⠑
rule trans coccionella ⠉⠕⠒⠊⠕⠝⠑⠇⠇⠁
rule trans colonel 14-135-123-135-1345-15-123
rule trans colonette ⠉⠕⠇⠕⠝⠑⠞⠞⠑
rule trans comedones ⠉⠕⠍⠫⠕⠝⠑⠎
rule trans componency ⠉⠕⠍⠏⠕⠝⠢⠉⠽
rule trans componendo ⠉⠕⠍⠏⠕⠝⠢⠙⠕
rule trans coneighbor ⠉⠕⠝⠑⠊⠣⠃⠕⠗
rule trans coneighbour ⠉⠕⠝⠑⠊⠣⠃⠳⠗
rule trans conessine ⠉⠕⠰⠎⠔⠑
rule trans contraponend ⠒⠞⠗⠁⠏⠕⠝⠢⠙
rule trans conversazione ⠒⠧⠻⠎⠁⠵⠊⠕⠝⠑
rule trans copatroness ⠉⠕⠏⠁⠞⠗⠕⠰⠎
rule trans coronel ⠉⠕⠗⠕⠝⠑⠇
rule trans coronene ⠉⠕⠗⠕⠝⠢⠑
rule trans coronet 14-135-1235-135-1345-15-2345
rule trans cottonee ⠉⠕⠞⠞⠕⠝⠑⠑
rule trans cottoneer ⠉⠕⠞⠞⠕⠝⠑⠻
rule trans cottoneers ⠉⠕⠞⠞⠕⠝⠑⠻⠎
rule trans cottonees ⠉⠕⠞⠞⠕⠝⠑⠑⠎
rule trans cryptoneurous ⠉⠗⠽⠏⠞⠕⠝⠑⠥⠗⠳⠎
rule trans cushionet ⠉⠥⠩⠊⠕⠝⠑⠞
rule trans cystonectae ⠉⠽⠌⠕⠝⠑⠉⠞⠁⠑
rule trans cystonectous ⠉⠽⠌⠕⠝⠑⠉⠞⠳⠎
rule trans cystoneuralgia ⠉⠽⠌⠕⠝⠑⠥⠗⠁⠇⠛⠊⠁
rule trans dahlonega ⠙⠁⠓⠇⠕⠝⠑⠛⠁
rule trans dahlonega's ⠙⠁⠓⠇⠕⠝⠑⠛⠁⠄⠎
rule trans daimones ⠙⠁⠊⠍⠕⠝⠑⠎
rule trans dantonesque ⠙⠁⠝⠞⠕⠝⠑⠎⠟⠥⠑
rule trans deaccessioned ⠙⠑⠁⠒⠑⠎⠨⠝⠫
rule trans deaconess 145-2-14-135-56-234
rule trans dehonestate ⠙⠑⠓⠐⠕⠌⠁⠞⠑
rule trans demoness ⠙⠑⠍⠕⠰⠎
rule trans demonetise ⠙⠑⠍⠐⠕⠞⠊⠎⠑
rule trans demonetize ⠙⠑⠍⠐⠕⠞⠊⠵⠑
rule trans deone ⠙⠑⠕⠝⠑
rule trans deone's ⠙⠑⠕⠝⠑⠄⠎
rule trans dermatoneurology ⠙⠻⠍⠁⠞⠕⠝⠑⠥⠗⠕⠇⠕⠛⠽
rule trans dermonecrotic ⠙⠻⠍⠕⠝⠑⠉⠗⠕⠞⠊⠉
rule trans dermoneural ⠙⠻⠍⠕⠝⠑⠥⠗⠁⠇
rule trans desmoneme ⠙⠑⠎⠍⠕⠝⠑⠍⠑
rule trans desmonemes ⠙⠑⠎⠍⠕⠝⠑⠍⠑⠎
rule trans desmoneoplasm ⠙⠑⠎⠍⠕⠝⠑⠕⠏⠇⠁⠎⠍
rule trans desmoneoplasms ⠙⠑⠎⠍⠕⠝⠑⠕⠏⠇⠁⠎⠍⠎
rule trans deutonephron ⠙⠑⠥⠞⠕⠝⠑⠏⠓⠗⠕⠝
rule trans deutonephrons ⠙⠑⠥⠞⠕⠝⠑⠏⠓⠗⠕⠝⠎
rule trans dextrolimonene ⠙⠑⠭⠞⠗⠕⠇⠊⠍⠕⠝⠢⠑
rule trans dictyonema ⠙⠊⠉⠞⠽⠕⠝⠑⠍⠁
rule trans digoneutic ⠙⠊⠛⠕⠝⠑⠥⠞⠊⠉
rule trans dione ⠙⠊⠕⠝⠑
rule trans dione's ⠙⠊⠕⠝⠑⠄⠎
rule trans diplonema ⠙⠊⠏⠇⠕⠝⠑⠍⠁
rule trans diplonephridia ⠙⠊⠏⠇⠕⠝⠑⠏⠓⠗⠊⠙⠊⠁
rule trans dishonest 256-125-5-135-34
rule trans disponee ⠲⠏⠕⠝⠑⠑
rule trans doblones ⠙⠕⠃⠇⠕⠝⠑⠎
rule trans dodonean ⠙⠕⠙⠕⠝⠂⠝
rule trans doneck ⠙⠕⠝⠑⠉⠅
rule trans donee ⠙⠕⠝⠑⠑
rule trans donees ⠙⠕⠝⠑⠑⠎
rule trans donegal 145-135-1345-15-1245-1-123
rule trans donegal ⠙⠕⠝⠑⠛⠁⠇
rule trans donegal's ⠙⠕⠝⠑⠛⠁⠇⠄⠎
rule trans donegan ⠙⠕⠝⠑⠛⠁⠝
rule trans donegan's ⠙⠕⠝⠑⠛⠁⠝⠄⠎
rule trans donela ⠙⠕⠝⠑⠇⠁
rule trans donela's ⠙⠕⠝⠑⠇⠁⠄⠎
rule trans donell's ⠙⠕⠝⠑⠇⠇⠄⠎
rule trans donella ⠙⠕⠝⠑⠇⠇⠁
rule trans donella's ⠙⠕⠝⠑⠇⠇⠁⠄⠎
rule trans donelle ⠙⠕⠝⠑⠇⠇⠑
rule trans donelle's ⠙⠕⠝⠑⠇⠇⠑⠄⠎
rule trans donelson ⠙⠕⠝⠑⠇⠎⠕⠝
rule trans donelson's ⠙⠕⠝⠑⠇⠎⠕⠝⠄⠎
rule trans donelu ⠙⠕⠝⠑⠇⠥
rule trans donelu's ⠙⠕⠝⠑⠇⠥⠄⠎
rule trans donet ⠙⠕⠝⠑⠞
rule trans donetsk ⠙⠕⠝⠑⠞⠎⠅
rule trans donetta ⠙⠕⠝⠑⠞⠞⠁
rule trans doone ⠙⠕⠕⠝⠑
rule trans doone's ⠙⠕⠕⠝⠑⠄⠎
rule trans doonesbury 145-135-135-1345-15-234-12-136-1235-13456
rule trans dragonesque ⠙⠗⠁⠛⠕⠝⠑⠎⠟⠥⠑
rule trans dragoness ⠙⠗⠁⠛⠕⠰⠎
rule trans dragonet ⠙⠗⠁⠛⠕⠝⠑⠞
rule trans dynamoneure ⠙⠽⠝⠁⠍⠕⠝⠑⠥⠗⠑
rule trans ebonee ⠑⠃⠕⠝⠑⠑
rule trans ecphoneses ⠑⠉⠏⠓⠕⠝⠑⠎⠑⠎
rule trans ecphonesis ⠑⠉⠏⠓⠕⠝⠑⠎⠊⠎
rule trans ectonephridium ⠑⠉⠞⠕⠝⠑⠏⠓⠗⠊⠙⠊⠥⠍
rule trans eioneus ⠑⠊⠕⠝⠑⠥⠎
rule trans electronegative ⠑⠇⠑⠉⠞⠗⠕⠝⠑⠛⠁⠞⠊⠧⠑
rule trans electronegativity ⠑⠇⠑⠉⠞⠗⠕⠝⠑⠛⠁⠞⠊⠧⠰⠽
rule trans electroneutral ⠑⠇⠑⠉⠞⠗⠕⠝⠑⠥⠞⠗⠁⠇
rule trans embastioned ⠑⠍⠃⠁⠎⠰⠝⠫
rule trans encoronet ⠢⠉⠕⠗⠕⠝⠑⠞
rule trans endoneurial ⠢⠙⠕⠝⠑⠥⠗⠊⠁⠇
rule trans enteroneuritis ⠢⠞⠻⠕⠝⠑⠥⠗⠊⠞⠊⠎
rule trans epiphonema ⠑⠏⠊⠏⠓⠕⠝⠑⠍⠁
rule trans epiphonema's ⠑⠏⠊⠏⠓⠕⠝⠑⠍⠁⠄⠎
rule trans epiphonemae ⠑⠏⠊⠏⠓⠕⠝⠑⠍⠁⠑
rule trans epiphonemas ⠑⠏⠊⠏⠓⠕⠝⠑⠍⠁⠎
rule trans epulones ⠑⠏⠥⠇⠕⠝⠑⠎
rule trans erigone ⠻⠊⠛⠕⠝⠑
rule trans erigone's ⠻⠊⠛⠕⠝⠑⠄⠎
rule trans erroneous 12456-1235-135-1345-15-1256-234
rule trans esoneural ⠑⠎⠕⠝⠑⠥⠗⠁⠇
rule trans euphonetic ⠑⠥⠏⠓⠕⠝⠑⠞⠊⠉
rule trans exoneural ⠑⠭⠕⠝⠑⠥⠗⠁⠇
rule trans exponence ⠑⠭⠏⠕⠝⠰⠑
rule trans exponency ⠑⠭⠏⠕⠝⠢⠉⠽
rule trans extraperitoneal ⠑⠭⠞⠗⠁⠏⠻⠊⠞⠕⠝⠂⠇
rule trans falconelle ⠋⠁⠇⠉⠕⠝⠑⠇⠇⠑
rule trans falcones ⠋⠁⠇⠉⠕⠝⠑⠎
rule trans falconet ⠋⠁⠇⠉⠕⠝⠑⠞
rule trans feloness ⠋⠑⠇⠕⠰⠎
rule trans fibroneuroma ⠋⠊⠃⠗⠕⠝⠑⠥⠗⠕⠍⠁
rule trans flagonet ⠋⠇⠁⠛⠕⠝⠑⠞
rule trans flagonets ⠋⠇⠁⠛⠕⠝⠑⠞⠎
rule trans gaberones ⠛⠁⠃⠻⠕⠝⠑⠎
rule trans gabonese ⠛⠁⠃⠕⠝⠑⠎⠑
rule trans gaborone ⠛⠁⠃⠕⠗⠕⠝⠑
rule trans ganglionectomy ⠛⠁⠝⠛⠇⠊⠕⠝⠑⠉⠞⠕⠍⠽
rule trans ganglioneural ⠛⠁⠝⠛⠇⠊⠕⠝⠑⠥⠗⠁⠇
rule trans ganglioneuron ⠛⠁⠝⠛⠇⠊⠕⠝⠑⠥⠗⠕⠝
rule trans gastronephritis ⠛⠁⠌⠗⠕⠝⠑⠏⠓⠗⠊⠞⠊⠎
rule trans gekkones ⠛⠑⠅⠅⠕⠝⠑⠎
rule trans gemstone ⠛⠑⠍⠌⠐⠕
rule trans genonema ⠛⠢⠕⠝⠑⠍⠁
rule trans genonemas ⠛⠢⠕⠝⠑⠍⠁⠎
rule trans geonegative ⠛⠑⠕⠝⠑⠛⠁⠞⠊⠧⠑
rule trans giorgione 1245-24-135-1235-1245-24-135-1345-15
rule trans glaucionetta ⠛⠇⠁⠥⠉⠊⠕⠝⠑⠞⠞⠁
rule trans glomerulonephritis ⠛⠇⠕⠍⠻⠥⠇⠕⠝⠑⠏⠓⠗⠊⠞⠊⠎
rule trans gluconeogenesis ⠛⠇⠥⠉⠕⠝⠑⠕⠛⠢⠑⠎⠊⠎
rule trans gluconeogenetic ⠛⠇⠥⠉⠕⠝⠑⠕⠛⠢⠑⠞⠊⠉
rule trans gluttoness ⠛⠇⠥⠞⠞⠕⠰⠎
rule trans glyconean ⠛⠇⠽⠉⠕⠝⠂⠝
rule trans glyconeogenetic ⠛⠇⠽⠉⠕⠝⠑⠕⠛⠢⠑⠞⠊⠉
rule trans gonef ⠛⠕⠝⠑⠋
rule trans goneoclinic ⠛⠕⠝⠑⠕⠉⠇⠔⠊⠉
rule trans gooney ⠛⠕⠕⠝⠑⠽
rule trans gorgonesque ⠛⠕⠗⠛⠕⠝⠑⠎⠟⠥⠑
rule trans gorgoneum ⠛⠕⠗⠛⠕⠝⠑⠥⠍
rule trans gynomonecious ⠛⠽⠝⠕⠍⠕⠝⠑⠉⠊⠳⠎
rule trans habronema ⠓⠁⠃⠗⠕⠝⠑⠍⠁
rule trans habronemic ⠓⠁⠃⠗⠕⠝⠑⠍⠊⠉
rule trans halcyone ⠓⠁⠇⠉⠽⠕⠝⠑
rule trans halcyone's ⠓⠁⠇⠉⠽⠕⠝⠑⠄⠎
rule trans harpooneer ⠓⠜⠏⠕⠕⠝⠑⠻
rule trans harpooneers ⠓⠜⠏⠕⠕⠝⠑⠻⠎
rule trans hasmonean ⠓⠁⠎⠍⠕⠝⠂⠝
rule trans hematonephrosis ⠓⠑⠍⠁⠞⠕⠝⠑⠏⠓⠗⠕⠎⠊⠎
rule trans hemonephrosis ⠓⠑⠍⠕⠝⠑⠏⠓⠗⠕⠎⠊⠎
rule trans hemoperitoneum ⠓⠑⠍⠕⠏⠻⠊⠞⠕⠝⠑⠥⠍
rule trans hepatonephric ⠓⠑⠏⠁⠞⠕⠝⠑⠏⠓⠗⠊⠉
rule trans hermione 125-12456-134-24-135-1345-15
rule trans honecker 125-135-1345-15-14-13-12456
rule trans honegger ⠓⠕⠝⠑⠶⠻
rule trans honegger's ⠓⠕⠝⠑⠶⠻⠄⠎
rule trans honest 125-5-135-34
rule trans hoplonemertea ⠓⠕⠏⠇⠕⠝⠑⠍⠻⠞⠑⠁
rule trans hoplonemertean ⠓⠕⠏⠇⠕⠝⠑⠍⠻⠞⠂⠝
rule trans hoplonemertine ⠓⠕⠏⠇⠕⠝⠑⠍⠻⠞⠔⠑
rule trans hoplophoneus ⠓⠕⠏⠇⠕⠏⠓⠕⠝⠑⠥⠎
rule trans hyalonema ⠓⠽⠁⠇⠕⠝⠑⠍⠁
rule trans hydronegative ⠓⠽⠙⠗⠕⠝⠑⠛⠁⠞⠊⠧⠑
rule trans hydronephrosis ⠓⠽⠙⠗⠕⠝⠑⠏⠓⠗⠕⠎⠊⠎
rule trans hydroperitoneum ⠓⠽⠙⠗⠕⠏⠻⠊⠞⠕⠝⠑⠥⠍
rule trans hypernatronemia ⠓⠽⠏⠻⠝⠁⠞⠗⠕⠝⠑⠍⠊⠁
rule trans hypoalonemia ⠓⠽⠏⠕⠁⠇⠕⠝⠑⠍⠊⠁
rule trans hyponea ⠓⠽⠏⠕⠝⠑⠁
rule trans hyponeas ⠓⠽⠏⠕⠝⠂⠎
rule trans hyponeuria ⠓⠽⠏⠕⠝⠑⠥⠗⠊⠁
rule trans hypophonesis ⠓⠽⠏⠕⠏⠓⠕⠝⠑⠎⠊⠎
rule trans ideophonetics ⠊⠙⠑⠕⠏⠓⠕⠝⠑⠞⠊⠉⠎
rule trans idoneity ⠊⠙⠕⠝⠑⠰⠽
rule trans idoneous ⠊⠙⠕⠝⠑⠳⠎
rule trans ilioperoneal ⠊⠇⠊⠕⠏⠻⠕⠝⠂⠇
rule trans inconel ⠔⠉⠕⠝⠑⠇
rule trans indonesia 35-145-135-1345-15-234-24-1
rule trans inerroneous ⠔⠻⠗⠕⠝⠑⠳⠎
rule trans inhonest ⠔⠓⠐⠕⠌
rule trans inidoneity ⠔⠊⠙⠕⠝⠑⠰⠽
rule trans inidoneous ⠔⠊⠙⠕⠝⠑⠳⠎
rule trans inoneuroma ⠔⠕⠝⠑⠥⠗⠕⠍⠁
rule trans intraperitoneal ⠔⠞⠗⠁⠏⠻⠊⠞⠕⠝⠂⠇
rule trans ionesco 24-135-1345-15-234-14-135
rule trans iridodonesis ⠊⠗⠊⠙⠕⠙⠕⠝⠑⠎⠊⠎
rule trans isoneph ⠊⠎⠕⠝⠑⠏⠓
rule trans isoneph's ⠊⠎⠕⠝⠑⠏⠓⠄⠎
rule trans isonephelic ⠊⠎⠕⠝⠑⠏⠓⠑⠇⠊⠉
rule trans isonephs ⠊⠎⠕⠝⠑⠏⠓⠎
rule trans jaconelli ⠚⠁⠉⠕⠝⠑⠇⠇⠊
rule trans jaconelli's ⠚⠁⠉⠕⠝⠑⠇⠇⠊⠄⠎
rule trans jaconet ⠚⠁⠉⠕⠝⠑⠞
rule trans jargoneer ⠚⠜⠛⠕⠝⠑⠻
rule trans jargonesque ⠚⠜⠛⠕⠝⠑⠎⠟⠥⠑
rule trans jasione ⠚⠁⠎⠊⠕⠝⠑
rule trans johnsonese ⠚⠕⠓⠝⠎⠕⠝⠑⠎⠑
rule trans jonel ⠚⠕⠝⠑⠇
rule trans jonell ⠚⠕⠝⠑⠇⠇
rule trans joneses ⠚⠐⠕⠎⠑⠎
rule trans jonesian ⠚⠐⠕⠎⠊⠁⠝
#ule trans jonestown ⠚⠐⠕⠎⠞⠪⠝
rule trans jonette ⠚⠕⠝⠑⠞⠞⠑
rule trans kanone ⠅⠁⠝⠕⠝⠑
rule trans kanonen ⠅⠁⠝⠕⠝⠢
rule trans ketonemia ⠅⠑⠞⠕⠝⠑⠍⠊⠁
rule trans kinetonema ⠅⠔⠑⠞⠕⠝⠑⠍⠁
rule trans kinetonemata ⠅⠔⠑⠞⠕⠝⠑⠍⠁⠞⠁
rule trans kionectomy ⠅⠊⠕⠝⠑⠉⠞⠕⠍⠽
rule trans konev ⠅⠕⠝⠑⠧
rule trans konev's ⠅⠕⠝⠑⠧⠄⠎
rule trans krone 13-1235-135-1345-15
rule trans kronen ⠅⠗⠕⠝⠢
rule trans kroner 13-1235-135-1345-12456
rule trans laestrygones ⠇⠁⠑⠌⠗⠽⠛⠕⠝⠑⠎
rule trans laparonephrectomy ⠇⠁⠏⠜⠕⠝⠑⠏⠓⠗⠑⠉⠞⠕⠍⠽
rule trans laparonephrotomy ⠇⠁⠏⠜⠕⠝⠑⠏⠓⠗⠕⠞⠕⠍⠽
rule trans lapponese ⠇⠁⠏⠏⠕⠝⠑⠎⠑
rule trans lazzarone ⠇⠁⠵⠵⠜⠕⠝⠑
rule trans lazzarone's ⠇⠁⠵⠵⠜⠕⠝⠑⠄⠎
rule trans legionella ⠇⠑⠛⠊⠕⠝⠑⠇⠇⠁
rule trans leonel 123-15-135-1345-15-123
rule trans leonese ⠇⠑⠕⠝⠑⠎⠑
rule trans leptonecrosis ⠇⠑⠏⠞⠕⠝⠑⠉⠗⠕⠎⠊⠎
rule trans leptonema ⠇⠑⠏⠞⠕⠝⠑⠍⠁
rule trans levolimonene ⠇⠑⠧⠕⠇⠊⠍⠕⠝⠢⠑
rule trans limonene ⠇⠊⠍⠕⠝⠢⠑
rule trans lionel 123-24-135-1345-15-123
rule trans lionesque ⠇⠊⠕⠝⠑⠎⠟⠥⠑
rule trans lioness 123-24-135-56-234
rule trans lionet ⠇⠊⠕⠝⠑⠞
rule trans lithonephria ⠇⠊⠹⠕⠝⠑⠏⠓⠗⠊⠁
rule trans londonese ⠇⠕⠝⠙⠕⠝⠑⠎⠑
rule trans londonesque ⠇⠕⠝⠙⠕⠝⠑⠎⠟⠥⠑
rule trans lonee ⠇⠕⠝⠑⠑
rule trans looney 123-135-135-1345-15-13456
rule trans lugones ⠇⠥⠛⠕⠝⠑⠎
rule trans luncheonette 123-136-1345-16-15-135-1345-15-2345-2345-15
rule trans lyonese ⠇⠽⠕⠝⠑⠎⠑
rule trans lyonetia ⠇⠽⠕⠝⠑⠞⠊⠁
rule trans lyonetian ⠇⠽⠕⠝⠑⠞⠊⠁⠝
rule trans macdonell ⠍⠁⠉⠙⠕⠝⠑⠇⠇
rule trans madrone ⠍⠁⠙⠗⠕⠝⠑
rule trans maisonette ⠍⠁⠊⠎⠕⠝⠑⠞⠞⠑
rule trans maisonette's ⠍⠁⠊⠎⠕⠝⠑⠞⠞⠑⠄⠎
rule trans maisonettes ⠍⠁⠊⠎⠕⠝⠑⠞⠞⠑⠎
rule trans malhonest ⠍⠁⠇⠓⠐⠕⠌
rule trans mamaroneck ⠍⠁⠍⠜⠕⠝⠑⠉⠅
rule trans mamaroneck's ⠍⠁⠍⠜⠕⠝⠑⠉⠅⠄⠎
rule trans mangonel ⠍⠁⠝⠛⠕⠝⠑⠇
rule trans mangonels ⠍⠁⠝⠛⠕⠝⠑⠇⠎
rule trans mantellone ⠍⠁⠝⠞⠑⠇⠇⠕⠝⠑
rule trans mantellones ⠍⠁⠝⠞⠑⠇⠇⠕⠝⠑⠎
rule trans marchioness 134-345-16-24-135-56-234
rule trans marionet ⠍⠜⠊⠕⠝⠑⠞
rule trans marionets ⠍⠜⠊⠕⠝⠑⠞⠎
rule trans marionette 134-345-24-135-1345-15-2345-2345-15
rule trans mastigoneme ⠍⠁⠌⠊⠛⠕⠝⠑⠍⠑
rule trans mastigonemes ⠍⠁⠌⠊⠛⠕⠝⠑⠍⠑⠎
rule trans mbabone ⠍⠃⠁⠃⠕⠝⠑
rule trans mbabone's ⠍⠃⠁⠃⠕⠝⠑⠄⠎
rule trans membranonervous ⠍⠑⠍⠃⠗⠁⠝⠕⠝⠻⠧⠳⠎
rule trans merioneth ⠍⠻⠊⠕⠝⠑⠹
rule trans merioneth's ⠍⠻⠊⠕⠝⠑⠹⠄⠎
rule trans merionethshire ⠍⠻⠊⠕⠝⠑⠹⠩⠊⠗⠑
rule trans merionethshire's ⠍⠻⠊⠕⠝⠑⠹⠩⠊⠗⠑⠄⠎
rule trans mesonephridium ⠍⠑⠎⠕⠝⠑⠏⠓⠗⠊⠙⠊⠥⠍
rule trans metroneuria ⠍⠑⠞⠗⠕⠝⠑⠥⠗⠊⠁
rule trans micronesia 134-24-14-1235-135-1345-15-234-24-1
rule trans mignonette ⠍⠊⠛⠝⠕⠝⠑⠞⠞⠑
rule trans minestrone 134-35-15-34-1235-135-1345-15
rule trans minionette ⠍⠔⠊⠕⠝⠑⠞⠞⠑
rule trans misoneism ⠍⠊⠎⠕⠝⠑⠊⠎⠍
rule trans misoneist ⠍⠊⠎⠕⠝⠑⠊⠌
rule trans misoneistic ⠍⠊⠎⠕⠝⠑⠊⠌⠊⠉
rule trans misoneists ⠍⠊⠎⠕⠝⠑⠊⠌⠎
rule trans moliones ⠍⠕⠇⠊⠕⠝⠑⠎
rule trans monecian ⠍⠕⠝⠑⠉⠊⠁⠝
rule trans monecious ⠍⠕⠝⠑⠉⠊⠳⠎
rule trans monee ⠍⠕⠝⠑⠑
rule trans monegasque ⠍⠕⠝⠑⠛⠁⠎⠟⠥⠑
rule trans monel ⠍⠕⠝⠑⠇
rule trans monembryonic ⠍⠕⠝⠑⠍⠃⠗⠽⠕⠝⠊⠉
rule trans monembryony ⠍⠕⠝⠑⠍⠃⠗⠽⠕⠝⠽
rule trans moneme ⠍⠕⠝⠑⠍⠑
rule trans monemes ⠍⠕⠝⠑⠍⠑⠎
rule trans monepic ⠍⠕⠝⠑⠏⠊⠉
rule trans monepiscopacy ⠍⠕⠝⠑⠏⠊⠎⠉⠕⠏⠁⠉⠽
rule trans monepiscopal ⠍⠕⠝⠑⠏⠊⠎⠉⠕⠏⠁⠇
rule trans monepiscopus ⠍⠕⠝⠑⠏⠊⠎⠉⠕⠏⠥⠎
rule trans monesia ⠍⠕⠝⠑⠎⠊⠁
rule trans monet 134-135-1345-15-2345
rule trans monetar 134-5-135-2345-345   # monetarily, monetarism, monetary
rule trans monetarist ⠍⠐⠕⠞⠜⠊⠌
rule trans moneth ⠍⠕⠝⠑⠹
rule trans monetise ⠍⠐⠕⠞⠊⠎⠑
rule trans monetised ⠍⠐⠕⠞⠊⠎⠫
rule trans monetiser ⠍⠐⠕⠞⠊⠎⠻
rule trans monetiser ⠍⠐⠕⠞⠊⠎⠻
rule trans monetisers ⠍⠐⠕⠞⠊⠎⠻⠎
rule trans monetisers ⠍⠐⠕⠞⠊⠎⠻⠎
rule trans monetises ⠍⠐⠕⠞⠊⠎⠑⠎
rule trans monetising ⠍⠐⠕⠞⠊⠎⠬
rule trans monetize ⠍⠐⠕⠞⠊⠵⠑
rule trans monetized ⠍⠐⠕⠞⠊⠵⠫
rule trans monetizer ⠍⠐⠕⠞⠊⠵⠻
rule trans monetizer ⠍⠐⠕⠞⠊⠵⠻
rule trans monetizers ⠍⠐⠕⠞⠊⠵⠻⠎
rule trans monetizers ⠍⠐⠕⠞⠊⠵⠻⠎
rule trans monetizes ⠍⠐⠕⠞⠊⠵⠑⠎
rule trans monetizing ⠍⠐⠕⠞⠊⠵⠬
rule trans monogoneutic ⠍⠕⠝⠕⠛⠕⠝⠑⠥⠞⠊⠉
rule trans mononeural ⠍⠕⠝⠕⠝⠑⠥⠗⠁⠇
rule trans montefiascone ⠍⠕⠝⠞⠑⠋⠊⠁⠎⠉⠕⠝⠑
rule trans moone ⠍⠕⠕⠝⠑
rule trans mooned ⠍⠕⠕⠝⠫
rule trans mooney 134-135-135-1345-15-13456
rule trans mormoness ⠍⠕⠗⠍⠕⠰⠎
rule trans morone ⠍⠕⠗⠕⠝⠑
rule trans morphoneme ⠍⠕⠗⠏⠓⠕⠝⠑⠍⠑
rule trans morphoneme⠎ ⠍⠕⠗⠏⠓⠕⠝⠑⠍⠑⠎
rule trans morphonemics ⠍⠕⠗⠏⠓⠕⠝⠑⠍⠊⠉⠎
rule trans morphophonemic ⠍⠕⠗⠏⠓⠕⠏⠓⠕⠝⠑⠍⠊⠉
rule trans morphotonemic ⠍⠕⠗⠏⠓⠕⠞⠕⠝⠑⠍⠊⠉
rule trans motoneuron ⠍⠕⠞⠕⠝⠑⠥⠗⠕⠝
rule trans moutonee ⠍⠳⠞⠕⠝⠑⠑
rule trans myeloneuritis ⠍⠽⠑⠇⠕⠝⠑⠥⠗⠊⠞⠊⠎
rule trans myonema ⠍⠽⠕⠝⠑⠍⠁
rule trans myoneuralgia ⠍⠽⠕⠝⠑⠥⠗⠁⠇⠛⠊⠁
rule trans myrmidones ⠍⠽⠗⠍⠊⠙⠕⠝⠑⠎
rule trans naponee ⠝⠁⠏⠕⠝⠑⠑
rule trans nectonema ⠝⠑⠉⠞⠕⠝⠑⠍⠁
rule trans nesonetta ⠝⠑⠎⠕⠝⠑⠞⠞⠁
rule trans nipponese ⠝⠊⠏⠏⠕⠝⠑⠎⠑
rule trans noneager ⠝⠕⠝⠂⠛⠻
rule trans nonearning ⠝⠕⠝⠑⠜⠝⠬
rule trans noneastern ⠝⠕⠝⠂⠌⠻⠝
rule trans noneatable ⠝⠕⠝⠂⠞⠁⠃⠇⠑
rule trans nonebullience ⠝⠕⠝⠑⠃⠥⠇⠇⠊⠰⠑
rule trans nonebullient ⠝⠕⠝⠑⠃⠥⠇⠇⠊⠢⠞
rule trans noneccentric ⠝⠕⠝⠑⠒⠢⠞⠗⠊⠉
rule trans noneccentrical ⠝⠕⠝⠑⠒⠢⠞⠗⠊⠉⠁⠇
rule trans nonecclesiastical ⠝⠕⠝⠑⠒⠇⠑⠎⠊⠁⠌⠊⠉⠁⠇
rule trans nonechoic ⠝⠕⠝⠑⠡⠕⠊⠉
rule trans noneclectic ⠝⠕⠝⠑⠉⠇⠑⠉⠞⠊⠉
rule trans noneclipsing ⠝⠕⠝⠑⠉⠇⠊⠏⠎⠬
rule trans nonecliptic ⠝⠕⠝⠑⠉⠇⠊⠏⠞⠊⠉
rule trans noneconomic ⠝⠕⠝⠑⠉⠕⠝⠕⠍⠊⠉
rule trans noneconomical ⠝⠕⠝⠑⠉⠕⠝⠕⠍⠊⠉⠁⠇
rule trans noneconomy ⠝⠕⠝⠑⠉⠕⠝⠕⠍⠽
rule trans nonecstatic ⠝⠕⠝⠑⠉⠌⠁⠞⠊⠉
rule trans nonecumenical ⠝⠕⠝⠑⠉⠥⠍⠢⠊⠉⠁⠇
rule trans nonedified ⠝⠕⠝⠫⠊⠋⠊⠫
rule trans nonedifying ⠝⠕⠝⠫⠊⠋⠽⠬
rule trans noneducational ⠝⠕⠝⠫⠥⠉⠁⠰⠝⠁⠇
rule trans noneffervescent ⠝⠕⠝⠑⠖⠻⠧⠑⠎⠉⠢⠞
rule trans noneffeteness ⠝⠕⠝⠑⠖⠑⠞⠑⠰⠎
rule trans nonefficacious ⠝⠕⠝⠑⠖⠊⠉⠁⠉⠊⠳⠎
rule trans nonefficient ⠝⠕⠝⠑⠖⠊⠉⠊⠢⠞
rule trans noneffusive ⠝⠕⠝⠑⠖⠥⠎⠊⠧⠑
rule trans nonegoistic ⠝⠕⠝⠑⠛⠕⠊⠌⠊⠉
rule trans nonegregious ⠝⠕⠝⠑⠛⠗⠑⠛⠊⠳⠎
rule trans noneidetic ⠝⠕⠝⠑⠊⠙⠑⠞⠊⠉
rule trans nonejecting ⠝⠕⠝⠑⠚⠑⠉⠞⠬
rule trans nonelaborate ⠝⠕⠝⠑⠇⠁⠃⠕⠗⠁⠞⠑
rule trans nonelastic ⠝⠕⠝⠑⠇⠁⠌⠊⠉
rule trans nonelected ⠝⠕⠝⠑⠇⠑⠉⠞⠫
rule trans nonelectric ⠝⠕⠝⠑⠇⠑⠉⠞⠗⠊⠉
rule trans nonelectrical ⠝⠕⠝⠑⠇⠑⠉⠞⠗⠊⠉⠁⠇
rule trans nonelemental ⠝⠕⠝⠑⠇⠑⠰⠞⠁⠇
rule trans nonelevated ⠝⠕⠝⠑⠇⠑⠧⠁⠞⠫
rule trans nonelevating ⠝⠕⠝⠑⠇⠑⠧⠁⠞⠬
rule trans nonelevation ⠝⠕⠝⠑⠇⠑⠧⠁⠰⠝
rule trans nonelicited ⠝⠕⠝⠑⠇⠊⠉⠊⠞⠫
rule trans noneligible ⠝⠕⠝⠑⠇⠊⠛⠊⠃⠇⠑
rule trans nonelimination ⠝⠕⠝⠑⠇⠊⠍⠔⠁⠰⠝
rule trans nonelite ⠝⠕⠝⠑⠇⠊⠞⠑
rule trans nonelliptic ⠝⠕⠝⠑⠇⠇⠊⠏⠞⠊⠉
rule trans nonelliptical ⠝⠕⠝⠑⠇⠇⠊⠏⠞⠊⠉⠁⠇
rule trans nonelongated ⠝⠕⠝⠑⠇⠰⠛⠁⠞⠫
rule trans nonelongation ⠝⠕⠝⠑⠇⠰⠛⠁⠰⠝
rule trans nonelopement ⠝⠕⠝⠑⠇⠕⠏⠑⠰⠞
rule trans noneloquent ⠝⠕⠝⠑⠇⠕⠟⠥⠢⠞
rule trans noneloquently ⠝⠕⠝⠑⠇⠕⠟⠥⠢⠞⠇⠽
rule trans nonelucidating ⠝⠕⠝⠑⠇⠥⠉⠊⠙⠁⠞⠬
rule trans nonelusive ⠝⠕⠝⠑⠇⠥⠎⠊⠧⠑
rule trans nonemanating ⠝⠕⠝⠑⠍⠁⠝⠁⠞⠬
rule trans nonemancipated ⠝⠕⠝⠑⠍⠁⠝⠉⠊⠏⠁⠞⠫
rule trans nonemancipation ⠝⠕⠝⠑⠍⠁⠝⠉⠊⠏⠁⠰⠝
rule trans nonemancipative ⠝⠕⠝⠑⠍⠁⠝⠉⠊⠏⠁⠞⠊⠧⠑
rule trans nonembarkation ⠝⠕⠝⠑⠍⠃⠜⠅⠁⠰⠝
rule trans nonembellished ⠝⠕⠝⠑⠍⠃⠑⠇⠇⠊⠩⠫
rule trans nonembezzlement ⠝⠕⠝⠑⠍⠃⠑⠵⠵⠇⠑⠰⠞
rule trans nonembryonic ⠝⠕⠝⠑⠍⠃⠗⠽⠕⠝⠊⠉
rule trans nonemendation ⠝⠕⠝⠑⠍⠢⠙⠁⠰⠝
rule trans nonemergent ⠝⠕⠝⠑⠍⠻⠛⠢⠞
rule trans nonemerging ⠝⠕⠝⠑⠍⠻⠛⠬
rule trans nonemigrant ⠝⠕⠝⠑⠍⠊⠛⠗⠁⠝⠞
rule trans nonemigrants ⠝⠕⠝⠑⠍⠊⠛⠗⠁⠝⠞⠎
rule trans nonemigration ⠝⠕⠝⠑⠍⠊⠛⠗⠁⠰⠝
rule trans nonemission ⠝⠕⠝⠑⠍⠊⠎⠨⠝
rule trans nonemotional ⠝⠕⠝⠑⠍⠕⠰⠝⠁⠇
rule trans nonemotionally ⠝⠕⠝⠑⠍⠕⠰⠝⠁⠇⠇⠽
rule trans nonemotive ⠝⠕⠝⠑⠍⠕⠞⠊⠧⠑
rule trans nonempathic ⠝⠕⠝⠑⠍⠏⠁⠹⠊⠉
rule trans nonemphatic ⠝⠕⠝⠑⠍⠏⠓⠁⠞⠊⠉
rule trans nonempirical ⠝⠕⠝⠑⠍⠏⠊⠗⠊⠉⠁⠇
rule trans nonemployed ⠝⠕⠝⠑⠍⠏⠇⠕⠽⠫
rule trans nonemployment ⠝⠕⠝⠑⠍⠏⠇⠕⠽⠰⠞
rule trans nonempty 1345-135-1345-15-134-1234-2345-13456
rule trans nonemulated ⠝⠕⠝⠑⠍⠥⠇⠁⠞⠫
rule trans nonemulation ⠝⠕⠝⠑⠍⠥⠇⠁⠰⠝
rule trans nonenactment ⠝⠕⠝⠢⠁⠉⠞⠰⠞
rule trans nonenclosure ⠝⠕⠝⠢⠉⠇⠕⠎⠥⠗⠑
rule trans nonencroachment ⠝⠕⠝⠢⠉⠗⠕⠁⠡⠰⠞
rule trans nonencyclopaedic ⠝⠕⠝⠢⠉⠽⠉⠇⠕⠏⠁⠫⠊⠉
rule trans nonencyclopedic ⠝⠕⠝⠢⠉⠽⠉⠇⠕⠏⠫⠊⠉
rule trans nonendemic ⠝⠕⠝⠢⠙⠑⠍⠊⠉
rule trans nonendorsement ⠝⠕⠝⠢⠙⠕⠗⠎⠑⠰⠞
rule trans nonendowment ⠝⠕⠝⠢⠙⠪⠰⠞
rule trans nonendurable ⠝⠕⠝⠢⠙⠥⠗⠁⠃⠇⠑
rule trans nonendurance ⠝⠕⠝⠢⠙⠥⠗⠨⠑
rule trans nonene ⠝⠕⠝⠢⠑
rule trans nonenemies ⠝⠕⠝⠢⠑⠍⠊⠑⠎
rule trans nonenemy ⠝⠕⠝⠢⠑⠍⠽
rule trans nonenergetic ⠝⠕⠝⠢⠻⠛⠑⠞⠊⠉
rule trans nonenervating ⠝⠕⠝⠢⠻⠧⠁⠞⠬
rule trans nonenforceable ⠝⠕⠝⠢⠿⠉⠂⠃⠇⠑
rule trans nonenforced ⠝⠕⠝⠢⠿⠉⠫
rule trans nonengaged ⠝⠕⠝⠢⠛⠁⠛⠫
rule trans nonengagement ⠝⠕⠝⠢⠛⠁⠛⠑⠰⠞
rule trans nonengaging ⠝⠕⠝⠢⠛⠁⠛⠬
rule trans nonengineering ⠝⠕⠝⠢⠛⠔⠑⠻⠬
rule trans nonengrossing ⠝⠕⠝⠢⠛⠗⠕⠎⠎⠬
rule trans nonenigmatic ⠝⠕⠝⠢⠊⠛⠍⠁⠞⠊⠉
rule trans nonenlightened ⠝⠕⠝⠢⠇⠊⠣⠞⠢⠫
rule trans nonenlightening ⠝⠕⠝⠢⠇⠊⠣⠞⠢⠬
rule trans nonenrolled ⠝⠕⠝⠢⠗⠕⠇⠇⠫
rule trans nonentertaining ⠝⠕⠝⠢⠞⠻⠞⠁⠔⠬
rule trans nonenthusiastic ⠝⠕⠝⠢⠹⠥⠎⠊⠁⠌⠊⠉
rule trans nonenthusiastically ⠝⠕⠝⠢⠹⠥⠎⠊⠁⠌⠊⠉⠁⠇⠇⠽
rule trans nonentitled ⠝⠕⠝⠢⠞⠊⠞⠇⠫
rule trans nonenumerated ⠝⠕⠝⠢⠥⠍⠻⠁⠞⠫
rule trans nonenunciation ⠝⠕⠝⠢⠥⠝⠉⠊⠁⠰⠝
rule trans nonenviable ⠝⠕⠝⠢⠧⠊⠁⠃⠇⠑
rule trans nonenvious ⠝⠕⠝⠢⠧⠊⠳⠎
rule trans nonenvironmental ⠝⠕⠝⠢⠧⠊⠗⠕⠝⠰⠞⠁⠇
rule trans nonenzymic ⠝⠕⠝⠢⠵⠽⠍⠊⠉
rule trans nonephemeral ⠝⠕⠝⠑⠏⠓⠑⠍⠻⠁⠇
rule trans nonepic ⠝⠕⠝⠑⠏⠊⠉
rule trans nonepicurean ⠝⠕⠝⠑⠏⠊⠉⠥⠗⠂⠝
rule trans nonepigrammatic ⠝⠕⠝⠑⠏⠊⠛⠗⠁⠍⠍⠁⠞⠊⠉
rule trans nonepileptic ⠝⠕⠝⠑⠏⠊⠇⠑⠏⠞⠊⠉
rule trans nonepiscopal ⠝⠕⠝⠑⠏⠊⠎⠉⠕⠏⠁⠇
rule trans nonepisodic ⠝⠕⠝⠑⠏⠊⠎⠕⠙⠊⠉
rule trans nonepithelial ⠝⠕⠝⠑⠏⠊⠮⠇⠊⠁⠇
rule trans nonepochal ⠝⠕⠝⠑⠏⠕⠡⠁⠇
rule trans nonequable ⠝⠕⠝⠑⠟⠥⠁⠃⠇⠑
rule trans nonequal ⠝⠕⠝⠑⠟⠥⠁⠇
rule trans nonequalized ⠝⠕⠝⠑⠟⠥⠁⠇⠊⠵⠫
rule trans nonequation ⠝⠕⠝⠑⠟⠥⠁⠰⠝
rule trans nonequations ⠝⠕⠝⠑⠟⠥⠁⠰⠝⠎
rule trans nonequatorial ⠝⠕⠝⠑⠟⠥⠁⠞⠕⠗⠊⠁⠇
rule trans nonequestrian ⠝⠕⠝⠑⠟⠥⠑⠌⠗⠊⠁⠝
rule trans nonequilateral ⠝⠕⠝⠑⠟⠥⠊⠇⠁⠞⠻⠁⠇
rule trans nonequilibrium ⠝⠕⠝⠑⠟⠥⠊⠇⠊⠃⠗⠊⠥⠍
rule trans nonequitable ⠝⠕⠝⠑⠟⠥⠊⠞⠁⠃⠇⠑
rule trans nonequivalence ⠝⠕⠝⠑⠟⠥⠊⠧⠁⠇⠰⠑
rule trans nonequivalent ⠝⠕⠝⠑⠟⠥⠊⠧⠁⠇⠢⠞
rule trans nonequivocal ⠝⠕⠝⠑⠟⠥⠊⠧⠕⠉⠁⠇
rule trans noneradicable ⠝⠕⠝⠻⠁⠙⠊⠉⠁⠃⠇⠑
rule trans nonerroneous ⠝⠕⠝⠻⠗⠕⠝⠑⠳⠎
rule trans nones ⠝⠐⠕⠎
rule trans nonescapable ⠝⠕⠝⠑⠎⠉⠁⠏⠁⠃⠇⠑
rule trans nonescape ⠝⠕⠝⠑⠎⠉⠁⠏⠑
rule trans nonesoteric ⠝⠕⠝⠑⠎⠕⠞⠻⠊⠉
rule trans nonespionage ⠝⠕⠝⠑⠎⠏⠊⠕⠝⠁⠛⠑
rule trans nonespousal ⠝⠕⠝⠑⠎⠏⠳⠎⠁⠇
rule trans nonessential 1345-135-1345-15-234-234-26-2345-24-1-123
rule trans nonestablished ⠝⠕⠝⠑⠌⠁⠃⠇⠊⠩⠫
rule trans nonesthetic ⠝⠕⠝⠑⠎⠮⠞⠊⠉
rule trans nonesthetically ⠝⠕⠝⠑⠎⠮⠞⠊⠉⠁⠇⠇⠽
rule trans nonesurient ⠝⠕⠝⠑⠎⠥⠗⠊⠢⠞
rule trans nonet ⠝⠕⠝⠑⠞
rule trans noneternal ⠝⠕⠝⠑⠞⠻⠝⠁⠇
rule trans nonetheless ⠝⠐⠕⠮⠨⠎
rule trans nonethereal ⠝⠕⠝⠑⠮⠗⠂⠇
rule trans nonethical ⠝⠕⠝⠑⠹⠊⠉⠁⠇
rule trans nonethically ⠝⠕⠝⠑⠹⠊⠉⠁⠇⠇⠽
rule trans nonethnic ⠝⠕⠝⠑⠹⠝⠊⠉
rule trans nonethyl ⠝⠕⠝⠑⠹⠽⠇
rule trans noneugenic ⠝⠕⠝⠑⠥⠛⠢⠊⠉
rule trans noneuphonious ⠝⠕⠝⠑⠥⠏⠓⠕⠝⠊⠳⠎
rule trans nonevacuation ⠝⠕⠝⠑⠧⠁⠉⠥⠁⠰⠝
rule trans nonevadable ⠝⠕⠝⠑⠧⠁⠙⠁⠃⠇⠑
rule trans nonevaluation ⠝⠕⠝⠑⠧⠁⠇⠥⠁⠰⠝
rule trans nonevanescent ⠝⠕⠝⠑⠧⠁⠝⠑⠎⠉⠢⠞
rule trans nonevangelical ⠝⠕⠝⠑⠧⠁⠝⠛⠑⠇⠊⠉⠁⠇
rule trans nonevaporating ⠝⠕⠝⠑⠧⠁⠏⠕⠗⠁⠞⠬
rule trans nonevasion ⠝⠕⠝⠑⠧⠁⠨⠝
rule trans nonevent 1345-135-1345-15-1236-26-2345
rule trans noneviction ⠝⠕⠝⠑⠧⠊⠉⠰⠝
rule trans nonevident ⠝⠕⠝⠑⠧⠊⠙⠢⠞
rule trans nonevil ⠝⠕⠝⠑⠧⠊⠇
rule trans nonevincive ⠝⠕⠝⠑⠧⠔⠉⠊⠧⠑
rule trans nonevocative ⠝⠕⠝⠑⠧⠕⠉⠁⠞⠊⠧⠑
rule trans nonevolutionary ⠝⠕⠝⠑⠧⠕⠇⠥⠰⠝⠜⠽
rule trans nonexactable ⠝⠕⠝⠑⠭⠁⠉⠞⠁⠃⠇⠑
rule trans nonexacting ⠝⠕⠝⠑⠭⠁⠉⠞⠬
rule trans nonexaggerated ⠝⠕⠝⠑⠭⠁⠶⠻⠁⠞⠫
rule trans nonexaggeration ⠝⠕⠝⠑⠭⠁⠶⠻⠁⠰⠝
rule trans nonexamination ⠝⠕⠝⠑⠭⠁⠍⠔⠁⠰⠝
rule trans nonexcavation ⠝⠕⠝⠑⠭⠉⠁⠧⠁⠰⠝
rule trans nonexcepted ⠝⠕⠝⠑⠭⠉⠑⠏⠞⠫
rule trans nonexceptional ⠝⠕⠝⠑⠭⠉⠑⠏⠰⠝⠁⠇
rule trans nonexcessive ⠝⠕⠝⠑⠭⠉⠑⠎⠎⠊⠧⠑
rule trans nonexchangeable ⠝⠕⠝⠑⠭⠡⠁⠝⠛⠂⠃⠇⠑
rule trans nonexcitable ⠝⠕⠝⠑⠭⠉⠊⠞⠁⠃⠇⠑
rule trans nonexclamatory ⠝⠕⠝⠑⠭⠉⠇⠁⠍⠁⠞⠕⠗⠽
rule trans nonexclusion ⠝⠕⠝⠑⠭⠉⠇⠥⠨⠝
rule trans nonexcommunicable ⠝⠕⠝⠑⠭⠉⠕⠍⠍⠥⠝⠊⠉⠁⠃⠇⠑
rule trans nonexculpable ⠝⠕⠝⠑⠭⠉⠥⠇⠏⠁⠃⠇⠑
rule trans nonexcusable ⠝⠕⠝⠑⠭⠉⠥⠎⠁⠃⠇⠑
rule trans nonexecutable ⠝⠕⠝⠑⠭⠑⠉⠥⠞⠁⠃⠇⠑
rule trans nonexecution ⠝⠕⠝⠑⠭⠑⠉⠥⠰⠝
rule trans nonexecutive ⠝⠕⠝⠑⠭⠑⠉⠥⠞⠊⠧⠑
rule trans nonexemplary ⠝⠕⠝⠑⠭⠑⠍⠏⠇⠜⠽
rule trans nonexempt 1345-135-1345-15-1346-15-134-1234-2345
rule trans nonexemption ⠝⠕⠝⠑⠭⠑⠍⠏⠰⠝
rule trans nonexemptions ⠝⠕⠝⠑⠭⠑⠍⠏⠰⠝⠎
rule trans nonexercise ⠝⠕⠝⠑⠭⠻⠉⠊⠎⠑
rule trans nonexercising ⠝⠕⠝⠑⠭⠻⠉⠊⠎⠬
rule trans nonexertion ⠝⠕⠝⠑⠭⠻⠰⠝
rule trans nonexhausted ⠝⠕⠝⠑⠭⠓⠁⠥⠌⠫
rule trans nonexhaustive ⠝⠕⠝⠑⠭⠓⠁⠥⠌⠊⠧⠑
rule trans nonexhibition ⠝⠕⠝⠑⠭⠓⠊⠃⠊⠰⠝
rule trans nonexhortation ⠝⠕⠝⠑⠭⠓⠕⠗⠞⠁⠰⠝
rule trans nonexigent ⠝⠕⠝⠑⠭⠊⠛⠢⠞
rule trans nonexistence 1345-135-1345-15-1346-24-34-56-15
rule trans nonexistent 1345-135-1345-15-1346-24-34-26-2345
rule trans nonexisting ⠝⠕⠝⠑⠭⠊⠌⠬
rule trans nonexoneration ⠝⠕⠝⠑⠭⠕⠝⠻⠁⠰⠝
rule trans nonexotic ⠝⠕⠝⠑⠭⠕⠞⠊⠉
rule trans nonexpanding ⠝⠕⠝⠑⠭⠏⠯⠬
rule trans nonexpansion ⠝⠕⠝⠑⠭⠏⠁⠝⠨⠝
rule trans nonexpansive ⠝⠕⠝⠑⠭⠏⠁⠝⠎⠊⠧⠑
rule trans nonexpansively ⠝⠕⠝⠑⠭⠏⠁⠝⠎⠊⠧⠑⠇⠽
rule trans nonexpectant ⠝⠕⠝⠑⠭⠏⠑⠉⠞⠁⠝⠞
rule trans nonexpectation ⠝⠕⠝⠑⠭⠏⠑⠉⠞⠁⠰⠝
rule trans nonexpedience ⠝⠕⠝⠑⠭⠏⠫⠊⠰⠑
rule trans nonexpeditious ⠝⠕⠝⠑⠭⠏⠫⠊⠞⠊⠳⠎
rule trans nonexperienced ⠝⠕⠝⠑⠭⠏⠻⠊⠰⠑⠙
rule trans nonexperimental ⠝⠕⠝⠑⠭⠏⠻⠊⠰⠞⠁⠇
rule trans nonexpiation ⠝⠕⠝⠑⠭⠏⠊⠁⠰⠝
rule trans nonexpiring ⠝⠕⠝⠑⠭⠏⠊⠗⠬
rule trans nonexplanatory ⠝⠕⠝⠑⠭⠏⠇⠁⠝⠁⠞⠕⠗⠽
rule trans nonexploding ⠝⠕⠝⠑⠭⠏⠇⠕⠙⠬
rule trans nonexploitation ⠝⠕⠝⠑⠭⠏⠇⠕⠊⠞⠁⠰⠝
rule trans nonexplosive ⠝⠕⠝⠑⠭⠏⠇⠕⠎⠊⠧⠑
rule trans nonexponential ⠝⠕⠝⠑⠭⠏⠕⠝⠢⠞⠊⠁⠇
rule trans nonexponentially ⠝⠕⠝⠑⠭⠏⠕⠝⠢⠞⠊⠁⠇⠇⠽
rule trans nonexponible ⠝⠕⠝⠑⠭⠏⠕⠝⠊⠃⠇⠑
rule trans nonexport ⠝⠕⠝⠑⠭⠏⠕⠗⠞
rule trans nonexportation ⠝⠕⠝⠑⠭⠏⠕⠗⠞⠁⠰⠝
rule trans nonexposure ⠝⠕⠝⠑⠭⠏⠕⠎⠥⠗⠑
rule trans nonexpressive ⠝⠕⠝⠑⠭⠏⠗⠑⠎⠎⠊⠧⠑
rule trans nonexpressively ⠝⠕⠝⠑⠭⠏⠗⠑⠎⠎⠊⠧⠑⠇⠽
rule trans nonexpulsion ⠝⠕⠝⠑⠭⠏⠥⠇⠨⠝
rule trans nonextempore ⠝⠕⠝⠑⠭⠞⠑⠍⠏⠕⠗⠑
rule trans nonextended ⠝⠕⠝⠑⠭⠞⠢⠙⠫
rule trans nonextending ⠝⠕⠝⠑⠭⠞⠢⠙⠬
rule trans nonextensile ⠝⠕⠝⠑⠭⠞⠢⠎⠊⠇⠑
rule trans nonextension ⠝⠕⠝⠑⠭⠞⠢⠨⠝
rule trans nonextenuating ⠝⠕⠝⠑⠭⠞⠢⠥⠁⠞⠬
rule trans nonextermination ⠝⠕⠝⠑⠭⠞⠻⠍⠔⠁⠰⠝
rule trans nonexternal ⠝⠕⠝⠑⠭⠞⠻⠝⠁⠇
rule trans nonextinct ⠝⠕⠝⠑⠭⠞⠔⠉⠞
rule trans nonextinguished ⠝⠕⠝⠑⠭⠞⠬⠥⠊⠩⠫
rule trans nonextortive ⠝⠕⠝⠑⠭⠞⠕⠗⠞⠊⠧⠑
rule trans nonextractable ⠝⠕⠝⠑⠭⠞⠗⠁⠉⠞⠁⠃⠇⠑
rule trans nonextraction ⠝⠕⠝⠑⠭⠞⠗⠁⠉⠰⠝
rule trans nonextradition ⠝⠕⠝⠑⠭⠞⠗⠁⠙⠊⠰⠝
rule trans nonextraneous ⠝⠕⠝⠑⠭⠞⠗⠁⠝⠑⠳⠎
rule trans nonextreme ⠝⠕⠝⠑⠭⠞⠗⠑⠍⠑
rule trans nonextricable ⠝⠕⠝⠑⠭⠞⠗⠊⠉⠁⠃⠇⠑
rule trans nonextrinsic ⠝⠕⠝⠑⠭⠞⠗⠔⠎⠊⠉
rule trans nonexuberant ⠝⠕⠝⠑⠭⠥⠃⠻⠁⠝⠞
rule trans nonexuding ⠝⠕⠝⠑⠭⠥⠙⠬
rule trans nonexultant ⠝⠕⠝⠑⠭⠥⠇⠞⠁⠝⠞
rule trans nonexultation ⠝⠕⠝⠑⠭⠥⠇⠞⠁⠰⠝
rule trans nonmonetary ⠝⠕⠝⠍⠐⠕⠞⠜⠽
rule trans nonphonemic ⠝⠕⠝⠏⠓⠕⠝⠑⠍⠊⠉
rule trans nonphonetic ⠝⠕⠝⠏⠓⠕⠝⠑⠞⠊⠉
rule trans notonecta ⠝⠕⠞⠕⠝⠑⠉⠞⠁
rule trans oconee ⠕⠉⠕⠝⠑⠑
rule trans octonematous ⠕⠉⠞⠕⠝⠑⠍⠁⠞⠳⠎
rule trans oenone ⠕⠢⠕⠝⠑
rule trans oligonephria ⠕⠇⠊⠛⠕⠝⠑⠏⠓⠗⠊⠁
rule trans olonets ⠕⠇⠕⠝⠑⠞⠎
rule trans oneal 135-1345-2-123
rule trans oneco ⠕⠝⠑⠉⠕
rule trans onega 135-1345-15-1245-1
rule trans onega's ⠕⠝⠑⠛⠁⠄⠎
rule trans onegin 135-1345-15-1245-35
rule trans onegite ⠕⠝⠑⠛⠊⠞⠑
rule trans onego ⠕⠝⠑⠛⠕
rule trans oneida 135-1345-15-24-145-1
rule trans oneil ⠕⠝⠑⠊⠇
rule trans oneil's ⠕⠝⠑⠊⠇⠄⠎
rule trans oneill ⠕⠝⠑⠊⠇⠇
rule trans oneill's ⠕⠝⠑⠊⠇⠇⠄⠎
rule trans oneiric ⠕⠝⠑⠊⠗⠊⠉
rule trans oneirical ⠕⠝⠑⠊⠗⠊⠉⠁⠇
rule trans oneirocritic ⠕⠝⠑⠊⠗⠕⠉⠗⠊⠞⠊⠉
rule trans oneirocritical ⠕⠝⠑⠊⠗⠕⠉⠗⠊⠞⠊⠉⠁⠇
rule trans oneirology ⠕⠝⠑⠊⠗⠕⠇⠕⠛⠽
rule trans onekama ⠕⠝⠑⠅⠁⠍⠁
rule trans oneonta ⠕⠝⠑⠕⠝⠞⠁
rule trans onerary ⠕⠝⠻⠜⠽
rule trans onerate ⠕⠝⠻⠁⠞⠑
rule trans onerative ⠕⠝⠻⠁⠞⠊⠧⠑
rule trans onerier ⠕⠝⠻⠊⠻
rule trans oneriest ⠕⠝⠻⠊⠑⠌
rule trans onerose ⠕⠝⠻⠕⠎⠑
rule trans onerosity ⠕⠝⠻⠕⠎⠰⠽
rule trans onerous 135-1345-12456-1256-234
rule trans onerously ⠕⠝⠻⠳⠎⠇⠽
rule trans onerousness ⠕⠝⠻⠳⠎⠰⠎
rule trans onery ⠕⠝⠻⠽
rule trans onesimus ⠕⠝⠑⠎⠊⠍⠥⠎
rule trans onesiphorus ⠕⠝⠑⠎⠊⠏⠓⠕⠗⠥⠎
rule trans onionet ⠕⠝⠊⠕⠝⠑⠞
rule trans ophthalmoneuritis ⠕⠏⠓⠹⠁⠇⠍⠕⠝⠑⠥⠗⠊⠞⠊⠎
rule trans opilionea ⠕⠏⠊⠇⠊⠕⠝⠑⠁
rule trans opiliones ⠕⠏⠊⠇⠊⠕⠝⠑⠎
rule trans opponency ⠕⠏⠏⠕⠝⠢⠉⠽
rule trans opponens ⠕⠏⠏⠕⠝⠢⠎
rule trans orthonectida ⠕⠗⠹⠕⠝⠑⠉⠞⠊⠙⠁
rule trans orthotonesis ⠕⠗⠹⠕⠞⠕⠝⠑⠎⠊⠎
rule trans osteonecrosis ⠕⠌⠑⠕⠝⠑⠉⠗⠕⠎⠊⠎
rule trans osteoneuralgia ⠕⠌⠑⠕⠝⠑⠥⠗⠁⠇⠛⠊⠁
rule trans otoneurology ⠕⠞⠕⠝⠑⠥⠗⠕⠇⠕⠛⠽
rule trans overhonest ⠕⠧⠻⠓⠐⠕⠌
rule trans oxytonesis ⠕⠭⠽⠞⠕⠝⠑⠎⠊⠎
rule trans padrone ⠏⠁⠙⠗⠕⠝⠑
rule trans padrone's ⠏⠁⠙⠗⠕⠝⠑⠄⠎
rule trans padrones ⠏⠁⠙⠗⠕⠝⠑⠎
rule trans palaeonemertea ⠏⠁⠇⠁⠑⠕⠝⠑⠍⠻⠞⠑⠁
rule trans palaeonemertean ⠏⠁⠇⠁⠑⠕⠝⠑⠍⠻⠞⠂⠝
rule trans pallone ⠏⠁⠇⠇⠕⠝⠑
rule trans pallones ⠏⠁⠇⠇⠕⠝⠑⠎
rule trans panettone ⠏⠁⠝⠑⠞⠞⠕⠝⠑
rule trans panettones ⠏⠁⠝⠑⠞⠞⠕⠝⠑⠎
rule trans pantalone ⠏⠁⠝⠞⠁⠇⠕⠝⠑
rule trans pantalone's ⠏⠁⠝⠞⠁⠇⠕⠝⠑⠄⠎
rule trans papiliones ⠏⠁⠏⠊⠇⠊⠕⠝⠑⠎
rule trans paraphronesis ⠏⠜⠁⠏⠓⠗⠕⠝⠑⠎⠊⠎
rule trans pardonee ⠏⠜⠙⠕⠝⠑⠑
rule trans parsonese ⠏⠜⠎⠕⠝⠑⠎⠑
rule trans parsoness ⠏⠜⠎⠕⠰⠎
rule trans parsonet ⠏⠜⠎⠕⠝⠑⠞
rule trans patagones ⠏⠁⠞⠁⠛⠕⠝⠑⠎
rule trans pathoneurosis ⠏⠁⠹⠕⠝⠑⠥⠗⠕⠎⠊⠎
rule trans patroness ⠏⠁⠞⠗⠕⠰⠎
rule trans pensione ⠏⠢⠎⠊⠕⠝⠑
rule trans pensioned ⠏⠢⠨⠝⠫
rule trans pensioner ⠏⠢⠨⠝⠻
rule trans pentagonese ⠏⠢⠞⠁⠛⠕⠝⠑⠎⠑
rule trans peones ⠏⠑⠕⠝⠑⠎
rule trans peptonemia ⠏⠑⠏⠞⠕⠝⠑⠍⠊⠁
rule trans peripheroneural ⠏⠻⠊⠏⠓⠻⠕⠝⠑⠥⠗⠁⠇
rule trans peritonea 1234-12456-24-2345-135-1345-15-1
rule trans peritoneal ⠏⠻⠊⠞⠕⠝⠂⠇
rule trans peritoneomuscular ⠏⠻⠊⠞⠕⠝⠑⠕⠍⠥⠎⠉⠥⠇⠜
rule trans peritoneoscopy ⠏⠻⠊⠞⠕⠝⠑⠕⠎⠉⠕⠏⠽
rule trans peritoneum 1234-12456-24-2345-135-1345-15-136-134
rule trans peroneal ⠏⠻⠕⠝⠂⠇
rule trans peroneotarsal ⠏⠻⠕⠝⠑⠕⠞⠜⠎⠁⠇
rule trans peroneus ⠏⠻⠕⠝⠑⠥⠎
rule trans persephone 1234-12456-234-15-1234-125-135-1345-15
rule trans personeity ⠏⠻⠎⠕⠝⠑⠰⠽
rule trans petronel ⠏⠑⠞⠗⠕⠝⠑⠇
rule trans petronella ⠏⠑⠞⠗⠕⠝⠑⠇⠇⠁
rule trans phonematic ⠏⠓⠕⠝⠑⠍⠁⠞⠊⠉
rule trans phonematics ⠏⠓⠕⠝⠑⠍⠁⠞⠊⠉⠎
rule trans phoneme 1234-125-135-1345-15-134-15
rule trans phonemic 1234-125-135-1345-15-134-24-14
rule trans phonendoscope ⠏⠓⠕⠝⠢⠙⠕⠎⠉⠕⠏⠑
rule trans phonesis ⠏⠓⠕⠝⠑⠎⠊⠎
rule trans phonestheme ⠏⠓⠕⠝⠑⠎⠮⠍⠑
rule trans phonestheme's ⠏⠓⠕⠝⠑⠎⠮⠍⠑⠄⠎
rule trans phonesthemes ⠏⠓⠕⠝⠑⠎⠮⠍⠑⠎
rule trans phonesthemic ⠏⠓⠕⠝⠑⠎⠮⠍⠊⠉
rule trans phonet ⠏⠓⠕⠝⠑⠞
rule trans phonetic 1234-125-135-1345-15-2345-24-14
rule trans phonetism ⠏⠓⠕⠝⠑⠞⠊⠎⠍
rule trans phonetize ⠏⠓⠕⠝⠑⠞⠊⠵⠑
rule trans phonetized ⠏⠓⠕⠝⠑⠞⠊⠵⠫
rule trans phonetizes ⠏⠓⠕⠝⠑⠞⠊⠵⠑⠎
rule trans phonetizing ⠏⠓⠕⠝⠑⠞⠊⠵⠬
rule trans phoroneus ⠏⠓⠕⠗⠕⠝⠑⠥⠎
rule trans photonegative ⠏⠓⠕⠞⠕⠝⠑⠛⠁⠞⠊⠧⠑
rule trans photonegatives ⠏⠓⠕⠞⠕⠝⠑⠛⠁⠞⠊⠧⠑⠎
rule trans photonephograph ⠏⠓⠕⠞⠕⠝⠑⠏⠓⠕⠛⠗⠁⠏⠓
rule trans photoneutron ⠏⠓⠕⠞⠕⠝⠑⠥⠞⠗⠕⠝
rule trans photoneutrons ⠏⠓⠕⠞⠕⠝⠑⠥⠞⠗⠕⠝⠎
rule trans phronesis ⠏⠓⠗⠕⠝⠑⠎⠊⠎
rule trans physonectae ⠏⠓⠽⠎⠕⠝⠑⠉⠞⠁⠑
rule trans pictones ⠏⠊⠉⠞⠕⠝⠑⠎
rule trans pigeoneer ⠏⠊⠛⠑⠕⠝⠑⠻
rule trans pioneer 1234-24-135-1345-15-12456
rule trans platonesque ⠏⠇⠁⠞⠕⠝⠑⠎⠟⠥⠑
rule trans pleonectic ⠏⠇⠑⠕⠝⠑⠉⠞⠊⠉
rule trans pleonexia ⠏⠇⠑⠕⠝⠑⠭⠊⠁
rule trans pleuronect ⠏⠇⠑⠥⠗⠕⠝⠑⠉⠞
rule trans pleuronema ⠏⠇⠑⠥⠗⠕⠝⠑⠍⠁
rule trans pleuroperitoneal ⠏⠇⠑⠥⠗⠕⠏⠻⠊⠞⠕⠝⠂⠇
rule trans pneumonectasia ⠏⠝⠑⠥⠍⠕⠝⠑⠉⠞⠁⠎⠊⠁
rule trans pneumonedema ⠏⠝⠑⠥⠍⠕⠝⠫⠑⠍⠁
rule trans pneumoperitoneum ⠏⠝⠑⠥⠍⠕⠏⠻⠊⠞⠕⠝⠑⠥⠍
rule trans polonese ⠏⠕⠇⠕⠝⠑⠎⠑
rule trans polygonella ⠏⠕⠇⠽⠛⠕⠝⠑⠇⠇⠁
rule trans polygoneutic ⠏⠕⠇⠽⠛⠕⠝⠑⠥⠞⠊⠉
rule trans pontooneer ⠏⠕⠝⠞⠕⠕⠝⠑⠻
rule trans postponence ⠏⠕⠌⠏⠕⠝⠰⠑
rule trans predisponency ⠏⠗⠫⠊⠎⠏⠕⠝⠢⠉⠽
rule trans preperitoneal ⠏⠗⠑⠏⠻⠊⠞⠕⠝⠂⠇
rule trans progoneate ⠏⠗⠕⠛⠕⠝⠂⠞⠑
rule trans pronegotiation ⠏⠗⠕⠝⠑⠛⠕⠞⠊⠁⠰⠝
rule trans pronephric ⠏⠗⠕⠝⠑⠏⠓⠗⠊⠉
rule trans pronephros ⠏⠗⠕⠝⠑⠏⠓⠗⠕⠎
rule trans proneur ⠏⠗⠕⠝⠑⠥⠗
rule trans properitoneal ⠏⠗⠕⠏⠻⠊⠞⠕⠝⠂⠇
rule trans protonema ⠏⠗⠕⠞⠕⠝⠑⠍⠁
rule trans protonemal ⠏⠗⠕⠞⠕⠝⠑⠍⠁⠇
rule trans protonemata ⠏⠗⠕⠞⠕⠝⠑⠍⠁⠞⠁
rule trans protonematal ⠏⠗⠕⠞⠕⠝⠑⠍⠁⠞⠁⠇
rule trans protonematoid ⠏⠗⠕⠞⠕⠝⠑⠍⠁⠞⠕⠊⠙
rule trans protoneme ⠏⠗⠕⠞⠕⠝⠑⠍⠑
rule trans protonephridium ⠏⠗⠕⠞⠕⠝⠑⠏⠓⠗⠊⠙⠊⠥⠍
rule trans protoneuron ⠏⠗⠕⠞⠕⠝⠑⠥⠗⠕⠝
rule trans protoneutron ⠏⠗⠕⠞⠕⠝⠑⠥⠞⠗⠕⠝
rule trans protoneutrons ⠏⠗⠕⠞⠕⠝⠑⠥⠞⠗⠕⠝⠎
rule trans pseudoneuropter ⠏⠎⠑⠥⠙⠕⠝⠑⠥⠗⠕⠏⠞⠻
rule trans psychoneural ⠏⠎⠽⠡⠕⠝⠑⠥⠗⠁⠇
rule trans psychoneurosis ⠏⠎⠽⠡⠕⠝⠑⠥⠗⠕⠎⠊⠎
rule trans psychoneurotic ⠏⠎⠽⠡⠕⠝⠑⠥⠗⠕⠞⠊⠉
rule trans pulmonectomy ⠏⠥⠇⠍⠕⠝⠑⠉⠞⠕⠍⠽
rule trans pyelonephritic ⠏⠽⠑⠇⠕⠝⠑⠏⠓⠗⠊⠞⠊⠉
rule trans pyelonephritis ⠏⠽⠑⠇⠕⠝⠑⠏⠓⠗⠊⠞⠊⠎
rule trans pyelonephrosis ⠏⠽⠑⠇⠕⠝⠑⠏⠓⠗⠕⠎⠊⠎
rule trans pyonephritis ⠏⠽⠕⠝⠑⠏⠓⠗⠊⠞⠊⠎
rule trans pyonephrosis ⠏⠽⠕⠝⠑⠏⠓⠗⠕⠎⠊⠎
rule trans pyonephrotic ⠏⠽⠕⠝⠑⠏⠓⠗⠕⠞⠊⠉
rule trans pyronema ⠏⠽⠗⠕⠝⠑⠍⠁
rule trans pythoness ⠏⠽⠹⠕⠰⠎
rule trans radionecrosis ⠗⠁⠙⠊⠕⠝⠑⠉⠗⠕⠎⠊⠎
rule trans radioneuritis ⠗⠁⠙⠊⠕⠝⠑⠥⠗⠊⠞⠊⠎
rule trans ramoneur ⠗⠁⠍⠕⠝⠑⠥⠗
rule trans ravonelle ⠗⠁⠧⠕⠝⠑⠇⠇⠑
rule trans reasoner ⠗⠂⠎⠕⠝⠻
rule trans reasoner's ⠗⠂⠎⠕⠝⠻⠄⠎
rule trans reasoners ⠗⠂⠎⠕⠝⠻⠎
rule trans reauditioned ⠗⠑⠁⠥⠙⠊⠰⠝⠫
rule trans rejoneador ⠗⠑⠚⠕⠝⠂⠙⠕⠗
rule trans rejoneador's ⠗⠑⠚⠕⠝⠂⠙⠕⠗⠄⠎
rule trans rejoneadors ⠗⠑⠚⠕⠝⠂⠙⠕⠗⠎
rule trans retroperitoneal ⠗⠑⠞⠗⠕⠏⠻⠊⠞⠕⠝⠂⠇
rule trans rhizoneure ⠗⠓⠊⠵⠕⠝⠑⠥⠗⠑
rule trans rhynchonella ⠗⠓⠽⠝⠡⠕⠝⠑⠇⠇⠁
rule trans rhynchonelloid ⠗⠓⠽⠝⠡⠕⠝⠑⠇⠇⠕⠊⠙
rule trans rhynconellid ⠗⠓⠽⠝⠉⠕⠝⠑⠇⠇⠊⠙
rule trans ronel ⠗⠕⠝⠑⠇
rule trans ronel's ⠗⠕⠝⠑⠇⠄⠎
rule trans ronen ⠗⠕⠝⠢
rule trans ronen's ⠗⠕⠝⠢⠄⠎
rule trans roneo ⠗⠕⠝⠑⠕
rule trans roneo's ⠗⠕⠝⠑⠕⠄⠎
rule trans rooney 1235-135-135-1345-15-13456
rule trans roystonea ⠗⠕⠽⠌⠕⠝⠑⠁
rule trans salmonella 234-1-123-134-135-1345-15-123-123-1
rule trans salmonellosis ⠎⠁⠇⠍⠕⠝⠑⠇⠇⠕⠎⠊⠎
rule trans salmonet ⠎⠁⠇⠍⠕⠝⠑⠞
rule trans samsoness ⠎⠁⠍⠎⠕⠰⠎
rule trans sawbones ⠎⠁⠺⠃⠐⠕⠎
rule trans sawboneses ⠎⠁⠺⠃⠐⠕⠎⠑⠎
rule trans schiavone ⠎⠡⠊⠁⠧⠕⠝⠑
rule trans schiavones ⠎⠡⠊⠁⠧⠕⠝⠑⠎
rule trans schizonemertea ⠎⠡⠊⠵⠕⠝⠑⠍⠻⠞⠑⠁
rule trans scorpiones ⠎⠉⠕⠗⠏⠊⠕⠝⠑⠎
rule trans scytonema ⠎⠉⠽⠞⠕⠝⠑⠍⠁
rule trans scytonematoid ⠎⠉⠽⠞⠕⠝⠑⠍⠁⠞⠕⠊⠙
rule trans scytonematous ⠎⠉⠽⠞⠕⠝⠑⠍⠁⠞⠳⠎
rule trans secamone ⠎⠑⠉⠁⠍⠕⠝⠑
rule trans semicoronet ⠎⠑⠍⠊⠉⠕⠗⠕⠝⠑⠞
rule trans sermoneer ⠎⠻⠍⠕⠝⠑⠻
rule trans sermonesque ⠎⠻⠍⠕⠝⠑⠎⠟⠥⠑
rule trans sermonet ⠎⠻⠍⠕⠝⠑⠞
rule trans sermonette ⠎⠻⠍⠕⠝⠑⠞⠞⠑
rule trans sermonettino ⠎⠻⠍⠕⠝⠑⠞⠞⠔⠕
rule trans seronegative ⠎⠻⠕⠝⠑⠛⠁⠞⠊⠧⠑
rule trans sextoness ⠎⠑⠭⠞⠕⠰⠎
rule trans shoneen ⠩⠕⠝⠑⠢
rule trans shoshone 146-135-146-135-1345-15
rule trans shoshonean ⠩⠕⠩⠕⠝⠂⠝
rule trans silone ⠎⠊⠇⠕⠝⠑
rule trans silone's ⠎⠊⠇⠕⠝⠑⠄⠎
rule trans simonetta ⠎⠊⠍⠕⠝⠑⠞⠞⠁
rule trans siphonet ⠎⠊⠏⠓⠕⠝⠑⠞
rule trans sirione ⠎⠊⠗⠊⠕⠝⠑
rule trans siriones ⠎⠊⠗⠊⠕⠝⠑⠎
rule trans soffione ⠎⠷⠋⠊⠕⠝⠑
rule trans solonets ⠎⠕⠇⠕⠝⠑⠞⠎
rule trans solonetz ⠎⠕⠇⠕⠝⠑⠞⠵
rule trans sonet ⠎⠕⠝⠑⠞
rule trans spinoneural ⠎⠏⠔⠕⠝⠑⠥⠗⠁⠇
rule trans splenonephric ⠎⠏⠇⠢⠕⠝⠑⠏⠓⠗⠊⠉
rule trans spooney ⠎⠏⠕⠕⠝⠑⠽
rule trans spumone 234-1234-136-134-135-1345-15
rule trans steironema ⠌⠑⠊⠗⠕⠝⠑⠍⠁
rule trans stereoneural ⠌⠻⠑⠕⠝⠑⠥⠗⠁⠇
rule trans stonecat ⠌⠐⠕⠉⠁⠞
rule trans stonecats ⠌⠐⠕⠉⠁⠞⠎
rule trans stonechat ⠌⠐⠕⠡⠁⠞
rule trans stonechats ⠌⠐⠕⠡⠁⠞⠎
rule trans stonegate ⠌⠐⠕⠛⠁⠞⠑
rule trans stoneite ⠌⠐⠕⠊⠞⠑
rule trans stonestreet ⠌⠐⠕⠌⠗⠑⠑⠞
rule trans struthiones ⠌⠗⠥⠹⠊⠕⠝⠑⠎
rule trans sturiones ⠌⠥⠗⠊⠕⠝⠑⠎
rule trans subanconeal ⠎⠥⠃⠁⠝⠉⠕⠝⠂⠇
rule trans subdeaconess ⠎⠥⠃⠙⠂⠉⠕⠰⠎
rule trans subpatroness ⠎⠥⠃⠏⠁⠞⠗⠕⠰⠎
rule trans subperitoneal ⠎⠥⠃⠏⠻⠊⠞⠕⠝⠂⠇
rule trans suiones ⠎⠥⠊⠕⠝⠑⠎
rule trans sulfonethylmethane ⠎⠥⠇⠋⠕⠝⠑⠹⠽⠇⠍⠑⠹⠁⠝⠑
rule trans sulphonethylmethane ⠎⠥⠇⠏⠓⠕⠝⠑⠹⠽⠇⠍⠑⠹⠁⠝⠑
rule trans surgeoness ⠎⠥⠗⠛⠑⠕⠰⠎
rule trans sycones ⠎⠽⠉⠕⠝⠑⠎
rule trans symphonetic ⠎⠽⠍⠏⠓⠕⠝⠑⠞⠊⠉
rule trans symphonette ⠎⠽⠍⠏⠓⠕⠝⠑⠞⠞⠑
rule trans synchroneity ⠎⠽⠝⠡⠗⠕⠝⠑⠰⠽
rule trans synecphonesis ⠎⠽⠝⠑⠉⠏⠓⠕⠝⠑⠎⠊⠎
rule trans tamonea ⠞⠁⠍⠕⠝⠑⠁
rule trans tarsonemid ⠞⠜⠎⠕⠝⠑⠍⠊⠙
rule trans tarsonemidae ⠞⠜⠎⠕⠝⠑⠍⠊⠙⠁⠑
rule trans tenonectomies ⠞⠢⠕⠝⠑⠉⠞⠕⠍⠊⠑⠎
rule trans tenonectomy ⠞⠢⠕⠝⠑⠉⠞⠕⠍⠽
rule trans thermoneurosis ⠮⠗⠍⠕⠝⠑⠥⠗⠕⠎⠊⠎
rule trans thermoneutral ⠮⠗⠍⠕⠝⠑⠥⠞⠗⠁⠇
rule trans thigmonegative ⠹⠊⠛⠍⠕⠝⠑⠛⠁⠞⠊⠧⠑
rule trans timoneer ⠞⠊⠍⠕⠝⠑⠻
rule trans tonedeaf ⠞⠐⠕⠙⠂⠋
rule trans tonedeafness ⠞⠐⠕⠙⠂⠋⠰⠎
rule trans tonelada ⠞⠕⠝⠑⠇⠁⠙⠁
rule trans toneladas ⠞⠕⠝⠑⠇⠁⠙⠁⠎
rule trans toneme ⠞⠕⠝⠑⠍⠑
rule trans toneme's ⠞⠕⠝⠑⠍⠑⠄⠎
rule trans tonemes ⠞⠕⠝⠑⠍⠑⠎
rule trans tonemic ⠞⠕⠝⠑⠍⠊⠉
rule trans tonemically ⠞⠕⠝⠑⠍⠊⠉⠁⠇⠇⠽
rule trans tonetic ⠞⠕⠝⠑⠞⠊⠉
rule trans tonetically ⠞⠕⠝⠑⠞⠊⠉⠁⠇⠇⠽
rule trans tonetician ⠞⠕⠝⠑⠞⠊⠉⠊⠁⠝
rule trans tonette ⠞⠕⠝⠑⠞⠞⠑
rule trans toone ⠞⠕⠕⠝⠑
rule trans toone's ⠞⠕⠕⠝⠑⠄⠎
rule trans toponeural ⠞⠕⠏⠕⠝⠑⠥⠗⠁⠇
rule trans torrone ⠞⠕⠗⠗⠕⠝⠑
rule trans torrones ⠞⠕⠗⠗⠕⠝⠑⠎
rule trans transperitoneal ⠞⠗⠁⠝⠎⠏⠻⠊⠞⠕⠝⠂⠇
rule trans treponema ⠞⠗⠑⠏⠕⠝⠑⠍⠁
rule trans treponemas ⠞⠗⠑⠏⠕⠝⠑⠍⠁⠎
rule trans treponemata ⠞⠗⠑⠏⠕⠝⠑⠍⠁⠞⠁
rule trans treponematosis ⠞⠗⠑⠏⠕⠝⠑⠍⠁⠞⠕⠎⠊⠎
rule trans treponeme ⠞⠗⠑⠏⠕⠝⠑⠍⠑
rule trans treponemes ⠞⠗⠑⠏⠕⠝⠑⠍⠑⠎
rule trans treponemicidal ⠞⠗⠑⠏⠕⠝⠑⠍⠊⠉⠊⠙⠁⠇
rule trans treponemicide ⠞⠗⠑⠏⠕⠝⠑⠍⠊⠉⠊⠙⠑
rule trans tribonema ⠞⠗⠊⠃⠕⠝⠑⠍⠁
rule trans trigonella ⠞⠗⠊⠛⠕⠝⠑⠇⠇⠁
rule trans trigoneutic ⠞⠗⠊⠛⠕⠝⠑⠥⠞⠊⠉
rule trans trigoneutism ⠞⠗⠊⠛⠕⠝⠑⠥⠞⠊⠎⠍
rule trans tritoness ⠞⠗⠊⠞⠕⠰⠎
rule trans trophonema ⠞⠗⠕⠏⠓⠕⠝⠑⠍⠁
rule trans trophonemata ⠞⠗⠕⠏⠓⠕⠝⠑⠍⠁⠞⠁
rule trans trophoneurotic ⠞⠗⠕⠏⠓⠕⠝⠑⠥⠗⠕⠞⠊⠉
rule trans tuonela ⠞⠥⠕⠝⠑⠇⠁
rule trans tuonela's ⠞⠥⠕⠝⠑⠇⠁⠄⠎
rule trans twoness ⠞⠺⠕⠰⠎
rule trans ultroneous ⠥⠇⠞⠗⠕⠝⠑⠳⠎
rule trans unbaronet ⠥⠝⠃⠜⠕⠝⠑⠞
rule trans uncolonellike ⠥⠝⠉⠕⠇⠕⠝⠑⠇⠇⠊⠅⠑
rule trans uncoroneted ⠥⠝⠉⠕⠗⠕⠝⠑⠞⠫
rule trans underhonest ⠐⠥⠓⠐⠕⠌
rule trans undermentioned ⠐⠥⠍⠢⠰⠝⠫
rule trans unerroneous ⠥⠝⠻⠗⠕⠝⠑⠳⠎
rule trans unhonestly ⠥⠝⠓⠐⠕⠌⠇⠽
rule trans unhonesty ⠥⠝⠓⠐⠕⠌⠽
rule trans unmentioned ⠥⠝⠍⠢⠰⠝⠫
rule trans unpensioned ⠥⠝⠏⠢⠨⠝⠫
rule trans unphonetic ⠥⠝⠏⠓⠕⠝⠑⠞⠊⠉
rule trans unpioneering ⠥⠝⠏⠊⠕⠝⠑⠻⠬
rule trans unstationed ⠥⠝⠌⠁⠰⠝⠫
rule trans vasoneurosis ⠧⠁⠎⠕⠝⠑⠥⠗⠕⠎⠊⠎
rule trans veillonella ⠧⠑⠊⠇⠇⠕⠝⠑⠇⠇⠁
rule trans vermilionette ⠧⠻⠍⠊⠇⠊⠕⠝⠑⠞⠞⠑
rule trans veronese 1236-12456-135-1345-15-234-15
rule trans waggonette ⠺⠁⠶⠕⠝⠑⠞⠞⠑
rule trans wagoneer ⠺⠁⠛⠕⠝⠑⠻
rule trans wagoneers ⠺⠁⠛⠕⠝⠑⠻⠎
rule trans wagonette ⠺⠁⠛⠕⠝⠑⠞⠞⠑
rule trans wagonette's ⠺⠁⠛⠕⠝⠑⠞⠞⠑⠄⠎
rule trans wagonettes ⠺⠁⠛⠕⠝⠑⠞⠞⠑⠎
rule trans washingtonese ⠺⠁⠩⠬⠞⠕⠝⠑⠎⠑
rule trans weaponeer ⠺⠂⠏⠕⠝⠑⠻
rule trans weaponeer's ⠺⠂⠏⠕⠝⠑⠻⠄⠎
rule trans weaponeers ⠺⠂⠏⠕⠝⠑⠻⠎
rule trans zabaglione ⠵⠁⠃⠁⠛⠇⠊⠕⠝⠑
rule trans zabagliones ⠵⠁⠃⠁⠛⠇⠊⠕⠝⠑⠎
rule trans zonesthesia ⠵⠕⠝⠑⠎⠮⠎⠊⠁
rule trans zygoneure ⠵⠽⠛⠕⠝⠑⠥⠗⠑
use

uses - - rule trans donell ⠙⠕⠝⠑⠇⠇
uses - - rule trans doneven ⠙⠕⠝⠑⠧⠢

use word_mid_end_+ word_mid_end_-
rule trans oned 135-1345-1246
rule trans onent 135-1345-26-2345
rule trans oner 135-1345-12456
rule trans onest 135-1345-15-34
use

## ought
uses not_modifier_<+ - rule trans ought 5-1256

use word_whole_begin_+ word_whole_begin_-
rule trans ploughtail ⠏⠇⠳⠣⠞⠁⠊⠇
rule trans roughtail ⠗⠳⠣⠞⠁⠊⠇
use


## part
uses not_modifier_<+ - rule trans part 5-1234

use word_whole_begin_+ word_whole_begin_-
rule trans parthenogenesis 1234-345-2346-1345-135-1245-26-15-234-24-234
rule trans parthenon 1234-345-2346-1345-135-1345
rule trans parthia 1234-345-1456-24-1
use

## question
uses not_modifier_<+ - rule trans question 5-12345

## right
uses not_modifier_<+ - rule trans right 5-1235

## some   10.7.7
uses not_modifier_<+ - rule trans some 5-234

use word_whole_begin_+ word_whole_begin_-
rule trans anisomeric ⠁⠝⠊⠎⠕⠍⠻⠊⠉
rule trans anisomerous ⠁⠝⠊⠎⠕⠍⠻⠳⠎
rule trans anisometric ⠁⠝⠊⠎⠕⠍⠑⠞⠗⠊⠉
rule trans anisometropia ⠁⠝⠊⠎⠕⠍⠑⠞⠗⠕⠏⠊⠁
rule trans blossomed 12-123-135-234-234-135-134-1246
rule trans chromoisomer ⠡⠗⠕⠍⠕⠊⠎⠕⠍⠻
rule trans chromoisomeric ⠡⠗⠕⠍⠕⠊⠎⠕⠍⠻⠊⠉
rule trans chromoisomerism ⠡⠗⠕⠍⠕⠊⠎⠕⠍⠻⠊⠎⠍
rule trans compressometer ⠉⠕⠍⠏⠗⠑⠎⠎⠕⠍⠑⠞⠻
rule trans diastereoisomer ⠙⠊⠁⠌⠻⠑⠕⠊⠎⠕⠍⠻
rule trans drosometer ⠙⠗⠕⠎⠕⠍⠑⠞⠻
rule trans ellipsometer ⠑⠇⠇⠊⠏⠎⠕⠍⠑⠞⠻
rule trans ellipsometry ⠑⠇⠇⠊⠏⠎⠕⠍⠑⠞⠗⠽
rule trans extensometer ⠑⠭⠞⠢⠎⠕⠍⠑⠞⠻
rule trans gasometer 1245-1-234-135-134-15-2345-12456
rule trans gasometric ⠛⠁⠎⠕⠍⠑⠞⠗⠊⠉
rule trans gasometrical ⠛⠁⠎⠕⠍⠑⠞⠗⠊⠉⠁⠇
rule trans howsomever ⠓⠪⠎⠕⠍⠐⠑
rule trans hypsometer ⠓⠽⠏⠎⠕⠍⠑⠞⠻
rule trans hypsometrist ⠓⠽⠏⠎⠕⠍⠑⠞⠗⠊⠌
rule trans isomer ⠊⠎⠕⠍⠻
rule trans isomera ⠊⠎⠕⠍⠻⠁
rule trans isomerase ⠊⠎⠕⠍⠻⠁⠎⠑
rule trans isomere ⠊⠎⠕⠍⠻⠑
rule trans isomeric ⠊⠎⠕⠍⠻⠊⠉
rule trans isomerical ⠊⠎⠕⠍⠻⠊⠉⠁⠇
rule trans isomeride ⠊⠎⠕⠍⠻⠊⠙⠑
rule trans isomerism ⠊⠎⠕⠍⠻⠊⠎⠍
rule trans isomerisms ⠊⠎⠕⠍⠻⠊⠎⠍⠎
rule trans isomerize ⠊⠎⠕⠍⠻⠊⠵⠑
rule trans isomerized ⠊⠎⠕⠍⠻⠊⠵⠫
rule trans isomerizes ⠊⠎⠕⠍⠻⠊⠵⠑⠎
rule trans isomerizing ⠊⠎⠕⠍⠻⠊⠵⠬
rule trans isomeromorphism ⠊⠎⠕⠍⠻⠕⠍⠕⠗⠏⠓⠊⠎⠍
rule trans isomerous ⠊⠎⠕⠍⠻⠳⠎
rule trans isometric 24-234-135-134-15-2345-1235-24-14
rule trans isometries ⠊⠎⠕⠍⠑⠞⠗⠊⠑⠎
rule trans isometrograph ⠊⠎⠕⠍⠑⠞⠗⠕⠛⠗⠁⠏⠓
rule trans isometropia ⠊⠎⠕⠍⠑⠞⠗⠕⠏⠊⠁
rule trans isometry ⠊⠎⠕⠍⠑⠞⠗⠽
rule trans mesomeric ⠍⠑⠎⠕⠍⠻⠊⠉
rule trans mesometral ⠍⠑⠎⠕⠍⠑⠞⠗⠁⠇
rule trans mesometric ⠍⠑⠎⠕⠍⠑⠞⠗⠊⠉
rule trans mesometrium ⠍⠑⠎⠕⠍⠑⠞⠗⠊⠥⠍
rule trans occlusometer ⠕⠒⠇⠥⠎⠕⠍⠑⠞⠻
rule trans passometer ⠏⠁⠎⠎⠕⠍⠑⠞⠻
rule trans photoisomeric ⠏⠓⠕⠞⠕⠊⠎⠕⠍⠻⠊⠉
rule trans photoisomerization ⠏⠓⠕⠞⠕⠊⠎⠕⠍⠻⠊⠵⠁⠰⠝
rule trans physometra ⠏⠓⠽⠎⠕⠍⠑⠞⠗⠁
rule trans prisometer ⠏⠗⠊⠎⠕⠍⠑⠞⠻
rule trans pseudoisomerism ⠏⠎⠑⠥⠙⠕⠊⠎⠕⠍⠻⠊⠎⠍
rule trans pseudoisometric ⠏⠎⠑⠥⠙⠕⠊⠎⠕⠍⠑⠞⠗⠊⠉
rule trans pulsometer ⠏⠥⠇⠎⠕⠍⠑⠞⠻
rule trans ransomed 1235-1-1345-234-135-134-1246
rule trans somersault 234-135-134-12456-234-1-136-123-2345
rule trans somerset 234-135-134-12456-234-15-2345
rule trans somever ⠎⠕⠍⠐⠑
rule trans stereoisomeric ⠌⠻⠑⠕⠊⠎⠕⠍⠻⠊⠉
rule trans stereoisomerism ⠌⠻⠑⠕⠊⠎⠕⠍⠻⠊⠎⠍
rule trans tensometer ⠞⠢⠎⠕⠍⠑⠞⠻
rule trans torsometer ⠞⠕⠗⠎⠕⠍⠑⠞⠻
rule trans transmissometer ⠞⠗⠁⠝⠎⠍⠊⠎⠎⠕⠍⠑⠞⠻
rule trans unbosomed 136-1345-12-135-234-135-134-1246
rule trans unisomeric ⠥⠝⠊⠎⠕⠍⠻⠊⠉
rule trans unisometrical ⠥⠝⠊⠎⠕⠍⠑⠞⠗⠊⠉⠁⠇
rule trans whatsomever ⠱⠁⠞⠎⠕⠍⠐⠑
rule trans whensomever ⠱⠢⠎⠕⠍⠐⠑
rule trans wheresomever ⠐⠱⠎⠕⠍⠐⠑
rule trans whosomever ⠱⠕⠎⠕⠍⠐⠑
rule trans isomera ⠊⠎⠕⠍⠻⠁
use

## spirit
uses not_modifier_<+ - rule trans spirit 456-234

## there   10.7.2

use word_whole_+ word_whole_-
rule trans there 5-2346
rule trans thereby 5-2346-12-13456
rule trans therefore 5-2346-123456-15
rule trans therefrom 5-2346-124-1235-135-134
rule trans therein 5-2346-35
rule trans thereof 5-2346-12356
rule trans thereon 5-2346-135-1345
rule trans thereto 5-2346-2345-135
rule trans thereupon 5-2346-45-136
rule trans therewith 5-2346-23456
use

## their
uses not_modifier_<+ - rule trans their 456-2346

## these   10.7.2
uses not_modifier_<+ - rule trans these 45-2346

use word_whole_begin_+ word_whole_begin_-
rule trans antitheses 1-1345-2345-24-2346-234-15-234
rule trans hypotheses 125-13456-1234-135-2346-234-15-234
rule trans parentheses 1234-345-26-2346-234-15-234
rule trans syntheses 234-13456-1345-2346-234-15-234
rule trans theses 2346-234-15-234
rule trans theseus 2346-234-15-136-234
use

## those   10.7.2
uses not_modifier_<+ - rule trans those 45-1456

use word_whole_begin_+ word_whole_begin_-
rule trans spathose 234-1234-1-1456-135-234-15
rule trans thoseby 1456-135-234-15-12-13456
use

## through
uses not_modifier_<+ - rule trans through 5-1456

## time   10.7.8
uses not_modifier_<+ - rule trans time 5-2345

use word_whole_begin_+ word_whole_begin_-
rule trans altimeter 1-123-2345-24-134-15-2345-12456
rule trans avertiment ⠁⠧⠻⠞⠊⠰⠞
rule trans centime 14-26-2345-24-134-15
rule trans desentimentaliz ⠙⠑⠎⠢⠞⠊⠰⠞⠁⠇⠊⠵
rule trans divertimenti ⠙⠊⠧⠻⠞⠊⠰⠞⠊
rule trans divertimento ⠙⠊⠧⠻⠞⠊⠰⠞⠕
rule trans hypersentimental ⠓⠽⠏⠻⠎⠢⠞⠊⠰⠞⠁⠇
rule trans intersentimental ⠔⠞⠻⠎⠢⠞⠊⠰⠞⠁⠇
rule trans mortimer 134-135-1235-2345-24-134-12456
rule trans multimedia 134-136-123-2345-24-134-1246-24-1
rule trans oversentimental ⠕⠧⠻⠎⠢⠞⠊⠰⠞⠁⠇
rule trans pentimento ⠏⠢⠞⠊⠰⠞⠕
rule trans presentiment 1234-1235-15-234-26-2345-24-56-2345
rule trans resentiment ⠗⠑⠎⠢⠞⠊⠰⠞
rule trans semisentimental ⠎⠑⠍⠊⠎⠢⠞⠊⠰⠞⠁⠇
rule trans sentiment 234-26-2345-24-56-2345
rule trans sortiment ⠎⠕⠗⠞⠊⠰⠞
rule trans supersentimental ⠎⠥⠏⠻⠎⠢⠞⠊⠰⠞⠁⠇
rule trans unsentimental 136-1345-234-26-2345-24-56-2345-1-123
use

## under   10.7.9
match trans (^|%[_~]%<*)|![ao] under -   - 5-136 -   10.7.9

use word_whole_begin_+ word_whole_begin_-
rule trans underived 136-1345-145-12456-24-1236-1246
rule trans underogatory 136-1345-145-12456-135-1245-1-2345-135-1235-13456
use

## upon   10.7.2
uses not_modifier_<+ - rule trans upon 45-136

uses word_whole_begin_+ word_whole_begin_- rule trans dupont 145-136-1234-135-1345-2345

## where
uses not_modifier_<+ - rule trans where 5-156

use word_whole_begin_+ word_whole_begin_-
rule trans where'er 156-12456-15-3-12456
rule trans whereupon 5-156-45-136
rule trans wherever 156-12456-5-15
use

## whose
uses not_modifier_<+ - rule trans whose 45-156

## word
uses not_modifier_<+ - rule trans word 45-2456

## work
uses not_modifier_<+ - rule trans work 5-2456

uses word_whole_begin_+ word_whole_begin_- rule trans dworkin 145-2456-135-1235-13-35

## world
uses not_modifier_<+ - rule trans world 456-2456

## young
uses not_modifier_<+ - rule trans young 5-13456


########################################
#   10.8   Final-Letter Groupsigns
########################################

filter final_letter_groupsign_+   %a             -
filter final_letter_groupsign_-   @[LETTER_<-]   -

#   The final-letter groupsigns that start with dots 56 are marked like
#   modifiers because thay could be mistaken with the grade 1 indicator, unless
#   they are marking the end of numeric mode.

macro mark_mod_final_letter
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans $1 $2
uses final_letter_groupsign_+ final_letter_groupsign_- rule init \M\;$2;\M \;$2;
eom

macro mark_mod_final_letter_numeric
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans $1 $2
match -backward init - \M\;$2;\M -   (^|!\;3456;)(@[DIGITS_-]|@[DIGITS_-][⠐⠲⠌])+|@[LETTER_DIGITLESS_<-] \;$2; -
eom

## ance
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans ance 46-15

uses word_whole_begin_+ word_whole_begin_- rule trans fiance 124-24-1-1345-14-15   # should be fiancé

## ence
@mark_mod_final_letter_numeric ence 56-15

use word_whole_begin_+ word_whole_begin_-
rule trans anencephalic ⠁⠝⠢⠉⠑⠏⠓⠁⠇⠊⠉
rule trans anencephalous ⠁⠝⠢⠉⠑⠏⠓⠁⠇⠳⠎
rule trans anencephaly ⠁⠝⠢⠉⠑⠏⠓⠁⠇⠽
rule trans archencephalon ⠜⠡⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans diencephalon ⠙⠊⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans echoencephalography ⠑⠡⠕⠢⠉⠑⠏⠓⠁⠇⠕⠛⠗⠁⠏⠓⠽
rule trans electroencephalogram 15-123-15-14-2345-1235-135-26-14-15-1234-125-1-123-135-1245-1235-1-134
rule trans electroencephalograph 15-123-15-14-2345-1235-135-26-14-15-1234-125-1-123-135-1245-1235-1-1234-125
rule trans epencephala ⠑⠏⠢⠉⠑⠏⠓⠁⠇⠁
rule trans epencephalic ⠑⠏⠢⠉⠑⠏⠓⠁⠇⠊⠉
rule trans epencephalon ⠑⠏⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans exencephaly ⠑⠭⠢⠉⠑⠏⠓⠁⠇⠽
rule trans hematencephalon ⠓⠑⠍⠁⠞⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans hydrencephalocele ⠓⠽⠙⠗⠢⠉⠑⠏⠓⠁⠇⠕⠉⠑⠇⠑
rule trans leukoencephalitis ⠇⠑⠥⠅⠕⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠎
rule trans lissencephalia ⠇⠊⠎⠎⠢⠉⠑⠏⠓⠁⠇⠊⠁
rule trans macrencephaly ⠍⠁⠉⠗⠢⠉⠑⠏⠓⠁⠇⠽
rule trans meningoencephalitis ⠍⠢⠬⠕⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠎
rule trans mesencephalon ⠍⠑⠎⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans mesencephalons ⠍⠑⠎⠢⠉⠑⠏⠓⠁⠇⠕⠝⠎
rule trans metencephalic ⠍⠑⠞⠢⠉⠑⠏⠓⠁⠇⠊⠉
rule trans metencephalon ⠍⠑⠞⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans metepencephalon ⠍⠑⠞⠑⠏⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans micrencephaly ⠍⠊⠉⠗⠢⠉⠑⠏⠓⠁⠇⠽
rule trans myelencephalon ⠍⠽⠑⠇⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans myelencephalous ⠍⠽⠑⠇⠢⠉⠑⠏⠓⠁⠇⠳⠎
rule trans myeloencephalitis ⠍⠽⠑⠇⠕⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠎
rule trans neencephalon ⠝⠑⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans notanencephalia ⠝⠕⠞⠁⠝⠢⠉⠑⠏⠓⠁⠇⠊⠁
rule trans otoencephalitis ⠕⠞⠕⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠎
rule trans palaeoencephalon ⠏⠁⠇⠁⠑⠕⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans paleencephala ⠏⠁⠇⠑⠢⠉⠑⠏⠓⠁⠇⠁
rule trans paleencephalon ⠏⠁⠇⠑⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans paleoencephalon ⠏⠁⠇⠑⠕⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans perencephalia ⠏⠻⠢⠉⠑⠏⠓⠁⠇⠊⠁
rule trans periencephalitis ⠏⠻⠊⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠎
rule trans pneumoencephalogram ⠏⠝⠑⠥⠍⠕⠢⠉⠑⠏⠓⠁⠇⠕⠛⠗⠁⠍
rule trans poliencephalitis ⠏⠕⠇⠊⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠎
rule trans polioencephalitis ⠏⠕⠇⠊⠕⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠎
rule trans porencephalic ⠏⠕⠗⠢⠉⠑⠏⠓⠁⠇⠊⠉
rule trans porencephalon ⠏⠕⠗⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans postencephalon ⠏⠕⠌⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans prosencephalic ⠏⠗⠕⠎⠢⠉⠑⠏⠓⠁⠇⠊⠉
rule trans prosencephalon ⠏⠗⠕⠎⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans pseudoencephalitic ⠏⠎⠑⠥⠙⠕⠢⠉⠑⠏⠓⠁⠇⠊⠞⠊⠉
rule trans rhinencephala ⠗⠓⠔⠢⠉⠑⠏⠓⠁⠇⠁
rule trans rhinencephalon ⠗⠓⠔⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans rhombencephalon ⠗⠓⠕⠍⠃⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans subencephalon ⠎⠥⠃⠢⠉⠑⠏⠓⠁⠇⠕⠝
rule trans telencephal ⠞⠑⠇⠢⠉⠑⠏⠓⠁⠇
rule trans thalamencephalic ⠹⠁⠇⠁⠍⠢⠉⠑⠏⠓⠁⠇⠊⠉
rule trans thalamencephalon ⠹⠁⠇⠁⠍⠢⠉⠑⠏⠓⠁⠇⠕⠝
use

## ful
@mark_mod_final_letter ful 56-123

uses word_whole_begin_+ word_whole_begin_- rule trans overfull 135-1236-12456-124-136-123-123

## ity   10.8.3
@mark_mod_final_letter ity 56-13456

use word_whole_+ word_whole_-
rule trans antitype 1-1345-2345-24-2345-13456-1234-15
rule trans biscuity 12-24-234-14-136-24-2345-13456
rule trans dacoity 145-1-14-135-24-2345-13456
rule trans fruity 124-1235-136-24-2345-13456
rule trans hoity-toity 125-135-24-2345-13456-36-2345-135-24-2345-13456
rule trans rabbity 1235-1-23-24-2345-13456
rule trans pityard 1234-24-2345-13456-345-145
use

## less
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans less 46-234

## ment
@mark_mod_final_letter ment 56-2345

use word_whole_begin_+ word_whole_begin_-
rule trans aforementioned 1-123456-15-134-26-56-1345-1246
rule trans beforementioned ⠆⠿⠑⠍⠢⠰⠝⠫
rule trans formention ⠿⠍⠢⠰⠝
rule trans intermention ⠔⠞⠻⠍⠢⠰⠝
rule trans premention ⠏⠗⠑⠍⠢⠰⠝
rule trans remention ⠗⠑⠍⠢⠰⠝
rule trans undermentioned ⠐⠥⠍⠢⠰⠝⠫
rule trans unmentionability ⠥⠝⠍⠢⠰⠝⠁⠃⠊⠇⠰⠽
rule trans unmentionable 136-1345-134-26-56-1345-1-12-123-15
rule trans unmentioned ⠥⠝⠍⠢⠰⠝⠫
use

## ness   10.8.4
@mark_mod_final_letter ness 56-234

use word_whole_begin_+ word_whole_begin_-
rule trans captainess 14-1-1234-2345-1-24-35-15-234-234
rule trans chieftainess 16-24-15-124-2345-1-35-15-234-234
rule trans citizeness 14-24-2345-24-1356-26-15-234-234
rule trans heatheness 125-2-2346-1345-15-234-234
use

#   overrides in
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans iness 24-56-234

## ong
@mark_mod_final_letter_numeric ong 56-1245

use word_whole_begin_+ word_whole_begin_-
rule trans alilonghi ⠁⠇⠊⠇⠕⠝⠣⠊
rule trans alilonghi ⠁⠇⠊⠇⠕⠝⠣⠊
rule trans cannongate ⠉⠁⠝⠝⠕⠝⠛⠁⠞⠑
rule trans cannongate's ⠉⠁⠝⠝⠕⠝⠛⠁⠞⠑⠄⠎
rule trans decongestion ⠙⠑⠉⠰⠛⠑⠎⠰⠝
rule trans lemongrass ⠇⠑⠍⠕⠝⠛⠗⠁⠎⠎
rule trans longhi ⠇⠕⠝⠣⠊
rule trans longhi's ⠇⠕⠝⠣⠊⠄⠎
rule trans longsleever ⠇⠰⠛⠎⠇⠑⠑⠧⠻
rule trans longsleevers ⠇⠰⠛⠎⠇⠑⠑⠧⠻⠎
rule trans melongrower ⠍⠑⠇⠕⠝⠛⠗⠪⠻
rule trans melongrower's ⠍⠑⠇⠕⠝⠛⠗⠪⠻⠄⠎
rule trans melongrowers ⠍⠑⠇⠕⠝⠛⠗⠪⠻⠎
rule trans mesolonghi ⠍⠑⠎⠕⠇⠕⠝⠣⠊
rule trans missolonghi ⠍⠊⠎⠎⠕⠇⠕⠝⠣⠊
rule trans missolonghi's ⠍⠊⠎⠎⠕⠇⠕⠝⠣⠊⠄⠎
rule trans moonglade ⠍⠕⠕⠝⠛⠇⠁⠙⠑
rule trans moonglades ⠍⠕⠕⠝⠛⠇⠁⠙⠑⠎
rule trans moonglow ⠍⠕⠕⠝⠛⠇⠪
rule trans moonglows ⠍⠕⠕⠝⠛⠇⠪⠎
rule trans moongod 134-135-135-1345-1245-135-145
rule trans moongod ⠍⠕⠕⠝⠛⠕⠙
rule trans moongod's ⠍⠕⠕⠝⠛⠕⠙⠄⠎
rule trans moongods ⠍⠕⠕⠝⠛⠕⠙⠎
rule trans noncongestion ⠝⠕⠝⠉⠰⠛⠑⠎⠰⠝
rule trans nongalactic ⠝⠕⠝⠛⠁⠇⠁⠉⠞⠊⠉
rule trans nongalvanized ⠝⠕⠝⠛⠁⠇⠧⠁⠝⠊⠵⠫
rule trans nongame ⠝⠕⠝⠛⠁⠍⠑
rule trans nonganglionic ⠝⠕⠝⠛⠁⠝⠛⠇⠊⠕⠝⠊⠉
rule trans nongangrenous ⠝⠕⠝⠛⠁⠝⠛⠗⠢⠳⠎
rule trans nongarrulous ⠝⠕⠝⠛⠜⠗⠥⠇⠳⠎
rule trans nongas ⠝⠕⠝⠛⠁⠎
rule trans nongaseous 1345-135-1345-1245-1-234-15-1256-234
rule trans nongaseous ⠝⠕⠝⠛⠁⠎⠑⠳⠎
rule trans nongassy ⠝⠕⠝⠛⠁⠎⠎⠽
rule trans nongelatinizing ⠝⠕⠝⠛⠑⠇⠁⠞⠔⠊⠵⠬
rule trans nongelatinous ⠝⠕⠝⠛⠑⠇⠁⠞⠔⠳⠎
rule trans nongelling ⠝⠕⠝⠛⠑⠇⠇⠬
rule trans nongenealogical ⠝⠕⠝⠛⠢⠂⠇⠕⠛⠊⠉⠁⠇
rule trans nongeneralized ⠝⠕⠝⠛⠢⠻⠁⠇⠊⠵⠫
rule trans nongenerating ⠝⠕⠝⠛⠢⠻⠁⠞⠬
rule trans nongenerative ⠝⠕⠝⠛⠢⠻⠁⠞⠊⠧⠑
rule trans nongeneric ⠝⠕⠝⠛⠢⠻⠊⠉
rule trans nongenetic ⠝⠕⠝⠛⠢⠑⠞⠊⠉
rule trans nongenetical ⠝⠕⠝⠛⠢⠑⠞⠊⠉⠁⠇
rule trans nongenetically ⠝⠕⠝⠛⠢⠑⠞⠊⠉⠁⠇⠇⠽
rule trans nongentile ⠝⠕⠝⠛⠢⠞⠊⠇⠑
rule trans nongentiles ⠝⠕⠝⠛⠢⠞⠊⠇⠑⠎
rule trans nongenuine ⠝⠕⠝⠛⠢⠥⠔⠑
rule trans nongeographic ⠝⠕⠝⠛⠑⠕⠛⠗⠁⠏⠓⠊⠉
rule trans nongeographical ⠝⠕⠝⠛⠑⠕⠛⠗⠁⠏⠓⠊⠉⠁⠇
rule trans nongeological ⠝⠕⠝⠛⠑⠕⠇⠕⠛⠊⠉⠁⠇
rule trans nongeometric ⠝⠕⠝⠛⠑⠕⠍⠑⠞⠗⠊⠉
rule trans nongeometrical ⠝⠕⠝⠛⠑⠕⠍⠑⠞⠗⠊⠉⠁⠇
rule trans nongeometrically ⠝⠕⠝⠛⠑⠕⠍⠑⠞⠗⠊⠉⠁⠇⠇⠽
rule trans nongermane ⠝⠕⠝⠛⠻⠍⠁⠝⠑
rule trans nongerminal ⠝⠕⠝⠛⠻⠍⠔⠁⠇
rule trans nongerminating ⠝⠕⠝⠛⠻⠍⠔⠁⠞⠬
rule trans nongermination ⠝⠕⠝⠛⠻⠍⠔⠁⠰⠝
rule trans nongerundial ⠝⠕⠝⠛⠻⠥⠝⠙⠊⠁⠇
rule trans nongerundive ⠝⠕⠝⠛⠻⠥⠝⠙⠊⠧⠑
rule trans nongestic ⠝⠕⠝⠛⠑⠌⠊⠉
rule trans nongilded ⠝⠕⠝⠛⠊⠇⠙⠫
rule trans nongildsman ⠝⠕⠝⠛⠊⠇⠙⠎⠍⠁⠝
rule trans nongilled ⠝⠕⠝⠛⠊⠇⠇⠫
rule trans nongipsies ⠝⠕⠝⠛⠊⠏⠎⠊⠑⠎
rule trans nongipsy ⠝⠕⠝⠛⠊⠏⠎⠽
rule trans nonglacial ⠝⠕⠝⠛⠇⠁⠉⠊⠁⠇
rule trans nonglandered ⠝⠕⠝⠛⠇⠯⠻⠫
rule trans nonglandular ⠝⠕⠝⠛⠇⠯⠥⠇⠜
rule trans nonglare ⠝⠕⠝⠛⠇⠜⠑
rule trans nonglazed ⠝⠕⠝⠛⠇⠁⠵⠫
rule trans nonglobular ⠝⠕⠝⠛⠇⠕⠃⠥⠇⠜
rule trans nonglucose ⠝⠕⠝⠛⠇⠥⠉⠕⠎⠑
rule trans nonglutenous ⠝⠕⠝⠛⠇⠥⠞⠢⠳⠎
rule trans nongod ⠝⠕⠝⠛⠕⠙
rule trans nongold ⠝⠕⠝⠛⠕⠇⠙
rule trans nongolfer ⠝⠕⠝⠛⠕⠇⠋⠻
rule trans nongolfers ⠝⠕⠝⠛⠕⠇⠋⠻⠎
rule trans nongospel ⠝⠕⠝⠛⠕⠎⠏⠑⠇
rule trans nongovernance ⠝⠕⠝⠛⠕⠧⠻⠝⠨⠑
rule trans nongovernment ⠝⠕⠝⠛⠕⠧⠻⠝⠰⠞
rule trans nongovernmental 1345-135-1345-1245-135-1236-12456-1345-56-2345-1-123
rule trans nongraceful ⠝⠕⠝⠛⠗⠁⠉⠑⠰⠇
rule trans nongraciosity ⠝⠕⠝⠛⠗⠁⠉⠊⠕⠎⠰⠽
rule trans nongracious ⠝⠕⠝⠛⠗⠁⠉⠊⠳⠎
rule trans nongraciously ⠝⠕⠝⠛⠗⠁⠉⠊⠳⠎⠇⠽
rule trans nongraded ⠝⠕⠝⠛⠗⠁⠙⠫
rule trans nongraduate ⠝⠕⠝⠛⠗⠁⠙⠥⠁⠞⠑
rule trans nongraduates ⠝⠕⠝⠛⠗⠁⠙⠥⠁⠞⠑⠎
rule trans nongraduation ⠝⠕⠝⠛⠗⠁⠙⠥⠁⠰⠝
rule trans nongrain ⠝⠕⠝⠛⠗⠁⠔
rule trans nongrains ⠝⠕⠝⠛⠗⠁⠔⠎
rule trans nongrainy ⠝⠕⠝⠛⠗⠁⠔⠽
rule trans nongrammatical ⠝⠕⠝⠛⠗⠁⠍⠍⠁⠞⠊⠉⠁⠇
rule trans nongranular ⠝⠕⠝⠛⠗⠁⠝⠥⠇⠜
rule trans nongranulated ⠝⠕⠝⠛⠗⠁⠝⠥⠇⠁⠞⠫
rule trans nongraphic ⠝⠕⠝⠛⠗⠁⠏⠓⠊⠉
rule trans nongraphical ⠝⠕⠝⠛⠗⠁⠏⠓⠊⠉⠁⠇
rule trans nongraphically ⠝⠕⠝⠛⠗⠁⠏⠓⠊⠉⠁⠇⠇⠽
rule trans nongraphics ⠝⠕⠝⠛⠗⠁⠏⠓⠊⠉⠎
rule trans nongraphitic ⠝⠕⠝⠛⠗⠁⠏⠓⠊⠞⠊⠉
rule trans nongrass ⠝⠕⠝⠛⠗⠁⠎⠎
rule trans nongrasses ⠝⠕⠝⠛⠗⠁⠎⠎⠑⠎
rule trans nongratification ⠝⠕⠝⠛⠗⠁⠞⠊⠋⠊⠉⠁⠰⠝
rule trans nongratifying ⠝⠕⠝⠛⠗⠁⠞⠊⠋⠽⠬
rule trans nongratuitous ⠝⠕⠝⠛⠗⠁⠞⠥⠊⠞⠳⠎
rule trans nongraven ⠝⠕⠝⠛⠗⠁⠧⠢
rule trans nongravitational ⠝⠕⠝⠛⠗⠁⠧⠊⠞⠁⠰⠝⠁⠇
rule trans nongravity ⠝⠕⠝⠛⠗⠁⠧⠰⠽
rule trans nongray ⠝⠕⠝⠛⠗⠁⠽
rule trans nongrayed ⠝⠕⠝⠛⠗⠁⠽⠫
rule trans nongreased ⠝⠕⠝⠛⠗⠂⠎⠫
rule trans nongreasy ⠝⠕⠝⠛⠗⠂⠎⠽
rule trans nongreen ⠝⠕⠝⠛⠗⠑⠢
rule trans nongregarious ⠝⠕⠝⠛⠗⠑⠛⠜⠊⠳⠎
rule trans nongremial ⠝⠕⠝⠛⠗⠑⠍⠊⠁⠇
rule trans nongrey ⠝⠕⠝⠛⠗⠑⠽
rule trans nongreyed ⠝⠕⠝⠛⠗⠑⠽⠫
rule trans nongrieving ⠝⠕⠝⠛⠗⠊⠑⠧⠬
rule trans nongrievous ⠝⠕⠝⠛⠗⠊⠑⠧⠳⠎
rule trans nongrooming ⠝⠕⠝⠛⠗⠕⠕⠍⠬
rule trans nongrounded ⠝⠕⠝⠛⠗⠨⠙⠫
rule trans nonguarantee ⠝⠕⠝⠛⠥⠜⠁⠝⠞⠑⠑
rule trans nonguaranteed ⠝⠕⠝⠛⠥⠜⠁⠝⠞⠑⠫
rule trans nonguarantees ⠝⠕⠝⠛⠥⠜⠁⠝⠞⠑⠑⠎
rule trans nonguard ⠝⠕⠝⠛⠥⠜⠙
rule trans nonguarded ⠝⠕⠝⠛⠥⠜⠙⠫
rule trans nonguarding ⠝⠕⠝⠛⠥⠜⠙⠬
rule trans nonguards ⠝⠕⠝⠛⠥⠜⠙⠎
rule trans nonguidable ⠝⠕⠝⠛⠥⠊⠙⠁⠃⠇⠑
rule trans nonguidance ⠝⠕⠝⠛⠥⠊⠙⠨⠑
rule trans nonguided ⠝⠕⠝⠛⠥⠊⠙⠫
rule trans nonguiding ⠝⠕⠝⠛⠥⠊⠙⠬
rule trans nonguilt ⠝⠕⠝⠛⠥⠊⠇⠞
rule trans nonguttural ⠝⠕⠝⠛⠥⠞⠞⠥⠗⠁⠇
rule trans nongymnast ⠝⠕⠝⠛⠽⠍⠝⠁⠌
rule trans nongymnasts ⠝⠕⠝⠛⠽⠍⠝⠁⠌⠎
rule trans nongypsies ⠝⠕⠝⠛⠽⠏⠎⠊⠑⠎
rule trans nongypsy ⠝⠕⠝⠛⠽⠏⠎⠽
rule trans precongestion ⠏⠗⠑⠉⠰⠛⠑⠎⠰⠝
rule trans recongestion ⠗⠑⠉⠰⠛⠑⠎⠰⠝
rule trans schongauer ⠎⠡⠕⠝⠛⠁⠥⠻
rule trans supercongestion ⠎⠥⠏⠻⠉⠰⠛⠑⠎⠰⠝
use

## ound
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans ound 46-145

## ount
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans ount 46-2345

## sion
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans sion 46-1345

use word_whole_begin_+ word_whole_begin_-
rule trans jasione ⠚⠁⠎⠊⠕⠝⠑
rule trans pensione ⠏⠢⠎⠊⠕⠝⠑
use

## tion
@mark_mod_final_letter tion 56-1345

uses word_whole_begin_+ word_whole_begin_- rule trans cation 14-1-2345-24-135-1345


########################################
#   10.9   Shortforms
########################################

macro contraction
rule premode $1 \;56;$1
rule premode $2 \;56;$2
rule premode $3 \;56;$3
rule premode $4 \;56;$4
rule premode $5 \;56;$5
rule premode $6 \;56;$6
eom

filter shortform_+   @[WORD_<+]   @[APOSS_+]@[WORD_>+]
filter shortform_-   @[WORD_<-]   @[APOSS_-]@[WORD_>-]

# 10.9.3

filter shortform_letter_+   @[WORD_<+]%a*             @[LETTER_>+]*@[APOSS_+]@[WORD_>+]
filter shortform_letter_-   @[WORD_<-]@[LETTER_<-]*   @[LETTER_>-]*@[APOSS_-]@[WORD_>-]

use shortform_letter_+ shortform_letter_-

rule trans braille 12-1235-123
rule trans great 1245-1235-2345

@contraction brl Brl BRL brls Brls BRLS   # braille
@contraction grt Grt GRT grts Grts GRTS   # great

match trans @[WORD_<+]%a* children (%c@[LETTER_>+]*)?@[APOSS_+]@[WORD_>+]   @[WORD_<-]@[LETTER_<-]* 16-1345 (%c@[LETTER_>-]*)?@[APOSS_-]@[WORD_>-]
uses word_whole_+ word_whole_- rule trans chn 14-125-1345

use

pattern CONSONANT_>- @[B_>-]|@[C_>-]|@[D_>-]|@[F_>-]|@[G_>-]|@[H_>-]|@[J_>-]|@[K_>-]|@[L_>-]|@[M_>-]|@[N_>-]|@[P_>-]|@[Q_>-]|@[R_>-]|@[S_>-]|@[T_>-]|@[V_>-]|@[W_>-]|@[X_>-]|@[Z_>-]

filter shortform_consonant_+   @[WORD_<+]   (%c@[LETTER_>+]*)?@[APOST_+]@[WORD_>+]
filter shortform_consonant_-   @[WORD_<-]   (@[CONSONANT_>-]@[LETTER_>-]*)?@[APOST_-]@[WORD_>-]

use shortform_consonant_+ shortform_consonant_-

rule trans blind 12-123
rule trans first 124-34
rule trans friend 124-1235
rule trans good 1245-145
rule trans letter 123-1235
rule trans little 123-123
rule trans quick 12345-13

rule trans blinds 12-123-234
rule trans firsts 124-34-234
rule trans friends 124-1235-234
rule trans goods 1245-145-234
rule trans letters 123-1235-234
rule trans littles 123-123-234
rule trans quicks 12345-13-234

@contraction bl Bl BL bls Bls BLS                            # blind
uses word_whole_+ word_whole_- rule trans fst 124-234-2345   # first
@contraction fr Fr FR frs Frs FRS                            # friend
@contraction gd Gd GD gds Gds GDS                            # good
@contraction lr Lr LR lrs Lrs LRS                            # letter
@contraction ll Ll LL lls Lls LLS                            # little
@contraction qk Qk QK qks Qks QKS                            # quick

use

#   10.9.5

#   Shortform does contain a groupsign, so it does not require grade 1
#   indicator.  The uncontracted shortform must be defined. (10.9.4)
macro shortform_word
uses shortform_+ shortform_- rule trans $1 $2
uses shortform_+ shortform_- rule trans $3 $4
uses word_whole_+ word_whole_- rule trans $3 $4
eom

#   Shortform does not have contain a groupsign, so it requires grade 1
#   indicator.  (10.9.5)
macro shortform_indicator
uses shortform_+ shortform_- rule trans $1 $2
@contraction $3 $4 $5 $3s $4s $5S
eom

use word_whole_+ word_whole_-
#shortform_indicator   about        1-12 ab Ab AB
@shortform_indicator   above        1-12-1236 abv Abv ABV
@shortform_indicator   according    1-14 ac Ac AC
@shortform_indicator   across       1-14-1235 acr Acr ACR
@shortform_indicator   after        1-124 af Af AF
@shortform_indicator   afternoon    1-124-1345 afn Afn AFN
@shortform_indicator   afterward    1-124-2456 afw Afw AFW
@shortform_indicator   again        1-1245 ag Ag AG
@shortform_word        against      1-1245-34 agst 1-1245-234-2345
#shortform_indicator   almost       1-123-134 alm Alm ALM
@shortform_indicator   already      1-123-1235 alr Alr ALR
@shortform_indicator   also         1-123 al Al AL
@shortform_word        although     1-123-1456 alth 1-123-2345-125
@shortform_indicator   altogether   1-123-2345 alt Alt ALT
@shortform_indicator   always       1-123-2456 alw Alw ALW
@shortform_word        because      23-14 bec 12-15-14
@shortform_word        before       23-124 bef 12-15-124
@shortform_word        behind       23-125 beh 12-15-125
@shortform_word        below        23-123 bel 12-15-123
@shortform_word        beneath      23-1345 ben 12-26   # not 12-15-1345
@shortform_word        beside       23-234 bes 12-15-234
@shortform_word        between      23-2345 bet 12-15-2345
@shortform_word        beyond       23-13456 bey 12-15-13456
@shortform_word        conceive     25-14-1236 concv 14-135-1345-14-1236
@shortform_word        conceiving   25-14-1236-1245 concvg 14-135-1345-14-1236-1245
@shortform_indicator   could        14-145 cd Cd CD
@shortform_indicator   deceive      145-14-1236 dcv Dcv DCV
@shortform_indicator   deceiving    145-14-1236-1245 dcvg Dcvg DCVG
@shortform_indicator   declare      145-14-123 dcl Dcl DCL
@shortform_indicator   declaring    145-14-123-1245 dclg Dclg DCLG
@shortform_indicator   either       15-24 ei Ei EI
@shortform_word        herself      125-12456-124 herf 125-15-1235-124
#shortform_indicator   him          125-134 hm Hm HM
@shortform_indicator   himself      125-134-124 hmf Hmf HMF
@shortform_indicator   immediate    24-134-134 imm Imm IMM
@shortform_indicator   its          1346-234 xs Xs XS
@shortform_indicator   itself       1346-124 xf Xf XF
@shortform_word        much         134-16 mch 134-14-125
@shortform_word        must         134-34 mst 134-234-2345
@shortform_indicator   myself       134-13456-124 myf Myf MYF
@shortform_indicator   necessary    1345-15-14 nec Nec NEC
@shortform_indicator   neither      1345-15-24 nei Nei NEI
@shortform_word        oneself      5-135-124 onef 135-1345-15-124
@shortform_word        ourselves    1256-1235-1236-234 ourvs 135-136-1235-1236-234
@shortform_indicator   paid         1234-145 pd Pd PD
@shortform_word        perceive     1234-12456-14-1236 percv 1234-15-1235-14-1236
@shortform_word        perceiving   1234-12456-14-1236-1245 percvg 1234-15-1235-14-1236-1245
@shortform_word        perhaps      1234-12456-125 perh 1234-15-1235-125
@shortform_indicator   receive      1235-14-1236 rcv Rcv RCV
@shortform_indicator   receiving    1235-14-1236-1245 rcvg Rcvg RCVG
@shortform_indicator   rejoice      1235-245-14 rjc Rjc RJC
@shortform_indicator   rejoicing    1235-245-14-1245 rjcg Rjcg RJCG
@shortform_indicator   said         234-145 sd Sd SD
@shortform_word        should       146-145 shd 234-125-145
@shortform_word        such         234-16 sch 234-14-125
@shortform_word        themselves   2346-134-1236-234 themvs 2345-125-15-134-1236-234
@shortform_word        thyself      1456-13456-124 thyf 2345-125-13456-124
@shortform_indicator   today        2345-145 td Td TD
@shortform_indicator   together     2345-1245-1235 tgr Tgr TGR
@shortform_indicator   tomorrow     2345-134 tm Tm TM
@shortform_indicator   tonight      2345-1345 tn Tn TN
@shortform_indicator   would        2456-145 wd Wd WD
@shortform_indicator   your         13456-1235 yr Yr YR
@shortform_indicator   yourself     13456-1235-124 yrf Yrf YRF
@shortform_indicator   yourselves   13456-1235-1236-234 yrvs Yrvs YRVS
use


########################################
#   Appendex 1
########################################

macro shortform_aah
rule trans $1 $2
rule trans $1s $3
rule premode $4 \;56;$4
rule premode $5 \;56;$5
rule premode $6 \;56;$6
eom

use word_whole_+ word_whole_-
@shortform_aah about 1-12 1-12-1256-2345-234 ab Ab AB
@shortform_aah almost 1-123-134 1-123-134-135-34-234 alm Alm ALM
@shortform_aah him 125-134 125-24-134-234 hm Hm HM
use


use word_whole_+ word_whole_-
@shortform_indicator   'twould                3-2345-2456-145 'twd 'twd 'TWD
@shortform_indicator   'twould've             3-2345-2456-145-3-1236-15 'twd've 'twd've 'TWD'VE
@shortform_indicator   'twoulda               3-2345-2456-145-1 'twda 'twda 'TWDA
@shortform_indicator   'twouldn't             3-2345-2456-145-1345-3-2345 'twdn't 'twdn't 'TWDN'T
@shortform_indicator   'twouldn't've          3-2345-2456-145-1345-3-2345-3-1236-15 'twdn't've 'twdn't've 'TWDN'T'VE
@shortform_indicator   aboutface              1-12-124-1-14-15 abface Abface ABFACE
@shortform_word        aboutfaced             1-12-124-1-14-1246 abfaced 1-12-124-1-14-15-145
@shortform_word        aboutfacer             1-12-124-1-14-12456 abfacer 1-12-124-1-14-15-1235
@shortform_word        aboutfacing            1-12-124-1-14-346 abfacing 1-12-124-1-14-24-1345-1245
@shortform_indicator   aboutturn              1-12-2345-136-1235-1345 abturn Abturn ABTURN
@shortform_word        aboutturned            1-12-2345-136-1235-1345-1246 abturned 1-12-2345-136-1235-1345-15-145
@shortform_word        aboveboard             1-12-1236-12-135-345-145 abvboard 1-12-1236-12-135-1-1235-145
@shortform_word        aboveground            1-12-1236-1245-1235-46-145 abvground 1-12-1236-1245-1235-135-136-1345-145
@shortform_word        abovementioned         1-12-1236-134-26-56-1345-1246 abvmentioned 1-12-1236-134-15-1345-2345-24-135-1345-15-145
@shortform_indicator   accordingly            1-14-123-13456 acly Acly ACLY
@shortform_word        aforesaid              1-123456-15-234-145 aforesd 1-124-135-1235-15-234-145
@shortform_indicator   afterbattle            1-124-12-1-2345-2345-123-15 afbattle Afbattle AFBATTLE
@shortform_word        afterbirth             1-124-12-24-1235-1456 afbirth 1-124-12-24-1235-2345-125
@shortform_word        afterbreakfast         1-124-12-1235-2-13-124-1-34 afbreakfast 1-124-12-1235-15-1-13-124-1-234-2345
@shortform_indicator   afterburn              1-124-12-136-1235-1345 afburn Afburn AFBURN
@shortform_word        afterburned            1-124-12-136-1235-1345-1246 afburned 1-124-12-136-1235-1345-15-145
@shortform_word        afterburner            1-124-12-136-1235-1345-12456 afburner 1-124-12-136-1235-1345-15-1235
@shortform_word        afterburning           1-124-12-136-1235-1345-346 afburning 1-124-12-136-1235-1345-24-1345-1245
@shortform_word        aftercare              1-124-14-345-15 afcare 1-124-14-1-1235-15
@shortform_indicator   afterclap              1-124-14-123-1-1234 afclap Afclap AFCLAP
@shortform_word        aftercoffee            1-124-14-12356-124-15-15 afcoffee 1-124-14-135-124-124-15-15
@shortform_indicator   afterdamp              1-124-145-1-134-1234 afdamp Afdamp AFDAMP
@shortform_word        afterdark              1-124-145-345-13 afdark 1-124-145-1-1235-13
@shortform_indicator   afterdeck              1-124-145-15-14-13 afdeck Afdeck AFDECK
@shortform_word        afterdinner            1-124-145-35-1345-12456 afdinner 1-124-145-24-1345-1345-15-1235
@shortform_word        afterflow              1-124-124-123-246 afflow 1-124-124-123-135-2456
@shortform_indicator   aftergame              1-124-1245-1-134-15 afgame Afgame AFGAME
@shortform_word        afterglow              1-124-1245-123-246 afglow 1-124-1245-123-135-2456
@shortform_word        afterguard             1-124-1245-136-345-145 afguard 1-124-1245-136-1-1235-145
@shortform_word        afterhatch             1-124-125-1-2345-16 afhatch 1-124-125-1-2345-14-125
@shortform_word        afterhatches           1-124-125-1-2345-16-15-234 afhatches 1-124-125-1-2345-14-125-15-234
@shortform_word        afterhour              1-124-125-1256-1235 afhour 1-124-125-135-136-1235
@shortform_indicator   afterlife              1-124-123-24-124-15 aflife Aflife AFLIFE
@shortform_word        afterlight             1-124-123-24-126-2345 aflight 1-124-123-24-1245-125-2345
@shortform_indicator   afterlives             1-124-123-24-1236-15-234 aflives Aflives AFLIVES
@shortform_word        afterlunch             1-124-123-136-1345-16 aflunch 1-124-123-136-1345-14-125
@shortform_word        afterlunches           1-124-123-136-1345-16-15-234 aflunches 1-124-123-136-1345-14-125-15-234
@shortform_word        aftermarket            1-124-134-345-13-15-2345 afmarket 1-124-134-1-1235-13-15-2345
@shortform_word        aftermatch             1-124-134-1-2345-16 afmatch 1-124-134-1-2345-14-125
@shortform_word        aftermatches           1-124-134-1-2345-16-15-234 afmatches 1-124-134-1-2345-14-125-15-234
@shortform_word        aftermath              1-124-134-1-1456 afmath 1-124-134-1-2345-125
@shortform_word        aftermeeting           1-124-134-15-15-2345-346 afmeeting 1-124-134-15-15-2345-24-1345-1245
@shortform_word        aftermidday            1-124-134-24-145-5-145 afmidday 1-124-134-24-145-145-1-13456
@shortform_word        aftermidnight          1-124-134-24-145-1345-24-126-2345 afmidnight 1-124-134-24-145-1345-24-1245-125-2345
@shortform_word        aftermost              1-124-134-135-34 afmost 1-124-134-135-234-2345
@shortform_indicator   afternoontea           1-124-1345-2345-15-1 afntea Afntea AFNTEA
@shortform_word        afterpain              1-124-1234-1-35 afpain 1-124-1234-1-24-1345
@shortform_word        afterparties           1-124-5-1234-24-15-234 afparties 1-124-1234-1-1235-2345-24-15-234
@shortform_word        afterparty             1-124-5-1234-13456 afparty 1-124-1234-1-1235-2345-13456
@shortform_indicator   afterpiece             1-124-1234-24-15-14-15 afpiece Afpiece AFPIECE
@shortform_indicator   afterplay              1-124-1234-123-1-13456 afplay Afplay AFPLAY
@shortform_indicator   aftersale              1-124-234-1-123-15 afsale Afsale AFSALE
@shortform_word        afterschool            1-124-234-16-135-135-123 afschool 1-124-234-14-125-135-135-123
@shortform_word        aftersensation         1-124-234-26-234-1-56-1345 afsensation 1-124-234-15-1345-234-1-2345-24-135-1345
@shortform_word        aftershave             1-124-146-1-1236-15 afshave 1-124-234-125-1-1236-15
@shortform_word        aftershock             1-124-146-135-14-13 afshock 1-124-234-125-135-14-13
@shortform_word        aftershow              1-124-146-246 afshow 1-124-234-125-135-2456
@shortform_word        aftershower            1-124-146-246-12456 afshower 1-124-234-125-135-2456-15-1235
@shortform_word        aftersupper            1-124-234-136-1234-1234-12456 afsupper 1-124-234-136-1234-1234-15-1235
@shortform_word        aftertaste             1-124-2345-1-34-15 aftaste 1-124-2345-1-234-2345-15
@shortform_indicator   aftertax               1-124-2345-1-1346 aftax Aftax AFTAX
@shortform_indicator   aftertaxes             1-124-2345-1-1346-15-234 aftaxes Aftaxes AFTAXES
@shortform_indicator   aftertea               1-124-2345-15-1 aftea Aftea AFTEA
@shortform_word        aftertheatre           1-124-2346-1-2345-1235-15 aftheatre 1-124-2345-125-15-1-2345-1235-15
@shortform_word        afterthought           1-124-1456-5-1256 afthoneu 1-124-2345-125-135-1345-15-136
@shortform_word        aftertime              1-124-5-2345 aftime 1-124-2345-24-134-15
@shortform_word        aftertreatment         1-124-2345-1235-2-2345-56-2345 aftreatment 1-124-2345-1235-15-1-2345-134-15-1345-2345
@shortform_word        afterword              1-124-45-2456 afword 1-124-2456-135-1235-145
@shortform_word        afterwork              1-124-5-2456 afwork 1-124-2456-135-1235-13
@shortform_word        afterworld             1-124-456-2456 afworld 1-124-2456-135-1235-123-145
@shortform_word        apperceive             1-1234-1234-12456-14-1236 appercv 1-1234-1234-15-1235-14-1236
@shortform_word        apperceived            1-1234-1234-12456-14-1236-145 appercvd 1-1234-1234-15-1235-14-1236-145
@shortform_word        apperceiver            1-1234-1234-12456-14-1236-1235 appercvr 1-1234-1234-15-1235-14-1236-1235
@shortform_word        apperceiving           1-1234-1234-12456-14-1236-1245 appercvg 1-1234-1234-15-1235-14-1236-1245
@shortform_word        archdeceiver           345-16-145-14-1236-1235 archdcvr 1-1235-14-125-145-14-1236-1235
@shortform_word        beforehand             23-124-125-12346 befhand 12-15-124-125-1-1345-145
@shortform_word        befriend               23-124-1235 befr 12-15-124-1235
@shortform_word        behindhand             23-125-125-12346 behhand 12-15-125-125-1-1345-145
@shortform_word        belittle               23-123-123 bell 12-15-123-123
@shortform_word        belittled              23-123-123-145 belld 12-15-123-123-145
@shortform_word        belittlement           23-123-123-56-2345 bellment 12-15-123-123-134-15-1345-2345
@shortform_word        belittler              23-123-123-1235 bellr 12-15-123-123-1235
@shortform_word        belowdeck              23-123-145-15-14-13 beldeck 12-15-123-145-15-14-13
@shortform_word        belowground            23-123-1245-1235-46-145 belground 12-15-123-1245-1235-135-136-1345-145
@shortform_word        belowmentioned         23-123-134-26-56-1345-1246 belmentioned 12-15-123-134-15-1345-2345-24-135-1345-15-145
@shortform_word        beneathdeck            23-1345-145-15-14-13 bendeck 12-15-1345-145-15-14-13
@shortform_word        beneathground          23-1345-1245-1235-46-145 benground 12-15-1345-1245-1235-135-136-1345-145
@shortform_word        betweendeck            23-2345-145-15-14-13 betdeck 12-15-2345-145-15-14-13
@shortform_word        betweentime            23-2345-5-2345 bettime 12-15-2345-2345-24-134-15
@shortform_word        betweenwhile           23-2345-156-24-123-15 betwhile 12-15-2345-2456-125-24-123-15
@shortform_word        blindfish              12-123-124-24-146 blfish 12-123-124-24-234-125
@shortform_word        blindfishes            12-123-124-24-146-15-234 blfishes 12-123-124-24-234-125-15-234
@shortform_indicator   blindfold              12-123-124-135-123-145 blfold Blfold BLFOLD
@shortform_word        blindfolded            12-123-124-135-123-145-1246 blfolded 12-123-124-135-123-145-15-145
@shortform_word        blindfolder            12-123-124-135-123-145-12456 blfolder 12-123-124-135-123-145-15-1235
@shortform_word        blindfolding           12-123-124-135-123-145-346 blfolding 12-123-124-135-123-145-24-1345-1245
@shortform_indicator   blindly                12-123-123-13456 blly Blly BLLY
@shortform_indicator   blindman               12-123-134-1-1345 blman Blman BLMAN
@shortform_word        blindmen               12-123-134-26 blmen 12-123-134-15-1345
@shortform_word        blindness              12-123-56-234 blness 12-123-1345-15-234-234
@shortform_word        blindnesses            12-123-56-234-15-234 blnesses 12-123-1345-15-234-234-15-234
@shortform_indicator   blindside              12-123-234-24-145-15 blside Blside BLSIDE
@shortform_word        blindsided             12-123-234-24-145-1246 blsided 12-123-234-24-145-15-145
@shortform_word        blindsider             12-123-234-24-145-12456 blsider 12-123-234-24-145-15-1235
@shortform_word        blindsiding            12-123-234-24-145-346 blsiding 12-123-234-24-145-24-1345-1245
@shortform_word        blindsight             12-123-234-24-126-2345 blsight 12-123-234-24-1245-125-2345
@shortform_word        blindstories           12-123-34-135-1235-24-15-234 blstories 12-123-234-2345-135-1235-24-15-234
@shortform_word        blindstory             12-123-34-135-1235-13456 blstory 12-123-234-2345-135-1235-13456
@shortform_indicator   blindworm              12-123-2456-135-1235-134 blworm Blworm BLWORM
@shortform_indicator   bloodletter            12-123-135-135-145-123-1235 bloodlr Bloodlr BLOODLR
@shortform_indicator   boyfriend              12-135-13456-124-1235 boyfr Boyfr BOYFR
@shortform_indicator   brailled               12-1235-123-145 brld Brld BRLD
@shortform_indicator   brailler               12-1235-123-1235 brlr Brlr BRLR
@shortform_word        braillewriter          12-1235-123-2456-1235-24-2345-12456 brlwriter 12-1235-123-2456-1235-24-2345-15-1235
@shortform_word        braillewriting         12-1235-123-2456-1235-24-2345-346 brlwriting 12-1235-123-2456-1235-24-2345-24-1345-1245
@shortform_indicator   brailley               12-1235-123-13456 brly Brly BRLY
@shortform_word        brainchildren          12-1235-1-35-16-1345 brainchn 12-1235-1-24-1345-14-125-1345
@shortform_word        chainletter            16-1-35-123-1235 chainlr 14-125-1-24-1345-123-1235
@shortform_word        children'swear         16-1345-3-234-2456-15-345 chn'swear 14-125-1345-3-234-2456-15-1-1235
@shortform_indicator   colorblind             14-135-123-135-1235-12-123 colorbl Colorbl COLORBL
@shortform_word        colorblindness         14-135-123-135-1235-12-123-56-234 colorblness 14-135-123-135-1235-12-123-1345-15-234-234
@shortform_word        colorblindnesses       14-135-123-135-1235-12-123-56-234-15-234 colorblnesses 14-135-123-135-1235-12-123-1345-15-234-234-15-234
@shortform_word        colourblind            14-135-123-1256-1235-12-123 colourbl 14-135-123-135-136-1235-12-123
@shortform_word        colourblindness        14-135-123-1256-1235-12-123-56-234 colourblness 14-135-123-135-136-1235-12-123-1345-15-234-234
@shortform_word        colourblindnesses      14-135-123-1256-1235-12-123-56-234-15-234 colourblnesses 14-135-123-135-136-1235-12-123-1345-15-234-234-15-234
@shortform_word        conceived              25-14-1236-145 concvd 14-135-1345-14-1236-145
@shortform_word        conceiver              25-14-1236-1235 concvr 14-135-1345-14-1236-1235
@shortform_indicator   could've               14-145-3-1236-15 cd've Cd've CD'VE
@shortform_indicator   coulda                 14-145-1 cda Cda CDA
@shortform_word        couldest               14-145-15-34 cdest 14-145-15-234-2345
@shortform_indicator   couldn't               14-145-1345-3-2345 cdn't Cdn't CDN'T
@shortform_indicator   couldn't've            14-145-1345-3-2345-3-1236-15 cdn't've Cdn't've CDN'T'VE
@shortform_word        couldst                14-145-34 cdst 14-145-234-2345
@shortform_word        deafblind              145-2-124-12-123 deafbl 145-15-1-124-12-123
@shortform_word        deafblindness          145-2-124-12-123-56-234 deafblness 145-15-1-124-12-123-1345-15-234-234
@shortform_word        deafblindnesses        145-2-124-12-123-56-234-15-234 deafblnesses 145-15-1-124-12-123-1345-15-234-234-15-234
@shortform_indicator   deceived               145-14-1236-145 dcvd Dcvd DCVD
@shortform_indicator   deceiver               145-14-1236-1235 dcvr Dcvr DCVR
@shortform_indicator   declared               145-14-123-145 dcld Dcld DCLD
@shortform_indicator   declarer               145-14-123-1235 dclr Dclr DCLR
@shortform_indicator   defriend               145-15-124-1235 defr Defr DEFR
@shortform_indicator   doityourselfer         145-135-24-2345-13456-135-136-1235-234-15-123-124-15-1235 doityourselfer Doityourselfer DOITYOURSELFER
@shortform_word        doublequick            145-1256-12-123-15-12345-13 doubleqk 145-135-136-12-123-15-12345-13
@shortform_word        eastabout              15-1-34-1-12 eastab 15-1-234-2345-1-12
@shortform_indicator   feelgood               124-15-15-123-1245-145 feelgd Feelgd FEELGD
@shortform_word        feetfirst              124-15-15-2345-124-34 feetfst 124-15-15-2345-124-234-2345
@shortform_word        firstaid               124-34-1-24-145 fstaid 124-234-2345-1-24-145
@shortform_word        firstaider             124-34-1-24-145-12456 fstaider 124-234-2345-1-24-145-15-1235
@shortform_word        firstborn              124-34-12-135-1235-1345 fstborn 124-234-2345-12-135-1235-1345
@shortform_word        firstclass             124-34-14-123-1-234-234 fstclass 124-234-2345-14-123-1-234-234
@shortform_word        firstclasses           124-34-14-123-1-234-234-15-234 fstclasses 124-234-2345-14-123-1-234-234-15-234
@shortform_word        firstday               124-34-5-145 fstday 124-234-2345-145-1-13456
@shortform_word        firstdayer             124-34-5-145-12456 fstdayer 124-234-2345-145-1-13456-15-1235
@shortform_word        firstfruit             124-34-124-1235-136-24-2345 fstfruit 124-234-2345-124-1235-136-24-2345
@shortform_word        firstfruiting          124-34-124-1235-136-24-2345-346 fstfruiting 124-234-2345-124-1235-136-24-2345-24-1345-1245
@shortform_word        firstgeneration        124-34-1245-26-12456-1-56-1345 fstgeneration 124-234-2345-1245-15-1345-15-1235-1-2345-24-135-1345
@shortform_word        firsthand              124-34-125-12346 fsthand 124-234-2345-125-1-1345-145
@shortform_word        firsthanded            124-34-125-12346-1246 fsthanded 124-234-2345-125-1-1345-145-15-145
@shortform_word        firstling              124-34-123-346 fstling 124-234-2345-123-24-1345-1245
@shortform_word        firstly                124-34-123-13456 fstly 124-234-2345-123-13456
@shortform_word        firstness              124-34-56-234 fstness 124-234-2345-1345-15-234-234
@shortform_word        firstnight             124-34-1345-24-126-2345 fstnight 124-234-2345-1345-24-1245-125-2345
@shortform_word        firstnighter           124-34-1345-24-126-2345-12456 fstnighter 124-234-2345-1345-24-1245-125-2345-15-1235
@shortform_word        firstrate              124-34-1235-1-2345-15 fstrate 124-234-2345-1235-1-2345-15
@shortform_word        firstrated             124-34-1235-1-2345-1246 fstrated 124-234-2345-1235-1-2345-15-145
@shortform_word        firstrating            124-34-1235-1-2345-346 fstrating 124-234-2345-1235-1-2345-24-1345-1245
@shortform_word        firststring            124-34-34-1235-346 fststring 124-234-2345-234-2345-1235-24-1345-1245
@shortform_word        forasmuch              123456-1-234-134-16 forasmch 124-135-1235-1-234-134-14-125
@shortform_word        foresaid               123456-15-234-145 foresd 124-135-1235-15-234-145
@shortform_word        fosterchildren         124-135-34-12456-16-1345 fosterchn 124-135-234-2345-15-1235-14-125-1345
@shortform_word        friendless             124-1235-46-234 frless 124-1235-123-15-234-234
@shortform_word        friendlessness         124-1235-46-234-56-234 frlessness 124-1235-123-15-234-234-1345-15-234-234
@shortform_word        friendlessnesses       124-1235-46-234-56-234-15-234 frlessnesses 124-1235-123-15-234-234-1345-15-234-234-15-234
@shortform_word        friendlier             124-1235-123-24-12456 frlier 124-1235-123-24-15-1235
@shortform_indicator   friendlies             124-1235-123-24-15-234 frlies Frlies FRLIES
@shortform_word        friendliest            124-1235-123-24-15-34 frliest 124-1235-123-24-15-234-2345
@shortform_word        friendliness           124-1235-123-24-56-234 frliness 124-1235-123-24-1345-15-234-234
@shortform_word        friendlinesses         124-1235-123-24-56-234-15-234 frlinesses 124-1235-123-24-1345-15-234-234-15-234
@shortform_indicator   friendly               124-1235-123-13456 frly Frly FRLY
@shortform_word        friendship             124-1235-146-24-1234 frship 124-1235-234-125-24-1234
@shortform_indicator   gadabout               1245-1-145-1-12 gadab Gadab GADAB
@shortform_word        gainsaid               1245-1-35-234-145 gainsd 1245-1-24-1345-234-145
@shortform_indicator   galfriend              1245-1-123-124-1235 galfr Galfr GALFR
@shortform_word        gentlemanfriend        1245-26-2345-123-15-134-1-1345-124-1235 gentlemanfr 1245-15-1345-2345-123-15-134-1-1345-124-1235
@shortform_word        gentlemenfriends       1245-26-2345-123-15-134-26-124-1235-234 gentlemenfrs 1245-15-1345-2345-123-15-134-15-1345-124-1235-234
@shortform_indicator   girlfriend             1245-24-1235-123-124-1235 girlfr Girlfr GIRLFR
@shortform_word        godchildren            1245-135-145-16-1345 godchn 1245-135-145-14-125-1345
@shortform_indicator   goodafternoon          1245-145-1-124-1345 gdafn Gdafn GDAFN
@shortform_indicator   goodby                 1245-145-12-13456 gdby Gdby GDBY
@shortform_indicator   goodbye                1245-145-12-13456-15 gdbye Gdbye GDBYE
@shortform_word        goodbyeing             1245-145-12-13456-15-346 gdbyeing 1245-145-12-13456-15-24-1345-1245
@shortform_word        goodbying              1245-145-12-13456-346 gdbying 1245-145-12-13456-24-1345-1245
@shortform_word        goodday                1245-145-5-145 gdday 1245-145-145-1-13456
@shortform_word        gooder                 1245-145-12456 gder 1245-145-15-1235
@shortform_word        goodest                1245-145-15-34 gdest 1245-145-15-234-2345
@shortform_word        goodevening            1245-145-15-1236-26-346 gdevening 1245-145-15-1236-15-1345-24-1345-1245
@shortform_word        goodfellow             1245-145-124-15-123-123-246 gdfellow 1245-145-124-15-123-123-135-2456
@shortform_word        goodfellowship         1245-145-124-15-123-123-246-146-24-1234 gdfellowship 1245-145-124-15-123-123-135-2456-234-125-24-1234
@shortform_word        goodhearted            1245-145-125-15-345-2345-1246 gdhearted 1245-145-125-15-1-1235-2345-15-145
@shortform_word        goodheartedly          1245-145-125-15-345-2345-1246-123-13456 gdheartedly 1245-145-125-15-1-1235-2345-15-145-123-13456
@shortform_word        goodheartedness        1245-145-125-15-345-2345-1246-56-234 gdheartedness 1245-145-125-15-1-1235-2345-15-145-1345-15-234-234
@shortform_indicator   goodhumor              1245-145-125-136-134-135-1235 gdhumor Gdhumor GDHUMOR
@shortform_word        goodhumored            1245-145-125-136-134-135-1235-1246 gdhumored 1245-145-125-136-134-135-1235-15-145
@shortform_word        goodhumoredly          1245-145-125-136-134-135-1235-1246-123-13456 gdhumoredly 1245-145-125-136-134-135-1235-15-145-123-13456
@shortform_word        goodhumoredness        1245-145-125-136-134-135-1235-1246-56-234 gdhumoredness 1245-145-125-136-134-135-1235-15-145-1345-15-234-234
@shortform_word        goodhumorednesses      1245-145-125-136-134-135-1235-1246-56-234-15-234 gdhumorednesses 1245-145-125-136-134-135-1235-15-145-1345-15-234-234-15-234
@shortform_word        goodhumour             1245-145-125-136-134-1256-1235 gdhumour 1245-145-125-136-134-135-136-1235
@shortform_word        goodhumoured           1245-145-125-136-134-1256-1235-1246 gdhumoured 1245-145-125-136-134-135-136-1235-15-145
@shortform_word        goodhumouredly         1245-145-125-136-134-1256-1235-1246-123-13456 gdhumouredly 1245-145-125-136-134-135-136-1235-15-145-123-13456
@shortform_word        goodhumouredness       1245-145-125-136-134-1256-1235-1246-56-234 gdhumouredness 1245-145-125-136-134-135-136-1235-15-145-1345-15-234-234
@shortform_word        goodhumourednesses     1245-145-125-136-134-1256-1235-1246-56-234-15-234 gdhumourednesses 1245-145-125-136-134-135-136-1235-15-145-1345-15-234-234-15-234
@shortform_indicator   goodie                 1245-145-24-15 gdie Gdie GDIE
@shortform_word        goodish                1245-145-24-146 gdish 1245-145-24-234-125
@shortform_word        goodlier               1245-145-123-24-12456 gdlier 1245-145-123-24-15-1235
@shortform_word        goodliest              1245-145-123-24-15-34 gdliest 1245-145-123-24-15-234-2345
@shortform_word        goodliness             1245-145-123-24-56-234 gdliness 1245-145-123-24-1345-15-234-234
@shortform_indicator   goodlook               1245-145-123-135-135-13 gdlook Gdlook GDLOOK
@shortform_word        goodlooker             1245-145-123-135-135-13-12456 gdlooker 1245-145-123-135-135-13-15-1235
@shortform_word        goodlooking            1245-145-123-135-135-13-346 gdlooking 1245-145-123-135-135-13-24-1345-1245
@shortform_indicator   goodly                 1245-145-123-13456 gdly Gdly GDLY
@shortform_indicator   goodman                1245-145-134-1-1345 gdman Gdman GDMAN
@shortform_word        goodmen                1245-145-134-26 gdmen 1245-145-134-15-1345
@shortform_word        goodmorning            1245-145-134-135-1235-1345-346 gdmorning 1245-145-134-135-1235-1345-24-1345-1245
@shortform_indicator   goodnature             1245-145-1345-1-2345-136-1235-15 gdnature Gdnature GDNATURE
@shortform_word        goodnatured            1245-145-1345-1-2345-136-1235-1246 gdnatured 1245-145-1345-1-2345-136-1235-15-145
@shortform_word        goodnaturedly          1245-145-1345-1-2345-136-1235-1246-123-13456 gdnaturedly 1245-145-1345-1-2345-136-1235-15-145-123-13456
@shortform_word        goodnaturedness        1245-145-1345-1-2345-136-1235-1246-56-234 gdnaturedness 1245-145-1345-1-2345-136-1235-15-145-1345-15-234-234
@shortform_word        goodness               1245-145-56-234 gdness 1245-145-1345-15-234-234
@shortform_word        goodnesses             1245-145-56-234-15-234 gdnesses 1245-145-1345-15-234-234-15-234
@shortform_word        goodnight              1245-145-1345-24-126-2345 gdnight 1245-145-1345-24-1245-125-2345
@shortform_indicator   goodsize               1245-145-234-24-1356-15 gdsize Gdsize GDSIZE
@shortform_word        goodsized              1245-145-234-24-1356-1246 gdsized 1245-145-234-24-1356-15-145
@shortform_word        goodtempered           1245-145-2345-15-134-1234-12456-1246 gdtempered 1245-145-2345-15-134-1234-15-1235-15-145
@shortform_word        goodtemperedly         1245-145-2345-15-134-1234-12456-1246-123-13456 gdtemperedly 1245-145-2345-15-134-1234-15-1235-15-145-123-13456
@shortform_word        goodtime               1245-145-5-2345 gdtime 1245-145-2345-24-134-15
@shortform_indicator   goodun                 1245-145-136-1345 gdun Gdun GDUN
@shortform_indicator   goodwife               1245-145-2456-24-124-15 gdwife Gdwife GDWIFE
@shortform_indicator   goodwill               1245-145-2456-24-123-123 gdwill Gdwill GDWILL
@shortform_word        goodwilled             1245-145-2456-24-123-123-1246 gdwilled 1245-145-2456-24-123-123-15-145
@shortform_indicator   goodwives              1245-145-2456-24-1236-15-234 gdwives Gdwives GDWIVES
@shortform_indicator   goody                  1245-145-13456 gdy Gdy GDY
@shortform_word        goodyear               1245-145-13456-15-345 gdyear 1245-145-13456-15-1-1235
@shortform_word        grandchildren          1245-1235-12346-16-1345 grandchn 1245-1235-1-1345-145-14-125-1345
@shortform_indicator   greataunt              1245-1235-2345-1-136-1345-2345 grtaunt Grtaunt GRTAUNT
@shortform_word        greatbatch             1245-1235-2345-12-1-2345-16 grtbatch 1245-1235-2345-12-1-2345-14-125
@shortform_indicator   greatcircle            1245-1235-2345-14-24-1235-14-123-15 grtcircle Grtcircle GRTCIRCLE
@shortform_indicator   greatcoat              1245-1235-2345-14-135-1-2345 grtcoat Grtcoat GRTCOAT
@shortform_word        greaten                1245-1235-2345-26 grten 1245-1235-2345-15-1345
@shortform_word        greatened              1245-1235-2345-26-1246 grtened 1245-1235-2345-15-1345-15-145
@shortform_word        greatener              1245-1235-2345-26-12456 grtener 1245-1235-2345-15-1345-15-1235
@shortform_word        greatening             1245-1235-2345-26-346 grtening 1245-1235-2345-15-1345-24-1345-1245
@shortform_word        greater                1245-1235-2345-12456 grter 1245-1235-2345-15-1235
@shortform_word        greatest               1245-1235-2345-15-34 grtest 1245-1235-2345-15-234-2345
@shortform_word        greatgrandaunt         1245-1235-2345-1245-1235-12346-1-136-1345-2345 grtgrandaunt 1245-1235-2345-1245-1235-1-1345-145-1-136-1345-2345
@shortform_word        greatgrandchild        1245-1235-2345-1245-1235-12346-16-24-123-145 grtgrandchild 1245-1235-2345-1245-1235-1-1345-145-14-125-24-123-145
@shortform_word        greatgrandchildren     1245-1235-2345-1245-1235-12346-16-1345 grtgrandchn 1245-1235-2345-1245-1235-1-1345-145-14-125-1345
@shortform_word        greatgranddad          1245-1235-2345-1245-1235-12346-145-1-145 grtgranddad 1245-1235-2345-1245-1235-1-1345-145-145-1-145
@shortform_word        greatgranddaughter     1245-1235-2345-1245-1235-12346-145-1-136-126-2345-12456 grtgranddaughter 1245-1235-2345-1245-1235-1-1345-145-145-1-136-1245-125-2345-15-1235
@shortform_word        greatgrandfather       1245-1235-2345-1245-1235-12346-5-124 grtgrandfather 1245-1235-2345-1245-1235-1-1345-145-124-1-2345-125-15-1235
@shortform_word        greatgrandfatherhood   1245-1235-2345-1245-1235-12346-5-124-125-135-135-145 grtgrandfatherhood 1245-1235-2345-1245-1235-1-1345-145-124-1-2345-125-15-1235-125-135-135-145
@shortform_word        greatgrandma           1245-1235-2345-1245-1235-12346-134-1 grtgrandma 1245-1235-2345-1245-1235-1-1345-145-134-1
@shortform_word        greatgrandmother       1245-1235-2345-1245-1235-12346-5-134 grtgrandmother 1245-1235-2345-1245-1235-1-1345-145-134-135-2345-125-15-1235
@shortform_word        greatgrandmotherhood   1245-1235-2345-1245-1235-12346-5-134-125-135-135-145 grtgrandmotherhood 1245-1235-2345-1245-1235-1-1345-145-134-135-2345-125-15-1235-125-135-135-145
@shortform_word        greatgrandnephew       1245-1235-2345-1245-1235-12346-1345-15-1234-125-15-2456 grtgrandnephew 1245-1235-2345-1245-1235-1-1345-145-1345-15-1234-125-15-2456
@shortform_word        greatgrandniece        1245-1235-2345-1245-1235-12346-1345-24-15-14-15 grtgrandniece 1245-1235-2345-1245-1235-1-1345-145-1345-24-15-14-15
@shortform_word        greatgrandpa           1245-1235-2345-1245-1235-12346-1234-1 grtgrandpa 1245-1235-2345-1245-1235-1-1345-145-1234-1
@shortform_word        greatgrandparent       1245-1235-2345-1245-1235-12346-1234-345-26-2345 grtgrandparent 1245-1235-2345-1245-1235-1-1345-145-1234-1-1235-15-1345-2345
@shortform_word        greatgrandparenthood   1245-1235-2345-1245-1235-12346-1234-345-26-2345-125-135-135-145 grtgrandparenthood 1245-1235-2345-1245-1235-1-1345-145-1234-1-1235-15-1345-2345-125-135-135-145
@shortform_word        greatgrandson          1245-1235-2345-1245-1235-12346-234-135-1345 grtgrandson 1245-1235-2345-1245-1235-1-1345-145-234-135-1345
@shortform_word        greatgranduncle        1245-1235-2345-1245-1235-12346-136-1345-14-123-15 grtgranduncle 1245-1235-2345-1245-1235-1-1345-145-136-1345-14-123-15
@shortform_word        greathearted           1245-1235-2345-125-15-345-2345-1246 grthearted 1245-1235-2345-125-15-1-1235-2345-15-145
@shortform_word        greatheartedly         1245-1235-2345-125-15-345-2345-1246-123-13456 grtheartedly 1245-1235-2345-125-15-1-1235-2345-15-145-123-13456
@shortform_word        greatheartedness       1245-1235-2345-125-15-345-2345-1246-56-234 grtheartedness 1245-1235-2345-125-15-1-1235-2345-15-145-1345-15-234-234
@shortform_word        greatheartednesses     1245-1235-2345-125-15-345-2345-1246-56-234-15-234 grtheartednesses 1245-1235-2345-125-15-1-1235-2345-15-145-1345-15-234-234-15-234
@shortform_indicator   greatly                1245-1235-2345-123-13456 grtly Grtly GRTLY
@shortform_indicator   greatnephew            1245-1235-2345-1345-15-1234-125-15-2456 grtnephew Grtnephew GRTNEPHEW
@shortform_word        greatness              1245-1235-2345-56-234 grtness 1245-1235-2345-1345-15-234-234
@shortform_word        greatnesses            1245-1235-2345-56-234-15-234 grtnesses 1245-1235-2345-1345-15-234-234-15-234
@shortform_indicator   greatniece             1245-1235-2345-1345-24-15-14-15 grtniece Grtniece GRTNIECE
@shortform_word        greatsword             1245-1235-2345-234-45-2456 grtsword 1245-1235-2345-234-2456-135-1235-145
@shortform_indicator   greatuncle             1245-1235-2345-136-1345-14-123-15 grtuncle Grtuncle GRTUNCLE
@shortform_indicator   guyfriend              1245-136-13456-124-1235 guyfr Guyfr GUYFR
@shortform_indicator   hateletter             125-1-2345-15-123-1235 hatelr Hatelr HATELR
@shortform_word        headfirst              125-2-145-124-34 headfst 125-15-1-145-124-234-2345
@shortform_word        hereabout              5-125-1-12 hereab 125-15-1235-15-1-12
@shortform_word        hereafter              5-125-1-124 hereaf 125-15-1235-15-1-124
@shortform_word        hereagain              5-125-1-1245 hereag 125-15-1235-15-1-1245
@shortform_word        hereagainst            5-125-1-1245-34 hereagst 125-15-1235-15-1-1245-234-2345
@shortform_word        hereinabove            5-125-35-1-12-1236 hereinabv 125-15-1235-15-24-1345-1-12-1236
@shortform_word        hereinafter            5-125-35-1-124 hereinaf 125-15-1235-15-24-1345-1-124
@shortform_word        hereinagain            5-125-35-1-1245 hereinag 125-15-1235-15-24-1345-1-1245
@shortform_word        highlypaid             125-24-126-123-13456-1234-145 highlypd 125-24-1245-125-123-13456-1234-145
@shortform_indicator   himbo                  125-134-12-135 hmbo Hmbo HMBO
@shortform_indicator   himboes                125-134-12-135-15-234 hmboes Hmboes HMBOES
@shortform_indicator   illpaid                24-123-123-1234-145 illpd Illpd ILLPD
@shortform_indicator   immediately            24-134-134-123-13456 immly Immly IMMLY
@shortform_word        immediateness          24-134-134-56-234 immness 24-134-134-1345-15-234-234
@shortform_word        inasmuch               35-1-234-134-16 inasmch 24-1345-1-234-134-14-125
@shortform_word        insomuch               35-234-135-134-16 insomch 24-1345-234-135-134-14-125
@shortform_indicator   knockabout             13-1345-135-14-13-1-12 knockab Knockab KNOCKAB
@shortform_indicator   ladyfriend             123-1-145-13456-124-1235 ladyfr Ladyfr LADYFR
@shortform_indicator   layabout               123-1-13456-1-12 layab Layab LAYAB
@shortform_indicator   letterbodies           123-1235-12-135-145-24-15-234 lrbodies Lrbodies LRBODIES
@shortform_indicator   letterbody             123-1235-12-135-145-13456 lrbody Lrbody LRBODY
@shortform_indicator   letterbomb             123-1235-12-135-134-12 lrbomb Lrbomb LRBOMB
@shortform_word        letterbombed           123-1235-12-135-134-12-1246 lrbombed 123-1235-12-135-134-12-15-145
@shortform_word        letterbomber           123-1235-12-135-134-12-12456 lrbomber 123-1235-12-135-134-12-15-1235
@shortform_word        letterbombing          123-1235-12-135-134-12-346 lrbombing 123-1235-12-135-134-12-24-1345-1245
@shortform_indicator   letterbox              123-1235-12-135-1346 lrbox Lrbox LRBOX
@shortform_word        letterboxed            123-1235-12-135-1346-1246 lrboxed 123-1235-12-135-1346-15-145
@shortform_word        letterboxer            123-1235-12-135-1346-12456 lrboxer 123-1235-12-135-1346-15-1235
@shortform_indicator   letterboxes            123-1235-12-135-1346-15-234 lrboxes Lrboxes LRBOXES
@shortform_word        letterboxing           123-1235-12-135-1346-346 lrboxing 123-1235-12-135-1346-24-1345-1245
@shortform_word        lettered               123-1235-1246 lred 123-1235-15-145
@shortform_word        letterer               123-1235-12456 lrer 123-1235-15-1235
@shortform_word        letterform             123-1235-123456-134 lrform 123-1235-124-135-1235-134
@shortform_word        letterhead             123-1235-125-2-145 lrhead 123-1235-125-15-1-145
@shortform_word        letterheading          123-1235-125-2-145-346 lrheading 123-1235-125-15-1-145-24-1345-1245
@shortform_word        lettering              123-1235-346 lring 123-1235-24-1345-1245
@shortform_indicator   letterman              123-1235-134-1-1345 lrman Lrman LRMAN
@shortform_word        lettermen              123-1235-134-26 lrmen 123-1235-134-15-1345
@shortform_word        letteropener           123-1235-135-1234-26-12456 lropener 123-1235-135-1234-15-1345-15-1235
@shortform_word        letterperfect          123-1235-1234-12456-124-15-14-2345 lrperfect 123-1235-1234-15-1235-124-15-14-2345
@shortform_indicator   letterpress            123-1235-1234-1235-15-234-234 lrpress Lrpress LRPRESS
@shortform_word        letterpressed          123-1235-1234-1235-15-234-234-1246 lrpressed 123-1235-1234-1235-15-234-234-15-145
@shortform_indicator   letterpresses          123-1235-1234-1235-15-234-234-15-234 lrpresses Lrpresses LRPRESSES
@shortform_word        letterpressing         123-1235-1234-1235-15-234-234-346 lrpressing 123-1235-1234-1235-15-234-234-24-1345-1245
@shortform_word        letterquality          123-1235-12345-136-1-123-56-13456 lrquality 123-1235-12345-136-1-123-24-2345-13456
@shortform_indicator   letterspace            123-1235-234-1234-1-14-15 lrspace Lrspace LRSPACE
@shortform_word        letterspaced           123-1235-234-1234-1-14-1246 lrspaced 123-1235-234-1234-1-14-15-145
@shortform_word        letterspacing          123-1235-234-1234-1-14-346 lrspacing 123-1235-234-1234-1-14-24-1345-1245
@shortform_indicator   lettertext             123-1235-2345-15-1346-2345 lrtext Lrtext LRTEXT
@shortform_indicator   littled                123-123-145 lld Lld LLD
@shortform_indicator   littleneck             123-123-1345-15-14-13 llneck Llneck LLNECK
@shortform_word        littleness             123-123-56-234 llness 123-123-1345-15-234-234
@shortform_word        littlenesses           123-123-56-234-15-234 llnesses 123-123-1345-15-234-234-15-234
@shortform_indicator   littler                123-123-1235 llr Llr LLR
@shortform_word        littlest               123-123-34 llst 123-123-234-2345
@shortform_word        lovechildren           123-135-1236-15-16-1345 lovechn 123-135-1236-15-14-125-1345
@shortform_indicator   loveletter             123-135-1236-15-123-1235 lovelr Lovelr LOVELR
@shortform_word        lowlypaid              123-246-123-13456-1234-145 lowlypd 123-135-2456-123-13456-1234-145
@shortform_indicator   manfriend              134-1-1345-124-1235 manfr Manfr MANFR
@shortform_word        menfriends             134-26-124-1235-234 menfrs 134-15-1345-124-1235-234
@shortform_indicator   midafternoon           134-24-145-1-124-1345 midafn Midafn MIDAFN
@shortform_indicator   misbraille             134-24-234-12-1235-123 misbrl Misbrl MISBRL
@shortform_indicator   misbrailled            134-24-234-12-1235-123-145 misbrld Misbrld MISBRLD
@shortform_word        misperceive            134-24-234-1234-12456-14-1236 mispercv 134-24-234-1234-15-1235-14-1236
@shortform_word        misperceived           134-24-234-1234-12456-14-1236-145 mispercvd 134-24-234-1234-15-1235-14-1236-145
@shortform_word        misperceiver           134-24-234-1234-12456-14-1236-1235 mispercvr 134-24-234-1234-15-1235-14-1236-1235
@shortform_word        misperceiving          134-24-234-1234-12456-14-1236-1245 mispercvg 134-24-234-1234-15-1235-14-1236-1245
@shortform_indicator   missaid                134-24-234-234-145 missd Missd MISSD
@shortform_word        morningafter           134-135-1235-1345-346-1-124 morningaf 134-135-1235-1345-24-1345-1245-1-124
@shortform_word        muchly                 134-16-123-13456 mchly 134-14-125-123-13456
@shortform_word        muchness               134-16-56-234 mchness 134-14-125-1345-15-234-234
@shortform_word        must've                134-34-3-1236-15 mst've 134-234-2345-3-1236-15
@shortform_word        musta                  134-34-1 msta 134-234-2345-1
@shortform_word        mustard                134-34-345-145 mstard 134-234-2345-1-1235-145
@shortform_word        mustier                134-34-24-12456 mstier 134-234-2345-24-15-1235
@shortform_word        mustiest               134-34-24-15-34 mstiest 134-234-2345-24-15-234-2345
@shortform_word        mustily                134-34-24-123-13456 mstily 134-234-2345-24-123-13456
@shortform_word        mustiness              134-34-24-56-234 mstiness 134-234-2345-24-1345-15-234-234
@shortform_word        mustn't                134-34-1345-3-2345 mstn't 134-234-2345-1345-3-2345
@shortform_word        mustn't've             134-34-1345-3-2345-3-1236-15 mstn't've 134-234-2345-1345-3-2345-3-1236-15
@shortform_word        musty                  134-34-13456 msty 134-234-2345-13456
@shortform_indicator   newsletter             1345-15-2456-234-123-1235 newslr Newslr NEWSLR
@shortform_word        nonesuch               1345-5-135-234-16 nonesch 1345-135-1345-15-234-14-125
@shortform_word        nonsuch                1345-135-1345-234-16 nonsch 1345-135-1345-234-14-125
@shortform_word        northabout             1345-135-1235-1456-1-12 northab 1345-135-1235-2345-125-1-12
@shortform_word        overmuch               135-1236-12456-134-16 overmch 135-1236-15-1235-134-14-125
@shortform_word        overpaid               135-1236-12456-1234-145 overpd 135-1236-15-1235-1234-145
@shortform_word        penfriend              1234-26-124-1235 penfr 1234-15-1345-124-1235
@shortform_word        perceived              1234-12456-14-1236-145 percvd 1234-15-1235-14-1236-145
@shortform_word        perceiver              1234-12456-14-1236-1235 percvr 1234-15-1235-14-1236-1235
@shortform_word        perhapses              1234-12456-125-15-234 perhes 1234-15-1235-125-15-234
@shortform_indicator   poorlypaid             1234-135-135-1235-123-13456-1234-145 poorlypd Poorlypd POORLYPD
@shortform_word        postpaid               1234-135-34-1234-145 postpd 1234-135-234-2345-1234-145
@shortform_indicator   preceive               1234-1235-14-1236 prcv Prcv PRCV
@shortform_indicator   preceiver              1234-1235-14-1236-1235 prcvr Prcvr PRCVR
@shortform_indicator   preceiving             1234-1235-14-1236-1245 prcvg Prcvg PRCVG
@shortform_indicator   prepaid                1234-1235-15-1234-145 prepd Prepd PREPD
@shortform_indicator   purblind               1234-136-1235-12-123 purbl Purbl PURBL
@shortform_indicator   purblindly             1234-136-1235-12-123-123-13456 purblly Purblly PURBLLY
@shortform_word        purblindness           1234-136-1235-12-123-56-234 purblness 1234-136-1235-12-123-1345-15-234-234
@shortform_word        purblindnesses         1234-136-1235-12-123-56-234-15-234 purblnesses 1234-136-1235-12-123-1345-15-234-234-15-234
@shortform_indicator   quickdraw              12345-13-145-1235-1-2456 qkdraw Qkdraw QKDRAW
@shortform_word        quicken                12345-13-26 qken 12345-13-15-1345
@shortform_word        quickened              12345-13-26-1246 qkened 12345-13-15-1345-15-145
@shortform_word        quickener              12345-13-26-12456 qkener 12345-13-15-1345-15-1235
@shortform_word        quickening             12345-13-26-346 qkening 12345-13-15-1345-24-1345-1245
@shortform_word        quicker                12345-13-12456 qker 12345-13-15-1235
@shortform_word        quickest               12345-13-15-34 qkest 12345-13-15-234-2345
@shortform_indicator   quickfire              12345-13-124-24-1235-15 qkfire Qkfire QKFIRE
@shortform_word        quickfiring            12345-13-124-24-1235-346 qkfiring 12345-13-124-24-1235-24-1345-1245
@shortform_indicator   quickfreeze            12345-13-124-1235-15-15-1356-15 qkfreeze Qkfreeze QKFREEZE
@shortform_word        quickfreezing          12345-13-124-1235-15-15-1356-346 qkfreezing 12345-13-124-1235-15-15-1356-24-1345-1245
@shortform_indicator   quickfroze             12345-13-124-1235-135-1356-15 qkfroze Qkfroze QKFROZE
@shortform_word        quickfrozen            12345-13-124-1235-135-1356-26 qkfrozen 12345-13-124-1235-135-1356-15-1345
@shortform_indicator   quickie                12345-13-24-15 qkie Qkie QKIE
@shortform_word        quickish               12345-13-24-146 qkish 12345-13-24-234-125
@shortform_word        quickishly             12345-13-24-146-123-13456 qkishly 12345-13-24-234-125-123-13456
@shortform_indicator   quicklime              12345-13-123-24-134-15 qklime Qklime QKLIME
@shortform_indicator   quickly                12345-13-123-13456 qkly Qkly QKLY
@shortform_word        quickness              12345-13-56-234 qkness 12345-13-1345-15-234-234
@shortform_word        quicknesses            12345-13-56-234-15-234 qknesses 12345-13-1345-15-234-234-15-234
@shortform_word        quicksand              12345-13-234-12346 qksand 12345-13-234-1-1345-145
@shortform_indicator   quickset               12345-13-234-15-2345 qkset Qkset QKSET
@shortform_word        quicksilver            12345-13-234-24-123-1236-12456 qksilver 12345-13-234-24-123-1236-15-1235
@shortform_word        quicksilvered          12345-13-234-24-123-1236-12456-1246 qksilvered 12345-13-234-24-123-1236-15-1235-15-145
@shortform_word        quicksilvering         12345-13-234-24-123-1236-12456-346 qksilvering 12345-13-234-24-123-1236-15-1235-24-1345-1245
@shortform_indicator   quicksnap              12345-13-234-1345-1-1234 qksnap Qksnap QKSNAP
@shortform_word        quickstep              12345-13-34-15-1234 qkstep 12345-13-234-2345-15-1234
@shortform_word        quickstepped           12345-13-34-15-1234-1234-1246 qkstepped 12345-13-234-2345-15-1234-1234-15-145
@shortform_word        quickstepper           12345-13-34-15-1234-1234-12456 qkstepper 12345-13-234-2345-15-1234-1234-15-1235
@shortform_word        quickstepping          12345-13-34-15-1234-1234-346 qkstepping 12345-13-234-2345-15-1234-1234-24-1345-1245
@shortform_word        quicktempered          12345-13-2345-15-134-1234-12456-1246 qktempered 12345-13-2345-15-134-1234-15-1235-15-145
@shortform_word        quicktime              12345-13-5-2345 qktime 12345-13-2345-24-134-15
@shortform_word        quickwitted            12345-13-2456-24-2345-2345-1246 qkwitted 12345-13-2456-24-2345-2345-15-145
@shortform_word        quickwittedly          12345-13-2456-24-2345-2345-1246-123-13456 qkwittedly 12345-13-2456-24-2345-2345-15-145-123-13456
@shortform_word        quickwittedness        12345-13-2456-24-2345-2345-1246-56-234 qkwittedness 12345-13-2456-24-2345-2345-15-145-1345-15-234-234
@shortform_indicator   quicky                 12345-13-13456 qky Qky QKY
@shortform_word        readacross             1235-2-145-1-14-1235 readacr 1235-15-1-145-1-14-1235
@shortform_indicator   rebraille              1235-15-12-1235-123 rebrl Rebrl REBRL
@shortform_indicator   rebrailled             1235-15-12-1235-123-145 rebrld Rebrld REBRLD
@shortform_indicator   rebrailler             1235-15-12-1235-123-1235 rebrlr Rebrlr REBRLR
@shortform_indicator   received               1235-14-1236-145 rcvd Rcvd RCVD
@shortform_indicator   receiver               1235-14-1236-1235 rcvr Rcvr RCVR
@shortform_word        receivership           1235-14-1236-1235-146-24-1234 rcvrship 1235-14-1236-1235-234-125-24-1234
@shortform_indicator   rejoiced               1235-245-14-145 rjcd Rjcd RJCD
@shortform_word        rejoiceful             1235-245-14-56-123 rjcful 1235-245-14-124-136-123
@shortform_word        rejoicefully           1235-245-14-56-123-123-13456 rjcfully 1235-245-14-124-136-123-123-13456
@shortform_word        rejoicefulness         1235-245-14-56-123-56-234 rjcfulness 1235-245-14-124-136-123-1345-15-234-234
@shortform_indicator   rejoicer               1235-245-14-1235 rjcr Rjcr RJCR
@shortform_indicator   rejoicingly            1235-245-14-1245-123-13456 rjcgly Rjcgly RJCGLY
@shortform_indicator   reletter               1235-15-123-1235 relr Relr RELR
@shortform_word        relettered             1235-15-123-1235-1246 relred 1235-15-123-1235-15-145
@shortform_word        relettering            1235-15-123-1235-346 relring 1235-15-123-1235-24-1345-1245
@shortform_indicator   repaid                 1235-15-1234-145 repd Repd REPD
@shortform_word        rightabout             5-1235-1-12 rightab 1235-24-1245-125-2345-1-12
@shortform_word        roundabout             1235-46-145-1-12 roundab 1235-135-136-1345-145-1-12
@shortform_word        roustabout             1235-1256-34-1-12 roustab 1235-135-136-234-2345-1-12
@shortform_indicator   runabout               1235-136-1345-1-12 runab Runab RUNAB
@shortform_word        saidest                234-145-15-34 sdest 234-145-15-234-2345
@shortform_word        saidst                 234-145-34 sdst 234-145-234-2345
@shortform_word        scattergood            234-14-1-2345-2345-12456-1245-145 scattergd 234-14-1-2345-2345-15-1235-1245-145
@shortform_word        schoolchildren         234-16-135-135-123-16-1345 schoolchn 234-14-125-135-135-123-14-125-1345
@shortform_word        schoolfriend           234-16-135-135-123-124-1235 schoolfr 234-14-125-135-135-123-124-1235
@shortform_word        should've              146-145-3-1236-15 shd've 234-125-145-3-1236-15
@shortform_word        shoulda                146-145-1 shda 234-125-145-1
@shortform_word        shouldest              146-145-15-34 shdest 234-125-145-15-234-2345
@shortform_word        shouldn't              146-145-1345-3-2345 shdn't 234-125-145-1345-3-2345
@shortform_word        shouldn't've           146-145-1345-3-2345-3-1236-15 shdn't've 234-125-145-1345-3-2345-3-1236-15
@shortform_word        shouldst               146-145-34 shdst 234-125-145-234-2345
@shortform_word        snowblind              234-1345-246-12-123 snowbl 234-1345-135-2456-12-123
@shortform_word        snowblindness          234-1345-246-12-123-56-234 snowblness 234-1345-135-2456-12-123-1345-15-234-234
@shortform_word        snowblindnesses        234-1345-246-12-123-56-234-15-234 snowblnesses 234-1345-135-2456-12-123-1345-15-234-234-15-234
@shortform_word        somesuch               5-234-234-16 somesch 234-135-134-15-234-14-125
@shortform_word        southabout             234-1256-1456-1-12 southab 234-135-136-2345-125-1-12
@shortform_word        stepchildren           34-15-1234-16-1345 stepchn 234-2345-15-1234-14-125-1345
@shortform_word        stirabout              34-24-1235-1-12 stirab 234-2345-24-1235-1-12
@shortform_word        suchlike               234-16-123-24-13-15 schlike 234-14-125-123-24-13-15
@shortform_word        supergood              234-136-1234-12456-1245-145 supergd 234-136-1234-15-1235-1245-145
@shortform_word        superquick             234-136-1234-12456-12345-13 superqk 234-136-1234-15-1235-12345-13
@shortform_word        tailfirst              2345-1-24-123-124-34 tailfst 2345-1-24-123-124-234-2345
@shortform_word        thereabout             5-2346-1-12 timeheab 2345-24-134-15-125-15-1-12
@shortform_word        thereafter             5-2346-1-124 timeheaf 2345-24-134-15-125-15-1-124
@shortform_word        thereagain             5-2346-1-1245 timeheag 2345-24-134-15-125-15-1-1245
@shortform_word        thereagainst           5-2346-1-1245-34 timeheagst 2345-24-134-15-125-15-1-1245-234-2345
@shortform_word        thereinafter           5-2346-35-1-124 timeheinaf 2345-24-134-15-125-15-24-1345-1-124
@shortform_word        thereinagain           5-2346-35-1-1245 timeheinag 2345-24-134-15-125-15-24-1345-1-1245
@shortform_word        togetherness           2345-1245-1235-56-234 tgrness 2345-1245-1235-1345-15-234-234
@shortform_indicator   turnabout              2345-136-1235-1345-1-12 turnab Turnab TURNAB
@shortform_indicator   unaccording            136-1345-1-14 unac Unac UNAC
@shortform_indicator   unaccordingly          136-1345-1-14-123-13456 unacly Unacly UNACLY
@shortform_indicator   unblindfold            136-1345-12-123-124-135-123-145 unblfold Unblfold UNBLFOLD
@shortform_word        unblindfolded          136-1345-12-123-124-135-123-145-1246 unblfolded 136-1345-12-123-124-135-123-145-15-145
@shortform_word        unblindfolding         136-1345-12-123-124-135-123-145-346 unblfolding 136-1345-12-123-124-135-123-145-24-1345-1245
@shortform_indicator   unbraille              136-1345-12-1235-123 unbrl Unbrl UNBRL
@shortform_indicator   unbrailled             136-1345-12-1235-123-145 unbrld Unbrld UNBRLD
@shortform_indicator   undeceive              136-1345-145-14-1236 undcv Undcv UNDCV
@shortform_indicator   undeceived             136-1345-145-14-1236-145 undcvd Undcvd UNDCVD
@shortform_indicator   undeceiver             136-1345-145-14-1236-1235 undcvr Undcvr UNDCVR
@shortform_indicator   undeceiving            136-1345-145-14-1236-1245 undcvg Undcvg UNDCVG
@shortform_indicator   undeclare              136-1345-145-14-123 undcl Undcl UNDCL
@shortform_indicator   undeclared             136-1345-145-14-123-145 undcld Undcld UNDCLD
@shortform_word        underpaid              5-136-1234-145 underpd 136-1345-145-15-1235-1234-145
@shortform_indicator   unfriend               136-1345-124-1235 unfr Unfr UNFR
@shortform_word        unfriendlier           136-1345-124-1235-123-24-12456 unfrlier 136-1345-124-1235-123-24-15-1235
@shortform_word        unfriendliest          136-1345-124-1235-123-24-15-34 unfrliest 136-1345-124-1235-123-24-15-234-2345
@shortform_word        unfriendliness         136-1345-124-1235-123-24-56-234 unfrliness 136-1345-124-1235-123-24-1345-15-234-234
@shortform_word        unfriendlinesses       136-1345-124-1235-123-24-56-234-15-234 unfrlinesses 136-1345-124-1235-123-24-1345-15-234-234-15-234
@shortform_indicator   unfriendly             136-1345-124-1235-123-13456 unfrly Unfrly UNFRLY
@shortform_word        unlettered             136-1345-123-1235-1246 unlred 136-1345-123-1235-15-145
@shortform_indicator   unnecessary            136-1345-1345-15-14 unnec Unnec UNNEC
@shortform_indicator   unpaid                 136-1345-1234-145 unpd Unpd UNPD
@shortform_word        unperceive             136-1345-1234-12456-14-1236 unpercv 136-1345-1234-15-1235-14-1236
@shortform_word        unperceived            136-1345-1234-12456-14-1236-145 unpercvd 136-1345-1234-15-1235-14-1236-145
@shortform_word        unperceiving           136-1345-1234-12456-14-1236-1245 unpercvg 136-1345-1234-15-1235-14-1236-1245
@shortform_indicator   unquick                136-1345-12345-13 unqk Unqk UNQK
@shortform_indicator   unreceived             136-1345-1235-14-1236-145 unrcvd Unrcvd UNRCVD
@shortform_indicator   unrejoice              136-1345-1235-245-14 unrjc Unrjc UNRJC
@shortform_indicator   unrejoiced             136-1345-1235-245-14-145 unrjcd Unrjcd UNRJCD
@shortform_word        unrejoiceful           136-1345-1235-245-14-56-123 unrjcful 136-1345-1235-245-14-124-136-123
@shortform_word        unrejoicefully         136-1345-1235-245-14-56-123-123-13456 unrjcfully 136-1345-1235-245-14-124-136-123-123-13456
@shortform_word        unrejoicefulness       136-1345-1235-245-14-56-123-56-234 unrjcfulness 136-1345-1235-245-14-124-136-123-1345-15-234-234
@shortform_indicator   unrejoicer             136-1345-1235-245-14-1235 unrjcr Unrjcr UNRJCR
@shortform_indicator   unrejoicing            136-1345-1235-245-14-1245 unrjcg Unrjcg UNRJCG
@shortform_indicator   unrejoicingly          136-1345-1235-245-14-1245-123-13456 unrjcgly Unrjcgly UNRJCGLY
@shortform_indicator   walkabout              2456-1-123-13-1-12 walkab Walkab WALKAB
@shortform_indicator   wellpaid               2456-15-123-123-1234-145 wellpd Wellpd WELLPD
@shortform_word        westabout              2456-15-34-1-12 westab 2456-15-234-2345-1-12
@shortform_word        whereabout             5-156-1-12 workhab 2456-135-1235-13-125-1-12
@shortform_word        whereafter             5-156-1-124 workhaf 2456-135-1235-13-125-1-124
@shortform_word        whereagain             5-156-1-1245 workhag 2456-135-1235-13-125-1-1245
@shortform_word        whereagainst           5-156-1-1245-34 workhagst 2456-135-1235-13-125-1-1245-234-2345
@shortform_word        whereinafter           5-156-35-1-124 workhinaf 2456-135-1235-13-125-24-1345-1-124
@shortform_word        whereinagain           5-156-35-1-1245 workhinag 2456-135-1235-13-125-24-1345-1-1245
@shortform_indicator   womanfriend            2456-135-134-1-1345-124-1235 womanfr Womanfr WOMANFR
@shortform_word        womenfriends           2456-135-134-26-124-1235-234 womenfrs 2456-135-134-15-1345-124-1235-234
@shortform_indicator   would've               2456-145-3-1236-15 wd've Wd've WD'VE
@shortform_indicator   woulda                 2456-145-1 wda Wda WDA
@shortform_word        wouldest               2456-145-15-34 wdest 2456-145-15-234-2345
@shortform_indicator   wouldn't               2456-145-1345-3-2345 wdn't Wdn't WDN'T
@shortform_indicator   wouldn't've            2456-145-1345-3-2345-3-1236-15 wdn't've Wdn't've WDN'T'VE
@shortform_word        wouldst                2456-145-34 wdst 2456-145-234-2345
use


########################################
#   extra shortforms
########################################

use word_whole_+ word_whole_-
@shortform_indicator   unrepaid   136-1345-1235-15-234-145 unrepd Unrepd UNREPD
@shortform_indicator   unsaid     136-1345-234-145 unsd Unsd UNSD
use


########################################

attrs - $contraction

################################################################################

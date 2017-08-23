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

################################################################################

#   letters   ⠁⠃⠉⠙⠑⠋⠛⠓⠊⠚⠅⠇⠍⠝⠕⠏⠟⠗⠎⠞⠥⠧⠺⠭⠽⠵
#   ⠁a ⠃b ⠉c ⠙d ⠑e ⠋f ⠛g ⠓h ⠊i ⠚j ⠅k ⠇l ⠍m ⠝n ⠕o ⠏p ⠟q ⠗r ⠎s ⠞t ⠥u ⠧v ⠺w ⠭x ⠽y ⠵z
#
#   modifiers   ⠈[⠡⠒⠬⠤] ⠘[⠯⠡⠩⠫⠻⠒⠌⠬] ⠘⠸[⠂⠆⠤]
#   ⠈⠡slash ⠈⠒horizontal ⠈⠬breve ⠈⠤macron
#   ⠘⠯cedilla  ⠘⠡grave ⠘⠩circumflex ⠘⠫ring ⠘⠻tilde ⠘⠒diaeresis ⠘⠌acute ⠘⠬caron
#   ⠘⠸⠂first   ⠘⠸⠆second ⠘⠸⠤third
#
#   alphabetic wordsigns   ⠵⠃⠉⠙⠑⠋⠛⠓⠭⠚⠅⠇⠍⠝⠏⠟⠗⠎⠞⠥⠧⠺⠽
#   ⠵as ⠃but ⠉can ⠙do ⠑every ⠋from ⠛go ⠓have ⠭it ⠚just ⠅knowledge ⠇like ⠍more
#   ⠝not ⠏people ⠟quite ⠗rather ⠎so ⠞that ⠥us ⠧very ⠺will ⠽you
#
#   strong wordsigns   ⠡⠳⠌⠩⠹⠱
#   ⠡child ⠳out ⠌still ⠩shall ⠹this ⠱which
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
#   initial-letter   ⠘[⠮⠹⠥⠱⠺] ⠸[⠉⠓⠍⠎⠮⠺] ⠐[⠡⠙⠑⠋⠓⠅⠇⠍⠝⠕⠳⠏⠟⠗⠎⠮⠹⠞⠥⠱⠺⠽]
#   ⠸⠉cannot ⠐⠡character ⠐⠙day ⠐⠑ever ⠐⠋father ⠸⠓had ⠐⠓here
#   ⠐⠅know ⠐⠇lord ⠸⠍many ⠐⠍mother ⠐⠝name ⠐⠕one ⠐⠳ought
#   ⠐⠏part ⠐⠟question ⠐⠗right ⠐⠎some ⠸⠎spirit
#   ⠸⠮their ⠐⠮there ⠘⠮these ⠘⠹those ⠐⠹through ⠐⠞time
#   ⠐⠥under ⠘⠥upon ⠐⠱where ⠘⠱whose ⠘⠺word ⠐⠺work ⠸⠺world ⠐⠽young
#
#   final-letter   ⠨[⠙⠑⠝⠎⠞] ⠰[⠑⠛⠇⠝⠎⠞⠽]
#   ⠨⠙ound ⠨⠑ance ⠨⠝sion ⠨⠎less ⠨⠞ount ⠰⠑ence ⠰⠛ong ⠰⠇ful ⠰⠝tion ⠰⠎ness ⠰⠞ment ⠰⠽ity
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
#   ⠆ 23        ; bb be    7.1.3
#   ⠖ 235       ! ff
#   ⠦ 236       ? “ his    7.5
#   ⠒ 25        : cc con   7.1.3
#   ⠲ 256       . dis      7.1.3
#   ⠴ 356       ” was      7.1.3

################################################################################

include english-ueb-grade1.rst

set contraction bit00
attrs = $contraction


########################################
#   word filters
########################################

filter word_whole_+         @[WORD_<+]                @[APOST_+]@[WORD_>+]
filter word_whole_begin_+   @[WORD_<+]                @[LETTER_>+]*@[APOST_+]@[WORD_>+]
filter word_whole_end+      @[WORD_<+]%a*             @[APOST_+]@[WORD_>+]
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
#   - 10.1.1   standing alone
#   - 10.1.2   followed by 'd, 'll, 're, 's, 't, 've and standing alone
#   - 2.6.4
#   ALPHABETIC CONTRACTION
#   preword - aftword '(d|ll|re|s|t|ve)
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

use word_whole_+ -

macro letter_sign
rule premode $1 \H\;56;\H$1
rule premode $2 \H\;56;\H$2
eom

@letter_sign B b
@letter_sign C c
@letter_sign D d
@letter_sign E e
@letter_sign F f
@letter_sign G g
@letter_sign H h

@letter_sign J j
@letter_sign K k
@letter_sign L l
@letter_sign M m
@letter_sign N n

@letter_sign P p
@letter_sign Q q
@letter_sign R r
@letter_sign S s
@letter_sign T t
@letter_sign U u
@letter_sign V v
@letter_sign W w
@letter_sign X x
@letter_sign Y y
@letter_sign Z z

use


########################################
#   10.2   Strong Wordsigns
#   - 10.2.1   standing alone
#   - 10.2.2   followed by 'd, 'll, 're, 's, 't, 've and standing alone
#   - 2.6.4
#   NOT ALPHABETIC
#   preword - aftword '(d|ll|re|s|t|ve)
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
#   - 10.11.2
#   NOT ALPHABETIC
#   any - any
########################################

use word_whole_begin_+ word_whole_begin_-

## and
#   can back translate with cedilla
uses - not_modifier_45_- rule trans and 12346

## for
uses - - rule trans for 123456

## of
uses - - rule trans of 12356

rule trans aeroflot 1-12456-135-124-123-135-2345
rule trans biofeedback 12-24-135-124-15-1246-12-1-14-13
rule trans chlorofluorocarbon 16-123-135-1235-135-124-123-136-135-1235-135-14-345-12-135-1345
rule trans chloroform 16-123-135-1235-135-123456-134
rule trans filofax 124-24-123-135-124-1-1346
rule trans hydrofoil 125-13456-145-1235-135-124-135-24-123
rule trans insofar 35-234-135-124-345
rule trans microfiche 134-24-14-1235-135-124-24-16-15
rule trans microfilm 134-24-14-1235-135-124-24-123-134
rule trans microwave 134-24-14-1235-135-2456-1-1236-15
rule trans microwaved 134-24-14-1235-135-2456-1-1236-1246
rule trans microwaving 134-24-14-1235-135-2456-1-1236-346
rule trans pianoforte 1234-24-1-1345-135-123456-2345-15
rule trans proforma 1234-1235-135-123456-134-1
rule trans retrofit 1235-15-2345-1235-135-124-24-2345
rule trans riboflavin 1235-24-12-135-124-123-1-1236-35
rule trans styrofoam 34-13456-1235-135-124-135-1-134
rule trans twofer 2345-2456-135-124-12456
rule trans twofold 2345-2456-135-124-135-123-145

## the
uses - - rule trans the 2346

rule trans aesthete 1-15-234-2346-2345-15
rule trans aesthetic 1-15-234-2346-2345-24-14
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
rule trans calisthenic 14-1-123-24-234-2346-1345-24-14
rule trans demosthenes 145-15-134-135-234-2346-1345-15-234
rule trans eratosthenes 12456-1-2345-135-234-2346-1345-15-234
rule trans esther 15-234-2346-1235
rule trans esthete 15-234-2346-2345-15
rule trans esthetic 15-234-2346-2345-24-14
rule trans fainthearted 124-1-35-2345-125-15-345-2345-1246
rule trans fathead 124-1-2345-125-2-145
rule trans hothead 125-135-2345-125-2-145
rule trans lightheaded 123-24-126-2345-125-2-145-1246
rule trans lighthearted 123-24-126-2345-125-15-345-2345-1246
rule trans motheaten 134-135-1456-2-2345-26
rule trans northeast 1345-135-1235-1456-2-34
rule trans prostheses 1234-1235-135-234-2346-234-15-234
rule trans prosthesis 1234-1235-135-234-2346-234-24-234
rule trans prosthetic 1234-1235-135-234-2346-2345-24-14
rule trans softhearted 234-12356-2345-125-15-345-2345-1246
rule trans southeast 234-1256-1456-2-34
rule trans sweetheart 234-2456-15-15-2345-125-15-345-2345
rule trans thence 1456-56-15

## with
uses - - rule trans with 23456

use


########################################
#   10.4   Strong Groupsigns
#   - 10.4.2    ch sh th wh ou st
#   - 10.4.3    ing
#   - 10.11.2   ch gh sh th wh
#   - 2.6.4     referred from 10.4.2 - 10.2
#   NOT ALPHABETIC
#   ch ou sh st th wh:  not word
#   ing:  not preword
########################################

use word_whole_begin_+ word_whole_begin_-

## ar
uses - - rule trans ar 345

rule trans aright 1-5-1235
rule trans infrared 35-124-1235-1-1235-1246
rule trans tearoom 2345-2-1235-135-135-134

## ch   10.4.2   10.11.2
#   can back translate with forward slash or grave accent
uses word_whole_+ word_whole_- rule trans ch 14-125
uses - not_modifier_4_45_- rule trans ch 16

rule trans overreact 135-1236-12456-1235-15-1-14-2345
rule trans overreaction 135-1236-12456-1235-15-1-14-56-1345
rule trans react 1235-15-1-14-2345
rule trans reaction 1235-15-1-14-56-1345

## ed
#   can back translate with ring
uses not_modifier_< not_modifier_45_- rule trans ed 1246

rule trans airedale 1-24-1235-15-145-1-123-15
rule trans comedown 14-135-134-15-145-246-1345
rule trans daredevil 145-345-15-145-15-1236-24-123
rule trans dumbledore 145-136-134-12-123-15-145-135-1235-15
rule trans hoedown 125-135-15-145-246-1345
rule trans kettledrum 13-15-2345-2345-123-15-145-1235-136-134
rule trans nosedive 1345-135-234-15-145-24-1236-15
rule trans nosedived 1345-135-234-15-145-24-1236-1246
rule trans nosediving 1345-135-234-15-145-24-1236-346
rule trans redevelop 1235-15-145-15-1236-15-123-135-1234
rule trans shakedown 146-1-13-15-145-246-1345
rule trans thistledown 1456-24-34-123-15-145-246-1345
rule trans tumbledown 2345-136-134-12-123-15-145-246-1345
rule trans turtledove 2345-136-1235-2345-123-15-145-135-1236-15
rule trans tweedledee 2345-2456-15-1246-123-15-145-15-15
rule trans tweedledum 2345-2456-15-1246-123-15-145-136-134
rule trans viced 1236-24-14-15-145

## er
#   can back translate with tilde
uses not_modifier_< not_modifier_45_- rule trans er 12456

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

rule trans bighearted 12-24-1245-125-15-345-2345-1246
rule trans bighorn 12-24-1245-125-135-1235-1345
rule trans bunghole 12-136-1345-1245-125-135-123-15
rule trans doghouse 145-135-1245-125-1256-234-15
rule trans foghorn 124-135-1245-125-135-1235-1345
rule trans pigheaded 1234-24-1245-125-2-145-1246
rule trans senghor 234-26-1245-125-135-1235
rule trans shanghai 146-1-1345-1245-125-1-24
rule trans songhai 234-135-1345-126-1-24
rule trans yoghourt 13456-135-1245-125-1256-1235-2345

## ing
#   can back translate with breve or caron
uses - not_modifier_4_45_- match trans %a@[SEQ_<+]* ing -  = 346 =

rule trans disingenuous 256-35-1245-26-136-1256-234
rule trans leningrad 123-26-35-1245-1235-1-145
rule trans stalingrad 34-1-123-35-1245-1235-1-145
rule trans vainglorious 1236-1-35-1245-123-135-1235-24-1256-234
rule trans vainglory 1236-1-35-1245-123-135-1235-13456

## ou
#   can back translate with breve or caron
uses word_whole_+ word_whole_- rule trans st 135-136
uses - - rule trans ou 1256

## ow
uses - - rule trans ow 246

rule trans autoworker 1-136-2345-135-5-2456-12456
rule trans coworker 14-135-5-2456-12456
rule trans kilowatt 13-24-123-135-2456-1-2345-2345
rule trans locoweed 123-135-14-135-2456-15-1246
rule trans monowheel 134-135-1345-135-156-15-15-123
rule trans noway 1345-135-2456-1-13456
rule trans nowhere 1345-135-5-156
rule trans nowise 1345-135-2456-24-234-15

## sh
#   can back translate with circumflex
uses word_whole_+ word_whole_- rule trans sh 234-125
uses - not_modifier_45_- rule trans sh 146

rule trans asshole 1-234-234-125-135-123-15
rule trans chisholm 16-24-234-125-135-123-134
rule trans dachshund 145-1-16-234-125-136-1345-145
rule trans florsheim 124-123-135-1235-234-125-15-24-134
rule trans grasshopper 1245-1235-1-234-234-125-135-1234-1234-12456
rule trans hogshead 125-135-1245-234-125-2-145
rule trans mishandle 134-24-234-125-12346-123-15
rule trans mishandled 134-24-234-125-12346-123-1246
rule trans mishandling 134-24-234-125-12346-123-346
rule trans mishap 134-24-234-125-1-1234

## st
#   can back translate with acute accent
uses word_whole_+ word_whole_- rule trans st 234-2345
uses - not_modifier_45_- rule trans st 34

rule trans asthma 1-234-1456-134-1
rule trans bastion 12-1-234-56-1345
rule trans bundestag 12-136-1345-145-15-234-2345-1-1245
rule trans combustion 14-135-134-12-136-234-56-1345
rule trans congestion 25-1245-15-234-56-1345
rule trans cooperstown 14-135-135-1234-12456-234-2345-246-1345
rule trans crosstown 14-1235-135-234-234-2345-246-1345
rule trans digestion 145-24-1245-15-234-56-1345
rule trans exhaustion 15-1346-125-1-136-234-56-1345
rule trans guesstimate 1245-136-15-234-234-2345-24-134-1-2345-15
rule trans guesstimated 1245-136-15-234-234-2345-24-134-1-2345-1246
rule trans guesstimating 1245-136-15-234-234-2345-24-134-1-2345-346
rule trans indigestion 35-145-24-1245-15-234-56-1345
rule trans ingestion 35-1245-15-234-56-1345
rule trans isthmi 24-234-1456-134-24
rule trans isthmus 24-234-1456-134-136-234
rule trans jamestown 245-1-134-15-234-2345-246-1345
rule trans kingstown 13-346-234-2345-246-1345
rule trans mistime 134-24-234-5-2345
rule trans painstaking 1234-1-35-234-2345-1-13-346
rule trans pastime 1234-1-234-5-2345
rule trans reichstag 1235-15-24-16-234-2345-1-1245
rule trans suggestion 234-136-2356-15-234-56-1345
rule trans youngstown 5-13456-234-2345-246-1345

## th
uses word_whole_+ word_whole_- rule trans th 2345-125
uses - - rule trans th 1456

rule trans adulthood 1-145-136-123-2345-125-135-135-145
rule trans anthill 1-1345-2345-125-24-123-123
rule trans bartholdi 12-345-2345-125-135-123-145-24
rule trans beethoven 12-15-15-2345-125-135-1236-26
rule trans courthouse 14-1256-1235-2345-125-1256-234-15
rule trans foothill 124-135-135-2345-125-24-123-123
rule trans foothold 124-135-135-2345-125-135-123-145
rule trans goatherd 1245-135-1-2345-125-12456-145
rule trans hothouse 125-135-2345-125-1256-234-15
rule trans knighthood 13-1345-24-126-2345-125-135-135-145
rule trans knothole 13-1345-135-2345-125-135-123-15
rule trans lighthouse 123-24-126-2345-125-1256-234-15
rule trans lufthansa 123-136-124-2345-125-1-1345-234-1
rule trans nighthawk 1345-24-126-2345-125-1-2456-13
rule trans nuthatch 1345-136-2345-125-1-2345-16
rule trans outhouse 1256-2345-125-1256-234-15
rule trans parenthood 1234-345-26-2345-125-135-135-145
rule trans penthouse 1234-26-2345-125-1256-234-15
rule trans pilothouse 1234-24-123-135-2345-125-1256-234-15
rule trans porthole 1234-135-1235-2345-125-135-123-15
rule trans potholder 1234-135-2345-125-135-123-145-12456
rule trans pothole 1234-135-2345-125-135-123-15
rule trans pothook 1234-135-2345-125-135-135-13
rule trans richthofen 1235-24-16-2345-125-12356-26
rule trans sainthood 234-1-35-2345-125-135-135-145
rule trans shorthand 146-135-1235-2345-125-12346
rule trans shorthorn 146-135-1235-2345-125-135-1235-1345
rule trans warthog 2456-345-2345-125-135-1245

## wh
uses word_whole_+ word_whole_- rule trans wh 2456-125
uses - - rule trans wh 156

rule trans rawhide 1235-1-2456-125-24-145-15
rule trans sawhorse 234-1-2456-125-135-1235-234-15

use


########################################
#   10.5   Lower Wordsigns
#   - 10.5.1   be were his was
#   - 10.5.2   enough
#   - 10.5.3   in
#   - 10.5.4   enough in
#   NOT ALPHABETIC
#   be his was were:  word contact upper
#   enough:  word  word upper also 's
#   in:  word upper
########################################
#filter lower_wordsign_+    @[NO_CAPS_<]@[CAPS_<]*|(^|%_)@[SEQ_INDCS_<]*|@[WORD_<+]@[SEQ_<+]*%u@[SEQ_INDCS_<]*   @[SEQ_>+]*%u@[SEQ_>+]*@[WORD_>+]|@[SEQ_INDCS_>]*(%_|^)|@[CAPS_>]*@[NO_CAPS_>]
#filter lower_wordsign_-    (^|%_)|@[WORD_<-]@[SEQ_<-]*(⠐⠣|⠨⠣|⠸⠣)|@[WORD_<-]@[SEQ_<-]*@[SEQ_INDCS_<]   @[SEQ_INDCS_>]@[SEQ_>-]*@[WORD_>-]|@[SEQ_>-]*(⠐⠜|⠨⠜|⠸⠜)@[SEQ_>-]*@[WORD_>-]|@[SEQ_>-]*(%_|^)

pattern NO_CAPS_<    [\H\S]([⠨⠘⠸⠈][⠆⠂⠶]|[⠈⠘⠸⠐⠨]⠼[⠆⠂⠶]|⠈⠨⠣|[⠰⠠]⠄)[\H\S]
pattern NO_CAPS_>    [\H\S](⠈⠨⠜|[⠈⠘⠸⠐⠨]⠼⠄|[⠨⠘⠸⠈]⠄)[\H\S]


chars +=*,.;:?!"'“”‘’ $lower_dots
chars ()[]{} $upper_dots

#   +=*,.;:?!"'“”‘’
#   ⠂⠄⠐⠠⠆⠢⠒⠤⠔⠰⠖⠦⠲⠴⠶
#
#   "'“”‘’ \;236;\;356; \;45;\;6;\;456;  ⠦|⠴|⠘⠦|⠘⠴|⠸⠦|⠸⠴|⠠⠦|⠠⠴
#   ?   \;236;                 ⠦
#   !   \;235;                 ⠖
#   :   \;25;                  ⠒
#   ;   \;23;                  ⠆
#   .   \;256;                 ⠲
#   ,   \;2;                   ⠂
#   *   \;5-35;                ⠐⠔
#   =   \;5-2356;              ⠐⠶
#   +   \;5-235;               ⠐⠖
#   -   \;5-6-36;\;6-36;\;36;  ⠐⠠⠤|⠠⠤|⠤
#
#   ⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠘⠙⠚⠛⠜⠝⠞⠟⠡⠣⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠸⠹⠺⠻⠼⠽⠾⠿
#
#   ⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠙⠚⠛⠜⠝⠞⠟⠡⠣⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠹⠺⠻⠼⠽⠾⠿|[⠘⠸][⠦⠴]

pattern LOWER_DOTS_+    [-‐‑‒–—―+=*,.;:?!"'“”‘’]
pattern LOWER_DOTS_<-   [\;2;\;236;\;356;\;235;\;25;\;23;\;256;\;35;\;2356;\;235;\;36;]
pattern LOWER_DOTS_>-   [\;2;\;236;\;356;\;235;\;25;\;23;\;256;\;45;\;6;\;456;\;5;]
pattern UPPER_DOTS_+    [\(\)\[\]{}]
pattern UPPER_DOTS_-    [⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠙⠚⠛⠜⠝⠞⠟⠡⠣⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠹⠺⠻⠼⠽⠾⠿\S]|[⠘⠸]![⠦⠴]

filter lower_wordsign_<+  @[LOWER_DOTS_+]    -
filter lower_wordsign_>+  -                  @[LOWER_DOTS_+]
filter lower_wordsign_<-  @[LOWER_DOTS_<-]   -
filter lower_wordsign_>-  -                  @[LOWER_DOTS_>-]

filter enough_in_<+    (^|%_)!%_*(@[UPPER_DOTS_+]|[\H\S]![\H\S⠠]+[\H\S])!%_* -
.stop
use lower_wordsign_<+ lower_wordsign_<-
rule trans be 12-15
rule trans his 125-24-234
rule trans was 2456-1-234
rule trans were 2356-15-1235-15
use lower_wordsign_>+ lower_wordsign_>-
rule trans be 12-15
rule trans his 125-24-234
rule trans was 2456-1-234
rule trans were 2356-15-1235-15
use word_whole_+ word_whole_-
rule trans be 23
rule trans his 236
rule trans was 356
rule trans were 2356
.cont

pattern CAPS_<  [\H\S](⠠?⠠?⠠|⠠⠄)[\H\S]
pattern CAPS_>  [\H\S](⠠⠠?⠠?|⠠⠄)[\H\S]

pattern UPPER_DOTS_<      [⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠙⠚⠛⠝⠞⠟⠡⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠹⠺⠻⠼⠽⠾⠿]|[⠘⠸]![⠦⠴]|[⠐⠨⠸][⠣⠜]
pattern UPPER_DOTS_>      [⠁⠃⠅⠇⠈⠉⠊⠋⠌⠍⠎⠏⠑⠓⠕⠗⠙⠚⠛⠝⠞⠟⠡⠥⠧⠨⠩⠪⠫⠬⠭⠮⠯⠱⠳⠵⠷⠹⠺⠻⠼⠽⠾⠿]|[⠘⠸]![⠦⠴]|[⠐⠨⠸][⠣⠜]

pattern SPACE_<+   (^|%_)@[SEQ_<+]*|(^|%[_~])@[SEQ_<+]*@[SEQ_<+]
pattern SPACE_>+   @[SEQ_>+]*@[SEQ_>+](%[_~]|^)|@[SEQ_>+]*(%_|^)
pattern SPACE_<-   (^|%_)@[SEQ_<-]*|(^|%[_~])@[SEQ_<-]*@[SEQ_<-]
pattern SPACE_>-   @[SEQ_>-]*@[SEQ_>-](%[_~]|^)|@[SEQ_>-]*(%_|^)

filter space_+   @[SPACE_<+]   @[SPACE_>+]
filter space_-   @[SPACE_<-]   @[SPACE_>-]

## be (word)
uses space_+ -             rule -forward  pretrans  be \M\;12-15;\M
uses -       word_whole_-  rule -backward trans     be 23
match -forward  posttrans (^|%_)@[SEQ_INDCS_<]*                    \M\;12-15;\M @[SEQ_INDCS_>]*(%_|^)                      - \;23; -
match -forward  posttrans (^|%_)!%_*@[UPPER_DOTS_<]@[SEQ_INDCS_<]* \M\;12-15;\M @[WORD_>-]                                 - \;23; -
match -forward  posttrans @[WORD_<-]                               \M\;12-15;\M @[SEQ_INDCS_>]*@[UPPER_DOTS_>]!%_*(%_|^)   - \;23; -

## his
uses space_+ -            rule -forward  pretrans his \M\;125-24-234;\M
uses -       word_whole_- rule -backward trans    his 236
match -forward  posttrans (^|%_)@[SEQ_INDCS_<]*                    \M\;125-24-234;\M @[SEQ_INDCS_>]*(%_|^)                      - \;236; -
match -forward  posttrans (^|%_)!%_*@[UPPER_DOTS_<]@[SEQ_INDCS_<]* \M\;125-24-234;\M @[WORD_>-]                                 - \;236; -
match -forward  posttrans @[WORD_<-]                               \M\;125-24-234;\M @[SEQ_INDCS_>]*@[UPPER_DOTS_>]!%_*(%_|^)   - \;236; -

## was
uses space_+ -            rule -forward  pretrans was \M\;2456-1-234;\M
uses -       word_whole_- rule -backward trans was 356
match -forward  posttrans (^|%_)@[SEQ_INDCS_<]*                    \M\;2456-1-234;\M @[SEQ_INDCS_>]*(%_|^)                      - \;356; -
match -forward  posttrans (^|%_)!%_*@[UPPER_DOTS_<]@[SEQ_INDCS_<]* \M\;2456-1-234;\M @[WORD_>-]                                 - \;356; -
match -forward  posttrans @[WORD_<-]                               \M\;2456-1-234;\M @[SEQ_INDCS_<]*@[UPPER_DOTS_>]!%_*(%_|^)   - \;356; -

## were
uses space_+ -            rule -forward  pretrans were \M\;2456-124565-15;\M
uses -       word_whole_- rule -backward trans were 2356
match -forward  posttrans (^|%_)@[SEQ_INDCS_<]*                    \M\;2456-124565-15;\M @[SEQ_INDCS_>]*(%_|^)                      - \;2356; -
match -forward  posttrans (^|%_)!%_*@[UPPER_DOTS_<]@[SEQ_INDCS_<]* \M\;2456-124565-15;\M @[WORD_>-]                                 - \;2356; -
match -forward  posttrans @[WORD_<-]                               \M\;2456-124565-15;\M @[SEQ_INDCS_<]*@[UPPER_DOTS_>]!%_*(%_|^)   - \;2356; -

## enough
uses word_whole_+ -            rule -forward  pretrans enough \M\;26-1256-126;\M
uses -            word_whole_- rule -backward trans enough 26
match -forward  posttrans (^|%_)@[SEQ_INDCS_<]*         \M\;26-1256-126;\M @[SEQ_INDCS_>]*(%_|^)           - \;26; -
match -forward  posttrans (^|%_)!%_*@[UPPER_DOTS_<]!%_* \M\;26-1256-126;\M @[WORD_>-]                      - \;26; -
match -forward  posttrans @[WORD_<-]                    \M\;26-1256-126;\M !%_*@[UPPER_DOTS_>]!%_*(%_|^)   - \;26; -

uses word_whole_+ word_whole_- rule trans enough’s 26-3-234
uses word_whole_+ word_whole_- rule trans enough's 26-3-234

## in (word)
uses word_whole_+ -            rule -forward  pretrans in \M\;24-1345;\M
uses -            word_whole_- rule -backward trans in 35
match -forward  posttrans (^|%_)@[SEQ_INDCS_<]*         \M\;24-1345;\M @[SEQ_INDCS_>]*(%_|^)           - \;35; -
match -forward  posttrans (^|%_)!%_*@[UPPER_DOTS_<]!%_* \M\;24-1345;\M @[WORD_>-]                      - \;35; -
match -forward  posttrans @[WORD_<-]                    \M\;24-1345;\M !%_*@[UPPER_DOTS_>]!%_*(%_|^)   - \;35; -

use


########################################
#   10.6   Lower Groupsigns
#   - 10.6.1    be con dis
#   - 10.6.2    be con dis
#   - 10.6.3    be con dis
#   - 10.6.4    be con dis
#   - 10.6.5    ea bb cc ff gg
#   - 10.6.6    ea bb cc ff gg
#   - 10.6.7    ea
#   - 10.6.8    en in
#   - 10.6.9    en
#   - 10.6.10
#   NOT ALPHABETIC
#   be con dis:  preword - letter*  no capital
#   bb cc ea ff gg:  letter* - letter*  no capital
#   en:  not word
#   in:  letter* - letter*  vs lower wordsign
#   multiple  upper somewhere
########################################

## bb   10.6.5   10.6.6

#   needed with not %[_l] for en and in
chars ⠯⠩⠫⠻⠌⠡⠒⠬⠂⠆⠤ $modifier

uses word_mid_+ word_mid_- rule trans bb 23

use word_whole_begin_+  word_whole_begin_-
rule trans dumbbell 145-136-134-12-12-15-123-123
rule trans subbasement 234-136-12-12-1-234-15-56-2345
rule trans subbing 234-136-12-12-346
use

## be (prefix)   10.6.1   10.6.2   10.6.3   10.6.4
match trans @[WORD_<+] be ati!n           @[WORD_<-] 23 ⠁(⠐⠞|⠰⠝|⠞(⠰⠽|⠊!@[N_>-]))
match trans @[WORD_<+] be atr             @[WORD_<-] 23 ⠁⠞@[R_>-]
match trans @[WORD_<+] be c![hkq]         @[WORD_<-] 23 (⠉|⠡|⠒|⠐⠡)!(⠓|⠸⠓|⠐⠓|⠅|⠐⠅|⠟|⠐⠟)
match trans @[WORD_<+] be dra             @[WORD_<-] 23   ⠙⠗@[A_>-]
match trans @[WORD_<+] be de              @[WORD_<-] 23 ⠙@[E_>-]
match trans @[WORD_<+] be da              @[WORD_<-] 23 ⠐⠙|⠙@[A_>-]
match trans @[WORD_<+] be elz             @[WORD_<-] 23 ⠑⠇@[Z_>-]
match trans @[WORD_<+] be g![gs]          @[WORD_<-] 23 (⠛!(⠛|⠣|⠶|⠎|⠩|⠌|⠐⠎|⠸⠎|⠨⠝))|⠣
match trans @[WORD_<+] be in              @[WORD_<-] 23   ⠬|⠔|⠊@[N_>-]
match trans @[WORD_<+] be l[aeiouwy]      @[WORD_<-] 23 ⠐⠇|⠨⠎|⠇(@[A_>-]|@[E_>-]|@[I_>-]|@[O_>-]|@[U_>-]|@[W_>-]|@[Y_>-])
match trans @[WORD_<+] be neficen         @[WORD_<-] 23 \;1345;\;15;\;124;\;24;\;14;(\;26;|\;56;|\;15;\;1345;)
match trans @[WORD_<+] be ne![dft]        @[WORD_<-] 23 ⠝(⠻|⠂|⠢|⠐⠑|⠰⠑|⠑!(⠙|⠲|⠐⠙|⠋|⠿|⠖|⠰⠇|⠐⠋|⠞|⠮|⠹|⠰⠝))
match trans @[WORD_<+] be n[aiu]          @[WORD_<-] 23 ⠐⠝|⠝(⠁|⠯|⠜|⠨⠑|⠊|⠬|⠔|⠰⠽|⠥|⠐⠥|⠘⠥)
match trans @[WORD_<+] be ra              @[WORD_<-] 23 ⠗@[A_>-]?   \;1235;;1;
match trans @[WORD_<+] be re!n            @[WORD_<-] 23 ⠗(⠫|⠻|⠂|⠐⠑|⠑!(@[N_>-]))
match trans @[WORD_<+] be stir            @[WORD_<-] 23 ⠌⠊@[R_>-]|⠎⠞⠊@[R_>-]
match trans @[WORD_<+] be st[or]          @[WORD_<-] 23 (⠌|⠎⠞)(@[O_>-]|@[R_>-])
match trans @[WORD_<+] be s![st]          @[WORD_<-] 23 ⠩|⠐⠎|⠸⠎|⠨⠝|⠎!(@[S_>-]|@[T_>-])
match trans @[WORD_<+] be tho             @[WORD_<-] 23 ⠘⠹|⠹@[O_>-]|⠞⠓@[O_>-]
match trans @[WORD_<+] be t![chst]        @[WORD_<-] 23 ⠐⠞|⠰⠝|⠞!(@[C_>-]|@[H_>-]|@[S_>-]|@[T_>-])
match trans @[WORD_<+] be [bfhjmopqwxz]   @[WORD_<-] 23 @[B_>-]|@[F_>-]|@[H_>-]|@[J_>-]|@[M_>-]|@[O_>-]|@[P_>-]|@[Q_>-]|@[W_>-]|@[X_>-]|@[Z_>-]
match trans @[WORD_<+] be @[MODIFER_>]    @[WORD_<-] 23 @[MODIFER_>]

#   be[cfhlnsty] are handled in 10.9.5

use word_whole_+ word_whole_-
rule trans bede 12-1246-15
rule trans bet 12-15-2345
rule trans beg 12-15-1245
rule trans bela 12-15-123-1
use
uses word_whole_begin_+ word_whole_begin_- rule trans beretta 12-12456-15-2345-2345-1
match trans @[WORD_<+] benet @[APOSS_+]@[WORD_>+]   @[WORD_<-] 23-1345-15-2345 @[APOSS_-]@[WORD_>-]

## cc   10.6.5   10.6.6
#   can back translate with horizontal slash or diaeresis
uses word_mid_+ word_mid_- rule trans cc 25

use word_whole_begin_+ word_whole_begin_-
rule trans arccosine 345-14-14-135-234-35-15
rule trans bacchanal 12-1-14-16-1-1345-1-123
rule trans bacchus 12-1-14-16-136-234
rule trans gracchus 1245-1235-1-14-16-136-234
rule trans pinocchio 1234-35-135-14-16-24-135
rule trans saccharin 234-1-14-16-345-35
rule trans zucchini 1356-136-14-16-35-24
use

## con   10.6.1   10.6.2   10.6.3   10.6.4
match trans @[WORD_<+] con c!h  @[WORD_<-] 25 ⠒@[LETTER_>-]|⠉!@[H_>-]   \;14;!\;125;   # concc concon con:
match trans @[WORD_<+] con est  @[WORD_<-] 25 ⠑|(⠌|⠎@[T_>-])   \;15;(\;34;|\;234;\;2345;)
match trans @[WORD_<+] con [abdfghijlmnopqrstuvwxyz]  @[WORD_<-] 25 @[A_>-]|@[B_>-]|@[D_>-]|@[F_>-]|@[G_>-]|@[H_>-]|@[I_>-]|@[J_>-]|@[L_>-]|@[M_>-]|@[N_>-]|@[O_>-]|@[P_>-]|@[Q_>-]|@[R_>-]|@[S_>-]|@[T_>-]|@[U_>-]|@[V_>-]|@[W_>-]|@[X_>-]|@[Y_>-]|@[Z_>-]
match trans @[WORD_<+] con @[MODIFER_>]   @[WORD_<-] 25 @[MODIFER_>]

use word_whole_begin_+ word_whole_begin_-
rule trans conakry 14-135-1345-1-13-1235-13456
rule trans conan  14-135-1345-1-1345
rule trans conned 14-135-1345-1345-1246
rule trans conurbation 14-135-1345-136-1235-12-1-56-1345
use word_whole_+ word_whole_-
rule trans cong 14-56-1245
rule trans cons 14-135-1345-234   "mod cons" 10.6.4
use

## dis   10.6.1   10.6.2   10.6.3   10.6.4
match trans @[WORD_<+] dis c!s  @[WORD_<-] 256 @[C_>-]!@[S_>-]   # discharacter discharge
match trans @[WORD_<+] dis he![dsv]  @[WORD_<-] 256 ⠐⠓|⠓([⠑⠻⠢⠂]|[⠐⠰]⠑)!(@[D_>-]|@[S_>-]|@[V_>-])   ⠓⠑![⠙⠎⠧]
match trans @[WORD_<+] dis h![ceiprtw]  @[WORD_<-] 256 (⠓|⠸⠓)!(@[C_>-]|@[E_>-]|@[I_>-]|@[P_>-]|@[R_>-]|@[T_>-]|@[W_>-])   ⠓![⠉⠑⠊⠏⠗⠞⠺⠄]
match trans @[WORD_<+] dis p!i  @[WORD_<-] 256 @[P_>-](!@[I_>-]|^)   #  dispart
match trans @[WORD_<+] dis [abdefgijlmnoqrstuvwxyz]  @[WORD_<-] 256 @[A_>-]|@[B_>-]|@[D_>-]|@[E_>-]|@[F_>-]|@[G_>-]|@[I_>-]|@[J_>-]|@[L_>-]|@[M_>-]|@[N_>-]|@[O_>-]|@[Q_>-]|@[R_>-]|@[S_>-]|@[T_>-]|@[U_>-]|@[V_>-]|@[W_>-]|@[X_>-]|@[Y_>-]|@[Z_>-]   # @[LETTER_>-]
match trans @[WORD_<+] dis @[MODIFER_>]   @[WORD_<-] 256 @[MODIFER_>]

use word_whole_+ word_whole_-
rule trans disc 145-24-234-14
rule trans discharacter 256-5-16
rule trans dish 145-24-146
rule trans diss 145-24-234-234
use

## ea   10.6.5   10.6.6   10.6.7

uses word_mid_+ word_mid_- rule trans ea 2
use
rule trans ear 15-345
rule trans pineapple 1234-35-15-1-1234-1234-123-15
rule trans wiseacr 2456-24-234-15-1-14-1235

use word_begin_+ word_begin_-
rule trans deact 145-15-1-14-2345   deactivate
rule trans deallo 145-15-1-123-123-135 deallocate
use word_whole_begin_+ word_whole_begin_-
rule trans deandre 145-15-1-1345-145-1235-15
rule trans deanna 145-15-1-1345-1345-1

use word_mid_end_+ word_mid_end_-
rule trans eance 15-46-15 vengeance
rule trans eand 15-12346 meander

use word_begin_+ word_begin_-
rule trans givea 1245-24-1236-15-1 giveaway
use word_whole_begin_+ word_whole_begin_-
rule trans geanticline 1245-15-1-1345-2345-24-14-123-35-15
rule trans gilead 1245-24-123-15-1-145

use word_whole_begin_+ word_whole_begin_-
rule trans leah 123-15-1-125
rule trans leanna 123-15-1-1345-1345-1
use word_whole_+ word_whole_-
rule trans leann 123-15-1-1345-1345   leanness
rule trans leanne 123-15-1-1345-1345-15   leanness

use word_begin_+ word_begin_-
rule trans readj 1235-15-1-145-245 eadjust
rule trans readm 1235-15-1-145-134 readmit
rule trans reaff 1235-15-1-235
use word_whole_begin_+ word_whole_begin_-
rule trans reagent 1235-15-1-1245-26-2345
use word_begin_+ word_begin_-
rule trans realig 1235-15-1-123-24-1245 align
rule trans reallo 1235-15-1-123-123-135 deallocate - really
rule trans rean 1235-15-1-1345 reanalyze, reanimate
rule trans reapp 1235-15-1-1234-1234 reappear
rule trans reass 1235-15-1-234-234
rule trans reaw 1235-15-1-2456 reawaken

use word_whole_begin_+ word_whole_begin_-
rule trans boreas 12-135-1235-15-1-234
rule trans hideaway 125-24-145-15-1-2456-1-13456
rule trans limeade 123-24-134-15-1-145-15
rule trans orangeade 135-1235-1-1345-1245-15-1-145-15
rule trans pream 1234-1235-15-1-134   preamble
rule trans roseann 1235-135-234-15-1-1345-1345
rule trans shakespearean 146-1-13-15-234-1234-15-345-15-1-1345
rule trans takeaway 2345-1-13-15-1-2456-1-13456

use

## ff   10.6.5   10.6.6
uses word_mid_+ word_mid_- rule trans ff 235

use word_whole_begin_+ word_whole_begin_-
rule trans afford 1-124-123456-145
rule trans afforest 1-124-123456-15-34
rule trans clifford 14-123-24-124-123456-145
rule trans effort 15-124-123456-2345
rule trans stafford 34-1-124-123456-145
use

## gg
uses word_mid_+ word_mid_- rule trans gg 2356

#3 en   10.6.8   10.6.9
match trans ^|!%m en %l*!%[_l] - 26 -
match trans !%[_lm]%l* en - - 26 -

uses word_mid_end_+ word_mid_end_- rule trans eness 15-56-234   closeness

use word_whole_begin_+ word_whole_begin_-
rule trans bluenose 12-123-136-15-1345-135-234-15
rule trans bottleneck 12-135-2345-2345-123-15-1345-15-14-13
rule trans forenoon 123456-15-1345-135-135-1345
rule trans forerunner 123456-15-1235-136-1345-1345-12456
rule trans toenail 2345-135-15-1345-1-24-123
rule trans turtleneck 2345-136-1235-2345-123-15-1345-15-14-13
use

## in (prefix)   10.6.8    94190   94746
match trans ^|!%m in %l*!%[_l]  - 35 -
match trans !%[_lm]%l* in -  - 35 -

#   iness overridden by ness

uses word_whole_begin_+ word_whole_begin_- rule trans multinational 134-136-123-2345-35-1-56-1345-1-123
use


########################################
#   10.7   Initial-Letter Contractions
#   BOTH ALPHABETIC AND NOT
#   any - any
#   list
########################################

## canont
uses not_modifier_< - rule trans cannot 456-14

## character
uses not_modifier_< - rule trans character 5-16

## day
uses not_modifier_< - rule trans day 5-145

use word_whole_begin_+ word_whole_begin_-

## ever   10.7.4
uses not_modifier_< - rule trans ever 5-15
rule trans achiever 1-16-24-15-1236-12456
rule trans believer 23-123-24-15-1236-12456
rule trans cheever 16-15-15-1236-12456
rule trans eversion 15-1236-12456-46-1345
rule trans evert 15-1236-12456-2345
rule trans guinevere 1245-136-35-15-1236-12456-15
rule trans monteverdi 134-135-1345-2345-15-1236-12456-145-24
rule trans nonbeliever 1345-135-1345-12-15-123-24-15-1236-12456
rule trans overachiever 135-1236-12456-1-16-24-15-1236-12456
rule trans retriever 1235-15-2345-1235-24-15-1236-12456
rule trans reversion 1235-15-1236-12456-46-1345
rule trans revert 1235-15-1236-12456-2345
rule trans thievery 1456-24-15-1236-12456-13456
rule trans unbeliever 136-1345-12-15-123-24-15-1236-12456
rule trans underachiever 5-136-1-16-24-15-1236-12456

#   reverend,revery <> reverse,revert,reverb,irreversible

rule trans irreversibl 24-1235-1235-15-1236-12456-234-24-12-123

rule trans reverbera        1235-15-1236-12456-12-12456-1

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

rule trans persever        1234-12456-234-15-1236-12456
rule trans severe 234-15-1236-12456-15
rule trans severer 234-15-1236-12456-12456
rule trans severity 234-15-1236-12456-56-13456
rule trans severus 234-15-1236-12456-136-234

rule trans severed  234-5-15-1246


## father
uses not_modifier_< - rule trans father 5-124

## had   10.7.3
uses not_modifier_< - rule trans had 456-125

rule trans hades 125-1-145-15-234
rule trans hadrian 125-1-145-1235-24-1-1345
rule trans menhaden 134-26-125-1-145-26

## here   10.7.5
uses not_modifier_< - rule trans here 5-125

rule trans adhered 1-145-125-12456-1246
rule trans adherence 1-145-125-12456-56-15
rule trans adherent 1-145-125-12456-26-2345
rule trans ciphered 14-24-1234-125-12456-1246
rule trans cohered 14-135-125-12456-1246
rule trans coherence 14-135-125-12456-56-15
rule trans coherent 14-135-125-12456-26-2345
rule trans deciphered 145-15-14-24-1234-125-12456-1246
rule trans hereditary 125-12456-1246-24-2345-345-13456
rule trans heredity 125-12456-1246-56-13456
rule trans hereford 125-12456-15-123456-145
rule trans herero 125-12456-12456-135
rule trans heresies 125-12456-15-234-24-15-234
rule trans heresy 125-12456-15-234-13456
rule trans heretic 125-12456-15-2345-24-14
rule trans heretofore 5-125-2345-135-123456-15
rule trans hereupon 5-125-45-136
rule trans incoherence 35-14-135-125-12456-56-15
rule trans incoherent 35-14-135-125-12456-26-2345
rule trans inhered 35-125-12456-1246
rule trans inherent 35-125-12456-26-2345

## know
uses not_modifier_< - rule trans know 5-13

rule trans lucknow 123-136-14-13-1345-246

## lord
uses not_modifier_< - rule trans lord 5-123
rule trans chlordane 16-123-135-1235-145-1-1345-15

## many
uses not_modifier_< - rule trans many 456-134

## mother
uses not_modifier_< - rule trans mother 5-134
rule trans chemotherapy 16-15-134-135-2346-1235-1-1234-13456

## name   10.7.5
uses not_modifier_< - rule trans name 5-1345

rule trans filename 124-24-123-15-5-1345
rule trans forename 123456-15-5-1345
rule trans ornament 135-1235-1345-1-56-2345
rule trans rename 1235-15-5-1345
rule trans tournament 2345-1256-1235-1345-1-56-2345
rule trans unamended 136-1345-1-134-26-145-1246
rule trans vietnamese 1236-24-15-2345-1345-1-134-15-234-15

## one   10.7.6
uses not_modifier_< - rule trans one 5-135

use word_mid_end_+ word_mid_end_-
rule trans oned 135-1345-1246
rule trans onent 135-1345-26-2345
rule trans oner 135-1345-12456
rule trans onest 135-1345-15-34

use word_whole_begin_+ word_whole_begin_-
rule trans abalone 1-12-1-123-135-1345-15
rule trans alcyone 1-123-14-13456-135-1345-15
rule trans anemone 1-1345-15-134-135-1345-15
rule trans antigone 1-1345-2345-24-1245-135-1345-15
rule trans austronesian 1-136-34-1235-135-1345-15-234-24-1-1345
rule trans baroness 12-345-135-56-234
rule trans baronet 12-345-135-1345-15-2345
rule trans bayonet 12-1-13456-135-1345-15-2345
rule trans boone 12-135-135-1345-15
rule trans cantonese 14-1-1345-2345-135-1345-15-234-15
rule trans citronella 14-24-2345-1235-135-1345-15-123-123-1
rule trans colonel 14-135-123-135-1345-15-123
rule trans coronet 14-135-1235-135-1345-15-2345
rule trans deaconess 145-2-14-135-56-234
rule trans dishonest 256-125-5-135-34
rule trans donegal 145-135-1345-15-1245-1-123
rule trans doonesbury 145-135-135-1345-15-234-12-136-1235-13456
rule trans erroneous 12456-1235-135-1345-15-1256-234
rule trans giorgione 1245-24-135-1235-1245-24-135-1345-15
rule trans hermione 125-12456-134-24-135-1345-15
rule trans honecker 125-135-1345-15-14-13-12456
rule trans honest 125-5-135-34
rule trans indonesia 35-145-135-1345-15-234-24-1
rule trans ionesco 24-135-1345-15-234-14-135
rule trans krone 13-1235-135-1345-15
rule trans leonel 123-15-135-1345-15-123
rule trans lionel 123-24-135-1345-15-123
rule trans lioness 123-24-135-56-234
rule trans looney 123-135-135-1345-15-13456
rule trans luncheonette 123-136-1345-16-15-135-1345-15-2345-2345-15
rule trans marchioness 134-345-16-24-135-56-234
rule trans marionette 134-345-24-135-1345-15-2345-2345-15
rule trans micronesia 134-24-14-1235-135-1345-15-234-24-1
rule trans minestrone 134-35-15-34-1235-135-1345-15
rule trans monet 134-135-1345-15-2345
rule trans mooney 134-135-135-1345-15-13456
rule trans nonempty 1345-135-1345-15-134-1234-2345-13456
rule trans nonessential 1345-135-1345-15-234-234-26-2345-24-1-123
rule trans nonevent 1345-135-1345-15-1236-26-2345
rule trans nonexempt 1345-135-1345-15-1346-15-134-1234-2345
rule trans nonexistence 1345-135-1345-15-1346-24-34-56-15
rule trans nonexistent 1345-135-1345-15-1346-24-34-26-2345
rule trans oneal 135-1345-2-123
rule trans onega 135-1345-15-1245-1
rule trans onegin 135-1345-15-1245-35
rule trans oneida 135-1345-15-24-145-1
rule trans onerous 135-1345-12456-1256-234
rule trans peritonea 1234-12456-24-2345-135-1345-15-1
rule trans peritoneum 1234-12456-24-2345-135-1345-15-136-134
rule trans persephone 1234-12456-234-15-1234-125-135-1345-15
rule trans phoneme 1234-125-135-1345-15-134-15
rule trans phonemic 1234-125-135-1345-15-134-24-14
rule trans phonetic 1234-125-135-1345-15-2345-24-14
rule trans pioneer 1234-24-135-1345-15-12456
rule trans rooney 1235-135-135-1345-15-13456
rule trans salmonella 234-1-123-134-135-1345-15-123-123-1
rule trans shoshone 146-135-146-135-1345-15
rule trans spumone 234-1234-136-134-135-1345-15
rule trans veronese 1236-12456-135-1345-15-234-15

rule trans kroner 13-1235-135-1345-12456
rule trans monetarily 134-5-135-2345-345-24-123-13456
rule trans monetarism 134-5-135-2345-345-24-234-134
rule trans monetary 134-5-135-2345-345-13456

## ought
uses not_modifier_< - rule trans ought 5-1256

## part
uses not_modifier_< - rule trans part 5-1234

rule trans parthenogenesis 1234-345-2346-1345-135-1245-26-15-234-24-234
rule trans parthenon 1234-345-2346-1345-135-1345
rule trans parthia 1234-345-1456-24-1

## question
uses not_modifier_< - rule trans question 5-12345

## right
uses not_modifier_< - rule trans right 5-1235

## some   10.7.7
uses not_modifier_< - rule trans some 5-234

rule trans blossomed 12-123-135-234-234-135-134-1246
rule trans gasometer 1245-1-234-135-134-15-2345-12456
rule trans isometric 24-234-135-134-15-2345-1235-24-14
rule trans ransomed 1235-1-1345-234-135-134-1246
rule trans somersault 234-135-134-12456-234-1-136-123-2345
rule trans somerset 234-135-134-12456-234-15-2345
rule trans unbosomed 136-1345-12-135-234-135-134-1246

## spirit
uses not_modifier_< - rule trans spirit 456-234

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

## their
uses not_modifier_< - rule trans their 456-2346

## these   10.7.2
uses not_modifier_< - rule trans these 45-2346

use word_whole_begin_+ word_whole_begin_-
rule trans antitheses 1-1345-2345-24-2346-234-15-234
rule trans hypotheses 125-13456-1234-135-2346-234-15-234
rule trans parentheses 1234-345-26-2346-234-15-234
rule trans syntheses 234-13456-1345-2346-234-15-234
rule trans theses 2346-234-15-234
rule trans theseus 2346-234-15-136-234

## those   10.7.2
uses not_modifier_< - rule trans those 45-1456

rule trans spathose 234-1234-1-1456-135-234-15
rule trans thoseby 1456-135-234-15-12-13456

## through
uses not_modifier_< - rule trans through 5-1456

## time   10.7.8
uses not_modifier_< - rule trans time 5-2345

rule trans altimeter 1-123-2345-24-134-15-2345-12456
rule trans centime 14-26-2345-24-134-15
rule trans mortimer 134-135-1235-2345-24-134-12456
rule trans multimedia 134-136-123-2345-24-134-1246-24-1
rule trans presentiment 1234-1235-15-234-26-2345-24-56-2345
rule trans sentiment 234-26-2345-24-56-2345
rule trans unsentimental 136-1345-234-26-2345-24-56-2345-1-123

## under   10.7.9
match trans (^|%[_~]%<*)|![ao] under -  - 5-136 -   10.7.9

rule trans underived 136-1345-145-12456-24-1236-1246
rule trans underogatory 136-1345-145-12456-135-1245-1-2345-135-1235-13456

## upon   10.7.2
uses not_modifier_< - rule trans upon 45-136

rule trans dupont 145-136-1234-135-1345-2345

## where
uses not_modifier_< - rule trans where 5-156

rule trans where'er 156-12456-15-3-12456
rule trans whereupon 5-156-45-136
rule trans wherever 156-12456-5-15

## whose
uses not_modifier_< - rule trans whose 45-156

## word
uses not_modifier_< - rule trans word 45-2456

#3 work
uses not_modifier_< - rule trans work 5-2456

#3 world
uses not_modifier_< - rule trans world 456-2456

## young
uses not_modifier_< - rule trans young 5-13456

use


########################################
#   10.8   Final-Letter Groupsigns
#   BOTH ALPHABETIC AND NOT
#   letter* no capital -
#   list
########################################

filter final_letter_groupsign_+   %a             -
filter final_letter_groupsign_-   @[LETTER_<-]   -

#   watch for numeric mode
macro final_letter_init
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans $1 $2
match -backward init - \M\;$2;\M -   (^|!\;3456;)@[LETTER_<-]+ \;$2; -
eom

use word_whole_begin_+ word_whole_begin_-

## ance
@final_letter_init ance 46-15

rule trans fiance 124-24-1-1345-14-15   should be fiancé

## ence
@final_letter_init ence 56-15

rule trans electroencephalogram 15-123-15-14-2345-1235-135-26-14-15-1234-125-1-123-135-1245-1235-1-134
rule trans electroencephalograph 15-123-15-14-2345-1235-135-26-14-15-1234-125-1-123-135-1245-1235-1-1234-125

## ful
@final_letter_init ful 56-123

rule trans overfull 135-1236-12456-124-136-123-123

use word_whole_+ word_whole_-

## ity   10.8.3
@final_letter_init ity 56-13456

rule trans biscuity 12-24-234-14-136-24-2345-13456
rule trans dacoity 145-1-14-135-24-2345-13456
rule trans fruity 124-1235-136-24-2345-13456
rule trans hoity-toity 124-135-24-2345-13456-36-2345-135-24-2345-13456
rule trans rabbity 1235-1-23-24-2345-13456
rule trans pityard 1234-24-2345-13456-345-145

## less
@final_letter_init less 46-234

use word_whole_begin_+ word_whole_begin_-

## ment
@final_letter_init ment 56-2345

rule trans aforementioned 1-123456-15-134-26-56-1345-1246
rule trans unmentionable 136-1345-134-26-56-1345-1-12-123-15

## ness   10.8.4
@final_letter_init ness 56-234

rule trans chieftainess 16-24-15-124-2345-1-35-15-234-234
rule trans citizeness 14-24-2345-24-1356-26-15-234-234
rule trans heatheness 125-2-2346-1345-15-234-234

#   overrides in
uses final_letter_groupsign_+ final_letter_groupsign_- rule trans iness 24-56-234

## ong
@final_letter_init ong 56-1245

rule trans moongod 134-135-135-1345-1245-135-145
rule trans nongaseous 1345-135-1345-1245-1-234-15-1256-234
rule trans nongovernmental 1345-135-1345-1245-135-1236-12456-1345-56-2345-1-123

## ound
@final_letter_init ound 46-145

## ount
@final_letter_init ount 46-2345

#3 sion
@final_letter_init sion 46-1345

## tion
@final_letter_init tion 56-1345

rule trans cation 14-1-2345-24-135-1345

use


########################################
#   10.9   Shortforms   not including 10.9.3
#   ALPHABETIC CONTRACTION
#   any - any
#   list
########################################

filter shortform_+   @[WORD_<+]   @[APOSS_+]@[WORD_>+]
filter shortform_-   @[WORD_<-]   @[APOSS_-]@[WORD_>-]

use shortform_+ shortform_-
rule trans about 1-12
rule trans above 1-12-1236
rule trans according 1-14
rule trans across 1-14-1235
rule trans after 1-124
rule trans afternoon 1-124-1345
rule trans afterward 1-124-2456
rule trans again 1-1245
rule trans against 1-1245-34
uses word_whole_+ word_whole_- rule trans almost 1-123-134
rule trans already 1-123-1235
rule trans also 1-123
rule trans although 1-123-1456
rule trans altogether 1-123-2345
rule trans always 1-123-2456
rule trans because 23-14
rule trans before 23-124
rule trans behind 23-125
rule trans below 23-123
rule trans beneath 23-1345
rule trans beside 23-234
rule trans between 23-2345
rule trans beyond 23-13456
rule trans conceive 25-14-1236
rule trans conceiving 25-14-1236-1245
rule trans could 14-145
rule trans deceive 145-14-1236
rule trans deceiving 145-14-1236-1245
rule trans declare 145-14-123
rule trans declaring 145-14-123-1245
rule trans either 15-24
rule trans herself 125-12456-124
rule trans him 125-134
rule trans himself 125-134-124
rule trans immediate 24-134-134
rule trans its 1346-234
rule trans itself 1346-124
rule trans much 134-16
rule trans must 134-34
rule trans myself 134-13456-124
rule trans necessary 1345-15-14
rule trans neither 1345-15-24
rule trans oneself 5-135-124
rule trans ourselves 1256-1235-1236-234
rule trans paid 1234-145
rule trans perceive 1234-12456-14-1236
rule trans perceiving 1234-12456-14-1236-1245
rule trans perhaps 1234-12456-125
rule trans receive 1235-14-1236
rule trans receiving 1235-14-1236-1245
rule trans rejoice 1235-245-14
rule trans rejoicing 1235-245-14-1245
rule trans said 234-145
rule trans should 146-145
rule trans such 234-16
rule trans themselves 2346-134-1236-234
rule trans thyself 1456-13456-124
rule trans today 2345-145
rule trans together 2345-1245-1235
rule trans tomorrow 2345-134
rule trans tonight 2345-1345
rule trans would 2456-145
rule trans your 13456-1235
rule trans yourself 13456-1235-124
rule trans yourselves 13456-1235-1236-234
use


#   10.9.5

macro contraction
rule premode $1 \;56;$1
rule premode $2 \;56;$2
rule premode $3 \;56;$3
rule premode $4 \;56;$4
rule premode $5 \;56;$5
rule premode $6 \;56;$6
rule premode $7 \;56;$7
rule premode $8 \;56;$8
rule premode $9 \;56;$9
eom

use word_whole_+ word_whole_-
#contraction ab Ab AB abs Abs ABS ab's Ab's AB'S                    # about
@contraction abv Abv ABV abvs Abvs ABVS abv's Abv's ABV'S           # above
@contraction ac Ac AC acs Acs ACS ac's Ac's AC'S                    # according
@contraction acr Acr ACR acrs Acrs ACRS acr's Acr's ACR'S           # across
@contraction af Af AF afs Afs AFS af's Af's AF'S                    # after
@contraction afn Afn AFN afns Afns AFNS afn's Afn's AFN'S           # afternoon
@contraction afw Afw AFW afws Afws AFWS afw's Afw's AFW'S           # afterward
@contraction ag Ag AG ags Ags AGS ag's Ag's AG'S                    # again
#contraction alm Alm ALM alms Alms ALMS alm's Alm's ALM'S           # almost
@contraction alr Alr ALR alrs Alrs ALRS alr's Alr's ALR'S           # already
@contraction al Al AL als Als ALS al's Al's AL'S                    # also
@contraction alt Alt ALT alts Alts ALTS alt's Alt's ALT'S           # altogether
@contraction alw Alw ALW alws Alws ALWS alw's Alw's ALW'S           # always
@contraction bl Bl BL bls Bls BLS bl's Bl's BL'S                    # blind
@contraction brl Brl BRL brls Brls BRLS brl's Brl's BRL'S           # braille
@contraction cd Cd CD cds Cds CDS cd's Cd's CD'S                    # could
@contraction dcv Dcv DCV dcvs Dcvs DCVS dcv's Dcv's DCV'S           # deceive
@contraction dcvg Dcvg DCVG dcvgs Dcvgs DCVGS dcvg's Dcvg's DCVG'S  # deceiving
@contraction dcl Dcl DCL dcls Dcls DCLS dcl's Dcl's DCL'S           # declare
@contraction dclg Dclg DCLG dclgs Dclgs DCLGS dclg's Dclg's DCLG'S  # declaring
@contraction ei Ei EI eis Eis EIS ei's Ei's EI'S                    # either
@contraction fr Fr FR frs Frs FRS fr's Fr's FR'S                    # friend
@contraction gd Gd GD gds Gds GDS gd's Gd's GD'S                    # good
@contraction grt Grt GRT grts Grts GRTS grt's Grt's GRT'S           # great
#contraction hm Hm HM hms Hms HMS hm's Hm's HM'S                    # him
@contraction hmf Hmf HMF hmfs Hmfs HMFS hmf's Hmf's HMF'S           # himself
@contraction imm Imm IMM imms Imms IMMS imm's Imm's IMM'S           # immediate
@contraction xs Xs XS xss Xss XSS xs's Xs's XS'S                    # its
@contraction xf Xf XF xfs Xfs XFS xf's Xf's XF'S                    # itself
@contraction lr Lr LR lrs Lrs LRS lr's Lr's LR'S                    # letter
@contraction ll Ll LL lls Lls LLS ll's Ll's LL'S                    # little
@contraction myf Myf MYF myfs Myfs MYFS myf's Myf's MYF'S           # myself
@contraction nec Nec NEC necs Necs NECS nec's Nec's NEC'S           # necessary
@contraction nei Nei NEI neis Neis NEIS nei's Nei's NEI'S           # neither
@contraction pd Pd PD pds Pds PDS pd's Pd's PD'S                    # paid
@contraction qk Qk QK qks Qks QKS qk's Qk's QK'S                    # quick
@contraction rcv Rcv RCV rcvs Rcvs RCVS rcv's Rcv's RCV'S           # receive
@contraction rcvg Rcvg RCVG rcvgs Rcvgs RCVGS rcvg's Rcvg's RCVG'S  # receiving
@contraction rjc Rjc RJC rjcs Rjcs RJCS rjc's Rjc's RJC'S           # rejoice
@contraction rjcg Rjcg RJCG rjcgs Rjcgs RJCGS rjcg's Rjcg's RJCG'S  # rejoicing
@contraction sd Sd SD sds Sds SDS sd's Sd's SD'S                    # said
@contraction td Td TD tds Tds TDS td's Td's TD'S                    # today
@contraction tgr Tgr TGR tgrs Tgrs TGRS tgr's Tgr's TGR'S           # together
@contraction tm Tm TM tms Tms TMS tm's Tm's TM'S                    # tomorrow
@contraction tn Tn TN tns Tns TNS tn's Tn's TN'S                    # tonight
@contraction wd Wd WD wds Wds WDS wd's Wd's WD'S                    # would
@contraction yr Yr YR yrs Yrs YRS yr's Yr's YR'S                    # your
@contraction yrf Yrf YRF yrfs Yrfs YRFS yrf's Yrf's YRF'S           # yourself
@contraction yrvs Yrvs YRVS yrvss Yrvss YRVSS yrvs's Yrvs's YRVS'S  # yourselves
use

# 10.9.3

# no words with "grt" or "brl" ... yet
filter shortform_letter_+   @[WORD_<+]%a*   @[LETTER_>+]*@[APOSS_+]@[WORD_>+]


filter shortform_letter_-   @[WORD_<-]@[LETTER_<-]*   @[LETTER_>-]*@[APOSS_-]@[WORD_>-]
use shortform_letter_+ shortform_letter_-

rule trans braille 12-1235-123
rule trans great 1245-1235-2345

match trans @[WORD_<+]%a* children (%c@[LETTER_>+]*)?@[APOSS_+]@[WORD_>+]  @[WORD_<-]@[LETTER_<-]* 16-1345 (%c@[LETTER_>-]*)?@[APOSS_-]@[WORD_>-]   10.9.3

pattern CONSONANT_>-  @[B_>-]|@[C_>-]|@[D_>-]|@[F_>-]|@[G_>-]|@[H_>-]|@[J_>-]|@[K_>-]|@[L_>-]|@[M_>-]|@[N_>-]|@[P_>-]|@[Q_>-]|@[R_>-]|@[S_>-]|@[T_>-]|@[V_>-]|@[W_>-]|@[X_>-]|@[Z_>-]

filter shortform_consonant_+   @[WORD_<+]      (%c@[LETTER_>+]*)?@[APOST_+]@[WORD_>+]
filter shortform_consonant_-   @[WORD_<-]      (@[CONSONANT_>-]@[LETTER_>-]*)?@[APOST_-]@[WORD_>-]
use shortform_consonant_+ shortform_consonant_-

rule trans blind 12-123
rule trans first 124-34
rule trans good 1245-145
rule trans friend 124-1235
rule trans letter 123-1235
rule trans little 123-123
rule trans quick 12345-13

rule trans blinds 12-123-234
rule trans firsts 124-34-234
rule trans goods 1245-145-234
rule trans friends 124-1235-234
rule trans letters 123-1235-234
rule trans littles 123-123-234
rule trans quicks 12345-13-234


########################################
#   Appendex 1
#   ALPHABETIC CONTRACTION
#   any - any
#   list
########################################

use word_whole_+ word_whole_-
rule trans abouts 1-12-1256-2345-234
rule trans almosts 1-123-134-135-34-234
rule trans hims 125-24-134-234

macro contraction_aah
rule premode $1 \;56;$1
rule premode $2 \;56;$2
rule premode $3 \;56;$3
rule premode $4 \;56;$4
rule premode $5 \;56;$5
rule premode $6 \;56;$6
eom

@contraction_aah ab Ab AB ab's Ab's AB'S        # about
@contraction_aah alm Alm ALM alm's Alm's ALM'S  # almost
@contraction_aah hm Hm HM hm's Hm's HM'S        # him

use shortform_+ shortform_-
rule trans 'twould  3-2345-2456-145
rule trans 'twould've  3-2345-2456-145-3-1236-15
rule trans 'twoulda  3-2345-2456-145-1
rule trans 'twouldn't  3-2345-2456-145-1345-3-2345
rule trans 'twouldn't've  3-2345-2456-145-1345-3-2345-3-1236-15
rule trans aboutface  1-12-124-1-14-15
rule trans aboutfaced  1-12-124-1-14-1246
rule trans aboutfacer  1-12-124-1-14-12456
rule trans aboutfacing  1-12-124-1-14-346
rule trans aboutturn  1-12-2345-136-1235-1345
rule trans aboutturned  1-12-2345-136-1235-1345-1246
rule trans aboveboard  1-12-1236-12-135-345-145
rule trans aboveground  1-12-1236-1245-1235-46-145
rule trans abovementioned  1-12-1236-134-26-56-1345-1246
rule trans accordingly  1-14-123-13456
rule trans aforesaid  1-123456-15-234-145
rule trans afterbattle  1-124-12-1-2345-2345-123-15
rule trans afterbirth  1-124-12-24-1235-1456
rule trans afterbreakfast  1-124-12-1235-2-13-124-1-34
rule trans afterburn  1-124-12-136-1235-1345
rule trans afterburned  1-124-12-136-1235-1345-1246
rule trans afterburner  1-124-12-136-1235-1345-12456
rule trans afterburning  1-124-12-136-1235-1345-346
rule trans aftercare  1-124-14-345-15
rule trans afterclap  1-124-14-123-1-1234
rule trans aftercoffee  1-124-14-12356-124-15-15
rule trans afterdamp  1-124-145-1-134-1234
rule trans afterdark  1-124-145-345-13
rule trans afterdeck  1-124-145-15-14-13
rule trans afterdinner  1-124-145-35-1345-12456
rule trans afterflow  1-124-124-123-246
rule trans aftergame  1-124-1245-1-134-15
rule trans afterglow  1-124-1245-123-246
rule trans afterguard  1-124-1245-136-345-145
rule trans afterhatch  1-124-125-1-2345-16
rule trans afterhatches  1-124-125-1-2345-16-15-234
rule trans afterhour  1-124-125-1256-1235
rule trans afterlife  1-124-123-24-124-15
rule trans afterlight  1-124-123-24-126-2345
rule trans afterlives  1-124-123-24-1236-15-234
rule trans afterlunch  1-124-123-136-1345-16
rule trans afterlunches  1-124-123-136-1345-16-15-234
rule trans aftermarket  1-124-134-345-13-15-2345
rule trans aftermatch 1-124-134-1-2345-16
rule trans aftermatches  1-124-134-1-2345-16-15-234
rule trans aftermath  1-124-134-1-1456
rule trans aftermeeting  1-124-134-15-15-2345-346
rule trans aftermidday  1-124-134-24-145-5-145
rule trans aftermidnight  1-124-134-24-145-1345-24-126-2345
rule trans aftermost  1-124-134-135-34
rule trans afternoontea  1-124-1345-2345-15-1
rule trans afterpain  1-124-1234-1-35
rule trans afterparties  1-124-5-1234-24-15-234
rule trans afterparty  1-124-5-1234-13456
rule trans afterpiece  1-124-1234-24-15-14-15
rule trans afterplay  1-124-1234-123-1-13456
rule trans aftersale  1-124-234-1-123-15
rule trans afterschool  1-124-234-16-135-135-123
rule trans aftersensation  1-124-234-26-234-1-56-1345
rule trans aftershave  1-124-146-1-1236-15
rule trans aftershock  1-124-146-135-14-13
rule trans aftershow  1-124-146-246
rule trans aftershower  1-124-146-246-12456
rule trans aftersupper  1-124-234-136-1234-1234-12456
rule trans aftertaste  1-124-2345-1-34-15
rule trans aftertax  1-124-2345-1-1346
rule trans aftertaxes  1-124-2345-1-1346-15-234
rule trans aftertea  1-124-2345-15-1
rule trans aftertheatre  1-124-2346-1-2345-1235-15
rule trans afterthought  1-124-1456-5-1256
rule trans aftertime  1-124-5-2345
rule trans aftertreatment  1-124-2345-1235-2-2345-56-2345
rule trans afterword  1-124-45-2456
rule trans afterwork  1-124-5-2456
rule trans afterworld  1-124-456-2456
rule trans apperceive  1-1234-1234-12456-14-1236
rule trans apperceived  1-1234-1234-12456-14-1236-145
rule trans apperceiver  1-1234-1234-12456-14-1236-1235
rule trans apperceiving  1-1234-1234-12456-14-1236-1245
rule trans archdeceiver  345-16-145-14-1236-1235
rule trans beforehand  23-124-125-12346
rule trans befriend  23-124-1235
rule trans behindhand  23-125-125-12346
rule trans belittle  23-123-123
rule trans belittled  23-123-123-145
rule trans belittlement  23-123-123-56-2345
rule trans belittler  23-123-123-1235
rule trans belowdeck  23-123-145-15-14-13
rule trans belowground  23-123-1245-1235-46-145
rule trans belowmentioned  23-123-134-26-56-1345-1246
rule trans beneathdeck  23-1345-145-15-14-13
rule trans beneathground  23-1345-1245-1235-46-145
rule trans betweendeck  23-2345-145-15-14-13
rule trans betweentime  23-2345-5-2345
rule trans betweenwhile  23-2345-156-24-123-15
rule trans blindfish  12-123-124-24-146
rule trans blindfishes  12-123-124-24-146-15-234
rule trans blindfold  12-123-124-135-123-145
rule trans blindfolded  12-123-124-135-123-145-1246
rule trans blindfolder  12-123-124-135-123-145-12456
rule trans blindfolding  12-123-124-135-123-145-346
rule trans blindly  12-123-123-13456
rule trans blindman  12-123-134-1-1345
rule trans blindmen  12-123-134-26
rule trans blindness  12-123-56-234
rule trans blindnesses  12-123-56-234-15-234
rule trans blindside  12-123-234-24-145-15
rule trans blindsided  12-123-234-24-145-1246
rule trans blindsider  12-123-234-24-145-12456
rule trans blindsiding  12-123-234-24-145-346
rule trans blindsight  12-123-234-24-126-2345
rule trans blindstories  12-123-34-135-1235-24-15-234
rule trans blindstory  12-123-34-135-1235-13456
rule trans blindworm  12-123-2456-135-1235-134
rule trans bloodletter  12-123-135-135-145-123-1235
rule trans boyfriend  12-135-13456-124-1235
rule trans brailled  12-1235-123-145
rule trans brailler  12-1235-123-1235
rule trans braillewriter  12-1235-123-2456-1235-24-2345-12456
rule trans braillewriting  12-1235-123-2456-1235-24-2345-346
rule trans brailley  12-1235-123-13456
rule trans brainchildren  12-1235-1-35-16-1345
rule trans chainletter  16-1-35-123-1235
rule trans children'swear  16-1345-3-234-2456-15-345
rule trans colorblind  14-135-123-135-1235-12-123
rule trans colorblindness  14-135-123-135-1235-12-123-56-234
rule trans colorblindnesses  14-135-123-135-1235-12-123-56-234-15-234
rule trans colourblind  14-135-123-1256-1235-12-123
rule trans colourblindness  14-135-123-1256-1235-12-123-56-234
rule trans colourblindnesses  14-135-123-1256-1235-12-123-56-234-15-234
rule trans conceived  25-14-1236-145
rule trans conceiver  25-14-1236-1235
rule trans could've  14-145-3-1236-15
rule trans coulda  14-145-1
rule trans couldest  14-145-15-34
rule trans couldn't  14-145-1345-3-2345
rule trans couldn't've  14-145-1345-3-2345-3-1236-15
rule trans couldst  14-145-34
rule trans deafblind  145-2-124-12-123
rule trans deafblindness  145-2-124-12-123-56-234
rule trans deafblindnesses  145-2-124-12-123-56-234-15-234
rule trans deceived  145-14-1236-145
rule trans deceiver  145-14-1236-1235
rule trans declared  145-14-123-145
rule trans declarer  145-14-123-1235
rule trans defriend  145-15-124-1235
rule trans do-it-yourselfer  145-36-1346-36-13456-1235-124-12456
rule trans doublequick  145-1256-12-123-15-12345-13
rule trans eastabout  15-1-34-1-12
rule trans feelgood  124-15-15-123-1245-145
rule trans feetfirst  124-15-15-2345-124-34
rule trans firstaid  124-34-1-24-145
rule trans firstaider  124-34-1-24-145-12456
rule trans firstborn  124-34-12-135-1235-1345
rule trans firstclass  124-34-14-123-1-234-234
rule trans firstclasses  124-34-14-123-1-234-234-15-234
rule trans firstday  124-34-5-145
rule trans firstdayer  124-34-5-145-12456
rule trans firstfruit  124-34-124-1235-136-24-2345
rule trans firstfruiting  124-34-124-1235-136-24-2345-346
rule trans firstgeneration  124-34-1245-26-12456-1-56-1345
rule trans firsthand  124-34-125-12346
rule trans firsthanded  124-34-125-12346-1246
rule trans firstling  124-34-123-346
rule trans firstly  124-34-123-13456
rule trans firstness  124-34-56-234
rule trans firstnight  124-34-1345-24-126-2345
rule trans firstnighter  124-34-1345-24-126-2345-12456
rule trans firstrate  124-34-1235-1-2345-15
rule trans firstrated  124-34-1235-1-2345-1246
rule trans firstrating  124-34-1235-1-2345-346
rule trans firststring  124-34-34-1235-346
rule trans forasmuch  123456-1-234-134-16
rule trans foresaid  123456-15-234-145
rule trans fosterchildren  124-135-34-12456-16-1345
rule trans friendless  124-1235-46-234
rule trans friendlessness  124-1235-46-234-56-234
rule trans friendlessnesses  124-1235-46-234-56-234-15-234
rule trans friendlier  124-1235-123-24-12456
rule trans friendlies  124-1235-123-24-15-234
rule trans friendliest  124-1235-123-24-15-34
rule trans friendliness  124-1235-123-24-56-234
rule trans friendlinesses  124-1235-123-24-56-234-15-234
rule trans friendly  124-1235-123-13456
rule trans friendship  124-1235-146-24-1234
rule trans gadabout  1245-1-145-1-12
rule trans gainsaid  1245-1-35-234-145
rule trans galfriend  1245-1-123-124-1235
rule trans gentlemanfriend  1245-26-2345-123-15-134-1-1345-124-1235
rule trans gentlemenfriends  1245-26-2345-123-15-134-26-124-1235-234
rule trans girlfriend  1245-24-1235-123-124-1235
rule trans godchildren  1245-135-145-16-1345
rule trans goodafternoon  1245-145-1-124-1345
rule trans goodby  1245-145-12-13456
rule trans goodbye  1245-145-12-13456-15
rule trans goodbyeing  1245-145-12-13456-15-346
rule trans goodbying  1245-145-12-13456-346
rule trans goodday  1245-145-5-145
rule trans gooder  1245-145-12456
rule trans goodest  1245-145-15-34
rule trans goodevening  1245-145-15-1236-26-346
rule trans goodfellow  1245-145-124-15-123-123-246
rule trans goodfellowship  1245-145-124-15-123-123-246-146-24-1234
rule trans goodhearted  1245-145-125-15-345-2345-1246
rule trans goodheartedly  1245-145-125-15-345-2345-1246-123-13456
rule trans goodheartedness  1245-145-125-15-345-2345-1246-56-234
rule trans goodhumor  1245-145-125-136-134-135-1235
rule trans goodhumored  1245-145-125-136-134-135-1235-1246
rule trans goodhumoredly  1245-145-125-136-134-135-1235-1246-123-13456
rule trans goodhumoredness  1245-145-125-136-134-135-1235-1246-56-234
rule trans goodhumorednesses  1245-145-125-136-134-135-1235-1246-56-234-15-234
rule trans goodhumour  1245-145-125-136-134-1256-1235
rule trans goodhumoured  1245-145-125-136-134-1256-1235-1246
rule trans goodhumouredly  1245-145-125-136-134-1256-1235-1246-123-13456
rule trans goodhumouredness  1245-145-125-136-134-1256-1235-1246-56-234
rule trans goodhumourednesses  1245-145-125-136-134-1256-1235-1246-56-234-15-234
rule trans goodie  1245-145-24-15
rule trans goodish  1245-145-24-146
rule trans goodlier  1245-145-123-24-12456
rule trans goodliest  1245-145-123-24-15-34
rule trans goodliness  1245-145-123-24-56-234
rule trans goodlook  1245-145-123-135-135-13
rule trans goodlooker  1245-145-123-135-135-13-12456
rule trans goodlooking  1245-145-123-135-135-13-346
rule trans goodly  1245-145-123-13456
rule trans goodman  1245-145-134-1-1345
rule trans goodmen  1245-145-134-26
rule trans goodmorning  1245-145-134-135-1235-1345-346
rule trans goodnature  1245-145-1345-1-2345-136-1235-15
rule trans goodnatured  1245-145-1345-1-2345-136-1235-1246
rule trans goodnaturedly  1245-145-1345-1-2345-136-1235-1246-123-13456
rule trans goodnaturedness  1245-145-1345-1-2345-136-1235-1246-56-234
rule trans goodness  1245-145-56-234
rule trans goodnesses  1245-145-56-234-15-234
rule trans goodnight  1245-145-1345-24-126-2345
rule trans goodsize  1245-145-234-24-1356-15
rule trans goodsized  1245-145-234-24-1356-1246
rule trans goodtempered  1245-145-2345-15-134-1234-12456-1246
rule trans goodtemperedly  1245-145-2345-15-134-1234-12456-1246-123-13456
rule trans goodtime  1245-145-5-2345
rule trans goodun  1245-145-136-1345
rule trans goodwife  1245-145-2456-24-124-15
rule trans goodwill  1245-145-2456-24-123-123
rule trans goodwilled  1245-145-2456-24-123-123-1246
rule trans goodwives  1245-145-2456-24-1236-15-234
rule trans goody  1245-145-13456
rule trans goodyear  1245-145-13456-15-345
rule trans grandchildren  1245-1235-12346-16-1345
rule trans greataunt  1245-1235-2345-1-136-1345-2345
rule trans greatbatch  1245-1235-2345-12-1-2345-16
rule trans greatcircle  1245-1235-2345-14-24-1235-14-123-15
rule trans greatcoat  1245-1235-2345-14-135-1-2345
rule trans greaten  1245-1235-2345-26
rule trans greatened  1245-1235-2345-26-1246
rule trans greatener  1245-1235-2345-26-12456
rule trans greatening  1245-1235-2345-26-346
rule trans greater  1245-1235-2345-12456
rule trans greatest  1245-1235-2345-15-34
rule trans greatgrandaunt  1245-1235-2345-1245-1235-12346-1-136-1345-2345
rule trans greatgrandchild  1245-1235-2345-1245-1235-12346-16-24-123-145
rule trans greatgrandchildren  1245-1235-2345-1245-1235-12346-16-1345
rule trans greatgranddad  1245-1235-2345-1245-1235-12346-145-1-145
rule trans greatgranddaughter  1245-1235-2345-1245-1235-12346-145-1-136-126-2345-12456
rule trans greatgrandfather  1245-1235-2345-1245-1235-12346-5-124
rule trans greatgrandfatherhood  1245-1235-2345-1245-1235-12346-5-124-125-135-135-145
rule trans greatgrandma  1245-1235-2345-1245-1235-12346-134-1
rule trans greatgrandmother  1245-1235-2345-1245-1235-12346-5-134
rule trans greatgrandmotherhood  1245-1235-2345-1245-1235-12346-5-134-125-135-135-145
rule trans greatgrandnephew  1245-1235-2345-1245-1235-12346-1345-15-1234-125-15-2456
rule trans greatgrandniece  1245-1235-2345-1245-1235-12346-1345-24-15-14-15
rule trans greatgrandpa  1245-1235-2345-1245-1235-12346-1234-1
rule trans greatgrandparent  1245-1235-2345-1245-1235-12346-1234-345-26-2345
rule trans greatgrandparenthood  1245-1235-2345-1245-1235-12346-1234-345-26-2345-125-135-135-145
rule trans greatgrandson  1245-1235-2345-1245-1235-12346-234-135-1345
rule trans greatgranduncle  1245-1235-2345-1245-1235-12346-136-1345-14-123-15
rule trans greathearted  1245-1235-2345-125-15-345-2345-1246
rule trans greatheartedly  1245-1235-2345-125-15-345-2345-1246-123-13456
rule trans greatheartedness  1245-1235-2345-125-15-345-2345-1246-56-234
rule trans greatheartednesses  1245-1235-2345-125-15-345-2345-1246-56-234-15-234
rule trans greatly  1245-1235-2345-123-13456
rule trans greatnephew  1245-1235-2345-1345-15-1234-125-15-2456
rule trans greatness  1245-1235-2345-56-234
rule trans greatnesses  1245-1235-2345-56-234-15-234
rule trans greatniece  1245-1235-2345-1345-24-15-14-15
rule trans greatsword  1245-1235-2345-234-45-2456
rule trans greatuncle  1245-1235-2345-136-1345-14-123-15
rule trans guyfriend  1245-136-13456-124-1235
rule trans hateletter  125-1-2345-15-123-1235
rule trans headfirst  125-2-145-124-34
rule trans hereabout  5-125-1-12
rule trans hereafter  5-125-1-124
rule trans hereagain  5-125-1-1245
rule trans hereagainst  5-125-1-1245-34
rule trans hereinabove  5-125-35-1-12-1236
rule trans hereinafter  5-125-35-1-124
rule trans hereinagain  5-125-35-1-1245
rule trans highlypaid  125-24-126-123-13456-1234-145
rule trans himbo  125-134-12-135
rule trans himboes  125-134-12-135-15-234
rule trans illpaid  24-123-123-1234-145
rule trans immediately  24-134-134-123-13456
rule trans immediateness  24-134-134-56-234
rule trans inasmuch  35-1-234-134-16
rule trans insomuch  35-234-135-134-16
rule trans knockabout  13-1345-135-14-13-1-12
rule trans ladyfriend  123-1-145-13456-124-1235
rule trans layabout  123-1-13456-1-12
rule trans letterbodies  123-1235-12-135-145-24-15-234
rule trans letterbody  123-1235-12-135-145-13456
rule trans letterbomb  123-1235-12-135-134-12
rule trans letterbombed  123-1235-12-135-134-12-1246
rule trans letterbomber  123-1235-12-135-134-12-12456
rule trans letterbombing  123-1235-12-135-134-12-346
rule trans letterbox  123-1235-12-135-1346
rule trans letterboxed  123-1235-12-135-1346-1246
rule trans letterboxer  123-1235-12-135-1346-12456
rule trans letterboxes  123-1235-12-135-1346-15-234
rule trans letterboxing  123-1235-12-135-1346-346
rule trans lettered  123-1235-1246
rule trans letterer  123-1235-12456
rule trans letterform  123-1235-123456-134
rule trans letterhead  123-1235-125-2-145
rule trans letterheading  123-1235-125-2-145-346
rule trans lettering  123-1235-346
rule trans letterman  123-1235-134-1-1345
rule trans lettermen  123-1235-134-26
rule trans letteropener  123-1235-135-1234-26-12456
rule trans letterperfect  123-1235-1234-12456-124-15-14-2345
rule trans letterpress  123-1235-1234-1235-15-234-234
rule trans letterpressed  123-1235-1234-1235-15-234-234-1246
rule trans letterpresses  123-1235-1234-1235-15-234-234-15-234
rule trans letterpressing  123-1235-1234-1235-15-234-234-346
rule trans letterquality  123-1235-12345-136-1-123-56-13456
rule trans letterspace  123-1235-234-1234-1-14-15
rule trans letterspaced  123-1235-234-1234-1-14-1246
rule trans letterspacing  123-1235-234-1234-1-14-346
rule trans lettertext  123-1235-2345-15-1346-2345
rule trans littled  123-123-145
rule trans littleneck  123-123-1345-15-14-13
rule trans littleness  123-123-56-234
rule trans littlenesses  123-123-56-234-15-234
rule trans littler  123-123-1235
rule trans littlest  123-123-34
rule trans lovechildren  123-135-1236-15-16-1345
rule trans loveletter  123-135-1236-15-123-1235
rule trans lowlypaid  123-246-123-13456-1234-145
rule trans manfriend  134-1-1345-124-1235
rule trans menfriends  134-26-124-1235-234
rule trans midafternoon  134-24-145-1-124-1345
rule trans misbraille  134-24-234-12-1235-123
rule trans misbrailled  134-24-234-12-1235-123-145
rule trans misperceive  134-24-234-1234-12456-14-1236
rule trans misperceived  134-24-234-1234-12456-14-1236-145
rule trans misperceiver  134-24-234-1234-12456-14-1236-1235
rule trans misperceiving  134-24-234-1234-12456-14-1236-1245
rule trans missaid  134-24-234-234-145
rule trans morningafter  134-135-1235-1345-346-1-124
rule trans muchly  134-16-123-13456
rule trans muchness  134-16-56-234
rule trans must've  134-34-3-1236-15
rule trans musta  134-34-1
rule trans mustard  134-34-345-145
rule trans mustier  134-34-24-12456
rule trans mustiest  134-34-24-15-34
rule trans mustily  134-34-24-123-13456
rule trans mustiness  134-34-24-56-234
rule trans mustn't  134-34-1345-3-2345
rule trans mustn't've  134-34-1345-3-2345-3-1236-15
rule trans musty  134-34-13456
rule trans newsletter  1345-15-2456-234-123-1235
rule trans nonesuch  1345-5-135-234-16
rule trans nonsuch  1345-135-1345-234-16
rule trans northabout  1345-135-1235-1456-1-12
rule trans overmuch  135-1236-12456-134-16
rule trans overpaid  135-1236-12456-1234-145
rule trans penfriend  1234-26-124-1235
rule trans perceived  1234-12456-14-1236-145
rule trans perceiver  1234-12456-14-1236-1235
rule trans perhapses  1234-12456-125-15-234
rule trans poorlypaid  1234-135-135-1235-123-13456-1234-145
rule trans postpaid  1234-135-34-1234-145
rule trans preceive  1234-1235-14-1236
rule trans preceiver  1234-1235-14-1236-1235
rule trans preceiving  1234-1235-14-1236-1245
rule trans prepaid  1234-1235-15-1234-145
rule trans purblind  1234-136-1235-12-123
rule trans purblindly  1234-136-1235-12-123-123-13456
rule trans purblindness  1234-136-1235-12-123-56-234
rule trans purblindnesses  1234-136-1235-12-123-56-234-15-234
rule trans quickdraw  12345-13-145-1235-1-2456
rule trans quicken  12345-13-26
rule trans quickened  12345-13-26-1246
rule trans quickener  12345-13-26-12456
rule trans quickening  12345-13-26-346
rule trans quicker  12345-13-12456
rule trans quickest  12345-13-15-34
rule trans quickfire  12345-13-124-24-1235-15
rule trans quickfiring  12345-13-124-24-1235-346
rule trans quickfreeze  12345-13-124-1235-15-15-1356-15
rule trans quickfreezing  12345-13-124-1235-15-15-1356-346
rule trans quickfroze  12345-13-124-1235-135-1356-15
rule trans quickfrozen  12345-13-124-1235-135-1356-26
rule trans quickie  12345-13-24-15
rule trans quickish  12345-13-24-146
rule trans quickishly  12345-13-24-146-123-13456
rule trans quicklime  12345-13-123-24-134-15
rule trans quickly  12345-13-123-13456
rule trans quickness  12345-13-56-234
rule trans quicknesses  12345-13-56-234-15-234
rule trans quicksand  12345-13-234-12346
rule trans quickset  12345-13-234-15-2345
rule trans quicksilver  12345-13-234-24-123-1236-12456
rule trans quicksilvered  12345-13-234-24-123-1236-12456-1246
rule trans quicksilvering  12345-13-234-24-123-1236-12456-346
rule trans quicksnap  12345-13-234-1345-1-1234
rule trans quickstep  12345-13-34-15-1234
rule trans quickstepped  12345-13-34-15-1234-1234-1246
rule trans quickstepper  12345-13-34-15-1234-1234-12456
rule trans quickstepping  12345-13-34-15-1234-1234-346
rule trans quicktempered  12345-13-2345-15-134-1234-12456-1246
rule trans quicktime  12345-13-5-2345
rule trans quickwitted  12345-13-2456-24-2345-2345-1246
rule trans quickwittedly  12345-13-2456-24-2345-2345-1246-123-13456
rule trans quickwittedness  12345-13-2456-24-2345-2345-1246-56-234
rule trans quicky  12345-13-13456
rule trans readacross  1235-2-145-1-14-1235
rule trans rebraille  1235-15-12-1235-123
rule trans rebrailled  1235-15-12-1235-123-145
rule trans rebrailler  1235-15-12-1235-123-1235
rule trans received  1235-14-1236-145
rule trans receiver  1235-14-1236-1235
rule trans receivership  1235-14-1236-1235-146-24-1234
rule trans rejoiced  1235-245-14-145
rule trans rejoiceful  1235-245-14-56-123
rule trans rejoicefully  1235-245-14-56-123-123-13456
rule trans rejoicefulness  1235-245-14-56-123-56-234
rule trans rejoicer  1235-245-14-1235
rule trans rejoicingly  1235-245-14-1245-123-13456
rule trans reletter  1235-15-123-1235
rule trans relettered  1235-15-123-1235-1246
rule trans relettering  1235-15-123-1235-346
rule trans repaid  1235-15-1234-145
rule trans rightabout  5-1235-1-12
rule trans roundabout  1235-46-145-1-12
rule trans roustabout  1235-1256-34-1-12
rule trans runabout  1235-136-1345-1-12
rule trans saidest  234-145-15-34
rule trans saidst  234-145-34
rule trans scattergood  234-14-1-2345-2345-12456-1245-145
rule trans schoolchildren  234-16-135-135-123-16-1345
rule trans schoolfriend  234-16-135-135-123-124-1235
rule trans should've  146-145-3-1236-15
rule trans shoulda  146-145-1
rule trans shouldest  146-145-15-34
rule trans shouldn't  146-145-1345-3-2345
rule trans shouldn't've  146-145-1345-3-2345-3-1236-15
rule trans shouldst  146-145-34
rule trans snowblind  234-1345-246-12-123
rule trans snowblindness  234-1345-246-12-123-56-234
rule trans snowblindnesses  234-1345-246-12-123-56-234-15-234
rule trans somesuch  5-234-234-16
rule trans southabout  234-1256-1456-1-12
rule trans stepchildren  34-15-1234-16-1345
rule trans stirabout  34-24-1235-1-12
rule trans suchlike  234-16-123-24-13-15
rule trans supergood  234-136-1234-12456-1245-145
rule trans superquick  234-136-1234-12456-12345-13
rule trans tailfirst  2345-1-24-123-124-34
rule trans thereabout  5-2346-1-12
rule trans thereafter  5-2346-1-124
rule trans thereagain  5-2346-1-1245
rule trans thereagainst  5-2346-1-1245-34
rule trans thereinafter  5-2346-35-1-124
rule trans thereinagain  5-2346-35-1-1245
rule trans togetherness  2345-1245-1235-56-234
rule trans turnabout  2345-136-1235-1345-1-12
rule trans unaccording  136-1345-1-14
rule trans unaccordingly  136-1345-1-14-123-13456
rule trans unblindfold  136-1345-12-123-124-135-123-145
rule trans unblindfolded  136-1345-12-123-124-135-123-145-1246
rule trans unblindfolding  136-1345-12-123-124-135-123-145-346
rule trans unbraille  136-1345-12-1235-123
rule trans unbrailled  136-1345-12-1235-123-145
rule trans undeceive  136-1345-145-14-1236
rule trans undeceived  136-1345-145-14-1236-145
rule trans undeceiver  136-1345-145-14-1236-1235
rule trans undeceiving  136-1345-145-14-1236-1245
rule trans undeclare  136-1345-145-14-123
rule trans undeclared  136-1345-145-14-123-145
rule trans underpaid  5-136-1234-145
rule trans unfriend  136-1345-124-1235
rule trans unfriendlier  136-1345-124-1235-123-24-12456
rule trans unfriendliest  136-1345-124-1235-123-24-15-34
rule trans unfriendliness  136-1345-124-1235-123-24-56-234
rule trans unfriendlinesses  136-1345-124-1235-123-24-56-234-15-234
rule trans unfriendly  136-1345-124-1235-123-13456
rule trans unlettered  136-1345-123-1235-1246
rule trans unnecessary  136-1345-1345-15-14
rule trans unpaid  136-1345-1234-145
rule trans unperceive  136-1345-1234-12456-14-1236
rule trans unperceived  136-1345-1234-12456-14-1236-145
rule trans unperceiving  136-1345-1234-12456-14-1236-1245
rule trans unquick  136-1345-12345-13
rule trans unreceived  136-1345-1235-14-1236-145
rule trans unrejoice  136-1345-1235-245-14
rule trans unrejoiced  136-1345-1235-245-14-145
rule trans unrejoiceful  136-1345-1235-245-14-56-123
rule trans unrejoicefully  136-1345-1235-245-14-56-123-123-13456
rule trans unrejoicefulness  136-1345-1235-245-14-56-123-56-234
rule trans unrejoicer  136-1345-1235-245-14-1235
rule trans unrejoicing  136-1345-1235-245-14-1245
rule trans unrejoicingly  136-1345-1235-245-14-1245-123-13456
rule trans walkabout  2456-1-123-13-1-12
rule trans wellpaid  2456-15-123-123-1234-145
rule trans westabout  2456-15-34-1-12
rule trans whereabout  5-156-1-12
rule trans whereafter  5-156-1-124
rule trans whereagain  5-156-1-1245
rule trans whereagainst  5-156-1-1245-34
rule trans whereinafter  5-156-35-1-124
rule trans whereinagain  5-156-35-1-1245
rule trans womanfriend  2456-135-134-1-1345-124-1235
rule trans womenfriends  2456-135-134-26-124-1235-234
rule trans would've  2456-145-3-1236-15
rule trans woulda  2456-145-1
rule trans wouldest  2456-145-15-34
rule trans wouldn't  2456-145-1345-3-2345
rule trans wouldn't've  2456-145-1345-3-2345-3-1236-15
rule trans wouldst  2456-145-34

use word_whole_+ word_whole_-
@contraction abface Abface ABFACE abfaces Abfaces ABFACES abface's Abface's ABFACE'S                             # aboutface
@contraction abturn Abturn ABTURN abturns Abturns ABTURNS abturn's Abturn's ABTURN'S                             # aboutturn
@contraction acly Acly ACLY aclys Aclys ACLYS acly's Acly's ACLY'S                                               # accordingly
@contraction afbattle Afbattle AFBATTLE afbattles Afbattles AFBATTLES afbattle's Afbattle's AFBATTLE'S           # afterbattle
@contraction afburn Afburn AFBURN afburns Afburns AFBURNS afburn's Afburn's AFBURN'S                             # afterburn
@contraction afclap Afclap AFCLAP afclaps Afclaps AFCLAPS afclap's Afclap's AFCLAP'S                             # afterclap
@contraction afdamp Afdamp AFDAMP afdamps Afdamps AFDAMPS afdamp's Afdamp's AFDAMP'S                             # afterdamp
@contraction afdeck Afdeck AFDECK afdecks Afdecks AFDECKS afdeck's Afdeck's AFDECK'S                             # afterdeck
@contraction afgame Afgame AFGAME afgames Afgames AFGAMES afgame's Afgame's AFGAME'S                             # aftergame
@contraction aflife Aflife AFLIFE aflifes Aflifes AFLIFES aflife's Aflife's AFLIFE'S                             # afterlife
@contraction aflight Aflight AFLIGHT aflights Aflights AFLIGHTS aflight's Aflight's AFLIGHT'S                    # afterlight
@contraction aflives Aflives AFLIVES aflivess Aflivess AFLIVESS aflives's Aflives's AFLIVES'S                    # afterlives
@contraction afntea Afntea AFNTEA afnteas Afnteas AFNTEAS afntea's Afntea's AFNTEA'S                             # afternoontea
@contraction afpiece Afpiece AFPIECE afpieces Afpieces AFPIECES afpiece's Afpiece's AFPIECE'S                    # afterpiece
@contraction afplay Afplay AFPLAY afplays Afplays AFPLAYS afplay's Afplay's AFPLAY'S                             # afterplay
@contraction afsale Afsale AFSALE afsales Afsales AFSALES afsale's Afsale's AFSALE'S                             # aftersale
@contraction aftax Aftax AFTAX aftaxs Aftaxs AFTAXS aftax's Aftax's AFTAX'S                                      # aftertax
@contraction aftaxes Aftaxes AFTAXES aftaxess Aftaxess AFTAXESS aftaxes's Aftaxes's AFTAXES'S                    # aftertaxes
@contraction aftea Aftea AFTEA afteas Afteas AFTEAS aftea's Aftea's AFTEA'S                                      # aftertea
@contraction blfold Blfold BLFOLD blfolds Blfolds BLFOLDS blfold's Blfold's BLFOLD'S                             # blindfold
@contraction blly Blly BLLY bllys Bllys BLLYS blly's Blly's BLLY'S                                               # blindly
@contraction blman Blman BLMAN blmans Blmans BLMANS blman's Blman's BLMAN'S                                      # blindman
@contraction blside Blside BLSIDE blsides Blsides BLSIDES blside's Blside's BLSIDE'S                             # blindside
@contraction blworm Blworm BLWORM blworms Blworms BLWORMS blworm's Blworm's BLWORM'S                             # blindworm
@contraction bloodlr Bloodlr BLOODLR bloodlrs Bloodlrs BLOODLRS bloodlr's Bloodlr's BLOODLR'S                    # bloodletter
@contraction boyfr Boyfr BOYFR boyfrs Boyfrs BOYFRS boyfr's Boyfr's BOYFR'S                                      # boyfriend
@contraction brld Brld BRLD brlds Brlds BRLDS brld's Brld's BRLD'S                                               # brailled
@contraction brlr Brlr BRLR brlrs Brlrs BRLRS brlr's Brlr's BRLR'S                                               # brailler
@contraction brly Brly BRLY brlys Brlys BRLYS brly's Brly's BRLY'S                                               # brailley
@contraction colorbl Colorbl COLORBL colorbls Colorbls COLORBLS colorbl's Colorbl's COLORBL'S                    # colorblind
@contraction cda Cda CDA cdas Cdas CDAS cda's Cda's CDA'S                                                        # coulda
@contraction dcvd Dcvd DCVD dcvds Dcvds DCVDS dcvd's Dcvd's DCVD'S                                               # deceived
@contraction dcvr Dcvr DCVR dcvrs Dcvrs DCVRS dcvr's Dcvr's DCVR'S                                               # deceiver
@contraction dcld Dcld DCLD dclds Dclds DCLDS dcld's Dcld's DCLD'S                                               # declared
@contraction dclr Dclr DCLR dclrs Dclrs DCLRS dclr's Dclr's DCLR'S                                               # declarer
@contraction defr Defr DEFR defrs Defrs DEFRS defr's Defr's DEFR'S                                               # defriend
@contraction defr Defr DEFR defrs Defrs DEFRS defr's Defr's DEFR'S                                               # defriend
@contraction feelgd Feelgd FEELGD feelgds Feelgds FEELGDS feelgd's Feelgd's FEELGD'S                             # feelgood
@contraction frlies Frlies FRLIES frliess Frliess FRLIESS frlies's Frlies's FRLIES'S                             # friendlies
@contraction frly Frly FRLY frlys Frlys FRLYS frly's Frly's FRLY'S                                               # friendly
@contraction gadab Gadab GADAB gadabs Gadabs GADABS gadab's Gadab's GADAB'S                                      # gadabout
@contraction galfr Galfr GALFR galfrs Galfrs GALFRS galfr's Galfr's GALFR'S                                      # galfriend
@contraction girlfr Girlfr GIRLFR girlfrs Girlfrs GIRLFRS girlfr's Girlfr's GIRLFR'S                             # girlfriend
@contraction gdafn Gdafn GDAFN gdafns Gdafns GDAFNS gdafn's Gdafn's GDAFN'S                                      # goodafternoon
@contraction gdby Gdby GDBY gdbys Gdbys GDBYS gdby's Gdby's GDBY'S                                               # goodby
@contraction gdbye Gdbye GDBYE gdbyes Gdbyes GDBYES gdbye's Gdbye's GDBYE'S                                      # goodbye
@contraction gdhumor Gdhumor GDHUMOR gdhumors Gdhumors GDHUMORS gdhumor's Gdhumor's GDHUMOR'S                    # goodhumor
@contraction gdie Gdie GDIE gdies Gdies GDIES gdie's Gdie's GDIE'S                                               # goodie
@contraction gdlook Gdlook GDLOOK gdlooks Gdlooks GDLOOKS gdlook's Gdlook's GDLOOK'S                             # goodlook
@contraction gdly Gdly GDLY gdlys Gdlys GDLYS gdly's Gdly's GDLY'S                                               # goodly
@contraction gdman Gdman GDMAN gdmans Gdmans GDMANS gdman's Gdman's GDMAN'S                                      # goodman
@contraction gdnature Gdnature GDNATURE gdnatures Gdnatures GDNATURES gdnature's Gdnature's GDNATURE'S           # goodnature
@contraction gdsize Gdsize GDSIZE gdsizes Gdsizes GDSIZES gdsize's Gdsize's GDSIZE'S                             # goodsize
@contraction gdun Gdun GDUN gduns Gduns GDUNS gdun's Gdun's GDUN'S                                               # goodun
@contraction gdwife Gdwife GDWIFE gdwifes Gdwifes GDWIFES gdwife's Gdwife's GDWIFE'S                             # goodwife
@contraction gdwill Gdwill GDWILL gdwills Gdwills GDWILLS gdwill's Gdwill's GDWILL'S                             # goodwill
@contraction gdwives Gdwives GDWIVES gdwivess Gdwivess GDWIVESS gdwives's Gdwives's GDWIVES'S                    # goodwives
@contraction gdy Gdy GDY gdys Gdys GDYS gdy's Gdy's GDY'S                                                        # goody
@contraction grtaunt Grtaunt GRTAUNT grtaunts Grtaunts GRTAUNTS grtaunt's Grtaunt's GRTAUNT'S                    # greataunt
@contraction grtcircle Grtcircle GRTCIRCLE grtcircles Grtcircles GRTCIRCLES grtcircle's Grtcircle's GRTCIRCLE'S  # greatcircle
@contraction grtcoat Grtcoat GRTCOAT grtcoats Grtcoats GRTCOATS grtcoat's Grtcoat's GRTCOAT'S                    # greatcoat
@contraction grtly Grtly GRTLY grtlys Grtlys GRTLYS grtly's Grtly's GRTLY'S                                      # greatly
@contraction grtnephew Grtnephew GRTNEPHEW grtnephews Grtnephews GRTNEPHEWS grtnephew's Grtnephew's GRTNEPHEW'S  # greatnephew
@contraction grtniece Grtniece GRTNIECE grtnieces Grtnieces GRTNIECES grtniece's Grtniece's GRTNIECE'S           # greatniece
@contraction grtuncle Grtuncle GRTUNCLE grtuncles Grtuncles GRTUNCLES grtuncle's Grtuncle's GRTUNCLE'S           # greatuncle
@contraction guyfr Guyfr GUYFR guyfrs Guyfrs GUYFRS guyfr's Guyfr's GUYFR'S                                      # guyfriend
@contraction hatelr Hatelr HATELR hatelrs Hatelrs HATELRS hatelr's Hatelr's HATELR'S                             # hateletter
@contraction hmbo Hmbo HMBO hmbos Hmbos HMBOS hmbo's Hmbo's HMBO'S                                               # himbo
@contraction hmboes Hmboes HMBOES hmboess Hmboess HMBOESS hmboes's Hmboes's HMBOES'S                             # himboes
@contraction illpd Illpd ILLPD illpds Illpds ILLPDS illpd's Illpd's ILLPD'S                                      # illpaid
@contraction immly Immly IMMLY immlys Immlys IMMLYS immly's Immly's IMMLY'S                                      # immediately
@contraction knockab Knockab KNOCKAB knockabs Knockabs KNOCKABS knockab's Knockab's KNOCKAB'S                    # knockabout
@contraction ladyfr Ladyfr LADYFR ladyfrs Ladyfrs LADYFRS ladyfr's Ladyfr's LADYFR'S                             # ladyfriend
@contraction layab Layab LAYAB layabs Layabs LAYABS layab's Layab's LAYAB'S                                      # layabout
@contraction lrbodies Lrbodies LRBODIES lrbodiess Lrbodiess LRBODIESS lrbodies's Lrbodies's LRBODIES'S           # letterbodies
@contraction lrbody Lrbody LRBODY lrbodys Lrbodys LRBODYS lrbody's Lrbody's LRBODY'S                             # letterbody
@contraction lrbomb Lrbomb LRBOMB lrbombs Lrbombs LRBOMBS lrbomb's Lrbomb's LRBOMB'S                             # letterbomb
@contraction lrbox Lrbox LRBOX lrboxs Lrboxs LRBOXS lrbox's Lrbox's LRBOX'S                                      # letterbox
@contraction lrboxes Lrboxes LRBOXES lrboxess Lrboxess LRBOXESS lrboxes's Lrboxes's LRBOXES'S                    # letterboxes
@contraction lrman Lrman LRMAN lrmans Lrmans LRMANS lrman's Lrman's LRMAN'S                                      # letterman
@contraction lrpress Lrpress LRPRESS lrpresss Lrpresss LRPRESSS lrpress's Lrpress's LRPRESS'S                    # letterpress
@contraction lrpresses Lrpresses LRPRESSES lrpressess Lrpressess LRPRESSESS lrpresses's Lrpresses's LRPRESSES'S  # letterpresses
@contraction lrspace Lrspace LRSPACE lrspaces Lrspaces LRSPACES lrspace's Lrspace's LRSPACE'S                    # letterspace
@contraction lrtext Lrtext LRTEXT lrtexts Lrtexts LRTEXTS lrtext's Lrtext's LRTEXT'S                             # lettertext
@contraction lld Lld LLD llds Llds LLDS lld's Lld's LLD'S                                                        # littled
@contraction llneck Llneck LLNECK llnecks Llnecks LLNECKS llneck's Llneck's LLNECK'S                             # littleneck
@contraction llr Llr LLR llrs Llrs LLRS llr's Llr's LLR'S                                                        # littler
@contraction lovelr Lovelr LOVELR lovelrs Lovelrs LOVELRS lovelr's Lovelr's LOVELR'S                             # loveletter
@contraction manfr Manfr MANFR manfrs Manfrs MANFRS manfr's Manfr's MANFR'S                                      # manfriend
@contraction midafn Midafn MIDAFN midafns Midafns MIDAFNS midafn's Midafn's MIDAFN'S                             # midafternoon
@contraction misbrl Misbrl MISBRL misbrls Misbrls MISBRLS misbrl's Misbrl's MISBRL'S                             # misbraille
@contraction misbrld Misbrld MISBRLD misbrlds Misbrlds MISBRLDS misbrld's Misbrld's MISBRLD'S                    # misbrailled
@contraction missd Missd MISSD missds Missds MISSDS missd's Missd's MISSD'S                                      # missaid
@contraction newslr Newslr NEWSLR newslrs Newslrs NEWSLRS newslr's Newslr's NEWSLR'S                             # newsletter
@contraction poorlypd Poorlypd POORLYPD poorlypds Poorlypds POORLYPDS poorlypd's Poorlypd's POORLYPD'S           # poorlypaid
@contraction prcv Prcv PRCV prcvs Prcvs PRCVS prcv's Prcv's PRCV'S                                               # preceive
@contraction prcvr Prcvr PRCVR prcvrs Prcvrs PRCVRS prcvr's Prcvr's PRCVR'S                                      # preceiver
@contraction prcvg Prcvg PRCVG prcvgs Prcvgs PRCVGS prcvg's Prcvg's PRCVG'S                                      # preceiving
@contraction prepd Prepd PREPD prepds Prepds PREPDS prepd's Prepd's PREPD'S                                      # prepaid
@contraction purbl Purbl PURBL purbls Purbls PURBLS purbl's Purbl's PURBL'S                                      # purblind
@contraction purblly Purblly PURBLLY purbllys Purbllys PURBLLYS purblly's Purblly's PURBLLY'S                    # purblindly
@contraction qkdraw Qkdraw QKDRAW qkdraws Qkdraws QKDRAWS qkdraw's Qkdraw's QKDRAW'S                             # quickdraw
@contraction qkfire Qkfire QKFIRE qkfires Qkfires QKFIRES qkfire's Qkfire's QKFIRE'S                             # quickfire
@contraction qkfreeze Qkfreeze QKFREEZE qkfreezes Qkfreezes QKFREEZES qkfreeze's Qkfreeze's QKFREEZE'S           # quickfreeze
@contraction qkfroze Qkfroze QKFROZE qkfrozes Qkfrozes QKFROZES qkfroze's Qkfroze's QKFROZE'S                    # quickfroze
@contraction qkie Qkie QKIE qkies Qkies QKIES qkie's Qkie's QKIE'S                                               # quickie
@contraction qklime Qklime QKLIME qklimes Qklimes QKLIMES qklime's Qklime's QKLIME'S                             # quicklime
@contraction qkly Qkly QKLY qklys Qklys QKLYS qkly's Qkly's QKLY'S                                               # quickly
@contraction qkset Qkset QKSET qksets Qksets QKSETS qkset's Qkset's QKSET'S                                      # quickset
@contraction qksnap Qksnap QKSNAP qksnaps Qksnaps QKSNAPS qksnap's Qksnap's QKSNAP'S                             # quicksnap
@contraction qky Qky QKY qkys Qkys QKYS qky's Qky's QKY'S                                                        # quicky
@contraction rebrl Rebrl REBRL rebrls Rebrls REBRLS rebrl's Rebrl's REBRL'S                                      # rebraille
@contraction rebrld Rebrld REBRLD rebrlds Rebrlds REBRLDS rebrld's Rebrld's REBRLD'S                             # rebrailled
@contraction rebrlr Rebrlr REBRLR rebrlrs Rebrlrs REBRLRS rebrlr's Rebrlr's REBRLR'S                             # rebrailler
@contraction rcvd Rcvd RCVD rcvds Rcvds RCVDS rcvd's Rcvd's RCVD'S                                               # received
@contraction rcvr Rcvr RCVR rcvrs Rcvrs RCVRS rcvr's Rcvr's RCVR'S                                               # receiver
@contraction rjcd Rjcd RJCD rjcds Rjcds RJCDS rjcd's Rjcd's RJCD'S                                               # rejoiced
@contraction rjcr Rjcr RJCR rjcrs Rjcrs RJCRS rjcr's Rjcr's RJCR'S                                               # rejoicer
@contraction rjcgly Rjcgly RJCGLY rjcglys Rjcglys RJCGLYS rjcgly's Rjcgly's RJCGLY'S                             # rejoicingly
@contraction relr Relr RELR relrs Relrs RELRS relr's Relr's RELR'S                                               # reletter
@contraction repd Repd REPD repds Repds REPDS repd's Repd's REPD'S                                               # repaid
@contraction runab Runab RUNAB runabs Runabs RUNABS runab's Runab's RUNAB'S                                      # runabout
@contraction turnab Turnab TURNAB turnabs Turnabs TURNABS turnab's Turnab's TURNAB'S                             # turnabout
@contraction unac Unac UNAC unacs Unacs UNACS unac's Unac's UNAC'S                                               # unaccording
@contraction unacly Unacly UNACLY unaclys Unaclys UNACLYS unacly's Unacly's UNACLY'S                             # unaccordingly
@contraction unblfold Unblfold UNBLFOLD unblfolds Unblfolds UNBLFOLDS unblfold's Unblfold's UNBLFOLD'S           # unblindfold
@contraction unbrl Unbrl UNBRL unbrls Unbrls UNBRLS unbrl's Unbrl's UNBRL'S                                      # unbraille
@contraction unbrld Unbrld UNBRLD unbrlds Unbrlds UNBRLDS unbrld's Unbrld's UNBRLD'S                             # unbrailled
@contraction undcv Undcv UNDCV undcvs Undcvs UNDCVS undcv's Undcv's UNDCV'S                                      # undeceive
@contraction undcvd Undcvd UNDCVD undcvds Undcvds UNDCVDS undcvd's Undcvd's UNDCVD'S                             # undeceived
@contraction undcvr Undcvr UNDCVR undcvrs Undcvrs UNDCVRS undcvr's Undcvr's UNDCVR'S                             # undeceiver
@contraction undcvg Undcvg UNDCVG undcvgs Undcvgs UNDCVGS undcvg's Undcvg's UNDCVG'S                             # undeceiving
@contraction undcl Undcl UNDCL undcls Undcls UNDCLS undcl's Undcl's UNDCL'S                                      # undeclare
@contraction undcld Undcld UNDCLD undclds Undclds UNDCLDS undcld's Undcld's UNDCLD'S                             # undeclared
@contraction unfr Unfr UNFR unfrs Unfrs UNFRS unfr's Unfr's UNFR'S                                               # unfriend
@contraction unfrly Unfrly UNFRLY unfrlys Unfrlys UNFRLYS unfrly's Unfrly's UNFRLY'S                             # unfriendly
@contraction unnec Unnec UNNEC unnecs Unnecs UNNECS unnec's Unnec's UNNEC'S                                      # unnecessary
@contraction unpd Unpd UNPD unpds Unpds UNPDS unpd's Unpd's UNPD'S                                               # unpaid
@contraction unqk Unqk UNQK unqks Unqks UNQKS unqk's Unqk's UNQK'S                                               # unquick
@contraction unrcvd Unrcvd UNRCVD unrcvds Unrcvds UNRCVDS unrcvd's Unrcvd's UNRCVD'S                             # unreceived
@contraction unrjc Unrjc UNRJC unrjcs Unrjcs UNRJCS unrjc's Unrjc's UNRJC'S                                      # unrejoice
@contraction unrjcd Unrjcd UNRJCD unrjcds Unrjcds UNRJCDS unrjcd's Unrjcd's UNRJCD'S                             # unrejoiced
@contraction unrjcr Unrjcr UNRJCR unrjcrs Unrjcrs UNRJCRS unrjcr's Unrjcr's UNRJCR'S                             # unrejoicer
@contraction unrjcg Unrjcg UNRJCG unrjcgs Unrjcgs UNRJCGS unrjcg's Unrjcg's UNRJCG'S                             # unrejoicing
@contraction unrjcgly Unrjcgly UNRJCGLY unrjcglys Unrjcglys UNRJCGLYS unrjcgly's Unrjcgly's UNRJCGLY'S           # unrejoicingly
@contraction walkab Walkab WALKAB walkabs Walkabs WALKABS walkab's Walkab's WALKAB'S                             # walkabout
@contraction wellpd Wellpd WELLPD wellpds Wellpds WELLPDS wellpd's Wellpd's WELLPD'S                             # wellpaid
@contraction womanfr Womanfr WOMANFR womanfrs Womanfrs WOMANFRS womanfr's Womanfr's WOMANFR'S                    # womanfriend
@contraction wda Wda WDA wdas Wdas WDAS wda's Wda's WDA'S                                                        # woulda
use


########################################
#   Appendix 1.2
########################################

rule trans dafter 145-1-124-2345-12456
rule trans drafter 145-1235-1-124-2345-12456
rule trans grafter 1245-1235-1-124-2345-12456
rule trans rafter 1235-1-124-2345-12456


########################################
#   extra shortforms
########################################

uses shortform_+ shortform_- rule trans unsaid 136-1345-234-145


########################################
#   misc
########################################

rule trans rared 1235-1-1235-1246

################################################################################

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

include english-ueb-grade2.rst


########################################
#   Indicators
########################################

rule init \xf32e -   math begin
rule init \xf32f -   math end

rule init \xf330 -   expression-begin
rule init \xf331 -   expression-separator
rule init \xf332 -   expression-end

rule init \x2061 -   function application
rule init \x2062 -   invisible times
rule init \x2063 -   invisible separator
rule init \x2064 -   invisible plus

#   fractions
rule trans \xf500 12356
rule trans \xf501 46-34
rule trans \xf502 46-34
rule trans \xf503 23456

chars \xf501\xf502 $numeric_cont

#   mixed fractions
rule trans \xf504 -
rule trans \xf505 34
rule trans \xf506 34
rule trans \xf507 -

#   complex fractions
rule trans \xf508 12356
rule trans \xf509 46-34
rule trans \xf50a 46-34
rule trans \xf50b 23456

#   simple fractions
rule trans \xf50c -
rule trans \xf50d 34
rule trans \xf50e 34
rule trans \xf50f -

chars \xf50d\xf50e $numeric_cont

#   subscripts
rule trans \xf580 -
rule trans \xf581 56-26
rule trans \xf582 -

#   superscripts
rule trans \xf583 -
rule trans \xf584 56-35
rule trans \xf585 -

#   sub/superscripts
rule trans \xf586 -
rule trans \xf587 56-35
rule trans \xf588 -

rule trans \xf589 6

#   underscripts
rule trans \xf5a0 -
rule trans \xf5a1 46-26
rule trans \xf5a2 -

#   underine
rule trans \xf5a1_\xf5a2 6-156
rule trans \xf5a1\x0332\xf5a2 6-156   combining

#   overscripts
rule trans \xf5a3 -
rule trans \xf5a4 46-35
rule trans \xf5a5 -

#   overline (vinculum)
rule trans \xf5a4\x203e\xf5a5 156   ‾
rule trans \xf5a4\x0305\xf5a5 156   combining
rule trans \xf5a4\x00af\xf5a5 156   !?!

#   under/overscripts
rule trans \xf5a6 -
rule trans \xf5a7 -
rule trans \xf5a8 -

#   root
rule trans \xf5b0 146-35
rule trans \xf5b1 -
rule trans \xf5b2 346

#   square root
rule trans \xf5b3 146
rule trans \xf5b4 346

#   tables
rule trans \xf600 -
rule trans \xf601 -
rule trans \xf602 -
rule trans \xf603 -
rule trans \xf604 -
rule trans \xf605 -

rule trans \xf610 6-12356
rule trans \xf611 6-23456
rule trans \xf612 6-4-12356
rule trans \xf613 6-4-23456
rule trans \xf614 6-46-12356
rule trans \xf615 6-46-23456
rule trans \xf616 6-46-46-12356
rule trans \xf617 6-46-46-23456
rule trans \xf618 6-1256

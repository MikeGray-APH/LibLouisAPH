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
#
# To start gdb manually, have it use this script:
#    gdb --command=debug/gdb/main.gdb
#
# The `debug/gdb/` directory also contains debugging scripts for `gdb`.  These
# scripts contain special macros and variables for certain functions.  The
# typical values are for function `do_something` would be:
#    * `$do_something_bpnum`:  for the breakpoint number for enabling and
#                              disabling.
#    * `out_do_something`:     outputs the variable and structures pertaining to
#                              the function
#    * `n_do_something`:       allows stepping through the function with output
#
# A list of functions that macros written for them are listed below.  Uncomment
# a function to set its breakpoint.
#
################################################################################

set print pretty on
set print elements 0x1000
set height 200
set unwindonsignal on

source debug/gdb/utf.gdb
source debug/gdb/table.gdb
source debug/gdb/pattern.gdb
source debug/gdb/compile.gdb
source debug/gdb/translate.gdb
source debug/gdb/generic.gdb
source debug/gdb/lookup.gdb

########################################

define spacer
	printf "--------------------------------------------------------------------------------\n"
end

########################################

#ena $utf16le_convert_escapes_bpnum

#ena $rule_add_new_bpnum
#ena $rule_match_forward_bpnum
#ena $rule_match_backward_bpnum

#ena $pattern_compile_expression_bpnum
#ena $pattern_compile_1_bpnum
#ena $pattern_compile_2_bpnum
#ena $pattern_compile_3_bpnum
#ena $pattern_compile_bpnum
#ena $pattern_reverse_expression_bpnum
#ena $pattern_check_expression_bpnum

#ena $convert_to_dots_bpnum
#ena $convert_with_dots_bpnum
#ena $compile_chars_bpnum
#ena $compile_rule_bpnum
#ena $compile_pattern_bpnum
#ena $compile_match_bpnum
#ena $compile_macro_bpnum
#ena $table_compile_from_file_bpnum

#ena $translate_start_bpnum

#ena $generic_match_rule_bpnum
#ena $generic_apply_rule_forward_bpnum
#ena $generic_apply_rule_backward_bpnum
#ena $generic_process_bpnum

#ena $translate_generic_forward_bpnum

#ena $mark_mode_bpnum
#ena $indicators_to_words_bpnum
#ena $words_to_passages_bpnum
#ena $add_indicators_emphases_bpnum
#ena $mark_capitals_bpnum
#ena $mark_nonalphabetic_words_bpnum
#ena $reset_words_in_passages_bpnum
#ena $capital_words_to_passages_bpnum
#ena $add_indicators_capital_bpnum
#ena $add_indicators_numeric_bpnum

#ena $add_soft_terminators_bpnum
#ena $convert_indicators_capital_bpnum
#ena $convert_indicators_numeric_bpnum

#ena $translate_generic_backward_bpnum

#ena $create_path_file_name_bpnum
#ena $lookup_table_bpnum
#ena $lookup_tables_bpnum
#ena $lookup_open_file_bpnum

########################################

define op
spacer
out_parse
printf "\n"
end

define np
next
op
end

define ot
spacer
out_translate translate
printf "\n"
end

define nt
next
ot
end

define otr
spacer
out_translate translate
out_rule rule
printf "\n"
end

define ntr
next
otr
end

########################################

#ena $translate_generic_forward_bpnum
#ena $translate_generic_backward_bpnum

define bb
ena $generic_process_bpnum
end
define bbb
ena $generic_match_rule_bpnum
end
define bbbb
ena $pattern_check_expression_bpnum
end

########################################

run

################################################################################

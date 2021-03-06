#
#   Copyright 2018 American Printing House for the Blind Inc.
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

define out_convert_nemeth_scripts

	printf "translate:\n"
	out_translate_input_and translate crs
	out_translate_output translate

	printf "\n"

	printf "seps              = "
	call debug_output_line(seps, sep_cnt)
	printf "sep_cnt           = %d\n", sep_cnt
	printf "sbp_cnt           = %d\n", sbp_cnt
	printf "sub_letter_digit  = %d\n", sub_letter_digit
	printf "need_reset        = %d\n", need_reset
	printf "in_numeric        = %d\n", in_numeric
	printf "len               = %d\n", len
	printf "mrk               = %d\n", mrk
	printf "crs               = %d\n", crs

	printf "\n"

end

define n_convert_nemeth_scripts
	next
	spacer
	out_convert_nemeth_scripts
end

break convert_nemeth_scripts
commands $bpnum

	call (void*)memset(translate->output, 0, translate->output_max * sizeof(unichar))
	set translate->output_len = 0
	set sep_cnt = 0
	set sbp_cnt = 0
	set sub_letter_digit = 0
	set need_reset = 0
	set in_numeric = 0
	set len = 0
	set mrk = 0
	set crs = 0

	spacer
	out_convert_nemeth_scripts

	printf "next = cns\n\n"

end
set $convert_nemeth_scripts_bpnum = $bpnum
dis $convert_nemeth_scripts_bpnum

define cns
n_convert_nemeth_scripts
end

################################################################################

define out_add_numeric_indicators

	out_translate translate
	printf "\n"

	printf "do_insert   = %d\n", do_insert

	printf "\n"

end

define n_add_numeric_indicators
	next
	spacer
	out_add_numeric_indicators
end

break add_numeric_indicators
commands $bpnum

	call (void*)memset(translate->output, 0, translate->output_max * sizeof(unichar))
	set do_insert = 0

	spacer
	out_add_numeric_indicators

	printf "next = ani\n\n"

end
set $add_numeric_indicators_bpnum = $bpnum
dis $add_numeric_indicators_bpnum

define ani
n_add_numeric_indicators
end

########################################

break translate_nemeth_forward
commands $bpnum

	set processed = 0

	spacer
	out_translate_generic

	printf "next = ntg\n\n"

end
set $translate_nemeth_forward_bpnum = $bpnum
dis $translate_nemeth_forward_bpnum

################################################################################

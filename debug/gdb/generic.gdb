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

define out_word_letter

	if $arg0 & 0x00000001
		printf "w"
	else
		printf " "
	end
	if $arg0 & 0x00000002
		printf "W"
	else
		printf " "
	end
	if $arg0 & 0x00000004
		printf "I"
	else
		printf " "
	end
	if $arg0 & 0x00000008
		printf "_"
	else
		printf " "
	end

	printf " "

end

define out_indicators

	if $arg0 & 0x00000001
		printf " begin"
	end
	if $arg0 & 0x00000002
		printf " end"
	end
	if $arg0 & 0x00000004
		printf " word"
	end
	if $arg0 & 0x00000008
		printf " symbol"
	end
	if $arg0 & 0x00000010
		printf " reset"
	end
end

define out_words

	set $translate = (struct translate*)$arg0
	set $words = (unsigned char*)$arg1

	set $i0 = 0
	while $i0 < $translate->input_len

		printf "["
		if $i0 < 100
			printf "0"
		end
		if $i0 < 10
			printf "0"
		end
		printf "%d] ", $i0
		call debug_output_uchar(translate->input[$i0], 0, 0)
		printf "\t"

		if $words > 0
			out_word_letter $words[$i0]
			printf " | "
		end
		printf "\n"
		set $i0 = $i0 + 1

	end

	printf "\n"

end

define out_indicators_words

	set $translate = (struct translate*)$arg0
	set $indicators = (unsigned int*)$arg1
	set $words = (unsigned char*)$arg2

	if $indicators > 0

		set $i0 = 0
		while $i0 < $translate->input_len

			printf "["
			if $i0 < 100
				printf "0"
			end
			if $i0 < 10
				printf "0"
			end
			printf "%d] ", $i0
			call debug_output_uchar(translate->input[$i0], 0, 0)
			printf "\t"

			if $words > 0
				out_word_letter $words[$i0]
				printf " | "
			end
			out_indicators $indicators[$i0]
			printf "\n"
			set $i0 = $i0 + 1

		end

		printf "[   ]  \t"
		if $words > 0
			out_word_letter $words[$translate->input_len]
			printf " | "
		end
		out_indicators $indicators[$translate->input_len]
		printf "\n"

	end

end

################################################################################

define out_mark_mode

	printf "translate:\n"
	if translate > 0
		out_translate_input_at translate i
	end

	printf "\n"

	printf "emp_begin          = %d\n", emp_begin
	printf "word_begin         = %d\n", word_begin
	printf "in_user_begin      = %d\n", in_user_begin
	printf "in_user_end        = %d\n", in_user_end
	printf "in_user_indicator  = %d\n", in_user_indicator
	printf "in_user_mode       = %d\n", in_user_mode
	printf "in_marked          = %d\n", in_marked
	printf "prv_space          = %d\n", prv_space
	printf "word_mark          = 0x%02x\n", word_mark
	printf "attrs              = 0x%08x\n", attrs

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_mark_mode
	next
	spacer
	out_mark_mode
end

break mark_mode
commands $bpnum

	set emp_begin = 0
	set word_begin = 0
	set in_user_begin = 0
	set in_user_end = 0
	set in_user_indicator = 0
	set in_user_mode = 0
	set in_marked = 0
	set prv_space = 0
	set word_mark = 0
	set attrs = 0

	spacer
	out_mark_mode

	printf "next = nmm\n\n"

end
set $mark_mode_bpnum = $bpnum
dis $mark_mode_bpnum

define nmm
n_mark_mode
end

########################################

define out_indicators_to_words

	printf "translate:\n"
	if translate > 0
		out_translate_input_at translate i
	end

	printf "\n"

	printf "ind_in      = %d\n", ind_in
	printf "emp_in      = %d\n", emp_in
	printf "word_in     = %d\n", word_in
	printf "word_began  = %d\n", word_began
	printf "word_begin  = %d\n", word_begin
	printf "word_whole  = %d\n", word_whole
	printf "word_stop   = %d\n", word_stop
	printf "word_len    = %d\n", word_len
	printf "emp_len     = %d\n", emp_len

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_indicators_to_words
	next
	spacer
	out_indicators_to_words
end

break indicators_to_words
commands $bpnum

	set ind_in = 0
	set emp_in = 0
	set word_in = 0
	set word_began = 0
	set word_begin = 0
	set word_whole = 0
	set word_stop = 0
	set word_len = 0
	set emp_len = 0

	spacer
	out_indicators_to_words

	printf "next = nitw\n\n"

end
set $indicators_to_words_bpnum = $bpnum
dis $indicators_to_words_bpnum

define nitw
n_indicators_to_words
end

########################################

define out_words_to_passages

	printf "translate:\n"
	if translate > 0
		out_translate_input_at translate i
	end

	printf "\n"

	printf "pass_in     = %d\n", pass_in
	printf "word_in     = %d\n", word_in
	printf "word_cnt    = %d\n", word_cnt
	printf "pass_begin  = %d\n", pass_begin
	printf "pass_end    = %d\n", pass_end

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_words_to_passages
	next
	spacer
	out_words_to_passages
end

break words_to_passages
commands $bpnum

	set word_cnt = 0
	set pass_begin = 0
	set pass_end = 0
	set pass_in = 0
	set word_in = 0

	spacer
	out_words_to_passages

end
set $words_to_passages_bpnum = $bpnum
dis $words_to_passages_bpnum

########################################

define out_add_indicators_emphases

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_add_indicators_emphases
	next
	spacer
	out_add_indicators_emphases
end

break add_indicators_emphases
commands $bpnum

	set indicators = (void*)0
	set words = (void*)0

	spacer
	out_add_indicators_emphases

	printf "next = naie\n\n"

end
set $add_indicators_emphases_bpnum = $bpnum
dis $add_indicators_emphases_bpnum

define naie
n_add_indicators_emphases
end

########################################

define out_add_indicators_numeric

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end

	printf "\n"

	printf "in_numeric          = %d\n", in_numeric
	printf "in_nocontract       = %d\n", in_nocontract
	printf "in_numeric_passage  = %d\n", in_nocontract
	printf "attrs               = 0x%08x\n", attrs
	printf "uchar               = "
	call debug_output_uchar_escape(uchar)
	printf "\n"

	printf "\n"
end

define n_add_indicators_numeric
	next
	spacer
	out_add_indicators_numeric
end

break add_indicators_numeric
commands $bpnum

	set in_numeric = 0
	set in_nocontract = 0
	set in_numeric_passage = 0
	set attrs = 0
	set uchar = 0

	spacer
	out_add_indicators_numeric

	printf "next = nain\n\n"

end
set $add_indicators_numeric_bpnum = $bpnum
dis $add_indicators_numeric_bpnum

define nain
n_add_indicators_numeric
end

########################################

define out_mark_capitals

	printf "translate:\n"
	if translate > 0
		out_translate_input_at translate i
	else
		printf "\n"
	end

	printf "caps_begin    = %d\n", caps_begin
	printf "caps_end      = %d\n", caps_end
	printf "caps_cnt      = %d\n", caps_cnt
	printf "indicator_in  = %d\n", indicator_in
	printf "attrs         = 0x%08x\n", attrs

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_mark_capitals
	next
	spacer
	out_mark_capitals
end

break mark_capitals
commands $bpnum

	set caps_begin = 0
	set caps_end = 0
	set caps_cnt = 0
	set indicator_in = 0
	set attrs = 0

	spacer
	out_mark_capitals

end
set $mark_capitals_bpnum = $bpnum
dis $mark_capitals_bpnum

########################################

define out_mark_nonalphabetic_words

	printf "translate:\n"
	if translate > 0
		out_translate_input_at translate i
	end

	printf "\n"

	printf "word_begin    = %d\n", word_begin
	printf "letter_cnt    = %d\n", letter_cnt

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_mark_nonalphabetic_words
	next
	spacer
	out_mark_nonalphabetic_words
end

break mark_nonalphabetic_words
commands $bpnum

	set word_begin = 0
	set letter_cnt = 0

	spacer
	out_mark_nonalphabetic_words

end
set $mark_nonalphabetic_words_bpnum = $bpnum
dis $mark_nonalphabetic_words_bpnum

########################################

define out_reset_words_in_passages

	printf "translate:\n"
	if translate > 0
		out_translate_input_at translate i
	end

	printf "\n"

	printf "word_begin    = %d\n", word_begin
	printf "word_in       = %d\n", word_in
	printf "pass_in       = %d\n", pass_in
	printf "word_reset    = %d\n", word_reset
	printf "letter_cnt    = %d\n", letter_cnt
	printf "indicator_in  = %d\n", indicator_in
	printf "at            = %d\n", at

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_reset_words_in_passages
	next
	spacer
	out_reset_words_in_passages
end

break reset_words_in_passages
commands $bpnum

	set word_begin = 0
	set word_in = 0
	set pass_in = 0
	set word_reset = 0
	set letter_cnt = 0
	set indicator_in = 0
	set at = 0

	spacer
	out_reset_words_in_passages

end
set $reset_words_in_passages_bpnum = $bpnum
dis $reset_words_in_passages_bpnum

########################################

define out_capital_words_to_passages

	printf "translate:\n"
	if translate > 0
		out_translate_input_at translate i
	end

	printf "\n"

	printf "pass_begin    = %d\n", pass_begin
	printf "pass_end      = %d\n", pass_end
	printf "pass_in       = %d\n", pass_in
	printf "word_in       = %d\n", word_in
	printf "word_cnt      = %d\n", word_cnt
	printf "indicator_in  = %d\n", indicator_in

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_capital_words_to_passages
	next
	spacer
	out_capital_words_to_passages
end

break capital_words_to_passages
commands $bpnum

	set pass_begin = 0
	set pass_end = 0
	set pass_in = 0
	set word_in = 0
	set word_cnt = 0
	set indicator_in = 0

	spacer
	out_capital_words_to_passages

	printf "next = cwtp\n\n"

end
set $capital_words_to_passages_bpnum = $bpnum
dis $capital_words_to_passages_bpnum

define cwtp
n_capital_words_to_passages
end

########################################

define out_add_indicators_capital

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end

	printf "\n"

	out_indicators_words translate indicators words

	printf "\n"
end

define n_add_indicators_capital
	next
	spacer
	out_add_indicators_capital
end

break add_indicators_capital
commands $bpnum

	set indicators = (void*)0
	set words = (void*)0

	spacer
	out_add_indicators_capital

	printf "next = naic\n\n"

end
set $add_indicators_capital_bpnum = $bpnum
dis $add_indicators_capital_bpnum

define naic
n_add_indicators_capital
end

########################################

define out_add_soft_terminators

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end

	printf "\n"

	printf "in_numeric     = %d\n", in_numeric
	printf "in_nocontract  = %d\n", in_nocontract

	printf "\n"

end

define n_add_soft_terminators
	next
	spacer
	out_add_soft_terminators
end

break add_soft_terminators
commands $bpnum

	set in_numeric = 0
	set in_nocontract = 0

	spacer
	out_add_soft_terminators

end
set $add_soft_terminators_bpnum = $bpnum
dis $add_soft_terminators_bpnum

########################################

define out_convert_indicators_capital

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end

	printf "\n"

	printf "capital_in  = %d\n", capital_in
	printf "upper       = "
	if(upper > 0)
		call debug_output_uchar_escape(upper)
	end
	printf "\n"
	printf "numeric_in  = %d\n", numeric_in

	printf "\n"

end

define n_convert_indicators_capital
	next
	spacer
	out_convert_indicators_capital
end

break convert_indicators_capital
commands $bpnum

	set capital_in = 0
	set numeric_in = 0
	set upper = 0

	spacer
	out_convert_indicators_capital

	printf "next = nric\n\n"

end
set $convert_indicators_capital_bpnum = $bpnum
dis $convert_indicators_capital_bpnum

define nric
n_convert_indicators_capital
end

########################################

define out_convert_indicators_numeric

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end

	printf "\n"

	printf "in_numeric          = %d\n", in_numeric
	printf "in_numeric_passage  = %d\n", in_numeric_passage
	printf "uchar               = "
	if(uchar > 0)
		call debug_output_uchar_escape(uchar)
	end
	printf "\n"

	printf "\n"

end

define n_convert_indicators_numeric
	next
	spacer
	out_convert_indicators_numeric
end

break convert_indicators_numeric
commands $bpnum

	set in_numeric = 0
	set in_numeric_passage = 0
	set uchar = 0

	spacer
	out_convert_indicators_numeric

end
set $convert_indicators_numeric_bpnum = $bpnum
dis $convert_indicators_numeric_bpnum

########################################

define n_generic_match_rule
	next
	spacer
	out_translate_and_rule
end

break generic_match_rule
commands $bpnum

	set rule = (void*)0

	spacer
	out_translate_and_rule

	printf "next = ngmr\n\n"

end
set $generic_match_rule_bpnum = $bpnum
dis $generic_match_rule_bpnum

define ngmr
n_generic_match_rule
end

########################################

define n_generic_apply_rule_forward
	next
	spacer
	out_translate_and_rule
end

break generic_apply_rule_forward
commands $bpnum

	spacer
	out_translate_and_rule

end
set $generic_apply_rule_forward_bpnum = $bpnum
dis $generic_apply_rule_forward_bpnum

########################################

define n_generic_apply_rule_backward
	next
	spacer
	out_translate_and_rule
end

break generic_apply_rule_backward
commands $bpnum

	spacer
	out_translate_and_rule

end
set $generic_apply_rule_backward_bpnum = $bpnum
dis $generic_apply_rule_backward_bpnum

########################################

define out_generic_process

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end

	printf "\n"

	printf "rule:\n"
	if rule > 0
		out_rule rule
	end

	printf "\n"

	printf "hash_type         = "
	output hash_type
	printf "\n"
	printf "direction         = "
	output direction
	printf "\n"
	printf "nocontract_state  = "
	output nocontract_state
	printf "\n"

	printf "\n"

end

define n_generic_process
	next
	spacer
	out_generic_process
end

break generic_process
commands $bpnum

	set rule = (void*)0

	spacer
	out_generic_process

	printf "next = ngp\n\n"

end
set $generic_process_bpnum = $bpnum
dis $generic_process_bpnum

define ngp
n_generic_process
end

########################################

define out_translate_generic

	printf "translate:\n"
	out_translate translate

	printf "\n"

	printf "processed  = %d\n", processed

	printf "\n"

end

define n_translate_generic
	next
	spacer
	out_translate_generic
end

break translate_generic_forward
commands $bpnum

	set processed = 0

	spacer
	out_translate_generic

	printf "next = nt\n\n"

end
set $translate_generic_forward_bpnum = $bpnum
dis $translate_generic_forward_bpnum

break translate_generic_backward
commands $bpnum

	set processed = 0

	spacer
	out_translate_generic

	printf "next = nt\n\n"

end
set $translate_generic_backward_bpnum = $bpnum
dis $translate_generic_backward_bpnum

define ntg
n_translate_generic
end

################################################################################

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

define out_unichar

	set $unichar = (struct unichar*)$arg0
	printf "   0x%lx\n", $unichar

	printf "      uchar       = 0x%04x   ", $unichar->uchar
	if $unichar->uchar > 0
		call uchar_output_escape($unichar->uchar, (void*)0, (void*)0)
	end
	printf "\n"

	printf "      other_case  = "
	if $unichar->other_case > 0
		printf "0x%04x   ", $unichar->other_case->uchar
		if $unichar->uchar > 0
			call uchar_output_escape($unichar->other_case->uchar, (void*)0, (void*)0)
		end
		printf "   0x%lx", $unichar->other_case
	else
		printf "NULL"
	end
	printf "\n"

end

########################################

define out_dot_string

	set $dot = (Unicode*)$arg0
	set $dot_len = (int)$arg1

	set $i0 = 0
	while($i0 < $dot_len)

		if $dot[$i0] & 0b00000001
			printf "1"
		end
		if $dot[$i0] & 0b00000010
			printf "2"
		end
		if $dot[$i0] & 0b00000100
			printf "3"
		end
		if $dot[$i0] & 0b00001000
			printf "4"
		end
		if $dot[$i0] & 0b00010000
			printf "5"
		end
		if $dot[$i0] & 0b00100000
			printf "6"
		end
		if $dot[$i0] & 0b01000000
			printf "7"
		end
		if $dot[$i0] & 0b10000000
			printf "8"
		end
		if $i0 < $dot_len - 1
			printf "-"
		end

		set $i0 = $i0 + 1

	end

end

define out_rule

	set $rule = (struct rule*)$arg0
	printf "   0x%lx\n", $rule
	printf "      attrs0           = 0x%08x\n", $rule->attrs

	if $rule->dots_len < 100

		printf "      chars_nxt        = 0x%lx\n", $rule->chars_nxt
		printf "      dots_nxt         = 0x%lx\n", $rule->dots_nxt
		printf "      chars[%2d]        = 0x%04x   ", $rule->chars_len, $rule->chars
		if $rule->chars_len > 0
			call debug_output_chomp($rule->chars, $rule->chars_len)
		end

		printf "\n"

		printf "      dots [%2d]        = 0x%04x", $rule->dots_len, $rule->dots
		if $rule->dots_len > 0
			printf "   "
			call debug_output_chomp($rule->dots, $rule->dots_len)
			printf "   "
			out_dot_string $rule->dots $rule->dots_len
		end

		printf "\n"

		printf "      filter_forward   = "
		if $rule->filter_forward > 0
			if $rule->filter_forward->name > 0
				call debug_output_chomp($rule->filter_forward->name, 0x20)
			else
				printf "0x%08x", $rule->filter_forward
				#if $rule->filter_forward->before > 0
				#	call pattern_print($rule->filter_forward->before, 0)
				#end
				#printf "   "
				#if $rule->filter_forward->after > 0
				#	call pattern_print($rule->filter_forward->after, 0)
				#end
			end
		else
			printf "NULL"
		end

		printf "\n"

		printf "      filter_backward  = "
		if $rule->filter_backward > 0
			if $rule->filter_backward->name > 0
				call debug_output_chomp($rule->filter_backward->name, 0x20)
			else
				printf "0x%08x", $rule->filter_backward
				#if $rule->filter_backward->before > 0
				#	call pattern_print($rule->filter_backward->before, 0)
				#end
				#printf "   "
				#if $rule->filter_backward->after > 0
				#	call pattern_print($rule->filter_backward->after, 0)
				#end
			end
		else
			printf "NULL"
		end

		printf "\n"

	end

end

################################################################################

define out_rule_add_new

	printf "chars      = "
	if chars > 0
		if chars_len > 0
			call debug_output_chomp(chars, chars_len)
		end
	else
		printf "NULL"
	end
	printf "\n"
	printf "chars_len  = %d\n", chars_len

	printf "dots       = "
	if chars > 0
		if dots_len > 0
			call debug_output_chomp(dots, dots_len)
		end
	else
		printf "NULL"
	end
	printf "\n"
	printf "dots_len   = %d\n", dots_len

	printf "\n"

	printf "chars_hash       = 0x%x\n", chars_hash
	printf "chars_hash_size  = %d\n", chars_hash_size
	printf "dots_hash        = 0x%x\n", dots_hash
	printf "dots_hash_size   = %d\n", dots_hash_size
	printf "filter_forward   = 0x%08x\n", filter_forward
	printf "filter_backward  = 0x%08x\n", filter_backward
	printf "hash             = %d\n", hash

	printf "\n"

	printf "rule_new:\n"
	if rule_new > 0
		out_rule rule_new
	end

	printf "\n"

	printf "rule_crs:\n"
	if rule_crs > 0
		out_rule rule_crs
	end

	printf "\n"

end

define n_rule_add_new
	next
	spacer
	out_rule_add_new
end

break rule_add_new
commands $bpnum

	set rule_new = (void*)0
	set rule_crs = (void*)0
	set hash = 0

	spacer
	out_rule_add_new

end
set $rule_add_new_bpnum = $bpnum
dis $rule_add_new_bpnum

########################################

define out_rule_match

	printf "chars      = "
	if chars > 0
		if chars_len > 0
			call debug_output_chomp(chars, chars_len)
		end
	else
		printf "NULL"
	end
	printf "\n"

	printf "chars_len  = %d\n", chars_len
	printf "hash       = %d\n", hash
	printf "hash_size  = %d\n", hash_size

	printf "\n"

	printf "rule:\n"
	if rule > 0
		out_rule rule
	end

	printf "\n"

	printf "at:\n"
	if at > 0
		out_rule at
	end

	printf "\n"

end

define n_rule_match
	next
	spacer
	out_rule_match
end

break rule_match_forward
commands $bpnum

	set rule = (void*)0
	set hash = 0

	spacer
	out_rule_match

end
set $rule_match_forward_bpnum = $bpnum
dis $rule_match_forward_bpnum

break rule_match_backward
commands $bpnum

	set rule = (void*)0
	set hash = 0

	spacer
	out_rule_match

end
set $rule_match_backward_bpnum = $bpnum
dis $rule_match_backward_bpnum

################################################################################

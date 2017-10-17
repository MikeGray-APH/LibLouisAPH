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

define out_parse_init

	set token_crs = (void*)0
	set token_len = 0
	set token_nxt = (void*)0

end

define out_parse

	if token_crs > 0
		printf "token_crs  = "
		if token_len > 0
			call debug_output_chomp(token_crs, token_len)
		end
		printf "\n"
	else
		printf "token_crs  = NULL\n"
	end
	printf "token_len  = %d\n", token_len

	if token_nxt > 0
		printf "token_nxt  = "
		call debug_output_chomp(token_nxt, 31)
		printf "\n"
	else
		printf "token_nxt  = NULL\n"
	end

	printf "\n"
end

################################################################################

define out_convert_to_dots

	out_parse

	printf "uchars      = "
	call debug_output_chomp(uchars, uchars_len)
	printf "\n"
	printf "uchars_len  = %d\n", uchars_len
	printf "crs         = %d\n", crs
	printf "off         = %d  %c\n", off, uchars[off]
	printf "cell        = 0x%04x  0b", cell
	output /t cell
	printf "\n"

	printf "\n"

end

define n_convert_to_dots
	next
	spacer
	out_convert_to_dots
end

break convert_to_dots
commands $bpnum

	set crs = 0
	set off = 0

	spacer
	out_convert_to_dots

end
set $convert_to_dots_bpnum = $bpnum
dis $convert_to_dots_bpnum

########################################

define out_convert_with_dots

	out_parse

	printf "esc        = %d\n", esc
	printf "crs        = %d\n", crs
	printf "off        = %d\n", off
	printf "cells_len  = %d\n", cells_len
	printf "cells_end  = %d\n", cells_end

	printf "\n"

end

define n_convert_with_dots
	next
	spacer
	out_convert_with_dots
end

break convert_with_dots
commands $bpnum

	set esc = 0
	set crs = 0
	set off = 0
	set cells_len = 0
	set cells_end = 0

	spacer
	out_convert_with_dots

end
set $convert_with_dots_bpnum = $bpnum
dis $convert_with_dots_bpnum

########################################

define out_compile_chars

	out_parse

	printf "unichar:\n"
	if unichar > 0
		out_unichar unichar
	end

	printf "\n"

	printf "bit  = 0x%08x\n", bit

	printf "\n"

end

define n_compile_chars
	next
	spacer
	out_compile_char
end

break compile_chars
commands $bpnum

	set unichar = (void*)0
	set bit = 0

	spacer
	out_compile_chars

end
set $compile_chars_bpnum = $bpnum
dis $compile_chars_bpnum

########################################

define out_compile_rule

	out_parse

	if chars > 0
		printf "chars      = "
		if chars_len > 0
			call debug_output_chomp(chars, chars_len)
		end
		printf "\n"
	else
		printf "chars      = NULL\n"
	end
	printf "chars_len  = %d\n", chars_len

	printf "dots       = "
	if dots_len > 0
		call debug_output_chomp(dots, 31)
	end
	printf "\n"
	printf "dots_len   = %d\n", dots_len

	printf "\n"

	printf "rule:\n"
	if rule > 0
		out_rule rule
	end

	printf "\n"

end

define n_compile_rule
	next
	spacer
	out_compile_rule
end

break compile_rule
commands $bpnum

	#   avoiding set charset
	set 'chars' = (void*)0
	set chars_len = 0
	set dots = (void*)0
	set dots_len = 0
	set rule = (void*)0

	spacer
	out_compile_rule

end
set $compile_rule_bpnum = $bpnum
dis $compile_rule_bpnum

########################################

define out_compile_pattern

	out_parse

	printf "token_tag[%2d]  = ", tag_len
	if token_tag > 0
		call debug_output_line(token_tag, tag_len)
	else
		printf "NULL\n"
	end
	printf "tag[%2d]        = ", tag_len
	if tag > 0
		call debug_output_line(tag, tag_len)
	else
		printf "NULL\n"
	end
	printf "expr_len       = %d\n", expr_len

	printf "\n"

end

define n_compile_pattern
	next
	spacer
	out_compile_pattern
end

break compile_pattern
commands $bpnum

	set subpattern = (void*)0
	set token_tag = (void*)0
	set tag = (void*)0
	set tag_len = 0
	set expr_data = (void*)0
	set expr_len = 0

	spacer
	out_compile_pattern

end
set $compile_pattern_bpnum = $bpnum
dis $compile_pattern_bpnum

########################################

define out_compile_match

	out_parse

	printf "chars[%2d]   = ", chars_len
	if chars > 0
		if chars_len > 0
			call debug_output_chomp(chars, chars_len)
		end
		printf "\n"
	else
		printf "NULL\n"
	end

	printf "dots[%2d]    = ", dots_len
	if dots > 0
		call debug_output_chomp(dots, dots_len)
		printf "\n"
	else
		printf "NULL\n"
	end
	printf "before_len  = %d\n", before_len
	printf "after_len   = %d\n", after_len

	printf "\n"

	printf "rule:\n"
	if rule > 0
		out_rule rule
	end

	printf "\n"

end

define n_compile_match
	next
	spacer
	out_compile_match
end

break compile_match
commands $bpnum

	set rule = (void*)0
	set 'chars' = (void*)0
	set dots = (void*)0
	set before = (void*)0
	set after = (void*)0
	set filter_forward = (void*)0
	set filter_backward = (void*)0
	set chars_len = 0
	set dots_len = 0
	set before_len = 0
	set after_len = 0

	spacer
	out_compile_match

end
set $compile_match_bpnum = $bpnum
dis $compile_match_bpnum

########################################

define out_compile_macro

	out_parse

	printf "table_line_begin  = %d\n", table_line_begin

	printf "\n"

	printf "ctag[%02d]  = %s\n", ctag_len, ctag
	printf "tag[%02d]   = ", tag_len
	if tag_len > 0
		call debug_output(tag, tag_len)
	end
	printf "\n"

	printf "\n"

	printf "token_line  = "
	if line_len > 0
		call debug_output(token_line, line_len)
	end
	printf "\n"
	printf "line_len    = %d\n", line_len
	printf "lines_cnt   = %d\n", lines_cnt

	printf "\n"

end

define n_compile_macro
	next
	spacer
	out_compile_macro
end

break compile_macro
commands $bpnum

	set ctag_len = 0
	set ctag[0] = 0
	set tag_len = 0
	set tag[0] = 0
	set line_len = 0
	set lines_cnt = 0
	set table_line_begin = 0

	spacer
	out_compile_macro

end
set $compile_macro_bpnum = $bpnum
dis $compile_macro_bpnum

########################################

define out_table_compile_from_file

	out_parse

	printf "cchars  = "
	output *cchars@31
	printf "\n"

	printf "\n"
end

define n_table_compile_from_file
	next
	spacer
	out_table_compile_from_file
end

break table_compile_from_file
commands $bpnum

	out_parse_init

	spacer
	out_table_compile_from_file

end
set $table_compile_from_file_bpnum = $bpnum
dis $table_compile_from_file_bpnum

################################################################################
